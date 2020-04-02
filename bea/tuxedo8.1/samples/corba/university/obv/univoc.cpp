//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univoc.cpp
//
// C++ client program for the university sample application
//
// BEA Systems Inc. sample code
//
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

       UniversityO::CourseSynopsisEnumerator_var
*/

#include <ctype.h> // toupper
#include <log.h>
#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#include "univo_utils.h"
#include "valuetypes_i.h"

//--------------------------------------------------------------------

// utility to get a boolean response from the user

static int get_boolean_response(const char* question)
{
    while (1) {
	char c;
	cout << question << " ('y' or 'n')?";
	cin >> c;
	switch (toupper(c)) {
	    case 'Y': return 1;
	    case 'N': return 0;
	}
    }
    // never get here!
    return 0;
}

//--------------------------------------------------------------------

// utility to get an integer from the user

static long get_long(const char* prompt)
{
    while (1) {
        cout << prompt << '?';
        long val;
        if (cin >> val) {
            return val;
        }
        cin.clear();
        char buf[256];
        buf[0] = 0;
        cin >> buf;
        cerr << '"' << buf << '"' << " is not an integer." << endl;
    }
    // never get here!
    return 0;
}

//--------------------------------------------------------------------

// utility to get a list of (non-validated) course numbers
// from the user

// pass the list a param instead of returning a value to avoid a copy

static void get_crs_num_lst(
    UniversityO::CourseNumberList& crs_num_lst
)
{
    int done = 0;
    while (!done) {
	long crs_num = get_long("Course number (-1 to finish)");
	if (crs_num < 0) {
	    done = 1;
	} else {
	    crs_num_lst.length(crs_num_lst.length()+1);
	    crs_num_lst[crs_num_lst.length()-1] =
                CORBA::ULong(crs_num);
	}
    }
}

//--------------------------------------------------------------------

// utility to display a list of courses synopsis

// returns FALSE if the user said to stop displaying
// more courses, TRUE otherwise :

static CORBA::Boolean display_course_synopsis_list(
    const UniversityO::CourseSynopsisList& crs_syn_lst,
    CORBA::ULong                           num_remaining
)
{
    for (CORBA::ULong i = 0; i < crs_syn_lst.length(); i++) {

        cout << crs_syn_lst[i] << endl;

        // display 10 courses at a time
        if (
               ((i % 10) == 9) &&
               (
                   (i + 1) < crs_syn_lst.length() ||
                   num_remaining > 0
               )
           ) {

            // give the user a chance to abort the display
            cout << endl;
            CORBA::Boolean display_more =
                get_boolean_response("View more courses");
            if (!display_more) {
                return CORBA_FALSE;
            } else {
                cout << endl;
            }
        }
    }

    return CORBA_TRUE;
}

//--------------------------------------------------------------------

// utility to destroy an enumerator

static void destroy_enumerator(
    UniversityO::CourseSynopsisEnumerator_ptr p_crs_syn_enum
)
{
    // there is an enumerator, destroy it

    if (CORBA::is_nil(p_crs_syn_enum)) {
        return;
    }

    // don't let any errors leak out since this is cleanup work
    try {
        p_crs_syn_enum->destroy();
    }
    catch (CORBA::Exception& e) {
        LOG("CORBA Exception : " << e);
    }
    catch (...) {
        LOG("unexpected exception");
    }
}

//--------------------------------------------------------------------

// utility to get the list of courses matching a search criteria
// and present those courses' sysopsis to the user.
// afterwards, lets the user select some courses for details.

static void get_courses_synopsis(
    UniversityO::Registrar_ptr p_reg_ref,
    const char*                search_criteria
)
{
    cout << endl;

    // get no more than this many at a time.
    // this is used to make sure that we don't marshal too much
    // data in a single CORBA remote method invocation
    CORBA::ULong num_to_get = 30;

    // if there are more courses, they'll come back thru
    // this object
    UniversityO::CourseSynopsisEnumerator_var v_crs_syn_enum;

    // how many more matching courses are available ?
    CORBA::ULong num_remaining;

    // get the matching courses
    UniversityO::CourseSynopsisList_var v_crs_syn_lst =
        p_reg_ref->get_courses_synopsis(
            search_criteria,     // in
            num_to_get,          // in
            num_remaining,       // out
            v_crs_syn_enum.out() // out
        );

    if (v_crs_syn_lst->length() == 0) {

        // v_crs_syn_enum should be NIL
        // thus doesn't need to be destroyed

        if (!strcmp(search_criteria, ""))
           cout << "No courses were found." 
                << endl;
        else
           cout << "No courses matching \"" 
                << search_criteria
                << "\" were found." 
                << endl;
       return;
   }

    // regardless of what happens, we need to destroy the
    // enumerator if there is one :
    try {

        // print the results :
        CORBA::Boolean display_more =
           display_course_synopsis_list(
               v_crs_syn_lst.in(),
               num_remaining
           );

        // while there are more courses, use the enumerator
        // to get them, then present them to the user
        while (display_more && num_remaining > 0) {
            v_crs_syn_lst =
                v_crs_syn_enum->get_next_n(
                    num_to_get,   // in
                    num_remaining // out
                );
            display_more =
                display_course_synopsis_list(
                    v_crs_syn_lst.in(),
                    num_remaining
                );
        }

        destroy_enumerator(v_crs_syn_enum.in());
    }
    catch (...) {
        destroy_enumerator(v_crs_syn_enum.in());
        // rethrow the original exception:
        throw;
    }
}

