//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// log_server.cpp
//
// C++ log utility routines for the university sample application server 
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <log.h>
#include <TP.h>

void _private_log_line(
    const char*   file,
    unsigned long line,
    const char*   txt
)
{
    TP::userlog("LOG : %s,%ld : %s", file, line, txt);
}

void _private_trace_line(
    const char*   file,
    unsigned long line,
    const char*   txt
)
{
    TP::userlog("TRACE : %s,%ld : %s", file, line, txt);
}
