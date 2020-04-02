Rem
Rem $Header: ldap/java/src/oracle/security/audit/rcu/scripts/WebCacheComponent.sql /main/8 2008/12/16 17:20:44 shiahuan Exp $
Rem
Rem WC.sql
Rem
Rem Copyright (c) 2006, 2008, Oracle and/or its affiliates.
Rem All rights reserved. 
Rem
Rem    NAME
Rem      WC.sql - Create The WC table
Rem
Rem    DESCRIPTION
Rem      Creates the WC table
Rem
Rem    NOTES
Rem      
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    sregmi      08/08/06 - Created
Rem

-- SQL Script for WebCacheComponent
-- &&1 - Audit Admin Role
-- &&2 - Audit Append Role
-- &&3 - Audit Viewer Role

CREATE TABLE WebCacheComponent (
	IAU_ID NUMBER , 
	IAU_TstzOriginating TIMESTAMP , 
	IAU_EventType VARCHAR(255) , 
	IAU_EventCategory VARCHAR(255) 
);

CREATE OR REPLACE SYNONYM WebCache FOR WebCacheComponent;

-- INDEX 
CREATE INDEX WebCacheComponent_Index
ON WebCacheComponent(IAU_TSTZORIGINATING);

-- PERMISSIONS 
GRANT ALL on WebCacheComponent to &&1;
GRANT INSERT on WebCacheComponent to &&2;
GRANT SELECT on WebCacheComponent to &&3;

-- SYNONYMS
CREATE OR REPLACE SYNONYM &&3..WebCacheComponent FOR &&1..WebCacheComponent;
CREATE OR REPLACE SYNONYM &&2..WebCacheComponent FOR &&1..WebCacheComponent;
