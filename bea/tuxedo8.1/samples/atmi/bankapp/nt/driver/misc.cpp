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
// #ident	"@(#) samples/atmi/bankapp/nt/driver/misc.cpp	$Revision: 1.5 $"

// misc.cpp : implementation file
//

#include "stdafx.h"
#include "driver.h"
#include "drivedlg.h"
#include <ctype.h>
#include <io.h>
#include <fcntl.h>
#include "remote.h"
#include "misc.h"
#include <stdarg.h>
#include <sys/stat.h>
#include "config.h"
#include "initconf.h"
#include <winperf.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CString envfile;
CString makefile;

static HWND hConsole;

char*
ErrorMessage(DWORD dwError)
{
	static CHAR szMesg[1024];
	DWORD cMsgLen;
	CHAR* msgBuf;
	char* ptr;

	cMsgLen = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, dwError, MAKELANGID(0, SUBLANG_ENGLISH_US),
		(LPTSTR) &msgBuf, 1024, NULL);

	if (!cMsgLen)
		sprintf(szMesg, "Unknown error %d", dwError);
	else {
		strcpy(szMesg, msgBuf);
		LocalFree((HLOCAL)msgBuf);
	}

	ptr = strrchr(szMesg, '\n');
	if (ptr)
		*ptr = 0;

	return szMesg;
}

void
Message(const char* fmt, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, fmt);

	vsprintf(buf, fmt, args);

	CWnd::GetActiveWindow()->MessageBox(buf, "Bankapp Driver Error", MB_OK);
}

void
InfoMessage(const char* fmt, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, fmt);

	vsprintf(buf, fmt, args);

	CWnd::GetActiveWindow()->MessageBox(buf, "Bankapp Driver Info", MB_OK);
}

void
WarningMessage(const char* fmt, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, fmt);

	vsprintf(buf, fmt, args);

	CWnd::GetActiveWindow()->MessageBox(buf, "Bankapp Driver Warning", MB_OK);
}

void
FatalMessage(const char* fmt, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, fmt);

	vsprintf(buf, fmt, args);

	CWnd::GetActiveWindow()->MessageBox(buf, "Bankapp Driver Fatal Error", MB_OK|MB_ICONSTOP);
}

// Determine if a file is readable, possibly with a pattern
BOOL
IsFileReadable(char* name)
{
	CStringArray* caMatches = expand_files_in_dir(NULL, name);

	if (!caMatches)
		return FALSE;

	CStringArray& caFiles = *caMatches;

	for (int i = 0 ; i < caFiles.GetSize() ; i++){
		if (_access(caFiles[i], 0) == -1){
			delete caMatches;
			return FALSE;
		}
	}

	delete caMatches;
	return TRUE;
}

// Determine if a directory exists on the local machine
BOOL IsLocalDir(const char* name)
{
	struct _stat statbuf;

	if (_stat(name, &statbuf) == -1)
		return FALSE;

	if ((statbuf.st_mode & _S_IFMT) != _S_IFDIR)
		return FALSE;

	return TRUE;
}

// Determine if file1 is newer than timeRef
BOOL
IsFileNewer(const char* file1, time_t timeRef)
{
	struct _stat statbuf1;

	if (_stat(file1, &statbuf1) == -1){
		// Need to rebuild
		return TRUE;
	}

	if (statbuf1.st_mtime > timeRef)
		return TRUE;

	return FALSE;
}

// Substitute lines in a file, and output in a new file
BOOL
substitute(char* ifile, char* ofile, CStringArray& patterns, CStringArray& replacements)
{
	FILE* finput = fopen(ifile, "r");

	if (!finput){
		FatalMessage("Cannot open %s: %s", ifile, strerror(errno));
		return FALSE;
	}

	FILE* foutput = fopen(ofile, "w");

	if (!foutput){
		FatalMessage("Cannot create %s: %s", ofile, strerror(errno));
		fclose(finput);
		return FALSE;
	}

	char buf[BUFSIZ];

	while (fgets(buf, sizeof buf, finput)){
		BOOL bReplaced = FALSE;
		for (int i = 0 ; i < patterns.GetSize() ; i++){
			if (strncmp(patterns[i], buf, patterns[i].GetLength()) == 0){
				fputs(replacements[i], foutput);
				putc('\n', foutput);
				bReplaced = TRUE;
				break;
			}
		}
		if (!bReplaced)
			fputs(buf, foutput);
	}

	fclose(finput);
	fclose(foutput);

	return TRUE;
}

// Copy ifile to ofile
BOOL
CopyFile(CString& ifile, CString& ofile)
{
	FILE* finput = fopen(ifile, "rb");

	if (!finput){
		FatalMessage("Cannot open %s: %s", (LPCSTR)ifile, strerror(errno));
		return FALSE;
	}

	FILE* foutput = fopen(ofile, "wb");

	if (!foutput){
		FatalMessage("Cannot create %s: %s", (LPCSTR)ofile, strerror(errno));
		fclose(finput);
		return FALSE;
	}

	char buf[BUFSIZ];
	unsigned count;

	while ((count = fread(buf, 1, sizeof buf, finput)) > 0){
		if (fwrite(buf, 1, count, foutput) != count){
			FatalMessage("Error Writing to %s: %s", (LPCSTR)ofile, strerror(errno));
			fclose(finput);
			fclose(foutput);
			return FALSE;
		}
	}

	fclose(finput);
	fclose(foutput);

	return TRUE;
}

// Build a argv array from a null terminated, variable length list of arguments
static CStringArray*
mk_argv(char* argv0, char* arg, va_list args)
{
	CStringArray* argv = new CStringArray;
	argv->SetSize(0, 10);

	if (argv0)
		argv->Add(argv0);

	if (!arg)
		return argv;

	argv->Add(arg);

	while ((arg = va_arg(args, char*)) != NULL)
		argv->Add(arg);

	return argv;
}