//--------------------------------------------------------------------

// utility to get course numbers from the user, then
// print those courses' details

static void display_courses_details(
    UniversityO::Registrar_ptr p_reg_ref
)
{
    // get a list of course numbers (non-validated)
    // from the user
    UniversityO::CourseNumberList crs_num_lst;
    get_crs_num_lst(crs_num_lst);

    UniversityO::Courses_var v_crs_det_lst =
        p_reg_ref->get_courses(crs_num_lst);

    cout << v_crs_det_lst.in() << endl;

    // use the list of returned courses to figure out which
    // course numbers were invalid :

    for (CORBA::ULong i = 0; i < crs_num_lst.length(); i++) {
        CORBA::Boolean found = CORBA_FALSE;

        for (CORBA::ULong j = 0;
             j < v_crs_det_lst->length() && !found;
             j++) {
            if (crs_num_lst[i] == v_crs_det_lst[j]->course_number()) {
                found = CORBA_TRUE;
            }
        }
        if (!found) {
            cout << endl << "Invalid course number : "
                 << crs_num_lst[i] << endl;
        }
    }
}

//--------------------------------------------------------------------

// utility to drive the main user interface

static void main_menu(
    Tobj_Bootstrap&            bootstrap,
    UniversityO::Registrar_ptr p_reg_ref
)
{
    while (1) {

        cout                                       << endl;
        cout << "--------------------------------" << endl;
        cout << "Options"                          << endl;    
        cout << "--------------------------------" << endl;
        cout << "(F) Find courses"                 << endl;
        cout << "(A) List all courses"             << endl;
        cout << "(D) Display course details"       << endl;

        cout << "(E) Exit"                         << endl;
        cout << "--------------------------------" << endl;
        cout << "Option?";

        char option;
        cin >> option;

        switch (toupper(option)) {

          case 'F':
            {
                // display courses containing the string
                // "search_criteria" in the title, description
                // or professor fields

                // prompt the user for the search criteria.
                // this should be big enough:
                char search_criteria[256];
                cout << endl << "Search string?";
                cin >> search_criteria;

                get_courses_synopsis(p_reg_ref, search_criteria);
            }
            break;

          case 'A':

            // display all courses

            // passing in an empty search criteria means that
            // all courses will be returned.
            get_courses_synopsis(p_reg_ref, "");
            break;

          case 'D':
            display_courses_details(p_reg_ref);
            break;

          case 'E':
            return; // done

          default :
            cout << option << " is not a valid option." << endl;
            break;
        }
    }
}

//--------------------------------------------------------------------

// utility to get the registrar

static UniversityO::Registrar_ptr get_registrar(
    Tobj_Bootstrap&        bootstrap
)
{
    // Use the bootstrap object to find the factory finder :
    CORBA::Object_var v_fact_finder_oref =
        bootstrap.resolve_initial_references("FactoryFinder");

    // Narrow the factory finder :
    Tobj::FactoryFinder_var v_fact_finder_ref =
        Tobj::FactoryFinder::_narrow(v_fact_finder_oref.in());

    // Use the factory finder to find the
    // university's registrar factory :
    CORBA::Object_var v_reg_fact_oref =
        v_fact_finder_ref->find_one_factory_by_id(
            UniversityO::_tc_RegistrarFactory->id()
        );

    // Narrow the registrar factory :
    UniversityO::RegistrarFactory_var v_reg_fact_ref =
        UniversityO::RegistrarFactory::_narrow(
            v_reg_fact_oref.in()
        );

    // Return the university's registrar :
    return v_reg_fact_ref->find_registrar();
}

//--------------------------------------------------------------------

int main(int argc, char* argv[])
{
    try {
        // Initialize the ORB :
	    CORBA::ORB_var v_orb = CORBA::ORB_init(argc, argv, "");

	    //
	    // Register our valuetype factories
	    //
	    Course_factory * cf = new Course_factory;
	    v_orb->register_value_factory ("IDL:beasys.com/UniversityO/Course:1.0", cf);

        // Create the bootstrap object:
        Tobj_Bootstrap bootstrap(v_orb.in(), "");

        UniversityO::Registrar_var v_reg_ref =
            get_registrar(bootstrap);

        // Go do the real work :
        main_menu(bootstrap, v_reg_ref.in());

    }
    catch (CosLifeCycle::NoFactory& e) {
        LOG("Can't find the university's registrar factory : " << e);
    }
    catch (Tobj::InvalidDomain& e) {
        LOG("Can't connect to the domain : " << e);
    }
    catch (CORBA::Exception& e) {
	LOG("CORBA exception : " << e);
    }
    catch (...) {
	LOG("unexpected exception");
    }

    return 0;
}

//--------------------------------------------------------------------
