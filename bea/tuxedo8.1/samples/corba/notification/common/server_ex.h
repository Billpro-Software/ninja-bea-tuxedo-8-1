//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// server_ex.h
//
// Utilities to help clients write info to the user log and handle
// CORBA and random exceptions.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _SERVER_EX_H_
#define _SERVER_EX_H_

#ifdef WIN32
#include <strstrea.h>
#else
#include <strstream.h>
#endif
#include "ex.h"

// write an ostream fragment to the userlog
#define REPORT(ostream_fragment)  \
                                  \
  ostrstream os;                  \
  os << ostream_fragment << ends; \
  const char* str = os.str();     \
  os.rdbuf()->freeze(0);          \
  TP::userlog("%s", str)

// catch all exceptions, report the exception to the userlog,
// then continue (v.s. rethrow)
#define CATCH_REPORT_AND_SWALLOW_EXCEPTION               \
                                                         \
  catch (CORBA::SystemException& e) {                    \
    REPORT("unexpected CORBA::SystemException : " << e); \
  }                                                      \
  catch (CORBA::Exception& e) {                          \
    REPORT("unexpected CORBA::Exception : " << e);       \
  }                                                      \
  catch (...) {                                          \
    REPORT("unexpected exception");                      \
  }

#endif
