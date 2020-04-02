/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1991 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF USL
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/

/* #ident	"@(#) samples/atmi/bankapp/nt/client/bankappw.c	$Revision: 1.5 $" */

#ifndef __STDC__
#define __STDC__ 0
#endif

#include <stdio.h>
#undef NULL
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
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
#include "bankapp.h"
#include "bankflds.h"

#ifdef __TURBOC__
 #pragma warn -stu
#endif

#ifdef __cplusplus
extern "C" {
#endif
typedef void (FAR PASCAL*     _TM_UNSOL)(char FAR *, long, long);
typedef long (FAR PASCAL* _TM_WNDPROC)(HWND, unsigned int, unsigned int, long);

#ifdef noatmi
int tperrno;
#endif
long FAR PASCAL WndProc(HWND, WORD, WORD, LONG);
BOOL FAR PASCAL TransferDlg(HWND, WORD, WORD, LONG);
BOOL FAR PASCAL WithdrawDlg(HWND, WORD, WORD, LONG);
BOOL FAR PASCAL DepositDlg(HWND, WORD, WORD, LONG);
BOOL FAR PASCAL BalanceDlg(HWND, WORD, WORD, LONG);
BOOL FAR PASCAL CloseDlg(HWND, WORD, WORD, LONG);
BOOL FAR PASCAL OpenDlg(HWND, WORD, WORD, LONG);
void FAR PASCAL UnsolProc(char FAR *, long, long);

#ifdef __cplusplus
}
#endif

static HANDLE	hInst;
static FBFR FAR *fbfr;
static char passwd[16];
static char user[32];

void
Error(char* fmt, ...)
{
	char msg[100];

	va_list args;
	va_start(args, fmt);
	vsprintf(msg, fmt, args);
	MessageBox(NULL, msg, "Error", MB_ICONSTOP|MB_OK);
	va_end(args);
}
	
BOOL FAR PASCAL
GetUser(HWND hDlg, unsigned message, WORD wParam, LONG lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_USER));
		return FALSE;
	case WM_COMMAND:
		switch(wParam){
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		case IDOK:
			if (GetDlgItemText(hDlg, IDC_USER, user, sizeof user) == 0){
				Error("Missing user name");
				SetFocus(GetDlgItem(hDlg, IDC_USER));
				return TRUE;
			}
			if (GetDlgItemText(hDlg, IDC_PASSWD, passwd, sizeof passwd) == 0){
				Error("Missing password");
				SetFocus(GetDlgItem(hDlg, IDC_PASSWD));
				return TRUE;
			}
			EndDialog(hDlg, 1);
			return TRUE;
		default:
			return FALSE;
		}
	default:
		break;
	}
	return FALSE;
}

int PASCAL
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASS  wc;
	TPINIT FAR *tpinfop;
	int auth_level;
	FARPROC lpProc;
	int got_data = 0;
	char* app_pw;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (_TM_WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, "MONEY");
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName =  "BANKAPP";
	wc.lpszClassName = "BANKAPP";
	RegisterClass(&wc);

	/* open the account dialog box */
	hInst = hInstance;

#ifdef noatmi
	fbfr = (FBFR FAR *)Falloc(0, 1024);
#else
	tpinfop = (TPINIT FAR*)tpalloc("TPINIT", NULL, TPINITNEED(16));
	if (!tpinfop){
		userlog("unable to get init buf\n");
		return(0);
	}

	if ((auth_level = tpchkauth()) == -1) {
		Error("unable to get authentication level: %s",
			tpstrerror(tperrno));
		tpfree((char *)tpinfop);
		return 0;
	}

	switch(auth_level){
	case TPNOAUTH:
		(void)strcpy(tpinfop->usrname, "bankapp");
		break;
	case TPSYSAUTH:
	case TPAPPAUTH:
		app_pw = tuxgetenv("APP_PW");
		if (!app_pw){
			Error("Missing application password in environ (APP_PW)");
			return 0;
		}

		lstrcpy(tpinfop->passwd, app_pw);
		if (auth_level == TPSYSAUTH)
			break;

		lpProc = MakeProcInstance(GetUser, hInst);
		switch(DialogBox(hInst, MAKEINTRESOURCE(IDD_USER), NULL, (DLGPROC)lpProc)){
		case -1:
			break;
		case 0: /* Cancel */
			break;
		default:
			if (*user && *passwd)
				got_data = 1;
			break;
		}

		FreeProcInstance(lpProc);

		if (!got_data){
			Error("Missing user/password information");
			tpfree((char*)tpinfop);
			return 0;
		}

		lstrcpy(tpinfop->cltname, "*");
		lstrcpy(tpinfop->usrname, user);
	    	lstrcpy((char FAR *)&tpinfop->data, passwd);
	    	break;
	}

	tpinfop->flags = TPU_DIP;
