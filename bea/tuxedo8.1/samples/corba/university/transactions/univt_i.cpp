//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univt_i.cpp
//
// C++ servant implementations for the university sample declaration.
//
// Classes implemented :
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

#include <string.h> // strlen
#include <log.h>
#include <unique_id.h>
#include <TP.h>
#include "univt_utils.h"
#include "univt_i.h"

//--------------------------------------------------------------------

/* Naming conventions :

   abbreviations
   -------------
   crs    course
   syn    synopsis
   det    details
   lst    list
   enum   enumerator
   stu    student
   fact   factory
   num    number
   cur    current
   _oref  CORBA::Object reference
   _ref   typed object reference
   p_     ptr
   v_     var
   s_     file static data
   m_     class member data

   method names and variable names start lower case and
   separate all words with underscores. variable names
   use abbreviations.  e.g. :

       m_v_crs_syn_lst =

           member data which is a var holding a
           course synopsis list

           m_  = member data
           v_  = var
           crs = course
           syn = synopsis
           lst = list

   type names start upper case and separate words by
   uppercasing the first letter of each word. type
   names do not use abbreviations.  e.g. :

       UniversityT::CourseSynopsisEnumerator_var
*/

//--------------------------------------------------------------------
// macro to handle exceptions in servant idl method implementations

#define HANDLE_EX                                   \
    catch (CORBA::Exception& e) {                   \
        LOG("unexpected CORBA::Exception : " << e); \
        throw;                                      \
    }                                               \
    catch (SamplesDBException& e) {                 \
        LOG("Unexpected database error : " << e);   \
        throw CORBA::PERSIST_STORE();               \
    }                                               \
    catch (...) {                                   \
        LOG("unexpected exception");                \
        throw CORBA::INTERNAL();                    \
    }

//--------------------------------------------------------------------
// utility to write a string to an ostream

static void write_string(ostream& os, const char* str)
{
    unsigned long len = (str != 0) ? strlen(str) : 0;
    os << len;
    if (len > 0) {
        os << " \"" << str << '"';
    }
}

//--------------------------------------------------------------------
// utility to read a string from an istream
// (caller is responsible for deleting the returned string)

#if defined(__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT >= 5
using std::ws;
#endif

static char* read_string(istream& is) // caller must delete it
{
    unsigned long len;
    is >> len;
    if (len == 0) {
        return 0;
    }
    is >> ws; // skip over white space
    { char c; is >> c; /* assert(c == '"'); */ }
    char* str = new char[len + 1];
    for (unsigned long i = 0; i < len; i++) {
        str[i] = is.get();
    }
    str[len] = '\0';
    { char c; is >> c; /* assert(c == '"'); */ }
    return str;
}

//--------------------------------------------------------------------
// utility to write a deactivation reason to an ostream

static ostream&
operator<<(ostream& os, TobjS::DeactivateReasonValue val)
{
    switch (val) {
      case TobjS::DR_METHOD_END:
        os << "method end";
        break;
      case TobjS::DR_SERVER_SHUTDOWN:
        os << "server shutdown";
        break;
      case TobjS::DR_TRANS_COMMITTING:
        os << "committing";
        break;
      case TobjS::DR_TRANS_ABORTED:
        os << "aborted";
        break;
      default:
        os << "unknown";
        break;
    }
    return os;
}

//--------------------------------------------------------------------
// utility to retrieve course details from the database and
// package them up to send back thru its corresponding IDL type

// fill in a parameter v.s. returning a value so that we can
// avoid a copy

