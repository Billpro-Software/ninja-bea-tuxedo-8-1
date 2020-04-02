<%
'//
'//	Copyright (c) 1998 BEA Systems, Inc.  All rights reserved
'//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
'//	The copyright notice above does not evidence any actual or intended
'//	publication of such source code.
'//
'//
'// This VBScript function is to cache the templates for BankApp.
'//

Dim templates(3)
CONST INQUIRY	    = 0
CONST DEPOSIT	    = 1
CONST WITHDRAWAL    = 2
CONST TRANSFER	    = 3

Sub web_cacheTemplates()
    If IsEmpty(Application("templates")) Then
	Application.Lock()
        If IsEmpty(Application("templates")) Then
	    '// Get full path to template directory and save it
	    Application("templatedir") = Server.MapPath("templates") & "\"
	    path = Application("templatedir")

	    '// Cache the BankApp templates for INQUIRY, DEPOSIT,
	    '// WITHDRAWAL and TRANSFER
	    Set templates(INQUIRY) = Server.CreateObject("BEAJOLTPOOL.AspTemplate")
	    Call templates(INQUIRY).load(path & "inquiry.temp")

	    Set templates(DEPOSIT) = Server.CreateObject("BEAJOLTPOOL.AspTemplate")
	    Call templates(DEPOSIT).load(path & "deposit.temp")

	    Set templates(WITHDRAWAL) = Server.CreateObject("BEAJOLTPOOL.AspTemplate")
	    Call templates(WITHDRAWAL).load(path & "withdrawal.temp")

	    Set templates(TRANSFER) = Server.CreateObject("BEAJOLTPOOL.AspTemplate")
	    Call templates(TRANSFER).load(path & "transfer.temp")

	    Application("templates") = templates
	End If
	Application.Unlock()
    End If
End Sub
%>
