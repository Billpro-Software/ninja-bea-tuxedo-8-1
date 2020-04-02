/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
//	Copyright (c) 1995 Novell, Inc.	
//	  All Rights Reserved 	 	

//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	
//	Novell, Inc.                     			
//	The copyright notice above does not evidence any   	
//	actual or intended publication of such source code.	

// #ident	"@(#) samples/atmi/bankapp/nt/bankappd/misc.cpp	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/bankappd/misc.cpp	$Revision: 1.4 $";
#endif

#include "stdafx.h"
#include "ctype.h"
#include "misc.h"
#include "sys\stat.h"

char*
ErrorMessage(DWORD dwError)
{
	static CHAR szMesg[1024];
	DWORD cMsgLen;
	CHAR* msgBuf;

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

	return szMesg;
}

void
Message(const char* fmt, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, fmt);

	vsprintf(buf, fmt, args);

	CWnd::GetActiveWindow()->MessageBox(buf, "Bankapp Agent Error", MB_OK);
}

void
InfoMessage(const char* fmt, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, fmt);

	vsprintf(buf, fmt, args);

	CWnd::GetActiveWindow()->MessageBox(buf, "Bankapp Agent Info", MB_OK);
}

void
FatalMessage(const char* fmt, ...)
{
	va_list args;
	char buf[1024];

	va_start(args, fmt);

	vsprintf(buf, fmt, args);

	CWnd::GetActiveWindow()->MessageBox(buf, "Bankapp Agent Fatal Error", MB_OK|MB_ICONSTOP);
}

BOOL
IsFullPath(CString& path)
{
	if (!isalpha(path[0]))
		return FALSE;
	if (path[1] != ':')
		return FALSE;
	if (path[2] != '\\')
		return FALSE;

	return TRUE;
}

BOOL
IsDirectory(CString& path)
{
	struct _stat statbuf;

	if (_stat(path, &statbuf) == -1)
		return FALSE;

	if ((statbuf.st_mode & _S_IFMT) != _S_IFDIR)
		return FALSE;

	return TRUE;
}

BOOL
IsFile(CString& path)
{
	struct _stat statbuf;

	if (_stat(path, &statbuf) == -1)
		return FALSE;

	if ((statbuf.st_mode & _S_IFMT) != _S_IFREG)
		return FALSE;

	return TRUE;
}
