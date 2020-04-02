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
/* #ident	"@(#) samples/atmi/bankapp/TOOLS/tlcmd.c	$Revision: 1.5 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) apps/bankapp/TOOLS/tlcmd.c	$Revision: 1.5 $";
#endif
#include <stdio.h>
#include <string.h>

main(argc, argv)
int	argc;
char	*argv[];
{
	FILE	*pfd;
	char	rootdir[512];
	char	appdir[512];
	char	lmid[512];
	char	nlsaddr[512];
	char	bridge[512];
	char	s[512];
	char	*ptr;
	char	*filename;

	rootdir[0]='\0';
	appdir[0]='\0';
	lmid[0]='\0';
	nlsaddr[0]='\0';
	bridge[0]='\0';

	if (argc != 2)
		exit(1);
	
	filename = tmpnam(NULL);
	(void) sprintf(s, "tmunloadcf > %s", filename);
	(void) system(s);
	if ((pfd = fopen(filename, "r")) == NULL) {
		(void) unlink(filename);
		exit(1);
	}

	/*
	 * Find the LMID for this machine.
	 */
	while (fgets(s, sizeof(s), pfd)) {
		if (strcmp(s,"*MACHINES\n") != 0)
			continue;
		while (fgets(s, sizeof(s), pfd)) {
			if (s[0] == '*')
				break;
			if (s[0] != '"')
				continue;
			ptr = strtok(s, "\" \t=\n");	/* match pmid */
			if (strcmp(ptr, argv[1]) != 0)
				continue;
			ptr = strtok(NULL, "\" \t=\n");	/* match LMID */
			ptr = strtok(NULL, "\" \t=\n");	/* match LMID val */
			strcpy(lmid, ptr);
			break;
		}
		if (lmid[0] == '\0') {
			fclose(pfd);
			unlink(filename);
			exit(1);
		}
		break;
	}
	if (lmid[0] == '\0') {
		fclose(pfd);
		unlink(filename);
		exit(1);
	}

	/*
	 * Now find the TUXDIR for this machine.
	 */
	while (fgets(s, sizeof(s), pfd)) {
		if (s[0] != '\t')
			break;
		ptr = strtok(s, "\" \t=\n");	/* match TUXDIR */
		if (strcmp(ptr, "TUXDIR") != 0)
			continue;
		ptr = strtok(NULL, "\" \t=\n");	/* match TUXDIR val */
		strcpy(rootdir, ptr);
		break;
	}

	if (rootdir[0] == '\0') {
		fclose(pfd);
		unlink(filename);
		exit(1);
	}

	/*
	 * Now find the APPDIR for this machine.
	 */
	while (fgets(s, sizeof(s), pfd)) {
		if (s[0] != '\t')
			break;
		ptr = strtok(s, "\" \t=\n");	/* match APPDIR */
		if (strcmp(ptr, "APPDIR") != 0)
			continue;
		ptr = strtok(NULL, "\" \t=\n");	/* match APPDIR val */
		strcpy(appdir, ptr);
		break;
	}

	if (appdir[0] == '\0') {
		fclose(pfd);
		unlink(filename);
		exit(1);
	}

	while (fgets(s, sizeof(s), pfd)) {
		if (strcmp(s,"*NETWORK\n") != 0)
			continue;
		while (fgets(s, sizeof(s), pfd)) {
			if (s[0] == '*')
				break;
			if (s[0] != '"')
				continue;
			ptr = strtok(s, "\" \t=\n");	/* match lmid */
			if (strcmp(ptr, lmid) != 0)
				continue;
			while (fgets(s, sizeof(s), pfd)) {
				if (s[0] != '\t')
					break;
				ptr = strtok(s, "\" \t=\n");	/* match tag */
				if (strcmp(ptr, "BRIDGE") == 0) {
					ptr = strtok(NULL, "\" \t=\n");
					strcpy(bridge, ptr);
				} else if (strcmp(ptr, "NLSADDR") == 0) {
					ptr = strtok(NULL, "\" \t=\n");
					strcpy(nlsaddr, ptr);
				}
			}
			break;
		}
		break;
	}

	fclose(pfd);
	unlink(filename);
	if (nlsaddr[0] == '\0') {
		exit(1);
	}

	printf("export TUXDIR LD_LIBRARY_PATH SHLIB_PATH LIBPATH ULOGPFX\n");
	printf("TUXDIR=%s\n", rootdir);
	printf("LD_LIBRARY_PATH=%s/lib\n", rootdir);
	printf("SHLIB_PATH=%s/lib\n", rootdir);
	printf("LIBPATH=%s/lib\n", rootdir);
	printf("ULOGPFX=%s/TLLOG\n", appdir);
	printf("%s/bin/tlisten -l %s ", rootdir, nlsaddr);
	if (bridge[0] != '\0')
		printf("-d %s ", bridge);
	printf("\n");
	exit(0);
}
