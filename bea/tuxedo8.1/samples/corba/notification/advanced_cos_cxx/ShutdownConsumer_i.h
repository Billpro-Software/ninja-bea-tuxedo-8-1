//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// ShutdownConsumer_i.h
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

#ifndef _shutdown_consumer_i_h
#define _shutdown_consumer_i_h

#include "CosNotifyComm_s.h"

// the servant class to receive shutdown and cancel events.
// it must implement the CosNotifyComm::StructuredPushConsumer idl interface

class ShutdownConsumer_i : public POA_CosNotifyComm::StructuredPushConsumer
{
  public:

    // assume that the user will only shut the subscriber down
    // (instead of canceling the news subscription too)
    ShutdownConsumer_i() : m_news_unsubscribe(0) {}

    // this method will be called when a shutdown or cancel event occurs
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

    // this method, which is called by the main, tells the main
    // whether or not we're just shutting down this subscriber or
    // cancelling this subscriber's news subscription
    int news_unsubscribe() { return m_news_unsubscribe; }

  private:
    int m_news_unsubscribe;
};

#endif
