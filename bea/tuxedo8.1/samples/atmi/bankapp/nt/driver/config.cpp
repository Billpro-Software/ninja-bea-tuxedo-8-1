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

// #ident	"@(#) samples/atmi/bankapp/nt/driver/config.cpp	$Revision: 1.4 $"

#include "stdafx.h"
#include "resource.h"
#include "remote.h"
#include "config.h"
#include "misc.h"
#include <Uunix.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// The configuration object is unique
CConfig config;

/////////////////////////////////////////////////////////////////////////////
// CSite class
IMPLEMENT_SERIAL(CUnixSite, CObject, 2)
IMPLEMENT_SERIAL(CNTLocalSite, CObject, 2)
IMPLEMENT_SERIAL(CNTRemoteSite, CObject, 2)

CSite::CSite()
{
	m_bridge = 0;
	m_tlisten = 0;
	m_osType = OS_NONE;
	m_timePropagated = 0;
	m_timeBuild = 0;
	m_timeBankdl = 0;
	m_timeTlog = 0;
}

CSite::~CSite()
{
}

void CSite::SerializeSite(CArchive& ar)
{
	DWORD tmp;
	if (ar.IsStoring()){
		ar << m_name;
		ar << m_rootdir;
		ar << m_home;
		ar << m_appdir;
		ar << m_netDevice;
		ar << m_netAddress;
		ar << m_type;
		tmp = m_bridge;
		ar << tmp;
		tmp = m_tlisten;
		ar << tmp;
		tmp = m_bRemote;
		ar << tmp;
		tmp = m_osType;
		ar << tmp;
		tmp = m_uid;
		ar << tmp;
		tmp = m_gid;
		ar << tmp;
		ar << m_timePropagated;
		ar << m_timeBuild;
		ar << m_timeBankdl;
		ar << m_timeTlog;
		tmp = m_nSite;
		ar << tmp;
	} else {
		ar >> m_name;
		ar >> m_rootdir;
		ar >> m_home;
		ar >> m_appdir;
		ar >> m_netDevice;
		ar >> m_netAddress;
		ar >> m_type;
		ar >> tmp;
		m_bridge = tmp;
		ar >> tmp;
		m_tlisten = tmp;
		ar >> tmp;
		m_bRemote = tmp;
		ar >> tmp;
		m_osType = (OsType)tmp;
		ar >> tmp;
		m_uid = tmp;
		ar >> tmp;
		m_gid = tmp;
		ar >> m_timePropagated;
		ar >> m_timeBuild;
		ar >> m_timeBankdl;
		ar >> m_timeTlog;
		ar >> tmp;
		m_nSite = tmp;
	}
}

void
CSite::CommonFileList(CStringArray& saList)
{
	// Build list of files to propagate
	CStringArray& sl = SourceFileList();

	saList.SetSize(0, 10);
	for (int i = 0 ; i < sl.GetSize() ; i++)
		saList.Add(sl[i]);
			
	char name[32];
	sprintf(name, "bankapp.mak%d", m_nSite);
	saList.Add(name);
}

void CSite::Propagate()
{
	CStringArray saList;

	m_timePropagated = 0;

	CommonFileList(saList);

	SpecialFiles(saList);

	if (!IsDirectory(m_appdir)){
		if (!CreateDir(m_appdir)){
			FatalMessage("Cannot create directory %s on %s", (LPCSTR)m_appdir,
				(LPCSTR)m_name);
			return;
		}
	}

	// Change the path separators, if necessary,
	// and prepare directory list
	CStringArray dirs;
	dirs.SetSize(0, 10);

	CStringArray dest;
	dest.SetSize(0, 10);
	for (int i = 0 ; i < saList.GetSize() ; i++){
		CString tmp = m_appdir;
		tmp += '/';

		int last = -1;
		for (int j = 0 ; j < saList[i].GetLength() ; j++){
			if (saList[i][j] == '\\'){
				tmp += DirSep();
				last = j;
			} else
				tmp += saList[i][j];
		}
		dest.Add(tmp);
		if (last > 0){
			CString dirname = tmp.Left(last + m_appdir.GetLength() + 1);
			for (j = 0 ; j < dirs.GetSize() ; j++){
				if (dirs[j] == dirname)
					break;
			}

			if (j == dirs.GetSize())
				dirs.Add(dirname);
		}
	}

	// Create all remote directories
	for (i = 0 ; i < dirs.GetSize() ; i++){
		(void)CreateDir(dirs[i]);
	}

	// Propagate all files
	for (i = 0 ; i < saList.GetSize() ; i++){
		if (!CopyFile(saList[i], dest[i])){
			FatalMessage("Cannot propagate file %s to %s",
				(LPCSTR)saList[i],
				(LPCSTR)m_name);
			return;
		}
	}

	m_timePropagated = time(0);
}

