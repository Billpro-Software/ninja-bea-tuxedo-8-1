@echo off
REM Copyright (c) 2006, 2010, Oracle and/or its affiliates. 
REM All rights reserved. 
REM
REM   cremds.bat
REM
REM  DESCRIPTION
REM    This file is used to create the database schema for the repository on 
REM    DB2.
REM
REM  NOTES
REM    The passed-in dbuser should have the default schema that MDS is going to use.
REM
REM
REM    This batch file should be invoked from DB2 directory of the view in
REM    which the SQL scripts exist.
REM 
REM
REM  MODIFIED   (MM/DD/YY)
REM   erwang    12/15/09 -  Creation
REM

setlocal

@set ADE_NT_VIEW_ROOT=%ADE_NT_ROOT%\%ADE_VIEW_NAME%
@set OH=%ADE_NT_VIEW_ROOT%\oracle
@set PH=%OH%\jdeveloper
@set RCU_HOME=%OH%
@set RCU_CP=%PH%\jlib\rcucommon.jar
@set MDS_CP=%PH%\mds\bin\mdstools.jar
@set JRE_DIR=%OH%\jdk\jre

REM Set the classpath
@set CLASSPATH=%RCU_CP%;%MDS_CP%

@set SQLCMD=%JRE_DIR%\bin\java -Dcontinue_on_errors=TRUE -DRCU_HOME=%RCU_HOME% -DORACLE_HOME=%OH% -Xmx128m -classpath %CLASSPATH% oracle.sysman.assistants.common.dbutil.jdbc.JDBCEngine
@set SCRIPT_DIR=%~d0%~p0

if %1.==. goto help
goto start



:help
echo MDS script for creating the MDS schema
echo Copyright(c) 2002, 2007, Oracle Corporation. All rights reserved.
echo Usage :
echo cremds username/password@'server:port:dbname'
echo Parameters:
echo server         -- server name
echo port           -- port number.  It can be ignored if default port number is used.
echo username       -- db user name created for MDS
echo password       -- db user password
echo dbname         -- database
goto end

:start
echo =========================================
echo Creating the tables, views, stored procedure etc.
echo =========================================
%SQLCMD% %1 DB2_SCRIPT %SCRIPT_DIR%/cremds.db2 


endlocal
:end

