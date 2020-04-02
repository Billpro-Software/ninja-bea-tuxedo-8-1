/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1993 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* ident	"@(#) samples/atmi/rpcsimp/client.c	$Revision: 1.5 $" */
#include <stdio.h>
#include <string.h>
#include "simp.h"
#include "rpc/texc.h"
#include "atmi.h"

#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char **argv)
#else
main(argc, argv)
int argc;
char **argv;
#endif
{
	idl_char str[100];

	if (argc > 1) {/* use command line argument if it exists */
		(void) strncpy((char *)str, argv[1], 100);
		str[99] = '\0';
	}
	else
		(void) strcpy((char *)str, "Hello, world");
#ifndef TMDCE
	if (tpinit(NULL) == -1) {
		fprintf(stdout, "tpinit failed\n");
		exit(1);
	}
#endif

	TRY
	to_upper(str);
	(void) fprintf(stdout, "to_upper returns: %s\n", str);
	to_lower(str);
	(void) fprintf(stdout, "to_lower returns: %s\n", str);
	/* control flow continues after ENDTRY */
	CATCH_ALL
		exc_report(THIS_CATCH); /* print to stderr */
#ifndef TMDCE
		(void) tpterm();
#endif
		exit(1);
	ENDTRY

#ifndef TMDCE
	(void) tpterm();
#endif
	exit(0);
}
