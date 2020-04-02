#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
Notification Advanced Cos Notification C++ Sample Readme
--------------------------------------------------------

This sample application contains a Tuxedo notification 
C++ application which allows reporters to report news 
stories and subscribers to receive those stories.

This sample shows advanced notification usage:
  - transient and persistent subscriptions
  - the COS Notification interface
    (instead of the Simple Events interface)
  - data filtering

This sample provides three executables :

   A wire service which posts events.  It is a notification
   service client and a Tuxedo server.  It implements an idl
   interface that reporters (see below) use.

   A reporter which reports news stories by invoking methods
   on the wire service.  The wire service, in turn, converts
   the stories into events and posts them using the
   notification service.  The reporter is a pure client.

   A subscriber which receives events.  The subscriber
   acts as a client when it subscribes for events and
   as a server when it receives events.

The wire service uses the notification service to post three
kinds of events :
  - "news"     events (used to deliver news to subscribers)
  - "shutdown" events (used to shutdown the subscribers temporarily)
  - "cancel"   events (used to shutdown subscribers permanently)
The notification service, in turn delivers the event to the
subscribers.  

The reporter is responsible for implementing the user interface
for reporting news as well as for shutting down and cancelling
subscriptions.  Rather than use the notification service directly
to post events, it just calls methods on the wire service server.

The subscriber uses the notification service to create a
persistent subscription to "news" events.  The subscriber
implements a persistent callback object (via the NewsConsumer_i
servant class) which is used to receive and process news events.
When the subscriber subscribes, the subscriber gives the
notification service a reference to this callback object.
When a matching event occurs, the notification service invokes
a method on this callback object to "push" the event to the
subscriber.  This method prints out the event.

The subscriber also uses the notification service to
create a transient subscription to "shutdown" and "cancel"
events.  The subscriber implements another callback object
(via the ShutdownConsumer_i servant class) which is used to
receive and process these events.

Whenever the subscriber runs, it prompts the user for a name.
The first time this user runs the subscriber program, the subscriber
creates a persistent subscription to news events.  To do this, the
subscriber prompts the user for which kind of news stories to subscribe
to and which port number the subscriber should run on.  The subscriber
runs on this port, subscribes, then writes the subscription id and port
number to a file (the name of the file is "user name".pstore).  The next
time the subscriber runs, the subscriber prompts the user for a name,
opens up the file "user name".pstore then reads the subscription id and
port number for this user from the file.  The subscriber needs to run on
the same port number each time since its news callback object's object
reference is persistent.

Since the subscriber creates a transient subscription to receive
shutdown and cancel events, this subscription is created and destroyed
every time the subscriber is run (and the shutdown/cancel callback
object's object reference is transient).  Therefore, this subscription
id is not written out to the file "user name".pstore.

When the subscriber receives a "shutdown" event, it destroys the
shutdown/callback subscription but leaves the news subscription intact.
If news events are posted after the subscriber is shutdown and before it
is restarted, then the notification service will either deliver the events
when the subscriber is restarted or will put the events on the error queue.
(You may use the "ntsadmin" tool to either delete these events from the
error queue or retry delivering them).

Whether or not the event is redelivered or is put on the error queue
depends on whether or not the subscriber restarts quickly enough.  This
depends on the retry parameters of the queue.  See advanced.inc (in the
notification samples' common directory) for the values of the queue
retry parameters.

News events have two parts : a category (e.g. "headline") and a story
(a multi-line text string).  The subscriber program prompts the user to
input a news category.  Next the subscriber subscribes to news events
whose category matches this string.  The reporter program prompts the
user for a news catetory and a story.  Next the reporter (by invoking a
method on the wire service) posts a corresponding news event.  The event
will only be delivered to subscribers who subscribed to that category
of news.

The category is just a string that the reporter and the subscriber agree
on.  There are no fixed categories in this sample.  So, in both the
reporter and subscriber, be sure to type the same string when prompted
for a category (including case and white space).

This sample also uses data filtering.  When a user first runs the
subscriber, the user will be prompted for a "keyword".  Events whose
category matches AND whose story contains the keyword will be delivered
to the subscriber.  If the user enters a keyword of "none", data
filtering will not be used (thus the user will receive all events
for the chosen news category).

To run this sample, you need to run at least one reporter
and at least one subscriber.  However, you may run multiple
reports and multiple subscribers.  Events posted by any
reporter will be delivered to all matching subscribers
(based on category).  Also, be sure to start the subscriber(s).
before posting events.  Events posted before the subscribers
are started will not be delivered.

This directory contains the following source files:

  Readme.txt               : this file
  setenv.cmd               : set the environment for Windows NT
  setenv.ksh               : set the environment for Unix
  makefile.nt              : makefile for Windows NT
  makefile.mk              : makefile for Unix
  makefile.inc             : common makefile used by makefile.nt,mk
  Reporter.cpp             : code for the reporter
  Subscriber.cpp           : code for the subscriber
  NewsConsumer_i.h,cpp     : callback servant class that subscribers use
                             to receive news events
  ShutdownConsumer_i.h,cpp : callback servant clasas that subscribers
                             use to receive shutdown and cancel events
  WireServiceServer.cpp    : code for the wire service server
  News.icf                 : icf file for the wire service interfaces
  WireService_i.h,cpp      : implements the wire service interfaces

This directory uses the following source files from the
notification samples' common directory :

  News.idl             : idl definitions for the wire service
  news_flds            : FML field definitions used to perform data
                         filtering on news events
  common.nt            : makefile symbols for Windows NT
  common.mk            : makefile symbols for Unix
  advanced.inc         : makefile for administrative targets
  ex.h                 : utilities to print exceptions
  client_ex.h          : client utilities to handle exceptions
  server_ex.h          : server utilities to handle exceptions

How to run this sample:

1)  Set the "TUXDIR" environment variable to the directory
    where Tuxedo is installed

2)  Make a copy of the notification samples
      Windows NT : %TUXDIR%\samples\corba\notification
      Unix       : ${TUXDIR}/samples/corba/notification

