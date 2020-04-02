;
;	(c) 2003 BEA Systems, Inc. All Rights Reserved.
; Copyright (c) 1995, 1996 BEA Systems, Inc.
; All Rights Reserved
;
; THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF
; BEA Systems, Inc.
; The copyright notice above does not evidence any
; actual or intended publication of such source code.
;
;
;
; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgCleanRuntime
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "driver.h"

ClassCount=20
Class1=CDriverApp
Class2=CDriverDlg
Class3=CAboutDlg

ResourceCount=20
Resource1=IDD_CLEAN_RUNTIME
Resource2=IDR_MAINFRAME
Resource3=IDD_IPCKEY
Resource4=IDD_INIT_MAIN
Class4=CInitMain
Resource5=IDD_INIT_CONFIG
Class5=CInitConfig
Resource6=IDD_INIT_MODE
Class6=CInitMode
Resource7=IDD_INIT_SITES
Class7=CConfSetup
Resource8=IDD_SITE_ADD
Class8=CSiteAdd
Class9=CSiteRemove
Resource9=IDD_SITE_REMOVE
Class10=CSiteDesc
Resource10=IDD_DRIVER_DIALOG
Class11=CConfIpckey
Resource11=IDD_SITE_INFO
Class12=CCommandOut
Resource12=IDD_RUN_COMMAND
Class13=CInitRuntime
Resource13=IDD_INIT_RUNTIME
Class14=CDlgUdOut
Resource14=IDD_RUN_UD
Resource15=IDD_TRANSACTION_COUNT
Class15=CTransCount
Resource16=IDD_WAIT
Class16=CdlgWait
Class17=CDlgAudit
Resource17=IDD_AUDIT
Class18=CDlgBranch
Resource18=IDD_SELECT_BRANCH
Resource19=IDD_CLEANUP
Class19=CDlgCleanup
Class20=CDlgCleanRuntime
Resource20=IDD_ABOUTBOX

[CLS:CDriverApp]
Type=0
HeaderFile=driver.h
ImplementationFile=driver.cpp
Filter=N

[CLS:CDriverDlg]
Type=0
HeaderFile=drivedlg.h
ImplementationFile=drivedlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CLIENT

[CLS:CAboutDlg]
Type=0
HeaderFile=drivedlg.h
ImplementationFile=drivedlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DRIVER_DIALOG]
Type=1
Class=CDriverDlg
ControlCount=11
Control1=IDC_INITIALIZE,button,1342242816
Control2=IDC_BOOT,button,1342242816
Control3=IDC_SHUTDOWN,button,1342242816
Control4=IDC_POPULATE,button,1342242816
Control5=IDC_CLIENT,button,1342242816
Control6=IDC_GENTRANS,button,1342242816
Control7=IDC_AUDIT,button,1342242816
Control8=IDC_TMADMIN,button,1342242816
Control9=IDC_CLEANUP,button,1342242816
Control10=IDOK,button,1342242816
Control11=ID_HELP,button,1342242816

[DLG:IDD_INIT_MAIN]
Type=1
Class=CInitMain
ControlCount=5
Control1=IDOK,button,1342242817
Control2=ID_HELP,button,1342242816
Control3=IDC_CONFIGURATION,button,1342242816
Control4=IDC_PROPAGATION,button,1342242816
Control5=IDC_RUNTIME,button,1342242816

[CLS:CInitMain]
Type=0
HeaderFile=initmain.h
ImplementationFile=initmain.cpp
Filter=D
VirtualFilter=dWC
LastObject=CInitMain

[DLG:IDD_INIT_CONFIG]
Type=1
Class=CInitConfig
ControlCount=4
Control1=IDOK,button,1342242817
Control2=ID_HELP,button,1342242816
Control3=IDC_UBBCONFIG,button,1342242816
Control4=IDC_TUXCONFIG,button,1342242816

[CLS:CInitConfig]
Type=0
HeaderFile=initconf.h
ImplementationFile=initconf.cpp
Filter=D
VirtualFilter=dWC
LastObject=ID_HELP

[DLG:IDD_INIT_MODE]
Type=1
Class=CInitMode
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_VERBOSE,button,1342177289
Control5=IDC_TERSE,button,1342177289

[CLS:CInitMode]
Type=0
HeaderFile=initconf.h
ImplementationFile=initconf.cpp
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_INIT_SITES]
Type=1
Class=CConfSetup
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ADD,button,1342242816
Control4=IDC_REMOVE,button,1342242816
Control5=IDC_SITE1,button,1476460544
Control6=IDC_SITE2,button,1476460544
Control7=IDC_SITE3,button,1476460544
Control8=IDC_SITE4,button,1476460544
Control9=IDC_SITE5,button,1476460544
Control10=IDC_SITE6,button,1476460544
Control11=IDC_SITE7,button,1476460544
Control12=IDC_SITE8,button,1476460544
Control13=IDC_SITE9,button,1476460544
Control14=IDC_SITE10,button,1476460544
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287

[CLS:CConfSetup]
Type=0
HeaderFile=initconf.h
ImplementationFile=initconf.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_SITE10

[DLG:IDD_SITE_ADD]
Type=1
Class=CSiteAdd
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SITE_NAME,edit,1350631552
Control5=IDC_OSNT,button,1342177289
Control6=IDC_OSUNIX,button,1342177289

[CLS:CSiteAdd]
Type=0
HeaderFile=initconf.h
ImplementationFile=initconf.cpp
Filter=D
VirtualFilter=dWC
LastObject=CSiteAdd

