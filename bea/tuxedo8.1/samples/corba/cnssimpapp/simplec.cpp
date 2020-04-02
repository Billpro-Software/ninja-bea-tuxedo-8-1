//--------------------------------------------------------------------
//
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
// simplensc.cpp
//
// C++ client program for the simple sample application which has been
// modified to use the NamingService instead of the Factory Finder
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <wchar.h>
#include <stdlib.h>

#include <iostream.h>
#include <fstream.h>
 
#ifdef WIN32
#include <strstrea.h>
#else
#include <strstream.h>
#endif

// include necessary files for use of Tuxedo Name Service
#include <CosNaming_c.h>

#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#include "simple_c.h"

int main(int argc, char* argv[])
{
    // Note : this method uses vars since they automatically
    // release object references and strings.  This greatly
    // simplifies cleanup handing.

    // Initialize the ORB :

    CORBA::ORB_var v_orb;

    try {
        v_orb = CORBA::ORB_init(argc, argv, "");
    }
    catch (...)
    {
        cerr << "Error initializing ORB" << endl;
        return 1;
    }

    // Create the bootstrap object:

    Tobj_Bootstrap * bootstrap;

    try{ 
        bootstrap = new Tobj_Bootstrap (v_orb.in(), "");
    }
    catch (...)
    {
        cerr << "Error connecting to the Tuxedo domain" << endl;
        return 1;
    }

    // retrieve the name service root obj ref

    CosNaming::NamingContext_var    root;

    try { 
        CORBA::Object_var obj = bootstrap->resolve_initial_references("NameService");
        root = CosNaming::NamingContext::_narrow (obj);
    }
    catch (...)
    {
        cerr << "Error retrieving name service root object reference" << endl;
        return 1;
    }

    // locate the SimpleFactory and perform the invocations

    try {

        // Establish Name used to locate simple factory in the Name Service
        // This name must match the name used by the server application when
        // the Object Reference was placed into the Name Service
        CosNaming::Name_var		factory_name = new CosNaming::Name(1);
        factory_name->length(1);
        factory_name[(CORBA::ULong) 0].id   = (const char *) "simple_factory";
        factory_name[(CORBA::ULong) 0].kind = (const char *) "";

        // Locate the simple_factory in the Name Service
        CORBA::Object_var v_simple_factory_oref = root->resolve( *factory_name);

        // Narrow the simple factory :
        SimpleFactory_var v_simple_factory_ref =
        SimpleFactory::_narrow(v_simple_factory_oref.in());

        // To make simpapp scalable, accept the parameter to identify
        // the client, and pass it to find_simple().

        // Now use the reference just obtained from the Name Service to
        // Find the simple object :
        Simple_var v_simple = v_simple_factory_ref->find_simple();

        // Get a string from the user :
        cout << "String?";
        char mixed[256]; // this should be big enough!
        char lower[256];
        char upper[256];
        wchar_t wmixed[256];

        cin >> mixed;
        // convert the string to a wide char string, 
        // because this is what the server will expect
        mbstowcs(wmixed, mixed, 256);

        // Convert the string to upper case :
        CORBA::WString_var v_upper = CORBA::wstring_dup(wmixed);
        v_simple->to_upper(v_upper.inout());
        wcstombs(upper, v_upper.in(), 256);
        cout << upper << endl;

        // Convert the string to lower case :
        CORBA::WString_var v_lower = v_simple->to_lower(wmixed);
        wcstombs(lower, v_lower.in(), 256);
        cout << lower << endl;

        // everything succeeded :
        return 0;
    }
    catch (CosNaming::NamingContext::NotFound& e)
    {
        cerr << "Naming Context Error, ";

        switch (e.why)
        {
            case CosNaming::NamingContext::missing_node:
                cerr << "missing node: ";
                break;

            case CosNaming::NamingContext::not_context:
                cerr << "not context: ";
                break;

            case CosNaming::NamingContext::not_object:
                cerr << "not object: ";
                break;
        }

        cerr << e.get_id() << endl;
    }
    catch (CosNaming::NamingContext::InvalidName& e)
    {
        cerr << "NamingContext Error, invalid name" << e.get_id() << endl;
    }
    catch (CosNaming::NamingContext::CannotProceed& e)
    {
        cerr << "NamingContext Error, cannot proceed: " << e.get_id() << endl;
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

