/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1990, 1994 Novell, Inc.	*/
/*	Copyright (c) 1994 Novell	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#) samples/atmi/creditapp/auditcon.c	$Revision: 1.5 $"
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/auditcon.c	$Revision: 1.5 $";
#endif

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
#include <atmi.h>		/* TUXEDO */
#include <Uunix.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */

#define	LINE	80		/* size of reply line	*/

/*
 * auditcon is a client program which interactively finds the total balance
 * of all the accounts/tellers at a branch or the total for the entire bank,
 * using conversations. functionaly, auditcon is similiar to audit.
 */

#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char *argv[])
#else
main(argc, argv)
int argc;
char *argv[];
#endif

{
	int cd;			/* conversation descriptor	*/
	char *line;		/* tux buffer holding reply	*/
	char reply[LINE+1];	/* reply line */
	long len;		/* length of recv'd line	*/
	long revent;		/* events for send/recv	*/

	/* Join application */

	if (tpinit((TPINIT *) NULL) == -1) {
		argc = argc;	/* unused */
		(void)userlog("%s: tpinit failed tperrno %d",argv[0],tperrno);
		exit(1);
	}

	/*
	 * string buffer will be used to convey balance request and return
	 * results from conversational service.
	 */

	if ((line = tpalloc("STRING","",LINE+1)) == (char *)NULL) {
		(void)userlog("%s: tpalloc failed tperrno %d",
				argv[0],tperrno);
		exit(1);
	}

	/* start global transaction with no timeout	*/

	if (tpbegin(0,0) == -1) {
		(void)userlog("%s: tpbegin failed tperrno %d",argv[0],tperrno);
		(void)tpabort(0);
		(void)tpterm();
		exit(1);
	}

	/* open connection to audit conversational service.	*/

	if ((cd = tpconnect("AUDITC",NULL,0,TPSENDONLY)) == -1) {
		(void)userlog("%s: tpconnect failed tperrno %d",
				argv[0],tperrno);
		(void)tpabort(0);
		(void)tpterm();
		exit(1);
	}

	/* repeatively query user for balance request type.	*/

	(void)puts("to request a TELLER or ACCOUNT balance for a branch, type");
	(void)puts("the letter t or a, followed by the branch id, followed by <return>\n");
	(void)puts("for ALL TELLER or ACCOUNT balances, type t or a <return>\n");
	(void)puts("q <return> quits the program\n");
	for (;;) {
		(void)gets(reply);
		(void) strcpy(line,reply);

		/* send balance request and relinquish line control.	*/

		if (tpsend(cd,line,0,TPRECVONLY,&revent) == -1) {
			(void)userlog("%s: tpsend failed tperrno %d",
				argv[0],tperrno);
			(void)tpabort(0);
			(void)tpterm();
			exit(1);
		}

		/* wait for service to return balance request results.	*/

		if (tprecv(cd,&line,&len,TPNOCHANGE,&revent) != -1) {
			(void)userlog("%s: tprecv failed tperrno %d revent %ld",
				argv[0],tperrno,revent);
			(void)tpabort(0);
			(void)tpterm();
			exit(1);
		}

		/* anything other than a send or disconnect event is an error.*/

		if ((tperrno != TPEEVENT) || ((revent != TPEV_SENDONLY) &&
			(revent != TPEV_SVCSUCC))) {
			(void)userlog("%s: tprecv failed tperrno %d revent %ld",
				argv[0],tperrno,revent);
			(void)tpabort(0);
			(void)tpterm();
			exit(1);
		}
		if (strcmp(reply, "q") == 0 || revent == TPEV_SVCSUCC)
			break;
		(void) printf("%s\n_________\nanother balance request ??\n",line);
	}


	if (tpcommit(0) == -1) {
		(void)userlog("%s: tpcommit failed tperrno %d",
			argv[0],tperrno);
		(void)tpterm();
		exit(1);
	}
	
	/* Leave application */

	if (tpterm() == -1) {
		(void)userlog("%s: failed to leave application\n", argv[0]);
		exit(1);
	}
	return(0);
}