#ifdef _TMSTHREADS
	tpinfop->flags |= TPMULTICONTEXTS;
#endif

	if (tpinit(tpinfop) == -1) {
		Error("tpinit failed: %s", tpstrerror(tperrno));
		tpfree((char*)tpinfop);
		return(0);
	}
	tpfree((char*)tpinfop);

	fbfr = (FBFR FAR *)tpalloc(FMLTYPE, NULL, 1024);
#endif
	if (fbfr == NULL) {
		userlog("Failed to allocated fielded buffer");
		return(0);
	}

	hwnd = CreateWindow ("BANKAPP", "BANKAPP",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		150, 155,
		NULL, NULL, hInstance, NULL);
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	/* process messages */
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if(hPrevInstance)			/* unused */
		lpCmdLine = lpCmdLine;		/* unused */
	tpfree((char FAR *)fbfr);
#ifndef noatmi
	(void) tpterm();
#endif

	return (msg.wParam);
}

long FAR PASCAL
WndProc(HWND hwnd, WORD message, WORD wParam, LONG lParam)
{
	static FARPROC lpfnTransferDlg;
	static FARPROC lpfnWithdrawDlg;
	static FARPROC lpfnDepositDlg;
	static FARPROC lpfnBalanceDlg;
	static FARPROC lpfnCloseDlg;
	static FARPROC lpfnOpenDlg;
	static FARPROC lpfnUnsolptr;

	switch (message) {
	case WM_COMMAND:
	switch (wParam) {
	case IDM_BALANCE:
		DialogBox (hInst, "BALANCE", hwnd, (DLGPROC)lpfnBalanceDlg);
		return(0);
	case IDM_DEPOSIT:
		DialogBox (hInst, "DEPOSIT", hwnd, (DLGPROC)lpfnDepositDlg);
		return(0);
	case IDM_TRANSFER:
		DialogBox (hInst, "TRANSFER", hwnd, (DLGPROC)lpfnTransferDlg);
		return(0);
	case IDM_WITHDRAWAL:
		DialogBox (hInst, "WITHDRAW", hwnd, (DLGPROC)lpfnWithdrawDlg);
		return(0);
	case IDM_OPEN:
		DialogBox (hInst, "OPEN", hwnd, (DLGPROC)lpfnOpenDlg);
		return(0);
	case IDM_CLOSE:
		DialogBox (hInst, "CLOSE", hwnd, (DLGPROC)lpfnCloseDlg);
		return(0);
	}
	break;

	case WM_CREATE:
		lpfnTransferDlg = (FARPROC)MakeProcInstance((FARPROC)TransferDlg, hInst);
		lpfnDepositDlg = (FARPROC)MakeProcInstance((FARPROC)DepositDlg, hInst);
		lpfnWithdrawDlg = (FARPROC)MakeProcInstance((FARPROC)WithdrawDlg, hInst);
		lpfnBalanceDlg = (FARPROC)MakeProcInstance((FARPROC)BalanceDlg, hInst);
		lpfnCloseDlg = (FARPROC)MakeProcInstance((FARPROC)CloseDlg, hInst);
		lpfnOpenDlg = (FARPROC)MakeProcInstance((FARPROC)OpenDlg, hInst);
		lpfnUnsolptr=(FARPROC)MakeProcInstance((FARPROC)UnsolProc, hInst);

		if(tpsetunsol((_TM_UNSOL)lpfnUnsolptr) == TPUNSOLERR)
			userlog("tpsetunsol failed");

		return(0);
	case WM_DESTROY:
		PostQuitMessage (0);
		return(0);
	}
	return(DefWindowProc (hwnd, message, wParam, lParam));
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
	GetDlgItemText (hDlg, item, account, 40);
	for (i=0; account[i] != 0 && i <= 6; i++) {
		if (!isdigit(account[i]))
			break;
		acc_num = acc_num * 10 + (account[i] - '0');
	}
	if (i < 5 || i > 6 || account[i] != '\0') {
		/* SetDlgItemText (hDlg, item, ""); */
		MessageBox (hDlg,
			"Account number must be 5 or 6 digits",
			"BANKAPP", MB_OK);
		SetFocus(GetDlgItem(hDlg, item));
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
	GetDlgItemText (hDlg, item, amount, 40);
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
		/* SetDlgItemText (hDlg, item, ""); */
		MessageBox (hDlg,
			"Invalid money amount specified",
			"BANKAPP", MB_OK);
		SetFocus(GetDlgItem(hDlg, item));
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
	GetDlgItemText (hDlg, item, socsec, 40);
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
		/* SetDlgItemText (hDlg, item, ""); */
		MessageBox (hDlg,
			"Social security number must be in form nnn-nn-nnnn",
			"BANKAPP", MB_OK);
		SetFocus(GetDlgItem(hDlg, item));
		return(-1);
	}
	return(0);
}

