# Copyright (c) 2009, 2010, Oracle and/or its affiliates. All rights reserved. 
################################################################################
# Caution: This file is part of the WLST implementation. Do not edit or move   #
# this file because this may cause WLST commands and scripts to fail. Do not   #
# try to reuse the logic in this file or keep copies of this file because this #
# could cause your WLST scripts to fail when you upgrade to a different version# 
# of WLST.                                                                     #
################################################################################

import sys

from sets import ImmutableSet as frozenset
required = frozenset(['-appStripe', '-name', '-resourceName', '-resourceType', '-actions'])
optional = frozenset(['-displayName','-description'])
import jpsCmdHelp

argmap = jpsCmdHelp.verifyArgs(required, optional, sys.argv[1:])

if argmap == None:
    jpsCmdHelp.createEntitlementHelp()
    exit()

appStripe = argmap['appStripe']
name = argmap['name']
resourceName = argmap['resourceName']
resourceType = argmap['resourceType']
actions = argmap['actions']
displayName = None
description = None

if 'displayName' in argmap:
        displayName = argmap['displayName']
if 'description' in argmap:
        description = argmap['description']
connect()
import Opss
Opss.createEntitlement(appStripe=appStripe, name=name, resourceName=resourceName,resourceType=resourceType, actions=actions, displayName=displayName, description=description)

