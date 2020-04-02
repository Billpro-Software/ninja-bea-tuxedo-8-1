/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1991 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/bankapp/appinit.c	$Revision: 1.5 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/appinit.c	$Revision: 1.5 $";
#endif


#include <stdio.h>		/* UNIX */
#include <atmi.h>		/* TUXEDO */
#include <Uunix.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */


/* ARGSUSED */
int
#if defined(__STDC__) || defined(__cplusplus)
tpsvrinit(int argc, char **argv)
#else
tpsvrinit(argc,argv)
int argc;
char **argv;
#endif

{


	/* Open database */

	if (tpopen() == -1) {
		(void)userlog("tpsvrinit: failed to open database due to ");
		switch (tperrno) {
		case TPEOS:
			(void)userlog("tpopen failed, Unix error %d\n",Uunixerr);
			break;
		case TPERELEASE:
			(void)userlog("tpopen failed, Incompatible release\n");
			break;
		default:
			(void)userlog("tpopen failed, tperrno: %d\n",tperrno);
		}
		argv = argv; argc = argc;	/* unused */
		return(-1);
	}
	return(0);
}

void
tpsvrdone()
{
	/* Close database */

	if (tpclose() == -1) {
		(void)userlog("tpsrvdone: failed to close database due to ");
		switch (tperrno) {
		case TPEOS:
			(void)userlog("tpclose failed, Unix error %d\n", Uunixerr);
			break;
		case TPERELEASE:
			(void)userlog("tpclose failed, Incompatible release\n");
			break;
		default:
			(void)userlog("tpclose failed, tperrno:  %d\n",tperrno);
		}
	}
}

