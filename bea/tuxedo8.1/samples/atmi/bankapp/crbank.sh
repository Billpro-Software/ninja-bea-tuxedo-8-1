#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/crbank.sh	$Revision: 1.5 $"

DIPCKEY1="${DIPCKEY:-80953}"
DIPCKEY2="`expr ${DIPCKEY} + 1`"
DIPCKEY3="`expr ${DIPCKEY} + 2`"

FSCONFIG=$APPDIR/bankdl1
DIPCKEY=${DIPCKEY1}
export FSCONFIG DIPCKEY
crbankdb
#
FSCONFIG=$APPDIR/bankdl2 
DIPCKEY=${DIPCKEY2}
export FSCONFIG DIPCKEY
crbankdb
#
FSCONFIG=$APPDIR/bankdl3
DIPCKEY=${DIPCKEY3}
export FSCONFIG DIPCKEY
crbankdb
