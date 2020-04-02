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
#ident	"@(#) samples/atmi/creditapp/gentran.c	$Revision: 1.5 $"
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/gentran.c	$Revision: 1.5 $";
#endif

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX	*/
#include <Uunix.h>		/* TUXEDO */
#undef MAXFLOAT
#include <math.h>		/* UNIX	*/
#include "bank.h"		/* BANKING #defines */

#define NB 10		/* number of branches */
#define NTT 4		/* number of transaction types */


static char *sn[] = { "INQUIRY", "DEPOSIT", "WITHDRAWAL", "TRANSFER" };

static int weight[] = {7, 29, 52, 12};	/* weights of transaction types */


/*
 * gentran is a program which generates transactions. Output from this
 * program should be piped to ud. See driver.
 */

#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char *argv[])

#else

main(argc, argv)
int argc;
char *argv[];
#endif

{
	int apb=DAPB;		/* account holders per branch */
	long loops=300L;	/* number of transactions */
	long i;			/* loop variable */
	int c;			/* Option character */
	long branch_id;		/* Branch id */
	long account_id;	/* Account id */
	long amount;		/* Amount of transaction */
	long tran_type;		/* Transaction type */
	char w_trantype;	/* weight variable character */
	int wsum;		/* sum of all weights */
	int wp;			/* loop through weights */
	int t_num;		/* raw random number for choosing trans. type */
	int tht;		/* threshhold total for choosing trans. type */

	while((c = getopt(argc,argv,"a:n:w:")) != EOF) {
		switch((char)c) {
		case 'a':
			apb=atoi(optarg);
			if (apb < 1L) {
				(void)fprintf(stderr,
					      "%s:  must have > 0 accounts per branch\n",
					      argv[0]);
				exit(2);
			}
			break;
		case 'n':
			loops=atol(optarg);
			if (loops < 1L) {
				(void)fprintf(stderr,
					      "%s:  must have > 0 transactions\n",
					      argv[0]);
				exit(2);
			}
			break;
		case 'w':
			w_trantype=optarg[0];
			switch (w_trantype) {
			case 'i':
				weight[0] = atoi(optarg+1);
				break;
			case 'd':
				weight[1] = atoi(optarg+1);
				break;
			case 'w':
				weight[2] = atoi(optarg+1);
				break;
			case 'x':
				weight[3] = atoi(optarg+1);
				break;
			default:
				(void)fprintf(stderr,
					      "%s:  -w requires one of idwx\n",
					      argv[0]);
				exit(2);
			}
			for (wp = 0; wp < NTT; wp++)
				if (weight[wp] <= 0) {
					(void)fprintf(stderr,
					              "%s:  zero weight value\n", 
						      argv[0]);
					exit(2);
				}
			break;
		default:
			(void)fprintf(stderr,
				      "%s:  usage %s [-a apb] [-n loops] [-wtv]...\n",
				      argv[0], argv[0]);
			exit(2);
		}
	}
	
	srand ((unsigned int)45191);	/* seed random generator */

	/* Major loop through branch records */

	for (i = 1; i <= loops; i++) {

		/*
		 * Choose branch id (1 to 10), account id for transaction,
		 * base amount (random no. is from 6-200 so eventual amount
		 * may never wind up zero due to dividing by 2 and/or 3).
		 */
		
		branch_id = (rand() % NB) + 1;
		account_id = 10000L * branch_id + (rand() % (apb * 2));
		amount = (rand() % 195) + 6;

		/* Scale down by 2/3 if checking rather than savings */

		if (account_id % 2 == 0)
			amount /= 3L;

		/*
		 * Random operation based on transaction type probability
		 * weights in weight[]
		 */

		wsum=0;
		for (wp = 0; wp < NTT; wp++)
			wsum += weight[wp];
		t_num = (int)(rand() % wsum);
		tht=0;
		for (wp = 0; wp < NTT && tht <= t_num; wp++)
			tht += weight[wp];
		tran_type = wp - 1;

		/* Scale amount by half if a withdrawal */

		if (strcmp(sn[tran_type], "WITHDRAWAL") == 0)
			amount /= 2L;

		/* Output variables to ud-format service request */

		(void)printf("n\n");
		(void)printf("SRVCNM\t%s\n", sn[tran_type]);
		(void)printf("ACCOUNT_ID\t%ld\n", account_id);
		if (strcmp(sn[tran_type], "TRANSFER") == 0) /* other account id */
			(void)printf("ACCOUNT_ID\t%ld\n", account_id ^ 1L);
		if (strcmp(sn[tran_type], "INQUIRY") != 0)
			(void)printf("SAMOUNT\t%ld.00\n", amount);
		(void)printf("\n");
	}
	return 1;
}
