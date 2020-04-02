/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1991 USL
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF USL
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/ws/BANKAPPP.C	$Revision: 1.5 $" */
#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#undef ADDRESS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "atmi.h"
#include "Usysflds.h"
#include "userlog.h"
#include "fml.h"
#include "bankflds.h"

#if defined(__OS2__) && defined(__32BIT__) && defined(__IBMC__)
#define far
#endif

#ifdef noatmi
int tperrno;
#undef tran
#endif
#include "bankapp.h"
#define  IDOK			231
#define  IDCANCEL		232

MRESULT EXPENTRY ClientWndProc(HWND, USHORT, MPARAM, MPARAM);
MRESULT EXPENTRY TransferDlgProc(HWND, USHORT, MPARAM, MPARAM);
MRESULT EXPENTRY WithdrawDlgProc(HWND, USHORT, MPARAM, MPARAM);
MRESULT EXPENTRY DepositDlgProc(HWND, USHORT, MPARAM, MPARAM);
MRESULT EXPENTRY BalanceDlgProc(HWND, USHORT, MPARAM, MPARAM);
MRESULT EXPENTRY CloseDlgProc(HWND, USHORT, MPARAM, MPARAM);
MRESULT EXPENTRY OpenDlgProc(HWND, USHORT, MPARAM, MPARAM);

static FBFR *fbfr;
static TPINIT *tpinfop;

int main(void)
{
	static CHAR szClientClass[] = "Bankapp";
	static ULONG flFrameFlags = FCF_TITLEBAR | FCF_SYSMENU |
				    FCF_SIZEBORDER | FCF_MINMAX |
	     			    FCF_SHELLPOSITION | FCF_TASKLIST | 
				    FCF_ICON | FCF_MENU;

	HAB hab;
	HMQ hmq;
	HWND	hwndFrame, hwndClient;
	QMSG qmsg;

	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab, 0);

	WinRegisterClass(hab, szClientClass, ClientWndProc, 0L, 0);
	hwndFrame = WinCreateStdWindow(HWND_DESKTOP, 
		WS_VISIBLE, &flFrameFlags, szClientClass, 
		"", 0L, (HMODULE)NULL, ID_MENUICON, &hwndClient); 
	while (WinGetMsg(hab, &qmsg, NULL, 0, 0))
		WinDispatchMsg(hab, &qmsg);

#ifndef noatmi
	tpfree((char *)fbfr);
	(void) tpterm();
#endif
	WinDestroyWindow(hwndFrame);
	WinDestroyMsgQueue(hmq);
	WinTerminate(hab);
	return(0);
}

MRESULT EXPENTRY
ClientWndProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
{
	HPS hps;

	switch (msg) {
	case WM_CREATE:
#ifdef noatmi
		fbfr = (FBFR *)Falloc(0, 1024);
#else
		if ((tpinfop = (TPINIT *)tpalloc("TPINIT", NULL, 
			sizeof(struct tpinfo_t))) == (TPINIT *)NULL) {
			userlog("unable to get init buf\n");
			return(0);
		}
		strcpy(tpinfop->usrname, "Smith");
		strcpy(tpinfop->cltname, "bankapp");
		strcpy(tpinfop->passwd, "mypasswd");
		tpinfop->flags = TPU_IGN;
		tpinfop->datalen = 0;
		tpinfop->data = 0;

		if (tpinit(tpinfop) == -1) {
			userlog("tpinit failed");
			return(0);
		}
		fbfr = (FBFR *)tpalloc("FML", NULL, 1500);
#endif
		if (fbfr == NULL) {
			userlog("Failed to allocated fielded buffer");
			return(0);
		}
		return(0);
	case WM_COMMAND:
		switch (COMMANDMSG(&msg)->cmd) {
		case IDM_BALANCE:
			WinDlgBox (HWND_DESKTOP, hwnd, BalanceDlgProc, 0, 
				IDD_BALANCE, NULL);
			return(0);
		case IDM_DEPOSIT:
			WinDlgBox (HWND_DESKTOP, hwnd, DepositDlgProc, 0, 
				IDD_DEPOSIT, NULL);
			return(0);
		case IDM_TRANSFER:
			WinDlgBox (HWND_DESKTOP, hwnd, TransferDlgProc, 0, 
				IDD_TRANSFER, NULL);
			return(0);
		case IDM_WITHDRAWAL:
			WinDlgBox (HWND_DESKTOP, hwnd, WithdrawDlgProc, 0, 
				IDD_WITHDRAW, NULL);
			return(0);
		case IDM_OPEN:
			WinDlgBox (HWND_DESKTOP, hwnd, OpenDlgProc, 0, 
				IDD_OPEN, NULL);
			return(0);
		case IDM_CLOSE:
			WinDlgBox (HWND_DESKTOP, hwnd, CloseDlgProc, 0, 
				IDD_CLOSE, NULL);
			return(0);
		}
		break;
	case WM_DESTROY:
		WinPostMsg (hwnd, WM_QUIT, NULL, NULL);
		return(0);
	case WM_PAINT:
		hps = WinBeginPaint(hwnd, NULL, NULL);
		GpiErase(hps);
		WinEndPaint(hps);
		return(0);
	}
	return(WinDefWindowProc (hwnd, msg, mp1, mp2));
}

