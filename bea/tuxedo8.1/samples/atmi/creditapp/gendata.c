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
#ident	"@(#) samples/atmi/creditapp/gendata.c	$Revision: 1.5 $"
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/gendata.c	$Revision: 1.5 $";
#endif


#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX	*/
#include <Uunix.h>		/* TUXEDO */
#undef MAXFLOAT
#include <math.h>		/* UNIX	*/
#include "bank.h"		/* BANKING #defines */



static char *badr[] = {
	"25 Powell St.                San Francisco, CA  94188",
	"211 Broadway                 Los Angeles, CA  90052",
	"34 Washington Ave.           Dallas, TX  75260",
	"50 North LaSalle St.         Chicago, IL 60607",
	"53 Market St.                St. Louis, MO   63155",
	"500 King Blvd.               Atlanta, GA  30304",
	"100 Maitland Ave.            Miami, FL  33021",
	"500 J. F. Kennedy Blvd.      Philadelphia, PA  19104",
	"100 Wall St.                 New York, NY  10081",
	"50 Charles St.               Boston, MA  02205"
};

static char *bph[] = {
	"415-753-9000",
	"213-798-3000",
	"214-321-7000",
	"312-733-9000",
	"314-298-6000",
	"404-873-5000",
	"305-267-3000",
	"215-831-8000",
	"212-798-3000",
	"508-335-2000"
};

static char *ac[] = {
		"415", "408", "415",
		"213", "818", "213",
		"214", "817", "214",
		"312", "312", "312",
		"314", "417", "816",
		"404", "404", "912",
		"305", "305", "305",
		"215", "717", "717",
		"212", "212", "212",
		"508", "617", "617"
};

#define MSNO 30000	/* max street number */
#define NSNA 30		/* number of street names */
static char *stn[] = {
		"Willow", "Washington", "Lincoln", "Lafayette",
		"Springfield", "Park", "Main", "Mountain", "Elm", "Maple",
		"Oak", "Green", "John", "Roosevelt", "Grafton", "Woodley",
		"Elliot", "Jones", "Carson", "Berkeley", "Oakland",
		"Vista", "Grand", "Livingston", "Hartford", "Erie",
		"Blackstone", "Grove", "Fairlawn", "Greenfield"
};

#define NSW 6		/* number of street words */
static char *stw[] = {"Ave.", "Blvd.", "St.", "Rd.", "Pl.", "Ct."};

#define NCT 30		/* number of cities for account holders */
#define CPB 3		/* number of cities per branch */
static char *cst[] = {	
		"San Francisco, CA  94103",
		"San Jose, CA  95101",
		"Oakland, CA  94544",
		"Los Angeles, CA  94321",
		"Pasadena, CA  91109",
		"Santa Barbara, CA  93102",
		"Dallas, TX 70562",
		"Ft. Worth, TX 76101",
		"Arlington, TX 76010",
		"Chicago, IL 60431",
		"Downers Grove, IL 60515",
		"Wheaton, IL 60187",
		"St. Louis, MO   63155",
		"Springfield, MO   65801",
		"Kansas City, MO   64108",
		"Atlanta, GA  30304",
		"Athens, GA  30601",
		"Savannah, GA  30892",
		"Miami, FL  33152",
		"Ft. Lauderdale, FL  33310",
		"Orlando, FL  33802",
		"Philadelphia, PA  19321",
		"Scranton, PA  18505",
		"Wilkes-Barre, PA  18701",
		"New York, NY  10081",
		"Brooklyn, NY  10385",
		"Staten Island, NY  10532",
		"Boston, MA  02205",
		"Worcester, MA  01805",
		"Lowell, MA  01853"
};

