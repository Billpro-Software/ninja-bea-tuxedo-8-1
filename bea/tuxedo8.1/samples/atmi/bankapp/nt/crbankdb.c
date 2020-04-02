/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*      Copyright (c) 1996 BEA Systems, Inc.
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
        SOURCE CODE OF BEA Systems, Inc.
        The copyright notice above does not
        evidence any actual or intended
        publication of such source code.
*/

/* #ident	"@(#) samples/atmi/bankapp/nt/crbankdb.c	$Revision: 1.4 $" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <Uunix.h>

void
main()
{
	char *fsconfig;
	char *dbname;
	char *dipckey;
	char *blksize;
	
	FILE *fd;
	int exitcode;

	fsconfig = tuxgetenv("FSCONFIG");

	if (!fsconfig){
		(void) fprintf(stderr, "Missing FSCONFIG in environment\n");
		exit(1);
	}

	dbname = tuxgetenv("DBNAME");

	if (!dbname){
		(void) fprintf(stderr, "Missing DBNAME in environment\n");
		exit(1);
	}

	dipckey = tuxgetenv("DIPCKEY");

	if (!dipckey){
		(void) fprintf(stderr, "Missing DIPCKEY in environment\n");
		exit(1);
	}
	
	blksize = tuxgetenv("BLKSIZE");

	if (!blksize){
		(void) fprintf(stderr, "Missing BLKSIZE in environment\n");
		exit(1);
	}

	fd = _popen("tmadmin -c", "wt");

	if (!fd){
		(void) fprintf(stderr, "Cannot start tmadmin: %s\n", strerror(errno));
		exit(1);
	}

	fprintf(fd, "crdl -z %s -b 30000\n", fsconfig);

	exitcode = _pclose(fd);

	if (exitcode != 0){
		(void) fprintf(stderr, "tmadmin failed to create device list.\n");
		exit(1);
	}

	fd = _popen("sql", "wt");
	if (!fd){
		(void) fprintf(stderr, "Cannot start sql: %s\n", strerror(errno));
		exit(1);
	}
	(void) fprintf(fd, "\\echo\n");
	(void) fprintf(fd, "create database %s with (	DEVNAME='%s'\n,", dbname,
		fsconfig);
	(void) fprintf(fd, "\tIPCKEY=%s,		LOGBLOCKING=0,	MAXDEV=1,\n",
		dipckey);
	(void) fprintf(fd, "\tNBLKTBL=200,	NBLOCKS=2048,	NBUF=70,	NFIELDS=80,\n");
	(void) fprintf(fd, "\tNFILES=20,	NFLDNAMES=60,	NFREEPART=40,	NLCKTBL=200,\n");
	(void) fprintf(fd, "\tNLINKS=80,	NPREDS=10,	NPROCTBL=20,	NSKEYS=20,\n");
	(void) fprintf(fd, "\tNSWAP=50,	NTABLES=20,	NTRANTBL=200,	PERM='0666',\n");
	(void) fprintf(fd, "\tSTATISTICS='n'\n");
	(void) fprintf(fd, ")\\g\n");
	(void) fprintf(fd, "\n");

	(void) fprintf(fd, "create table BRANCH (\n");
	(void) fprintf(fd, "\tBRANCH_ID	integer not null,\n");
	(void) fprintf(fd, "\tBALANCE		real,\n");
	(void) fprintf(fd, "\tLAST_ACCT	integer,\n");
	(void) fprintf(fd, "\tLAST_TELLER	integer,\n");
	(void) fprintf(fd, "\tPHONE		char(14),\n");
	(void) fprintf(fd, "\tADDRESS		char(60),\n");
	(void) fprintf(fd, "\tprimary key(BRANCH_ID)\n");
	(void) fprintf(fd, ") with (\n");
	(void) fprintf(fd, "\tFILETYPE='hash',	ICF='PI',	FIELDED='FML',\n");
	(void) fprintf(fd, "\tBLOCKLEN=%s,	DBLKS=8,	OVBLKS=2\n", blksize);
	(void) fprintf(fd, ")\\g\n");
	(void) fprintf(fd, "\n");

	(void) fprintf(fd, "create table ACCOUNT (\n");
	(void) fprintf(fd, "\tACCOUNT_ID	integer not null,\n");
	(void) fprintf(fd, "\tBRANCH_ID	integer not null,\n");
	(void) fprintf(fd, "\tSSN		char(12) not null,\n");
	(void) fprintf(fd, "\tBALANCE		real,\n");
	(void) fprintf(fd, "\tACCT_TYPE	character,\n");
	(void) fprintf(fd, "\tLAST_NAME	char(20),\n");
	(void) fprintf(fd, "\tFIRST_NAME	char(20),\n");
	(void) fprintf(fd, "\tMID_INIT	character,\n");
	(void) fprintf(fd, "\tPHONE		char(14),\n");
	(void) fprintf(fd, "\tADDRESS		char(60),\n");
	(void) fprintf(fd, "\tprimary key (ACCOUNT_ID)\n");
	(void) fprintf(fd, ") with (\n");
	(void) fprintf(fd, "\tFILETYPE='hash',	ICF='ST',	FIELDED='FML',\n");
	(void) fprintf(fd, "\tBLOCKLEN=%s,	DBLKS=100,	OVBLKS=25\n", blksize);
	(void) fprintf(fd, ")\\g\n");
	(void) fprintf(fd, "\n");
	
	(void) fprintf(fd, "create table TELLER (\n");
	(void) fprintf(fd, "\tTELLER_ID	integer not null,\n");
	(void) fprintf(fd, "\tBRANCH_ID	integer not null,\n");
	(void) fprintf(fd, "\tBALANCE		real,\n");
	(void) fprintf(fd, "\tLAST_NAME	char(20),\n");
	(void) fprintf(fd, "\tFIRST_NAME	char(20),\n");
	(void) fprintf(fd, "\tMID_INIT	character,\n");
	(void) fprintf(fd, "\tprimary key (TELLER_ID)\n");
	(void) fprintf(fd, ") with (\n");
	(void) fprintf(fd, "\tFILETYPE='hash',	ICF='ST',	FIELDED='FML',\n");
	(void) fprintf(fd, "\tBLOCKLEN=%s,	DBLKS=8,	OVBLKS=2\n", blksize);
	(void) fprintf(fd, ")\\g\n");
	(void) fprintf(fd, "\n");
	
	(void) fprintf(fd, "create table HISTORY (\n");
	(void) fprintf(fd, "\tACCOUNT_ID	integer not null,\n");
	(void) fprintf(fd, "\tTELLER_ID	integer not null,\n");
	(void) fprintf(fd, "\tBRANCH_ID	integer not null,\n");
	(void) fprintf(fd, "\tAMOUNT		real\n");
	(void) fprintf(fd, ") with (\n");
	(void) fprintf(fd, "\tFILETYPE='heap',	ICF='ST',	FIELDED='FML',\n");
	(void) fprintf(fd, "\tBLOCKLEN=%s,	DBLKS=800,	OVBLKS=10\n", blksize);
	(void) fprintf(fd, ")\\g\n");
	(void) fprintf(fd, "\n");
	
	(void) fprintf(fd, "create index ANAMEIDX on ACCOUNT (LAST_NAME, FIRST_NAME, MID_INIT)\n");
	(void) fprintf(fd, "with (\n");
	(void) fprintf(fd, "\tBLOCKLEN=%s,	DBLKS=0,		FILETYPE='BTREE',\n",
		blksize);
	(void) fprintf(fd, "\tICF='ST',		LINKNAME='name_acct',	LINKTYPE='indx',\n");
	(void) fprintf(fd, "\tMULTIREC='n',		OVBLKS=13,		SPARSE='n'\n");
	(void) fprintf(fd, ")\\g\n");
	(void) fprintf(fd, "\n");
	
	(void) fprintf(fd, "create index TNAMEIDX on TELLER (LAST_NAME, FIRST_NAME, MID_INIT)\n");
	(void) fprintf(fd, "with (\n");
	(void) fprintf(fd, "\tBLOCKLEN=%s,	DBLKS=0,		FILETYPE='BTREE',\n",
		blksize);
	(void) fprintf(fd, "\tICF='ST',		LINKNAME='name_tell',	LINKTYPE='indx',\n");
	(void) fprintf(fd, "\tMULTIREC='n',		OVBLKS=5,		SPARSE='n'\n");
	(void) fprintf(fd, ")\\g\n");
	(void) fprintf(fd, "\n");
	
	(void) fprintf(fd, "\\q\n");

	exitcode = _pclose(fd);
	if (exitcode != 0){
		(void) fprintf(stderr, "sql failed to construct database.\n");
		exit(1);
	}

	(void) printf("crbankdb successful.\n");

	exit(0);
}
