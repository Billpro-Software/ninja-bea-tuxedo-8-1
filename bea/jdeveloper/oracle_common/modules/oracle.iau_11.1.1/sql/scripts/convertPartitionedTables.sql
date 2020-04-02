Rem
Rem $Header: entsec_ldap/java/src/oracle/security/audit/rcu/scripts/convertPartitionedTables.sql /main/3 2009/09/24 17:47:15 shiahuan Exp $
Rem
Rem convertPartitionedTables.sql
Rem
Rem Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
Rem
Rem    NAME
Rem      convertPartitionedTables.sql - <one-line expansion of the name>
Rem
Rem    DESCRIPTION
Rem      <short description of component this file declares/defines>
Rem
Rem    NOTES
Rem      <other useful comments, qualifications, etc.>
Rem
Rem    MODIFIED   (MM/DD/YY)
Rem    shiahuan    02/06/09 - Created
Rem

-- This is a sample SQL script to convert the base and component tables
-- in Audit schema into partitioned ones.


-- IAU_BASE

RENAME IAU_BASE TO IAU_BASE_NONPART;

CREATE TABLE IAU_BASE
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION IAU_BASE_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM IAU_BASE_NONPART;

ALTER TABLE IAU_BASE
ENABLE ROW MOVEMENT;

ALTER INDEX EVENT_TIME_INDEX
RENAME TO EVENT_TIME_INDEX_NONPART;

CREATE INDEX EVENT_TIME_INDEX
ON IAU_BASE(IAU_TSTZORIGINATING) LOCAL;

-- WEBCACHECOMPONENT

RENAME WEBCACHECOMPONENT TO WEBCACHECOMPONENT_NONPART;

CREATE TABLE WEBCACHECOMPONENT
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION WEBCACHECOMPONENT_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM WEBCACHECOMPONENT_NONPART;

ALTER TABLE WEBCACHECOMPONENT
ENABLE ROW MOVEMENT;

ALTER INDEX WEBCACHECOMPONENT_INDEX
RENAME TO WEBCACHE_INDEX_NONPART;

CREATE INDEX WEBCACHECOMPONENT_INDEX
ON WEBCACHECOMPONENT(IAU_TSTZORIGINATING) LOCAL;

-- OVDCOMPONENT

RENAME OVDCOMPONENT TO OVDCOMPONENT_NONPART;

CREATE TABLE OVDCOMPONENT
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OVDCOMPONENT_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OVDCOMPONENT_NONPART;

ALTER TABLE OVDCOMPONENT
ENABLE ROW MOVEMENT;

ALTER INDEX OVDCOMPONENT_INDEX
RENAME TO OVD_INDEX_NONPART;

CREATE INDEX OVDCOMPONENT_INDEX
ON OVDCOMPONENT(IAU_TSTZORIGINATING) LOCAL;

-- OIDCOMPONENT

RENAME OIDCOMPONENT TO OIDCOMPONENT_NONPART;

CREATE TABLE OIDCOMPONENT
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OIDCOMPONENT_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OIDCOMPONENT_NONPART;

ALTER TABLE OIDCOMPONENT
ENABLE ROW MOVEMENT;

ALTER INDEX OIDCOMPONENT_INDEX
RENAME TO OID_INDEX_NONPART;

CREATE INDEX OIDCOMPONENT_INDEX
ON OIDCOMPONENT(IAU_TSTZORIGINATING) LOCAL;

-- OWSM_PM_EJB

RENAME OWSM_PM_EJB TO OWSM_PM_EJB_NONPART;

CREATE TABLE OWSM_PM_EJB
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OWSM_PM_EJB_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OWSM_PM_EJB_NONPART;

ALTER TABLE OWSM_PM_EJB
ENABLE ROW MOVEMENT;

ALTER INDEX OWSM_PM_EJB_INDEX
RENAME TO OWSM_PM_EJB_INDEX_NONPART;

CREATE INDEX OWSM_PM_EJB_INDEX
ON OWSM_PM_EJB(IAU_TSTZORIGINATING) LOCAL;

-- OWSM_AGENT

RENAME OWSM_AGENT TO OWSM_AGENT_NONPART;

CREATE TABLE OWSM_AGENT
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OWSM_AGENT_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OWSM_AGENT_NONPART;

ALTER TABLE OWSM_AGENT
ENABLE ROW MOVEMENT;

ALTER INDEX OWSM_AGENT_INDEX
RENAME TO OWSM_AGENT_INDEX_NONPART;

CREATE INDEX OWSM_AGENT_INDEX
ON OWSM_AGENT(IAU_TSTZORIGINATING) LOCAL;

-- DIP

RENAME DIP TO DIP_NONPART;

CREATE TABLE DIP
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION DIP_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM DIP_NONPART;

ALTER TABLE DIP
ENABLE ROW MOVEMENT;

ALTER INDEX DIP_INDEX
RENAME TO DIP_INDEX_NONPART;

CREATE INDEX DIP_INDEX
ON DIP(IAU_TSTZORIGINATING) LOCAL;