void CSite::Build()
{
	char command[BUFSIZ];

	sprintf(command, "%s -f bankapp.mak%d clean all", MakeCommand(), m_nSite);

	if (RunCommand((CString)command))
		m_timeBuild = time(0);
	else
		m_timeBuild = 0;
}

void CSite::Clean()
{
	char command[BUFSIZ];

	sprintf(command, "%s -f bankapp.mak%d clean", MakeCommand(), m_nSite);
	(void)RunCommand((CString)command);

	m_timeBuild = 0;
}

void CSite::CreateBank()
{
	char bankdb[BUFSIZ];

	sprintf(bankdb, "%s/bankdl%d", m_appdir, m_nSite);
	RemoveFiles((CString)bankdb);

	CString command = "crbankdb";

	if (RunCommand(command))
		m_timeBankdl = time(0);
	else
		m_timeBankdl = 0;
}

void CSite::CreateTlog()
{
	CString command;
	char tlog[100];

	sprintf(tlog, "%s/TLOG", m_appdir);

	RemoveFiles((CString)tlog);

	if (m_bRemote)
		command = "crtlog";
	else
		command = "crtlog -m";

	if (RunCommand(command))
		m_timeTlog = time(0);
	else
		m_timeTlog = 0;
}

void CSite::MachinesSection(FILE* fd)
{
	fprintf(fd, "%s\tLMID=SITE%d\n", (LPCSTR)m_name, m_nSite);
	fprintf(fd, "\tTUXDIR=\"%s\"\n", (LPCSTR)m_rootdir);
	fprintf(fd, "\tAPPDIR=\"%s\"\n", (LPCSTR)m_appdir);
	fprintf(fd, "\tENVFILE=\"%s%cENVFILE\"\n", (LPCSTR)m_appdir, DirSep());
	fprintf(fd, "\tTLOGDEVICE=\"%s%cTLOG\"\n", (LPCSTR)m_appdir, DirSep());
	fprintf(fd, "\tTLOGNAME=TLOG\n");
	fprintf(fd, "\tTUXCONFIG=\"%s%ctuxconfig\"\n", (LPCSTR)m_appdir, DirSep());
	if (!m_type.IsEmpty())
		fprintf(fd, "\tTYPE=\"%s\"\n", (LPCSTR)m_type);
	fprintf(fd, "\tUID=%d\n", m_uid);
	fprintf(fd, "\tGID=%d\n", m_gid);
	fprintf(fd, "\n");
}

void CSite::GroupsSection(FILE* fd)
{
	fprintf(fd, "BANKB%d\tLMID=SITE%d\tGRPNO=%d\n", m_nSite, m_nSite, m_nSite);
	fprintf(fd, "\tOPENINFO=\"TUXEDO/SQL:%s%cbankdl%d%cbankdb%creadwrite\"\n",
		(LPCSTR)m_appdir, DirSep(), m_nSite, PathSep(),	PathSep());
}

void CSite::NetworkSection(FILE* fd)
{
 	fprintf(fd, "SITE%d\tNADDR=\"%s\"\n", m_nSite, mk_addr(m_netAddress, m_bridge));
	fprintf(fd, "\tNLSADDR=\"%s\"\n", mk_addr(m_netAddress, m_tlisten));
	if (!m_netDevice.IsEmpty())
		fprintf(fd, "\tBRIDGE=\"%s\"\n", (LPCSTR)m_netDevice);
	fprintf(fd, "\n");
}

