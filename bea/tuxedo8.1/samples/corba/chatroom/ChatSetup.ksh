#!/bin/ksh
# -----------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# ChatSetup.ksh
#
# Script to setup the environment for the Tuxedo Chat application
# You should copy the Chat directory from the Tuxedo sample directory to
#   your own directory and then change to your directory. 
# Next, execute this command file. It will create further subdirectories 
#   as needed but expects expect that all the sources and command files
#   are at the right relative place; that is, they are in the same directory 
#   as this command file.
#
# -----------------------------------------------------------------

echo Setting up the Tuxedo Chat application


# Check that the user properly called this script.
if [ "${#}" != "0" ]; then
    echo "Syntax : ${0}"
    return 1
fi


# Shortcut for calling "make".
export MAKE="make -f ChatRoom.mk"

# Cleanup in case this isn't the first time this
# script is has been run.
%MAKE% adminclean > /dev/null 2>&1
echo "     Cleaned up the previous Tuxedo administrative setup"

# If this is the first time this file has been run, we
# need to create a subdirectory "Admin", which will 
# keep all the administrative parts of the application.
mkdir Admin >/dev/null 2>&1


# Check that the TUXDIR environment variable is defined.
if [ "${TUXDIR}" = "" ]; then
    echo Error : The TUXDIR environment variable is not defined
    return 1
fi

# Check that TUXDIR is an absolute pathname
# (that is, it starts with "/").
if [ "`echo ${TUXDIR} | grep "^/"`" = "" ]; then
    echo Error : The TUXDIR environment variable is not an absolute pathname
    return 1
fi

# If the user hasn't specified HOST, PORT or IPCKEY,
# then use these defaults.
export HOST="${HOST:-`uname -n`}"
export PORT="${PORT:-2468}"
export IPCKEY="${IPCKEY:-55432}"

# APPDIR is a special environment variable that is used
# by Tuxedo when running server apps.  It needs to be set
# to be set to the absolute pathname of the current
# working directory.
export APPDIR="`pwd`/Admin"

# TOBJADDR is another special environment variable that
# is used by Tuxedo when running remote C++ clients.
export TOBJADDR="//${HOST}:${PORT}"

# Set environment variables that are only used by this
# application.

# Did we encounter an error while running this script?
export ERROR=""

# The pathname of the log file used to capture the
# output of running this script (except the build)
export LOG=${APPDIR}/setup.log

# The pathname of the setenv.ksh file.
export SETENV="${APPDIR}/setenv.ksh"

# The pathname of the configuration file.
export UBB="${APPDIR}/ubb"

# TUXCONFIG is another special environment variable that
# is used by Tuxedo to find the configuration file.
export TUXCONFIG="${APPDIR}/tuxconfig"

# Make sure that "." is in "PATH".
if [ "`echo ${PATH} | grep "^\.:"`" = "" ]; then
    if [ "`echo ${PATH} | grep "^\.$"`" = "" ]; then
        if [ "`echo ${PATH} | grep ":\.:"`" = "" ]; then
            if [ "`echo ${PATH} | grep ":\.$"`" = "" ]; then
                export PATH=".:${PATH}"
            fi
        fi
    fi
fi

# Make sure that the proper Tuxedo directories are
# in "PATH".
export ADD_TO_PATH=${TUXDIR}/bin
if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
    export PATH="${ADD_TO_PATH}:${PATH}"
fi

# How to build depends on which Unix system we're on.
# CPPCMPL is the C++ compiler.
# CPPINC is the directory where standard C++ include files reside.
export SYSTEM=`uname -s`
case ${SYSTEM} in
  HP-UX)
    export SHLIB_PATH="${TUXDIR}/lib"
    export CPPCMPL="aCC"
    export CPPINC="/opt/aCC/include/CC"
    export SYSFLAGS="+DA1.1 +DS1.0"
	export PATH=${PATH}:/opt/aCC/bin
    ;;
  SunOS)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="CC"
    export CPPINC=.
    export SYSFLAGS=" "
    if [ -d /opt/SUNWspro/SC5.0/bin ]
    then
        export ADD_TO_PATH=/usr/ccs/bin:/opt/SUNWspro/SC5.0/bin
    else
        export ADD_TO_PATH=/usr/ccs/bin:/usr/opt/SUNWspro/SC5.0/bin
    fi
    if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
        export PATH="${ADD_TO_PATH}:${PATH}"
    fi
    ;;
  AIX)
    export LIBPATH="${TUXDIR}/lib"
    export CPPCMPL="xlC"
    export CPPINC="/usr/lpp/xlC/include"
    export LANG="C"
	if [ `uname -r` = "3" ]
	then
		export CPPINC=/usr/ibmcxx/include
		export PATH=${PATH}:/usr/ibmcxx/bin
	else
	    export CPPINC=/usr/lpp/xlC/include
	fi
    ;;
  OSF1)
	export SYSFLAGS=-DA_OSF
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="cxx"
    export CPPINC="/usr/include/cxx"
    ;;
  DYNIX/ptx)
    export SYSFLAGS="-version3 -tpautooff -std -eh"
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="c++"
    export CPPINC="/opt/ptxC++/include/cfront"
    ;;
  IRIX64)
    export SYSFLAGS="-o32 -exceptions"
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="CC"
    export CPPINC="/usr/include/CC"
    ;;
  Linux)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL=g++
    export CPPINC="/usr/include"
    ;;
  ReliantUNIX-N)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL=CC
    export CPPINC="."
    ;;
