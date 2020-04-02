//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simplefs.cpp
//
// C++ server program for the simpapp_par sample application
//
// Implements the Server::initialize/create_servant/release methods
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <string.h> // for "strcmp"
#include <Server.h>
#include <TP.h>
#include "simple_i.h"
#include "simplef_i.h"
#include "simplef_s.h"

//--------------------------------------------------------------------
// Use a file static variable to record the factory object reference
// since we need a way to pass the factory reference created in
// Server::initialize to Server::release so that we can unregister
// the factory.  Use a var so that the reference is automatically
// released when the process exits.
//--------------------------------------------------------------------

static CORBA::Object_var s_v_fact_ref;

//--------------------------------------------------------------------
// Method to start up the server
//--------------------------------------------------------------------

CORBA::Boolean Server::initialize(int argc, char* argv[])
{
    // create the factory object reference

    // For now use a single SimpleFactory, hence a non-unique
    // "simple_factory" for the object_id.

    // To make simpapp_par scalable, you must allow many SimpleFactories
    // to co-exist. So generate and use unique object_ids.

    s_v_fact_ref =
        TP::create_object_reference(
            _tc_SimpleFactory->id(), // factory interface id
            "simple_factory",        // object id
            CORBA::NVList::_nil()    // routing criteria
        );

    // register the factory reference with the factory finder:
    TP::register_factory(
        s_v_fact_ref.in(),          // factory object reference
        _tc_SimpleFactory->id()     // factory interface id
    );

    // we've succeeded:
    return CORBA_TRUE;
}

//--------------------------------------------------------------------
// Method to shutdown the server
//--------------------------------------------------------------------

void Server::release()
{
    // this will only be called if Server::initialize succeeded
    // thus we know that the factory has been registered with
    // the factory finder.

    // unregister the factory.
    // use a try block since cleanup code shouldn't throw exceptions
    try {
        TP::unregister_factory(
            s_v_fact_ref.in(),      // factory object reference
            _tc_SimpleFactory->id() // factory interface id
        );
    }
    catch (...) {
        TP::userlog("Couldn't unregister the SimpleFactory");
    }
}

//--------------------------------------------------------------------
// Method to create servants
//--------------------------------------------------------------------

Tobj_Servant Server::create_servant(const char* intf_repos_id)
{
    if (!strcmp(intf_repos_id, _tc_SimpleFactory->id())) {
        return new SimpleFactory_i();
    }

    return 0; // unknown interface
}

//--------------------------------------------------------------------

