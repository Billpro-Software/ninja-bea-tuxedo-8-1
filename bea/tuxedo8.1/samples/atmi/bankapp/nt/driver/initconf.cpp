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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/initconf.cpp	$Revision: 1.4 $"

// initconf.cpp : implementation file
//

#include "stdafx.h"
#include "driver.h"
#include "remote.h"
#include "config.h"
#include "initconf.h"
#include "misc.h"
#include <winsock.h>
#include <Uunix.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitConfig dialog


CInitConfig::CInitConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CInitConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInitConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitConfig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitConfig, CDialog)
	//{{AFX_MSG_MAP(CInitConfig)
	ON_BN_CLICKED(IDC_UBBCONFIG, OnUbbconfig)
	ON_BN_CLICKED(IDC_TUXCONFIG, OnTuxconfig)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitConfig implementation

BOOL CInitConfig::PrereqUbbconfig()
{
	return !config.m_bValidConfig || !IsFileReadable("UBB");
}

BOOL CInitConfig::PrereqTuxconfig()
{
	return config.m_bValidConfig &&
		IsFileReadable("UBB") && !IsFileReadable("tuxconfig");
}

void CInitConfig::CheckPrereq()
{
	CWait dlgWait;

	dlgWait.start((CString)"Checking configuration status");

	CWnd* wButton;
	BOOL bUbbEnable;
	BOOL bTuxconfigEnable;

	wButton = GetDlgItem(IDC_UBBCONFIG);
	bUbbEnable = PrereqUbbconfig();
	wButton->EnableWindow(bUbbEnable);

	wButton = GetDlgItem(IDC_TUXCONFIG);
	bTuxconfigEnable = PrereqTuxconfig();
	wButton->EnableWindow(bTuxconfigEnable);

	if (bUbbEnable)	
		GotoDlgCtrl(GetDlgItem(IDC_UBBCONFIG));
	else if (bTuxconfigEnable)
		GotoDlgCtrl(GetDlgItem(IDC_TUXCONFIG));
	else
		CDialog::OnOK();
	
	dlgWait.stop();
}

/////////////////////////////////////////////////////////////////////////////
// CInitConfig message handlers

BOOL CInitConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckPrereq();
	
	// CheckPrereq sets the focus
	return FALSE;
}

void CInitConfig::OnUbbconfig() 
{
	ShowWindow(SW_HIDE);

	if (Setup()){
		SetLocalFiles();
		int response = MessageBox("Would you like to generate the tuxconfig file at this time?",
			"UBBCONFIG file generation sucessful", MB_YESNO);
		if (response == IDYES){
			OnTuxconfig();
			ShowWindow(SW_SHOW);
			return;
		}
	} else {
		Message("UBBCONFIG file generation failed\nconfig related files removed");
		::RemoveFiles("UBB");
		::RemoveFiles("bankapp.mak*");
		::RemoveFiles("bankvar.mp*");
	}

	CheckPrereq();

	ShowWindow(SW_SHOW);
}

void CInitConfig::OnTuxconfig() 
{
	ShowWindow(SW_HIDE);

	::RemoveFiles("tuxconfig");
	config.FindSite(0)->RunCommand((CString)"tmloadcf -y UBB");

	// TODO: CHKSYS

	CheckPrereq();	

	ShowWindow(SW_SHOW);
}

void CInitConfig::OnHelp() 
{
	theApp.Help();
}
/////////////////////////////////////////////////////////////////////////////
// CInitMode dialog


CInitMode::CInitMode(CWnd* pParent /*=NULL*/)
	: CDialog(CInitMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitMode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	IdChecked = IDC_VERBOSE;
}


void CInitMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitMode)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitMode, CDialog)
	//{{AFX_MSG_MAP(CInitMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInitMode message handlers

