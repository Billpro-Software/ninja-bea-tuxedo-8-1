import jarray
import sys

from jarray import array

from java.io import File

from java.lang import Boolean
from java.lang import Class
from java.lang import Exception
from java.lang import Long
from java.lang import Object
from java.lang import RuntimeException
from java.lang import String

from javax.management import Attribute
from javax.management import ObjectName

import ora_help
import ora_mbs
import ora_util

TYPE_STRING = "java.lang.String"
TYPE_STRING_ARRAY = "[Ljava.lang.String;"

#######Helper utilities##########

def queryMBeanName(name):
  #MBean name is different for diff app servers, so modify the name accordingly
  on = name
  if(ora_mbs.isWebSphereND() == 1):
    on = AdminControl.completeObjectName(name+',process=dmgr,*')
  elif(ora_mbs.isWebSphereAS() == 1):
      on = AdminControl.completeObjectName(name+',*')

  beans = ora_mbs.queryNames(ObjectName(on), None)
  if beans is None or beans.size() == 0:
    raise Exception, name + " MBEAN_NOT_FOUND"
  else:
    objectName = beans.iterator().next()
  return objectName

def getObjectNameForAdapters(contextName):
  query = 'com.oracle:type=OVD,context=' + contextName + ',name=AdaptersConfig'
  return queryMBeanName(query)

def getObjectNameForAnAdapter(contextName, adapterName):
  query = 'com.oracle:type=OVD.AdaptersConfig,OVD=AdaptersConfig,context=' + contextName + ',name=' + adapterName
  return queryMBeanName(query)

def getObjectNameForAnAdapterRouting(contextName, adapterName):
  query = 'com.oracle:type=OVD.AdaptersConfig.Routing,OVD.AdaptersConfig=' + adapterName + ',OVD=AdaptersConfig,context=' + contextName + ',name=Routing'
  return queryMBeanName(query)

def getObjectNameForPlugins(contextName, adapterName):
  query = 'com.oracle:name=PluginsChain,type=OVD.AdaptersConfig.PluginsChain,OVD.AdaptersConfig=' + adapterName + ',OVD=AdaptersConfig,context=' + contextName
  return queryMBeanName(query)

def getObjectNameForAPlugin(contextName, adapterName, pluginName):
  query = 'com.oracle:name=' + pluginName + ',type=OVD.AdaptersConfig.PluginsChain.PluginConfig,OVD=AdaptersConfig,OVD.AdaptersConfig=' + adapterName + ',OVD.AdaptersConfig.PluginsChain=PluginsChain,context=' + contextName
  return queryMBeanName(query)

def getObjectNameForGlobalPlugins(contextName):
  query = 'com.oracle:name=PluginsChain,context=' + contextName + ',type=OVD.PluginsChain,OVD=ServerConfig'
  return queryMBeanName(query)

def getObjectNameForAGlobalPlugin(contextName, pluginName):
  query = 'com.oracle:name=' + pluginName + ',context=' + contextName + ',type=OVD.PluginsChain.PluginConfig,OVD=ServerConfig,OVD.PluginsChain=PluginsChain'
  return queryMBeanName(query)

#######Command Implementation##########

def createLDAPAdapter(adapterName, root, host, port, remoteBase, isSecure, bindDN, bindPasswd, passCred, contextName):
  objName = getObjectNameForAdapters(contextName)
  objArray = jarray.array([adapterName, root, "No", host, port, isSecure, bindDN, bindPasswd, remoteBase, passCred, 0], Object)
  sigArray = jarray.array([TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING, "int", "boolean", TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING, "boolean"],String)
  ora_mbs.invoke(objName, 'createLDAPAdapter', objArray, sigArray)

def createJoinAdapter(adapterName, root, primaryAdapter, bindAdapter, contextName):
  objName = getObjectNameForAdapters(contextName)
  if (bindAdapter is None):
    bindAdapter = primaryAdapter
  objArray = jarray.array([adapterName, root, primaryAdapter, bindAdapter], Object)
  sigArray = jarray.array([TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING], String)
  ora_mbs.invoke(objName, 'createJoinAdapter', objArray, sigArray)

def deleteAdapter(adapterName, contextName):
  objName = getObjectNameForAdapters(contextName)
  objArray = jarray.array([adapterName], Object)
  sigArray = jarray.array([TYPE_STRING], String)
  ora_mbs.invoke(objName, 'deleteAdapter', objArray, sigArray)

def modifyLDAPAdapter(adapterName, attribute, value, contextName):
  if (attribute == 'Visible'):
    objName = getObjectNameForAnAdapterRouting(contextName, adapterName)
  else :
    objName = getObjectNameForAnAdapter(contextName, adapterName)  
  attr = Attribute(attribute, value);
  ora_mbs.setAttribute(objName, attr)

    
def addLDAPHost(adapterName, host, port, contextName):
  objName = getObjectNameForAnAdapter(contextName, adapterName)
  objArray = jarray.array([host, port, 100, 0],Object)
  sigArray = jarray.array([TYPE_STRING, "int", "int", "boolean"], String)
  ora_mbs.invoke(objName, 'addHost', objArray, sigArray)