#define NFN 100	/* number of first names to choose from */
static char *fn[] = {
		"Terrance", "Jane", "James", "Mary", "Joan", "Martha",
		"Darlene", "James", "Robert", "Barbara", "Marguerite",
		"Doug", "Amy", "John", "Diana", "Alan", "Leslie",
		"Betty", "John", "Douglas", "Nancy", "Terry", "Ardyce",
		"Jo", "Ronnie", "David", "Morgan", "Keith", "Ralph",
		"Vickie", "Robert", "Catherine", "Richard", "Gerard",
		"Gregory", "Douglas", "Steven", "Rosa", "Robert",
		"Richard", "Jeanne", "Larry", "Richard", "Dawn",
		"Joseph", "Jean", "Patricia", "Darwin", "Brian",
		"Janet", "Charles", "Susan", "Randall", "Joe", "David",
		"Dorothy", "David", "George", "Mondo", "Susan", "Keith",
		"Carolyn", "Craig", "Roger", "Belinda", "Gwendolyn",
		"Patricia", "Alice", "David", "Thomas", "Robert",
		"George", "Nettie", "Edward", "Anthony", "Kathleen",
		"Eileen", "Richard", "Elisa", "Lee", "Marvin", "David",
		"Elizabeth", "Lesley", "Steven", "Victor", "David",
		"Paul", "Beverly", "Thomas", "Clarence", "Edward",
		"Melvia", "Maxine", "Mary", "Allan", "Norman",
		"Kathleen", "Sharon", "Terrance"
};


#define NLN 100	/* number of last names to choose from */
static char *ln[] = {
		"Abbasi", "Allaire", "Andrus", "Avants", "Barabas",
		"Baumgartner", "Bennett", "Bitzer", "Bonfiglio",
		"Brady", "Brophy", "Buckley", "Butler", "Cappelluti",
		"Castanaras", "Chen", "Clark", "Collins", "Corley",
		"Crockett", "Dalida", "Dawson", "Deppong", "Dobosz",
		"Dryer", "Echols", "Ennis", "Farrell", "Fiore",
		"Forney", "Fries", "Gardner", "Gibbons", "Goldschmidt",
		"Grayson", "Grumhaus", "Hall", "Harrington", "Hayes",
		"Herman", "Hoang", "Horbock", "Hulse", "Jackson",
		"Jesensky", "Jones", "Kaminoff", "Kendall",
		"Kirkpatrick", "Koridek", "Kwas", "Lashevicki",
		"Leinbach", "Lines", "Louie", "Mackey", "Marak",
		"Masone", "Mcelhiney", "Melander", "Miller", "Molina",
		"Morrisino", "Murphy", "Nemjo", "Norwood", "Olson",
		"Palmer", "Pavon", "Peterson", "Pittman", "Pravidlo",
		"Radicsh", "Reed", "Richey", "Robinson", "Russell",
		"Rybak", "Sauer", "Schrivener", "Seppie", "Shiran",
		"Skelton", "Smith", "Spear", "Steinher", "Stremler",
		"Swinney", "Terrell", "Tippett", "Trivett", "Valdez",
		"Vincent", "Walraven", "Weaver", "Wheeler", "Williams",
		"Winchock", "Wright", "Yunits"
};


