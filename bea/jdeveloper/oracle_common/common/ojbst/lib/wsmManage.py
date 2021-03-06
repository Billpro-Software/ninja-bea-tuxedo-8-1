"""
 Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved. 

Caution: This file is part of the command scripting implementation. Do not edit or move
this file because this may cause commands and scripts to fail. Do not
try to reuse the logic in this file or keep copies of this file because this
could cause your scripts to fail when you upgrade to a different version
"""
"""
@author: Varun Arora
@since: 11.1.1.3
"""

from jarray import array
from java.io import File
from java.lang import Boolean
from java.lang import Exception as java_lang_Exception
from java.lang import String as java_String
from java.text import MessageFormat
from java.util import ArrayList
from java.util import List
from java.util import Map
from java.util import ResourceBundle
from java.util import Set
from javax.management import ObjectName
from javax.management import JMX
from javax.management import RuntimeMBeanException as javax_management_RuntimeMBeanException

from oracle.j2ee.ws.mgmt.wlst import ListWebServices
from oracle.j2ee.ws.mgmt.wlst import ListWebServiceRefs
from oracle.j2ee.ws.mgmt.wlst import ListWebServicePorts
from oracle.j2ee.ws.mgmt.wlst import ListWebServiceRefPortInfos
from oracle.j2ee.ws.mgmt.wlst import ListWebServicePolicy
from oracle.wsm.cli import CommandLineException
from oracle.wsm.cli import RepositoryCommands
from oracle.wsm.policymanager import IAlgorithmProcessor
from oracle.wsm.policymanager import IDocumentManager
from oracle.wsm.policymanager import IUpgradeManager
import ora_mbs
import ora_util
import os


wsmdebug = 0


"""
---------------------------------------------------------------------
Help Commands for WLST
---------------------------------------------------------------------
"""
def wsm_init_help():

    addHelpCommandGroup("wsmManage", "wsmManageHelp")
    addHelpCommand("upgradeWSMPolicyRepository", "wsmManage", online = "true")
    addHelpCommand("resetWSMPolicyRepository", "wsmManage", online = "true")
    addHelpCommand("abortRepositorySession", "wsmManage", online = "true")
    addHelpCommand("beginRepositorySession", "wsmManage", online = "true")
    addHelpCommand("commitRepositorySession", "wsmManage", online = "true")
    addHelpCommand("describeRepositorySession", "wsmManage", online = "true")
    addHelpCommand("createPolicySet", "wsmManage", online = "true")
    addHelpCommand("clonePolicySet", "wsmManage", online = "true")
    addHelpCommand("modifyPolicySet", "wsmManage", online = "true")
    addHelpCommand("attachPolicySet", "wsmManage", online = "true")
    addHelpCommand("setPolicySetDescription", "wsmManage", online = "true")
    addHelpCommand("enablePolicySet", "wsmManage", online = "true")
    addHelpCommand("attachPolicySetPolicy", "wsmManage", online = "true")
    addHelpCommand("detachPolicySetPolicy", "wsmManage", online = "true")
    addHelpCommand("enablePolicySetPolicy", "wsmManage", online = "true")
    addHelpCommand("deletePolicySet", "wsmManage", online = "true")
    addHelpCommand("displayPolicySet", "wsmManage", online = "true")
    addHelpCommand("listPolicySets", "wsmManage", online = "true")
    addHelpCommand("validatePolicySet", "wsmManage", online = "true")
    addHelpCommand("migrateAttachments", "wsmManage", online = "true")
    addHelpCommand("exportRepository", "wsmManage", online = "true")
    addHelpCommand("importRepository", "wsmManage", online = "true")

# Load the help messages when the script is loaded.
try:
    if ora_mbs.getPlatform() == "WLS":
        wsm_init_help()
    elif ora_mbs.getPlatform() == "WAS":
        import OracleHelp
        # Create help messages for WAS platform
        def help(topic=None):
            wsm_name = 'wsmManage'
            if topic == None:
               topic = wsm_name
            else:
               topic = wsm_name + '.' + topic
    	    return OracleHelp.help(topic)
except:
    pass
    