def removeLDAPHost(adapterName, host, contextName):
  objName = getObjectNameForAnAdapter(contextName, adapterName)
  objArray = jarray.array([host],Object)
  sigArray = jarray.array([TYPE_STRING], String)
  ora_mbs.invoke(objName, 'removeHost', objArray, sigArray)

def addJoinRule(adapterName, secondary, condition, joinerType, contextName):
  objName = getObjectNameForAnAdapter(contextName, adapterName)
  objArray = jarray.array([secondary, joinerType, condition], Object)
  sigArray = jarray.array([TYPE_STRING, TYPE_STRING, TYPE_STRING], String)
  ora_mbs.invoke(objName, 'addJoinRule', objArray, sigArray)

def removeJoinRule(adapterName, secondary, contextName):
  objName = getObjectNameForAnAdapter(contextName, adapterName)
  objArray = jarray.array([secondary], Object)
  sigArray = jarray.array([TYPE_STRING], String)
  ora_mbs.invoke(objName, 'removeJoinRule', objArray, sigArray)

def addPlugin(pluginName, pluginClass, paramKeys, paramValues, adapterName, contextName):
  if (adapterName == 'GlobalPlugin') :
    objName = getObjectNameForGlobalPlugins(contextName)
  else :
    objName = getObjectNameForPlugins(contextName, adapterName)
  initParamKeys = jarray.array(paramKeys.split("|"),String)
  initParamValues = jarray.array(paramValues.split("|"),String)
  objArray = jarray.array([pluginName, pluginClass, -1, None, None, initParamKeys, initParamValues], Object)
  sigArray = jarray.array([TYPE_STRING, TYPE_STRING, "int", TYPE_STRING_ARRAY, TYPE_STRING_ARRAY, TYPE_STRING_ARRAY, TYPE_STRING_ARRAY], String)
  ora_mbs.invoke(objName, 'createPlugin', objArray, sigArray)

def removePlugin(pluginName, adapterName, contextName):
  if (adapterName == 'GlobalPlugin') :
    objName = getObjectNameForGlobalPlugins(contextName)
  else :
    objName = getObjectNameForPlugins(contextName, adapterName)
  objArray = jarray.array([pluginName], Object)
  sigArray = jarray.array([TYPE_STRING], String)
  ora_mbs.invoke(objName, 'deletePlugin', objArray, sigArray)

def addPluginParam(pluginName, paramKeys, paramValues, adapterName, contextName):
  if (adapterName == 'GlobalPlugin') :
    objName = getObjectNameForAGlobalPlugin(contextName, pluginName)
  else :
    objName = getObjectNameForAPlugin(contextName, adapterName, pluginName)
  initParamKeys = jarray.array(paramKeys.split("|"),String)
  initParamValues = jarray.array(paramValues.split("|"),String)
  objArray = jarray.array([initParamKeys, initParamValues], Object)
  sigArray = jarray.array([TYPE_STRING_ARRAY, TYPE_STRING_ARRAY], String)
  ora_mbs.invoke(objName, 'addParam', objArray, sigArray)

def removePluginParam(pluginName, paramKey, adapterName, contextName):
  if (adapterName == 'GlobalPlugin') : 
    objName = getObjectNameForAGlobalPlugin(contextName, pluginName)
  else :
    objName = getObjectNameForAPlugin(contextName, adapterName, pluginName)
  objArray = jarray.array([paramKey], Object)
  sigArray = jarray.array([TYPE_STRING], String)
  ora_mbs.invoke(objName, 'removeParam', objArray, sigArray)

def listAdapters(contextName):
  ovdObject = getObjectNameForAdapters(contextName)
  objArray = jarray.array([], Object)
  sigArray = jarray.array([], String)
  adapterObjects = ora_mbs.invoke(ovdObject, 'listAdapters', objArray, sigArray)
  length = len(adapterObjects)
  for i in range(length):
    adapterObj = adapterObjects[i]
    print 'Adapter Name : %-10s' % (ora_mbs.getAttribute(adapterObj,'Id'))
    print 'Adapter Type : %-10s' % (ora_mbs.getAttribute(adapterObj,'AdapterType'))
    print '\n'

