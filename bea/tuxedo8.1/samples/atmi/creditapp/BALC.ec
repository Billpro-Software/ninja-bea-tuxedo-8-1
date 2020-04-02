/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
#ident	"@(#) samples/atmi/creditapp/BALC.ec	$Revision: 1.6 $" 
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/BALC.ec	$Revision: 1.6 $";
#endif


#include <stdio.h>		/* UNIX */
#include <atmi.h>		/* TUXEDO */
#include <sqlcode.h>		/* TUXEDO */
#include "bank.flds.h"		/* bankdb fields */
#include "aud.h"		/* BANKING view defines */

EXEC SQL begin declare section;
static long branch_id;		/* branch id */
static float bal;		/* balance */
EXEC SQL end declare section;



/*
 * Service to find the sum of the account balances at a specific branch
 */

void 
#if defined(__STDC__) || defined(__cplusplus)
ABALC_BID(TPSVCINFO *transb)

#else

ABALC_BID(transb)
TPSVCINFO *transb;
#endif

{
	struct aud *transv;	/* view of decoded message */

	/* Set pointer to TPSVCINFO data buffer  */

	transv = (struct aud *)transb->data;

	/* Get branch id from message, do query */

	branch_id = transv->b_id;
	EXEC SQL declare abcur cursor for
		select SUM(BALANCE) from ACCOUNT where BRANCH_ID = :branch_id;
	EXEC SQL open abcur;
	EXEC SQL fetch abcur into :bal;		/* fetch */
	if (SQLCODE != SQL_OK) {		/* nothing found */
		(void)sprintf (transv->ermsg, 
		               "abal_bid failed, branch %ld not found.", branch_id);
		EXEC SQL close abcur;
		tpreturn(TPSUCCESS, 1, transb->data, sizeof(struct aud), 0);
	}
	EXEC SQL close abcur;
	transv->balance = bal;
	tpreturn (TPSUCCESS, 0, transb->data, sizeof(struct aud), 0);
}

/*
 * Service to find the sum of the teller balances at a specific branch
 */

void 
#if defined(__STDC__) || defined(__cplusplus)
TBALC_BID(TPSVCINFO *transb)

#else

TBALC_BID(transb)
TPSVCINFO *transb;

#endif

{
	struct aud *transv;	/* view of decoded message */


	/* Set pointer to TPSVCINFO data buffer  */
	transv = (struct aud *)transb->data;

	/* Get branch id from message, do query */

	branch_id = transv->b_id;
	EXEC SQL declare tbcur cursor for
		select BALANCE from BRANCH where BRANCH_ID = :branch_id;
	EXEC SQL open tbcur;
	EXEC SQL fetch tbcur into :bal;		/* fetch */
	if (SQLCODE != SQL_OK) {		/* nothing found */
		(void)sprintf(transv->ermsg, 
			      "tbal_bid failed, branch %ld not found", branch_id);
		EXEC SQL close tbcur;
		tpreturn(TPSUCCESS, 1, transb->data, sizeof(struct aud), 0);
	}
	EXEC SQL close tbcur;
	transv->balance = bal;
	tpreturn (TPSUCCESS, 0, transb->data, sizeof(struct aud), 0);
}
