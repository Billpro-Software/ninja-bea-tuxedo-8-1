/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*      Copyright (c) 1998 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/


#ifndef _SAMPLESDB_H
#define _SAMPLESDB_H

// MODULE NAME:
//
//    samplesdb.h
//
// FACILITY:
//
//    Samples 
//
// ABSTRACT:
//
//    This include file contains C++ class definitions for
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
typedef unsigned long CourseNumber; 
typedef unsigned long StudentId; 
typedef unsigned long AccountNumber; 
#include <iostream.h>

// ***************************
// SamplesDBException classes
// ***************************

class SamplesDBException        { public: virtual ostream& print(ostream& os); };

class SamplesCannotConnectDatabase      : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesDatabaseNotConnected       : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesBadStudentId               : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesBadCourseId                : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesNoMoreItems                : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesNoMatches                  : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesCourseRegFull              : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesAlreadyRegistered          : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };
class SamplesDbError                    : public virtual SamplesDBException
                                { public: ostream& print(ostream& os); };

// ***************************
// ostream insertion operator 
// ***************************

inline ostream& operator<<(ostream& os, SamplesDBException& ex)
                                { return ex.print(os); }

// ***************************
// RefCount classes
// ***************************

//
//class RefCountInterface
//
// Abstract class that hides the details of how
// data is accessed.
class RefCountInterface
{

public:
    // Constructors and Destructors
    virtual ~RefCountInterface() {};

    // Accessors
    virtual void reference() = 0;
    virtual void unreference() = 0;

};

//
//class RefCount
//
class RefCount
{
private:
    RefCountInterface* m_delegate_RC;

public:
    // Constructors and Destructors
    RefCount(RefCountInterface* delegate) : m_delegate_RC(delegate)
                                { m_delegate_RC->reference(); };
    RefCount(const RefCount& rc) : m_delegate_RC(rc.m_delegate_RC)
                                { m_delegate_RC->reference(); };
    virtual ~RefCount() { m_delegate_RC->unreference(); };

    // Operators
    void operator=(const RefCount& rc) 
    {
        if ( m_delegate_RC != rc.m_delegate_RC)
        {
            rc.m_delegate_RC->reference();
            m_delegate_RC->unreference();
            m_delegate_RC = rc.m_delegate_RC;
        };
    };

};


// ***************************
// CourseSynopsis classes
// ***************************

//
//class CourseSynopsisInterface
//
// Abstract class that hides the details of how
// data is accessed.
class CourseSynopsisInterface : public virtual RefCountInterface
{

public:
    // Constructors and Destructors
    virtual ~CourseSynopsisInterface() {};

    // Accessors
    virtual CourseNumber get_course_number() = 0;
    virtual const char*  get_title() = 0;
};

//
//class CourseSynopsis
//
class CourseSynopsis : private RefCount
{
private:
    CourseSynopsisInterface* m_delegate;

public:
    // Constructors and Destructors
    CourseSynopsis(CourseSynopsisInterface* delegate) :
                                RefCount(delegate), m_delegate(delegate) {};
    ~CourseSynopsis() {};

    CourseSynopsis(const CourseSynopsis& cs) :
                                RefCount(cs), m_delegate(cs.m_delegate) {};

    // Operators
    void operator=(const CourseSynopsis& cs)
    {
        (RefCount&)(*this) = (RefCount&)cs;
        m_delegate = cs.m_delegate;
    }

    // Accessors
    CourseNumber get_course_number() { return m_delegate->get_course_number(); };
    const char*  get_title()    { return m_delegate->get_title(); };
};


// ******************************
// CourseSynopsisIterator classes
// ******************************

//
//class CourseSynopsisIteratorInterface
//
// Abstract class that hides the details of how
// data is accessed.
class CourseSynopsisIteratorInterface  : public virtual RefCountInterface
{

public:
    // Constructors and Destructors
    virtual ~CourseSynopsisIteratorInterface() {};

    // Accessors
    virtual CourseSynopsis next() = 0;
    virtual unsigned long get_count() = 0;
    virtual unsigned long get_num_remaining() = 0;
};

//
//class CourseSynopsisIterator
//
class CourseSynopsisIterator : private RefCount
{
private:
    CourseSynopsisIteratorInterface* m_delegate;

public:
    // Constructors and Destructors
    CourseSynopsisIterator(CourseSynopsisIteratorInterface* delegate) :
                                RefCount(delegate), m_delegate(delegate) {};
    ~CourseSynopsisIterator() {};

    CourseSynopsisIterator(const CourseSynopsisIterator& csi) :
                                RefCount(csi), m_delegate(csi.m_delegate) {};

    // Operators
    void operator=(const CourseSynopsisIterator& csi)
    {
        (RefCount&)(*this) = (RefCount&)csi;
        m_delegate = csi.m_delegate;
    }

