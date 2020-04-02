/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/* #ident	"@(#) samples/atmi/bankapp/AUDITC.c	$Revision: 1.5 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/AUDITC.c	$Revision: 1.5 $";
#endif

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
#ifdef _TMFML32
#include <fml32.h>
#include <fml1632.h>
#else
#include <fml.h>
#endif
#include <atmi.h>		/* TUXEDO */
#include <Uunix.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */
#include "bank.h"		/* BANKING #defines */
#include "aud.h"		/* BANKING view defines */

#define INVI 0			/* account inquiry */
#define ACCT 1			/* account inquiry */
#define TELL 2			/* teller inquiry */
#define LINE 80			/* size of balance request line	*/


static long sitelist[NSITE] = SITEREP;	/* list of machines to audit */
static char pgmname[STATLEN];		/* program name = argv[0] */
static struct aud *audv;		/* pointer to audit buf struct */
static void sum_bal _((char *, char *, char *));

/*
 * AUDITC is a conversational server containing a service of the same 
 * name that finds the total balance of all accounts/tellers at a 
 * branch or the total for the entire bank
 */

int
#if defined(__STDC__) || defined(__cplusplus)
tpsvrinit(int argc, char **argv)
#else
tpsvrinit(argc,argv)
int     argc;
char    **argv;
#endif
{
	(void)strcpy(pgmname, argv[0]); /* program name */
	userlog("%s started", pgmname);

	/* open resource manager	*/

	if (tpopen() == -1) {
		argc = argc;	/* unused */
		(void)userlog("%s: tpopen failed tperrno %d",
			pgmname,tperrno);
		return(-1);
	}

	/* allocate view buffer to used in all balance queries.	*/

	if ((audv = (struct aud *)tpalloc(VIEWTYPE, "aud", sizeof(struct aud)))
		    == (struct aud *)NULL) {
		(void)userlog("%s: view tpalloc failed tperrno %d",
			pgmname,tperrno);
		return(-1);
	}
	return(0);
}

void
#if defined(__STDC__) || defined(__cplusplus)
AUDITC(TPSVCINFO *svcinfo)
#else
AUDITC(svcinfo)
TPSVCINFO *svcinfo;
#endif
{
	
	char c;			/* Option character */
	char svc_name[NAMELEN];	/* service name */
	char hdr_type[NAMELEN];	/* heading to appear on output */
	char *line;		/* tux buffer holding request	*/
	int audrl=0;		/* audit return length */
	long q_branchid;	/* branch_id to query */
	long len;		/* length of recv'd line	*/
	long revent;		/* events for send/recv */

	/* allocate buffer to receive balance request.	*/

	if ((line = tpalloc("STRING","",LINE+1)) == (char *)NULL) {
		(void)userlog("%s: string tpalloc failed tperrno %d",
                        pgmname,tperrno);
		(void)tpreturn(TPFAIL,0,NULL,0,0);
	}
	for (;;) {

		/* receive balance request	*/

		if (tprecv(svcinfo->cd,&line,&len,TPNOCHANGE,&revent) != -1) {
			(void)userlog("%s: recv'd message without event",pgmname);
			(void)sprintf(line,"%s:  audit request failed (see ulog)\n",
	                                pgmname);
			(void)tpreturn(TPFAIL,0,line,strlen(line),0);
		}

		/* if anything other than an event is received, its an error. */

		switch (tperrno) {
		case	TPEEVENT:
			switch ((int)revent) {
			case	TPEV_SENDONLY:
				break;
			case	TPEV_DISCONIMM: /* disorderly disconnect */
				(void)tpreturn(TPSUCCESS,0,NULL,0,0);
			}
			break;
		default:
			(void)userlog("%s: tprecv failed tperrno %d revent %ld",                                pgmname,tperrno,revent);
			(void)sprintf(line,"%s:  audit request failed (see ulog)\n",
					pgmname);
			(void)tpreturn(TPFAIL,0,line,strlen(line),0);
		}
	
		/*
		 * if no branch id is provided, the service request will be to
		 *  "ABAL" or "TBAL," which query the global database to 
		 *  obtain a total bank balance for accounts or tellers
		 *  respectively.  If there is a branch id, the service
		 *  request will be to "ABAL_BID" or "TBAL_BID"
		 */

		(void)sscanf(line,"%c %ld",&c,&q_branchid);
		switch((int)c) {
		case 'q':
			(void)tpreturn(TPSUCCESS,0,NULL,0,0);
			break;
		case 'a':
			(void)strcpy(svc_name,"ABAL");
			(void)strcpy(hdr_type,"Account");
			break;
		case 't':
			(void)strcpy(svc_name,"TBAL");
			(void)strcpy(hdr_type,"Teller");
			break;
		default:
			(void)sprintf(line,
				      "%s:  usage %s a|t [branch_id]\n",
				      pgmname, pgmname);
		}
		switch((int)c) {
		case 'a':
		case 't':
			if (strlen(line) == 1) {
				/* no branch id specified so do a global sum */

				sum_bal(svc_name, hdr_type, line);
			} else {
				/* Prepare aud structure */
		
				audv->b_id = q_branchid;
				audv->balance = 0.0;
				audv->ermsg[0] = '\0';
		
				(void)strcat(svc_name, "C_BID");
				if (tpcall(svc_name,(char *)audv,
					sizeof(struct aud),(char **)&audv,
					   (long *)&audrl,0) == -1){
					(void)userlog("%s: tpcall failed tperrno %d",
						pgmname,tperrno);
					(void)sprintf(line,
						"%s: balance request failed (see ulog)\n",
						pgmname);
					(void)tpreturn(TPFAIL,0,line,strlen(line),0);
				}
				switch (tpurcode) {
				case	0:
					(void)sprintf(line,
					"Branch %ld %s balance is $%.2f\n",
					audv->b_id, hdr_type, audv->balance);
					break;
				case	1:
					(void)sprintf(line,
						"%s service failed\n%s: %s\n",
						svc_name,svc_name,audv->ermsg);
					break;
				default:
					(void)sprintf(line,
						"%s: invalid tpucode %ld",
						pgmname, tpurcode);
					(void)tpreturn(TPFAIL,0,line,strlen(line),0);
				}
			}
			break;
		default:
			break;
		}

		/* return balance query results	*/

		if (tpsend(svcinfo->cd,line,0,TPRECVONLY,&revent) == -1) {
			switch (tperrno) {
			case	TPEEVENT:
				switch ((int)revent) {
				case	TPEV_DISCONIMM:
					(void)tpreturn(TPSUCCESS,0,NULL,0,0);
				}
			default:
				(void)userlog("%s: tpsend failed tperrno %d revent %ld",
	                       	pgmname,tperrno,revent);
				(void)sprintf(line,
					"%s: tpsend failed (see ulog)\n",
					pgmname);
				(void)tpreturn(TPFAIL,0,line,strlen(line),0);
			}
		}
	}
}

