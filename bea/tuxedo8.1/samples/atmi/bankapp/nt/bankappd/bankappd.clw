;	(c) 2003 BEA Systems, Inc. All Rights Reserved.
;	Copyright (c) 1995 Novell, Inc.	
;	  All Rights Reserved 	 

;	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF 
;	Novell, Inc.  
;	The copyright notice above does not evidence any  
;	actual or intended publication of such source code.

;Copyright (c) 1995 Novell, Inc.
;All rights reserved
;ident	"@(#) samples/atmi/bankapp/nt/bankappd/bankappd.clw	$Revision: 1.4 $"

; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTuxdirDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "bankappd.h"

ClassCount=4
Class1=CBankappdApp
Class2=CBankappdDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_BANKAPPD_DIALOG
Resource4=IDD_TUXDIR
Class4=CTuxdirDlg

[CLS:CBankappdApp]
Type=0
HeaderFile=bankappd.h
ImplementationFile=bankappd.cpp
Filter=N

[CLS:CBankappdDlg]
Type=0
HeaderFile=bankadlg.h
ImplementationFile=bankadlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATUS

[CLS:CAboutDlg]
Type=0
HeaderFile=bankadlg.h
ImplementationFile=bankadlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BANKAPPD_DIALOG]
Type=1
Class=CBankappdDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATUS,static,1342308353
Control3=IDC_STATIC,button,1342177287

[DLG:IDD_TUXDIR]
Type=1
Class=CTuxdirDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TUXDIR,edit,1350631552

[CLS:CTuxdirDlg]
Type=0
HeaderFile=bankadlg.h
ImplementationFile=bankadlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CTuxdirDlg

