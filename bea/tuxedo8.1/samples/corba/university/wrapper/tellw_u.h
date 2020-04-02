/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
#ifndef _TELLW_U_H
#define	_TELLW_U_H

#define MINACCT         100000  	/* smallest account number */
#define MAXACCT         999999		/* largest account number  */

#define STATLEN  80      /* length of string for status line */

char     * getstr _((char *, long));

long	SQLCODE;

#endif