void CSite::ServersSection(FILE* fd, int low, int high)
{
	fprintf(fd, "\n");
	fprintf(fd, "XFER\tSRVGRP=BANKB%d\n", m_nSite);
	fprintf(fd, "\tSRVID=%d01\n", m_nSite);

	fprintf(fd, "\n");
	fprintf(fd, "ACCT\tSRVGRP=BANKB%d\n", m_nSite);
	fprintf(fd, "\tSRVID=%d02\n", m_nSite);

	fprintf(fd, "\n");
	fprintf(fd, "BAL\tSRVGRP=BANKB%d\n", m_nSite);
	fprintf(fd, "\tSRVID=%d03\n", m_nSite);

	fprintf(fd, "\n");
	fprintf(fd, "BTADD\tSRVGRP=BANKB%d\n", m_nSite);
	fprintf(fd, "\tSRVID=%d04\n", m_nSite);

	fprintf(fd, "\n");
	fprintf(fd, "BALC\tSRVGRP=BANKB%d\n", m_nSite);
	fprintf(fd, "\tSRVID=%d05\n", m_nSite);

	int k = 11;
	for (int curtlr = low ; curtlr <= high ; curtlr++, k++){
		fprintf(fd, "\n");
		fprintf(fd, "TLR\tSRVGRP=BANKB%d\n", m_nSite);
		fprintf(fd, "\tSRVID=%d%d\n", m_nSite, k);
		fprintf(fd, "\tRQADDR=tlr%d\n", m_nSite);
		fprintf(fd, "\tREPLYQ=Y\n");
		fprintf(fd, "\tCLOPT=\"-A -- -T %d00\"\n", curtlr);
	}

	fprintf(fd, "\n");
}


// Thread procedure to get data from pipe and inject it in the dialog
void CSite::GetCommandOutput(LPVOID pParam)
{

	CCommandOut* dlg = (CCommandOut*)pParam;
	char buf[BUFSIZ];

	int length = 0;

	while (fgets(buf, sizeof buf, dlg->m_pipe)){
		dlg->m_commandOutput.SetSel(length, length);
		dlg->m_commandOutput.ReplaceSel(buf);
		length += strlen(buf);
	}

	if ((dlg->m_exitcode = pclose(dlg->m_pipe)) != 0)
		sprintf(buf, "\r\n\r\n%s terminated with exit code %d\r\n", dlg->m_command, dlg->m_exitcode);
	else
		sprintf(buf, "\r\n\r\n%s successful\r\n", dlg->m_command);
	dlg->m_commandOutput.SetSel(length, length);
	dlg->m_commandOutput.ReplaceSel(buf);
	length += strlen(buf);

	// Enable dialog buttons
	dlg->CanDestroy();

	// Terminate the thread and deallocate the thread object
	AfxEndThread(0);
}

BOOL CSite::RunPipeCommand(CString& command)
{
	CString full_command = command;
	full_command += " 2>&1";

	FILE* fd = popen(full_command, "rb");

	if (!fd){
		Message("Cannot run %s: %s", (LPCSTR)command, strerror(errno));
		return FALSE;
	}

	CCommandOut dlg;

	dlg.m_pipe = fd;
	dlg.m_command = command;

	dlg.m_pThread = AfxBeginThread((AFX_THREADPROC)GetCommandOutput, &dlg,
		0, 0, CREATE_SUSPENDED);
	if (!dlg.m_pThread){
		FatalMessage("Cannot create command thread");
		pclose(fd);
		return FALSE;
	}

	int response = dlg.DoModal();

	if (dlg.m_exitcode != 0)
		return FALSE;

	return TRUE;
}

CUnixSite::CUnixSite() : CSite()
{
	m_osType = OS_UNIX;
}

CNTSite::CNTSite() : CSite()
{
	m_osType = OS_NT;
}

CNTSite::~CNTSite()
{
}

CNTLocalSite::CNTLocalSite() : CNTSite()
{
}

CNTLocalSite::~CNTLocalSite()
{
}

CNTRemoteSite::CNTRemoteSite() : CNTSite()
{
	m_bConnected = FALSE;
}

CNTRemoteSite::~CNTRemoteSite()
{
	if (m_bConnected)
		m_remote.Disconnect();
}

void
CUnixSite::Serialize(CArchive& ar)
{
	SerializeSite(ar);
}

void
CNTSite::Serialize(CArchive& ar)
{
	SerializeSite(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CConfig class
CConfig::CConfig(CString& name)
{
	m_name = name;
	m_bValidConfig = FALSE;
	m_bRemoveOnExit = FALSE;
	m_ipckey = 0;
	m_timePopulate = 0;

	for (int i = 0 ; i < MAX_SITES ; i++)
		m_sites[i] = NULL;
}

CConfig::CConfig()
{
	m_bValidConfig = FALSE;
	m_bRemoveOnExit = FALSE;
	m_ipckey = 0;
	m_timePopulate = 0;

	for (int i = 0 ; i < MAX_SITES ; i++)
		m_sites[i] = NULL;
}

CConfig::~CConfig()
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		if (m_sites[i])
			delete m_sites[i];
	}
}