// Getopt equivalent
static int
getopt(CStringArray& argv, char* opts, int& optind, const char*& optarg)
{
	// optarg is NULL in most return situations
	optarg = NULL;

	if (optind >= argv.GetSize()){
		// Exhausted all arguments
		return EOF;
	}

	static const char* cur_opt;

	if (optind == 1){
		// Reinitialize scan
		cur_opt = NULL;
	}

	if (cur_opt == NULL || *cur_opt == 0){
		// Fetch the next argument
		const char* arg = (LPCSTR)argv[optind];
		if (*arg != '-'){
			// Argument does not begin with -: exhausted all options
			return EOF;
		}
		if (arg[1] == '\0'){
			// Argument is an isolated -: this is not an option,
			// but the stdin(out) indicator.
			return EOF;
		}
		if (arg[1] == '-' && arg[2] == '\0'){
			// Argument is --: separates the options from the
			// parameters
			optind++;
			return EOF;
		}

		cur_opt = arg + 1;
	}
		
	char opt_char = *cur_opt++;

	char* ptr;

	if ((ptr = strchr(opts, opt_char)) == NULL){
		// Argument letter is not in args: wrong option
		Message("%s: Illegal option -- %c", (LPCSTR)argv[0], opt_char);
		if (*cur_opt == 0)
			optind++;
		return '?';
	}
	
	if (*(ptr + 1) != ':'){
		// Option does not require an argument: return option letter
		if (*cur_opt == 0)
			optind++;
		return opt_char;
	}
	
	if (*cur_opt == 0 && optind == argv.GetSize() - 1){
		// There is no argument immediately after the option letter or
		// after the option
		optind++;
		Message("%s: Missing argument for option %c", (LPCSTR)argv[0], opt_char);
		return '?';
	}

	if (*cur_opt){
		// Option argument immediately follows argument letter
		optarg = cur_opt;
		cur_opt = 0;
		optind++;
		return opt_char;
	}
	
	// Option argument is next argument in list
	optarg = (LPCSTR)argv[optind + 1];
	cur_opt = 0;
	optind += 2;
	return opt_char;
}

// Retrieve computer name
static void
GetUname(CString& name)
{
	char buf[64];
	unsigned long length = sizeof buf;

	GetComputerName(buf, &length);

	name = buf;
}

// Retrieve a variable definition in an environ file
// Two formats exists. Unix files start with name=
// NT files start with set name=
static CString*
FileGetenv(const char* var, const char* file)
{
	FILE* fd = fopen(file, "r");
	if (!fd)
		return NULL;

	char buf[BUFSIZ];

	int len = strlen(var);
	while (fgets(buf, sizeof buf, fd)){
		char* anchor;
		if (strncmp(buf, "set ", 4) == 0)
			anchor = buf + 4;
		else
			anchor = buf;
		if (strncmp(anchor, var, len) == 0){
			char* start;
			char* equal = strchr(buf, '=');
			if (equal)
				start = equal + 1;
			else
				start = buf;
			CString* reply = new CString(start);

			fclose(fd);
			return reply;
		}
	}

	fclose(fd);
	return NULL;
}

void show_console()
{
	if (!hConsole){
		hConsole = FindWindow("ConsoleWindowClass", NULL);
		if (!hConsole)
			return;
	}

	ShowWindow(hConsole, SW_SHOW);
	UpdateWindow(hConsole);
}

void hide_console()
{
	if (!hConsole){
		hConsole = FindWindow("ConsoleWindowClass", NULL);
		if (!hConsole)
			return;
	}

	ShowWindow(hConsole, SW_HIDE);
	UpdateWindow(hConsole);
}

// Replacement for _popen that does not expect a console.
static HANDLE hChild;

FILE* popen(const char* cmd, const char* type)
{
	static BOOL		bFirst = TRUE;
	HANDLE			hPipe[2];
	SECURITY_ATTRIBUTES	sa;
	int			side;
	HANDLE			hProcess;
	FILE*			fd;
	int			n;
	int			flags;
	STARTUPINFOA		sia;
	PROCESS_INFORMATION	pi;
	char			cmdline[1024];

	if (bFirst){
		bFirst = FALSE;

		_dup2(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_RDWR), 0);
		_dup2(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_RDWR), 1);
		_dup2(_open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_RDWR), 2);
	}

	/*
	 * Create a pipe with both sides inheritable
	 */
	sa.nLength = sizeof sa;
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	
	if (!CreatePipe(&hPipe[0], &hPipe[1], &sa, 0)){
		Message("Cannot create pipe: %s", ErrorMessage(GetLastError()));
		return NULL;
	}

	switch(type[0]){
	case 'r':
		/*
		 * Make the read side not inheritable, so that the
		 * child only gets the write side
		 */
		side = 0;
		flags = _O_RDONLY;
		break;
	case 'w':
		/*
		 * Make the write side not inheritable, so that the
		 * child only gets the read side
		 */
		side = 1;
		flags = _O_WRONLY;
		break;
	default:
		CloseHandle(hPipe[0]);
		CloseHandle(hPipe[1]);
		Message("Invalid pipe type %s", type);
		return NULL;
	}
		
	hProcess = GetCurrentProcess();
	if (!DuplicateHandle(hProcess, hPipe[side], hProcess, &hPipe[side],
	    0, FALSE, DUPLICATE_SAME_ACCESS|DUPLICATE_CLOSE_SOURCE)){
		Message("Cannot duplicate pipe handle: %s",
			ErrorMessage(GetLastError()));
		CloseHandle(hPipe[0]);
		CloseHandle(hPipe[1]);
		return NULL;
	}

	/*
	 * Create a stdio fd for the local (non inheritable) side
	 */
	switch(type[1]){
	case 't':
	default:
		flags |= _O_TEXT;
		break;
	case 'b':
		flags |= _O_BINARY;
		break;
	}
	n = _open_osfhandle((long)hPipe[side], flags);

	if (n == -1){
		Message("Cannot get os file handle: %s", strerror(errno));
		CloseHandle(hPipe[0]);
		CloseHandle(hPipe[1]);
		return NULL;
	}

	fd = fdopen(n, type);
	if (!fd){
		Message("Cannot get stdio file handle: %s", strerror(errno));
		_close(n);
		CloseHandle(hPipe[1 - side]);
		return NULL;
	}

	/*
	 * Create child process, with appropriate stdin/stdout replaced with
	 * inheritable (remote) side of pipe
	 */
	memset(&sia, 0, sizeof sia);
	sia.cb = sizeof sia;
	sia.dwFlags = STARTF_USESTDHANDLES;
	switch(side){
	case 0:
		sia.hStdOutput = hPipe[1];
		sia.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		break;
	case 1:
		sia.hStdInput = hPipe[0];
		sia.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		break;
	}
	sia.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	

	sprintf(cmdline, "cmd /c %s", cmd);

	if (!CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &sia,
	    &pi)){
		Message("Cannot create process: %s", ErrorMessage(GetLastError()));
		fclose(fd);
		CloseHandle(hPipe[1 - side]);
		return NULL;
	}

	/*
	 * Store child process handle for pclose
	 */
	hChild = pi.hProcess;

	CloseHandle(pi.hThread);

	/*
	 * Close inheritable side in parent process
	 */
	CloseHandle(hPipe[1 - side]);

	return fd;
}

