################################################################
# Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################

from java.lang import Exception
from java.lang import Object
from java.lang import String
import jarray
import ora_help
import ora_mbs

TYPE_STRING = "java.lang.String"


###########################
# Helper Methods
###########################

#MBean name is different for diff app servers, so modify the name accordingly
def getIGFMBeanObject(name):
  if(ora_mbs.isWebSphereND() == 1):
    on = AdminControl.completeObjectName(name+',process=dmgr,*')
  elif(ora_mbs.isWebSphereAS() == 1):
    on = AdminControl.completeObjectName(name+',*')
  else:
    on = name
  objectName = ora_mbs.makeObjectName(on)
  return objectName



##############################
# Command Implementation
##############################

# This function lists all Entity Names in a CARML
def listAllIgfEntityNamesImpl(appName):
  carmlObj = getIGFMBeanObject('com.oracle.igf:name=CarmlConfig_' + appName + ',type=Xml')
  objs1 = jarray.array([], Object)
  sigs1 = jarray.array([], String)
  interactions = ora_mbs.invoke(carmlObj, 'listAllEntityNames', objs1, sigs1)
  length = len(interactions)
  print '%-7s\n' % ('EntityNames')
  for i in range(length):
     print '%-7s' % (interactions[i])


# This function lists all the interactions in a CARML
def listAllIgfInteractionsImpl(appName):
  carmlObj = getIGFMBeanObject('com.oracle.igf:name=CarmlConfig_' + appName + ',type=Xml')
  objs1 = jarray.array([], Object)
  sigs1 = jarray.array([], String)
  interactions = ora_mbs.invoke(carmlObj, 'listAllInteractions', objs1, sigs1)
  length = len(interactions)
  print '%-25s\t%-20s\t%-7s\n' % ('InteractionName','InteractionType','EntityName')
  for i in range(length):
     splitVals = interactions[i].split(",")
     print '%-25s\t%-20s\t%-7s' % (splitVals[0], splitVals[1], splitVals[2])


# This function adds the attribute to CARML & Mapping file
def addIgfAttributeImpl(appName, attrName, targetName, dataType, entities, interactions, isAddToFilter, params, paramVals):
  carmlObj = getIGFMBeanObject('com.oracle.igf:name=CarmlConfig_' + appName + ',type=Xml')
  mappingObj = getIGFMBeanObject('com.oracle.igf:name=MappingConfig_' + appName + ',type=Xml')
  objs1 = jarray.array([attrName, targetName, dataType, entities, interactions, isAddToFilter, params, paramVals], Object)
  sigs1 = jarray.array([TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING, TYPE_STRING], String)
  res = ora_mbs.invoke(carmlObj, 'addAttributeWLST', objs1, sigs1)
  res = ora_mbs.invoke(mappingObj, 'addAttributeWLST', objs1, sigs1)


# This function adds the attribute reference to the interacation(s) in a CARML
def addIgfAttributeToInteractionImpl(appName, attrName, interaction, entity):
  carmlObj = getIGFMBeanObject('com.oracle.igf:name=CarmlConfig_' + appName + ',type=Xml')
  objs1 = jarray.array([attrName, interaction, entity], Object)
  sigs1 = jarray.array([TYPE_STRING, TYPE_STRING, TYPE_STRING], String)
  res = ora_mbs.invoke(carmlObj, 'addAttributeToInteraction', objs1, sigs1)


# This function deletes the attribute from CARML & Mapping file
def deleteIgfAttributeImpl(appName, attrName):
  carmlObj = getIGFMBeanObject('com.oracle.igf:name=CarmlConfig_' + appName + ',type=Xml')
  mappingObj = getIGFMBeanObject('com.oracle.igf:name=MappingConfig_' + appName + ',type=Xml')
  objs1 = jarray.array([attrName], Object)
  sigs1 = jarray.array([TYPE_STRING], String)
  ora_mbs.invoke(carmlObj, 'deleteAttribute', objs1, sigs1)
  ora_mbs.invoke(mappingObj, 'deleteAttribute', objs1, sigs1)


# This function modifies the attribute mapping in Mapping file
def modifyIgfMappingImpl(appName, entityName, attrName, newTargetName):
  mappingObj = getIGFMBeanObject('com.oracle.igf:name=MappingConfig_' + appName + ',type=Xml')
  objs1 = jarray.array([entityName, attrName, newTargetName], Object)
  sigs1 = jarray.array([TYPE_STRING, TYPE_STRING, TYPE_STRING], String)
  try :
    res = ora_mbs.invoke(mappingObj, 'modifyMapping', objs1, sigs1)
  except MBeanException, e :
    print e.getMessage() + "\n"


def addIGFCommandHelpImpl():
  try:
    ora_help.addHelpCommandGroup("igfconfig", "igfconfig_wlst")
    ora_help.addHelpCommand("listAllIgfInteractions", "igfconfig")
    ora_help.addHelpCommand("listAllIgfEntityNames", "igfconfig")
    ora_help.addHelpCommand("deleteIgfAttribute", "igfconfig")
    ora_help.addHelpCommand("modifyIgfMapping", "igfconfig")
    ora_help.addHelpCommand("addIgfAttributeToInteraction", "igfconfig")
    ora_help.addHelpCommand("addIgfAttribute", "igfconfig")
  except (Exception), exc:
    return