BOOL
CConfig::Load()
{
	CFile* input = new CFile;

	CFileException fe;

	if (!input->Open(m_name, CFile::modeRead, &fe))
		return FALSE;

	CArchive ar(input, CArchive::load);

	try {
		Serialize(ar);
		ar.Close();
		input->Close();
		delete input;
	}

	catch(...){
		input->Abort();
		delete input;
		return FALSE;
	}

	return TRUE;
}

BOOL
CConfig::Store()
{
	CFile* output = new CFile;

	CFileException fe;

	if (!m_bValidConfig){
		if (m_bRemoveOnExit){
			// Configuration is being removed
			_unlink(m_name);
			return TRUE;
		}
		// Confirm before storing invalid config file
		int response = CWnd::GetActiveWindow()->MessageBox(
			"Configuration is invalid.\nSave anyway?",
			"Invalid Configuration", 
			MB_YESNOCANCEL|MB_ICONQUESTION);
		switch(response){
		case IDYES:
			break;
		case IDNO:
			// The file is not saved, but the application can terminate
			return TRUE;
		case IDCANCEL:
			// Go back to the application
			return FALSE;
		}
	}

	if (!output->Open(m_name, CFile::modeCreate|CFile::modeReadWrite, &fe))
		return FALSE;

	CArchive ar(output, CArchive::store);

	try {
		Serialize(ar);
		ar.Close();
		output->Close();
		delete output;
	}
	catch(...){
		output->Abort();
		delete output;

		return FALSE;
	}

	return TRUE;
}

void CConfig::Serialize(CArchive& ar)
{
	long tmp;
	int i;

	if (ar.IsStoring()){
		tmp = m_bValidConfig;
		ar << tmp;
		tmp = m_ipckey;
		ar << tmp;
		ar << m_timePopulate;
		for (i = 0 ; i < MAX_SITES ; i++){
			if (m_sites[i]){
				tmp = 1;
				ar << tmp;
				tmp = m_sites[i]->m_osType;
				ar << tmp;
				m_sites[i]->Serialize(ar);
			} else {
				tmp = 0;
				ar << tmp;
			}
		}
	} else {
		ar >> tmp;
		m_bValidConfig = tmp;
		ar >> tmp;
		m_ipckey = tmp;
		ar >> m_timePopulate;

		for (i = 0 ; i < MAX_SITES ; i++){
			ar >> tmp;
			if (!tmp)
				continue;
			ar >> tmp;
			switch(tmp){
			case OS_UNIX:
				m_sites[i] = new CUnixSite;
				break;
			case OS_NT:
				if (i == 0)
					m_sites[i] = new CNTLocalSite;
				else
					m_sites[i] = new CNTRemoteSite;
				break;
			}
			m_sites[i]->Serialize(ar);
		}
	}
}

BOOL CConfig::IsSiteName(CString& name)
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		if (!m_sites[i])
			continue;
		if (m_sites[i]->m_name == name)
			return TRUE;
	}

	return FALSE;
}

CSite* CConfig::FindSite(CString& name)
{
	for (int i = 0 ; i < MAX_SITES ; i++){
		if (m_sites[i] && m_sites[i]->m_name == name)
			return m_sites[i];
	}

	return NULL;
}

BOOL CUnixSite::Connect()
{
	// No connection needed. Done with repetitive calls to rsh.
	return TRUE;
}

BOOL CUnixSite::GetLoginDir()
{
	return RunRemoteGetLine(m_name, "pwd", m_home);
}

BOOL CUnixSite::GetId()
{
	CString id;

	if (!RunRemoteGetLine(m_name, "id", id))
		return FALSE;

	char* ptr = strchr(id, '=');

	if (!ptr)
		return FALSE;

	m_uid = atoi(ptr + 1);

	ptr = strchr (ptr + 1, '=');
	if (!ptr)
		return FALSE;

	m_gid = atoi(ptr + 1);

	return TRUE;
}

BOOL CUnixSite::GetMachineType()
{
	if (!RunRemoteGetLine(m_name, "uname -m", m_type))
		return FALSE;

	m_type += "UNIX";

	return TRUE;
}

