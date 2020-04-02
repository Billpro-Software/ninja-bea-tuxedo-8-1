/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1994 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ident	"@(#) samples/atmi/creditapp/CRDTA.ec	$Revision: 1.5 $"
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/CRDTA.ec	$Revision: 1.5 $";
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
static float  c_bal, b_bal;			/* BALANCE */
static char   c_acct_type;			/* account type */
static char   last_name[21], first_name[21];	/* last name, first name */
static char   mid_init;				/* middle initial */
static char   ss_n[12];				/* social security number */
static char   address[61];			/* address */
static char   phone[13];			/* telephone */
static long   last_cr_acct;			/* last credit account branch gave */
EXEC SQL end declare section;

static FBFR *reqfb;     	/* fielded buffer for request message */
static long reqlen;		/* length of request buffer */
static char amts[BALSTR];	/* string representation of float */
static char amts2[BALSTR];	/* string representation of float */

/*
 * Service to open a new account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
OPENCA(TPSVCINFO *transb)
#else
OPENCA(transb)
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

        /* each account starts with $5000 */

	c_bal=5000.0;
	/* all is available to user  */
	b_bal=5000.0;




	/* must have account type */
	len = sizeof(c_acct_type) ;
	if (Fget(transf, C_ACCT_TYPE, 0, &c_acct_type, &len) < 0) {
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

userlog ("BEFORE SQL ");

	/* retrieve LAST CREDIT ACCOUNT number for this branch */
	EXEC SQL declare ocur cursor for
		select LAST_CR_ACCT from BRANCH where BRANCH_ID = :branch_id;
	EXEC SQL open ocur;
	EXEC SQL fetch ocur into :last_cr_acct;
	if (SQLCODE != SQL_OK) {		/* nothing found */
		(void)Fchg(transf, STATLIN, 0, getstr("branch",SQLCODE), (FLDLEN)0);
		EXEC SQL close ocur;		/* close cursor */
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close ocur;			/* close if not already closed */

userlog ("BEFORE SQL2 ");
	/* Insert new account record into ACCOUNT*/

	account_id = ++last_cr_acct; 		/* get new account number */

userlog ("ACCOUNT %d ",account_id);
	EXEC SQL insert into CREDIT (C_ACCOUNT_ID, BRANCH_ID, SSN, C_CAMOUNT,
	C_BAMOUNT,C_ACCT_TYPE, LAST_NAME, FIRST_NAME, MID_INIT, ADDRESS, PHONE) 
	values
		(:account_id, :branch_id, :ss_n, :c_bal,:b_bal, :c_acct_type,
		 :last_name, :first_name, :mid_init, :address, :phone);
	if (SQLCODE != SQL_OK) {		/* Failure to insert */
		(void)Fchg(transf, STATLIN, 0, 
			"Cannot update ACCOUNT", (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

userlog ("BEFORE SQL3 ");
	/* Update branch record with new LAST_ACCT */

	EXEC SQL update BRANCH set LAST_CR_ACCT = :last_cr_acct
		where BRANCH_ID = :branch_id;
	if (SQLCODE != SQL_OK) {		/* Failure to update */
		(void)Fchg(transf, STATLIN, 0,"Cannot update BRANCH", (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

userlog ("BEFORE SQL4 ");
	
	EXEC SQL COMMIT WORK;


	/* prepare buffer for successful return */
	(void)Fchg(transf, C_ACCOUNT_ID, 0, (char *)&account_id, (FLDLEN)0);
	(void)Fchg(transf, FORMNAM, 0, "HCOPEN", (FLDLEN)0);
	(void)Fchg(transf, C_BAMOUNT, 0, (char *)&b_bal, (FLDLEN)0);
	(void)Fchg(transf, C_CAMOUNT, 0, (char *)&c_bal, (FLDLEN)0);
	tpfree((char *)reqfb);
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}

/*
 * Service to close an account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
CLOSECA(TPSVCINFO *transb)
#else
CLOSECA(transb)
TPSVCINFO *transb;
#endif
{
	FBFR *transf;			/* fielded buffer of decoded message */

	/* set pointer to TPSVCINFO data buffer */
	transf = (FBFR *)transb->data;

	/* must have valid account number */
	if (((account_id = Fvall(transf, C_ACCOUNT_ID, 0)) < MIN_CR_ACCT) || 
	    (account_id > MAX_CR_ACCT)) {
		(void)Fchg(transf, STATLIN, 0, "Invalid account number", (FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }

	/* Retrieve AMOUNT to be deleted */
	EXEC SQL declare ccur cursor for
		select C_BAMOUNT from CREDIT where C_ACCOUNT_ID = :account_id;
	EXEC SQL open ccur;
	EXEC SQL fetch ccur into :b_bal;
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
        (void)Fchg(reqfb,C_ACCOUNT_ID,0,(char *)&account_id, (FLDLEN)0);

	/* put amount into request buffer */
	(void)sprintf(amts2,"%.2f",b_bal);
	(void)Fchg(reqfb,C_BAMOUNT,0,amts2, (FLDLEN)0);

	(void)sprintf(amts,"%.2f",c_bal);
	(void)Fchg(reqfb,C_CAMOUNT,0,amts, (FLDLEN)0);

	/* increase the priority of this withdraw */
	if (tpsprio(PRIORITY, 0L) == -1)
		(void)userlog("Unable to increase priority of withdraw");


	/* Delete credit record */

	EXEC SQL delete from CREDIT where C_ACCOUNT_ID = :account_id;
	if (SQLCODE != SQL_OK) {		/* Failure to delete */
		(void)Fchg(transf, STATLIN, 0,"Cannot close account", (FLDLEN)0);
		tpfree((char *)reqfb);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	EXEC SQL COMMIT WORK;

	/* prepare buffer for successful return */
/*	(void)Fchg(transf, BAMOUNT, 0, Fvals(reqfb,C_BAMOUNT,0), (FLDLEN)0); */
	(void)sprintf(amts,"$%.2f",b_bal);
	(void)Fchg(transf, SBALANCE, 0, amts, (FLDLEN)0);
	(void)Fchg(transf, C_BAMOUNT, 0, (char *)&b_bal, (FLDLEN)0);
	(void)Fchg(transf, FORMNAM, 0, "HCCLOSE", (FLDLEN)0);
	(void)Fchg(transf, STATLIN, 0, " ", (FLDLEN)0);
	tpfree((char *)reqfb);
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}
