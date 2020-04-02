/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/config.h	$Revision: 1.4 $"

#include <time.h>

#define MAX_SITES	10

/////////////////////////////////////////////////////////////////////////////
// Configuration info
enum OsType { OS_NONE, OS_UNIX, OS_NT };

class CSite : public CObject {
public:
	CSite();
	virtual ~CSite();

// Attributes. Too many classes can access them.
// Hence they are public
public:
	CString m_name;
	CString m_rootdir;
	CString m_home;
	CString m_appdir;
	CString m_netDevice;
	CString m_netAddress;
	CString m_type;
	UINT m_bridge;
	UINT m_tlisten;
	BOOL m_bRemote;
	OsType m_osType;
	UINT m_uid;
	UINT m_gid;
	time_t m_timePropagated;
	time_t m_timeBuild;
	time_t m_timeBankdl;
	time_t m_timeTlog;
	int m_nSite;

public:
	void Propagate();
	void Build();
	void Clean();
	void CreateBank();
	void CreateTlog();
	void MachinesSection(FILE* fd);
	void GroupsSection(FILE* fd);
	void NetworkSection(FILE* fd);
	void ServersSection(FILE* fd, int low, int high);
protected:
	static void GetCommandOutput(LPVOID param);
	BOOL RunPipeCommand(CString& command);
	void SerializeSite(CArchive& ar);
	void CommonFileList(CStringArray& saList);
public:
	virtual void Serialize(CArchive& ar) = 0;
	virtual BOOL Connect() = 0;
	virtual BOOL GetLoginDir() = 0;
	virtual BOOL GetId() = 0;
	virtual BOOL GetMachineType() = 0;
	virtual BOOL GetTuxdir() = 0;
	virtual BOOL RemoveFiles(CString& dir) = 0;
	virtual BOOL CreateDir(CString& dir) = 0;
	virtual void SpecialFiles(CStringArray& saList) = 0;
	virtual BOOL IsDirectory(CString& dir) = 0;
	virtual BOOL CopyFile(CString& source, CString& dest) = 0;
	virtual BOOL RunCommand(CString& command) = 0;
	virtual void StartTlisten() = 0;
	virtual void KillTlisten() = 0;
	virtual void CleanIpc() = 0;
	virtual void CleanBank() = 0;
	virtual void CleanTlog() = 0;
	virtual void CleanUserlogs() = 0;
	virtual BOOL CreateBankvar() = 0;
	virtual BOOL CreateMakefile() = 0;
	virtual char PathSep() = 0;
	virtual char DirSep() = 0;
	virtual char* MakeCommand() = 0;
};

class CConfig {
// Attributes
protected:
	CString m_name;
	CSite *m_sites[MAX_SITES];

public:
	BOOL m_bValidConfig;
	BOOL m_bRemoveOnExit;
	int m_ipckey;
	time_t m_timePopulate;

public:
	CConfig();
	CConfig(CString& name);
	~CConfig();
	void SetFileName(CString& name) { m_name = name; }
	void SetFileName(char* name) { m_name = name; }
	BOOL IsSiteName(CString& name);
	void SetSite(int i, CSite* site) { m_sites[i] = site; }
	CSite* FindSite(CString& name);
	CSite* FindSite(int i) { return m_sites[i]; }
	void MarkForRemove() { m_bRemoveOnExit = TRUE; }

	BOOL Store();
	BOOL Load();

// Implementation
protected:
	virtual void Serialize(CArchive& ar);
};

class CUnixSite : public CSite {
protected:
	DECLARE_SERIAL(CUnixSite)
public:
	CUnixSite();
	virtual void Serialize(CArchive& ar);
	virtual BOOL Connect();
	virtual BOOL GetLoginDir();
	virtual BOOL GetId();
	virtual BOOL GetMachineType();
	virtual BOOL GetTuxdir();
	virtual BOOL RemoveFiles(CString& dir);
	virtual BOOL CreateDir(CString& dir);
	virtual void SpecialFiles(CStringArray& saList);
	virtual BOOL IsDirectory(CString& dir);
	virtual BOOL CopyFile(CString& source, CString& dest);
	virtual BOOL RunCommand(CString& command);
	virtual void StartTlisten();
	virtual void KillTlisten();
	virtual void CleanIpc();
	virtual void CleanBank();
	virtual void CleanTlog();
	virtual void CleanUserlogs();
	virtual BOOL CreateBankvar();
	virtual BOOL CreateMakefile();
	virtual char PathSep() { return ':'; }
	virtual char DirSep() { return '/'; }
	virtual char* MakeCommand() { return "make"; }
};

class CNTSite : public CSite {
protected:
	static void GetCommandOutput(LPVOID param);
public:
	CNTSite();
	virtual ~CNTSite();
	virtual void Serialize(CArchive& ar);
	virtual BOOL Connect() = 0;
	virtual BOOL GetLoginDir() = 0;
	virtual BOOL GetId();
	virtual BOOL GetMachineType() = 0;
	virtual BOOL GetTuxdir() = 0;
	virtual BOOL RemoveFiles(CString& dir) = 0;
	virtual BOOL CreateDir(CString& dir) = 0;
	virtual void SpecialFiles(CStringArray& saList);
	virtual BOOL IsDirectory(CString& dir) = 0;
	virtual BOOL CopyFile(CString& source, CString& dest) = 0;
	virtual BOOL RunCommand(CString& command) = 0;
	virtual void StartTlisten();
	virtual void KillTlisten() = 0;
	virtual void CleanIpc() =0;
	virtual void CleanBank();
	virtual void CleanTlog();
	virtual void CleanUserlogs();
	virtual BOOL CreateBankvar();
	virtual BOOL CreateMakefile();
	virtual char PathSep() { return ';'; }
	virtual char DirSep() { return '\\'; }
	virtual char* MakeCommand() { return "nmake -nologo"; }
};

class CNTLocalSite : public CNTSite {
protected:
	DECLARE_SERIAL(CNTLocalSite)
public:
	CNTLocalSite();
	~CNTLocalSite();
	virtual BOOL Connect();
	virtual BOOL GetLoginDir();
	virtual BOOL GetMachineType();
	virtual BOOL GetTuxdir();
	virtual void KillTlisten();
	virtual void CleanIpc();
	virtual BOOL RemoveFiles(CString& dir);
	virtual BOOL CreateDir(CString& dir);
	virtual BOOL IsDirectory(CString& dir);
	virtual BOOL CopyFile(CString& source, CString& dest);
	virtual BOOL RunCommand(CString& command);
};

class CNTRemoteSite : public CNTSite {
	CBankappClient m_remote;
	BOOL m_bConnected;
protected:
	DECLARE_SERIAL(CNTRemoteSite)
	static void GetCommandOutput(LPVOID param);
public:
	CNTRemoteSite();
	~CNTRemoteSite();
	virtual BOOL Connect();
	virtual BOOL GetLoginDir();
	virtual BOOL GetMachineType();
	virtual BOOL GetTuxdir();
	virtual void KillTlisten();
	virtual void CleanIpc();
	virtual BOOL RemoveFiles(CString& dir);
	virtual BOOL CreateDir(CString& dir);
	virtual BOOL IsDirectory(CString& dir);
	virtual BOOL CopyFile(CString& source, CString& dest);
	virtual BOOL RunCommand(CString& command);
};

extern CConfig config;
