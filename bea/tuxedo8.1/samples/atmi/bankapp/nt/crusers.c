/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*      Copyright (c) 1996 BEA Systems, Inc.
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
        SOURCE CODE OF BEA Systems, Inc.
        The copyright notice above does not
        evidence any actual or intended
        publication of such source code.
*/

/* #ident	"@(#) samples/atmi/bankapp/nt/crusers.c	$Revision: 1.4 $" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <io.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static char	tpusr[MAX_PATH];
static char	tpgrp[MAX_PATH];

static BOOL
cleanup(DWORD dwCtrlType)
{
	if (tpusr[0])
		(void)_unlink(tpusr);
	if (tpgrp[0])
		(void)_unlink(tpgrp);
	return TRUE;
}

void
main(int argc, char* argv[])
{
	char*	appdir;
	char	name[100];
	char	cmd[200];
	char	username[100];
	DWORD	userlength;

	appdir = getenv("APPDIR");
	if (!appdir){
		(void) fprintf(stderr, "APPDIR not set\n");
		exit(1);
	}

	(void) sprintf(tpusr, "%s\\tpusr", appdir);
	(void) sprintf(tpgrp, "%s\\tpgrp", appdir);

	/*
 	 * Verify whether the user authentication file(s) exists
 	 */
	if (_access(tpusr, 0) == 0 || _access(tpgrp, 0) == 0){
		(void) printf("crusers: WARN: Files 'tpgrp' and/or 'tpusr' exists! ");
		(void) printf("Delete them to rerun 'crusers'\n");
		exit(1);
	}

	/*
	 * Cleanup in case of premature failure
	 */
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)cleanup, TRUE);

	/*
	 * Create groups
	 */
	(void) printf("\nCreating groups and users for authentication\n");

	(void) printf("\nCreating group - bankmgr\n");

	if (system("tpgrpadd -g 101 bankmgr") == -1)
		exit(1);

	(void) printf("Creating group - bankaud\n");

	if (system("tpgrpadd -g 201 bankaud") == -1)
		exit(1);

	(void) printf("Creating group - bankusr\n");

	if (system("tpgrpadd -g 301 bankusr") == -1)
		exit(1);
		
	/*
	 * Create users
	 */
	(void) printf("Creating users in group 'bankmgr'\n");
	(void) printf("\nEnter user name for a bank manager: (bankmgr1): ");

	name[0] = 0;
	(void) gets(name);

	if (!name[0])
		(void) strcpy(name, "bankmgr1");

	(void) sprintf(cmd, "tpusradd -u 1001 -g bankmgr -c tpsysadm %s", name);

	if (system(cmd) == -1)
		exit(1);

	(void) printf("\nCreating users in group 'bankaud'\n");
	(void) printf("\nEnter user name for a bank auditor: (bankaud1): ");

	name[0] = 0;
	(void) gets(name);

	if (!name[0])
		(void) strcpy(name, "bankaud1");

	(void) sprintf(cmd, "tpusradd -u 2001 -g bankaud -c * %s", name);

	if (system(cmd) == -1)
		exit(1);

	(void) printf("\nCreating users in group 'bankusr'\n");
	/*
	 * Get login name of the user installing the bankapp demo app
	 */
	userlength = sizeof username;
	GetUserName(username, &userlength);
	(void) printf("\nEnter user name for a bank user: (%s): ", username);

	name[0] = 0;
	(void) gets(name);

	if (!name[0])
		(void) strcpy(name, username);

	(void) sprintf(cmd, "tpusradd -u 3001 -g bankusr %s", username);

	if (system(cmd) == -1)
		exit(1);

	exit(0);
}