static void get_crs_det(
    Database&                   db,
    UniversityT::CourseNumber   crs_num,
    UniversityT::CourseDetails& crs_det
)
{
    // get the coure details from the db
    Course crs = db.get_course(crs_num);

    {
        // extract and convert the schedule

        ClassSchedule sched = crs.get_schedule();

        UniversityT::Days days = 0;
        if (sched.get_mon_sched()) { days |= UniversityT::MONDAY;    }
        if (sched.get_tue_sched()) { days |= UniversityT::TUESDAY;   }
        if (sched.get_wed_sched()) { days |= UniversityT::WEDNESDAY; }
        if (sched.get_thu_sched()) { days |= UniversityT::THURSDAY;  }
        if (sched.get_fri_sched()) { days |= UniversityT::FRIDAY;    }

        crs_det.class_schedule.start_hour = sched.get_start_hour();
        crs_det.class_schedule.duration   = sched.get_duration();
        crs_det.class_schedule.class_days = days;
    }

    // fill in the rest of the fields

    crs_det.course_number     = crs.get_course_number();
    crs_det.cost              = crs.get_cost();
    crs_det.number_of_credits = crs.get_number_of_credits();
    crs_det.number_of_seats   = (CORBA::UShort)crs.get_number_of_seats();
    crs_det.title             = crs.get_title();
    crs_det.professor         = crs.get_professor();
    crs_det.description       = crs.get_description();
}

//--------------------------------------------------------------------
// utility to add a "not registered" error to a list of errors

static void add_not_reg(
    UniversityT::NotRegisteredList&  not_reg_lst,
    UniversityT::CourseNumber        crs_num,
    UniversityT::NotRegisteredReason reason
)
{
    CORBA::ULong index = not_reg_lst.length();
    not_reg_lst.length(index+1);
    not_reg_lst[index].course_number = crs_num;
    not_reg_lst[index].not_registered_reason = reason;
}

//====================================================================
// CourseSynopsisEnumerator_i method implementations
//====================================================================

//--------------------------------------------------------------------

CourseSynopsisEnumerator_i::CourseSynopsisEnumerator_i(
    Database& db
) :
    m_db(db),
    m_index(0)
{ 
    TRACE_METHOD(
        "CourseSynopsisEnumerator_i::CourseSynopsisEnumerator_i"
    );
}

//--------------------------------------------------------------------

CourseSynopsisEnumerator_i::~CourseSynopsisEnumerator_i()
{
    TRACE_METHOD(
        "CourseSynopsisEnumerator_i::~CourseSynopsisEnumerator_i()"
    );
}

//--------------------------------------------------------------------

void
CourseSynopsisEnumerator_i::activate_object(
    const char* object_id
)
{
    TRACE_METHOD("CourseSynopsisEnumerator_i::activate_object");

    try {

        TRACE("object_id = " << object_id);

        // This method gives the object_id to the enumerator.
        // This id contains the search criteria as well
        // as a unique id.

        // extract the unique id and the search criteria
        // from the object id:
        istrstream is((char*)object_id);

        // first, the unique id:
        {
            UniqueId uid;
            is >> uid;
        }

        // next, the search criteria:
        char* p_srch_crit = read_string(is);

        // regardless of success or failure, we have to
        // delete p_srch_crit
        try {

            // get an iterator from the database (that is, find
            // the courses whose title/description or professor
            // contains the string "p_srch_crit") - an empty
            // or 0 string indicates that all courses match
            try {
                CourseSynopsisIterator crs_syn_iter(
                    m_db.get_courses(p_srch_crit)
                );
                // get all of the matches out of the database
                // and put them into a list:
                m_matches.length(crs_syn_iter.get_num_remaining());
                for (CORBA::ULong i = 0; i < m_matches.length(); i++) {
                    CourseSynopsis crs_syn = crs_syn_iter.next();
                    m_matches[i].course_number = crs_syn.get_course_number();
                    m_matches[i].title = crs_syn.get_title();
                }
                m_index = 0;
            }
            catch (SamplesNoMatches&) {
                m_matches.length(0);
                m_index = 0;
            }
            delete [] p_srch_crit;
        }
        catch (...) {
            delete [] p_srch_crit;
            throw;
        }
    }
    HANDLE_EX
}

//--------------------------------------------------------------------

