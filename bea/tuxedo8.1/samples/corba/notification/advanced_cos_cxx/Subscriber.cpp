//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// Subscriber.cpp
//
// Subscriber joint client/server program for the advanced
// cos notification c++ sample.
//
// This program acts as a client when it subscribes and unsubscribes
// for events.  It acts as a server when it receives events.  This
// program receives event by implementing callback objects which
// are invoked by the notification service when events need to
// be delivered.
//
// This program creates two subscriptions.  The first, a persistent
// subscription, subscribes to news events. The second, a transient
// subscription, subscribes to news administration events.
//
// For the news event subscription, this program creates a persistent
// callback object reference to the "NewsConsumer_i" servant class.
//
// The first time that this program is run, it prompts the user
// for a name.  Then it prompts the user for which port to run on
// (since the persistent callback object reference must always be
// run on the same port number).  Then it prompts the user for a
// news category and a keyword.  It creates the subscription and
// writes out the port number and subscription id to a file named
// <name>.pstore.  It uses the keyword to create a data filter
// (that is, only receive events whose "Story" field contains the
// keyword).
//
// The second time that this program is run, it prompts the user
// for a name.  Then it opens the file <name>.pstore and extracts
// the port number (so that is can re-start the persistent callback
// object).  It also extracts the subscription id so that it can
// unsubscribe if necessary.
//
// There are two kinds of news admin events.  The first, called
// "Shutdown", tells this subscriber to shutdown the process but
// leave the news subscription intact.  The second, called "Cancel",
// tells this subscriber to shutdown the process and cancel the
// news subscription.  As a side effect, the file <name>.pstore is
// also removed.
//
// If news events are posted while this subscriber has shutdown,
// then the events are stored and re-sent to this program when it
// is restarted.  However, if this subscriber shuts down for too
// long (see the retry parameters of the queue), then the events
// are moved to the error queue and the administrator, using
// ntsadmin, must either retry the news events or delete them.
//
// For the news admin event subscription, this program creates
// a transient subscription (using a transient callback reference)
// every time that the subscriber is run.  When the program
// shuts down, it cancels this transient subscription.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifdef WIN32
#include <strstrea.h>
#include <stdio.h>  // for "unlink"
#else
#include <strstream.h>
#include <unistd.h> // for "unlink"
#endif
#include <fstream.h>
#include <Tobj_Bootstrap.h>
#include <tobj_c.h>
#include <beawrapper.h>
#include "Tobj_Notification_c.h"
#include "NewsConsumer_i.h"
#include "ShutdownConsumer_i.h"
#include <client_ex.h>

#if defined(__SUNPRO_CC_COMPAT) && __SUNPRO_CC_COMPAT >= 5
using std::ws;
#endif

//--------------------------------------------------------------------

// This utility class manages:
// 1) on the first run, prompting the user for news subscription info
// 2) writing the subscription info to a file
// 3) reading the subscription info back in when the subscriber is
//    restarted
// 4) deleting the file when the subscriber is cancelled
// This class is not responsible for creating or deleting
// subscriptions.

class SubscriptionInfo
{
  public:

    // constructor
    SubscriptionInfo();

    // methods to access subscription info

    // return the name (always valid)
    const char* subscription_name () { return m_subscription_name; }

    // return the port (always valid)
    const char* port() { return m_port; }

    // return the category (only valid on 1st run)
    const char* category() { return m_category; }

    // return the keyword (only valid on 1st run)
    const char* keyword() { return m_keyword; }

    // have we already subscribed? (that is, is this the 1st run?)
    int news_subscribed() { return m_news_subscribed; }

    // return the subscription id (only valid after we're subscribed)
    CosNotifyChannelAdmin::ProxyID news_subscription_id()
      { return m_news_subscription_id; }

    // return the filter id (only valid after we're subscribed)
    CosNotifyFilter::FilterID news_filter_id()
      { return m_news_filter_id; }

    // since we don't subscribe, someone else is responsible for subscribing.
    // however, we're responsible for writing out the persistent storage
    // file which includes the subscription id and filter id.  Therefore,
    // provide methods that allows the subscriber to hand us the subscription
    // id and filter id. These method is only valid on the 1st run.
    void news_subscription_id(CosNotifyChannelAdmin::ProxyID id)
      { m_news_subscription_id = id; }

