try:
  _oc = System.getProperty('COMMON_COMPONENTS_HOME')
  if _oc is not None:
    _sh = os.path.join(_oc, os.path.join('common', 'script_handlers'))
    if _sh not in sys.path:
      sys.path.append(_sh)
except:
  print "" #ignore the exception

import OracleLibOVD_handler as libovdhandler

def createLDAPAdapter(adapterName, root, host, port, remoteBase, isSecure=0, bindDN='', bindPasswd='', passCred='Always', contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.createLDAPAdapter(adapterName, root, host, port, remoteBase, isSecure, bindDN, bindPasswd, passCred, contextName)

def createJoinAdapter(adapterName, root, primaryAdapter, bindAdapter=None, contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.createJoinAdapter(adapterName, root, primaryAdapter, bindAdapter, contextName)

def deleteAdapter(adapterName, contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.deleteAdapter(adapterName, contextName)

def modifyLDAPAdapter(adapterName, attribute, value, contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.modifyLDAPAdapter(adapterName, attribute, value, contextName)

def addLDAPHost(adapterName, host, port, contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.addLDAPHost(adapterName, host, port, contextName)

def removeLDAPHost(adapterName, host, contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.removeLDAPHost(adapterName, host, contextName)

def addJoinRule(adapterName, secondary, condition, joinerType='Simple', contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.addJoinRule(adapterName, secondary, condition, joinerType, contextName)

def removeJoinRule(adapterName, secondary, contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.removeJoinRule(adapterName, secondary, contextName)

def addPlugin(pluginName, pluginClass, paramKeys, paramValues, adapterName='GlobalPlugin', contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.addPlugin(pluginName, pluginClass, paramKeys, paramValues, adapterName, contextName)

def removePlugin(pluginName, adapterName='GlobalPlugin', contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.removePlugin(pluginName, adapterName, contextName)
  
def addPluginParam(pluginName, paramKeys, paramValues, adapterName='GlobalPlugin', contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.addPluginParam(pluginName, paramKeys, paramValues, adapterName, contextName)

def removePluginParam(pluginName, paramKey, adapterName='GlobalPlugin', contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.removePluginParam(pluginName, paramKey, adapterName, contextName)

def listAdapters(contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.listAdapters(contextName)

def getAdapterDetails(adapterName, contextName='default'):
  libOVD_gotoDomainRuntime()
  libovdhandler.getAdapterDetails(adapterName, contextName)

#internal commands

def addLibOVDCommandHelp():
  libovdhandler.addLibOVDCommandHelp();

def libOVD_gotoDomainRuntime():
  currentNode = pwd()
  if (currentNode.find('domainRuntime') == -1):
    ctree = currentTree()
    domainRuntime()
    ora_mbs.setMbs(mbs)
    return ctree
  else:
    return None

addLibOVDCommandHelp()
  
