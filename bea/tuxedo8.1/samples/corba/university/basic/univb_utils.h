//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univb_utils.h
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

#ifndef _univb_utils_h
#define _univb_utils_h

#include <iostream.h>
#include "univb_c.h"

//--------------------------------------------------------------------
// Print a course's synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityB::CourseSynopsis&      val
);

//--------------------------------------------------------------------
// Print a course's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityB::CourseDetails&       val
);

//--------------------------------------------------------------------
// Print a list of course numbers to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityB::CourseNumberList&    val
);

//--------------------------------------------------------------------
// Print a list of courses' synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityB::CourseSynopsisList&  val
);

//--------------------------------------------------------------------
// Print a list of coures' details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityB::CourseDetailsList&   val
);

//--------------------------------------------------------------------

#endif
