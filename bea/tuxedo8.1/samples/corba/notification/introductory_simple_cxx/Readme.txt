#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
Notification Introductory Simple Events C++ Sample Readme
---------------------------------------------------------

This sample application contains a Tuxedo notification
C++ application which allows reporters to report news
stories and subscribers to receive those stories.

This sample shows the simplest notification usage:
  - only transient subscriptions
  - the Simple Events interface
    (instead of the COS Notification interface)
  - no data filtering

This sample provides two executables :

   A reporter which posts events.  It is a pure client.

   A subscriber which receives events.  The subscriber
   acts as a client when it subscribes for events and
   as a server when it receives events.

The reporter uses the notification service to post
"news" events.  The notification service then delivers
them to the subscribers.

The subscriber uses the notification service to subscribe
to "news" events.  The subscriber implements a callback
object (via the NewsConsumer_i servant class) which is
used to receive and process news events.  When the
subscriber subscribes, it gives the notification service
a reference to this callback object.  When a matching event
occurs, the notification service invokes a method on this
callback object to "push" the event to the subscriber.
For simplicity, this method prints out the event, unsubscribes
then shuts down the subscriber.

News events have two parts : a category (e.g. "headline")
and a story (a multi-line text string).  The subscriber
program prompts the user to input a news category.  Next
the subscriber subscribes to news events whose category
matches this string.  The reporter program prompts the
user for a news category and a story.  Next the reporter
posts a corresponding news event.  The event will only be
delivered to subscribers who subscribed to that category
of news.

The category is just a string that the reporter and
the subscriber agree on.  There are no fixed categories
in this sample.  So, in both the reporter and subscriber,
be sure to type the same string when prompted for a category
(including case and white space).

To run this sample, you need to run at least one reporter
and at least one subscriber.  However, you may run multiple
reports and multiple subscribers.  Events posted by any
reporter will be delivered to all matching subscribers
(based on category).  Also, be sure to start the subscriber(s).
before posting events.  Events posted before the subscribers
are started will not be delivered.

This directory contains the following source files:

  Readme.txt           : this file
  setenv.cmd           : set the environment for Windows NT
  setenv.ksh           : set the environment for Unix
  makefile.nt          : makefile for Windows NT
  makefile.mk          : makefile for Unix
  makefile.inc         : common makefile used by makefile.nt,mk
  Reporter.cpp         : code for the reporter
  Subscriber.cpp       : code for the subscriber
  NewsConsumer_i.h,cpp : callback servant class that subscribers use
                         to receive news events

This directory uses the following source files from the
notification samples' common directory :

  common.nt            : makefile symbols for Windows NT
  common.mk            : makefile symbols for Unix
  introductory.inc     : makefile for administrative targets
  ex.h                 : utilities to print exceptions
  client_ex.h          : client utilities to handle exceptions

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

    prompt>is_subscriber
    Name?                     enter a name (without spaces)
    Category (or all)         enter the category of news
                              you'd like or "all"

    You may type in any string for the news category (that is,
    there is no fixed list of news categories).  When you run
    the reporter (see step 11), make sure to specify the same
    string for the news category.

    The subscriber will create a subscription then print
    "Ready" when it is ready to receive events

    You may start multiple subscribers by starting a window
    per subscriber and doing steps 1, 6, 7 & 10 each window.

11) Run the reporter:

    create a new window and do steps 1, 6 & 7

    prompt>is_reporter
    ------------------------------------------------------------
    (r) Report news
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
                                        return.

    Subscribers whose category matches the category of this
    story will receive, and print out, the story.  When a
    subscriber receives a story, it automatically shuts down.
    To send more news, start another subscriber then report
    another story.  When you're done reporting news, choose
    the exit (e) option.

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
