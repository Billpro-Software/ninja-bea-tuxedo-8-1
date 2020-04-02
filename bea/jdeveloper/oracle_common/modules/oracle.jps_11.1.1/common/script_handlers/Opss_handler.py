################################################################
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################
from java.util import ResourceBundle
from java.util import Locale
from java.util import ArrayList
from java.util import Set
from java.lang import String 
import ora_mbs
import ora_help
from oracle.security.jps import WlstResources
from oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
from oracle.security.jps import JpsException
from javax.management import MBeanException

#######################################################
# This function adds command help
# (Internal function)
#######################################################
 
def addOpssCommandHelp():  
 try:
   ora_help.addHelpCommandGroup("opss","jpsWLSTResourceBundle")
   ora_help.addHelpCommand("listCred","opss", offline="false", online="true")
   ora_help.addHelpCommand("createCred","opss", offline="false", online='true')
   ora_help.addHelpCommand("updateCred","opss", offline="false", online="true")
   ora_help.addHelpCommand("deleteCred","opss", offline="false", online="true")
   ora_help.addHelpCommand("listAppRoles","opss", offline="false", online="true")
   ora_help.addHelpCommand("createResourceType","opss", offline="false", online="true")
   ora_help.addHelpCommand("getResourceType","opss", offline="false", online="true")
   ora_help.addHelpCommand("deleteResourceType","opss", offline="false", online="true")
   ora_help.addHelpCommand("createAppRole","opss", offline="false", online="true")
   ora_help.addHelpCommand("deleteAppRole","opss", offline="false", online="true")
   ora_help.addHelpCommand("listAppRoleMembers","opss", offline="false", online="true")
   ora_help.addHelpCommand("grantAppRole","opss",offline="false", online="true")
   ora_help.addHelpCommand("revokeAppRole","opss", offline="false", online="true")
   ora_help.addHelpCommand("listPermissions","opss",offline="false", online="true")
   ora_help.addHelpCommand("grantPermission","opss",offline="false", online="true")
   ora_help.addHelpCommand("revokePermission","opss",offline="false", online="true")
   ora_help.addHelpCommand("deleteAppPolicies","opss",offline="false", online="true")
   ora_help.addHelpCommand("migrateSecurityStore","opss", offline="true", online="false")
   ora_help.addHelpCommand("reassociateSecurityStore","opss",offline="false", online="true")
   ora_help.addHelpCommand("upgradeSecurityStore", "opss", offline="true", online="false")
   ora_help.addHelpCommand("modifyBootStrapCredential", "opss", offline="true", online="false")   
   ora_help.addHelpCommand("patchPolicyStore", "opss", offline="true", online="false")
   ora_help.addHelpCommand("listKeyStores", "opss", offline="false", online="true")
   ora_help.addHelpCommand("createKeyStore", "opss", offline="false", online="true")
   ora_help.addHelpCommand("deleteKeyStore", "opss", offline="false", online="true")
   ora_help.addHelpCommand("changeKeyStorePassword", "opss", offline="false", online="true")
   ora_help.addHelpCommand("generateKeyPair", "opss", offline="false", online="true")
   ora_help.addHelpCommand("generateSecretKey", "opss", offline="false", online="true")
   ora_help.addHelpCommand("listKeyStoreAliases", "opss", offline="false", online="true")
   ora_help.addHelpCommand("changeKeyStoreKeyPassword", "opss", offline="false", online="true")
   ora_help.addHelpCommand("getKeyStoreCertificates", "opss", offline="false", online="true")
   ora_help.addHelpCommand("getKeyStoreSecretKeyProperties", "opss", offline="false", online="true")
   ora_help.addHelpCommand("exportKeyStoreCertificateRequest", "opss", offline="false", online="true")
   ora_help.addHelpCommand("exportKeyStoreCertificate", "opss", offline="false", online="true")
   ora_help.addHelpCommand("importKeyStoreCertificate", "opss", offline="false", online="true")
   ora_help.addHelpCommand("deleteKeyStoreEntry", "opss", offline="false", online="true")
   ora_help.addHelpCommand("listExpiringCertificates", "opss", offline="false", online="true")
   ora_help.addHelpCommand("exportKeyStore", "opss", offline="false", online="true")
   ora_help.addHelpCommand("importKeyStore", "opss", offline="false", online="true")
 except Exception, e:
    return
   

opss_resourceBundle = ResourceBundle.getBundle("oracle.security.jps.WlstResources", Locale.getDefault(), WlstResources.getClassLoader())



#######################################################
# Helper methods 
#######################################################

def validateRequiredArgs(args, reqArgs) :
    for i in range(len(reqArgs)) :
        if (args.get(reqArgs[i]) is None ) :
            msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_REQUIRED_ARG_MISSING)
            print msg + reqArgs[i]
            raise Exception, msg + reqArgs[i]

def validateConflictingArgs(args, arg1, arg2) :
    if (args.get(arg1) is not None and args.get(arg2) is not None) :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_CONFLICTING_ARG)
        print msg + arg1 + ", " + arg2
        raise Exception, msg + arg1 + ", " + arg2

def validateGroupArgs(args, grp) :
    found = 0
    for i in range(len(grp)) :
        if (args.get(grp[i])) :
            found = found + 1
    if (found != 0 and found != len(grp)) :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_GROUP_ARG_MISSING)
        print msg + grp.toString()
        raise Exception, msg + grp.toString()

def validateBooleanValue(arg, value) :
     if  not (value.lower() == "true" or value.lower() == "false") :
         print  arg + " " + opss_resourceBundle.getString(WlstResources.MSG_WLST_BOOLEAN_ARG)
         raise Exception, arg + " " +  opss_resourceBundle.getString(WlstResources.MSG_WLST_BOOLEAN_ARG)

def createCredObj(user, password, desc) :
    from oracle.security.jps.mas.mgmt.jmx.credstore import PortablePasswordCredential
    #Create Password Credential object
    pc = PortablePasswordCredential(user, password, desc)
    return pc

