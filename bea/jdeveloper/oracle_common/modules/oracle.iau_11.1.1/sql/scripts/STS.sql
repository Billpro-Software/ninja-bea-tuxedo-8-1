Rem
Rem $Header: entsec_ldap/java/src/oracle/security/audit/rcu/scripts/STS.sql /st_entsec_11.1.1.4.0/1 2010/10/14 22:51:03 skalyana Exp $
Rem
Rem STS.sql
Rem
Rem Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved. 
Rem
Rem    NAME
Rem      STS.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    skalyana    10/06/10 - Created
Rem

SET ECHO ON
SET FEEDBACK 1
SET NUMWIDTH 10
SET LINESIZE 80
SET TRIMSPOOL ON
SET TAB OFF
SET PAGESIZE 100

CREATE TABLE STS (
        IAU_ID NUMBER ,
        IAU_TstzOriginating TIMESTAMP ,
        IAU_EventType VARCHAR(255) ,
        IAU_EventCategory VARCHAR(255),
        IAU_Requester VARCHAR(255),
	IAU_RelyingParty VARCHAR(255),
	IAU_UserID VARCHAR(255),
	IAU_TokenType VARCHAR(100),
	IAU_Token CLOB,
	IAU_TokenContext CLOB,
	IAU_Message CLOB,
	IAU_OperationType VARCHAR(255),
	IAU_OperationData CLOB,
	IAU_OldSettings CLOB,
	IAU_NewSettings CLOB,
	IAU_TemplateID VARCHAR(100),
	IAU_ProfileID VARCHAR(100),
	IAU_PartnerID VARCHAR(100),
	IAU_SettingsID VARCHAR(400),
);

-- INDEX 
CREATE INDEX STS_Index
ON STS(IAU_TSTZORIGINATING);

-- PERMISSIONS 
GRANT ALL on STS to &&1;
GRANT INSERT on STS to &&2;
GRANT SELECT on STS to &&3;

-- SYNONYMS 
CREATE OR REPLACE SYNONYM &&3..STS FOR &&1..STS;
CREATE OR REPLACE SYNONYM &&2..STS FOR &&1..STS;
