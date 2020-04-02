/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1998 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/


// MODULE NAME:
//
//    SamplesDB.cpp
//
// FACILITY:
//
//    Samples 
//
// ABSTRACT:
//
//    This file contains C++ class print methods for SamplesDBExceptions
//
//    
//
// CLASSES CONTAINED IN THIS MODULE:
//    
//
// AUTHORS:	Mark Scanlon, Martin Varela
//		
// CREATION DATE: 4-Feb-1998
//
//

#include "samplesdb.h"

// *********************************
// SamplesDBException classes print
// *********************************

ostream& SamplesDBException::print(ostream& os)
{
 return os << "SamplesDBException " ;
}

ostream& SamplesCannotConnectDatabase::print(ostream& os)
{
 return os << "SamplesCannotConnectDatabase " ;
}

ostream& SamplesDatabaseNotConnected::print(ostream& os)
{
 return os << "SamplesDatabaseNotConnected " ;
}

ostream& SamplesBadStudentId::print(ostream& os)
{
 return os << "SamplesBadStudentId " ;
}

ostream& SamplesBadCourseId::print(ostream& os)
{
 return os << "SamplesBadCourseId " ;
}

ostream& SamplesNoMoreItems::print(ostream& os)
{
 return os << "SamplesNoMoreItems " ;
}

ostream& SamplesNoMatches::print(ostream& os)
{
 return os << "SamplesNoMatches " ;
}

ostream& SamplesCourseRegFull::print(ostream& os)
{
 return os << "SamplesCourseRegFull " ;
}

ostream& SamplesAlreadyRegistered::print(ostream& os)
{
 return os << "SamplesAlreadyRegistered " ;
}

ostream& SamplesDbError::print(ostream& os)
{
 return os << "SamplesDbError " ;
}
