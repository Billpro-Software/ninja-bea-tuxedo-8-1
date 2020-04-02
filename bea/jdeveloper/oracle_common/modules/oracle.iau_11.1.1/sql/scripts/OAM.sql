Rem
Rem $Header: entsec_ldap/java/src/oracle/security/audit/rcu/scripts/OAM.sql /st_entsec_11.1.1.4.0/2 2010/11/09 20:22:33 skalyana Exp $
Rem
Rem OAM.sql
Rem
Rem Copyright (c) 2009, 2010, Oracle and/or its affiliates. 
Rem All rights reserved. 
Rem
Rem    NAME
Rem      OAM.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    skalyana    11/08/10 - Bug # 10268948
Rem    skalyana    10/10/10 - schema changes for OAM
Rem    shiahuan    09/09/09 - Created
Rem

-- SQL Script for OAM
-- &&1 - Audit Admin Role
-- &&2 - Audit Append Role
-- &&3 - Audit Viewer Role

CREATE TABLE OAM (
	IAU_ID NUMBER , 
	IAU_TstzOriginating TIMESTAMP , 
	IAU_EventType VARCHAR(255) , 
	IAU_EventCategory VARCHAR(255) , 
	IAU_ApplicationDomainName VARCHAR(40) , 
	IAU_AuthenticationSchemeID VARCHAR(40) , 
	IAU_AgentID VARCHAR(40) , 
	IAU_SSOSessionID VARCHAR(100) , 
	IAU_AdditionalInfo CLOB, 
	IAU_AuthorizationScheme VARCHAR(40) , 
	IAU_UserDN VARCHAR(255) , 
	IAU_ResourceID VARCHAR(40) , 
	IAU_AuthorizationPolicyID VARCHAR(40) , 
	IAU_AuthenticationPolicyID VARCHAR(255) , 
	IAU_UserID VARCHAR(40) , 
	IAU_ResourceHost VARCHAR(255) , 
	IAU_RequestID VARCHAR(255) , 
	IAU_PolicyName VARCHAR(40) , 
	IAU_SchemeName VARCHAR(40) , 
	IAU_ResourceHostName VARCHAR(100) , 
	IAU_OldAttributes VARCHAR(1000) , 
	IAU_NewAttributes VARCHAR(1000) , 
        IAU_SchmeType VARCHAR(40) ,
	IAU_ResponseType VARCHAR(40) , 
	IAU_AgentType VARCHAR(40) , 
	IAU_ConstraintType VARCHAR(40) , 
	IAU_InstanceName VARCHAR(40) , 
	IAU_DataSourceName VARCHAR(100) , 
	IAU_DataSourceType VARCHAR(100) , 
	IAU_HostIdentifierName VARCHAR(100) , 
	IAU_ResourceURI VARCHAR(255) , 
        IAU_ResourceTemplateName VARCHAR(100),
	IAU_Impersonator VARCHAR(255),
	IAU_OldSettings CLOB,
	IAU_NewSettings CLOB,
	IAU_ResourceType VARCHAR(255)
);

-- INDEX 
CREATE INDEX OAM_Index
ON OAM(IAU_TSTZORIGINATING);

-- PERMISSIONS 
GRANT ALL on OAM to &&1;
GRANT INSERT on OAM to &&2;
GRANT SELECT on OAM to &&3;

-- SYNONYMS 
CREATE OR REPLACE SYNONYM &&3..OAM FOR &&1..OAM;
CREATE OR REPLACE SYNONYM &&2..OAM FOR &&1..OAM;