int pclose(FILE* fd)
{
	DWORD	dwCode;

	/*
	 * Wait for child to terminate
	 */
	WaitForSingleObject(hChild, INFINITE);

	/*
	 * Get child status
	 */
	GetExitCodeProcess(hChild, &dwCode);

	return dwCode;
}
	
// Thread procedure to get data from ud pipe and update %age
static void GetUdOutput(LPVOID pParam)
{

	CDlgUdOut* dlg = (CDlgUdOut*)pParam;
	char line[60];
	char buf[BUFSIZ];

	int length = 0;
	int curDone = 0;
	int percentDone = 0;
	int percentDisplayed = -1;
	int selEnd = 0;

	memset(line, ' ', sizeof line - 1);
	line[sizeof line - 1] = '\0';

	dlg->m_percent.SetWindowText(line);
	dlg->m_warnings = 0;
	dlg->m_errors = 0;

	length = dlg->m_percent.GetWindowTextLength();

	while (fgets(buf, sizeof buf, dlg->m_pipe)){
		if (strncmp("RTN pkt", buf, 7) == 0){
			curDone++;
			percentDone = curDone * 100 / dlg->m_max;
			if (percentDone != percentDisplayed){
				int null = sprintf(line + length / 2, "%d %%", percentDone);
				line[length / 2 + null] = ' ';
				dlg->m_percent.SetWindowText(line);
				percentDisplayed = percentDone;
				int maxSel = (length * percentDone) / 100;
				dlg->m_percent.SetSel(0, maxSel);
			}
		} else if (strstr(buf, "_CAT:994") != NULL){
			dlg->m_warnings++;
		} else if (strstr(buf, "_CAT:") != NULL){
			dlg->m_errors++;
		}
	}

	dlg->m_exitcode = pclose(dlg->m_pipe);

	dlg->CanDestroy();

	// Terminate the thread and deallocate the thread object
	AfxEndThread(0);
}

// Run a ud command, showing the progress.
// Assumes FML.
// Must run on the master machine.
// Works in a way similar to RunCommand, but shows the %age done
// rather than the actual output
static BOOL RunUd(const char* ud_source, const char* window_title)
{
	// Create population data, and copy it in a temporary file.
	// Count the number of calls generated.

	CString full_command = "bankvar.mp1";
	const char* tmpFile = "ud.tmp";

	full_command += " 2>&1 & ";
	full_command += ud_source;
	full_command += " 2>&1";

	FILE* fout = fopen(tmpFile, "w");
	if (!fout){
		Message("Cannot create %s: %s", tmpFile, strerror(errno));
		return FALSE;
	}

	FILE* fd = popen(full_command, "rt");
	if (!fd){
		Message("Cannot run %s: %s", full_command, strerror(errno));
		fclose(fout);
		_unlink(tmpFile);
		return FALSE;
	}

	char buf[BUFSIZ];

	int countTotal = 0;
	while (fgets(buf, sizeof buf, fd)){
		if (strcmp(buf, "n\n") == 0)
			countTotal++;
		fputs(buf, fout);
	}

	pclose(fd);
	fclose(fout);

	// Start ud and capture output
	full_command = "bankvar.mp1";
	full_command += " 2>&1 & ud -t 30 < ";
	full_command += tmpFile;
	full_command += " 2>&1";

	fd = popen(full_command, "rt");
	if (!fd){
		Message("Cannot run %s: %s", full_command, strerror(errno));
		_unlink(tmpFile);
		return FALSE;
	}

	CDlgUdOut dlg;

	dlg.m_pipe = fd;
	dlg.m_max = countTotal;
	dlg.m_title = window_title;

	dlg.m_pThread = AfxBeginThread((AFX_THREADPROC)GetUdOutput, &dlg,
		0, 0, CREATE_SUSPENDED);
	if (!dlg.m_pThread){
		FatalMessage("Cannot create command thread");
		pclose(fd);
		_unlink(tmpFile);
		return FALSE;
	}

	int response = dlg.DoModal();

	if (_unlink(tmpFile) == -1)
		WarningMessage("Cannot delete %s: %s", tmpFile, strerror(errno));

	if (dlg.m_exitcode != 0)
		return FALSE;

	return TRUE;
}

BOOL Populate()
{
	return RunUd("gendata", "Populate the database");
}

BOOL Gentrans()
{
	CTransCount dlg;
	char command[25];
	char title[50];

	dlg.m_ntrans = 10;

	if (dlg.DoModal() != IDOK)
		return FALSE;

	sprintf(command, "gentran -n %d", dlg.m_ntrans);
	sprintf(title, "Generate %d transactions", dlg.m_ntrans);

	return RunUd(command, title);
}

static void mk_nodenms(CStringArray& nodenms, CUIntArray& nodenums, CStringArray& argv, int optind)
{
	for (int i = optind ; i < argv.GetSize() ; i++){
		nodenms.Add(argv[i]);
	}

	char name[30];
	CString* uname_env;

	if (nodenums.GetSize() == 0){
		if (nodenms.GetSize() == 0){

			for (i = 1 ; ; i++){
				sprintf(name, "bankvar.mp%d", i);

				if (!IsFileReadable(name)){
					sprintf(name, "bankvar.mp%d.cmd", i);
					if (!IsFileReadable(name))
						break;
				}

				uname_env = FileGetenv("UNAME", name);
				if (uname_env){
					nodenms.Add(*uname_env);
					delete uname_env;
				}
			}
		}
	} else {
		for (i = 0 ; i < nodenums.GetSize() ; i++){
			sprintf(name, "bankvar.mp%d", nodenums[i]);

			if (!IsFileReadable(name)){
				sprintf(name, "bankvar.mp%d.cmd", nodenums[i]);
				if (!IsFileReadable(name));
					continue;
			}
			uname_env = FileGetenv("UNAME", name);
			if (uname_env){
				nodenms.Add(*uname_env);
				delete uname_env;
			}
		}
	}
}

