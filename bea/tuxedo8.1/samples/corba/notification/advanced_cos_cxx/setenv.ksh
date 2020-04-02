#!/bin/ksh
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.

#---------------------------------------------------------------------
#
# setenv.ksh
#
# Unix script which sets the environment variables needed to build
# and run the advanced cos notification c++ sample
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
export DOMAIN_PORT="2365"
export DOMAIN_IPCKEY="52365"
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

# variables for setting up the queues
export QUE_IPCKEY="52465"
export QMCONFIG="${APPDIR}/QUE"

# variables for locating the FML field definitions (enables data filtering)
export FLDTBLDIR32="${COMMONDIR}"
export FIELDTBLS32="news_flds"

# export a variable which indicates that this script has been run.
# the makefiles check that this variable has been set
export ADVANCED_COS_CXX_SETUP="yes"
