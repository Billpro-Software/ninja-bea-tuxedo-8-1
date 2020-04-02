@echo off
REM Copyright (c) 2006, 2007, Oracle. All rights reserved.  
REM
REM   cremds.bat
REM
REM  DESCRIPTION
REM    This file is used to create the database schema for the repository on 
REM    SQL Server.
REM
REM  NOTES
REM    The user login should have default database set to the one which will
REM    be used by MDS.  The passed-in dbuser should have the default schema 
REM    that MDS is going to use.
REM
REM
REM    This batch file should be invoked from MSSQL directory of the view in
REM    which the SQL scripts exist.
REM 
REM
REM  MODIFIED   (MM/DD/YY)
REM   erwang    08/21/07  - Fix ojdl path
REM   erwang    06/27/07  - #(5919142) Workaround RCU empty string issue.
REM   erwang    06/01/07  - fix datadirect jar path
REM   erwang    03/05/07  - Switch to use rcu JDBCEngine
REM   erwang    12/27/06  - Globalization Support for SQL server
REM   erwang    11/13/06  - update to use cremds.sql
REM   erwang    10/19/06 -  Moved to MSSQL directory.
REM   erwang    09/26/06 -  Creation
REM

setlocal

REM Set MDS_VARCHAR="NVARCHAR" to create Unicode compliant tables and stored-procedures.  
REM Set MDS_VARCHAR="VARCHAR" to create tables and stored-procedures that use localized character sets.

@set MDS_VARCHAR="NVARCHAR"


if "%2"=="NonUnicode" set MDS_VARCHAR="VARCHAR"


@set ADE_NT_VIEW_ROOT=%ADE_NT_ROOT%\%ADE_VIEW_NAME%
@set OH=%ADE_NT_VIEW_ROOT%\oracle
@set JRE_DIR=%OH%\jdk\jre
@set RCU_HOME=%OH%
@set JLIB_DIR=%OH%\lib
@set DATADIRECT_HOME=%ADE_NT_VIEW_ROOT%\datadirect\lib
@set SQLSERVER_CP=%DATADIRECT_HOME%\YMBase.jar;%DATADIRECT_HOME%\YMutil.jar;%DATADIRECT_HOME%\YMsqlserver.jar
@set OC4J_CP=%OH%\j2ee\home\oc4j.jar
@set RCU_CP=%OH%\jlib\rcu.jar
@set SHARE_CP=%JLIB_DIR%\share.jar
@set OJDL_CP=%OH%\jlib\ojdl.jar
@set AS_CP=%JLIB_DIR%\SchemaVersion.jar
@set ADMIN_CP=%JLIB_DIR%\adminserver.jar

REM Set the classpath
@set CLASSPATH=%RCU_CP%;%SQLSERVER_CP%;%OC4J_CP%;%SHARE_CP%;%OJDL_CP%;AS_CP%;%ADMIN_CP%

@set SQLCMD=%JRE_DIR%\bin\java -Dcontinue_on_errors=TRUE -DRCU_HOME=%RCU_HOME% -DORACLE_HOME=%OH% -DLAUNCH_MODE=%LAUNCH_MODE% -Xmx128m -classpath %CLASSPATH% oracle.sysman.assistants.common.dbutil.jdbc.JDBCEngine
@set SCRIPT_DIR=%~d0%~p0

if %1.==. goto help
goto start



:help
echo MDS script for creating the MDS schema
echo Copyright(c) 2002, 2007, Oracle Corporation. All rights reserved.
echo Usage :
echo cremds username/password@server[:port#] [NonUnicode]
echo Parameters:
echo server         -- server name
echo port#          -- port number.  It can be ignored if default port number is used.
echo username       -- db user name created for MDS
echo password       -- db user password
echo NonUnicode     -- If specified, MDS tables will be created using CHAR and 
echo                   VARCHAR etc. for text columns.  Without this flag, MDS tables 
echo                   will be created using NCHAR and NVARCHAR for text columns.
goto end

:start
echo =========================================
echo Creating the tables, views, stored procedure etc.
echo =========================================
%SQLCMD% %1 SQLSERVER_SCRIPT %SCRIPT_DIR%/cremds.sql -v MDS_VARCHAR=%MDS_VARCHAR%


endlocal
:end