// Build source file list
CStringArray&
SourceFileList()
{
	static CStringArray sl;

	if (sl.GetSize() == 0){
		// First time. Build permanent file list
		FILE* fd = popen("nmake -nologo -f nt/bankapp.mak list", "rt");
		if (!fd){
			FatalMessage("Cannot start nmake: %s (%d)", strerror(errno), GetLastError());
			return sl;
		}
		
		char buf[100];
		char* ptr;

		while (fgets(buf, sizeof buf, fd)){
			if (strncmp(buf, "samples\\atmi\\bankapp\\", 21) == 0)
				ptr = buf + 21;
			else
				ptr = buf;
			char* ptr2 = strrchr(ptr, '\n');
			if (ptr2)
				*ptr2 = '\0';
			sl.Add(ptr);
		}
		pclose(fd);
	}

	return sl;
}

// Determine if propagation has been done to all (or particular machines)
// Check against all the files that can be propagated on the target machine
// Site1 is the local site, where no propagation occurs.
BOOL
IsPropagated()
{
	BOOL bFirst = TRUE;
	CStringArray sl2;

	sl2.SetSize(0, 10);

	for (int i = 1 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		if (pSite->m_timePropagated == 0)
			return FALSE;

		if (bFirst){
			CStringArray& sl = SourceFileList();

			// Build variant file list
			CStringArray* bankvar1 = expand_files_in_dir(NULL, "bankvar.mp*");
			CStringArray* bankapp_mak1 = expand_files_in_dir(NULL, "bankvar.mak*");

			for (i = 0 ; i < sl.GetSize() ; i++)
				sl2.Add(sl[i]);

			if (bankvar1){
				CStringArray& bankvar = *bankvar1;

				for (i = 0 ; i < bankvar.GetSize() ; i++)
					sl2.Add(bankvar[i]);

				delete bankvar1;
			}

			if (bankapp_mak1){
				CStringArray& bankapp_mak = *bankapp_mak1;

				for (i = 0 ; i < bankapp_mak.GetSize() ; i++)
					sl2.Add(bankapp_mak[i]);

				delete bankapp_mak1;
			}

			bFirst = FALSE;
		}

		for (i = 0 ; i < sl2.GetSize() ; i++){
			if (IsFileNewer(sl2[i], pSite->m_timePropagated))
				return FALSE;
		}
	}

	return TRUE;
}

// Determine if different types of build have been done
BOOL
IsBuilt(BuildItem bi)
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		if (i > 0 && pSite->m_timePropagated == 0)
			return FALSE;
		switch(bi){
		case BI_BUILD:
			if (pSite->m_timeBuild == 0 || pSite->m_timePropagated > pSite->m_timeBuild)
				return FALSE;
			break;
		case BI_BANKDL:
			if (pSite->m_timeBankdl == 0 || pSite->m_timePropagated > pSite->m_timeBankdl)
				return FALSE;
			break;
		case BI_TLOG:
			if (pSite->m_timeTlog == 0 || pSite->m_timePropagated > pSite->m_timeTlog)
				return FALSE;
			break;
		}
	}

	return TRUE;
}

// Determine if different types of build have been done
BOOL
IsAnyBuilt(BuildItem bi)
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		CSite* pSite = config.FindSite(i);
		if (!pSite)
			continue;
		if (i > 0 && pSite->m_timePropagated == 0)
			continue;
		switch(bi){
		case BI_BUILD:
			if (pSite->m_timeBuild != 0)
					return TRUE;
			break;
		case BI_BANKDL:
			if (pSite->m_timeBankdl != 0)
				return TRUE;
			break;
		case BI_TLOG:
			if (pSite->m_timeTlog != 0)
				return TRUE;
			break;
		}
	}

	return FALSE;
}
// Determine if a process is active
BOOL IsActive(char* process)
{
	char index_proc_thread_obj[50];
	PERF_DATA_BLOCK* pdb;
	DWORD dwType;
	DWORD dwSize;
	DWORD dwRes;
	DWORD dwProcessIndex;

	// Determine the process and thread indices in the registry
	char* titleBuffer;
	char* ptr;
	unsigned len;
	unsigned index;
	DWORD dwThreadIndex;
	int found;

	// Get Counter names and indices
	dwRes = RegQueryValueEx(HKEY_PERFORMANCE_DATA, "Counter 009", 0, &dwType, 0, &dwSize);
	if (dwRes != ERROR_SUCCESS){
		Message("Cannot get title size: %d", dwRes);
		return FALSE;
	}

	if ((titleBuffer = new char[dwSize]) == NULL){
		Message("Cannot allocate titleBuffer");
		return FALSE;
	}

	dwRes = RegQueryValueEx(HKEY_PERFORMANCE_DATA, "Counter 009",
		0, &dwType, (LPBYTE)titleBuffer, &dwSize);
	if (dwRes != ERROR_SUCCESS){
		Message("Cannot get title data: %d", dwRes);
		delete titleBuffer;
		return FALSE;
	}

	ptr = titleBuffer;

	found = 0;
	while (found < 2 && (len = strlen(ptr)) != 0){
		index = atoi(ptr);
		ptr += len + 1;
		if (strcmp(ptr, "Process") == 0){
			dwProcessIndex = index;
			found++;
		}
		else if (strcmp(ptr, "Thread") == 0){
			dwThreadIndex = index;
			found++;
		}
		ptr += strlen(ptr) + 1;
	}

	delete titleBuffer;

	if (found != 2){
		Message("Cannot find all indices");
		return FALSE;
	}

	sprintf(index_proc_thread_obj, "%ld %ld", dwProcessIndex,
		dwThreadIndex);

	// Now retrieve data
	long dwDataSize = 50 * 1024;

	if ((pdb = (PERF_DATA_BLOCK*)malloc(dwDataSize)) == NULL){
		Message("Cannot allocate perf data block");
		return FALSE;
	}

	do {
		dwSize = dwDataSize;

		dwRes = RegQueryValueEx(HKEY_PERFORMANCE_DATA,
			index_proc_thread_obj, 0, &dwType, (LPBYTE)pdb,
			&dwSize);

		if (dwRes == ERROR_MORE_DATA){
			dwDataSize += 1024;
			if ((pdb = (PERF_DATA_BLOCK*)realloc(pdb, dwDataSize)) == NULL){
				Message("Cannot expand perf data block");
				return FALSE;
			}
		}
	} while (dwRes == ERROR_MORE_DATA);

	if (dwRes != ERROR_SUCCESS){
		Message("Cannot get perf data block: %d", dwRes);
		free(pdb);
		return FALSE;
	}

	// Retrieve process data
	PERF_OBJECT_TYPE* pot;
	pot = (PERF_OBJECT_TYPE*)((LPBYTE)pdb + pdb->HeaderLength);

	for (DWORD nObj = 0 ; nObj < pdb->NumObjectTypes ; nObj++){
		if (pot->ObjectNameTitleIndex == dwProcessIndex)
			break;

		pot = (PERF_OBJECT_TYPE*)((PBYTE)pot + pot->TotalByteLength);
	}

	if (nObj == pdb->NumObjectTypes){
		Message("Cannot find process data");
		free(pdb);
		return FALSE;
	}

	PERF_INSTANCE_DEFINITION* pid;
	PERF_COUNTER_BLOCK* pcb;

	pid = (PERF_INSTANCE_DEFINITION*)((LPBYTE)pot + pot->DefinitionLength);

	for (int i = 0 ; i < pot->NumInstances ; i++){
		char* name = (char*)((LPBYTE)pid + pid->NameOffset);
		// Name is in UNICODE
		char AnsiName[32];
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)name, -1, AnsiName, sizeof AnsiName, NULL, NULL);
		if (strcmp(process, AnsiName) == 0)
			break;

		pcb = (PERF_COUNTER_BLOCK*)((LPBYTE)pid + pid->ByteLength);
		pid = (PERF_INSTANCE_DEFINITION*)((LPBYTE)pcb + pcb->ByteLength);
	}

	BOOL bRet;
	if (i == pot->NumInstances)
		bRet = FALSE;
	else
		bRet = TRUE;

	free(pdb);

	return bRet;
}