def opss_getPrincipalType(className):
        from  oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType
        princType = None
        if (className == "oracle.security.jps.service.policystore.ApplicationRole"):
            princType = PrincipalType.APP_ROLE
        elif (className == "weblogic.security.principal.WLSUserImpl"):
                princType = PrincipalType.ENT_USER
        elif (className == "weblogic.security.principal.WLSGroupImpl"):
                princType = PrincipalType.ENT_ROLE
        else:
            princType = PrincipalType.CUSTOM
        return princType 



#######################################################
# LIST METHODS
#######################################################

#######################################################
# listCredImpl API
#######################################################

def listCredImpl(m,on) :
    from oracle.security.jps.mas.mgmt.jmx.credstore import PortableCredential         
    reqArgs = ArrayList()
    reqArgs.add("map")
    reqArgs.add("key")
    validateRequiredArgs(m, reqArgs)
    cred = None
    try:
        
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("map"), m.get("key")]
        sign = ["java.lang.String", "java.lang.String"]
        cred =  ora_mbs.invoke(objectName, "getPortableCredential", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg +  e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if cred != None:
        credObject = PortableCredential.from(cred)
        print credObject
        print "PASSWORD:" + String.valueOf(credObject.getPassword())
    else:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_CRED_NOT_FOUND)
        print msg


#######################################################
# listAppRoles API
#######################################################

def listAppRolesImpl(m,on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableApplicationRole   
   
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    validateRequiredArgs(m, reqArgs)

    try:
        
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe")]
        sign = ["java.lang.String"]
        appRoles = ora_mbs.invoke(objectName, "getAllApplicationRoles", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg +  e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if appRoles != None:
        for r in appRoles:
            print PortableApplicationRole.from(r)
    else:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_APP_NOT_FOUND)
        print msg + m.get("appStripe")

# function end

#######################################################
# listAppRoleMembers API
#######################################################

def listAppRoleMembersImpl(m,on) :

    from oracle.security.jps.mas.mgmt.jmx.policy import PortableApplicationRole
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableRoleMember
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("appRoleName")
    validateRequiredArgs(m, reqArgs)

    members = None

    try :
       
        objectName = ora_mbs.makeObjectName(on)
        pAr = PortableApplicationRole(m.get("appRoleName"), "", "", "", "")

        params = [m.get("appStripe"), pAr.toCompositeData(None)]
        sign = ["java.lang.String", "javax.management.openmbean.CompositeData"]
        members = ora_mbs.invoke(objectName, "getMembersForApplicationRole", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if members != None:
        for m in members:
            print PortableRoleMember.from(m)
    else:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_APP_NOT_FOUND)
        print msg + m.get("appStripe")


#######################################################
# listPermissions API
#######################################################

def listPermissionsImpl(m,on_global,on_app) :

    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePrincipal
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePermission
    from oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType
    
    reqArgs = ArrayList()
    reqArgs.add("principalClass")
    reqArgs.add("principalName")
    validateRequiredArgs(m, reqArgs)

    try :
       
        p = PortablePrincipal(m.get("principalClass"), m.get("principalName"), PrincipalType.CUSTOM)
        if m.get("appStripe") is None:
            objectName = ora_mbs.makeObjectName(on_global)
            params = [p.toCompositeData(None)]
            sign = ["javax.management.openmbean.CompositeData"]
            perms =  ora_mbs.invoke(objectName, "getPermissions", params, sign)
        else:
            objectName = ora_mbs.makeObjectName(on_app)
            params = [m.get("appStripe"), p.toCompositeData(None)]
            sign = ["java.lang.String", "javax.management.openmbean.CompositeData"]
            perms = ora_mbs.invoke(objectName, "getPermissions", params, sign)
        for p in perms:
            print PortablePermission.from(p)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

## resource start here
def createResourceImpl(m, on) :
    from java.lang import String
    from java.util import ArrayList
    import jarray

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("type")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"
    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name"), m.get("type"), m.get("displayName"), m.get("description")]
        sign = [STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME]
        ora_mbs.invoke(objectName, "createResource", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def getResourceImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableResource
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("type")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name"), m.get("type")]
        sign = [STR_NAME, STR_NAME, STR_NAME ]
        resource = ora_mbs.invoke(objectName, "getResource", params, sign)
        print PortableResource.from(resource)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def deleteResourceImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableResource
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("type")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name"), m.get("type")]
        sign = [STR_NAME, STR_NAME, STR_NAME ]
        ora_mbs.invoke(objectName, "deleteResource", params, sign)

    except MBeanException, e:
	msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def listResourcesImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableResource
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"),  m.get("type")]
        sign = [STR_NAME, STR_NAME]
        resources = ora_mbs.invoke(objectName, "listResources", params, sign)
        for resource in resources:
            print PortableResource.from(resource)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
 	msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def listResourceActionsImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableResourceActions
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("entitlementName")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"),  m.get("entitlementName")]
        sign = [STR_NAME, STR_NAME]
        resourceActions = ora_mbs.invoke(objectName, "listResourceActions", params, sign)
        for resourceAction in resourceActions:
            print PortableResourceActions.from(resourceAction)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
    	msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise
## resource end here

## permission set start here

def createEntitlementImpl(m, on) :
    from java.lang import String
    from java.util import ArrayList
    import jarray

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("resourceName")
    reqArgs.add("resourceType")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"
    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name"), m.get("displayName"), m.get("description"), m.get("resourceName"), m.get("resourceType"), m.get("actions")]
        sign = [STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME]
        ora_mbs.invoke(objectName, "createEntitlement", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


def getEntitlementImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePermissionSet
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name")]
        sign = [STR_NAME, STR_NAME]
        permissionset = ora_mbs.invoke(objectName, "getEntitlement", params, sign)
        print PortablePermissionSet.from(permissionset)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def deleteEntitlementImpl(m, on) :
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name")]
        sign = [STR_NAME, STR_NAME]
        ora_mbs.invoke(objectName, "deleteEntitlement", params, sign)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


def addResourceToEntitlementImpl(m, on) :
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("resourceName")
    reqArgs.add("resourceType")
    reqArgs.add("actions")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name"), m.get("resourceName"), m.get("resourceType"), m.get("actions")]
        sign = [STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME ]
        ora_mbs.invoke(objectName, "addResourceToEntitlement", params, sign)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def revokeResourceFromEntitlementImpl(m, on) :
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("resourceName")
    reqArgs.add("resourceType")
    reqArgs.add("actions")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("name"), m.get("resourceName"), m.get("resourceType"), m.get("actions")]
        sign = [STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME ]
        ora_mbs.invoke(objectName, "revokeResourceFromEntitlement", params, sign)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def listEntitlementsImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePermissionSet
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    validateRequiredArgs(m, reqArgs)

    grpArgs = ArrayList()
    grpArgs.add("resourceTypeName")
    grpArgs.add("resourceName") 
    validateGroupArgs(m, grpArgs)

    STR_NAME = "java.lang.String"

    try :
        pPl = None
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("resourceTypeName"), m.get("resourceName")]
        sign = [STR_NAME, STR_NAME, STR_NAME]
        permissions = ora_mbs.invoke(objectName, "listEntitlements", params, sign)
        for permission in permissions:
            print PortablePermissionSet.from(permission)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def grantEntitlementImpl(m, on) :
    from javax.management.openmbean import CompositeData
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePrincipal
    from oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("principalName")
    reqArgs.add("principalClass")
    reqArgs.add("entitlementName")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        pPl = None
        princType = opss_getPrincipalType(m.get("principalClass"))
        pPl = PortablePrincipal(m.get("principalClass"), m.get("principalName"), princType)
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("entitlementName"),pPl.toCompositeData(None)]
        sign = [STR_NAME, STR_NAME, "javax.management.openmbean.CompositeData"]
        ora_mbs.invoke(objectName, "grantEntitlement", params, sign)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def revokeEntitlementImpl(m, on) :
    from javax.management.openmbean import CompositeData
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePrincipal
    from oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("principalName")
    reqArgs.add("principalClass")
    reqArgs.add("entitlementName")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        pPl = None
        princType = opss_getPrincipalType(m.get("principalClass"))
        pPl = PortablePrincipal(m.get("principalClass"), m.get("principalName"), princType)
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("entitlementName"),pPl.toCompositeData(None)]
        sign = [STR_NAME, STR_NAME, "javax.management.openmbean.CompositeData"]
        ora_mbs.invoke(objectName, "revokeEntitlement", params, sign)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise
## permission set end here

## resourcetype start here

def createResourceTypeImpl(m, on) :
    from java.lang import String
    from java.util import ArrayList
    import jarray

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("resourceTypeName")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"
    STRING_ARRAY_NAME = "[Ljava.lang.String;"
    
    provider = m.get("provider")
    matcher = m.get("matcher")
    delimiter = m.get("delimiter")

    if matcher is None :
       matcher = "oracle.security.jps.ResourcePermission"
    if delimiter is None :
       delimiter = ","

    try :
        objectName = ora_mbs.makeObjectName(on)
        actionsArray = None
        actionsString = m.get("allowedActions")
        if actionsString is not None :
         actionsArray = jarray.array (actionsString.split(','), String)
        params = [m.get("appStripe"), m.get("resourceTypeName"), m.get("displayName"), m.get("description"), provider, matcher, actionsArray, delimiter ]
        sign = [STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME, STR_NAME, STRING_ARRAY_NAME, STR_NAME ]
        ora_mbs.invoke(objectName, "createResourceType", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def getResourceTypeImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableResourceType
    from java.util import ArrayList
    
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("resourceTypeName")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("resourceTypeName")]
        sign = [STR_NAME, STR_NAME ]
        resourceType = ora_mbs.invoke(objectName, "getResourceType", params, sign)
        print PortableResourceType.from(resourceType)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def deleteResourceTypeImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableResourceType
    from java.util import ArrayList
    
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("resourceTypeName")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("resourceTypeName")]
        sign = [STR_NAME, STR_NAME ]
        ora_mbs.invoke(objectName, "deleteResourceType", params, sign)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

def listResourceTypesImpl(m, on) :
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableResourceType
    from java.util import ArrayList

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    validateRequiredArgs(m, reqArgs)
    STR_NAME = "java.lang.String"

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe")]
        sign = [STR_NAME]
        resourceTypes = ora_mbs.invoke(objectName, "listResourceTypes", params, sign)
        for resourceType in resourceTypes:
            print PortableResourceType.from(resourceType)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise
## resource type commands end here

###################################
# listAppStripesImpl API
###################################
def listAppStripesImpl(m, on):
    from oracle.security.jps.tools.utility import JpsWLSTUtil
    from oracle.security.jps import JpsException
    STR_NAME = "java.lang.String"
    try :
         connected = m.get("connected")
         if (connected == "true"):
           objectName = ora_mbs.makeObjectName(on)
           params = [m.get("regularExpression")]
           sign = [STR_NAME]
           appStripes = ora_mbs.invoke(objectName, "listAppStripes", params, sign)
         else:
           reqArgs = ArrayList()
           reqArgs.add("configFile")
           validateRequiredArgs(m, reqArgs)
           appStripes = JpsWLSTUtil.listAppStripesImpl(m)
         for appStripe in appStripes:
             print appStripe
    except JpsException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise



#######################################################
# createAppRoleImpl API
#######################################################

