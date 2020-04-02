//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// log.cpp
//
// C++ log utility routines for the university sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <log.h>
#include <string.h> // for "strlen"

//--------------------------------------------------------------

void _private_log(
    const char*   file,
    unsigned long line,
    char*         txt
)
{
    unsigned long len = strlen(txt)+1;
    unsigned long start = 0;
    for (unsigned long i = 0; i < len; i++) {
        if (txt[i] == '\n') {
            txt[i] = '\0';
            _private_log_line(file, line, &(txt[start]));
            start = i+1;
        }
    }
    if (start < len) {
        _private_log_line(file, line, &(txt[start]));
    } 
}

//--------------------------------------------------------------

void _private_trace(
    const char*   file,
    unsigned long line,
    char*         txt
)
{
    unsigned long len = strlen(txt)+1;
    unsigned long start = 0;
    for (unsigned long i = 0; i < len; i++) {
        if (txt[i] == '\n') {
            txt[i] = '\0';
            _private_trace_line(file, line, &(txt[start]));
            start = i+1;
        }
    }
    if (start < len) {
        _private_trace_line(file, line, &(txt[start]));
    } 
}

//--------------------------------------------------------------

_private_TraceBlock::_private_TraceBlock(
    const char*   file,
    unsigned long line,
    const char*   txt
) :
    m_file(file),
    m_line(line),
    m_txt(txt)
{
    ostrstream os;
    os << "entering " << m_txt << ends;
    char* str = os.str();
    os.rdbuf()->freeze(0);
    _private_trace(m_file, m_line, str);
}

_private_TraceBlock::~_private_TraceBlock()
{
    ostrstream os;
    os << "exiting " << m_txt << ends;
    char* str = os.str();
    os.rdbuf()->freeze(0);
    _private_trace(m_file, m_line, str);
}

//--------------------------------------------------------------
