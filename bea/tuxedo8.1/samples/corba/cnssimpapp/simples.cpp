//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// simplenss.cpp
//
// C++ server program for the simple sample application which has been
// modified to use the NamingService instead of the Factory Finder
//
// Implements the Server::initialize/create_servant/release methods
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <string.h> // for "strcmp"

// include necessary files for use of Tuxedo Name Service
#include <CosNaming_c.h>

#include <Server.h>
#include <TP.h>
#include "simple_i.h"

#include <time.h>   // for time() and getpid()
#include <fstream.h>

#ifdef WIN32
#include <process.h>
#include <strstrea.h>
#else
#include <unistd.h>
#include <strstream.h>
#endif

static CosNaming::NamingContext_var root;

static CORBA::Object_var s_v_fact_ref;

static int   s_pid       = 0; // this process id
static long  s_birth_sec = 0; // the second when this process started

//--------------------------------------------------------------------
// Method to start up the server
//--------------------------------------------------------------------

CORBA::Boolean Server::initialize(int argc, char* argv[])
{
	// Initialize the ORB :

	CORBA::ORB_var v_orb;

	try {
		v_orb = CORBA::ORB_init(argc, argv, "");
		}
	catch (...)
	{
		TP::userlog("Error initializing ORB");
	    return CORBA_FALSE;
	}

    // Create the bootstrap object:

	Tobj_Bootstrap * bootstrap;

    try{ 
		bootstrap = new Tobj_Bootstrap (v_orb.in(), "");
	}
	catch (...)
	{
		TP::userlog("Error connecting to the Tuxedo domain");
		return 1;
	}

	// retrieve the name service root obj ref

	try { 
		CORBA::Object_var obj = bootstrap->resolve_initial_references("NameService");
		root = CosNaming::NamingContext::_narrow (obj);
	}
	catch (...)
	{
		TP::userlog("Error retrieving name service root object reference");
	    return CORBA_FALSE;
	}


	// locate the SimpleFactory and perform the invocations

	// Establish Name used to identify the simple factory in the Name Service
	// This name must match the name used by the client application when
	// the Object Reference is being retrieved from the Name Service
	CosNaming::Name_var		factory_name = new CosNaming::Name(1);
	factory_name->length(1);
	factory_name[(CORBA::ULong) 0].id   = (const char *)"simple_factory";
	factory_name[(CORBA::ULong) 0].kind = (const char *) "";
	
	// create the factory object reference


    s_pid       = getpid();     // get my process id
    s_birth_sec = time(0);      // get the current time

    s_v_fact_ref =
        TP::create_object_reference(
            _tc_SimpleFactory->id(), // factory interface id
            "simple_factory",        // object id
            CORBA::NVList::_nil()    // routing criteria
        );


	// place the factory reference in the Name Service 
	try {
		root->bind( factory_name, s_v_fact_ref); 
	}
	catch (CosNaming::NamingContext::AlreadyBound& e)
	{
		TP::userlog("NamingContext Error, already bound %s", e.get_id());
	    return CORBA_FALSE;
	}
	catch (CosNaming::NamingContext::NotFound& e)
	{
		switch (e.why)
			{
			case CosNaming::NamingContext::missing_node:
				TP::userlog("NamingContext Error, missing node");
				break;

			case CosNaming::NamingContext::not_context:
				TP::userlog("NamingContext Error, not context");
				break;

			case CosNaming::NamingContext::not_object:
				TP::userlog("NamingContext Error, not object");
				break;
			}

	    return CORBA_FALSE;
	}
	catch (CosNaming::NamingContext::InvalidName& e)
	{
		TP::userlog("NamingContext Error, invalid name %s", e.get_id());
	    return CORBA_FALSE;
	}
	catch (CosNaming::NamingContext::CannotProceed& e)
	{
		TP::userlog("NamingContext Error, cannot proceed %s", e.get_id());
	    return CORBA_FALSE;
	}

    // we've succeeded:
    return CORBA_TRUE;
}

//--------------------------------------------------------------------
// Method to shutdown the server
//--------------------------------------------------------------------

void Server::release()
{

	// this will only be called if Server::initialize succeeded
    // thus we know that the factory has been bound in the 
    // Name Service.
    
	CosNaming::Name_var		factory_name = new CosNaming::Name(1);
	factory_name->length(1);
	factory_name[(CORBA::ULong) 0].id   = (const char *) "simple_factory";
	factory_name[(CORBA::ULong) 0].kind = (const char *) "";

    // unbind the simple factory reference.
    // use a try block since cleanup code shouldn't throw exceptions
    try {
	root->unbind( factory_name);
    }
	catch (CosNaming::NamingContext::NotFound& e)
	{
		switch (e.why)
			{
			case CosNaming::NamingContext::missing_node:
				TP::userlog("NamingContext Error, not found, missing node");
				break;

			case CosNaming::NamingContext::not_context:
				TP::userlog("NamingContext Error, not found, not context");
				break;

			case CosNaming::NamingContext::not_object:
				TP::userlog("NamingContext Error, not found, not object");
				break;
			}
	}
	catch (CosNaming::NamingContext::InvalidName& e)
	{
        TP::userlog("NamingContext Error, invalid name: %s", e.get_id());
	}
	catch (CosNaming::NamingContext::CannotProceed& e)
	{
        TP::userlog("NamingContext Error, cannot proceed: %s", e.get_id());
	}
    catch (...) {
        TP::userlog("Couldn't unbind the SimpleFactory");
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

