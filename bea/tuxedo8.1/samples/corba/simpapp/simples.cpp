//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simples.cpp
//
// C++ server program for the simple sample application
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

#include <time.h>   // for time() and getpid()
#ifdef WIN32
#include <process.h>
#include <strstrea.h>
#else
#include <unistd.h>
#include <strstream.h>
#endif

//--------------------------------------------------------------------
// Use a file static variable to record the factory object reference
// since we need a way to pass the factory reference created in
// Server::initialize to Server::release so that we can unregister
// the factory.  Use a var so that the reference is automatically
// released when the process exits.
//--------------------------------------------------------------------

static CORBA::Object_var s_v_fact_ref;

static int   s_pid       = 0; // this process id
static long  s_birth_sec = 0; // the second when this process started

//--------------------------------------------------------------------
// Method to start up the server
//--------------------------------------------------------------------

CORBA::Boolean Server::initialize(int argc, char* argv[])
{
    // create the factory object reference

    // For now use a single SimpleFactory, hence a non-unique
    // "simple_factory" for the object_id.

    // To make simpapp scalable, you must allow many SimpleFactories
    // to co-exist. So generate and use unique object_ids.

    s_pid       = getpid();     // get my process id
    s_birth_sec = time(0);      // get the current time

    s_v_fact_ref =
        TP::create_object_reference(
            _tc_SimpleFactory->id(), // factory interface id
            "simple_factory",        // object id
            CORBA::NVList::_nil()    // routing criteria
        );

    // register the factory reference with the factory finder:
    TP::register_factory(
        s_v_fact_ref.in(),      // factory object reference
        _tc_SimpleFactory->id() // factory interface id
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
        TP::userlog("Couldn't unregistering the SimpleFactory");
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
    if (!strcmp(intf_repos_id, _tc_Simple->id())) {
        return new Simple_i();
    }
    return 0; // unknown interface
}

//--------------------------------------------------------------------

// method to generate a unique object id for the object id,
// use the pid + second the process started + a counter

char* generate_unique_id()
{
    // An oref is tied to a group and a group runs on one machine.
    // Hence it does not matter if servers on different machines start
    // at the same time with same pid. It is unlikely that a server is
    // shutdown, restarted within a second and gets the same pid.

    static long count = 0;
    ostrstream os;
    os << s_pid << ' ' << hex << s_birth_sec << ' ' << count++ << ends;
    char* str = os.str();
    os.rdbuf()->freeze(0);
    return CORBA::string_dup(str);
}