static int
chk_phone(HWND hDlg, int item, char *phone)
{

	*phone = '\0';
	GetDlgItemText (hDlg, item, phone, 40);
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
		/* SetDlgItemText (hDlg, item, ""); */
		MessageBox (hDlg,
			"Phone number must be in form nnn-nnn-nnnn",
			"BANKAPP", MB_OK);
		SetFocus(GetDlgItem(hDlg, item));
		return(-1);
	}
	return(0);
}

chk_null(HWND hDlg, int item, char *value, char *warning)
{

	*value = '\0';
	GetDlgItemText (hDlg, item, value, 80);
	if (value[0] == '\0') {
		MessageBox (hDlg, warning, "BANKAPP", MB_OK);
		SetFocus(GetDlgItem(hDlg, item));
		return(-1);
	}
	return(0);
}
/* End of Field Validation Routines */


#ifdef noatmi
tpcall(char *service, char *bufi, long len, char **bufo, long *len2, long flags)
{
	FBFR FAR *fbfr;
	char bal[30];
	long l;
	FILE *fp;

	fbfr = (FBFR FAR *)bufi;

	fp = fopen("fbfr.out", "a+");
	fprintf(fp, "Service: %s\n", service);
	Ffprint(fbfr, fp);
	fprintf(fp, "\n\n");
	fclose(fp);

	Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
	lstrcpy(bal, "2030.20");
	Fchg(fbfr, SBALANCE, 0, bal, 0);
	lstrcpy(bal, "3050.75");
	Fchg(fbfr, SBALANCE, 1, bal, 0);
	l = 10000;
	Fchg(fbfr, ACCOUNT_ID, 0, (char FAR *)&l, 0);
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
BOOL FAR PASCAL
BalanceDlg(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
	char account1[120];
	long acc_num;
	long len;
	char FAR *s;

	switch (message) {
	case WM_INITDIALOG:
		lParam = lParam;
		return(TRUE);

	case WM_COMMAND:
#ifndef WIN32
	if(AEWisblocked() == 1)
		break;
#endif
	switch(wParam) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return(TRUE);

		Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char FAR *)&acc_num, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			lstrcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("INQUIRY", (char FAR *)fbfr, 0, (char FAR *FAR *)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr,STATLIN,0,0)) != 0) {
				lstrcpy(account1, s);
			}
			else
				lstrcpy(account1,"Inquiry failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				lstrcpy(account1, "Inquiry failed");
			}
			else
#endif
				
				wsprintf(account1, "Account Balance:  %s",
					(LPSTR) Ffind(fbfr, SBALANCE, 0, 0));
		}

		MessageBox (hDlg, account1, "BANKAPP", MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		EndDialog (hDlg, 0);
		return(TRUE);
	}
	break;
	}
	return(FALSE);
}

BOOL FAR PASCAL
CloseDlg(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
	char account1[120];
	long acc_num;
	long len;
	char FAR *s;

	switch (message) {
	case WM_INITDIALOG:
		lParam = lParam;
		return(TRUE);

	case WM_COMMAND:
#ifndef WIN32
	if(AEWisblocked() == 1)
		break;
#endif
	switch(wParam) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return(TRUE);

		Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char FAR *)&acc_num, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			lstrcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("CLOSE_ACCT", (char FAR *)fbfr, 0, (char FAR *FAR *)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr,STATLIN,0,0)) != 0) {
				lstrcpy(account1, s);
			}
			else
				lstrcpy(account1,"Close account failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				lstrcpy(account1, "Close account failed");
			}
			else
#endif
				wsprintf(account1, "Final Balance:  %s",
					(LPSTR) Ffind(fbfr, SBALANCE, 0, 0));
		}

		MessageBox (hDlg, account1, "BANKAPP", MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		EndDialog (hDlg, 0);
		return(TRUE);
	}
	break;
	}
	return(FALSE);
}

