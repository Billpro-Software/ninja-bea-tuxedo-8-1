import OracleLibOVD_handler as handler
import OracleHelp

def createLDAPAdapter(adapterName, root, host, port, remoteBase, isSecure=0, bindDN='', bindPasswd='', passCred='Always', contextName='default'):
  handler.createLDAPAdapter(adapterName, root, host, port, remoteBase, isSecure, bindDN, bindPasswd, passCred, contextName)

def createJoinAdapter(adapterName, root, primaryAdapter, bindAdapter=None, contextName='default'):
  handler.createJoinAdapter(adapterName, root, primaryAdapter, bindAdapter, contextName)

def deleteAdapter(adapterName, contextName='default'):
  handler.deleteAdapter(adapterName, contextName)

def modifyLDAPAdapter(adapterName, attribute, value, contextName='default'):
  handler.modifyLDAPAdapter(adapterName, attribute, value, contextName)

def addLDAPHost(adapterName, host, port, contextName='default'):
  handler.addLDAPHost(adapterName, host, port, contextName)

def removeLDAPHost(adapterName, host, contextName='default'):
  handler.removeLDAPHost(adapterName, host, contextName)

def addJoinRule(adapterName, secondary, condition, joinerType='Simple', contextName='default'):
  handler.addJoinRule(adapterName, secondary, condition, joinerType, contextName)

def removeJoinRule(adapterName, secondary, contextName='default'):
  handler.removeJoinRule(adapterName, secondary, contextName)

def addPlugin(pluginName, pluginClass, paramKeys, paramValues, adapterName='GlobalPlugin', contextName='default'):
  handler.addPlugin(pluginName, pluginClass, paramKeys, paramValues, adapterName, contextName)

def removePlugin(pluginName, adapterName='GlobalPlugin', contextName='default'):  handler.removePlugin(pluginName, adapterName, contextName)
  
def addPluginParam(pluginName, paramKeys, paramValues, adapterName='GlobalPlugin', contextName='default'):
  handler.addPluginParam(pluginName, paramKeys, paramValues, adapterName, contextName)

def removePluginParam(pluginName, paramKey, adapterName='GlobalPlugin', contextName='default'):
  handler.removePluginParam(pluginName, paramKey, adapterName, contextName)

def listAdapters(contextName='default'):
  handler.listAdapters(contextName)

def getAdapterDetails(adapterName, contextName='default'):
  handler.getAdapterDetails(adapterName, contextName)

#internal commands
def help(topic = None):
  m_name = 'OracleLibOVDConfig'
  if topic == None:
    topic = m_name
  else:
    topic = m_name + '.' + topic
  return OracleHelp.help(topic)


  
