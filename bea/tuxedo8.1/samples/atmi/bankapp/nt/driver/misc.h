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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/misc.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/driver/misc.h	$Revision: 1.4 $";
#endif
void Message(const char* fmt, ...);
void InfoMessage(const char* fmt, ...);
void WarningMessage(const char* fmt, ...);
void FatalMessage(const char* fmt, ...);
char* ErrorMessage(DWORD dwError);
extern BOOL IsFileReadable(char* name);
extern BOOL IsLocalDir(const char* name);
extern BOOL IsPropagated();
extern CStringArray& SourceFileList();
extern BOOL Propagate(const char* name, CString& dir, CStringArray& files);
extern BOOL substitute(char* ifile, char* ofile, CStringArray& patterns, CStringArray& replacements);

enum BuildItem { BI_BUILD, BI_BANKDL, BI_TLOG };

extern FILE* popen(const char* cmd, const char* mode);
extern int pclose(FILE* fd);

extern BOOL IsBuilt(BuildItem bi);
extern BOOL IsAnyBuilt(BuildItem bi);
extern BOOL IsActive(char* process);
extern BOOL Setup();
extern BOOL RunCommand(const char* command, const char* envfile);
extern BOOL Populate();
extern BOOL Gentrans();
extern BOOL RunRemoteGetLine(const char* name, const char* cmd, CString& line);
extern BOOL RunLocalGetLine(const char* cmd, CString& line);
extern BOOL RunRemoteVerify(const char* name, const char* cmd);
extern BOOL CopyFile(CString& ifile, CString& ofile);
extern char* mk_addr(const char* address, UINT port);
extern void SetLocalFiles();
extern void mk_forw_path(CString& path);
extern void show_console();
extern void hide_console();
extern int CountSites();
extern CString envfile;
extern CString makefile;

/////////////////////////////////////////////////////////////////////////////
// CCommandOut dialog

class CCommandOut : public CDialog
{
// Construction
public:
	CCommandOut(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommandOut)
	enum { IDD = IDD_RUN_COMMAND };
	CEdit	m_commandOutput;
	//}}AFX_DATA

	// UNIX data
	FILE* m_pipe;
	// NT data
	CBankappClient* m_remote;

	// Common data
	CString m_command;
	int m_exitcode;
	CWinThread* m_pThread;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandOut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommandOut)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void CanDestroy();
};

/////////////////////////////////////////////////////////////////////////////
// CDlgUdOut dialog

class CDlgUdOut : public CDialog
{
// Construction
public:
	CDlgUdOut(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUdOut)
	enum { IDD = IDD_RUN_UD };
	CEdit	m_percent;
	//}}AFX_DATA

	FILE* m_pipe;
	int m_max;
	int m_exitcode;
	int m_warnings;
	int m_errors;
	CString m_title;
	CWinThread* m_pThread;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUdOut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUdOut)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void CanDestroy();
};
/////////////////////////////////////////////////////////////////////////////
// CTransCount dialog

class CTransCount : public CDialog
{
// Construction
public:
	CTransCount(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransCount)
	enum { IDD = IDD_TRANSACTION_COUNT };
	UINT	m_ntrans;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransCount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransCount)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CdlgWait dialog

class CdlgWait : public CDialog
{
// Construction
public:
	CdlgWait(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CdlgWait)
	enum { IDD = IDD_WAIT };
	CString	m_reason;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdlgWait)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CdlgWait)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CWait {
	CdlgWait		m_dlg;
	BOOL			m_bStarted;
	static HCURSOR	m_hcurWait;
	HCURSOR			m_hcurOld;
public:
	CWait();
	void start(CString& reason);
	void stop();
};
