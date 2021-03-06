Rem
Rem $Header: ldap/java/src/oracle/security/audit/rcu/scripts/ReportsServerComponent.sql /main/7 2008/12/16 17:20:44 shiahuan Exp $
Rem
Rem ReportsServer.sql
Rem
Rem Copyright (c) 2007, 2008, Oracle and/or its affiliates.
Rem All rights reserved. 
Rem
Rem    NAME
Rem      ReportsServer.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    sregmi      12/24/07 - 
Rem    gsandeep    12/18/07 - Created
Rem

-- SQL Script for ReportsServerComponent
-- &&1 - Audit Admin Role
-- &&2 - Audit Append Role
-- &&3 - Audit Viewer Role

CREATE TABLE ReportsServerComponent (
	IAU_ID NUMBER , 
	IAU_TstzOriginating TIMESTAMP , 
	IAU_EventType VARCHAR(255) , 
	IAU_EventCategory VARCHAR(255) 
);

CREATE OR REPLACE SYNONYM ReportsServer FOR ReportsServerComponent;

-- INDEX 
CREATE INDEX ReportsServerComponent_Index
ON ReportsServerComponent(IAU_TSTZORIGINATING);

-- PERMISSIONS 
GRANT ALL on ReportsServerComponent to &&1;
GRANT INSERT on ReportsServerComponent to &&2;
GRANT SELECT on ReportsServerComponent to &&3;

-- SYNONYMS
CREATE OR REPLACE SYNONYM &&3..ReportsServerComponent FOR &&1..ReportsServerComponent;
CREATE OR REPLACE SYNONYM &&2..ReportsServerComponent FOR &&1..ReportsServerComponent;