static char mi[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ          ";
#define NMI (sizeof(mi)-1)	/* number of middle initials to choose from */

#define NB 10		/* number of branches */

/*
 * gendata generates data for populating the datbases. Its output should
 * be piped to ud. See populate.
 */

#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char *argv[])
#else
main(argc, argv)
int argc;
char *argv[];
#endif
{
	int	apb=DAPB;		/* Accounts per branch default */
	int	tpb=DTPB;		/* Tellers per branch default */
	int	c;			/* Option character */
	long	a_ctr, t_ctr;		/* Account, teller counters */
	char	*np;			/* pointer to phone string */
	long	exc, numb;		/* exchange, number */
	long	branch_id;		/* Branch id */
	float	bal;			/* Balance */
	float	c_bal;			/* credit line */
	float	b_bal;			/* available bal*/
	char	acct_type;		/* Account type is 'C' or 'S' */
	char	last_name[21];		/* Last name */
	char	first_name[21];		/* First name */
	char	mid_init;		/* Middle initial */
	char	address[61];		/* Address */
	char	phone[14];		/* Phone */
	long	last_acct;		/* Last account opened at this branch */
	long	last_cr_acct;		/* Last  credit account opened at this branch */
	long	last_tell;		/* Last teller hired at this branch */
	int	cstp;			/* subscript to city/state array */
	unsigned int i = 1;
	char	*sp;			/* pointer to ssn string */
	long	first;			/* first 3 digits of the ssn */
	long	second;			/* second 2 digits of the ssn */
	long	third;			/* third 4 digits of the ssn  */
	char	ss_n[12];		/* Social security number */
	char	c_acct_type='\0';	/* Credit Card Account type: 'M', 'V' */
	char	opencr = 'N';		/* Open a Credit Card Account */

	while((c = getopt(argc,argv,"a:t:")) != EOF) {
		switch((char)c) {
		case ' ':
			apb=atoi(optarg);
			if (apb < 1) {
				(void)fprintf(stderr,
					      "%s:  must have > 0 accounts per branch\n",
					      argv[0]);
				exit(2);
			}
			break;
		case 't':
			tpb=atoi(optarg);
			if (apb < 1) {
				(void)fprintf(stderr,
				 	      "%s:  must have > 0 tellers per branch\n",
					      argv[0]);
				exit(2);
			}
			break;
		default:
			(void)fprintf(stderr,"%s:  usage %s [-a apb] [-t tpb]\n",
				      argv[0], argv[0]);
			exit(2);
		}
	}

	/* Major loop through branch records */

	for (branch_id = 1; branch_id <= MAXBRANCH ; branch_id++) {

		/* Account and teller bases, branch address and phone */

		last_acct = branch_id * 10000L - 1L;		/* last account */
		last_cr_acct = branch_id * 10000000L - 1L;		/* last  credit account */
		last_tell = branch_id * 100L - 1L;		/* last teller */
		(void)strcpy(address, badr[branch_id - 1L]);	/* branch address */
		(void)strcpy(phone,   bph [branch_id - 1L]);	/* branch phone */

		/* Output variables to ud-format service request */

		(void)printf("n\nSRVCNM\tBR_ADD\n");
		(void)printf("BRANCH_ID\t%ld\n", branch_id);
		(void)printf("LAST_ACCT\t%ld\n", last_acct);
		(void)printf("LAST_CR_ACCT\t%ld\n", last_cr_acct);
		(void)printf("LAST_TELLER\t%ld\n", last_tell);
		(void)printf("ADDRESS\t%s\n", address);
		(void)printf("PHONE\t%s\n", phone);
		(void)printf("\n");
	}
			
	/* Major loop for teller records */

	for (branch_id = 1; branch_id <= MAXBRANCH ; branch_id++) {

		/* Minor loop through teller records */
	
		for (t_ctr = 0; t_ctr < tpb; t_ctr++) {

			/* Teller balance, name */

			srand(i++); /*seed the random number generator*/
			bal = (float)(rand() % 30000L) + 70000.0;
			(void)strncpy(last_name, ln[rand() % NLN], 19);
			last_name[19]='\0';
			srand(i++);
			(void)strncpy(first_name, fn[rand() % NFN], 19);
			first_name[19]='\0';
			mid_init=mi[rand() % NMI];

			(void)printf("n\nSRVCNM\tTLR_ADD\n");
			(void)printf("BRANCH_ID\t%ld\n", branch_id);
			(void)printf("SBALANCE\t%.2f\n", bal);
			(void)printf("LAST_NAME\t%s\n", last_name);
			(void)printf("FIRST_NAME\t%s\n", first_name);
			(void)printf("MID_INIT\t%c\n", mid_init);
			(void)printf("\n");
		}
	}

	/* Major loop for account records */

	for (branch_id = 1; branch_id <= MAXBRANCH ; branch_id++) {

		c_acct_type  = '\0';
		opencr = 'N';
		/* Minor loop through account records */
	
		for (a_ctr = 0; a_ctr < apb; a_ctr++) {

			/* Choose balance, checking account, name */

			srand(i++);
			bal = (float)(rand() % 1800) + 200.0;
			acct_type = 'C';
			srand(i++);
			(void)strncpy(last_name, ln[rand() % NLN], 19);
			last_name[19]='\0';
			srand(i++);
			(void)strncpy(first_name, fn[rand() % NFN], 19);
			first_name[19]='\0';
			mid_init=mi[rand() % NMI];

/*gwc			if (branch_id % 2) {    */
				opencr = 'Y';
				if (branch_id % 3) 
					c_acct_type = 'M';
				else
					c_acct_type = 'V';
/*gwc			}          */

			/* Social Security number construction */
			srand(i++);
			first = rand() % 1000;

			srand(i++);
			second = rand() % 100;

			srand(i++);
			third = (long)rand() % 10000L;  /* last 4 digits */

			(void)sprintf(ss_n, "%3ld-%2ld-%4ld", first, second, third);

			for (sp = ss_n; *sp != '\0'; sp++) { /* spaces become 0s */
				if (*sp == ' ')
					*sp='0';
			}

			/* Address construction */

			(void)sprintf(address, "%ld ", (long)(rand() % MSNO) + 1L);
			srand(i++);
			(void)strcat(address, stn[rand() % NSNA]);
			(void)strcat(address, " ");
			srand(i++);
			(void)strcat(address, stw[rand() % NSW]);
			(void)strcat(address, "                              ");
			address[30] = '\0';
			srand(i++);
			cstp = (int)(branch_id * CPB + rand() % CPB - 3);
			(void)strcat(address, cst[cstp]);

			/* Phone number construction */

			exc = 100L;			/* exchange */
			srand(i++);
			while (exc > 100L && exc < 200L)
				exc = rand() % 1000;
			srand(i++);
			numb = (long)rand() % 10000L;  /* last 4 digits */
			(void)sprintf(phone, "%s-%3ld-%4ld", ac[cstp], exc, numb);
			for (np = phone; *np != '\0'; np++) { /* spaces become 0s */
				if (*np == ' ') 
					*np='0';
			}

			/* output variables to ud-format service request */

			(void)printf("n\nSRVCNM\tOPEN_ACCT2\n");
			(void)printf("BRANCH_ID\t%ld\n", branch_id);
			(void)printf("ACCT_TYPE\t%c\n", acct_type);
			(void)printf("SAMOUNT\t%.2f\n", bal);
			(void)printf("LAST_NAME\t%s\n", last_name);
			(void)printf("FIRST_NAME\t%s\n", first_name);
			(void)printf("MID_INIT\t%c\n", mid_init);
			(void)printf("ADDRESS\t%s\n", address);
			(void)printf("PHONE\t%s\n", phone);
			(void)printf("SSN\t%s\n", ss_n);
			(void)printf("\n");

			/* Add savings account with its own balance */

			srand(i++);
			bal = (float)(rand() % 19800) + 200.0;
			acct_type = 'S';

			/* output variables to ud-format service request */

			(void)printf("n\nSRVCNM\tOPEN_ACCT2\n");
			(void)printf("BRANCH_ID\t%ld\n", branch_id);
			(void)printf("ACCT_TYPE\t%c\n", acct_type);
			(void)printf("SAMOUNT\t%.2f\n", bal);
			(void)printf("LAST_NAME\t%s\n", last_name);
			(void)printf("FIRST_NAME\t%s\n", first_name);
			(void)printf("MID_INIT\t%c\n", mid_init);
			(void)printf("ADDRESS\t%s\n", address);
			(void)printf("PHONE\t%s\n", phone);
			(void)printf("SSN\t%s\n", ss_n);
			(void)printf("\n");

			/* Add credit  account with its own balance */

			srand(i++);
			c_bal = (float)(rand() % 30000L) + 90000.0;
			c_bal = (float)(rand() % 19800) + 500.0;
			b_bal = c_bal;

			/* output variables to ud-format service request */

			(void)printf("n\nSRVCNM\tOPENC\n");
			(void)printf("BRANCH_ID\t%ld\n", branch_id);
			(void)printf("CAMOUNT\t%.2f\n", c_bal);
			(void)printf("BAMOUNT\t%.2f\n", b_bal);
			(void)printf("LAST_NAME\t%s\n", last_name);
			(void)printf("FIRST_NAME\t%s\n", first_name);
			(void)printf("MID_INIT\t%c\n", mid_init);
			(void)printf("ADDRESS\t%s\n", address);
			(void)printf("PHONE\t%s\n", phone);
			(void)printf("SSN\t%s\n", ss_n);
			(void)printf("C_ACCT_TYPE\t%c\n", c_acct_type);
			(void)printf("OPEN_CR\t%c\n", opencr);
			(void)printf("\n");
		}
	}
	return 1;
}
