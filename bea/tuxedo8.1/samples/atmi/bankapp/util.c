/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1990 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/bankapp/util.c	$Revision: 1.5 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) samples/atmi/bankapp/util.c	$Revision: 1.5 $";
#endif

#include <stdio.h>
#include <string.h>
#include <sqlca.h>
#include <sqlcode.h>
#include <time.h>
#ifdef WIN32
#include <conio.h>
#endif
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



char *
#if defined(__STDC__) || defined(__cplusplus)
gettime (void)

#else

gettime ()
#endif

{
    time_t	clk_ticks ;
    char *	timestr = NULL ;

    clk_ticks = time ((time_t) 0) ;	/* get # sec since Jan 1, 1970 */
    timestr = ctime (&clk_ticks) ;	/* conv to date-time text string */
    (void)strtok (timestr, "\n") ;   		/* delete the '\n'  char */

    return timestr ;
}



#ifdef WIN32

#include <conio.h>
// Get the password for security from the console.

#define  MAXPASSLEN	8

char *
getpass(const char *prompt)
{
	char	*p;
	int	c;
	static char  passwd[MAXPASSLEN+1];

	(void) fputs(prompt, stderr);
	for(p=passwd; (c = getch()) != '\r' && c != EOF; ) {
		if(p < &passwd[MAXPASSLEN])
			*p++ = (char)c;
	}
	*p = '\0';
	(void) putc('\n', stderr);
	return(passwd);
}
#endif
