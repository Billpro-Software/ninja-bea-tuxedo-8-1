//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simple_per_object_i.cpp
//
// The simpapp_mt sample application provides two different implementations
// of the Simple interface. This source file includes implementations for
// Simple and SimplePerObjectFactory servants which will be included in
// a reentrant server which will be started using a Thread-per-Object 
// concurrency policy.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <ctype.h> // toupper, tolower
#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#include <TP.h>
#include "thread_macros.h"  // platform-independent thread convenience macros
#include "simple_per_object_i.h"

// Declare function which will be executed in an application-managed thread
extern "C" {SIMPTHR_THREAD_ROUTINE_RETURN execute_forward(void*); }

// Context information which will be shared with an application-
// managed child thread. See Simple_i::forward_upper for an example.
struct ThreadInfo
{
    SIMPTHR_ID id;
    SIMPTHR_ID caller_id;
    SIMPTHR_HANDLE handle;
    SIMPTHRSignalWait * event;
    long context;
    CORBA::Char* input;
    CORBA::Char* result;
};

//--------------------------------------------------------------------
// Implementation of the Simple_i::activate_object method. This method
// is called to associate this servant with a specific object, as 
// directed by the activation policies.
//--------------------------------------------------------------------

void Simple_i::activate_object(const char* stroid)
{
    TP::userlog("activate_object called in thread %lu for objectid %s", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID,
                stroid);
}

//--------------------------------------------------------------------
// Implementation of the Simple_i::deactivate_object method. This method
// is called to remove the association between this servant and a 
// specific object, as directed by the activation policies.
//--------------------------------------------------------------------

void Simple_i::deactivate_object(const char* stroid,
                            TobjS::DeactivateReasonValue reason)
{
    TP::userlog("deactivate_object called in thread %lu for objectid %s", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID,
                stroid);
}

//--------------------------------------------------------------------
// Implementation of the Simple_i::to_lower method which converts
// a string to lower case.
//--------------------------------------------------------------------