BOOL CInitMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set default to verbose
	CheckRadioButton(IDC_VERBOSE, IDC_TERSE, IDC_VERBOSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInitMode::OnOK() 
{
	IdChecked = GetCheckedRadioButton(IDC_VERBOSE, IDC_TERSE);
	
	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CConfSetup dialog

static int setup_items[] = {
	IDC_SITE1, 
	IDC_SITE2, 
	IDC_SITE3, 
	IDC_SITE4, 
	IDC_SITE5, 
	IDC_SITE6, 
	IDC_SITE7, 
	IDC_SITE8, 
	IDC_SITE9, 
	IDC_SITE10
};
 
CConfSetup::CConfSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CConfSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfSetup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfSetup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfSetup, CDialog)
	//{{AFX_MSG_MAP(CConfSetup)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_SITE1, OnSite1)
	ON_BN_CLICKED(IDC_SITE2, OnSite2)
	ON_BN_CLICKED(IDC_SITE3, OnSite3)
	ON_BN_CLICKED(IDC_SITE4, OnSite4)
	ON_BN_CLICKED(IDC_SITE5, OnSite5)
	ON_BN_CLICKED(IDC_SITE6, OnSite6)
	ON_BN_CLICKED(IDC_SITE7, OnSite7)
	ON_BN_CLICKED(IDC_SITE8, OnSite8)
	ON_BN_CLICKED(IDC_SITE9, OnSite9)
	ON_BN_CLICKED(IDC_SITE10, OnSite10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfSetup implementation
void CConfSetup::CheckButtons()
{
	CWnd* wButton;

	for (int i = 0 ; i < MAX_SITES ; i++){
		wButton = GetDlgItem(setup_items[i]);
		CSite* pSite = config.FindSite(i);
		if (pSite){
			wButton->EnableWindow(TRUE);
			wButton->SetWindowText(pSite->m_name);
		} else {
			char buf[10];
			wButton->EnableWindow(FALSE);
			if (i < 9){
				sprintf(buf, "Site&%d", i + 1);
				wButton->SetWindowText(buf);
			} else {
				wButton->SetWindowText("Site1&0");
			}
		}
	}
}

void CConfSetup::OnSite(CSite* pSite)
{
	ShowWindow(SW_HIDE);

	CSiteDesc dlg;

	dlg.m_pSite = pSite;

	int response = dlg.DoModal();

	ShowWindow(SW_SHOW);
}

/////////////////////////////////////////////////////////////////////////////
// CConfSetup message handlers

BOOL CConfSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Site1 is always the local site, and is NT
	char buf[100];
	char name[32];
	DWORD length = sizeof name;

	CSite* pSite = config.FindSite(0);

	if (!pSite){
		pSite  = new CNTLocalSite;
		config.SetSite(0, pSite);
		// Fill in name
		GetComputerName(name, &length);
		pSite->m_name = name;
		pSite->m_bRemote = FALSE;
		pSite->m_nSite = 1;

		// Fill in rootdir
		char* rootdir = tuxgetenv("TUXDIR");
		if (rootdir){
			pSite->m_rootdir = rootdir;
		}

		// Fill in homedir
		char* homedrive = tuxgetenv("HOMEDRIVE");
		char* homedir = tuxgetenv("HOMEPATH");

		if (!homedrive && !homedir){
			GetWindowsDirectory(buf, sizeof buf);
			pSite->m_home = buf;
		} else if (!homedrive)
			pSite->m_home = homedir;
		else if (!homedir){
			sprintf(buf, "%s\\", homedrive);
			pSite->m_home = buf;
		} else {
			sprintf(buf, "%s%s", homedrive, homedir);
			pSite->m_home = buf;
		}

		// Fill in appdir
		GetCurrentDirectory(sizeof buf, buf);

		pSite->m_appdir = buf;

		pSite->GetMachineType();

		// Initialise network address
		struct hostent* pHost = gethostbyname(pSite->m_name);
		if (pHost){
			sprintf(buf, "%d.%d.%d.%d", pHost->h_addr[0] & 0xff,
				pHost->h_addr[1] & 0xff, pHost->h_addr[2] & 0xff,
				pHost->h_addr[3] & 0xff);
			pSite->m_netAddress = buf;
		}

		// Initialise port numbers
		pSite->m_bridge = rand() % (24 *  1024) + 32 * 1024;
		pSite->m_tlisten = pSite->m_bridge + 1;


		pSite->GetId();
	}
		
	sprintf(buf, "Configuration setup for %s", pSite->m_name);
	SetWindowText(buf);

	UpdateData(FALSE);

	CheckButtons();

	GotoDlgCtrl(GetDlgItem(IDC_SITE1));

	return FALSE;
}

void CConfSetup::OnOK() 
{
	CSite* pSite = NULL;
	BOOL bBadLocal = FALSE;
	BOOL bMP = FALSE;
	
	for (int i = 0 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (!pSite)
			continue;

		if (i > 1)
			bMP = TRUE;

		if (pSite->m_rootdir.IsEmpty() || pSite->m_appdir.IsEmpty() ||
		    pSite->m_home.IsEmpty()){
			goto error;
		}
		if (pSite->m_netAddress.IsEmpty() || pSite->m_bridge == 0 ||
			pSite->m_tlisten == 0 || pSite->m_type.IsEmpty()){
			if (i == 0)
				bBadLocal = TRUE;
			else
				goto error;
		}
	}

	if (bBadLocal && bMP){
		pSite = config.FindSite(0);
		goto error;
	}

	config.m_bValidConfig = TRUE;
	CDialog::OnOK();
	return;

error:
	Message("Site %s is not configured properly", pSite->m_name);
}

void CConfSetup::OnCancel() 
{
	config.m_bValidConfig = FALSE;	
	CDialog::OnCancel();
}

void CConfSetup::OnAdd() 
{
	ShowWindow(SW_HIDE);

	CSite* pSite = NULL;

	for (int i = 1 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (!pSite)
			break;
	}

	if (i == MAX_SITES){
		Message("All sites are configured");
		ShowWindow(SW_SHOW);
		return;
	}

	CWait dlgWait;

	CSiteAdd dlg;

	if (dlg.DoModal() == IDOK){
		switch(dlg.m_osType){
		case OS_NT:
			pSite = new CNTRemoteSite;
			break;
		case OS_UNIX:
			pSite = new CUnixSite;
			break;
		}
		if (!pSite)
			return;

		CString checking = "Trying to call site ";
		checking += dlg.m_name;

		dlgWait.start(checking);

		pSite->m_name = dlg.m_name;		
		if (!pSite->Connect()){
			dlgWait.stop();
			Message("Cannot communicate with site %s", (LPCSTR)dlg.m_name);
			delete pSite;
			ShowWindow(SW_SHOW);
			return;
		}
		pSite->m_bRemote = TRUE;
		pSite->m_nSite = i + 1;
		pSite->m_timePropagated = 0;
		pSite->m_timeBuild = 0;
		pSite->m_timeBankdl = 0;
		pSite->m_timeTlog = 0;

		// Initialise network address
		struct hostent* pHost = gethostbyname(pSite->m_name);
		if (pHost){
				char buf[50];
				sprintf(buf, "%d.%d.%d.%d", pHost->h_addr[0] & 0xff,
					pHost->h_addr[1] & 0xff, pHost->h_addr[2] & 0xff,
					pHost->h_addr[3] & 0xff);
				pSite->m_netAddress = buf;
		}

		CSite* pSiteLocal = config.FindSite(0);
		pSite->m_bridge = pSiteLocal->m_bridge;
		pSite->m_tlisten = pSiteLocal->m_tlisten;

		pSite->m_uid = 0;
		pSite->m_gid = 0;

		// Get Remote Info
		if (!pSite->GetLoginDir()){
			dlgWait.stop();
			Message("Cannot get login directory on site %s", (LPCSTR)dlg.m_name);
			delete pSite;
			ShowWindow(SW_SHOW);
			return;
		}

		if (!pSite->m_home.IsEmpty()){
			pSite->m_appdir = pSite->m_home;
			pSite->m_appdir += pSite->DirSep();
			pSite->m_appdir += "bankapp";
		}

		pSite->GetTuxdir();
		pSite->GetId();

		pSite->GetMachineType();

		config.SetSite(i, pSite);

		CheckButtons();

		dlgWait.stop();

	}

	ShowWindow(SW_SHOW);
}

void CConfSetup::OnRemove() 
{
	CSite* pSite = NULL;
	for (int i = 1 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (pSite)
			break;
	}

	if (i == MAX_SITES){
		Message("No remote site exist");
		return;
	}

	ShowWindow(SW_HIDE);
	CSiteRemove dlg;

	if (dlg.DoModal() == IDOK){
		CheckButtons();
	}
	
	ShowWindow(SW_SHOW);
}

void CConfSetup::OnSite1() 
{
	OnSite(config.FindSite(0));
}

void CConfSetup::OnSite2() 
{
	OnSite(config.FindSite(1));
}

void CConfSetup::OnSite3() 
{
	OnSite(config.FindSite(2));
}

void CConfSetup::OnSite4() 
{
	OnSite(config.FindSite(3));
}

void CConfSetup::OnSite5() 
{
	OnSite(config.FindSite(4));
}

void CConfSetup::OnSite6() 
{
	OnSite(config.FindSite(5));
}

void CConfSetup::OnSite7() 
{
	OnSite(config.FindSite(6));
}

void CConfSetup::OnSite8() 
{
	OnSite(config.FindSite(7));
}

void CConfSetup::OnSite9() 
{
	OnSite(config.FindSite(8));
}

void CConfSetup::OnSite10() 
{
	OnSite(config.FindSite(9));
}

/////////////////////////////////////////////////////////////////////////////
// CSiteAdd dialog


CSiteAdd::CSiteAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CSiteAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSiteAdd)
	m_name = _T("");
	//}}AFX_DATA_INIT
}


void CSiteAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSiteAdd)
	DDX_Text(pDX, IDC_SITE_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSiteAdd, CDialog)
	//{{AFX_MSG_MAP(CSiteAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSiteAdd message handlers

void CSiteAdd::OnOK() 
{
	UpdateData(TRUE);

	if (m_name.IsEmpty()){
		GotoDlgCtrl(GetDlgItem(IDC_SITE_NAME));
		return;
	}

	if (config.IsSiteName(m_name)){
		Message("Site \"%s\" already exists", (LPCSTR)m_name);
		GotoDlgCtrl(GetDlgItem(IDC_SITE_NAME));
		return;
	}


	switch(GetCheckedRadioButton(IDC_OSNT, IDC_OSUNIX)){
	case IDC_OSNT:
		m_osType = OS_NT;
		break;
	case IDC_OSUNIX:
		m_osType = OS_UNIX;
		break;
	}

	CDialog::OnOK();
}

BOOL CSiteAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GotoDlgCtrl(GetDlgItem(IDC_SITE_NAME));

	// Default to NT
	CheckRadioButton(IDC_OSNT, IDC_OSUNIX, IDC_OSNT);

	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CSiteRemove dialog


CSiteRemove::CSiteRemove(CWnd* pParent /*=NULL*/)
	: CDialog(CSiteRemove::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSiteRemove)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSiteRemove::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSiteRemove)
	DDX_Control(pDX, IDC_SITE_LIST, m_siteList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSiteRemove, CDialog)
	//{{AFX_MSG_MAP(CSiteRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSiteRemove message handlers

