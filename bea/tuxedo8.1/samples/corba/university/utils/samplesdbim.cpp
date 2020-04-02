/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*      Copyright (c) 1998 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/


// MODULE NAME:
//
//    samplesdbim.cpp
//
// FACILITY:
//
//    samples 
//
// ABSTRACT:
//
//    This include file contains C++ class methods that implements access to
//    an in-memory database. Classes are
//
//      CourseSynopsisIM
//      CourseSynopsisIteratorIM
//      ClassScheduleIM
//      CourseIM
//      StudentIM
//      DatabaseIM
//    
//
// CLASSES CONTAINED IN THIS MODULE:
//    
//
// AUTHORS:     Mark Scanlon, Martin Varela
//              
// CREATION DATE: 4-Feb-1998
//
//

#ifdef WIN32
#include <windows.h>
#else
#include <ctype.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// *IM* Added for abs() for dummy data
//
#include <math.h>

#include <TP.h>
#include <userlog.h>

#ifdef NO_TRACING
#undef NO_TRACING
#endif

#ifndef DB_TRACING
#define NO_TRACING
#endif

#include "samplesdbim.h"


    // Define a host structure for the output values of a SELECT statement
    // Lets define separate structures for each of the classes so that these
    // do not get trashed underneath us.

    struct courseSynDat {
        unsigned long     id;
        char    title[22];
    } CourseSynRec;

    struct courseSIDat {
        unsigned long     id;
    } CourseSIRec;

    struct courseDat {
        unsigned long     id;
        char              title[22];
        char              desc[52];
        float             amount;
        char              professor[32];
        unsigned short    seats;
        unsigned short    credits;
        unsigned short    reg_students;
    } CourseRec;

    struct courseNIDat {
        unsigned long     id;
    } CourseNIRec;

    struct RegnDat {
        unsigned long     stud_id;
        unsigned long     course_id;
        unsigned short    seats;
        unsigned short    reg_students;
    } RegnRec;

    struct classScheduleDat {
        unsigned long     id;
        unsigned short    start_hr;
        unsigned short    duration;
        char      monday_scheduled;
        char      tuesday_scheduled;
        char      wednesday_scheduled;
        char      thursday_scheduled;
        char      friday_scheduled;
    } ClassScheduleRec;

    struct studentDat {
        unsigned long     id;
        char              name[21];
        unsigned long     account;
    } StudentRec;


    char          search[21];

    int   count;

//
// *IM*
// We create some temporary datastructures to hold artifical in-memory
// data until the TopEnd stuff is hooked up.
//
#define MAX_COURSE_SI 4
unsigned long IM_course_si_rec[MAX_COURSE_SI]; 
unsigned long IM_course_ni_rec[MAX_COURSE_SI]; 

// Forward declare the getEnvVariable function
unsigned long   getEnvVariable( char * envVarName,
				char * envVarValue,
				unsigned long envValueLen);

static unsigned short   sqlConnected = CORBA_FALSE;

//
//class CourseSynopsisIM
//
CourseSynopsisIM::CourseSynopsisIM(CourseNumber course_number)
{
    // TRACE_METHOD("CourseSynopsisIM");
    // TRACE("CourseNumber : " << course_number);

    // Query the database for the Course title

    CourseSynRec.id = course_number;

    // TRACE("Found COURSE : " << course_number);

    m_course_number = course_number;

    //
    // *IM* This needs to be replaced by code which takes the course
    // number, calls the database server and gets the course title
    //
    switch (course_number)
    {
        case 100001:
            strcpy(CourseSynRec.title,"Fundamentals of CS");
            m_title = new char[ strlen(CourseSynRec.title) + 1 ];
            strcpy(m_title, (char *) CourseSynRec.title);
            break;
        case 100002:
            strcpy(CourseSynRec.title,"Foundations of CS");
            m_title = new char[ strlen(CourseSynRec.title) + 1 ];
            strcpy(m_title, (char *) CourseSynRec.title);
            break;
        case 100003:
            strcpy(CourseSynRec.title,"Intro to Algorithms");
            m_title = new char[ strlen(CourseSynRec.title) + 1 ];
            strcpy(m_title, (char *) CourseSynRec.title);
            break;
        case 100004:
            strcpy(CourseSynRec.title,"Advanced Algorithms");
            m_title = new char[ strlen(CourseSynRec.title) + 1 ];
            strcpy(m_title, (char *) CourseSynRec.title);
            break;
    }
}

