/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1991 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/bankapp/TLR.ec	$Revision: 1.5 $" */

#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/TLR.ec	$Revision: 1.5 $";
#endif


#include <stdio.h>			/* UNIX */
#undef MAXFLOAT
#include <math.h>			/* UNIX */
#ifdef _TMFML32
#include <fml32.h>			/* TUXEDO */
#include <fml1632.h>			/* TUXEDO */
#include <Usysfl32.h>			/* TUXEDO */
#else
#include <fml.h>			/* TUXEDO */
#include <Usysflds.h>			/* TUXEDO */
#endif
#include <atmi.h>			/* TUXEDO */
#include <sqlcode.h>			/* TUXEDO */
#include <userlog.h>			/* TUXEDO */
#include "bank.h"			/* BANKING #defines */
#include "bankflds.h"			/* bankdb fields */
#include "eventflds.h"			/* event fields */

EXEC SQL begin declare section;		/* sql declares must be global */
static long account_id;  		/* account id  		 */
static long branch_id;			/* branch id 		 */
static long teller_id;			/* teller id 		 */
static float amt;			/* amount of transaction */
static float acct_bal;			/* account balance       */
static float tlr_bal;			/* teller balance	 */
static float branch_bal;		/* branch balance	 */
EXEC SQL end declare section;

static char amts[BALSTR];		/* string to hold amount */

/* Event logic related */
static float	evt_thresh = 10000.00;	/* default for event threshold */
static char 	emsg[200] ;		/* used by event posting logic */


int
#if defined(__STDC__) || defined(__cplusplus)
tpsvrinit(int argc, char **argv)

#else

tpsvrinit(argc,argv)
int argc;
char **argv;
#endif