BOOL CSiteRemove::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for (int i = 1 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);

		if (!pSite || pSite->m_name.IsEmpty())
			continue;
		m_siteList.AddString(pSite->m_name);
	}
	
	GotoDlgCtrl(GetDlgItem(IDC_SITE_LIST));
	
	return FALSE;
}

void CSiteRemove::OnOK() 
{
	int selected;

	selected = m_siteList.GetSelCount();

	if (selected == 0){
		Message("No sites selected");
		return;
	}

	
	int* items = new int(selected);

	if (!items){
		CDialog::OnCancel();
		return;
	}

	m_siteList.GetSelItems(selected, items);

	for (int i = 0 ; i < selected ; i++){
		CString name;

		m_siteList.GetText(items[i], name);

		CSite* pSite = config.FindSite(name);

		if (!pSite)
			continue;

		delete pSite;
		config.SetSite(i, NULL);
	}

	delete items;

	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CSiteDesc dialog


CSiteDesc::CSiteDesc(CWnd* pParent /*=NULL*/)
	: CDialog(CSiteDesc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSiteDesc)
	m_appdir = _T("");
	m_home = _T("");
	m_netAddress = _T("");
	m_netDevice = _T("");
	m_rootdir = _T("");
	m_bridge = 0;
	m_tlisten = 0;
	m_type = _T("");
	m_uid = 0;
	m_gid = 0;
	//}}AFX_DATA_INIT

	m_pSite = NULL;
}