-- OHSCOMPONENT

RENAME OHSCOMPONENT TO OHSCOMPONENT_NONPART;

CREATE TABLE OHSCOMPONENT
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OHSCOMPONENT_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OHSCOMPONENT_NONPART;

ALTER TABLE OHSCOMPONENT
ENABLE ROW MOVEMENT;

ALTER INDEX OHSCOMPONENT_INDEX
RENAME TO OHS_INDEX_NONPART;

CREATE INDEX OHSCOMPONENT_INDEX
ON OHSCOMPONENT(IAU_TSTZORIGINATING) LOCAL;

-- JPS

RENAME JPS TO JPS_NONPART;

CREATE TABLE JPS
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION JPS_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM JPS_NONPART;

ALTER TABLE JPS
ENABLE ROW MOVEMENT;

ALTER INDEX JPS_INDEX
RENAME TO JPS_INDEX_NONPART;

CREATE INDEX JPS_INDEX
ON JPS(IAU_TSTZORIGINATING) LOCAL;

-- ADMINSERVER

RENAME ADMINSERVER TO ADMINSERVER_NONPART;

CREATE TABLE ADMINSERVER
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION ADMINSERVER_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM ADMINSERVER_NONPART;

ALTER TABLE ADMINSERVER
ENABLE ROW MOVEMENT;

ALTER INDEX ADMINSERVER_INDEX
RENAME TO ADMINSERVER_INDEX_NONPART;

CREATE INDEX ADMINSERVER_INDEX
ON ADMINSERVER(IAU_TSTZORIGINATING) LOCAL;

-- REPORTSSERVERCOMPONENT

RENAME REPORTSSERVERCOMPONENT TO REPORTSSERVERCOMPONENT_NONPART;

CREATE TABLE REPORTSSERVERCOMPONENT
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION REPORTSSERVERCOMPONENT_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM REPORTSSERVERCOMPONENT_NONPART;

ALTER TABLE REPORTSSERVERCOMPONENT
ENABLE ROW MOVEMENT;

ALTER INDEX REPORTSSERVERCOMPONENT_INDEX
RENAME TO REPORTSSERVER_INDEX_NONPART;

CREATE INDEX REPORTSSERVERCOMPONENT_INDEX
ON REPORTSSERVERCOMPONENT(IAU_TSTZORIGINATING) LOCAL;

-- WEBSERVICES

RENAME WEBSERVICES TO WEBSERVICES_NONPART;

CREATE TABLE WEBSERVICES
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION WEBSERVICES_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM WEBSERVICES_NONPART;

ALTER TABLE WEBSERVICES
ENABLE ROW MOVEMENT;

ALTER INDEX WEBSERVICES_INDEX
RENAME TO WEBSERVICES_INDEX_NONPART;

CREATE INDEX WEBSERVICES_INDEX
ON WEBSERVICES(IAU_TSTZORIGINATING) LOCAL;

-- WS_POLICYATTACHMENT

RENAME WS_POLICYATTACHMENT TO WS_POLICYATTACHMENT_NONPART;

CREATE TABLE WS_POLICYATTACHMENT
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION WS_POLICYATTACHMENT_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM WS_POLICYATTACHMENT_NONPART;

ALTER TABLE WS_POLICYATTACHMENT
ENABLE ROW MOVEMENT;

ALTER INDEX WS_POLICYATTACHMENT_INDEX
RENAME TO WS_POLICY_INDEX_NONPART;

CREATE INDEX WS_POLICYATTACHMENT_INDEX
ON WS_POLICYATTACHMENT(IAU_TSTZORIGINATING) LOCAL;

-- OIF

RENAME OIF TO OIF_NONPART;

CREATE TABLE OIF
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OIF_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OIF_NONPART;

ALTER TABLE OIF
ENABLE ROW MOVEMENT;

ALTER INDEX OIF_INDEX
RENAME TO OIF_INDEX_NONPART;

CREATE INDEX OIF_INDEX
ON OIF(IAU_TSTZORIGINATING) LOCAL;

-- OAM

RENAME OAM TO OAM_NONPART;

CREATE TABLE OAM
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OAM_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OAM_NONPART;

ALTER TABLE OAM
ENABLE ROW MOVEMENT;

ALTER INDEX OAM_INDEX
RENAME TO OAM_INDEX_NONPART;

CREATE INDEX OAM_INDEX
ON OAM(IAU_TSTZORIGINATING) LOCAL;

-- OAAM

RENAME OAAM TO OAAM_NONPART;

CREATE TABLE OAAM
PARTITION BY RANGE (IAU_TSTZORIGINATING)
(
    PARTITION OAAM_DEFAULT VALUES LESS THAN (MAXVALUE)
)
AS SELECT * FROM OAAM_NONPART;

ALTER TABLE OAAM
ENABLE ROW MOVEMENT;

ALTER INDEX OAAM_INDEX
RENAME TO OAAM_INDEX_NONPART;

CREATE INDEX OAAM_INDEX
ON OAAM(IAU_TSTZORIGINATING) LOCAL;