{
	int c = 0;

	teller_id = -1L;
	/* TLR must have a teller_id see UBBCONFIG */
	while((c = getopt(argc, argv, "T:e:")) != EOF) {
		switch((char)c) {
		case 'T':
			teller_id = atol(optarg);
			break;
		
		case 'e' :
			evt_thresh = (float)atof (optarg) ;
			break ;
		}
	}

	if (teller_id == -1L) {
		(void)userlog("Unable to get Teller ID from config file\n");
		return(-1);
	}

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

/*
 * Service to make a deposit into an account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
DEPOSIT(TPSVCINFO *transb)

#else
DEPOSIT(transb)
TPSVCINFO *transb;
#endif

{
	FBFR *transf;			/* fielded buffer of decoded message */
	
	/* set pointer to TPSVCINFO data buffer */
	transf = (FBFR *)transb->data;


	/* Get all values for service request from fielded buffer */


	/* must have valid account number */
	if (((account_id = Fvall(transf, ACCOUNT_ID, 0)) < MINACCT) || 
  	    (account_id > MAXACCT)) {
		(void)Fchg(transf, STATLIN, 0, "Invalid account number",(FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }

	if (Fget(transf, SAMOUNT, 0, amts, 0) < 0 || strcmp(amts,"") == 0) {
		(void)Fchg(transf, STATLIN, 0, "Invalid deposit amount",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)sscanf(amts,"%f",&amt);

	/* must have valid amount to deposit */
	if (amt <= 0.0) {
		(void)Fchg(transf, STATLIN, 0,
		           "Deposit amount must be greater than $0.00",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* set cursor dacur on account record */

	EXEC SQL declare dacur cursor for
		select BALANCE from ACCOUNT
			where ACCOUNT_ID = :account_id;
	EXEC SQL open dacur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("account",SQLCODE),(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch dacur into :acct_bal;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("account",SQLCODE),(FLDLEN)0);
		EXEC SQL close dacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* set cursor dtcur on teller record */

	EXEC SQL declare dtcur cursor for
		select BRANCH_ID, BALANCE from TELLER
			where TELLER_ID = :teller_id;
	EXEC SQL open dtcur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("teller",SQLCODE),(FLDLEN)0);
		EXEC SQL close dacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch dtcur into :branch_id, :tlr_bal;
	if (SQLCODE != SQL_OK) {			/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("teller",SQLCODE),(FLDLEN)0);
		EXEC SQL close dacur;
		EXEC SQL close dtcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}


	/* set cursor dbcur on branch record */

	EXEC SQL declare dbcur cursor for
		select BALANCE from BRANCH
			where BRANCH_ID = :branch_id;
	EXEC SQL open dbcur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("branch",SQLCODE),(FLDLEN)0);
		EXEC SQL close dacur;
		EXEC SQL close dtcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch dbcur into :branch_bal;
	if (SQLCODE != SQL_OK) {			/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("branch",SQLCODE),(FLDLEN)0);
		EXEC SQL close dacur;
		EXEC SQL close dtcur;
		EXEC SQL close dbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* Update account record with new BALANCE */

	acct_bal += amt;
	EXEC SQL update ACCOUNT set BALANCE = :acct_bal where current of dacur;
	if (SQLCODE != SQL_OK) {			/* Failure to update */
		(void)Fchg(transf, STATLIN, 0,"Cannot update ACCOUNT",(FLDLEN)0);
		EXEC SQL close dacur;
		EXEC SQL close dtcur;
		EXEC SQL close dbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	EXEC SQL close dacur;

	/* Update teller record with new BALANCE */

	tlr_bal += amt;
	EXEC SQL update TELLER set BALANCE = :tlr_bal where current of dtcur; 
	if (SQLCODE != SQL_OK) {			/* Failure to update */ 
		(void)Fchg(transf, STATLIN, 0, "Cannot update TELLER",(FLDLEN)0); 
		EXEC SQL close dtcur;
		EXEC SQL close dbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	EXEC SQL close dtcur;

	/* Update branch record with new BALANCE */

	branch_bal += amt;
	EXEC SQL update BRANCH set BALANCE = :branch_bal where current of dbcur; 
	if (SQLCODE != SQL_OK) {			/* Failure to update */ 
		(void)Fchg(transf, STATLIN, 0,"Cannot update BRANCH",(FLDLEN)0); 
		EXEC SQL close dbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close dbcur;

	/* Insert history record */

	EXEC SQL insert into HISTORY 
		(ACCOUNT_ID, TELLER_ID, BRANCH_ID, AMOUNT) 
		values 
		(:account_id, :teller_id, :branch_id, :amt);
	if (SQLCODE != SQL_OK) {			/* Failure to insert */
		(void)Fchg(transf, STATLIN, 0, "Cannot update HISTORY",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* prepare buffer for successful return */
	(void)sprintf(amts,"$%.2f",acct_bal);
	(void)Fchg(transf, SBALANCE, 0, amts,(FLDLEN)0);
	(void)sprintf(amts,"$%.2f",amt);
	(void)Fchg(transf, SAMOUNT, 0, amts,(FLDLEN)0);
	(void)Fchg(transf, FORMNAM, 0, "CDEPOSIT",(FLDLEN)0);
	(void)Fchg(transf, STATLIN, 0, "",(FLDLEN)0);
	(void)Fchg(transf, BALANCE, 0, (char *)&acct_bal, (FLDLEN)0);

	/* Post a BANK_TLR_DEPOSIT event ? */

	if (amt < evt_thresh) {
	    /* no event to post  - we're done */
	    tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
	}

	/* initialize the error message string */
	(void)strcpy (emsg, "") ;

	/* add event related fields */
	if ((Fchg (transf, EVENT_NAME, 0, "BANK_TLR_DEPOSIT", (FLDLEN)0) == -1) ||
	    (Fchg (transf, EVENT_TIME, 0, gettime(), (FLDLEN)0) == -1) ||
	    (Fchg (transf, AMOUNT, 0, (char *)&amt,  (FLDLEN)0) == -1)) {

		(void)sprintf (emsg, "Fchg failed for event fields: %s",
					Fstrerror(Ferror));
	}

	/* post the event */
	else if (tppost ("BANK_TLR_DEPOSIT",	/* event name */
			 (char *)transf,	/* data */
			 0L,			/* len */
			 TPNOTRAN | TPSIGRSTRT) == -1) {

	    /* If event broker is not reachable, ignore the error.
	     * This would happen if the event broker was not configured.
	     */
	    if (tperrno != TPENOENT)
		(void)sprintf (emsg, "tppost failed: %s", tpstrerror (tperrno));
	}

	/* any error in processing the post event ? */
	
	if (strcmp (emsg, "") != 0) {
	    (void)userlog ("WARN: Event BANK_TLR_DEPOSIT not posted: %s", emsg);
	    (void)strcpy (emsg, "") ;
	}

	/* delete the event fields from the buffer being returned */
	(void)Fdel(transf, EVENT_NAME, 0) ;
	(void)Fdel(transf, EVENT_TIME, 0) ;
	(void)Fdel(transf, AMOUNT, 0) ;

	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}

/*
 * Service to make a withdrawal from an account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
WITHDRAWAL(TPSVCINFO *transb)

#else

WITHDRAWAL(transb)
TPSVCINFO *transb;
#endif

{
	FBFR *transf;			/* fielded buffer of decoded message */

	/* Set pointer to  TPSVCINFO data buffer */

	transf = (FBFR *)transb->data;

	/* Get all values for service request from fielded buffer */

	/* must have valid account number */
	if (((account_id = Fvall(transf, ACCOUNT_ID, 0)) < MINACCT) || 
	    (account_id > MAXACCT)) {
		(void)Fchg(transf, STATLIN, 0, "Invalid account number", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }

	/* get amount to be withdrawn */
	if (Fget(transf, SAMOUNT, 0, amts, 0) < 0 || strcmp(amts,"") == 0) {
		(void)Fchg(transf, STATLIN, 0, "Invalid withdrawal amount",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)sscanf(amts,"%f",&amt);

	/* must have valid amount to withdraw */
	if (amt <= 0.0) {
		(void)Fchg(transf, STATLIN, 0,
		           "Withdrawal amount must be greater than $0.00",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* set cursor wacur on account record */

	EXEC SQL declare wacur cursor for
		select BALANCE from ACCOUNT
			where ACCOUNT_ID = :account_id;
	EXEC SQL open wacur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("account",SQLCODE),(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch wacur into :acct_bal;
	if (SQLCODE != SQL_OK) {			/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("account",SQLCODE), (FLDLEN)0);
		EXEC SQL close wacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	if (amt > acct_bal) {
		if (fabs(acct_bal - amt) > 0.01) {
			(void)Fchg(transf, STATLIN, 0, "Account Overdraft", (FLDLEN)0);
			EXEC SQL close wacur;
			tpreturn(TPFAIL, 0, transb->data, 0L, 0);
		}
		/* very small discrepancy so make them equal */
		amt = acct_bal;
	}

	/* set cursor wtcur on teller record */

	EXEC SQL declare wtcur cursor for
		select BRANCH_ID, BALANCE from TELLER
			where TELLER_ID = :teller_id;
	EXEC SQL open wtcur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("teller",SQLCODE),(FLDLEN)0);
		EXEC SQL close wacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch wtcur into :branch_id, :tlr_bal;
	if (SQLCODE != SQL_OK) {			/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("teller",SQLCODE), (FLDLEN)0);
		EXEC SQL close wacur;
		EXEC SQL close wtcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	if (amt > tlr_bal) {
		(void)Fchg(transf, STATLIN, 0, "Teller overdraft", (FLDLEN)0);
		EXEC SQL close wacur;
		EXEC SQL close wtcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* set cursor wbcur on branch record */

	EXEC SQL declare wbcur cursor for
		select BALANCE from BRANCH
			where BRANCH_ID = :branch_id;
	EXEC SQL open wbcur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("branch",SQLCODE),(FLDLEN)0);
		EXEC SQL close wacur;
		EXEC SQL close wtcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch wbcur into :branch_bal;
	if (SQLCODE != SQL_OK) {			/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("branch",SQLCODE), (FLDLEN)0);
		EXEC SQL close wacur;
		EXEC SQL close wtcur;
		EXEC SQL close wbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	if (amt > branch_bal) {
		(void)Fchg(transf, STATLIN, 0, "Branch overdraft", (FLDLEN)0);
		EXEC SQL close wacur;
		EXEC SQL close wtcur;
		EXEC SQL close wbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* Update account record with new BALANCE */

	acct_bal -= amt;
	EXEC SQL update ACCOUNT set BALANCE = :acct_bal where current of wacur;
	if (SQLCODE != SQL_OK) {			/* Failure to update */
		(void)Fchg(transf, STATLIN, 0, "Cannot update ACCOUNT", (FLDLEN)0);
		EXEC SQL close wacur;
		EXEC SQL close wtcur;
		EXEC SQL close wbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close wacur;

	/* Update teller record with new BALANCE */

	tlr_bal -= amt;
	EXEC SQL update TELLER set BALANCE = :tlr_bal where current of wtcur;
	if (SQLCODE != SQL_OK) {			/* Failure to update */
		(void)Fchg(transf, STATLIN, 0, "Cannot update TELLER", (FLDLEN)0);
		EXEC SQL close wtcur;
		EXEC SQL close wbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close wtcur;

	/* Update branch record with new BALANCE */

	branch_bal -= amt;
	EXEC SQL update BRANCH set BALANCE = :branch_bal where current of wbcur;
	if (SQLCODE != SQL_OK) {			/* Failure to update */
		(void)Fchg(transf, STATLIN, 0, "Cannot update BRANCH", (FLDLEN)0);
		EXEC SQL close wbcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close wbcur;

	/* Insert history record */

	EXEC SQL insert into HISTORY 
		(ACCOUNT_ID, TELLER_ID, BRANCH_ID, AMOUNT) 
		values 
		(:account_id, :teller_id, :branch_id, :amt);
	if (SQLCODE != SQL_OK) {			/* Failure to insert */
		(void)Fchg(transf, STATLIN, 0, "Cannot update HISTORY", (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* prepare buffer for successful return */
	(void)sprintf(amts,"$%.2f",acct_bal);
	(void)Fchg(transf, SBALANCE, 0, amts, (FLDLEN)0);
	(void)sprintf(amts,"$%.2f",amt);
	(void)Fchg(transf, SAMOUNT, 0, amts, (FLDLEN)0);
	(void)Fchg(transf, FORMNAM, 0, "CWITHDRAW",(FLDLEN)0);
	(void)Fchg(transf, STATLIN, 0, " ", (FLDLEN)0);

	/* Post a BANK_TLR_WITHDRAWAL event ? */

	if (amt < evt_thresh) {
	    /* no event to post */
	    tpreturn(TPSUCCESS, 0,transb->data , 0L, 0);
	}

	/* prepare to post the event */
	if ((Fchg (transf, EVENT_NAME, 0, "BANK_TLR_WITHDRAWAL", (FLDLEN)0) == -1) ||
	    (Fchg (transf, EVENT_TIME, 0, gettime(), (FLDLEN)0) == -1) ||
	    (Fchg (transf, AMOUNT, 0, (char *)&amt, (FLDLEN)0) == -1)) {
		(void)sprintf (emsg, "Fchg failed for event fields: %s",
					Fstrerror(Ferror)) ;
	}

	/* post the event */
	else if (tppost ("BANK_TLR_WITHDRAWAL",	/* event name */
			 (char *)transf,	/* data */
			 0L,			/* len */
			 TPNOTRAN | TPSIGRSTRT) == -1) {
	    /* If event broker is not reachable, ignore the error */
	    if (tperrno != TPENOENT)
		(void)sprintf (emsg, "tppost failed: %s", tpstrerror (tperrno));
	}

	/* any error in processing the post event ? */
	
	if (strcmp (emsg, "") != 0) {
	    (void)userlog ("WARN: Event BANK_TLR_WITHDRAWAL not posted: %s", emsg);
	    (void)strcpy (emsg, "");
	}

	/* delete the event fields from the buffer being returned */
	(void)Fdel(transf, EVENT_NAME, 0);
	(void)Fdel(transf, EVENT_TIME, 0);
	(void)Fdel(transf, AMOUNT, 0);

	tpreturn(TPSUCCESS, 0,transb->data , 0L, 0);
}

/*
 * Service to make a balance inquiry on an account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
INQUIRY(TPSVCINFO *transb)

#else

INQUIRY(transb)
TPSVCINFO *transb;
#endif

{
	FBFR *transf;			/* fielded buffer of decoded message */

	/*  Set pointer to TPSVCINFO data buffer */
	transf = (FBFR *)transb->data;

	/* Get all values for service request from fielded buffer */

	/* must have valid account number */
	if (((account_id = Fvall(transf, ACCOUNT_ID, 0)) < MINACCT) || 
   	    (account_id > MAXACCT)) {
		(void)Fchg(transf, STATLIN, 0, "Invalid account number", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }

	/* Become current on account record */
	EXEC SQL declare icur cursor for
		select BALANCE from ACCOUNT where ACCOUNT_ID = :account_id;
	
	EXEC SQL open icur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg(transf, STATLIN, 0, getstr("account",SQLCODE),(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch icur into :acct_bal;
	if (SQLCODE != SQL_OK) {			/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("account",SQLCODE), (FLDLEN)0);
		EXEC SQL close icur;
		tpreturn(TPFAIL, 0, transb->data , 0L, 0);
	}
	EXEC SQL close icur;


	/* prepare buffer for successful return */
	(void)sprintf(amts,"$%.2f",acct_bal);
	(void)Fchg(transf, SBALANCE, 0, amts, (FLDLEN)0);
	(void)Fchg(transf, FORMNAM, 0, "CBALANCE",(FLDLEN)0);
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}
