//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// billps.cpp
//
// C++ billing server program for the university sample application
//
// Implements the Server::initialize/create_servant/release methods
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <string.h> // for "strcmp"
#include <log.h>
#include <unique_id.h>
#include <Server.h>
#include <TP.h>
#include <tobj_c.h>
#include "billp_i.h"

//--------------------------------------------------------------------
// utilities to manage the teller factory object reference

// the teller factory's object reference
// (set to NIL if cleanup not necessary)

CORBA::Object_var s_v_fact_ref;

// lets exceptions leak out since it's initialization work
static void register_fact()
{
    // use a unique id for the object_id to allow many
    //teller factories to co-exist (for scaling)
    ostrstream os;
    UniqueId uid = UniqueId::generate();
    os << uid << ends;
    const char* object_id = os.str();
    os.rdbuf()->freeze(0);

    // create an object reference for my factory
    // don't use a try block since the object should never be
    // created if an exception is thrown
    s_v_fact_ref =
        TP::create_object_reference(
            BillingP::_tc_TellerFactory->id(),
            object_id,
            CORBA::NVList::_nil()
        );

    try {
        // register the registrar_factory reference with
        // the factory finder
        TP::register_factory(
            s_v_fact_ref.in(),
            BillingP::_tc_TellerFactory->id()
        );
        TRACE("registered factory");
    }
    catch (...) {
        // set the factory ref to NIL to indicate that
        // unregistration shouldn't be done:
        s_v_fact_ref = CORBA::Object::_nil();
        throw;
    }
}

// doesn't let exceptions leak out since it's cleanup work
static void unregister_fact()
{
    if (CORBA::is_nil(s_v_fact_ref.in())) {
        return; // cleanup not necessary
    }

    // don't let any exceptions leak out :
    try {
        TP::unregister_factory(
            s_v_fact_ref.in(),
            BillingP::_tc_TellerFactory->id()
        );
    }
    catch (CORBA::Exception& e) {
        LOG("CORBA exception : " << e);
    }
    catch (...) {
        LOG("unexpected exception");
    }

    // remember that we've cleaned up
    s_v_fact_ref = CORBA::Object::_nil();
}

//--------------------------------------------------------------------
// utilities to manage "transaction resource manager"-ness

// record whether or not we became transactional
// (thus require cleanup)

// note : if it's safe to call TP::close_xa_rm
// regardless if TP::open_xa_rm was successfully called,
// then we can get rid of this :

CORBA::Boolean s_became_transactional = CORBA_FALSE;

// let's exceptions leak out since it's initialization work
static void begin_transactional()
{
    // should protect against double initialization :

    TP::open_xa_rm();
    s_became_transactional = CORBA_TRUE;
}

// doesn't let exceptions leak out since it's cleanup work
static void end_transactional()
{
    if (!s_became_transactional) {
        return; // cleanup not necessary
    }

    try {
        TP::close_xa_rm();
    }
    catch (CORBA::Exception& e) {
        LOG("CORBA Exception : " << e);
    }
    catch (...) {
        LOG("unexpected exception");
    }

    // remember that we've cleaned up
    s_became_transactional = CORBA_FALSE;
}

//--------------------------------------------------------------------

static void cleanup()
{
    unregister_fact();

    end_transactional();
}

//====================================================================
// Server method implementations
//====================================================================

//--------------------------------------------------------------------
// Method to start up the server

CORBA::Boolean Server::initialize(int arc, char* argv[])
{
    TRACE_METHOD("Server::initialize");

    // if anything goes wrong, assume "release" isn't
    // called.  therefore, whatever we've done must be
    // undone.

    try {
        begin_transactional();
        register_fact();
        return CORBA_TRUE;
    }
    catch (CORBA::Exception& e) {
        LOG("CORBA exception : " << e);
    }
    catch (...) {
        LOG("unexpected exception");
    }

    // if we get here, something went wrong.
    // cleanup whatever we successfully started:
    cleanup();

    return CORBA_FALSE;
}

//--------------------------------------------------------------------
// Method to shutdown the server

void Server::release()
{
    TRACE_METHOD("Server::release");
    cleanup();
}

//--------------------------------------------------------------------
// Method to create servants

Tobj_Servant Server::create_servant(const char* intf_repos_id)
{
    TRACE_METHOD("create servant");

    try {
        if (!strcmp(
                 intf_repos_id,
                BillingP::_tc_TellerFactory->id()
             )) {
            return new TellerFactory_i();
        }
        if (!strcmp(
                 intf_repos_id,
                 BillingP::_tc_Teller->id()
             )) {
            return new
                Teller_i();
        }
        LOG("unexpected interface : " << intf_repos_id);
    }
    catch (CORBA::Exception& e) {
        LOG("CORBA Exception : " << e);
    }
    catch (...) {
        LOG("unexpected exception");
    }

    return 0; // unknown interface
}

//--------------------------------------------------------------------
