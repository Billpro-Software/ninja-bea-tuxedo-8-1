//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univs_utils.h
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

#ifndef _univs_utils_h
#define _univs_utils_h

#include <iostream.h>
#include "univs_c.h"

//--------------------------------------------------------------------
// Print a course's synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityS::CourseSynopsis&      val
);

//--------------------------------------------------------------------
// Print a course's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityS::CourseDetails&       val
);

//--------------------------------------------------------------------
// Print a student's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityS::StudentDetails&      val
);

//--------------------------------------------------------------------
// Print a list of course numbers to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityS::CourseNumberList&    val
);

//--------------------------------------------------------------------
// Print a list of courses' synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityS::CourseSynopsisList&  val
);

//--------------------------------------------------------------------
// Print a list of coures' details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityS::CourseDetailsList&   val
);

//--------------------------------------------------------------------

#endif
