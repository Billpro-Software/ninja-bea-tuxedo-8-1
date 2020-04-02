#!/bin/ksh
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# -----------------------------------------------------------------
#
# runme.ksh
#
# Unix script to build and run the simpapp_par sample application
#
# BEA Systems Inc. sample code
#
# -----------------------------------------------------------------

# Check that the user properly called this script.
if [ "${#}" != "0" ]; then
    echo "Syntax : ${0}"
    return 1
fi

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

# Check that JAVA_HOME is an absolute pathname when JAVA_HOME is defined
# (that is, it starts with "/").
if [ "${JAVA_HOME}" != "" ]; then
    if [ "`echo ${JAVA_HOME} | grep "^/"`" = "" ]; then
        echo Error : The JAVA_HOME environment variable is not an absolute pathname
        return 1
    fi
fi

# If the user hasn't specified HOST, PORT or IPCKEY,
# then use these defaults.
export HOST="${HOST:-`uname -n`}"
export PORT="${PORT:-2468}"
export IPCKEY="${IPCKEY:-55432}"

echo "Testing simpapp_par"

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
if [ "${JAVA_HOME}" = "" ]; then
    export BUILD_TARGET="all"
else
    export BUILD_TARGET="java_all"
fi

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

# The pathname of the client output file with the pid's stripped out
export OUTPUT_NOPID="${OUTPUT}_nopid"

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

if [ "${JAVA_HOME}" != "" ]; then
    export ADD_TO_PATH=${JAVA_HOME}/bin
    if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
        export PATH="${ADD_TO_PATH}:${PATH}"
    fi

    export CLASSPATH="${TUXDIR}/udataobj/java/jdk/m3envobj.jar:${TUXDIR}/udataobj/java/jdk/wleclient.jar:.:${CLASSPATH}"
fi

# Make sure that the proper lib directories are set
if [ "`uname -s`" = "HP-UX" ]; then
    if [ "`echo ${SHLIB_PATH} | grep ${TUXDIR}/lib`" = "" ]; then
        export SHLIB_PATH="${TUXDIR}/lib:${SHLIB_PATH}"
    fi
elif [ "`uname -s`" = "AIX" ]; then
    if [ "`echo ${LIBPATH} | grep ${TUXDIR}/lib`" = "" ]; then
        export LIBPATH="${TUXDIR}/lib:.:{LIBPATH}"
    fi
else
    if [ "`echo ${LD_LIBRARY_PATH} | grep ${TUXDIR}/lib`" = "" ]; then
        export LD_LIBRARY_PATH="${TUXDIR}/lib:.:{LD_LIBRARY_PATH}"
    fi
fi

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

if [ "${JAVA_HOME}" != "" ]; then
cat <<_JAVA_SETENV_ >>${SETENV}
export JAVA_HOME="${JAVA_HOME}"
export CLASSPATH="${CLASSPATH}"
_JAVA_SETENV_
fi

chmod +x ${SETENV}

# Make the "ubb" configuration file for this sample.
#   
cat <<_UBB_ >${UBB}
*RESOURCES
    IPCKEY    ${IPCKEY}
    DOMAINID  simpapp_par
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
    APP_GRP3
        LMID    = SITE1
        GRPNO   = 4
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
    simple_factory
        SRVGRP  = APP_GRP1
        SRVID   = 1
        RESTART = N
    simple_server
        SRVGRP  = APP_GRP2
        SRVID   = 1
        RESTART = N
    simple_server
        SRVGRP  = APP_GRP3
        SRVID   = 1
        RESTART = N
    ISL
        SRVGRP  = SYS_GRP
        SRVID   = 5
        CLOPT   = "-A -- -n ${TOBJADDR} -d /dev/tcp"
*SERVICES
_UBB_

# Make a file containing the user input for the client.
cat <<_INPUT_ >${INPUT}
AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz
_INPUT_

# Make a file with the expected output from the client.
cat <<_EXPECTED_OUTPUT_ >${EXPECTED_OUTPUT}
native
String?
AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
remote
String?
AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
_EXPECTED_OUTPUT_

if [ "${JAVA_HOME}" != "" ]; then
cat <<_JAVA_EXPECTED_OUTPUT_ >>${EXPECTED_OUTPUT}
Java remote client
String?
AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
_JAVA_EXPECTED_OUTPUT_
fi

echo "    prepared"

# Build the sample.
eval ${MAKE} ${BUILD_TARGET} >> ${LOG} 2>&1
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
    echo "native"                             > ${OUTPUT}2
    simple_client                 < ${INPUT} >> ${OUTPUT} & 2>&1
    simple_client                 < ${INPUT} >> ${OUTPUT}2 & 2>&1
    sleep 30
    echo "remote"                            >> ${OUTPUT}
    echo "remote"                            >> ${OUTPUT}2
    simple_client -ORBid BEA_IIOP < ${INPUT} >> ${OUTPUT} & 2>&1
    simple_client -ORBid BEA_IIOP < ${INPUT} >> ${OUTPUT}2 & 2>&1
    sleep 30
    if [ "${JAVA_HOME}" != "" ]; then
        echo "Java remote client" >> ${OUTPUT}
        echo "Java remote client" >> ${OUTPUT}2
        java -classpath ${CLASSPATH} -DTOBJADDR=${TOBJADDR} SimpleClient < ${INPUT} >> ${OUTPUT} & 2>&1
        java -classpath ${CLASSPATH} -DTOBJADDR=${TOBJADDR} SimpleClient < ${INPUT} >> ${OUTPUT}2 & 2>&1
    sleep 30
    fi

    # Get the output with PID info stripped
    egrep -v ProcessID ${OUTPUT} > ${OUTPUT_NOPID}
    egrep -v ProcessID ${OUTPUT}2 > ${OUTPUT_NOPID}2

    # Get just the pid output in one file
    grep ProcessID ${OUTPUT} > ${OUTPUT}_PIDS
    grep ProcessID ${OUTPUT}2 >> ${OUTPUT}_PIDS

    diff -b ${EXPECTED_OUTPUT} ${OUTPUT_NOPID} >/dev/null 2>&1
    if [ "${?}" != "0" ]; then
        echo "    run error"
        export ERROR="y"
    fi

    if [ "${ERROR}" != "y" ]; then
        diff -b ${EXPECTED_OUTPUT} ${OUTPUT_NOPID}2 >/dev/null 2>&1
        if [ "${?}" != "0" ]; then
            echo "    run error"
            export ERROR="y"
        fi
    fi

    if [ "${ERROR}" != "y" ]; then
        # Make sure requests hit different server processes
        # If file is same sorted forward and backward, then all 
        # process ids were equal.  This is an error.
        sort < ${OUTPUT}_PIDS > ${OUTPUT}_PIDS_SORT
        sort -r < ${OUTPUT}_PIDS > ${OUTPUT}_PIDS_REVERSE
        diff -b ${OUTPUT}_PIDS_SORT ${OUTPUT}_PIDS_REVERSE >/dev/null 2>&1
        if [ "${?}" = "0" ]; then
            echo "    run error"
            export ERROR="y"
        else
            echo "    ran"
        fi
    fi

    rm -f ${OUTPUT}_PIDS_SORT
    rm -f ${OUTPUT}_PIDS_REVERSE
    rm -f ${OUTPUT_NOPID}
    rm -f ${OUTPUT_NOPID}2
    rm -f ${OUTPUT}_PIDS

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
