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
//    oradbconn.cpp
//
// FACILITY:
//
//    samples 
//
// ABSTRACT:
//
//    This source file provides access (connect) to an Oracle SQL database instance
//    We either link in
//        oradbconn         if using a local or remote database instance
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
    // Connect to the Oracle database instance

    sqlConnectDb();
}
