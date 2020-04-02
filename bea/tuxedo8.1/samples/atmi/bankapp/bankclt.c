/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*
 * Copyright * 1999 BEA Systems, Inc.
 *
 * Portions of this software Copyright * 1995 Novell, Inc.
 * All rights reserved
 *
 * THIS IS UNPUBLISHED PROPRIETARY
 * SOURCE CODE OF BEA Systems, Inc.
 * The copyright notice above does not
 * evidence any actual or intended
 * publication of such source code.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <atmi.h>
#ifdef FML32
#include <Usysfl32.h>
#include <fml32.h>
#include <fml1632.h>
#else
#include <Usysflds.h>
#include <fml.h>
#endif
#include <userlog.h>
#include "bankflds.h"


/* Prototype definitions for functions */
static int	Balance(void);
static int	Withdrawal(void);
static int	Deposit(void);
static int	Transfer(void);
static int	OpenAccount(void);
static int	CloseAccount(void);
static long	get_account(char *);
static int	get_amount(char *, int);
static int	get_socsec(char *, int);
static int	get_phone(char *, int);
static int	get_val(char *, int, char *);
static int	getline(char *, int);
static void	(_TMDLLENTRY unsolfcn)(char *, long, long);
static int	do_tpcall(char *);


/* Pointer to FML buffer that is used for communication */
static FBFR	*fbfr;

/* This is the layout of the menu that is displayed to the user */
char *menu = "\n\n\
                      Welcome to the Tuxedo Bank\n\
           Make a selection from the following choices\n\
                    1. Balance Inquiry\n\
                    2. Withdrawal\n\
                    3. Deposit\n\
                    4. Transfer\n\
                    5. Open Account\n\
                    6. Close Account\n\
                    0. Exit Application\n\
\n\
                   Enter Selection: ";

/*
 * Main
 */
/*ARGSUSED0*/
main(int argc, char **argv)
{
	TPINIT *tpinfop;
	int	done=0;

	/* Allocate a TPINIT buffer */
	if ((tpinfop = (TPINIT *)tpalloc("TPINIT", NULL,
		sizeof(struct tpinfo_t))) == (TPINIT *)NULL) {
		(void)fprintf(stderr, "ERROR: tpalloc failed (%s)\n",
			tpstrerror(tperrno));
		return(1);
	}

	/* Enter user information */
	(void)strcpy(tpinfop->usrname, "Bill");
	(void)strcpy(tpinfop->cltname, "bankclt");
	(void)strcpy(tpinfop->passwd, "mypasswd");
	tpinfop->flags = TPU_DIP;
	tpinfop->datalen = 0;
	tpinfop->data = 0;

	/* Join the Tuxedo System */
	if (tpinit(tpinfop) == -1) {
		(void)fprintf(stderr, "ERROR: tpinit failed (%s)\n",
			tpstrerror(tperrno));
		return(1);
	}

	/* Allocate the FML buffer used for all communication */
	fbfr = (FBFR *)tpalloc(FMLTYPE, NULL, 1024);
	if (fbfr == NULL) {
		(void)fprintf(stderr,
			"ERROR: tpalloc of FML buffer failed (%s)\n",
			tpstrerror(tperrno));
		return(1);
	}

	/* Set an unsolicited message handler */
	if(tpsetunsol(unsolfcn) == TPUNSOLERR) {
		(void)fprintf(stderr, "ERROR: tpsetunsol failed (%s)\n",
			tpstrerror(tperrno));
		return(1);
	}
	do {
		char option[10];

		(void)fprintf(stdout, "%s", menu);	/* Display the menu */
		(void)fflush(stdout);
		if(get_val(option, sizeof(option), "Please enter an option\n")
				== -1) {
			(void)fprintf(stderr, "Exiting\n");
			return(1);
		}
		switch(option[0]) {
		case '1':		/* Balance Inquiry */
			if(Balance() == -1)
				done = 1;
			break;
		case '2':		/* Withdrawal */
			if(Withdrawal() == -1)
				done = 1;
			break;
		case '3':		/* Deposit */
			if(Deposit() == -1)
				done = 1;
			break;
		case '4':		/* Transfer */
			if(Transfer() == -1)
				done = 1;
			break;
		case '5':		/* Open Account */
			if(OpenAccount() == -1)
				done = 1;
			break;
		case '6':		/* Close Account */
			if(CloseAccount() == -1)
				done = 1;
			break;
		case '0':		/* Exit Application */
			done=1;
			break;
		default :		/* unknown input, retry */
			break;
		}
	} while(done == 0);
	tpfree((char *)fbfr);
	tpterm();
	return(0);
}

