//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// Reporter.cpp
//
// Reporter client program for the introductory simple events c++ sample
//
// This program prompts the user to enter news articles, then
// uses the simple events interface to post events for these
// articles.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <Tobj_Bootstrap.h>       // bootstrap api
#include "Tobj_SimpleEvents_c.h"  // simple events api
#include <client_ex.h>            // exception handling utils
#ifdef WIN32
#include <strstrea.h>
#else
#include <strstream.h>
#endif

#if defined(__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT >= 5
using std::ws;
#endif

// method to report a news article
static void
report_news(
  Tobj_SimpleEvents::Channel_ptr channel
)
{
  // prompt for the news category
  cout << "Category?" << flush;
  char category[256];
  cin >> ws; // skip over white space
  cin.getline(category, sizeof(category));

  // prompt for the news story
  cout << "Enter story (terminate with '.')" << endl;
  ostrstream story_os;
  int first = 1;
  while (1) {
    char line[256];
    cin.getline(line, sizeof(line));
    if (!strcmp(line, ".")) {
      break;
    }
    if (!first) {
      story_os << endl;
    } else {
      first = 0;
    }
    story_os << line;
  }
  story_os << ends;
  const char* story = story_os.str();
  // make story_os responsible for deleting the buffer when
  // story_os goes out of scope:
  story_os.rdbuf()->freeze(0);

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

  // Subscribers who subscribed to events whose domain is
  // "News" and whose type matches the news category will
  // receive this event

  channel->push_structured_event(notification);
}

int main(int argc, char* argv[])
{
  try {

    // initialize the orb and bootstrap
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");

    Tobj_Bootstrap bootstrap(orb.in(), "");

    // get the Simple Events channel factory object reference
    CORBA::Object_var channel_factory_oref =
      bootstrap.resolve_initial_references("Tobj_SimpleEventsService");

    Tobj_SimpleEvents::ChannelFactory_var channel_factory =
      Tobj_SimpleEvents::ChannelFactory::_narrow(channel_factory_oref.in());

    // use the channel factory to get the default channel
    Tobj_SimpleEvents::Channel_var channel =
      channel_factory->find_channel(Tobj_SimpleEvents::DEFAULT_CHANNEL);

    // command line driven user interface
    int done = 0;
    while (!done) {

      cout << "------------------------------------------------------------" << endl;
      cout << "(r) Report news" << endl;
      cout << "(e) Exit"        << endl;
      cout << "Option?" << flush;

      char option;
      cin >> option;

      switch (option) {
        case 'r': report_news(channel.in()); break; // do the real work here
        case 'e': done = 1;                  break;
      }
    }
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;
  return 0;
}
