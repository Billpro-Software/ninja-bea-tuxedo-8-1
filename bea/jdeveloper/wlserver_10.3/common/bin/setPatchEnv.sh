# ****************************************************************************
# This script is used to set up the patch environment and should only be called
# from commEnv or after commEnv has already been loaded.
#
# It sets the following variables:
# PATCH_CLASSPATH         - WebLogic system classpath patch
# PATCH_LIBPATH           - Library path used for patches
# PATCH_PATH              - Path used for patches
# WEBLOGIC_EXTENSION_DIRS - Extension dirs for WebLogic classpath patch
#
# For additional information, refer to the WebLogic Server Administration
# Guide (http://e-docs.bea.com/wls/docs70/adminguide/startstop.html).
# ****************************************************************************

WLS1034_PATCH_CLASSPATH=${BEA_HOME}/patch_wls1034/profiles/default/sys_manifest_classpath/weblogic_patch.jar

WLS1034_PATCH_EXT_DIR=${BEA_HOME}/patch_wls1034/profiles/default/sysext_manifest_classpath

WLS1034_PATCH_LIBPATH=${BEA_HOME}/patch_wls1034/profiles/default/native

WLS1034_PATCH_PATH=${BEA_HOME}/patch_wls1034/profiles/default/native

JDEV1111_PATCH_CLASSPATH=${BEA_HOME}/patch_jdev1111/profiles/default/sys_manifest_classpath/weblogic_patch.jar

JDEV1111_PATCH_EXT_DIR=${BEA_HOME}/patch_jdev1111/profiles/default/sysext_manifest_classpath

JDEV1111_PATCH_LIBPATH=${BEA_HOME}/patch_jdev1111/profiles/default/native

JDEV1111_PATCH_PATH=${BEA_HOME}/patch_jdev1111/profiles/default/native


export WLS1034_PATCH_CLASSPATH WLS1034_PATCH_EXT_DIR WLS1034_PATCH_LIBPATH WLS1034_PATCH_PATH

export JDEV1111_PATCH_CLASSPATH JDEV1111_PATCH_EXT_DIR JDEV1111_PATCH_LIBPATH JDEV1111_PATCH_PATH

if [ "${PATCH_CLASSPATH}" = "" ]; then
    PATCH_CLASSPATH=${WLS1034_PATCH_CLASSPATH}${CLASSPATHSEP}${JDEV1111_PATCH_CLASSPATH}
fi

if [ "${WEBLOGIC_EXTENSION_DIRS}" = "" ]; then
    WEBLOGIC_EXTENSION_DIRS=${WLS1034_PATCH_EXT_DIR}${PATHSEP}${JDEV1111_PATCH_EXT_DIR}
fi

if [ "${PATCH_LIBPATH}" = "" ]; then
    PATCH_LIBPATH=${WLS1034_PATCH_LIBPATH}${PATHSEP}${JDEV1111_PATCH_LIBPATH}
fi

if [ "${PATCH_PATH}" = "" ]; then
    PATCH_PATH=${WLS1034_PATCH_PATH}${PATHSEP}${JDEV1111_PATCH_PATH}
fi


export PATCH_CLASSPATH WEBLOGIC_EXTENSION_DIRS PATCH_LIBPATH PATCH_PATH
