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
// #ident	"@(#) samples/atmi/bankapp/nt/bankappd/bankappd.cpp	$Revision: 1.4 $"

// bankappd.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "bankappd.h"
#include "remote.h"
#include "misc.h"
#include "bankadlg.h"
#include <string.h>
#include <sys\stat.h>
#include <Uunix.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankappdApp

BEGIN_MESSAGE_MAP(CBankappdApp, CWinApp)
	//{{AFX_MSG_MAP(CBankappdApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankappdApp construction

CBankappdApp::CBankappdApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBankappdApp object

CBankappdApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBankappdApp initialization

BOOL CBankappdApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	CBankappdDlg dlg;
	m_pMainWnd = &dlg;
	if (!dlg.m_cbs.Create()){
		return FALSE;
	}

	// Create and hide a console window, to run commands
	AllocConsole();

	HWND hConsole = FindWindow("ConsoleWindowClass", NULL);
	if (!hConsole){
		FatalMessage("Error", "Cannot find console window");
		return FALSE;
	}

	ShowWindow(hConsole, SW_HIDE);
	UpdateWindow(hConsole);
	
	//_dup2(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_RDWR), 0);
	//_dup2(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_RDWR), 1);
	//_dup2(_open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_RDWR), 2);

	// Start second thread to do the "real" work
	dlg.m_pThread = AfxBeginThread((AFX_THREADPROC)BankappServer, &dlg,
		0, 0, CREATE_SUSPENDED);
	if (!dlg.m_pThread){
		FatalMessage("Cannot create server thread");
		return FALSE;
	}

	dlg.m_tuxdir = tuxgetenv("TUXDIR");

	if (dlg.m_tuxdir.IsEmpty()){
		CTuxdirDlg tdlg;
		if (tdlg.DoModal() != IDOK){
			FatalMessage("Cannot continue without TUXDIR. Exiting");
			return FALSE;
		}
		dlg.m_tuxdir = tdlg.m_tuxdir;
	}

	dlg.m_connectstatus = CS_WAIT_CONNECT;
	dlg.m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	if (!dlg.m_hEvent){
		FatalMessage("Cannot create synchronization event");
		return FALSE;
	}

	dlg.m_status = "Waiting for connection";

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Kill the second thread
	SetEvent(dlg.m_hEvent);
	WaitForSingleObject(dlg.m_pThread->m_hThread, INFINITE);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

HANDLE hCmdPipe;
HANDLE hCmdProcess;

// Start a command, on behalf of the remote client
BOOL CommandStart(char* command)
{
	HANDLE hTmpPipe;
	HANDLE hTmpPipe2;
	HANDLE hProcess;
	SECURITY_ATTRIBUTES sa;
		
	sa.nLength = sizeof sa;
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hCmdPipe, &hTmpPipe, &sa, 0)){
		FatalMessage("Cannot create command pipe: %s",
			ErrorMessage(GetLastError()));
		return FALSE;
	}

	// Make the read side not inheritable, so that the pipe
	// will be destroyed when the child closes its
	// STD_INPUT_HANDLE.

	hProcess = GetCurrentProcess();
	if (!DuplicateHandle(hProcess, hCmdPipe, hProcess, &hTmpPipe2, 0, FALSE,
		DUPLICATE_SAME_ACCESS|DUPLICATE_CLOSE_SOURCE)){
		FatalMessage("Cannot duplicate command pipe handle: %s",
			ErrorMessage(GetLastError()));
		CloseHandle(hCmdPipe);
		CloseHandle(hTmpPipe);
		return FALSE;
	}

	hCmdPipe = hTmpPipe2;

	// Create process
	STARTUPINFOA sia;
	PROCESS_INFORMATION pi;

	memset(&sia, 0, sizeof sia);
	sia.cb = sizeof sia;
	sia.dwFlags = STARTF_USESTDHANDLES;
	sia.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	sia.hStdOutput = hTmpPipe;
	sia.hStdError = hTmpPipe;

	CString FullCommand = "cmd /c ";
	FullCommand += command;

	if (!CreateProcess(NULL, (char*)(LPCSTR)FullCommand, NULL, NULL, TRUE, 0,
	    NULL, NULL, &sia, &pi)){
		//Message("Cannot start process: %s", ErrorMessage(GetLastError()));
		CloseHandle(hCmdPipe);
		CloseHandle(hTmpPipe);
		return FALSE;
	}

	hCmdProcess = pi.hProcess;
	CloseHandle(pi.hThread);
	CloseHandle(hTmpPipe);

	return TRUE;
}

