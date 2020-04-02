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
