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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/initconf.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/initconf.h	$Revision: 1.4 $";
#endif

// initconf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInitConfig dialog

class CInitConfig : public CDialog
{
// Construction
public:
	CInitConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInitConfig)
	enum { IDD = IDD_INIT_CONFIG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CheckPrereq();
	BOOL PrereqUbbconfig();
	BOOL PrereqTuxconfig();

	// Generated message map functions
	//{{AFX_MSG(CInitConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnUbbconfig();
	afx_msg void OnTuxconfig();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CInitMode dialog

class CInitMode : public CDialog
{
// Construction
public:
	CInitMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInitMode)
	enum { IDD = IDD_INIT_MODE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsVerbose() { return (IdChecked == IDC_VERBOSE); }
protected:
	int IdChecked;

	// Generated message map functions
	//{{AFX_MSG(CInitMode)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CConfSetup dialog

class CConfSetup : public CDialog
{
// Construction
public:
	CConfSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfSetup)
	enum { IDD = IDD_INIT_SITES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	void CheckButtons();

protected:
	void OnSite(CSite* pSite);

	// Generated message map functions
	//{{AFX_MSG(CConfSetup)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnSite1();
	afx_msg void OnSite2();
	afx_msg void OnSite3();
	afx_msg void OnSite4();
	afx_msg void OnSite5();
	afx_msg void OnSite6();
	afx_msg void OnSite7();
	afx_msg void OnSite8();
	afx_msg void OnSite9();
	afx_msg void OnSite10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CSiteAdd dialog

class CSiteAdd : public CDialog
{
// Construction
public:
	CSiteAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSiteAdd)
	enum { IDD = IDD_SITE_ADD };
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSiteAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSiteAdd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	OsType m_osType;
};
/////////////////////////////////////////////////////////////////////////////
// CSiteRemove dialog

class CSiteRemove : public CDialog
{
// Construction
public:
	CSiteRemove(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSiteRemove)
	enum { IDD = IDD_SITE_REMOVE };
	CListBox	m_siteList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSiteRemove)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CSiteRemove)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CSiteDesc dialog

class CSiteDesc : public CDialog
{
// Construction
public:
	CSiteDesc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSiteDesc)
	enum { IDD = IDD_SITE_INFO };
	CString	m_appdir;
	CString	m_home;
	CString	m_netAddress;
	CString	m_netDevice;
	CString	m_rootdir;
	UINT	m_bridge;
	UINT	m_tlisten;
	CString	m_type;
	UINT	m_uid;
	UINT	m_gid;
	//}}AFX_DATA


// attributes
	CSite* m_pSite;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSiteDesc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSiteDesc)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CConfIpckey dialog

class CConfIpckey : public CDialog
{
// Construction
public:
	CConfIpckey(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfIpckey)
	enum { IDD = IDD_IPCKEY };
	int		m_ipckey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfIpckey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfIpckey)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
