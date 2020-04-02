#	(c) 2003 BEA Systems, Inc. All Rights Reserved.

    Simpapp Read Me
    ~~~~~~~ ~~~~ ~~

    The "simpapp" sample application contains a simple Tuxedo
    C++ server with a C++ and Java client. The server will
    convert strings to upper and lower case.

    These instructions will help you run this sample.

    1) Make sure that the directory that you installed Tuxedo
       under is set in the environment variable "TUXDIR"

    2) Make a copy of the simpapp directory.

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

       Some progress messages will be printed out along with
       whether or not the sample passed or failed.

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

    This application has now been modified slightly to have the
    SimpleFactory::find_simple() create Simple object references with
    unique object ids. This avoids contention in the AOM caused by lots
    of clients using the same object id and invoking on the same server.

    This application DOES NOT show all the ways that a Tuxedo 
    application can be modified to increase scalability.  However, 
    the university production sample demonstrates these features in 
    $(TUXDIR)/samples/corba/university/production.

    To make simpapp scalable, by

    a) using multiple SimpleFactory object references (unique object ids),
    b) starting multiple servers to avoid contention for a single
       simple_server,
    c) using factory based routing to allow the administrator to control
       which group (thus machine) services a client,

    one can look for comments in the following files, browse through
    similar files in the university production sample and modify the
    code appropriately.

        simple.idl
        simple_i.h
        simplec.cpp
        simples.cpp
        simple_i.cpp
        runme.ksh
        runme.cmd
