//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// log.h
//
// C++ log utility header for the university sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _LOG_H_
#define _LOG_H_

//--------------------------------------------------------------

#include <CORBA.h>

#ifdef WIN32
#include <strstrea.h>
#else
#include <strstream.h>
#endif

//--------------------------------------------------------------

extern void
_private_log_line(
    const char*   file,
    unsigned long line,
    const char*   txt
);

extern void
_private_log(
    const char*   file,
    unsigned long line,
    char*         txt
);

#define LOG(ostream_fragment)			\
    {						\
        ostrstream os;				\
        os << ostream_fragment << ends;		\
        char* str = os.str();			\
        os.rdbuf()->freeze(0);			\
        _private_log(__FILE__,__LINE__,str);	\
    }

//--------------------------------------------------------------

extern void
_private_trace_line(
    const char*   file,
    unsigned long line,
    const char*   txt
);

extern void
_private_trace(
    const char*   file,
    unsigned long line,
    char*         txt
);

#ifndef NO_TRACING
#define TRACE(ostream_fragment)				\
    {							\
        ostrstream os;					\
        os << ostream_fragment << ends;			\
        char* str = os.str();				\
        os.rdbuf()->freeze(0);				\
        _private_trace(__FILE__, __LINE__, str);	\
    }
#else
#define TRACE(ostream_fragment)
#endif

//--------------------------------------------------------------

class _private_TraceBlock
{
public:
    _private_TraceBlock(
        const char*   file,
        unsigned long line,
        const char*   txt
    );
    ~_private_TraceBlock();
private:
    const char*   m_file;
    unsigned long m_line;
    const char*   m_txt;
};

#ifndef NO_TRACING
#define TRACE_METHOD(method_name)	\
    _private_TraceBlock			\
	_##__LINE__##_tracer(__FILE__,__LINE__,method_name)
#else
#define TRACE_METHOD(method_name)
#endif

//--------------------------------------------------------------

inline ostream& operator<<(ostream& os, CORBA::Exception& e)
{
    return os << e.get_id();
}

//--------------------------------------------------------------

#endif // _LOG_H_

