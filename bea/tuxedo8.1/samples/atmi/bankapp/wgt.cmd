rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@echo off

rem	Copyright (c) 1995 Novell, Inc.	
rem	  All Rights Reserved 	 

rem	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF 
rem	Novell, Inc.  
rem	The copyright notice above does not evidence any  
rem	actual or intended publication of such source code.

rem	Copyright (c) 1995 Novell, Inc.
rem	All rights reserved
rem	ident	"@(#) samples/atmi/bankapp/wgt.cmd	$Revision: 1.4 $"

rem Customize WSENVFILE variable value as needed
rem set WSENVFILE=%TUXDIR%\bankapp\wsenv

gentran -n 1000 | wud -t 30 -e 10000