void CSiteDesc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSiteDesc)
	DDX_Text(pDX, IDC_APPDIR, m_appdir);
	DDX_Text(pDX, IDC_HOME, m_home);
	DDX_Text(pDX, IDC_NET_ADDRESS, m_netAddress);
	DDX_Text(pDX, IDC_NET_DEVICE, m_netDevice);
	DDX_Text(pDX, IDC_ROOTDIR, m_rootdir);
	DDX_Text(pDX, IDC_BRIDGE, m_bridge);
	DDX_Text(pDX, IDC_TLISTEN, m_tlisten);
	DDX_Text(pDX, IDC_TYPE, m_type);
	DDX_Text(pDX, IDC_UID, m_uid);
	DDX_Text(pDX, IDC_GID, m_gid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSiteDesc, CDialog)
	//{{AFX_MSG_MAP(CSiteDesc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSiteDesc message handlers

BOOL CSiteDesc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char buf[100];

	sprintf(buf, "Configuration info for %s", m_pSite->m_name);

	SetWindowText(buf);

	m_appdir = m_pSite->m_appdir;
	m_home = m_pSite->m_home;
	m_netAddress = m_pSite->m_netAddress;
	m_netDevice = m_pSite->m_netDevice;
	m_rootdir = m_pSite->m_rootdir;
	m_bridge = m_pSite->m_bridge;
	m_tlisten = m_pSite->m_tlisten;
	m_type = m_pSite->m_type;
	m_uid = m_pSite->m_uid;
	m_gid = m_pSite->m_gid;

	UpdateData(FALSE);

	switch(m_pSite->m_osType){
	case OS_NONE:
	case OS_UNIX:
		GetDlgItem(IDC_UID_TEXT)->EnableWindow(TRUE);
		GetDlgItem(IDC_UID)->EnableWindow(TRUE);
		GetDlgItem(IDC_GID_TEXT)->EnableWindow(TRUE);
		GetDlgItem(IDC_GID)->EnableWindow(TRUE);
		break;
	case OS_NT:
		GetDlgItem(IDC_UID_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_UID)->EnableWindow(FALSE);
		GetDlgItem(IDC_GID_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_GID)->EnableWindow(FALSE);
		break;
	}

	if (!m_pSite->m_bRemote){
		// Cannot change appdir on local site
		GetDlgItem(IDC_APPDIR)->EnableWindow(FALSE);
		// No network device on local site
		GetDlgItem(IDC_NET_DEVICE_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_NET_DEVICE)->EnableWindow(FALSE);
	} else {
		GetDlgItem(IDC_APPDIR)->EnableWindow(TRUE);
		GetDlgItem(IDC_NET_DEVICE_TEXT)->EnableWindow(TRUE);
		GetDlgItem(IDC_NET_DEVICE)->EnableWindow(TRUE); 
	}

	GotoDlgCtrl(GetDlgItem(IDC_ROOTDIR));
	return FALSE;
}

