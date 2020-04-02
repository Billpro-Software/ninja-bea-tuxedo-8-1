rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
rem	#ident	"@(#) samples/atmi/bankapp/cleandb.cmd	$Revision: 1.4 $"
set DIPCKEY1=61913
set DIPCKEY2=62917
set DIPCKEY3=61915
rem 
set FSCONFIG=%APPDIR%\bankdl1
set DIPCKEY=%DIPCKEY1%
rmskill
rem
set FSCONFIG=%APPDIR%\bankdl2
set DIPCKEY=%DIPCKEY2%
rmskill
rem
set FSCONFIG=%APPDIR%\bankdl3
set DIPCKEY=%DIPCKEY3%
rmskill
