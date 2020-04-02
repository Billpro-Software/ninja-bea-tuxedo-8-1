//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// Subscriber.cpp
//
// Subscriber joint client/server program for the introductory
// simple events c++ sample.
//
// This program creates a transient simple events subscription to
// receive news events.  After the first event is received, this
// program unsubscribes then shuts itself down.
//
// This program acts as a client when it subscribes and unsubscribes
// for events.  It acts as a server when it receives events.  This
// program receives event by implementing a callback object which
// is invoked by the notification service when an event needs to
// be delivered.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <Tobj_Bootstrap.h>      // bootstrap api
#include <beawrapper.h>          // callback api
#include "Tobj_SimpleEvents_c.h" // simple events api
#include "NewsConsumer_i.h"      // servant that receives news events     
#include <client_ex.h>           // exception handling utils

#if defined(__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT >= 5
using std::ws;
#endif

//--------------------------------------------------------------------

// cleanup notes:
//
// While the main creates the notification subscription, under normal
// conditions the callback object must cancel the subscription.
// Here's why:
//
// The main creates a notification subscription (and corresponding
// servant) then calls orb->run to wait for the notification service
// to "callback" to the servant to deliver an event.
//
// The notification service invokes a method on the "callback"
// servant to deliver the event.  The servant, in this method,
// prints out the event, calls orb->shutdown then returns.  After
// this callback method returns, orb->run returns and control is
// handed back to the main so that it can exit gracefully.
//
// Before main exits, it must cancel the subscription by invoking
// the "unsubscribe" operation on the notification service.  However,
// once orb->shutdown has been called, CORBA invokes are illegal.
// Therefore, the subscription must be cancelled in the callback
// servant's method BEFORE the method calls orb->shutdown.
//
// However, if the main successfully subscribes then an error
// occurs, the event might not be delivered to the callback
// servant.  In this case, the main must be responsible for
// cancelling the subscription.
//
// So, if no error occurs, when the callback servant is called,
// it must cancel the subscription before it calls orb->shutdown
// to stop the ORB.  However, if an error does occur, the main
// must cancel the subscription before it exits.
//
// To accomplish the above, an "unsubscribe" routine, with
// corresponding global variables, is provided.  After the main
// subscribes, it records the info necessary to unsubscribe in
// these global variables.  The "unsubscribe" routine looks
// at these global variables.  If "unsubscribe" finds that there
// is a subscription, then "unsubscribe" cancels the subscription
// and clears out the global variables.  If "unsubscribe" finds
// that there isn't a subscription, then it returns gracefully.
// "unsubscribe" is called by both the main and the servant so
// that regardless of how the subscriber exits (normally or
// because of an error), the subscription is cancelled.
//
// To keep the shutdown details out of the servant method, a
// "shutdown" routine is also provided.  This routine calls
// "unsubscribe" then orb->shutdown.  The callback servant's
// callback method first prints out the event, calls "shutdown"
// then returns.
//
// A note on global variables: instead of having global "vars"
// whose destructors are run after "main" exits, use "vars" on
// the main's stack (thus the destructors are run before "main"
// exits) then have global "ptrs" which refer to the references
// the main's "vars" manage.

//--------------------------------------------------------------------

// "unsubscribe" routine - it can safely be called multiple times

static int                               s_subscribed = 0;  // are we subscribed?
static Tobj_SimpleEvents::Channel_ptr    s_channel;         // the channel
static Tobj_SimpleEvents::SubscriptionID s_subscription_id; // our subscription id

static void unsubscribe()
{
  if (!s_subscribed) return;
  try {
    s_channel->unsubscribe(s_subscription_id);
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;
  s_subscribed = 0;
}

//--------------------------------------------------------------------

// "shutdown" routine used by the callback servant.
// note : no header file is provided for this declaration.

static CORBA::ORB_ptr s_orb;

extern void shutdown()
{
  unsubscribe();
  s_orb->shutdown(0);
}

//--------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try {

    // prompt for user name & category
    char subscription_name[256];
    cout << "Name?" << flush;
    cin >> ws; // skip over white space
    cin.getline(subscription_name, sizeof(subscription_name));

    char category[256];
    cout << "News category (or all)?" << flush;
    cin >> ws; // skip over white space
    cin.getline(category, sizeof(category));

    // initialize the orb & bootstrap
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");
    s_orb = orb.in();

    Tobj_Bootstrap bootstrap(orb.in(), "");

    // get the Simple Event channel factory object reference
    CORBA::Object_var channel_factory_oref =
      bootstrap.resolve_initial_references(
        "Tobj_SimpleEventsService"
      );

    Tobj_SimpleEvents::ChannelFactory_var channel_factory =
        Tobj_SimpleEvents::ChannelFactory::_narrow(
          channel_factory_oref.in()
        );

    // use the channel factory to get the default channel
    Tobj_SimpleEvents::Channel_var channel =
        channel_factory->find_channel(
          Tobj_SimpleEvents::DEFAULT_CHANNEL
        );
    s_channel = channel.in();

    // to receive events, this client must also be a server -
    // that is, this client must implement a CORBA object that
    // will be invoked (called back) when an event occurs

    // create a callback wrapper object since this client needs to
    // support callbacks
    BEAWrapper::Callbacks wrapper(orb.in());

    // instantiate the servant that receives the events
    NewsConsumer_i* news_consumer_impl = new NewsConsumer_i;

    // use a try block so that we can delete servant regardless
    // of whether or not an exception occurs.
    try {

      // create a transient object reference to the callback servant
      CORBA::Object_var news_consumer_oref =
          wrapper.start_transient(
            news_consumer_impl,
            CosNotifyComm::_tc_StructuredPushConsumer->id()
          );

      CosNotifyComm::StructuredPushConsumer_var
        news_consumer =
          CosNotifyComm::StructuredPushConsumer::_narrow(
            news_consumer_oref.in()
          );

      // set the quality of service to TRANSIENT
      CosNotification::QoSProperties qos;
      qos.length(1);
      qos[0].name =
        CORBA::string_dup(Tobj_SimpleEvents::SUBSCRIPTION_TYPE);
      qos[0].value <<=
        Tobj_SimpleEvents::TRANSIENT_SUBSCRIPTION;

      // set the type to the news category (or a wild card for all categories)
      const char* type = (!strcmp(category, "all")) ? ".*" : category;

      // create the subscription. set the domain to "News" and
      // don't use a data filter.
      s_subscription_id =
        channel->subscribe(
          subscription_name,
          "News", // domain
          type,   // = news category
          "",     // data filter
          qos,
          news_consumer.in()
        );
      s_subscribed = 1;

      // use a try block so that we can unsubscribe regardless
      // of whether or not an exception occurs.
      try {

        // process events until we're shut down

        // in this sample, after the first news item is received,
        // the callback servant calls orb->shutdown (indirectly)

        // the servant receives the news item because someone ran
        // the reporter program and reported a news story that
        // this servant subscribed to

        cout << "Ready" << endl;
        orb->run();
      }
      CATCH_REPORT_AND_SWALLOW_EXCEPTION;
      // unsubscribe regardless of whether or not an error occurred
      unsubscribe();
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;
    // delete the servant regardless of whether or not an error occurred
    delete news_consumer_impl;
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;
  return 0;
}

//--------------------------------------------------------------------
