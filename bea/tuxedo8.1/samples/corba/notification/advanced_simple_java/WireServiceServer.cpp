//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// WireServiceServer.cpp
//
// The Server class for the advanced simple events c++ sample's
// WireService server.
//
// This server provides the interface for the Reporter clients
// (see News.idl).  It allows reporters to post new articles,
// shutdown the subscribers and cancel the subscribers.  The wire
// service accomplishes these tasks by posting events which the
// subscribers receive.
// 
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <Server.h>
#include <TP.h>
#include "WireService_i.h"
#include <server_ex.h>

static CORBA::Object_var
  s_factory_oref;           // the wire service factory's object reference

static Tobj_SimpleEvents::Channel_var
  s_channel;                // the simple events' channel

static int
  s_registered_factory = 0; // did we register our factory?

static int
  s_opened_xa_rm       = 0; // did we open as an xa resource manager?

// method to cleanup whatever we've intialized
static void cleanup()
{
  s_channel = Tobj_SimpleEvents::Channel::_nil();

  // if we managed to register the factory, then unregister it
  if (s_registered_factory) {
    try {
      TP::unregister_factory(
        s_factory_oref.in(),
        News::_tc_WireServiceFactory->id()
      );
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;
    s_registered_factory = 0;
  }

  // make sure the factory oref is nil since it's a static "_var"
  // that will be destructed when the process exits
  s_factory_oref = CORBA::Object::_nil();

  // if we managed to open as an xa resource manager, then close it
  if (s_opened_xa_rm) {
    try {
     TP::close_xa_rm();
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION; 
    s_opened_xa_rm = 0;
  }
}

CORBA::Boolean Server::initialize(int argc, char* argv[])
{
  try {

    // open as an xa resource manager
    TP::open_xa_rm();
    s_opened_xa_rm = 1;

    // create an object reference for the WireService server's
    // factory object
    s_factory_oref =
      TP::create_object_reference(
        News::_tc_WireServiceFactory->id(), // interface id
        "WireServiceFactory",               // object id
        CORBA::NVList::_nil()               // factory based routing criteria
      );

    // register the WireService factory with the factory finder
    TP::register_factory(
      s_factory_oref.in(),
      News::_tc_WireServiceFactory->id()
    );
    s_registered_factory = 1;

    // get the simple events' channel factory
    CORBA::Object_var channel_factory_oref =
      TP::bootstrap()->resolve_initial_references(
        "Tobj_SimpleEventsService"
      );

    Tobj_SimpleEvents::ChannelFactory_var channel_factory =
      Tobj_SimpleEvents::ChannelFactory::_narrow(
        channel_factory_oref.in()
      );

    // get the simple events' channel from the channel factory
    s_channel =
      channel_factory->find_channel(
        Tobj_SimpleEvents::DEFAULT_CHANNEL
      );

    return CORBA_TRUE;
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;

  cleanup(); // if anything went wrong, undo whatever we initialized
  return CORBA_FALSE;
}

void Server::release()
{
  // undo whatever we initialized
  cleanup();
}

Tobj_Servant Server::create_servant(const char* intf)
{
  if (!strcmp(intf, News::_tc_WireService->id())) {
    // create a wire service servant - hand it the channel so that
    // it can post events
    return new WireService_i(s_channel.in());
  }
  if (!strcmp(intf, News::_tc_WireServiceFactory->id())) {
    // create a wire service factory servant
    return new WireServiceFactory_i();
  }
  return 0; // should never get here
}
