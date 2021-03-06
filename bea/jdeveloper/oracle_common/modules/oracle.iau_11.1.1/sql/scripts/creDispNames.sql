Rem
Rem $Header: entsec_ldap/java/src/oracle/security/audit/rcu/scripts/creDispNames.sql /main/3 2009/08/06 11:26:48 shiahuan Exp $
Rem
Rem creDispNames.sql
Rem
Rem Copyright (c) 2008, 2009, Oracle and/or its affiliates. 
Rem All rights reserved. 
Rem
Rem    NAME
Rem      creDispNames.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    pdatta      12/18/08 - sql script to create display name tables
Rem    pdatta      12/18/08 - Created
Rem

-- SQL Script for Translation Tables
-- &&1 - Audit Admin Role
-- &&2 - Audit Append Role
-- &&3 - Audit Viewer Role

-- Create Translation Table
CREATE TABLE IAU_DISP_NAMES_TL ( 
 IAU_LOCALE_STR VARCHAR2(7), 
 IAU_DISP_NAME_KEY VARCHAR2(255), 
 IAU_COMPONENT_TYPE VARCHAR2(255), 
 IAU_DISP_NAME_KEY_TYPE VARCHAR2(255), 
 IAU_DISP_NAME_TRANS VARCHAR2(4000),
 CONSTRAINT PK_DISP_NAMES PRIMARY KEY (IAU_LOCALE_STR, 
    IAU_DISP_NAME_KEY, IAU_COMPONENT_TYPE, IAU_DISP_NAME_KEY_TYPE)
); 

-- Create Locale Map table 
CREATE TABLE IAU_LOCALE_MAP_TL ( 
 IAU_LOC_LANG VARCHAR2(2), 
 IAU_LOC_CNTRY VARCHAR2(3), 
 IAU_LOC_STR VARCHAR2(7) 
); 

DELETE FROM IAU_DISP_NAMES_TL;
DELETE FROM IAU_LOCALE_MAP_TL;

-- INSERT into IAU_LOCALE_MAP_TL
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'de', null, 'de');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'en', null, 'en');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'es', null, 'es');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'fr', null, 'fr');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'it', null, 'it');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'ja', null, 'ja');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'ko', null, 'ko');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'pt', 'BR', 'pt_BR');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'zh', 'CN', 'zh_CN');
INSERT INTO IAU_LOCALE_MAP_TL(IAU_LOC_LANG, IAU_LOC_CNTRY, IAU_LOC_STR) VALUES ( 'zh', 'TW', 'zh_TW');


-- GRANTS
GRANT ALL on IAU_DISP_NAMES_TL to &&1;
GRANT INSERT on IAU_DISP_NAMES_TL to &&2;
GRANT SELECT on IAU_DISP_NAMES_TL to &&3;

-- SYNONYMS
CREATE or REPLACE SYNONYM &&3..IAU_DISP_NAMES_TL FOR &&1..IAU_DISP_NAMES_TL;
CREATE or REPLACE SYNONYM &&2..IAU_DISP_NAMES_TL FOR &&1..IAU_DISP_NAMES_TL;

-- GRANTS
GRANT ALL on IAU_LOCALE_MAP_TL to &&1;
GRANT INSERT on IAU_LOCALE_MAP_TL to &&2;
GRANT SELECT on IAU_LOCALE_MAP_TL to &&3;

-- SYNONYMS
CREATE or REPLACE SYNONYM &&3..IAU_LOCALE_MAP_TL FOR &&1..IAU_LOCALE_MAP_TL;
CREATE or REPLACE SYNONYM &&2..IAU_LOCALE_MAP_TL FOR &&1..IAU_LOCALE_MAP_TL;