3)  cd to the copy.  If you're on Unix, start a ksh.

4)  Change the permissions on all the files in all the
    directories to give them write and execute access.

5)  Windows NT : make sure "nmake" is in your path.
    Unix       : make sure "make"  is in your path.

6)  cd to your copy of this sample

7)  Set the environment:

    Windows NT : prompt>.\setenv.cmd
    Unix       : prompt>. ./setenv.ksh

8)  Build the sample:

    Windows NT : prompt>nmake -f makefile.nt
    Unix       : prompt>make -f makefile.mk

9)  Boot the system:

    prompt>tmboot -y

10) Run the subscriber:

    prompt>ac_subscriber
    Name?                     enter a name (without spaces)

    first time (only) :

    Port (e.g. 2465)          enter the port number that this
                              subscriber should run on
                              
    Category (or all)         enter the category of news
                              you'd like or "all"

    Keyword (or none)         enter a keyword that you want all
                              delivered stories to contain

    You may type in any string for the news category (that is,
    there is no fixed list of news categories).  When you run
    the reporter (see step 11), make sure to specify the same
    string for the news category.

    Similarly, you may type in a string for a keyword (that is,
    there is no fixed list of keywords).  When you run the
    reporter (see step 11), make sure that the story contains
    the same string (otherwise the story will not be delivered
    to this subscriber).

    The first time the subscriber is run for this user name,
    it will create a news subscription.  On subsequent runs,
    the subscriber will re-use this subscription.  Regardless,
    the subscriber will print "Ready" when it is ready to
    receive events.

    You may start multiple subscribers by starting a window
    per subscriber and doing steps 1, 6, 7 & 10 each window.

11) Run the reporter:

    create a new window and do steps 1, 6 & 7

    prompt>ac_reporter
    ------------------------------------------------------------
    (r) Report news
    (s) Shutdown subscribers
    (c) Cancel subscribers
    (e) Exit
    Option?                             enter "r" to report news

    Category?                           enter the news category
                                        (it must exactly match the
                                        category you typed for the
                                        subscriber - including
                                        white space and case)

    Enter story (terminate with '.')    enter your story. it can
                                        span multiple lines.
                                        finish the story by
                                        typing only "." on a line
                                        followed by a carriage
                                        return.  If you typed in
                                        a keyword when subscribing,
                                        make sure the story contains
                                        this string too (including
                                        white spaces and case)

    Subscribers whose category matches the category of this
    story will receive, and print out, the story.

    If you choose the "s" option, a "shutdown" event will be posted
    and received by all the subscribers.  The subscribers will shutdown.
    While the subscribers are shut down, you may post another news
    story (by using the "r" option again).  After you restart the
    subscribers (repeat step 10), they should receive this second
    story (unless you waited so long to restart them that the event
    was moved to the error queue - use "ntsadmin" to handle this
    condition).

    If you choose the "c" option, a "cancel" event will be posted
    and received by all the subscribers.  The subscribers will cancel
    their news subscriptions then shutdown.  If you try to restart the
    subscribers, then you will be re-prompted for port, category and
    keyword since you're creating a brand new subscription.

    When you're done reporting news, choose the exit (e) option.

    You may start multiple reporters by repeating this step.
    Any news story reported by any reporter will be delivered
    to all matching subscribers.  Make sure you've exited all
    reporters before proceeding to step 12.

12) Shutdown the system:

    By this time, all the reporter and subscriber processes
    should have stopped.  In one of the windows type:

      prompt>tmshutdown -y

13) To restore the directory to its original state:

    In one of the windows, type :

      Windows NT : prompt>nmake -f makefile.nt clean
      Unix       : prompt>make -f makefile.mk clean
