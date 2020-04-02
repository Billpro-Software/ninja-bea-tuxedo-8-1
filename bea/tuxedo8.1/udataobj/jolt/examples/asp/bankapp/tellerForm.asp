<!--
--	Copyright (c) 1998 BEA Systems, Inc.  All rights reserved
--	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
--	The copyright notice above does not evidence any actual or intended
--	publication of such source code.
-->

<%@ LANGUAGE = VBSCRIPT %>
<!--#INCLUDE FILE="web_admin.inc"-->
<!--#INCLUDE FILE="web_start.inc" -->
<!--#INCLUDE FILE="web_templates.inc"-->

<%
'// Initialize the session manager and cache templates
Call web_initSessionMgr("bankapp.properties")
Call web_cacheTemplates()
%>

<HTML>
<HEAD>
<TITLE>Banking Demo</TITLE>
</HEAD>
<BODY>
<CENTER>
<H2>Please Select One of the Banking Transactions:</H2>
<FORM NAME="teller">
<INPUT TYPE="button" VALUE="Inquiry" onClick="window.location='inquiryForm.htm'">
<BR>
<INPUT TYPE="button" VALUE="Deposit" onClick="window.location='depositForm.htm'">
<BR>
<INPUT TYPE="button" VALUE="Withdrawal" onClick="window.location='withdrawalForm.htm'">
<BR>
<INPUT TYPE="button" VALUE="Transfer" onClick="window.location='transferForm.htm'">
</FORM>
</CENTER>
<P>
<CENTER>
<FORM NAME="status" ACTION="webadmin.asp" METHOD="GET">
<INPUT TYPE="submit" NAME=get VALUE="Status">
</FORM>
</CENTER>
</BODY>
</HTML>
