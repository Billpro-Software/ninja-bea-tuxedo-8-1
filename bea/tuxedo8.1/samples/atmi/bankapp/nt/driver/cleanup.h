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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/cleanup.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/cleanup.h	$Revision: 1.4 $";
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanup dialog

class CDlgCleanup : public CDialog
{
// Construction
public:
	CDlgCleanup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCleanup)
	enum { IDD = IDD_CLEANUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCleanup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CheckPrereq();
	BOOL PrereqCleanAll();
	BOOL PrereqCleanConfiguration();
	BOOL PrereqCleanIpc();
	BOOL PrereqCleanRuntime();
	BOOL PrereqCleanServers();
	BOOL PrereqCleanTlisten();

	void CleanAll();
	void CleanConfiguration();
	void CleanIpc();
	void CleanServers();
	void CleanTlisten();

	// Generated message map functions
	//{{AFX_MSG(CDlgCleanup)
	virtual BOOL OnInitDialog();
	afx_msg void OnHelp();
	afx_msg void OnCleanAll();
	afx_msg void OnCleanConfiguration();
	afx_msg void OnCleanIpc();
	afx_msg void OnCleanRuntime();
	afx_msg void OnCleanServers();
	afx_msg void OnCleanTlisten();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCleanRuntime dialog

class CDlgCleanRuntime : public CDialog
{
// Construction
public:
	CDlgCleanRuntime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCleanRuntime)
	enum { IDD = IDD_CLEAN_RUNTIME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCleanRuntime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void CleanAll();
protected:
	void CheckPrereq();
	BOOL PrereqCleanBankdls();
	BOOL PrereqCleanTlogs();
	BOOL PrereqCleanUserlogs();
	BOOL PrereqCleanAll();

	void CleanBankdls();
	void CleanTlogs();
	void CleanUserlogs();
	// Generated message map functions
	//{{AFX_MSG(CDlgCleanRuntime)
	virtual BOOL OnInitDialog();
	afx_msg void OnHelp();
	afx_msg void OnCleanBankdls();
	afx_msg void OnCleanTlogs();
	afx_msg void OnCleanUserlogs();
	afx_msg void OnCleanAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
