"""
Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.

Caution: This file is part of the wsadmin/jboss implementation. Do not edit or 
move this file because this may cause wsadmin/jboss commands and scripts to 
fail. Do not try to reuse the logic in this file or keep copies of this file 
because this could cause your wsadmin/jboss scripts to fail when you upgrade 
to a different version of wsadmin/jboss.

Oracle Fusion Middleware logging commands.

"""

import cie.OracleHelp as OracleHelp
import jarray
import os
import sys
import java.lang
import ora_mbs
import ora_help
from java.lang import Class
from java.lang import String
from java.lang import StringBuffer
from java.util import Locale
from java.util import ResourceBundle
from javax.management import ObjectName
from javax.management import MBeanServerInvocationHandler
from javax.management import MBeanServerConnection
from javax.management import InstanceNotFoundException

ORACLEADMINSERVER = "OracleAdminServer"
DEPLOYMENTMANAGER = "dmgr"

JBOSS_SERVER = "jrfServer"

# mbean objectNames
WAS_SERVER  = "WebSphere:type=Server,processType=DeploymentManager,*"
WAS_MANAGED = "WebSphere:type=Server,processType=ManagedProcess,*"
WAS_OAS     = "WebSphere:type=Server,processType=ManagedProcess,process=OracleAdminServer,*"

MSGFILE     = "oracle.as.management.logging.messages.CommandHelp"

#replacement strings
F_ADMINSERVER = "AdminServer" 
R_ADMINSERVER = "DeploymentManager"
R_PREFIX      = "print OracleDFW."

errStr = ""
"""
listADRHomes command
"""
def listADRHomes(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server = kws.get(handler.SERVER)

  try:
    mbeanStr = _setMBeanServer(handler.INCIDENT_MANAGER, server)

    ret = handler.listADRHomes(_MBS(), mbeanStr, **kws)
    print handler.formatListADRHomes(ret)
    _hideDisplay()
    return ret
  except DfwError, ex:
    print ex.getMsg()
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except: 
    _printError(server)


"""
listProblems command
"""
def listProblems(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server   = kws.get(handler.SERVER)
  try:
    mbeanStr = _setMBeanServer(handler.INCIDENT_MANAGER, server)

    problems =  handler.listProblems(_MBS(), mbeanStr, **kws)
    print handler.formatListProblems(problems)
    _hideDisplay()
    return problems
  except DfwError, ex:
    print ex.getMsg()
  except Exception, ex:
    print ex
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)

"""
listIncidents command
"""
def listIncidents(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server = kws.get(handler.SERVER)

  try:
    mbeanStr = _setMBeanServer(handler.INCIDENT_MANAGER, server)

    incidents =  handler.listIncidents(_MBS(), mbeanStr, **kws)
    print handler.formatListIncidents(incidents)
    _hideDisplay()
    return incidents
  except DfwError, ex:
    print ex.getMsg()
  except Exception, ex:
    print ex
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)


"""
showIncident command
"""
def showIncident(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server   = kws.get(handler.SERVER)
  try:
    mbeanStr = _setMBeanServer(handler.INCIDENT_MANAGER, server)

    incident =  handler.showIncident(_MBS(), mbeanStr, **kws)
    print handler.formatShowIncident(incident)
    _hideDisplay()
    return incident
  except DfwError, ex:
    print ex.getMsg()
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)


"""
createIncident command
"""
def createIncident(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server = kws.get(handler.SERVER)
  try:
    mbeanStr = _setMBeanServer(handler.INCIDENT_MANAGER, server)

    incident = handler.createIncident(_MBS(), mbeanStr, **kws)
    print handler.formatCreateIncident(incident)
    _hideDisplay()
    return incident
  except DfwError, ex:
    print ex.getMsg()
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)


"""
getIncidentFile command
"""
def getIncidentFile(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server = kws.get(handler.SERVER)

  try:
    mbeanStr  = _setMBeanServer(handler.INCIDENT_MANAGER, server)
    streamStr = _setMBeanServer(handler.STREAMER, server)

    incident =  handler.getIncidentFile(_MBS(), mbeanStr, streamStr, **kws)
    print handler.formatGetIncidentFile(incident)
    _hideDisplay()
    return incident
  except DfwError, ex:
    print ex.getMsg()
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)



"""
listDumps command
"""
def listDumps(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server = kws.get(handler.SERVER)

  try:
    mbeanStr = _setMBeanServer(handler.DUMP_MANAGER, server)

    dumps =  handler.listDumps(_MBS(), mbeanStr, **kws)
    print handler.formatListDumps(dumps)
    _hideDisplay()
    return dumps
  except DfwError, ex:
    print ex.getMsg()
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)


"""
describeDump Command
"""
def describeDump(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print GetMsg(handler.NOT_CONNECTED, None)
    return

  server = kws.get(handler.SERVER)

  try:
    mbeanStr = _setMBeanServer(handler.DUMP_MANAGER, server)

    dump = handler.describeDump(_MBS(), mbeanStr, **kws)
    print handler.formatDescribeDump(dump)
    _hideDisplay()
    return dump
  except DfwError, ex:
    print ex.getMsg()
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)


"""
executeDump command
"""
def executeDump(**kws):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if not _isConnected():
    print handler.oraDfwGetMsg(handler.NOT_CONNECTED, None)
    return

  server = kws.get(handler.SERVER)

  try:
    mbeanStr  = _setMBeanServer(handler.DUMP_MANAGER, server)
    streamStr = _setMBeanServer(handler.STREAMER, server)

    dump = handler.executeDump(_MBS(), mbeanStr, streamStr, **kws)
    print handler.formatExecuteDump(dump)
    _hideDisplay()
    return dump
  except DfwError, ex:
    print ex.getMsg()
  except InstanceNotFoundException, ex:
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server)
  except:
    _printError(server)