// Start pipe command to remote machine
static FILE* RunRemote(const char* name, const char* cmd)
{
	CString remCmd = "rsh ";
	FILE*	fd;

	remCmd += name;
	remCmd += " \"";
	remCmd += cmd;
	remCmd += " 2>&1 \"";

	fd = popen(remCmd, "rt");
	if (!fd)
		Message("Cannot run \"%s\" on site %s", cmd, name);

	return fd;
}

// Run a remote command and check exit status
BOOL RunRemoteVerify(const char* name, const char* cmd)
{
	CString fullcmd = cmd;

	fullcmd += " ; echo $?";

	FILE* fd = RunRemote(name, fullcmd);

	if (!fd)
		return FALSE;

	char buf[BUFSIZ];

	if (!fgets(buf, sizeof buf, fd)){
		pclose(fd);
		return FALSE;
	}

	int ret = pclose(fd);

	if (ret != 0)
		return FALSE;

	ret = atoi(buf);

	if (ret)
		return FALSE;

	return TRUE;
}

// Run remote command and return first line
BOOL RunRemoteGetLine(const char* name, const char* cmd, CString& line)
{
	FILE* fd = RunRemote(name, cmd);

	if (!fd)
		return FALSE;

	char buf[BUFSIZ];

	errno = 0;
	if (!fgets(buf, sizeof buf, fd)){
		Message("Cannot get response from site %s: %s", name, strerror(errno));
		pclose(fd);
		return FALSE;
	}

	int ret = pclose(fd);

	if (ret != 0){
		Message("Error closing pipe");
		return FALSE;
	}

	char* ptr = strrchr(buf, '\n');
	if (ptr)
		*ptr = '\0';

	line = buf;

	return TRUE;
}

// Run local command and return first line
BOOL RunLocalGetLine(const char* cmd, CString& line)
{
	CString command;
	command = "bankvar.mp1 & ";
	command += cmd;
	command += " 2>&1";
	FILE* fd = popen(command, "rt");

	if (!fd)
		return FALSE;

	char buf[BUFSIZ];

	if (!fgets(buf, sizeof buf, fd)){
		pclose(fd);
		return FALSE;
	}

	int ret = pclose(fd);

	if (ret != 0)
		return FALSE;

	char* ptr = strrchr(buf, '\n');
	if (ptr)
		*ptr = '\0';

	line = buf;

	return TRUE;
}

// Return a pointer a string with the full hex address
// including port
char*
mk_addr(const char* address, UINT port)
{
	static char res[30];
	int addr[4];

	const char* ptr;

	ptr = address;

	for (int i = 0 ; i < 4 ; i++){
		addr[i] = atoi(ptr);
		ptr = strchr(ptr + 1, '.');
		if (!ptr)
			break;

		ptr++;
	}

	sprintf(res, "0x0002%04x%02x%02x%02x%02x", port,
		addr[0] & 0xFF, addr[1] & 0xFF,
		addr[2] & 0xFF, addr[3] & 0xFF);

	return res;
}

int CountSites()
{
	CSite* pSite;

	int numsites = 0;
	for (int i = 0 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (pSite)
			numsites++;
	}

	return numsites;
}
	
