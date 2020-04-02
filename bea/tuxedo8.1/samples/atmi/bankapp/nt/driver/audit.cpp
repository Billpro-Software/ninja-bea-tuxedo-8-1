//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//	Copyright (c) 1995 Novell, Inc.	
//	  All Rights Reserved 	 	

//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	
//	Novell, Inc.                     			
//	The copyright notice above does not evidence any   	
//	actual or intended publication of such source code.	

// #ident	"@(#) samples/atmi/bankapp/nt/driver/audit.cpp	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/audit.cpp	$Revision: 1.4 $";
#endif

#include "stdafx.h"
#include "driver.h"
#include "remote.h"
#include "config.h"
#include "misc.h"
#include "audit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudit dialog


CDlgAudit::CDlgAudit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAudit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudit, CDialog)
	//{{AFX_MSG_MAP(CDlgAudit)
	ON_BN_CLICKED(IDC_AUDIT_ACCOUNTS, OnAuditAccounts)
	ON_BN_CLICKED(IDC_AUDIT_TELLERS, OnAuditTellers)
	ON_BN_CLICKED(IDC_CONV_AUDIT, OnConvAudit)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgAudit message handlers

BOOL CDlgAudit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GotoDlgCtrl(GetDlgItem(IDC_AUDIT_ACCOUNTS));
	
	return FALSE;
}

void CDlgAudit::OnAuditAccounts() 
{
	RunAudit('a');
}

void CDlgAudit::OnAuditTellers() 
{
	RunAudit('t');	
}

void CDlgAudit::OnConvAudit() 
{
	system("bankvar.mp1 & start auditcon");
}

void CDlgAudit::OnHelp() 
{
	theApp.Help();
}

BOOL CDlgAudit::SelectBranch(UINT& branch)
{
	CDlgBranch dlg;

	if (dlg.DoModal() != IDOK)
		return FALSE;

	if (dlg.m_bAll)
		branch = 0;
	else
		branch = dlg.m_branch;

	return TRUE;
}

void CDlgAudit::RunAudit(char type) 
{
	UINT iBranch;

	ShowWindow(SW_HIDE);

	if (!SelectBranch(iBranch)){
		ShowWindow(SW_SHOW);
		return;
	}

	CWait dlgWait;

	dlgWait.start((CString)"Running audit command");
	char command[20];

	if (iBranch)
		sprintf(command, "audit -%c %d", type, iBranch);
	else
		sprintf(command, "audit -%c", type);

	CString output;

	if (!RunLocalGetLine(command, output)){
		dlgWait.stop();
		ShowWindow(SW_SHOW);
		return;
	}

	dlgWait.stop();
	InfoMessage(output);
	ShowWindow(SW_SHOW);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgBranch dialog


CDlgBranch::CDlgBranch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBranch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBranch)
	m_branch = 0;
	//}}AFX_DATA_INIT

	m_branch = 1;
	m_bAll = TRUE;
}


void CDlgBranch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBranch)
	DDX_Text(pDX, IDC_BRANCH, m_branch);
	DDV_MinMaxUInt(pDX, m_branch, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBranch, CDialog)
	//{{AFX_MSG_MAP(CDlgBranch)
	ON_BN_CLICKED(IDC_AUDIT_ALL, OnAuditAll)
	ON_BN_CLICKED(IDC_AUDIT_ONE, OnAuditOne)
	ON_EN_SETFOCUS(IDC_BRANCH, OnSetfocusBranch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgBranch message handlers

void CDlgBranch::OnAuditAll() 
{
	m_bAll = TRUE;
}

void CDlgBranch::OnAuditOne() 
{
	m_bAll = FALSE;

	GotoDlgCtrl(GetDlgItem(IDC_BRANCH));
}

BOOL CDlgBranch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Default to all branches
	CheckRadioButton(IDC_AUDIT_ALL, IDC_AUDIT_ONE, IDC_AUDIT_ALL);
	
	GotoDlgCtrl(GetDlgItem(IDOK));

	return FALSE;
}

void CDlgBranch::OnOK() 
{
	CDialog::OnOK();
}

void CDlgBranch::OnSetfocusBranch() 
{
	CheckRadioButton(IDC_AUDIT_ALL, IDC_AUDIT_ONE, IDC_AUDIT_ONE);
	OnAuditOne();
}