CourseSynopsisIM::~CourseSynopsisIM()
{
    delete[] m_title;
}


//
//class CourseSynopsisIteratorIM
//
CourseSynopsisIteratorIM::CourseSynopsisIteratorIM(
                            const char* search_criteria) 
{
    // SQL Command to select based on search_criteria

    // TRACE_METHOD("CourseSynopsisIteratorIM");
    // TRACE("Search Criteria : " << search_criteria);


    // Get the count of all courses matching the search criteria before actually
    // getting each of the course description records.

    if (search_criteria != NULL)
    {

            //
            // *IM* We were given a search criteria and we need
            // to do a call to a database to get the count of
            // courses matching the search criteria in search.arr
            // For now we will artificially seed a structure with four
            // course ids that we supposedly found.
            //
            count = MAX_COURSE_SI;

    }
    else
        //
        // *IM* We were not given a search criteria which means we
        // should do a wildcard and get back all the course numbers
        // For now we will articially seed a structure with four
        // course ids that we supposedly found.
        //
        count = MAX_COURSE_SI;

	   // TRACE("Found COURSE : " << search_criteria);

	   m_count = count;


        //
        // *IM* We just stuff some in-memory data so that when we
        // use the next on the iterator we can return something. We will
        // need to do a call here to TopEnd to get back an array of
        // the course numbers that match the search criteria (ie contain
        // the string in the course title, description or professor name)
        // For now we'll just return a count of 4 since that is how
        // many dummy courses we're dealing with.
        //
        for (unsigned short i = 0; i < MAX_COURSE_SI; i++)
            IM_course_si_rec[i] = 100000 + i + 1;

    m_num_remaining = count;
}

CourseSynopsisIteratorIM::~CourseSynopsisIteratorIM()
{

    //
    // *IM* Clear the dummy array of course numbers
    //
    for (unsigned short i = 0; i < MAX_COURSE_SI; i++)
        IM_course_si_rec[i] = 0;

}

CourseSynopsis CourseSynopsisIteratorIM::next()
{
    // TRACE_METHOD("CourseSynopsisIteratorIM::next");
    //
    // *IM*
    // As the m_num_remaining decreases we want to return the
    // course numbers in increasing order out of the array, just like
    // they'd be returned from the SQL fetch.
    //
    CourseSIRec.id = IM_course_si_rec[abs(m_count - m_num_remaining)];
    m_num_remaining--;
    return CourseSynopsis(new CourseSynopsisIM(CourseSIRec.id) );
}


//
//class CourseNumberIteratorIM
//
CourseNumberIteratorIM::CourseNumberIteratorIM(
				StudentId student_id)
{
    // TRACE_METHOD("CourseNumberIteratorIM");
    // TRACE("StudentId : " << student_id);

    // Get the count of all courses before actually getting each of the
    // course number records.

     CourseNIRec.id = student_id;
     m_count = count;
       //
        // *IM* We just stuff some in-memory data so that when we
        // use the next on the iterator we can return something. We will
        // need to do a call here to a database to get back an array of
        // the course numbers that match the search criteria (ie. Are 
		// registered to the student). For now we'll just return a count
	    // of 4 since that is how many dummy courses we're dealing with.
        //
    for (unsigned short i = 0; i < MAX_COURSE_SI; i++)
            IM_course_ni_rec[i] = 100000 + i + 1;

    m_num_remaining = count;

}

CourseNumberIteratorIM::~CourseNumberIteratorIM()
{

    //
    // *IM* Clear the dummy array of course numbers
    //
    for (unsigned short i = 0; i < MAX_COURSE_SI; i++)
        IM_course_ni_rec[i] = 0;


}

CourseNumber CourseNumberIteratorIM::next()
{
    // TRACE_METHOD("CourseNumberIteratorIM::next");

    CourseNIRec.id = IM_course_ni_rec[abs(m_count - m_num_remaining)];
    m_num_remaining--;
    return CourseNIRec.id;
}


