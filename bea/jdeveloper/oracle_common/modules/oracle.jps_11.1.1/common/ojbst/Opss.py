################################################################
# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################

import Opss_common as opss
import cie.OracleHelp

def addOpssCommandHelp() :
   opss.addOpssCommandHelp()

def help(topic = None):
  m_name = 'opss'
  if topic == None:
    topic = m_name
  else:
    topic = m_name + '.' + topic
  return OracleHelp.help(topic)

#######################################################
# This function list the credentials
#######################################################

def listCred(map=None, key=None) :
   opss.listCred(map,key)

#######################################################
# This function creates ResourceType
#######################################################
def createResourceType(appStripe=None, resourceTypeName=None, displayName=None, description=None, provider=None, matcher=None, allowedActions=None, delimiter=None) :
    opss.createResourceType(appStripe, resourceTypeName, displayName, description, provider, matcher, allowedActions, delimiter)

#######################################################
# This function prints ResourceType
#######################################################
def getResourceType(appStripe=None, resourceTypeName=None) :
    opss.getResourceType(appStripe, resourceTypeName)

#######################################################
# This function deletes ResourceType
#######################################################
def deleteResourceType(appStripe=None, resourceTypeName=None) :
    opss.deleteResourceType(appStripe, resourceTypeName)

############################################
# This function creates Resource
############################################
def createResource(appStripe=None, name=None, type=None, displayName=None, description=None) :
    opss.createResource(appStripe, name, type, displayName, description)

############################################
# This function prints the resource
############################################
def getResource(appStripe=None, name=None, type=None) :
    opss.getResource(appStripe, name, type)

#############################################
# This function deletes the resource
#############################################
def deleteResource(appStripe=None, name=None, type=None) :
    opss.deleteResource(appStripe, name, type)

#############################################
# This function lists the resources
#############################################
def listResources(appStripe=None, type=None) :
    opss.listResources(appStripe, type)

#############################################
# This function lists the resource actions
#############################################
def listResourceActions(appStripe=None, entitlementName=None) :
    opss.listResourceActions(appStripe, entitlementName)

#############################################
# This function lists the resource types
#############################################
def listResourceTypes(appStripe=None) :
    opss.listResourceTypes(appStripe)

############################################
# This function creates Permission Set
############################################
def createEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None, displayName=None, description=None) :
    opss.createEntitlement(appStripe, name, resourceName, resourceType, actions, displayName, description)

############################################
# This function prints the permission set
############################################
def getEntitlement(appStripe=None, name=None) :
    opss.getEntitlement(appStripe, name)

#############################################
# This function deletes the permission set
#############################################
def deleteEntitlement(appStripe=None, name=None) :
    opss.deleteEntitlement(appStripe, name)

####################################################
# This function adds a member to the permission set
####################################################
def addResourceToEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None) :
    opss.addResourceToEntitlement(appStripe, name, resourceName, resourceType, actions)

########################################################
# This function revokes a member from the permission set
########################################################
def revokeResourceFromEntitlement(appStripe=None, name=None, resourceName=None, resourceType=None, actions=None) :
    opss.revokeResourceFromEntitlement(appStripe, name, resourceName, resourceType, actions)

#############################################
# This function lists all permission sets
#############################################
def listEntitlements(appStripe=None, resourceTypeName=None, resourceName=None,principalName=None, principalClass=None) :
    opss.listEntitlements(appStripe, resourceTypeName, resourceName, principalName, principalClass)

######################################################
# This function grants a permission set to a principal
######################################################
def grantEntitlement(appStripe=None, principalName=None, principalClass=None, entitlementName=None) :
    opss.grantEntitlement(appStripe, principalName, principalClass, entitlementName)

######################################################
# This function revokes a permission set from a principal
######################################################
def revokeEntitlement(appStripe=None, principalName=None, principalClass=None, entitlementName=None) :
    opss.revokeEntitlement(appStripe, principalName, principalClass, entitlementName)

#######################################################
# This function lists all the app stripes
#######################################################

def listAppStripes(configFile=None, regularExpression=None) :
    opss.listAppStripes(configFile, regularExpression)

#######################################################
# This function list the approles
#######################################################

def listAppRoles(appStripe=None) :
    opss.listAppRoles(appStripe)

#######################################################
# This function list the approle members
#######################################################

def listAppRoleMembers(appStripe=None, appRoleName=None) :
    opss.listAppRoleMembers(appStripe, appRoleName)

#######################################################
# This function list the permissions
#######################################################

def listPermissions(appStripe=None, principalClass=None, principalName=None) :
    opss.listPermissions(appStripe, principalClass, principalName)


