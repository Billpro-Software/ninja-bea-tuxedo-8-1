//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univb_utils.cpp
//
// Implements university specific utilities for the university
// sample application
//
// Utilities include printing functions) for the various course
// and student datatypes.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include "univb_utils.h"

//--------------------------------------------------------------------
// Print a course's synopsis to an ostream

ostream&
operator<<(
    ostream&                           os,
    const UniversityB::CourseSynopsis& val
)
{
    return os << val.course_number << '\t' << val.title.in();
}

//--------------------------------------------------------------------
// Print a course's details to an ostream

ostream&
operator<<(
    ostream&                          os,
    const UniversityB::CourseDetails& val
)
{
    os << val.course_number << '\t' << val.title.in() << endl;

    os << "cost $" << val.cost
       << '\t' << "credits " << val.number_of_credits
       << endl;

    {
        // convert the start hour from military time to "civilian" time:
        CORBA::UShort start = val.class_schedule.start_hour;

        os << "starts at ";
        if (start == 0) {
            os << "12 am";
        } else if (1 <= start && start <= 11) {
            os << start << " am";
        } else if (start == 12) {
            os << "12 pm";
        } else if (13 <= start && start <= 23) {
            os << (start - 12) << " pm";
        } else {
            os << "illegal start hour : " << start;
        }
    }

    {
        // convert the duration from minutes to hours and minutes
        CORBA::UShort duration = val.class_schedule.duration;
        CORBA::UShort hours    = duration / 60;
        CORBA::UShort minutes  = duration - (60*hours);
        os << ", duration " << hours << ':' << minutes;
    }

    {
        os << '\t';
        UniversityB::Days days =
            val.class_schedule.class_days;
        if ( days & UniversityB::MONDAY    ) { os << "mon "; }
        if ( days & UniversityB::TUESDAY   ) { os << "tue "; }
        if ( days & UniversityB::WEDNESDAY ) { os << "wed "; }
        if ( days & UniversityB::THURSDAY  ) { os << "thu "; }
        if ( days & UniversityB::FRIDAY    ) { os << "fri "; }
        os << endl;
    }

    os << val.number_of_seats << " seats" << endl;

    os << "taught by " << val.professor.in() << endl;

    os << val.description.in();

    return os;
}

//--------------------------------------------------------------------
// Print a list of course numbers to an ostream

ostream&
operator<<(
    ostream&                             os,
    const UniversityB::CourseNumberList& val
)
{
    for (CORBA::ULong i = 0; i < val.length(); i++) {
        os << endl << val[i];
    }
    return os;
}

//--------------------------------------------------------------------
// Print a list of courses' synopsis to an ostream

ostream&
operator<<(
    ostream&                               os,
    const UniversityB::CourseSynopsisList& val
)
{
    for (CORBA::ULong i = 0; i < val.length(); i++) {
        os << endl << val[i];
    }
    return os;
}

//--------------------------------------------------------------------
// Print a list of coures' details to an ostream

ostream&
operator<<(
    ostream&                              os,
    const UniversityB::CourseDetailsList& val
)
{
    for (CORBA::ULong i = 0; i < val.length(); i++) {
        os << endl << endl << val[i];
    }
    return os;
}

//--------------------------------------------------------------------
