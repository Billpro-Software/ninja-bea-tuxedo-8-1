#!/bin/ksh

#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# setenv.ksh
#
# Unix script which sets the environment variables needed to build
# and run the interceptor c++ sample
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

export APPDIR="`pwd`/app_cxx"
export HOST="`uname -n`"
export DOMAIN_PORT="2365"
export DOMAIN_IPCKEY="42365"
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

# the interceptor samples' common directory:
export COMMONDIR="${APPDIR}/../common"

# setup platform specific build tools
# these are default values that you may need to modify

export SYSTEM=`uname -s`
case ${SYSTEM} in
  HP-UX)
    export MAKEFILE_PREFIX=hpux
    export SHLIB_PATH="${TUXDIR}/lib"
    export CPPCMPL="aCC"
    export CPPINC="/opt/aCC/include/CC"
    export SYSFLAGS="+DA1.1 +DS1.0 +Z "
    export CPPFLAGS="${SYSFLAGS} -D_REENTRANT -I. -I${CPPINC} -I${TUXDIR}/include -I${COMMONDIR} "
    ;;
  SunOS)
    export MAKEFILE_PREFIX=solaris
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="CC"
    export CPPINC="."
    export ADD_TO_PATH=/usr/ccs/bin
    if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
        export PATH="${ADD_TO_PATH}:${PATH}"
    fi
    export ADD_TO_PATH=/opt/SUNWspro/bin
    if [ "`echo ${PATH} | grep ${ADD_TO_PATH}`" = "" ]; then
        export PATH="${ADD_TO_PATH}:${PATH}"
    fi
    export SYSFLAGS=" "
    export CPPFLAGS="${SYSFLAGS} -D_REENTRANT -I. -I${CPPINC} -I${TUXDIR}/include -I${COMMONDIR}"
    ;;
  AIX)
    export MAKEFILE_PREFIX=aix
    export LIBPATH="${TUXDIR}/lib"
    export CPPCMPL="xlC"
    export CPPINC="/usr/lpp/xlC/include"
    export LANG="C"
    export SYSFLAGS=" "
    export CPPFLAGS="${SYSFLAGS} -D_REENTRANT -I. -I${CPPINC} -I${TUXDIR}/include -I${COMMONDIR}"
    ;;
  OSF1)
    export MAKEFILE_PREFIX=osf
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="cxx"
    export CPPINC="/usr/include/cxx"
    export SYSFLAGS="-g  "
    export CPPFLAGS="${SYSFLAGS} -D_REENTRANT -I. -I${CPPINC} -I${TUXDIR}/include -I${COMMONDIR}"
    ;;
  IRIX64)
    export MAKEFILE_PREFIX=sgi
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="CC"
    export CPPINC="-KPIC -o32 -exceptions "
    export SYSFLAGS=" "
    export CPPFLAGS="${SYSFLAGS} -D_REENTRANT -I. ${CPPINC} -I${TUXDIR}/include -I${COMMONDIR}"
    ;;
  DYNIX/ptx)
    export MAKEFILE_PREFIX=sequent
    export LD_LIBRARY_PATH="${TUXDIR}/lib:."
    export CPPCMPL="c++"
    export CPPINC="-KPIC -o32 -exceptions "
    export SYSFLAGS="-trdforinit -version3 -eh -rtti -tpautooff -std -KPIC -Dsys5"
    export CPPFLAGS="${SYSFLAGS} -D_REENTRANT -I. -I${CPPINC} -I${TUXDIR}/include -I${COMMONDIR}"
    ;;
  Linux)
    export MAKEFILE_PREFIX=linux
    export LD_LIBRARY_PATH="${TUXDIR}/lib"
    export CPPCMPL="g++"
    export CPPINC="/usr/include"
    export SYSFLAGS=" "
    export CPPFLAGS="${SYSFLAGS} -D_REENTRANT -I. -I${CPPINC} -I${TUXDIR}/include -I${COMMONDIR} "
    ;;
esac

# export a variable which indicates that this script has been run.
# the makefiles check that this variable has been set
export INTERCEPTOR_CXX_SETUP="yes"
