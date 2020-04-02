rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@echo off
rem
rem Copyright (c) 1996 BEA Systems, Inc.
rem All rights reserved
rem
rem ident	"@(#) samples/atmi/bankapp/runslave.cmd	$Revision: 1.4 $"

rem set environment
echo set TUXDIR=%TUXDIR%> tmp
copy tmp+nt\bankvar bankvar.cmd
del tmp
call bankvar.cmd

rem run daemon
start bankappd
