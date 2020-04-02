#	(c) 2003 BEA Systems, Inc. All Rights Reserved.

    simpapp_mt Read Me
    ~~~~~~~~~~ ~~~~ ~~

    The "simpapp_mt" sample application contains a simple Tuxedo
    C++ application which converts strings to upper and lower 
    case using a multi-threaded C++ server. It is intended to 
    demonstrate the following features:

    - the use of the new buildobjserver command line qualifiers
      for building multi-threaded servers
    
    - the use of the new ubb configuration file thread administration
      commands to specify concurrency strategies
    
    - the use of the new thread extension APIs for Servers and Servants
    
    - the use of application managed threads within a server


    These instructions will help you run this sample.

    1) Make sure that the directory that you installed Tuxedo
       under is set in the environment variable "TUXDIR"

    2) Make a copy of the simpapp_mt directory.

    3) cd to the copy.  If you're on Unix, start a ksh.

    4) Change the permissions on all the files to give them
       read-access.

    5) For Windows NT, make sure "nmake" is in your path.
       For Unix,       make sure "make"  is in your path.

    6) Build and run the sample automatically by typing:

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

      d) Shutdown the sample:

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
