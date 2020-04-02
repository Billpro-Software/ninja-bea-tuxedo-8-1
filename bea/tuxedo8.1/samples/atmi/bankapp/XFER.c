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
/* #ident	"@(#) samples/atmi/bankapp/XFER.c	$Revision: 1.5 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/XFER.c	$Revision: 1.5 $";
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
#include <userlog.h>		/* TUXEDO */
#include "bank.h"		/* BANKING #defines */
#include "bankflds.h"		/* bankdb fields */

/*
 * Service to transfer an amount from a debit account to a credit account
 */

void
#if defined(__STDC__) || defined(__cplusplus)
TRANSFER(TPSVCINFO *transb)

#else

TRANSFER(transb)
TPSVCINFO *transb;
#endif

{
	FBFR *transf;		/* fielded buffer of decoded message  */
	long db_id, cr_id;	/* from/to account id's 	      */
	float db_bal, cr_bal;	/* from/to account balances           */
	float tamt;		/* amount of the transfer             */
	FBFR *reqfb;		/* fielded buffer for request message */
	int reqlen;		/* length of fielded buffer           */
	char t_amts[BALSTR];	/* string for transfer amount         */
	char db_amts[BALSTR];	/* string for debit account balance   */
	char cr_amts[BALSTR];	/* string for credit account balance  */
	char *s;		/* pointer for statline transfer      */

	/* Set pointr to TPSVCINFO data buffer  */
	transf = (FBFR *)transb->data;

	/* Get debit (db_id) and credit (cr_id) account IDs */

	/* must have valid debit account number */
	if (((db_id = Fvall(transf, ACCOUNT_ID, 0)) < MINACCT) || (db_id > MAXACCT)) {
		(void)Fchg(transf, STATLIN, 0,"Invalid debit account number",(FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }
	/* must have valid credit account number */
	if ((cr_id = Fvall(transf, ACCOUNT_ID, 1)) < MINACCT || cr_id > MAXACCT) {
		(void)Fchg(transf,STATLIN, 0,"Invalid credit account number",(FLDLEN)0);
                tpreturn(TPFAIL, 0, transb->data, 0L, 0);
        }

	/* get amount to be withdrawn */
	if (Fget(transf, SAMOUNT, 0, t_amts, 0) < 0 || strcmp(t_amts,"") == 0) {
		(void)Fchg(transf, STATLIN, 0, "Invalid amount",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	(void)sscanf(t_amts,"%f",&tamt);

	/* must have valid amount to transfer */
	if (tamt <= 0.0) {
		(void)Fchg(transf, STATLIN, 0,
		           "Transfer amount must be greater than $0.00",(FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* make withdraw request buffer */
	if ((reqfb = (FBFR *)tpalloc(FMLTYPE,NULL,transb->len)) == (FBFR *)NULL) {
		(void)userlog("tpalloc failed in transfer\n");
		(void)Fchg(transf, STATLIN, 0,
			   "unable to allocate request buffer", (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}
	reqlen = (int)Fsizeof(reqfb);
	(void)Finit(reqfb,(FLDLEN)reqlen);

	/* put ID in request buffer */
	(void)Fchg(reqfb,ACCOUNT_ID,0,(char *)&db_id, (FLDLEN)0);

	/* put amount in request buffer */
	(void)Fchg(reqfb,SAMOUNT,0,t_amts, (FLDLEN)0);

	/* increase the priority of withdraw call */
	if (tpsprio(PRIORITY, 0L) == -1)
		(void)userlog("Unable to increase priority of withdraw\n");

	if (tpcall("WITHDRAWAL", (char *)reqfb,0, (char **)&reqfb, 
		   (long *)&reqlen,TPSIGRSTRT) == -1) {
		if(tperrno == TPESVCFAIL && reqfb != NULL &&
		   (s=Ffind(reqfb, STATLIN, 0, 0)) != NULL && *s)
			(void)Fchg(transf, STATLIN, 0, s, (FLDLEN)0);
		else
			(void)Fchg(transf, STATLIN, 0, 
			   "Cannot withdraw from debit account", (FLDLEN)0);
		tpfree((char *)reqfb);
		tpreturn(TPFAIL, 0,transb->data, 0L, 0);
	}

	/* get "debit" balance from return buffer */

	(void)strcpy(db_amts, Fvals((FBFR *)reqfb,SBALANCE,0));
	(void)sscanf(db_amts,"$%f",&db_bal);
	if ((db_amts == NULL) || (db_bal < 0.0)) {
		(void)Fchg(transf, STATLIN, 0, 
			   "illegal debit account balance", (FLDLEN)0);
		tpfree((char *)reqfb);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* make deposit request buffer */
	(void)Finit(reqfb,(FLDLEN)Fsizeof(reqfb));

	/* put deposit account ID in request buffer */
	(void)Fchg(reqfb,ACCOUNT_ID,0,(char *)&cr_id, (FLDLEN)0);

	/* put transfer amount in request buffer */
	(void)Fchg(reqfb,SAMOUNT,0,t_amts, (FLDLEN)0);

	/* Up the priority of deposit call */
	if (tpsprio(PRIORITY, 0L) == -1)
		(void)userlog("Unable to increase priority of deposit\n");

	/* Do a tpcall to deposit to second account */
	if (tpcall("DEPOSIT", (char *)reqfb, 0, (char **)&reqfb, 
		   (long *)&reqlen, TPSIGRSTRT) == -1) {
		if(tperrno == TPESVCFAIL && reqfb != NULL &&
		   (s=Ffind(reqfb, STATLIN, 0, 0)) != NULL && *s)
			(void)Fchg(transf, STATLIN, 0, s, (FLDLEN)0);
		else
			(void)Fchg(transf, STATLIN, 0, 
			   "Cannot deposit into credit account", (FLDLEN)0);
		tpfree((char *)reqfb);
		tpreturn(TPFAIL, 0,transb->data, 0L, 0);
	}

	/* get "credit" balance from return buffer */

	(void)strcpy(cr_amts, Fvals((FBFR *)reqfb,SBALANCE,0));
	(void)sscanf(cr_amts,"$%f",&cr_bal);
	if ((cr_amts == NULL) || (cr_bal < 0.0)) {
		(void)Fchg(transf, STATLIN, 0, 
			   "Illegal credit account balance", (FLDLEN)0);
		tpreturn(TPFAIL, 0, transb->data, 0L, 0);
	}

	/* set buffer for successful return */
	(void)Fchg(transf, FORMNAM, 0, "CTRANSFER", (FLDLEN)0);
	(void)Fchg(transf, SAMOUNT, 0, Fvals(reqfb,SAMOUNT,0), (FLDLEN)0);
	(void)Fchg(transf, STATLIN, 0, "", (FLDLEN)0);
	(void)Fchg(transf, SBALANCE, 0, db_amts, (FLDLEN)0);
	(void)Fchg(transf, SBALANCE, 1, cr_amts, (FLDLEN)0);
	tpfree((char *)reqfb);
	tpreturn(TPSUCCESS, 0,transb->data, 0L, 0);
}