BOOL CUnixSite::GetTuxdir()
{
	return RunRemoteGetLine(m_name, "echo $TUXDIR", m_rootdir);
}

BOOL CUnixSite::CreateDir(CString& dir)
{
	char cmd[BUFSIZ];

	sprintf(cmd, "mkdir %s", (LPCSTR)dir);

	return RunRemoteVerify(m_name, cmd);
}

BOOL CUnixSite::RemoveFiles(CString& dir)
{
	char cmd[BUFSIZ];

	sprintf(cmd, "rm -rf %s", (LPCSTR)dir);

	return RunRemoteVerify(m_name, cmd);
}

void CUnixSite::SpecialFiles(CStringArray& saList)
{
	char name[32];
	sprintf(name, "bankvar.mp%d", m_nSite);
	saList.Add(name);
}

BOOL CUnixSite::IsDirectory(CString& dir)
{
	char cmd[BUFSIZ];

	sprintf(cmd, "[ -d %s ]", dir);

	return RunRemoteVerify(m_name, cmd);
}

BOOL CUnixSite::CopyFile(CString& source, CString& dest)
{
	CString cmd = "rcp ";
	cmd += source;
	cmd += " ";
	cmd += m_name;
	cmd += ":";
	cmd += dest;

	// Do not really need a pipe, but popen makes sure there is a console
	// so, be lazy.
	FILE* fd = popen(cmd, "rt");
	if (!fd)
		return FALSE;
	int ret = pclose(fd);

	if (ret != 0)
		return FALSE;

	return TRUE;
}


// Run a command, and display the output in a window
// Set environment before running the command
BOOL CUnixSite::RunCommand(CString& command)
{
	char full_command[BUFSIZ];

	sprintf(full_command, "rsh %s \"cd %s;TERM=ansi;export TERM;. ./bankvar.mp%d;%s\"",
		(LPCSTR)m_name, (LPCSTR)m_appdir, m_nSite, (LPCSTR)command);

	return RunPipeCommand((CString)full_command);
}

void
CUnixSite::StartTlisten()
{
	CString command;

	command = "export TAGENTLOG ; TAGENTLOG=";
	command += m_appdir;
	command += "/TAGENT ; ";
	command += m_rootdir;
	command += "/bin/tlisten -l ";
	command += mk_addr(m_netAddress, m_tlisten);
	if (!m_netDevice.IsEmpty()){
		command += " -d ";
		command += m_netDevice;
	}

	// -L option is obsolete in R6.3
	// command += " -L ";
	// command += m_appdir;
	// command += "/TLLOG";

	(void)RunCommand(command);
}

void
CUnixSite::KillTlisten()
{
	CString command;

	command = "TLPID=\\`grep ' CMDTUX_CAT:1468:' ";
	command += m_appdir;
	command += "/TLLOG | tail -1 | sed -e 's/; CMDTUX_CAT:.*$//' -e 's/.*; //'\\`;";
	command += "if [ -n \\\"\\${TLPID}\\\" ];then;kill -15 \\${TLPID} 2>/dev/null;";
	command += "rm -f ";
	command += m_appdir;
	command += "/TLLOG;fi";

	(void)RunCommand(command);
}

void
CUnixSite::CleanIpc()
{
	CString command;

	command = "IPCLIST=\\`ipcs -c |";
	command += "sed -n \\\"/\\${LOGNAME}[ ]*[^ ]*\\$/s/\\(.*\\) 0x.*/-\\1/p\\\" |";
	command += "tr '\\\\012' ' '\\`;";
	command += "if [ -n \\\"\\${IPCLIST}\\\" ];then;";
	command += "ipcrm \\${IPCLIST};";
	command += "fi";

	(void)RunCommand(command);
}

void CUnixSite::CleanBank()
{
	char command[BUFSIZ];

	sprintf(command, "rmskill -f ; rm -f bankdl%d", m_nSite);
	if (RunCommand((CString)command)){
		m_timeBankdl = 0;
		config.m_timePopulate = 0;
	}
}

void CUnixSite::CleanTlog()
{
	char command[BUFSIZ];

	sprintf(command, "rm -f TLOG");
	if (RunCommand((CString)command))
		m_timeTlog = 0;
}

void CUnixSite::CleanUserlogs()
{
	char command[BUFSIZ];

	sprintf(command, "rm -f ULOG.* stdout stderr");
	(void)RunCommand((CString)command);
}

