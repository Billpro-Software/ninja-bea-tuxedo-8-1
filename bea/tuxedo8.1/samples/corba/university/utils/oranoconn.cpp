/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*      Copyright (c) 1998 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/


// MODULE NAME:
//
//    oranoconn.cpp
//
// FACILITY:
//
//    samples 
//
// ABSTRACT:
//
//    This source stubs the sqlConnect() call in the case where we use the XA RM
//
//    We either link in
//        oralocconn        if using a local database
//        oraremconn        if using a remote database instance
//        oranoconn         if using an XA RM to handle our transactions
//
// CLASSES CONTAINED IN THIS MODULE:
//    
//
// AUTHORS:     Mark Scanlon, Martin Varela
//              
// CREATION DATE: 23-Mar-1998
//
//

#include "samplesdbsql.h"

void sqlConnect()
{
    // Using an XA RM to connect and handle our transactions
}
