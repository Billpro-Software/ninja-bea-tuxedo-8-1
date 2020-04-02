rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@echo off
rem
rem Copyright (c) 1996 BEA Systems, Inc.
rem All rights reserved
rem
rem ident	"@(#) samples/atmi/bankapp/runmast.cmd	$Revision: 1.4 $"

rem set environment
copy nt\bankvar  bankvar.cmd
call bankvar.cmd

rem run driver
start driver