BOOL CUnixSite::CreateBankvar()
{
	CStringArray patterns;
	CStringArray replacements;
	char buf[256];

	patterns.SetSize(0, 10);
	replacements.SetSize(0, 10);

	patterns.Add("TUXDIR");
	sprintf(buf, "TUXDIR=%s", (LPCSTR)m_rootdir);
	replacements.Add(buf);

	patterns.Add("APPDIR");
	sprintf(buf, "APPDIR=%s", (LPCSTR)m_appdir);
	replacements.Add(buf);

	patterns.Add("DIPCKEY");
	sprintf(buf, "DIPCKEY=%d", config.m_ipckey + 1);
	replacements.Add(buf);

	patterns.Add("NADDR");
	sprintf(buf, "NADDR=%s", mk_addr(m_netAddress, m_bridge));
	replacements.Add(buf);

	patterns.Add("NLSADDR");
	sprintf(buf, "NLSADDR=%s", mk_addr(m_netAddress, m_tlisten));
	replacements.Add(buf);

	patterns.Add("NDEVICE");
	sprintf(buf, "NDEVICE=%s", (LPCSTR)m_netDevice);
	replacements.Add(buf);

	patterns.Add("BLKSIZE");
	sprintf(buf, "BLKSIZE=%d", 1024);
	replacements.Add(buf);

	patterns.Add("UNAME");
	sprintf(buf, "UNAME=%s", (LPCSTR)m_name);
	replacements.Add(buf);

	patterns.Add("FSCONFIG");
	sprintf(buf, "FSCONFIG=%s/bankdl%d", (LPCSTR)m_appdir, m_nSite);
	replacements.Add(buf);

	sprintf(buf, "bankvar.mp%d", m_nSite);
	
	return substitute("bankvar", buf, patterns, replacements);
}

BOOL CUnixSite::CreateMakefile()
{
	CStringArray patterns;
	CStringArray replacements;
	char buf[256];

	patterns.SetSize(0, 10);
	replacements.SetSize(0, 10);

	sprintf(buf, "TUXDIR=%s", (LPCSTR)m_rootdir);
	replacements.Add(buf);

	patterns.Add("APPDIR=");
	sprintf(buf, "APPDIR=%s", (LPCSTR)m_appdir);
	replacements.Add(buf);

	sprintf(buf, "bankapp.mak%d", m_nSite);
	return substitute("bankapp.mk", buf, patterns, replacements);
}

// Common NT code
BOOL CNTSite::GetId()
{
	m_uid = 0;
	m_gid = 0;

	return TRUE;
}

void CNTSite::SpecialFiles(CStringArray& saList)
{
	char name[32];
	sprintf(name, "bankvar.mp%d.cmd", m_nSite);
	saList.Add(name);
}

void CNTSite::StartTlisten()
{
	CString command;

	command = "(set TAGENTLOG=";
	command += m_appdir;
	command += "\\TAGENT) & tlisten -l ";
	command += mk_addr(m_netAddress, m_tlisten);

	// -L option is obsolete in R6.3
	// command += " -L ";
	// command += m_appdir;
	// command += "\\TLLOG";

	(void)RunCommand(command);
}

void CNTSite::CleanBank()
{
	char command[BUFSIZ];

	sprintf(command, "rmskill -f");
	(void)RunCommand((CString)command);
	sprintf(command, "%s/bankdl%d", m_appdir, m_nSite);
	if (RemoveFiles((CString)command)){
		m_timeBankdl = 0;
		config.m_timePopulate = 0;
	}
}

void CNTSite::CleanTlog()
{
	char tlog[BUFSIZ];

	sprintf(tlog, "%s/TLOG", m_appdir);

	if (RemoveFiles((CString)tlog))
		m_timeTlog = 0;
}

void CNTSite::CleanUserlogs()
{
	char file[BUFSIZ];

	sprintf(file, "%s/ULOG.*", m_appdir);
	(void)RemoveFiles((CString)file);

	sprintf(file, "%s/stdout", m_appdir);
	(void)RemoveFiles((CString)file);

	sprintf(file, "%s/stderr", m_appdir);
	(void)RemoveFiles((CString)file);
}

