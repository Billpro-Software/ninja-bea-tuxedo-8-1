#!/bin/ksh
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# -----------------------------------------------------------------
#
# runme.ksh
#
# NT script to build nd run the simple sample application
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

echo "Testing simpapp"

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

# How to build depends on which Unix system we're on.
# CPPCMPL is the C++ compiler.
# CPPINC is the directory where standard C++ include files reside.
export SYSTEM=`uname -s`
case ${SYSTEM} in
  HP-UX)
    export SHLIB_PATH="${TUXDIR}/lib"
    export CPPCMPL="aCC"
    export CPPINC="/opt/aCC/include/CC"
    ;;
  SunOS)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="CC"
    export CPPINC="."
    export ADD_TO_PATH=/usr/ccs/bin
    if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
        export PATH="${ADD_TO_PATH}:${PATH}"
    fi
    ;;
  AIX)
    export LIBPATH="${TUXDIR}/lib"
    export CPPCMPL="xlC_r"
    export CPPINC="/usr/lpp/xlC/include"
    export LANG="C"
    ;;
  OSF1)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="cxx"
    export CPPINC="/usr/include/cxx"
    ;;
  DYNIX/ptx)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL=c++
    export CPPINC=/opt/ptxC++/include/cfront
    ;;
  IRIX64)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL=CC
    export CPPINC="/usr/include/CC"
    ;;
  Linux)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL=g++
    ;;
  ReliantUNIX-N)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="CC"
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
export CPPCMPL="${CPPCMPL}"
export CPPINC="${CPPINC}"
export LANG="${LANG}"
export SHLIB_PATH="${SHLIB_PATH}"
export LIBPATH="${LIBPATH}"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}"
export SYSFLAGS="${SYSFLAGS}"
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
# To make simpapp scalable, browse through the ubb configuration file
# provided with the university production samples to help you make
# changes in the following sections, and use factory based routing.
#   
#    a) GROUPS,     instead of a single APP_GRP create two (or more)
#                   application groups eg. APP_GRP1, APP_GRP2, etc.
#    b) SERVERS,    instead of a single simple_server specify multiple
#                   simple_servers each in a separate group.
#    c) INTERFACES, specify the interface and name the criteria to be
#                   used for factory based routing.
#    d) ROUTING,    configure how the criteria should be used to
#                   perform factory based routing.
#   
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
*GROUPS
    SYS_GRP
        LMID    = SITE1
        GRPNO   = 1
    APP_GRP
        LMID    = SITE1
        GRPNO   = 2
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
    simple_server
        SRVGRP  = APP_GRP
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
String?AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz
remote
String?AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ
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
    simple_client                 < ${INPUT} >> ${OUTPUT} 2>&1
    echo "remote"                            >> ${OUTPUT}
    simple_client -ORBid BEA_IIOP < ${INPUT} >> ${OUTPUT} 2>&1
    if [ "${JAVA_HOME}" != "" ]; then
        echo "Java remote client" >> ${OUTPUT}
        java -classpath ${CLASSPATH} -DTOBJADDR=${TOBJADDR} SimpleClient < ${INPUT} >> ${OUTPUT} 2>&1
    fi
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
