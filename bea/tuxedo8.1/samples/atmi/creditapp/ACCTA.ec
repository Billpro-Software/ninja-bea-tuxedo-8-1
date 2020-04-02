/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1994 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ident	"@(#) samples/atmi/creditapp/ACCTA.ec	$Revision: 1.5 $" 
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/ACCTA.ec	$Revision: 1.5 $";
#endif

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
#include <fml.h>		/* TUXEDO */
#include <atmi.h>		/* TUXEDO */
#include <Usysflds.h>		/* TUXEDO */
#include <sqlcode.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */
#include "bank.h"		/* BANKING #defines */
#include "bank.flds.h"		/* bankdb fields */


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

/*
 * Service to open a new account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
OPEN_ACCT2(TPSVCINFO *transb)
#else
OPEN_ACCT2(transb)
TPSVCINFO *transb;
#endif
{
	FBFR   *transf;	/* fielded buffer of decoded message */
	FLDLEN len;

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
        if ((reqfb = (FBFR *)tpalloc("FML",NULL,transb->len)) == (FBFR *)NULL) {
                (void)userlog("tpalloc failed in open_acct\n");
                (void)Fchg(transf, STATLIN, 0, 
			   "Unable to allocate request buffer", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }
        reqlen = Fsizeof(reqfb);
        (void)Finit(reqfb,(int)reqlen);

	/* put ID in request buffer */
        (void)Fchg(reqfb,ACCOUNT_ID,0,(char*)&account_id, (FLDLEN)0);

	/* put amount into request buffer */
	(void)sprintf(amts,"%.2f",bal);
	(void)Fchg(reqfb,SAMOUNT,0,amts, (FLDLEN)0);


	/* increase the priority of the deposit call */
	if (tpsprio(PRIORITY, 0L) == -1)
		(void)userlog("Unable to increase priority of deposit\n");

	if (tpcall("DEPOSITA", (char *)reqfb, 0L, (char **)&reqfb, (long *)&reqlen,
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
	tpfree((char *)reqfb);
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
        if ((reqfb = (FBFR *)tpalloc("FML",NULL,transb->len)) == (FBFR *)NULL) {
                (void)userlog("tpalloc failed in close_acct\n");
                (void)Fchg(transf, STATLIN, 0, 
			   "Unable to allocate request buffer", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }
        reqlen = Fsizeof(reqfb);
        (void)Finit(reqfb,(int)reqlen);

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
