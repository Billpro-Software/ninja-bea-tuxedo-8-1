#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1992 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/RUNME.sh	$Revision: 1.5 $"
#

TMPDIR="${TMPDIR:-/tmp}"
TF0="${TMPDIR}/TF0.${$}"
trap "rm -f ${TMPDIR}/*.${$} ; exit 0" 0 2 15

if [ -r setvars ] ; then
	. ./setvars
fi

if [ -z "$TUXDIR" ] ; then
	if [ -z "$ROOTDIR" ] ; then
		echo "TUXDIR must be set to the root directory for the TUXEDO \c"
		echo "System software"
		exit 1
	else
		TUXDIR=$ROOTDIR
		export TUXDIR
	fi
fi

# Set all possible shared library paths in advance
export LD_LIBRARY_PATH SHLIB_PATH LIBPATH
LD_LIBRARY_PATH=${TUXDIR}/lib:/usr/lib:${LD_LIBRARY_PATH}
SHLIB_PATH=${TUXDIR}/lib:/usr/lib:${SHLIB_PATH}
LIBPATH=${TUXDIR}/lib:/usr/lib:${LIBPATH}

ARGUSAGE="[-r <rsh-name{rsh}>]"
USAGE="usage: `basename ${0}` ${ARGUSAGE}"
OPTIONS="r:"
RSH=
set -- `getopt "${OPTIONS}" ${*}`
if [ ${?} != 0 ]
then
	echo "${USAGE}" >&2
	exit 1
fi

for ARG in ${*}
do
	case ${ARG} in
	-r) RSH=${2} ; shift 2 ;;
    	--) shift ; break ;;
	esac
done

cd TOOLS
echo "\nMaking tools, please wait, ... \c"
make >/dev/null 2>&1
echo "done."
rm -f ../setvars
ln setvars .. 2>/dev/null
cd ..
export PATH UNAME RSH APS
PATH=${PATH}:`pwd`/TOOLS:.
UNAME="`uname -n`"
if [ "`uname -s`" = "SunOS" ] ; then
	PATH="/usr/5bin:${PATH}"
	t="`uname -r`"
	if [ "`expr ${t} : '^4\.'`" -eq 2 ] ; then
		APS="ps -cx"
	else
		APS="ps -u${LOGNAME}"
	fi
	unset t
else
	APS="ps -u${LOGNAME}"
fi
if [ -d /usr/ccs/bin ] ; then
	PATH="/usr/ccs/bin:${PATH}"
fi

if [ -z "${RSH}" ] ; then
	FOUND_RSH="`type rsh 2>/dev/null | grep ' is '`"
	FOUND_REMSH="`type remsh 2>/dev/null | grep ' is '`"
	FOUND_RCMD="`type rcmd 2>/dev/null | grep ' is '`"
	# Test for rcmd first since can't use rsh on SCO
	if [ -n "${FOUND_RCMD}" ] ; then
		RSH=rcmd
	elif [ -n "${FOUND_REMSH}" ] ; then
		RSH=remsh
	elif [ -n "${FOUND_RSH}" ] ; then
		RSH=rsh
	else
		RSH="`menudriver MENUS/RSH`"
	fi
fi
${RSH} ${UNAME} pwd >${TF0}
if [ ${?} -ne 0 -o ! -s ${TF0} ] ; then
	echo "Cannot remote shell (${RSH}) local machine (${UNAME})."
	echo "Please check ${HOME}/.rhosts and retry."
	exit 1
fi

#
# Now copy MENUS and TOOLS if necessary
#
if [ ! -d MENUS ] ; then
	if [ -d ${TUXDIR}/MENUS ] ; then
		mkdir MENUS
		cp ${TUXDIR}/MENUS/* MENUS
	else
		echo "${TUXDIR}/MENUS and ./MENUS do not exist."
		exit 1
	fi
fi
if [ ! -d TOOLS ] ; then
	if [ -d ${TUXDIR}/TOOLS ] ; then
		mkdir TOOLS
		cp ${TUXDIR}/TOOLS/* TOOLS
	else
		echo "${TUXDIR}/TOOLS and ./TOOLS do not exist."
		exit 1
	fi
fi

menudriver MENUS/MAIN
