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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/drivedlg.cpp	$Revision: 1.4 $"

// drivedlg.cpp : implementation file
//

#include "stdafx.h"
#include "driver.h"
#include "drivedlg.h"
#include "remote.h"
#include "misc.h"
#include "config.h"
#include "initmain.h"
#include "audit.h"
#include "cleanup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	
	// TODO: Add extra about dlg initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CDriverDlg dialog

CDriverDlg::CDriverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDriverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDriverDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDriverDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDriverDlg, CDialog)
	//{{AFX_MSG_MAP(CDriverDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_AUDIT, OnAudit)
	ON_BN_CLICKED(IDC_BOOT, OnBoot)
	ON_BN_CLICKED(IDC_CLEANUP, OnCleanup)
	ON_BN_CLICKED(IDC_GENTRANS, OnGentrans)
	ON_BN_CLICKED(IDC_INITIALIZE, OnInitialize)
	ON_BN_CLICKED(IDC_POPULATE, OnPopulate)
	ON_BN_CLICKED(IDC_SHUTDOWN, OnShutdown)
	ON_BN_CLICKED(IDC_TMADMIN, OnTmadmin)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_CLIENT, OnClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverDlg implementation

// Check prerequisite for Initialize
BOOL CDriverDlg::PrereqInitialize()
{
	if (!IsFileReadable("bankvar.mp1.cmd") && IsFileReadable("bankvar.mp*")){
		// Not on the master machine
		return FALSE;
	}

	// Check for initialisation
	if (!config.m_bValidConfig || !IsFileReadable("tuxconfig") ||
		!IsFileReadable("UBB"))
		return TRUE;

	if (!config.m_bValidConfig)
		return TRUE;

	if (!IsFileReadable("bankapp.mak*") || !IsFileReadable("bankvar.mp*"))
		return TRUE;

	// Check for propagation
	if (!IsPropagated())
			return TRUE;

	// Check for builds
	if (!IsBuilt(BI_BUILD))
		return TRUE;
	if (!IsBuilt(BI_BANKDL))
		return TRUE;
	if (!IsBuilt(BI_TLOG))
		return TRUE;

	// Master is initialised
	return FALSE;
}

BOOL CDriverDlg::PrereqBoot()
{
	if (!IsFileReadable("bankvar.mp1.cmd") && IsFileReadable("bankvar.mp*")){
		// Not on the master machine
		return FALSE;
	}

	if (IsActive("BBL"))
		return FALSE;

	if (!config.m_bValidConfig)
		return FALSE;

	if (!IsFileReadable("tuxconfig"))
		return FALSE;

	if (!IsFileReadable("bankdl1") || !IsFileReadable("TLOG") ||
	    !IsFileReadable("ACCT.exe"))
		return FALSE;

	if (!IsBuilt(BI_BANKDL) || !IsBuilt(BI_TLOG) || !IsBuilt(BI_BUILD))
		return FALSE;

	return TRUE;
}

BOOL CDriverDlg::PrereqShutdown()
{
	if (!IsFileReadable("bankvar.mp1.cmd") && IsFileReadable("bankvar.mp*")){
		// Not on the master machine
		return FALSE;
	}

	if (!IsActive("BBL"))
		return FALSE;

	return TRUE;
}

BOOL CDriverDlg::PrereqPopulate()
{
	if (!IsFileReadable("bankvar.mp1.cmd") && IsFileReadable("bankvar.mp*")){
		// Not on the master machine
		return FALSE;
	}

	if (config.m_timePopulate != 0)
		return FALSE;

	if (!IsActive("BBL"))
		return FALSE;

	return TRUE;
}

BOOL CDriverDlg::PrereqClient()
{
	if (!IsActive("BBL"))
		return FALSE;

	if (config.m_timePopulate == 0)
		return FALSE;

	return TRUE;
}

BOOL CDriverDlg::PrereqGentrans()
{
	return PrereqClient();
}

BOOL CDriverDlg::PrereqAudit()
{
	return PrereqClient();
}

BOOL CDriverDlg::PrereqTmadmin()
{
	if (!IsActive("BBL"))
		return FALSE;
	return TRUE;
}

BOOL CDriverDlg::PrereqCleanup()
{
	if (IsActive("BBL"))
		return FALSE;

	if (!IsAnyBuilt(BI_BANKDL) && !IsAnyBuilt(BI_TLOG) && !IsAnyBuilt(BI_BUILD) &&
	    !IsFileReadable("ULOG.*") && !IsFileReadable("bankvar.mp*")){
		return FALSE;
	}

	return TRUE;
}