UniversityT::CourseSynopsisList*
CourseSynopsisEnumerator_i::get_next_n(
    CORBA::ULong     number_to_get,
    CORBA::ULong_out number_remaining
)
{
    TRACE_METHOD("CourseSynopsisEnumerator_i::get_next_n");

    try {

        TRACE("number_to_get = " << number_to_get);

        // figure out how many course synopsis are available to
        // be returned
        unsigned long number_returned = m_matches.length() - m_index;

        TRACE("old number_remaining = " << number_returned);

        // if the user set a limit on how many to return, and
        // we have more, only return the amount the user is
        // willing to accept

        if (number_to_get > 0 && number_to_get < number_returned) {
            number_returned = number_to_get;
        }

        TRACE("number_returned = " << number_returned);

        // now that we have the size, create the list we want to return.
        // use a "var" for the returned list so that if anything
        // goes wrong, cleanup is automatic
        UniversityT::CourseSynopsisList_var v_crs_syn_lst =
            new UniversityT::CourseSynopsisList;
        v_crs_syn_lst->length(number_returned);

        // fill up the list
        for (CORBA::ULong i = 0; i < number_returned; i++, m_index++) {
            v_crs_syn_lst[i] = m_matches[m_index];
        }

        number_remaining = m_matches.length() - m_index;

        TRACE("v_crs_syn_lst = " << v_crs_syn_lst.in());
        TRACE("number_remaining = " << number_remaining);

        // tell the _var to give up its memory so that I
        // can pass it back to the system as a return value:
        return v_crs_syn_lst._retn();
    }
    HANDLE_EX
}

//--------------------------------------------------------------------

void CourseSynopsisEnumerator_i::destroy()
{
    TRACE_METHOD("CourseSynopsisEnumerator_i::destroy");

    try {

        // when the client calls "destroy" on the enumerator,
        // then this object needs to be "destructed".
        // do this by telling the TP framework that we're
        // done with this object.

        // note : if the client calls a method on
        // the enumerator after calling destroy, then the
        // enumerator gets re-activated and we start returning
        // the entire list again!

        TP::deactivateEnable();
    }
    HANDLE_EX
}

//====================================================================
// Registrar_i method implementations
//====================================================================

//--------------------------------------------------------------------

Registrar_i::Registrar_i(
    Database& db
) :
    m_db(db)
{
    TRACE_METHOD("Registrar_i::Registrar_i");
}

//--------------------------------------------------------------------

Registrar_i::~Registrar_i()
{
    TRACE_METHOD("Registrar_1::~Registrar_i");
}

//--------------------------------------------------------------------

