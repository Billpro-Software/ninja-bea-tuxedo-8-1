//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// course_is.h
//
// Declares the C++ implementations for the course valuetype and its
// factory on the server.
//
// Classes declared :
//
//   Course_impl
//   Course_factory
//
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _course_is_h
#define _course_is_h

//--------------------------------------------------------------------

#include "univo_c.h"

//--------------------------------------------------------------------

class Course_impl : virtual public OBV_UniversityO::Course,
		    virtual public CORBA::DefaultValueRefCountBase
{
    public:
	Course_impl();
	Course_impl (UniversityO::CourseNumber	course_number,
		     double		cost,
		     unsigned short	number_of_credits,
		     const UniversityO::ClassSchedule	class_schedule,
		     unsigned short	number_of_seats,
		     const char *	title,
		     const char *	professor,
		     const char *	description);
	CORBA::Boolean is_taught(UniversityO::Day aDay);
	CORBA::String days_taught();
	unsigned short start_hour();
	unsigned short duration();

	CORBA::ValueBase* _copy_value();
};

class Course_factory : virtual public UniversityO::Course_init
{
    public:
	CORBA::ValueBase * create_for_unmarshal();
	UniversityO::Course * create (UniversityO::CourseNumber	course_number,
				      double		cost,
				      unsigned short	number_of_credits,
				      const UniversityO::ClassSchedule & class_schedule,
				      unsigned short	number_of_seats,
				      const char *	title,
				      const char *	professor,
				      const char *	description);
};

#endif

