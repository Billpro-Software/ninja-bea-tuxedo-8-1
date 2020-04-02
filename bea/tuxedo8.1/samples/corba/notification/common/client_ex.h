//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// client_ex.h
//
// Utilities to help clients handle CORBA and random exceptions.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _CLIENT_EX_H_
#define _CLIENT_EX_H_

#include "ex.h"

// catch all exceptions, report the exception to standard error,
// then continue (v.s. rethrow)
#define CATCH_REPORT_AND_SWALLOW_EXCEPTION                       \
                                                                 \
  catch (CORBA::SystemException& e) {                            \
    cerr << "unexpected CORBA::SystemException : " << e << endl; \
  }                                                              \
  catch (CORBA::Exception& e) {                                  \
    cerr << "unexpected CORBA::Exception : " << e << endl;       \
  }                                                              \
  catch (...) {                                                  \
    cerr << "unexpected exception" << endl;                      \
  }

#endif
