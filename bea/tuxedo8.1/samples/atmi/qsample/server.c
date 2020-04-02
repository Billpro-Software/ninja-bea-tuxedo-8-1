/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*      Copyright (c) 1992 USL
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
        SOURCE CODE OF USL
        The copyright notice above does not
        evidence any actual or intended
        publication of such source code.
*/

/* #ident	"@(#) samples/atmi/qsample/server.c	$Revision: 1.5 $" */

#include <stdio.h>
#include <ctype.h>
#include "atmi.h"

STRING(msg)
TPSVCINFO *msg;
{
	char *str;
	int i;

	/* set pointer to data portion of message */
	str = (char *)msg->data;

	/* convert string to upper case */
	for (i = 0; i < msg->len; i++) {
		str[i] = toupper(str[i]);
	}
	tpreturn(TPSUCCESS, 0, msg->data, 0L, 0);
}
