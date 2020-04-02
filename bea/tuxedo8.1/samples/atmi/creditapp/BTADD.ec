/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1994 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ident	"@(#) samples/atmi/creditapp/BTADD.ec	$Revision: 1.5 $" 
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/BTADD.ec	$Revision: 1.5 $";
#endif


#include <stdio.h>		/* UNIX */
#include <fml.h>		/* TUXEDO */
#include <atmi.h>		/* TUXEDO */
#include <Usysflds.h>		/* TUXEDO */
#include <sqlcode.h>		/* TUXEDO */
#include "bank.h"		/* BANKING #defines */
#include "bank.flds.h"		/* bankdb fields */


EXEC SQL begin declare section;
static long branch_id;			/* branch id */
static float bal, branch_bal;		/* balance, branch balance */
static char first_name[20];		/* first name */
static char last_name[20];		/* last name */
static char mid_init;			/* middle initial */
static char address[60];		/* address */
static char phone[14];			/* telephone */
static long last_cr_acct;			/* last account branch gave */
static long last_acct;			/* last account branch gave */
static long last_teller;		/* last teller branch hired */
EXEC SQL end declare section;

static char amts[BALSTR];		/* stores float in string form */

/*
 * Service to add a new branch to a SITE
 */

void
#if defined(__STDC__) || defined(__cplusplus)
BR_ADD(TPSVCINFO *transb)

#else

BR_ADD(transb)
TPSVCINFO *transb;
#endif

{
	char receipt[STATLEN];
	FBFR *transf;	/* fielded buffer of decoded message */

	/* set pointer to TPSVCINFO data buffer */
	transf = (FBFR *)transb->data;	


	/* Get all values for service request from fielded buffer */

	bal = 0.0;	/* all branches start with no money */
	branch_id = (long)Fvall(transf, BRANCH_ID, 0);
	address[0] = '\0';
	(void)Fget(transf, ADDRESS, 0, address, 0);
	phone[0] = '\0';
	(void)Fget(transf, PHONE, 0, phone, 0);
	last_acct = (long)Fvall(transf, LAST_ACCT, 0);
	last_cr_acct = (long)Fvall(transf, LAST_CR_ACCT, 0);
	last_teller = (long)Fvall(transf, LAST_TELLER, 0);

userlog("ENTERED ADD BRANCH SERVICE FOR BRANCH %d",branch_id);

	/* Insert branch record */

	EXEC SQL insert into BRANCH 
		(BRANCH_ID, BALANCE, LAST_ACCT, LAST_TELLER, ADDRESS, PHONE,LAST_CR_ACCT) 
		values
		(:branch_id, :bal, :last_acct, :last_teller, :address, :phone,:last_cr_acct);
	if (SQLCODE != SQL_OK) {		/* failure to insert */
		(void)sprintf (receipt,
		               "br_add at branch %ld failed, BRANCH insert", branch_id);
		(void)Fchg(transf, STATLIN, 0, receipt, (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

userlog(" ADD BRANCH SERVICE FOR BRANCH %d COMPLETED",branch_id);

	/* prepare buffer for successful return */
	(void)sprintf(amts,"$%.2f",bal);
	(void)Fchg(transf, SBALANCE, 0, amts,(FLDLEN)0);
	(void)sprintf(receipt, "Branch %ld added", branch_id);
	(void)Fchg(transf, STATLIN, 0, receipt, (FLDLEN)0);
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}

/*
 * Service to add a new teller to a SITE
 */
 
void
#if defined(__STDC__) || defined(__cplusplus)
TLR_ADD(TPSVCINFO *transb)

#else

TLR_ADD(transb)
TPSVCINFO *transb;
#endif

{
	char receipt[STATLEN];
	FBFR *transf;	/* fielded buffer of decoded message */

	/* Set pointer to TPSVCINFO data buffer */
	transf = (FBFR *)transb->data;
	
	/* Get all values for service request from fielded buffer */

	if (Fget(transf, SBALANCE, 0, amts, 0) < 0 || strcmp(amts,"") == 0) {
		(void)Fchg(transf, STATLIN, 0, "Invalid teller balance",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)sscanf(amts,"%f",&bal);

	branch_id = (long)Fvall(transf, BRANCH_ID, 0);
	last_name[0] = '\0';
	(void)Fget(transf, LAST_NAME, 0, last_name, 0);
	first_name[0] = '\0';
	(void)Fget(transf, FIRST_NAME, 0, first_name, 0);
	mid_init = '\0';
	(void)Fget(transf, MID_INIT, 0, &mid_init, 0);

	/* Get teller id by reading branch's LAST_ACCT */

userlog("ENTERED ADD TELLER SERVICE FOR BRANCH %d",branch_id);

	EXEC SQL declare tcur cursor for
		select BALANCE, LAST_TELLER from BRANCH where
		BRANCH_ID = :branch_id;
	EXEC SQL open tcur;
	EXEC SQL fetch tcur into :branch_bal, :last_teller;	/* fetch */
	if (SQLCODE != SQL_OK) {				/* nothing found */
		(void)sprintf (receipt, 
			       "tlr_add failed, branch %ld not found", branch_id);
		(void)Fchg(transf, STATLIN, 0, receipt, (FLDLEN)0);
		EXEC SQL close tcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* Insert teller record */

	last_teller++;
	EXEC SQL insert into TELLER 
		(TELLER_ID, BRANCH_ID, BALANCE, LAST_NAME, FIRST_NAME, MID_INIT) 
		values
		(:last_teller, :branch_id, :bal, :last_name, :first_name, :mid_init);
	if (SQLCODE != SQL_OK) {			/* Failure to insert */
		(void)sprintf (receipt,
		               "tlr_add at branch %ld failed, TELLER insert",branch_id);
		(void)Fchg(transf, STATLIN, 0, receipt, (FLDLEN)0);
		EXEC SQL close tcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* Update branch record with new LAST_TELLER */

	branch_bal += bal;				/* new branch balance */
	EXEC SQL update BRANCH set LAST_TELLER = :last_teller, BALANCE = :branch_bal
		where current of tcur;
	if (SQLCODE != SQL_OK) {
		(void)sprintf(receipt,
		              "tlr_add at branch %ld failed, BRANCH update", branch_id);
		(void)Fchg(transf, STATLIN, 0, receipt, (FLDLEN)0);
		EXEC SQL close tcur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	EXEC SQL close tcur;

userlog(" ADD TELLER SERVICE FOR BRANCH %d COMPLETED",branch_id);

	/* prepare buffer for successful return */
	(void)sprintf(amts,"$%.2f",bal);
	(void)Fchg(transf, SBALANCE, 0, amts,(FLDLEN)0);
	(void)sprintf(receipt, "Teller %ld added at branch %ld", last_teller, branch_id);
	(void)Fchg(transf, STATLIN, 0, receipt, (FLDLEN)0);
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}
