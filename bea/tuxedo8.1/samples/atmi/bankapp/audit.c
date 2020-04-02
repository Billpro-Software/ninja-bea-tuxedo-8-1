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
/* #ident	"@(#) samples/atmi/bankapp/audit.c	$Revision: 1.5 $" */

#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/audit.c	$Revision: 1.5 $";
#endif

/*
 * audit is a client program which finds the total balance of all the
 * accounts/tellers at a branch or the total for the entire bank
 */

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
#ifdef _TMFML32
#include <fml32.h>		/* TUXEDO */
#include <fml1632.h>		/* TUXEDO */
#else
#include <fml.h>		/* TUXEDO */
#endif
#include <atmi.h>		/* TUXEDO */
#include <Uunix.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */
#include "bank.h"		/* BANKING #defines */
#include "aud.h"		/* BANKING view defines */

#define INVI 0			/* account inquiry */
#define ACCT 1			/* account inquiry */
#define TELL 2			/* teller inquiry */


static int sum_bal _((char *, char *));
static long sitelist[NSITE] = SITEREP;	/* list of machines to audit */
static char result_str[STATLEN];	/* string to hold results of query */


#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char *argv[])

#else

main(argc, argv)
int argc;
char *argv[];
#endif

{
	int aud_type=INVI;	/* audit type -- invalid unless specified */
	int clarg;		/* command line arg index from optind */
	int c;			/* Option character */
	int cflgs=0;		/* Commit flags, currently unused */
	int aflgs=0;		/* Abort flags, currently unused */
	int nbl=0;		/* count of branch list entries */
	char svc_name[NAMELEN];	/* service name */
	char hdr_type[NAMELEN];	/* heading to appear on output */
	int retc=0;		/* return value of sum_bal() */
	struct aud *audv;	/* pointer to audit buf struct */
	int audrl=0;		/* audit return length */
	long q_branchid;	/* branch_id to query */

	TPINIT *tpinitbuf ;	/* for client identification */
	int	auth ;		/* to hold value of tpchkauth() */
	char	*passwd ;	/* passwd obtained from user */

	(void)strcpy(result_str,"");
	if (strrchr(argv[0],'/') != NULL)
		proc_name = strrchr(argv[0],'/')+1;
	else
		proc_name = argv[0];

	while((c = getopt(argc,argv,"at")) != EOF)
		switch((char)c) {
		case 'a':
			aud_type=ACCT;
			(void)strcpy(svc_name,"ABAL");
			(void)strcpy(hdr_type,"Account");
			break;
		case 't':
			aud_type=TELL;
			(void)strcpy(svc_name,"TBAL");
			(void)strcpy(hdr_type,"Teller");
			break;
		default:
			(void)fprintf(stderr,
				      "%s:  usage %s -a|-t [branch_id]\n",
				      proc_name, proc_name);
			exit(2);
		}

	/* No -a or -t specified */

	if (aud_type == INVI) {
		(void)fprintf(stderr, "%s:  usage %s -a|-t [branch_id]\n",
			      proc_name, proc_name);
		exit(2);
	}

	/*
	 *  Positional argument is a branch to query.  If there are
	 *  no such arguments, the service request will be to "ABAL" or
	 *  "TBAL," which query the global database to obtain a total
	 *  bank balance for accounts or tellers respectively.  If there
	 *  is one such argument, the service request will be to
	 *  "ABAL_BID" or "TBAL_BID" (hence the strcat statement),
	 *  once for each element in "sitelist".  If there are two or
	 *  more such elements, print an error message and exit.
	 */

	clarg = optind;

	/* If more than one positional argument, exit */

	if (clarg < argc - 1) {
		(void)fprintf(stderr, "%s:  usage %s -a|-t [branch_id]\n",
		              proc_name, proc_name);
		exit(2);
	}

	/* If one positional argument, call ABAL_BID or TBAL_BID */

	if (clarg < argc) {
		(void)strcat(svc_name, "_BID");
		q_branchid = atol(argv[clarg]);
		if (q_branchid < 1) {
			(void)fprintf(stderr, "%s:  BRANCH_ID must be > 0\n",proc_name);
			exit(2);
		}
		nbl++;
		clarg++;
	}

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
	

	/* Start global transaction in LOCONS mode */

	if (tpbegin(30, 0) == -1) {
		(void)fprintf(stderr, "Failed to begin transaction, %s\n",
			tpstrerror(tperrno));
		(void)userlog("Failed to begin transaction, %s",
			tpstrerror(tperrno));
		(void)tpterm();
		exit(1);
	}

	if (nbl == 0) {	/* no branch id specified so do a global sum */
		retc = sum_bal(svc_name, hdr_type);
	} else {

		/* Create buffer and set data pointer */

		if ((audv = (struct aud *)tpalloc(VIEWTYPE, "aud", sizeof(struct aud))) 
		    == (struct aud *)NULL) {
			(void)fprintf(stderr, "Unable to allocate space for VIEW, %s\n",
				tpstrerror(tperrno));
			(void)userlog("Unable to allocate space for VIEW, %s",
				tpstrerror(tperrno));
			(void)tpterm();
			exit(1);
		}

		/* Prepare aud structure */

		audv->b_id = q_branchid;
		audv->balance = 0.0;
		audv->ermsg[0] = '\0';

		/* Do tpcall */

		if ((retc=tpcall(svc_name,(char *)audv,sizeof(struct aud),
			   (char **)&audv,(long *)&audrl,0)) == -1){
			(void)fprintf (stderr,"%s service failed\n%s:  %s\n%s:  %s\n",
					svc_name, svc_name, audv->ermsg,
					svc_name, tpstrerror(tperrno));
		}
		else {
			(void)sprintf(result_str,"Branch %ld %s balance is $%.2f\n",
				      audv->b_id, hdr_type, audv->balance);
		}
		tpfree((char *)audv);
	}

	/* Commit global transaction in LOCONS mode */

	if (retc < 0)		/* sum_bal failed so abort */
		(void) tpabort(aflgs);
	else {
		if (tpcommit(cflgs) == -1) {
			(void)fprintf(stderr, "Failed to commit transaction, %s\n",
				tpstrerror(tperrno));
			(void)userlog("Failed to commit transaction, %s",
				tpstrerror(tperrno));
			(void)tpterm();
			exit(1);
		}
		/*print out results only when transaction has committed successfully*/
		(void)printf("%s",result_str);
	}


	/* Leave application */

	if (tpterm() == -1) {
		(void)fprintf(stderr, "Failed to leave application, %s\n",
			tpstrerror(tperrno));
		(void)userlog("Failed to leave application, %s",
			tpstrerror(tperrno));
		exit(1);
	}
	return(0);
}

