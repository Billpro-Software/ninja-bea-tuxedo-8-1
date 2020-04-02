//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

//	Copyright (c) 1995 Novell, Inc.	
//	  All Rights Reserved 	 	

//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	
//	Novell, Inc.                     			
//	The copyright notice above does not evidence any   	
//	actual or intended publication of such source code.	

// #ident	"@(#) samples/atmi/bankapp/nt/bankappd/bankappd.h	$Revision: 1.4 $"	

#ifndef NOWHAT
static  char    sccsid[] = "@(#) samples/atmi/bankapp/nt/bankappd/bankappd.h	$Revision: 1.4 $";
#endif

// bankappd.h : main header file for the BANKAPPD application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBankappdApp:
// See bankappd.cpp for the implementation of this class
//

class CBankappdApp : public CWinApp
{
public:
	CBankappdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankappdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBankappdApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

extern DWORD BankappServer(LPVOID parms);
