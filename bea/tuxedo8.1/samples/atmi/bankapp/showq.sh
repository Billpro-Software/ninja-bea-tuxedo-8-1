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
#ident	"@(#) samples/atmi/bankapp/showq.sh	$Revision: 1.5 $"

#
# Ensure that QMCONFIG is set (run script ./bankvar)
# Open the Q space (QSP_BANKAPP)
# Set the Q whose info is desired ( default is Q_OPENACCT_LOG)
# Turn ON verbose mode
# List Q contents
# Show Q creation information
#

qmadmin <<!
qopen QSP_BANKAPP
qset ${1:-Q_OPENACCT_LOG}
verbose
qlist
qinfo ${1:-Q_OPENACCT_LOG}
!
