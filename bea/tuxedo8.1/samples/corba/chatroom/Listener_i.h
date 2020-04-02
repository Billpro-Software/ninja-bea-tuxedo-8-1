/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/* File: Listener_i.h
 * ---------------------------------------------------------------------
 *
 * This module contains the definition of the implementation class
 *
 *    Listener_i
 *
 */
#ifndef _Listener_i_h
#define _Listener_i_h


#include "ChatClient_s.h"

class Listener_i : public POA_ChatClient::Listener {
    public:

        Listener_i ();
        virtual ~Listener_i();

        void post (
            const char * from,
            const char * output_line); 

        // the following is not part of the IDL, it's local to the client
        int get_other_chatter( char* from, char* output_line);
    
    private:
        char m_from[20];
        char m_output_line[80];
};
#endif
