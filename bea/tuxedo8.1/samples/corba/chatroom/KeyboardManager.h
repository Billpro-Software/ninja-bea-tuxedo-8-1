/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
#ifndef _KeyboardManager_h
#define _KeyboardManager_h


// File: KeyboardManager.h
//
// Part of the ChatClient
// Defines the KeyboardManager class to get input from the keyboard
//  without blocking

#ifndef WIN32
#include <termios.h>
#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif
#endif


const short MAX_CHARS_ON_LINE = 80;
const short MAX_HANDLE_LENGTH = 20;

// This is a very simple User Interface class for chatters using
//  a console keyboard. It takes care of reading from the keyboard
//  and outputting messages from the other chatters.
class KeyboardManager {

private:
    char m_keyboard[100];
    int m_num_keys;
    short m_max_to_read;
    short m_line_ready;
    char  m_prompt_string[MAX_HANDLE_LENGTH];
#ifndef WIN32
    struct termios m_termstruct;
    tcflag_t m_local_modes;
    cc_t  m_saved_cc[NCCS];

    int set_term();
    int unset_term();

#endif


public:
    KeyboardManager(short max_chars, char * prompt);
	~KeyboardManager();

    short input_available();
    void get_line(char* buffer);
    void interrupt_output(char* from_who, char* buffer);
};

#endif