//
//class ClassScheduleIM
//
ClassScheduleIM::ClassScheduleIM(CourseNumber course_number)
{
    // TRACE_METHOD("ClassScheduleIM");
    // TRACE("CourseNumber : " << course_number);

    ClassScheduleRec.id = course_number;

    //
    // *IM* We need to get the class schedule info for the
    // course number from TopEnd, or pull it over earlier
    // and get it from memory. For now we'll do dummy data.
    // See university.sql in the utils directory for this info
    //
    switch (course_number)
    {
        case 100001:
            ClassScheduleRec.start_hr =18;
            ClassScheduleRec.duration = 150;
            ClassScheduleRec.monday_scheduled = 'Y';
            ClassScheduleRec.tuesday_scheduled = 'N';
            ClassScheduleRec.wednesday_scheduled = 'N';
            ClassScheduleRec.thursday_scheduled = 'N';
            ClassScheduleRec.friday_scheduled = 'N';
            break;
        case 100002:
            ClassScheduleRec.start_hr =18;
            ClassScheduleRec.duration = 180;
            ClassScheduleRec.monday_scheduled = 'N';
            ClassScheduleRec.tuesday_scheduled = 'N';
            ClassScheduleRec.wednesday_scheduled = 'N';
            ClassScheduleRec.thursday_scheduled = 'Y';
            ClassScheduleRec.friday_scheduled = 'N';
            break;
        case 100003:
            ClassScheduleRec.start_hr =18;
            ClassScheduleRec.duration = 180;
            ClassScheduleRec.monday_scheduled = 'N';
            ClassScheduleRec.tuesday_scheduled = 'N';
            ClassScheduleRec.wednesday_scheduled = 'N';
            ClassScheduleRec.thursday_scheduled = 'Y';
            ClassScheduleRec.friday_scheduled = 'N';
            break;
        case 100004:
            ClassScheduleRec.start_hr =17;
            ClassScheduleRec.duration = 180;
            ClassScheduleRec.monday_scheduled = 'N';
            ClassScheduleRec.tuesday_scheduled = 'Y';
            ClassScheduleRec.wednesday_scheduled = 'N';
            ClassScheduleRec.thursday_scheduled = 'N';
            ClassScheduleRec.friday_scheduled = 'N';
            break;
    }

    // TRACE("Found ClassScheduleSQL : " << course_number);

    m_start_hour = ClassScheduleRec.start_hr;
    m_duration   = ClassScheduleRec.duration;

    m_days_scheduled = 0;

    if (ClassScheduleRec.monday_scheduled == 'Y')
        m_days_scheduled |= MON;

    if (ClassScheduleRec.tuesday_scheduled == 'Y')
        m_days_scheduled |= TUE;

    if (ClassScheduleRec.wednesday_scheduled == 'Y')
        m_days_scheduled |= WED;

    if (ClassScheduleRec.thursday_scheduled == 'Y')
        m_days_scheduled |= THU;

    if (ClassScheduleRec.friday_scheduled == 'Y')
        m_days_scheduled |= FRI;

}

ClassScheduleIM::~ClassScheduleIM() 
{  
}


//
//class CourseIM
//

