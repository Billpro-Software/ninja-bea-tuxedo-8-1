#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/setvars.sh	$Revision: 1.5 $"
#
# @(#) Description: Script to set bankapp environment variables

if [ -z "${UNAME}" ] ; then
	UNAME="`uname -n`"
fi
if [ `grep -l "^UNAME=${UNAME}$" ./bankvar.* 2>/dev/null | wc -l` -eq 1 ]
then
	. ./`grep -l "^UNAME=${UNAME}$" bankvar.* 2>/dev/null`
fi
