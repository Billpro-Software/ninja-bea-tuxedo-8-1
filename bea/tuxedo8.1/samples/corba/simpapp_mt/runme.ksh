#!/bin/ksh
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# -----------------------------------------------------------------
#
# runme.ksh
#
# NT script to build nd run the simpapp_mt sample application
#
# BEA Systems Inc. sample code
#
# -----------------------------------------------------------------

# Check that the user properly called this script.
if [ "${#}" != "0" ]; then
    echo "Syntax : ${0}"
    exit 1
fi

# Check that the TUXDIR environment variable is defined.
if [ "${TUXDIR}" = "" ]; then
    echo Error : The TUXDIR environment variable is not defined
    exit 1
fi

# Check that TUXDIR is an absolute pathname
# (that is, it starts with "/").
if [ "`echo ${TUXDIR} | grep "^/"`" = "" ]; then
    echo Error : The TUXDIR environment variable is not an absolute pathname
    exit 1
fi

# If the user hasn't specified HOST, PORT or IPCKEY,
# then use these defaults.
export HOST="${HOST:-`uname -n`}"
export PORT="${PORT:-2468}"
export IPCKEY="${IPCKEY:-55432}"

echo "Testing simpapp_mt"

# APPDIR is a special environment variable that is used when
# running server apps. It needs to be set to the absolute
# pathname of the current working directory.
export APPDIR="`pwd`"

# TOBJADDR is another special environment variable that
# is used when running remote C++ clients.
export TOBJADDR="//${HOST}:${PORT}"

# Set environment variables that are only used by this
# application.

# Did we encounter an error while running this script?
export ERROR=""

# Shortcut for calling "make".
export MAKE="make -f makefile.mk"

# The pathname of directory we're going to store the
# results of running this script in.
export RESULTSDIR="${APPDIR}/results"

# The pathname of the log file used to capture the
# output of running this script.
export LOG="${RESULTSDIR}/log"

# The pathname of the setenv.ksh file.
export SETENV="${RESULTSDIR}/setenv.ksh"

# The pathname of the configuration file.
export UBB="${RESULTSDIR}/ubb"

# The pathname of the client input file.
export INPUT="${RESULTSDIR}/input"

# The pathname of the client output file.
export OUTPUT="${RESULTSDIR}/output"

# The pathname of the expected client output file.
export EXPECTED_OUTPUT="${RESULTSDIR}/expected_output"

# TUXCONFIG is another special environment variable that
# is used to find the configuration file.
export TUXCONFIG="${RESULTSDIR}/tuxconfig"

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

# Make sure that the proper bin directories are in "PATH".
export ADD_TO_PATH=${TUXDIR}/bin
if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
    export PATH="${ADD_TO_PATH}:${PATH}"
fi

# How to build depends on which Unix system we're on.
export SYSTEM=`uname -s`
case ${SYSTEM} in
  HP-UX)
    export SHLIB_PATH="${TUXDIR}/lib"
    ;;
  SunOS)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    ;;
  AIX)
    export LIBPATH="${TUXDIR}/lib"
    ;;
  OSF1)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    ;;
  DYNIX/ptx)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    ;;
  IRIX64)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    ;;
  Linux)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    ;;
esac

# Cleanup in case this isn't the first time this
# script is has been run.
eval ${MAKE} clean >/dev/null 2>&1
echo "    cleaned up"

# Make a directory to capture the results from running
# this script.
mkdir ${RESULTSDIR} >/dev/null 2>&1

# Make a "setenv.ksh" file so that the user can
# manually build and run this sample later on.
cat <<_SETENV_ >${SETENV}
#!/bin/ksh
export TUXDIR="${TUXDIR}"
export TOBJADDR="${TOBJADDR}"
export APPDIR="${APPDIR}"
export TUXCONFIG="${TUXCONFIG}"
export PATH="${PATH}"
export RESULTSDIR="${RESULTSDIR}"
export SHLIB_PATH="${SHLIB_PATH}"
export LIBPATH="${LIBPATH}"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}"
_SETENV_

chmod +x ${SETENV}

# Make the "ubb" configuration file for this sample.

cat <<_UBB_ >${UBB}
*RESOURCES
    IPCKEY    ${IPCKEY}
    DOMAINID  simpapp
    MASTER    SITE1
    MODEL     SHM
    LDBAL     N
*MACHINES
    "${HOST}"
        LMID         = SITE1
        APPDIR       = "${APPDIR}"
        TUXCONFIG    = "${TUXCONFIG}"
        TUXDIR       = "${TUXDIR}"
        MAXWSCLIENTS = 10
        MAXACCESSERS = 200
