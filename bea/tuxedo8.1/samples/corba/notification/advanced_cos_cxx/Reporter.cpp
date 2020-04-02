//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// Reporter.cpp
//
// Reporter client program for the advanced cos notification c++
// sample
//
// This client allows the user to choose among 4 options:
// reporting a news story, telling the subscribers to shutdown (such
// that the subscribers can be restarted), telling the subscribers to
// shutdown and cancel their subscriptions, and exiting this program.
//
// Rather than post events itself, this program invokes methods on the
// WireService server.  The WireService server, in turn, posts events.
// The subscribers (who subscribed to these events) then receive
// the events and do the appropriate action.
// 
// BEA Systems Inc. sample code
//

#ifdef WIN32
#include <strstrea.h>
#else
#include <strstream.h>
#endif
#include <iostream.h>
#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#include "News_c.h"
#include <client_ex.h>

#if defined(__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT >= 5
using std::ws;
#endif

// method to report a news article
static void
report_news(
  News::WireService_ptr wire_service
)
{
  // prompt for the news category
  cout << "Category?" << flush;
  char category[256];
  cin >> ws;
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
  story_os.rdbuf()->freeze(0);

  // invoke a method on the wire service to report this news story
  wire_service->report_news(category, story);
}

int main(int argc, char* argv[])
{
  try {

    // initialize the orb and bootstrap
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "");

    Tobj_Bootstrap bootstrap(orb.in(), "");

    CORBA::Object_var factory_finder_oref =
      bootstrap.resolve_initial_references("FactoryFinder");

    // get the factory finder
    Tobj::FactoryFinder_var factory_finder =
      Tobj::FactoryFinder::_narrow(factory_finder_oref.in());

    // use the factory finder to find the wire service factory
    CORBA::Object_var wire_service_factory_oref =
        factory_finder->find_one_factory_by_id(News::_tc_WireServiceFactory->id());

    News::WireServiceFactory_var wire_service_factory =
      News::WireServiceFactory::_narrow(wire_service_factory_oref.in());

    // use the wire service factory to find the wire service
    News::WireService_var wire_service =
      wire_service_factory->find();

    // command line driven user interface
    int done = 0;
    while (!done) {

      cout << "------------------------------------------------------------" << endl;
      cout << "(r) Report news"          << endl;
      cout << "(s) Shutdown subscribers" << endl;
      cout << "(c) Cancel subscribers"   << endl;
      cout << "(e) Exit"                 << endl;
      cout << "Option?" << flush;

      char option;
      cin >> option;

      switch (option) {
        case 'r': report_news(wire_service.in());       break;

        // shutdown all subscribers (such that they can restart)
        // delegate to the wire service
        case 's': wire_service->shutdown_subscribers(); break;

        // cancel all subscribers (that is shutdown and cancel
        // the subscription)
        // delegate to the wire service
        case 'c': wire_service->cancel_subscribers();   break;

        case 'e': done = 1;                             break;
      }
    }
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;
  return 0;
}
