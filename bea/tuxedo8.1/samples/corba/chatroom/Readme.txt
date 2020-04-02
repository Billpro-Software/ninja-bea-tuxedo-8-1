
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
    Chatroom Read Me
    ~~~~~~~~ ~~~~ ~~

    The "chatroom" sample application contains a simple Tuxedo C++
    client & server which implements a "chat" room. Clients
    specify a chat room to connect to and receive callbacks
    containing the comments of other connected clients.

    These instructions will help you run this sample.

    1) Make sure that the directory that you installed Tuxedo under
       is set in the environment variable "TUXDIR"

    2) Make a copy of the chatroom directory.

    3) cd to the copy.  If you're on Unix, start a ksh.

    4) Change the permissions on all the files to give them
       read-access.

    5) For Windows NT, make sure "nmake" is in your path.
       For Unix,       make sure "make"  is in your path.

    6) Build the sample by typing:

           Windows NT
           ----------
           prompt>ChatSetup.cmd

           Unix
           ----
           prompt>. ./ChatSetup.ksh

       This will build the sample and print out a message
       directing you to issue a "tmboot -y" command to
       boot the application.

    7) Run a chat client by typing:

           Windows NT
           ----------
	   prompt>Admin\setenv.cmd
           prompt>ChatClient <chatroom name>

           Unix
           ----
	   prompt>. ./Admin/setenv.ksh
           prompt>ChatClient <chatroom name>

       where <chatroom name> is the name of a chat room to
       which you would like to connect.  You will be
       prompted for a handle to identify yourself.  Type
       the '\' character to exit.  

       In order to see the chat in action, a second chat
       client should also be started up using the same
       chat room name.

       Note that ChatClientW is a version of ChatClient
	   which uses the callback convenience wrapper class.

    8) To restore the directory to its original state:

           Windows NT
           ----------
           prompt>Admin\setenv.cmd
           prompt>nmake -f ChatRoom.nt superclean

           Unix
           ----
           prompt>. ./Admin/setenv.ksh
           prompt>make -f ChatRoom.mk superclean
