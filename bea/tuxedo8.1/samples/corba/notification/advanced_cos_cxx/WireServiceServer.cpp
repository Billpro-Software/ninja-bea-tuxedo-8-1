//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// WireServiceServer.cpp
//
// The Server class for the advanced cos notification c++ sample's
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

static CosNotifyChannelAdmin::StructuredProxyPushConsumer_var
  s_proxy_push_consumer;    // the proxy used to post events

static int
  s_registered_factory = 0; // did we register our factory?

static int
  s_opened_xa_rm       = 0; // did we open as an xa resource manager?


// method to cleanup whatever we've intialized
static void cleanup()
{
  // if we've successfully created a proxy, then disconnect from it
  if (!CORBA::is_nil(s_proxy_push_consumer.in())) {
    try {
      s_proxy_push_consumer->disconnect_structured_push_consumer();
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;
    s_proxy_push_consumer =
      CosNotifyChannelAdmin::StructuredProxyPushConsumer::_nil();
  }

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

    // get the Cos Notification channel factory object reference
    CORBA::Object_var channel_factory_oref =
      TP::bootstrap()->resolve_initial_references(
        "NotificationService"
      );

    CosNotifyChannelAdmin::EventChannelFactory_var
      channel_factory =
        CosNotifyChannelAdmin::EventChannelFactory::_narrow(
          channel_factory_oref.in()
        );

    // use the channel factory to get the default channel
    CosNotifyChannelAdmin::EventChannel_var channel =
      channel_factory->get_event_channel(
        Tobj_Notification::DEFAULT_CHANNEL
      );

    // since we're a supplier (that is, we post events)
    // get the supplier admin object
    CosNotifyChannelAdmin::SupplierAdmin_var supplier_admin =
      channel->default_supplier_admin();

    // use the supplier admin to create a proxy.  events are posted
    // to the proxy (unlike the simple events interface where events
    // are posted to the channel).
    CosNotifyChannelAdmin::ProxyID proxy_id;
    CosNotifyChannelAdmin::ProxyConsumer_var generic_proxy_consumer =
      supplier_admin->obtain_notification_push_consumer(
        CosNotifyChannelAdmin::STRUCTURED_EVENT,
        proxy_id
      );

    s_proxy_push_consumer =
      CosNotifyChannelAdmin::StructuredProxyPushConsumer::_narrow(
        generic_proxy_consumer
      );

    // Connect to the proxy so that we can post events.
    s_proxy_push_consumer->connect_structured_push_supplier(
      CosNotifyComm::StructuredPushSupplier::_nil()
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
    // create a wire service servant - hand it the proxy so that
    // it can post events
    return new WireService_i(s_proxy_push_consumer.in());
  }
  if (!strcmp(intf, News::_tc_WireServiceFactory->id())) {
    // create a wire service factory servant
    return new WireServiceFactory_i();
  }
  return 0; // should never get here
}
