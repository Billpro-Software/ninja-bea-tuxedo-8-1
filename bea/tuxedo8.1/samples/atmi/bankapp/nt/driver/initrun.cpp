//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//	Copyright (c) 1995 Novell, Inc.	
//	  All Rights Reserved 	 	

//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	
//	Novell, Inc.                     			
//	The copyright notice above does not evidence any   	
//	actual or intended publication of such source code.	

// #ident	"@(#) samples/atmi/bankapp/nt/driver/initrun.cpp	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/initrun.cpp	$Revision: 1.4 $";
#endif

// initrun.cpp : implementation file
//

#include "stdafx.h"
#include "driver.h"
#include "initrun.h"
#include "remote.h"
#include "config.h"
#include "misc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitRuntime dialog


CInitRuntime::CInitRuntime(CWnd* pParent /*=NULL*/)
	: CDialog(CInitRuntime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitRuntime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInitRuntime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitRuntime)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitRuntime, CDialog)
	//{{AFX_MSG_MAP(CInitRuntime)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_BANKDL, OnBankdl)
	ON_BN_CLICKED(IDC_BUILD, OnBuild)
	ON_BN_CLICKED(IDC_TLOG, OnTlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitRuntime implementation

BOOL CInitRuntime::PrereqBuild()
{
	if (!IsPropagated())
		return FALSE;

	if (IsBuilt(BI_BUILD))
		return FALSE;

	return TRUE;
}

BOOL CInitRuntime::PrereqBankdl()
{
	if (!IsBuilt(BI_BUILD))
		return FALSE;

	if (IsBuilt(BI_BANKDL))
		return FALSE;

	return TRUE;
}

BOOL CInitRuntime::PrereqTlog()
{
	if (!IsBuilt(BI_BUILD))
		return FALSE;

	if (IsBuilt(BI_TLOG))
		return FALSE;

	return TRUE;
}

void CInitRuntime::CheckPrereq()
{
	CWait dlgWait;

	dlgWait.start((CString)"Checking run time status");

	CWnd* wBuild = GetDlgItem(IDC_BUILD);
	BOOL bBuildEnable = PrereqBuild();
	wBuild->EnableWindow(bBuildEnable);

	CWnd* wBankdl = GetDlgItem(IDC_BANKDL);
	BOOL bBankdlEnable = PrereqBankdl();
	wBankdl->EnableWindow(bBankdlEnable);

	CWnd* wTlog = GetDlgItem(IDC_TLOG);
	BOOL bTlogEnable = PrereqTlog();
	wTlog->EnableWindow(bTlogEnable);

	if (bBuildEnable)
		GotoDlgCtrl(wBuild);
	else if (bBankdlEnable)
		GotoDlgCtrl(wBankdl);
	else if (bTlogEnable)
		GotoDlgCtrl(wTlog);
	else
		CDialog::OnOK();
	
	dlgWait.stop();
}

/////////////////////////////////////////////////////////////////////////////
// CInitRuntime message handlers

void CInitRuntime::OnBuild() 
{
	ShowWindow(SW_HIDE);

	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;

		if (pSite->m_timeBuild > pSite->m_timePropagated)
			continue;
		
		pSite->Build();
	}
	CheckPrereq();

	ShowWindow(SW_SHOW);
}

void CInitRuntime::OnBankdl() 
{
	ShowWindow(SW_HIDE);

	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		
		if (pSite->m_timeBankdl > pSite->m_timePropagated)
			continue;

		pSite->CreateBank();
	}

	config.m_timePopulate = 0;

	CheckPrereq();
	
	ShowWindow(SW_SHOW);
}

void CInitRuntime::OnTlog() 
{
	ShowWindow(SW_HIDE);

	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		
		if (pSite->m_timeTlog > pSite->m_timePropagated)
			continue;

		pSite->CreateTlog();
	}

	CheckPrereq();
	
	ShowWindow(SW_SHOW);
}

void CInitRuntime::OnHelp() 
{
	theApp.Help();
}

void CInitRuntime::OnOK() 
{
	CDialog::OnOK();
}

BOOL CInitRuntime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckPrereq();

	return FALSE;
}
