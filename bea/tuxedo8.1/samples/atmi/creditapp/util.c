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
#ident	"@(#) samples/atmi/creditapp/util.c	$Revision: 1.5 $"
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/creditapp/util.c	$Revision: 1.5 $";
#endif

#include <stdio.h>
#include <string.h>
#include <sqlca.h>
#include <sqlcode.h>
#include "bank.h"

static char errmsg[STATLEN];

char *
#if defined(__STDC__) || defined(__cplusplus)
getstr(char *str, long sqlnum)

#else

getstr(str, sqlnum)
char *str;
long sqlnum;
#endif

{
	switch (sqlnum) {
	case SQLNOTFOUND:
		(void)strcpy(errmsg,"Invalid ");
		(void)strcat(errmsg,str);
		(void)strcat(errmsg," number");
		break;
	case QLDEADLOCK:
		(void)strcpy(errmsg,str);
		(void)strcat(errmsg," busy try again");
		break;
	default:
		(void)strcpy(errmsg,"Database access error");
	}
	return(errmsg);
}