"""
---------------------------------------------------------------------
Global Variables
---------------------------------------------------------------------
"""
#Define the Repository CommandS
wsm_rcs = None
#Cache the MBean Server Connection Object
wsm_mbs = None
#The resource bundle.
wsm_rb = ResourceBundle.getBundle("oracle.wsm.resources.cli.CLIMessageBundle")


"""
---------------------------------------------------------------------
RepositorySession Commands
---------------------------------------------------------------------
"""


def abortRepositorySession():

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.abortRepositorySession()
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def beginRepositorySession():

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retString = wsm_rcs.beginRepositorySession()
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            print retString
    finally:
        wsm_backtoOldTree(oldTree)


def commitRepositorySession():

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.commitRepositorySession()
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def describeRepositorySession():

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.describeRepositorySession()
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


"""
---------------------------------------------------------------------
PolicySet Authoring Commands
---------------------------------------------------------------------
"""

def attachPolicySet(attachTo):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.attachPolicySet(attachTo)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def attachPolicySetPolicy(uri):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.attachPolicySetPolicy(uri)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def clonePolicySet(name, source, attachTo=None, description=None, enable='True'):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            bool_enable = wsm_getBooleanFromArg(enable)
            retList = wsm_rcs.clonePolicySet(name, source, attachTo, description, bool_enable)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def createPolicySet(name, type, attachTo, description=None, enable='True'):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            bool_enable = wsm_getBooleanFromArg(enable)
            retList = wsm_rcs.createPolicySet(name, type, attachTo, description, bool_enable)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def deletePolicySet(name):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.deletePolicySet(name)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def detachPolicySetPolicy(uri):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.detachPolicySetPolicy(uri)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def displayPolicySet(name=None):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return
    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.displayPolicySet(name)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def enablePolicySet(enable='True'):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return
    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            bool_enable = wsm_getBooleanFromArg(enable)
            retList = wsm_rcs.enablePolicySet(bool_enable)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def enablePolicySetPolicy(uri, enable='True'):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return
    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            bool_enable = wsm_getBooleanFromArg(enable)
            retList = wsm_rcs.enablePolicySetPolicy(uri, bool_enable)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def listPolicySets(type=None):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.listPolicySets(type)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def modifyPolicySet(name):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.modifyPolicySet(name)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def setPolicySetDescription(description):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return
    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.setPolicySetDescription(description)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def validatePolicySet(name=None):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()
            retList = wsm_rcs.validatePolicySet(name)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


"""
---------------------------------------------------------------------
Repository Commands
---------------------------------------------------------------------
"""

def exportRepository(archive, documents=None, expandReferences="false"):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()
    renmsg = ''
    try:
        try:
            wsm_rcs = wsm_getRCS()
            bool_value = wsm_getBooleanFromArg(expandReferences)
            archiveFile = File(archive)
            #If given archiveFile is a directory throw error
            if archiveFile.directory:
                raise Exception, wsm_getMsg('INVALID_FILE', [archiveFile.absolutePath])
            #If the directory is not writable throw error
            if not archiveFile.absoluteFile.parentFile.canWrite():
                raise Exception, wsm_getMsg('DIRECTORY_NOT_WRITABLE', [archiveFile.absoluteFile.parent])
            #If file exists prompt for overwrite
            if archiveFile.exists():
                isCorrectOpt = "false"
                while isCorrectOpt == "false":
                    isCorrectOpt = "true"
                    userOption = raw_input(wsm_getMsg('PROMPT_FOR_EXPORT'))
                    userOption = userOption.lower()
                    if userOption == wsm_getMsg('PROMPT_MODE_OPTION_ABORT'):
                        #Abort operation
                        print wsm_getMsg('CANCEL_OPERATION')
                        return
                    if userOption == wsm_getMsg('PROMPT_MODE_OPTION_NO'):
                        #rename the orignal file to bak file
                        os.rename(archive, archive+'-bak')
                        renmsg = wsm_getMsg('BAK_FILE',[archive])
                    elif userOption != wsm_getMsg('PROMPT_MODE_OPTION_YES'):
                        #wrong choice abort operation
                        print wsm_getMsg('UNSUPPORTED_OPTION')
                        isCorrectOpt = "false"
            retList = wsm_rcs.exportRepository(archiveFile, documents, bool_value)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
            if len(renmsg) > 0:
                print renmsg
    finally:
        wsm_backtoOldTree(oldTree)