BOOL CNTSite::CreateBankvar()
{
	CStringArray patterns;
	CStringArray replacements;
	char buf[256];

	patterns.SetSize(0, 10);
	replacements.SetSize(0, 10);

	patterns.Add("set TUXDIR");
	sprintf(buf, "set TUXDIR=%s", (LPCSTR)m_rootdir);
	replacements.Add(buf);

	patterns.Add("set APPDIR");
	sprintf(buf, "set APPDIR=%s", (LPCSTR)m_appdir);
	replacements.Add(buf);

	patterns.Add("set DIPCKEY");
	sprintf(buf, "set DIPCKEY=%d", config.m_ipckey + 1);
	replacements.Add(buf);

	patterns.Add("set NADDR");
	sprintf(buf, "set NADDR=%s", mk_addr(m_netAddress, m_bridge));
	replacements.Add(buf);

	patterns.Add("set NLSADDR");
	sprintf(buf, "set NLSADDR=%s", mk_addr(m_netAddress, m_tlisten));
	replacements.Add(buf);

	patterns.Add("set NDEVICE");
	sprintf(buf, "set NDEVICE=%s", (LPCSTR)m_netDevice);
	replacements.Add(buf);

	patterns.Add("set BLKSIZE");
	sprintf(buf, "set BLKSIZE=%d", 1024);
	replacements.Add(buf);

	patterns.Add("set UNAME");
	sprintf(buf, "set UNAME=%s", (LPCSTR)m_name);
	replacements.Add(buf);

	patterns.Add("set FSCONFIG");
	sprintf(buf, "set FSCONFIG=%s\\bankdl%d", (LPCSTR)m_appdir, m_nSite);
	replacements.Add(buf);

	sprintf(buf, "bankvar.mp%d.cmd", m_nSite);
	
	return substitute("nt\\bankvar", buf, patterns, replacements);
}

BOOL CNTSite::CreateMakefile()
{
	CStringArray patterns;
	CStringArray replacements;
	char buf[256];

	patterns.SetSize(0, 10);
	replacements.SetSize(0, 10);

	patterns.Add("TUXDIR=");
	sprintf(buf, "TUXDIR=%s", (LPCSTR)m_rootdir);
	replacements.Add(buf);

	patterns.Add("APPDIR=");
	sprintf(buf, "APPDIR=%s", (LPCSTR)m_appdir);
	replacements.Add(buf);

	sprintf(buf, "bankapp.mak%d", m_nSite);
	
	return substitute("nt\\bankapp.mak", buf, patterns, replacements);
}

// Local NT site
BOOL CNTLocalSite::Connect()
{
	return TRUE;
}

BOOL CNTLocalSite::GetLoginDir()
{
	m_home = tuxgetenv("HOMEDRIVE");
	m_home += tuxgetenv("HOMEPATH");
	return TRUE;
}

BOOL CNTLocalSite::GetTuxdir()
{
	m_home = tuxgetenv("TUXDIR");
	return TRUE;
}

BOOL CNTLocalSite::GetMachineType()
{
	SYSTEM_INFO si;

	GetSystemInfo(&si);
	switch(si.dwProcessorType){
	case PROCESSOR_INTEL_386:
	case PROCESSOR_INTEL_486:
	case PROCESSOR_INTEL_PENTIUM:
		m_type = "i386NT";
		break;
	case PROCESSOR_MIPS_R4000:
		m_type = "mipsNT";
		break;
	case PROCESSOR_ALPHA_21064:
		m_type = "alphaNT";
		break;
	default:
		m_type = "defaultNT";
		break;
	}
	return TRUE;
}

BOOL CNTLocalSite::RemoveFiles(CString& dir)
{
	return ::RemoveFiles(dir);
}

BOOL CNTLocalSite::CreateDir(CString& dir)
{
	return CreateDirectory(dir, NULL);
}

BOOL CNTLocalSite::IsDirectory(CString& dir)
{
	return IsLocalDir(dir);
}

BOOL CNTLocalSite::CopyFile(CString& source, CString& dest)
{
	return ::CopyFile(source, dest);
}

BOOL CNTLocalSite::RunCommand(CString& command) 
{
	CString full_command;
	char env_file[32];

	sprintf(env_file, "bankvar.mp%d 2>&1 & ", m_nSite);

	full_command += env_file;
	full_command += command;

	return RunPipeCommand(full_command);
}

void
CNTLocalSite::KillTlisten()
{
	CString tllog;

	tllog = m_appdir;
	tllog += "\\TLLOG";

	::KillTlisten(tllog);
}

void
CNTLocalSite::CleanIpc()
{
	::CleanIpc();
}

