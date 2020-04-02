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
/* #ident	"@(#) samples/atmi/bankapp/auditcon.c	$Revision: 1.5 $" */

#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/auditcon.c	$Revision: 1.5 $";
#endif

/*
 * auditcon is a client program which interactively finds the total balance
 * of all the accounts/tellers at a branch or the total for the entire bank,
 * using conversations. functionaly, auditcon is similiar to audit.
 */

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
#include <atmi.h>		/* TUXEDO */
#include <Uunix.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */

#define	LINE	80		/* size of reply line	*/

#ifdef WIN32
extern char *getpass _((const char *prompt));
#endif


/* ARGSUSED */

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

	TPINIT *tpinitbuf ;	/* for client identification */
	int	auth ;		/* to hold value of tpchkauth() */
	char	*passwd ;	/* passwd obtained from user */

	if (strrchr(argv[0],'/') != NULL)
		proc_name = strrchr(argv[0],'/')+1;
	else
		proc_name = argv[0];

	/*
	 * Alloc a TPINIT buffer for identification purposes
	 * This is not mandatory if no authentication is configured
	 */

	tpinitbuf = (TPINIT *) tpalloc("TPINIT", NULL, TPINITNEED(16)) ;

	if (tpinitbuf == (TPINIT *) NULL) {
		(void)fprintf(stderr, "Failed for TPINIT buffer, %s\n",
			tpstrerror(tperrno));
		(void)userlog("Failed for TPINIT buffer, %s",
			tpstrerror(tperrno));
		exit(1);
	}

	/*
	 * Check the type of authentication the application is configured
	 * for and populate TPINIT buffer with authentication info.
	 */

	switch (auth = tpchkauth()) {
	    case TPNOAUTH :
		    (void)strcpy (tpinitbuf->usrname, argv[0]) ;
		    (void)strcpy (tpinitbuf->passwd, "") ;
		    break ;

	    case TPSYSAUTH :
	    case TPAPPAUTH :
		    /* request for the application password */

		    if ((passwd = getpass("Application Password:")) == NULL) {
			(void)userlog ("ERROR: Unable to get Application Password");
			exit(3) ;
		    }
		    (void)strcpy (tpinitbuf->passwd, passwd) ;

		    if (auth == TPSYSAUTH)
			break ;

		    /* request for the user name and user's password */

		    (void)printf ("User Name:") ;
		    (void)gets (tpinitbuf->usrname) ;
		    (void)strcpy (tpinitbuf->cltname, "*") ;
		    (void)strcpy (tpinitbuf->grpname, "") ;

		    if ((passwd = getpass("User Password:")) == NULL) {
			(void)userlog ("ERROR: Unable to get User Password");
			exit(3) ;
		    }
		    (void)strcpy ((char *) &tpinitbuf->data, passwd) ;

		    tpinitbuf->datalen = strlen ((char *) &tpinitbuf->data)+1L;
		    break ;
	}

	/* Join application */

	if (tpinit(tpinitbuf) == -1) {
		(void)fprintf(stderr, "Failed to join application, %s\n",
			tpstrerror(tperrno));
		(void)userlog("Failed to join application, %s",
			tpstrerror(tperrno));
		exit(1);
	}
	
	/*
	 * string buffer will be used to convey balance request and return
	 * results from conversational service.
	 */

	if ((line = tpalloc("STRING","",LINE+1)) == (char *)NULL) {
		(void)fprintf(stderr,"tpalloc failed tperrno %d\n", tperrno);
		(void)userlog("tpalloc failed tperrno %d", tperrno);
		exit(1);
	}

	/* start global transaction with no timeout	*/

	if (tpbegin(0,0) == -1) {
		(void)fprintf(stderr,"tpbegin failed tperrno %d\n",tperrno);
		(void)userlog("tpbegin failed tperrno %d",tperrno);
		(void)tpabort(0);
		(void)tpterm();
		exit(1);
	}

	/* open connection to audit conversational service.	*/

	if ((cd = tpconnect("AUDITC",NULL,0,TPSENDONLY)) == -1) {
		(void)fprintf(stderr,"tpconnect failed tperrno %d\n", tperrno);
		(void)userlog("tpconnect failed tperrno %d", tperrno);
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
			(void)fprintf(stderr,"tpsend failed tperrno %d\n", tperrno);
			(void)userlog("tpsend failed tperrno %d", tperrno);
			(void)tpabort(0);
			(void)tpterm();
			exit(1);
		}

		/* wait for service to return balance request results.	*/

		if (tprecv(cd,&line,&len,TPNOCHANGE,&revent) != -1) {
			(void)fprintf(stderr,"tprecv failed tperrno %d revent %ld\n",
				tperrno,revent);
			(void)userlog("tprecv failed tperrno %d revent %ld",
				tperrno,revent);
			(void)tpabort(0);
			(void)tpterm();
			exit(1);
		}

		/* anything other than a send or disconnect event is an error.*/

		if ((tperrno != TPEEVENT) || ((revent != TPEV_SENDONLY) &&
			(revent != TPEV_SVCSUCC))) {
			(void)fprintf(stderr,"tprecv failed tperrno %d revent %ld\n",
				tperrno,revent);
			(void)userlog("tprecv failed tperrno %d revent %ld",
				tperrno,revent);
			(void)tpabort(0);
			(void)tpterm();
			exit(1);
		}
		if (strcmp(reply, "q") == 0 || revent == TPEV_SVCSUCC)
			break;
		(void) printf("%s\n_________\nanother balance request ??\n",line);
	}


	if (tpcommit(0) == -1) {
		(void)fprintf(stderr,"tpcommit failed tperrno %d\n",
			tperrno);
		(void)userlog("tpcommit failed tperrno %d",
			tperrno);
		(void)tpterm();
		exit(1);
	}
	
	/* Leave application */

	if (tpterm() == -1) {
		(void)fprintf(stderr,"failed to leave application\n\n");
		(void)userlog("failed to leave application\n");
		exit(1);
	}
	return(0);
}
