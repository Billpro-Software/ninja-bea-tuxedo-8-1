<!--
--	Copyright (c) 1998 BEA Systems, Inc.  All rights reserved
--	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
--	The copyright notice above does not evidence any actual or intended
--	publication of such source code.
-->

<%@ LANGUAGE = VBSCRIPT %>
<%
CONST INQUIRY	= 0
CONST DEPOSIT	= 1
CONST WITHDRAWAL= 2
CONST TRANSFER	= 3

If Not IsObject(Application("mgr")) Then
%>
	<HTML>
	<HEAD><TITLE>Error</TITLE></HEAD>
	<BODY><CENTER>
	<H2>Session Manager is not initialized</H2>
	<P>Make sure that you access the correct HTML
	</CENTER></BODY>
	</HTML>
<%
Elseif Request("SVCNAME") <> "" Then

	'// Select a session pool object
	Set pool = Application("mgr").getSessionPool("bankapp")

	'// Choose the response template
	If IsEmpty(Application("templates")) Then
		Set template = Server.CreateObject("BEAJOLTPOOL.AspTemplate")
	Else
		Select Case Request("SVCNAME")
		Case "INQUIRY"
			Set template = Application("templates")(INQUIRY)
		Case "DEPOSIT"
			Set template = Application("templates")(DEPOSIT)
		Case "WITHDRAWAL"
			Set template = Application("templates")(WITHDRAWAL)
		Case "TRANSFER"
			Set template = Application("templates")(TRANSFER)
		End Select
	End If

	'// Prepare template data from the input request
	Dim iodata(1)
	Set iodata(0) = Server.CreateObject("BEAJOLTPOOL.AspDataSet")
	Call iodata(0).importRequest()

	'// Call the TUXEDO service
	Set output = pool.call(Request("SVCNAME"), Null, Nothing)

	'// Prepare template data from the service output
	Set iodata(1) = output

	'// Display the HTML page using a template
	path = Application("templatedir")
	If (Not IsObject(output)) Or (output is Nothing) Then
		Call template.evalFile(path & "\nosession.temp", Null)
	Elseif output.noError() Then
		Call template.eval(iodata)
	Elseif output.applicationError() Then
		Call template.evalFile(path & "\error.temp", iodata)
	Else
		'// System error
		Dim errdata(0)
		Set errdata(0) = Server.CreateObject("BEAJOLTPOOL.AspDataSet")
		Call errdata(0).setValue("ERRNO", output.getError())
		Call errdata(0).setValue("ERRMSG", output.getStringError())
		Call template.evalFile(path & "\syserror.temp", errdata)
	End If
End If
%>