/*
 * Field Validation Routines:
 *	chk_account - get account field and validate - returns account number
 *	chk_amount - get amount field, validate, and put in canonical form
 *	chk_socsec - get social security number field and validate
 *	chk_phone - get phone number field and validate
 *	chk_null - get specified field and print warning if not set
 */
static long
chk_account(HWND hDlg, int item, char *account)
{
	int i;
	long acc_num = 0;

	*account = '\0';
	WinQueryDlgItemText (hDlg, item, 40, account);
	for (i=0; account[i] != 0 && i <= 6; i++) {
		if (!isdigit(account[i]))
			break;
		acc_num = acc_num * 10 + (account[i] - '0');
	}
	if (i < 5 || i > 6 || account[i] != '\0') {
		WinSetDlgItemText (hDlg, item, "");
		WinMessageBox (HWND_DESKTOP, hDlg, 
			"   Account number must be 5 or 6 digits", 
			"BANKAPP", 0, MB_OK);
		WinSetFocus(HWND_DESKTOP, WinWindowFromID(hDlg, item));
		return(-1);
	}
	return(acc_num);
}

static int
chk_amount(HWND hDlg, int item, char *amount)
{
	int i;
	int decimal = 0;

	/* FORMAT:  1234567.00 */
	*amount = '\0';
	WinQueryDlgItemText (hDlg, item, 40, amount);
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
		WinSetDlgItemText (hDlg, item, "");
		WinMessageBox (HWND_DESKTOP, hDlg, 
			"    Invalid money amount specified", 
			"BANKAPP", 0, MB_OK);
		WinSetFocus(HWND_DESKTOP, WinWindowFromID(hDlg, item));
		return(-1);
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
	return(0);
}

static int
chk_socsec(HWND hDlg, int item, char *socsec)
{
	*socsec = '\0';
	WinQueryDlgItemText (hDlg, item, 40, socsec);
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
		WinSetDlgItemText (hDlg, item, "");
		WinMessageBox (HWND_DESKTOP, hDlg, 
			"    Social security number must be in form nnn-nn-nnnn", 
			"BANKAPP", 0, MB_OK);
		WinSetFocus(HWND_DESKTOP, WinWindowFromID(hDlg, item));
		return(-1);
	}
	return(0);
}

static int
chk_phone(HWND hDlg, int item, char *phone)
{
	*phone = '\0';
	WinQueryDlgItemText (hDlg, item, 40, phone);
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
		WinSetDlgItemText (hDlg, item, "");
		WinMessageBox (HWND_DESKTOP, hDlg, 
			"    Phone number must be in form nnn-nnn-nnnn", 
			"BANKAPP", 0, MB_OK);
		WinSetFocus(HWND_DESKTOP, WinWindowFromID(hDlg, item));
		return(-1);
	}
	return(0);
}


chk_null(HWND hDlg, int item, char *value, char *warning)
{
	*value = '\0';
	WinQueryDlgItemText (hDlg, item, 80, value);
	if (value[0] == '\0') {
		WinMessageBox (HWND_DESKTOP, hDlg, warning, "BANKAPP", 0, 
				MB_OK);
		WinSetFocus(HWND_DESKTOP, WinWindowFromID(hDlg, item));
		return(-1);
	}
	return(0);
}
/* End of Field Validation Routines */