// Set the button state according to the prerequisites
void CDriverDlg::CheckPrereq()
{
	CWait dlgWait;

	dlgWait.start((CString)"Checking application status");

	CWnd* wInitialize = GetDlgItem(IDC_INITIALIZE);
	BOOL bInitializeEnable = PrereqInitialize();
	wInitialize->EnableWindow(bInitializeEnable);

	CWnd* wBoot = GetDlgItem(IDC_BOOT);
	BOOL bBootEnable = PrereqBoot();
	wBoot->EnableWindow(bBootEnable);

	CWnd* wShutdown = GetDlgItem(IDC_SHUTDOWN);
	BOOL bShutdownEnable = PrereqShutdown();
	wShutdown->EnableWindow(bShutdownEnable);

	CWnd* wPopulate = GetDlgItem(IDC_POPULATE);
	BOOL bPopulateEnable = PrereqPopulate();
	wPopulate->EnableWindow(bPopulateEnable);

	CWnd* wClient = GetDlgItem(IDC_CLIENT);
	BOOL bClientEnable = PrereqClient();
	wClient->EnableWindow(bClientEnable);

	CWnd* wGentrans = GetDlgItem(IDC_GENTRANS);
	BOOL bGentransEnable = PrereqGentrans();
	wGentrans->EnableWindow(bGentransEnable);

	CWnd* wAudit = GetDlgItem(IDC_AUDIT);
	BOOL bAuditEnable = PrereqAudit();
	wAudit->EnableWindow(bAuditEnable);

	CWnd* wTmadmin = GetDlgItem(IDC_TMADMIN);
	BOOL bTmadminEnable = PrereqTmadmin();
	wTmadmin->EnableWindow(bTmadminEnable);

	CWnd* wCleanup = GetDlgItem(IDC_CLEANUP);
	BOOL bCleanupEnable = PrereqCleanup();
	wCleanup->EnableWindow(bCleanupEnable);

	if (bInitializeEnable)
		GotoDlgCtrl(wInitialize);
	else if (bBootEnable)
		GotoDlgCtrl(wBoot);
	else if (bShutdownEnable)
		GotoDlgCtrl(wShutdown);
	else if (bPopulateEnable)
		GotoDlgCtrl(wPopulate);
	else if (bClientEnable)
		GotoDlgCtrl(wClient);
	else if (bGentransEnable)
		GotoDlgCtrl(wGentrans);
	else if (bAuditEnable)
		GotoDlgCtrl(wAudit);
	else if (bTmadminEnable)
		GotoDlgCtrl(wTmadmin);
	else if (bCleanupEnable)
		GotoDlgCtrl(wCleanup);
	else
		CDialog::OnOK();

	dlgWait.stop();
}

/////////////////////////////////////////////////////////////////////////////
// CDriverDlg message handlers

BOOL CDriverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}
	
	CheckPrereq();

	// CheckPrereq sets the focus	
	return FALSE;
}

void CDriverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CDriverDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDriverDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDriverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDriverDlg::OnInitialize() 
{
	ShowWindow(SW_HIDE);
	CInitMain dlg;

	int nResponse = dlg.DoModal();

	CheckPrereq();
	ShowWindow(SW_SHOW);
}

void CDriverDlg::OnAudit() 
{
	ShowWindow(SW_HIDE);

	CDlgAudit dlg;

	int nResponse = dlg.DoModal();

	ShowWindow(SW_SHOW);
}

void CDriverDlg::OnBoot() 
{
	ShowWindow(SW_HIDE);

	// Start tlisten on each site
	int numsites = CountSites();

	if (numsites > 1){
		for (int i = 0 ; i < MAX_SITES ; i++){
			CSite* pSite = config.FindSite(i);
			if (!pSite)
				continue;
		
			pSite->StartTlisten();
		}
	}

	config.FindSite(0)->RunCommand((CString)"tmboot -y");
	
	CheckPrereq();

	ShowWindow(SW_SHOW);
}

void CDriverDlg::OnShutdown() 
{
	ShowWindow(SW_HIDE);

	config.FindSite(0)->RunCommand((CString)"tmshutdown -y");
	
	CheckPrereq();	

	ShowWindow(SW_SHOW);
}

void CDriverDlg::OnPopulate() 
{
	ShowWindow(SW_HIDE);

	if (Populate())
		config.m_timePopulate = time(0);
	else
		config.m_timePopulate = 0;

	CheckPrereq();

	ShowWindow(SW_SHOW);
}


void CDriverDlg::OnClient() 
{
	system("bankvar.mp1 & start bankappn");
}

void CDriverDlg::OnCleanup() 
{
	ShowWindow(SW_HIDE);

	CDlgCleanup dlg;

	int nResponse = dlg.DoModal();

	CheckPrereq();

	ShowWindow(SW_SHOW);
}

void CDriverDlg::OnGentrans() 
{
	ShowWindow(SW_HIDE);

	Gentrans();

	ShowWindow(SW_SHOW);
}

void CDriverDlg::OnTmadmin() 
{
	system("bankvar.mp1 & start tmadmin");

	CheckPrereq();
}

void CDriverDlg::OnHelp() 
{
	theApp.Help();
}

void CDriverDlg::OnOK() 
{
	if (!config.Store()){
		GotoDlgCtrl(GetDlgItem(IDC_INITIALIZE));
		return;
	}
	
	CDialog::OnOK();
}
