//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
// File: Listener_i.cpp
//
// Callback object to deal with messages from other people in the chat room.
// This object is invoked by the chat room moderator when somebody else
//   in the chat room has entered a message. 


#include <iostream.h>
#include "Listener_i.h"

/*
 *
 *  FUNCTION NAME:       Listener_i
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *     Constructor for Implementation: Listener_i
 *
 */

Listener_i::Listener_i ()
{
    m_from[0] = '\0';
    m_output_line[0] = '\0';
}

/*
 *
 *  FUNCTION NAME:       ~Listener_i
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *     Destructor for Implementation: Listener_i
 *
 */

Listener_i::~Listener_i ()
{
}

/*
 *
 *  FUNCTION NAME: 	Listener_i::post
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Receive a message from some other chatter.
 *      The first parameter is the handle of the source of the conversation
 *          so show it as the source. The second is the actual conversation line.
 *      We just save the information and the mainline program can get
 *          it later via the get_other_chatter function.
 *      If a second message comes in before the first is retrieved, it is
 *          lost. We do this for simplicity of the User Interface, not
 *          because it's a good idea.
 *
 */
void Listener_i::post (
    const char * from,
    const char * output_line)
{
    strcpy(m_from,        from);
    strcpy(m_output_line, output_line);
    return ;
}

// Routine to return anything that has come in via the callback
// Once something has returned, it is erased.
// Return 1 if there is something, 0 if none.
int Listener_i::get_other_chatter(
    char * from,
    char * output_line)
{
    if (m_output_line[0] != 0) {
        strcpy(from,        m_from);
        strcpy(output_line, m_output_line);
        m_output_line[0] = '\0';
        return 1;
    }
    else {
        return 0;
    };
}