#ifdef noatmi
tpcall(char *service, char *bufi, long len, char **bufo, long *len2, long flags)
{
	FBFR *fbfr;
	char bal[30];
	long l;
	FILE *fp;

	fbfr = (FBFR *)bufi;

	fp = fopen("fbfr.out", "a+");
	fprintf(fp, "Service: %s\n", service);
	Ffprint(fbfr, fp);
	fprintf(fp, "\n\n");
	fclose(fp);

	Finit(fbfr, Fsizeof(fbfr));
	strcpy(bal, "2030.20");
	Fchg(fbfr, SBALANCE, 0, bal, 0);
	strcpy(bal, "3050.75");
	Fchg(fbfr, SBALANCE, 1, bal, 0);
	l = 10000;
	Fchg(fbfr, ACCOUNT_ID, 0, (char *)&l, 0);
	return(0);
}
#endif
/*
 * Routines to handle Dialog Boxes for Services
 *	BalanceDlg(hDlg, message, wParam, lParam)
 *	CloseDlg(hDlg, message, wParam, lParam)
 *	DepositDlg(hDlg, message, wParam, lParam)
 *	OpenDlg(hDlg, message, wParam, lParam)
 *	TransferDlg(hDlg, message, wParam, lParam)
 *	WithdrawDlg(hDlg, message, wParam, lParam)
 */
MRESULT EXPENTRY BalanceDlgProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
{
	char account1[120];
	long acc_num;
	long len;
	char *s;

	switch (msg) {
	case WM_INITDLG:
		mp2 = mp2;
		WinSetFocus(HWND_DESKTOP, mp1);
		return((void far *)1);

	case WM_COMMAND:
	if(AEPisblocked() == 1)
		return((void far*)1);
	switch(COMMANDMSG(&msg)->cmd) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return((void far *)1);

		Finit(fbfr, Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			strcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("INQUIRY", (char *)fbfr, 0, (char **)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr, STATLIN, 0, 0)) != 0) {
				strcpy(account1, s);
			}
			else
				strcpy(account1, "Inquiry failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				strcpy(account1, "Inquiry failed");
			}
			else
#endif
				
				sprintf(account1, "Account Balance:  %s", 
					Ffind(fbfr, SBALANCE, 0, 0));
		}

		WinMessageBox (HWND_DESKTOP, hDlg, account1, "BANKAPP", 0, 
				MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		WinDismissDlg (hDlg, 0);
		return((void far *)1);
	}
	break;
	}
	return(WinDefDlgProc(hDlg, msg, mp1, mp2));
}

MRESULT EXPENTRY CloseDlgProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
{
	char account1[120];
	long acc_num;
	long len;
	char *s;

	switch (msg) {
	case WM_INITDLG:
		mp2 = mp2;
		WinSetFocus(HWND_DESKTOP, mp1);
		return((void far *)1);

	case WM_COMMAND:
	if(AEPisblocked() == 1)
		return((void far*)1);
	switch(COMMANDMSG(&msg)->cmd) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return((void far *)1);

		Finit(fbfr, Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			strcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("CLOSE_ACCT", (char *)fbfr, 0, (char **)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr, STATLIN, 0, 0)) != 0) {
				strcpy(account1, s);
			}
			else
				strcpy(account1, "Close account failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				strcpy(account1, "Close account failed");
			}
			else
#endif
				sprintf(account1, "Final Balance:  %s", 
					Ffind(fbfr, SBALANCE, 0, 0));
		}

		WinMessageBox (HWND_DESKTOP, hDlg, account1, "BANKAPP", 0, 
			MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		WinDismissDlg (hDlg, 0);
		return((void far *)1);
	}
	break;
	}
	return(WinDefDlgProc(hDlg, msg, mp1, mp2));
}

MRESULT EXPENTRY DepositDlgProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
{
	char account1[120];
	char amount[40];
	long acc_num;
	long len;
	char *s;

	switch (msg) {
	case WM_INITDLG:
		mp2 = mp2;
		WinSetFocus(HWND_DESKTOP, mp1);
		return((void far *)1);

	case WM_COMMAND:
	if(AEPisblocked() == 1)
		return((void far*)1);
	switch(COMMANDMSG(&msg)->cmd) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return((void far *)1);

		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return((void far *)1);

		Finit(fbfr, Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
		(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			strcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("DEPOSIT", (char *)fbfr, 0, (char **)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr, STATLIN, 0, 0)) != 0) {
				strcpy(account1, s);
			}
			else
				strcpy(account1, "Deposit failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				strcpy(account1, "Deposit failed");
			}
			else
#endif
				sprintf(account1, "Account Balance:  %s", 
					Ffind(fbfr, SBALANCE, 0, 0));
		}

		WinMessageBox (HWND_DESKTOP, hDlg, account1, "BANKAPP", 0, 
				MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		WinDismissDlg (hDlg, 0);
		return((void far *)1);
	}
	break;
	}
	return(WinDefDlgProc(hDlg, msg, mp1, mp2));
}

