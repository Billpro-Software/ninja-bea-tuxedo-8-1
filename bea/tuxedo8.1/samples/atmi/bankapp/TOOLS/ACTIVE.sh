#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/ACTIVE.sh	$Revision: 1.5 $"
#
APS="${APS:-ps -u${LOGNAME}}"
test -n "`${APS} | sed -e '/BBL/!d' -e '/grep/d'`"
