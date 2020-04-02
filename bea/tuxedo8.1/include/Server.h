/*      Copyright (c) 1988 AT&T; 1991 USL; 1996, 1997 BEA
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
        SOURCE CODE OF BEA Systems Inc.
        The copyright notice above does not
        evidence any actual or intended
        publication of such source code.
*/                                      
/* #ident       "@(#)iceberg:include/Server.h  $Revision: 1.9 $" */

#ifndef _SERVER_H
#define _SERVER_H

#ifndef NOWHAT
static char h_server[] = "@(#)iceberg:include/Server.h  $Revision: 1.9 $";
#endif

// ***************************************************
// Class   : Server
// Purpose : Application interface to the TP Framework
// ***************************************************

#if defined(WIN32)
#pragma warning(disable : 4290)	// warning C4290: C++ Exception Specification ignored
#endif

#include <TobjS_c.h>
#include <Tobj_ServantBase.h>

#if defined(WIN32)
# if defined(EXPDLL_LIBNATIVE)
#  define OBBEXPDLLUSER __declspec(dllexport)
# else
#  define OBBEXPDLLUSER __declspec(dllimport)
# endif
#else
# define OBBEXPDLLUSER
#endif

class OBBEXPDLLUSER ServerBase {
public:

	virtual CORBA::Boolean
		initialize(int argc, char** argv) = 0;

	virtual void
		release() = 0;

	virtual Tobj_Servant
		create_servant(const char* interfaceName) = 0;


	// Default Implementations Supplied
	virtual Tobj_Servant
		create_servant_with_id(const char* interfaceName,
		                       const char* stroid);

	virtual CORBA::Boolean
		thread_initialize(int argc, char** argv);

	virtual void
		thread_release();
};

class Server : public ServerBase {
public:

	CORBA::Boolean initialize(int argc, char** argv);
	void release();
	Tobj_Servant create_servant(const char* interfaceName);
};

#undef OBBEXPDLLUSER

#endif // _SERVER_H
