rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
REM	Copyright (c) 1995 Novell, Inc.	
REM	  All Rights Reserved 	 

REM	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF 
REM	Novell, Inc.  
REM	The copyright notice above does not evidence any  
REM	actual or intended publication of such source code.

REM Copyright (c) 1995 Novell, Inc.
REM All rights reserved
REM ident	"@(#) samples/atmi/bankapp/nt/driver/makehelp.bat	$Revision: 1.4 $"

@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DRIVER.HPJ. >hlp\driver.hm
echo. >>hlp\driver.hm
echo // Commands (ID_* and IDM_*) >>hlp\driver.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\driver.hm
echo. >>hlp\driver.hm
echo // Prompts (IDP_*) >>hlp\driver.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\driver.hm
echo. >>hlp\driver.hm
echo // Resources (IDR_*) >>hlp\driver.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\driver.hm
echo. >>hlp\driver.hm
echo // Dialogs (IDD_*) >>hlp\driver.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\driver.hm
echo. >>hlp\driver.hm
echo // Frame Controls (IDW_*) >>hlp\driver.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\driver.hm
REM -- Make help for Project DRIVER

echo Building Win32 Help files
call hc31 driver.hpj
if exist windebug copy driver.hlp windebug
if exist winrel copy driver.hlp winrel
EndLocal
