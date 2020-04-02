/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1990, 1994 Novell, Inc.	*/
/*	Copyright (c) 1994 Novell	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/


/*	Copyright (c) 1994 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ident	"@(#) samples/atmi/creditapp/bank.h	$Revision: 1.5 $"
#ifndef NOWHAT
static	char	h_bank[] = "@(#) samples/atmi/creditapp/bank.h	$Revision: 1.5 $";
#endif


#ifndef BANK_H
#define	BANK_H

/*  The following keywords give mnemonics to various banking functions  */

#define DAPB 		10	/* accounts per branch default*/
#define DTPB 		3	/* tellers per branch default */
#define STATLEN 	80	/* length of string for status line */
#define NAMELEN		16	/* length of service names */
#define PRIORITY	40	/* message priority increase value */
#define MAXBRANCH 	10	/* number of bank branches */
#define MINACCT		10000L 	/* smallest account number */
#define MAXACCT		120000L	/* largest account number  */
#define MIN_CR_ACCT	10000000L /* smallest credit account number */
#define MAX_CR_ACCT	120000000L	/* largest  credit account number  */
#define BALSTR		12	/* length of amount strings*/

/* 
 * Branch representatives for each machine.  The system administrator
 * must set this array so that one branch id from each machine, appears.
 * This enables clients to send requests to all machines by branch id. 
 */

#define SITEREP		{ 1, 5, 8 }

/* 
 * Number of machines in system.  The system administrator must set this
 * to the number of machines in the configuration. 
 */

#define NSITE		3

#undef _
#if defined(__STDC__) || defined(__cplusplus)
#define _(a) a
#else
#define _(a) ()
#endif

char	*getstr _((char *, long));
/* Unix functions not in header files */
extern	long nrand48 _((unsigned short []));
extern	unsigned short *seed48 _((unsigned short []));
extern	void srand _((unsigned));
extern	int rand _((void));

#endif
