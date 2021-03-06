Rem
Rem $Header: ldap/java/src/oracle/security/audit/rcu/scripts/OHSComponent.sql /main/7 2008/12/16 17:20:44 shiahuan Exp $
Rem
Rem OHS.sql
Rem
Rem Copyright (c) 2007, 2008, Oracle and/or its affiliates.
Rem All rights reserved. 
Rem
Rem    NAME
Rem      OHS.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    sregmi      07/29/07 - Created
Rem

-- SQL Script for OHSComponent
-- &&1 - Audit Admin Role
-- &&2 - Audit Append Role
-- &&3 - Audit Viewer Role

CREATE TABLE OHSComponent (
	IAU_ID NUMBER , 
	IAU_TstzOriginating TIMESTAMP , 
	IAU_EventType VARCHAR(255) , 
	IAU_EventCategory VARCHAR(255) , 
	IAU_Reason CLOB , 
	IAU_SSLConnection VARCHAR(255) , 
	IAU_AuthorizationType VARCHAR(255) 
);

CREATE OR REPLACE SYNONYM OHS FOR OHSComponent;

-- INDEX 
CREATE INDEX OHSComponent_Index
ON OHSComponent(IAU_TSTZORIGINATING);

-- PERMISSIONS 
GRANT ALL on OHSComponent to &&1;
GRANT INSERT on OHSComponent to &&2;
GRANT SELECT on OHSComponent to &&3;

-- SYNONYMS
CREATE OR REPLACE SYNONYM &&3..OHSComponent FOR &&1..OHSComponent;
CREATE OR REPLACE SYNONYM &&2..OHSComponent FOR &&1..OHSComponent;