// Get Command output
BOOL
CommandOutput(BankappReply& reply, HANDLE hEvent)
{
	HANDLE handles[2];

	handles[0] = hCmdPipe;
	handles[1] = hEvent;

	int nevents = hEvent ? 2 : 1;
		
	DWORD dwWait = WaitForMultipleObjects(nevents, handles, FALSE, INFINITE);

	if (dwWait == WAIT_FAILED){
		FatalMessage("Wait failed: %s", ErrorMessage(GetLastError()));
		AfxEndThread(1);
	}

	if (dwWait == WAIT_OBJECT_0){
		// Something on the pipe
		if (!ReadFile(hCmdPipe, reply.data, sizeof reply.data, &reply.size, NULL) || reply.size == 0){
			WaitForSingleObject(hCmdProcess, INFINITE);
			GetExitCodeProcess(hCmdProcess, &reply.exitcode);
			reply.status = BR_OK;
			CloseHandle(hCmdProcess);
			CloseHandle(hCmdPipe);
			return TRUE;
		}
		reply.status = BR_MORE;
		return TRUE;
	}

	// Event was triggered
	AfxEndThread(0);

	// Not reached
	return FALSE;
}

// Cancel command
BOOL
CommandCancel()
{
	return FALSE;
}

// Server thread routine
DWORD
BankappServer(LPVOID parms)
{
	CBankappdDlg* dlg = (CBankappdDlg*)parms;

	BankappRequest request;
	BankappReply reply;
	DWORD dwWritten;
	SYSTEM_INFO si;
	CString data;

	for (;;){
		switch(dlg->m_connectstatus){
		case CS_WAIT_CONNECT:
			if (!dlg->m_cbs.Accept(dlg->m_hEvent))
				continue;

			dlg->UpdateStatus(CS_CONNECTED);
			continue;
		case CS_CONNECTED:
			if (!dlg->m_cbs.GetRequest(request, dlg->m_hEvent)){
				(void)dlg->m_cbs.Disconnect();
				dlg->UpdateStatus(CS_WAIT_CONNECT);
				continue;
			}
			switch(request.type){
			case BR_DISCONNECT:
				reply.status = BR_OK;
				(void)dlg->m_cbs.SendReply(reply);
				(void)dlg->m_cbs.Disconnect();
				dlg->UpdateStatus(CS_WAIT_CONNECT);
				continue;
			case BR_GET_TUXDIR:
				reply.status = BR_OK;
				strcpy(reply.data, dlg->m_tuxdir);
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_GET_CURDIR:
				if (GetCurrentDirectory(sizeof reply.data, reply.data) == 0){
					reply.status = BR_FAILED;
				} else
					reply.status = BR_OK;
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_GET_HOME_DIR:
				sprintf(reply.data, "%s%s", tuxgetenv("HOMEDRIVE"), tuxgetenv("HOMEPATH"));
				reply.status = BR_OK;
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_IS_REMOTE_DIR:
				data = request.data;
				if (!IsDirectory(data)){
					reply.status = BR_FAILED;
				} else
					reply.status = BR_OK;
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_CREATE_DIR:
				if (!CreateDirectory(request.data, NULL))
					reply.status = BR_FAILED;
				else
					reply.status = BR_OK;
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_REMOVE_FILES:
				dlg->UpdateStatus(CS_REMOVING_FILES);
				if (!RemoveFiles(request.data))
					reply.status = BR_FAILED;
				else
					reply.status = BR_OK;
				dlg->UpdateStatus(CS_CONNECTED);
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_GET_MACHINE_TYPE:
				GetSystemInfo(&si);
				switch(si.dwProcessorType){
				case PROCESSOR_INTEL_386:
				case PROCESSOR_INTEL_486:
				case PROCESSOR_INTEL_PENTIUM:
					strcpy(reply.data, "i386");
					reply.status = BR_OK;
					break;
				case PROCESSOR_MIPS_R4000:
					strcpy(reply.data, "mips");
					reply.status = BR_OK;
					break;
				case PROCESSOR_ALPHA_21064:
					strcpy(reply.data, "alpha");
					reply.status = BR_OK;
					break;
				default:
					reply.status = BR_FAILED;
				}
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_SEND_FILE:
				dlg->m_hFile = CreateFile(request.data, GENERIC_WRITE, 0, NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (dlg->m_hFile == INVALID_HANDLE_VALUE){
					reply.status = BR_FAILED;
				} else {
					reply.status = BR_OK;
					dlg->UpdateStatus(CS_RECV_FILE);
				}
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_RUN:
				if (!CommandStart(request.data)){
					reply.status = BR_FAILED;
				} else {
					reply.status = BR_OK;
					dlg->UpdateStatus(CS_RUNNING_COMMAND);
				}

				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_KILL_TLISTEN:
				dlg->UpdateStatus(CS_KILL_TLISTEN);
				data = request.data;
				if (!KillTlisten(data))
					reply.status = BR_FAILED;
				else
					reply.status = BR_OK;
				dlg->UpdateStatus(CS_CONNECTED);
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_CLEAN_IPC:
				dlg->UpdateStatus(CS_CLEAN_IPC);
				if (!CleanIpc())
					reply.status = BR_FAILED;
				else
					reply.status = BR_OK;
				dlg->UpdateStatus(CS_CONNECTED);
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			default:
				FatalMessage("Unknown request type %d",
					request.type);
				reply.status = BR_INVALID_REQUEST;
				(void)dlg->m_cbs.SendReply(reply);
				(void)dlg->m_cbs.Disconnect();
				dlg->UpdateStatus(CS_WAIT_CONNECT);
				continue;
			}
		case CS_RECV_FILE:
			if (!dlg->m_cbs.GetRequest(request, dlg->m_hEvent)){
				(void)dlg->m_cbs.Disconnect();
				dlg->UpdateStatus(CS_WAIT_CONNECT);
				continue;
			}
			switch(request.type){
			case BR_FILE_DATA:
				if (!WriteFile(dlg->m_hFile, request.data, request.size, &dwWritten, NULL) ||
					dwWritten != request.size){
					reply.status = BR_FAILED;
					CloseHandle(dlg->m_hFile);
					dlg->m_hFile = 0;
					dlg->UpdateStatus(CS_CONNECTED);
				} else
					reply.status = BR_OK;

				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_EOF:
				CloseHandle(dlg->m_hFile);
				dlg->m_hFile = 0;
				dlg->UpdateStatus(CS_CONNECTED);
				reply.status = BR_OK;
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			default:
				FatalMessage("Unexpected request type %d during file transfer",
					request.type);
				reply.status = BR_INVALID_REQUEST;
				(void)dlg->m_cbs.SendReply(reply);
				(void)dlg->m_cbs.Disconnect();
				dlg->UpdateStatus(CS_WAIT_CONNECT);
				continue;
			}
		case CS_RUNNING_COMMAND:
			if (!dlg->m_cbs.GetRequest(request, dlg->m_hEvent)){
				(void)dlg->m_cbs.Disconnect();
				dlg->UpdateStatus(CS_WAIT_CONNECT);
				continue;
			}
			switch(request.type){
			case BR_RUN_OUTPUT:
				if (!CommandOutput(reply, dlg->m_hEvent))
					reply.status = BR_FAILED;
				else if (reply.status == BR_OK)
					dlg->UpdateStatus(CS_CONNECTED);
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			case BR_RUN_CANCEL:
				if (!CommandCancel())
					reply.status = BR_FAILED;
				else
					reply.status = BR_OK;
				if (!dlg->m_cbs.SendReply(reply)){
					(void)dlg->m_cbs.Disconnect();
					dlg->UpdateStatus(CS_WAIT_CONNECT);
				}
				continue;
			default:
				FatalMessage("Unexpected request type %d during command execution",
					request.type);
				reply.status = BR_INVALID_REQUEST;
				(void)dlg->m_cbs.SendReply(reply);
				(void)dlg->m_cbs.Disconnect();
				dlg->UpdateStatus(CS_WAIT_CONNECT);
				continue;
			}
		}
	}
	return 0;
}
