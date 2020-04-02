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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/driver.cpp	$Revision: 1.5 $"

// driver.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "driver.h"
#include "drivedlg.h"
#include "remote.h"
#include "misc.h"
#include "config.h"

#include <direct.h>
#include <winsock.h>
#include <Uunix.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverApp

BEGIN_MESSAGE_MAP(CDriverApp, CWinApp)
	//{{AFX_MSG_MAP(CDriverApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverApp construction

CDriverApp::CDriverApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDriverApp object

CDriverApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDriverApp initialization

BOOL CDriverApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Initialise Winsock
	WSADATA wd;
	WORD wVersion = 0x0101;

	if (WSAStartup(wVersion, &wd) != 0){
		FatalMessage("Cannot initialise winsock");
		return FALSE;
	}

	// Create a console for popen(), and hide it
	AllocConsole();
	hide_console();
	SetConsoleTitle("Bankapp driver");

	// Initialize randomizer
	srand(time(0));

	// Change to $TUXDIR/samples/atmi/bankapp
	char* tuxdir = tuxgetenv("TUXDIR");
	if (!tuxdir){
		FatalMessage("TUXDIR not set");
		return FALSE;
	}

	CString dir = tuxdir;
	dir += "\\samples\\atmi\\bankapp";

	if (_chdir(dir) == -1){
		FatalMessage("Cannot change to directory %s", (LPCSTR)dir);
		return FALSE;
	}

	// Configuration file name
	config.SetFileName("bankapp.config");

	(void)config.Load();

	SetLocalFiles();

	CDriverDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CDriverApp::Help()
{
	OnHelp();
}
