/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

//	Copyright (c) 1995 Novell, Inc.	
//	  All Rights Reserved 	 	

//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	
//	Novell, Inc.                     			
//	The copyright notice above does not evidence any   	
//	actual or intended publication of such source code.	

// #ident	"@(#) samples/atmi/bankapp/nt/driver/audit.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/audit.h	$Revision: 1.4 $";
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudit dialog

class CDlgAudit : public CDialog
{
// Construction
public:
	CDlgAudit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAudit)
	enum { IDD = IDD_AUDIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAudit)
	virtual BOOL OnInitDialog();
	afx_msg void OnAuditAccounts();
	afx_msg void OnAuditTellers();
	afx_msg void OnConvAudit();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL SelectBranch(UINT& branch);
	void RunAudit(char type);
};
/////////////////////////////////////////////////////////////////////////////
// CDlgBranch dialog

class CDlgBranch : public CDialog
{
// Construction
public:
	CDlgBranch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBranch)
	enum { IDD = IDD_SELECT_BRANCH };
	UINT	m_branch;
	//}}AFX_DATA

	BOOL m_bAll;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBranch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBranch)
	afx_msg void OnAuditAll();
	afx_msg void OnAuditOne();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetfocusBranch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
