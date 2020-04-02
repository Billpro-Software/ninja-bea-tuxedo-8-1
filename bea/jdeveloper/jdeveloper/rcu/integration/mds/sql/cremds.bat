@echo off
REM    cremds.bat
REM
REM  DESCRIPTION
REM    This file is used to create the database schema for the repository. 
REM
REM
REM  NOTES
REM    The database user must have grant to create sequence in order to 
REM    successfully use the MDS Repository.
REM
REM    This batch file should be invoked from the same directory in which 
REM    the SQL scripts exist.
REM 
REM    This batch file needed to be created to run the SQL scripts.  One would
REM    think that we shouldn't need a batch file just to run a bunch of SQL
REM    scripts, but it turns out that (in order to be a part of the APPS ARU)
REM    all of the SQL scripts must have an EXIT command; which means that we
REM    would only be able to run one SQL script before SQLPLUS exited.  That
REM    is why this script was created.
REM
REM
REM  MODIFIED   (MM/DD/YY)
REM   gnagaraj   07/31/08  - #(7377948) Moved XDB scripts to oraclexdb directory
REM   abhatt     07/12/07  - #(6135856) Update comments, remove dbms_lock notes
REM   erwang     07/06/07  - #(5528236) quit sqlplus immediately upon login
REM                          fail
REM   rupandey   05/09/07  - Modified script to create xdb tables only for MDS 
REM                          development environment.
REM   rupandey   09/26/06  - This script act as a wrapper and invokes cremds.sql now. 
REM							 Any new sql script, pls script or
REM                          invocation of a procedure should be added to cremds.sql.
REM   rupandey   08/22/06  - Added call to PL/SQL to load data in 
REM			                 MDS_XDB_TRANSFORMS table.
REM   gnagaraj   06/17/06  - Move shredded tables to separate script.
REM   gnagaraj   05/21/06  - Introduce mds_internal_common package.
REM   pwhaley    04/06/06  - XDB now requires DB 10.2
REM   gnagaraj   12/21/05  - Run SQLPLUS in silent mode 
REM   gnagaraj   08/01/05  - Move creation of XDB Repository schema to
REM                          cremdsxdr.bat
REM   gnagaraj   06/29/05  - Create PL/SQL packages for XDBMetadataStore
REM   gnagaraj   06/15/05  - Document grant on dbms_lock requirement 
REM   gnagaraj   04/19/05  - Cleanup
REM   enewman    12/01/04  - Rename to MDS 
REM   enewman    05/16/03 -  Add JDR_UTILS package spec and body
REM   kaalvare   12/03/02 -  Add JDR_DOCBUILDER package spec and body
REM   enewman    06/11/02 -  Creation
REM
setlocal

set SQLPLUSCMD=sqlplus -L -S
if %1.==. goto help
if "%2" == "xdb" goto xdb
if "%2" == ""    goto normal


:help

echo.MDS script for creating the MDS schema
echo.Copyright(c) 2002, 2008, Oracle Corporation. All rights reserved.
echo.Usage :
echo.cremds the_connect_string (i.e. username/password@tnsname) 
goto end


:xdb

echo.========================================================
echo.Creating MDS repository with XDB tables (for internal
echo.use by MDS development only)
echo.========================================================
REM #(7377948) Create the Shredded & XDB schema 
REM (note that oraclexdb dir only exists in the source control)
cd ..\oraclexdb
%SQLPLUSCMD% %1 @cremds_xdb.sql
goto end


:normal

echo.=========================================
echo.Creating MDS repository.
echo.=========================================
%SQLPLUSCMD% %1 @cremds.sql


:end