// Generate the ASCII configuration files and configuration related makefiles
// and variable scripts for an MP configuration
BOOL Setup()
{
	// Determine operation mode (verbose, terse)
	CInitMode dlg;

	int response = dlg.DoModal();

	if (response == IDCANCEL)
		return FALSE;

	BOOL bVerbose = dlg.IsVerbose();

	CConfSetup dlgSetup;

	response = dlgSetup.DoModal();

	if (response != IDOK)
		return FALSE;

	// Calculate IPCKEY
	if (config.m_ipckey == 0){
		config.m_ipckey = 80952 + rand() % 200;
	}

	if (bVerbose){
		CConfIpckey dlgIpckey;

		dlgIpckey.m_ipckey = config.m_ipckey;

		response = dlgIpckey.DoModal();
	
		if (response == IDCANCEL){
			config.m_ipckey = 0;
			return FALSE;
		}

		config.m_ipckey = dlgIpckey.m_ipckey;
	}

	
	// Calculate routing criteria
	int numsites = CountSites();
	
	CSite* pSite;
	int* lowrng = new int[numsites];
	int* hirng = new int[numsites];

	if (!lowrng || !hirng){
		FatalMessage("No memory for ranges");
		if (lowrng)
			delete lowrng;
		if (hirng)
			delete hirng;
		return FALSE;
	}

	int inct10 = 100 / numsites;

	for (int i = 1 ; i <= numsites ; i++){

		// Compute the low value of this range
		if (i == 1)
			lowrng[0] = 1;
		else
			lowrng[i - 1] = hirng[i - 2] + 1;

		// Now compute the high value for this range
		if (i == numsites)
			hirng[i - 1] = 10;
		else {
			// Compute the span of this range. We use the increment * 10
			// to smooth out the curve. i.e. for 4 sites we'll do
			// 1-2, 3-5, 6-7, 8-10 instead of 1-2, 3-4, 5-6, 7-10
			hirng[i - 1] = inct10 * i / 10;
		}
	}
	// Create ubbconfig
	FILE* fd = fopen("UBB", "w");

	if (!fd){
		FatalMessage("Cannot create UBB: %s", strerror(errno));
		delete lowrng;
		delete hirng;
		return FALSE;
	}

	// Resources section
	CSite* pLocal = config.FindSite(0);
	fprintf(fd, "*RESOURCES\n");
	fprintf(fd, "IPCKEY\t\t%d\n", config.m_ipckey);
	fprintf(fd, "UID\t\t%d\n", pLocal->m_uid);
	fprintf(fd, "GID\t\t%d\n", pLocal->m_gid);
	fprintf(fd, "PERM\t\t0660\n");
	fprintf(fd, "MAXACCESSERS\t40\n");
	fprintf(fd, "MAXSERVERS\t%d\n", numsites * 15 + 20);
	fprintf(fd, "MAXSERVICES\t%d\n", numsites * 25 + 30);
	fprintf(fd, "MAXCONV\t\t10\n");
	fprintf(fd, "MAXGTT\t\t25\n");

	// ACL stuff (commented out)
	fprintf(fd, "##SECURITY	ACL\n");
	fprintf(fd, "##AUTHSVC	\"..AUTHSVC\"\n");

	if (numsites == 1){
		fprintf(fd, "MASTER\t\tSITE1\n");
		fprintf(fd, "# No OPTIONS set for SHM model bankapp\n");
		fprintf(fd, "MODEL\t\tSHM\n");
	} else {
		/*
		 * Migration is not always possible to a UNIX site,
		 * if the release does not match.
		 */
		for (i = 0 ; i < MAX_SITES ; i++){
			pSite = config.FindSite(i);
			if (!pSite)
				continue;
			if (pSite->m_nSite == 2)
				break;
		}

		if (i < MAX_SITES && pSite && pSite->m_type == OS_NT)
			fprintf(fd, "MASTER\t\tSITE1, SITE2\n");
		else
			fprintf(fd, "MASTER\t\tSITE1\n");
		fprintf(fd, "OPTIONS\t\tLAN\n");
		fprintf(fd, "MODEL\t\tMP\n");
	}

	fprintf(fd, "LDBAL\t\tY\n");
	fprintf(fd, "\n");

	// Machines section
	fprintf(fd, "*MACHINES\n");

	for (i = 0 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (!pSite)
			continue;

		pSite->MachinesSection(fd);
	}

	// Groups section
	fprintf(fd, "*GROUPS\n");

	// ACL stuff (commented out)
	fprintf(fd, "##AUTHGRP	LMID=SITE1	GRPNO=11\n\n");

	// events stuff (commented out)
	fprintf(fd, "##QGRP1	LMID=SITE1	GRPNO=12\n");
	fprintf(fd, "##	TMSNAME=TMS_QM	TMSCOUNT=2\n");
	fprintf(fd, "##	OPENINFO=\"TUXEDO/QM:%s\\qdevice;QSP_BANKAPP\"\n",
		(LPCSTR)config.FindSite(0)->m_appdir);
	fprintf(fd, "\n");
	fprintf(fd, "##MGRGRP1	LMID=SITE1      GRPNO=13\n");
	fprintf(fd, "\n");
	fprintf(fd, "##EVBGRP1	LMID=SITE1      GRPNO=14\n\n");

	fprintf(fd, "DEFAULT:\tTMSNAME=TMS_SQL TMSCOUNT=2\n");
	for (i = 0 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (!pSite)
			continue;

		pSite->GroupsSection(fd);
	}
	// Network section
	if (numsites > 1){
		fprintf(fd, "*NETWORK\n");
		for (i = 0 ; i < MAX_SITES ; i++){
			pSite = config.FindSite(i);
			if (!pSite)
				continue;
			pSite->NetworkSection(fd);
		}
	}

	// Servers section
	fprintf(fd, "*SERVERS\n");

	// ACL stuff (commented out)
	fprintf(fd, "##AUTHSVR	SRVGRP=AUTHGRP	SRVID=1	RESTART=Y  GRACE=0  MAXGEN=2\n");
	fprintf(fd, "##	CLOPT=\"-A\"\n\n");

	// events stuff (commented out)
	fprintf(fd, "##TMQUEUE	SRVGRP=QGRP1	SRVID=1	CONV=N	GRACE=0\n");
	fprintf(fd, "##	CLOPT=\"-s QSP_BANKAPP:TMQUEUE\"\n");
	fprintf(fd, "\n");
	fprintf(fd, "##TMQFORWARD	SRVGRP=QGRP1	SRVID=2	CONV=N	REPLYQ=N GRACE=0\n");
	fprintf(fd, "##	CLOPT=\"-- -e -n -d -q Q_OPENACCT_LOG\"\n");
	fprintf(fd, "\n");
	fprintf(fd, "##TMUSREVT        SRVGRP=EVBGRP1	SRVID=1	GRACE=3600\n");
	fprintf(fd, "##		ENVFILE=\"tmusrevt.env\"\n");
	fprintf(fd, "##		CLOPT=\"-e tmusrevt.out -o tmusrevt.out -A --\n");
	fprintf(fd, "##			-f %s\\tmusrevt.dat\"\n",
		(LPCSTR)config.FindSite(0)->m_appdir);
	fprintf(fd, "##		SEQUENCE=11\n");
	fprintf(fd, "\n");
	fprintf(fd, "##ACCTMGR SRVGRP=MGRGRP1	SRVID=1\n");
	fprintf(fd, "##	CLOPT=\"-A -o ACCTMGR.LOG -- -w 1000.00\"\n");
	fprintf(fd, "##		SEQUENCE=12\n\n");

	fprintf(fd, "DEFAULT:\tRESTART=Y MAXGEN=5 REPLYQ=N CLOPT=\"-A\"\n\n");
	fprintf(fd, "AUDITC\tSRVGRP=BANKB1\tSRVID=1 CONV=Y MIN=1 MAX=10 REPLYQ=Y RQADDR=\"auditc\"\n\n");

	int j;
	for (i = 0, j = 0 ; i < numsites && j < MAX_SITES ; j++){
		pSite = config.FindSite(j);
		if (!pSite)
			continue;
		pSite->ServersSection(fd, lowrng[i], hirng[i]);

		i++;
	}

	// Services section
	fprintf(fd, "*SERVICES\n");
	fprintf(fd, "DEFAULT:\tLOAD=50 AUTOTRAN=N\n");
	fprintf(fd, "\n");
	fprintf(fd, "WITHDRAWAL\tPRIO=50\tROUTING=ACCOUNT_ID\n");
	fprintf(fd, "DEPOSIT\t\tPRIO=50\tROUTING=ACCOUNT_ID\n");
	fprintf(fd, "TRANSFER\tPRIO=50\tROUTING=ACCOUNT_ID\n");
	fprintf(fd, "INQUIRY\t\tPRIO=50\tROUTING=ACCOUNT_ID\n");
	fprintf(fd, "CLOSE_ACCT\tPRIO=40\tROUTING=ACCOUNT_ID\n");

	fprintf(fd, "OPEN_ACCT\tPRIO=40\tROUTING=BRANCH_ID\n");
	fprintf(fd, "BR_ADD\t\tPRIO=20\tROUTING=BRANCH_ID\n");
	fprintf(fd, "TLR_ADD\t\tPRIO=20\tROUTING=BRANCH_ID\n");

	fprintf(fd, "ABAL\t\tPRIO=30\tROUTING=b_id\n");
	fprintf(fd, "TBAL\t\tPRIO=30\tROUTING=b_id\n");
	fprintf(fd, "ABAL_BID\tPRIO=30\tROUTING=b_id\n");
	fprintf(fd, "TBAL_BID\tPRIO=30\tROUTING=b_id\n");
	fprintf(fd, "ABALC_BID\tPRIO=30\tROUTING=b_id\n");
	fprintf(fd, "TBALC_BID\tPRIO=30\tROUTING=b_id\n");

	fprintf(fd, "\n");

	// Routing section
	CString bankh_siterp;

	fprintf(fd, "*ROUTING\n\n");

	// Acount id routing criteria (FML)
	fprintf(fd, "ACCOUNT_ID\tFIELD=ACCOUNT_ID\n");
	fprintf(fd, "\t\tBUFTYPE=\"FML\"\n");
	fprintf(fd, "\t\tRANGES=\"");

	for (i = 0, j = 0 ; i < numsites && j < MAX_SITES ; j++){
		pSite = config.FindSite(j);
		if (!pSite)
			continue;

	 	if (i > 0){
			fprintf(fd, ",");
			bankh_siterp += ", ";
		}

		fprintf(fd, "%d0000-%d9999:BANKB%d", lowrng[i], hirng[i], pSite->m_nSite);

		char lowrange[10];
		sprintf(lowrange, "%d", lowrng[i]);
		bankh_siterp += lowrange;
		i++;
	}
	fprintf(fd, ",*:*\"\n");

	// Branch id routing criteria (FML)
	fprintf(fd, "BRANCH_ID\tFIELD=BRANCH_ID\n");
	fprintf(fd, "\t\tBUFTYPE=\"FML\"\n");
	fprintf(fd, "\t\tRANGES=\"");

	for (i = 0, j = 0 ; i < numsites && j < MAX_SITES ; j++){
		pSite = config.FindSite(j);
		if (!pSite)
			continue;

	 	if (i > 0){
			fprintf(fd, ",");
		}

		fprintf(fd, "%d-%d:BANKB%d", lowrng[i], hirng[i], pSite->m_nSite);

		i++;
	}
	fprintf(fd, ",*:*\"\n");

	// B_id routing criteria (VIEW)
	fprintf(fd, "b_id\t\tFIELD=b_id\n");
	fprintf(fd, "\t\tBUFTYPE=\"VIEW:aud\"\n");
	fprintf(fd, "\t\tRANGES=\"");

	for (i = 0, j = 0 ; i < numsites && j < MAX_SITES ; j++){
		pSite = config.FindSite(j);
		if (!pSite)
			continue;

	 	if (i > 0){
			fprintf(fd, ",");
		}

		fprintf(fd, "%d-%d:BANKB%d", lowrng[i], hirng[i], pSite->m_nSite);

		i++;
	}
	fprintf(fd, ",*:*\"\n");

	fclose(fd);

	delete lowrng;
	delete hirng;

	// Generate bank.h

	CStringArray patterns;
	CStringArray replacements;
	patterns.SetSize(0, 10);
	replacements.SetSize(0, 10);

	CString siterep = "#define SITEREP";
	patterns.Add(siterep);
	siterep += "\t{ ";
	siterep += bankh_siterp;
	siterep += " }";
	replacements.Add(siterep);

	CString nsites = "#define NSITE";
	patterns.Add(nsites);
	char ssites[10];
	sprintf(ssites, "\t%d", numsites);
	nsites += ssites;
	replacements.Add(nsites);

	patterns.Add("#define DTPB");
	replacements.Add("#define DTPB\t\t1");

	if (!IsFileReadable("bankh.org")){
		if (!IsFileReadable("bank.h")){
			FatalMessage("Cannot locate bank.h");
			return FALSE;
		}
		if (!CopyFile((CString)"bank.h", (CString)"bankh.org"))
			return FALSE;
	}

	if (!substitute("bankh.org", "bank.h", patterns, replacements))
		return FALSE;

	// Generate bankvar.mp files

	for (i = 0 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (!pSite)
			continue;

		if (!pSite->CreateBankvar())
			return FALSE;
	}

	// Create makefiles
	for (i = 0 ; i < MAX_SITES ; i++){
		pSite = config.FindSite(i);
		if (!pSite)
			continue;

		if (!pSite->CreateMakefile())
			return FALSE;
	}

	return TRUE;
}

