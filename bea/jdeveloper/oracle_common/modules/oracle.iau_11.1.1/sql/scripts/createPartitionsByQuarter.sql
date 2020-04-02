Rem
Rem $Header: entsec_ldap/java/src/oracle/security/audit/rcu/scripts/createPartitionsByQuarter.sql /main/2 2009/09/24 17:47:15 shiahuan Exp $
Rem
Rem createPartitionsByQuarter.sql
Rem
Rem Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved. 
Rem
Rem    NAME
Rem      createPartitionsByQuarter.sql - <one-line expansion of the name>
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

-- This is a sample SQL script to create partitions by quarter
-- for the base and component tables in Audit schema.
-- Users need to update the value of YEAR every year.


-- IAU_BASE

ALTER TABLE IAU_BASE
SPLIT PARTITION IAU_BASE_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION IAU_BASE_Q1_2008, PARTITION IAU_BASE_DEFAULT)
UPDATE INDEXES;

ALTER TABLE IAU_BASE
SPLIT PARTITION IAU_BASE_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION IAU_BASE_Q2_2008, PARTITION IAU_BASE_DEFAULT)
UPDATE INDEXES;

ALTER TABLE IAU_BASE
SPLIT PARTITION IAU_BASE_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION IAU_BASE_Q3_2008, PARTITION IAU_BASE_DEFAULT)
UPDATE INDEXES;

ALTER TABLE IAU_BASE
SPLIT PARTITION IAU_BASE_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION IAU_BASE_Q4_2008, PARTITION IAU_BASE_DEFAULT)
UPDATE INDEXES;

-- WEBCACHECOMPONENT

ALTER TABLE WEBCACHECOMPONENT
SPLIT PARTITION WEBCACHECOMPONENT_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION WEBCACHECOMPONENT_Q1_2008, PARTITION WEBCACHECOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WEBCACHECOMPONENT
SPLIT PARTITION WEBCACHECOMPONENT_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION WEBCACHECOMPONENT_Q2_2008, PARTITION WEBCACHECOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WEBCACHECOMPONENT
SPLIT PARTITION WEBCACHECOMPONENT_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION WEBCACHECOMPONENT_Q3_2008, PARTITION WEBCACHECOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WEBCACHECOMPONENT
SPLIT PARTITION WEBCACHECOMPONENT_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION WEBCACHECOMPONENT_Q4_2008, PARTITION WEBCACHECOMPONENT_DEFAULT)
UPDATE INDEXES;

-- OVDCOMPONENT

ALTER TABLE OVDCOMPONENT
SPLIT PARTITION OVDCOMPONENT_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OVDCOMPONENT_Q1_2008, PARTITION OVDCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OVDCOMPONENT
SPLIT PARTITION OVDCOMPONENT_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OVDCOMPONENT_Q2_2008, PARTITION OVDCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OVDCOMPONENT
SPLIT PARTITION OVDCOMPONENT_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OVDCOMPONENT_Q3_2008, PARTITION OVDCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OVDCOMPONENT
SPLIT PARTITION OVDCOMPONENT_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OVDCOMPONENT_Q4_2008, PARTITION OVDCOMPONENT_DEFAULT)
UPDATE INDEXES;

-- OIDCOMPONENT

ALTER TABLE OIDCOMPONENT
SPLIT PARTITION OIDCOMPONENT_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OIDCOMPONENT_Q1_2008, PARTITION OIDCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OIDCOMPONENT
SPLIT PARTITION OIDCOMPONENT_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OIDCOMPONENT_Q2_2008, PARTITION OIDCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OIDCOMPONENT
SPLIT PARTITION OIDCOMPONENT_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OIDCOMPONENT_Q3_2008, PARTITION OIDCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OIDCOMPONENT
SPLIT PARTITION OIDCOMPONENT_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OIDCOMPONENT_Q4_2008, PARTITION OIDCOMPONENT_DEFAULT)
UPDATE INDEXES;

-- OWSM_PM_EJB

ALTER TABLE OWSM_PM_EJB
SPLIT PARTITION OWSM_PM_EJB_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OWSM_PM_EJB_Q1_2008, PARTITION OWSM_PM_EJB_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OWSM_PM_EJB
SPLIT PARTITION OWSM_PM_EJB_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OWSM_PM_EJB_Q2_2008, PARTITION OWSM_PM_EJB_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OWSM_PM_EJB
SPLIT PARTITION OWSM_PM_EJB_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OWSM_PM_EJB_Q3_2008, PARTITION OWSM_PM_EJB_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OWSM_PM_EJB
SPLIT PARTITION OWSM_PM_EJB_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OWSM_PM_EJB_Q4_2008, PARTITION OWSM_PM_EJB_DEFAULT)
UPDATE INDEXES;