#######################################################
# This function creates an approle
#######################################################

def createAppRole(appStripe=None, appRoleName=None) :  
    opss.createAppRole(appStripe, appRoleName)

#######################################################
# This function creates a credential
#######################################################

def createCred(map=None, key=None, user=None, password=None, desc=None) :
    opss.createCred(map, key, user, password, desc)


#######################################################
# This function deletes an app policy
#######################################################

def deleteAppPolicies(appStripe=None) :
    opss.deleteAppPolicies(appStripe)


#######################################################
# This function deletes an approle
#######################################################

def deleteAppRole(appStripe=None, appRoleName=None) :  
    opss.deleteAppRole(appStripe, appRoleName)


#######################################################
# This function deletes a credential
#######################################################

def deleteCred(map=None, key=None) :
    opss.deleteCred(map, key)

#######################################################
# This function grants an approle
#######################################################

def grantAppRole(appStripe=None, appRoleName=None, principalClass=None, principalName=None) :  
    opss.grantAppRole(appStripe, appRoleName, principalClass, principalName)

#######################################################
# This function grants a permission
#######################################################

def grantPermission(appStripe=None, principalClass=None, principalName=None, codeBaseURL=None, permClass=None, permTarget=None, permActions=None) :    
    opss.grantPermission(appStripe, principalClass, principalName, codeBaseURL, permClass, permTarget, permActions)

#######################################################
# This function revokes an approle
#######################################################

def revokeAppRole(appStripe=None, appRoleName=None, principalClass=None, principalName=None) :  
    opss.revokeAppRole(appStripe, appRoleName, principalClass, principalName)

#######################################################
# This function revokes a permission
#######################################################

def revokePermission(appStripe=None, principalClass=None, principalName=None, codeBaseURL=None, permClass=None, permTarget=None, permActions=None) :   
    opss.revokePermission(appStripe, principalClass, principalName, codeBaseURL, permClass, permTarget, permActions)

#######################################################
# This function updates a credential
#######################################################

def updateCred(map=None, key=None, user=None, password=None, desc=None) :    
    opss.updateCred(map, key, user, password, desc)


###########################################################################
# This function migrates the policies istore/global/apppolicy/policystore
###########################################################################

def migrateSecurityStore(type=None, src=None, dst=None, srcApp=None, dstApp=None, srcFolder=None, dstFolder=None, dstLdifFile=None, srcConfigFile=None, configFile=None, overWrite=None, processPrivRole=None, resourceTypeFile=None, migrateIdStoreMapping=None, preserveAppRoleGuid=None, mode=None, reportFile=None) :   
    opss.migrateSecurityStore(type, src, dst, srcApp, dstApp, srcFolder, dstFolder, dstLdifFile, srcConfigFile, configFile, overWrite, processPrivRole, resourceTypeFile, migrateIdStoreMapping, preserveAppRoleGuid, mode, reportFile)

###########################################################################
# This function upgraded the policies 
###########################################################################

def upgradeSecurityStore(type=None, srcRealm=None, dst=None, srcJaznConfigFile=None, srcJaznDataFile=None, jpsConfigFile=None, users=None, dstJaznDataFile=None, resourceTypeFile=None, srcApp=None) :   
    opss.upgradeSecurityStore(type, srcRealm, dst, srcJaznConfigFile, srcJaznDataFile, jpsConfigFile, users, dstJaznDataFile, resourceTypeFile, srcApp)

###########################################################################
# This function reassociates
###########################################################################

def reassociateSecurityStore(domain=None, admin=None, password=None,ldapurl=None,servertype=None,jpsroot=None,join=None, datasourcename=None) :    
    opss.reassociateSecurityStore(domain, admin, password,ldapurl,servertype,jpsroot,join,datasourcename)

###########################################################################
# This function modifies the boot strap credential
###########################################################################

def modifyBootStrapCredential(jpsConfigFile=None,username=None, password=None) :   
    opss.modifyBootStrapCredential(jpsConfigFile,username, password)

###########################################################################
# This function modifies the boot strap credential
###########################################################################

def patchPolicyStore(phase=None, patchDeltaFolder=None, productionJpsConfig=None, baselineFile=None, patchFile=None, baselineAppStripe=None, productionAppStripe=None, patchAppStripe=None, silent=None) :
    opss.patchPolicyStore(phase, patchDeltaFolder, productionJpsConfig, baselineFile, patchFile, baselineAppStripe, productionAppStripe, patchAppStripe, silent)

###########################################################################
# This function configures identity store in default jps context
###########################################################################