BOOL FAR PASCAL
DepositDlg(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
	char account1[120];
	char amount[40];
	long acc_num;
	long len;
	char FAR *s;

	switch (message) {
	case WM_INITDIALOG:
		lParam = lParam;
		return(TRUE);

	case WM_COMMAND:
#ifndef WIN32
	if(AEWisblocked() == 1)
		break;
#endif
	switch(wParam) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return(TRUE);

		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return(TRUE);

		Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char FAR *)&acc_num, 0);
		(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			lstrcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("DEPOSIT", (char FAR *)fbfr, 0, (char FAR *FAR *)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr,STATLIN,0,0)) != 0) {
				lstrcpy(account1, s);
			}
			else
				lstrcpy(account1,"Deposit failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				lstrcpy(account1, "Deposit failed");
			}
			else
#endif
				wsprintf(account1, "Account Balance:  %s",
					(LPSTR) Ffind(fbfr, SBALANCE, 0, 0));
		}

		MessageBox (hDlg, account1, "BANKAPP", MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		EndDialog (hDlg, 0);
		return(TRUE);
	}
	break;
	}
	return(FALSE);
}

BOOL FAR PASCAL
OpenDlg(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
	char FAR *s;
	char account1[120], amount[40];
	char firstname[80], lastname[80], midname[3], phone[20], street[80];
	char citystate[80], socsec[20];
	static int branch, accounttype;
	long acc_num, l;
	int i, ok;
	long len;

	switch (message) {
	case WM_INITDIALOG:
		lParam = lParam;
		branch = IDC_BRANCH1;
		SetFocus(GetDlgItem(hDlg, branch));
		accounttype = IDC_ACCOUNTTYPE1;
		SetFocus(GetDlgItem(hDlg, accounttype));
		SetFocus(GetDlgItem(hDlg, IDC_LASTNAME));
		return(TRUE);

	case WM_COMMAND:
#ifndef WIN32
	if(AEWisblocked() == 1)
		break;
#endif
	switch(wParam) {
	case IDOK:
		ok = 0;
		if(chk_null(hDlg, IDC_LASTNAME, lastname,
			"Please enter last name") < 0)
			return(TRUE);
		if(chk_null(hDlg, IDC_FIRSTNAME, firstname,
			"Please enter first name") < 0)
			return(TRUE);
		midname[0] = '\0';
		GetDlgItemText (hDlg, IDC_MIDNAME, midname, sizeof(midname));
		if(chk_phone(hDlg, IDC_PHONE, phone) < 0)
			return(TRUE);
		if(chk_null(hDlg, IDC_STREET, street,
			"Please enter street address") < 0)
			return(TRUE);
		if(chk_null(hDlg, IDC_CITYSTATE, citystate,
			"Please enter city, state, and zip") < 0)
			return(TRUE);
		if(chk_socsec(hDlg, IDC_SOCSEC, socsec) < 0)
			return(TRUE);
		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return(TRUE);
#ifndef noatmi
		if ((fbfr = (FBFR FAR *)tprealloc((char FAR *)fbfr, 512)) == NULL) {
			userlog("tprealloc failed");
			return(TRUE);
		}
#endif
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
		if (Fchg(fbfr, BRANCH_ID, 0, (char FAR *)&l, 0) < 0) {
			userlog("Fchg failed");
		}

#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			lstrcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("OPEN_ACCT", (char FAR *)fbfr, 0, (char FAR *FAR *)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr,STATLIN,0,0)) != 0) {
				lstrcpy(account1, s);
			}
			else
				lstrcpy(account1,"Open Account failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				lstrcpy(account1, "Open Account failed");
			}
			else
#endif
			{
				Fget(fbfr, ACCOUNT_ID, 0, (char FAR *)&acc_num, 0);
				wsprintf(account1,
				"Account Number:  %ld\nAccount Balance: %s",
					acc_num,
					(LPSTR) Ffind(fbfr, SBALANCE, 0, 0));
				ok = 1;
			}
		}
		MessageBox (hDlg, account1, "BANKAPP", MB_OK);
		if (!ok)
			break;
		/* FALL THRU */
	case IDCANCEL:
		EndDialog (hDlg, 0);
		return(TRUE);
	case IDC_ACCOUNTTYPE1:
	case IDC_ACCOUNTTYPE2:
		CheckRadioButton (hDlg, IDC_ACCOUNTTYPE1, IDC_ACCOUNTTYPE2,
			wParam);
		accounttype = wParam;
		return(TRUE);
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
		CheckRadioButton (hDlg, IDC_BRANCH1, IDC_BRANCH10, wParam);
		branch = wParam;
		return(TRUE);
	}
	break;
	}
	return(FALSE);
}

