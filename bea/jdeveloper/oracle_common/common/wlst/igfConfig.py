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

import igfConfig_handler as igfhandler
import ora_mbs


def addIGFCommandHelp():
  igfhandler.addIGFCommandHelpImpl();

addIGFCommandHelp()


#######################################################
# Helper methods
#######################################################
def igfConfig_gotoDomainRuntime():
  currentNode = pwd()
  if (currentNode.find('domainRuntime') == -1):
    ctree = currentTree()
    domainRuntime()
    ora_mbs.setMbs(mbs)
    return ctree
  else:
    return None



#######################################################
# This function lists all Entity Names in a CARML
#######################################################
def listAllIgfEntityNames(appName):
  igfConfig_gotoDomainRuntime()
  igfhandler.listAllIgfEntityNamesImpl(appName)


#######################################################
# This function lists all the interactions in a CARML
#######################################################
def listAllIgfInteractions(appName):
  igfConfig_gotoDomainRuntime()
  igfhandler.listAllIgfInteractionsImpl(appName)


#########################################################
# This function adds the attribute to CARML & Mapping file
#########################################################
def addIgfAttribute(appName, attrName, targetName, dataType, entities, interactions, isAddToFilter, params, paramVals):
  igfConfig_gotoDomainRuntime()
  igfhandler.addIgfAttributeImpl(appName, attrName, targetName, dataType, entities, interactions, isAddToFilter, params, paramVals)


##############################################################################
# This function adds the attribute reference to the interacation(s) in a CARML
##############################################################################
def addIgfAttributeToInteraction(appName, attrName, interaction, entity):
  igfConfig_gotoDomainRuntime()
  igfhandler.addIgfAttributeToInteractionImpl(appName, attrName, interaction, entity)


##############################################################
# This function deletes the attribute from CARML & Mapping file
##############################################################
def deleteIgfAttribute(appName, attrName):
  igfConfig_gotoDomainRuntime()
  igfhandler.deleteIgfAttributeImpl(appName, attrName)


##############################################################
# This function modifies the attribute mapping in Mapping file
##############################################################
def modifyIgfMapping(appName, entityName, attrName, newTargetName):
  igfConfig_gotoDomainRuntime()
  igfhandler.modifyIgfMappingImpl(appName, entityName, attrName, newTargetName)