    void news_filter_id(CosNotifyFilter::FilterID id)
      { m_news_filter_id = id; }

    // write out the persistent storage file (only valid on 1st run)
    // Again, since we don't subscribe, we need to be told when to
    // write out the persistent storage file.
    void write();

    // delete the persistent storage file
    void cancel();

  private:
    char                           m_subscription_name [256];
    char                           m_port              [256];
    char                           m_category          [256];
    char                           m_keyword           [256];
    int                            m_news_subscribed;
    CosNotifyChannelAdmin::ProxyID m_news_subscription_id;
    CosNotifyFilter::FilterID      m_news_filter_id;
    ostrstream                     m_pstore_path_os;
    const char*                    m_pstore_path;
};

// constructor
SubscriptionInfo::SubscriptionInfo()
{
  m_subscription_name    [0] =  0;
  m_port                 [0] =  0;
  m_category             [0] =  0;
  m_keyword              [0] =  0;
  m_news_subscribed          =  0;
  m_news_subscription_id     = -1;
  m_news_filter_id           = -1;
  m_pstore_path              =  0;

  // regardless of whether or not this is the first run,
  // prompt the user for a name
  cout << "Name?" << flush;
  cin >> ws;
  cin.getline(m_subscription_name, sizeof(m_subscription_name));

  // construct the persistent storage filename (= <name>.pstore)
  m_pstore_path_os << m_subscription_name << ".pstore" << ends;
  m_pstore_path = m_pstore_path_os.str();
  m_pstore_path_os.rdbuf()->freeze(0);

  {
    // try to open the file to see if it exists
    // (that is, whether or not this is the first run)
    // read in the port number, subscription id and filter id
    ifstream pstore_is(m_pstore_path);
    pstore_is.getline(m_port, sizeof(m_port));
    pstore_is >> m_news_subscription_id >> m_news_filter_id;
    if (pstore_is) {
      // the open and read succeeded therefore we've already
      // successfully subscribed (that is, this isn't the 1st run)
      m_news_subscribed = 1;
    }
  }

  // if this is isn't the 1st run, we have all the data we need
  if (m_news_subscribed) return;

  // first run.
  // prompt the user for a port number, news category and keyword

  cout << "Port (e.g. 2465)?" << flush;
  cin >> ws;
  cin.getline(m_port, sizeof(m_port));

  cout << "News category (or all)?" << flush;
  cin >> ws;
  cin.getline(m_category, sizeof(m_category));

  cout << "Keyword (or none)?" << flush;
  cin >> ws;
  cin.getline(m_keyword, sizeof(m_keyword));
}

// write out the persistent storage file
void SubscriptionInfo::write()
{
  m_news_subscribed = 1;

  // create the file
  ofstream pstore_os(m_pstore_path);

  // write out the port number, subscription id and filter id
  pstore_os
    << m_port
    << endl
    << m_news_subscription_id
    << endl
    << m_news_filter_id
    << ends;
}

