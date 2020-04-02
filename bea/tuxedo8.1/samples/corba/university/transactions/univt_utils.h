//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univt_utils.h
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

#ifndef _univt_utils_h
#define _univt_utils_h

#include <iostream.h>
#include "univt_c.h"

//--------------------------------------------------------------------
// Print a course's synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::CourseSynopsis&      val
);

//--------------------------------------------------------------------
// Print a course's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::CourseDetails&       val
);

//--------------------------------------------------------------------
// Print a student's details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::StudentDetails&      val
);

//--------------------------------------------------------------------
// Print the reason why a student couldn't register for a
// course to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::NotRegisteredReason& val
);

//--------------------------------------------------------------------
// Print the reason why a student couldn't register for a course
// along with the course's number to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::NotRegistered&       val
);

//--------------------------------------------------------------------
// Print a list of course numbers to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::CourseNumberList&    val
);

//--------------------------------------------------------------------
// Print a list of courses' synopsis to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::CourseSynopsisList&  val
);

//--------------------------------------------------------------------
// Print a list of coures' details to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::CourseDetailsList&   val
);

//--------------------------------------------------------------------
// Print a list of courses that a student couldn't register for
// along with the reasons why to an ostream

extern ostream&
operator<<(
    ostream&                                os,
    const UniversityT::NotRegisteredList&   val
);

//--------------------------------------------------------------------

#endif
