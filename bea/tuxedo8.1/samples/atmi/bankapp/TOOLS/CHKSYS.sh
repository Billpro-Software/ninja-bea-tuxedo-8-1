#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/CHKSYS.sh	$Revision: 1.5 $"
#

TMPDIR="${TMPDIR:-/tmp}"
TF0="${TMPDIR}/TF0.${$}"
TF1="${TMPDIR}/TF1.${$}"
TF2="${TMPDIR}/TF2.${$}"
trap "rm -f ${TMPDIR}/*.${$} ; exit 0" 0 2

ARGUSAGE=""
USAGE="usage: `basename ${0}` ${ARGUSAGE}"
OPTIONS=""
set -- `getopt "${OPTIONS}" ${*}`
if [ ${?} != 0 ]
then
	echo "${USAGE}" >&2
	exit 1
fi

for ARG in ${*}
do
	case ${ARG} in
    	--) shift ; break ;;
	esac
done

FIRST=y
PARMS="SEMUME|SEMMNU|SEMMNS|SEMMSL|SEMMNI|MSGMNI|MSGMAP|SHMMAX|SHMSEG"
NUMPARMS=9
tmboot -c 2>/dev/null |
	sed -e '1,/^---/d' -e '/^$/,$d' -e 's/[ 	][ 	]*/ /g' \
		-e 's/A + [12] //' -e 's/K/000/g' |
	while
		read UN SEMXXX SEMMSL SEMMULT MSGMNI MSGMAP SHMMULT
	do
		if [ -z "${SHMMULT}" ] ; then
			continue
		fi
		if [ "${FIRST}" = "y" ] ; then
			echo "\tChecking system configurations for \c"
			echo "configured application:\n"
			FIRST=n
		fi
		${RSH:-rsh} ${UN} -n '/etc/sysdef 2>/dev/null' |
			egrep "${PARMS}" |
			sed -e 's/^[ 	]*//' -e 's/[^0-9].*(/	/' \
				-e 's/).*//' >${TF0}
		if [ "`cat ${TF0} | wc -l`" -ne ${NUMPARMS} ] ; then
			echo "\t\t${UN}\t: Could not access /etc/sysdef"
			continue
		fi
		rm -f ${TF2}
		# Check SEMUME, SEMMNU and SEMMNS
		for VAR in SEMUME SEMMNU SEMMNS
		do
			SYSVAL0="`grep ${VAR} ${TF0} | cut -f1`"
			if [ -z "${SYSVAL0}" ] ; then
				echo "\t\t${UN}\t: /etc/sysdef did not \c"
				echo "report ${VAR}"
				touch ${TF1} ${TF2}
			elif [ ${SYSVAL0} -lt ${SEMXXX} ] ; then
				echo "\t\t${UN}\t: ${VAR} is ${SYSVAL0}, \c"
				echo "should be >= ${SEMXXX}"
				touch ${TF1} ${TF2}
			fi
		done
		SYSVAL0="`grep SEMMSL ${TF0} | cut -f1`"
		if [ -z "${SYSVAL0}" ] ; then
			echo "\t\t${UN}\t: /etc/sysdef did not \c"
			echo "report SEMMSL"
			touch ${TF1} ${TF2}
		else
			SYSVAL1="`grep SEMMNI ${TF0} | cut -f1`"
			if [ -z "${SYSVAL0}" ] ; then
				echo "\t\t${UN}\t: /etc/sysdef did not \c"
				echo "report SEMMNI"
				touch ${TF1} ${TF2}
			else
				if [ ${SYSVAL0} -lt ${SEMMSL} ] ; then
					echo "\t\t${UN}\t: SEMMSL is \c"
					echo "${SYSVAL0}, should be >= ${SEMMSL}"
					touch ${TF1} ${TF2}
				else
					if [ ${SYSVAL0} -ge 10 ] ; then
						MNI=8
					elif [ ${SYSVAL0} -lt 3 ] ; then
						MNI=0
					else
						MNI=`expr ${SYSVAL1} - 2`
					fi
					if [ ${MNI} -eq 0 ] ; then
						echo "\t\t${UN}\t: SEMMNI \c"
						echo "set too low"
						touch ${TF1} ${TF2}
					else
						MUL=`expr ${MNI} \* ${SYSVAL0}`
						if [ ${MUL} -lt ${SEMMULT} ]
						then
						echo "\t\t${UN}\t: SEMMNI \c"
						echo "set too low"
						touch ${TF1} ${TF2}
						fi
					fi
				fi
			fi
		fi
		SYSVAL0="`grep MSGMNI ${TF0} | cut -f1`"
		if [ -z "${SYSVAL0}" ] ; then
			echo "\t\t${UN}\t: /etc/sysdef did not \c"
			echo "report MSGMNI"
			touch ${TF1} ${TF2}
		elif [ ${SYSVAL0} -lt ${MSGMNI} ] ; then
			echo "\t\t${UN}\t: MSGMNI is ${SYSVAL0}, \c"
			echo "should be >= ${MSGMNI}"
			touch ${TF1} ${TF2}
		fi
		SYSVAL0="`grep MSGMAP ${TF0} | cut -f1`"
		if [ -z "${SYSVAL0}" ] ; then
			echo "\t\t${UN}\t: /etc/sysdef did not \c"
			echo "report MSGMAP"
			touch ${TF1} ${TF2}
		elif [ ${SYSVAL0} -lt ${MSGMAP} ] ; then
			echo "\t\t${UN}\t: MSGMAP is ${SYSVAL0}, \c"
			echo "should be >= ${MSGMAP}"
			touch ${TF1} ${TF2}
		fi
		SYSVAL0="`grep SHMMAX ${TF0} | cut -f1`"
		SYSVAL1="`grep SHMSEG ${TF0} | cut -f1`"
		if [ -z "${SYSVAL0}" -o -z "${SYSVAL1}" ] ; then
			echo "\t\t${UN}\t: /etc/sysdef did not \c"
			echo "report SHMMAX or SHMSEG"
			touch ${TF1} ${TF2}
		else

                        NUM1=`expr ${SHMMULT} / $SYSVAL1`

                        NUM2=`expr ${SHMMULT} % $SYSVAL1`

                        if [ $SYSVAL0 -le $NUM1 ]
                        then
                                if [ $SYSVAL0 -lt $NUM1 -o $NUM2 -ne 0 ]
                                then
                                        echo "\t\t${UN}\t: SHMMAX is ${SYSVAL0}
and SHMSEG is ${SYSVAL1}, \c"
                                        echo "SHMMAX*SHMSEG should be >= ${SHMMU
LT}"
                                        touch ${TF1} ${TF2}
                                fi
                        fi
		fi
		if [ ! -r ${TF2} ] ; then
			echo "\t\t${UN}\t: OK"
		fi
	done

if [ -r ${TF1} ] ; then
	echo "\n\tYou may need to reconfigure the appropriate\c"
	echo " systems before continuing."
fi
exit 0