def createAppRoleImpl(m,on) :
    
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("appRoleName")
    validateRequiredArgs(m, reqArgs)

    try :        
        objectName = ora_mbs.makeObjectName(on)

        params = [m.get("appStripe"), m.get("appRoleName"), None, None, None]

        sign = ["java.lang.String", "java.lang.String", "java.lang.String", "java.lang.String", "java.lang.String"]
        ora_mbs.invoke(objectName, "createApplicationRole", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise



#######################################################
# createCredImpl API
#######################################################

def createCredImpl(m,on) :
    
    map = m.get("map")
    key = m.get("key")
    user = m.get("user")
    password = m.get("password")
    desc = m.get("desc")

    reqArgs = ArrayList()
    reqArgs.add("map")
    reqArgs.add("key")
    reqArgs.add("user")
    reqArgs.add("password")
    validateRequiredArgs(m, reqArgs)

    try :
        pc = createCredObj(user, password, desc)
        objectName = ora_mbs.makeObjectName(on)

        cd = pc.toCompositeData(None);
        params = [map, key, cd]
        sign = ["java.lang.String", "java.lang.String", "javax.management.openmbean.CompositeData"]
        
        ora_mbs.invoke(objectName, "setPortableCredential", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise



#######################################################
# deleteAppPoliciesImpl API
#######################################################

def deleteAppPoliciesImpl(m,on) :
    
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    validateRequiredArgs(m, reqArgs)

    try :        
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe")]
        sign = ["java.lang.String"]
        ora_mbs.invoke(objectName, "deleteApplicationPolicy", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

#######################################################
# deleteAppRolesImpl API
#######################################################

def deleteAppRolesImpl(m,on) :
   
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("appRoleName")
    validateRequiredArgs(m, reqArgs)

    try :
       
        objectName = ora_mbs.makeObjectName(on)
        params = [m.get("appStripe"), m.get("appRoleName")]

        sign = ["java.lang.String", "java.lang.String"]
        ora_mbs.invoke(objectName, "removeApplicationRole", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

#######################################################
# deleteCredImpl API
#######################################################

def deleteCredImpl(m,on) :
    
    map = m.get("map")
    key = m.get("key")
    # Check if the required arguments were passed.
    reqArgs = ArrayList()
    reqArgs.add("map")
    reqArgs.add("key")
    validateRequiredArgs(m, reqArgs)
    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [map, key]
        sign = ["java.lang.String", "java.lang.String"]
        ora_mbs.invoke(objectName, "deleteCredential", params, sign)
    except MBeanException, e :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


#######################################################
# grantAppRoleImpl API
#######################################################

def grantAppRoleImpl(m,on) :
    from javax.management.openmbean import CompositeData
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableApplicationRole
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableRoleMember
    from  oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType
    import jarray
    
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("appRoleName")
    reqArgs.add("principalClass")
    reqArgs.add("principalName")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        r = PortableApplicationRole(m.get("appRoleName"), "", "", "", m.get("appStripe"))
        princType = opss_getPrincipalType(m.get("principalClass")) 
	print princType
        pm = PortableRoleMember(m.get("principalClass"), m.get("principalName"), princType, m.get("appStripe"))
        marr = jarray.array([pm.toCompositeData(None)], CompositeData)
	print marr
        params = [m.get("appStripe"), r.toCompositeData(None), marr]

        sign = ["java.lang.String", "javax.management.openmbean.CompositeData", "[Ljavax.management.openmbean.CompositeData;"]
        ora_mbs.invoke(objectName, "addMembersToApplicationRole", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except Exception, e1:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
	print e1.getLocalizedMessage()
        raise e1

#######################################################
# grantPermissionImpl API
#######################################################

def grantPermissionImpl(m,on,obn) :
    from javax.management.openmbean import CompositeData
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePrincipal
    from oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePermission
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableCodeSource
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableGrantee
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableGrant
    import jarray

    reqArgs = ArrayList()
    reqArgs.add("permClass")
    validateRequiredArgs(m, reqArgs)

    grpArgs = ArrayList()
    grpArgs.add("principalClass")
    grpArgs.add("principalName")
    validateGroupArgs(m, grpArgs)
    try :
        
        pPl = None
        if m.get("principalClass") is not None and m.get("principalName")is not None:
            pPl = PortablePrincipal(m.get("principalClass"), m.get("principalName"), PortablePrincipal.PrincipalType.CUSTOM)
        pCs = PortableCodeSource(m.get("codeBaseURL"))
        pPlArray = None
        if pPl is not None:
            pPlArray = jarray.array([pPl], PortablePrincipal)
        pGe = PortableGrantee(pPlArray, pCs)
        pPm = PortablePermission(m.get("permClass"), m.get("permTarget"), m.get("permActions"))
        pGt = PortableGrant(pGe, jarray.array([pPm], PortablePermission))
        if m.get("appStripe") is None:
            objectName = ora_mbs.makeObjectName(on)
            params = [jarray.array([pGt.toCompositeData(None)], CompositeData)]
            sign = ["[Ljavax.management.openmbean.CompositeData;"]
            perms =  ora_mbs.invoke(objectName, "grantToSystemPolicy", params, sign)
        else:
            objectName = ora_mbs.makeObjectName(obn)
            params = [m.get("appStripe"), jarray.array([pGt.toCompositeData(None)], CompositeData)]
            sign = ["java.lang.String", "[Ljavax.management.openmbean.CompositeData;"]
            perms =  ora_mbs.invoke(objectName, "grantToApplicationPolicy", params, sign)

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise



#######################################################
# revokeAppRoleImpl API
#######################################################

def revokeAppRoleImpl(m,on) :
    from javax.management.openmbean import CompositeData
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePrincipal
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableApplicationRole
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableRoleMember
    from  oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType    
    import jarray   
    
    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("appRoleName")
    reqArgs.add("principalClass")
    reqArgs.add("principalName")
    validateRequiredArgs(m, reqArgs)

    try :
        
        objectName = ora_mbs.makeObjectName(on)
        r = PortableApplicationRole(m.get("appRoleName"), "", "", "", m.get("appStripe"))
        princType = opss_getPrincipalType(m.get("principalClass")) 
        pm = PortableRoleMember(m.get("principalClass"), m.get("principalName"), princType, m.get("appStripe"))
        marr = jarray.array([pm.toCompositeData(None)], CompositeData)
        params = [m.get("appStripe"), r.toCompositeData(None), marr]
        sign = ["java.lang.String", "javax.management.openmbean.CompositeData", "[Ljavax.management.openmbean.CompositeData;"]
        ora_mbs.invoke(objectName, "removeMembersFromApplicationRole", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

#######################################################
# revokePermissionImpl API
#######################################################

def revokePermissionImpl(m,on,obn) :
    from javax.management.openmbean import CompositeData
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePrincipal
    from oracle.security.jps.mas.mgmt.jmx.policy.PortablePrincipal import PrincipalType
    from oracle.security.jps.mas.mgmt.jmx.policy import PortablePermission
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableCodeSource
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableGrantee
    from oracle.security.jps.mas.mgmt.jmx.policy import PortableGrant

    import jarray  
   
    reqArgs = ArrayList()
    reqArgs.add("permClass")
    validateRequiredArgs(m, reqArgs)
    grpArgs = ArrayList()
    grpArgs.add("principalClass")
    grpArgs.add("principalName")
    validateGroupArgs(m, grpArgs)

    try :
        pPl = None
        if m.get("principalClass") is not None and m.get("principalName")is not None:
            pPl = PortablePrincipal(m.get("principalClass"), m.get("principalName"), PortablePrincipal.PrincipalType.CUSTOM)
        pCs = PortableCodeSource(m.get("codeBaseURL"))
        pPlArray = None
        if pPl is not None:
            pPlArray = jarray.array([pPl], PortablePrincipal)
        pGe = PortableGrantee(pPlArray, pCs)
        pPm = PortablePermission(m.get("permClass"), m.get("permTarget"), m.get("permActions"))
        pGt = PortableGrant(pGe, jarray.array([pPm], PortablePermission))
        if m.get("appStripe") is None:
            objectName = ora_mbs.makeObjectName(on)
            params = [jarray.array([pGt.toCompositeData(None)], CompositeData)]
            sign = ["[Ljavax.management.openmbean.CompositeData;"]
            ora_mbs.invoke(objectName, "revokeFromSystemPolicy", params, sign)
        else:
            objectName = ora_mbs.makeObjectName(obn)
            params = [m.get("appStripe"), jarray.array([pGt.toCompositeData(None)], CompositeData)]
            sign = ["java.lang.String", "[Ljavax.management.openmbean.CompositeData;"]
            ora_mbs.invoke(objectName, "revokeFromApplicationPolicy", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


#######################################################
# updateCredImpl API
#######################################################

def updateCredImpl(m,on) :
    import jarray

    map = m.get("map")
    key = m.get("key")
    user = m.get("user")
    password = m.get("password")
    desc = m.get("desc")

    reqArgs = ArrayList()
    reqArgs.add("map")
    reqArgs.add("key")
    reqArgs.add("user")
    reqArgs.add("password")
    validateRequiredArgs(m, reqArgs)
    
    try :
        pc = createCredObj(user, password, desc)
        objectName = ora_mbs.makeObjectName(on)
        cd = pc.toCompositeData(None);
        params = [map, key, cd]
        sign = ["java.lang.String", "java.lang.String", "javax.management.openmbean.CompositeData"]        
        ora_mbs.invoke(objectName, "resetPortableCredential", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


#######################################################
# migrateSecurityStoreImpl API
#######################################################

def migrateSecurityStoreImpl(m) :
    from oracle.security.jps.tools.utility import JpsUtilMigrationTool
    
    reqArgs = ArrayList()
    reqArgs.add("type")
    reqArgs.add("src")
    reqArgs.add("dst")
    reqArgs.add("configFile")
    validateRequiredArgs(m, reqArgs)
    grpArgs = ArrayList()
    grpArgs.add("processPrivRole")
    grpArgs.add("resourceTypeFile")
    validateGroupArgs(m, grpArgs)


    validateConflictingArgs(m, "dstLdifFile", "srcApp")
    validateConflictingArgs(m, "dstLdifFile", "dstApp")
    if not (m.get("processPrivRole") is  None) :
       validateBooleanValue("processPrivRole", m.get("processPrivRole"))
    if not (m.get("overWrite") is  None) :
       validateBooleanValue("overWrite", m.get("overWrite"))
    if not (m.get("preserveAppRoleGuids") is  None) :
       validateBooleanValue("preserveAppRoleGuids", m.get("preserveAppRoleGuids"))
    try :
        mig = JpsUtilMigrationTool.executeCommand(m)
    except JpsException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


#######################################################
# upgradeSecurityStoreImpl API
#######################################################

def upgradeSecurityStoreImpl(m) :
    from oracle.security.jps.tools.utility import JpsUtilUpgradeTool
    
    reqArgs = ArrayList()
    reqArgs.add("type")
    reqArgs.add("jpsConfigFile")
    validateRequiredArgs(m, reqArgs)
    
    validateConflictingArgs(m, "srcJaznConfigFile", "srcJaznDataFile")
    
    try :
        mig = JpsUtilUpgradeTool.executeCommand(m)
    except JpsException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

#######################################################
# reassociateService API
#######################################################

#Mbean apis are called for reassociation of policy and credential store
def reassociateService(pm,o,s,join) :    
      
    params = [pm.toCompositeData(None), s] 
    sign = ["javax.management.openmbean.CompositeData","java.lang.String"]
    ora_mbs.invoke(o,"checkServiceSetUp", params, sign)
    msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_LDAP_SERVER_SETUP_DONE)
    print msg
    if  (join == "false") :
    	ora_mbs.invoke(o, "checkAndSeedSchema", None, None)
    	msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_LDAP_SCHEMA_SEEDED)
    	print msg 
    	ora_mbs.invoke(o, "migrateData", None, None)
    	msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_DATA_MIGRATED)
    	print msg
    	ora_mbs.invoke(o, "testJpsService", None, None)
    	msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_SERVICE_POST_MIGRATION_OK)
    	print msg
    	
    ora_mbs.invoke(o, "updateLDAPReassociationConfiguration", None, None)
    msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_JPS_CONFIGURATION_DONE)
    print msg

#######################################################
# reassociateSecurityStoreImpl API
#######################################################

def reassociateSecurityStoreImpl(m,on) :
    from oracle.security.jps.mas.mgmt.jmx.config import PortableMap       
    from javax.management import RuntimeMBeanException
    import Opss as opss

    #Remove empty arguments
    rmArgs = ArrayList()
    for k in m.keySet():
        if (m.get(k) is None) :
            rmArgs.add(k)
    for i in range(len(rmArgs)) :
        m.remove(rmArgs[i])

    #Construct the required and optional argurments for the script
    reqArgs = ArrayList()
    reqArgs.add("domain")
    reqArgs.add("servertype")
    reqArgs.add("jpsroot")

    servertype = m.get("servertype")
    if (servertype == "DB_ORACLE") :
        reqArgs.add("datasourcename")
    elif (servertype == "OID") :
        reqArgs.add("admin")
        reqArgs.add("password")
        reqArgs.add("ldapurl")
    else :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_INVALID_STORE_TYPE)
        print msg + servertype
        raise Exception, msg + servertype

    #validate if all the required args are passed through the commandline. Else inform the user
    #about the missing or conflict arguments
    validateRequiredArgs(m, reqArgs)
    validateConflictingArgs(m, "ldapurl", "datasourcename")

    #check and validate if the group attribute information is passed
    grpArgs = ArrayList()
    grpArgs.add("admin")
    grpArgs.add("password")
    validateGroupArgs(m, grpArgs)

    #join option implies, it is configuration only reassociation without migration
    join = None

    if (m.get("join") is  None) :
	join = "false"
        m.remove("join")
    else :
    	validateBooleanValue("join", m.get("join"))
	join = m.remove("join")
       
   
    try :
        #Navigate to the current domain. WLST inbuild tree command     
        o = ora_mbs.makeObjectName(on)     
        pm = PortableMap(m)
        #Reassociate the Policy Store
        s = "POLICY_STORE"               
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_POLICY_STORE_REASS_START)
        print msg
        reassociateService(pm,o,s,join)       
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_POLICY_STORE_REASS_END)
        print msg 
        
        #Reassociate credential store
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_CRED_STORE_REASS_START)
        print msg
        s = "CREDENTIAL_STORE"
        reassociateService(pm,o,s,join)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_CRED_STORE_REASS_END)
        print msg
        
	#Reassociate keystore 
        try :
            msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_KEY_STORE_REASS_START)
            print msg
            s = "KEY_STORE"
            reassociateService(pm,o,s,join)
            msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_KEY_STORE_REASS_END)
            print msg
        except RuntimeMBeanException, rme:
            print rme.getLocalizedMessage() + "\n"

        #persist the changes to jps-config.xml        
        ora_mbs.invoke(o, "persist", None, None)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_CONFIG_CHANGE_REASS)
        print msg

    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

