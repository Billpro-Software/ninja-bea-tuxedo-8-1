REM	(c) 2003 BEA Systems, Inc. All Rights Reserved.
REM ident	"@(#) samples/atmi/CSIMPAPP/ws/windows/make.bat	$Revision: 1.4 $"
REM assume MicroFocus Cobol for Windows 
REM assume tuxedo is built for Windows (3.1), and LAN WorkPlace 
REM Winsock interface using MicroSoft C compiler (v7 or later)
REM
REM note we need to link with lcoboldw because we use DISPLAY
REM as our output interface (i.e. this is NOT a Windows App)
REM hence we can't use buildclt since it always links in lcobolw.
REM
REM replace \tuxedo with %TUXDIR% if needed, and make sure 
REM LIB env var is set to include %TUXDIR%\lib and
REM path name of directory where wlibsock.lib can be found
REM
set COBCPY=\tuxedo\cobinc
cobol csimpcl.cbl litlink;
link csimpcl+cblwinaf,,, wcobatmi+cobws+wtuxws+lcobol+lcoboldw+cobw+cobfp87w+wlibsock,csimpcl.def /nod/noe;
