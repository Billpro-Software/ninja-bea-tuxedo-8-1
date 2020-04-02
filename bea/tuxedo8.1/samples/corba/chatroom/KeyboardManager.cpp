//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
// File: KeyboardManager.cpp
//
// Part of the ChatClient
// Implements the KeyboardManager class to get input from the keyboard
//  without blocking

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
#include "conio.h"
#else
#include <stdio.h>
#endif
#include "KeyboardManager.h"

KeyboardManager::KeyboardManager(short max_chars, char * prompt) // constructor
{ 
    m_num_keys=0;                   // number of keystrokes read so far
    m_line_ready=0;                 // a carriage return has finished
    								//  the line
    m_max_to_read = max_chars;      // maximimum number of characters
    								//  to read
    strcpy(m_prompt_string, prompt); //the prompt to output to start
        								//  a new line
#ifndef WIN32
	if (set_term()) {
		exit(0);
	}
#endif
	
    // output prompt
    cout << m_prompt_string << "> " << flush;
};


// Desturctor
KeyboardManager::~KeyboardManager() {

#ifndef WIN32
	(void)unset_term();
#endif

}
#ifndef WIN32
// Sets the terminal if unix to non-blocking io
int KeyboardManager::set_term() {

	// For unix we need to set mess with the termio settings in
	// order to get non-blocking read behavior
	int errret = 0;
  
	// get current stdin settings
  	if (errret = tcgetattr( STDIN_FILENO, &m_termstruct)) {
    	cout << "Error getting terminal attributes" << endl << flush;
		return (errret);
  	}
	// Save away the local modes so we can restore them when
	//  we're done
  	m_local_modes = m_termstruct.c_lflag;

	// no canonical input
  	m_termstruct.c_lflag = m_termstruct.c_lflag & ~ICANON;

	// Save away the control chars so we can restore them when
	//  we're done
	for (int i=0; i < NCCS; i++) {
		m_saved_cc[i] = m_termstruct.c_cc[i];
	}
  	// return is immediate with either the number of characters
    //  requested or the number of characters currently available
    //  without waiting for more characters to be input.
  	m_termstruct.c_cc[VMIN] = 0;
  	m_termstruct.c_cc[VTIME] = 0;

    // Set the new values on stdin
  	if (errret = tcsetattr( STDIN_FILENO, TCSANOW, &m_termstruct)) {
    	perror(" tcsetattr");
    	cout << "Error setting terminal attributes" << endl << flush;
		return (errret);
  	}


	return (0);
}
#endif

#ifndef WIN32
// Resets the terminal if unix to its original io mode
int KeyboardManager::unset_term() {
	// For unix we need to reset the termio settings in
	// order to get the original behavior
	int errret = 0;
  
	// Reset the local modes
  	m_termstruct.c_lflag = m_local_modes;

	// Restore the control chars
	for (int i=0; i < NCCS; i++) {
		 m_termstruct.c_cc[i] = m_saved_cc[i];
	}

    // Set the new values on stdin
  	if (errret = tcsetattr( STDIN_FILENO, TCSANOW, &m_termstruct)) {
    	perror(" tcsetattr");
    	cout << "Error setting terminal attributes" << endl << flush;
		return (errret);
  	}

	return (0);
}
#endif

// Check to see if a line of input is available, return 1 if
//  so, 0 if not. In so doing, we might read a single character
//  at a time, saving it, so that we can return immediately.
//  Note: this means no editing.
short KeyboardManager::input_available() {

    // if the line was finished but not yet retrieved, tell
    //  caller again
    if (m_line_ready!=0) return 1;

    // if there's a keyboard hit, that means we can read a
    //  character without blocking
#ifdef WIN32
    if (_kbhit()) {
        m_keyboard[m_num_keys]=_getche();
        // if the character we just read is the last, set string
        //  end and return the answer
        if ((m_num_keys+1) == m_max_to_read ||
        		m_keyboard[m_num_keys]=='\r') {
            m_keyboard[m_num_keys]='\0';
            m_line_ready=1;
        }
        else {
            m_num_keys++;
        };
    };
#else
	// do a non-blocking getchar
	char current_char = getchar();
	// Different OSs return different things if there is
	//  nothing to retrieve
	if (current_char == 0 || current_char == -1 || current_char == 255) {
		return m_line_ready;
	} else {
		// get the next character
		m_keyboard[m_num_keys++] = current_char;

        // if the character we just read is the last, set string
        //  end and return the answer
        if ((m_num_keys+1) == m_max_to_read ||
        		current_char=='\n') {
            m_keyboard[m_num_keys-1]='\0';
            m_line_ready=1;
        }
    };
#endif
    return m_line_ready;
};


// Return the input line that this user type. This function should
//  be called only after it is determined that there is a line, by
//  a positive return from line_available.
void KeyboardManager::get_line(char* buffer){
    strcpy(buffer, m_keyboard);
    m_line_ready =0;            // now that the line is retrieved,
    							//  start over
    m_num_keys=0;

    // output prompt for the next line
#ifdef WIN32
    cout << endl << m_prompt_string << "> " << flush;
#else
    cout << m_prompt_string << "> " << flush;
#endif
};
    


// Output a message from another chatter.
// Erase the current line of input, output the message, then rewrite
// current line
void KeyboardManager::interrupt_output(char* from_who, char* buffer){
    cout << '\r'; // go to start of line

    // erase current line, consisting of prompt and current input
    for (int i=0; i < (int)strlen(m_prompt_string) + m_num_keys + 2; i++) 
        cout << " ";

    // output the message from the other chatter
    cout << "\r  <" << from_who << "> " << buffer << endl;

    // now output what was on the line previously
    cout << m_prompt_string << "> " << flush;
    for (int j=0; j<m_num_keys; j++) 
        cout << m_keyboard[j];
    cout << flush;
};


