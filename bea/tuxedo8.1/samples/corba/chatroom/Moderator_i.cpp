/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/* File: Moderator_i.cpp
 * 
 * Implementation for 
 *      ChatRoom::Moderator 
 *      ChatRoom::ModeratorFactory
 * -----------------------------------------------------------------------
 *
 */
#include "Moderator_i.h"
#include <TP.h>
#include <string.h>
#include <iostream.h>

/*
 *
 *  FUNCTION NAME: 	ChatRoom_i::signon
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      IDL operation implementation.
 *      Add the person handle and the person's callback to the list. 
 *      Error conditions: Use of handle "Moderator". (ChatRoom::Moderator::IdAlreadyUsed)
 *                        Handle already in use.     (ChatRoom::Moderator::IdAlreadyUsed)
 *                        No room in the list.       (ChatRoom::Moderator::NoRoomLeft)
 *      
 */

void Moderator_i::signon ( const char *              who,
                           ChatClient::Listener_ptr  callback_ref) 
{                             
    // look first to see if it's already there. if so, error
    if (!strcmp(who,"Moderator") || (find(who)!=CHATTER_LIMIT))
        throw ChatRoom::Moderator::IdAlreadyUsed();

    // look for a place to put it. If find one, insert it and return
    for (int i = 0; i< CHATTER_LIMIT; i++) {
        if (!chatters[i]) {
            callbacks[i]=ChatClient::Listener::_duplicate(callback_ref);
            chatters[i]=CORBA::string_dup(who);
			TP::userlog("Chatroom '%s': Handle '%s' signed on in slot '%i'.", 
                        m_chatroom_name, who, i);

            // Tell any others that this person has signed on
            send( who, " is signing on.");
            return;
        }
    }
    // didn't find anyplace to put it, signal an error
	TP::userlog("Chatroom '%s': No room for signon of Handle '%s', throw exception.", 
                m_chatroom_name, who);
    throw ChatRoom::Moderator::NoRoomLeft();
}

/*
 *
 *  FUNCTION NAME: 	Moderator_i::send
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      IDL operation implementation.
 *      A member of the Moderator is sending a message to be broadcast
 *      to all other members of the Moderator. 
 *
 *      We first validate that the handle of the sender is known to us.
 *          (If not, exception ChatRoom::Moderator::IdNotKnown)
 *      Then relay the message to all other members.
 */
void Moderator_i::send (const char * who,
                        const char * input_line) 
{
    int index_of_sender = find(who);
    if (index_of_sender==CHATTER_LIMIT)
        throw ChatRoom::Moderator::IdNotKnown();

	TP::userlog("Chatroom '%s': Handle: '%s', slot '%i', sent in '%s'", 
                m_chatroom_name, who, index_of_sender, input_line);

    for (int i=0; i<CHATTER_LIMIT; i++ ) {
        if (chatters[i] != 0) {
            if (i != index_of_sender) {
            	TP::userlog("Chatroom '%s': Message from handle '%s' sent out to '%s'.", 
                            m_chatroom_name, who, chatters[i]);
                try {
                    callbacks[i] -> post( who, input_line );
                }
                catch(const CORBA::Exception& ex) {
                    // something failed on the send
            	    TP::userlog("Chatroom '%s': Message sent to '%s' failed. Exception: %s", 
                            m_chatroom_name, chatters[i], ex.get_id());
                }
            }
        }
    }
}

/*
 *
 *  FUNCTION NAME: 	Moderator_i::signoff
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      IDL operation implementation.
 *      Remove the person whose handle is given.
 *          Error conditions: Handle not on list (ChatRoom::Moderator::IdNotKnown)
 *      After removing the handle, check to see if the list is empty.
 *          If it is, shut down the moderator (deactivate it).
 *
 */
void Moderator_i::signoff (const char * who) 
{
    int index = find(who);    
    if (index!=CHATTER_LIMIT) {
        if (chatters[index] != 0)
        {
            TP::userlog("Chatroom '%s': Handle '%s' signed off from slot '%i'.", 
                     m_chatroom_name, who, index);
            // Tell any others that this person has signed off
            send( who, " has signed off.");
		    // Now take name off list so that the slot is empty for next signon
            CORBA::string_free(chatters[index]);
			chatters[index] = 0;
            callbacks[index] = ChatClient::Listener::_nil();
    	}
	}
    else
        throw ChatRoom::Moderator::IdNotKnown();

    // now check to see if we should shut down due to lack of interest
    for (int i=0; i<CHATTER_LIMIT; i++ ) {
        if (chatters[i] != 0) 
            return; // found a chatter, so keep going
    };
    // didn't find any chatters, deactivate the ChatRoom::Moderator
	TP::userlog("Chatroom '%s': No one still active, ask to shut down.", 
                m_chatroom_name);
    TP::deactivateEnable();
}


/*
 *
 *  FUNCTION NAME: 	Moderator_i::activate_object
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      initialize lists of chatter ids and callbacks, each to null,
 *      initialize the chatroom name for purpose of logging
 */
void Moderator_i::activate_object( const char* stroid ) 
{
    for (int i=0; i<CHATTER_LIMIT; i++ ) {
        chatters[i] = 0; // no chatter here 
        callbacks[i] = ChatClient::Listener::_nil(); // nor callback
    };
	m_chatroom_name = CORBA::string_dup(stroid);
    TP::userlog("Chatroom '%s' activated.", m_chatroom_name);
}

/*
 *
 *  FUNCTION NAME: 	Moderator_i::deactivate_object
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      TP Framework callback.
 *      Reset state to null--delete all character strings 
 *
 */
void Moderator_i::deactivate_object( const char*      stroid,
                        TobjS::DeactivateReasonValue reason)
{
    for (int i=0; i<CHATTER_LIMIT; i++ ) {
        if (chatters[i]!=0) {
            CORBA::string_free(chatters[i]);
		    chatters[i] = 0;
        }
    }
	TP::userlog("Chatroom '%s' deactivated.", m_chatroom_name);
}

/*
 *
 *  FUNCTION NAME: 	Moderator_i::find
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Internal convenience routine.
 *      Find a chatter on the list, return index in chatters array.
 *      If not on list, return CHATTER_LIMIT.
 *      
 *
 */
int Moderator_i::find( const char* handle ) {
    int i;
    for (i = 0; i< CHATTER_LIMIT; i++) {
        if (chatters[i] != 0 && !strcmp(chatters[i], handle) )
            break;
    }
    return i;    
};

/*
 *
 *  FUNCTION NAME: 	ModeratorFactory::get_moderator
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      This is a factory for a chat room moderator.
 *      The parameter is the chat room desired. Return a reference
 *          to a Moderator object with the chat rooom name as the ObjectId
 *
 */
ChatRoom::Moderator_ptr ModeratorFactory_i::get_moderator( const char* chatroom_name ) {
    
    ChatRoom::Moderator_var moderator_ref = ChatRoom::Moderator::_nil();
    try {
        // Create an object reference for a Moderator using the name
        // Do not use a try block since the object will not be
        //   created if an exception is thrown.
        CORBA::Object_var obj = TP::create_object_reference(
            ChatRoom::_tc_Moderator->id(),   // Interf Repos Id
            chatroom_name,                   // ObjectId 
            CORBA::NVList::_nil()            // No special needs
            );
        moderator_ref = ChatRoom::Moderator::_narrow( obj );
    }
    catch (...) {
        TP::userlog("ERROR: Couldn't create object ref for Moderator");
    }

	return ChatRoom::Moderator::_duplicate( moderator_ref );
};

