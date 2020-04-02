
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
This directory contains C++ samples for Request Level Interceptors.  Three
interceptors are provided, along with a sample application:

        PersonQuery             an application client and server which allows
                                a user to make simple queries to search a
                                simple database for specific individuals.
        InterceptorSimp         a simple interceptor sample
        InterceptorSec          an interceptor which demonstrates a simple
                                security mechanism.  This interceptor only
                                secures the PersonQuery application.
        InterceptorData         an interceptor which demonstrates how to
                                intercept the parameters of the PersonQuery
                                application's request invocations and
                                the responses to those requests.

In order to build these samples:

1)  Set the "TUXDIR" environment variable to the directory
    where Tuxedo is installed

2)  Make a copy of the C++ interceptor samples
      Windows NT : %TUXDIR%\samples\corba\interceptors_cxx
      Unix       : ${TUXDIR}/samples/corba/interceptors_cxx

3)  cd to the copy.  If you're on Unix, start a ksh.

4)  Change the permissions on all the files in all the
    directories to give them write and execute access.

5)  Windows NT : make sure "nmake" is in your path.
    Unix       : make sure "make"  is in your path.

6)  cd to your copy of this sample

7)  Set the environment:

    Windows NT : prompt>.\setenv.cmd
    Unix       : prompt>. ./setenv.ksh

8)  Build the sample and the interceptors:

    Windows NT : prompt>nmake -f makefile.nt
    Unix       : prompt>make -f makefile.mk


9)  In order to run the sample app with interceptors, the interceptors must 
be registered. The interceptors makefiles each contain targets to register
and unregister the interceptor.  It is not necessary to register the 
interceptors to run the sample app, however, you can do so by:

    Windows NT :
	prompt> cd %TUXDIR%\samples\corba\interceptors_cxx\simple_cxx
        prompt> nmake -f makefile.nt config
        prompt> cd ..\security_cxx
        prompt> nmake -f makefile.nt config
        prompt> cd ..\data_cxx
        prompt> nmake -f makefile.nt config

    Unix       :
	prompt> cd $TUXDIR/samples/corba/interceptors_cxx/simple_cxx
        prompt> make -f makefile.mk config
        prompt> cd ../security_cxx
        prompt> make -f makefile.mk config
        prompt> cd ../data_cxx
        prompt> nmake -f makefile.mk config


You can unregister in a similar fashion by using the make target 'unconfig'.
Please see the documentation on the RLI Samples for more information.

10) Boot the system:

        prompt> tmboot -y 

11) Run the PersonQueryClient:

    Windows NT :
        prompt> cd %TUXDIR%\samples\corba\interceptors_cxx\app_cxx

    Unix       :
        prompt> cd $TUXDIR/samples/corba/interceptors_cxx/app_cxx

    On all systems :
        prompt> PersonQueryClient
        -------------------------------
        Options?                       enter a search parameter/value,
                                       for example, 'age 16', but without
                                       the quotes
        hits: 4                        PersonQueryClient found 4 entries that
                                       matched the search parameter above.
        -------------------------------
        Options?                       enter a more restrictive parameter/value
                                       such as 'age 16 hair blue'
        hits: 3                        PersonQueryClient found 3 entries that
                                       match the more restrictive search
        -------------------------------
        Options?                       enter 'result' to view the complete
                                       data record for found entries.
        [ 3 database entries displayed]
        -------------------------------
        Options?                       enter 'exit' to exit PersonQueryClient 

12) Shutdown the system:

        prompt> tmshutdown -y

13) Viewing the interceptor data:

    If you had registered an interceptor prior to booting the system and
    running PersonQueryClient, you can now look at the output from the
    interceptor.  See the RLI Samples documentation for information of
    where to find the interceptor output.

14) To restore the directory to its original state:

    Windows NT :
        prompt> cd %TUXDIR%\samples\corba\interceptors_cxx
        prompt> nmake -f makefile.nt clean

    Unix       :
        prompt> cd $TUXDIR/samples/corba/interceptors_cxx
        prompt> make -f makefile.mk clean


Please see the RLI Samples documentation for more information on running the
PersonQuery application and looking at the interceptor output.
