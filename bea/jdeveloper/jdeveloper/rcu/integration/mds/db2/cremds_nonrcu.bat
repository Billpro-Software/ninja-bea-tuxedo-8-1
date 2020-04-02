@echo off
REM Copyright (c) 2006, 2010, Oracle and/or its affiliates. 
REM All rights reserved. 
REM
REM   cremds_nonrcu.bat
REM
REM  DESCRIPTION
REM    This file is used to create the database schema for the repository on 
REM    DB2 server.
REM
REM  NOTES
REM    The user login should have default database set to the one which will
REM    be used by MDS.  The passed-in dbuser should have the default schema 
REM    that MDS is going to use.
REM
REM
REM    This batch file should be invoked from db2 directory in which the
REM    SQL scripts exist.
REM 
REM
REM  MODIFIED   (MM/DD/YY)
REM   pwhaley   04/19/10 - #(9585915) XbranchMerge pwhaley_upgmds_db2 from main
REM   pwhaley   04/14/10 - #(9584856) split dropping for upgrade.
REM   erwang    08/28/09 - Add commit at the end
REM   erwang    07/15/09 - Creation
REM

setlocal

set SQLCMD=db2 -td@ -vf
set SCRIPT_DIR=.
set ADE_NT_VIEW_ROOT=%ADE_NT_ROOT%/%ADE_VIEW_NAME%
set PREP_DIR=%ADE_NT_VIEW_ROOT%/jtmds/src/tools


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
echo cremds_nonrcu database user [password]
echo Parameters:
echo database       -- database name
echo user           -- user
echo password       -- password
goto end

:start
echo =========================================
echo Creating the tables, views, stored procedure etc.
echo =========================================

if %3.==. goto crtdflt
    db2 connect to %1 user %2 using %3
goto crtproc

:crtdflt
db2 connect to %1 user %2

:crtproc
REM Drop tables and procedures etc.
%SQLCMD% %SCRIPT_DIR%/dropmds.db2
%SQLCMD% %SCRIPT_DIR%/droptabs.db2

REM Create tables and Indexes.
perl %PREP_DIR%/prep.pl -v IN_TABLESPACE "" <%SCRIPT_DIR%\cremdcmtbs.db2> %SCRIPT_DIR%\cremdcmtbs.sql

%sqlcmd% %SCRIPT_DIR%/cremdcmtbs.sql

del %SCRIPT_DIR%\cremdcmtbs.sql

perl %PREP_DIR%/prep.pl -v IN_TABLESPACE "" <%SCRIPT_DIR%/cremdsrtbs.db2> %SCRIPT_DIR%/cremdsrtbs.sql

%sqlcmd% %SCRIPT_DIR%/cremdsrtbs.sql

del %SCRIPT_DIR%\cremdsrtbs.sql

perl %PREP_DIR%/prep.pl <%SCRIPT_DIR%/cremdsinds.db2> %SCRIPT_DIR%/cremdsinds.sql

%sqlcmd% %SCRIPT_DIR%/cremdsinds.sql

del %SCRIPT_DIR%\cremdsinds.sql

REM Create MDS Procedures.
perl %PREP_DIR%/prep.pl <%SCRIPT_DIR%/mdsinc.db2> %SCRIPT_DIR%/mdsinc.sql

%sqlcmd% %SCRIPT_DIR%/mdsinc.sql

del %SCRIPT_DIR%\mdsinc.sql

perl %PREP_DIR%/prep.pl <%SCRIPT_DIR%/mdsinsr.db2> %SCRIPT_DIR%/mdsinsr.sql

%sqlcmd% %SCRIPT_DIR%/mdsinsr.sql

del %SCRIPT_DIR%\mdsinsr.sql

REM commit the changes
db2 commit

REM disconnect
db2 connect reset

endlocal
:end

