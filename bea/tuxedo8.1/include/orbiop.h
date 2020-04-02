/*	Copyright (c) 1997 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) objtm/include/orbiop.h	$Revision: 1.7 $" */


#ifndef _ORBIOP_H
#define _ORBIOP_H

#ifndef NOWHAT
static char h_orbiop[] = "@(#)iceberg:include/orbiop.h  $Revision: 1.7 $";
#endif

#include <CORBA.h>

#if defined(__hpux) && defined(__cplusplus) && __cplusplus >= 199707L
#define NS_CORBA(attr)	CORBA::attr
#define NS_BA(attr)	BA::attr
#define NS_TPFC(attr)	TPFC::attr
#define NS_NS(attr)	CosNaming::attr
#define NS_LCS(attr)	CosLifeCycle::attr
#define NS_OTS(attr)	CosTransactions::attr
#define NS_TOBJ(attr)	Tobj::attr
#else
#define NS_CORBA(attr)	CORBA:: ## attr
#define NS_BA(attr)		BA:: ## attr
#define NS_TPFC(attr)	TPFC:: ## attr
#define NS_NS(attr)		CosNaming:: ## attr
#define NS_LCS(attr)	CosLifeCycle:: ## attr
#define NS_OTS(attr)	CosTransactions:: ## attr
#define NS_TOBJ(attr)	Tobj:: ## attr
#endif

#ifndef NOEXCEPTIONS	// Compiler supports C++ Exceptions

#define IDL_ENV			
#define IDL_C_ENV		
#define IDL_DFN_ENV
#define IDL_DCL_ENV		
#define IDL_DCL_I_ENV	
#define IDL_DCL_C_ENV 	
#define IDL_DCL_C_I_ENV

#define IDL_CHECK_ENV() \
{ }

#define IDL_INIT_THROW() \
{ }

#define IDL_THROW0(CLASS) \
{ \
  throw CLASS(); \
}

#define IDL_THROW0_RETURN(CLASS) \
{ \
  throw CLASS(); \
}

#define IDL_THROW0_RTNVAL(CLASS, RTNVAL) \
{ \
  throw CLASS(); \
}

#define IDL_THROW1(CLASS, ARG1) \
{ \
  throw CLASS(ARG1); \
}

#define IDL_THROW1_RETURN(CLASS, ARG1) \
{ \
  throw CLASS(ARG1); \
}

#define IDL_THROW1_RTNVAL(CLASS, ARG1, RTNVAL) \
{ \
  throw CLASS(ARG1); \
}

#else // Define for CORBA environment variables

#define IDL_ENV			IT_env
#define IDL_C_ENV		,IDL_ENV
#define IDL_DFN_ENV		NS_CORBA(Environment) IDL_ENV
#define IDL_DCL_ENV		NS_CORBA(Environment)& IDL_ENV
#define IDL_DCL_I_ENV	IDL_DCL_ENV					// =Tobj::default_environment
#define IDL_DCL_C_ENV 	,IDL_DCL_ENV
#define IDL_DCL_C_I_ENV	,IDL_DCL_ENV				// =Tobj::default_environment

#define IDL_CHECK_ENV() \
{ if (IT_env.exception()) { _ev2ex(IT_env); } }

#define IDL_INIT_THROW() \
{ IT_env.exception(NULL); }

#define IDL_THROW0(CLASS) \
{ CLASS* _ex = new ORBNEWTHROW CLASS; \
  IT_env.exception(_ex); \
  throw CLASS(); \
}

#define IDL_THROW1(CLASS, ARG1) \
{ CLASS* _ex = new ORBNEWTHROW CLASS(ARG1); \
  IT_env.exception(_ex); \
  throw CLASS(ARG1); \
}

#define IDL_THROW0_RETURN(CLASS) \
{ CLASS* _ex = new ORBNEWTHROW CLASS; \
  IT_env.exception(_ex); \
  return; \
}

#define IDL_THROW0_RTNVAL(CLASS, RTNVAL) \
{ CLASS* _ex = new ORBNEWTHROW CLASS; \
  IT_env.exception(_ex); \
  return RTNVAL; \
}

#define IDL_THROW1_RETURN(CLASS, ARG1) \
{ CLASS* _ex = new ORBNEWTHROW CLASS(ARG1); \
  IT_env.exception(_ex); \
  return; \
}


#define IDL_THROW1_RTNVAL(CLASS, ARG1, RTNVAL) \
{ CLASS* _ex = new ORBNEWTHROW CLASS(ARG1); \
  IT_env.exception(_ex); \
  return RTNVAL; \
}

#endif

const NS_CORBA(Boolean) ORB_TRUE = CORBA_TRUE;
const NS_CORBA(Boolean) ORB_FALSE = CORBA_FALSE;

void _ev2ex (IDL_DCL_I_ENV);


// The following class is used to work around warnings issued by g++ on
// Linux whenever a class has only private constructors or destructors,
// or all of its other members are private, and the class has no friend
// classes.  Because the warnings cannot be selectively suppressed, we
// get rid of them by specifying a do-nothing friend class (this one)
// in any class getting such warnings.
//
#ifdef __linux__
class FalseFriend_orbiop
{
    public:
        FalseFriend_orbiop() {};
        ~FalseFriend_orbiop() {};
};
#endif

#endif	// _ORBIOP_H
