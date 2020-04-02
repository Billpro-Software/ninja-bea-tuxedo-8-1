################################################################
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################

from java.lang import Exception
from java.util import HashMap
from java.util import ResourceBundle
from java.util import Locale

from oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
from oracle.security.jps import WlstResources

import ora_util
import ora_mbs
import Opss_handler as handler


#######################################################
# This function adds command help
# (Internal function)
#######################################################

def addOpssCommandHelp() :
    try :
        handler.addOpssCommandHelp()
    except Exception, e :
        ora_util.raiseScriptingException(e)

opss_resourceBundle = ResourceBundle.getBundle("oracle.security.jps.WlstResources", Locale.getDefault(), WlstResources.getClassLoader())

#workaround for bug9697953, for the final approach, we filed bug 9704933
def getCompleteMBeanName(objname):
    if(ora_mbs.isJBoss()):
        on = objname
    elif(ora_mbs.isWebSphereND() == 1):
        on = AdminControl.completeObjectName(objname+',process=dmgr,*')
    elif(ora_mbs.isWebSphereAS() == 1):
        on = AdminControl.completeObjectName(objname+',*')
    else:
        on = objname
    return on

#######################################################
# This function list the credentials
#######################################################

def listCred(map=None, key=None) :
    m = HashMap()
    m.put("map", map)
    m.put("key", key)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_CREDENTIAL_STORE)
    try :
        handler.listCredImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

