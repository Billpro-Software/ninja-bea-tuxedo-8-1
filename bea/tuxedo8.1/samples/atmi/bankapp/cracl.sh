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
#ident	"@(#) samples/atmi/bankapp/cracl.sh	$Revision: 1.5 $"


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


# Check if there are entries in the ACL authentication file
# Entries beginning with '#' are ignored.
#
grep -s -c "^[^#]"  ${APPDIR}/tpacl >/dev/null 2>&1
if [ $? -eq 0 ] ; then
    echo "$0: WARN: Entries exist in the ACL authentication file 'tpacl' ! \c"
    echo "Delete them to re-run '$0' "
    exit
fi


# Cleanup in case of premature failure
#
trap "rm -rf ${APPDIR}/tpacl" 1 2 15


###############
# Create ACLs
###############

echo "Creating Access Control Lists (ACL)"
echo

# Services called by client "audit"
#
tpacladd -g "bankaud" -t "SERVICE" 	ABAL
[ $? -ne 0 ] && exit

tpacladd -g "bankaud" -t "SERVICE" 	ABAL_BID
[ $? -ne 0 ] && exit

tpacladd -g "bankaud" -t "SERVICE" 	TBAL
[ $? -ne 0 ] && exit

tpacladd -g "bankaud" -t "SERVICE" 	TBAL_BID
[ $? -ne 0 ] && exit


# Services called by client "auditcon"
#
tpacladd -g "bankaud" -t "SERVICE" 	AUDITC
[ $? -ne 0 ] && exit

tpacladd -g "bankaud" -t "SERVICE" 	ABALC_BID
[ $? -ne 0 ] && exit

tpacladd -g "bankaud" -t "SERVICE" 	TBALC_BID
[ $? -ne 0 ] && exit


# Queue dequeued by client "bankmgr"
#
tpacladd -g "bankmgr" -t "DEQ"		Q_OPENACCT
[ $? -ne 0 ] && exit
