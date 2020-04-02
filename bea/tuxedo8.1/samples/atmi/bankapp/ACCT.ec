
/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1991 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/bankapp/ACCT.ec	$Revision: 1.5 $" */

#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/ACCT.ec	$Revision: 1.5 $";
#endif

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
#ifdef _TMFML32
#include <fml32.h>		/* TUXEDO */
#include <fml1632.h>		/* TUXEDO */
#include <Usysfl32.h>		/* TUXEDO */
#else
#include <fml.h>		/* TUXEDO */
#include <Usysflds.h>		/* TUXEDO */
#endif
#include <atmi.h>		/* TUXEDO */
#include <sqlcode.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */
#include "bank.h"		/* BANKING #defines */
#include "bankflds.h"		/* bankdb fields */
#ifdef HOST
#include "creditflds.h"	/* creditdb fields */
#endif
#include "eventflds.h"		/* event fields */

EXEC SQL begin declare section;
static long   account_id;			/* account id */
static long   branch_id;			/* branch id */
static float  bal, tlr_bal;			/* BALANCE */
static char   acct_type;			/* account type */
static char   last_name[21], first_name[21];	/* last name, first name */
static char   mid_init;				/* middle initial */
static char   ss_n[12];				/* social security number */
static char   address[61];			/* address */
static char   phone[13];			/* telephone */
static long   last_acct;			/* last account branch gave */
EXEC SQL end declare section;

static FBFR *reqfb;     	/* fielded buffer for request message */
static long reqlen;		/* length of request buffer */
static char amts[BALSTR];	/* string representation of float */

/* Event logic related */
static char 	emsg[200] ;	/* holds error message string */

/*
 * Service to open a new account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
OPEN_ACCT(TPSVCINFO *transb)
#else
OPEN_ACCT(transb)
TPSVCINFO *transb;
#endif
{
	FBFR   *transf;	/* fielded buffer of decoded message */
	FLDLEN len;

#ifdef HOST
	/* credit card account handling */
	int    opencr=0;	/* set to 1, if credit card account is openned*/
	char   vssn[12];	/* return ssn from VALDC call */
	float  svc_chg;		/* SVCHG*/
	char   svcchg[BALSTR];	/* string rep of SVCHG*/
	char   open_cr;		/* open a credit card? Y/N */
	char   c_acct_type;	/* credit card type */
	long   c_account_id=0L;	/* credit account id */
	float  c_bal=0.0; 	/* credit balance*/
	float  c_crt_line=0.0; 	/* credit line */
	char   cbal[11];
	char   ccrtline[11];