[DLG:IDD_SITE_REMOVE]
Type=1
Class=CSiteRemove
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SITE_LIST,listbox,1352728843
Control4=IDC_STATIC,static,1342308352

[CLS:CSiteRemove]
Type=0
HeaderFile=initconf.h
ImplementationFile=initconf.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CSiteDesc]
Type=0
HeaderFile=initconf.h
ImplementationFile=initconf.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_APPDIR

[DLG:IDD_SITE_INFO]
Type=1
Class=CSiteDesc
ControlCount=24
Control1=IDC_ROOTDIR,edit,1350631552
Control2=IDC_HOME,edit,1350631552
Control3=IDC_APPDIR,edit,1350631552
Control4=IDC_TYPE,edit,1350631552
Control5=IDC_NET_DEVICE,edit,1350631552
Control6=IDC_NET_ADDRESS,edit,1350631552
Control7=IDC_BRIDGE,edit,1350631552
Control8=IDC_TLISTEN,edit,1350631552
Control9=IDC_UID,edit,1350631552
Control10=IDC_GID,edit,1350631552
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_NET_DEVICE_TEXT,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_UID_TEXT,static,1342308352
Control24=IDC_GID_TEXT,static,1342308352

[DLG:IDD_IPCKEY]
Type=1
Class=CConfIpckey
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_IPCKEY,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:CConfIpckey]
Type=0
HeaderFile=initconf.h
ImplementationFile=initconf.cpp
Filter=D
VirtualFilter=dWC
LastObject=CConfIpckey

[DLG:IDD_RUN_COMMAND]
Type=1
Class=CCommandOut
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMMAND_OUTPUT,edit,1353780292

[CLS:CCommandOut]
Type=0
HeaderFile=misc.h
ImplementationFile=misc.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMMAND_OUTPUT

[DLG:IDD_INIT_RUNTIME]
Type=1
Class=CInitRuntime
ControlCount=5
Control1=IDC_BUILD,button,1342242816
Control2=IDC_BANKDL,button,1342242816
Control3=IDC_TLOG,button,1342242816
Control4=IDOK,button,1342242817
Control5=ID_HELP,button,1342242816

[CLS:CInitRuntime]
Type=0
HeaderFile=initrun.h
ImplementationFile=initrun.cpp
Filter=D
VirtualFilter=dWC
LastObject=CInitRuntime

[DLG:IDD_RUN_UD]
Type=1
Class=CDlgUdOut
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_PERCENT,edit,1350633600

[CLS:CDlgUdOut]
Type=0
HeaderFile=misc.h
ImplementationFile=misc.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgUdOut

[DLG:IDD_TRANSACTION_COUNT]
Type=1
Class=CTransCount
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TRANSACTION_COUNT,edit,1350631552

[CLS:CTransCount]
Type=0
HeaderFile=misc.h
ImplementationFile=misc.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_TRANSACTION_COUNT

[DLG:IDD_WAIT]
Type=1
Class=CdlgWait
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_WAIT_REASON,static,1342308353

[CLS:CdlgWait]
Type=0
HeaderFile=misc.h
ImplementationFile=misc.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_WAIT_REASON

[DLG:IDD_AUDIT]
Type=1
Class=CDlgAudit
ControlCount=5
Control1=IDC_AUDIT_ACCOUNTS,button,1342242816
Control2=IDC_AUDIT_TELLERS,button,1342242816
Control3=IDC_CONV_AUDIT,button,1342242816
Control4=IDOK,button,1342242817
Control5=ID_HELP,button,1342242816

[CLS:CDlgAudit]
Type=0
HeaderFile=audit.h
ImplementationFile=audit.cpp
Filter=D
VirtualFilter=dWC
LastObject=ID_HELP

[DLG:IDD_SELECT_BRANCH]
Type=1
Class=CDlgBranch
ControlCount=5
Control1=IDC_AUDIT_ALL,button,1342177289
Control2=IDC_AUDIT_ONE,button,1342177289
Control3=IDC_BRANCH,edit,1350631552
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816

[CLS:CDlgBranch]
Type=0
HeaderFile=audit.h
ImplementationFile=audit.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BRANCH

[DLG:IDD_CLEANUP]
Type=1
Class=CDlgCleanup
ControlCount=8
Control1=IDC_CLEAN_CONFIGURATION,button,1342242816
Control2=IDC_CLEAN_SERVERS,button,1342242816
Control3=IDC_CLEAN_RUNTIME,button,1342242816
Control4=IDC_CLEAN_TLISTEN,button,1342242816
Control5=IDC_CLEAN_IPC,button,1342242816
Control6=IDC_CLEAN_ALL,button,1342242816
Control7=IDOK,button,1342242817
Control8=ID_HELP,button,1342242816

[CLS:CDlgCleanup]
Type=0
HeaderFile=cleanup.h
ImplementationFile=cleanup.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CLEAN_TLISTEN

[DLG:IDD_CLEAN_RUNTIME]
Type=1
Class=CDlgCleanRuntime
ControlCount=6
Control1=IDOK,button,1342242817
Control2=ID_HELP,button,1342242816
Control3=IDC_CLEAN_BANKDLS,button,1342242816
Control4=IDC_CLEAN_TLOGS,button,1342242816
Control5=IDC_CLEAN_USERLOGS,button,1342242816
Control6=IDC_CLEAN_ALL,button,1342242816

[CLS:CDlgCleanRuntime]
Type=0
HeaderFile=cleanup.h
ImplementationFile=cleanup.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CLEAN_ALL