# reassociateSecurityStoreImp function ends

#######################################################
# modifyBootStrapCredentialImpl API
#######################################################

def modifyBootStrapCredentialImpl(m) :
    #Check for required arguments
    from oracle.security.jps.tools.utility import JpsUtilModifyBootCredTool
    from jarray import array
   
    reqArgs = ArrayList()
    reqArgs.add("jpsConfigFile")
    reqArgs.add("username")
    reqArgs.add("password")
    validateRequiredArgs(m, reqArgs)
    
    configfile = m.get("jpsConfigFile")
    username   = m.get("username")
    password   = m.get("password")
  
    carr = array(password,'c')
    
    try :
        JpsUtilModifyBootCredTool.executeCommand(configfile,username,carr)
    except JpsException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


#######################################################
# addBootStrapCredentialImpl API
#######################################################

def addBootStrapCredentialImpl(m) :
    #Check for required arguments
    from oracle.security.jps.tools.utility import JpsUtilAddBootCredTool
    from jarray import array

    reqArgs = ArrayList()
    reqArgs.add("jpsConfigFile")
    reqArgs.add("map")
    reqArgs.add("key")
    reqArgs.add("username")
    reqArgs.add("password")
    validateRequiredArgs(m, reqArgs)

    configfile = m.get("jpsConfigFile")
    map        = m.get("map")
    key        = m.get("key")
    username   = m.get("username")
    password   = m.get("password")

    carr = array(password,'c')

    try :
        JpsUtilAddBootCredTool.executeCommand(configfile,map,key,username,carr)
    except JpsException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

