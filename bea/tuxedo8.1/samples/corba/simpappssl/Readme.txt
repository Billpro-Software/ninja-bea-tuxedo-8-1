#	(c) 2003 BEA Systems, Inc. All Rights Reserved.

    SSL Simpapp Read Me
    ~~~ ~~~~~~~ ~~~~ ~~

    The SSL "simpapp" sample application contains a simple Tuxedo
    C++ server with a C++ and Java client. The server will 
    convert strings to upper and lower case.

    These instructions will help you run this sample.

    1) Make sure that the directory that you installed Tuxedo
       under is set in the environment variable "TUXDIR"

    2) Make a copy of the simpappssl directory.

    3) cd to the copy.  If you're on Unix, start a ksh.

    4) Change the permissions on all the files to give them
       read-access.

    5) Make sure that the IIOPListener private key is present in the 
       simpappssl directory (IIOPListener.pem). The runme script will 
       prompt for the pass phrase for the IIOPListener private key.

    6) For Windows NT, make sure "nmake" is in your path.
       For Unix,       make sure "make"  is in your path.

    7) Run the sample automatically by typing:

           Windows NT
           ----------
           prompt>runme

           Unix
           ----
           prompt>./runme.ksh

       Some progress messages will be printed out along with
       whether or not the sample passed or failed.

    8) To run the sample by hand:

      a) Start the sample:

           Windows NT
           ----------
           prompt>results\setenv
           prompt>tmboot -y

           Unix
           ----
           prompt>. ./results/setenv.ksh
           prompt>tmboot -y

      b) Run the remote C++ client:

           prompt>simple_client -ORBid BEA_IIOP -ORBpeerValidate none 

      c) Run the remote Java client:

           Windows NT
           ----------
           prompt>java -Dorg.omg.CORBA.ORBpeerValidate=none -DTOBJADDR=%TOBJADDR% -classpath %CLASSPATH% SimpleClient

           Unix
           ----
           prompt>java -Dorg.omg.CORBA.ORBpeerValidate=none -DTOBJADDR=$TOBJADDR -classpath $CLASSPATH SimpleClient

      d) Shutdown the sample:

           prompt>tmshutdown -y

    9) To restore the directory to its original state:

           Windows NT
           ----------
           prompt>results\setenv
           prompt>nmake -f makefile.nt clean

           Unix
           ----
           prompt>. ./results/setenv.ksh
           prompt>make -f makefile.mk clean

    10) To use client certificate based authentication do the following:

      a) Place the client certificate into the LDAP directory service
         
      b) Place the private key file in $TUXDIR/udataobj/security/keys

      c) Edit the ubb file in the results directory as follows:

           - Under '*RESOURCES' change the 'SECURITY' setting
             from 'NONE' to 'USER_AUTH'
           - Under '*SERVERS' change the 'ISL' options by
             adding '-a' to 'CLOPT' parameter
           - Under '*SERVERS' add a server as follows
	     AUTHSVR  SRVGRP=SYS_GRP	SRVID=7  
	     
      d) Reload the tuxedo configuration file:

           prompt>tmshutdown -y
           prompt>tmloadcf -y ubb
           prompt>tmboot -y

      e) To use the C++ client:
      
            i)  Edit the simplec.cpp client program:

                - Add '#define TEST_SSL_AUTH' to the top of file
                - Update 'TUXCERTEMAIL' with the certificate email address
                - Update 'TUXCERTPASSWD' with the private key pass phrase

           ii)  Rebuild the C++ client:

                Windows NT
                ----------
                prompt>nmake -f makefile.nt

                Unix
                ----
                prompt>make -f makefile.mk

	   iii) Create a tpusr file

                tpusradd IIOPListener <use the same password as 
                the pass phrase u provided, when the runme script
                prompted>

                tpusradd <certificate email address>
                <Use the same password as in TUXCERTPASSWD>

            v) Run the C++ client as in step 8

      f) To use the remote Java client, run the client as in
         step 8 with the additional command line options:

           -DTUXCERT=YES -DTUX_EMAIL=<email> -DTUX_PASSWORD=<pass>

         where:

           <email> = the certificate email address
           <pass>  = the private key file pass phrase

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
    the university production sample demonstrates these features
    in $(TUXDIR)/samples/corba/university/production.

    To make SSL simpapp scalable, by

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