def help(cmd=None):
    _module = "OracleDFW"
    if cmd == None:
        cmd = _module
    else:
        cmd = _module + '.' + cmd
    return OracleHelp.help(cmd)

"""
Private methods
=======================================================================
"""

# verify wsadmin/ojbst is connected to the server
def _isConnected():
  return ora_mbs.isConnected()

def _setMBeanServer(baseStr, server):
  if ora_mbs.isWebSphereND():
    return _setMBeanServer_WAS(baseStr, server)
  elif ora_mbs.isWebSphereAS():
    return _setMBeanServer_WAS(baseStr, server)
  elif ora_mbs.isJBoss():
    return _setMBeanServer_JBOSS(baseStr, server)
  return None



def _setMBeanServer_WAS(baseStr, server):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  global errStr

  dmgr    = AdminControl.completeObjectName(WAS_SERVER)
  process = ObjectName(dmgr).getKeyProperty("name")

  if process is None:
    dmgr    = AdminControl.completeObjectName(WAS_MANAGED)
    process = ObjectName(dmgr).getKeyProperty("name")

  if process == DEPLOYMENTMANAGER:
    oas    = AdminControl.completeObjectName(WAS_OAS)
    oasProc = ObjectName(oas).getKeyProperty("name")
    if oasProc is None:
      handler = Oracle_dfw_handler()
      raise DfwError, handler.oraDfwGetMsg(handler.OAS_NOT_UP, None)
    if server is None:
      process = ORACLEADMINSERVER
    else:
      process = server
  else:
    # if this isn't dmgr and the server name is not this server return error
    if server is not None and server != process:
      handler = Oracle_dfw_handler()
      raise DfwError,  _strFilter(handler.oraDfwGetMsg(handler.WRONG_SERVER))
      return

  # WAS AS edition is a single process, and so there is no process in the
  # string
  if process is None:
    queryName = baseStr + ",*"
  else:
    queryName = baseStr +  ",process=" + process +",*"

  objStr = AdminControl.queryNames(queryName)

  return objStr

def _setMBeanServer_JBOSS(baseStr, server):
  #print ora_mbs.queryNames(ObjectName("*:*"), None)
  if server is None:
    x =  ora_mbs.queryNames(ObjectName(baseStr), None).toArray()
    if len(x) == 0:
      return baseStr + ",ServerName=" + JBOSS_SERVER
    else:
      return baseStr
  else:
    str = baseStr + ",ServerName=" + server
    if server == JBOSS_SERVER:
      x =  ora_mbs.queryNames(ObjectName(str), None).toArray()
      if len(x) == 0:
        return baseStr
    return str;

def _printError(server):
  from Oracle_dfw_handler import Oracle_dfw_handler
  from Oracle_dfw_handler import DfwError

  handler = Oracle_dfw_handler()
  if str(sys.exc_info()[1]).find('InstanceNotFoundException') > -1: 
    if server is None:
      server = ORACLEADMINSERVER
    print handler.oraDfwGetMsg(handler.INCIDENT_MGR_DISABLED, server) 
  else: 
    print str(sys.exc_info()[1])[41:] 

def _strFilter(str, cmd = None):
  str = str.replace(F_ADMINSERVER, R_ADMINSERVER)

  if cmd is not None:
    rStr = R_PREFIX + cmd
    str = str.replace(cmd, rStr)

  return str

def _eatDisplay(dummy):
    sys.displayhook = saved_displayhook

def _hideDisplay():
    global saved_displayhook
    saved_displayhook = sys.displayhook
    sys.displayhook = _eatDisplay

"""
Provides a MBeanServerConnection interface around ora_mbs object.
This class DOES NOT implement all MBeanServerConnection methods. An
exception will be thrown if a non-implemented method is invoked.
This was borrowed from OracleODL.py
"""
class _MBS(MBeanServerConnection):

    def getAttribute(self, name, attr):
        return ora_mbs.getAttribute(name, attr)

    def getAttributes(self, name, attrs):
        return ora_mbs.getAttributes(name, attrs)

    def invoke(self, name, operationName, params, signature):
        return ora_mbs.invoke(name, operationName, params, signature)

    def isRegistered(self, name):
        return ora_mbs.isRegistered(name)

    def queryNames(self, name, query):
        return ora_mbs.queryNames(name, query)

    def setAttribute(self, name, attr):
        return ora_mbs.setAttribute(name, attr)

    def setAttributes(self, name, attrs):
        return ora_mbs.setAttributes(name, attrs)

    def getMBeanInfo(self, name):
        return ora_mbs.getMBeanInfo(name)