UniversityT::CourseSynopsisList*
Registrar_i::get_courses_synopsis(
    const char*                               search_criteria,
    CORBA::ULong                              number_to_get,
    CORBA::ULong_out                          number_remaining,
    UniversityT::CourseSynopsisEnumerator_out rest
)
{
    TRACE_METHOD("Registrar_i::get_courses_synopsis");

    try {
        unsigned short len =
            (search_criteria == 0) ? 0 : strlen(search_criteria);

        TRACE(
            "search_criteria = " <<
            ((len == 0) ? "all" : search_criteria)
        );

        TRACE("number_to_get = " << number_to_get);

        // instead of querying the database directly, create an
        // object reference for an enumerator, and use that
        // reference to get the first batch of course synopsis
        // to return.

        // in the enumerator's object_id, record the search
        // criteria the enumerator's activate_object method
        // will extract this search criterial from the object_id
        // and use it to query the database

        // also put a unique id in the enumerator's object_id
        // so that each enumerator has it's own state

        // for the object id, use a "unique id" plus
        // the search criteria.  use an ostrstream to help:
        ostrstream os;
        {
            UniqueId uid = UniqueId::generate();
            os << uid;
        }
        os << ' ';
        write_string(os, search_criteria);
        os << ends;
        const char* object_id = os.str();
        os.rdbuf()->freeze(0);

        TRACE("object_id = " << object_id);

        // get the repository id for the enumerator's
        // IDL interface
        const char* crs_syn_enum_repos_id =
            UniversityT::_tc_CourseSynopsisEnumerator->id();

        // create an object reference for the enumerator:
        CORBA::Object_var rest_oref =
            TP::create_object_reference(
                crs_syn_enum_repos_id,
                object_id,
                CORBA::NVList::_nil()
            );

        UniversityT::CourseSynopsisEnumerator_var v_rest = 
            UniversityT::CourseSynopsisEnumerator::_narrow(
                rest_oref.in()
            );

        // use it to get the initial course synopsis list:
        UniversityT::CourseSynopsisList_var v_crs_syn_lst =
            v_rest->get_next_n(number_to_get, number_remaining);

        TRACE("v_crs_syn_lst = " << v_crs_syn_lst.in());
        TRACE("number_remaining = " << number_remaining);

        if (number_remaining == 0) {
            // since there are no more entries to retrieve,
            // destroy the enumerator and make sure we return
            // a "nil" one
            v_rest->destroy();
            v_rest = UniversityT::CourseSynopsisEnumerator::_nil();
            TRACE("returning nil enumerator");
        } else {
            TRACE("returning non-nil enumerator");
        }

        // make the vars give up their memory so that it
        // can be returned
        rest = v_rest._retn();
        return v_crs_syn_lst._retn();
    }
    HANDLE_EX
}

//--------------------------------------------------------------------

UniversityT::CourseDetailsList*
Registrar_i::get_courses_details(
    const UniversityT::CourseNumberList& courses
)
{
    TRACE_METHOD("Registrar_i::get_courses_details");

    try {
    
        TRACE("courses = " << courses);

        UniversityT::CourseDetailsList_var v_crs_det_lst =
           new UniversityT::CourseDetailsList();

        // get the courses' details
        for (CORBA::ULong i = 0; i < courses.length(); i++) {
            try {
                UniversityT::CourseDetails crs_det;
                get_crs_det(m_db, courses[i], crs_det);
                CORBA::ULong len = v_crs_det_lst->length();
                v_crs_det_lst->length(len+1);
                v_crs_det_lst[len] = crs_det;
            }
            catch (SamplesBadCourseId&) {
                // just don't send back details for it
                TRACE("invalid course number : " << courses[i]);
            }
        }

        TRACE("v_crs_det_lst = " << v_crs_det_lst.in());
        return v_crs_det_lst._retn();
    }
    HANDLE_EX
}

//--------------------------------------------------------------------

UniversityT::StudentDetails*
Registrar_i::get_student_details(
    UniversityT::StudentId stu_id
)
{
    TRACE_METHOD("Registrar_i::get_student_details");

    try {

        TRACE("stu_id = " << stu_id);

        UniversityT::StudentDetails_var v_stu_det =
            new UniversityT::StudentDetails();

        Student stu = m_db.get_student(stu_id);
        v_stu_det->student_id = stu.get_student_id();
        v_stu_det->name = stu.get_name();
        try {
            CourseNumberIterator crs_num_iter =
                stu.get_registered_courses();

            while (crs_num_iter.get_num_remaining() > 0) {
                UniversityT::CourseDetails crs_det;
                get_crs_det(m_db, crs_num_iter.next(), crs_det);
                CORBA::ULong len =
                    v_stu_det->registered_courses.length();
                v_stu_det->registered_courses.length(len+1);
                v_stu_det->registered_courses[len] = crs_det;
            }
        }
        catch (SamplesNoMatches&) {
           // that's ok!
        }
        TRACE("v_stu_det = " << v_stu_det.in());
        return v_stu_det._retn();
    }
    catch (SamplesBadStudentId&) {
        LOG("Invalid student id : " << stu_id);
        throw CORBA::BAD_PARAM();
    }
    HANDLE_EX
}

//--------------------------------------------------------------------