def importRepository(archive, map=None,generateMapFile="false"):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            wsm_rcs = wsm_getRCS()

            archiveFile = File(archive)
            if map is None:
                mapFile=None
            else:
                mapFile = File(map)
            bool_value = wsm_getBooleanFromArg(generateMapFile)
            retList = wsm_rcs.importRepository(archiveFile, mapFile, bool_value)
        except CommandLineException, ex:
            for message in ex.getMessages():
                print message
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            for retVal in retList:
                print retVal
    finally:
        wsm_backtoOldTree(oldTree)


def resetWSMPolicyRepository(clearStore='False'):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            operationName = 'resetWSMPolicyRepository'
            print "\n" + wsm_getMsg("START_OPERATION_MSG") + operationName + " ...\n"
            ium = wsm_getUpgradeManager()
            returnVal = ium.resetWSMPolicyRepository(wsm_getBooleanFromArg(clearStore))
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            wsm_PrintMap(returnVal, operationName)
            print "\n" + operationName + wsm_getMsg("END_OPERATION_MSG")
    finally:
        wsm_backtoOldTree(oldTree)


def upgradeWSMPolicyRepository():

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:
            operationName = 'upgradeWSMPolicyRepository'
            print "\n" + wsm_getMsg("START_OPERATION_MSG") + operationName + " ...\n"
            ium = wsm_getUpgradeManager()
            returnVal = ium.upgradeWSMPolicyRepository()
        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
        else:
            wsm_PrintMap(returnVal, operationName)
            print "\n" + operationName + wsm_getMsg("END_OPERATION_MSG")
    finally:
        wsm_backtoOldTree(oldTree)


"""
---------------------------------------------------------------------
Attachment Migration
---------------------------------------------------------------------
"""

def migrateAttachments(mode = None):

    if not wsm_isConnected(wsm_getMsg('NOT_CONNECTED')):
        return

    # The default mode is 'prompt'. Since that needs to be localized,
    # can't directly specify the default value in the function signature.
    if mode == None:
        mode = wsm_getMsg("PROMPT_MODE")

    #Verify Mode.
    mode = mode.lower()
    if not (mode == wsm_getMsg("PROMPT_MODE") or mode == wsm_getMsg("PREVIEW_MODE") or mode == wsm_getMsg("FORCE_MODE")):
        raise Exception, wsm_getMsg('INVALID_MODE',
                                    [mode,
                                    wsm_getMsg("PREVIEW_MODE"),
                                    wsm_getMsg("PROMPT_MODE"),
                                    wsm_getMsg("FORCE_MODE")])

    oldTree = wsm_gotoDomainRuntime()

    try:
        try:

            #Get a handle to IAlgorithmProcessor
            beanObjName = wsm_getMBeanObjectName("oracle.wsm:*,name=WSMAlgorithmProcessor,type=Engine")
            iap = JMX.newMXBeanProxy(ora_mbs.getMbsInstance(), beanObjName, IAlgorithmProcessor)

            #Walk the Server to get the list of WebServices and relevant information.
            policySubjectList = wsm_walk("false")

            #Walk the Server to get the list of WebService Clients and the relevant information.
            policySubjectClientList = wsm_walk("true")

            #Append Client list to Server list
            policySubjectList.extend(policySubjectClientList)

            #Process the migration
            wsm_process(mode, policySubjectList, iap)

        except java_lang_Exception, ex:
            ora_util.raiseScriptingException(ex)
    finally:
        wsm_backtoOldTree(oldTree)


"""
---------------------------------------------------------------------
Internal Functions
---------------------------------------------------------------------
All internal functions will be prepended with 'wsm_'
to make them unique across all python scripts.
This is the recommended way of preventing ambiguity and
name clashes.
---------------------------------------------------------------------
"""

"""
Get an instance of the UpgradeManager MBean.
@return: JMX proxy for IUpgradeManager
"""
def wsm_getUpgradeManager():

    beanName = 'oracle.wsm:*,name=WSMUpgradeManager,type=Repository'
    beanObjName = wsm_getMBeanObjectName(beanName)
    ium = JMX.newMXBeanProxy(ora_mbs.getMbsInstance(), beanObjName, IUpgradeManager)

    return ium


