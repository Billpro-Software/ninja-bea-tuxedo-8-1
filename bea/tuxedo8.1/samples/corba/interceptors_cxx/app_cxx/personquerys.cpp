
//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// personquerys.cpp
//
// C++ server program for the interceptors sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <Server.h>
#include <TP.h>
#include "personquery_i.h"


CORBA::Object_var	FactoryObjRef = CORBA::Object::_nil();

//***************************************************************************
// Method  : initialize
// Purpose : perform application server initialization
//***************************************************************************
CORBA::Boolean Server::initialize ( int argc , CORBA::Char ** argv )
{


    try
    {

    // get the repository id for the PersonQuery factory's
    // IDL interface
    const char* reg_fact_repos_id =
        _tc_QueryFactory->id();

    // use the same object id for my factory
    // this id must not collide with any other ids in this process
    const char* object_id = "QueryFactory";

	// Create  object reference and register with Finder
	//
	// TP::create_object_reference() throws:
	//			TobjS::IllegalInterface
	//			TobjS::InvalidInterface
	//			TobjS::InvalidObjectId		

	FactoryObjRef = TP::create_object_reference(
	    reg_fact_repos_id,		// Interface Name
	    object_id,			// Unique Object Id (string)
	    CORBA::NVList::_nil());	// Criteria


	// The register_factory() method locates the FactoryFinder and
	// registers an application 
	//
	// register_factory() throws:
	//			TobjS::AlreadyRegistered
	//			TobjS::CannotProceed
	//			TobjS::InvalidName
	//			TobjS::InvalidObject
	//			TobjS::RegistrarNotAvailable		

	TP::register_factory ( FactoryObjRef.in() , reg_fact_repos_id );
    } 

    catch (...)
    {
	// TP::userlog allows messages to be written to the ULOG file
	TP::userlog ( "ERROR: exception raised in Server::initialize()" );
        FactoryObjRef = CORBA::Object::_nil();
        return CORBA_FALSE;
    }

    return CORBA_TRUE;

}

//***************************************************************************
// Method  : release
// Purpose : perform application server cleanup before termination
//***************************************************************************

void Server::release()
{
    // get the repository id for the PersonQuery factory's
    // IDL interface
    const char* reg_fact_repos_id =
        _tc_QueryFactory->id();

    //
    // Unregister the factory with Finder
    //

    try
    {
    TP::unregister_factory ( FactoryObjRef.in() , reg_fact_repos_id );
    } 

    catch (...)
    {
    }
    FactoryObjRef = CORBA::Object::_nil();

    return;

}

//***************************************************************************
// Method	: create_servant
// Description	: create a servant for the various interfaces
//***************************************************************************

Tobj_Servant Server::create_servant ( const CORBA::Char * interfaceName )
{
    try {

        // get the repository ids for the PersonQuery factory interface
        // and the PersonQuery interface (that is, the interfaces this
        // server supports.)
        const char* reg_fact_repos_id =
            _tc_QueryFactory->id();

        const char* person_repos_id =
            _tc_PersonQuery->id();


        if (!strcmp(interfaceName, reg_fact_repos_id)) {
            return new QueryFactory_i();
        }

        if (!strcmp(interfaceName, person_repos_id)) {
            return new PersonQuery_i();
        }
     }

     catch (...) {
        TP::userlog("ERROR: unknown interface: %s\n", interfaceName);
     }
     return 0; // unknown interface

}

