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

/* #ident	"@(#) samples/atmi/bankapp/nt/crtlog.c	$Revision: 1.4 $" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <Uunix.h>

static void
usage()
{
	(void) fprintf(stderr, "Usage: crtlog [-m]\n");
	exit(2);
}

void
main(int argc, char* argv[])
{
	char *tlogdevice;
	FILE *fd;
	int exitcode;
	int mopt = 0;
	char *cmd = "tmadmin -c";

	switch(argc) {
	case 1:
		break;
	case 2:
		if (strcmp(argv[1], "-m") == 0) {
			mopt = 1;
			cmd = "tmadmin";
		}
		else
			usage();
		break;
	default:
		usage();
	}

		
	tlogdevice = tuxgetenv("TLOGDEVICE");

	if (!tlogdevice) {
		(void) fprintf(stderr, "Missing TLOGDEVICE in environment\n");
		exit(1);
	}

	fd = _popen(cmd, "wt");

	if (!fd){
		(void) fprintf(stderr, "Cannot start tmadmin: %s\n", strerror(errno));
		exit(1);
	}

	(void) fprintf(fd, "echo\n");

	(void) fprintf(fd, "crdl -z %s -b 1500\n", tlogdevice);

	if (mopt) {
		(void) fprintf(fd, "crlog -m SITE1\n");
	}

	exitcode = _pclose(fd);

	if (exitcode != 0) {
		(void) fprintf(stderr, "tmadmin failed to create device list.\n");
		exit(1);
	}

	(void) printf("crtlog successful.\n");

	exit(0);
}