"""
Display the result of reset/upgrade repository operations.
@param val - Map containing information to be displayed
@param operationName - The name of the operation.
"""
def wsm_PrintMap(val, operationName):

    list_create = []
    list_update = []
    list_delete = []

    addMsgKey = ""
    delMsgKey = ""
    updateMsgKey = ""

    if val is None or val.size() == 0:
        print "\n" + wsm_getMsg("NO_CHANGE_MSG") + "\n"
        return

    if isinstance(val, Map):
        keys = val.keySet()
        for key in keys:
            operation = val.get(key)
            if operation == "CREATE":
                list_create.append(key)
            elif operation == "UPDATE":
                list_update.append(key)
            elif operation == "DELETE":
                list_delete.append(key)

    #Print the Documents
    if operationName == "upgradeWSMPolicyRepository":
        addMsgKey = "UPGRADE_ADDED_MSG"
        delMsgKey = "UPGRADE_DELETED_MSG"
        updateMsgKey = "UPGRADE_UPDATED_MSG"
    else:
        addMsgKey = "RESET_ADDED_MSG"
        delMsgKey = "RESET_DELETED_MSG"
        updateMsgKey = "RESET_UPDATED_MSG"

    if len(list_create) > 0:
        print "\n" + wsm_getMsg(addMsgKey) + "\n"
        list_create.sort()
        for doc in list_create:
            print doc

    if len(list_update) > 0:
        print "\n" + wsm_getMsg(updateMsgKey) + "\n"
        list_update.sort()
        for doc in list_update:
            print doc

    if len(list_delete) > 0:
        print "\n" + wsm_getMsg(delMsgKey) + "\n"
        list_delete.sort()
        for doc in list_delete:
            print doc


"""
Get the RepositoryCommands object used for authoring commands.

@return: RepositoryCommands object
"""
def wsm_getRCS():

    global wsm_rcs
    global wsm_mbs

    # If the stored wsm_mbs is different from the current one, then the client
    # might have reconnected, so the DocumentManager JMX proxy needs to be refreshed.
    if wsm_rcs is None or wsm_mbs != ora_mbs.getMbsInstance():
        beanObjName = wsm_getMBeanObjectName("oracle.wsm:*,name=WSMDocumentManager,type=Repository")
        idm = JMX.newMXBeanProxy(ora_mbs.getMbsInstance(), beanObjName, IDocumentManager)

        if wsm_rcs is None:
            wsm_rcs = RepositoryCommands(idm)
        else:
            wsm_rcs.setDocumentManager(idm)

        #Update the cached wsm_mbs object
        wsm_mbs = ora_mbs.getMbsInstance()

    return wsm_rcs


"""
Walk the server to get the list of all policy subjects
and their relevant information including the list of
direct attachments.

@return - List of dictionaries where each dictionary
          contains information about a specific endpoint.
"""
def wsm_walk(client="false"):

    # List of PolicySubjects
    policySubjectList = []

    #Get webServiceList
    if client == "false":
        webServiceList = wsm_listWebServices()
    else:
        webServiceList = wsm_listWebServiceClients()

    if webServiceList is None:
        return policySubjectList

    applicationPaths = webServiceList.keySet()

    for applicationPath in applicationPaths:
        #List of all webservices in each application
        webServices = webServiceList.get(applicationPath)

        if webServices is None:
            continue

        for webServiceArray in webServices:
            #Get the Module Name and Module Type
            webService = webServiceArray[0]
            moduleType = webServiceArray[1]
            moduleName = webServiceArray[2]

            # Get the Port
            if client == "false":
                portList = wsm_listWebServicePorts(applicationPath, webService, moduleType, moduleName)
            else:
                portList = wsm_listWebServiceClientPorts(applicationPath, webService, moduleType, moduleName)

            for port in portList:

                # Get the Bean Name for Bean Operations
		beanObjName = ObjectName(port[1])
                # Get the Resource Pattern Attribute
                resourcePattern = wsm_getMBeanAttribute(beanObjName, "PolicySubjectResourcePattern")

                # Get List of Direct Attachments
                directAttachments = wsm_getDirectAttachments(beanObjName)

                dict = {}
                dict['APPLICATION_PATH'] = applicationPath
                dict['WEBSERVICE'] = webService
                dict['MODULE_TYPE'] = moduleType
                dict['MODULE_NAME'] = moduleName
                dict['PORT'] = port[0]
                dict['DIRECT_ATTACHMENTS'] = directAttachments
                dict['RESOURCE_PATTERN'] = resourcePattern
                dict['OBJECT_NAME'] = beanObjName

                #Add the information to the List.
                policySubjectList.append(dict)

    return policySubjectList


