Rem
Rem $Header: ldap/java/src/oracle/security/audit/rcu/scripts/OWSM-PM-EJB.sql /main/7 2008/12/16 17:20:44 shiahuan Exp $
Rem
Rem OWSM_PM_EJB.sql
Rem
Rem Copyright (c) 2007, 2008, Oracle and/or its affiliates.
Rem All rights reserved. 
Rem
Rem    NAME
Rem      OWSM_PM_EJB.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    sregmi      09/10/07 - Created
Rem

-- SQL Script for OWSM_PM_EJB
-- &&1 - Audit Admin Role
-- &&2 - Audit Append Role
-- &&3 - Audit Viewer Role

CREATE TABLE OWSM_PM_EJB (  
	IAU_ID NUMBER , 
	IAU_TstzOriginating TIMESTAMP , 
	IAU_EventType VARCHAR(255) , 
	IAU_EventCategory VARCHAR(255) , 
	IAU_Version NUMBER , 
	IAU_ToVersion NUMBER 
);
   
-- INDEX 
CREATE INDEX OWSM_PM_EJB_Index
ON OWSM_PM_EJB(IAU_TSTZORIGINATING);

-- PERMISSIONS 
GRANT ALL on OWSM_PM_EJB to &&1;
GRANT INSERT on OWSM_PM_EJB to &&2;
GRANT SELECT on OWSM_PM_EJB to &&3;

-- SYNONYMS
CREATE OR REPLACE SYNONYM &&3..OWSM_PM_EJB FOR &&1..OWSM_PM_EJB;
CREATE OR REPLACE SYNONYM &&2..OWSM_PM_EJB FOR &&1..OWSM_PM_EJB;
