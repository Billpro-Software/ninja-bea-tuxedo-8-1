/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/* Copyright (c) 1994 Novell Inc. */

/* #ident	"@(#) samples/atmi/rpcsimp/dcebind.c	$Revision: 1.5 $" */

#include <stdio.h>
#include <stdlib.h>
#include <dce/dce_error.h>	/* required to call dce_error_inq_text */
#include <dce/idlbase.h>	/* base data types */
#include <dce/rpc.h>		/* rpc_ types, prototypes */
#include <dce/binding.h>	/* binding to registry */
#include <dce/pgo.h>		/* registry i/f */
#include <dce/secidmap.h>	/* translate global name -> princ name */
#include <dce/sec_login.h>	/* sec_login types/prototypes */

/* DEFINITIONS FOR APPLICATION MANAGER */

/* Define the name of the server in the directory */
#define SERVER_NAME		"/.:/changecase_<HOST>"

/* Define group of which principal must be a member */
#define SERVER_PRINCIPAL_GROUP	"<SERVER_PRINCIPAL_GROUP>"

/* interface specification */
#define INTERFACE_SPEC		changecase_v1_0_c_ifspec

/* interface header */
#define INTERFACE_HDR		"simpdce.h"

/* END DEFINITIONS FOR APPLICATION MANAGER */

/* status checking macro */
#define RESUME 0
#define ABORT  1

#define CHECK_STATUS(input_status, comment, action) \
{ \
	if(input_status != rpc_s_ok) { \
		dce_error_inq_text(input_status, error_string, &error_stat); \
		fprintf(stderr, "%s %s\n", comment, error_string); \
		if(action == ABORT) \
			return(-1); \
	} \
}

/* end status checking */


#include INTERFACE_HDR		/* header created by the IDL compiler */

int
dobind(rpc_binding_handle_t *binding_handle)
{
	int			error_stat;	/* last error status */
	unsigned char		error_string[dce_c_error_string_len];
	unsigned32		status;		/* error status */
	sec_login_handle_t	login_context;	/* current login context */
	rpc_ns_handle_t		import_context;	/* import binding query */
	sec_rgy_handle_t	rgy_handle;	/* registry query */
	sec_rgy_name_t		princ_name;	/* principal name for server */
	unsigned_char_t		*server_princ_name;	/* principal name */
	boolean32		is_member;	/* member of group */

	/*
	 * Get server binding from the name space.
	 */

	rpc_ns_binding_import_begin(	/* set context to import handles */
		rpc_c_ns_syntax_dce,	/* dce syntax */
		(unsigned_char_t *)SERVER_NAME,	/* search using this name */
		INTERFACE_SPEC,		/* interface specification */
		NULL,			/* no optional object UUID required */
		&import_context,	/* import context obtained */
		&status);
	CHECK_STATUS(status, "Import begin failed", ABORT);

	rpc_ns_binding_import_next(
		import_context,		/* context from import_begin */
		binding_handle,		/* binding handle obtained */
		&status);
	CHECK_STATUS(status, "Import next failed", ABORT);

	rpc_ns_binding_import_done(
		&import_context,	/* close context from import_begin */
		&status);
	CHECK_STATUS(status, "Import done failed", ABORT);

	/*
	 * Determine the server's principal name.
	 */
	rpc_ep_resolve_binding(
		*binding_handle,	/* resolve server's binding handle */
		INTERFACE_SPEC,		/* interface specification */
		&status);
	CHECK_STATUS (status, "resolve_binding failed", ABORT);

	rpc_mgmt_inq_server_princ_name(
		*binding_handle,	/* server's binding handle */
		rpc_c_authn_dce_secret,	/* DCE shared-secret key authen. */
		&server_princ_name,	/* obtained principal name */
		&status);
	CHECK_STATUS (status, "inq_princ_name failed", ABORT);

	/*
	 * Find out if the principal name that is returned by the
	 * server is a member of SERVER_PRINCIPAL_GROUP.
	 */

	/* Open a registry site for query */
	sec_rgy_site_open_query(
		NULL,			/* use local cell site name */
		&rgy_handle,		/* obtained handle */
		&status);
	CHECK_STATUS (status, "rgy_site_open failed", ABORT);

	/*
	 * Ask the Security registry to translate the global principal
	 * name into a simple principal name.
	 */
	sec_id_parse_name(
		rgy_handle,		/* obtained handle */
		server_princ_name,	/* full (global) name of principal */
		NULL,			/* returned home cell name */
		NULL,			/* returned home uuid */
		princ_name,		/* returned local principal name */
		NULL,			/* returned principal uuid */
		&status);
	CHECK_STATUS (status, "sec_id_parse_name failed", ABORT);

	/* The group membership check. */
	is_member = sec_rgy_pgo_is_member(
		rgy_handle,		/* obtained handle */
		sec_rgy_domain_group,	/* check if member of domain group */
		(unsigned_char_t *)SERVER_PRINCIPAL_GROUP,/* group name */
		princ_name,		/* principal name */
		&status);
	CHECK_STATUS (status, "is_member failed", ABORT);

	/*
	 * We are done with the registry; we can release the
	 * rgy_handle now.
	 */
	sec_rgy_site_close(rgy_handle, &status);
	CHECK_STATUS (status, "rgy_site_close failed", ABORT);

	if (!is_member) {
		fprintf(stderr, "got an imposter\n");
		return(-1);
	}

	/*
	 * Annotate our binding handle for authentication.
	 */
	sec_login_get_current_context(
		&login_context,		/* current login context */
		&status);
	CHECK_STATUS (status, "sec_login_get_current_context failed", ABORT);

	rpc_binding_set_auth_info(
		*binding_handle,	/* binding handle for server */
		server_princ_name,	/* principal name */
		rpc_c_protect_level_pkt_integ,	/* packet level integrity */
		rpc_c_authn_dce_secret,	/* DCE shared-secret key authen. */
		login_context,		/* current login context */
		rpc_c_authz_dce,	/* author.  using client's PAC */
		&status);
	CHECK_STATUS (status, "binding_set_auth_info failed", ABORT);

	return(0);
}
