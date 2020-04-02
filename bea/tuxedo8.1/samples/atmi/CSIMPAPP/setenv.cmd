rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@echo off
rem
rem #ident	"@(#) samples/atmi/CSIMPAPP/setenv.cmd	$Revision: 1.5 $"

rem Remove the following lines if your COBOL compiler is already configured
rem properly to run from the command line
set COBOLBASE=<full path to COBOL directory>
set PATH=%COBOLBASE%\exedll;%PATH%
set LIB=%COBOLBASE%\lib;%LIB%
set COBOLBASE=

set TUXDIR=<full path of TUXEDO software>
call %TUXDIR%\tuxenv

set APPDIR=<full path of current directory>
set TUXCONFIG=%APPDIR%\tuxconfig