############################################
# This function creates Resource
############################################
def createResource(appStripe=None, name=None, type=None, displayName=None, description=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("type",type)
    m.put("displayName",displayName)
    m.put("description",description)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.createResourceImpl(m,on)

############################################
# This function prints the resource
############################################
def getResource(appStripe=None, name=None, type=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("type",type)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.getResourceImpl(m,on)

#############################################
# This function deletes the resource
#############################################
def deleteResource(appStripe=None, name=None, type=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("type",type)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.deleteResourceImpl(m,on)

#############################################
# This function lists the resources
#############################################
def listResources(appStripe=None, type=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("type",type)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.listResourcesImpl(m,on)

#############################################
# This function lists the resource actions
#############################################
def listResourceActions(appStripe=None, entitlementName=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("entitlementName",entitlementName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.listResourceActionsImpl(m,on)

#############################################
# This function lists the resource types
#############################################
def listResourceTypes(appStripe=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.listResourceTypesImpl(m,on)

############################################
# This function creates Permission Set
############################################
def createEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None, displayName=None, description=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("resourceName",resourceName)
    m.put("resourceType",resourceType)
    m.put("actions",actions)
    m.put("displayName",displayName)
    m.put("description",description)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.createEntitlementImpl(m,on)

############################################
# This function prints the permission set
############################################
def getEntitlement(appStripe=None, name=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    handler.getEntitlementImpl(m,on)

#############################################
# This function deletes the permission set
#############################################
def deleteEntitlement(appStripe=None, name=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE
)
    handler.deleteEntitlementImpl(m,on)

####################################################
# This function adds a member to the permission set
####################################################
def addResourceToEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("resourceName",resourceName)
    m.put("resourceType",resourceType)
    m.put("actions",actions)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE
)
    handler.addResourceToEntitlementImpl(m,on)

########################################################
# This function revokes a member from the permission set
########################################################
def revokeResourceFromEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("name",name)
    m.put("resourceName",resourceName)
    m.put("resourceType",resourceType)
    m.put("actions",actions)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE
)
    handler.revokeResourceFromEntitlementImpl(m,on)

#############################################
# This function lists all permission sets
#############################################
def listEntitlements(appStripe=None, resourceTypeName=None, resourceName=None, principalName=None, principalClass=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("resourceTypeName",resourceTypeName)
    m.put("resourceName",resourceName)
    m.put("principalName",principalName)
    m.put("principalClass",principalClass)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE
)
    handler.listEntitlementsImpl(m,on)

######################################################
# This function grants a permission set to a principal
######################################################
def grantEntitlement(appStripe=None, principalName=None, principalClass=None, entitlementName=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("principalName",principalName)
    m.put("principalClass",principalClass)
    m.put("entitlementName",entitlementName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE
)
    handler.grantEntitlementImpl(m,on)

######################################################
# This function revokes a permission set from a principal
######################################################
def revokeEntitlement(appStripe=None, principalName=None, principalClass=None, entitlementName=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("principalName",principalName)
    m.put("principalClass",principalClass)
    m.put("entitlementName",entitlementName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE
)
    handler.revokeEntitlementImpl(m,on)

#######################################################
# This function creates ResourceType
#######################################################
def createResourceType(appStripe=None, resourceTypeName=None, displayName=None, description=None, provider=None, matcher=None, allowedActions=None, delimiter=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("resourceTypeName",resourceTypeName)
    m.put("displayName",displayName)
    m.put("description",description)
    m.put("provider",provider)
    m.put("matcher",matcher)
    m.put("allowedActions",allowedActions)
    m.put("delimiter",delimiter)    
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :    
        handler.createResourceTypeImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function prints ResourceType
#######################################################
def getResourceType(appStripe=None, resourceTypeName=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("resourceTypeName",resourceTypeName)    
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.getResourceTypeImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function deletes ResourceType
#######################################################
def deleteResourceType(appStripe=None, resourceTypeName=None) :
    m = HashMap()
    m.put("appStripe",appStripe)
    m.put("resourceTypeName",resourceTypeName)    
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try : 
        handler.deleteResourceTypeImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#############################################
# This function lists all the app stripes
#############################################
def listAppStripes(configFile=None, regularExpression=None):
    m = HashMap()
    m.put("configFile",configFile)
    m.put("regularExpression",regularExpression)
    on = None
    # If a configFile is provided, use that, otherwise connect to the server.
    if (configFile is None):
      m.put("connected", "true")
      on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
      handler.listAppStripesImpl(m,on)
    except Exception, e :
      ora_util.raiseScriptingException(e)

#######################################################
# This function list the approles
#######################################################

def listAppRoles(appStripe=None) :   
    m = HashMap()
    m.put("appStripe", appStripe)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.listAppRolesImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function list the approle members
#######################################################

def listAppRoleMembers(appStripe=None, appRoleName=None) :   
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("appRoleName", appRoleName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.listAppRoleMembersImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)


#######################################################
# This function list the permissions
#######################################################

def listPermissions(appStripe=None, principalClass=None, principalName=None) :    
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("principalClass", principalClass)
    m.put("principalName", principalName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_GLOBAL_POLICY_STORE)
    obn = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.listPermissionsImpl(m,on,obn)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function creates an approle
#######################################################

def createAppRole(appStripe=None, appRoleName=None) :   
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("appRoleName", appRoleName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.createAppRoleImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function creates a credential
#######################################################

def createCred(map=None, key=None, user=None, password=None, desc=None) :   
    m = HashMap()
    m.put("map", map)
    m.put("key", key)
    m.put("user", user)
    m.put("password", password)
    m.put("desc", desc)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_CREDENTIAL_STORE)
    try :
        handler.createCredImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function deletes an app policy
#######################################################

def deleteAppPolicies(appStripe=None) :  
    m = HashMap()
    m.put("appStripe", appStripe)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.deleteAppPoliciesImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function deletes an approle
#######################################################

def deleteAppRole(appStripe=None, appRoleName=None) :    
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("appRoleName", appRoleName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.deleteAppRolesImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function deletes a credential
#######################################################

def deleteCred(map=None, key=None) :    
    m = HashMap()
    m.put("map", map)
    m.put("key", key)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_CREDENTIAL_STORE)
    try :
        handler.deleteCredImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function grants an approle
#######################################################

def grantAppRole(appStripe=None, appRoleName=None, principalClass=None, principalName=None) :   
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("appRoleName", appRoleName)
    m.put("principalClass", principalClass)
    m.put("principalName", principalName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.grantAppRoleImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function grants a permission
#######################################################

def grantPermission(appStripe=None, principalClass=None, principalName=None, codeBaseURL=None, permClass=None, permTarget=None, permActions=None) :    
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("principalClass", principalClass)
    m.put("principalName", principalName)
    m.put("codeBaseURL", codeBaseURL)
    m.put("permClass", permClass)
    m.put("permTarget", permTarget)
    m.put("permActions", permActions)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_GLOBAL_POLICY_STORE)
    obn = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.grantPermissionImpl(m,on,obn)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function revokes an approle
#######################################################

def revokeAppRole(appStripe=None, appRoleName=None, principalClass=None, principalName=None) :    
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("appRoleName", appRoleName)
    m.put("principalClass", principalClass)
    m.put("principalName", principalName)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.revokeAppRoleImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

#######################################################
# This function revokes a permission
#######################################################

def revokePermission(appStripe=None, principalClass=None, principalName=None, codeBaseURL=None, permClass=None, permTarget=None, permActions=None ) :   
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("principalClass", principalClass)
    m.put("principalName", principalName)
    m.put("permClass", permClass)
    m.put("permTarget", permTarget)
    m.put("permActions", permActions)
    m.put("codeBaseURL", codeBaseURL)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_GLOBAL_POLICY_STORE)
    obn = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_APPLICATION_POLICY_STORE)
    try :
        handler.revokePermissionImpl(m,on,obn)
    except Exception, e :
        ora_util.raiseScriptingException(e) 

#######################################################
# This function updates a credential
#######################################################

def updateCred(map=None, key=None, user=None, password=None, desc=None) :    
    m = HashMap()
    m.put("map", map)
    m.put("key", key)
    m.put("user", user)
    m.put("password", password)
    m.put("desc", desc)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_CREDENTIAL_STORE)
    try :
        handler.updateCredImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# This function migrates the policies istore/global/apppolicy/policystore
###########################################################################

def migrateSecurityStore(type=None, src=None, dst=None, srcApp=None, dstApp=None, srcFolder=None, dstFolder=None, dstLdifFile=None, srcConfigFile=None, configFile=None, overWrite=None, processPrivRole=None, resourceTypeFile=None, migrateIdStoreMapping=None, preserveAppRoleGuid=None, mode=None, reportFile=None) :   
    m = HashMap()
    m.put("type", type)
    m.put("src", src)
    m.put("dst", dst)
    m.put("srcApp", srcApp)
    m.put("dstApp", dstApp)
    m.put("srcFolder", srcFolder)
    m.put("dstFolder", dstFolder)
    m.put("dstLdifFile", dstLdifFile)
    m.put("srcConfigFile", srcConfigFile)
    m.put("configFile", configFile)
    m.put("processPrivRole", processPrivRole)
    m.put("resourceTypeFile", resourceTypeFile)
    m.put("overWrite", overWrite)     
    m.put("migrateIdStoreMapping", migrateIdStoreMapping)
    m.put("preserveAppRoleGuids", preserveAppRoleGuid)
    m.put("mode",mode)
    m.put("reportFile", reportFile)
    try :
        handler.migrateSecurityStoreImpl(m)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# This function upgraded the policies 
###########################################################################

def upgradeSecurityStore(type=None, srcRealm=None, dst=None, srcJaznConfigFile=None, srcJaznDataFile=None, jpsConfigFile=None, users=None, dstJaznDataFile=None, resourceTypeFile=None, srcApp=None, jpsContext=None) :   
    m = HashMap()
    m.put("type", type)
    m.put("srcRealm", srcRealm)
    m.put("dst", dst)
    m.put("srcJaznConfigFile", srcJaznConfigFile)
    m.put("srcJaznDataFile", srcJaznDataFile)
    m.put("jpsConfigFile", jpsConfigFile)
    m.put("users", users)
    m.put("dstJaznDataFile", dstJaznDataFile)
    m.put("resourceTypeFile", resourceTypeFile)
    m.put("srcApp", srcApp)
    m.put("jpsContext", jpsContext)
    try :
        handler.upgradeSecurityStoreImpl(m)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# This function reassociates
###########################################################################

def reassociateSecurityStore(domain=None, admin=None, password=None,ldapurl=None,servertype=None,jpsroot=None,join=None, datasourcename=None) :    
    m = HashMap()
    m.put("domain", domain)
    m.put("admin", admin)
    m.put("password", password)
    m.put("ldapurl", ldapurl)
    m.put("servertype", servertype)
    m.put("jpsroot", jpsroot)
    m.put("join", join)
    m.put("datasourcename", datasourcename)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_CONFIG_FUNCTIONAL)
    try :
        handler.reassociateSecurityStoreImpl(m,on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# This function modifies the boot strap credential
###########################################################################

def modifyBootStrapCredential(jpsConfigFile=None,username=None, password=None) :   
    m = HashMap()   
    m.put("jpsConfigFile", jpsConfigFile)
    m.put("username", username)
    m.put("password", password)
    try :
        handler.modifyBootStrapCredentialImpl(m)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# This function adds the boot strap credential
###########################################################################

def addBootStrapCredential(jpsConfigFile=None, map=None, key=None, username=None, password=None) :
    m = HashMap()
    m.put("jpsConfigFile", jpsConfigFile)
    m.put("map", map)
    m.put("key", key)
    m.put("username", username)
    m.put("password", password)
    try :
        handler.addBootStrapCredentialImpl(m)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# This function modifies the boot strap credential
###########################################################################

def patchPolicyStore(phase=None, patchDeltaFolder=None, productionJpsConfig=None, baselineFile=None, patchFile=None, baselineAppStripe=None, productionAppStripe=None, patchAppStripe=None, silent=None) :
    
    from oracle.security.jps.patch import PatchTool
    from oracle.security.jps.patch import PatchingException 
    m = HashMap()
    m.put(PatchTool.phase, phase)
    m.put(PatchTool.baselineFile, baselineFile)
    m.put(PatchTool.patchFile,patchFile)
    m.put(PatchTool.productionJpsConfig,productionJpsConfig)
    m.put(PatchTool.patchDeltaFolder,patchDeltaFolder)
    m.put(PatchTool.baselineAppStripe,baselineAppStripe)
    m.put(PatchTool.productionAppStripe,productionAppStripe)
    m.put(PatchTool.newlineAppStripe,patchAppStripe)
    m.put(PatchTool.silent,silent)
    try :
        handler.patchPolicyStoreImpl(m)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# This function configures identity store in default jps context
###########################################################################

def configIdStoreInternal(props=None) :
    import jarray
    from java.lang import Object
    from java.lang import String
    from java.util import ArrayList
    from oracle.security.jps.mas.mgmt.jmx.config import PortableMap
    from oracle.security.jps.mas.mgmt.jmx.config import JpsConfigMBeanConstants
    
    args= ArrayList()

    ldapHost = props.remove(JpsConfigMBeanConstants.LDAP_HOST)    
    if (ldapHost is None) :
        args.add(JpsConfigMBeanConstants.LDAP_HOST)

    ldapPort = props.remove(JpsConfigMBeanConstants.LDAP_PORT)    
    if (ldapPort is None) :
        args.add(JpsConfigMBeanConstants.LDAP_PORT) 

    groupSearchBaseStr = props.remove(JpsConfigMBeanConstants.GROUP_SEARCH_BASES)
    if (groupSearchBaseStr is None) :
        args.add(JpsConfigMBeanConstants.GROUP_SEARCH_BASES)

    userSearchBaseStr = props.remove(JpsConfigMBeanConstants.USER_SEARCH_BASES)
    if (userSearchBaseStr is None) :
        args.add(JpsConfigMBeanConstants.USER_SEARCH_BASES)

    adminId = props.remove(JpsConfigMBeanConstants.ADMIN_ID)
    if (adminId is None) :
        args.add(JpsConfigMBeanConstants.ADMIN_ID)

    pwd = props.remove(JpsConfigMBeanConstants.ADMIN_PASS)
    if (pwd is None) :
        args.add(JpsConfigMBeanConstants.ADMIN_PASS)
  
    subscriberName = props.remove(JpsConfigMBeanConstants.SUBSCRIBER_NAME)

    ldapType = props.remove(JpsConfigMBeanConstants.LDAP_IDSTORE_TYPE)
    if (ldapType is None) :
        args.add(JpsConfigMBeanConstants.LDAP_IDSTORE_TYPE)

    argsarr=None
    for i in range(len(args)) :
        if(argsarr is None ) :
            argsarr = args[i]
        else :
            argsarr = argsarr + "," + args[i]

    if (len(args) > 0 ) :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_REQUIRED_ARG_MISSING)
        raise Exception, msg+str(argsarr)

    groupSearchBase = jarray.array([groupSearchBaseStr], String)
    arrPassword = jarray.array(pwd,'c')
    userSearchBase =  jarray.array ([userSearchBaseStr], String)

    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_CONFIG_FUNCTIONAL)
    # remove 'ssl' from props as we don't want it to be in the ldap id store attributes.
    ssl = props.remove(JpsConfigMBeanConstants.SSL_LDAP)
    protocol = 'ldap://'
    if (ssl is not None and ssl.lower() == "true") :
        protocol = 'ldaps://'

    ldapUrl = str(protocol)+str(ldapHost)+':'+str(ldapPort)

    print 'ldapUrl: ' + str(ldapUrl)
    print 'adminId: ' + str(adminId)
    #Default dont check for ldap service instance. Only if the flag is set and the value is true do the check   
    checkLdapInst = props.remove(JpsConfigMBeanConstants.CHECK_LDAP_INSTANCE) 
    if (checkLdapInst is None ) :
      checkLdapInst = "false"

    mp = PortableMap(props).toCompositeData(None)
    try :
        handler.configureIdentityStoreImpl(on,ldapUrl,adminId,arrPassword,ldapType,subscriberName,userSearchBase,groupSearchBase,mp,checkLdapInst)
    except Exception, e :
        ora_util.raiseScriptingException(e)



def configureIdentityStore(propsFileLoc=None) :
    from java.util import Properties
    from java.io import File
    from java.io import FileInputStream

    if (propsFileLoc is None) :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_EMPTY_PROP_FILE)
        print msg 
        raise Exception, msg 
        
    props = Properties()
    props.load(FileInputStream(File(propsFileLoc)))
    configIdStoreInternal(props)

###########################################################################
# this function lists all keystores
###########################################################################

def listKeyStores(appStripe=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.listKeyStoresImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# this function creates a keystore 
###########################################################################

def createKeyStore(appStripe=None, name=None, password=None, permission=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("permission", permission)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.createKeyStoreImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
# this function deletes a keystore 
###########################################################################

def deleteKeyStore(appStripe=None, name=None, password=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.deleteKeyStoreImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function changes keystore password
###########################################################################

def changeKeyStorePassword(appStripe=None, name=None, currentpassword=None, newpassword=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("currentpassword", currentpassword)
    m.put("newpassword", newpassword)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.changeKeyStorePasswordImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function generates a key pair
###########################################################################

def generateKeyPair(appStripe=None, name=None, password=None, dn=None, keysize=None, alias=None, keypassword=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("dn", dn)
    m.put("keysize", keysize)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.generateKeyPairImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function generates a secret key
###########################################################################

def generateSecretKey(appStripe=None, name=None, password=None, algorithm=None, keysize=None, alias=None, keypassword=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("algorithm", algorithm)
    m.put("keysize", keysize)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.generateSecretKeyImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function lists keystore aliases 
###########################################################################

def listKeyStoreAliases(appStripe=None, name=None, password=None, type=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("type", type)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.listKeyStoreAliasesImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function changes keystore key password 
###########################################################################

def changeKeyStoreKeyPassword(appStripe=None, name=None, password=None, alias=None, currentkeypassword=None, newkeypassword=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("alias", alias)
    m.put("currentkeypassword", currentkeypassword)
    m.put("newkeypassword", newkeypassword)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.changeKeyStoreKeyPasswordImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function gets a keystore certificate 
###########################################################################

def getKeyStoreCertificates(appStripe=None, name=None, password=None, alias=None, keypassword=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.getKeyStoreCertificatesImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function gets keystore secret key properties 
###########################################################################

def getKeyStoreSecretKeyProperties(appStripe=None, name=None, password=None, alias=None, keypassword=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.getKeyStoreSecretKeyPropertiesImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function generates and exports a certificate request 
###########################################################################

def exportKeyStoreCertificateRequest(appStripe=None, name=None, password=None,alias=None, keypassword=None, filepath=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    m.put("filepath", filepath)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.exportKeyStoreCertificateRequestImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function exports a BASE64 encoded certificate, trusted certificate 
###########################################################################

def exportKeyStoreCertificate(appStripe=None, name=None, password=None,alias=None, keypassword=None, type=None, filepath=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    m.put("type", type)
    m.put("filepath", filepath)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.exportKeyStoreCertificateImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function imports a BASE64 encoded certificate, trusted certificate 
###########################################################################

def importKeyStoreCertificate(appStripe=None, name=None, password=None,alias=None, keypassword=None, type=None, filepath=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    m.put("type", type)
    m.put("filepath", filepath)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.importKeyStoreCertificateImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function imports a BASE64 encoded certificate, trusted certificate 
###########################################################################

def deleteKeyStoreEntry(appStripe=None, name=None, password=None,alias=None, keypassword=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("alias", alias)
    m.put("keypassword", keypassword)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.deleteKeyStoreEntryImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function lists all expiring certificates and optionally renews them 
###########################################################################

def listExpiringCertificates(days=None, autorenew=None) :
    m = HashMap()
    m.put("days", days)
    m.put("autorenew", autorenew)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.listExpiringCertificatesImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function exports the keystore into file 
###########################################################################

def exportKeyStore(appStripe=None, name=None, password=None,aliases=None, keypasswords=None, type=None, filepath=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("aliases", aliases)
    m.put("keypasswords", keypasswords)
    m.put("type", type)
    m.put("filepath", filepath)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.exportKeyStoreImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################
#  this function imports a keystore from file 
###########################################################################

def importKeyStore(appStripe=None, name=None, password=None,aliases=None, keypasswords=None, type=None, permission=None, filepath=None) :
    m = HashMap()
    m.put("appStripe", appStripe)
    m.put("name", name)
    m.put("password", password)
    m.put("aliases", aliases)
    m.put("keypasswords", keypasswords)
    m.put("type", type)
    m.put("permission", permission)
    m.put("filepath", filepath)
    on = getCompleteMBeanName(JpsJmxConstants.MBEAN_JPS_KEY_STORE)
    try :
        handler.importKeyStoreImpl(m, on)
    except Exception, e :
        ora_util.raiseScriptingException(e)

###########################################################################

