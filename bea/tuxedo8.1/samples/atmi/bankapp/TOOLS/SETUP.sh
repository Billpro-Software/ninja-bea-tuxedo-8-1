#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/SETUP.sh	$Revision: 1.5 $"
#
# This is an interactive script that generates the ASCII configuration
# file and configuration related makefiles and variable scripts for an MP
# configuration.
#
# INPUTS:
#	Environment Variables
#		RSH	- Optionally set to indicate the remotes shell (rsh)
#		VERBOSE	- Set to "n" or "y" to indicate if VERBOSE mode.
#
# OUTPUTS:
#	Files
#		UBB	      - ASCII configuration file
#		bank.h	      - Modified to indicate the account distribution
#		bankvar.mp<#> - One per machine with env settings
#		BANKAPP.mk<#> - One per machine to be used for make
#
# RETURNS:
#	This script only exits on its own after successful completion and does
#	so with an exit code of 0.  However, the user may <break> out of
#	processing in which case no files are generated and an exit code
#	of 2 is returned.
#

# On some platforms ksh's builtin echo does not handle \c and \n correctly,
# so make sure we get the standard semantics.
if [ -x /usr/5bin/echo ] ; then
	alias -x echo=/usr/5bin/echo
elif [ -x /bin/echo ] ; then
	alias -x echo=/bin/echo
fi

TMPDIR="${TMPDIR:-/tmp}"
if [ -z "${TUXDIR}" ] ; then
	if [ ! -z "${ROOTDIR}" ] ; then
		TUXDIR=$ROOTDIR
		export TUXDIR
	fi
fi
TF0="${TMPDIR}/TF0.${$}"
TF2="${TMPDIR}/TF2.${$}"
trap "rm -f ${TMPDIR}/*.${$} ; exit 0" 0
trap "rm -f ${TMPDIR}/*.${$} ; rm -f UBB bankvar.mp* BANKAPP.mk* ; exit 2" 2

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

export VERBOSE
VERBOSE=n

while true
do
	echo "\nBankapp initialization has two modes -->\n"
	echo "    Verbose mode - more input, more output, more questions,\c"
	echo " more flexibility"
	echo "    Terse mode - less input, less output, less questions,\c"
	echo " less flexibility"

	echo "\nVerbose(v) or Terse(t) Mode (<cr> == v) ? \c"
	read CHOICE
	if [ -z "${CHOICE}" ] ; then
		CHOICE=v
	fi
	case "${CHOICE}" in
		v) VERBOSE=y ; break ;;
		t) VERBOSE=n ; break ;;
	esac
done

echo "\nEntering MP mode configuration setup for `uname -n`.\n"

#
# If main script couldn't figure out where rsh is or told where, find
# out now.  If we can't find it, then error out immediately.
#
while [ -z "${RSH}" ] ; do
	echo "Enter remote shell command name ? \c"
	read RSH
	if [ -z "`type ${RSH} | grep ' is '`" ] ; then
		RSH=
		continue
	fi
done

#
# Find out how many sites they want to configure altogether.
#
NUMSITES=0
MINSITES=1
MAXSITES=10
AD_SUBDIR=
UID="`expr "\`id\`" : 'uid=\([0-9]*\)('`"
GID="`expr "\`id\`" : '.*gid=\([0-9]*\)('`"

while [ ${NUMSITES} -eq 0 ] ; do
	echo "How many sites would you like to configure \c"
	echo "(${MINSITES} <= # <= ${MAXSITES}, <cr>==${MINSITES}) ? \c"
	read NUMSITES
	if [ -z "${NUMSITES}" ] ; then
		NUMSITES=${MINSITES}
	elif [ "${NUMSITES}" -lt ${MINSITES} -o "${NUMSITES}" -gt ${MAXSITES} ]
	then
		echo "\n\tInvalid input, number of sites must be \c"
		echo "between ${MINSITES} and ${MAXSITES} inclusive"
		echo "\tPlease try again.\n"
		NUMSITES=0
		continue
	fi
done

#
# Ok, now 1 by 1, get the information relating to the configuration of each
# machine.  Be careful to differentiate between verbose and terse mode.
#

