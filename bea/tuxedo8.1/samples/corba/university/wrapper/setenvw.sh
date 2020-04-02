#!/bin/ksh
# -----------------------------------------------------------------
#
# setenvw.sh
#
# Unix script to set environment variables needed to build and
# run the university sample application
#
# Edit any item beginning with the text "MY_" to reflect your
# particular site configuration data.
#
# Also, check that the values of TUXDIR, ORACLE_HOME
# and JDKDIR are correct (this file contains typical values)
#
# BEA Systems Inc. sample code
#
# -----------------------------------------------------------------

# Pathname of your copy of this sample application.
# Must match "APPDIR" in "ubb_w.mk"
#
APPDIR=${HOME}/MY_APP_DIR

# Pathname of the tuxconfig file.
# Must match "TUXCONFIG" in "ubb_w.mk"
#
TUXCONFIG=${APPDIR}/tuxconfig

# Pathname of the transaction log.
# Must match "TLOGDEVICE" in "ubb_w.mk"
#
TLOGDEVICE=${APPDIR}/TLOG

# Pathname of the Tuxedo installation.
# Must match "TUXDIR" in "ubb_w.mk"
#
if [ "$TUXDIR" = "" ]
then
    TUXDIR="/usr/local/tuxdir"
    echo "Warning : TUXDIR not set."
    echo "          Using $TUXDIR"
fi

# Directory of the ORACLE installation.
if [ "$ORACLE_HOME" = "" ]
then
    ORACLE_HOME="/usr/local/oracle"
    echo "Warning : ORACLE_HOME not set."
    echo "          Using $ORACLE_HOME"
fi

export APPDIR TUXCONFIG TUXDIR ORACLE_HOME

SYSTEM=`uname -s`

#   Directory of the JDK 1.2 installation
if [ "${JAVA_HOME}" != "" ]
then
    JDKDIR=${JAVA_HOME}
fi
if [ "$JDKDIR" = "" ]
then
    JDKDIR="/usr/local/jdk1.2"
    echo "Warning : JDKDIR not set."
    echo "          Using $JDKDIR"
fi

#   Typical path
PATH=${ORACLE_HOME}/bin:${PATH}
PATH=${JDKDIR}/bin:${PATH}
PATH=${TUXDIR}/bin:${PATH}
PATH=${APPDIR}:${PATH}

#   Typical class path
CLASSPATH=.:${CLASSPATH}
CLASSPATH=${TUXDIR}/udataobj/java/jdk/m3envobj.jar:${CLASSPATH}
CLASSPATH=${APPDIR}:${CLASSPATH}

#   Idl to java command
IDLTOJAVA=idltojava

# For client-only machines, the address of the server's listener must be
# specified in the "TOBJADDR" environment variable. It must exactly match
# (including case) the host and port specified in the server's ubb file.
TOBJADDR=//MY_MACHINE:MY_PORT_NUMBER

export JDKDIR CLASSPATH PATH IDLTOJAVA TOBJADDR

# System specific shared lib paths and compiler flags

case ${SYSTEM} in
	HP-UX)	SHLIB_PATH=${TUXDIR}/lib:${ORACLE_HOME}/lib:${JDKDIR}/lib
		CCMPL=cc
		CPPCMPL=aCC
		CPPINC=/opt/aCC/include
		case `uname -m` in
		ia64) SYSFLAGS="+DD64 +Olit=all" 
		      CPPINC="/opt/aCC/include include=/opt/aCC/include/iostream"
		      ;;
		*) SYSFLAGS="+DA1.1 +DS1.0 -DD32" ;;
		esac
#               Compile flag for ANSI C needed for cc on HP-UX B.10.20
                OSREV=`uname -r`
                if [ "$OSREV" = "B.10.20" ]
                then
                   ANCFLAGS="-Ae"
                fi

		PATH=${PATH}:/opt/aCC/bin

#               Userid/Password of the default ORACLE database.
		DEF_USERID="scott/tiger@lcs901"

