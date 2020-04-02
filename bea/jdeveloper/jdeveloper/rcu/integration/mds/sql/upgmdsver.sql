Rem
Rem upgmdsver.sql
Rem
Rem Copyright (c) 2009, 2010, Oracle and/or its affiliates. 
Rem All rights reserved. 
Rem
Rem    NAME
Rem      upgmdsver.sql - SQL script to upgrade MDS schema version 
Rem
Rem    DESCRIPTION
Rem      This file upgrades the version value in schema_version_registry
Rem      table for the specified MDS component schema to 11.1.1.4.0
Rem
Rem    NOTES
Rem      To run this script in sqlplus, the user has to connect as SYSDBA
Rem      and pass in schema owner as an argument.
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    veyunni     04/09/10 - XbranchMerge llu_bp_sparse_transfer_merge from
Rem                           st_jdevadf_drop8bld3_ias
Rem    llu         04/07/10 - Updated the schema registry vesrion to 11.1.1.4.0
Rem    vyerrama    03/23/10 - Updated the schema registry version to 11.1.1.4.0
Rem    vyerrama    03/23/10 - Updated the schema registry version to 11.1.1.3.0
Rem    gnagaraj    12/21/09 - Update version for PS2, grant execute priv
Rem                           on required packages
Rem    jhsi        11/06/09 - Created
Rem

SET ECHO ON
SET FEEDBACK 1
SET NUMWIDTH 10
SET LINESIZE 80
SET TRIMSPOOL ON
SET TAB OFF
SET PAGESIZE 100

UPDATE schema_version_registry SET version='11.1.1.4.0' 
  WHERE comp_id='MDS' AND owner=UPPER('&&1');

Rem #(9207217) Ensure the user has grant on packages used by MDS 
grant execute on DBMS_LOB to &&1;
grant execute on DBMS_OUTPUT to &&1;

COMMIT;

EXIT;