esac

# Cleanup in case this isn't the first time this
# script is has been run.
# eval ${MAKE} clean >/dev/null 2>&1
# echo "    cleaned up"

# Make a directory to capture the results from running
# this script.
mkdir ${RESULTSDIR} >/dev/null 2>&1

# Make a "setenv.ksh" file so that the user can
# manually build and run this sample later on.
cat <<_SETENV_ >${SETENV}
#!/bin/ksh
# File "setenv.ksh" is used to setup the environment without
# running ChatSetup.ksh again.
#This file automatically generated from ChatSetup.ksh of the distribution CD
#
# Pathname of the Tuxedo installation must match "TUXDIR" in UBB
export TUXDIR="${TUXDIR}"
export TOBJADDR="${TOBJADDR}"
# Pathname of admin files for the application
# Must match APPDIR in the config file (aka UBB file)
export APPDIR="${APPDIR}"
#
# Pathname of the app config file.
# Must match "TUXCONFIG" in UBB
export TUXCONFIG="${TUXCONFIG}"
#
# Typical path
export PATH="${PATH}"
export CPPCMPL="${CPPCMPL}"
export CPPINC="${CPPINC}"
export LANG="${LANG}"
export SHLIB_PATH="${SHLIB_PATH}"
export LIBPATH="${LIBPATH}"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}"
export SYSFLAGS="${SYSFLAGS}"
_SETENV_

chmod +x ${SETENV}

echo "     Created file ${SETENV} for running later"

# Make the "ubb" configuration file for this sample.
cat <<_UBB_ >${UBB}
# Configuration file for the Chat example.
# This file automatically generated from ChatSetup
#   command; change at your own risk
#
*RESOURCES
    IPCKEY    ${IPCKEY}
    DOMAINID  chatapp
    MASTER    SITE1
    MODEL     SHM
    LDBAL     N
#
*MACHINES
#
#	The name of the server machine
    "${HOST}"
        LMID         = SITE1
#
#	Pathname of default startup directory for the appl.
#	Must match "APPDIR" in the environment variables.
        APPDIR       = "${APPDIR}"
#
#	Pathname of the tuxconfig file
#	Must match "TUXCONFIG" in the environment variables.
        TUXCONFIG    = "${TUXCONFIG}"
#
#	Pathname of the Tuxedo installation.
#	Must match "TUXDIR" in the environment variables
        TUXDIR       = "${TUXDIR}"
        MAXWSCLIENTS = 10
#
*GROUPS
    SYS_GRP
        LMID    = SITE1
        GRPNO   = 1
    CHAT_GRP
        LMID    = SITE1
        GRPNO   = 2
#
*SERVERS
# List of servers started automatically at tmboot time
#
# By default, restart a server if it crashes,
#	up to 5 times in 24 hours.
    DEFAULT:
        RESTART = Y
        MAXGEN  = 5
#
# The first set of servers are systems servers, the same
#	for every Tuxedo application
#
# The first server is the Tuxedo provided System Event
#	Broker.  It must be started before the NameManager
#	Service servers.
    TMSYSEVT
        SRVGRP  = SYS_GRP
        SRVID   = 1
#
# TMFFNAME is a Tuxedo provided server that runs the 
# FactoryFinder and supporting NameManager services 
# which maintain a mapping of application-supplied 
# names to object references.
#
# Start the NameManager Service (-N option).
#	It is being started as a Master (-M option).
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 2
        CLOPT   = "-A -- -N -M"
#
# Start a slave NameManager Service
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 3
        CLOPT   = "-A -- -N"
#
# Start the FactoryFinder (-F) service
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 4
        CLOPT   = "-A -- -F"
#   This specifies the current machine
#    port number 2500 is typical
    ISL
       SRVGRP  = SYS_GRP
       SRVID   = 5
       CLOPT   = "-A -- -n ${TOBJADDR} -O"
       MIN     = 1
       MAX     = 1
#
# Server for the Chat example
#
# The chat server takes no parameters
    "`pwd`/ChatRoomServer"
        SRVGRP  = CHAT_GRP
        SRVID   = 1
        RESTART = N
#
*SERVICES
# empty

_UBB_

echo "     Created a Tuxedo configuration file in ${UBB}"

# Load the configuration file.
if [ "${ERROR}" = "" ]; then
    tmloadcf -y ${UBB} >> ${LOG} 2>&1
    if [ "${?}" = "0" ]; then
        echo "     Tuxedo loaded the configuration file successfully"
    else
        echo "     Error : unable to load the configuration file"
        export ERROR="y"
    fi
fi

# Build the sample.
if [ "${ERROR}" = "" ]; then
    echo "Starting to build the application"

    eval ${MAKE} all >> build.log 2>&1
    if [ "${?}" = "0" ]; then
cat << _SUCCESS_
Chat example code built successfully. Now Type:
      tmboot -y
Then start a chat client, giving a chat room name. For example,
      ChatClient Woods
You will be asked to give a handle. You might enter 'Smokey'.
After you're signed on, enter messages. 
You'll see messages from other chatters in that same chat room.
You can start several clients from different windows.
When you're done chatting, enter a backslash (\) and you'll be signed off.
When all chatters are signed off and you're done with the application, 
   to stop the application, type
   tmshutdown -y
_SUCCESS_
    else
        echo "     Error : encountered an error building the application"
		echo "             check build.log to see how far it got."
        export ERROR="y"
    fi
fi
