//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
//	Copyright (c) 1995, 1996 BEA Systems, Inc.
//	All Rights Reserved
//
//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF
//	BEA Systems, Inc.
//	The copyright notice above does not evidence any
//	actual or intended publication of such source code.
//

//

// #ident	"@(#) samples/atmi/bankapp/nt/driver/cleanup.cpp	$Revision: 1.4 $"

// cleanup.cpp : implementation file
//

#include "stdafx.h"
#include "driver.h"
#include "remote.h"
#include "config.h"
#include "misc.h"
#include "cleanup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanup dialog


CDlgCleanup::CDlgCleanup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCleanup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCleanup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCleanup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCleanup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCleanup, CDialog)
	//{{AFX_MSG_MAP(CDlgCleanup)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_CLEAN_ALL, OnCleanAll)
	ON_BN_CLICKED(IDC_CLEAN_CONFIGURATION, OnCleanConfiguration)
	ON_BN_CLICKED(IDC_CLEAN_IPC, OnCleanIpc)
	ON_BN_CLICKED(IDC_CLEAN_RUNTIME, OnCleanRuntime)
	ON_BN_CLICKED(IDC_CLEAN_SERVERS, OnCleanServers)
	ON_BN_CLICKED(IDC_CLEAN_TLISTEN, OnCleanTlisten)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgCleanup::CheckPrereq()
{
	CWait dlgWait;

	dlgWait.start((CString)"Checking application status");

	CWnd* wCleanAll = GetDlgItem(IDC_CLEAN_ALL);
	BOOL bCleanAllEnable = PrereqCleanAll();
	wCleanAll->EnableWindow(bCleanAllEnable);

	CWnd* wCleanConfiguration = GetDlgItem(IDC_CLEAN_CONFIGURATION);
	BOOL bCleanConfigurationEnable = PrereqCleanConfiguration();
	wCleanConfiguration->EnableWindow(bCleanConfigurationEnable);

	CWnd* wCleanIpc = GetDlgItem(IDC_CLEAN_IPC);
	BOOL bCleanIpcEnable = PrereqCleanIpc();
	wCleanIpc->EnableWindow(bCleanIpcEnable);

	CWnd* wCleanRuntime = GetDlgItem(IDC_CLEAN_RUNTIME);
	BOOL bCleanRuntimeEnable = PrereqCleanRuntime();
	wCleanRuntime->EnableWindow(bCleanRuntimeEnable);

	CWnd* wCleanServers = GetDlgItem(IDC_CLEAN_SERVERS);
	BOOL bCleanServersEnable = PrereqCleanServers();
	wCleanServers->EnableWindow(bCleanServersEnable);

	CWnd* wCleanTlisten = GetDlgItem(IDC_CLEAN_TLISTEN);
	BOOL bCleanTlistenEnable = PrereqCleanTlisten();
	wCleanTlisten->EnableWindow(bCleanTlistenEnable);

	if (bCleanConfigurationEnable)
		GotoDlgCtrl(wCleanConfiguration);
	else if (bCleanServersEnable)
		GotoDlgCtrl(wCleanServers);
	else if (bCleanRuntimeEnable)
		GotoDlgCtrl(wCleanRuntime);
	else if (bCleanTlistenEnable)
		GotoDlgCtrl(wCleanTlisten);
	else if (bCleanIpcEnable)
		GotoDlgCtrl(wCleanIpc);
	else if (bCleanAllEnable)
		GotoDlgCtrl(wCleanAll);
	else
		CDialog::OnOK();
	
	dlgWait.stop();
}

BOOL CDlgCleanup::PrereqCleanAll()
{
	if (IsAnyBuilt(BI_BUILD) || IsAnyBuilt(BI_TLOG) || IsAnyBuilt(BI_BANKDL))
		return TRUE;

	if (IsFileReadable("bankvar.mp*") || IsFileReadable("ULOG.*"))
		return TRUE;

	return FALSE;
}

BOOL CDlgCleanup::PrereqCleanConfiguration()
{
	// Check if there is anything to clean
	if (!IsFileReadable("tuxconfig") && !IsFileReadable("UBB") &&
		!IsFileReadable("bankvar.mp*") && !IsFileReadable("bankapp.mak*")){
		return FALSE;
	}

	// Neither tlog nor bankdl can be there.
	// Nothing can be built either, because the bankvar files are needed.
	if (IsAnyBuilt(BI_TLOG) || IsAnyBuilt(BI_BANKDL) || IsAnyBuilt(BI_BUILD))
		return FALSE;

	return TRUE;
}

BOOL CDlgCleanup::PrereqCleanIpc()
{
	return IsFileReadable("bankvar.mp1*");
}

BOOL CDlgCleanup::PrereqCleanRuntime()
{
	if (IsFileReadable("ULOG.*") || IsAnyBuilt(BI_TLOG) || IsAnyBuilt(BI_BANKDL))
		return TRUE;
	return FALSE;
}

BOOL CDlgCleanup::PrereqCleanServers()
{
	return IsAnyBuilt(BI_BUILD);
}

BOOL CDlgCleanup::PrereqCleanTlisten()
{
	if (CountSites() > 1)
		return TRUE;
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanup message handlers

BOOL CDlgCleanup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckPrereq();

	return FALSE;
}

void CDlgCleanup::OnHelp() 
{
	theApp.Help();
}

void CDlgCleanup::OnCleanAll() 
{
	CleanAll();
	CheckPrereq();
}