MRESULT EXPENTRY OpenDlgProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
{
	char *s;
	char account1[120], amount[40];
	char firstname[80], lastname[80], midname[3], phone[20], street[80];
	char citystate[80], socsec[20];
	static int branch, accounttype;
	long acc_num, l;
	int i, ok;
	long len;

	switch (msg) {
	case WM_INITDLG:
		mp2 = mp2;
		branch = IDC_BRANCH1;
		accounttype = IDC_ACCOUNTTYPE1;
		WinSendDlgItemMsg(hDlg, branch, 
		    BM_SETCHECK, MPFROM2SHORT(TRUE, 0), NULL);
		WinSendDlgItemMsg(hDlg, accounttype, 
			    BM_SETCHECK, MPFROM2SHORT(TRUE, 0), NULL);
		WinSetFocus(HWND_DESKTOP, mp1);
		return((void far *)1);
	case WM_CONTROL:
		switch (SHORT1FROMMP(mp1))
			{
			case IDC_ACCOUNTTYPE1:
			case IDC_ACCOUNTTYPE2:
		        	WinSendDlgItemMsg(hDlg, accounttype, 
				    BM_SETCHECK, MPFROM2SHORT(FALSE, 0), NULL);
				WinSendDlgItemMsg(hDlg, SHORT1FROMMP(mp1), 
				    BM_SETCHECK, MPFROM2SHORT(TRUE, 0), NULL);
				accounttype = SHORT1FROMMP(mp1);
				return((void far *)1);
			case IDC_BRANCH1:
			case IDC_BRANCH2:
			case IDC_BRANCH3:
			case IDC_BRANCH4:
			case IDC_BRANCH5:
			case IDC_BRANCH6:
			case IDC_BRANCH7:
			case IDC_BRANCH8:
			case IDC_BRANCH9:
			case IDC_BRANCH10:
				WinSendDlgItemMsg(hDlg, branch, 
				    BM_SETCHECK, MPFROM2SHORT(FALSE, 0), NULL);
				WinSendDlgItemMsg(hDlg, SHORT1FROMMP(mp1), 
				    BM_SETCHECK, MPFROM2SHORT(TRUE, 0), NULL);
				branch = SHORT1FROMMP(mp1);
				return((void far *)1);
			}
		break;
	case WM_COMMAND:
	if(AEPisblocked() == 1)
		return((void far*)1);
	switch(COMMANDMSG(&msg)->cmd) {
	case IDOK:
		ok = 0;
		if(chk_null(hDlg, IDC_LASTNAME, lastname, 
			"    Please enter last name") < 0)
			return((void far *)1);
		if(chk_null(hDlg, IDC_FIRSTNAME, firstname, 
			"    Please enter first name") < 0)
			return((void far *)1);
		midname[0] = '\0';
		WinQueryDlgItemText (hDlg, IDC_MIDNAME, sizeof(midname), midname);
		if(chk_phone(hDlg, IDC_PHONE, phone) < 0)
			return((void far *)1);
		if(chk_null(hDlg, IDC_STREET, street, 
			"    Please enter street address") < 0)
			return((void far *)1);
		if(chk_null(hDlg, IDC_CITYSTATE, citystate, 
			"    Please enter city, state, and zip") < 0)
			return((void far *)1);
		if(chk_socsec(hDlg, IDC_SOCSEC, socsec) < 0)
			return((void far *)1);
		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return((void far *)1);
#ifndef noatmi
		if ((fbfr = (FBFR *)tprealloc((char *)fbfr, 512)) == NULL) {
			userlog("tprealloc failed");
			return((void far *)1);
		}
#endif
		Finit(fbfr, Fsizeof(fbfr));
		if (accounttype == IDC_ACCOUNTTYPE1)
			(void) Fchg(fbfr, ACCT_TYPE, 0, "C", 0);
		else
			(void) Fchg(fbfr, ACCT_TYPE, 0, "S", 0);
		(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);
		(void) Fchg(fbfr, LAST_NAME, 0, lastname, 0);
		(void) Fchg(fbfr, FIRST_NAME, 0, firstname, 0);
		(void) Fchg(fbfr, MID_INIT, 0, midname, 0);
		/*
		 * format of address is
		 * 30 character street address followed by city state zip
		 */
		i = strlen(street);
		if (i > 30) {
			i = 30;
			street[30] = '\0';
		}
		else {
			for (; i < 30; i++)
				street[i] = ' ';
		}
		(void) strcat(street, citystate);
		street[60] = '\0';
		(void) Fchg(fbfr, ADDRESS, 0, street, 0);
		(void) Fchg(fbfr, PHONE, 0, phone, 0);
		(void) Fchg(fbfr, SSN, 0, socsec, 0);
		l = branch - IDC_BRANCH1 + 1;
		if (Fchg(fbfr, BRANCH_ID, 0, (char *)&l, 0) < 0) {
			userlog("Fchg failed");
		}

#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			strcpy(account1, "Transaction failed");
		}
		else
#endif
		len = 0;
		if (tpcall("OPEN_ACCT", (char *)fbfr, 0, (char **)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr, STATLIN, 0, 0)) != 0) {
				strcpy(account1, s);
			}
			else
				strcpy(account1, "Open Account failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				strcpy(account1, "Open Account failed");
			}
			else
#endif
			{
				Fget(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
				sprintf(account1, 
				"Account Number:  %ld\nAccount Balance: %s", 
					acc_num, 
					Ffind(fbfr, SBALANCE, 0, 0));
				ok = 1;
			}
		}
		WinMessageBox (HWND_DESKTOP, hDlg, account1, "BANKAPP", 0, 
				MB_OK);
		if (!ok)
			break;
		/* FALL THRU */
	case IDCANCEL:
		WinDismissDlg (hDlg, 0);
		return((void far *)1);
	}
	break;
	}
	return(WinDefDlgProc(hDlg, msg, mp1, mp2));
}

