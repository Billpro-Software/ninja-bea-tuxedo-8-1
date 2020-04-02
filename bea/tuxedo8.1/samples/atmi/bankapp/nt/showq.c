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

/* #ident	"@(#) samples/atmi/bankapp/nt/showq.c	$Revision: 1.4 $" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void
main(int argc, char* argv[])
{
	char*	qmconfig;
	FILE*	fd;

	/*
	 * Ensure that QMCONFIG is set (run script ./bankvar)
	 * Open the Q space (QSP_BANKAPP)
	 * Set the Q whose info is desired (default is Q_OPENACCT_LOG)
	 * Turn ON verbose mode
	 * List Q contents
	 * Show Q creation information
	 */

	qmconfig = getenv("QMCONFIG");
	if (!qmconfig){
		(void) fprintf(stderr, "QMCONFIG not set\n");
		exit(1);
	}

	fd = _popen("qmadmin", "wt");
	if (!fd)
		exit(1);
	(void) fprintf(fd, "qopen QSP_BANKAPP\n");
	if (argc > 1)
		(void) fprintf(fd, "qset %s\n", argv[1]);
	else
		(void) fprintf(fd, "qset Q_OPENACCT_LOG\n");
	(void) fprintf(fd, "verbose\n");
	(void) fprintf(fd, "qlist\n");
	if (argc > 1)
		(void) fprintf(fd, "qinfo %s\n", argv[1]);
	else
		(void) fprintf(fd, "qinfo Q_OPENACCT_LOG\n");

	exit(_pclose(fd));
}
