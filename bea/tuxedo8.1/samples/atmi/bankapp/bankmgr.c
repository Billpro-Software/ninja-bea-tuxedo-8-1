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
/* #ident	"@(#) samples/atmi/bankapp/bankmgr.c	$Revision: 1.5 $" */

#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/bankmgr.c	$Revision: 1.5 $";
#endif

/*
 * This is a continuously running client program which subscribes to two
 * events. One event is BANK_TLR_WITHDRAWAL with notification via an
 * unsolicited messages handler. This event is posted in the service 
 * WITHDRAWAL. The other event is BANK_CTR_OPENACCT with notification via an
 * application queue using the /Q component. This event is posted in the
 * service OPEN_ACCT.
 * An endless loop polls for events and prints them on stdout when received.
 */

#include <stdio.h>		/* UNIX */
#include <string.h>		/* UNIX */
#include <signal.h>		/* UNIX */
#include <ctype.h>		/* UNIX */
#ifdef _TMFML32
#include <fml32.h>		/* TUXEDO */
#include <fml1632.h>		/* TUXEDO */
#else
#include <fml.h>		/* TUXEDO */
#endif
#include <atmi.h>		/* TUXEDO */
#include <Uunix.h>		/* TUXEDO */
#include <Usignal.h>		/* TUXEDO */
#include <userlog.h>		/* TUXEDO */
#include "bank.h"		/* BANKING #defines */
#include "bankflds.h"		/* Bank */
#include "eventflds.h"		/* Events */

#ifdef WIN32
extern int sleep _((unsigned));
#endif

#ifdef _as400_
extern char *getpass _((const char *prompt));
#endif

/* Define TRUE and FALSE */

#ifdef TRUE
#undef TRUE
#endif
#define TRUE	1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE	0

static long sub_ev_withdraw = 0L ; 	/* event subscription handle */
static long sub_ev_newacct = 0L ;	/* ---------- " ------------ */
static int  f_sig_recvd ;	/* flag indicating that the signal was rcvd */

/* Handler for unsolicited messages (events) */
static void _TMDLLENTRY unsol_evhndlr _((char *, long, long)) ;

/* Signal handler for SIGINT & SIGTERM signals */ 
static USIGTYP prockill_handler _((int)) ;	/* See Usignal.h */


#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char *argv[])

#else

main(argc, argv)
int argc;
char *argv[];
#endif

