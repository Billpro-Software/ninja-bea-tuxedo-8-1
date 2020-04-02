//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// ShutdownConsumer_i.cpp
//
// Implementation of a callback servant which receives shutdown and
// cancel events for the advanced cos notification c++ sample
//
// When this callback servant receives a shutdown or cancel event,
// it invokes a "shutdown" method (provided by the main).  This method
// causes the application to shut down.
//
// This servant keeps member data to store whether or not the
// application is just shutting down or if the news subscription
// should be cancelled.  When this servant receives a cancel event,
// it remembers that this news subscription should be cancelled.  This
// state is made available by the servant's "news_unsubscribe"
// method.
//
// After the "shutdown" routine is called, the main invokes the
// "news_unsubscribe" method on this servant to determine if it
// should just shut down or if it should also cancel the news
// subscription.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <iostream.h>
#include "ShutdownConsumer_i.h"

extern void shutdown(); // tell the "main" to shutdown this process

// Subscriber.cpp creates a simple events subscription to "NewsAdmin"
// events.  When a news admin event occurs (this happens when a user
// runs the Reporter and selects the shutdown or cancel option), this
// method will be invoked:

void
ShutdownConsumer_i::push_structured_event(
  const CosNotification::StructuredEvent& notification
)
{
  // for coding simplicity, assume that:
  //   notification.header.fixed_header.event_type.domain_name is "NewsAdmin"
  //   notification.header.fixed_header.event_type.type_name is either
  //   "Cancel" or "Shutdown"

  const char* type = notification.header.fixed_header.event_type.type_name.in();

  if (!strcmp(type, "Cancel")) {

    // we've received a cancel event.  

    cout << "------------------------------------------------------------" << endl;
    cout << "Shutting down and cancelling" << endl;

    // remember that the news subscription should be canceled
    m_news_unsubscribe = 1;

  } else if (!strcmp(type, "Shutdown")) {

    // we've received a shutdown event.  

    cout << "------------------------------------------------------------" << endl;
    cout << "Shutting down" << endl;

  } else {
    // shouldn't get here
  }

  // call a method (provided by the main), to terminate the application
  shutdown();
}
