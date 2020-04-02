//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// NewsConsumer_i.cpp
//
// Implementation of a callback servant which receives news events
// for the advanced cos notification c++ sample
//
// When this callback servant receives an event, it prints out the
// event.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include "NewsConsumer_i.h"
#include <iostream.h>

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
}
