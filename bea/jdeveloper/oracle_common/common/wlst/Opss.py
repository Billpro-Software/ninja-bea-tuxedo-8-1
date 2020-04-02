################################################################
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################

try:
    _oc = System.getProperty('COMMON_COMPONENTS_HOME')
    if _oc is not None:
        _sh = os.path.join(_oc, os.path.join('common', 'script_handlers'))
        if _sh not in sys.path:
            sys.path.append(_sh)
except:
    print "" #ignore the exception

import Opss_handler as handler
from java.util import HashMap
from oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
from oracle.security.jps import WlstResources
from java.util import ResourceBundle
from java.util import Locale
import ora_mbs



############################################
# This function creates Resource
############################################
def createResource(appStripe=None, name=None, type=None, displayName=None, description=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("type",type)
    m.put("displayName",displayName)
    m.put("description",description)
    wlstModule.domainRuntime()
    handler.createResourceImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

############################################
# This function prints the resource
############################################
def getResource(appStripe=None, name=None, type=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("type",type)
    wlstModule.domainRuntime()
    handler.getResourceImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

#############################################
# This function deletes the resource
#############################################
def deleteResource(appStripe=None, name=None, type=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("type",type)
    wlstModule.domainRuntime()
    handler.deleteResourceImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

#############################################
# This function lists the resources
#############################################
def listResources(appStripe=None, type=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("type",type)
    wlstModule.domainRuntime()
    handler.listResourcesImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

#############################################
# This function lists the resource actions
#############################################
def listResourceActions(appStripe=None, entitlementName=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("entitlementName",entitlementName)
    wlstModule.domainRuntime()
    handler.listResourceActionsImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

#############################################
# This function lists the resource types
#############################################
def listResourceTypes(appStripe=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    wlstModule.domainRuntime()
    handler.listResourceTypesImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

############################################
# This function creates Permission Set
############################################
def createEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None, displayName=None, description=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("resourceName",resourceName)
    m.put("resourceType",resourceType)
    m.put("actions",actions)
    m.put("displayName",displayName)
    m.put("description",description)
    wlstModule.domainRuntime()
    handler.createEntitlementImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

############################################
# This function prints the permission set
############################################
def getEntitlement(appStripe=None, name=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    wlstModule.domainRuntime()
    handler.getEntitlementImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

#############################################
# This function deletes the permission set
#############################################
def deleteEntitlement(appStripe=None, name=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    wlstModule.domainRuntime()
    handler.deleteEntitlementImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

####################################################
# This function adds a member to the permission set
####################################################
def addResourceToEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("resourceName",resourceName)
    m.put("resourceType",resourceType)
    m.put("actions",actions)
    wlstModule.domainRuntime()
    handler.addResourceToEntitlementImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

########################################################
# This function revokes a member from the permission set
########################################################
def revokeResourceFromEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("resourceName",resourceName)
    m.put("resourceType",resourceType)
    m.put("actions",actions)
    wlstModule.domainRuntime()
    handler.revokeResourceFromEntitlementImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

#############################################
# This function lists all permission sets
#############################################
def listEntitlements(appStripe=None, resourceTypeName=None, resourceName=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("resourceTypeName",resourceTypeName)
    m.put("resourceName",resourceName)
    wlstModule.domainRuntime()
    handler.listEntitlementsImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

######################################################
# This function grants a permission set to a principal
######################################################
def grantEntitlement(appStripe=None, principalName=None, principalClass=None, entitlementName=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("principalName",principalName)
    m.put("principalClass",principalClass)
    m.put("entitlementName",entitlementName)
    wlstModule.domainRuntime()
    handler.grantEntitlementImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

######################################################
# This function revokes a permission set from a principal
######################################################
def revokeEntitlement(appStripe=None, principalName=None, principalClass=None, entitlementName=None) :
    import wlstModule
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("principalName",principalName)
    m.put("principalClass",principalClass)
    m.put("entitlementName",entitlementName)
    wlstModule.domainRuntime()
    handler.revokeEntitlementImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

#############################################
# This function lists all the app stripes
#############################################
def listAppStripes(configFile=None, regularExpression=None):
    import wlstModule
    m = HashMap()
    m.put("configFile",configFile)
    m.put("regularExpression",regularExpression)
    if (configFile is None):
      wlstModule.domainRuntime()
      m.put("connected", "true")
    handler.listAppStripesImpl(m,JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)

