//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//
// ex.h
//
// Utilities to print out CORBA exceptions.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _EX_H_
#define _EX_H_

#include <CORBA.h>
#include <iostream.h>

#ifdef minor
#undef minor
#endif

// exception handling utilities

// print out a completion status
static ostream& operator<<(ostream& os, CORBA::CompletionStatus s)
{
  switch (s) {
    case CORBA::COMPLETED_YES   : return os << "yes"   ;
    case CORBA::COMPLETED_NO    : return os << "no"    ;
    case CORBA::COMPLETED_MAYBE : return os << "maybe" ;
  }
  return os << (int)s; // out of range
}

// print out a CORBA exception
static ostream& operator<<(ostream& os, CORBA::Exception& e)
{
  return os << e.get_id(); // repository id
}

// print out a CORBA system exception
// (prints out the minor code in decimal and hex)

// NOTE : Some exceptions are raised by the notification service
// and some are raised by the ORB.  All the minor codes (in hex)
// for exceptions raised by the notification service can be found
// in the notification idl files (Tobj_Events.idl and
// Tobj_Notification.idl).  So, if an exception has been raised,
// try looking in these idl files for a matching minor code.
// If the exception was raised by the notification service, then
// you'll find more details about why the exception was raised.

static ostream& operator<<(ostream& os, CORBA::SystemException& e)
{
  return
    os
      << e.get_id()                               // repository id
      << ", minor = " << dec << e.minor()         // minor code in decimal
      << " (0x" << hex << e.minor() << ")" << dec // minor code in hex
      << ", completed = " << e.completed()        // completion status
   ;
}

#endif
