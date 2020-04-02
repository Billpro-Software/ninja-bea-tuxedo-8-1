//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// NewsConsumer_i.cpp
//
// Implementation of a callback servant which receives news events
// for the introductory simple events c++ sample
//
// When this callback servant receives an event, it prints out the
// event then invokes a method (provided by the main) which shuts
// down the application.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include "NewsConsumer_i.h"
#include <iostream.h>

extern void shutdown(); // tell the "main" to shutdown this process

//--------------------------------------------------------------------

// Subscriber.cpp creates a simple events subscription to "News" events
// and has the events delivered to a NewsConsumer_i object.  When a
// news event occurs (this happens when a user runs the Reporter
// application and reports a news story), this method will be invoked:

void
NewsConsumer_i::push_structured_event(
  const CosNotification::StructuredEvent& notification
)
{
  // for coding simplicity, assume that:
  //   notification.header.fixed_header.event_type.domain_name is "News"
  //   notification.header.fixed_header.event_type.type_name is the news category
  //   notification.filterable_data.length() is 1
  //   notification.filterable_data[0].name  is "Story"
  //   notification.filterable_data[0].value contains the story (as a string)

  // extract the story from the first field in the event's filterable data
  char* story;
  notification.filterable_data[0].value >>= story;
  // for coding simplicity, assume "story" is not "null"

  // print out the event
  cout
    << "------------------------------------------------------------"
    << endl
    << "Category : "
    << notification.header.fixed_header.event_type.type_name.in()
    << endl
    << "Story    : "
    << story
    << endl;

  // we need a mechanism to shut down the Subscriber.
  // we can't easily wait for user input in C++ since we're not
  // multi-threaded.  so, for simplicity, shut down after receiving one event

  // call a method (provided by the main), to terminate the application
  shutdown();
}