MRESULT EXPENTRY TransferDlgProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
{
	char *s;
	char account1[120];
	char account2[40];
	char amount[40];
	long acc_num1, acc_num2;
	long len;

	switch (msg) {
	case WM_INITDLG:
		mp2 = mp2;
		WinSetFocus(HWND_DESKTOP, mp1);
		return((void far *)1);

	case WM_COMMAND:
	if(AEPisblocked() == 1)
		return((void far*)1);
	switch(COMMANDMSG(&msg)->cmd) {
	case IDOK:
		if((acc_num1 = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return((void far *)1);

		if((acc_num2 = chk_account(hDlg, IDC_ACCOUNT2, account2)) < 0)
			return((void far *)1);

		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return((void far *)1);

		Finit(fbfr, Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num1, 0);
		(void) Fchg(fbfr, ACCOUNT_ID, 1, (char *)&acc_num2, 0);
		(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			strcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("TRANSFER", (char *)fbfr, 0, (char **)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr, STATLIN, 0, 0)) != 0) {
				strcpy(account1, s);
			}
			else
				strcpy(account1, "Transfer failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				strcpy(account1, "Transfer failed");
			}
			else
#endif
				sprintf(account1, 
		"Debit Account Balance:  %s\nCredit Account Balance: %s", 
					Ffind(fbfr, SBALANCE, 0, 0), 
					Ffind(fbfr, SBALANCE, 1, 0));
		}

		WinMessageBox (HWND_DESKTOP, hDlg, account1, "BANKAPP", 0, 
				MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		WinDismissDlg (hDlg, 0);
		return((void far *)1);
	}
	break;
	}
	return(WinDefDlgProc(hDlg, msg, mp1, mp2));
}

MRESULT EXPENTRY WithdrawDlgProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
{
	char *s;
	char account1[120];
	char amount[40];
	long acc_num;
	long len;

	switch (msg) {
	case WM_INITDLG:
		mp2 = mp2;
		WinSetFocus(HWND_DESKTOP, mp1);
		return((void far *)1);

	case WM_COMMAND:
	if(AEPisblocked() == 1)
		return((void far*)1);
	switch(COMMANDMSG(&msg)->cmd) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return((void far *)1);

		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return((void far *)1);

		Finit(fbfr, Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char *)&acc_num, 0);
		(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			strcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("WITHDRAWAL", (char *)fbfr, 0, (char **)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr, STATLIN, 0, 0)) != 0) {
				strcpy(account1, s);
			}
			else
				strcpy(account1, "Withdrawal failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				strcpy(account1, "Withdrawal failed");
			}
			else
#endif
				sprintf(account1, "Account Balance:  %s", 
					Ffind(fbfr, SBALANCE, 0, 0));
		}

		WinMessageBox (HWND_DESKTOP, hDlg, account1, "BANKAPP", 0, 
				MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		WinDismissDlg (hDlg, 0);
		return((void far *)1);
	}
	break;
	}
	return(WinDefDlgProc(hDlg, msg, mp1, mp2));
}