def getAdapterDetails(adapterName, contextName):
  objName = getObjectNameForAnAdapter(contextName, adapterName)
  print 'DETAILS OF ADAPTER :  ' + adapterName
  adapterType = ora_mbs.getAttribute(objName,'AdapterType')
  print 'Adapter Type                : ' + adapterType
  if adapterType == 'LDAP':
    print 'Name                        : %-10s' % (ora_mbs.getAttribute(objName,'Id'))
    print 'Virtual NameSpace           : %-10s' % (ora_mbs.getAttribute(objName,'Root'))
    print 'Remote NameSpace            : %-10s' % (ora_mbs.getAttribute(objName,'RemoteBase'))
    serverType = ora_mbs.getAttribute(objName,'ServerType')
    if serverType != 'OPSS-IDSTORE':
      length = ora_mbs.getAttribute(objName, 'NumberOfHosts')
      i = 0
      while (i < length):
        objArray2 = jarray.array([i], Object)
        sigArray2 = jarray.array(["int"], String)
        hostName = ora_mbs.invoke(objName, 'getHostName', objArray2, sigArray2)
        objArray1 = jarray.array([hostName], Object)
        sigArray1 = jarray.array([TYPE_STRING], String) 
        port = ora_mbs.invoke(objName, 'getPort', objArray1, sigArray1)
        print 'LDAP Host                   : [%-10s : %5d]' % (hostName, port)
        i = i + 1
      secure = ora_mbs.getAttribute(objName,'Secure')
      if secure == 0:
        secureBool = 'false'
      elif secure == 1:
        secureBool = 'true'
      print 'Secure                      : ' + secureBool
      print 'Bind DN                     : %-10s' % (ora_mbs.getAttribute(objName,'BindDN'))
    print 'Pass Credentials            : %-10s' % (ora_mbs.getAttribute(objName,'PassCredentials'))
    print 'Max size of Connection Pool : %-10s' % (ora_mbs.getAttribute(objName,'MaxPoolSize'))
  elif adapterType == 'JOIN':
    print 'Name                        : %-10s' % (ora_mbs.getAttribute(objName,'Id'))
    print 'Virtual NameSpace           : %-10s' % (ora_mbs.getAttribute(objName,'Root'))
    print 'Primary Adapter             : %-10s' % (ora_mbs.getAttribute(objName,'Primary'))
    objArray = jarray.array([], Object)
    sigArray = jarray.array([], String)
    bindAdapters = ora_mbs.invoke(objName, 'listBindAdapters', objArray, sigArray)
    length = len(bindAdapters)
    for i in range(length):
      bindAdapter = bindAdapters[i]
      print 'Bind Adapter                : ' + bindAdapter     
    length1 = ora_mbs.getAttribute(objName, 'NumberOfJoinRules')
    i = 0
    while (i < length1):
      print 'Join Rule : '
      objArray2 = jarray.array([i], Object)
      sigArray2 = jarray.array(["int"], String)
      secondaryAdp = ora_mbs.invoke(objName, 'getSecondaryOfJoinRule', objArray2, sigArray2)
      print '\tSecondary Adapter   : ' + secondaryAdp
      objArray3 = jarray.array([secondaryAdp], Object)
      sigArray3 = jarray.array([TYPE_STRING], String)
      joinerType = ora_mbs.invoke(objName, 'getJoinerType', objArray3, sigArray3)
      if (joinerType == 'oracle.ods.virtualization.engine.join.SimpleJoiner'):
        joinerType = 'Simple'
      elif (joinerType == 'oracle.ods.virtualization.engine.join.CondSimpleJoiner'):
        joinerType = 'Conditional'
      elif (joinerType == 'oracle.ods.virtualization.engine.join.OneToManyJoiner'):
        joinerType = 'OneToMany'
      elif (joinerType == 'oracle.ods.virtualization.engine.join.ShadowJoiner'):
        joinerType = 'Shadow'
      print '\tJoiner Type         : ' + joinerType
      joinConditions = ora_mbs.invoke(objName, 'getJoinCondition', objArray3, sigArray3)
      length2 = len(joinConditions)
      for count in range(length2):
        joinCondn = joinConditions[count]
	print '\tJoin Condition      : ' + joinCondn
      i = i + 1
  else :
    print 'The adapter type %s is not supported through WLST' % (adapterType)

def addLibOVDCommandHelp():
  try:
    ora_help.addHelpCommandGroup("OracleLibOVDConfig", "OracleLibOVDConfig_resource")
    ora_help.addHelpCommand("createLDAPAdapter", "OracleLibOVDConfig")
    ora_help.addHelpCommand("modifyLDAPAdapter", "OracleLibOVDConfig")
    ora_help.addHelpCommand("addLDAPHost", "OracleLibOVDConfig")
    ora_help.addHelpCommand("removeLDAPHost", "OracleLibOVDConfig")
    ora_help.addHelpCommand("createJoinAdapter", "OracleLibOVDConfig")
    ora_help.addHelpCommand("deleteAdapter", "OracleLibOVDConfig")
    ora_help.addHelpCommand("addJoinRule", "OracleLibOVDConfig")
    ora_help.addHelpCommand("removeJoinRule", "OracleLibOVDConfig")
    ora_help.addHelpCommand("addPlugin", "OracleLibOVDConfig")
    ora_help.addHelpCommand("removePlugin", "OracleLibOVDConfig")
    ora_help.addHelpCommand("addPluginParam", "OracleLibOVDConfig")
    ora_help.addHelpCommand("removePluginParam", "OracleLibOVDConfig")
    ora_help.addHelpCommand("listAdapters", "OracleLibOVDConfig")
    ora_help.addHelpCommand("getAdapterDetails", "OracleLibOVDConfig")    
  except (Exception), exc:
    return

