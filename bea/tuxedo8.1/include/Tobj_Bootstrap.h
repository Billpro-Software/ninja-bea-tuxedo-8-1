/*	Copyright (c) 1997 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) objtm/include/Tobj_Bootstrap.h	$Revision: 1.4 $" */


#ifndef TOBJ_BOOTSTRAP_H
#define TOBJ_BOOTSTRAP_H

#ifndef NOWHAT
static	char	h_tobj_bootstrap[] = "@(#)iceberg:include/Tobj_Bootstrap.h	$Revision: 1.4 $";
#endif

#include <CORBA.h>

class DynamicLibrary;

#if defined(WIN32)
# if defined(EXPDLL_LIBENV)
#  define OBBEXPDLLUSER __declspec(dllexport)
# else
#  define OBBEXPDLLUSER __declspec(dllimport)
# endif
#else
# define OBBEXPDLLUSER
#endif

class OBBEXPDLLUSER Tobj_Bootstrap {
private:
	Tobj_Bootstrap *m_impl;
	DynamicLibrary *m_lib;
protected:
	Tobj_Bootstrap() { m_impl = 0; m_lib = 0; }
public:
	Tobj_Bootstrap(CORBA::ORB* orb, const char* address);
	virtual ~Tobj_Bootstrap();
	virtual CORBA::Object_ptr
			resolve_initial_references(const char* id);
	virtual void destroy_current();
	virtual void register_callback_port(CORBA::Object_ptr objref);
private:
	Tobj_Bootstrap( const Tobj_Bootstrap&) { } //Make private to prevent copy by appl
	void operator=(const Tobj_Bootstrap&) { }

};

#undef OBBEXPDLLUSER

#endif /* TOBJ_BOOTSTRAP_H */
