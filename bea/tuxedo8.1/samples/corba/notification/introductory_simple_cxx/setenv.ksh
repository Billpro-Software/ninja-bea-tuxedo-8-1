#!/bin/ksh
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.

#---------------------------------------------------------------------
#
# setenv.ksh
#
# Unix script which sets the environment variables needed to build
# and run the introductory simple events c++ sample
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

# make sure that TUXDIR has been set
if [ "${TUXDIR}" = "" ]; then
    echo ERROR : The TUXDIR environment variable is not defined
    return 1
fi

# setup the standard environment variables

export APPDIR="`pwd`"
export HOST="`uname -n`"
export DOMAIN_PORT="2359"
export DOMAIN_IPCKEY="52359"
export NLSPATH="${TUXDIR}/locale/C"
export TOBJADDR="//${HOST}:${DOMAIN_PORT}"
export PATH="${TUXDIR}/bin:${APPDIR}:${PATH}"
export TUXCONFIG="${APPDIR}/tuxconfig"

# make sure the appropriate directories are in the search path

export ADD_TO_PATH=${APPDIR}
if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
    export PATH="${ADD_TO_PATH}:${PATH}"
fi

export ADD_TO_PATH=${TUXDIR}/bin
if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
    export PATH="${ADD_TO_PATH}:${PATH}"
fi

# setup platform specific build tools
# these are default values that you may need to modify

export SYSTEM=`uname -s`
case ${SYSTEM} in
  HP-UX)
    export SHLIB_PATH="${TUXDIR}/lib"
    export CPPCMPL="aCC"
    export CPPINC="/opt/aCC/include/CC"
    export SYSFLAGS="+DA1.1 +DS1.0"
    ;;
  SunOS)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="CC"
    export CPPINC="."
    export ADD_TO_PATH=/usr/ccs/bin
    if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
        export PATH="${ADD_TO_PATH}:${PATH}"
    fi
    export ADD_TO_PATH=/opt/SUNWspro/SC5.0/bin
    if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
        export PATH="${ADD_TO_PATH}:${PATH}"
    fi
    ;;
  AIX)
    export LIBPATH="${TUXDIR}/lib"
    export CPPCMPL="xlC"
    export CPPINC="/usr/lpp/xlC/include"
    export LANG="C"
    ;;
  OSF1)
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="cxx"
    export CPPINC="/usr/include/cxx"
    ;;
  Linux)
    export LD_LIBRARY_PATH="${TUXDIR}/lib"
    export CPPCMPL="g++"
    export LANG="C"
    ;;
  ReliantUNIX-N)
    export LD_LIBRARY_PATH="${TUXDIR}/lib"
    export CPPCMPL="CC"
    export LANG="C"
    ;;
esac

# the notification samples' common directory:
export COMMONDIR="${APPDIR}/../common"

# export a variable which indicates that this script has been run.
# the makefiles check that this variable has been set
export INTRO_SIMPLE_CXX_SETUP="yes"
