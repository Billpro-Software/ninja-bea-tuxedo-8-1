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

/*	Copyright (c) 1994 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ident	"@(#) samples/atmi/creditapp/audit.c	$Revision: 1.5 $"
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/audit.c	$Revision: 1.5 $";
#endif

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
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
static char pgmname[STATLEN];		/* program name = argv[0] */
static char result_str[STATLEN];	/* string to hold results of query */


/*
 * audit is a client program which finds the total balance of all the
 * accounts/tellers at a branch or the total for the entire bank
 */

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
	int retc;		/* return value of sum_bal() */
	struct aud *audv;	/* pointer to audit buf struct */
	int audrl=0;		/* audit return length */
	long q_branchid;	/* branch_id to query */

	(void)strcpy(result_str,"");
	(void)strcpy(pgmname, argv[0]);	/* program name */
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
				      pgmname, pgmname);
			exit(2);
		}

	/* No -a or -t specified */

	if (aud_type == INVI) {
		(void)fprintf(stderr, "%s:  usage %s -a|-t [branch_id]\n",
			      pgmname, pgmname);
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
		              pgmname, pgmname);
		exit(2);
	}

	/* If one positional argument, call ABAL_BID or TBAL_BID */

	if (clarg < argc) {
		(void)strcat(svc_name, "_BID");
		q_branchid = atol(argv[clarg]);
		if (q_branchid < 1) {
			(void)fprintf(stderr, "%s:  BRANCH_ID must be > 0\n",pgmname);
			exit(2);
		}
		nbl++;
		clarg++;
	}

	/* Join application */

	if (tpinit((TPINIT *) NULL) == -1) {
		(void)userlog("%s: failed to join application, %s\n",
			pgmname, tpstrerror(tperrno));
		exit(1);
	}
	

	/* Start global transaction in LOCONS mode */

	if (tpbegin(30, 0) == -1) {
		(void)userlog("%s: failed to begin transaction, %s\n",
			pgmname, tpstrerror(tperrno));
		(void)tpterm();
		exit(1);
	}

	if (nbl == 0) {	/* no branch id specified so do a global sum */
		retc = sum_bal(svc_name, hdr_type);
	} else {

		/* Create buffer and set data pointer */

		if ((audv = (struct aud *)tpalloc("VIEW", "aud", sizeof(struct aud))) 
		    == (struct aud *)NULL) {
			(void)userlog("audit: unable to allocate space for VIEW, %s\n",
				tpstrerror(tperrno));
			(void)tpterm();
			exit(1);
		}

		/* Prepare aud structure */

		audv->b_id = q_branchid;
		audv->balance = 0.0;
		audv->ermsg[0] = '\0';

		/* Do tpcall */

		if (tpcall(svc_name,(char *)audv,sizeof(struct aud),
			   (char **)&audv,(long *)&audrl,0) == -1){
			(void)fprintf (stderr,"%s service failed\n%s:  %s\n%s:  %s\n",
					svc_name, svc_name, audv->ermsg,
					svc_name, tpstrerror(tperrno));
			retc = -1;
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
			(void)userlog("%s: failed to commit transaction, %s\n",
				pgmname, tpstrerror(tperrno));
			(void)tpterm();
			exit(1);
		}
		/*print out results only when transaction has committed successfully*/
		(void)printf("%s",result_str);
	}


	/* Leave application */

	if (tpterm() == -1) {
		(void)userlog("%s: failed to leave application, %s\n",
			pgmname, tpstrerror(tperrno));
		exit(1);
	}
#ifdef lint
	return 1;
#else
	exit(1);
#endif
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

	if ((audv = (struct aud *)tpalloc("VIEW", "aud", sizeof(struct aud))) ==
	    (struct aud *)NULL){
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
				      pgmname, sname, sitelist[i], tpstrerror(tperrno));
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
					pgmname, sname, audv->b_id,
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