void CSiteDesc::OnOK() 
{
	UpdateData(TRUE);
	
	if (m_appdir.IsEmpty()){
		Message("Application Directory must be specified");
		GotoDlgCtrl(GetDlgItem(IDC_APPDIR));
		return;
	}

	// Check for remote appdir
	char msg[BUFSIZ];

	BOOL bOldAppdir = FALSE;

	if (m_pSite->m_bRemote){
		if (m_pSite->IsDirectory(m_appdir)){
			sprintf(msg, "Remove existing %s on %s before continuing?",
				(LPCSTR)m_appdir, (LPCSTR)m_pSite->m_name);
			switch(MessageBox(msg, "Application directory exists",
				MB_YESNOCANCEL|MB_ICONQUESTION)){
			case IDCANCEL:
				GotoDlgCtrl(GetDlgItem(IDC_APPDIR));
				return;
			case IDNO:
				bOldAppdir = TRUE;
				break;
			case IDYES:
				if (!m_pSite->RemoveFiles(m_appdir)){
					FatalMessage("Cannot remove existing %s on %s",
						(LPCSTR)m_appdir, (LPCSTR)m_pSite->m_name);
					GotoDlgCtrl(GetDlgItem(IDC_APPDIR));
					return;
				}
				break;
			}
		}

		if (!bOldAppdir){
			if (!m_pSite->CreateDir(m_appdir)){
				FatalMessage("Cannot create %s on %s",
					(LPCSTR)m_appdir, (LPCSTR)m_pSite->m_name);
				GotoDlgCtrl(GetDlgItem(IDC_APPDIR));
				return;
			}
		}
	}

	m_pSite->m_appdir = m_appdir;

	if (m_home.IsEmpty()){
		Message("Home directory must be specified");
		GotoDlgCtrl(GetDlgItem(IDC_HOME));
		return;
	}
	m_pSite->m_home = m_home;

	if (m_rootdir.IsEmpty()){
		Message("Tuxedo root directory must be specified (TUXDIR)");
		GotoDlgCtrl(GetDlgItem(IDC_ROOTDIR));
		return;
	}
	// Check for rootdir
	if (m_pSite->m_bRemote){
		if (!m_pSite->IsDirectory(m_rootdir)){
			Message("Invalid TUXDIR %s for %s",
				(LPCSTR)m_rootdir, (LPCSTR)m_pSite->m_name);
			GotoDlgCtrl(GetDlgItem(IDC_ROOTDIR));
			return;
		}
	} else {
		if (!IsLocalDir(m_rootdir)){
			Message("Invalid TUXDIR %s for local site",
				(LPCSTR)m_rootdir);
			GotoDlgCtrl(GetDlgItem(IDC_ROOTDIR));
			return;
		}
	}

	m_pSite->m_rootdir = m_rootdir;

	if (m_pSite->m_bRemote){
		if (m_netAddress.IsEmpty()){
			Message("Missing network address");
			GotoDlgCtrl(GetDlgItem(IDC_NET_ADDRESS));
			return;
		}

		if (m_bridge == 0 || m_bridge >= 64 * 1024){
			Message("Missing or invalid bridge port");
			GotoDlgCtrl(GetDlgItem(IDC_BRIDGE));
			return;
		}

		if (m_tlisten == 0 || m_tlisten >= 64 * 1024){
			Message("Missing or invalid tlisten port");
			GotoDlgCtrl(GetDlgItem(IDC_TLISTEN));
			return;
		}

		if (m_type.IsEmpty()){
			Message("Machine type must be specified");
			GotoDlgCtrl(GetDlgItem(IDC_TYPE));
			return;
		}
	}

	m_pSite->m_type = m_type;
	m_pSite->m_netAddress = m_netAddress;
	m_pSite->m_netDevice = m_netDevice;
	m_pSite->m_bridge = m_bridge;
	m_pSite->m_tlisten = m_tlisten;
	
	m_pSite->m_uid = m_uid;
	m_pSite->m_gid = m_gid;

	m_pSite->m_timePropagated = 0;
	m_pSite->m_timeBuild = 0;
	m_pSite->m_timeBankdl = 0;
	m_pSite->m_timeTlog = 0;

	CDialog::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CConfIpckey dialog


CConfIpckey::CConfIpckey(CWnd* pParent /*=NULL*/)
	: CDialog(CConfIpckey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfIpckey)
	m_ipckey = 0;
	//}}AFX_DATA_INIT
}


void CConfIpckey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfIpckey)
	DDX_Text(pDX, IDC_IPCKEY, m_ipckey);
	DDV_MinMaxInt(pDX, m_ipckey, 32768, 16777215);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfIpckey, CDialog)
	//{{AFX_MSG_MAP(CConfIpckey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConfIpckey message handlers

BOOL CConfIpckey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GotoDlgCtrl(GetDlgItem(IDC_IPCKEY));
	return FALSE;
}
