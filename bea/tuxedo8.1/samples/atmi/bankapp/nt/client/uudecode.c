/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1995 Novell, Inc.	*/
/*	  All Rights Reserved 	 	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	Novell, Inc.                     			*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/* #ident	"@(#) samples/atmi/bankapp/nt/client/uudecode.c	$Revision: 1.4 $"	*/

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/client/uudecode.c	$Revision: 1.4 $";
#endif

/*
 * uudecode [input]
 *
 * create the specified file, decoding as you go.
 * used with uuencode.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

/* single character decode */
#define DEC(c)	(((c) - ' ') & 077)

static void decode(FILE *in, FILE *out);
static void outdec(unsigned char *p, FILE *f, int n);
static char *index(register char *sp, register char c);

main(int argc, char **argv)
{
	FILE *in, *out;
	long mode;
	char dest[128];
	char buf[80];

	/* optional input arg */
	if (argc > 1) {
		if ((in = fopen(argv[1], "r")) == NULL) {
			perror(argv[1]);
			return(1);
		}
		argv++; argc--;
	} else
		in = stdin;

	if (argc != 1) {
		(void)printf("Usage: uudecode [infile]\n");
		return(2);
	}

	/* search for header line */
	for (;;) {
		if (fgets(buf, sizeof buf, in) == NULL) {
			(void)fprintf(stderr, "No begin line\n");
			return(3);
		}
		if (strncmp(buf, "begin ", 6) == 0)
			break;
	}
	(void)sscanf(buf, "begin %lo %s", &mode, dest);


	/* create output file */
	out = fopen(dest, "w");
	if (out == NULL) {
		perror(dest);
		return(4);
	}
	/* (void)chmod(dest, mode); */

	decode(in, out);

	if (fgets(buf, sizeof buf, in) == NULL || strcmp(buf, "end\n")) {
		(void)fprintf(stderr, "No end line\n");
		return(5);
	}
	return(0);
}

/*
 * copy from in to out, decoding as you go along.
 */
static void
decode(FILE *in, FILE *out)
{
	unsigned char buf[80];
	unsigned char *bp;
	int n;

	for (;;) {
		/* for each input line */
		if (fgets(buf, sizeof buf, in) == NULL) {
			(void)printf("Short file\n");
			exit(10);
		}
		n = DEC(buf[0]);
		if (n <= 0)
			break;

		bp = &buf[1];
		while (n > 0) {
			outdec(bp, out, n);
			bp += 4;
			n -= 3;
		}
	}
	return;
}

/*
 * output a group of 3 bytes (4 input characters).
 * the input chars are pointed to by p, they are to
 * be output to file f.  n is used to tell us not to
 * output all of them at the end of the file.
 */
static void
outdec(unsigned char *p, FILE *f, int n)
{
	int c1, c2, c3;

	c1 = DEC(*p) << 2 | DEC(p[1]) >> 4;
	c2 = DEC(p[1]) << 4 | DEC(p[2]) >> 2;
	c3 = DEC(p[2]) << 6 | DEC(p[3]);
	if (n >= 1)
		(void)putc(c1, f);
	if (n >= 2)
		(void)putc(c2, f);
	if (n >= 3)
		(void)putc(c3, f);
	return;
}


/* fr: like read but stdio */
int
fr(FILE *fd, char *buf, int cnt)
{
	int c, i;

	for (i=0; i<cnt; i++) {
		c = getc(fd);
		if (c == EOF)
			return(i);
		buf[i] = c;
	}
	return (cnt);
}

/*
 * Return the ptr in sp at which the character c appears;
 * NULL if not found
 */

static char *
index(register char *sp, register char c)
{
	do {
		if (*sp == c)
			return(sp);
	} while (*sp++);
	return(NULL);
}
