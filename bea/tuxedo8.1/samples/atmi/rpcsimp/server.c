/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1993 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* ident	"@(#) samples/atmi/rpcsimp/server.c	$Revision: 1.5 $" */
#include <stdio.h>
#include <ctype.h>
#include "tx.h"
#include "simp.h"

int
tpsvrinit(argc, argv)
int argc;
char **argv;
{
	if (tx_open() != TX_OK) {
		(void) userlog("tx_open failed");
		return(-1);
	}
	(void) userlog("tpsvrinit() succeeds.");
	return(1);
}

void
to_upper(str)
idl_char *str;
{
	idl_char *p;

	for (p=str; *p != '\0'; p++)
		*p = toupper((int)*p);
	return;
}

void
to_lower(str)
idl_char *str;
{
	idl_char *p;

	for (p=str; *p != '\0'; p++)
		*p = tolower((int)*p);
	return;
}
