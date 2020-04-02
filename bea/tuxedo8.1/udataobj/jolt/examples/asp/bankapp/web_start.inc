<%
'//
'//	Copyright (c) 1998 BEA Systems, Inc.  All rights reserved
'//	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
'//	The copyright notice above does not evidence any actual or intended
'//	publication of such source code.
'//
'//
'// Create the session pool.
'// Customers should modify the bankapp.properties file for the hosts and
'// ports for the primary server addresses and the failover server addresses,
'// the user authentication information as well as the minimum and maximum
'// number of sessions.
'//

Sub web_start(propfile)
    '// Get the bankapp.properties file
    Set config = Server.CreateObject("BEAJOLTPOOL.AspPoolManagerConfig")
    Set props = config.loadProperties(Server.MapPath(".") & "\" & propfile)
    Call config.startup(props)

    Set Application("mgr") = config.getSessionPoolManager()
End Sub
%>
