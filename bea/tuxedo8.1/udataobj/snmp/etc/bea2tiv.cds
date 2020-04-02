CLASS Tux_Event
  SELECT
    1: ATTR(=, "tuxEventsName" ) ;
    2: ATTR(=, "tuxEventsLmid" ) ;
    3: ATTR(=, "tuxEventsTime" ) ;
    4: ATTR(=, "tuxEventsDescription" ) ;
    5: ATTR(=, "tuxEventsClass" ) ;
    6: ATTR(=, "tuxEventsUlogCat" ) ;
    7: ATTR(=, "tuxEventsUlogMsgNum" ) ;
    8: ATTR(=, "beaDomainID" ) ;
    9: ATTR(=, "beaDomainKey" ) ;
   10: ATTR(=, "beaLogicalAgentName" ) ;
  MAP
    source = "TUXEDO";
    enterprise = "tuxedo";
    sub_source = $V1;
    hostname = $V2; 
    date = $V3;
    msg = $V4; 
    class = $V5; 
    ulogcat = $V6; 
    ulogmsgnum = $V7; 
    domainid = $V8;
    ipckey = $V9;
    agentname = $V10;
END
