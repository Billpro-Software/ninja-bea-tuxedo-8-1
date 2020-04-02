#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
Interceptor C++ Sample Application Readme
--------------------------------------------------------

This sample application contains a Tuxedo C++ application 
which allows users to query a simple database for people 
with specific physical features.

This sample application can be used in conjunction with
the sample interceptors to demonstrate possible interceptor
functionality. It queries the database server in order
to pass data which can be intercepted.
 
This sample provides two executables :

   A database service which contains a simple database of
   physical characteristics of people.  It implements an
   idl interface which allows search and retrieval of
   data from the database.

   A query application which allows users to interactively
   search the database for people who fit the desired
   characteristices.  The application will invoke methods
   on the database service to search and retrieve the
   database.  The query application is a pure client.


The sample application and database service do not themselves
implement interceptors.  However, the interceptors provided in
the interceptor samples can be registered and used with this
application.  Each interceptor sample demonstrates possible
interceptor functionality.  

The security and data stream interceptor requires the use of this 
application in order to demonstrate its functionality.  This is 
because it intercepts data which is specific to the interface
implemented by this sample application.


When the query application runs, it prompts the user to enter data
item which will be packaged as a database search.  Pressing "Enter"
will display the options for data items.  Once the items are gathered,
the database request is constructed and sent.  The number of returned
entries is displayed by the application.  If the actual results are
desired, use the command "results".  To exit the application, enter
"exit".

The sample data interceptor implements logging of the request and
response parameters.

To run this sample, you need to run at least one database server
and at least one query application.  You may run multiple query
applications. Since interceptors run within the process space of
the server and client, each server and client will accumulate
unique log files.

This directory contains the following source files:

  Readme.txt               : this file
  makefile.nt              : makefile for Windows NT
  makefile.mk              : makefile for Unix
  makefile.inc             : common makefile used by makefile.nt,mk
  ex.h                     : include file
  personqueryc.cpp         : code for the query application
  personquerys.cpp         : code for the database server
  personquery_i.h,cpp      : servant class that implements database searching 

This directory uses the following source files from the
C++ interceptor samples' common directory :

  personquery.idl      : idl definitions for the database query interface
  common.nt            : makefile symbols for Windows NT
  common.mk            : makefile symbols for Unix
  makefile.nt          : makefile for Windows NT
  makefile.mk          : makefile for Unix
  app.inc              : makefile for administrative targets

How to run this sample:

1)  Set the "TUXDIR" environment variable to the directory
    where Tuxedo is installed

2)  Make a copy of the C++ interceptor samples
      Windows NT : %TUXDIR%\samples\corba\interceptors
      Unix       : ${TUXDIR}/samples/corba/interceptors

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

10) Run the query application:

    prompt>PersonQueryClient
    Option?                     enter a "return"; options will be displayed 

    A single command line is constructed into a database search
    request, however, you may enter as many commands as you like.
    The number of "hits" is displayed after each request.  If
    you want to see the results of the search request, enter "results".

    Data items containing white space (ie, spaces, tabs) must be
    contained in double quotes.  For example, a person's name would
    be entered as "fred murtz".

    When you're done, choose the exit option.

    You may start multiple query applications by repeating this step.

11) Shutdown the system:

    In one of the windows type:

      prompt>tmshutdown -y

12) To restore the directory to its original state:

    In one of the windows, type :

      Windows NT : prompt>nmake -f makefile.nt clean
      Unix       : prompt>make -f makefile.mk clean
