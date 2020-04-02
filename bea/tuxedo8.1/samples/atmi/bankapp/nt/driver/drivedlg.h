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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/drivedlg.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/drivedlg.h	$Revision: 1.4 $";
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverDlg dialog

class CDriverDlg : public CDialog
{
// Construction
public:
	CDriverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDriverDlg)
	enum { IDD = IDD_DRIVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL PrereqInitialize();
	BOOL PrereqBoot();
	BOOL PrereqPopulate();
	BOOL PrereqClient();
	BOOL PrereqAudit();
	BOOL PrereqShutdown();
	BOOL PrereqTmadmin();
	BOOL PrereqCleanup();
	BOOL PrereqGentrans();
	void CheckPrereq();

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDriverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAudit();
	afx_msg void OnBoot();
	afx_msg void OnCleanup();
	afx_msg void OnGentrans();
	afx_msg void OnInitialize();
	afx_msg void OnPopulate();
	afx_msg void OnShutdown();
	afx_msg void OnTmadmin();
	afx_msg void OnHelp();
	virtual void OnOK();
	afx_msg void OnClient();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
