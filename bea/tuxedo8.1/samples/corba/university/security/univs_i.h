//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univs_i.h
//
// Declares the C++ servant implementations for the university
// sample declaration.
//
// Classes declared :
//
//   CourseSynopsisEnumerator_i
//   Registrar_i
//   RegistrarFactory_i
//
// This file was originally generated by using the "-i" idl switch,
// then edited by hand.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _univs_i_h
#define _univs_i_h

//--------------------------------------------------------------------

#include <samplesdb.h>
#include "univs_s.h"

//--------------------------------------------------------------------

class CourseSynopsisEnumerator_i :
    public POA_UniversityS::CourseSynopsisEnumerator
{
  public:

    CourseSynopsisEnumerator_i(Database& db);

    virtual ~CourseSynopsisEnumerator_i();

    virtual void destroy();

    virtual void
    activate_object(
        const char* object_id
    );

    virtual UniversityS::CourseSynopsisList*
    get_next_n(
        CORBA::ULong     number_to_get,
        CORBA::ULong_out number_remaining
    );

  private:
     Database&                       m_db;
     UniversityS::CourseSynopsisList m_matches;
     CORBA::ULong                    m_index;
};

//--------------------------------------------------------------------

class Registrar_i :
    public POA_UniversityS::Registrar
{
  public:

    Registrar_i(
        Database& db
    );

    virtual ~Registrar_i();


    virtual UniversityS::CourseSynopsisList*
    get_courses_synopsis(
        const char*                               search_criteria,
        CORBA::ULong                              number_to_get,
        CORBA::ULong_out                          number_remaining,
        UniversityS::CourseSynopsisEnumerator_out rest
    );

    virtual UniversityS::CourseDetailsList*
    get_courses_details(
         const UniversityS::CourseNumberList& courses
    );

    virtual UniversityS::StudentDetails*
    get_student_details(
        UniversityS::StudentId student
    );

  private:
    Database& m_db;
};

//--------------------------------------------------------------------

class RegistrarFactory_i :
    public POA_UniversityS::RegistrarFactory
{
  public:
    RegistrarFactory_i();

    virtual ~RegistrarFactory_i();

    virtual UniversityS::Registrar_ptr find_registrar(
    );
};

//--------------------------------------------------------------------

#endif