CourseIM::CourseIM(CourseNumber course_number)
{
    // TRACE_METHOD("CourseIM");
    // TRACE("CourseNumber : " << course_number);


    CourseRec.id = course_number;

    // TRACE("Found CourseSQL : " << course_number);

    //
    // *IM* Given a course number we need to get the course detail
    // information.  For now, until we have TopEnd calls we'll generate
    // some dummy data. See university.sql in the utils dir for this info
    //
    switch( course_number)
    {
        case 100001:
            strcpy(CourseRec.title,"Fundamentals of CS");
            strcpy(CourseRec.desc,"Fundamentals of Computer Science");
            CourseRec.amount = 825.00;
            strcpy(CourseRec.professor, "Charles Steele");
            CourseRec.seats = 20;
            CourseRec.credits = 3;
            CourseRec.reg_students = 10;
            break;
        case 100002:
            strcpy(CourseRec.title,"Foundations of CS");
            strcpy(CourseRec.desc,"Foundationss of Computer Science");
            CourseRec.amount = 1299.00;
            strcpy(CourseRec.professor, "Charles Steele");
            CourseRec.seats = 20;
            CourseRec.credits = 3;
            CourseRec.reg_students = 10;
            break;
        case 100003:
            strcpy(CourseRec.title,"Into to Algorithms");
            strcpy(CourseRec.desc,"Introduction to Algorithms");
            CourseRec.amount = 965.00;
            strcpy(CourseRec.professor, "Glenn C Smith");
            CourseRec.seats = 25;
            CourseRec.credits = 3;
            CourseRec.reg_students = 10;
            break;
        case 100004:
            strcpy(CourseRec.title,"Advanced Algorithms");
            strcpy(CourseRec.desc,"Advanced Algorithms");
            CourseRec.amount =999.00;
            strcpy(CourseRec.professor, "Fred Lewis");
            CourseRec.seats = 20;
            CourseRec.credits = 4;
            CourseRec.reg_students = 10;
            break;
    }

    m_course_number = course_number;

    //
    // *IM* we're not dealing with VARCHARs here but with char arrays
    // so we need to do things a little differently
    //
    m_title = new char[ strlen(CourseRec.title) + 1 ];
    strcpy(m_title, (char *) CourseRec.title);

    m_description = new char[ strlen(CourseRec.desc) + 1 ];
    strcpy(m_description, (char *) CourseRec.desc);

    m_professor = new char[ strlen(CourseRec.professor) + 1 ];
    strcpy(m_professor, (char *) CourseRec.professor);

    // Is number_of_credits a float or unsigned short?
    // Is cost a double or simply a float?

    m_cost              = CourseRec.amount;
    m_number_of_seats   = CourseRec.seats;
    m_number_of_credits = CourseRec.credits;
    m_number_of_registered_students = CourseRec.reg_students;

}
	
CourseIM::~CourseIM()
{
    if ( m_title != NULL )
        delete [] m_title;

    if ( m_description != NULL )
        delete [] m_description;

    if ( m_professor != NULL )
        delete [] m_professor;
	
}

//
//class Student
//
	
StudentIM::StudentIM(StudentId student_id)
{

    // TRACE_METHOD("StudentIM");
    // TRACE("StudentId : " << student_id);

// Add code for in-memory DB

    m_student_id = student_id;
 
	switch( student_id )
    {
        case 100001:
            strcpy(StudentRec.name,"Joseph Matthews");
            StudentRec.account = 200010;
            break;
        case 100002:
            strcpy(StudentRec.name,"Robert Blodgett");
            StudentRec.account = 200011;            
            break;
        case 100003:
            strcpy(StudentRec.name,"Ralph Martin");
            StudentRec.account = 200012;
            break;
        case 100004:
            strcpy(StudentRec.name,"Betsy Fedak");
            StudentRec.account = 200013;
            break;
        case 100005:
            strcpy(StudentRec.name,"Chris Putur");
            StudentRec.account = 200014;
            break;
        case 100006:
            strcpy(StudentRec.name,"Nancy Glidden");
            StudentRec.account = 200015;
            break;
        case 100007:
            strcpy(StudentRec.name,"Joe Atterberry");
            StudentRec.account = 200016;
            break;
        case 100008:
            strcpy(StudentRec.name,"Thomas Cooper");
            StudentRec.account = 200017;
            break;
        case 100009:
            strcpy(StudentRec.name,"Richard DeWitt");
            StudentRec.account = 200018;
            break;
        case 100010:
            strcpy(StudentRec.name,"Shawn O'Reilly");
            StudentRec.account = 200019;
            break;
    }

    m_name = new char[ strlen(StudentRec.name) + 1 ];
    strcpy(m_name, (char *) StudentRec.name);
    m_account_number = StudentRec.account;


}


CourseNumberIterator	StudentIM::get_registered_courses()
{

    // TRACE_METHOD("StudentIM::get_registered_courses");

    return ( CourseNumberIterator ( new CourseNumberIteratorIM( m_student_id ) ) );

}


StudentIM::~StudentIM()
{

    delete [] m_name;

}


Student  DatabaseIM::get_student(StudentId student_id)
{

    // TRACE_METHOD("DatabaseIM::get_student");

    return ( Student( new StudentIM( student_id ) ) );

}


