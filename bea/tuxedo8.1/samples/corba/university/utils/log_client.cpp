//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// log_client.cpp
//
// C++ log utility routines for the university sample application client 
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <log.h>

//--------------------------------------------------------------------

void _private_log_line(
    const char*   file,
    unsigned long line,
    const char*   txt
)
{
   cerr << "LOG : " << file << "," << line << " : " << txt << endl;
}

//--------------------------------------------------------------------

void _private_trace_line(
    const char*   file,
    unsigned long line,
    const char*   txt
)
{
    cout << "TRACE : " << file << "," << line << " : " << txt << endl;
}
