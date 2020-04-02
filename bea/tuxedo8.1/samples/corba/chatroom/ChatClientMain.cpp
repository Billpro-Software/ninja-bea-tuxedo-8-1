//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
// File: ChatClient.cpp
//
// Client for a chat room. 
// This client gets the Chat Room name from the command line and asks
//   the operator for a handle. It then creates
//   a callback object to output other people's comments in the chat
//   room. Given those three pieces of information, it signs on to the
//   chat room. After this setup, it loops, looking for input from the
//   keyboard and allowing the ORB to service the callback (which
//   will output to the keyboard's window.

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#ifdef WIN32
#include "conio.h"
#endif
#include "Listener_i.h"
#include "ChatRoom_c.h"
#ifdef BEA_WRAPPER
#include <beawrapper.h>
#endif
#include "KeyboardManager.h"



int main(int argc, char **argv)
{

	CORBA::ORB_ptr				orb_ptr;
#ifdef BEA_WRAPPER
    BEAWrapper::Callbacks*      cb;
#else
    PortableServer::POA_ptr		root_poa_ptr = 0;
	PortableServer::POA_ptr		bidir_poa_ptr = 0;
#endif
	Tobj_Bootstrap				*bs;
    ChatRoom::Moderator_var		v_moderator_ref;
    char                        handle[MAX_HANDLE_LENGTH];
    char                        buffer[MAX_CHARS_ON_LINE];
    char                        from_who[MAX_HANDLE_LENGTH];
    Listener_i*                 listener_callback_servant;

    // Expect that the first paramater on the command line is the chat
    //  room name, to use in finding the correct chat room
    if (argc<2) {
        cerr << "usage: " << argv[0] <<
        	" <Chat Room Name> (such as 'Politics', no quotes)>" << endl;
        return 1;
    }

    CORBA::String_var v_chat_room_name = CORBA::string_dup(argv[1]);

    cout << "Attempting to contact the '"
    	 << v_chat_room_name.in()
    	 << "' Chat Room. Stand by..." << endl;

    // Initialize ORB, POA
    try {
        orb_ptr = CORBA::ORB_init(argc, argv, "BEA_IIOP");

#ifndef BEA_WRAPPER
        CORBA::PolicyList		policy_list(1);
		CORBA::Any val;

		CORBA::Object_ptr o_init_poa;
	    	o_init_poa = orb_ptr->resolve_initial_references("RootPOA");

		// Narrow to get the Root POA
		root_poa_ptr = PortableServer::POA::_narrow(o_init_poa);
		CORBA::release(o_init_poa);

		// Init the BiDir policy Any
		val <<= BiDirPolicy::BOTH;

		// Create BiDir Policy
		CORBA::Policy_ptr   bidir_pol_ptr = orb_ptr->create_policy(
		    BiDirPolicy::BIDIRECTIONAL_POLICY_TYPE, val);
		policy_list.length ( 1 );
		policy_list[0] = bidir_pol_ptr;

		// Create the BiDir POA
		bidir_poa_ptr = root_poa_ptr->create_POA("BiDirPOA", 
                                                 root_poa_ptr->the_POAManager(),
                                                 policy_list);

		// Activate the root POA, which also activates the BiDir POA
		root_poa_ptr->the_POAManager()->activate();
#endif
	}
	catch(const CORBA::Exception& ex) {
        cerr << "ERROR Starting ORB or POA" << endl
             << "   " << ex.get_id() << endl;
        return 1;
    }
    catch (...) {
        cerr << "ERROR unexpected exception" << endl; 
        return 1;
	}

    // Set up callback object, the "Listener"
	ChatClient::Listener_var v_listener_callback_ref;

	try {
        // Create a servant for Listener (to print chatter
        // from other participants) and activate it
        listener_callback_servant = new Listener_i();
        CORBA::Object_var           v_listener_oref;

#ifdef BEA_WRAPPER
        cb = new BEAWrapper::Callbacks( orb_ptr );
        v_listener_oref = cb->start_transient( listener_callback_servant, 
                                            ChatClient::_tc_Listener->id() );
#else
	    PortableServer::ObjectId_var temp_OId =
	    	bidir_poa_ptr ->activate_object ( listener_callback_servant );
	
		// Create object reference with repository_id and the
		// returned system ObjectId
		v_listener_oref = bidir_poa_ptr->create_reference_with_id( temp_OId,
											ChatClient::_tc_Listener->id() );
#endif
		v_listener_callback_ref =
			ChatClient::Listener::_narrow( v_listener_oref.in() );
    }
    catch(const CORBA::Exception& ex) {
        cerr << "ERROR while trying to create the listener_callback" << endl
             << "   " << ex.get_id() << endl;
        return 1;
    }
    catch(...) {
        cerr << "Failed to create listener_callback, can't start chatting."
        	<< endl;
        return 1;
    }

	// Create a bootstrap object (note: outside of a try block)
	try {
    	bs = new Tobj_Bootstrap(orb_ptr,"");
	}
	// Main Exception Handling
	catch (Tobj::InvalidDomain& ex) {
		cout << "User exception:" << ex.get_id() << endl;
		cout << "Make sure that the server is running" << endl;
		return 1;
	}
	catch (CORBA::UserException& ex) {
		cout << "User exception:" << ex.get_id() << endl;
		return 1;
	}
	catch (CORBA::SystemException& ex) {
		cout << "System exception:" << ex.get_id() << endl;
		return 1;
	}
	catch (...) {
		cout << "Unknown ChatClient exception" << endl;
		return 1;
	}


    // Get Factory Finder, find a moderator factory, get a moderator
	try {
	// Use the bootstrap object to find the factory finder
        CORBA::Object_var v_fact_finder_oref =
   			bs->resolve_initial_references("FactoryFinder");

	    // Narrow the factory finder
        Tobj::FactoryFinder_var v_factory_finder =
   			Tobj::FactoryFinder::_narrow(v_fact_finder_oref.in());

	    // Use the factory finder to find the
    	// ChatRoom Moderator's factory
        CORBA::Object_var v_mod_fact_oref =
   			v_factory_finder->find_one_factory_by_id( "ModeratorFactory" );

        // narrow the Moderator Factory
        ChatRoom::ModeratorFactory_var v_mod_factory =
			ChatRoom::ModeratorFactory::_narrow( v_mod_fact_oref.in() );

		// get a Moderator for us
        v_moderator_ref =
    		v_mod_factory->get_moderator( v_chat_room_name.in() );    
    }
    catch(const CosLifeCycle::NoFactory& ex) {
        cerr << "ERROR finding ChatRoom factory" << endl 
             << "   " << ex.get_id() << endl;
        return 1;
    }
    catch (Tobj::InvalidDomain& ex) {
        cerr << "ERROR Can't find the Domain" << endl 
             << "   " << ex.get_id() << endl;
        return 1;
	}
    catch (Tobj::InvalidName& ex) {
        cerr << "ERROR Invalid Name" << endl 
             << "   " << ex.get_id() << endl;
        return 1;
	}
    catch(const CORBA::Exception& ex) {
        cerr << "ERROR finding FactoryFinder or Moderator" << endl
             << "   " << ex.get_id() << endl;
        return 1;
    }
    catch (...) {
        cerr << "ERROR unexpected exception" << endl; 
        return 1;
	}

	
    // Get a handle. Since other people may have chosen the same one,
    //   give the user a chance to keep trying for a unique handle.
    short success = 0;
    while (!success)
	{
		try {
			cout << "What is your handle? ";
	        cin.getline(handle, MAX_HANDLE_LENGTH);
            if (strlen(handle)!=0) {    // ignore null input
	        
	            // Sign on to the chatroom, giving my handle
	            //	and listener_callback to receive chatter
	            //  from other visitors to the the chatroom
	            v_moderator_ref->signon( handle, v_listener_callback_ref.in() );

                // No exception means we succeeded
			    success = 1;
            };
	    }
	    catch(const ChatRoom::Moderator::IdAlreadyUsed&) {
	        cout << "The handle '" << handle
	        	 << "' is already in use. Try another." << endl;
	    }
	    catch(const ChatRoom::Moderator::NoRoomLeft&) {
	        cout << "The chat room is filled right now. Try again later."
	        	<< endl;
	        return 1;
	    }
	    catch(const CORBA::Exception& ex) {
	        cerr << "ERROR while trying to signon" << endl
	             << "   " << ex.get_id() << endl;
	        return 1;
	    }
	    catch(...) {
	        cerr << "ERROR Unexpected while attempting to signon"
	        	<< endl;
	        return 1;
	    }
	}


    cout << "You have signed onto the '" << v_chat_room_name.in() 
        << "' chat room. Use \\ to exit. Now behave yourself, " << handle << "!" << endl;
    
    // Since we must share the thread with the ORB, we loop, asking
    //  both the user at the command line and the ORB if there's
    //  anything to do

    // Set up the keyboard manager and start the loop.
    KeyboardManager* kb_mgr_ptr = new KeyboardManager(MAX_CHARS_ON_LINE, handle);
    if (!kb_mgr_ptr)
		return 0;

    while (1) {

        // First check the keyboard
        if (kb_mgr_ptr->input_available()) {

            // input from user is finally available, get it
            kb_mgr_ptr->get_line(buffer);

            // if the first character is "\" treat it as signoff
            if (buffer[0]=='\\') break;

            // send message only if it is not null, that is, it isn't
            //  length zero
            if (buffer[0]!=0) {
            	try {
                    v_moderator_ref->send( handle, buffer );
                }
        	    catch(const ChatRoom::Moderator::IdNotKnown&) {
	                cerr << "ERROR Unknown id" << endl;
	                return 1;
        	    }
	            catch(const CORBA::Exception& ex) {
	                cerr << "ERROR while trying to send" << endl
	                     << "   " << ex.get_id() << endl;
        	        return 1;
	            }
            }
        }

        // If there is ORB work to be done then do it
	    while (orb_ptr->work_pending())
		{
        	orb_ptr->perform_work();
        }

        // Finally, check to see if there's any input from other chatters
        //   If so, print it via the KeyboardManager
        if (listener_callback_servant->get_other_chatter(from_who, buffer)){
            kb_mgr_ptr->interrupt_output(from_who, buffer);
        };
#ifdef WIN32
        // Sleep for a 100 milliseconds to give the rest of the
        //  windows a chance. The unix 1 second granularity is
		//  too much
        _sleep(100);
#endif
    };
    
    cout << "Signing off." << endl;
    try {
    	v_moderator_ref->signoff( handle );
	    }
	    catch(const ChatRoom::Moderator::IdNotKnown&) {
	        cerr << "ERROR Unknown id"
	        	 << endl;
	        return 1;
	    }
	    catch(const CORBA::Exception& ex) {
	        cerr << "ERROR while trying to signoff" << endl
	             << "   " << ex.get_id() << endl;
	        return 1;
	    }

	// Clean up the KeyboardManager and on unix reset the terminal
	delete kb_mgr_ptr;

	delete bs;

#ifdef BEA_WRAPPER
	// Stop everything so that the POA that was created
	//  can be destroyed.
	cb->stop_all_objects();
	delete cb;
	cb = 0;
#else
	CORBA::release(bidir_poa_ptr);
	bidir_poa_ptr = 0;
#endif

	// Shutdown, wait for completion and clean up
	orb_ptr->shutdown(CORBA_TRUE);	
	CORBA::release(orb_ptr);
	orb_ptr = 0;

    return 0;
}