-- OWSM_AGENT

ALTER TABLE OWSM_AGENT
SPLIT PARTITION OWSM_AGENT_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OWSM_AGENT_Q1_2008, PARTITION OWSM_AGENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OWSM_AGENT
SPLIT PARTITION OWSM_AGENT_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OWSM_AGENT_Q2_2008, PARTITION OWSM_AGENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OWSM_AGENT
SPLIT PARTITION OWSM_AGENT_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OWSM_AGENT_Q3_2008, PARTITION OWSM_AGENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OWSM_AGENT
SPLIT PARTITION OWSM_AGENT_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OWSM_AGENT_Q4_2008, PARTITION OWSM_AGENT_DEFAULT)
UPDATE INDEXES;

-- DIP

ALTER TABLE DIP
SPLIT PARTITION DIP_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION DIP_Q1_2008, PARTITION DIP_DEFAULT)
UPDATE INDEXES;

ALTER TABLE DIP
SPLIT PARTITION DIP_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION DIP_Q2_2008, PARTITION DIP_DEFAULT)
UPDATE INDEXES;

ALTER TABLE DIP
SPLIT PARTITION DIP_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION DIP_Q3_2008, PARTITION DIP_DEFAULT)
UPDATE INDEXES;

ALTER TABLE DIP
SPLIT PARTITION DIP_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION DIP_Q4_2008, PARTITION DIP_DEFAULT)
UPDATE INDEXES;

-- OHSCOMPONENT

ALTER TABLE OHSCOMPONENT
SPLIT PARTITION OHSCOMPONENT_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OHSCOMPONENT_Q1_2008, PARTITION OHSCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OHSCOMPONENT
SPLIT PARTITION OHSCOMPONENT_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OHSCOMPONENT_Q2_2008, PARTITION OHSCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OHSCOMPONENT
SPLIT PARTITION OHSCOMPONENT_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OHSCOMPONENT_Q3_2008, PARTITION OHSCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OHSCOMPONENT
SPLIT PARTITION OHSCOMPONENT_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OHSCOMPONENT_Q4_2008, PARTITION OHSCOMPONENT_DEFAULT)
UPDATE INDEXES;

-- JPS

ALTER TABLE JPS
SPLIT PARTITION JPS_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION JPS_Q1_2008, PARTITION JPS_DEFAULT)
UPDATE INDEXES;

ALTER TABLE JPS
SPLIT PARTITION JPS_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION JPS_Q2_2008, PARTITION JPS_DEFAULT)
UPDATE INDEXES;

ALTER TABLE JPS
SPLIT PARTITION JPS_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION JPS_Q3_2008, PARTITION JPS_DEFAULT)
UPDATE INDEXES;

ALTER TABLE JPS
SPLIT PARTITION JPS_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION JPS_Q4_2008, PARTITION JPS_DEFAULT)
UPDATE INDEXES;

-- ADMINSERVER

ALTER TABLE ADMINSERVER
SPLIT PARTITION ADMINSERVER_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION ADMINSERVER_Q1_2008, PARTITION ADMINSERVER_DEFAULT)
UPDATE INDEXES;

ALTER TABLE ADMINSERVER
SPLIT PARTITION ADMINSERVER_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION ADMINSERVER_Q2_2008, PARTITION ADMINSERVER_DEFAULT)
UPDATE INDEXES;

ALTER TABLE ADMINSERVER
SPLIT PARTITION ADMINSERVER_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION ADMINSERVER_Q3_2008, PARTITION ADMINSERVER_DEFAULT)
UPDATE INDEXES;

ALTER TABLE ADMINSERVER
SPLIT PARTITION ADMINSERVER_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION ADMINSERVER_Q4_2008, PARTITION ADMINSERVER_DEFAULT)
UPDATE INDEXES;

-- REPORTSSERVERCOMPONENT

