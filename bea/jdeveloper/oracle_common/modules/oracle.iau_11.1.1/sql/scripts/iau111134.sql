Rem
Rem $Header: entsec_ldap/java/src/oracle/security/audit/rcu/scripts/iau111134.sql /st_entsec_11.1.1.4.0/2 2010/11/09 20:22:33 skalyana Exp $
Rem
Rem iau11113.sql
Rem
Rem Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved. 
Rem
Rem    NAME
Rem      iau11113.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    skalyana    11/08/10 - bug # 10268948
Rem    skalyana    05/10/10 - Created
Rem

ALTER SESSION SET CURRENT_SCHEMA=&&1;

ALTER TABLE OAAM
MODIFY IAU_CaseActionEnum VARCHAR(4000);
ALTER TABLE OAAM
MODIFY IAU_CaseChallengeResult NUMBER;
ALTER TABLE OAAM
MODIFY IAU_CaseDisposition VARCHAR(4000);
ALTER TABLE OAAM
MODIFY IAU_CaseSeverity VARCHAR(4000);
ALTER TABLE OAAM
MODIFY IAU_CaseStatus VARCHAR(4000);

ALTER TABLE JPS
ADD IAU_stripeName VARCHAR(1024);
ALTER TABLE JPS
ADD IAU_keystoreName VARCHAR(1024);
ALTER TABLE JPS
ADD IAU_alias VARCHAR(1024);
ALTER TABLE JPS
ADD IAU_operation VARCHAR(1024);

ALTER TABLE IAU_BASE
ADD IAU_ComponentData CLOB;

@@STS.sql  &&1 &&2 &&3

ALTER TABLE OAM
ADD IAU_ResourceTemplateName VARCHAR(100);
ALTER TABLE OAM
ADD IAU_Impersonator VARCHAR(255);
ALTER TABLE OAM
ADD IAU_OldSettings CLOB;
ALTER TABLE OAM
ADD IAU_NewSettings CLOB;
ALTER TABLE OAM
ADD IAU_ResourceType VARCHAR(255);
ALTER TABLE OAM
MODIFY IAU_AdditionalInfo CLOB;

@@auditschema.pls &&1 &&2 &&3
@@auditreports.pls &&1 &&2 &&3
