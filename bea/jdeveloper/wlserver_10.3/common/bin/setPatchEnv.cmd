@rem ****************************************************************************
@rem This script is used to set up the patch environment and should only be called
@rem from commEnv or after commEnv has already been loaded.
@rem
@rem It sets the following variables:
@rem PATCH_CLASSPATH         - WebLogic system classpath patch
@rem PATCH_LIBPATH           - Library path used for patches
@rem PATCH_PATH              - Path used for patches
@rem WEBLOGIC_EXTENSION_DIRS - Extension dirs for WebLogic classpath patch
@rem
@rem For additional information, refer to the WebLogic Server Administration
@rem Guide (http://e-docs.bea.com/wls/docs70/adminguide/startstop.html).
@rem ****************************************************************************

SET  WLS1034_PATCH_CLASSPATH=%BEA_HOME%\patch_wls1034\profiles\default\sys_manifest_classpath\weblogic_patch.jar

SET  WLS1034_PATCH_EXT_DIR=%BEA_HOME%\patch_wls1034\profiles\default\sysext_manifest_classpath

SET  WLS1034_PATCH_LIBPATH=%BEA_HOME%\patch_wls1034\profiles\default\native

SET  WLS1034_PATCH_PATH=%BEA_HOME%\patch_wls1034\profiles\default\native

SET  JDEV1111_PATCH_CLASSPATH=%BEA_HOME%\patch_jdev1111\profiles\default\sys_manifest_classpath\weblogic_patch.jar

SET  JDEV1111_PATCH_EXT_DIR=%BEA_HOME%\patch_jdev1111\profiles\default\sysext_manifest_classpath

SET  JDEV1111_PATCH_LIBPATH=%BEA_HOME%\patch_jdev1111\profiles\default\native

SET  JDEV1111_PATCH_PATH=%BEA_HOME%\patch_jdev1111\profiles\default\native


if "%PATCH_CLASSPATH%" == "" set PATCH_CLASSPATH=%WLS1034_PATCH_CLASSPATH%;%JDEV1111_PATCH_CLASSPATH%

if "%WEBLOGIC_EXTENSION_DIRS%" == "" set WEBLOGIC_EXTENSION_DIRS=%WLS1034_PATCH_EXT_DIR%;%JDEV1111_PATCH_EXT_DIR%

if "%PATCH_LIBPATH%" == "" set PATCH_LIBPATH=%WLS1034_PATCH_LIBPATH%;%JDEV1111_PATCH_LIBPATH%

if "%PATCH_PATH%" == "" set PATCH_PATH=%WLS1034_PATCH_PATH%;%JDEV1111_PATCH_PATH%

