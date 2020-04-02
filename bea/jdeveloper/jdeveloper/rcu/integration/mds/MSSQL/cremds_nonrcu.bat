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
REM    This batch file should be invoked from MSSQL directory in which the
REM    SQL scripts exist.
REM 
REM
REM  MODIFIED   (MM/DD/YY)
REM   erwang    06/27/07 - #(5919142) Workaround RCU empty string issue.
REM   erwang    03/06/07 - Renamed from original cremds.bat
REM   erwang    12/27/06 - Globalization Support for SQL server
REM   erwang    11/13/06 - update to use cremds.sql
REM   erwang    10/19/06 - Moved to MSSQL directory.
REM   erwang    09/26/06 - Creation
REM

setlocal

REM Set MDS_VARCHAR="NVARCHAR" to create Unicode compliant tables and stored-procedures.  
REM Set MDS_VARCHAR="VARCHAR" to create tables and stored-procedures that use localized character sets.

set MDS_VARCHAR="NVARCHAR"

if "%4"=="NonUnicode" set MDS_VARCHAR="VARCHAR"




set SQLCMD=sqlcmd -w 80 -e -v MDS_VARCHAR=%MDS_VARCHAR%
set SCRIPT_DIR=.

if %1.==. goto help
goto start

if %2.==. goto help
goto start

if %3.==. goto help
goto start



:help
echo MDS script for creating the MDS schema
echo Copyright(c) 2002, 2005, Oracle Corporation. All rights reserved.
echo Usage :
echo cremds server username password [NonUnicode]
echo Parameters:
echo server         -- server name
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
%SQLCMD% -S %1 -U %2 -P %3  -i %SCRIPT_DIR%/cremds.sql 


endlocal
:end

