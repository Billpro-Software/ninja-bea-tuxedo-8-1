/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1994 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/bankapp/TOOLS/hostaddr.c	$Revision: 1.5 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) apps/bankapp/TOOLS/hostaddr.c	$Revision: 1.5 $";
#endif
#include <stdio.h>
#include <string.h>

main(argc, argv)
int	argc;
char	*argv[];
{
	FILE	*fd;
	char	s[512], *addr, *hname, *octet;
	int	i;

	if (argc != 2)
		exit(1);
	if ((fd = fopen("/etc/hosts", "r")) == NULL)
		exit(1);

	while (fgets(s, sizeof(s), fd)) {
		for (i=0; strchr(" \t", s[i]) != NULL ;i++)
			continue;
		if (strchr("#", s[i]) != NULL)
			continue;
		if ((addr = strtok(s, " \t")) == NULL)
			continue;
		if ((hname = strtok(NULL, " \t")) == NULL)
			continue;
		if (strcmp(hname, argv[1]) != 0)
			continue;
		octet = strtok(addr, ".");
		while (octet != NULL) {
			printf("%02x", atoi(octet) & 0xff);
			octet = strtok(NULL, ".");
		}
		printf("\n");
		exit(0);
	}
	exit(1);
}
