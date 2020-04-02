/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/* File: Moderator_i.h
 * ---------------------------------------------------------------------
 *
 * This module contains the definition of the implementation class
 *
 *    Moderator_i
 *
 */
#ifndef _Moderator_i_h
#define _Moderator_i_h

#include "ChatRoom_s.h"

const int CHATTER_LIMIT = 5;           // the most chatters allowed

class Moderator_i : public POA_ChatRoom::Moderator {
    public:
        // First the IDL functions we have to implement
        void signon ( const char*           who,
                      ChatClient::Listener_ptr    callback_ref); 

        void send ( const char * who,
                    const char * input_line); 

        void signoff ( const char * who); 

        // Now the Framework functions
        virtual void activate_object  ( const char* stroid );
		
		virtual void deactivate_object( const char* stroid,
                                        TobjS::DeactivateReasonValue reason);
    private:
        // function to find name on list
        int find( const char * handle ); // return handle index in list

        // name of the chat room overseen by the moderator
        char* m_chatroom_name;

        // data for maintaining list
        CORBA::String            chatters[CHATTER_LIMIT];  // chatter[n] id
        ChatClient::Listener_var callbacks[CHATTER_LIMIT]; // chatter[n] callback ref
};

class ModeratorFactory_i : public POA_ChatRoom::ModeratorFactory {
    public:
        ChatRoom::Moderator_ptr get_moderator ( const char* chatroom_name ); 
};
#endif
