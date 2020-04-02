//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// valuetype_i.cpp
//
// Implements the valuetypes for:
//	Course
//
// and the valuetype factories:
//	Course_factory
//
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <string.h> // for "strcmp"
#include <log.h>
#include <Server.h>
#include <TP.h>
#include "valuetypes_i.h"


//
// Course_impl constructors
//

Course_impl::Course_impl()
{
}

Course_impl::Course_impl (UniversityO::CourseNumber	number,
		     double		amount,
		     unsigned short	credits,
		     const UniversityO::ClassSchedule	schedule,
		     unsigned short	seats,
		     const char *	atitle,
		     const char *	aprofessor,
		     const char *	adescription)
{
    course_number(number);
    cost(amount);
    number_of_credits(credits);
    class_schedule(schedule);
    number_of_seats(seats);
    title(atitle);
    professor(aprofessor);
    description(adescription);
}


//
// Implementation of is_taught.  Returns true if the course is taught on
// the specified day, otherwise returns false.
//
CORBA::Boolean 
Course_impl::is_taught(UniversityO::Day aDay)
{
    switch (aDay)
    {
	case UniversityO::Mon:
	    return ((class_schedule().class_days & UniversityO::MONDAY) != 0) ? CORBA_TRUE : CORBA_FALSE;
	case UniversityO::Tue:
	    return ((class_schedule().class_days & UniversityO::TUESDAY) != 0) ? CORBA_TRUE : CORBA_FALSE;
	case UniversityO::Wed:
	    return ((class_schedule().class_days & UniversityO::WEDNESDAY) != 0) ? CORBA_TRUE : CORBA_FALSE;
	case UniversityO::Thu:
	    return ((class_schedule().class_days & UniversityO::THURSDAY) != 0) ? CORBA_TRUE : CORBA_FALSE;
	case UniversityO::Fri:
	    return ((class_schedule().class_days & UniversityO::FRIDAY) != 0) ? CORBA_TRUE : CORBA_FALSE;
	default:
	    return CORBA_FALSE;
    }
}

//
// Implementation of days_taught.  Returns a string listing the days
// the course is taught in the form of "Mon Tue Wed" for a course
// that is taught on Monday, Tuesday, and Wednesday.
//
CORBA::String 
Course_impl::days_taught()
{
    CORBA::String ret = ::CORBA::string_alloc (64);	// Long enough for "Mon Tue Wed Thu Fri" and then some

    if ((class_schedule().class_days & UniversityO::MONDAY) != 0)
	strcat(ret, "Mon ");
    if ((class_schedule().class_days & UniversityO::TUESDAY) != 0)
	strcat(ret, "Tue ");
    if ((class_schedule().class_days & UniversityO::WEDNESDAY) != 0)
	strcat(ret, "Wed ");
    if ((class_schedule().class_days & UniversityO::THURSDAY) != 0)
	strcat(ret, "Thu ");
    if ((class_schedule().class_days & UniversityO::FRIDAY) != 0)
	strcat(ret, "Fri ");
    if (strlen(ret) > 0)
	ret[strlen(ret)] = '\0'; // Remove trailing space if any

    return ret;
}

//
// Implementation of start_hour.  Returns the starting hour of the course
// in miltary time, i.e., 1:00pm is 13, 0 is midnight, 12 is noon.
//
unsigned short Course_impl::start_hour()
{
    return class_schedule().start_hour;
}

//
// Implementation of duration.  Returns the length of the course in minutes.
//
unsigned short Course_impl::duration()
{
    return class_schedule().duration;
}



//
// Implementation of _copy_value.  Simple new another Course_impl and populate
// all the data members.
//
CORBA::ValueBase*
Course_impl::_copy_value()
{
    return new Course_impl(course_number(),
			   cost(),
			   number_of_credits(),
			   class_schedule(),
			   number_of_seats(),
			   title(),
			   professor(),
			   description());
}


//
// Implementation of create_for_unmarshal
//
CORBA::ValueBase*
Course_factory::create_for_unmarshal()
{
    return new Course_impl();
}


//
// Implementation of
//
UniversityO::Course* 
Course_factory::create (UniversityO::CourseNumber	course_number,
			double		cost,
			unsigned short	number_of_credits,
			const UniversityO::ClassSchedule & class_schedule,
			unsigned short	number_of_seats,
			const char *	title,
			const char *	professor,
			const char *	description)
{
    return new Course_impl(course_number,
			   cost,
			   number_of_credits,
			   class_schedule,
			   number_of_seats,
			   title,
			   professor,
			   description);
}