#######################################################
# patchPolicyStoreImpl API
#######################################################

def patchPolicyStoreImpl(m) :
    
    from oracle.security.jps.patch import PatchTool
    from oracle.security.jps.patch import PatchingException

    reqArgs = ArrayList()
    reqArgs.add(PatchTool.phase)
    reqArgs.add(PatchTool.patchDeltaFolder)
    reqArgs.add(PatchTool.productionJpsConfig)
    validateRequiredArgs(m, reqArgs)
    silent = m.get(PatchTool.silent)
    if silent is None :
        m.put(PatchTool.silent,"false")
    else :
        validateBooleanValue(PatchTool.silent,silent)

    try :
        PatchTool.patchPolicyStore(m)
    except PatchingException, pe :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + pe.getLocalizedMessage() + "\n"
        raise pe
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise


#######################################################

#######################################################
# configureIdStoreImpl API                            #
#######################################################

def configureIdentityStoreImpl(on,ldapUrl,adminId,arrPassword,ldapType,subscriberName,userSearchBase,groupSearchBase,mp,checkLdapInst):
    from oracle.security.jps.mas.mgmt.jmx.config import JpsConfigMXBean
    from javax.management import MBeanException
    from jarray import array
    from java.lang import Object
    from java.lang import String
    from java.util import Properties
    from java.io import File
    from java.io import FileInputStream
    from oracle.security.jps.mas.mgmt.jmx.config import JpsConfigMBeanConstants
   
    
    STR_NAME = "java.lang.String"
    CHAR_ARRAY_NAME = "[C"
    STRING_ARRAY_NAME = "[Ljava.lang.String;"
    COMPOSITEDATA_NAME = "javax.management.openmbean.CompositeData"

    params = [None, ldapUrl, adminId, arrPassword, ldapType, subscriberName, userSearchBase, groupSearchBase, mp]
    sign = [STR_NAME, STR_NAME, STR_NAME, CHAR_ARRAY_NAME, STR_NAME, STR_NAME, STRING_ARRAY_NAME, STRING_ARRAY_NAME, COMPOSITEDATA_NAME]

    lParams = [ldapUrl,adminId,arrPassword]
    lSign = [STR_NAME,STR_NAME,CHAR_ARRAY_NAME]
    
    validateBooleanValue(JpsConfigMBeanConstants.CHECK_LDAP_INSTANCE, checkLdapInst)

    try :
          o = ora_mbs.makeObjectName(on)
          if (checkLdapInst == "true" ) :
           ora_mbs.invoke(o, 'testLDAPConnection', lParams,lSign)
          ora_mbs.invoke(o, 'configureLDAPIdentityStore', params, sign)
          ora_mbs.invoke(o, 'persist', None, None)
    except MBeanException, e:          
          msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
          print msg + e.getLocalizedMessage() + "\n"
          raise e
    except :
          msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
          print msg
          raise


