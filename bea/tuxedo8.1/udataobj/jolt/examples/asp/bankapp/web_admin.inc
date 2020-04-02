<%
'//
'//	Copyright (c) 1998 BEA Systems, Inc.  All rights reserved
'//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
'//	The copyright notice above does not evidence any actual or intended
'//	publication of such source code.
'//
'//
'// This file contains the generic VBScript functions to support the
'// administrative functions.  Typically, there is no need to modify
'// these functions unless the customers want to change the HTML output
'// of the session monitoring page.
'//

Sub web_initSessionMgr(propfile)
	If Not IsObject(Application("mgr")) Then
		Application.Lock()
		If Not IsObject(Application("mgr")) Then
			Call web_start(propfile)
		End If
		Application.Unlock()
	End If
End Sub

Sub web_stop(id)
	If IsObject(Application("mgr")) Then
		Call Application("mgr").stopSessionPool(id)
	End If
End Sub

Sub web_suspend(id)
	If IsObject(Application("mgr")) Then
		Call Application("mgr").suspendSessionPool(id, True)
	End If
End Sub

Sub web_resume(id)
	If IsObject(Application("mgr")) Then
		Call Application("mgr").suspendSessionPool(id, False)
	End If
End Sub

Sub web_mod( id, name, value )
	If IsObject(Application("mgr")) Then
		Set pool = Application("mgr").getSessionPool(id)
		If name = "poolSize" Then
			pool.setMaxConnections(pool.getMaxConnections()+value)
		End If
	End If
End Sub

Sub web_status(id)
%>
	<HTML>
	<HEAD><TITLE>Session Pool Statistics</TITLE></HEAD>
	<BODY>
<%
    	If IsObject(Application("mgr")) Then
		Set pool = Application("mgr").getSessionPool(id)
		If (Not IsObject(pool)) Or (pool is Nothing) Then
%>
			<H2>Invalid Session Pool ID</H2></BODY></HTML>
<%
			Exit Sub
		End If

		poolsize = CInt(pool.getMaxConnections())

		If pool.isSuspended() Then
			hdr = "Suspended Connection Status"
		Else
			hdr = "Active Connection Status" 
		End If
%>
		<CENTER><H2><%= hdr %></H2>
		<TABLE BORDER=1>
		<TR>
			<TD>&nbsp                                   </TD>
			<TD ALIGN=CENTER><B>Address		</B></TD>
			<TD ALIGN=CENTER><B>Status		</B></TD>
			<TD ALIGN=CENTER><B>In Transaction	</B></TD>
			<TD ALIGN=CENTER><B>Last Use Time	</B></TD>
			<TD ALIGN=CENTER><B>Total Rqsts		</B></TD>
			<TD ALIGN=CENTER><B>Pending Rqsts	</B></TD>
			<TD ALIGN=CENTER><B>Errors		</B></TD>
		</TR>
<%
		For i=0 To poolsize-1
			Set con = pool.getConnection(i)
			If (Not IsObject(con)) Or (con is Nothing) Then
				Call connection_row(i+1, "NO CONNECTION", _
					"<FONT COLOR=red>Dead</FONT>", _
					"No", "&nbsp;", "0", "0", "0")
			Else
				If con.isAlive() Then
					state = "<FONT COLOR=green>Alive</FONT>"
				Else
					state = "<FONT COLOR=red>Dead</FONT>"
				End If

				If con.inTransaction() Then
					intran = "Yes"
				Else
					intran = "No"
				End If

				Call connection_row(i+1, con.getAddr(), _
					state, intran, con.getAccessTime(), _
					con.getRequestCount(), _
					con.getUseCount(), _
					con.getErrorCount())
			End If
		Next
%>
		</TABLE>

		<FORM NAME=control ACTION=webadmin.asp METHOD=GET>
		<INPUT TYPE=submit NAME=get VALUE=Status>
		<INPUT TYPE=submit NAME=get VALUE=Suspend>
		<INPUT TYPE=submit NAME=get VALUE=Resume>
		<INPUT TYPE=submit NAME=get VALUE=Start>
		<INPUT TYPE=submit NAME=get VALUE=Increase>
		<FONT COLOR=red>
		<INPUT TYPE=submit NAME=get VALUE=Stop>
		</FONT>
		</FORM>

		</CENTER>
		</BODY>
		</HTML>
<%
	End If
End Sub

Sub connection_row(index, addr, state, intran, acctime, rqts, pending, errors)
%>
	<TR>
	<TD ALIGN=RIGHT> <%=index%>	</TD>
	<TD ALIGN=LEFT>  <%=addr%>	</TD>
	<TD ALIGN=CENTER><%=state%>	</TD>
	<TD ALIGN=CENTER><%=intran%>	</TD>
	<TD ALIGN=CENTER><%=acctime%>	</TD>
	<TD ALIGN=CENTER><%=rqts%>	</TD>
	<TD ALIGN=CENTER><%=pending%>	</TD>
	<TD ALIGN=CENTER><%=errors%>	</TD>
	</TR>
<%
End Sub
%>
