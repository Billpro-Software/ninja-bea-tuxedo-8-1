//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// NewsConsumer_i.h
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

#ifndef _news_consumer_i_h
#define _news_consumer_i_h

#include "CosNotifyComm_s.h"

// the servant class to receive news events.
// it must implement the CosNotifyComm::StructuredPushConsumer idl interface

class NewsConsumer_i : public POA_CosNotifyComm::StructuredPushConsumer
{
  public:

    // this method will be called when a news event occurs
    virtual void
    push_structured_event(
      const CosNotification::StructuredEvent& notification
    ); 

    // OMG's CosNotifyComm::StructuredPushConsumer idl
    // interface defines/ the methods "offer_change" and
    // "disconnect_structured_push_consumer".  Since Tuxedo's
    // notification service never invokes these methods, just
    // have them throw a CORBA::NO_IMPLEMENT exception

    virtual void
    offer_change(
      const CosNotification::EventTypeSeq& added,
      const CosNotification::EventTypeSeq& removed
    )
    {
      throw CORBA::NO_IMPLEMENT();
    }

    virtual void disconnect_structured_push_consumer()
    {
      throw CORBA::NO_IMPLEMENT();
    }
};

#endif