UniversityT::NotRegisteredList*
Registrar_i::register_for_courses(
    UniversityT::StudentId               stu_id,
    const UniversityT::CourseNumberList& crs_num_lst
)
{
    TRACE_METHOD("Registrar_i::register_for_courses");

    try {

        TRACE("stu_id = " << stu_id);
        TRACE("crs_num_lst = " << crs_num_lst);

        UniversityT::NotRegisteredList_var v_not_reg_lst =
            new UniversityT::NotRegisteredList();

        CORBA::UShort number_of_credits =  0;
        CORBA::UShort maximum_credits   = 18;

        // see how many credits we're already registered for:
        Student stu = m_db.get_student(stu_id);

        try {
            CourseNumberIterator crs_num_iter =
                stu.get_registered_courses();
            while (crs_num_iter.get_num_remaining() > 0) {
                Course course = m_db.get_course(crs_num_iter.next());
                number_of_credits += course.get_number_of_credits();
            }
        }
        catch (SamplesNoMatches&) {
            // we're not registered for any courses : that's ok!
        }

        // register for the courses :
        for (CORBA::ULong i = 0; i < crs_num_lst.length(); i++) {

            UniversityT::CourseNumber crs_num = crs_num_lst[i];

            try {
                TRACE("adding reg : " << stu_id << ", " << crs_num);
                m_db.add_registration(stu_id, crs_num);

                // have we registered for too many courses?
                // (only count courses we actually can register for!)
                Course crs = m_db.get_course(crs_num);
                number_of_credits += crs.get_number_of_credits();
                if (number_of_credits > maximum_credits) {
                    LOG("Too many credits for student : " << stu_id);
                    UniversityT::TooManyCredits e;
                    e.maximum_credits = maximum_credits;
                    throw e;
                }

            }
            catch (SamplesAlreadyRegistered&) {
                add_not_reg(
                    v_not_reg_lst.inout(),
                    crs_num,
                    UniversityT::AlreadyRegistered
                );
            }
            catch (SamplesBadCourseId&) {
                add_not_reg(
                    v_not_reg_lst.inout(),
                    crs_num,
                    UniversityT::NoSuchCourse
                );
            }
        }

        TRACE("v_not_reg_lst = " << v_not_reg_lst.in());
        return v_not_reg_lst._retn();
    }
    catch (UniversityT::TooManyCredits&) {
        // let it pass thru
        throw;
    }
    catch (SamplesBadStudentId&) {
        LOG("Invalid student id : " << stu_id);
        throw CORBA::BAD_PARAM();
    }
    HANDLE_EX
}

//====================================================================
// RegistrarFactory_i method implementations
//====================================================================

//--------------------------------------------------------------------

RegistrarFactory_i::RegistrarFactory_i ()
{
    TRACE_METHOD("RegistrarFactory_i::RegistrarFactory_i");
}

//--------------------------------------------------------------------

RegistrarFactory_i::~RegistrarFactory_i ()
{
    TRACE_METHOD("RegistrarFactory_i::~RegistrarFactory_i");
}

//--------------------------------------------------------------------

UniversityT::Registrar_ptr RegistrarFactory_i::find_registrar(
)
{
    TRACE_METHOD("RegistrarFactory_i::find_registrar");

    try {

        // get the repository id for the registrar's
        // IDL interface
        const char* reg_repos_id =
            UniversityT::_tc_Registrar->id();

        // since there's only one logical registrar right now
        // (we're not worrying about scalability yet), use a
        // canned object id.  It must not collide with other
        // ids in this process (e.g. registrar factory and
        // course synopsis enumerators).
        const char* object_id = "registrar";

        // create an object reference for the registrar
        // and return it.

        CORBA::Object_var v_reg_oref =
            TP::create_object_reference(
                reg_repos_id,
                object_id,
                CORBA::NVList::_nil()
            );

        return UniversityT::Registrar::_narrow(v_reg_oref.in());
    }
    HANDLE_EX
}

//--------------------------------------------------------------------