#endif

	/* set pointer to TPSVCINFO data buffer */

	transf = (FBFR *)transb->data;
	(void)Fchg(transf, STATLIN, 0, "", (FLDLEN)0);

	/* Get all values for service request from fielded buffer */

	/* must have opening balance */

	len = BALSTR;
	if (Fget(transf, SAMOUNT, 0, amts, &len) < 0 
		|| strcmp(amts,"") == 0) {
		(void)Fchg(transf, STATLIN, 0, "Invalid amount",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)sscanf(amts,"%f",&bal);

	/* must have valid amount to deposit */
	if (bal <= 0.0) {
		(void)Fchg(transf, STATLIN, 0,
			"Initial deposit must be greater than $0.00",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* must have account type */
	len = sizeof(acct_type) ;
	if (Fget(transf, ACCT_TYPE, 0, &acct_type, &len) < 0) {
                (void)Fchg(transf, STATLIN, 0, 
			   "Invalid account type", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        } 
	len = sizeof(last_name);
	last_name[0] = '\0';
	(void)Fget(transf, LAST_NAME, 0, last_name, &len);

	len = sizeof(first_name);
	first_name[0] = '\0';
	(void)Fget(transf, FIRST_NAME, 0, first_name, &len);

	len = sizeof(mid_init);
	mid_init = '\0';
	(void)Fget(transf, MID_INIT, 0, &mid_init, &len);

	len = sizeof(address);
	address[0] = '\0';
	(void)Fget(transf, ADDRESS, 0, address, &len);

	len = sizeof(phone);
	phone[0] = '\0';
	(void)Fget(transf, PHONE, 0, phone, &len);

	len = sizeof(ss_n);
	ss_n[0] = '\0';
	(void)Fget(transf, SSN, 0, ss_n, &len);

	/* must have branch id */
	if (((branch_id = (long)Fvall(transf, BRANCH_ID, 0)) <= 0L) || 
	    (branch_id > MAXBRANCH)) {
		(void)Fchg(transf, STATLIN, 0, "Invalid branch id", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

#ifdef HOST
	cbal[0] = '\0';
	ccrtline[0] = '\0';

	/* check if want to open a credit card?*/
	len = sizeof(open_cr);
	(void)Fget(transf, OPEN_CR, 0, &open_cr, &len);
	if (open_cr == 'y' || open_cr == 'Y') {
		/* get credit card account type */
		if (Fget(transf, C_ACCT_TYPE, 0, &c_acct_type,&len) < 0) {
                	(void)Fchg(transf, STATLIN, 0, 
			   "Invalid credit card account type", (FLDLEN)0);
                	tpreturn(TPFAIL, 0, transb->data, 0L, 0);
		}

		/* allocate the buffer for OPENC request */
		if ((reqfb = (FBFR *)tpalloc(FMLTYPE,NULL,transb->len)) 
			== (FBFR *)NULL) {
			(void)userlog("tpalloc failed in open_acct\n");
			(void)Fchg(transf, STATLIN, 0,
				"Unable to allocate request buffer", 
				(FLDLEN)0);
			tpreturn(TPFAIL, 0, transb->data, 0L, 0);
		}
		reqlen = Fsizeof(reqfb);

		(void)Fchg(reqfb, LAST_NAME, 0,last_name, (FLDLEN)0);
		(void)Fchg(reqfb, FIRST_NAME, 0,first_name, (FLDLEN)0);
		(void)Fchg(reqfb, MID_INIT, 0,&mid_init, (FLDLEN)0);
		(void)Fchg(reqfb, ADDRESS, 0,address, (FLDLEN)0);
		(void)Fchg(reqfb, SSN, 0,ss_n, (FLDLEN)0);
		(void)Fchg(reqfb, PHONE, 0,phone, (FLDLEN)0);
		(void)Fchg(reqfb, C_ACCT_TYPE, 0,&c_acct_type, (FLDLEN)0);
		(void)Fchg(reqfb, VIEWNAME, 0,"open_cro", (FLDLEN)0);

		/* increase the priority of withdraw call */
		if (tpsprio(PRIORITY, 0L) == -1)
			(void)userlog("Unable to increase priority of withdraw\n");

		/* make the service request call */
		if (tpcall("OPENC", (char *)reqfb, 0L, (char **)&reqfb, 
			(long *)&reqlen, TPNOTRAN) < 0 ) {
			opencr = 0;
			(void)Fchg(transf, STATLIN, 0, 
			   "Unable to open the credit card currently",(FLDLEN)0);
		}
		else {
			opencr = 1;
			c_account_id = (long)Fvall(reqfb,C_ACCOUNT_ID,0);
			(void)Fget(reqfb, C_BAMOUNT, 0, cbal, 0);
			(void)Fget(reqfb, C_CAMOUNT, 0, ccrtline, 0);
		}
		tpfree((char *)reqfb);
        }

	svc_chg = 0.0;
	/* If open a checking account, do a credit reference checking. 
	 * If no credit reference, service charge of $1.00.
	 * If good credit reference, service charge is waived. */
	if ((acct_type == 'c' || acct_type == 'C') && !opencr) {
		if ((reqfb = (FBFR *)tpalloc(FMLTYPE,NULL,transb->len)) 
			== (FBFR *)NULL) {
			(void)userlog("tpalloc failed in open_acct\n");
			(void)Fchg(transf, STATLIN, 0,
				"Unable to allocate request buffer", 
				(FLDLEN)0);
			tpreturn(TPFAIL, 0, transb->data, 0L, 0);
		}
		reqlen = Fsizeof(reqfb);
		(void)Finit(reqfb,(int)reqlen);

		/* put SSN in request buffer */
		(void)Fchg(reqfb, SSN, 0,ss_n, (FLDLEN)0);
		(void)Fchg(reqfb, VIEWNAME, 0,"vald_cr", (FLDLEN)0);

		/* put C_ACCOUNT_ID in request buffer */
		(void)Fadd(reqfb, C_ACCOUNT_ID,(char *)&c_account_id, (FLDLEN)0);

		/* increase the priority of withdraw call */
		if (tpsprio(PRIORITY, 0L) == -1)
			(void)userlog("Unable to increase priority of withdraw\n");
		/* make the service request call */
		if ((tpcall("VALDC", (char *)reqfb, 0L, (char **)&reqfb, 
			(long *)&reqlen, TPNOTRAN) < 0 ) ||
			(Fvall(reqfb, C_ACCOUNT_ID, 0) == 0) ||
			(Fvals(reqfb, SSN, 0) == NULL) ||
			(strcmp(Fvals(reqfb, SSN, 0),"000-00-0000")== 0 )) {
			bal -= 1.0;
			svc_chg = 1.0;
			if (bal <= 0.0) {
				(void)Fchg(transf, STATLIN, 0,
"No credit reference, initial depost must be greater than $1.01",0);
				tpreturn(TPFAIL, 0, transb->data, 0L, 0);
			}

		}
		tpfree((char *)reqfb);
	}  /* if open a checking account */
	(void)sprintf(svcchg,"$%.2f",svc_chg);
#endif

	/* retrieve LAST ACCOUNT number for this branch */
	EXEC SQL declare ocur cursor for
		select LAST_ACCT from BRANCH where BRANCH_ID = :branch_id;
	EXEC SQL open ocur;
	EXEC SQL fetch ocur into :last_acct;
	if (SQLCODE != SQL_OK) {		/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("branch",SQLCODE), (FLDLEN)0);
		EXEC SQL close ocur;		/* close cursor */
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close ocur;			/* close if not already closed */

	/* Insert new account record into ACCOUNT*/

	account_id = ++last_acct; 		/* get new account number */
	tlr_bal = 0.0;				/* temporary balance of 0 */

	EXEC SQL insert into ACCOUNT (ACCOUNT_ID, BRANCH_ID, SSN, BALANCE,
		ACCT_TYPE, LAST_NAME, FIRST_NAME, MID_INIT, ADDRESS, PHONE) 
	values
		(:account_id, :branch_id, :ss_n, :tlr_bal, :acct_type,
		 :last_name, :first_name, :mid_init, :address, :phone);
	if (SQLCODE != SQL_OK) {		/* Failure to insert */
		(void)Fchg(transf, STATLIN, 0, 
			"Cannot update ACCOUNT", (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* Update branch record with new LAST_ACCT */

	EXEC SQL update BRANCH set LAST_ACCT = :last_acct
		where BRANCH_ID = :branch_id;
	if (SQLCODE != SQL_OK) {		/* Failure to update */
		(void)Fchg(transf, STATLIN, 0,"Cannot update BRANCH", (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	
	/* tpcall to deposit service to add amount of initial balance */

	/* make deposit request buffer */
        if ((reqfb = (FBFR *)tpalloc(FMLTYPE,NULL,transb->len)) == (FBFR *)NULL) {
                (void)userlog("tpalloc failed in open_acct\n");
                (void)Fchg(transf, STATLIN, 0, 
			   "Unable to allocate request buffer", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }
        reqlen = Fsizeof(reqfb);
        (void)Finit(reqfb,(FLDLEN)reqlen);

	/* put ID in request buffer */
        (void)Fchg(reqfb,ACCOUNT_ID,0,(char*)&account_id, (FLDLEN)0);

	/* put amount into request buffer */
	(void)sprintf(amts,"%.2f",bal);
	(void)Fchg(reqfb,SAMOUNT,0,amts, (FLDLEN)0);


	/* increase the priority of the deposit call */
	if (tpsprio(PRIORITY, 0L) == -1)
		(void)userlog("Unable to increase priority of deposit\n");

	if (tpcall("DEPOSIT", (char *)reqfb, 0L, (char **)&reqfb, (long *)&reqlen,
 		   TPSIGRSTRT) == -1) {
		(void)Fchg(transf, STATLIN, 0, 
			   "Cannot make deposit into new account", (FLDLEN)0);
		tpfree((char *)reqfb);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }


	/* prepare buffer for successful return */
	(void)Fchg(transf, SBALANCE, 0, Fvals(reqfb,SAMOUNT,0), (FLDLEN)0);
	(void)Fchg(transf, ACCOUNT_ID, 0, (char *)&account_id, (FLDLEN)0);
	(void)Fchg(transf, FORMNAM, 0, "COPEN", (FLDLEN)0);
#ifdef HOST
	(void)Fchg(transf, SVCHG, 0, (char *)svcchg, (FLDLEN)0);
	(void)Fchg(transf, C_BAMOUNT, 0, (char *)cbal, (FLDLEN)0);
	(void)Fchg(transf, C_CAMOUNT, 0, (char *)ccrtline, (FLDLEN)0);
	(void)Fchg(transf, C_ACCOUNT_ID, 0,(char *)&c_account_id, (FLDLEN)0);
#endif
	tpfree((char *)reqfb);

	/* Post a BANK_CTR_OPENACCT event */

	/* initialize error message string */
	(void)strcpy (emsg, "") ;

	/* add event related fields */
	if ((Fchg (transf, EVENT_NAME, 0, "BANK_CTR_OPENACCT", (FLDLEN)0) == -1) ||
	    (Fchg (transf, EVENT_TIME, 0, gettime(), (FLDLEN)0) == -1) ||
	    (Fchg (transf, AMOUNT, 0, (char *)&bal, (FLDLEN)0) == -1)) {

		(void)sprintf (emsg, "Fchg failed for event fields: %s",
					Fstrerror(Ferror)) ;
	}

	/* post the event */
	else if (tppost ("BANK_CTR_OPENACCT",	/* event name */
			 (char *)transf,	/* data */
			 0L,			/* len */
			 TPNOTRAN | TPSIGRSTRT) == -1) {

	    /* If event broker is not reachable, ignore the error.
	     * This would happen if an event broker was not configured.
	     */
	    if (tperrno != TPENOENT)
		(void)sprintf (emsg, "tppost failed: %s", tpstrerror(tperrno));
	}

	/* any error in processing the post event ? */
	
	if (strcmp (emsg, "") != 0) {
	    (void)userlog("WARN: Event BANK_CTR_OPENACCT not posted: %s", emsg);
	    (void)strcpy (emsg, "") ;
	}

	/* delete the event fields from the buffer being returned */
	(void)Fdel (transf, EVENT_NAME, 0) ;
	(void)Fdel (transf, EVENT_TIME, 0) ;
	(void)Fdel (transf, AMOUNT, 0) ;

	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}

/*
 * Service to close an account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
CLOSE_ACCT(TPSVCINFO *transb)
#else
CLOSE_ACCT(transb)
TPSVCINFO *transb;
#endif
{
	FBFR *transf;			/* fielded buffer of decoded message */

	/* set pointer to TPSVCINFO data buffer */
	transf = (FBFR *)transb->data;

	/* must have valid account number */
	if (((account_id = Fvall(transf, ACCOUNT_ID, 0)) < MINACCT) || 
	    (account_id > MAXACCT)) {
		(void)Fchg(transf, STATLIN, 0, "Invalid account number", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }

	/* Retrieve AMOUNT to be deleted */
	EXEC SQL declare ccur cursor for
		select BALANCE from ACCOUNT where ACCOUNT_ID = :account_id;
	EXEC SQL open ccur;
	EXEC SQL fetch ccur into :bal;
	if (SQLCODE != SQL_OK) {		/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("account",SQLCODE), (FLDLEN)0);
		EXEC SQL close ccur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close ccur;

	/* Do final withdrawal */

	/* make withdraw request buffer */
        if ((reqfb = (FBFR *)tpalloc(FMLTYPE,NULL,transb->len)) == (FBFR *)NULL) {
                (void)userlog("tpalloc failed in close_acct\n");
                (void)Fchg(transf, STATLIN, 0, 
			   "Unable to allocate request buffer", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }
        reqlen = Fsizeof(reqfb);
        (void)Finit(reqfb,(FLDLEN)reqlen);

	/* put ID in request buffer */
        (void)Fchg(reqfb,ACCOUNT_ID,0,(char *)&account_id, (FLDLEN)0);

	/* put amount into request buffer */
	(void)sprintf(amts,"%.2f",bal);
	(void)Fchg(reqfb,SAMOUNT,0,amts, (FLDLEN)0);

	/* increase the priority of this withdraw */
	if (tpsprio(PRIORITY, 0L) == -1)
		(void)userlog("Unable to increase priority of withdraw");

	/* tpcall to withdraw service to remove remaining balance */
	if (tpcall("WITHDRAWAL", (char *)reqfb, 0L, (char **)&reqfb, 
		   (long *)&reqlen,TPSIGRSTRT) == -1) {
		(void)Fchg(transf, STATLIN, 0,"Cannot make withdrawal", (FLDLEN)0);
		tpfree((char *)reqfb);
		tpreturn(TPFAIL, 0,transb->data, 0L, 0);
	}

	/* Delete account record */

	EXEC SQL delete from ACCOUNT where ACCOUNT_ID = :account_id;
	if (SQLCODE != SQL_OK) {		/* Failure to delete */
		(void)Fchg(transf, STATLIN, 0,"Cannot close account", (FLDLEN)0);
		tpfree((char *)reqfb);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* prepare buffer for successful return */
	(void)Fchg(transf, SBALANCE, 0, Fvals(reqfb,SAMOUNT,0), (FLDLEN)0);
	(void)Fchg(transf, FORMNAM, 0, "CCLOSE", (FLDLEN)0);
	(void)Fchg(transf, STATLIN, 0, " ", (FLDLEN)0);
	tpfree((char *)reqfb);
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}
