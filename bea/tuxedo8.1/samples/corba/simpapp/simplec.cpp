//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simplec.cpp
//
// C++ client program for the simple sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <iostream.h>
#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#include "simple_c.h"

int main(int argc, char* argv[])
{
    // Note : this method uses vars since they automatically
    // release object references and strings.  This greatly
    // simplifies cleanup handing.

    try {
        // Initialize the ORB :
        CORBA::ORB_var v_orb = CORBA::ORB_init(argc, argv, "");

        // Create the bootstrap object:
        Tobj_Bootstrap bootstrap(v_orb.in(), "");

        // Use the bootstrap object to find the factory finder :
        CORBA::Object_var v_fact_finder_oref =
            bootstrap.resolve_initial_references("FactoryFinder");

        // Narrow the factory finder :
        Tobj::FactoryFinder_var v_fact_finder_ref =
            Tobj::FactoryFinder::_narrow(v_fact_finder_oref.in());

        // Use the factory finder to find the simple factory :
        CORBA::Object_var v_simple_factory_oref =
            v_fact_finder_ref->find_one_factory_by_id(
                _tc_SimpleFactory->id()
            );

        // Narrow the simple factory :
        SimpleFactory_var v_simple_factory_ref =
            SimpleFactory::_narrow(v_simple_factory_oref.in());

        // To make simpapp scalable, accept the parameter to identify
        // the client, and pass it to find_simple().

        // Find the simple object :
        Simple_var v_simple = v_simple_factory_ref->find_simple();

        // Get a string from the user :
        cout << "String?";
        char mixed[256]; // this should be big enough!
        cin >> mixed;

        // Convert the string to upper case :
        CORBA::String_var v_upper = CORBA::string_dup(mixed);
        v_simple->to_upper(v_upper.inout());
        cout << v_upper.in() << endl;

        // Convert the string to lower case :
        CORBA::String_var v_lower = v_simple->to_lower(mixed);
        cout << v_lower.in() << endl;

        // everything succeeded :
        return 0;
    }
    catch (CosLifeCycle::NoFactory& e) {
        cerr << "Can't find the simple factory : " << e.get_id() << endl;
    }
    catch (Tobj::InvalidDomain& e) {
        cerr << "Can't connect to the domain : " << e.get_id() << endl;
    }
    catch (CORBA::Exception& e) {
	cerr << "CORBA exception : " << e.get_id() << endl;
    }
    catch (...) {
	cerr <<"unexpected exception" << endl;
    }

    return 1;
}
