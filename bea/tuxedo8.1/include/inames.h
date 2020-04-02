/*	Copyright (c) 1997 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) objtm/include/inames.h	$Revision: 1.3 $" */


#ifndef _INAMES_H
#define _INAMES_H

#ifndef NOWHAT
static char h_inames[] = "@(#)iceberg:include/inames.h  $Revision: 1.3 $";
#endif

// +++++  Iceberg object-related names  +++++

const char* const WILDCARD	= "*";

const char* const COS_SVR	= ":CosSvr";

const char* const ICEBERG	= "TobjDomain";
const char* const FAC_KND	= "Factory";
const char* const SVC_KND	= "Service";

const char* const NS_NAM	= "NamingService";
const char* const NS_ID		= "TobjNamingService";
const char* const NS_INTF	= "IDL:beasys.com/Tobj/NamingContext:1.0";

const char* const LCS_FF_NAM	= "FactoryFinder";
const char* const LCS_FF_ID	= "TobjFactoryFinder";
const char* const LCS_FF_INTF	= "IDL:beasys.com/Tobj/FactoryFinder:1.0";

#endif  // _INAMES_H
