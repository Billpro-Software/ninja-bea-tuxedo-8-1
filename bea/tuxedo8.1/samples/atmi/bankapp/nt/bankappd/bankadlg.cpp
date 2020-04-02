//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//	Copyright (c) 1995 Novell, Inc.	
//	  All Rights Reserved 	 	

//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	
//	Novell, Inc.                     			
//	The copyright notice above does not evidence any   	
//	actual or intended publication of such source code.	

// #ident	"@(#) samples/atmi/bankapp/nt/bankappd/bankadlg.cpp	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/bankappd/bankadlg.cpp	$Revision: 1.4 $";
#endif

// bankadlg.cpp : implementation file
//

#include "stdafx.h"
#include "bankappd.h"
#include "remote.h"
#include "misc.h"
#include "bankadlg.h"

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
// CBankappdDlg dialog

CBankappdDlg::CBankappdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBankappdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBankappdDlg)
	m_status = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pThread = 0;
}

void CBankappdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBankappdDlg)
	DDX_Text(pDX, IDC_STATUS, m_status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBankappdDlg, CDialog)
	//{{AFX_MSG_MAP(CBankappdDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankappdDlg message handlers

BOOL CBankappdDlg::OnInitDialog()
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
	

	m_pThread->ResumeThread();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBankappdDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBankappdDlg::OnPaint() 
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
HCURSOR CBankappdDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Update the status message
void CBankappdDlg::UpdateStatus(ConnectStatus cs)
{
	m_connectstatus = cs;
	switch(cs){
	case CS_WAIT_CONNECT:
		m_status = "Waiting for connection";
		break;
	case CS_CONNECTED:
		m_status = "Connected";
		break;
	case CS_RECV_FILE:
		m_status = "Receiving a file";
		break;
	case CS_RUNNING_COMMAND:
		m_status = "Running a command";
		break;
	case CS_REMOVING_FILES:
		m_status = "Removing files";
		break;
	case CS_KILL_TLISTEN:
		m_status = "Killing tlisten";
		break;
	case CS_CLEAN_IPC:
		m_status = "Cleaning IPC";
		break;
	default:
		m_status = "Unknown status";
		break;
	}

	SetDlgItemText(IDC_STATUS, m_status);
}
/////////////////////////////////////////////////////////////////////////////
// CTuxdirDlg dialog


CTuxdirDlg::CTuxdirDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTuxdirDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTuxdirDlg)
	m_tuxdir = _T("");
	//}}AFX_DATA_INIT
}


void CTuxdirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTuxdirDlg)
	DDX_Text(pDX, IDC_TUXDIR, m_tuxdir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTuxdirDlg, CDialog)
	//{{AFX_MSG_MAP(CTuxdirDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTuxdirDlg message handlers

void CTuxdirDlg::OnOK() 
{
	UpdateData(TRUE);

	if (m_tuxdir.IsEmpty()){
		Message("Must specify TUXDIR");
		GotoDlgCtrl(GetDlgItem(IDC_TUXDIR));
		return;
	}

	if (!IsFullPath(m_tuxdir)){
		Message("%s is not a full pathname",
			(LPCSTR)m_tuxdir);
		GotoDlgCtrl(GetDlgItem(IDC_TUXDIR));
		return;
	}

	if (!IsDirectory(m_tuxdir)){
		Message("%s is not a valid directory",
			(LPCSTR)m_tuxdir);
		GotoDlgCtrl(GetDlgItem(IDC_TUXDIR));
		return;
	}

	CDialog::OnOK();
}

BOOL CTuxdirDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GotoDlgCtrl(GetDlgItem(IDC_TUXDIR));
	return FALSE;
}
