//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univo_utils.cpp
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

#include "univo_utils.h"

//--------------------------------------------------------------------
// Print a course's synopsis to an ostream

ostream&
operator<<(
    ostream&                           os,
    const UniversityO::CourseSynopsis& val
)
{
    return os << val.course_number << '\t' << val.title.in();
}

//--------------------------------------------------------------------
// Print a course's details to an ostream

ostream&
operator<<(
    ostream&                          os,
    const UniversityO::Course_ptr crs
)
{
    os << crs->course_number() << '\t' << crs->title() << endl;

    os << "cost $" << crs->cost()
       << '\t' << "credits " << crs->number_of_credits()
       << endl;

    {
        // convert the start hour from military time to "civilian" time:
        CORBA::UShort start = crs->start_hour();

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
        CORBA::UShort duration = crs->duration();
        CORBA::UShort hours    = duration / 60;
        CORBA::UShort minutes  = duration - (60*hours);
        os << ", duration " << hours << ':' << minutes;
    }

    {
        os << '\t';
	os << crs->days_taught();
        os << endl;
    }

    os << crs->number_of_seats() << " seats" << endl;

    os << "taught by " << crs->professor() << endl;

    os << crs->description();

    return os;
}

//--------------------------------------------------------------------
// Print a list of course numbers to an ostream

ostream&
operator<<(
    ostream&                             os,
    const UniversityO::CourseNumberList& val
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
    const UniversityO::CourseSynopsisList& val
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
    const UniversityO::Courses& val
)
{

    for (CORBA::ULong i = 0; i < val.length(); i++) {
        os << endl << endl << val[i];
    }
    return os;
}

//--------------------------------------------------------------------
