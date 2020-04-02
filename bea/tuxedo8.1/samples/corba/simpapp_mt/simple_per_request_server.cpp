//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simple_per_request_server.cpp
//
// C++ server program for the simpapp_mt sample application
//
// Implements the ServerBase methods that this server overrides.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <string.h> // for "strcmp"
#include <Server.h>
#include <TP.h>
#include "thread_macros.h"
#include "simple_per_request_server.h"
#include "simple_per_request_i.h"

#include <time.h>   // for time() and getpid()
#include <stdio.h>

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
SIMPTHR_DECLARE_CRITICAL_SECTION(uid_count_cs); // protect static count variable

//--------------------------------------------------------------------
// Method to start up the server
//--------------------------------------------------------------------

CORBA::Boolean simple_per_request_server::initialize(int argc, char* argv[])
{
    TP::userlog("initialize");

    // create the factory object reference

    // For now use a single SimpleFactory, hence a non-unique
    // "simple_factory" for the object_id.

    // To make simpapp scalable, you must allow many SimpleFactories
    // to co-exist. So generate and use unique object_ids.

    s_pid       = getpid();     // get my process id
    s_birth_sec = time(0);      // get the current time

    s_v_fact_ref =
        TP::create_object_reference(
            _tc_SimplePerRequestFactory->id(), // factory interface id
            "SimplePerRequestFactory",        // object id
            CORBA::NVList::_nil()    // routing criteria
        );

    // register the factory reference with the factory finder:
    TP::register_factory(
        s_v_fact_ref.in(),      // factory object reference
        _tc_SimplePerRequestFactory->id() // factory interface id
    );

    // Initialize the critical section which protects the static 
    // count variable used in generate_unique_id()
    SIMPTHR_INITIALIZE_CRITICAL_SECTION(uid_count_cs);

    // we've succeeded:
    return CORBA_TRUE;
}

//--------------------------------------------------------------------
// Method to shutdown the server
//--------------------------------------------------------------------

void simple_per_request_server::release()
{
    // this will only be called if Server::initialize succeeded
    // thus we know that the factory has been registered with
    // the factory finder.

    // unregister the factory.
    // use a try block since cleanup code shouldn't throw exceptions
    try {
        TP::unregister_factory(
            s_v_fact_ref.in(),      // factory object reference
            _tc_SimplePerRequestFactory->id() // factory interface id
        );
    }
    catch (...) {
        TP::userlog("Couldn't unregister the SimplePerRequestFactory");
    }

    try {
        SIMPTHR_DELETE_CRITICAL_SECTION(uid_count_cs);
    }
    catch (...) {
        TP::userlog("Couldn't delete the critical section");
    }
}

//--------------------------------------------------------------------
// Method to create servants
//--------------------------------------------------------------------

Tobj_Servant simple_per_request_server::create_servant(const char* intf_repos_id)
{
    TP::userlog("create_servant called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    if (!strcmp(intf_repos_id, _tc_SimplePerRequestFactory->id())) {
        return new SimplePerRequestFactory_i();
    }
    if (!strcmp(intf_repos_id, _tc_Simple->id())) {
        return new Simple_i();
    }
    return 0; // unknown interface
}

//--------------------------------------------------------------------
// Implementation of the create_servant_with_id method. This method
// is called to create a servant for a specific object. For the 
// purposes of this sample, we override the default implementation 
// to record the id of the thread that was used to execute this method.
//--------------------------------------------------------------------

Tobj_Servant simple_per_request_server::create_servant_with_id(const char* intf_repos_id, const char* stroid)
{
    TP::userlog("create_servant_with_id called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    // If necessary, we could do customized servant construction here,
    // using knowledge of the objectID that this servant is being activated
    // for. In this case, we don't need to do anything special so just
    // forward to our create_servant.
    return create_servant(intf_repos_id);
}

//--------------------------------------------------------------------
// Implementation of the thread_initialize method. This method
// is called to allow an application developer to do any initialization
// necessary before a thread is used to execute application methods.For 
// the purposes of this sample, we override the default implementation 
// to record the id of the thread that was used to execute this method.
//--------------------------------------------------------------------

CORBA::Boolean simple_per_request_server::thread_initialize(int argc, char** argv)
{
    TP::userlog("thread_initialize called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    // No special initialization necessary
    return CORBA_TRUE;
}

//--------------------------------------------------------------------
// Implementation of the thread_release method. This method is called 
// to allow an application developer to release any resources assigned
// to a thread in the thread_initialize method. For the purposes of 
// this sample, we override the default implementation to record the 
// id of the thread that was used to execute this method.
//--------------------------------------------------------------------

void simple_per_request_server::thread_release()
{
    TP::userlog("thread_release called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    // No special thread cleanup necessary
}

//--------------------------------------------------------------------

// function to generate a unique object id for the object id,
// use the pid + second the process started + a counter

char* generate_unique_id()
{
    // An oref is tied to a group and a group runs on one machine.
    // Hence it does not matter if servers on different machines start
    // at the same time with same pid. It is unlikely that a server is
    // shutdown, restarted within a second and gets the same pid.

    static long count = 0;
    char uniqueId[40];

    // Use a critical section to make sure that two threads don't generate
    // the same uniqueId
    SIMPTHR_ENTER_CRITICAL_SECTION(uid_count_cs);
        (void)sprintf(uniqueId, "%d-%ld-%ld", s_pid, s_birth_sec, count++);
    SIMPTHR_LEAVE_CRITICAL_SECTION(uid_count_cs);

    return CORBA::string_dup(uniqueId);
}
