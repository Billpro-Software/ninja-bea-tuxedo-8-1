#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/crbankdb.sh	$Revision: 1.5 $"

#
# Create device list
#
tmadmin -c <<!
# Replace the following line with your device zero entry      <<<<<<<<<<<
crdl -z ${FSCONFIG} -b 2560
!

if [ ${?} -ne 0 ] ; then
	echo "tmadmin failed to created device list."
	exit 1
fi
#
# Create database files, fields, and secondary indices
#
sql <<!
\echo
create database ${DBNAME} with (	DEVNAME='${FSCONFIG}',
	IPCKEY=${DIPCKEY},		LOGBLOCKING=0,	MAXDEV=1,
	NBLKTBL=200,	NBLOCKS=2048,	NBUF=70,	NFIELDS=80,
	NFILES=20,	NFLDNAMES=60,	NFREEPART=40,	NLCKTBL=200,
	NLINKS=80,	NPREDS=10,	NPROCTBL=20,	NSKEYS=20,
	NSWAP=50,	NTABLES=20,	NTRANTBL=20,	PERM='0666',
	STATISTICS='n'
)\g

create table BRANCH (
	BRANCH_ID	integer not null,
	BALANCE		real,
	LAST_ACCT	integer,
	LAST_TELLER	integer,
	PHONE		char(14),
	ADDRESS		char(60),
	primary key(BRANCH_ID)
) with (
	FILETYPE='hash',	ICF='PI',	FIELDED='FML',
	BLOCKLEN=${BLKSIZE},	DBLKS=8,	OVBLKS=2
)\g

create table ACCOUNT (
	ACCOUNT_ID	integer not null,
	BRANCH_ID	integer not null,
	SSN		char(12) not null,
	BALANCE		real,
	ACCT_TYPE	character,
	LAST_NAME	char(20),
	FIRST_NAME	char(20),
	MID_INIT	character,
	PHONE		char(14),
	ADDRESS		char(60),
	primary key (ACCOUNT_ID)
) with (
	FILETYPE='hash',	ICF='ST',	FIELDED='FML',
	BLOCKLEN=${BLKSIZE},	DBLKS=100,	OVBLKS=25
)\g

create table TELLER (
	TELLER_ID	integer not null,
	BRANCH_ID	integer not null,
	BALANCE		real,
	LAST_NAME	char(20),
	FIRST_NAME	char(20),
	MID_INIT	character,
	primary key (TELLER_ID)
) with (
	FILETYPE='hash',	ICF='ST',	FIELDED='FML',
	BLOCKLEN=${BLKSIZE},	DBLKS=8,	OVBLKS=2
)\g

create table HISTORY (
	ACCOUNT_ID	integer not null,
	TELLER_ID	integer not null,
	BRANCH_ID	integer not null,
	AMOUNT		real
) with (
	FILETYPE='heap',	ICF='ST',	FIELDED='FML',
	BLOCKLEN=${BLKSIZE},	DBLKS=800,	OVBLKS=10
)\g

create index ANAMEIDX on ACCOUNT (LAST_NAME, FIRST_NAME, MID_INIT)
with (
	BLOCKLEN=${BLKSIZE},	DBLKS=0,		FILETYPE='BTREE',
	ICF='ST',		LINKNAME='name_acct',	LINKTYPE='indx',
	MULTIREC='n',		OVBLKS=30,		SPARSE='n'
)\g

create index TNAMEIDX on TELLER (LAST_NAME, FIRST_NAME, MID_INIT)
with (
	BLOCKLEN=${BLKSIZE},	DBLKS=0,		FILETYPE='BTREE',
	ICF='ST',		LINKNAME='name_tell',	LINKTYPE='indx',
	MULTIREC='n',		OVBLKS=5,		SPARSE='n'
)\g

\q
!

if [ ${?} -ne 0 ] ; then
	echo "sql failed to construct database."
	exit 1
fi

echo "`basename ${0}` successful."
exit 0