#               ORACLE_SID specific to your ORACLE installation.
		DEF_ORACLE_SID="ORC1"
	;;

	SunOS)	LD_LIBRARY_PATH=${TUXDIR}/lib:${ORACLE_HOME}/lib:${JDKDIR}/lib:.
		CCMPL=cc
		CPPCMPL="CC"

		if [ -d /opt/SUNWspro/WS6/bin ]
		then
		    PATH=${PATH}:/usr/ccs/bin:/opt/SUNWspro/WS6/bin
		    CPPINC=/opt/SUNWspro/WS6/include/CCios
		else
		    PATH=${PATH}:/usr/ccs/bin:/usr/opt/SUNWspro/WS6/bin
		    CPPINC=/usr/opt/SUNWspro/WS6/include/CCios
		fi

		DEF_USERID="system/manager"
		DEF_ORACLE_SID="TORC"
	;;

	AIX)	PATH=.:${JDKDIR}/jre/sh:${JDKDIR}/sh:${ORACLE_HOME}/bin:/usr/ibmcxx/bin:${PATH}:$TUXDIR/bin
		JRELIB=${JDKDIR}/jre/bin
		JAVALIB=${JRELIB}:${JRELIB}/classic
		LIBPATH=.:${TUXDIR}/lib:${JAVALIB}:${ORACLE_HOME}/lib
		CCMPL=cc_r
		CPPCMPL=xlC_r
		CXXFLAGS="-brtl"
		LANG="C"

		if [ `uname -r` = "3" ]
		then
		    CPPINC=/usr/ibmcxx/include
		else
		    CPPINC=/usr/lpp/xlC/include
		fi

		DEF_USERID="system/manager"
		DEF_ORACLE_SID="ORC1"
	;;

	OSF1)	LD_LIBRARY_PATH=${TUXDIR}/lib:${ORACLE_HOME}/lib:${JDKDIR}/lib:.
		SYSFLAGS=-DA_OSF
		CCMPL=cc
		CPPCMPL=cxx
		CPPINC=/usr/include/cxx

		DEF_USERID="scott/tiger"
		DEF_ORACLE_SID="ORC1"
	;;

	DYNIX/ptx)	LD_LIBRARY_PATH=${TUXDIR}/lib:${ORACLE_HOME}/lib:${JDKDIR}/lib:.
		CCMPL=cc
		CPPCMPL=c++
		CPPINC=/opt/ptxC++/include/cfront
		CXXFLAGS="-version3 -tpautooff -std -eh"
		DEF_USERID=scott/tiger
		DEF_ORACLE_SID=ORCL
	;;

	IRIX64)	LD_LIBRARY_PATH=${TUXDIR}/lib:${ORACLE_HOME}/lib:${JDKDIR}/lib:.
		CCMPL=cc
		CPPCMPL=CC
		CPPINC=/usr/include/CC
		CXXFLAGS="-o32 -exceptions"
		DEF_USERID=scott/tiger
		DEF_ORACLE_SID=ORCL
	;;
	Linux)
		LD_LIBRARY_PATH=${TUXDIR}/lib:${ORACLE_HOME}/lib:${JDKDIR}/lib:.
		SYSFLAGS=-Dlinux
		CCMPL=cc
		CPPCMPL="g++"
		CPPINC=/usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include
		DEF_USERID="system/manager"
		DEF_ORACLE_SID=TORC
	;;
esac

if [ "$USERID" = "" ]
then
    USERID=$DEF_USERID
    echo "Warning : USERID not set."
    echo "          Using $USERID"
fi

if [ "$ORACLE_SID" = "" ]
then
    ORACLE_SID=$DEF_ORACLE_SID
    echo "Warning : ORACLE_SID not set."
    echo "          Using $ORACLE_SID"
fi

export CCMPL CPPCMPL CPPINC ANCFLAGS SHLIB_PATH LD_LIBRARY_PATH
export PATH LIBPATH SYSFLAGS CXXFLAGS LANG USERID ORACLE_SID
