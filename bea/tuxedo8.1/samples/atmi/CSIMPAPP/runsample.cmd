rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@echo off
rem
rem Copyright (c) 1996 BEA Systems
rem All rights reserved
rem
rem #ident	"@(#) samples/atmi/CSIMPAPP/runsample.cmd	$Revision: 1.5 $"

rem set the environment
call setenv

rem build the client and server
nmake -e -f csimpapp.nt

rem create the tuxconfig file
tmloadcf -y UBBCSIMPLE.nt

rem boot the application
tmboot -y

rem run the client
CSIMPCL "hello world"

rem shutdown the application
tmshutdown -y

rem remove the client, server and utilities
nmake -f Makefile.nt clobber

rem remove all files created
del tuxconfig stdout stderr ULOG*
