@echo off
REM mdsdelete.bat
REM
REM
REM  DESCRIPTION
REM    This file is used to call the MDSDeleteTool utility 
REM
REM
REM  NOTES
REM 
REM
REM
REM   MODIFIED   (MM/DD/YY)
REM   snoton     08/24/09 - #(8808215) use mds-tools.jar instead of 
REM                         setMDSclasspath
REM   snoton     02/11/09 - #(8246400) check for JAVA_HOME
REM   allechen   08/19/08  - Use datadirect 3.7 in WLS install
REM   dklein     06/05/07  - Use setMDSclasspath.bat
REM   erwang     05/18/07  - Update YMSqlserver.jar location
REM   erwang     12/26/06  - Add DataDirect JDBC driver support
REM   pwhaley    01/15/07  - Add UCP jar, SQLServer jdbc jar.
REM   pwhaley    01/08/07  - Remove concurrent.jar.
REM   gnagaraj   01/03/07  - Consume ojdbc5dms.jar
REM   dklein     12/20/06  - Add dafrt.jar and its dependencies
REM   gnagaraj   12/05/06  - Remove bc4jct.jar and collections.jar dependency
REM   dklein     09/22/06  - Rename adfshare.jar to adfsharebase.jar
REM   ntriggs    09/13/06  - Add JAXB 2.0 classes
REM   gkonduri   01/05/06  - Add commons-collections.jar 
REM   spathak    09/30/05  - 
REM   hlie       09/26/05  - Add adfshare.jar
REM   lramados   07/26/05  - Remove classes directory from the classpath. 
REM   gnagaraj   07/06/05  - Add xdb.jar to classpath 
REM   azgibson   07/08/05  - Updating location of xml.jar.
REM   gnagaraj   06/01/05  - Add xml.jar to classpath for JAXB.
REM   hlie       05/16/05  - Changed to use mdsrt.jar.
REM   hlie       04/25/05  - Changes in library locations (el, cli, cache).
REM   prasubra   03/08/05  - Added concurrent.jar in the classpath
REM   lramados   03/04/05  - Add xmlef.jar in the classpath 
REM   lramados   02/07/05  - Comment error level 
REM   lramados   01/28/05  - Include log configuration file in the command
REM   prasubra   01/21/05  - Package name changes. 
REM   prasubra   01/20/05  - Prasubra_deletetool_integration
REM   prasubra   01/12/05  - Small correction. 
REM   prasubra   01/10/05  - Creation
REM

:: #############################################################################
:: ##   This file should be in sync with the "mdsdelete" shell script         ##
:: ##   Please update "mdsdelete" when updating this file.                    ##
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
shift
goto start

:: ----------------- Done with the parameter processing. 
:: -- Prepare to call the MDSTransferTool utility
:done


:: ------- Set class path
set cp=%DELIVER%\mds\bin\mdstools.jar

:: ------- PATH settings
set PATH=%JAVA_HOME%\bin;%path%

if %verbose% == "n" goto done_verbose
java -version
echo CLASSPATH = %cp%
echo on
:done_verbose

java -Djava.util.logging.config.file=%logFile% -classpath %cp% oracle.mds.tools.delete.MDSDeleteTool %PARAMS%

@echo off
:: For testing return value from the tool
:: echo MDSDeleteTool returned: %ERRORLEVEL%


:end
endlocal