"""
Get the list of Directly attached policies for the given endpoint.

@param beanObjName - The endpoint identified by the MBean Object Name.
@return - List of directly attached policies.
"""
def wsm_getDirectAttachments(beanObjName):

    directAttachments = wsm_getMBeanAttribute(beanObjName, "PolicyReferences")
    directAttachmentList = []

    if directAttachments == None:
        return directAttachmentList

    for directAttachment in directAttachments:
        daDict = wsm_getDictfromTabularData(directAttachment)
        policyName = daDict['URI']

        #Get Config Overrides
        try:
            configOverride = wsm_invokeMBeanOperation(beanObjName, "getPolicyOverride", [policyName], ['java.lang.String'])
            coDict = wsm_getDictfromTabularData(configOverride)
            daDict['CONFIG_OVERRIDE'] = coDict
        except java_lang_Exception, ex:
            if isinstance(ex, javax_management_RuntimeMBeanException) or isinstance(ex.getCause(), javax_management_RuntimeMBeanException):
               daDict['CONFIG_OVERRIDE'] = ''
            else:
               ora_util.raiseScriptingException(ex)
        directAttachmentList.append(daDict)

    return directAttachmentList


"""
Get a list of policies which are potential candidates to be detached.
@param effectivePolicies - List of policies returned by IAlgorithmProcessor
@param directAttachments - List of directly attached policies of an endpoint
@return List of policies which can be detached.
"""
def wsm_getDetachablePolicies(effectivePolicies, directAttachments):
    detachablePolicies = []
    coPolicies = []
    nonMatchingPolicies = []
    detachablePolicySourceList = []
    references = 0

    for da in directAttachments:
        policyURI = da['URI']

        # Output each attachment.
        references = references + 1
        if references == 1:
            print wsm_getMsg("DISPLAY_REFERENCE_1", [wsm_getMsg("DIRECT_ATTACHMENT", [da['category'], da['URI'], da['enabled']])])
        else:
            print wsm_getMsg("DISPLAY_REFERENCE_N", [wsm_getMsg("DIRECT_ATTACHMENT", [da['category'], da['URI'], da['enabled']])])

        # Ignore disabled attachments.
        if da['enabled'] != "true":
            continue

        policykeys = effectivePolicies.keySet()
        for policysource in policykeys:
            #Check if a global policy set has a corresponding attachments
            if policysource.startswith(policyURI) and not policysource.endswith("#direct"):
               policySourceValue = effectivePolicies.get(policysource)
               valueEntries = policySourceValue.split('|')
               polSetStatus = valueEntries[0]
               polRefStatus = valueEntries[2]
               if 'enabled' == polSetStatus and 'enabled' == polRefStatus:
               	  detachablePolicies.append(policyURI)
                  detachablePolicySourceList.append(policysource)

            #Check if returned map does not contains this direct attachment. This means, no matching
            # attachment found in the global policy set(s)
            elif not policysource.startswith(policyURI):
               nonMatchingPolicies.append(policyURI)

            # Check if there were config overrides for this direct attachment.
            elif len(da['CONFIG_OVERRIDE']) > 0:
               coPolicies.append(policyURI)
               # Display overrides
               keys = da['CONFIG_OVERRIDE'].keys()
               for key in keys:
                   value = da['CONFIG_OVERRIDE'].get(key)
                   print wsm_getMsg("DISPLAY_OVERRIDE", [key, value])

    # Show migratable attachments.
    for globalPolicySource in detachablePolicySourceList:
        policyEntry = globalPolicySource.split('|')
        policyName = policyEntry[0]
        policySetName = policyEntry[1]
        value = effectivePolicies.get(globalPolicySource)
        policyStatusEntry = value.split('|')
        referenceStatus = policyStatusEntry[2]
        references = references + 1
        if references == 1:
            print wsm_getMsg("DISPLAY_REFERENCE_1", [
                          wsm_getMsg("GLOBAL_ATTACHMENT", [
                                  wsm_getMsg("DIRECT_ATTACHMENT", [
                                          policySetName, 
                                          policyName, 
                                          wsm_getMsg(referenceStatus)])])])
        else:
            print wsm_getMsg("DISPLAY_REFERENCE_N", [
                          wsm_getMsg("GLOBAL_ATTACHMENT", [
                                  wsm_getMsg("DIRECT_ATTACHMENT", [
                                          policySetName, 
                                          policyName, 
                                          wsm_getMsg(referenceStatus)])])])


    return detachablePolicies,coPolicies,nonMatchingPolicies