Course   DatabaseIM::get_course(CourseNumber course_number)
{
    // TRACE_METHOD("DatabaseIM::get_course");
    // TRACE("CourseNumber : " << course_number);

    return ( Course( new CourseIM(course_number) ) );
}

CourseSynopsisIterator DatabaseIM::get_courses(const char* search_criteria)
{
    // TRACE_METHOD("DatabaseIM::get_courses");
    // TRACE("Search Criteria : " << search_criteria);

    return ( CourseSynopsisIterator( new CourseSynopsisIteratorIM(search_criteria) ) );
}
    
void DatabaseIM::add_registration(StudentId student_id,
				       CourseNumber course_number)
{
#ifdef NOT_TOP_END
    // TRACE_METHOD("DatabaseIM::add_registration");
    // TRACE("StudentId : " << student_id);
    // TRACE("CourseNumber : " << course_number);

    // SQL Command to register a student for a specified course

    if (!sqlConnected)
        throw SamplesDatabaseNotConnected();

    // Do we have a valid student id?

    EXEC SQL WHENEVER NOT FOUND DO _throwBadStudentId();

    RegnRec.stud_id = student_id;
    EXEC SQL SELECT STUD_ID INTO :RegnRec.stud_id FROM STUDENT
                        WHERE   STUD_ID = :RegnRec.stud_id;

    // Do we have a valid Course id?
    // If yes, then is the registration for this course open?

    EXEC SQL WHENEVER NOT FOUND DO _throwBadCourseId();

    RegnRec.course_id = course_number;
    EXEC SQL SELECT SEATS, REG_STUD INTO :RegnRec.seats,
                                         :RegnRec.reg_students
                FROM COURSE WHERE   COURSE_NO = :RegnRec.course_id
                FOR UPDATE OF SEATS, REG_STUD;

    if (RegnRec.reg_students == RegnRec.seats)
        throw SamplesCourseRegFull();

    // Register the student for this course

    EXEC SQL WHENEVER NOT FOUND continue;
    EXEC SQL WHENEVER SQLERROR DO _throwAlreadyRegistered();

    // TRACE("Doing add_registration : ");

    EXEC SQL INSERT INTO REGISTRATION VALUES (:RegnRec.stud_id, :RegnRec.course_id);

    EXEC SQL WHENEVER SQLERROR DO _throwDbError();

    // TRACE("Doing update COURSE reg_stud : ");

    // Increment the number of registered students for this Course

    EXEC SQL UPDATE COURSE SET REG_STUD = REG_STUD + 1
                    WHERE COURSE_NO = :RegnRec.course_id;

    // When we introduce transactions, we commit/rollback at a higher level
    // EXEC SQL COMMIT WORK;
#endif  // NOT_TOP_END

}

Database Database::open_db()
{
    // TRACE_METHOD("Database::open_db");

    sqlConnected = CORBA_TRUE;
    return ( Database( new DatabaseIM( ) ) );
}


//
// FUNCTION NAME:
//
//      getEnvVariable()
//
// DESCRIPTION:
//
//      This routine gets an environment variable
//
// FORMAL PARAMETERS:
//
//      NONE
//
// RETURN VALUE:
//
//      NONE
//
unsigned long   getEnvVariable( char * envVarName,
                                char * envVarValue,
                                unsigned long envValueLen)
{
    unsigned long return_len;
#ifndef WIN32
    char *        cptr;
#endif

#ifdef WIN32
    return_len = GetEnvironmentVariable( (LPTSTR) envVarName,
                                         (LPTSTR) envVarValue,
                                         (DWORD) envValueLen );
#else   //  ifdef unix
    cptr       = getenv( envVarName );
#endif

    //  If environment variable name not found
#ifdef WIN32
    if ( return_len == 0 )
        return( return_len );

#else   //  ifdef unix
    if ( cptr == NULL )
        return( 0 );

    return_len = (unsigned long)strlen( cptr );
#endif

    //  If buffer is too small, return 0
    if ( return_len  > envValueLen )
        return( 0 );

#ifndef WIN32
    // Copy the value to the buffer
    strcpy( envVarValue, cptr );
#endif

    //  Return number of characters stored in envVarValue buffer
    return( return_len );
}
