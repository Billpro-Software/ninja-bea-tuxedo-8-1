//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//	Copyright (c) 1995 Novell, Inc.	
//	  All Rights Reserved 	 	

//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	
//	Novell, Inc.                     			
//	The copyright notice above does not evidence any   	
//	actual or intended publication of such source code.	

// #ident	"@(#) samples/atmi/bankapp/nt/driver/initmain.cpp	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/initmain.cpp	$Revision: 1.4 $";
#endif

// initmain.cpp : implementation file
//

#include "stdafx.h"
#include "driver.h"
#include "initmain.h"
#include "remote.h"
#include "config.h"
#include "initconf.h"
#include "initrun.h"

#include "misc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitMain dialog


CInitMain::CInitMain(CWnd* pParent /*=NULL*/)
	: CDialog(CInitMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitMain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInitMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitMain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitMain, CDialog)
	//{{AFX_MSG_MAP(CInitMain)
	ON_BN_CLICKED(IDC_CONFIGURATION, OnConfiguration)
	ON_BN_CLICKED(IDC_PROPAGATION, OnPropagation)
	ON_BN_CLICKED(IDC_RUNTIME, OnRuntime)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInitMain implementation

// Prerequisites for configuration
BOOL CInitMain::PrereqConfiguration()
{
	if (!IsFileReadable("tuxconfig") || !IsFileReadable("UBB"))
		return TRUE;

	if (!config.m_bValidConfig)
		return TRUE;

	return FALSE;
}

BOOL CInitMain::PrereqPropagation()
{
	if (!config.m_bValidConfig)
		return FALSE;

	if (!IsFileReadable("tuxconfig") || !IsFileReadable("UBB") ||
	    !IsFileReadable("bankvar.mp*") || !IsFileReadable("bankapp.mak*"))
		return FALSE;

	if (IsPropagated())
		return FALSE;

	return TRUE;
}

BOOL CInitMain::PrereqRuntime()
{
	if (!config.m_bValidConfig)
		return FALSE;

	if (!IsFileReadable("tuxconfig") || !IsFileReadable("UBB") ||
	    !IsFileReadable("bankvar.mp*") || !IsFileReadable("bankapp.mak*"))
		return FALSE;

	if (!IsBuilt(BI_BUILD))
		return TRUE;
	if (!IsBuilt(BI_BANKDL))
		return TRUE;
	if (!IsBuilt(BI_TLOG))
		return TRUE;

	return FALSE;
}

// Check prerequisites for the buttons
void CInitMain::CheckPrereq()
{
	CWait dlgWait;

	dlgWait.start((CString)"Checking initialization status");

	CWnd* wConfiguration = GetDlgItem(IDC_CONFIGURATION);
	BOOL bConfigurationEnable = PrereqConfiguration();
	wConfiguration->EnableWindow(bConfigurationEnable);

	CWnd* wPropagation = GetDlgItem(IDC_PROPAGATION);
	BOOL bPropagationEnable = PrereqPropagation();
	wPropagation->EnableWindow(bPropagationEnable);

	CWnd* wRuntime = GetDlgItem(IDC_RUNTIME);
	BOOL bRuntimeEnable = PrereqRuntime();
	wRuntime->EnableWindow(bRuntimeEnable);

	if (bConfigurationEnable)
		GotoDlgCtrl(wConfiguration);
	else if (bPropagationEnable)
		GotoDlgCtrl(wPropagation);
	else if (bRuntimeEnable)
		GotoDlgCtrl(wRuntime);
	else
		CDialog::OnOK();

	dlgWait.stop();
}

/////////////////////////////////////////////////////////////////////////////
// CInitMain message handlers


BOOL CInitMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckPrereq();

	// CheckPrereq sets the focus
	return FALSE;		
}

void CInitMain::OnConfiguration() 
{
	ShowWindow(SW_HIDE);

	CInitConfig	dlg;

	int response = dlg.DoModal();

	CheckPrereq();

	ShowWindow(SW_SHOW);
}

// Propagate source code to remote sites
void CInitMain::OnPropagation() 
{
	ShowWindow(SW_HIDE);

	CWait dlgWait;
	CString propagating;
	for (int i = 1 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);

		if (!pSite)
			continue;

		propagating = "Propagating files to site ";
		propagating += pSite->m_name;
		dlgWait.start(propagating);
		pSite->Propagate();
		dlgWait.stop();
	}

	CheckPrereq();

	ShowWindow(SW_SHOW);
}

void CInitMain::OnRuntime() 
{
	ShowWindow(SW_HIDE);

	CInitRuntime dlg;

	int response = dlg.DoModal();

	CheckPrereq();

	ShowWindow(SW_SHOW);
}

void CInitMain::OnHelp() 
{
	theApp.Help();
}
