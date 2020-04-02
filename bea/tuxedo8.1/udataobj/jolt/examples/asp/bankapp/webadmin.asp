<!--
--	Copyright (c) 1998 BEA Systems, Inc.  All rights reserved
--	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
--	The copyright notice above does not evidence any actual or intended
--	publication of such source code.
-->
<%@ LANGUAGE = VBSCRIPT %>
<!--#INCLUDE FILE="web_admin.inc"-->
<!--#INCLUDE FILE="web_start.inc"-->

<%
'//
'// This is the code that serves the administrative commands.
'//
Select Case Request.QueryString("get")
	Case "Suspend"
		'// Suspend the session pool, so it won't accept any new requests
		Call web_suspend("bankapp")
	Case "Resume"
		'// Resume the session pool, so it will accept new requests
		Call web_resume("bankapp")
	Case "Stop"
		'// Stop the session pool, all connections in the pool terminates.
		Call web_stop("bankapp")
	Case "Start"
		'// Restart the session pool.
		Call web_start("bankapp.properties")
	Case "Increase"
		'// Increase the session pool by one.
		Call web_mod("bankapp", "poolSize", 1)
End Select
Call web_status("bankapp")
%>
