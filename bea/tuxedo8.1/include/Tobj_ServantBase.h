/*      Copyright (c) 1988 AT&T; 1991 USL; 1996, 1997 BEA
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
        SOURCE CODE OF BEA Systems Inc.
        The copyright notice above does not
        evidence any actual or intended
        publication of such source code.
*/                                      

#ifndef TOBJ_SERVANTBASE_H
#define TOBJ_SERVANTBASE_H

#ifndef NOWHAT
static	char	h_tobj_servantbase[] = "@(#)iceberg:include/Tobj_ServantBase.h	$Revision: 1.6 $";
#endif

#if defined(WIN32)
#pragma warning(disable : 4290)	// warning C4290: C++ Exception Specification ignored
#endif

#include <orbiop.h>
#include <TobjS_c.h>
#include <PortableServer.h>

class Tobj_ServantBase : public PortableServer::RefCountServantBase {
public:
	
	Tobj_ServantBase& operator=(const Tobj_ServantBase&);
	Tobj_ServantBase() {}
	Tobj_ServantBase(const Tobj_ServantBase& s) :
		PortableServer::RefCountServantBase(s) {}

	virtual void activate_object(const char *) {}

	virtual void deactivate_object(const char*,
		TobjS::DeactivateReasonValue) {}

	virtual CORBA::Boolean _is_reentrant() { return CORBA_FALSE; }
};

typedef Tobj_ServantBase * Tobj_Servant;

#endif
