/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*
 *      Copyright (c) 1998 BEA Systems, Inc.
 *      All rights reserved
 */
/* #ident       "@(#)samples/billingapp/teller.ec $Revision: 1.6 $" */

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/billingapp/teller.ec	$Revision: 1.6 $";
#endif


#include <stdio.h>                      /* UNIX headers */
#undef MAXFLOAT
#include <math.h>                       

#include <Uunix.h>                      /* TUXEDO headers */
#include <fml32.h>                      
#include <Usysfl32.h>           
#include <atmi.h>       
#include <sqlcode.h>
#include <userlog.h>                    

#include "tellw_flds.h"                /* teller app fields */
#include "tellw_u.h"                    /* teller app header */

EXEC SQL begin declare section;         /* sql declares must be global */
static long account_no;                 /* account number        */
static double amt;                      /* amount of transaction */
static double curr_balance;             /* balance avl in account */
EXEC SQL end declare section;


int
#if defined(__STDC__) || defined(__cplusplus)
tpsvrinit(int argc, char **argv)
#else
tpsvrinit(argc,argv)
int argc;
char **argv;
#endif
{
	/* open database */
	if (tpopen() == -1) {
		(void)userlog("tpsvrinit: failed to open database due to ");
		switch (tperrno) {
		case TPEOS:
			(void)userlog("tpopen failed, Unix error %d\n",
				Uunixerr);
			break;
		case TPERELEASE:
			(void)userlog("tpopen failed, Incompatible release\n");
			break;
		default:
			(void)userlog("tpopen failed, tperrno: %d\n",
				tperrno);
		}
		return(-1);
	}

	userlog("Welcome to Teller Server...\n");
	return(0);
}

void
tpsvrdone()
{
	/* close database */
	if (tpclose() == -1) {
		(void)userlog("tpsrvdone: failed to close database due to ");
		switch (tperrno) {
		case TPEOS:
			(void)userlog("tpclose failed, Unix error %d\n", 
				Uunixerr);
			break;
		case TPERELEASE:
			(void)userlog("tpclose failed, Incompatible release\n");
			break;
		default:
			(void)userlog("tpclose failed, tperrno:  %d\n",
				tperrno);
		}
	}

	userlog("Teller Server is shutting down...\n");
}

/*
 * Service to DECREASE current balance in an account
 */
#if defined(__STDC__) || defined(__cplusplus)
CREDIT(TPSVCINFO *transb)

#else
CREDIT(transb)
TPSVCINFO *transb;
#endif

