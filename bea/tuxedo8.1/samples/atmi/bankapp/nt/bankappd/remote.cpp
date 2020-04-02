/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
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
// #ident	"@(#) samples/atmi/bankapp/nt/bankappd/remote.cpp	$Revision: 1.4 $"

#include "stdafx.h"
#include "remote.h"
#include "misc.h"

CBankappRemote::~CBankappRemote()
{
	if (hPipe)
		CloseHandle(hPipe);
}

CBankappServer::CBankappServer() : CBankappRemote()
{
	m_hAsyncEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CBankappServer::~CBankappServer()
{
	CloseHandle(m_hAsyncEvent);
}

void
CBankappServer::WaitForPipeOrEvent(HANDLE hEvent)
{
	HANDLE handles[2];

	handles[0] = m_hAsyncEvent;
	handles[1] = hEvent;

	int nevents = hEvent ? 2 : 1;
		
	DWORD dwWait = WaitForMultipleObjects(nevents, handles, FALSE, INFINITE);

	if (dwWait == WAIT_FAILED){
		FatalMessage("Wait failed: %s", ErrorMessage(GetLastError()));
		AfxEndThread(1);
	}

	if (dwWait == WAIT_OBJECT_0){
		// Something on the pipe
		return;
	}

	// Event was triggered
	AfxEndThread(0);
}

BOOL
CBankappServer::Create()
{
	name = "\\\\.\\pipe\\" BANKAPP_PIPE;
	hPipe = CreateNamedPipe(name, PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_MESSAGE|PIPE_WAIT|PIPE_READMODE_MESSAGE, 1,
		0, 0, 5000, NULL);
	if (hPipe == INVALID_HANDLE_VALUE){
		FatalMessage("Cannot create daemon pipe %s",
			(LPCSTR)name);
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappServer::Accept(HANDLE hEvent)
{
	OVERLAPPED ovl;

	ovl.Internal = 0;
	ovl.InternalHigh = 0;
	ovl.Offset = 0;
	ovl.OffsetHigh = 0;
	ovl.hEvent = m_hAsyncEvent;

	(void)ConnectNamedPipe(hPipe, &ovl);
	if (GetLastError() != ERROR_IO_PENDING){
		FatalMessage("Accept failed: %s",
			ErrorMessage(GetLastError()));
		return FALSE;
	}

	WaitForPipeOrEvent(hEvent);

	DWORD dwTransferred;

	if (!GetOverlappedResult(hPipe, &ovl, &dwTransferred, FALSE)){
		FatalMessage("Cannot accept connection: %s",
			ErrorMessage(GetLastError()));
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappServer::Disconnect()
{
	(void)FlushFileBuffers(hPipe);
	(void)DisconnectNamedPipe(hPipe);
	return TRUE;
}
		
BOOL
CBankappServer::GetRequest(BankappRequest& br, HANDLE hEvent)
{
	DWORD dwRead;

	OVERLAPPED ovl;

	ovl.Internal = 0;
	ovl.InternalHigh = 0;
	ovl.Offset = 0;
	ovl.OffsetHigh = 0;
	ovl.hEvent = m_hAsyncEvent;

	if (!ReadFile(hPipe, &br, sizeof br, &dwRead, &ovl)){
		if (GetLastError() != ERROR_IO_PENDING){
			FatalMessage("Read error on connection: %s",
				ErrorMessage(GetLastError()));
			return FALSE;
		}

		WaitForPipeOrEvent(hEvent);

		if (!GetOverlappedResult(hPipe, &ovl, &dwRead, FALSE)){
			FatalMessage("Read error on connection: %s",
				ErrorMessage(GetLastError()));
			return FALSE;
		}
	}
			
	if (dwRead != sizeof br){
		FatalMessage("Received invalid request size %u/%u",
			dwRead, sizeof br);
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappServer::SendReply(BankappReply& br)
{
	DWORD dwWritten;

	if (!WriteFile(hPipe, &br, sizeof br, &dwWritten, NULL)){
		FatalMessage("Write error on connection: %s",
			ErrorMessage(GetLastError()));
		return FALSE;
	}

	if (dwWritten != sizeof br){
		FatalMessage("Sent invalid reply size %u/%u",
			dwWritten, sizeof br);
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::Connect(CString& site)
{
	name = "\\\\";
	name += site;
	name += "\\pipe\\" BANKAPP_PIPE;

	do {
		if (!WaitNamedPipe(name, NMPWAIT_WAIT_FOREVER)){
			Message("Cannot access bankappd server on site %s: %s",
				(LPCSTR)site, ErrorMessage(GetLastError()));
			return FALSE;
		}

		hPipe = CreateFile(name, GENERIC_READ|GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
	} while (hPipe == INVALID_HANDLE_VALUE &&
	    GetLastError() == ERROR_PIPE_BUSY);

	if (hPipe == INVALID_HANDLE_VALUE){
		Message("Cannot connect to bankappd pipe on site %s: %s",
			(LPCSTR)site, ErrorMessage(GetLastError()));
		return FALSE;
	}

	DWORD dwState = PIPE_READMODE_MESSAGE;

	if (!SetNamedPipeHandleState(hPipe, &dwState, NULL, NULL)){
		Message("Cannot set bankappd server pipe state for site %s: %s",
			(LPCSTR)site, ErrorMessage(GetLastError()));
		return FALSE;
	}


	return TRUE;
}

BOOL
CBankappClient::SendRequest(BankappRequest& request, BankappReply& reply)
{
	DWORD dwRead;

	if (!TransactNamedPipe(hPipe, &request, sizeof request, &reply, sizeof reply,
	    &dwRead, NULL)){
		Message("Cannot send request to bankappd server: %s",
			ErrorMessage(GetLastError()));
		return FALSE;
	}

	if (dwRead != sizeof reply){
		Message("Received invalid reply length from bankappd server (%d/%d)",
			dwRead, sizeof reply);
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::Disconnect()
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_DISCONNECT;

	if (!SendRequest(request, reply))
		return FALSE;

	CloseHandle(hPipe);
	hPipe = 0;

	return TRUE;
}

BOOL
CBankappClient::GetTuxdir(CString& tuxdir)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_GET_TUXDIR;

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot get remote tuxdir");
		return FALSE;
	}

	tuxdir = reply.data;

	return TRUE;
}

BOOL
CBankappClient::GetMachineType(CString& mach)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_GET_MACHINE_TYPE;

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot get remote machine type");
		return FALSE;
	}

	mach = reply.data;

	return TRUE;
}

BOOL
CBankappClient::IsDirectory(CString& dir, BOOL& bRes)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_IS_REMOTE_DIR;
	strcpy(request.data, dir);

	if (!SendRequest(request, reply))
		return FALSE;

	bRes = (reply.status == BR_OK);

	return TRUE;
}

BOOL
CBankappClient::CreateDirectory(CString& path)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_CREATE_DIR;
	strcpy(request.data, path);

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot create remote directory");
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::RemoveFiles(CString& path)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_REMOVE_FILES;
	strcpy(request.data, path);

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot remove remote files");
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::GetCurrentDir(CString& curdir)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_GET_CURDIR;

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot get remote directory");
		return FALSE;
	}

	curdir = reply.data;

	return TRUE;
}

BOOL
CBankappClient::GetHomeDir(CString& curdir)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_GET_HOME_DIR;

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot get remote home directory");
		return FALSE;
	}

	curdir = reply.data;

	return TRUE;
}

BOOL
CBankappClient::CopyFile(CString& local, CString& remote)
{
	BankappRequest request;
	BankappReply reply;
	HANDLE hFile;

	hFile = CreateFile(local, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE){
		Message("Cannot open %s: %s", (LPCSTR)local,
			ErrorMessage(GetLastError()));
		return FALSE;
	}

	request.type = BR_SEND_FILE;
	strcpy(request.data, remote);

	if (!SendRequest(request, reply)){
		CloseHandle(hFile);
		return FALSE;
	}

	if (reply.status != BR_OK){
		Message("Cannot create remote file \"%s\"",
			(LPCSTR)remote);
		CloseHandle(hFile);
		return FALSE;
	}

	request.type = BR_FILE_DATA;
	while (ReadFile(hFile, request.data, sizeof request.data, &request.size, NULL)){
		if (request.size == 0)
			break;

		if (!SendRequest(request, reply)){
			CloseHandle(hFile);
			return FALSE;
		}

		if (reply.status != BR_OK){
			Message("Error writing to remote file");
			CloseHandle(hFile);
			return FALSE;
		}
	}

	CloseHandle(hFile);

	request.type = BR_EOF;
	if (!SendRequest(request, reply)){
		return FALSE;
	}

	if (reply.status != BR_OK){
		Message("Error closing remote file");
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::StartCommand(CString& command)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_RUN;
	strcpy(request.data, command);

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot start remote command");
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::GetCommandOutput(char* pData, DWORD& dwSize, BOOL& bTerminated, DWORD& dwExitCode)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_RUN_OUTPUT;
	request.size = dwSize;

	if (!SendRequest(request, reply))
		return FALSE;

	switch(reply.status){
	case BR_MORE:
		bTerminated = FALSE;
		dwSize = reply.size;
		memcpy(pData, reply.data, reply.size);
		return TRUE;
	case BR_OK:
		bTerminated = TRUE;
		dwSize = reply.size;
		memcpy(pData, reply.data, reply.size);
		dwExitCode = reply.exitcode;
		return TRUE;
	default:
		Message("Cannot read command output");
		return FALSE;
	}
}

BOOL
CBankappClient::CancelCommand()
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_RUN_CANCEL;

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot cancel remote command");
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::KillTlisten(CString& tllog)
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_KILL_TLISTEN;
	strcpy(request.data, tllog);

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot kill remote tlisten");
		return FALSE;
	}

	return TRUE;
}

BOOL
CBankappClient::CleanIpc()
{
	BankappRequest request;
	BankappReply reply;

	request.type = BR_CLEAN_IPC;

	if (!SendRequest(request, reply))
		return FALSE;

	if (reply.status != BR_OK){
		Message("Cannot clean remote IPC");
		return FALSE;
	}

	return TRUE;
}

// Kill local tlisten (helper function, common to bankappd and the driver)
BOOL
KillTlisten(CString& tllog)
{
	static char pattern[] = "CMDTUX_CAT:1468";
	static int len = sizeof pattern - 1;

	FILE* fd = fopen(tllog, "r");
	if (!fd)
		return TRUE;

	char buf[BUFSIZ];
	int pid = 0;

	while (fgets(buf, sizeof buf, fd)){
		char *ptr = buf;

		for(;;) {
			ptr = strchr(ptr, pattern[0]);
			if (!ptr)
				break;
			if (strncmp(ptr, pattern, len) == 0)
				break;
			ptr++;
		}

		if (!ptr)
			continue;

		// pid is before pattern
		while (ptr != buf && *ptr != ';')
			ptr--;
		if (ptr == buf)
			continue;

		while (ptr != buf && isdigit(*ptr))
			ptr--;

		pid = atoi(ptr);
	}
	
	fclose(fd);

	(void)_unlink(tllog);

	if (!pid)
		return TRUE;

	HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (!hProc)
		return FALSE;

	BOOL bRet = TerminateProcess(hProc, 0);
	CloseHandle(hProc);
	return bRet;
}

// Clean IPC (helper function, common to bankappd and the driver)
BOOL
CleanIpc()
{
	system("ipclean");
	return TRUE;
}

#define next(p, c) if ((c = *p++) == 0) return 0

/*
 * Match a character string to a pattern
 * Ignore case in comparison
 */
static int
match(const char* s, const char* p, int nocase)
{
	char pc;
	char sc;
	char low;
	int not;
	int ok;

	/*
	 * Check for empty pattern
	 */
	if (!p || !*p){
		if (!s || !*s)
			return 1;
		return 0;
	}

	pc = *p++;
	sc = *s++;

	/*
	 * Match first character and recursively match the remainder
	 */
	if (nocase){
		sc = tolower(sc);
		pc = tolower(pc);
	}

	switch(pc){
	case '\\':
		/*
		 * Skip \\ and see if there is a perfect match
		 */
		next(p, pc);
		/* FALLTHRU */
	default:
		if (pc != sc)
			return 0;
		return match(s, p, nocase);
	case '?':
		if (!sc)
			return 0;
		return match(s, p, nocase);
	case '*':
		/*
		 * Skip repeated *'s
		 */
		while (*p == '*')
			p++;

		/*
		 * *'s to the end: match
		 */
		if (*p == 0)
			return 1;

		/*
		 * Loop matching the remainder, until there is a hit
		 * or until the end of the string is reached
		 */
		while (*s){
			if (match(s, p, nocase))
				return 1;

			s++;
		}
		return 0;
	case '[':
		if (!sc)
			return 0;

		if (*p == '!'){
			not = 1;
			p++;
		} else
			not = 0;

		next(p, pc);
		if (nocase)
			pc = tolower(pc);

		low = 0;
		ok = 0;
		do  {
			/*
			 * Interval
			 */
			if (pc == '-' && *p != ']'){
				next(p, pc);
				if (pc == '\\'){
					next(p, pc);
					if (nocase)
						pc = tolower(pc);
				}
				if (not){
					if (sc < low || sc > pc)
						ok++;
					else
						return 0;
				} else if (low <= sc && sc <= pc)
					ok++;
			} else if (pc == '\\'){
				next(p, pc);
				if (nocase)
					pc = tolower(pc);
			}

			/*
			 * Might be the beginning of an interval
			 */
			low = pc;

			if (not){
				if (pc != sc)
					ok++;
				else
					return 0;
			} else if (pc == sc)
				ok++;
			next(p, pc);
			if (nocase)
				pc = tolower(pc);
		} while (pc != ']');

		if (ok)
			return match(s, p, nocase);
		return 0;
	}
}

// Remove a subtree
static BOOL scandir(const char* dir);

static BOOL
RemoveTree(const char* path)
{
	if (path[0] == '.' && (path[1] == '\0' || path[1] == '.' && path[2] == '\0'))
		return FALSE;

	DWORD dwAttr = GetFileAttributes(path);

	if (dwAttr == 0xFFFFFFFF)
		return TRUE;

	if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
		return scandir(path);

	(void)SetFileAttributes(path, FILE_ATTRIBUTE_NORMAL);

	if (DeleteFile(path) < 0)
		return FALSE;

	return TRUE;
}

static BOOL
scandir(const char* dir)
{
	char buf[MAX_PATH + 1];
	int len = strlen(dir);
	
	if (len > MAX_PATH)
		return FALSE;

	strcpy(buf, dir);
	buf[len++] = '\\';

	strcpy(buf + len, "*.*");

	WIN32_FIND_DATA fdd;
	HANDLE hFind = FindFirstFile(buf, &fdd);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	BOOL bRes = TRUE;
	do {
		if (fdd.cFileName[0] == '.' && (fdd.cFileName[1] == '\0' ||
		    fdd.cFileName[1] == '.' && fdd.cFileName[2] == '\0'))
		    	continue;

		strcpy(buf + len, fdd.cFileName);
		if (!RemoveTree(buf))
			bRes = FALSE;
	} while (FindNextFile(hFind, &fdd));

	FindClose(hFind);

	(void)SetFileAttributes(dir, FILE_ATTRIBUTE_NORMAL);

	if (bRes){
		if (!RemoveDirectory(dir))
			return FALSE;
	}
	return bRes;
}

/*
 * Expand the pattern in a list of files in dir
 */
CStringArray*
expand_files_in_dir(const char* dir, const char* pattern)
{
	CString tpl;
	WIN32_FIND_DATA fdd;
	HANDLE hFind;
	int dirlen;
	int hasslash;

	/*
	 * Open directory
	 */
	if (dir){
		dirlen = strlen(dir);
		tpl = dir;
		if (dir[dirlen - 1] == '/' || dir[dirlen - 1] == '\\' || dir[dirlen - 1] == ':'){
			hasslash = 1;
			tpl += "*.*";
		} else {
			hasslash = 0;
			tpl += "/*.*";
		}
	} else {
		hasslash = 0;
		dirlen = 0;
		tpl = "*.*";
	}

	hFind = FindFirstFile(tpl, &fdd);
	if (hFind == INVALID_HANDLE_VALUE){
		return 0;
	}

	/*
	 * Loop on all entries in the dir, matching with the pattern
	 */
	CStringArray* caMatches = 0;

	do {
		/*
		 * Skip . and ..
		 */
		if (pattern[0] != '.' && fdd.cFileName[0] == '.' && (fdd.cFileName[1] == '\0' ||
		    fdd.cFileName[1] == '.' && fdd.cFileName[2] == '\0'))
		    	continue;

		if (match(fdd.cFileName, pattern, 1)){
			if (!caMatches){
				caMatches = new CStringArray;
				caMatches->SetSize(0, 10);
			}
			if (dir){
				CString fullname = dir;
				if (!hasslash)
					fullname += '/';
				fullname += fdd.cFileName;

				caMatches->Add(fullname);
			} else 
				caMatches->Add(fdd.cFileName);
		}
	} while (FindNextFile(hFind, &fdd));

	FindClose(hFind);

	return caMatches;
}

// remove files, possibly with a pattern
BOOL
RemoveFiles(const char* name)
{
	char buf[MAX_PATH];

	strcpy(buf, name);

	char* backslash = strrchr(buf, '\\');
	char* slash = strrchr(buf, '/');

	char* ptr;

	if (!backslash)
		ptr = slash;
	else if (!slash)
		ptr = backslash;
	else if (slash < backslash)
		ptr = backslash;
	else
		ptr = slash;

	CStringArray* caMatches;
	
	if (ptr){
		*ptr = 0;
		caMatches = expand_files_in_dir(buf, ptr + 1);
		*ptr = '\\';
	} else {
		caMatches = expand_files_in_dir(NULL, buf);
	}

	if (!caMatches)
		return TRUE;

	CStringArray& caFiles = *caMatches;

	for (int i = 0 ; i < caFiles.GetSize() ; i++){
		if (!RemoveTree(caFiles[i]))
			return FALSE;
	}

	delete caMatches;

	return TRUE;
}