CORBA::Char* Simple_i::to_lower(const char* val)
{
    TP::userlog("Method to_lower called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    // Convert the string to lower case.
    CORBA::String_var v_lower = CORBA::string_dup(val);
    for (char* p = v_lower; p && *p; p++) {
        *p = tolower(*p);
    }

    return v_lower._retn();
}

//--------------------------------------------------------------------
// Implementation of the Simple_i::to_upper method which converts
// a string to upper case.
//--------------------------------------------------------------------

CORBA::Char* Simple_i::to_upper(const char* val)
{
    TP::userlog("Method to_upper called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    // Convert the string to upper case.
    CORBA::String_var v_upper = CORBA::string_dup(val);
    for (char* p = v_upper; p && *p; p++) {
        *p = toupper(*p);
    }

    return v_upper._retn();
}

//--------------------------------------------------------------------
// Implementation of the Simple_i::forward_lower method. forward_lower
// has the same application semantics as to_lower, but is implemented
// by creating another instance of Simple and directing that instance
// to do a to_lower. 
//--------------------------------------------------------------------

CORBA::Char* Simple_i::forward_lower(const char* val)
{
    CORBA::Object_var v_object;
    Tobj::FactoryFinder_var v_fact_finder_ref;
    SimplePerObjectFactory_var v_factory_ref;
    Simple_var v_simple;

    TP::userlog("Method forward_lower called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    // Find the Factory Finder
    v_object = TP::bootstrap()->resolve_initial_references("FactoryFinder");
    v_fact_finder_ref = Tobj::FactoryFinder::_narrow(v_object.in());

    // Use the factory finder to find the factory
    v_object = v_fact_finder_ref->find_one_factory_by_id(_tc_SimplePerObjectFactory->id());
    v_factory_ref = SimplePerObjectFactory::_narrow(v_object.in());

    // Create a new instance of Simple, and ask it to do the to_lower method
    v_simple = v_factory_ref->find_simple();

    return v_simple->to_lower(val);
}

//--------------------------------------------------------------------
// Implementation of the Simple_i::forward_upper method. forward_upper
// has the same application semantics as to_upper, but is implemented
// by creating an application managed child thread and asking that thread
// make a request for the to_upper operation.
//--------------------------------------------------------------------

CORBA::Char* Simple_i::forward_upper(const char* val)
{
    TP::userlog("Method forward_upper called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    ThreadInfo * thread = new ThreadInfo();
    if (!thread)
    {
        TP::userlog("  Error: memory allocation failed");
        return CORBA::string_dup("");
    }

    // Fetch the current thread context
    thread->handle = SIMPTHR_HANDLE_NULL;
    thread->input = CORBA::string_dup(val);
    thread->result = NULL;
    thread->context = TP::orb()->get_ctx();
    thread->caller_id = SIMPTHR_GETCURRENTTHREADID;

    thread->event = new ORBNEWTHROW SIMPTHRSignalWait();
    if (!(thread->event) ||
        !(thread->event->Initialized()))
    {
        TP::userlog("  Error: event creation failed");
        return CORBA::string_dup("");
    }

    // Create a new thread
    SIMPTHR_CREATE_THREAD(thread->handle, execute_forward, thread);
    if (thread->handle == SIMPTHR_HANDLE_NULL)
    {
        TP::userlog("  Error: application managed thread creation failed");
        return CORBA::string_dup("");
    }

    // Wait for the thread to complete
    thread->event->Wait();

    CORBA::string_free(thread->input);
    delete thread->event;

    // return result
    CORBA::Char * ret_val; 
    if (thread->result)
        ret_val = thread->result;
    else 
        ret_val = CORBA::string_dup("");
    delete thread;
    return ret_val;
}

//--------------------------------------------------------------------
// Implementation of the SimpleFactory_i::find_simple method which
// creates an object reference to a Simple object.
//--------------------------------------------------------------------

Simple_ptr SimplePerObjectFactory_i::find_simple()
{
    TP::userlog("Method find_simple called in thread %lu", 
                (unsigned long)SIMPTHR_GETCURRENTTHREADID);

    // Instead of a non-unique id eg. "simple", use a unique id for the
    // object_id to allow many simple objects to co-exist. This will help
    // to avoid contention when running a lot of clients.
    CORBA::String_var oid = generate_unique_id();

    CORBA::Object_var v_simple_oref =
        TP::create_object_reference(
            _tc_Simple->id(),     // interface id
            oid.in(),             // object id
            CORBA::NVList::_nil() // routing criteria
        );

    // Send back the narrowed reference.  The ORB will
    // be responsible for releasing it since it's a return value.
    return Simple::_narrow(v_simple_oref.in());
}

//--------------------------------------------------------------------

extern "C"
{
    SIMPTHR_THREAD_ROUTINE_RETURN execute_forward(void* ThreadInfoArg)
    {
        CORBA::Object_var v_object;
        Tobj::FactoryFinder_var v_fact_finder_ref;
        SimplePerObjectFactory_var v_factory_ref;
        Simple_var v_simple;
        ThreadInfo* thread = (ThreadInfo*)ThreadInfoArg;
        thread->id = SIMPTHR_GETCURRENTTHREADID;

        SIMPTHR_THREAD_DETACH;

        TP::userlog("Method execute_forward called in thread %lu by thread %lu", thread->id, thread->caller_id);

        try
        {
            // Set the thread context to our creators
            TP::orb()->set_ctx(thread->context);

            // Execute the request
            // Find the Factory Finder
            v_object = TP::bootstrap()->resolve_initial_references("FactoryFinder");
            v_fact_finder_ref = Tobj::FactoryFinder::_narrow(v_object.in());

            // Use the factory finder to find the factory
            v_object = v_fact_finder_ref->find_one_factory_by_id(_tc_SimplePerObjectFactory->id());
            v_factory_ref = SimplePerObjectFactory::_narrow(v_object.in());

            // Create a new instance of Simple, and ask it to do the to_upper method
            v_simple = v_factory_ref->find_simple();
            thread->result = v_simple->to_upper(thread->input);

            TP::userlog("Method execute_forward completed in thread %lu", thread->id);
        }
        catch (CORBA::SystemException & exc)
        {
            TP::userlog("ERROR: CORBA::SystemException caught during execute_forward in thread %lu", thread->id);
            TP::userlog("Exception: %s", exc.get_id());
        }
        catch (...)
        {
            TP::userlog("ERROR: Unknown exception thrown during execute_forward in thread %lu", thread->id);
        }

        // Finished with CORBA calls, clear the thread context
        try 
        {
            TP::orb()->clear_ctx();
        }
        catch (...)
        {
            TP::userlog("ERROR: Unknown exception thrown during clear_ctx in thread %lu", thread->id);
        }

        // Signal thread completion for the creator of this thread
        TP::orb()->inform_thread_exit(thread->id);
        thread->event->Signal();
        SIMPTHR_RETURN_FROM_THREAD_ROUTINE(0);
    }
}
