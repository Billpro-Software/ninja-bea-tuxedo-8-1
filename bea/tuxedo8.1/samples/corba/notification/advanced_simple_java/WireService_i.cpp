//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// WireService_i.cpp
//
// Implementations of the WireService & WireServiceFactory idl
// interfaces for the advanced simple events c++ sample
//
// The WireServant_i class implements the WireService idl interface.
// This interface has three methods : one to report a news story,
// one to shutdown all subscribers and one to cancel all subscribers.
// These methods are called by the Reporter client program.  This
// servant implements these methods by posting events.  Subscribers,
// in turn, receive these events and perform the appropriate action.
//
// The WireServiceFactory_i servant class generates WireService
// object references.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <TP.h>
#include "WireService_i.h"

// report a news story
void WireService_i::report_news(const char* category, const char* story)
{
  // create an event
  CosNotification::StructuredEvent notification;

  // set the domain to "News"
  notification.header.fixed_header.event_type.domain_name =
    CORBA::string_dup("News");

  // set the type to the news category
  notification.header.fixed_header.event_type.type_name =
    CORBA::string_dup(category);

  // add one field, which will contain the story, to the
  // event's filterable data. set the field's name to
  // "Story" and value to a string containing the story
  notification.filterable_data.length(1);
  notification.filterable_data[0].name = CORBA::string_dup("Story");
  notification.filterable_data[0].value <<= story;

  // post the event
  m_channel->push_structured_event(notification);
}

// shutdown all subscribers (such that they can be restarted)
void WireService_i::shutdown_subscribers()
{
  // create an event
  CosNotification::StructuredEvent notification;

  // set the domain to "NewsAdmin"
  notification.header.fixed_header.event_type.domain_name =
    CORBA::string_dup("NewsAdmin");

  // set the type to "Shutdown"
  notification.header.fixed_header.event_type.type_name =
    CORBA::string_dup("Shutdown");

  // post the event
  m_channel->push_structured_event(notification);
}

// shutdown and cancel all subscribers (such that they cannot be restarted)
void WireService_i::cancel_subscribers()
{
  // create an event
  CosNotification::StructuredEvent notification;

  // set the domain to "NewsAdmin"
  notification.header.fixed_header.event_type.domain_name =
    CORBA::string_dup("NewsAdmin");

  // set the type to "Cancel"
  notification.header.fixed_header.event_type.type_name =
    CORBA::string_dup("Cancel");

  // post the event
  m_channel->push_structured_event(notification);
}

// find the wire service
News::WireService_ptr WireServiceFactory_i::find()
{
  // create a wire service object reference

  // note : for simplicity, this sample uses a fixed object id
  // ("WireService") for the wire service object.  This means that
  // there is only one wire service object that is shared by all
  // reporters.  If this example were scaled to have many reporters,
  // then they would contend for this one wire service object.  This
  // bottleneck can be corrected by using a different object id each
  // time this factory method is called.  See the production version
  // of the university sample application for an example of this.

  CORBA::Object_var wire_service_oref =
    TP::create_object_reference(
      News::_tc_WireService->id(), // interface id
      "WireService",               // object id
      CORBA::NVList::_nil()        // factory based routing criteria
    );

  return News::WireService::_narrow(wire_service_oref.in());
}
