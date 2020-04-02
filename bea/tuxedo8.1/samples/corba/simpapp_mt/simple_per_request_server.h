//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simple_per_request_server.h
//
// User defined servant declarations for the simpapp_mt sample.
//
// This include file name and the class name must match the name 
// specified as a value to the -b parameter in the buildobjserver 
// command line.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _simple_per_request_server_h
#define _simple_per_request_server_h

#include <Server.h>

class simple_per_request_server : public ServerBase
{
    public:
        CORBA::Boolean initialize(int argc, char** argv);
        void release();
        Tobj_Servant create_servant(const char* interfaceName);
        Tobj_Servant create_servant_with_id(const char* interfaceName,
                                            const char* stroid);
        CORBA::Boolean thread_initialize(int argc, char** argv);
        void thread_release();
};

#endif
