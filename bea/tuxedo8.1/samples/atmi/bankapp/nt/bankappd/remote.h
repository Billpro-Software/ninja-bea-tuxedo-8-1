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

// #ident	"@(#) samples/atmi/bankapp/nt/bankappd/remote.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/bankappd/remote.h	$Revision: 1.4 $";
#endif

#define BANKAPP_PIPE	"BankappPipe"

enum RequestType {
	BR_DISCONNECT, BR_GET_TUXDIR, BR_GET_CURDIR,
	BR_SEND_FILE, BR_FILE_DATA, BR_EOF, BR_RUN,
	BR_RUN_OUTPUT, BR_RUN_CANCEL, BR_GET_MACHINE_TYPE,
	BR_IS_REMOTE_DIR, BR_CREATE_DIR, BR_REMOVE_FILES,
	BR_GET_HOME_DIR, BR_KILL_TLISTEN, BR_CLEAN_IPC
};

enum ReplyStatus {
	BR_OK, BR_INVALID_REQUEST, BR_FAILED, BR_MORE
};

struct BankappRequest {
	RequestType type;
	DWORD size;
	char data[512];
};

struct BankappReply {
	ReplyStatus status;
	DWORD size;
	DWORD exitcode;
	char data[512];
};

class CBankappRemote {
protected:
	HANDLE hPipe;
	CString name;
public:
	CBankappRemote() {
		hPipe = 0;
	}
	virtual BOOL Disconnect() = 0;
	virtual ~CBankappRemote();
};

class CBankappClient : public CBankappRemote {
protected:
	BOOL SendRequest(BankappRequest& request, BankappReply& reply);
public:
	BOOL Connect(CString& site);
	BOOL GetTuxdir(CString& tuxdir);
	BOOL GetCurrentDir(CString& curdir);
	BOOL GetHomeDir(CString& homedir);
	BOOL CopyFile(CString& local, CString& remote);
	BOOL StartCommand(CString& command);
	BOOL GetCommandOutput(char* pData, DWORD& dwSize, BOOL& bTerminated, DWORD& dwExitCode);
	BOOL GetMachineType(CString& mach);
	BOOL CancelCommand();
	BOOL IsDirectory(CString& path, BOOL& bRes);
	BOOL CreateDirectory(CString& path);
	BOOL RemoveFiles(CString& path);
	BOOL Disconnect();
	BOOL KillTlisten(CString& tllog);
	BOOL CleanIpc();
};

class CBankappServer : public CBankappRemote {
	HANDLE m_hAsyncEvent;
	void WaitForPipeOrEvent(HANDLE hEvent);
public:
	CBankappServer();
	~CBankappServer();
	BOOL Create();
	BOOL Disconnect();
	BOOL Accept(HANDLE hEvent = NULL);
	BOOL GetRequest(BankappRequest& br, HANDLE hEvent = NULL);
	BOOL SendReply(BankappReply& br);
};
	
extern BOOL KillTlisten(CString& tllog);
extern BOOL CleanIpc();
extern BOOL RemoveFiles(const char* name);
extern CStringArray* expand_files_in_dir(const char* dir, const char* pattern);