def configureIdentityStore(propsFileLoc=None) : 
    opss.configureIdentityStore(propsFileLoc)

###########################################################################
# this function lists all keystores
###########################################################################

def listKeyStores(appStripe=None) :
    opss.listKeyStores(appStripe)

###########################################################################
# this function creates a keystore 
###########################################################################

def createKeyStore(appStripe=None, name=None, password=None, permission=None) :
    opss.createKeyStore(appStripe, name, password, permission)

###########################################################################
# this function deletes a keystore 
###########################################################################

def deleteKeyStore(appStripe=None, name=None, password=None) :
    opss.deleteKeyStore(appStripe, name, password)

###########################################################################
#  this function changes keystore password
###########################################################################

def changeKeyStorePassword(appStripe=None, name=None, currentpassword=None, newpassword=None) :
    opss.changeKeyStorePassword(appStripe, name, currentpassword, newpassword)

###########################################################################
#  this function generates a key pair
###########################################################################

def generateKeyPair(appStripe=None, name=None, password=None, dn=None, keysize=None, alias=None, keypassword=None) :
    opss.generateKeyPair(appStripe, name, password, dn, keysize, alias, keypassword)

###########################################################################
#  this function generates a secret key
###########################################################################

def generateSecretKey(appStripe=None, name=None, password=None, algorithm=None, keysize=None, alias=None, keypassword=None) :
    opss.generateSecretKey(appStripe, name, password, algorithm, keysize, alias, keypassword)

###########################################################################
#  this function lists keystore aliases 
###########################################################################

def listKeyStoreAliases(appStripe=None, name=None, password=None, type=None) :
    opss.listKeyStoreAliases(appStripe, name, password, type)

###########################################################################
#  this function changes keystore key password 
###########################################################################

def changeKeyPassword(appStripe=None, name=None, password=None, alias=None, currentkeypassword=None, newkeypassword=None) :
    opss.changeKeyPassword(appStripe, name, password, alias, currentkeypassword, newkeypassword)

###########################################################################
#  this function gets a keystore certificate 
###########################################################################

def getKeyStoreCertificates(appStripe=None, name=None, password=None, alias=None, keypassword=None) :
    opss.getKeyStoreCertificates(appStripe, name, password, alias, keypassword)

###########################################################################
#  this function gets keystore secret key properties 
###########################################################################

def getKeyStoreSecretKeyProperties(appStripe=None, name=None, password=None, alias=None, keypassword=None) :
    opss.getKeyStoreSecretKeyProperties(appStripe, name, password, alias, keypassword)

###########################################################################
#  this function generates and exports a certificate request 
###########################################################################

def exportKeyStoreCertificateRequest(appStripe=None, name=None, password=None,alias=None, keypassword=None, filepath=None) :
    opss.exportKeyStoreCertificateRequest(appStripe, name, password,alias, keypassword, filepath)

###########################################################################
#  this function exports a BASE64 encoded certificate, trusted certificate 
###########################################################################

def exportKeyStoreCertificate(appStripe=None, name=None, password=None,alias=None, keypassword=None, type=None, filepath=None) :
    opss.exportKeyStoreCertificate(appStripe, name, password, alias, keypassword, type, filepath)

###########################################################################
#  this function imports a BASE64 encoded certificate, trusted certificate 
###########################################################################

def importKeyStoreCertificate(appStripe=None, name=None, password=None,alias=None, keypassword=None, type=None, filepath=None) :
    opss.importKeyStoreCertificate(appStripe, name, password, alias, keypassword, type, filepath)

###########################################################################
#  this function deletes a keystore entry 
###########################################################################

def deleteKeyStoreEntry(appStripe=None, name=None, password=None,alias=None, keypassword=None) :
    opss.deleteKeyStoreEntry(appStripe, name, password, alias, keypassword)

###########################################################################
#  this function lists all expiring certificates and optionally renews them 
###########################################################################

def listExpiringCertificates(days=None, autorenew=None) :
    opss.listExpiringCertificates(days, autorenew)

###########################################################################
#  this function exports the keystore into file 
###########################################################################

def exportKeyStore(appStripe=None, name=None, password=None,aliases=None, keypasswords=None, type=None, filepath=None) :
    opss.exportKeyStore(appStripe, name, password, aliases, keypasswords, type, filepath)

###########################################################################
#  this function imports a keystore from file 
###########################################################################

def importKeyStore(appStripe=None, name=None, password=None,aliases=None, keypasswords=None, type=None, permission=None, filepath=None) :
    opss.importKeyStore(appStripe, name, password, aliases, keypasswords, type, permission, filepath)

###########################################################################