{

int	c;		/* option character */
char	*eventexpr ;	/* option arg for option -e */
char	*filter ;	/* option arg for option -f */
TPINIT	*tpinitbuf ;	/* tpalloc'd pointer */
int	auth ;		/* authentication level */
TPEVCTL	evctl ;		/* event control struct */
TPQCTL	qctl ;		/* queue control struct */
char	*deq_buf ;	/* tpalloc'd buffer to dequeue a Q message */
long	deq_buflen ;	/* len of dequeued message */
char	*passwd ;	/* passwd obtained from user */

    /* Set 'proc_name' to identify client by name in the ULOG */

    if (strrchr(argv[0],'/') != NULL)
	    proc_name = strrchr(argv[0],'/')+1;
    else
	    proc_name = argv[0];

    /* Set up defaults  for options (-e, -f) */

    eventexpr = "BANK_TLR_WITHDRAWAL" ;		/* default for option -e */
    filter = "AMOUNT > 10000.00" ;		/* default for option -f */

    /* If no options were specified, use defaults */

    if (argc == 1) {
	(void)fprintf(stdout, "%s: Usage: %s [-e eventexpr [-f filter]]\n",
			      proc_name, proc_name);

	(void)fprintf(stdout, "%s: Using defaults: %s -e '%s' -f '%s'\n",
			      proc_name, proc_name,
			      eventexpr,
			      (filter ? filter : "(null)" )) ;
    }

    /* Process any command line options if specified */

    while((c = getopt(argc,argv,"e:f:")) != EOF) {
	switch((char)c) {
	    case 'e':
		eventexpr = optarg ;
		if (eventexpr == NULL)
		    (void)fprintf(stderr, "%s: Usage: %s [-e eventexpr [-f filter]]\n",
					  proc_name, proc_name);
		break ;

	    case 'f':
		filter = optarg ;
		break;

	    default:
		(void)fprintf(stderr, "%s: Usage: %s [-e eventexpr [-f filter]]\n",
				      proc_name, proc_name);
		return 1 ;
	}
    }

    /* Alloc a TPINIT buffer for identification purposes.
     * This is not mandatory if no authentication is configured
     */

    tpinitbuf = (TPINIT *) tpalloc("TPINIT", NULL, TPINITNEED(16)) ;

    if (tpinitbuf == (TPINIT *) NULL) {
	(void)fprintf(stderr, "ERROR: Failed for TPINIT buffer, %s\n",
				tpstrerror(tperrno));
	(void)userlog("ERROR: Failed for TPINIT buffer, %s",
				tpstrerror(tperrno));
	return 2 ;
    }

    /* Check the type of authentication the appl is configured for
     * and populate TPINIT buffer with authentication info.
     */

    switch (auth = tpchkauth()) {
	case TPNOAUTH :
		(void)strcpy (tpinitbuf->usrname, argv[0]) ;
		(void)strcpy (tpinitbuf->passwd, "") ;
		(void)strcpy (tpinitbuf->cltname, "tpsysadm") ;
		break ;

	case TPSYSAUTH :
	case TPAPPAUTH :
		if ((passwd = getpass("Application Password:")) == NULL) {
		    (void)userlog ("ERROR: Unable to get Application Password");
		    return 3 ;
		}
		(void)strcpy (tpinitbuf->passwd, passwd) ;
		(void)strcpy (tpinitbuf->cltname, "tpsysadm") ;

		if (auth == TPSYSAUTH)
		    break ;

		(void)printf ("User Name:") ;
		(void)gets (tpinitbuf->usrname) ;
		(void)strcpy (tpinitbuf->grpname, "") ;

		if ((passwd = getpass("User Password:")) == NULL) {
		    (void)userlog ("ERROR: Unable to get User Password");
		    return 4 ;
		}
		(void)strcpy ((char *) &tpinitbuf->data, passwd) ;

		tpinitbuf->datalen = strlen ((char *) &tpinitbuf->data)+1L;
		break ;
    }

    /* Join application */

    if (tpinit(tpinitbuf) == -1) {
	(void)fprintf(stderr, "ERROR: Failed to join application, %s\n",
				tpstrerror(tperrno));
	(void)userlog("ERROR: Failed to join application, %s",
				tpstrerror(tperrno));
	return 5 ;
    }

    /* the tpinitbuf is no longer needed and may be freed */
    tpfree ((char *) tpinitbuf) ;

    /* Prepare to Subscribe to event eventexpr. (default BANK_TLR_WITHDRAWAL)
     * Bank manager would like to be notified in case of large withdrawals.
     */

    /* Set the unsolicited message handler for the event */

    if (tpsetunsol ((void (_TMDLLENTRY *) _((char *, long, long))) unsol_evhndlr) == TPUNSOLERR) {
	(void)fprintf (stderr, "ERROR: tpsetunsol failed: %s\n",
				 tpstrerror (tperrno)) ;
	(void)userlog ("ERROR: tpsetunsol failed: %s", tpstrerror(tperrno));
	tpterm () ;
	return 6 ;
    }

    /* Subscribe to event eventexpr
     * requesting notification via an unsolicited  message handler
     */

    sub_ev_withdraw = tpsubscribe ( eventexpr,
				    filter,
				    (TPEVCTL *)NULL,
				    TPSIGRSTRT) ;
    if (sub_ev_withdraw == -1L) {
	(void)fprintf (stderr, "ERROR: tpsubscribe for event %s failed: %s\n",
				eventexpr, tpstrerror(tperrno)) ;
	(void)userlog ("ERROR: tpsubscribe for event %s failed: %s",
				eventexpr, tpstrerror(tperrno)) ;
	tpterm () ;
	return 7 ;
    }
    else
	(void)fprintf (stdout, "INFO: Subscribed to event '%s'\n", eventexpr) ;


    /* Prepare to subscribe to event BANK_CTR_OPENACCT.
     * Bank manager would like to give special treatment to customers
     * who maintain large accounts.
     */

    evctl.flags = TPEVQUEUE ;
    (void)strcpy (evctl.name1, "QSP_BANKAPP") ;
    (void)strcpy (evctl.name2, "Q_OPENACCT") ;
    evctl.qctl.flags = TPQFAILUREQ | TPQCORRID | TPQPRIORITY ;
    (void)strcpy (evctl.qctl.failurequeue, "Q_ERROR") ;

    (void)memset (evctl.qctl.corrid, (int)'\0', (size_t)TMCORRIDLEN) ;
    (void)strcpy (evctl.qctl.corrid, "BANKMGR") ;

    evctl.qctl.priority = 10L ;

    /* Subscribe to event BANK_CTR_OPENACCT
     * requesting notification via an application queue.
     */

    sub_ev_newacct = tpsubscribe ("BANK_CTR_OPENACCT",
				    "AMOUNT > 10000.00",
				    &evctl,
				    TPSIGRSTRT) ;

    if (sub_ev_newacct == -1L) {
	(void)fprintf (stderr, "ERROR: tpsubscribe for event BANK_CTR_OPENACCT failed: %s\n",
				tpstrerror(tperrno)) ;
	(void)userlog ("ERROR: tpsubscribe for event BANK_CTR_OPENACCT failed: %s",
				tpstrerror(tperrno)) ;
	tpterm () ;
	return 8 ;
    }
	(void)fprintf (stdout, "INFO: Subscribed to event 'BANK_CTR_OPENACCT'\n") ;

    /* Catch SIGINT and SIGTERM signals */

    if ((Usignal (SIGINT,  (USIGTYP (*) _((int))) prockill_handler) == SIG_ERR) ||
	(Usignal (SIGTERM, (USIGTYP (*) _((int))) prockill_handler) == SIG_ERR)) {
	perror ("ERROR: Usignal() failed") ;

	/* unsubscribe the subscribed events (clean up) before exit */

	if (tpunsubscribe (sub_ev_withdraw, TPSIGRSTRT) == -1) {
	    (void)fprintf (stderr, "ERROR: tpunsubscribe failed for %s: %s\n",
			    eventexpr, tpstrerror (tperrno));
	    (void)userlog ("ERROR: tpunsubscribe failed for %s: %s",
			    eventexpr, tpstrerror (tperrno));
	}

	if (tpunsubscribe (sub_ev_newacct, TPSIGRSTRT) == -1) {
	    (void)fprintf (stderr, "ERROR: tpunsubscribe failed for BANK_CTR_OPENACCT: %s\n",
			    tpstrerror (tperrno));
	    (void)userlog ("ERROR: tpunsubscribe failed for BANK_CTR_OPENACCT: %s",
			    tpstrerror (tperrno));
	}
	(void)tpterm () ;
	return 9 ;
    }

    /* set up the application Q dequeuing parameters */

    qctl.flags = TPQGETBYCORRID ;
    (void)memset (qctl.corrid, (int)'\0', (size_t)TMCORRIDLEN) ;
    (void)strcpy (qctl.corrid, "BANKMGR") ;

    /* tpalloc a buffer to dequeue data */

    deq_buf = tpalloc ("FML", NULL, 1024) ;
    if (deq_buf == (char *) NULL) {
	(void)fprintf(stderr, "ERROR: tpalloc failed for dequeue buffer, %s\n",
				tpstrerror(tperrno));
	(void)userlog("ERROR: tpalloc failed for dequeue buffer, %s",
				tpstrerror(tperrno));

	/* unsubscribe the subscribed events (clean up) before exit */

	if (tpunsubscribe (sub_ev_withdraw, TPSIGRSTRT) == -1) {
	    (void)fprintf (stderr, "ERROR: tpunsubscribe failed for %s: %s\n",
			    eventexpr, tpstrerror (tperrno));
	    (void)userlog ("ERROR: tpunsubscribe failed for %s: %s",
			    eventexpr, tpstrerror (tperrno));
	}

	if (tpunsubscribe (sub_ev_newacct, TPSIGRSTRT) == -1) {
	    (void)fprintf (stderr, "ERROR: tpunsubscribe failed for BANK_CTR_OPENACCT: %s\n",
			    tpstrerror (tperrno));
	    (void)userlog ("ERROR: tpunsubscribe failed for BANK_CTR_OPENACCT: %s",
			    tpstrerror (tperrno));
	}

	tpterm () ;
	return 10 ;
    }
	
    f_sig_recvd = FALSE;	/* loop condition */

    /* Loop checking for messages */

    while (f_sig_recvd == FALSE) {
	/*
	 * Check for any unsolicited messages. Actually this is needed only
	 * if notification method configured is DIPIN notification.
	 */
	if (tpchkunsol () == -1) {
	    (void)fprintf (stderr, "ERROR: tpchkunsol failed: %s\n",
				    tpstrerror(tperrno)) ;
	    (void)userlog ("ERROR: tpchkunsol failed: %s", tpstrerror(tperrno));
	}

	/*
	 * check the application queue for messages. If the error is due
	 * to Q being empty, ignore the error.
	 */
	if (tpdequeue ("QSP_BANKAPP", "Q_OPENACCT", &qctl, &deq_buf,
		       &deq_buflen, TPSIGRSTRT) == -1) {
	    if (tperrno == TPEDIAGNOSTIC) {
		if (qctl.diagnostic != QMENOMSG) {
		    (void)fprintf (stderr, "ERROR: tpdequeue failed, qctl diagnostic: %ld\n",
					    qctl.diagnostic) ;
		    (void)userlog ("ERROR: tpdequeue failed, qctl diagnostic: %ld",
					    qctl.diagnostic) ;
		}
	    }
	    else {
		(void)fprintf (stderr, "ERROR: tpdequeue failed: %s\n",
					tpstrerror(tperrno));
		(void)userlog ("ERROR: tpdequeue failed: %s",
					tpstrerror(tperrno)) ;
	    }
	}
	else {
	    (void)fprintf (stdout, "%20s|%28s|%8ld|%10.2f\n",
			    Fvals ((FBFR *)deq_buf, EVENT_NAME, 0),
			    Fvals ((FBFR *)deq_buf, EVENT_TIME, 0),
			    Fvall ((FBFR *)deq_buf, ACCOUNT_ID, 0),
			    *( (float *)CFfind ((FBFR *)deq_buf,
						AMOUNT, 0, NULL, FLD_FLOAT)) );
	}

	(void)sleep (5) ;

    } /* while */

    /* Free the dequeue buffer */
    tpfree (deq_buf) ;

    /* Unsubscribe to the subscribed events */

    if (tpunsubscribe (sub_ev_withdraw, TPSIGRSTRT) == -1) {
	(void)fprintf (stderr, "ERROR: tpunsubscribe failed for %s: %s\n",
			eventexpr, tpstrerror (tperrno));
	(void)userlog ("ERROR: tpunsubscribe failed for %s: %s",
			eventexpr, tpstrerror (tperrno));
    }
    else
	(void)fprintf (stdout, "INFO: UnSubscribed to event %s\n", eventexpr) ;

    if (tpunsubscribe (sub_ev_newacct, TPSIGRSTRT) == -1) {
	(void)fprintf (stderr, "ERROR: tpunsubscribe failed for BANK_CTR_OPENACCT: %s\n",
			tpstrerror (tperrno));
	(void)userlog ("ERROR: tpunsubscribe failed for BANK_CTR_OPENACCT: %s",
			tpstrerror (tperrno));
    }
    else
	(void)fprintf (stdout, "INFO: UnSubscribed to event BANK_CTR_OPENACCT\n") ;

    /* Leave application */

    tpterm() ;

    return 0 ;
}


