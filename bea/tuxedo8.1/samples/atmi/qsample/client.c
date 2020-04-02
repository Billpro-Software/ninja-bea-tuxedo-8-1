/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1999 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*      Copyright (c) 1999 BEA Systems, Inc.
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
        SOURCE CODE OF USL
        The copyright notice above does not
        evidence any actual or intended
        publication of such source code.
*/

/* #ident	"@(#) samples/atmi/qsample/client.c	$Revision: 1.5 $" */

#include <stdio.h>
#include "Uunix.h"
#include "atmi.h"

int
main()
{
	char *reqstr;	/* string to be sent */
	long len;	/* length of return string */
	TPQCTL qctl;	/* Q control structures */

	/* join the application */
        if (tpinit(NULL) == -1) {
		(void) fprintf(stderr,"failed to join application: %s\n",
			tpstrerror(tperrno));
                exit(1);
        }

	/* get request buffer */
	if ((reqstr = tpalloc("STRING",NULL,100))==NULL){
		(void) fprintf(stderr,"unable to allocate STRING buffer: %s",
			tpstrerror(tperrno));
		exit(1);
	}
	(void) strcpy(reqstr,"this is a q example");
	(void) printf("before: %s\n", reqstr);

	/* set flag in control structure indicating a reply queue */
	qctl.flags = TPQREPLYQ;

	/* provide name of reply queue in control structure */
	(void) strcpy(qctl.replyqueue, "RPLYQ");

#ifdef TPQDELIVERYQOS
	/* Tuxedo 7.1 or later */
	qctl.flags |= TPQDELIVERYQOS;/* specify delivery quality of service */

	/* non-persistent */
	qctl.delivery_qos = TPQQOSNONPERSISTENT;
#endif

	if (tpenqueue("QSPACE", "STRING", (TPQCTL *)&qctl,(char *)reqstr,
		0, 0) == -1) {
		(void) fprintf(stderr,"Failure to enqueue STRING service: %s\n",
			tpstrerror(tperrno));
		if (tperrno == TPEDIAGNOSTIC) {
			(void) fprintf(stderr,"Queue manager diagnostic %ld\n",
				qctl.diagnostic);
		}
		tpfree((char *)reqstr);
		(void) tpterm();
		exit(1);
	}

	/* set flag indicating we will wait for a reply */
	qctl.flags = TPQWAIT;
	if (tpdequeue("QSPACE", "RPLYQ", (TPQCTL *)&qctl, (char **)&reqstr,
		&len, TPNOTIME) == -1) {
		(void) fprintf(stderr,"Failure to dequeue STRING service: %s\n",
			tpstrerror(tperrno));
		if (tperrno == TPEDIAGNOSTIC) {
			(void) fprintf(stderr,"Queue manager diagnostic %ld\n",
				qctl.diagnostic);
		}
		tpfree(reqstr);
		(void) tpterm();
		exit(1);
	}
	(void) printf("after: %s\n",reqstr);
	/* clean up and exit */
	tpfree(reqstr);
	(void) tpterm();
	return(0);
}
