Rem
Rem $Header: entsec_ldap/java/src/oracle/security/audit/rcu/scripts/auditDataPurge.sql /st_entsec_11.1.1.4.0/1 2010/10/14 22:51:03 skalyana Exp $
Rem
Rem auditDataPurge.sql
Rem
Rem Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved. 
Rem
Rem    NAME
Rem      auditDataPurge.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    skalyana    05/25/10 - Created
Rem

ALTER SESSION SET CURRENT_SCHEMA=&&1;

ALTER SESSION SET NLS_DATE_FORMAT = 'DD-MON-YYYY HH24:MI:SS';

delete from IAU_BASE where IAU_TstzOriginating < (sysdate  - &&2); 
delete from AdminServer where IAU_TstzOriginating < (sysdate  - &&2); 
delete from DIP where IAU_TstzOriginating < (sysdate  - &&2); 
delete from JPS where IAU_TstzOriginating < (sysdate  - &&2); 
delete from OAAM where IAU_TstzOriginating < (sysdate  - &&2); 
delete from OAM where IAU_TstzOriginating < (sysdate  - &&2); 
delete from OIF where IAU_TstzOriginating < (sysdate  - &&2); 
delete from OVD where IAU_TstzOriginating < (sysdate  - &&2); 
delete from OHSComponent where IAU_TstzOriginating < (sysdate  - &&2); 
delete from OIDComponent where IAU_TstzOriginating < (sysdate  - &&2); 
delete from WebCacheComponent where IAU_TstzOriginating < (sysdate  - &&2);
delete from OWSM_PM_EJB where IAU_TstzOriginating < (sysdate  - &&2);
delete from OWSM_AGENT where IAU_TstzOriginating < (sysdate  - &&2);
delete from WS_PolicyAttachment where IAU_TstzOriginating < (sysdate  - &&2);
delete from WebServices where IAU_TstzOriginating < (sysdate  - &&2);
delete from STS where IAU_TstzOriginating < (sysdate  - &&2);
commit;