void CDlgCleanup::OnCleanConfiguration() 
{
	CleanConfiguration();
	CheckPrereq();
}

void CDlgCleanup::OnCleanIpc() 
{
	CleanIpc();
	CheckPrereq();
}

void CDlgCleanup::OnCleanRuntime() 
{
	ShowWindow(SW_HIDE);

	CDlgCleanRuntime dlg;

	int nResponse = dlg.DoModal();

	CheckPrereq();

	ShowWindow(SW_SHOW);
}

void CDlgCleanup::OnCleanServers() 
{
	CleanServers();
	CheckPrereq();
}

void CDlgCleanup::OnCleanTlisten() 
{
	CleanTlisten();
	CheckPrereq();
}

void CDlgCleanup::CleanAll() 
{
	CDlgCleanRuntime dlg;
	
	dlg.CleanAll();
	
	CleanIpc();
	CleanTlisten();
	CleanServers();
	CleanConfiguration();	
}

void CDlgCleanup::CleanConfiguration() 
{
	::RemoveFiles("tuxconfig");
	::RemoveFiles("UBB");	
	::RemoveFiles("bankvar.mp*");
	::RemoveFiles("bankapp.mak*");

	config.m_bValidConfig = FALSE;
	config.MarkForRemove();
}

void CDlgCleanup::CleanIpc() 
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		pSite->CleanIpc();
	}
}

void CDlgCleanup::CleanServers() 
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		pSite->Clean();
	}
}

void CDlgCleanup::CleanTlisten() 
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		pSite->KillTlisten();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanRuntime dialog


CDlgCleanRuntime::CDlgCleanRuntime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCleanRuntime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCleanRuntime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCleanRuntime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCleanRuntime)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCleanRuntime, CDialog)
	//{{AFX_MSG_MAP(CDlgCleanRuntime)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_CLEAN_BANKDLS, OnCleanBankdls)
	ON_BN_CLICKED(IDC_CLEAN_TLOGS, OnCleanTlogs)
	ON_BN_CLICKED(IDC_CLEAN_USERLOGS, OnCleanUserlogs)
	ON_BN_CLICKED(IDC_CLEAN_ALL, OnCleanAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgCleanRuntime::CheckPrereq()
{
	CWait dlgWait;

	dlgWait.start((CString)"Checking runtime status");

	CWnd* wCleanBankdls = GetDlgItem(IDC_CLEAN_BANKDLS);
	BOOL bCleanBankdlsEnable = PrereqCleanBankdls();
	wCleanBankdls->EnableWindow(bCleanBankdlsEnable);

	CWnd* wCleanTlogs = GetDlgItem(IDC_CLEAN_TLOGS);
	BOOL bCleanTlogsEnable = PrereqCleanTlogs();
	wCleanTlogs->EnableWindow(bCleanTlogsEnable);

	CWnd* wCleanUserlogs = GetDlgItem(IDC_CLEAN_USERLOGS);
	BOOL bCleanUserlogsEnable = PrereqCleanUserlogs();
	wCleanUserlogs->EnableWindow(bCleanUserlogsEnable);

	CWnd* wCleanAll = GetDlgItem(IDC_CLEAN_ALL);
	BOOL bCleanAllEnable = PrereqCleanAll();
	wCleanAll->EnableWindow(bCleanAllEnable);

	if (bCleanBankdlsEnable)
		GotoDlgCtrl(wCleanBankdls);
	else if (bCleanTlogsEnable)
		GotoDlgCtrl(wCleanTlogs);
	else if (bCleanUserlogsEnable)
		GotoDlgCtrl(wCleanUserlogs);
	else if (bCleanAllEnable)
		GotoDlgCtrl(wCleanAll);
	else
		CDialog::OnOK();
	
	dlgWait.stop();
}

BOOL CDlgCleanRuntime::PrereqCleanBankdls()
{
	return IsAnyBuilt(BI_BANKDL);
}

BOOL CDlgCleanRuntime::PrereqCleanTlogs()
{
	return IsAnyBuilt(BI_TLOG);
}

BOOL CDlgCleanRuntime::PrereqCleanUserlogs()
{
	return IsFileReadable("ULOG.*");
}

BOOL CDlgCleanRuntime::PrereqCleanAll()
{
	return IsAnyBuilt(BI_BANKDL) || IsAnyBuilt(BI_TLOG) || IsFileReadable("ULOG.*");
}

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanRuntime message handlers

BOOL CDlgCleanRuntime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckPrereq();

	return FALSE;
}

void CDlgCleanRuntime::OnHelp() 
{
	theApp.Help();
}

void CDlgCleanRuntime::OnCleanBankdls() 
{
	CleanBankdls();
	CheckPrereq();
}

void CDlgCleanRuntime::OnCleanTlogs() 
{
	CleanTlogs();
	CheckPrereq();
}

void CDlgCleanRuntime::OnCleanUserlogs() 
{
	CleanUserlogs();
	CheckPrereq();
}

void CDlgCleanRuntime::OnCleanAll() 
{
	CleanAll();
	CheckPrereq();
}

void CDlgCleanRuntime::CleanBankdls() 
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		pSite->CleanBank();
	}
}

void CDlgCleanRuntime::CleanTlogs() 
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		pSite->CleanTlog();
	}
}

void CDlgCleanRuntime::CleanUserlogs() 
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		pSite->CleanUserlogs();
	}
}

void CDlgCleanRuntime::CleanAll() 
{
	CleanBankdls();
	CleanTlogs();
	CleanUserlogs();
}
