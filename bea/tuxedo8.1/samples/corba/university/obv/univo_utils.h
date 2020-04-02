//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univo_utils.h
//
// Declares university specific utilities for the university
// sample application
//
// Utilities include printing functions for the various course and
// student datatypes.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _univo_utils_h
#define _univo_utils_h

#include <iostream.h>
#include "univo_c.h"

//--------------------------------------------------------------------
// Print a course's synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityO::CourseSynopsis&      val
);

//--------------------------------------------------------------------
// Print a course's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    UniversityO::Course&       val
);

//--------------------------------------------------------------------
// Print a list of course numbers to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityO::CourseNumberList&    val
);

//--------------------------------------------------------------------
// Print a list of courses' synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityO::CourseSynopsisList&  val
);

//--------------------------------------------------------------------
// Print a list of courses' details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityO::Courses&   val
);

//--------------------------------------------------------------------

#endif