*GROUPS
    SYS_GRP
        LMID    = SITE1
        GRPNO   = 1
    APP_GRP1
        LMID    = SITE1
        GRPNO   = 2
    APP_GRP2
        LMID    = SITE1
        GRPNO   = 3
*SERVERS
    DEFAULT:
        RESTART = Y
        MAXGEN  = 5
    TMSYSEVT
        SRVGRP  = SYS_GRP
        SRVID   = 1
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 2
        CLOPT   = "-A -- -N -M"
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 3
        CLOPT   = "-A -- -N"
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 4
        CLOPT   = "-A -- -F"
   simple_per_object_server
        SRVGRP  = APP_GRP1
        SRVID   = 1 
        MINDISPATCHTHREADS = 10
        MAXDISPATCHTHREADS = 100
        CONCURR_STRATEGY = PER_OBJECT
        RESTART = N
    simple_per_request_server
        SRVGRP  = APP_GRP2
        SRVID   = 2
        MINDISPATCHTHREADS = 10
        MAXDISPATCHTHREADS = 100
        CONCURR_STRATEGY = PER_REQUEST
        RESTART = N
    ISL
        SRVGRP  = SYS_GRP
        SRVID   = 5
        CLOPT   = "-A -- -n ${TOBJADDR}"
*SERVICES
_UBB_

# Make a file containing the user input for the client.
cat <<_INPUT_ >${INPUT}
4
AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz
AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz
_INPUT_
# Make a file with the expected output from the client.
cat <<_EXPECTED_OUTPUT_ >${EXPECTED_OUTPUT}
native
Number of simultaneous requests to post (1-50)? String to convert using thread-per-request server?Sending 4 deferred forward_lower requests
forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
Sending 4 deferred forward_upper requests
forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
String to convert using thread-per-object server?Sending 4 deferred forward_lower requests
forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
Sending 4 deferred forward_upper requests
forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
remote
Number of simultaneous requests to post (1-50)? String to convert using thread-per-request server?Sending 4 deferred forward_lower requests
forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
Sending 4 deferred forward_upper requests
forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
String to convert using thread-per-object server?Sending 4 deferred forward_lower requests
forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
Sending 4 deferred forward_upper requests
forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
_EXPECTED_OUTPUT_

echo "    prepared"

# Build the sample.
eval ${MAKE} >> ${LOG} 2>&1
if [ "${?}" = "0" ]; then
    echo "    built"
else
    echo "    build error"
    export ERROR="y"
fi

# Load the configuration file.
if [ "${ERROR}" = "" ]; then
    tmloadcf -y ${UBB} >> ${LOG} 2>&1
    if [ "${?}" = "0" ]; then
        echo "    loaded ubb"
    else
        echo "    configuration error"
        export ERROR="y"
    fi
fi

# Startup the server.
if [ "${ERROR}" = "" ]; then
    export SHUTDOWN="y"
    tmboot -y >>${LOG} 2>&1
    if [ "${?}" = "0" ]; then
        echo "    booted"
    else
        echo "    boot error"
        export ERROR="y"
    fi
fi

# Run the client and capture the output.
if [ "${ERROR}" = "" ]; then
    echo "native"                             > ${OUTPUT}
    simple_client                 < ${INPUT} >> ${OUTPUT} 2>&1
    echo "remote"                            >> ${OUTPUT}
    simple_client -ORBid BEA_IIOP < ${INPUT} >> ${OUTPUT} 2>&1
    diff -b ${EXPECTED_OUTPUT} ${OUTPUT} >/dev/null 2>&1
    if [ "${?}" = "0" ]; then
        echo "    ran"
    else
        echo "    run error"
        export ERROR="y"
    fi
fi

# Shutdown the server
if [ "${SHUTDOWN}" = "y" ]; then
    tmshutdown -y >>${LOG} 2>&1
    if [ "${?}" = "0" ]; then
        echo "    shutdown"
    else
        echo "    shutdown error"
        export ERROR="y"
    fi
fi

# Capture logs, etc. that are created when the sample is run.
mv ULOG*  ${RESULTSDIR} >/dev/null 2>&1
mv *.trc  ${RESULTSDIR} >/dev/null 2>&1
mv *.dat  ${RESULTSDIR} >/dev/null 2>&1
mv stdout ${RESULTSDIR} >/dev/null 2>&1
mv stderr ${RESULTSDIR} >/dev/null 2>&1
echo "    saved results"

# Tell the user whether or not we successfully ran the sample.
if [ "${ERROR}" = "" ]; then
    echo "  PASSED"
else
    echo "  FAILED"
fi
