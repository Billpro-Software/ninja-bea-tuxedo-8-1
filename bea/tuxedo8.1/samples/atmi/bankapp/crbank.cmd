rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
rem	#ident	"@(#) samples/atmi/bankapp/crbank.cmd	$Revision: 1.4 $"
set DIPCKEY1=61913
set DIPCKEY2=62917
set DIPCKEY3=61915
rem 
set FSCONFIG=%APPDIR%\bankdl1
set DIPCKEY=%DIPCKEY1%
crbankdb
rem
set FSCONFIG=%APPDIR%\bankdl2
set DIPCKEY=%DIPCKEY2%
crbankdb
rem
set FSCONFIG=%APPDIR%\bankdl3
set DIPCKEY=%DIPCKEY3%
crbankdb