// Determine the environ and makefile for this machine
// Cannot use the configuration, which is present only on
// the master machine
void SetLocalFiles()
{
	if (config.m_bValidConfig){
		// Running on the master
		envfile = "bankvar.mp1.cmd";
		makefile = "bankapp.mak1";
		return;
	}

	CString uname;
	GetUname(uname);

	for (int i = 1 ; i <= MAX_SITES ; i++){
		char env[100];

		sprintf(env, "bankvar.mp%d.cmd", i);
		if (!IsFileReadable(env))
			continue;

		CString* fname = FileGetenv("UNAME", env);
		if (*fname == uname){
			char make[100];
			envfile = env;
			sprintf(make, "bankapp.mak%d", i);
			makefile = make;
			delete fname;
			return;
		}
		delete fname;
	}

	return;
}

#ifdef notdef
/*
 * Expand the pattern in a list of files, recursing on /'s
 */
static struct tree*
expand_files(unsigned char* dir, unsigned char* pattern, char* quotes)
{
	char* slash;
	char* nquotes;
	char* ptr;
	struct tree* list;
	struct tree* head;
	struct tree* tail;
	struct tree* t;
	struct tree* tnew;
	struct tree* result;
	DWORD dwAttr;

	//printf("expand_files(%s, %s)\n", dir, pattern);

	if (dir){
		if ((dwAttr = GetFileAttributes(dir)) == 0xFFFFFFFF)
			return 0;
		if (!(dwAttr &  FILE_ATTRIBUTE_DIRECTORY))
			return 0;
	}

	if (!dir){
		/*
		 * Extract leading drive and /
		 */
		char drive[10];
		int len;

		len = strlen(pattern);
		if (len >= 2){
			if (isalpha(pattern[0]) && pattern[1] == ':'){
				if (len == 2){
					/*
					 * Drive only
					 */
					return 0;
				}
				if (len >= 3 && pattern[2] == '/'){
					sprintf(drive, "%c:/", pattern[0]);
					return expand_files(drive, pattern + 3,
						quotes + 3);
				} else {
					sprintf(drive, "%c:", pattern[0]);
					return expand_files(drive, pattern + 2,
						quotes + 2);
				}
			} else if (pattern[0] == '/'){
				if (pattern[1] == '/'){
					ptr = strchr(pattern + 2, ':');
					if (ptr && ptr[1] == '/'){
						nquotes = quotes + (ptr + 1 - pattern);
						ptr[1] = 0;
						sprintf(drive, "%s/", pattern);
						ptr[1] = '/';
						return expand_files(drive,
							ptr + 2, nquotes);
					}
				} else {
					return expand_files("/", pattern + 1,
						quotes + 1);
				}
			}					
		}
	}
	slash = strchr(pattern, '/');

	if (slash)
		*slash = 0;

	if (slash == pattern){
		result = expand_files(dir, pattern + 1, quotes + 1);
		*slash = '/';
		return result;
	}

	list = expand_files_in_dir(dir, pattern, quotes);
	if (!list){
		if (slash)
			*slash = '/';
		return 0;
	}
		
	if (!slash)
		return list;

	*slash = '/';

	/*
	 * Loop on each entry in the list, appending to the existing directory
	 * and recursing on the pattern remainder
	 */
	head = tail = 0;

	if (slash[1] == 0){
		/*
		 * Special case: return only the directories
		 */
		for (t = list ; t ; t = tnew){
			tnew = t->next;
			if ((dwAttr = GetFileAttributes(string_buffer(t->word))) == 0xFFFFFFFF)
				continue;
			if (!(dwAttr &  FILE_ATTRIBUTE_DIRECTORY))
				continue;

			if (t == list)
				list = t->next;
			remove_token(t);
			add_char_buffer(t->word, '/', QUOTE_NONE);
			if (!head)
				head = tail = t;
			else {
				append_token(tail, t);
				tail = t;
			}
		}
	} else {
		/*
		 * Normal case
		 */
		nquotes = quotes + (slash - pattern);
		for (t = list ; t ; t = t->next){
			result = expand_files(string_buffer(t->word), slash + 1, nquotes);

			if (!result)
				continue;

			if (!head)
				head = result;
			else
				tail->next = result;
			result->prev = tail;

			for (tail = result ; tail->next ; tail = tail->next)
				;
		}
	}

	free_tree(list);

	return head;
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CCommandOut dialog


CCommandOut::CCommandOut(CWnd* pParent /*=NULL*/)
	: CDialog(CCommandOut::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommandOut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	m_pipe = NULL;
	m_exitcode = -1;
}

void CCommandOut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandOut)
	DDX_Control(pDX, IDC_COMMAND_OUTPUT, m_commandOutput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommandOut, CDialog)
	//{{AFX_MSG_MAP(CCommandOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCommandOut::CanDestroy()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CCommandOut message handlers

