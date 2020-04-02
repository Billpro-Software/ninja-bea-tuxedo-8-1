@echo off
REM mdsbeangen.bat
REM
REM
REM  DESCRIPTION
REM    This file is used to call the MDSBeanGenTool utility 
REM
REM
REM  NOTES
REM 
REM
REM
REM   MODIFIED   (MM/DD/YY)
REM   snoton      08/24/09 - #(8808215) use mds-tools.jar instead of 
REM                          setMDSclasspath
REM   snoton      02/11/09 - #(8246400) check for JAVA_HOME
REM   erwang      09/16/08 - Clean up internal references in comments
REM   dklein      06/05/07 - Use setMDSclasspath.bat
REM   gnagaraj    01/11/07 - Use commons-collections from j2ee\home\lib
REM   pwhaley     01/08/07 - Remove concurrent.jar.
REM   dklein      09/12/06 - adfshare.jar renamed to adfsharebase.jar
REM   snoton      04/11/06 - Add adfshare.jar to classpath
REM   cbarrow     04/26/06 - Add Java Object Cache to classpath 
REM   dklein      03/14/06 - Discontinue work around.
REM   dklein      03/08/06 - Added commons-collections.jar 
REM                          to classpath
REM   dklein      01/31/06 - Add to classpath libraries to get round  
REM                          the issue, and share.jar for relationship support. 
REM   ntriggs     01/24/06 - Add jars for --usemelem option
REM   spathak     09/30/05 - 
REM   azgibson    08/01/05 - Changing location of xml.jar. 
REM   hlie        05/16/05  - Changed to use mdsrt.jar.
REM   hlie        04/25/05  - Changes in library locations (el, cli, cache).
REM   jhsi        03/21/05  - jhsi_bean_gen_tool
REM   jhsi        02/25/05  - Creation
REM

:: #############################################################################
:: ##   This file should be in sync with the "mdsbeangen" shell script        ##
:: ##   Please update "mdsbeangen" when updating this file.                   ##
:: #############################################################################

setlocal

:: ------------------------------------------------------------------
:: --------- COMPUTE DELIVER. DO NOT CHANGE THIS VALUE !! ---------
:: -- DELIVER directory
:: Set DELIVER to the value of the BUILT environment setting if present (means
:: this script was called by rtmdstest.bat).  
:: Otherwise, compute it by assuming this script is being called from the
:: jdev\bin subdir of the DELIVER directory.
set DELIVER=%BUILT%
if "%BUILT%"=="" set DELIVER=%~d0%~p0..\..

if not "%JAVA_HOME%"=="" goto done_java_home
echo JAVA_HOME environment variable is not set. Default is %DELIVER%\..\jdk
set JAVA_HOME=%DELIVER%\..\jdk
:done_java_home

:: need to set the default values for variables
set verbose="n"
set logFile=%DELIVER%\mds\bin\mdstoolslog.properties

:start
if %1.==. goto done
if /i %1==--verbose goto verbose_handle
:: -- Finished processing the current parameter. Process the next parameter set
set PARAMS=%PARAMS% %1
shift
goto start

:verbose_handle
set verbose="y"
set PARAMS=%PARAMS% %1
shift
goto start

:: ----------------- Done with the parameter processing. 
:: -- Prepare to call the MDSBeanGenTool utility
:done


:: ------- Set class path
set cp=%DELIVER%\mds\bin\mdstools.jar

:: ------- PATH settings
set PATH=%JAVA_HOME%\bin;%path%

if %verbose% == "n" goto done_verbose
echo JAVA_HOME is %JAVA_HOME%
java -version
echo CLASSPATH = %cp%
echo on
:done_verbose

java -Djava.util.logging.config.file=%logFile% -classpath %cp% oracle.mds.tools.bean.MDSBeanGenTool %PARAMS%

@echo off
:: For testing return value from the tool
:: echo MDSBeanGenTool returned: %ERRORLEVEL%


:end
endlocal