/*
 * sum_bal does asynchronous calls to service ABAL or TBAL for each SITE 
 * and then returns the total of the balances.
 */

static int
#if defined(__STDC__) || defined(__cplusplus)
sum_bal(char *sname, char *htype)

#else

sum_bal(sname, htype)
char *sname, *htype;
#endif

{
	int i;			/* counter */
	struct aud *audv;	/* pointers to audit buf struct */
	long audrl;		/* return length on getrply */
	int anycd;		/* receives call descriptor */
	float total = 0.0;	/* total bank balance */

	/* Create buffer and set data pointer */

	if ((audv = (struct aud *)tpalloc(VIEWTYPE, "aud", sizeof(struct aud))) ==
	    (struct aud *)NULL){
		(void)fprintf(stderr, "sum_bal: unable to allocate space for VIEW, %s\n",
			tpstrerror(tperrno));
		(void)userlog("sum_bal: unable to allocate space for VIEW, %s",
			tpstrerror(tperrno));
		return(-1);
	}

	/* initialize aud structure */
	audv->balance = 0.0;
	audv->ermsg[0] = '\0';

	for (i=0; i<NSITE; i++) {

		audv->b_id = sitelist[i];	/* routing done on this field */

		/* Do tpacall */

		if (tpacall(sname, (char *)audv, sizeof(struct aud), 0) == -1) {
			(void)fprintf(stderr,
				      "%s: %s service request failed for site rep %ld, %s\n",
				      proc_name, sname, sitelist[i], tpstrerror(tperrno));
			tpfree((char *)audv);
			return(-1);
        	}
	}

	/* 
	 * Do tpgetrplys to retrieve answers to questions 
	 * failure of any one will result in total failure 
	 */
	for (i=0; i<NSITE; i++) {
		if (tpgetrply(&anycd, (char **)&audv,&audrl, TPGETANY) == -1) {
			if (tperrno != TPESVCFAIL) {
				(void)fprintf (stderr,"service tpgetrply failed, %s\n",
					tpstrerror(tperrno));
				tpfree((char *)audv);
				return(-1);
        		}
			(void)fprintf(stderr,
					"%s: %s service routine failed for site rep %ld, %s\n",
					proc_name, sname, audv->b_id,
					tpstrerror(tperrno));
			tpfree((char *)audv);
			return(-1);
        	}
		total += audv->balance;
	}

	(void)sprintf(result_str,"%s balance for entire bank is $%.2f\n", htype, total);
	tpfree((char *)audv);
	return(0);
}
