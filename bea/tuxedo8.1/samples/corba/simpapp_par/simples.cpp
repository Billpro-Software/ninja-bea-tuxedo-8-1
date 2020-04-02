//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simples.cpp
//
// C++ server program for the simpapp_par sample application
//
// Implements the Server::initialize/create_servant/release methods
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <string.h> // for "strcmp"
#include <Server.h>
#include <TP.h>
#include "simple_i.h"

#ifdef WIN32
#include <process.h>
#include <strstrea.h>
#else
#include <unistd.h>
#include <strstream.h>
#endif

static int   s_pid       = 0; // this process id

//--------------------------------------------------------------------
// Method to start up the server
//--------------------------------------------------------------------

CORBA::Boolean Server::initialize(int argc, char* argv[])
{
    s_pid       = getpid();     // get my process id

    // we've succeeded:
    return CORBA_TRUE;
}

//--------------------------------------------------------------------
// Method to shutdown the server
//--------------------------------------------------------------------

void Server::release()
{
}

//--------------------------------------------------------------------
// Method to create servants
//--------------------------------------------------------------------

Tobj_Servant Server::create_servant(const char* intf_repos_id)
{
    if (!strcmp(intf_repos_id, _tc_Simple->id())) {
        return new Simple_i();
    }

    return 0; // unknown interface
}

