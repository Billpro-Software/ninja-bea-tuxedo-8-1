
/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/* #ident	"@(#) samples/atmi/bankapp/BALC.ec	$Revision: 1.5 $" */
#ifndef NOWHAT
static  char	sccsid[] = "@(#) samples/atmi/bankapp/BALC.ec	$Revision: 1.5 $";
#endif


#include <stdio.h>		/* UNIX */
#include <atmi.h>		/* TUXEDO */
#include <sqlcode.h>		/* TUXEDO */
#include "bankflds.h"		/* bankdb fields */
#include "aud.h"		/* BANKING view defines */

EXEC SQL begin declare section;
static long branch_id;		/* branch id */
static float bal;		/* balance */
EXEC SQL end declare section;

static float total_balance;
 
#ifdef TRUE
#undef TRUE
#endif
#define TRUE    1
 
#ifdef FALSE
#undef FALSE
#endif
#define FALSE   0



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
	int first_time=TRUE;

	/* Set pointer to TPSVCINFO data buffer  */

	transv = (struct aud *)transb->data;

	/* Get branch id from message, do query */

	branch_id = transv->b_id;

	/* 
	* Cursor points to all rows for this branch.
	*/
	EXEC SQL declare abcur cursor for
		select BALANCE 
		from ACCOUNT
		where BRANCH_ID = :branch_id;

	/*
	* Open the cursor, which will have it point to 
	* the first row of data that meets the above
	* criteria.
	*/
	EXEC SQL open abcur;

	/*
	* Loop through each of the rows, tallying
	* a total balance for this branch. Quit when
	* there are no rows left to process.
	*/
	total_balance = 0.0;

	for (;;) {
		EXEC SQL fetch abcur
		into :bal;

		if (SQLCODE == SQLNOTFOUND) break;
		
		/*
		* first_time is used to determine whether or
		* not some data existed for this query and the
		* balance was 0, or no data existed at all for
		* this branch.
		*/
		first_time = FALSE;

		total_balance = total_balance + bal;

	}
	
	EXEC SQL close abcur;

	/*
	* If the balance is 0 and first_time is true, no data 
	* existed for the branch given.
	*/
	if ( (total_balance == 0) && ( first_time ) ) {
		(void)sprintf (transv->ermsg, 
		               "abal_bid failed, branch %ld not found.", branch_id);
		EXEC SQL close abcur;
		tpreturn(TPSUCCESS, 1, transb->data, sizeof(struct aud), 0);
	}

	/* 
	* Set the balance for return to the client.
	*/
	transv->balance = total_balance;
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
