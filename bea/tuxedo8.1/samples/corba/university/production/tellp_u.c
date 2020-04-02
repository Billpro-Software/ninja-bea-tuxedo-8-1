/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	
 *	Copyright (c) 1997 BEA Systems, Inc.
 *	All rights reserved
 */
/* #ident	"@(#) samples/corba/university/production/tellp_u.c	$Revision: 1.4 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/corba/university/production/tellp_u.c	$Revision: 1.4 $";
#endif

#include <stdio.h>
#include <string.h>
#include <sqlca.h>
#include <sqlcode.h>
#include <time.h>
#ifdef WIN32
#include <conio.h>
#endif
#include "tellp_u.h"

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

