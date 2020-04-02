//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// univos.cpp
//
// C++ server program for the university sample application
//
// Implements the Server::initialize/create_servant/release methods
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <string.h> // for "strcmp"
#include <log.h>
#include <Server.h>
#include <TP.h>
#include "univo_i.h"

//--------------------------------------------------------------------
// utitities to open and close the database

// connection to the database
// (set to 0 if cleanup not necessary)

// connect to the database when the server starts up, keep the
// connection open for the duration of the server, and hand the
// connection to servants as they are created (v.s. repeatedly
// connecting to the database as each servant is activated)

// normally the database is referenced by a stack
// allocated object.  however, since we have no
// place to stack allocate it, and the Database
// class doesn't have a no-arg constructor, use
// the copy constructor to heap allocate one:
Database* s_p_db = 0;

// lets exceptions leak out since it's initialization work:
static void open_database()
{
    // should protect against double initialization :

    s_p_db = new Database(Database::open_db());
}

// doesn't let exceptions leak out since it's cleanup work:
static void close_database()
{
    // don't need a "try/catch" block since
    // destructors should NEVER throw exceptions :
    delete s_p_db;
    s_p_db = 0;
}

//--------------------------------------------------------------------
// utilities to manage the registrar factory object reference

// the registrar factory's object reference
// (set to NIL if cleanup not necessary)

CORBA::Object_var s_v_fact_ref;

// lets exceptions leak out since it's initialization work
static void register_fact()
{
    // get the repository id for the registrar factory's
    // IDL interface
    const char* reg_fact_repos_id =
        UniversityO::_tc_RegistrarFactory->id();

    // use the same object id for all of my factories
    // this id must not collide with any other ids in this process
    // (that is, registrars and course enumerators)
    const char* object_id = "registrar_factory";

    // create an object reference for my factory
    // don't use a try block since the object should never be
    // created if an exception is thrown
    s_v_fact_ref =
        TP::create_object_reference(
            reg_fact_repos_id,
            object_id,
            CORBA::NVList::_nil()
        );

    try {
        // register the registrar_factory reference with
        // the factory finder
        TP::register_factory(s_v_fact_ref.in(), reg_fact_repos_id);
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

        // get the repository id for the registrar factory's
        // IDL interface
        const char* reg_fact_repos_id =
            UniversityO::_tc_RegistrarFactory->id();

        TP::unregister_factory(s_v_fact_ref.in(), reg_fact_repos_id);
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

static void cleanup()
{
    unregister_fact();

    close_database();
}

//====================================================================
// Server method implementations
//====================================================================

//--------------------------------------------------------------------
// Method to start up the server

CORBA::Boolean Server::initialize(int argc, char* argv[])
{
    TRACE_METHOD("Server::initialize");

    // if anything goes wrong, assume "release" isn't
    // called.  therefore, whatever we've done must be
    // undone.

    try {

        open_database();

        register_fact();

        return CORBA_TRUE;
    }
    catch (CORBA::Exception& e) {
        LOG("CORBA exception : " << e);
    }
    catch (SamplesCannotConnectDatabase&) {
        LOG("Can't connect to database");
    }
    catch (SamplesDBException& e) {
        LOG("Unexpected database error : " << e);
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

        // get the repository ids for the registrar factory,
        // registrar and course synopsis enumerator IDL interfaces
        // (that is, the IDL interfaces this server supports)
        const char* reg_fact_repos_id =
            UniversityO::_tc_RegistrarFactory->id();

        const char* reg_repos_id =
            UniversityO::_tc_Registrar->id();

        const char* crs_syn_enum_repos_id =
            UniversityO::_tc_CourseSynopsisEnumerator->id();

        if (!strcmp(intf_repos_id, reg_fact_repos_id)) {
            return new RegistrarFactory_i();
        }
        if (!strcmp(intf_repos_id, reg_repos_id)) {
            return new Registrar_i(*s_p_db);
        }
        if (!strcmp(intf_repos_id, crs_syn_enum_repos_id)) {
            return new CourseSynopsisEnumerator_i(*s_p_db);
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
