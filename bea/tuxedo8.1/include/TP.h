/*	Copyright (c) 1997 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) objtm/include/TP.h	$Revision: 1.8 $" */


#ifndef _TP_H
#define _TP_H

#ifndef NOWHAT
static char h_tp[] = "@(#)iceberg:include/tp.h  $Revision: 1.8 $";
#endif

// *************************************
// Class    : TP
// Purpsose : TP Framework Externals API
// *************************************

#if defined(WIN32)
#pragma warning(disable : 4290)	// warning C4290: C++ Exception Specification ignored
#endif

#include <orbiop.h>
#include <TobjS_c.h>
#include <Tobj_Bootstrap.h>
#include <Tobj_ServantBase.h>

#ifdef WIN32
# ifdef EXPDLL_LIBNATIVE
#  define EXPORTXXX __declspec(dllexport)
# else
#  define EXPORTXXX __declspec(dllimport)
# endif
#else
# define EXPORTXXX
#endif

class EXPORTXXX TP {
public:

	// ----------  Class Object Reference  ----------

	static CORBA::Object_ptr
		create_object_reference(const char* interfaceName, 
								const char* stroid,
								CORBA::NVList_ptr criteria IDL_DCL_C_I_ENV);
	static CORBA::Object_ptr
		create_active_object_reference(const char* interfaceName, 
								const char* stroid,
								Tobj_Servant servant IDL_DCL_C_I_ENV);
	static CORBA::Object_ptr
		get_object_reference(IDL_DCL_I_ENV);
	
	static char * 
		get_object_id(CORBA::Object_ptr objp IDL_DCL_I_ENV);
		
	// ----------  Class FactoryFinder  ----------

	static void
		register_factory(CORBA::Object_ptr objp, const char* id IDL_DCL_C_I_ENV);

	static void
		unregister_factory(CORBA::Object_ptr objp, const char* id IDL_DCL_C_I_ENV);

	// ----------  Class Application-controlled deactivation  ----------

	static void deactivateEnable(IDL_DCL_I_ENV);

	static void deactivateEnable(const char* interfaceName, 
								const char* stroid,
								Tobj_Servant servant IDL_DCL_C_I_ENV);

	// ----------  Class ORB Access  ----------

	static NS_CORBA(ORB_ptr)
		orb(IDL_DCL_I_ENV);
	static Tobj_Bootstrap*
		bootstrap(IDL_DCL_I_ENV);

	// ----------  Class XA Utilities  ----------

	static void open_xa_rm(IDL_DCL_I_ENV);
	static void close_xa_rm(IDL_DCL_I_ENV);

	// ----------  Class Public Utilities  ----------

	static int
		userlog(char *, ... );

	static void application_responsibility(Tobj_Servant servant IDL_DCL_C_I_ENV);

private:
	
	// ----------  Class Private Utilities  ----------

	static void
		do_reg_task(int bind, CORBA::Object_ptr objp, const char* id IDL_DCL_C_I_ENV);
};

#undef EXPORTXXX

#endif // _TP_H
