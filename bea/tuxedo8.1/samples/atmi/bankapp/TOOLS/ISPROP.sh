#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/ISPROP.sh	$Revision: 1.5 $"
#
#
# Script determine if propagation has been done to all (or particular)
# machines.
#
ARGUSAGE="[-c] [-n <#> [...]] [uname1 [...]]"
USAGE="usage: `basename ${0}` ${ARGUSAGE}"
OPTIONS="cn:"
CURRENT=
NODENUMS=
NODENMS=
UNAME="`uname -n`"

set -- `getopt "${OPTIONS}" ${*}`
if [ ${?} != 0 ]
then
	echo "${USAGE}" >&2
	exit 1
fi

for ARG in ${*}
do
	case ${ARG} in
	-c) CURRENT=y ; shift ;;
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

if [ -n "${CURRENT}" ] ; then
	SL="`make -f bankapp.mk list | sed -e 's;apps/bankapp/;;'`"
fi

for NODE in ${NODENMS}
do
	if [ "${NODE}" = "${UNAME}" ] ; then
		continue
	fi
	if [ ! -r .timestamps/prop/${NODE} ] ; then
		exit 1
	fi
	if [ -n "${CURRENT}" ] ; then
		TMP="`find ${SL} bankvar.mp* BANKAPP.mk* \
					-newer .timestamps/prop/${NODE} \
					-print 2>/dev/null`"
		if [ -n "${TMP}" ] ; then
			exit 1
		fi
	fi
done
exit 0