// Remote NT Site
BOOL CNTRemoteSite::Connect()
{
	if (m_bConnected)
		return TRUE;

	if (!m_remote.Connect(m_name))
		return FALSE;

	m_bConnected = TRUE;

	return TRUE;
}

BOOL CNTRemoteSite::GetLoginDir()
{
	if (!Connect())
		return FALSE;

	return m_remote.GetHomeDir(m_home);
}

BOOL CNTRemoteSite::GetTuxdir()
{
	if (!Connect())
		return FALSE;

	return m_remote.GetTuxdir(m_rootdir);
}

BOOL CNTRemoteSite::GetMachineType()
{
	if (!Connect())
		return FALSE;

	if (!m_remote.GetMachineType(m_type))
		return FALSE;
	m_type += "NT";

	return TRUE;
}

BOOL CNTRemoteSite::RemoveFiles(CString& dir)
{
	if (!Connect())
		return FALSE;

	return m_remote.RemoveFiles(dir);
}

BOOL CNTRemoteSite::CreateDir(CString& dir)
{
	if (!Connect())
		return FALSE;

	return m_remote.CreateDirectory(dir);
}

BOOL CNTRemoteSite::IsDirectory(CString& dir)
{
	if (!Connect())
		return FALSE;

	BOOL bRes;
	if (!m_remote.IsDirectory(dir, bRes))
		return FALSE;
	return bRes;
}

BOOL CNTRemoteSite::CopyFile(CString& source, CString& dest)
{
	if (!Connect())
		return FALSE;

	return m_remote.CopyFile(source, dest);
}

// Thread procedure to get data from remote and inject it in the dialog
void CNTRemoteSite::GetCommandOutput(LPVOID pParam)
{
	CCommandOut* dlg = (CCommandOut*)pParam;
	char buf[BUFSIZ + 1];

	DWORD dwLength;
	int nSelLength = 0;
	BOOL bTerminated;
	DWORD dwExitCode;

	while ((dwLength = sizeof buf, dlg->m_remote->GetCommandOutput(buf, dwLength, bTerminated, dwExitCode)) && !bTerminated){
		dlg->m_commandOutput.SetSel(nSelLength, nSelLength);
		buf[dwLength] = 0;
		dlg->m_commandOutput.ReplaceSel(buf);
		nSelLength += strlen(buf);
	}

	dlg->m_exitcode = dwExitCode;

	if (dlg->m_exitcode != 0)
		sprintf(buf, "\r\n\r\n%s terminated with exit code %d\r\n", dlg->m_command, dlg->m_exitcode);
	else
		sprintf(buf, "\r\n\r\n%s successful\r\n", dlg->m_command);
	dlg->m_commandOutput.SetSel(nSelLength, nSelLength);
	dlg->m_commandOutput.ReplaceSel(buf);
	nSelLength += strlen(buf);

	// Enable dialog buttons
	dlg->CanDestroy();

	// Terminate the thread and deallocate the thread object
	AfxEndThread(0);
}

BOOL CNTRemoteSite::RunCommand(CString& command) 
{
	CString full_command;
	char env_file[32];

	// Change drive and directory
	if (m_appdir[1] == ':'){
		full_command = m_appdir[0];
		full_command += ": & ";
	}
	full_command += "cd ";
	full_command += m_appdir;
	full_command += " & ";

	sprintf(env_file, "bankvar.mp%d 2>&1 & ", m_nSite);

	full_command += env_file;
	full_command += command;

	if (!Connect())
		return FALSE;

	if (!m_remote.StartCommand(full_command))
		return FALSE;

	CCommandOut dlg;

	dlg.m_remote = &m_remote;
	dlg.m_command = command;

	dlg.m_pThread = AfxBeginThread((AFX_THREADPROC)GetCommandOutput, &dlg,
		0, 0, CREATE_SUSPENDED);
	if (!dlg.m_pThread){
		FatalMessage("Cannot create command thread");
		m_remote.CancelCommand();
		return FALSE;
	}

	dlg.DoModal();

	if (dlg.m_exitcode != 0)
		return FALSE;

	return TRUE;
}

void
CNTRemoteSite::KillTlisten()
{
	if (!Connect())
		return;

	CString tllog;

	tllog = m_appdir;
	tllog += "\\TLLOG";

	m_remote.KillTlisten(tllog);
}

void
CNTRemoteSite::CleanIpc()
{
	if (!Connect())
		return;

	m_remote.CleanIpc();
}