    // Accessors
    CourseSynopsis next() { return m_delegate->next(); }; 
    // throws exceptions
    // throw (SamplesDatabaseNotConnected,
    // 	  SamplesNoMoreItems,
    // 	  SamplesDbError)

    unsigned long get_count() { return m_delegate->get_count(); };
    unsigned long get_num_remaining()
                                { return m_delegate->get_num_remaining(); };
};

// ******************************
// CourseNumberIterator classes
// ******************************

//
//class CourseNumberIteratorInterface
//
// Abstract class that hides the details of how
// data is accessed.
class CourseNumberIteratorInterface  : public virtual RefCountInterface
{

public:
    // Constructors and Destructors
    virtual ~CourseNumberIteratorInterface() {};

    // Accessors
    virtual CourseNumber next() = 0;
    virtual unsigned long get_count() = 0;
    virtual unsigned long get_num_remaining() = 0;
};



//
//class CourseNumberIterator
//
class CourseNumberIterator : private RefCount
{
private:
    CourseNumberIteratorInterface* m_delegate;

public:
    // Constructors and Destructors
    CourseNumberIterator(CourseNumberIteratorInterface* delegate) :
                                RefCount(delegate), m_delegate(delegate) {};
    ~CourseNumberIterator() {};

    CourseNumberIterator(const CourseNumberIterator& cni) :
                                RefCount(cni), m_delegate(cni.m_delegate) {};

    // Operators
    void operator=(const CourseNumberIterator& cni)
    {
        (RefCount&)(*this) = (RefCount&)cni;
        m_delegate = cni.m_delegate;
    }

    // Accessors
    CourseNumber next()		{ return m_delegate->next(); }; 
    // throws exceptions
    // throw (SamplesDatabaseNotConnected,
    // 	  SamplesNoMoreItems,
    // 	  SamplesDbError)

    unsigned long get_count() { return m_delegate->get_count(); };
    unsigned long get_num_remaining()
                                { return m_delegate->get_num_remaining(); };
};



// ***************************
// ClassSchedule classes
// ***************************

//
//class ClassScheduleInterface
//
class ClassScheduleInterface : public virtual RefCountInterface
{
public:
    // Constructors and Destructors
    virtual ~ClassScheduleInterface() {};

    // Accessors
    virtual unsigned short get_start_hour() = 0;
    virtual unsigned short get_duration() = 0; 
    virtual          short get_mon_sched() = 0;
    virtual          short get_tue_sched() = 0;
    virtual          short get_wed_sched() = 0;
    virtual          short get_thu_sched() = 0;
    virtual          short get_fri_sched() = 0;

};

//
//class ClassSchedule
//
class ClassSchedule : private RefCount
{
private:
    ClassScheduleInterface* m_delegate;

public:
    // Constructors and Destructors
    ClassSchedule(ClassScheduleInterface* delegate) :
                                RefCount(delegate), m_delegate(delegate) {};
    ~ClassSchedule() {};
	
    ClassSchedule(const ClassSchedule& cs) :
                                RefCount(cs), m_delegate(cs.m_delegate) {};

    // Operators
    void operator=(const ClassSchedule& cs)
    {
        (RefCount&)(*this) = (RefCount&)cs;
        m_delegate = cs.m_delegate;
    }

    // Accessors
    unsigned short get_start_hour() { return m_delegate->get_start_hour(); }; 
    unsigned short get_duration()   { return m_delegate->get_duration(); }; 
             short get_mon_sched()  { return m_delegate->get_mon_sched(); };
             short get_tue_sched()  { return m_delegate->get_tue_sched(); };
             short get_wed_sched()  { return m_delegate->get_wed_sched(); };
             short get_thu_sched()  { return m_delegate->get_thu_sched(); };
             short get_fri_sched()  { return m_delegate->get_fri_sched(); };
};



// ***************************
// Course classes
// ***************************

//
//class CourseInterface
//
class CourseInterface : public virtual RefCountInterface
{
public:
    // Constructors and Destructors
    virtual ~CourseInterface() {};

    // Accessors
    virtual CourseNumber    get_course_number() = 0;
    virtual const char*     get_title() = 0;
    virtual unsigned short  get_number_of_credits() = 0; 
    virtual double          get_cost() = 0;
    virtual const char*     get_professor() = 0; 
    virtual ClassSchedule   get_schedule() = 0;
    virtual const char*     get_description() = 0;
    virtual unsigned short  get_number_of_seats() = 0;
    virtual unsigned short  get_number_of_registered_students() = 0;

};

//
//class Course
//
class Course : private RefCount
{
private:
    CourseInterface* m_delegate;

public:
    // Constructors and Destructors
    Course(CourseInterface* delegate) :
                                RefCount(delegate), m_delegate(delegate) {};
    ~Course() {};

    Course(const Course& crs) : RefCount(crs), m_delegate(crs.m_delegate) {};

