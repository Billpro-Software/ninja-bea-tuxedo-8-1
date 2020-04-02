#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/PROP.sh	$Revision: 1.5 $"
#
#
# ARGUMENTS:
#	File names
#
# RETURNS:
#	This script only exits on successful completion with an exit code of 0.
#	Failure returns a non-0 exit code.
#

TMPDIR="${TMPDIR:-/tmp}"
TF0="${TMPDIR}/TF0.${$}"
trap "rm -f ${TMPDIR}/*.${$} ; echo DONE ; exit 0" 0 2

ARGUSAGE="uname appdir files"
USAGE="usage: `basename ${0}` ${ARGUSAGE}"
OPTIONS=""
set -- `getopt "${OPTIONS}" ${*}`
if [ ${?} != 0 ]
then
	echo "${USAGE}" >&2
	echo DONE
	exit 1
fi

for ARG in ${*}
do
	case ${ARG} in
    	--) shift ; break ;;
	esac
done

UN="${1}"
AD="${2}"
shift 2
SL="${*}"

if [ -r .timestamps/prop/${UN} ] ; then
	UL="`find ${SL} -newer .timestamps/prop/${UN} -print 2>/dev/null`"
	for FL in ${UL}
	do
		${RSH} ${UN} -n rm -f ${AD}/${FL}
		rcp ${FL} ${UN}:${AD}/${FL}
		if [ ${?} -ne 0 ] ; then
			echo DONE
			exit 1
		fi
	done
	rm -f .timestamps/build/${UN}
	echo "OK\nDONE"
	exit 0
fi

DIRS="`echo ${SL} | tr ' ' '\012' | sed 's/\/[^\/]*$//' | sort -u`"
${RSH} ${UN} -n mkdir ${AD} 2>/dev/null
for DIR in ${DIRS}
do
	if [ "${DIR}" != "." ] ; then
		${RSH} ${UN} -n mkdir ${AD}/${DIR}
	fi
	UL="`echo ${SL} | tr ' ' '\012' | grep \"^${DIR}/\"`"
	rcp ${UL} ${UN}:${AD}/${DIR}
	if [ ${?} -ne 0 ] ; then
		echo DONE
		exit 1
	fi
done
rm -f .timestamps/build/${UN}
echo "OK\nDONE"
exit 0
