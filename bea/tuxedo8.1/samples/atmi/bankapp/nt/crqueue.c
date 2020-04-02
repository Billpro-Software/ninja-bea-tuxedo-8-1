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

/* #ident	"@(#) samples/atmi/bankapp/nt/crqueue.c	$Revision: 1.4 $" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <io.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static char	qdevice[MAX_PATH];

/*
 * Function called to remove Q stuff in case of premature failure
 */

static BOOL
cleanup(DWORD dwCtrlType)
{
	FILE* fd;

	fd = _popen("qmadmin", "wt");

	if (fd){
		(void) fprintf(fd, "ipcrm -y QSP_BANKAPP\n");
		(void) _pclose(fd);
	}
		
	if (qdevice[0])
		(void) _unlink(qdevice);

	return(TRUE);
}

void
main(int argc, char* argv[])
{
	char*	qmconfig;
	char*	appdir;
	FILE*	fd;

	appdir = getenv("APPDIR");

	if (!appdir) {
		(void) fprintf(stderr, "APPDIR not set\n");
		exit(1);
	}

	qmconfig = getenv("QMCONFIG");

	if (!qmconfig) {
		(void) fprintf(stderr, "QMCONFIG not set\n");
		exit(1);
	}

	(void) sprintf(qdevice, "%s\\qdevice", appdir);

	/*
	 * Verify whether the Q device exists
	 */

	if (_access(qdevice, 0) == 0){
		(void) printf("crqueue: WARN: Q device 'qdevice' exists!\n");
		(void) printf("crqueue: INFO: To force a re-create, use qmadmin(1) to ");
		(void) printf("remove Queue Space ipcs (ipcrm -y QSP_BANKAPP), then delete ");
		(void) printf("qdevice (file %s) and re-run 'crqueue'\n", qdevice);
		exit(1);
	}

	/*
	 * Cleanup in case of premature failure
	 */

	SetConsoleCtrlHandler((PHANDLER_ROUTINE) cleanup, TRUE) ;

	/*
	 * Create a Q device
	 * Create a Q space (QSP_BANKAPP) within the device
	 * Open Q space
	 * Create Qs (Q_ERROR, Q_OPENACCT_LOG, Q_OPENACCT) in the Q space
	 * Close Q scape
	 */

	fd = _popen("qmadmin > nul", "wt");

	if (!fd)
		exit(1);

	(void) fprintf(fd, "crdl %s 0 500\n", qmconfig);
	(void) fprintf(fd, "qspacecreate QSP_BANKAPP 88946 200 20 5 5 200 Q_ERROR 'y' 16\n");
	(void) fprintf(fd, "qopen QSP_BANKAPP\n");
	(void) fprintf(fd, "qcreate Q_ERROR fifo none 0 0 100%% 0 \"\"\n");
	(void) fprintf(fd, "qcreate Q_OPENACCT_LOG fifo none 2 2 5m 0m \"tmboot -s TMQFORWARD\"\n");
	(void) fprintf(fd, "qcreate Q_OPENACCT fifo none 0 0 100%% 0%% \"\"\n");
	(void) fprintf(fd, "qclose\n");

	exit(_pclose(fd));
}