CURSITE=0
while [ ${CURSITE} -lt ${NUMSITES} ] ; do
	#
	# Find out the system name for the site, note that we don't need to
	# do this for CURSITE == 0 since that's the local site by definition.
	#
	if [ ${CURSITE} -eq 0 ] ; then
		CFG_UNAME[${CURSITE}]="`uname -n`"
		CFG_HOME[${CURSITE}]="${HOME}"
	else
		echo "\nEnter system name for system $((CURSITE+1)) ? \c"
		read CFG_UNAME[${CURSITE}]
		echo "\n\tAttempting to contact ${CFG_UNAME[${CURSITE}]} via \c"
		echo "remote shell."
		echo "\tA long delay may indicate an invalid machine or that"
		echo "\tthe selected machine is down.\n"
		CFG_HOME[${CURSITE}]="`eval ${RSH:-rsh} \
			${CFG_UNAME[${CURSITE}]} -n pwd 2>/dev/null`"
		if [ -z "${CFG_HOME[${CURSITE}]}" ] ; then
			echo "\n\tError contacting ${CFG_UNAME[${CURSITE}]}."
			echo
			continue
		fi
	fi

	#
	# At this point we have the following env variables set for the
	# current site.
	#
	#	CFG_UNAME
	#	CFG_HOME
	#
	# Now figure out what the TUXDIR is for the current node.  If we're
	# dealing with the local site, then it might already be set in our
	# environment, if we're dealing with a remote site, it might be set
	# in the .profile or in a .rootdir file found in the home directory
	# Present the choices by creating a temporary menu conforming to the
	# syntax defined for menudriver and invoking the menudriver program
	# to process the users input.
	#
	if [ ${CURSITE} -eq 0 ] ; then
		#
		# Figure out TUXDIR for the local site.
		#
		while
			true
		do
			echo "OPTIONS	SELECTION" >${TF0}
			if [ -n "${TUXDIR}" -a -d "${TUXDIR}" ] ; then
				if [ "${VERBOSE}" = "n" ] ; then
					CFG_ROOT[${CURSITE}]="${TUXDIR}"
					break
				fi
			fi
			cat <<EOF >>${TF0}
TITLE	TUXDIR Selection for ${CFG_UNAME[${CURSITE}]}
${TUXDIR}
	PRIO	exit 1
	SHEL	echo ${TUXDIR}
	END
other
	SHEL	TUXDIR=
	SHEL	while [ -z "\${TUXDIR}" -o ! -d "\${TUXDIR}" ] ; do
	SHEL		echo "Enter TUXDIR ? \c" 1>&2
	SHEL		read TUXDIR
	SHEL	done
	SHEL	echo "\${TUXDIR}"
	END
EOF
			CFG_ROOT[${CURSITE}]="`menudriver ${TF0}`"
			if [ -d ${CFG_ROOT[${CURSITE}]} ] ; then
				break
			fi
		done
	else
		while
			true
		do
			mkdir .rootdirs 2>/dev/null
			#
			# First check to see if we've done this site before.
			# If so, then present a menu of choices to the user,
			# otherwise, just do a loop where they enter their
			# own rootdir.
			#
			if [ -s .rootdirs/${CFG_UNAME[${CURSITE}]} ] ; then
				TR=`cat .rootdirs/${CFG_UNAME[${CURSITE}]}`
				if [ "${VERBOSE}" = "n" ] ; then
					CFG_ROOT[${CURSITE}]=${TR}
					echo "\t${CFG_UNAME[${CURSITE}]}\t: \c"
					echo "TUXDIR=${TR}"
					break
				fi
				cat <<EOF >${TF0}
OPTIONS	SELECTION
TITLE	TUXDIR Selection for ${CFG_UNAME[${CURSITE}]}
${TR}
	PRIO	exit 1
	SHEL	echo ${TR}
	END
other
	SHEL	TUXDIR=
	SHEL	while [ -z "\${TUXDIR}" ] ; do
	SHEL		echo "Enter TUXDIR ? \c" 1>&2
	SHEL		read TUXDIR
	SHEL	done
	SHEL	echo "\${TUXDIR}"
	END
