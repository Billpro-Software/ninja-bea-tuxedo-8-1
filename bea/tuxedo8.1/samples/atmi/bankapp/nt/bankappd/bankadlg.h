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

// #ident	"@(#) samples/atmi/bankapp/nt/bankappd/bankadlg.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/bankappd/bankadlg.h	$Revision: 1.4 $";
#endif

// bankadlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBankappdDlg dialog

enum ConnectStatus { CS_WAIT_CONNECT, CS_CONNECTED, CS_RECV_FILE, CS_RUNNING_COMMAND,
	CS_REMOVING_FILES, CS_KILL_TLISTEN, CS_CLEAN_IPC };

class CBankappdDlg : public CDialog
{
// Construction
public:
	CBankappdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBankappdDlg)
	enum { IDD = IDD_BANKAPPD_DIALOG };
	CString	m_status;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankappdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
public:
	CWinThread* m_pThread;
	ConnectStatus m_connectstatus;
	CBankappServer m_cbs;
	HANDLE m_hEvent;
	CString m_tuxdir;
	HANDLE m_hFile;

	// Generated message map functions
	//{{AFX_MSG(CBankappdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void UpdateStatus(ConnectStatus status);
};
/////////////////////////////////////////////////////////////////////////////
// CTuxdirDlg dialog

class CTuxdirDlg : public CDialog
{
// Construction
public:
	CTuxdirDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTuxdirDlg)
	enum { IDD = IDD_TUXDIR };
	CString	m_tuxdir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTuxdirDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTuxdirDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
