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
#ident	"@(#) samples/atmi/bankapp/crqueue.sh	$Revision: 1.5 $"


# On some platforms ksh's builtin echo handles \c and \n differently.
# so make sure we get the standard semantics.
 
if [ -x /usr/5bin/echo ] ; then
        alias -x echo=/usr/5bin/echo
elif [ -x /bin/echo ] ; then
        alias -x echo=/bin/echo
fi


# Verify that QMCONFIG and APPDIR are set
#
QMCONFIG=${QMCONFIG:?}
APPDIR=${APPDIR:?}


# Verify whether the Q device exists
#
if [ -f ${APPDIR}/qdevice ]; then
    echo "$0: WARN: Q device 'qdevice' exists!"
    echo "$0: INFO: To force a re-create, use qmadmin(1) to \c"
    echo "remove Queue Space ipcs (ipcrm -y QSP_BANKAPP), then delete \c"
    echo "qdevice (file ${APPDIR}/qdevice) and re-run '$0'"
    exit
fi


# Cleanup in case of premature failure
#
trap "q_cleanup" 1 2 15

# Function called to remove Q stuff in case of premature failure
#
q_cleanup() {
    qmadmin <<!
ipcrm -y QSP_BANKAPP
!
    rm -r ${APPDIR}/qdevice
}


#
# Create a Q device
# Create a Q space (QSP_BANKAPP) within the device
# Open Q space
# Create Qs (Q_ERROR, Q_OPENACCT_LOG, Q_OPENACCT) in the Q space
# Close Q scape
#

qmadmin <<!  >/dev/null
crdl ${QMCONFIG} 0 500
qspacecreate QSP_BANKAPP 88945 200 20 5 5 200 Q_ERROR 'y' 16
qopen QSP_BANKAPP
qcreate Q_ERROR fifo none 0 0 100% 0% ""
qcreate Q_OPENACCT_LOG fifo none 2 2 5m 0m "tmboot -s TMQFORWARD"
qcreate Q_OPENACCT fifo none 0 0 100% 0% ""
qclose
!