EOF
				CFG_ROOT[${CURSITE}]="`menudriver ${TF0}`"
			else
				#
				# Figure out TUXDIR for the REMOTE site.  There
				# are no defaults for this, you've got to enter
				# them all and we check them via RSH.
				#
				CFG_ROOT[${CURSITE}]=
				while [ -z "${CFG_ROOT[${CURSITE}]}" ] ; do
					echo "Enter TUXDIR for site \c"
					echo "${CFG_UNAME[${CURSITE}]} ? \c"
					read CFG_ROOT[${CURSITE}]
				done
			fi
			#
			# Now check the validity of the remote TUXDIR, in
			# verbose mode, tell them about the check.  Now warning
			# here about time delays since RSH above to check HOME
			# was ok.
			#
			if [ "${VERBOSE}" = "y" ] ; then
				echo "\n\tChecking validity of \c"
				echo "${CFG_ROOT[${CURSITE}]} \c"
				echo "on machine ${CFG_UNAME[${CURSITE}]}."
				echo "\tPlease wait ...\n"
			else
				echo "\t${CFG_UNAME[${CURSITE}]}\t: test -d \c"
				echo "${CFG_ROOT[${CURSITE}]}"
			fi
			if [ -n "`eval ${RSH:-rsh} ${CFG_UNAME[${CURSITE}]} -n \
				ls -d ${CFG_ROOT[${CURSITE}]} 2>/dev/null`" ]
			then
				break
			fi
			echo "Invalid TUXDIR for ${CFG_UNAME[${CURSITE}]}, \c"
			echo "try again."
		done
		echo ${CFG_ROOT[${CURSITE}]} >.rootdirs/${CFG_UNAME[${CURSITE}]}
	fi
	#
	# At this point we have the following env variables set for the
	# current site.
	#
	#	CFG_UNAME
	#	CFG_HOME
	#	CFG_ROOT
	#
	# Now find out what the APPDIR is.  For the local machine it must
	# be the current directory.  For remote machines, if the same subdir
	# in the home dir is in use, see if the user wants it cleared out.
	# If they're not in the home directory, then reset the
	# appdir to "bankapp" immediately.
	# 
	if [ ${CURSITE} -eq 0 ] ; then
		CFG_APPDIR[0]="`pwd`"
		if [ "`dirname ${CFG_APPDIR[0]}`" = "${CFG_HOME[0]}" ] ; then
			AD_SUBDIR="`
				echo ${CFG_APPDIR[0]} |
				sed \"s;${CFG_HOME[0]}/;;\"`"
		else
			AD_SUBDIR=bankapp
		fi
	else
		CFG_APPDIR[${CURSITE}]="${CFG_HOME[${CURSITE}]}/${AD_SUBDIR}"
		if [ "${VERBOSE}" = "y" ] ; then
			echo "\n\tChecking existence of \c"
			echo "${CFG_APPDIR[${CURSITE}]}\c"
			echo " on ${CFG_UNAME[${CURSITE}]}."
			echo "\tPlease wait ...\n"
		else
			echo "\t${CFG_UNAME[${CURSITE}]}\t: test -d \c"
			echo "${CFG_APPDIR[${CURSITE}]}"
		fi
		ANSWER=y
		if [ -n "`eval ${RSH:-rsh} ${CFG_UNAME[${CURSITE}]} -n \
			ls -d ${CFG_APPDIR[${CURSITE}]} 2>/dev/null`" ] ; then
			ANSWER=y
			if [ "${VERBOSE}" = "y" ] ; then
				echo "\nRemove ${CFG_APPDIR[${CURSITE}]} \c"
				echo "on ${CFG_UNAME[${CURSITE}]} before \c"
				echo "continuing (<cr> == y) ? \c"
				read ANSWER
			fi
			if [ "${ANSWER}" != "n" ] ; then
				echo "\t${CFG_UNAME[${CURSITE}]}\t: \c"
				echo "rm -fr ${CFG_APPDIR[${CURSITE}]}"
				eval ${RSH:-rsh} ${CFG_UNAME[${CURSITE}]} -n \
					rm -fr ${CFG_APPDIR[${CURSITE}]}
				rm -fr .timestamps/*/${CFG_UNAME[${CURSITE}]}
			fi
		fi
		if [ "${ANSWER}" != "n" ] ; then
			if [ "${VERBOSE}" = "y" ] ; then
				echo "\n\tMaking directory \c"
				echo "${CFG_APPDIR[${CURSITE}]} \c"
				echo "on ${CFG_UNAME[${CURSITE}]}"
			else
				echo "\t${CFG_UNAME[${CURSITE}]}\t: mkdir \c"
				echo "${CFG_APPDIR[${CURSITE}]}"
			fi
			OK="`${RSH:-rsh} ${CFG_UNAME[${CURSITE}]} -n \"\
				mkdir ${CFG_APPDIR[${CURSITE}]} 2>/dev/null ; \
				ls -d ${CFG_APPDIR[${CURSITE}]} 2>/dev/null\"`"
			if [ -z "${OK}" ] ; then
				echo "\n\t*** Error making directory \c"
				echo "${CFG_APPDIR[${CURSITE}]}. ***"
				exit 1
			fi
		fi
	fi
	#
	# At this point we have the following env variables set for the
	# current site.
	#
	#	CFG_UNAME
	#	CFG_HOME
	#	CFG_ROOT
	#	CFG_APPDIR
	#
	# And the CFG_APPDIR has been instantiated and optionally cleaned.
	#
	# Now set the machine type according to the uname -m output for that
	# site
	#
	if [ ${CURSITE} -eq 0 ] ; then
		CFG_TYPE[0]="`uname -m`"
	else
		if [ "${VERBOSE}" = "y" ] ; then
			echo "\n\tQuerying ${CFG_UNAME[${CURSITE}]} \c"
			echo "for machine type, please wait."
		fi
		CFG_TYPE[${CURSITE}]="`eval ${RSH:-rsh} \
			${CFG_UNAME[${CURSITE}]} -n uname -m`"
	fi
	if [ -z "${CFG_TYPE[${CURSITE}]}" ] ; then
		CFG_TYPE[${CURSITE}]="BA_type${CURSITE}"
	fi
	echo "\t${CFG_UNAME[${CURSITE}]}\t: Machine type set to \c"
	echo "${CFG_TYPE[${CURSITE}]}"

	#
	# At this point we have the following env variables set for the
	# current site.
	#
	#	CFG_UNAME
	#	CFG_HOME
	#	CFG_ROOT
	#	CFG_APPDIR
	#	CFG_TYPE
	#
	# And the CFG_APPDIR has been instantiated and optionally cleaned.
	#
	#
	# Now figure out the networking, for site 0 we need to figure out
	# the type (tcp/ip, starlan, etc.) and port number.  For each site
	# we need to figure out the addressing format.
	#
	if [ ${NUMSITES} -gt 1 ] ; then
	    if [ ${CURSITE} -eq 0 ] ; then
		NET_TYPE=
		if [ "${VERBOSE}" = "n" -a -r /etc/hosts ] ; then
			NET_TYPE=tcpip
		fi
		while [ -z "${NET_TYPE}" ] ; do
			cat <<EOF >${TF0}
TITLE	Network Type Selection
OPTIONS	SELECTION
tcp/ip
	PRIO	if [ -r /etc/hosts ] ; then
	PRIO		exit 1
	PRIO	fi
	PRIO	exit 0
	SHEL	echo tcpip
	END
starlan
	SHEL	echo starlan
	END
EOF
			NET_TYPE="`menudriver ${TF0}`"
		done
		#
		# Now generate a port number (4 digits) that can be used
		# for either starlan or tcpip.  use UID modulus 24K plus 32K
		# to get a number somewhere in the 24k-56k range which should
		# be safe.
		#
		NET_PORT_NUM=$(((UID%24576)+32768))
		NET_NPORT_NUM=$((NET_PORT_NUM+1))
		#
		# Now convert both port numbers to 4 digit hex strings for
		# use later.
		#
		NET_PORT="`echo \"obase=16\n${NET_PORT_NUM}\" | bc`"
		NET_NPORT="`echo \"obase=16\n${NET_NPORT_NUM}\" | bc`"
		#
		# Ok, now we've figured out the generic network stuff, figure
		# out the per-site stuff for site 0 now.  This includes
		# the following (CFG_NW_NADDR, CFG_NW_NLSADDR, CFG_NW_BRIDGE).
		#
		case ${NET_TYPE} in
		    tcpip)
			#
			# See what the device is, we know about /dev/tcp and
			# /dev/it.  If exactly one of them exists, then use it
			# otherwise ask the user what they want.
			#
			DC="`ls /dev/tcp /dev/inet/tcp /dev/it \
				/dev/streams/xtiso/tcp 2>/dev/null |
				wc -l`"
			if [ "${DC}" -ge 1 ] ; then
				CFG_NW_BRIDGE[${CURSITE}]="`
				ls /dev/tcp /dev/inet/tcp /dev/it \
					/dev/streams/xtiso/tcp 2>/dev/null |
					tail -1`"
			elif [ "${VERBOSE}" = "y" ] ; then
				echo "Enter tcp/ip device for \c"
				echo "${CFG_UNAME[${CURSITE}]} \c"
				echo "(<cr>==NONE) ? \c"
				read CFG_NW_BRIDGE[${CURSITE}]
			else
				CFG_NW_BRIDGE[${CURSITE}]=""
			fi
			#
			# Assume the default tcp/ip addressing format, find
			# the host address from the /etc/hosts file.
			#
			HA="`hostaddr ${CFG_UNAME[${CURSITE}]}`"
			while [ ${#HA} -ne 8 ] ; do
				echo "Cannot retrieve 8 digit hex host address"
				echo "from /etc/hosts."
				echo "\nPlease enter 8 digit hex host \c"
				echo "address ? \c"
				read HA
			done
			CFG_NW_NADDR[${CURSITE}]="0x0002${NET_PORT}${HA}"
			CFG_NW_NLSADDR[${CURSITE}]="0x0002${NET_NPORT}${HA}"
			;;
		    starlan)
			CFG_NW_NADDR[${CURSITE}]="${CFG_UNAME[${CURSITE}]}.${NET_PORT}"
			CFG_NW_NLSADDR[${CURSITE}]="${CFG_UNAME[${CURSITE}]}.${NET_NPORT}"
			CFG_NW_BRIDGE[${CURSITE}]="/dev/starlan"
			;;
		esac
	    else
		#
		# For remote sites figure out only the per-site stuff for
		# the network.
		#
		case ${NET_TYPE} in
		    tcpip)
			#
			# See what the device is, we know about /dev/tcp and
			# /dev/it.  If exactly one of them exists, then use it
			# otherwise ask the user what they want.
			#
			DC="`eval ${RSH:-rsh} ${CFG_UNAME[${CURSITE}]} -n \
				ls /dev/tcp /dev/inet/tcp /dev/it \
					/dev/streams/xtiso/tcp 2>/dev/null |
					wc -l`"
			if [ "${DC}" -ge 1 ] ; then
				CFG_NW_BRIDGE[${CURSITE}]="`
				eval ${RSH:-rsh} ${CFG_UNAME[${CURSITE}]} -n \
				ls /dev/tcp /dev/inet/tcp /dev/it \
					/dev/streams/xtiso/tcp 2>/dev/null |
					tail -1`"
			else
				echo "Enter tcp/ip device for \c"
				echo "${CFG_UNAME[${CURSITE}]} \c"
				echo "(<cr>==NONE) ? \c"
				read CFG_NW_BRIDGE[${CURSITE}]
			fi
			#
			# Assume the default tcp/ip addressing format, find
			# the host address from the /etc/hosts file.
			#
			HA="`hostaddr ${CFG_UNAME[${CURSITE}]}`"
			while [ ${#HA} -ne 8 ] ; do
				echo "Cannot retrieve 8 digit hex host address"
				echo "from /etc/hosts."
				echo "\nPlease enter 8 digit hex host \c"
				echo "address ? \c"
				read HA
			done
			CFG_NW_NADDR[${CURSITE}]="0x0002${NET_PORT}${HA}"
			CFG_NW_NLSADDR[${CURSITE}]="0x0002${NET_NPORT}${HA}"
			;;
		    starlan)
			CFG_NW_NADDR[${CURSITE}]="${CFG_UNAME[${CURSITE}]}.${NET_PORT}"
			CFG_NW_NLSADDR[${CURSITE}]="${CFG_UNAME[${CURSITE}]}.${NET_NPORT}"
			CFG_NW_BRIDGE[${CURSITE}]="/dev/starlan"
			;;
		esac
	    fi
	fi
	#
	# At this point we have the following env variables set for the
	# current site.
	#
	#	CFG_UNAME
	#	CFG_HOME
	#	CFG_ROOT
	#	CFG_APPDIR
	#	CFG_TYPE
	#	CFG_NW_NADDR
	#	CFG_NW_NLSADDR
	#	CFG_NW_BRIDGE
	#
	# And the CFG_APPDIR has been instantiated and optionally cleaned.
	#

	#
	# Find out the page size for this processor.
	#
	${RSH:-rsh} ${CFG_UNAME[${CURSITE}]} -n "\
		export PATH
		PATH=/usr/5bin:/usr/ccs/bin:/opt/SUNWspro/bin:\$PATH
		cd ${CFG_APPDIR[${CURSITE}]} ; cat <<-EOF >_blksz.c
			#include <fs.h>
			main() { printf(\"%d\\n\", PAGESIZE); exit(0); }
			EOF
		cc -I${CFG_ROOT[${CURSITE}]}/include _blksz.c -o _blksz
		./_blksz ; rm -fr _blksz*" >${TF0} 2>${TF2}
	CFG_BLKSIZE[${CURSITE}]=`cat ${TF0}`
	echo "\t${CFG_UNAME[${CURSITE}]}\t: Block size == \c"
	echo "${CFG_BLKSIZE[${CURSITE}]:-512?}"
	if [ -z "${CFG_BLKSIZE[${CURSITE}]}" ] ; then
		echo "\nError computing remote block size:\n"
		cat ${TF2}
		echo
		CFG_BLKSIZE[${CURSITE}]=512
	fi
	rm -f ${TF2}

	echo
	CURSITE=$((CURSITE+1))
done
#
# Now find out what IPCKEY to use.
#
while true
do
	DK=$((80952+UID))
	if [ "${VERBOSE}" = "y" ] ; then
		echo "\n\tYou will be asked to enter an IPCKEY, this"
		echo "\tis a numeric value that is used to allocate"
		echo "\tshared memory for both /T and the database"
		echo "\tallocated in /D.  The default is usually fine"
		echo "\tunless others are using the indicated key on"
		echo "\tthis machine."

		echo "\nWhat IPCKEY would you like to use \c"
		echo "(<cr> == ${DK}) ? \c"
		read IPCKEY
		if [ -z "${IPCKEY}" ] ; then
			IPCKEY=${DK}
			break
		fi
		NS="`expr "${IPCKEY}" : '[0-9]*'`"
		LS="`expr "${IPCKEY}" : '.*'`"
		if [ "${NS}" -ne "${LS}" ] ; then
			echo "\tIPCKEY must be all numeric"
			continue
		fi
	else
		echo "\t`uname -n`\t: IPCKEY set to ${DK}"
		IPCKEY="${DK}"
	fi
	break
done
DIPCKEY=$((IPCKEY+1))

#
# Before generating the UBB file, figure out what the routing
# criteria are based on the number of sites.
#
I=1
INCT10=$((100/NUMSITES))
while [ ${I} -le ${NUMSITES} ] ; do
	#
	# Compute the low value of this range
	#
	if [ ${I} -eq 1 ] ; then
		RNG_LOW[$((I-1))]=1
	else
		RNG_LOW[$((I-1))]=$((RNG_HIGH[$((I-2))]+1))
	fi
	#
	# Now compute the high value for this range
	#
	if [ ${I} -eq ${NUMSITES} ] ; then
		RNG_HIGH[$((I-1))]=10
	else
		#
		# Compute the span of this range, we use the increment * 10
		# to smooth out the curve, i.e., for 4 sites we'll do
		# 1-2, 3-5, 6-7, 8-10 instead of 1-2, 3-4, 5-6, 7-10.
		#
		RNG_HIGH[$((I-1))]=$(((INCT10\*I)/10))
	fi
	I=$((I+1))
done

#
# Ok, now we're ready to create the UBB file based on the parameters set
# above.
#
# For this script to be successful, we have to create the UBB as
# part of successful completeion of the following steps.
#
#	1* Create UBB
#	2. Create bankvar.mp# for each site
#	3. Create BANKAPP.mk# for each site
#	4. Update bank.h to reflect the partitioning of the database.
#

#
# Create UBB/*RESOURCES
#
if [ "${NUMSITES}" -eq 1 ] ; then
	MASTER=SITE1
	MODEL=SHM
	OPTIONS="# No OPTIONS set for SHM mode bankapp"
else
	MASTER=SITE1,SITE2
	MODEL=MP
	OPTIONS="OPTIONS		LAN"
fi

cat <<EOF >UBB
#
# The banking demo application, bankapp, has been enhanced to demonstrate
# some of the new features introduced in release 6. For a list of the new
# features and how they appear in bankapp, refer to the file README2 under
# the bankapp directory ($TUXDIR/apps/bankapp/README2). The bankapp
# application comes "armed" with these features but not "activated". The
# README2 file lists the steps required to "activate" the new features.
#
# When this file is generated (running the RUNME.sh script), there are lines
# produced, that begin with the characters '##'. These are related to the new
# features in bankapp. (Recall that lines beginning with the '#' character
# are treated as comments). Comments are inserted in-line to briefly explain 
# the new features where they appear.
#
*RESOURCES
IPCKEY		${IPCKEY}
DOMAINID	bankapp
UID		${UID}
GID		${GID}
PERM		0660
MAXACCESSERS	50
MAXSERVERS	$(((NUMSITES*20)+25))
MAXSERVICES	$(((NUMSITES*35)+30))
MAXCONV		10
MAXGTT		25
MASTER		${MASTER}
${OPTIONS}
MODEL		${MODEL}
LDBAL		Y
##SECURITY	ACL
EOF


cat <<EOF >>UBB
##AUTHSVC		"..AUTHSVC"

EOF

#
# Create UBB/*MACHINES
#
echo "*MACHINES" >>UBB
CURSITE=0
while [ ${CURSITE} -lt ${NUMSITES} ] ; do
	SN=$((CURSITE+1))
	cat <<EOF >>UBB
"${CFG_UNAME[${CURSITE}]}"	LMID=SITE${SN}
	TUXDIR="${CFG_ROOT[${CURSITE}]}"
	APPDIR="${CFG_APPDIR[${CURSITE}]}"
	ENVFILE="${CFG_APPDIR[${CURSITE}]}/ENVFILE"
	TLOGDEVICE="${CFG_APPDIR[${CURSITE}]}/TLOG"
	TLOGNAME=TLOG
	TUXCONFIG="${CFG_APPDIR[${CURSITE}]}/tuxconfig"
	TYPE="${CFG_TYPE[${CURSITE}]}"
	ULOGPFX="${CFG_APPDIR[${CURSITE}]}/ULOG"

EOF
	CURSITE=$((CURSITE+1))
done

#
# Create UBB/*GROUPS
#
cat <<EOF >>UBB
*GROUPS
#
# Group for Authentication Servers
#
##AUTHGRP	LMID=SITE1	GRPNO=101
 
#
# Group for Application Queue (/Q) Servers
#
##QGRP1	LMID=SITE1	GRPNO=102
##	TMSNAME=TMS_QM	TMSCOUNT=2
##	OPENINFO="TUXEDO/QM:${CFG_APPDIR[0]}/qdevice:QSP_BANKAPP"
 
#
# Group for Application Manager's Servers
#
##MGRGRP1	LMID=SITE1      GRPNO=103
 
#
# Group for Event Broker Servers
#
##EVBGRP1	LMID=SITE1      GRPNO=104

EOF

CURSITE=0
while [ ${CURSITE} -lt ${NUMSITES} ] ; do
	SN=$((CURSITE+1))
	cat <<EOF >>UBB
BANKB${SN}	LMID=SITE${SN}	GRPNO=${SN}
		TMSNAME=TMS_SQL	TMSCOUNT=2
	OPENINFO="TUXEDO/SQL:${CFG_APPDIR[${CURSITE}]}/bankdl${SN}:bankdb:readwrite"
EOF

	CURSITE=$((CURSITE+1))
done


#
# Create UBB/*NETWORK
#
if [ ${NUMSITES} -gt 1 ] ; then
	echo "*NETWORK" >>UBB
	CURSITE=0
	while [ ${CURSITE} -lt ${NUMSITES} ] ; do
		SN=$((CURSITE+1))
		cat <<EOF >>UBB
SITE${SN}	NADDR="${CFG_NW_NADDR[${CURSITE}]}"
	NLSADDR="${CFG_NW_NLSADDR[${CURSITE}]}"
EOF
	if [ -n "${CFG_NW_BRIDGE[${CURSITE}]}" ] ; then
		echo "	BRIDGE=\"${CFG_NW_BRIDGE[${CURSITE}]}\"" >>UBB
	fi
	echo >>UBB
		CURSITE=$((CURSITE+1))
	done
fi

#
# Create UBB/*SERVERS
#
cat <<EOF >>UBB
*SERVERS
#
# TUXEDO System /T server providing application specific authentication.
# Ref. AUTHSVR(5).
#
##AUTHSVR	SRVGRP=AUTHGRP	SRVID=1	RESTART=Y  GRACE=0  MAXGEN=2
##	CLOPT="-A"
 
#
# TUXEDO System /T Message Queue Manager. It is a server that enqueues and
# dequeues messages on behalf of programs calling tpenqueue(3) and
# tpdequeue(3) respectively. Ref. TMQUEUE(5).
#
##TMQUEUE	SRVGRP=QGRP1	SRVID=1	CONV=N	GRACE=0
##	CLOPT="-s QSP_BANKAPP:TMQUEUE"
 
#
# TUXEDO System /T Message Forwarding Server that forwards messages that have
# been stored using tpenqueue(3) for later processing. Ref. TMQFORWARD(5).
#
##TMQFORWARD	SRVGRP=QGRP1	SRVID=2	CONV=N	REPLYQ=N GRACE=0
##	CLOPT="-- -e -n -d -q Q_OPENACCT_LOG"

#
# TUXEDO System /T User Event Broker that manages user events by notifying
# subscribers when those events are posted. Ref. TMUSREVT(5).
#
##TMUSREVT        SRVGRP=EVBGRP1	SRVID=1	GRACE=3600
##		ENVFILE="${CFG_APPDIR[0]}/TMUSREVT.ENV"
##		CLOPT="-e tmusrevt.out -o tmusrevt.out -A --
##			-f ${CFG_APPDIR[0]}/tmusrevt.dat"
##		SEQUENCE=11

#
# TUXEDO Application Server that subscribes to certain events.
#
##ACCTMGR SRVGRP=MGRGRP1	SRVID=1
##	CLOPT="-A -o ACCTMGR.LOG -- -w 1000.00"
##		SEQUENCE=12
 
DEFAULT: RESTART=Y MAXGEN=5 REPLYQ=N CLOPT="-A"

AUDITC	SRVGRP=BANKB1	SRVID=1 CONV=Y MIN=1 MAX=10 REPLYQ=Y RQADDR="auditc"

EOF

CURSITE=0
while [ ${CURSITE} -lt ${NUMSITES} ] ; do
	SN=$((CURSITE+1))

	cat <<EOF >>UBB

XFER	SRVGRP=BANKB${SN}
	SRVID=${SN}01

ACCT	SRVGRP=BANKB${SN}
	SRVID=${SN}02

BAL	SRVGRP=BANKB${SN}
	SRVID=${SN}03

BTADD	SRVGRP=BANKB${SN}
	SRVID=${SN}04

BALC	SRVGRP=BANKB${SN}
	SRVID=${SN}05

EOF
	CURTLR=${RNG_LOW[${CURSITE}]}
	J=11
	while [ ${CURTLR} -le ${RNG_HIGH[${CURSITE}]} ] ; do
		cat <<EOF >>UBB
TLR	SRVGRP=BANKB${SN}
	SRVID=${SN}${J}
	RQADDR=tlr${SN}
	REPLYQ=Y
	CLOPT="-A -- -T ${CURTLR}00 -e 1000.00"
EOF
		CURTLR=$((CURTLR+1))
		J=$((J+1))
	done
	CURSITE=$((CURSITE+1))
done

#
# Create UBB/*SERVICES
#
cat <<EOF >>UBB
*SERVICES
DEFAULT: LOAD=50 AUTOTRAN=Y TRANTIME=30

EOF

cat <<EOF >>UBB
WITHDRAWAL	PRIO=50		ROUTING=ACCOUNT_ID
DEPOSIT		PRIO=50		ROUTING=ACCOUNT_ID
TRANSFER	PRIO=50		ROUTING=ACCOUNT_ID
INQUIRY		PRIO=50		ROUTING=ACCOUNT_ID
CLOSE_ACCT	PRIO=40		ROUTING=ACCOUNT_ID
OPEN_ACCT	PRIO=40		ROUTING=BRANCH_ID
BR_ADD		PRIO=20		ROUTING=BRANCH_ID
TLR_ADD		PRIO=20		ROUTING=BRANCH_ID
ABAL		PRIO=30		ROUTING=b_id
TBAL		PRIO=30		ROUTING=b_id
ABAL_BID	PRIO=30		ROUTING=b_id
TBAL_BID	PRIO=30		ROUTING=b_id
ABALC_BID	PRIO=30		ROUTING=b_id
TBALC_BID	PRIO=30		ROUTING=b_id

EOF

#
# Output the header for the *ROUTING section.
#
cat <<EOF >>UBB
*ROUTING

EOF

#
# Output the routing criteria for ACCOUNT_ID routing.
#
cat <<EOF >>UBB
ACCOUNT_ID	FIELD=ACCOUNT_ID
		BUFTYPE="FML"
EOF
echo "\t\tRANGES=\"\c" >>UBB
I=0
BANKH_SITEREP=
while [ ${I} -lt ${NUMSITES} ] ; do
	if [ ${I} -gt 0 ] ; then
		echo ",\c" >>UBB
		BANKH_SITEREP="${BANKH_SITEREP}, "
	fi
	echo "${RNG_LOW[${I}]}0000-${RNG_HIGH[${I}]}9999:BANKB$((I+1))\c" \
		>>UBB
	BANKH_SITEREP="${BANKH_SITEREP}${RNG_LOW[${I}]}"
	I=$((I+1))
done
echo ",*:*\"" >>UBB

#
# Output the routing criteria for BRANCH_ID routing.
#
cat <<EOF >>UBB
BRANCH_ID	FIELD=BRANCH_ID
		BUFTYPE="FML"
EOF
echo "\t\tRANGES=\"\c" >>UBB
I=0
while [ ${I} -lt ${NUMSITES} ] ; do
	if [ ${I} -gt 0 ] ; then
		echo ",\c" >>UBB
	fi
	echo "${RNG_LOW[${I}]}-${RNG_HIGH[${I}]}:BANKB$((I+1))\c" \
		>>UBB
	I=$((I+1))
done
echo ",*:*\"" >>UBB

#
# Output the routing criteria for b_id routing.
#
cat <<EOF >>UBB
b_id		FIELD=b_id
		BUFTYPE="VIEW:aud"
EOF
echo "\t\tRANGES=\"\c" >>UBB
I=0
while [ ${I} -lt ${NUMSITES} ] ; do
	if [ ${I} -gt 0 ] ; then
		echo ",\c" >>UBB
	fi
	echo "${RNG_LOW[${I}]}-${RNG_HIGH[${I}]}:BANKB$((I+1))\c" \
		>>UBB
	I=$((I+1))
done
echo ",*:*\"" >>UBB

#
# Now update the bank.h file for building things, this makes the audit stuff
# work.
#
if [ "${VERBOSE}" = "y" ] ; then
	echo "\n\t`uname -n`\t: Modifying bank.h to reflect configuration"
fi
chmod u+w bank.h
ed bank.h <<-EOF >/dev/null
	g/^#define[ 	]*SITEREP.*$/s//#define SITEREP { ${BANKH_SITEREP} }/
	g/^#define[ 	]*NSITE.*$/s//#define NSITE ${NUMSITES}/
	g/^#define[ 	]*DTPB.*$/s//#define DTPB 1/
	w
	q
	EOF

#
# Ok, now create the bankvar.mp<#> files for each processor.
#
I=0
while [ ${I} -lt ${NUMSITES} ] ; do
	J=$((I+1))
	echo "\t`uname -n`\t: Creating bankvar.mp${J} for ${CFG_UNAME[${I}]}"
	sed	-e "s;^TUXDIR=.*$;TUXDIR=${CFG_ROOT[${I}]};g" \
		-e "s;^APPDIR=.*$;APPDIR=${CFG_APPDIR[${I}]};g" \
		-e "s;^DIPCKEY=.*$;DIPCKEY=${DIPCKEY};g" \
		-e "s;^NADDR=.*$;NADDR=${CFG_NW_NADDR[${I}]};g" \
		-e "s;^NLSADDR=.*$;NLSADDR=${CFG_NW_NLSADDR[${I}]};g" \
		-e "s;^NDEVICE=.*$;NDEVICE=${CFG_NW_BRIDGE[${I}]};g" \
		-e "s;^TERM=.*$;TERM=\${TERM:-${TERM}};g" \
		-e "s;^BLKSIZE=.*$;BLKSIZE=${CFG_BLKSIZE[${I}]};g" \
		-e "s;^UNAME=.*$;UNAME=${CFG_UNAME[${I}]};g" \
		-e "s;^FSCONFIG=.*$;FSCONFIG=${CFG_APPDIR[${I}]}/bankdl${J};g" \
	bankvar >bankvar.mp${J}
	I=${J}
done

#
# Ok, now create the BANKAPP.mk<#> files for each processor.
#
I=0
while [ ${I} -lt ${NUMSITES} ] ; do
	J=$((I+1))
	echo "\t`uname -n`\t: Creating BANKAPP.mk${J} for ${CFG_UNAME[${I}]}"
	sed	-e "s;^TUXDIR=.*$;TUXDIR=${CFG_ROOT[${I}]};g" \
		-e "s;^APPDIR=.*$;APPDIR=${CFG_APPDIR[${I}]};g" \
	bankapp.mk >BANKAPP.mk${J}
	I=${J}
done
