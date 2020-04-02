//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simplec.cpp
//
// C++ client program for the simple sample SSL application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
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

        // Resolve SecurityCurrent
        CORBA::Object_var seccurobj = bootstrap.resolve_initial_references("SecurityCurrent");
        SecurityLevel2::Current_var seccur = SecurityLevel2::Current::_narrow(seccurobj.in());

#ifdef TEST_SSL_AUTH
        // This code can be used when certificate based authentication is
        // required. To enable certificate based authentication, enable
        // this code, specify the principal name (TUXCERTEMAIL definition
        // and the password pass phrase for the principal private key
        //

// SSL REQUIRED definitions
#define TUXCERTPASSWD ""
#define TUXCERTEMAIL  ""


        // Verify that all SSL required definitions have been resolved
        if((strlen(TUXCERTPASSWD) == 0) ||
           (strlen(TUXCERTEMAIL) == 0))
        {
                cerr << "Required SSL definitions not specified" << endl;
                exit(1);
        }

        // Perform client certificate-based authentication
        SecurityLevel2::Credentials_var the_creds;
        Security::AttributeList_var     privileges;
        Security::Opaque_var continuation_data;
        Security::Opaque_var auth_specific_data;
        Security::Opaque_var response_data;
    
        // Client certificate email address
        char emailAddress[] = TUXCERTEMAIL;

        // Client certificate private key password
        char password[] = TUXCERTPASSWD;

        // Convert the certificate private key password to opaque
        unsigned long password_len = strlen(password);
        Security::Opaque ssl_auth_data(password_len);

        // Authenticate client certificate with principal authenticator
        for(int i = 0; (unsigned long) i < password_len; i++)
            ssl_auth_data[i] = password[i];
        Security::AuthenticationStatus auth_status;
        SecurityLevel2::PrincipalAuthenticator_var PA = seccur->principal_authenticator();

        auth_status = PA->authenticate(Tobj::CertificateBased, emailAddress, ssl_auth_data,
                         privileges, the_creds, continuation_data, auth_specific_data);
        while(auth_status == Security::SecAuthContinue) {
                auth_status = PA->continue_authentication(
                        response_data,
                        the_creds,
                        continuation_data,
                        auth_specific_data);
        }
        if(auth_status != Security::SecAuthSuccess) {
                cerr << "Authenticate failed with status " << ((long) auth_status) << endl;
                exit(1);
        }
#endif        // TEST_SSL_AUTH

        // Use the bootstrap object to find the factory finder :
        CORBA::Object_var v_fact_finder_oref =
            bootstrap.resolve_initial_references("FactoryFinder");

        // Narrow the factory finder :
        Tobj::FactoryFinder_var v_fact_finder_ref =
            Tobj::FactoryFinder::_narrow(v_fact_finder_oref.in());

        // Use the factory finder to find the simple factory :
        CORBA::Object_var v_simple_factory_oref =
            v_fact_finder_ref->find_one_factory_by_id(_tc_SimpleFactory->id());

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
        cerr << "Unexpected exception" << endl;
    }

    return 1;
}
