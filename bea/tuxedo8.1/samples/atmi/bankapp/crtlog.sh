#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/crtlog.sh	$Revision: 1.5 $"
if [ "${1}" = "-m" ] ; then
	#
	# If -m specified, create device and TLOG
	#
	tmadmin <<-!
		echo
		crdl -b 500 -z ${TLOGDEVICE}
		crlog -m SITE1
		q
		!
elif [ -z "${1}" ] ; then
	#
	# If -m not specified, create device only
	#
	tmadmin -c <<-!
		echo
		crdl -b 500 -z ${TLOGDEVICE}
		q
		!
else
	#
	# If other things specified, error
	#
	echo "$0:  usage:  $0 [-m]"
	exit 2
fi

if [ ${?} -eq 0 ] ; then
	echo "`basename ${0}` successful."
	exit 0
fi