    // Operators
    void operator=(const Course& crs)
    {
        (RefCount&)(*this) = (RefCount&)crs;
        m_delegate = crs.m_delegate;
    }

    // Accessors
    CourseNumber   get_course_number()      { return m_delegate->get_course_number(); }; 
    const char*    get_title()              { return m_delegate->get_title(); }; 
    unsigned short get_number_of_credits()  { return m_delegate->get_number_of_credits(); }; 
    double         get_cost()               { return m_delegate->get_cost(); }; 
    const char*    get_professor()          { return m_delegate->get_professor(); }; 

    ClassSchedule  get_schedule()           { return m_delegate->get_schedule(); }; 
    // throws exceptions
    // throw (SamplesDatabaseNotConnected,
    // 	  SamplesDbError)

    const char*    get_description()        { return m_delegate->get_description(); }; 
    unsigned short get_number_of_seats()    { return m_delegate->get_number_of_seats(); }; 
    unsigned short get_number_of_registered_students() 
                            { return m_delegate->get_number_of_registered_students(); }; 

};



// ***************************
// Student classes
// ***************************

//
//class StudentInterface
//
class StudentInterface : public virtual RefCountInterface
{
public:
    // Constructors and Destructors
    virtual ~StudentInterface() {};

    // Accessors
    virtual StudentId       get_student_id() = 0;
    virtual const char*     get_name() = 0;
    virtual AccountNumber   get_account_number() = 0;
    virtual CourseNumberIterator
                            get_registered_courses() = 0;

};

//
//class Student
//
class Student : private RefCount
{
private:
    StudentInterface* m_delegate;

public:
    // Constructors and Destructors
    Student(StudentInterface* delegate) :
                                RefCount(delegate), m_delegate(delegate) {};
    ~Student() {};

    Student(const Student& std) :
                                RefCount(std), m_delegate(std.m_delegate) {};

    // Operators
    void operator=(const Student& std)
    {
        (RefCount&)(*this) = (RefCount&)std;
        m_delegate = std.m_delegate;
    }

    // Accessors
    StudentId       get_student_id() { return m_delegate->get_student_id(); }; 
    const char*     get_name()       { return m_delegate->get_name(); }; 
    AccountNumber   get_account_number() { return m_delegate->get_account_number(); };
    CourseNumberIterator
                    get_registered_courses()
                                { return m_delegate->get_registered_courses(); };

};



// ***************************
// Database classes
// ***************************

//
//class DatabaseInterface
//
class DatabaseInterface : public virtual RefCountInterface
{
public:
    // Constructors and Destructors
    ~DatabaseInterface() { };

    // Accessors
    virtual Student  get_student(StudentId student_id) = 0;
    virtual Course   get_course(CourseNumber course_number) = 0;
    virtual CourseSynopsisIterator get_courses(const char* search_criteria) = 0;
    virtual void add_registration(StudentId student_id, CourseNumber course_number) = 0;

};

//
//class Database
//
class Database : private RefCount
{
private:
    DatabaseInterface* m_delegate;

public:
    static Database open_db(); 
    // throws exceptions
    // throw (SamplesCannotConnectDatabase)

    // Constructors and Destructors
    Database(DatabaseInterface* delegate):
                                RefCount(delegate), m_delegate(delegate) {};
    ~Database() {};

    Database(const Database& db) :
                                RefCount(db), m_delegate(db.m_delegate) {};

    // Operators
    void operator=(const Database& db)
    {
        (RefCount&)(*this) = (RefCount&)db;
        m_delegate = db.m_delegate;
    }

    // Accessors
    Student get_student(StudentId student_id) 
                    { return m_delegate->get_student(student_id); };
    // throws exceptions
    // throw (SamplesDatabaseNotConnected,
    // 	  SamplesBadStudentId)

    Course  get_course(CourseNumber course_number) 
                    { return m_delegate->get_course(course_number); }; 
    // throws exceptions
    // throw (SamplesDatabaseNotConnected,
    // 	  SamplesBadCourseId)

    CourseSynopsisIterator get_courses(const char* search_criteria) 
                    { return m_delegate->get_courses(search_criteria); };
    // throws exceptions
    // throw (SamplesDatabaseNotConnected,
    // 	  SamplesNoMatches,
    // 	  SamplesNoMoreItems,
    // 	  SamplesDbError)

    void add_registration(StudentId student_id, CourseNumber course_number)
                    { m_delegate->add_registration(student_id, course_number); };
    // throws exceptions
    // throw (SamplesDatabaseNotConnected,
    // 	  SamplesBadStudentId,
    // 	  SamplesBadCourseId,
    // 	  SamplesCourseRegFull,
    // 	  SamplesStudentAlRegistered,
    // 	  SamplesDbError)

};

#endif
// _SAMPLESDB_H