/* ARGSUSED */

static USIGTYP
#if defined(__STDC__) || defined(__cplusplus)
prockill_handler (int sig)

#else

prockill_handler (sig)
int sig;
#endif

{
    f_sig_recvd = TRUE;	    /* flag indicating that the signal was recvd */

    return ;
}



/* ARGSUSED */

static void
_TMDLLENTRY
#if defined(__STDC__) || defined(__cplusplus)
unsol_evhndlr (char *data, long len, long flags)

#else

unsol_evhndlr (data, len, flags)
char *data ;
long len ;
long flags ;
#endif

{
    (void)fprintf (stdout, "%20s|%28s|%8ld|%10.2f\n",
			    Fvals ((FBFR *)data, EVENT_NAME, 0),
			    Fvals ((FBFR *)data, EVENT_TIME, 0),
			    Fvall ((FBFR *)data, ACCOUNT_ID, 0),
	    *( (float *)CFfind ((FBFR *)data, AMOUNT, 0, NULL, FLD_FLOAT)) );

    return ;
}

#ifdef _as400_
#define MAXPASSWDLEN 32
extern char *_gets_hidden(char *, int);

char *
getpass(const char *prompt)
{
	static char passwd[MAXPASSWDLEN];

	fprintf(stderr, "%s\n", prompt);
	return _gets_hidden(passwd, sizeof(passwd));
}
#endif
