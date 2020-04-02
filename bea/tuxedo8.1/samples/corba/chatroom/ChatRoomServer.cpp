/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
// File ChatRoomServer.cpp

#include "Moderator_i.h"
#include <iostream.h>
#include <Server.h>
#include <TP.h>

/*
 * CLASS: Server
 *
 * The Tuxedo object definitions for integration in the Tuxedo
 * TP Framework. These are all callbacks, invoked at the correct
 *   time by the TPF.
 *     Server::initialize registers a ChatFactory by the name of "ChatRoom"
 *     Server::create_servant creates a new Moderator_i servant
 *     Server::release deregisters the factory
 */


 // Static variables and procedures

// the Moderator factory object reference -- a static variable
// so that we can unregister at shutdown.

CORBA::Object_var chat_room_factory_ref;

/*
 *  FUNCTION NAME:  Server::initialize
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Process specific initialization. 
 *      Called by TP Framework at process startup.
 *
 *      The only initialization needed is to register a "factory" for the
 *      ChatRoom. In this case, we don't really register a factory, we
 *      register a reference to a Moderator itself.
 *
 *      Thus, when a user finds a "factory", the user has found the 
 *      Moderator and uses it directly. This is a bit different from
 *      from the usual Tuxedo way of doing things and is not very scalable.
 *      However, a Chat Room is not scalable since it must be stateful.
 *
 */
CORBA::Boolean Server::initialize(int argc, char* argv[])
{

    CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv, "");

    try {
        // Create an object reference for this factory.
        // Do not use a try block since the object will not be
        //   created if an exception is thrown.
        chat_room_factory_ref = TP::create_object_reference(
            ChatRoom::_tc_ModeratorFactory->id(),       // Interf Repos Id
            "ChatRoom",                      // meaningless ObjectId 
            CORBA::NVList::_nil()            // No special needs
            );
    }
    catch (...) {
        TP::userlog("ERROR: Couldn't create object ref for Moderator");
        return CORBA_FALSE; 
    }
    
    try {
        TP::register_factory(chat_room_factory_ref, "ModeratorFactory");
    }
    catch (...) {
        // Failed to register. Do not worry about the reason why
        // Set the static factory ref to NIL to indicate 
        //   that unregistration should not be done at process rundown
        chat_room_factory_ref = CORBA::Object::_nil();
        throw;
   }

    return CORBA_TRUE;
}

/*
 *  FUNCTION NAME:  Server::create_servant
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Create and return a servant for the Moderator.
 *      Called by the TP Framework when servant is needed.
 */
Tobj_Servant Server::create_servant(const char* intf_repos_id)
{

    Tobj_Servant	ModeratorFactoryServant = NULL;
    const CORBA::Char	* ModeratorFactoryInterfaceName;
    const CORBA::Char	* ModeratorInterfaceName;

    try {

	    ModeratorFactoryInterfaceName = ChatRoom::ModeratorFactory::_get_interface_name();
	    ModeratorInterfaceName = ChatRoom::Moderator::_get_interface_name();

	    if ( ! strcmp ( intf_repos_id , ModeratorFactoryInterfaceName ) )
	    {
			ModeratorFactoryServant = new ModeratorFactory_i();
	    }
	    else if ( ! strcmp ( intf_repos_id , ModeratorInterfaceName ) )
	    {
			ModeratorFactoryServant = new Moderator_i();
	    }
		else
		{
			TP::userlog("ERROR: unexpected interface in ChatRoomServer: %s", intf_repos_id);
		}

	    return ModeratorFactoryServant;

    }
    catch (CORBA::Exception& e) {
        TP::userlog("ERROR: creating servant, '%s'", e.get_id() );
    }
    catch (...) {
        TP::userlog("ERROR: unexpected exception creating servant"); 
    }

    return 0; // unknown interface
}

/*
 *  FUNCTION NAME:  Server::release
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Process specific shutdown. 
 *      Called by TP Framework at process rundown.
 */
void Server::release()
{
    // only rundown needed is to unregister factory
    if (CORBA::is_nil(chat_room_factory_ref.in())) {
        return; // cleanup not necessary
    }

    // do not let any exceptions leak out :
    try {
        TP::unregister_factory(chat_room_factory_ref.in(), "ChatRoom");
    }
    catch (CORBA::Exception& ex) {
        TP::userlog("ERROR: CORBA exception : %s", ex.get_id());
    }
    catch (...) {
		TP::userlog("ERROR: Unexpected exception" );
    }

    // remember that we have cleaned up
    chat_room_factory_ref = CORBA::Object::_nil();
}