ALTER TABLE REPORTSSERVERCOMPONENT
SPLIT PARTITION REPORTSSERVERCOMPONENT_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION REPORTSSERVERCOMPONENT_Q1_2008, PARTITION REPORTSSERVERCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE REPORTSSERVERCOMPONENT
SPLIT PARTITION REPORTSSERVERCOMPONENT_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION REPORTSSERVERCOMPONENT_Q2_2008, PARTITION REPORTSSERVERCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE REPORTSSERVERCOMPONENT
SPLIT PARTITION REPORTSSERVERCOMPONENT_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION REPORTSSERVERCOMPONENT_Q3_2008, PARTITION REPORTSSERVERCOMPONENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE REPORTSSERVERCOMPONENT
SPLIT PARTITION REPORTSSERVERCOMPONENT_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION REPORTSSERVERCOMPONENT_Q4_2008, PARTITION REPORTSSERVERCOMPONENT_DEFAULT)
UPDATE INDEXES;

-- WEBSERVICES

ALTER TABLE WEBSERVICES
SPLIT PARTITION WEBSERVICES_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION WEBSERVICES_Q1_2008, PARTITION WEBSERVICES_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WEBSERVICES
SPLIT PARTITION WEBSERVICES_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION WEBSERVICES_Q2_2008, PARTITION WEBSERVICES_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WEBSERVICES
SPLIT PARTITION WEBSERVICES_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION WEBSERVICES_Q3_2008, PARTITION WEBSERVICES_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WEBSERVICES
SPLIT PARTITION WEBSERVICES_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION WEBSERVICES_Q4_2008, PARTITION WEBSERVICES_DEFAULT)
UPDATE INDEXES;

-- WS_POLICYATTACHMENT

ALTER TABLE WS_POLICYATTACHMENT
SPLIT PARTITION WS_POLICYATTACHMENT_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION WS_POLICYATTACHMENT_Q1_2008, PARTITION WS_POLICYATTACHMENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WS_POLICYATTACHMENT
SPLIT PARTITION WS_POLICYATTACHMENT_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION WS_POLICYATTACHMENT_Q2_2008, PARTITION WS_POLICYATTACHMENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WS_POLICYATTACHMENT
SPLIT PARTITION WS_POLICYATTACHMENT_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION WS_POLICYATTACHMENT_Q3_2008, PARTITION WS_POLICYATTACHMENT_DEFAULT)
UPDATE INDEXES;

ALTER TABLE WS_POLICYATTACHMENT
SPLIT PARTITION WS_POLICYATTACHMENT_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION WS_POLICYATTACHMENT_Q4_2008, PARTITION WS_POLICYATTACHMENT_DEFAULT)
UPDATE INDEXES;

-- OIF

ALTER TABLE OIF
SPLIT PARTITION OIF_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OIF_Q1_2008, PARTITION OIF_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OIF
SPLIT PARTITION OIF_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OIF_Q2_2008, PARTITION OIF_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OIF
SPLIT PARTITION OIF_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OIF_Q3_2008, PARTITION OIF_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OIF
SPLIT PARTITION OIF_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OIF_Q4_2008, PARTITION OIF_DEFAULT)
UPDATE INDEXES;

-- OAM

ALTER TABLE OAM
SPLIT PARTITION OAM_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OAM_Q1_2008, PARTITION OAM_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OAM
SPLIT PARTITION OAM_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OAM_Q2_2008, PARTITION OAM_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OAM
SPLIT PARTITION OAM_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OAM_Q3_2008, PARTITION OAM_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OAM
SPLIT PARTITION OAM_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OAM_Q4_2008, PARTITION OAM_DEFAULT)
UPDATE INDEXES;

-- OAAM

ALTER TABLE OAAM
SPLIT PARTITION OAAM_DEFAULT AT (TO_DATE('01/04/2008', 'DD/MM/YYYY')) INTO (PARTITION OAAM_Q1_2008, PARTITION OAAM_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OAAM
SPLIT PARTITION OAAM_DEFAULT AT (TO_DATE('01/07/2008', 'DD/MM/YYYY')) INTO (PARTITION OAAM_Q2_2008, PARTITION OAAM_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OAAM
SPLIT PARTITION OAAM_DEFAULT AT (TO_DATE('01/10/2008', 'DD/MM/YYYY')) INTO (PARTITION OAAM_Q3_2008, PARTITION OAAM_DEFAULT)
UPDATE INDEXES;

ALTER TABLE OAAM
SPLIT PARTITION OAAM_DEFAULT AT (TO_DATE('01/01/2009', 'DD/MM/YYYY')) INTO (PARTITION OAAM_Q4_2008, PARTITION OAAM_DEFAULT)
UPDATE INDEXES;