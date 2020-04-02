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

/* #ident	"@(#) samples/atmi/bankapp/nt/cracl.c	$Revision: 1.4 $" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static char	tpacl[MAX_PATH];

static BOOL
cleanup(DWORD dwCtrlType)
{
	if (tpacl[0])
		(void)_unlink(tpacl);
	return(TRUE);
}

void
main(int argc, char* argv[])
{
	char	buf[BUFSIZ];
	char*	appdir;
	FILE* fd;

	appdir = getenv("APPDIR");
	if (!appdir) {
		(void) fprintf(stderr, "APPDIR not set\n");
		exit(1);
	}

	(void) sprintf(tpacl, "%s\\tpacl", appdir);

	/*
	 * Check if there are entries in the ACL authentication file
	 * Entries beginning with '#' are ignored.
	 */
	if ((fd = fopen(tpacl, "r")) != 0){
		while (fgets(buf, sizeof buf, fd)){
			if (buf[0] != '#'){
				(void) printf("cracl: Entries exist in the ACL authentication file 'tpacl' !");
				(void) printf("Delete them to re-run 'cracl'\n");
				exit(1);
			}
		}
		(void) fclose(fd);
	}

	/*
	 * Cleanup in case of premature failure
	 */
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)cleanup, TRUE);

	/*
	 * Create ACLs
	 */
	(void) printf("Creating Access Control Lists (ACL)\n");

	/*
	 * Services called by client "audit"
	 */
	if (system("tpacladd -g bankaud -t SERVICE ABAL") == -1)
		exit(1);

	if (system("tpacladd -g bankaud -t SERVICE ABAL_BID") == -1)
		exit(1);

	if (system("tpacladd -g bankaud -t SERVICE TBAL") == -1)
		exit(1);

	if (system("tpacladd -g bankaud -t SERVICE TBAL_BID") == -1)
		exit(1);

	/*
	 * Services called by client "auditcon"
	 */
	if (system("tpacladd -g bankaud -t SERVICE AUDITC") == -1)
		exit(1);

	if (system("tpacladd -g bankaud -t SERVICE ABALC_BID") == -1)
		exit(1);

	if (system("tpacladd -g bankaud -t SERVICE TBALC_BID") == -1)
		exit(1);

	/*
	 * Queue dequeued by client "bankmgr"
	 */
	if (system("tpacladd -g bankmgr -t DEQ Q_OPENACCT") == -1)
		exit(1);

	exit(0);
}