{
	FBFR32  *transf;
	
	/* set pointer to TPSVCINFO data buffer */
	transf = (FBFR32 *)transb->data;

	/* get account number */
	if (((account_no = Fvall32(transf, ACCOUNT_NO, 0)) < MINACCT) || 
		(account_no > MAXACCT)) {
		(void)Fchg32(transf,STATUSLINE,0,"Invalid account number",
			(FLDLEN32)0);
		tpreturn(TPFAIL,0,transb->data,0L,0);
	}
      (void)userlog("CREDIT: account number = %ld\n", account_no);

	/* get & validate amount to be credited */
	if (Fget32(transf, AMOUNT, 0, (char *)&amt, 0) < 0) {
		(void)Fchg32(transf,STATUSLINE,0,"Invalid credit amount",
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)userlog("CREDIT: amount = %f\n", amt);

	if (amt <= 0.0) {
		(void)Fchg32(transf,STATUSLINE,0,"Credit amount must be greater than $0.00",(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* set cursor dacur on account record */
	EXEC SQL declare dacur cursor for
		select CURR_BALANCE from ACCOUNT
			where ACCOUNT_NO = :account_no
			FOR UPDATE OF CURR_BALANCE;
	EXEC SQL open dacur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg32(transf,STATUSLINE,0,getstr("account",SQLCODE),
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch dacur into :curr_balance;
	if (SQLCODE != SQL_OK) {
		(void)Fchg32(transf,STATUSLINE,0,getstr("account",SQLCODE),
			(FLDLEN32)0);
		EXEC SQL close dacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)userlog("CREDIT: curr_balance = %f\n", curr_balance);

	/* Update account record with new CURR_BALANCE */
	curr_balance -= amt;
	EXEC SQL update ACCOUNT set CURR_BALANCE = :curr_balance where current of dacur;
	if (SQLCODE != SQL_OK) {        /* Failure to update */
		(void)Fchg32(transf,STATUSLINE,0,"Cannot update ACCOUNT",
			(FLDLEN32)0);
		EXEC SQL close dacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	EXEC SQL close dacur;

	/* prepare buffer for successful return */
	(void)Fchg32(transf, STATUSLINE, 0, "",(FLDLEN32)0);
	(void)Fchg32(transf,CURR_BALANCE,0, (char *)&curr_balance,
		(FLDLEN32)0);

	/* return success */
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}

/*
 * Service to INCREASE current balance in an account
 */
#if defined(__STDC__) || defined(__cplusplus)
DEBIT(TPSVCINFO *transb)

#else
DEBIT(transb)
TPSVCINFO *transb;
#endif

{
	FBFR32  *transf;

	/* Set pointer to  TPSVCINFO data buffer */
	transf = (FBFR32 *)transb->data;

	/* get account number */
	if (((account_no = Fvall32(transf,ACCOUNT_NO,0)) < MINACCT) || 
		(account_no > MAXACCT)) {
		(void)Fchg32(transf,STATUSLINE,0,"Invalid account number",
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)userlog("DEBIT: account number = %ld\n", account_no);

	/* get & validate amount to be debited */
	if (Fget32(transf, AMOUNT, 0, (char *)&amt, 0) < 0) {
		(void)Fchg32(transf,STATUSLINE,0,"Invalid debit amount",
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)userlog("DEBIT: amount = %f\n", amt);

	if (amt <= 0.0) {
		(void)Fchg32(transf,STATUSLINE,0,
			"Debit amount must be greater than $0.00",
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* set cursor wacur on account record */
	EXEC SQL declare wacur cursor for
		select CURR_BALANCE from ACCOUNT
			where ACCOUNT_NO = :account_no
			FOR UPDATE OF CURR_BALANCE;
	EXEC SQL open wacur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg32(transf,STATUSLINE,0,getstr("account",SQLCODE),
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch wacur into :curr_balance;
	if (SQLCODE != SQL_OK) {                /* nothing found */
		(void)Fchg32(transf,STATUSLINE,0,getstr("account",SQLCODE),
			(FLDLEN32)0);
		EXEC SQL close wacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* Update account record with new CURR_BALANCE */
	curr_balance += amt;
	EXEC SQL update ACCOUNT set CURR_BALANCE = :curr_balance where current of wacur;
	if (SQLCODE != SQL_OK) {                /* Failure to update */
		(void)Fchg32(transf, STATUSLINE, 0, "Cannot update ACCOUNT", (FLDLEN32)0);
		EXEC SQL close wacur;
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL close wacur;

	/* prepare buffer for successful return */
	(void)Fchg32(transf, CURR_BALANCE, 0, (char *)&curr_balance, 
		(FLDLEN32)0);
	(void)Fchg32(transf, STATUSLINE, 0, " ", (FLDLEN32)0);

	/* return success */
	tpreturn(TPSUCCESS, 0,transb->data , 0L, 0);
}

/*
 * Service to check current balance in an account
 */
#if defined(__STDC__) || defined(__cplusplus)
CURRBALANCE(TPSVCINFO *transb)

#else
CURRBALANCE(transb)
TPSVCINFO *transb;
#endif

{
	FBFR32  *transf;        /* fielded buffer of decoded message */

	/*  Set pointer to TPSVCINFO data buffer */
	transf = (FBFR32 *)transb->data;

	/* get valid account number */
	if (((account_no = Fvall32(transf,ACCOUNT_NO,0)) < MINACCT) || 
		(account_no > MAXACCT)) {
		(void)Fchg32(transf,STATLIN,0,"Invalid account number", 
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)userlog("CURRBALANCE: account number = %ld\n", account_no);

	/* Become current on account record */
	EXEC SQL declare icur cursor for
		select CURR_BALANCE from ACCOUNT where ACCOUNT_NO = :account_no;
	
	EXEC SQL open icur;
	if (SQLCODE != SQL_OK) {
		(void)Fchg32(transf,STATLIN,0,getstr("account",SQLCODE),
			(FLDLEN32)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	EXEC SQL fetch icur into :curr_balance;
	if (SQLCODE != SQL_OK) {                /* nothing found */
		(void)Fchg32(transf,STATLIN,0,getstr("account",SQLCODE), 
			(FLDLEN32)0);
		EXEC SQL close icur;
		tpreturn(TPFAIL, 0, transb->data , 0L, 0);
	}
	EXEC SQL close icur;


	/* prepare buffer for successful return */
      (void)userlog("CURRBALANCE: curr_balance = %f\n", curr_balance);
	(void)Fchg32(transf, CURR_BALANCE, 0, (char *)&curr_balance, 
		(FLDLEN32)0);
	(void)Fchg32(transf, STATUSLINE, 0, " ", (FLDLEN32)0);
	
	tpreturn(TPSUCCESS, 0, transb->data, 0L, 0);
}