"""
Detach a policy from an endpoint.

@param beanObjName - MBean object name identifying the endpoint.
@param policyURI - URI of the policy to be detached.
"""
def wsm_detachPolicy(beanObjName, policyURI):
    try:
        wsm_invokeMBeanOperation(beanObjName, "removePolicyReference", [policyURI], ['java.lang.String'])
    except:
        # print a warning as the process should not be stopped.
        print wsm_getMsg('POLICY_DETACH_ERROR_MSG', [policyURI])
    else:
        print wsm_getMsg('POLICY_DETACH_DONE_MSG', [policyURI])


"""
Get a list of all JRF Web Services.

@return - List of all the webservices
"""
def wsm_listWebServices():

    try:
        lws = ListWebServices(ora_mbs.getMbsInstance())
        #Message Level of 4 supresses any messages from being printed on the screen.
        lws.setMessageLevel(4)
        retValue = lws.execute(None, None)

    except java_lang_Exception, ex:
        raise ora_util.raiseScriptingException(ex)

    return retValue


"""
Get a list of all JRF Web Service Clients

@return - List of all webservice Clients
"""
def wsm_listWebServiceClients():

    try:
        lwr = ListWebServiceRefs(ora_mbs.getMbsInstance())
        #Message Level of 4 supresses any messages from being printed on the screen.
        lwr.setMessageLevel(4)
        retValue = lwr.execute(None, None)

    except java_lang_Exception, ex:
        raise ora_util.raiseScriptingException(ex)

    return retValue


"""
Get a list of all Web Service Ports for a Web Service
@param application - The name of the application.
@param serviceName - The WebService name of the application or composite
@param moduleType - The module type can be web or soa
@param moduleName - The web module name or SOA composite name.

@return List of all ports on this Web Service.
"""
def wsm_listWebServicePorts(application, serviceName, moduleType, moduleName):

    try:
        lwsp = ListWebServicePorts(ora_mbs.getMbsInstance())
        #Message Level of 4 supresses any messages from being printed on the screen.
        lwsp.setMessageLevel(4)
        retValue = lwsp.execute(application, serviceName, moduleType, moduleName)

    except java_lang_Exception, ex:
        raise ora_util.raiseScriptingException(ex)

    return retValue


"""
Get a list of all Web Service Client Ports for a Web Service
@param application - The name of the application.
@param serviceRefName - The WebService client name of the application or composite name
@param moduleName - The web module name or SOA composite name.
@param moduleType - The module type can be web or soa

@return List of all ports on this Web Service.
"""
def wsm_listWebServiceClientPorts(application, serviceRefName, moduleType, moduleName):

    try:
        lwrp = ListWebServiceRefPortInfos(ora_mbs.getMbsInstance())
        #Message Level of 4 supresses any messages from being printed on the screen.
        lwrp.setMessageLevel(4)
        retValue = lwrp.execute(application, serviceRefName, moduleType, moduleName)
    except java_lang_Exception, ex:
        raise ora_util.raiseScriptingException(ex)

    return retValue

