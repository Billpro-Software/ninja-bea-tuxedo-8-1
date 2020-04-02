#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.
#	Copyright (c) 1984 AT&T
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF
#	UNIX System Laboratories, Inc.
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/crusers.sh	$Revision: 1.5 $"


# On some platforms ksh's builtin echo handles \c and \n differently.
# so make sure we get the standard semantics.
 
if [ -x /usr/5bin/echo ] ; then
        alias -x echo=/usr/5bin/echo
elif [ -x /bin/echo ] ; then
        alias -x echo=/bin/echo
fi


# Verify that APPDIR is set
#
APPDIR=${APPDIR:?}


# Verify whether the user authentication file(s) exists
#
if [ -f ${APPDIR}/tpgrp -o -f ${APPDIR}/tpusr ]; then
    echo "$0: WARN: Files 'tpgrp' and/or 'tpusr' exists! \c"
    echo "Delete them to rerun '$0'"
    exit
fi


# Cleanup in case of premature failure
#
trap "rm -rf ${APPDIR}/tpgrp ${APPDIR}/tpusr" 1 2 15

###############
# Create groups
###############

echo
echo "Creating groups and users for authentication"
echo
echo "Creating group - bankmgr"

tpgrpadd -g 101 "bankmgr"
[ $? -ne 0 ] && exit

echo "Creating group - bankaud"

tpgrpadd -g 201 "bankaud"
[ $? -ne 0 ] && exit

echo
echo "Creating group - bankusr"

tpgrpadd -g 301 "bankusr"
[ $? -ne 0 ] && exit

echo

###############
# Create users
###############

echo "Creating users in group 'bankmgr'"
echo
echo "Enter user name for a bank manager: (bankmgr1) :\c"

read USRNAME
[ -z "${USRNAME}" ] && USRNAME=bankmgr1

tpusradd -u 1001 -g "bankmgr" -c "tpsysadm" ${USRNAME}
[ $? -ne 0 ] && exit

echo

echo "Creating users in group 'bankaud'"
echo
echo "Enter user name for a bank auditor: (bankaud1) :\c"

read USRNAME
[ -z "${USRNAME}" ] && USRNAME=bankaud1

tpusradd -u 2001 -g "bankaud" -c "*" ${USRNAME}
[ $? -ne 0 ] && exit

echo

echo "Creating users in group 'bankusr'"
echo

# Get unix user name of the user installing the bankapp demo app
#
UID="`expr "\`id\`" : 'uid=[0-9]*(\(.*\)).*gid'`"
echo "Enter user name for a bank user: (${UID}) :\c"

read USRNAME
[ -z "${USRNAME}" ] && USRNAME=${UID}

tpusradd -u 3001 -g "bankusr" ${USRNAME}
[ $? -ne 0 ] && exit