/*
 * sum_bal does asynchronous calls to service ABAL or TBAL for each SITE 
 * and then returns the total of the balances.
 */

static void
#if defined(__STDC__) || defined(__cplusplus)
sum_bal(char *sname, char *htype, char *line)
#else
sum_bal(sname, htype, line)
char *sname, *htype, *line;
#endif
{
	int i;			/* counter */
	long audrl;		/* return length on getrply */
	int anycd;		/* receives call descriptor */
	float total = 0.0;	/* total bank balance */

	/* initialize aud structure */
	audv->balance = 0.0;
	audv->ermsg[0] = '\0';

	for (i=0; i<NSITE; i++) {

		audv->b_id = sitelist[i];	/* routing done on this field */

		/* query all sites asynchronously	*/

		if (tpacall(sname, (char *)audv, sizeof(struct aud), 0) == -1) {
			(void)userlog("%s: tpacall failed tperrno %d",
        			pgmname,tperrno);
			(void)sprintf(line,
				"%s: %s site %ld service request failed (see ulog)\n",
				pgmname, sname, sitelist[i]);
			tpreturn(TPFAIL,0,line,strlen(line),0);
        	}
	}

	/* 
	 * Do tpgetrplys to retrieve answers to questions 
	 * failure of any one will result in total failure 
	 */
	for (i=0; i<NSITE; i++) {
		if (tpgetrply(&anycd, (char **)&audv,&audrl, TPGETANY) == -1) {
			if (tperrno != TPESVCFAIL) {
				(void)userlog("%s: tpgetrply failed tperrno %d",
					pgmname,tperrno);
				(void)sprintf (line,
					"service tpgetrply failed (see ulog)\n");
				tpreturn(TPFAIL,0,line,strlen(line),0);
        		}
			(void)sprintf(line,
			      "%s: %s service routine failed for site rep %ld\n",
			      pgmname,sname,audv->b_id);
			tpreturn(TPFAIL,0,line,strlen(line),0);
        	}
		total += audv->balance;
	}

	(void)sprintf(line,"%s balance for entire bank is $%.2f\n",
					htype, total);
	return;
}