void CCommandOut::OnOK() 
{
	CDialog::OnOK();
}

void CCommandOut::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CCommandOut::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	
	SetWindowText(m_command);
	GotoDlgCtrl(GetDlgItem(IDC_COMMAND_OUTPUT));

	// Release the thread now that the windows are created
	m_pThread->ResumeThread();

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgUdOut dialog


CDlgUdOut::CDlgUdOut(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUdOut::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUdOut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUdOut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUdOut)
	DDX_Control(pDX, IDC_PERCENT, m_percent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUdOut, CDialog)
	//{{AFX_MSG_MAP(CDlgUdOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgUdOut message handlers

BOOL CDlgUdOut::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	
	SetWindowText(m_title);

	GotoDlgCtrl(GetDlgItem(IDC_PERCENT));

	// Release the thread now that the windows are created
	m_pThread->ResumeThread();

	return FALSE;
}

void CDlgUdOut::CanDestroy()
{
	CWnd* wOk = GetDlgItem(IDOK);
	
	wOk->EnableWindow(TRUE);
	GotoDlgCtrl(wOk);
}
/////////////////////////////////////////////////////////////////////////////
// CTransCount dialog


CTransCount::CTransCount(CWnd* pParent /*=NULL*/)
	: CDialog(CTransCount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransCount)
	m_ntrans = 0;
	//}}AFX_DATA_INIT

	m_ntrans = 10;
}


void CTransCount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransCount)
	DDX_Text(pDX, IDC_TRANSACTION_COUNT, m_ntrans);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransCount, CDialog)
	//{{AFX_MSG_MAP(CTransCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTransCount message handlers

BOOL CTransCount::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GotoDlgCtrl(GetDlgItem(IDC_TRANSACTION_COUNT));

	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CdlgWait dialog


CdlgWait::CdlgWait(CWnd* pParent /*=NULL*/)
	: CDialog(CdlgWait::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdlgWait)
	m_reason = _T("");
	//}}AFX_DATA_INIT
}


void CdlgWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdlgWait)
	DDX_Text(pDX, IDC_WAIT_REASON, m_reason);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdlgWait, CDialog)
	//{{AFX_MSG_MAP(CdlgWait)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CdlgWait message handlers

/////////////////////////////////////////////////////////////////////////////
// Wait modeless dialog
HCURSOR CWait::m_hcurWait;

CWait::CWait()
{
	m_bStarted = FALSE;
	m_hcurOld = NULL;
	if (!m_hcurWait)
		m_hcurWait = ::LoadCursor(NULL, IDC_WAIT);
}

void CWait::start(CString& reason)
{
	m_dlg.m_reason = reason;

	m_dlg.Create(IDD_WAIT);
	m_bStarted = TRUE;

	m_hcurOld = ::SetCursor(m_hcurWait);
}

void CWait::stop()
{
	if (m_bStarted){
		m_bStarted = FALSE;
		m_dlg.DestroyWindow();
		(void)::SetCursor(m_hcurOld);
	}
}
