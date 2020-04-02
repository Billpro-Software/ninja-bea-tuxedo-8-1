/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*      Copyright (c) 1998 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/


#ifndef _SAMPLESDBSQL_H
#define _SAMPLESDBSQL_H

// MODULE NAME:
//
//    samplesdbsql.h
//
// FACILITY:
//
//    Samples 
//
// ABSTRACT:
//
//    This include file contains C++ class methods for
//    CourseSynopsisIterator 
//    CourseSynopsis
//    Course
//    ClassSchedule
//    Student
//    Database
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

#include "samplesdb.h"

//
// Bit mask for the Class Schedule
//
#define MON             (1<<7)
#define TUE             (1<<6)
#define WED             (1<<5)
#define THU             (1<<4)
#define FRI             (1<<3)

//
//_throwSamples exceptions because EXEC SQL does not like DO C++ calls
//
void _throwCannotConnectDatabase();
void _throwDatabaseNotConnected();
void _throwBadStudentId();
void _throwBadCourseId();
void _throwNoMoreItems();
void _throwNoMatches();
void _throwCourseRegFull();
void _throwAlreadyRegistered();
void _throwDbError();

//
//class RefCountImpl
//
class RefCountImpl : public virtual RefCountInterface
{
private:
    unsigned long refcount;

public:
    // Constructors and Destructors
    RefCountImpl() : refcount(0) {};
    virtual ~RefCountImpl() {};

    // Accessors
    virtual void reference() { refcount++; };
    virtual void unreference() 
    {
        refcount--;
        if ( 0 == refcount ) delete this;
    }

private:
    // Don't allow assignment
    RefCountImpl(const RefCountImpl& rci);
    void operator=(const RefCountImpl& rci);

};


//
//class CourseSynopsisSQL
//
class CourseSynopsisSQL :   public virtual CourseSynopsisInterface,
                            public virtual RefCountImpl
{
private:
    char* m_title;
    CourseNumber m_course_number;

public:
    // Accessors
    CourseNumber get_course_number() { return m_course_number; };
    const char*  get_title()     { return m_title; };
    virtual void reference()     { RefCountImpl::reference(); };
    virtual void unreference()   { RefCountImpl::unreference(); };

    // Constructors and Destructors
    CourseSynopsisSQL(CourseNumber course_number);
    ~CourseSynopsisSQL();
};


//
//class CourseSynopsisIteratorSQL
//
class CourseSynopsisIteratorSQL : public virtual CourseSynopsisIteratorInterface,
                            public virtual RefCountImpl
{
private:
    unsigned long m_count;
    unsigned long m_num_remaining;

public:
    // Accessors
    CourseSynopsis next();
    unsigned long get_count() { return m_count; };
    unsigned long get_num_remaining() { return m_num_remaining; };
    virtual void  reference() { RefCountImpl::reference(); };
    virtual void  unreference() { RefCountImpl::unreference(); };

    // Constructors and Destructors
    CourseSynopsisIteratorSQL(const char* search_criteria);

    ~CourseSynopsisIteratorSQL();

};


//
//class CourseNumberIteratorSQL
//
class CourseNumberIteratorSQL : public virtual CourseNumberIteratorInterface,
                            public virtual RefCountImpl
{
private:
    unsigned long m_count;
    unsigned long m_num_remaining;

public:
    // Accessors
    CourseNumber next();
    unsigned long get_count() { return m_count; };
    unsigned long get_num_remaining() { return m_num_remaining; };
    virtual void  reference() { RefCountImpl::reference(); };
    virtual void  unreference() { RefCountImpl::unreference(); };

    // Constructors and Destructors
    CourseNumberIteratorSQL(StudentId student_id);

    ~CourseNumberIteratorSQL();

};


//
//class ClassScheduleSQL
//
class ClassScheduleSQL : public virtual ClassScheduleInterface,
                            public virtual RefCountImpl
{
private:
    unsigned short m_start_hour;
    unsigned short m_duration;
    unsigned char  m_days_scheduled;

public:
    // Accessors
    unsigned short get_start_hour() { return m_start_hour; }; 
    unsigned short get_duration()   { return m_duration; }; 
             short get_mon_sched()  { return (m_days_scheduled & MON); };
             short get_tue_sched()  { return (m_days_scheduled & TUE); };
             short get_wed_sched()  { return (m_days_scheduled & WED); };
             short get_thu_sched()  { return (m_days_scheduled & THU); };
             short get_fri_sched()  { return (m_days_scheduled & FRI); };
    virtual void   reference() { RefCountImpl::reference(); };
    virtual void   unreference() { RefCountImpl::unreference(); };

    // Constructors and Destructors
    ClassScheduleSQL(CourseNumber course_number);
    ~ClassScheduleSQL();
};


//
//class CourseSQL
//
class CourseSQL : public virtual CourseInterface,
                            public virtual RefCountImpl
{
private:
    CourseNumber    m_course_number;
    char*           m_title; 
    unsigned short  m_number_of_credits; 
    double          m_cost; 
    char*           m_professor; 
    char*           m_description; 
    unsigned short  m_number_of_seats; 
    unsigned short  m_number_of_registered_students; 


public:
    // Accessors
    CourseNumber   get_course_number() { return m_course_number; }; 
    const char*    get_title()         { return m_title; }; 
    unsigned short get_number_of_credits() { return m_number_of_credits; }; 
    double         get_cost()          { return m_cost; }; 
    const char*    get_professor()     { return m_professor; }; 
    ClassSchedule  get_schedule()
                { return ClassSchedule(new ClassScheduleSQL(m_course_number)); }; 
    const char*    get_description()   { return m_description; }; 
    unsigned short get_number_of_seats()   { return m_number_of_seats; }; 
    unsigned short get_number_of_registered_students()
                        { return m_number_of_registered_students; }; 

    virtual void   reference() { RefCountImpl::reference(); };
    virtual void   unreference() { RefCountImpl::unreference(); };

    // Constructors and Destructors
    CourseSQL(CourseNumber   course_number);

    ~CourseSQL();
};


//
//class Student
//
class StudentSQL : public virtual StudentInterface,
                            public virtual RefCountImpl
{
private:
    StudentId         m_student_id; 
    char*             m_name; 
    AccountNumber m_account_number;

public:
    // Accessors
    StudentId         get_student_id() { return m_student_id; }; 
    const char*       get_name()       { return m_name; }; 
    AccountNumber get_account_number() { return m_account_number; };
    CourseNumberIterator
                      get_registered_courses();
    virtual void   reference() { RefCountImpl::reference(); };
    virtual void   unreference() { RefCountImpl::unreference(); };

    // Constructors and Destructors
    StudentSQL(StudentId student_id);

    ~StudentSQL();
};


//
// class DatabaseSQL
//
class DatabaseSQL : public virtual DatabaseInterface,
                            public virtual RefCountImpl
{
public:
    // Constructors and Destructors
    ~DatabaseSQL() {};
    DatabaseSQL() {};

    Student  get_student(StudentId student_id);
    Course   get_course(CourseNumber course_number);

    CourseSynopsisIterator   // NULL = return all courses
                get_courses(const char* search_criteria);
    
    void add_registration(StudentId student_id,
                            CourseNumber course_number);

    virtual void   reference() { RefCountImpl::reference(); };
    virtual void   unreference() { RefCountImpl::unreference(); };

};

// Function prototypes for the sql Connect function
void    sqlConnect();
void    sqlConnectDb();

#endif
// _SAMPLESDBSQL_H
