
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
    NameService Simpapp Read Me
    ~~~~~~~~~~~ ~~~~~~~ ~~~~ ~~

    The NameService "simpapp" sample application contains a simple 
    Tuxedo C++ server with a C++ and Java client.  The server will 
    convert strings to upper and lower case.  This sample also 
    shows how to use wide character strings in an object interface.
    Note that because wstring is not a supported type in the JDK 
    1.2 ORB nor in the Tuxedo ORB, the Java client for this sample 
    will work only with the JDK 1.3 ORB.  This restriction extends 
    to any Java client that uses an interface containing the types 
    wstring or wchar.
    
    These instructions will help you run this sample.

    1) Make sure that the directory that you installed Tuxedo
       under is set in the environment variable "TUXDIR"

    2) Make a copy of the cnssimpapp directory.

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
           prompt>. ./runme.ksh

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

    The Java client will be built and run only when the runme
    script detects that the JAVA_HOME environment variable is
    defined. Otherwise, only the C++ client will be used.  Also, 
    because wstring is not a supported type in the JDK 1.2 ORB 
    nor in the Tuxedo ORB, the Java client for this sample will 
    work only with the JDK 1.3 ORB.  This restriction extends to 
    any Java client that uses an interface containing the types 
    wstring or wchar.
