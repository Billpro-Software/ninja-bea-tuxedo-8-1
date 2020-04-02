#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/ISBUILT.sh	$Revision: 1.5 $"
#
#
# Script determine if different types of build processing have been done.
#
ARGUSAGE="[-t type] [-n <#> [...]] [uname1 [...]]"
USAGE="usage: `basename ${0}` ${ARGUSAGE}"
OPTIONS="n:t:"
NODENUMS=
NODENMS=
UNAME="`uname -n`"
TYPE="build"

set -- `getopt "${OPTIONS}" ${*}`
if [ ${?} != 0 ]
then
	echo "${USAGE}" >&2
	exit 1
fi

for ARG in ${*}
do
	case ${ARG} in
	-t) TYPE="${2}" ; shift 2 ;;
	-n) NODENUMS="${NODENUMS:+${NODENUMS} }${2}" ; shift 2 ;;
	-f) FULL=y ; shift ;;
    	--) shift ; break ;;
	esac
done

for ARG in ${*}
do
	NODENMS="${NODENMS:+${NODENMS} }${ARG}"
done

if [ -z "${NODENUMS}" ] ; then
	if [ -z "${NODENMS}" ] ; then
		I=1
		while [ -r bankvar.mp${I} ] ; do
			MUN="`grep '^UNAME=' bankvar.mp${I} |
				sed 's/.*=//'`"
			NODENMS="${NODENMS:+${NODENMS} }${MUN}"
			I="`expr ${I} + 1`"
		done
	fi
else
	for I in ${NODENUMS}
	do
		if [ ! -r bankvar.mp${I} ] ; then
			continue
		fi
		MUN="`grep '^UNAME=' bankvar.mp${I} | sed 's/.*=//'`"
		NODENMS="${NODENMS:+${NODENMS} }${MUN}"
	done
fi

if [ -z "${NODENMS}" ] ; then
	exit 1
fi

for NODE in ${NODENMS}
do
	if [ ! -r .timestamps/${TYPE}/${NODE} ] ; then
		exit 1
	fi
done
exit 0
