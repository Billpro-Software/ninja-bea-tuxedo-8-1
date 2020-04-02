//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simple_client.cpp
//
// C++ client program for the simpapp_mt sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <iostream.h>
#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#include "simple_c.h"

int convert_using(const int requestCount, 
                  CORBA::ORB_ptr v_orb, 
                  char* prompt, 
                  Simple_ptr v_simple);

int main(int argc, char* argv[])
{
    Simple_var v_simple;
    CORBA::Object_var v_simple_factory_oref;

    try 
    {
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

        // Ask the user how many simultaneous requests they would like to do
        cout << "Number of simultaneous requests to post (1-50)? ";
        int requestCount;
        cin >> requestCount;
        if (requestCount < 1 || requestCount > 50)
            requestCount = 5;

        // Use the factory finder to find factory that can create
        // an instance in the thread-per-request server
        CORBA::Object_var v_simple_factory_oref =
            v_fact_finder_ref->find_one_factory_by_id(
                _tc_SimplePerRequestFactory->id());

        SimplePerRequestFactory_var v_simple_per_request_factory_ref =
            SimplePerRequestFactory::_narrow(v_simple_factory_oref.in());

        // Create the Simple object, and interact with it.
        v_simple = v_simple_per_request_factory_ref->find_simple();
        if (convert_using(requestCount,
                          v_orb.in(),
                          (char*)"String to convert using thread-per-request server?", 
                          v_simple.in()))
            return 1;

        // Now do the same using the thread-per-object server
        // implementation of Simple.  Note that these requests 
        // will serialize because they all are made using the 
        // same object and are using the thread-per-object server.
        // In order to make the requests run concurrently, the 
        // code for the convert_using function could be changed 
        // to create a different Simple object for each request 
        // rather than using the one that is passed in as a 
        // parameter.
        v_simple_factory_oref =
            v_fact_finder_ref->find_one_factory_by_id(
                _tc_SimplePerObjectFactory->id());

        SimplePerObjectFactory_var v_simple_per_object_factory_ref =
            SimplePerObjectFactory::_narrow(v_simple_factory_oref.in());

        // Create the Simple object, and interact with it.
        v_simple = v_simple_per_object_factory_ref->find_simple();
        if (convert_using(requestCount,
                          v_orb.in(),
                          (char*)"String to convert using thread-per-object server?", 
                          v_simple.in()))
            return 1;

        return 0;
    }
    catch (CosLifeCycle::NoFactory& e) 
    {
        cerr << "Can't find the simple factory : " << e.get_id() << endl;
    }
    catch (Tobj::InvalidDomain& e) 
    {
        cerr << "Can't connect to the domain : " << e.get_id() << endl;
    }
    catch (CORBA::Exception& e) 
    {
        cerr << "CORBA exception : " << e.get_id() << endl;
    }
    catch (...) 
    {
        cerr <<"unexpected exception" << endl;
    }

    return 1;
}

//--------------------------------------------------------------------
//
// Ask the user for a string to convert using the specified server
// object
//
//--------------------------------------------------------------------

int convert_using(const int requestCount, 
                  CORBA::ORB_ptr v_orb, 
                  char* prompt, 
                  Simple_ptr v_simple)
{
    CORBA::Any              val_any;
    CORBA::String           v_result[50];
    CORBA::Any              result_any[50];
    CORBA::Request_ptr      requests[50];
    CORBA::Context_ptr      context;
    CORBA::NVList_var       arg_list[50];
    CORBA::NamedValue_var   resultp[50];

    try
    {
        v_orb->get_default_context(context);

        // Get a string to convert from the user
        cout << prompt;
        char mixed[256]; // this should be big enough!
        cin >> mixed;
        val_any <<= mixed;

        // Create a bunch of requests to convert the string to lower case
        int idx;
        for (idx=0; idx<requestCount; idx++)
        {
            v_orb->create_list(1, arg_list[idx].out());
            arg_list[idx]->add_value("val", val_any, CORBA::ARG_IN);
            result_any[idx].replace(CORBA::_tc_string, &v_result[idx]);
            resultp[idx] = v_orb->create_named_value(0,&result_any[idx],0);
            v_simple->_create_request (context, "forward_lower", arg_list[idx].in(), 
                                       resultp[idx].in(), requests[idx], 0);
        }

        // Send the requests to the server
        CORBA::ORB::RequestSeq rseq1 (requestCount, requestCount, requests, CORBA_FALSE);
        cout << "Sending " << requestCount << " deferred forward_lower requests" << endl;
        v_orb->send_multiple_requests_deferred (rseq1);

        // Get the responses from the server
        for (idx=0; idx<requestCount; idx++)
        {
            requests[idx]->get_response();
            char* val_result;
            result_any[idx] >>= val_result;
            cout << "forward_lower request #" << idx << " returned:" << val_result << endl;
            CORBA::string_free(val_result);
            CORBA::release(requests[idx]);
        }

        // Create a bunch of requests to convert the string to upper case
        for (idx=0; idx<requestCount; idx++)
        {
            v_orb->create_list(1, arg_list[idx].out());
            arg_list[idx]->add_value("val", val_any, CORBA::ARG_IN);
            result_any[idx].replace(CORBA::_tc_string, &v_result[idx]);
            resultp[idx] = v_orb->create_named_value(0,&result_any[idx],0);
            v_simple->_create_request (context, "forward_upper", arg_list[idx].in(), 
                                       resultp[idx].in(), requests[idx], 0);
        }

        // Send the requests to the server
        CORBA::ORB::RequestSeq rseq2 (requestCount, requestCount, requests, CORBA_FALSE);
        cout << "Sending " << requestCount << " deferred forward_upper requests" << endl;
        v_orb->send_multiple_requests_deferred (rseq2);

        // Get the responses from the server
        for (idx=0; idx<requestCount; idx++)
        {
            requests[idx]->get_response();
            char* val_result;
            result_any[idx] >>= val_result;
            cout << "forward_upper request #" << idx << " returned: " << val_result << endl;
            CORBA::string_free(val_result);
            CORBA::release(requests[idx]);
        }

        // everything succeeded
        CORBA::release(context);
        return 0;
    }
    catch (CORBA::Exception& e) 
    {
        cerr << "CORBA exception : " << e.get_id() << endl;
    }
    catch (...) 
    {
        cerr <<"unexpected exception" << endl;
    }

    return 1;
}
