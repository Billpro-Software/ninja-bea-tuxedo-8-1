################################################################
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################

from javax.management import RuntimeMBeanException
from java.util import ResourceBundle
from java.util import Locale
from oracle.security.audit.mesg import AuditMBeanResource
import ora_mbs
import ora_help 

#######################################################
# This function adds command help
# (Internal function)
#######################################################

def addAuditCommandHelp():
  try:
    ora_help.addHelpCommandGroup("audit","audit_wlst")
    ora_help.addHelpCommand("getAuditPolicy","audit", offline='false', online='false')
    ora_help.addHelpCommand("setAuditPolicy","audit", offline='false', online='false')
    ora_help.addHelpCommand("getAuditRepository","audit", offline='false', online='false')
    ora_help.addHelpCommand("setAuditRepository","audit", offline='false', online='false')
    ora_help.addHelpCommand("listAuditEvents","audit", offline='false', online='false')
    ora_help.addHelpCommand("importAuditConfig","audit", offline='false', online='false')
    ora_help.addHelpCommand("exportAuditConfig","audit", offline='false', online='false')
    ora_help.addHelpCommand("getNonJavaEEAuditMBeanName", "audit", offline='false', online='false')
  except Exception, e:
    return

mAuditResourceBundle = ResourceBundle.getBundle("oracle.security.audit.mesg.AuditMBeanResource", Locale.getDefault(), AuditMBeanResource.getClassLoader())

#######################################################
# This function gets the audit policy settings
#######################################################

def getAuditPolicy(on):
    config = None    
    try:
        if (ora_mbs.isConnected() == 1):
          obn = ora_mbs.makeObjectName(on)
          config = ora_mbs.invoke(obn,"wlstAuditConfig",None,None)
        else:
         msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
         print msg
    except RuntimeMBeanException, e:
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

def getAuditRepository(on):
    config = None
    try:
       if (ora_mbs.isConnected() == 1):
         obn = ora_mbs.makeObjectName(on)
         config = ora_mbs.invoke(obn,"wlstAuditLoaderConfig",None,None)
       else:
         msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
         print msg
    except RuntimeMBeanException, e:
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

def setAuditPolicy(m, on):
    retval = None
    try:
         if(ora_mbs.isConnected() == 1):
          obn = ora_mbs.makeObjectName(on)
          params = [m.get("filterPreset"), m.get("addSpecialUsers"), m.get("removeSpecialUsers"), m.get("addCustomEvents"), m.get("removeCustomEvents")]
          sign = ["java.lang.String", "java.lang.String", "java.lang.String", "java.lang.String", "java.lang.String"]
          retval = ora_mbs.invoke(obn, "wlstUpdateAuditPolicy", params, sign)
         else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
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

def setAuditRepository(m, on):
    retval = None
    try:
        if (ora_mbs.isConnected() == 1):
          obn = ora_mbs.makeObjectName(on)
          params =[m.get("switchToDB"), m.get("dataSourceName"), m.get("interval")]
          sign = ["java.lang.String", "java.lang.String", "java.lang.String"]
          retval = ora_mbs.invoke(obn,"wlstUpdateAuditRepository",params,sign) 
        else:
         msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
         print msg
    except RuntimeMBeanException, e:
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
        	print "Server has to be restarted\n" 

###########################################################
# This function lists the audit events of a given component
###########################################################

def listAuditEvents(m, on):
    events = None
    try:
        if (ora_mbs.isConnected() == 1):
          obn = ora_mbs.makeObjectName(on)
          params = [m.get("componentType")]
          sign = ["java.lang.String"]
          events = ora_mbs.invoke(obn, "wlstAuditEvents", params, sign)
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
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

def exportAuditConfig(m, on):
    audconfig = None
    try:
        if (ora_mbs.isConnected() == 1):
          obn = ora_mbs.makeObjectName(on)
          audconfig = ora_mbs.invoke(obn,"wlstExportAuditConfig",None,None)
          f = open(m.get("fileName"), 'w')
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
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except IOError:
        msg = mAuditResourceBundle.getString("MSG_WLST_CANT_OPEN")
        print msg + fileName
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

def importAuditConfig(m, on):
    audconfig = None
    retval = None
    try:
        if (ora_mbs.isConnected() == 'true'):
          obn = ora_mbs.makeObjectName(on)
          f = open(m.get("fileName"), 'r')
          audconfig = f.read()
          f.close()
          params = [audconfig]
          sign = ["java.lang.String"]
          retval = ora_mbs.invoke(obn,"wlstImportAuditConfig",params,sign)
        else:
          msg = mAuditResourceBundle.getString("MSG_WLST_CONNECT")
          print msg
    except RuntimeMBeanException, e:
        msg = mAuditResourceBundle.getString("MSG_WLST_COMMAND_FAILED")
        print msg + e.getMessage() + "\n"
    except IOError:
        msg = mAuditResourceBundle.getString("MSG_WLST_CANT_OPEN")
        print msg + fileName
    except :
        msg = mAuditResourceBundle.getString("MSG_WLST_UNKNOWN_REASON")
        print msg
        raise

    if retval != None:
      print retval

addAuditCommandHelp()
