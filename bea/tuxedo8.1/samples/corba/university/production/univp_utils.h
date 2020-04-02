//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univp_utils.h
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

#ifndef _univp_utils_h
#define _univp_utils_h

#include <iostream.h>
#include "univp_c.h"

//--------------------------------------------------------------------
// Print a course's synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::CourseSynopsis&      val
);

//--------------------------------------------------------------------
// Print a course's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::CourseDetails&       val
);

//--------------------------------------------------------------------
// Print a student's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::StudentDetails&      val
);

//--------------------------------------------------------------------
// Print the reason why a student couldn't register for a
// course to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::NotRegisteredReason& val
);

//--------------------------------------------------------------------
// Print the reason why a student couldn't register for a course
// along with the course's number to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::NotRegistered&       val
);

//--------------------------------------------------------------------
// Print a list of course numbers to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::CourseNumberList&    val
);

//--------------------------------------------------------------------
// Print a list of courses' synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::CourseSynopsisList&  val
);

//--------------------------------------------------------------------
// Print a list of coures' details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::CourseDetailsList&   val
);

//--------------------------------------------------------------------
// Print a list of courses that a student couldn't register for
// along with the reasons why to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityP::NotRegisteredList&   val
);

//--------------------------------------------------------------------

#endif