########################################################
#  listKeyStores
########################################################

def listKeyStoresImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        params = [appStripe]
        sign = ["java.lang.String"]
        arr = None
        arr = ora_mbs.invoke(objectName, "listKeyStores", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (arr != None):
        length = len(arr)
        for i in range(length):
            print arr[i]

########################################################
#  createKeyStore 
########################################################

def createKeyStoreImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.lang import Boolean
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    permission = m.get("permission")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("permission")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        tmpbool = String(permission)
        tmp = Boolean(tmpbool)
        boolval = tmp.booleanValue()
        params = [appStripe, name, pwd, boolval]
        sign = ["java.lang.String", "java.lang.String", "[C", "boolean"]
        ora_mbs.invoke(objectName, "createKeyStore", params, sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CREATE_KS_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  deleteKeyStore 
########################################################
    
def deleteKeyStoreImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        params = [appStripe, name, pwd]
        sign = ["java.lang.String", "java.lang.String", "[C"]
        ora_mbs.invoke(objectName, "deleteKeyStore", params, sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_DELETE_KS_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  changeKeyStorePassword 
########################################################

def changeKeyStorePasswordImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")
    name = m.get("name")
    currentpassword = m.get("currentpassword")
    newpassword = m.get("newpassword")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("currentpassword")
    reqArgs.add("newpassword")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        cpwd = String(currentpassword).toCharArray()
        npwd = String(newpassword).toCharArray()
        params = [appStripe, name, cpwd, npwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "[C"]
        ora_mbs.invoke(objectName, "changeKeyStorePassword", params, sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CHANGE_KS_PWD_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  generateKeyPair 
########################################################

def generateKeyPairImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from oracle.security.jps.mas.mgmt.jmx.config import PortableMap
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.util import HashMap 
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    dn = m.get("dn")
    keysize = m.get("keysize")
    alias = m.get("alias")
    keypassword = m.get("keypassword")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("dn")
    reqArgs.add("keysize")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()
        keyprops = HashMap()
        keyprops.put("keySize", keysize)
        pm = PortableMap(keyprops)

        params = [appStripe, name, pwd, dn, pm.toCompositeData(None), alias, kpwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "javax.management.openmbean.CompositeData", "java.lang.String", "[C"]
        ora_mbs.invoke(objectName, "createDemoCASignedCertificate", params, sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CREATE_KP_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  generateSecretKey 
########################################################

def generateSecretKeyImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from oracle.security.jps.mas.mgmt.jmx.config import PortableMap
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.util import HashMap 
    appStripe = m.get("appstripe")
    name = m.get("name")
    password = m.get("password")
    algorithm = m.get("algorithm")
    keysize = m.get("keysize")
    alias = m.get("alias")
    keypassword = m.get("keypassword")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("algorithm")
    reqArgs.add("keysize")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()
        keyprops = HashMap()
        keyprops.put("keySize", keysize)
        keyprops.put("algorithm", algorithm)
        pm = PortableMap(keyprops)
        params = [appStripe, name, pwd, pm.toCompositeData(None), alias, kpwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "javax.management.openmbean.CompositeData", "java.lang.String", "[C"]
        ora_mbs.invoke(objectName, "generateSecretKey", params, sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CREATE_SK_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  listKeyStoreAliases 
########################################################

def listKeyStoreAliasesImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    type = m.get("type")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("type")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        params = [appStripe, name, pwd, type]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String"
]
        arr = None
        arr = ora_mbs.invoke(objectName, "listAliases", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (arr != None):
        length = len(arr)
        for i in range(length):
            print arr[i]

########################################################
#  changeKeyStoreKeyPassword 
########################################################

def changeKeyStoreKeyPasswordImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    alias = m.get("alias")
    currentkeypassword = m.get("currentkeypassword")
    newkeypassword = m.get("newkeypassword")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("alias")
    reqArgs.add("currentkeypassword")
    reqArgs.add("newkeypassword")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        ckpwd = String(currentkeypassword).toCharArray()
        nkpwd = String(newkeypassword).toCharArray()
        params = [appStripe, name, pwd, alias, ckpwd, nkpwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "[C", "[C"]
        ora_mbs.invoke(objectName, "changeKeyPassword", params, sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CHANGE_KEY_PWD_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  getKeyStoreCertificates 
########################################################

def getKeyStoreCertificatesImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    alias = m.get("alias")
    keypassword = m.get("keypassword")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()
        params = [appStripe, name, pwd, alias, kpwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "[C"]
        arr = None
        arr = ora_mbs.invoke(objectName, "getCertificates", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (arr != None):
        length = len(arr)
        for i in range(length):
            print arr[i]

########################################################
#  getKeyStoreSecretKeyProperties 
########################################################

def getKeyStoreSecretKeyPropertiesImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    alias = m.get("alias")
    keypassword = m.get("keypassword")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()
        params = [appStripe, name, pwd, alias, kpwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "[C"]
        list = None
        list = ora_mbs.invoke(objectName, "getSecretKeyProperties", params, sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (list != None):
        print '-------------------------------------------------------'
        algo = list[0]
        msg = "Algorithm = "
        print msg + algo
        print '-------------------------------------------------------'

########################################################
#  exportKeyStoreCertificateRequest 
########################################################

def exportKeyStoreCertificateRequestImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.io import FileOutputStream
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    alias = m.get("alias")
    keypassword = m.get("keypassword")
    filepath = m.get("filepath")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    reqArgs.add("filepath")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()
        params = [appStripe, name, pwd, alias, kpwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "[C"]
        base64 = None
        base64 = ora_mbs.invoke(objectName, "exportCertificateRequest", params,sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (base64 != None):
        arr = String(base64).getBytes()
        fos = FileOutputStream(filepath)
        fos.write(arr)
        fos.flush()
        fos.close()
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CERT_REQ_EXPORTED)
        print msg
    else:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CERT_REQ_FAILED)
        print msg

########################################################
#  exportKeyStoreCertificate 
########################################################

def exportKeyStoreCertificateImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.io import FileOutputStream
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    alias = m.get("alias")
    keypassword = m.get("keypassword")
    type = m.get("type")
    filepath = m.get("filepath")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    reqArgs.add("type")
    reqArgs.add("filepath")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()
        params = [appStripe, name, pwd, alias, kpwd, type]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "[C", "java.lang.String"]
        base64 = None
        base64 = ora_mbs.invoke(objectName, "exportCertificates", params,sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (base64 != None):
        arr = String(base64).getBytes()
        fos = FileOutputStream(filepath)
        fos.write(arr)
        fos.flush()
        fos.close()
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CERT_EXPORTED)
        print msg
    else:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_CERT_FAILED)
        print msg

########################################################
#  importKeyStoreCertificate 
########################################################

def importKeyStoreCertificateImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.io import FileInputStream
    from jarray import zeros
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    alias = m.get("alias")
    keypassword = m.get("keypassword")
    type = m.get("type")
    filepath = m.get("filepath")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    reqArgs.add("type")
    reqArgs.add("filepath")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()

        fis = FileInputStream(filepath)
        num = fis.available()
        arr = zeros(num, 'b')
        fis.read(arr)
        fis.close()
        base64 = String(arr)

        params = [appStripe, name, pwd, alias, kpwd, type, base64]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "[C", "java.lang.String", "java.lang.String"]
        ora_mbs.invoke(objectName, "importCertificates", params,sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_IMPORT_CERT_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  deleteKeyStoreEntry 
########################################################

def deleteKeyStoreEntryImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    alias = m.get("alias")
    keypassword = m.get("keypassword")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("alias")
    reqArgs.add("keypassword")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        kpwd = String(keypassword).toCharArray()
        params = [appStripe, name, pwd, alias, kpwd]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "[C"]
        ora_mbs.invoke(objectName, "deleteKeyStoreEntry", params,sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_DELETE_ENTRY_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
#  listExpiringCertificates 
########################################################

def listExpiringCertificatesImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.lang import Boolean
    from java.lang import Integer
    days = m.get("days")
    autorenew = m.get("autorenew")

    reqArgs = ArrayList()
    reqArgs.add("days")
    reqArgs.add("autorenew")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        tmp = Integer(days)
        numberOfDays = tmp.intValue()
        tmpbool = String(autorenew)
        tmp = Boolean(tmpbool)
        boolval = tmp.booleanValue()
        params = [numberOfDays, boolval]
        sign = ["int", "boolean"]
        outerlist = None
        outerlist = ora_mbs.invoke(objectName, "listExpiringCertificates", params,sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (outerlist != None):
        length = len(outerlist)
        for i in range(length):
            certinfo = outerlist[i]
            stripe = certinfo[0]
            ksname = certinfo[1]
            alias = certinfo[2]
            status = certinfo[3]
            expiry = certinfo[4]
            print '---------------------------------------------------'
            print "Stripe = " + stripe
            print "Keystore = " + ksname
            print "Alias = " + alias
            print "Certificate status = " + status
            print "Expiration Date = " + expiry
            print '---------------------------------------------------'

########################################################
#  exportKeyStore 
########################################################

def exportKeyStoreImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.io import FileOutputStream
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    aliases = m.get("aliases")
    keypasswords = m.get("keypasswords")
    type = m.get("type")
    filepath = m.get("filepath")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("aliases")
    reqArgs.add("keypasswords")
    reqArgs.add("type")
    reqArgs.add("filepath")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        params = [appStripe, name, pwd, aliases, keypasswords, type]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String", "java.lang.String", "java.lang.String"]
        ksbytes = None
        ksbytes = ora_mbs.invoke(objectName, "exportKeyStore", params,sign)
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

    if (ksbytes != None):
        fos = FileOutputStream(filepath)
        fos.write(ksbytes)
        fos.flush()
        fos.close()
    msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_EXPORT_KS_DONE)
    print msg + "\n"

########################################################
#  importKeyStore 
########################################################

def importKeyStoreImpl(m, on):
    from  oracle.security.jps.mas.mgmt.jmx.util import JpsJmxConstants
    from javax.management import MBeanException
    from java.util import ArrayList
    from java.lang import Boolean
    from jarray import zeros 
    from java.io import FileInputStream
    appStripe = m.get("appStripe")
    name = m.get("name")
    password = m.get("password")
    aliases = m.get("aliases")
    keypasswords = m.get("keypasswords")
    type = m.get("type")
    permission = m.get("permission")
    filepath = m.get("filepath")

    reqArgs = ArrayList()
    reqArgs.add("appStripe")
    reqArgs.add("name")
    reqArgs.add("password")
    reqArgs.add("aliases")
    reqArgs.add("keypasswords")
    reqArgs.add("type")
    reqArgs.add("permission")
    reqArgs.add("filepath")
    validateRequiredArgs(m, reqArgs)

    try :
        objectName = ora_mbs.makeObjectName(on)
        pwd = String(password).toCharArray()
        tmpbool = String(permission)
        tmp = Boolean(tmpbool)
        boolval = tmp.booleanValue()
        fis = FileInputStream(filepath)
        num = fis.available()
        arr = zeros(num, 'b')
        fis.read(arr)
        fis.close()

        params = [appStripe, name, pwd, aliases, keypasswords, type, arr, boolval]
        sign = ["java.lang.String", "java.lang.String", "[C", "java.lang.String" , "java.lang.String", "java.lang.String", "[B", "boolean"]
        ora_mbs.invoke(objectName, "importKeyStore", params,sign)
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_FKS_IMPORT_KS_DONE)
        print msg + "\n"
    except MBeanException, e:
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_COMMAND_FAILED)
        print msg + e.getLocalizedMessage() + "\n"
        raise e
    except :
        msg = opss_resourceBundle.getString(WlstResources.MSG_WLST_UNKNOWN_REASON)
        print msg
        raise

########################################################