/*
 * Get the Cash Balance for an account
 */
int
Balance(void)
{
	long acc_num=-1;

	if((acc_num = get_account("\nEnter Account Number: ")) < 0)
		return(0);

	/* Initialize the FML buffer */
	Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
	/* Add the Account number to the buffer */
	(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);

	/* send a request to the INQUIRY service and get the reply */
	if (do_tpcall("INQUIRY") == 0) {
		/* if Success the result is in the FML buffer */
		(void)fprintf(stdout, "\nAccount Balance:  %s\n",
			(char *) Ffind(fbfr, SBALANCE, 0, 0));
	}
	return(0);
}

/*
 * Withdraw money from an account
 */

int
Withdrawal(void)
{
	char amount[40];
	long acc_num;

	if((acc_num = get_account("\nEnter Account Number: ")) < 0)
		return(0);

	if(get_amount(amount, sizeof(amount)) < 0)
		return(0);

	/* Initialize the FML buffer */
	Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
	/* Add the Account number and the amount to the buffer */
	(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
	(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);

	/* send a request to the WITHDRAWAL service and get the reply */
	if (do_tpcall("WITHDRAWAL") == 0) {
		/* if Success the result is in the FML buffer */
		(void)fprintf(stdout,
			"\nWithdrawal for $%s succeeded\n", amount);
		(void)fprintf(stdout, "\nAccount Balance:  %s\n",
			(char *) Ffind(fbfr, SBALANCE, 0, 0));
	}
	return(0);
}

/*
 * Deposit Money to an account
 */
static int
Deposit(void)
{
	char amount[40];
	long acc_num;

	if((acc_num = get_account("\nEnter Account Number: ")) < 0)
		return(0);

	if(get_amount(amount, sizeof(amount)) < 0)
		return(0);

	/* Initialize the FML buffer */
	Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
	/* Add the Account number and amount to the buffer */
	(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
	(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);

	/* send a request to the DEPOSIT service and get the reply */
	if (do_tpcall("DEPOSIT") == 0) {
		/* if Success the result is in the FML buffer */
		(void)fprintf(stdout, "\nDeposit for $%s succeeded\n", amount);
		(void)fprintf(stdout, "\nAccount Balance:  %s\n",
			(char *) Ffind(fbfr, SBALANCE, 0, 0));
	}
	return(0);
}

/*
 * Transfer money between accounts
 */
static int
Transfer(void)
{
	char amount[40];
	long source_num, dest_num;

	if((source_num = get_account("\nEnter Source Account Number: ")) < 0)
		return(0);

	if((dest_num = get_account("\nEnter Destination Account Number: ")) < 0)
		return(0);

	if(get_amount(amount, sizeof(amount)) < 0)
		return(0);

	/* Initialize the FML buffer */
	Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
	/* Add the Account numbers and the amount to transfer to the buffer */
	(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&source_num, 0);
	(void) Fchg(fbfr, ACCOUNT_ID, 1, (char *)&dest_num, 0);
	(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);

	/* send a request to the TRANSFER service and get the reply */
	if (do_tpcall("TRANSFER") == 0) {
		/* if Success the result is in the FML buffer */
		(void)fprintf(stdout, "\nTransfer for $%s succeeded\n", amount);
		(void)fprintf(stdout, "\nSource Account %ld Balance:  %s\n",
			source_num, (char *) Ffind(fbfr, SBALANCE, 0, 0));
		(void)fprintf(stdout,
			"\nDestination Account %ld Balance:  %s\n",
			dest_num, (char *) Ffind(fbfr, SBALANCE, 1, 0));
	}
	return(0);
}

/*
 * Open a new account
 */
static int
OpenAccount(void)
{
	char amount[40];
	char firstname[80], lastname[80], midname[3], phone[20], street[80];
	char citystate[80], socsec[20];
	char br[3], acct_type[2];
	long acc_num;
	int i;
	static int branch;


	/* Initialize the FML buffer */
	Finit(fbfr, (FLDLEN)Fsizeof(fbfr));

	(void)fprintf(stdout, "Please enter Last Name: ");
	(void)fflush(stdout);
	if(get_val(lastname, sizeof(lastname),
			"\nPlease enter Last Name: ") == -1)
		return(0);
	(void) Fchg(fbfr, LAST_NAME, 0, lastname, 0);

	(void)fprintf(stdout, "First Name: ");
	(void)fflush(stdout);
	if(get_val(firstname, sizeof(firstname),
			"Please Enter First Name: ") == -1)
		return(0);
	(void) Fchg(fbfr, FIRST_NAME, 0, firstname, 0);

	(void)fprintf(stdout, "Middle Initial: ");
	(void)fflush(stdout);
	midname[0] = '\0';
	if(getline(midname, sizeof(midname)) == 0)
		return(0);
	(void) Fchg(fbfr, MID_INIT, 0, midname, 0);

	(void)fprintf(stdout, "Social Security Number: ");
	(void)fflush(stdout);
	if(get_socsec(socsec, sizeof(socsec)) == -1)
		return(0);
	(void) Fchg(fbfr, SSN, 0, socsec, 0);

	(void)fprintf(stdout, "Mailing Address: ");
	(void)fflush(stdout);
	if(get_val(street, sizeof(street),
			"Please Enter Mailng Address: ") == -1)
		return(0);

	(void)fprintf(stdout, "City, State and Zip: ");
	(void)fflush(stdout);
	if(get_val(citystate, sizeof(citystate),
			"Please Enter City, State and Zip: ") == -1)
		return(0);
	/*
	 * format of address is
	 * 30 character street address followed by city state zip
	 */
	i = strlen(street);
	if (i > 30) {
		i = 30;
	}
	else {
		for (; i < 30; i++)
			street[i] = ' ';
	}
	street[30] = '\0';
	(void) strcat(street, citystate);
	street[60] = '\0';
	(void) Fchg(fbfr, ADDRESS, 0, street, 0);

	(void)fprintf(stdout, "Telephone Number: ");
	(void)fflush(stdout);
	if(get_phone(phone, sizeof(phone)) == -1)
		return(0);
	(void) Fchg(fbfr, PHONE, 0, phone, 0);

	/*CONSTCOND*/
	while(1) {
	    (void)fprintf(stdout, "Account Type C - checking S - Savings: ");
	    (void)fflush(stdout);
	    if(get_val(acct_type, sizeof(acct_type),
			"Please Enter Account Type: ") == -1)
		return(0);
	    if(strcmp(acct_type, "C") != 0 && strcmp(acct_type, "S") != 0)
		continue;
	    (void) Fchg(fbfr, ACCT_TYPE, 0, acct_type, 0);
	    break;
	}

	/*CONSTCOND*/
	while(1) {
	    (void)fprintf(stdout, "Bank Branches are\n");
	    (void)fprintf(stdout, "%-16s%-16s%-16s%-16s%-15s\n",
"1-San Francisco", "2-Los Angeles", "3-Dallas", "4-Chacago", "5-St. Louis");
	    (void)fprintf(stdout, "%-16s%-16s%-16s%-16s%-15s\n",
"6-Atlanta", "7-Maimi", "8-Philadelphia", "9-New York", "10-Boston");
	    (void)fprintf(stdout, "Desired Branch For Account: ");
	    (void)fflush(stdout);
	    if(get_val(br, sizeof(br),
			"Please Enter Desired Branch: ") == -1)
		return(0);
	    branch = atoi(br);
	    if(branch < 1 || branch > 10)
		continue;
	    Fchg(fbfr, BRANCH_ID, 0, (char *)&branch, 0);
	    break;
	}

	(void)fprintf(stdout, "Initial Balance: ");
	(void)fflush(stdout);
	if(get_val(amount, sizeof(amount),
			"Please Enter Initial Balance: ") == -1)
		return(0);
	(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);

	/* send a request to the OPEN_ACCT service and get the reply */
	if (do_tpcall("OPEN_ACCT") == 0) {
		/* if Success the result is in the FML buffer */
		Fget(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
		(void)fprintf(stdout, "\nNew Account Opened\n");
		(void)fprintf(stdout,
			"\nAccount Number: %ld\nAccount Balance:  %s\n",
			acc_num,
			(char *) Ffind(fbfr, SBALANCE, 0, 0));
	}
	return(0);
}

/*
 * Close and existing account
 */
static int
CloseAccount(void)
{
	long acc_num;

	if((acc_num = get_account("\nEnter Account Number To Close: ")) < 0)
		return(0);

	/* Initialize the FML buffer */
	Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
	/* Add the Account number to the buffer */
	(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);

	/* send a request to the CLOSE_ACCOUNT service and get the reply */
	if (do_tpcall("CLOSE_ACCT") == 0) {
		(void)fprintf(stdout, "\nAccount %ld Closed\n", acc_num);
		(void)fprintf(stdout, "\nFinal Balance:  %s\n",
			(char *) Ffind(fbfr, SBALANCE, 0, 0));
	}
	return(0);
}


/*
 * This function does the tpcall to Tuxedo.
 */
static int
do_tpcall(char *service)
{

	long len;
	char *server_status;

	/* Begin a Global transaction */
	if (tpbegin(30, 0) == -1) {
		(void)fprintf(stderr, "ERROR: tpbegin failed (%s)\n",
			tpstrerror(tperrno));
		return(-1);
	}
	/* Request the service with the user data */
	if (tpcall(service, (char *)fbfr, 0, (char **)&fbfr, &len, 0) == -1) {
		if(tperrno== TPESVCFAIL && fbfr != NULL &&
		    (server_status=Ffind(fbfr,STATLIN,0,0)) != 0) {
			/* Server returned failure */
			(void)fprintf(stderr, "%s returns failure (%s)\n",
				service,server_status);
		}
		else {
			(void)fprintf(stderr,
				"ERROR: %s failed (%s)\n", service,
				tpstrerror(tperrno));
		}
		/* Abort the transaction */
		(void) tpabort(0);
		return(-1);
	}
	/* Commit the transaction */
	if(tpcommit(0) < 0) {
		(void)fprintf(stderr, "ERROR: tpcommit failed (%s)\n",
			tpstrerror(tperrno));
		return(-1);
	}
	return(0);
}

/*
 * This is the function that gets called when a unsolicited message is received
 */
void _TMDLLENTRY
unsolfcn(char *inbuf, long len, long flags)
{
	char buftype[9];
	
	len = len; /* UNUSED */
	flags = flags; /* UNUSED */
	/* Get the buffer type */
	if(tptypes(inbuf, (char *)buftype, NULL) == -1) {
		(void)fprintf(stderr, "ERROR: tptypes() failed (%s)\n",
			tpstrerror(tperrno));
		return;
	}
	/* Only understand the STRING buffer */
	if(strcmp(buftype, "STRING") != 0) {
		(void)fprintf(stderr, "Unsupported Buffer Type %s\n", buftype);
		return;
	}
	/* print out the message */
	(void)fprintf(stdout, "\n\nUnsolicited message received:%s\n\n", inbuf);
	(void)fflush(stdout);
	return;
}

/*
 * Get the account number
 */
static long
get_account(char *message)
{
	char account[120];
	int i;
	long acc_num = 0;

	/*CONSTCOND*/
	while(1) {
		(void)fprintf(stdout, message);
		if(getline(account, sizeof(account)) == 0)
			return(-1);

		for (i=0; account[i] != 0 && i <= 6; i++) {
			if (!isdigit(account[i]))
				break;
			acc_num = acc_num * 10 + (account[i] - '0');
		}
		if (i < 5 || i > 6 || account[i] != '\0') {
			(void)fprintf(stderr,
			"ERROR: Account number must be 5 or 6 digits\n");
			acc_num = 0;
			continue;
		}
		break;
	}
	return(acc_num);
}

/*
 * Get the amount
 */
static int
get_amount(char *amount, int size)
{
	int i;
	int decimal = 0;

	/*CONSTCOND*/
	while(1) {
		(void)fprintf(stdout, "\nEnter Amount: ");
		if(getline(amount, size) == 0)
			return(-1);

		/* FORMAT:  1234567.00 */
		for (i=0; amount[i] != 0 && i < 10; i++) {
			if (amount[i] == '.') {
				if (decimal)
					break;
				decimal++;
				continue;
			}
			if (!isdigit(amount[i]))
				break;
			if (decimal) {
				decimal++;
				if (decimal > 3)
					break;
			}
		}
		if (i == 0 || (3 - decimal) + i > 10) {
			(void)fprintf(stderr,
				"Invalid money amount specified.\n");
			(void)fprintf(stderr, "The format is 1234567.00\n");
			continue;
		}
		if (!decimal) {
			amount[i++] = '.';
			decimal++;
		}
		while (decimal < 3) {
			amount[i++] = '0';
			decimal++;
		}
		amount[i] = '\0';
		break;
	}
	return(0);
}

/*
 * Get the social security number
 */
static int
get_socsec(char *socsec, int size)
{

	/*CONSTCOND*/
	while(1) {
		if(getline(socsec, size) == 0)
			return(-1);

		if (!isdigit(socsec[0]) ||
		    !isdigit(socsec[1]) ||
		    !isdigit(socsec[2]) ||
		    socsec[3] != '-' ||
		    !isdigit(socsec[4]) ||
		    !isdigit(socsec[5]) ||
		    socsec[6] != '-' ||
		    !isdigit(socsec[7]) ||
		    !isdigit(socsec[8]) ||
		    !isdigit(socsec[9]) ||
		    !isdigit(socsec[10])) {
			(void)fprintf(stderr, 
		"Social security number must be in form nnn-nn-nnnn\n");
			continue;
		}
		break;
	}
	return(0);
}

/*
 * Get the telephone number
 */
static int
get_phone(char *phone, int size)
{

	/*CONSTCOND*/
	while(1) {
		if(getline(phone, size) == 0)
			return(-1);
		if (!isdigit(phone[0]) ||
		    !isdigit(phone[1]) ||
		    !isdigit(phone[2]) ||
		    phone[3] != '-' ||
		    !isdigit(phone[4]) ||
		    !isdigit(phone[5]) ||
		    !isdigit(phone[6]) ||
		    phone[7] != '-' ||
		    !isdigit(phone[8]) ||
		    !isdigit(phone[9]) ||
		    !isdigit(phone[10]) ||
		    !isdigit(phone[11])) {
			(void)fprintf(stderr, 
				"Phone number must be in form nnn-nnn-nnnn\n");
			continue;
		}
		break;
	}
	return(0);
}

/*
 * Get a line without a null value
 */
static int
get_val(char *value, int size, char *warning)
{

	/*CONSTCOND*/
	while(1) {
		*value = '\0';
		if(getline(value, size) == -1)
			return(-1);
		if (value[0] == '\0') {
			(void)fprintf(stderr, "%s", warning);
			continue;
		}
		break;
	}
	return(0);
}
/* End of Field Validation Routines */


/*
 * Get a line of input from the keyboard.
 */
static int
getline(char *value, int size)
{
	int ch, offset = 0;

	if(size <= 0)
		return (-1);
	do {
		if((ch=getchar()) == EOF) {
			value[0] = '\0';
			return(-1);
		}
		if(ch == '\n' || ch == '\r')
			break;
		value[offset++] = (char) ch;
	} while (offset < size);
	value[offset] = '\0';
	return(offset);
}