"""
Main control loop for the migration
"""
def wsm_process(mode, policySubjectList, iap):

    preview_mode = wsm_getMsg("PREVIEW_MODE")
    prompt_mode = wsm_getMsg("PROMPT_MODE")
    force_mode = wsm_getMsg("FORCE_MODE")

    for policySubject in policySubjectList:
        # Need to create a java.util.ArrayList instead of a normal list,
        # because WAS is not able to interpret the calculateEffectivePolicies method correctly
        # if python list is used.
        daList = ArrayList()

        for da in policySubject['DIRECT_ATTACHMENTS']:
            if da['enabled'] == "true" and len(da['CONFIG_OVERRIDE']) > 0 :
                daList.add(da['URI'])

        try:
            if wsmdebug:
                print policySubject['RESOURCE_PATTERN'], daList

            effectivePolicies = iap.calculateEffectivePolicies(policySubject['RESOURCE_PATTERN'], daList)

            if wsmdebug:
                print effectivePolicies
        except java_lang_Exception, ex:
            raise ex

        # Print information related to the end point
        wsm_display(policySubject)
        detachablePolicies,coPolicies,nonMatchingPolicies = wsm_getDetachablePolicies(effectivePolicies, policySubject['DIRECT_ATTACHMENTS'])
        print ""

        if len(detachablePolicies) == 0:
            continue

        for detachablePolicy in detachablePolicies:
            # Python does not suppport switch statement.
            # Using iterative if else statements.

            if mode == preview_mode:
                print wsm_getMsg("POLICY_DETACH_INPUT_MSG", [detachablePolicy, wsm_getMsg("PROMPT_MODE_OPTION_NO")])
                # Do nothing. All relevant information is already printed.
                continue
            elif mode == force_mode:
                print wsm_getMsg("POLICY_DETACH_INPUT_MSG", [detachablePolicy, wsm_getMsg("PROMPT_MODE_OPTION_YES")])
                # Take the action.
                wsm_detachPolicy(policySubject['OBJECT_NAME'], detachablePolicy)
            elif mode == prompt_mode:
                correctMode = "false"
                while correctMode == "false":
                    correctMode = "true"
                    #Prompt for user input.
                    userOption = raw_input(wsm_getMsg("POLICY_DETACH_INPUT_MSG", [detachablePolicy, ""]))
                    userOption = userOption.lower()
                    if userOption == wsm_getMsg("PROMPT_MODE_OPTION_YES"):
                        wsm_detachPolicy(policySubject['OBJECT_NAME'], detachablePolicy)
                    elif userOption == wsm_getMsg("PROMPT_MODE_OPTION_NO"):
                        continue
                    elif userOption == wsm_getMsg("PROMPT_MODE_OPTION_ABORT"):
                        print "\n" + wsm_getMsg("ABORT_MSG")
                        return
                    #Print error message for unrecognized input.
                    else:
                        print wsm_getMsg("PROMPT_MODE_INCORRECT_OPTION",
                                         [userOption,
                                          wsm_getMsg("PROMPT_MODE_OPTION_YES"),
                                          wsm_getMsg("PROMPT_MODE_OPTION_NO"),
                                          wsm_getMsg("PROMPT_MODE_OPTION_ABORT")])
                        correctMode = "false"

        print ""


"""
---------------------------------------------------------------------
WLS Utility Methods
The following methods are specific to WLST/WLS
---------------------------------------------------------------------
"""

"""
Change to Domain Runtime Tree and return the old tree
@return - old tree
"""
def wsm_gotoDomainRuntime():

    if not ora_mbs.isWebLogic():
        return

    currentNode = pwd()
    if (currentNode.find('domainRuntime') == -1):
        ctree = currentTree()
        domainRuntime()
        ora_mbs.setMbs(mbs)
        return ctree
    else:
        return None


"""
Return to the old tree and update the mbs object.

@param oldTree - Tree to be returned back to.
"""
def wsm_backtoOldTree(oldTree = None):

    if not ora_mbs.isWebLogic():
        return

    if (oldTree != None):
        oldTree()
        #Return the state of mbs
        ora_mbs.setMbs(mbs)


"""
---------------------------------------------------------------------
Methods specific for MBeans
---------------------------------------------------------------------
"""

"""
Query the MBean Server and return the Object Name if found.
@param query - pattern to query the mbean server.

@return Object name of the MBean if found, else None.
"""
def wsm_getMBeanObjectName(query):

    beanObjName = ObjectName(query)

    beans = ora_mbs.queryMBeans(beanObjName,None)

    if beans is None or beans.size() == 0:
        raise Exception, wsm_getMsg("MBEAN_NOT_FOUND",[query])
    else:
        objectName = beans.iterator().next().getObjectName()

    return objectName