// delete the persistent storage file
void SubscriptionInfo::cancel()
{
  if (!m_news_subscribed) return;
  try {
    // delete the file
    unlink(m_pstore_path);
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;
  m_news_subscribed = 0;
}

//--------------------------------------------------------------------

// This utility class manages the news subscription.  It creates the
// news callback servant, creates its reference and manages its
// subscription. It uses the subscription info class.

class NewsSubscription
{
  public:
    // constructor
    NewsSubscription(
      SubscriptionInfo&                        subscription_info,
      CosNotifyChannelAdmin::ConsumerAdmin_ptr consumer_admin,
      CosNotifyFilter::FilterFactory_ptr       filter_factory,
      BEAWrapper::Callbacks&                   callbacks
    );
    // destroy the subscription and persistent storage file
    void cancel();
  private:
    SubscriptionInfo&                        m_subscription_info;
    CosNotifyChannelAdmin::ConsumerAdmin_ptr m_consumer_admin;
    NewsConsumer_i                           m_news_consumer_impl;
};

// constructor
NewsSubscription::NewsSubscription(
  SubscriptionInfo&                        subscription_info,
  CosNotifyChannelAdmin::ConsumerAdmin_ptr consumer_admin,
  CosNotifyFilter::FilterFactory_ptr       filter_factory,
  BEAWrapper::Callbacks&                   callbacks
) :
  // remember the subscription info and consumer admin objects
  m_subscription_info(subscription_info),
  m_consumer_admin(consumer_admin)
{
  // create a persistent object reference to the news callback servant
  CORBA::Object_var
    news_consumer_oref =
      callbacks.start_persistent_userid(
        &m_news_consumer_impl,
        CosNotifyComm::_tc_StructuredPushConsumer->id(),
        "news_subscription"
      );

  CosNotifyComm::StructuredPushConsumer_var
    news_consumer =
      CosNotifyComm::StructuredPushConsumer::_narrow(
        news_consumer_oref.in()
      );

  // if we're already subscribed, then we're done starting up
  if (m_subscription_info.news_subscribed()) return;

  // create a new subscription (at this point, it isn't complete)
  //
  // hand the subscription id to the subscription info object so
  // that it can write the subscription id out to persistent
  // storage.
  //
  // when a subscription is created, the subscription must be
  // completed within 5 minutes or the subscription is
  // automatically destroyed.  therefore, don't bother putting
  // in error handling to remove the subscription if any problem
  // occurs.

  CosNotifyChannelAdmin::ProxyID subscription_id;
  CosNotifyChannelAdmin::ProxySupplier_var
    generic_subscription =
      m_consumer_admin->obtain_notification_push_supplier(
        CosNotifyChannelAdmin::STRUCTURED_EVENT,
        subscription_id
      );
  m_subscription_info.news_subscription_id(subscription_id);

  CosNotifyChannelAdmin::StructuredProxyPushSupplier_var
    subscription =
      CosNotifyChannelAdmin::StructuredProxyPushSupplier::_narrow(
        generic_subscription.in()
      );

  // set the quality of service.  this sets the subscription name
  // and subscription type (=PERSISTENT)
  CosNotification::QoSProperties qos;
  qos.length(2);
  qos[0].name    = CORBA::string_dup(Tobj_Notification::SUBSCRIPTION_NAME);
  qos[0].value <<= m_subscription_info.subscription_name();
  qos[1].name    = CORBA::string_dup(Tobj_Notification::SUBSCRIPTION_TYPE);
  qos[1].value <<= Tobj_Notification::PERSISTENT_SUBSCRIPTION;

  subscription->set_qos(qos);

  // create a filter (used to specify domain, type and data filter)
  // when a filter is created, the subscription must be completed
  // within 5 minutes or the filter is automatically destroyed.
  // therefore, don't bother putting in error handling to remove
  // the filter if any problem occurs.
  CosNotifyFilter::Filter_var filter =
    filter_factory->create_filter(Tobj_Notification::CONSTRAINT_GRAMMAR);

  // set the type to the news category (or a wild card for all categories)
  const char* category = m_subscription_info.category();
  const char* type = (!strcmp(category, "all")) ? ".*" : category;

  // if the user only wants stories that include a keyword, then
  // create a data filter for that keyword.

  ostrstream data_filter_os;

  if (strcmp(m_subscription_info.keyword(), "none") != 0) {
    data_filter_os << "Story %% '.*(" << m_subscription_info.keyword() << ").*'";
  }

  data_filter_os << ends;
  const char* data_filter = data_filter_os.str();
  data_filter_os.rdbuf()->freeze(0);

  // set the filtering parameters
  // (domain = "News", type and data filter)

  CosNotifyFilter::ConstraintExpSeq constraints;
  constraints.length(1);
  constraints[0].event_types.length(1);
  constraints[0].event_types[0].domain_name = CORBA::string_dup("News");
  constraints[0].event_types[0].type_name   = CORBA::string_dup(type);
  constraints[0].constraint_expr            = CORBA::string_dup(data_filter);

  CosNotifyFilter::ConstraintInfoSeq_var add_constraints_results =
    filter->add_constraints(constraints);

  // add the filter to the subscription
  //
  // hand the filter id to the subscription info object so
  // that it can write the filter id out to persistent
  // storage.

  m_subscription_info.news_filter_id(
    subscription->add_filter(filter.in())
  );

  // now that we've set the subscription name, type and filtering
  // parameters, complete the subscription by passing in the
  // reference of the callback object to deliver the news events to
  subscription->connect_structured_push_consumer(news_consumer.in());

  // tell the subscription info object to write out the
  // subscription info to a file
  m_subscription_info.write();
}

// cancel the subscription and delete the persistent storage file
void NewsSubscription::cancel()
{
  if (!m_subscription_info.news_subscribed()) return;

  try {

    // use the subscription id to get back the subscription object
    CosNotifyChannelAdmin::ProxySupplier_var
      generic_subscription =
        m_consumer_admin->get_proxy_supplier(
          m_subscription_info.news_subscription_id()
        );

    CosNotifyChannelAdmin::StructuredProxyPushSupplier_var
      subscription =
        CosNotifyChannelAdmin::StructuredProxyPushSupplier::_narrow(
          generic_subscription.in()
        );

    // use the filter id to get back the filter object
    CosNotifyFilter::Filter_var filter =
      subscription->get_filter(
        m_subscription_info.news_filter_id()
      );

    // get rid of the subscription
    try {
      subscription->disconnect_structured_push_supplier();
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;

    // get rid of the filter
    try {
      filter->destroy();
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;

  // tell the subscription info object to get rid of the persistent
  // storage file which records the subscription info
  m_subscription_info.cancel();
}

//--------------------------------------------------------------------

// This utility class manages the news admin subscription.  It
// creates the news admin callback servant, creates its reference,
// and manages its subscription.  It uses the subscription info class.

class ShutdownSubscription
{
  public:

    // constructor
    ShutdownSubscription(
      SubscriptionInfo&                        subscription_info,
      CosNotifyChannelAdmin::ConsumerAdmin_ptr consumer_admin,
      CosNotifyFilter::FilterFactory_ptr       filter_factory,
      BEAWrapper::Callbacks&                   callbacks
    );

    // when we're shutting down, the news admin callback servant
    // knows whether or not we're supposed to cancel the subscription
    // too.  This method returns this info.
    int news_unsubscribe() { return m_shutdown_consumer_impl.news_unsubscribe(); }

    // used to remove this subscription.  This is called by either by
    // the news admin callback servant when it shuts down this process
    // (via the "shutdown" method), or by the destructor (to remove
    // the subscription when we're exiting because of an error)
    void cancel();

    // destructor - gets rid of the news admin subscription
    ~ShutdownSubscription();

  private:
    SubscriptionInfo&                 m_subscription_info;
    CosNotifyChannelAdmin::StructuredProxyPushSupplier_var
                                      m_subscription;
    CosNotifyFilter::Filter_var       m_filter;
    ShutdownConsumer_i                m_shutdown_consumer_impl;
};

// constructor
ShutdownSubscription::ShutdownSubscription(
  SubscriptionInfo&                        subscription_info,
  CosNotifyChannelAdmin::ConsumerAdmin_ptr consumer_admin,
  CosNotifyFilter::FilterFactory_ptr       filter_factory,
  BEAWrapper::Callbacks&                   callbacks
) :
  // remember the subscription info object
  m_subscription_info(subscription_info)
{
  // create a transient object reference to the news admin
  // callback servant
  CORBA::Object_var
    shutdown_consumer_oref =
      callbacks.start_transient(
        &m_shutdown_consumer_impl,
        CosNotifyComm::_tc_StructuredPushConsumer->id()
      );

  CosNotifyComm::StructuredPushConsumer_var
    shutdown_consumer =
      CosNotifyComm::StructuredPushConsumer::_narrow(
        shutdown_consumer_oref.in()
      );

  CosNotifyChannelAdmin::ProxyID subscription_id;
  CosNotifyChannelAdmin::ProxySupplier_var
    generic_subscription =
      consumer_admin->obtain_notification_push_supplier(
        CosNotifyChannelAdmin::STRUCTURED_EVENT,
        subscription_id
      );

  // create a new subscription (at this point, it isn't complete)
  //
  // remember the subscription id so that we can unsubscribe later.
  //
  // when a subscription is created, the subscription must be
  // completed within 5 minutes or the subscription is
  // automatically destroyed.  therefore, don't bother putting
  // in error handling to remove the subscription if any problem
  // occurs.

  m_subscription =
    CosNotifyChannelAdmin::StructuredProxyPushSupplier::_narrow(
      generic_subscription.in()
    );

  // set the quality of service.  this sets the subscription name
  // and subscription type (=TRANSIENT)
  CosNotification::QoSProperties qos;
  qos.length(2);
  qos[0].name    = CORBA::string_dup(Tobj_Notification::SUBSCRIPTION_NAME);
  qos[0].value <<= m_subscription_info.subscription_name();
  qos[1].name    = CORBA::string_dup(Tobj_Notification::SUBSCRIPTION_TYPE);
  qos[1].value <<= Tobj_Notification::TRANSIENT_SUBSCRIPTION;

  m_subscription->set_qos(qos);

  // create a filter (used to specify domain, type and (no) data filter)
  // when a filter is created, the subscription must be completed
  // within 5 minutes or the filter is automatically destroyed.
  // therefore, don't bother putting in error handling to remove
  // the filter if any problem occurs.
  m_filter =
    filter_factory->create_filter(Tobj_Notification::CONSTRAINT_GRAMMAR);

  // set the filtering parameters
  // (domain = "NewsAdmin", type "Shutdown" or "Cancel", no data filter)
  CosNotifyFilter::ConstraintExpSeq constraints;
  constraints.length(1);
  constraints[0].event_types.length(1);
  constraints[0].event_types[0].domain_name = CORBA::string_dup("NewsAdmin");
  constraints[0].event_types[0].type_name   = CORBA::string_dup("(Shutdown|Cancel)");
  constraints[0].constraint_expr            = CORBA::string_dup("");

  CosNotifyFilter::ConstraintInfoSeq_var add_constraints_results =
    m_filter->add_constraints(constraints);

  // add the filter to the subscription
  // remember the filter id so that we can get rid of the filter later
  CosNotifyFilter::FilterID filter_id =
    m_subscription->add_filter(m_filter.in());

  // now that we've set the subscription name, type and filtering
  // parameters, complete the subscription by passing in the
  // reference of the callback object to deliver the news admin events to
  m_subscription->connect_structured_push_consumer(shutdown_consumer.in());
}

// remove this subscription
void ShutdownSubscription::cancel()
{
  // get rid of the news admin subscription
  if (!CORBA::is_nil(m_filter.in())) {
    try {
      m_filter->destroy();
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;
    m_filter = CosNotifyFilter::Filter::_nil();
  }

  // get rid of the news admin filter
  if (!CORBA::is_nil(m_subscription.in())) {
    try {
      m_subscription->disconnect_structured_push_supplier();
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;
    m_subscription =
      CosNotifyChannelAdmin::StructuredProxyPushSupplier::_nil();
  }
}

// destructor (automatically removes this subscription)
ShutdownSubscription::~ShutdownSubscription()
{
  cancel();
}

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
// the "disconnect_structured_proxy_supplier" operation on the
// subscription object.  However, once orb->shutdown has been
// called, CORBA invokes are illegal.  Therefore, the subscription
// must be cancelled in the callback servant's method BEFORE the
// method calls orb->shutdown.
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
// Since we're using the cos notification api, we not only
// have to create a subscription, we also have to create a filter.
// Like the subscription, the filter object must be destroyed by
// calling its destroy method.  There the "destroy_filter"
// routine, analogous to "unsubscribe", is provided.  This
// routine is called by both the main and the servant to ensure
// that the filter is destroyed.
//
// To keep the shutdown details out of the servant method, a
// "shutdown" routine is also provided.  This routine uses the
// NewsSubscription & ShutdownSubscription objects to unsubscribe.
//
// A note on global variables: instead of having global "vars"
// whose destructors are run after "main" exits, use "vars" on
// the main's stack (thus the destructors are run before "main"
// exits) then have global "ptrs" which refer to the references
// the main's "vars" manage.

//--------------------------------------------------------------------

static CORBA::ORB_ptr        s_orb;
static NewsSubscription*     s_news_subscription;
static ShutdownSubscription* s_shutdown_subscription;

extern void shutdown()
{
  // if the Reporter sent a "Cancel" event, then get rid of the
  // news subscription (filter too) and persistent storage file
  if (s_shutdown_subscription->news_unsubscribe()) {
    s_news_subscription->cancel();
  }
  // regardless, get rid of the news admin subscription (filter too)
  s_shutdown_subscription->cancel();

  // finally, shut down the orb
  s_orb->shutdown(0);
}

//--------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try {

    // Create the object that manages the subscription info
    // This must be done first since we need to know the port
    // number before we initialize the orb.
    // Heap allocate it since the servants will use it (indirectly).
    SubscriptionInfo* subscription_info = new SubscriptionInfo;

    // use a try block to that we can destroy the object
    // regardless of whether or not an exception is thrown
    try {

      // Initialize the orb on the proper port number.
      // Since we're using persistent callback references,
      // we must run IIOP (v.s. native).  Do this by creating
      // our own argc/argv.
      char* orb_argv[6];
      int   orb_argc = 0;
      orb_argv[orb_argc++] = argv[0];
      orb_argv[orb_argc++] = (char *)"-ORBport";
      orb_argv[orb_argc++] = (char*)subscription_info->port();
      orb_argv[orb_argc++] = (char *)"-ORBid";
      orb_argv[orb_argc++] = (char *)"BEA_IIOP";
      orb_argv[orb_argc  ] = 0;

      CORBA::ORB_var orb = CORBA::ORB_init(orb_argc, orb_argv, "");
      s_orb = orb.in();

      // intialize the bootstrap
      Tobj_Bootstrap bootstrap(orb.in(), "");

      CORBA::Object_var
        channel_factory_oref =
          bootstrap.resolve_initial_references(
            "NotificationService"
          );

      // get the Cos Notification channel factory object reference
      CosNotifyChannelAdmin::EventChannelFactory_var
        channel_factory =
          CosNotifyChannelAdmin::EventChannelFactory::_narrow(
            channel_factory_oref.in()
          );

      // use the channel factory to get the default channel
      CosNotifyChannelAdmin::EventChannel_var channel =
        channel_factory->get_event_channel(
          Tobj_Notification::DEFAULT_CHANNEL
        );

      // use the channel to get the consumer admin and the filter factory

      CosNotifyChannelAdmin::ConsumerAdmin_var consumer_admin =
        channel->default_consumer_admin();

      CosNotifyFilter::FilterFactory_var filter_factory =
        channel->default_filter_factory();

      // to receive events, this client must also be a server -
      // that is, this client must implement a CORBA object that
      // will be invoked (called back) when an event occurs

      // create a callback wrapper object since this client needs to
      // support callbacks
      BEAWrapper::Callbacks callbacks(orb.in());

      // create the object that processes "NewsAdmin" events
      // heap allocate it since it will be accessed by servants.
      s_shutdown_subscription = new
        ShutdownSubscription(
          *subscription_info,
          consumer_admin.in(),
          filter_factory.in(),
          callbacks
        );

      // use a try block to that we can destroy the object
      // regardless of whether or not an exception is thrown
      try {

        // create the object that processes "News" events
        // heap allocate it since it will be accessed by servants.
        s_news_subscription = new
          NewsSubscription(
            *subscription_info,
            consumer_admin.in(),
            filter_factory.in(),
            callbacks
          );

        // use a try block to that we can destroy the object
        // regardless of whether or not an exception is thrown
        try {
          if (subscription_info->news_subscribed()) {

            // process events until we're shut down
            // Eventually, we'll receive a "NewsAdmin" event
            // which will cause this process to shutdown.

            cout << "Ready" << endl;
            orb->run();
          }
        }
        CATCH_REPORT_AND_SWALLOW_EXCEPTION;
        // get rid of the heap allocated news subscription object
        delete s_news_subscription;
      }
      CATCH_REPORT_AND_SWALLOW_EXCEPTION;
      // get rid of the heap allocated news admin subscription object
      delete s_shutdown_subscription;
    }
    CATCH_REPORT_AND_SWALLOW_EXCEPTION;
    // get rid of the heap allocated subscription info object
    delete subscription_info;
  }
  CATCH_REPORT_AND_SWALLOW_EXCEPTION;
  cout << "Done" << endl;
  return 0;
}

//--------------------------------------------------------------------