BOOL FAR PASCAL
TransferDlg(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
	char FAR *s;
	char account1[120];
	char account2[40];
	char amount[40];
	long acc_num1, acc_num2;
	long len;

	switch (message) {
	case WM_INITDIALOG:
		lParam = lParam;
		return(TRUE);

	case WM_COMMAND:
#ifndef WIN32
	if(AEWisblocked() == 1)
		break;
#endif
	switch(wParam) {
	case IDOK:
		if((acc_num1 = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return(TRUE);

		if((acc_num2 = chk_account(hDlg, IDC_ACCOUNT2, account2)) < 0)
			return(TRUE);

		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return(TRUE);

		Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char FAR *)&acc_num1, 0);
		(void) Fchg(fbfr, ACCOUNT_ID, 1, (char FAR *)&acc_num2, 0);
		(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			lstrcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("TRANSFER", (char FAR *)fbfr, 0, (char FAR *FAR *)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr,STATLIN,0,0)) != 0) {
				lstrcpy(account1, s);
			}
			else
				lstrcpy(account1,"Transfer failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				lstrcpy(account1, "Transfer failed");
			}
			else
#endif
				wsprintf(account1,
		"Debit Account Balance:  %s\nCredit Account Balance: %s",
					(LPSTR) Ffind(fbfr, SBALANCE, 0, 0),
					(LPSTR) Ffind(fbfr, SBALANCE, 1, 0));
		}

		MessageBox (hDlg, account1, "BANKAPP", MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		EndDialog (hDlg, 0);
		return(TRUE);
	}
	break;
	}
	return(FALSE);
}

BOOL FAR PASCAL
WithdrawDlg(HWND hDlg, WORD message, WORD wParam, LONG lParam)
{
	char FAR *s;
	char account1[120];
	char amount[40];
	long acc_num;
	long len;

	switch (message) {
	case WM_INITDIALOG:
		lParam = lParam;
		return(TRUE);

	case WM_COMMAND:
#ifndef WIN32
	if(AEWisblocked() == 1)
		break;
#endif
	switch(wParam) {
	case IDOK:
		if((acc_num = chk_account(hDlg, IDC_ACCOUNT1, account1)) < 0)
			return(TRUE);

		if(chk_amount(hDlg, IDC_AMOUNT, amount) < 0)
			return(TRUE);

		Finit(fbfr, (FLDLEN)Fsizeof(fbfr));
		(void) Fchg(fbfr, ACCOUNT_ID, 0, (char FAR *)&acc_num, 0);
		(void) Fchg(fbfr, SAMOUNT, 0, amount, 0);
#ifdef tran
		if (tpbegin(30, 0) == -1) {
			(void) userlog("failed to begin transaction\n");
			lstrcpy(account1, "Transaction failed");
		}
		else
#endif
		if (tpcall("WITHDRAWAL", (char FAR *)fbfr, 0, (char FAR *FAR *)&fbfr, &len, 0) == -1) {
			if(tperrno== TPESVCFAIL && fbfr != NULL &&
			    (s=Ffind(fbfr,STATLIN,0,0)) != 0) {
				lstrcpy(account1, s);
			}
			else
				lstrcpy(account1,"Withdrawal failed");
#ifdef tran
			(void) tpabort(0);
#endif
		}
		else {
#ifdef tran
			if(tpcommit(0) < 0) {
				lstrcpy(account1, "Withdrawal failed");
			}
			else
#endif
				wsprintf(account1, "Account Balance:  %s",
					(LPSTR) Ffind(fbfr, SBALANCE, 0, 0));
		}

		MessageBox (hDlg, account1, "BANKAPP", MB_OK);
		/* FALL THRU */
	case IDCANCEL:
		EndDialog (hDlg, 0);
		return(TRUE);
	}
	break;
	}
	return(FALSE);
}

void FAR PASCAL
UnsolProc(char FAR * inbuf, long len, long flags)
{
	char buftype[9];
	
	len = len; /* UNUSED */
	flags = flags; /* UNUSED */
	if(tptypes(inbuf, (char FAR *)buftype, NULL) == -1) {
		MessageBox(GetFocus(), "Cannot determine buffer type", "Unsolicited Message", MB_OK);
		return;
	}
	if(lstrcmp(buftype, "STRING") != 0) {
		MessageBox(GetFocus(), "Unsupported Buffer Type", "Unsolicited Message", MB_OK);
		return;
	}
	MessageBox(GetFocus(), inbuf, "Unsolicited Message", MB_OK);
	return;
}
