################################################################
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################

import Audit_Handler as handler
from java.util import HashMap
import ora_mbs
import OracleHelp

#######################################################
# This function adds command help
# (Internal function)
#######################################################

def addAuditCommandHelp():

    handler.addAuditCommanHelp();

#######################################################
# This function gets the audit policy settings
#######################################################

def getAuditPolicy(on = None):
    if (on == None):
       on = getCompleteMBeanName()
    handler.getAuditPolicy(on)

#######################################################
# This function gets the audit repository settings
#######################################################

def getAuditRepository(on = None):
    if (on == None):
       on = getCompleteMBeanName()
    handler.getAuditRepository(on)

#######################################################
# This function sets the audit policy settings
#######################################################

def setAuditPolicy(on = None, filterPreset = None,addSpecialUsers = None,removeSpecialUsers = None,addCustomEvents = None,removeCustomEvents = None):
    m = HashMap()
    m.put("filterPreset", filterPreset)
    m.put("addSpecialUsers", addSpecialUsers)
    m.put("removeSpecialUsers", removeSpecialUsers)
    m.put("addCustomEvents", addCustomEvents)
    m.put("removeCustomEvents", removeCustomEvents)
    if (on == None):
       on = getCompleteMBeanName()
    handler.setAuditPolicy(m, on)
    
#######################################################
# This function sets the audit repository settings
#######################################################

def setAuditRepository(on = None, switchToDB = None,dataSourceName = None,interval = None):
    m = HashMap()
    m.put("switchToDB", switchToDB)
    m.put("dataSourceName", dataSourceName)
    m.put("interval", interval)
    if (on == None):
       on = getCompleteMBeanName()
    handler.setAuditRepository(m, on)

###########################################################
# This function lists the audit events of a given component
###########################################################

def listAuditEvents(on = None, componentType = None):
    m = HashMap()
    m.put("componentType", componentType)
    if (on == None):
       on = getCompleteMBeanName()
    handler.listAuditEvents(m, on)

def exportAuditConfig(on = None, fileName = None):
    m = HashMap()
    m.put("fileName", fileName)
    if (on == None):
       on = getCompleteMBeanName()
    handler.exportAuditConfig(m, on)

def importAuditConfig(on = None, fileName = None):
    m = HashMap()
    m.put("fileName", fileName)
    if (on == None):
       on = getCompleteMBeanName()
    handler.importAuditonfig(m. on)

def getNonJavaEEAuditMBeanName(instName=None, compName=None, compType=None):
    if (compType == 'ovd'):
       str = String("oracle.as." + compType + ":type=component.auditconfig,name=auditconfig,instance=" + instName + ",component=" + compName)
    if (compType == 'oid'):
       str = String("oracle.as.management.mbeans.register:type=component.auditconfig,name=auditconfig1,instance=" + instName + ",component=" + compName)
    if (compType == 'WebCache'):
       str = String("oracle.as.management.mbeans:name=WebCacheAuditConfig,componentname=" + compName + ",instancename=" + instName + ",type=" + compType)
    if (compType == 'ohs'):
       str = String("oracle.as.management.mbeans.register:type=component,name=" + compName +",instance=" + instName +",child=AuditMBean,childtype=AuditProxy")
    return str

def help(topic = None):
  m_name = 'audit'
  if topic == None:
    topic = m_name
  else:
    topic = m_name + '.' + topic
  return OracleHelp.help(topic)

def getCompleteMBeanName():
    if(ora_mbs.isWebSphereND() == 1):
       on= AdminControl.completeObjectName('com.oracle.jps:type=JpsConfig,process=dmgr,*')
    else:
       on= AdminControl.completeObjectName('com.oracle.jps:type=JpsConfig,*')
    return on

handler.addAuditCommandHelp()
