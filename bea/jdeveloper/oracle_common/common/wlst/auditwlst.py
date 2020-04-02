################################################################
# Caution: This file is part of the WLST implementation. 
# Do not edit or move this file because this may cause 
# WLST commands and scripts to fail. Do not try to reuse 
# the logic in this file or keep copies of this file because 
# this could cause your WLST scripts to fail when you 
# upgrade to a different version of WLST. 
#
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################

from javax.management import RuntimeMBeanException
from java.util import ResourceBundle
from java.util import Locale

#######################################################
# This function adds command help
# (Internal function)
#######################################################

def addAuditCommandHelp():
  try:
    addHelpCommandGroup("audit","audit_wlst")
    addHelpCommand("getAuditPolicy","audit")
    addHelpCommand("setAuditPolicy","audit")
    addHelpCommand("getAuditRepository","audit")
    addHelpCommand("setAuditRepository","audit")
    addHelpCommand("listAuditEvents","audit")
    addHelpCommand("importAuditConfig","audit")
    addHelpCommand("exportAuditConfig","audit")
    addHelpCommand("getNonJavaEEAuditMBeanName", "audit")
  except Exception, e:
    return

mAuditResourceBundle = ResourceBundle.getBundle("oracle.security.audit.mesg.AuditMBeanResource")

#######################################################
# This function gets the audit policy settings
#######################################################

def getAuditPolicy(on="com.oracle.jps:type=JpsConfig"):
    config = None    
    try:
        if (connected == 'true'):
          location = currentTree()
          if (on == "com.oracle.jps:type=JpsConfig"):
            domainRuntime()
          else:
            serverRuntime()
          obn = ObjectName(on)
          config = mbs.invoke(obn,"wlstAuditConfig",None,None)
          location()
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
        location()
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

    if config != None:
       print config
    else:
       msg = mAuditResourceBundle.getString("MSG_WLST_CONFIG_NOT_FOUND")
       print msg

#######################################################
# This function gets the audit repository settings
#######################################################

def getAuditRepository(on="com.oracle.jps:type=JpsConfig"):
    config = None
    
    try:
       if (connected == 'true'):
         location = currentTree()
         if (on == "com.oracle.jps:type=JpsConfig"):
           domainRuntime()
         else:
           serverRuntime()
         obn = ObjectName(on)
         config = mbs.invoke(obn,"wlstAuditLoaderConfig",None,None)
         location()
       else:
         msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
         print msg
    except RuntimeMBeanException, e:
       location()
       msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
       print msg + e.getMessage() + "\n"
    except :
       msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
       print msg
       raise

    if config != None:
       print config
    else:
       msg = mAuditResourceBundle.getString("MSG_WLST_CONFIG_NOT_FOUND")
       print msg

#######################################################
# This function sets the audit policy settings
#######################################################

def setAuditPolicy(on="com.oracle.jps:type=JpsConfig",filterPreset = None,addSpecialUsers = None,removeSpecialUsers = None,addCustomEvents = None,removeCustomEvents = None):
    retval = None
    
    try:
        if (connected == 'true'):
          location = currentTree()
          if (on == "com.oracle.jps:type=JpsConfig"):
            domainRuntime()
          else:
            serverRuntime()
          obn = ObjectName(on)
          params = [filterPreset,addSpecialUsers,removeSpecialUsers,addCustomEvents,removeCustomEvents]
          sign = ["java.lang.String", "java.lang.String", "java.lang.String", "java.lang.String", "java.lang.String"]
          retval = mbs.invoke(obn, "wlstUpdateAuditPolicy", params, sign)
          location()
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
        location()
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

    if retval != None:
        print retval
        msg = mAuditResourceBundle.getString("MSG_WLST_SERVER_RESTART")
        print msg
    
#######################################################
# This function sets the audit repository settings
#######################################################

def setAuditRepository(on="com.oracle.jps:type=JpsConfig",switchToDB = None,dataSourceName = None,interval = None):
    retval = None
    
    try:
        if (connected == 'true'):
          location = currentTree()
          if (on == "com.oracle.jps:type=JpsConfig"):
            domainRuntime()
          else:
            serverRuntime()
          obn = ObjectName(on)
          params =[switchToDB,dataSourceName,interval]
          sign = ["java.lang.String", "java.lang.String", "java.lang.String"]
          retval = mbs.invoke(obn,"wlstUpdateAuditRepository",params,sign) 
          location()
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
        location()
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

    if retval != None:
        print retval
	if (retval.find("Audit Repository Information updated") != -1):
        	msg = mAuditResourceBundle.getString("MSG_WLST_SERVER_RESTART")
        	print msg

###########################################################
# This function lists the audit events of a given component
###########################################################

def listAuditEvents(componentType = None, on="com.oracle.jps:type=JpsConfig"):
    events = None
    
    try:
        if (connected == 'true'):
          location = currentTree()
          if (on == "com.oracle.jps:type=JpsConfig"):
            domainRuntime()
          else:
            serverRuntime()
          obn = ObjectName(on)
          params = [componentType]
          sign = ["java.lang.String"]
          events = mbs.invoke(obn, "wlstAuditEvents", params, sign)
          location()
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
        location()
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

    if events != None:
        print events
    else:
        msg = mAuditResourceBundle.getString("MSG_WLST_EVENTS_NOT_FOUND")
        print msg

def exportAuditConfig(fileName = None,on="com.oracle.jps:type=JpsConfig"):
    audconfig = None
    
    try:
        if (connected == 'true'):
          location = currentTree()
          if (on == "com.oracle.jps:type=JpsConfig"):
            domainRuntime()
          else:
            serverRuntime()
          obn = ObjectName(on)
          audconfig = mbs.invoke(obn,"wlstExportAuditConfig",None,None)
          location()
          f = open(fileName,'w')
          f.write(audconfig)
          f.close()
          if audconfig != None:
            print audconfig
          else:
            msg = mAuditResourceBundle.getString("MSG_WLST_CONFIG_NOT_FOUND")
            print msg
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
        location()
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except IOError:
        msg = mAuditResourceBundle.getString("MSG_WLST_CANT_OPEN")
        print msg + fileName
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

def importAuditConfig(fileName = None,on="com.oracle.jps:type=JpsConfig"):
    audconfig = None
    
    retval = None
    try:
        if (connected == 'true'):
          location = currentTree()
          if (on == "com.oracle.jps:type=JpsConfig"):
            domainRuntime()
          else:
            serverRuntime()
          obn = ObjectName(on)
          f = open(fileName,'r')
          audconfig = f.read()
          f.close()
          params = [audconfig]
          sign = ["java.lang.String"]
          retval = mbs.invoke(obn,"wlstImportAuditConfig",params,sign)
          location()
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
        location()
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except IOError:
        location()
        msg = mAuditResourceBundle.getString("MSG_WLST_CANT_OPEN")
        print msg + fileName
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

    if retval != None:
      print retval

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

addAuditCommandHelp()
