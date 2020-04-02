#	(c) 2003 BEA Systems, Inc. All Rights Reserved.

    Simpapp_par Read Me
    ~~~~~~~~~~~ ~~~~ ~~

    The "simpapp_par" sample application contains a Tuxedo C++
    server with a C++ and Java client. The server will convert
    strings to upper and lower case.  There is also a method to
    return the process id of the server which handles the 
    request.  The simple.icf file is included to set the 
    concurrency_policy on the Simple interface to user_controlled
    in order to demonstrate parallel objects.  The runme script
    will run two clients at a time and will verify that the 
    object actually ran on multiple server processes by checking
    the results of the calls to the s_pid method.

    These instructions will help you run this sample.

    1) Make sure that the directory that you installed Tuxedo
       under is set in the environment variable "TUXDIR"

    2) Make a copy of the simpapp_par directory.

    3) cd to the copy.  If you're on Unix, start a ksh.

    4) Change the permissions on all the files to give them
       read-access.

    5) For Windows NT, make sure "nmake" is in your path.
       For Unix,       make sure "make"  is in your path.

    6) Run the sample automatically by typing:

           Windows NT
           ----------
           prompt>runme

           Unix
           ----
           prompt>./runme.ksh

       Some progress messages will be printed out.

    7) To run the sample by hand:

      a) Start the sample:

           Windows NT
           ----------
           prompt>results\setenv
           prompt>tmboot -y

           Unix
           ----
           prompt>. ./results/setenv.ksh
           prompt>tmboot -y

      b) Run the native C++ client:

           prompt>simple_client

      c) Run the remote C++ client:

           prompt>simple_client -ORBid BEA_IIOP

      d) Run the remote Java client:

           Windows NT
           ----------
           prompt>java -DTOBJADDR=%TOBJADDR% -classpath %CLASSPATH% SimpleClient

           Unix
           ----
           prompt>java -DTOBJADDR=$TOBJADDR -classpath $CLASSPATH SimpleClient

      e) Shutdown the sample:

           prompt>tmshutdown -y

    8) To restore the directory to its original state:

           Windows NT
           ----------
           prompt>results\setenv
           prompt>nmake -f makefile.nt clean

           Unix
           ----
           prompt>. ./results/setenv.ksh
           prompt>make -f makefile.mk clean

    Notes:

    The Java client will be built and run only when then runme
    script detects that the JAVA_HOME environment variable is
    defined. Otherwise, only the C++ client will be used.

    This application DOES NOT show all the ways that a Tuxedo
    application can be modified to increase scalability.  However,
    the university production sample demonstrates these features in
    $(TUXDIR)/samples/corba/university/production.
