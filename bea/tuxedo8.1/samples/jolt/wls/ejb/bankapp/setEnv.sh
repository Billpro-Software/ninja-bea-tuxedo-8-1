#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# This script can be used to set up your environment for your
# own development work with WebLogic Server. This script ensures 
# that the CLASSPATH variable is set to include the WebLogic 
# Server classes and required JDK classes. It also ensures that 
# the bin directory of the WebLogic Server and JDK distributions 
# are added to the PATH variables and that the appropriate variables 
# are set for you native libraries. This script contains the 
# following variables: 
# 
# WL_HOME   - This must point to the root directory of your WebLogic 
#             installation. 
# JAVA_HOME - Determines the version of Java used to compile  
#             and run examples. This variable must point to the 
#             root directory of a complete JDK installation. See 
#             the WebLogic platform support page 
#             (http://e-docs.bea.com/wls/platforms/index.html)
#             for an up-to-date list of supported JVMs on your platform. 
# 
# jDriver for Oracle users: This script assumes that native libraries 
# required for jDriver for Oracle have been installed in the proper 
# location and that your system LD_LIBRARY_PATH variable has been set appropriately. 
# Also note that this script default to the oci816_8 version of the 
# shared libraries. If this is not the version you need, please adjust the 
# LD_LIBRARY_PATH variable accordingly. 
#
# For additional information, refer to Installing and Setting up WebLogic 
# Server (/install/index.html in your local documentation set or on the 
# Internet at http://e-docs.bea.com/wls/docs60/install/index.html). 

# Set user-defined variables.
WL_HOME=/home3/beadev/wls60sp1/wlserver6.0sp1
JAVA_HOME=/home3/beadev/wls60sp1/jdk130
export WL_HOME
export JAVA_HOME

# Check that script is being run from the appropriate directory
if [ ! -f $WL_HOME/lib/weblogic.jar ]; then
  echo "The WebLogic Server was not found in directory $WL_HOME." 1>&2

# Check for JDK
elif [ ! -f $JAVA_HOME/bin/java ]; then
  echo "The JDK was not found in directory $JAVA_HOME." 1>&2

else

CLASSPATH=$JAVA_HOME/lib/tools.jar:$WL_HOME/lib/weblogic_sp.jar:$WL_HOME/lib/weblogic.jar:$WL_HOME/lib/jolt.jar:$WL_HOME/lib/joltjse.jar:$WL_HOME/lib/joltwls.jar:$CLASSPATH
export CLASSPATH
echo "CLASSPATH=$CLASSPATH"

PATH=$WL_HOME/bin:$JAVA_HOME/jre/bin:$JAVA_HOME/bin:$PATH
export PATH
echo "PATH=$PATH"

APPLICATIONS=$WL_HOME/config/mydomain/applications
export APPLICATIONS

CLIENT_CLASSES=$WL_HOME/config/examples/clientclasses
export CLIENT_CLASSES

SERVER_CLASSES=$WL_HOME/config/examples/serverclasses
export SERVER_CLASSES

case `uname -s` in
AIX)
  if [ -n "$LIBPATH" ]; then
    LIBPATH=$LIBPATH:$WL_HOME/lib/aix
  else
    LIBPATH=$WL_HOME/lib/aix
  fi
  export LIBPATH
  echo "LIBPATH=$LIBPATH"
;;
HP-UX)
  if expr "`uname -r`" : "..11..." > /dev/null 2>&1; then
    hpsubdir=hpux11
  elif expr "`uname -r`" : "..10..." > /dev/null 2>&1; then 
    hpsubdir=hpux10
  fi
 
  if [ -n "$SHLIB_PATH" ]; then
    SHLIB_PATH=$SHLIB_PATH:$WL_HOME/lib/$hpsubdir
  else
    SHLIB_PATH=$WL_HOME/lib/$hpsubdir
  fi
  export SHLIB_PATH
  echo "SHLIB_PATH=$SHLIB_PATH"
;;
IRIX)
  if [ -n "$LD_LIBRARY_PATH" ]; then
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$WL_HOME/lib/irix
  else
    LD_LIBRARY_PATH=$WL_HOME/lib/irix
  fi
  export LD_LIBRARY_PATH
  echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
;;
LINUX|Linux)
  if [ -n "$LD_LIBRARY_PATH" ]; then
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$WL_HOME/lib/linux
  else
    LD_LIBRARY_PATH=$WL_HOME/lib/linux
  fi
  export LD_LIBRARY_PATH
  echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
;;
OSF1)
  if [ -n "$_RLD_LIST" ]; then
    _RLD_LIST=$_RLD_LIST:$WL_HOME/lib/tru64unix
  else
    _RLD_LIST=$WL_HOME/lib/tru64unix
  fi
  export _RLD_LIST
  echo "_RLD_LIST=$_RLD_LIST"
;;
SunOS)
  if [ -n "$LD_LIBRARY_PATH" ]; then
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$WL_HOME/lib/solaris:$WL_HOME/lib/solaris/oci816_8
  else
    LD_LIBRARY_PATH=$WL_HOME/lib/solaris:$WL_HOME/lib/solaris/oci816_8
  fi
    export LB_LIBRARY_PATH
  echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
;;
*)
  echo "$0: Don't know how to set the shared library path for `uname -s`.  "
esac

echo ""
echo "Your environment has been set."

fi