"""
Get the value of a particular MBean attribute

@param beanObjName - The object name identifying the MBean
@param attributeName - Name of the attribute whose value is required.

@return The value of the MBean attribute.
"""
def wsm_getMBeanAttribute(beanObjName, attributeName):
    attributeValue = None

    try:
        attributeValue = ora_mbs.getAttribute(beanObjName, attributeName)
    except java_lang_Exception, ex:
        raise ex

    return attributeValue


"""
Invoke a particular MBean operation.
@param beanObjName - The object name identifying the MBean
@param operationName - Name of the operation to be invoked
@param params - List of parameters required for the operation
@param signature - List of types forming the signature for the operation.
"""
def wsm_invokeMBeanOperation(beanObjName,operationName,params,signature):

    returnVal = None

    from java.lang import Object
    from java.lang import String

    try:
        operation_params = array(params, Object)
        operation_signature = array(signature, String)
        returnVal = ora_mbs.invoke(beanObjName, operationName, operation_params, operation_signature)
    except java_lang_Exception, ex:
        raise ex

    return returnVal


"""
Get a python dictionary from the openmbean type tabular data

@param tabData - The tabular data obtained from invoking the MBean operation
@return - dictionary holding tabular data values.
"""
def wsm_getDictfromTabularData(tabData):
    dict = {}

    if tabData == None:
        return dict

    #Get the Collection of CompositeData
    rows = tabData.values()
    for row in rows:
        value = row.values().toArray()
        dict[value[0]] = value[1]

    return dict


"""
---------------------------------------------------------------------
General Utility Methods
---------------------------------------------------------------------
"""

"""
Verify is the client is connected to the server or not.
For WLS, need to call the setMbs to set the mbs variable.
@param msg - The message to be printed in case the client is
            not connected to the server.
"""
def wsm_isConnected(msg=None):

    #Set the mbs for weblogic.
    if ora_mbs.isWebLogic():
        ora_mbs.setMbs(mbs)

    status = ora_mbs.isConnected()
    if msg is not None and not status:
        print msg

    return status


"""
Given the key, return the corresponding message from the message bundle.
If the key is not found, return the passed key as is.

@param key - key used to obtain the corresponding message.
@param args - List of arguments to format the message
"""
def wsm_getMsg(key, args=None):
    msg = key
    global wsm_rb

    try:
        if wsm_rb.containsKey(key):
            pattern = wsm_rb.getString(key)

            if args is None:
                msg = pattern
            else:
                msg = MessageFormat.format(pattern, args)
    except:
        pass

    return msg


"""
Get a boolean object from the argument.

@param arg - value to be converted to boolean
@return the corresponding boolean value
"""
def wsm_getBooleanFromArg(arg):
    if arg is None:
        return Boolean('false')

    # For WLST, since True and False are defined and are integers.
    if type(arg) == type(1):
        return Boolean(arg)

    # For WAS, since the argument is a string.
    if type(arg) == type("a"):
        if arg.lower() == 'true':
            return Boolean('true')
        else:
            return Boolean('false')

    return Boolean('false')


"""
Display information about the endpoint.

@param policySubject: Map containing all the values to be displayed.
"""
def wsm_display(policySubject):
    print wsm_getMsg("DISPLAY_POLICY_SUBJECT_HEADER")
    print wsm_getMsg("DISPLAY_APPLICATION_PATH", [policySubject['APPLICATION_PATH']])
    print wsm_getMsg("DISPLAY_WEBSERVICE_NAME", [policySubject['WEBSERVICE']])
    print wsm_getMsg("DISPLAY_MODULE_TYPE", [policySubject['MODULE_TYPE']])
    print wsm_getMsg("DISPLAY_MODULE_NAME", [policySubject['MODULE_NAME']])
    print wsm_getMsg("DISPLAY_PORT", [policySubject['PORT']])
    if wsmdebug:
        print wsm_getMsg("DISPLAY_RESOURCE_PATTERN", [policySubject['RESOURCE_PATTERN']])
        print wsm_getMsg("DISPLAY_OBJECT_NAME", [policySubject['OBJECT_NAME']])

