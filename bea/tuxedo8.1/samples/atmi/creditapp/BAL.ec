/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1994 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ident	"@(#) samples/atmi/creditapp/BAL.ec	$Revision: 1.5 $" 
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/BAL.ec	$Revision: 1.5 $";
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
 * Service to find sum of the account balances at a SITE
 */

void
#if defined(__STDC__) || defined(__cplusplus)
ABAL(TPSVCINFO *transb)

#else

ABAL(transb)
TPSVCINFO *transb;
#endif

{
	struct aud *transv;			/* view of decoded message */

	/* Set pointer to TPSVCINFO data buffer  */

	transv = (struct aud *)transb->data;

	/* Get branch id from message, do query */

	EXEC SQL declare acur cursor for
		select SUM(BALANCE) from ACCOUNT;
	EXEC SQL open acur;			/* open */
	EXEC SQL fetch acur into :bal;		/* fetch */
	if (SQLCODE != SQL_OK) {		/* nothing found */
		(void)strcpy (transv->ermsg,"abal failed in sql aggregation");
		EXEC SQL close acur;
		tpreturn(TPFAIL, 0, transb->data, sizeof(struct aud), 0);
	}
	EXEC SQL close acur;
	transv->balance = bal;
	tpreturn (TPSUCCESS, 0, transb->data, sizeof(struct aud), 0);
}

/*
 * Service to find sum of the teller balances at a SITE
 */

void
#if defined(__STDC__) || defined(__cplusplus)
TBAL(TPSVCINFO *transb)

#else

TBAL(transb)
TPSVCINFO *transb;
#endif

{
	struct aud *transv;	/* view of decoded message */

	/* Set pointer to TPSVCINFO data buffer  */

	transv = (struct aud *)transb->data;

	/* Get branch id from message, do query */

	EXEC SQL declare tcur cursor for
		select SUM(BALANCE) from BRANCH;
	EXEC SQL open tcur;			/* open */
	EXEC SQL fetch tcur into :bal;		/* fetch */
	if (SQLCODE != SQL_OK) {		/* nothing found */
		(void)strcpy (transv->ermsg, "tbal failed in sql aggregation");
		EXEC SQL close tcur;
		tpreturn(TPFAIL, 0, transb->data, sizeof(struct aud), 0);
	}
	EXEC SQL close tcur;
	transv->balance = bal;
	tpreturn (TPSUCCESS, 0, transb->data, sizeof(struct aud), 0);
}


/*
 * Service to find the sum of the account balances at a specific branch
 */

void 
#if defined(__STDC__) || defined(__cplusplus)
ABAL_BID(TPSVCINFO *transb)

#else

ABAL_BID(transb)
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
		tpreturn(TPFAIL, 0, transb->data, sizeof(struct aud), 0);
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
TBAL_BID(TPSVCINFO *transb)

#else

TBAL_BID(transb)
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
		tpreturn(TPFAIL, 0, transb->data, sizeof(struct aud), 0);
	}
	EXEC SQL close tbcur;
	transv->balance = bal;
	tpreturn (TPSUCCESS, 0, transb->data, sizeof(struct aud), 0);
}
