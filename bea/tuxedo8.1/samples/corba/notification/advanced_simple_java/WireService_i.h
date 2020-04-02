//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// WireService_i.h
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

#ifndef _wire_service_i_h
#define _wire_service_i_h

#include "News_s.h"
#include "Tobj_SimpleEvents_c.h"

// the wire service servant class
class WireService_i : public POA_News::WireService
{
  public:

    // constructor
    WireService_i(Tobj_SimpleEvents::Channel_ptr channel) :
      m_channel(channel)
    {
    }

    // report a news story
    virtual void report_news(const char* category, const char* story);

    // shutdown all subscribers (such that they can be restarted)
    virtual void shutdown_subscribers();

    // shutdown and cancel all subscribers (such that they cannot be restarted)
    virtual void cancel_subscribers();

  private:
    Tobj_SimpleEvents::Channel_ptr m_channel;
};

// the factory servant class
class WireServiceFactory_i : public POA_News::WireServiceFactory
{
  public:
    // find the wire service
    virtual News::WireService_ptr find();
};

#endif
