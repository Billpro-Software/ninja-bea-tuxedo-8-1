      *
      *	(c) 2003 BEA Systems, Inc. All Rights Reserved.
      *
      * Copyright (c) 1992 USL
      * All rights reserved
      *
      * THIS IS UNPUBLISHED PROPRIETARY
      * SOURCE CODE OF USL
      * The copyright notice above does not
      * evidence any actual or intended
      * publication of such source code.
      *
      * #ident	"@(#) samples/atmi/CSIMPAPP/CSIMPCL.cbl	$Revision: 1.5 $" 
      * static	char	sccsid[] = "@(#) samples/atmi/CSIMPAPP/CSIMPCL.cbl	$Revision: 1.5 $";
      *
        IDENTIFICATION DIVISION.
        PROGRAM-ID. CSIMPCL.
        AUTHOR. TUXEDO DEVELOPMENT.
        ENVIRONMENT DIVISION.
        CONFIGURATION SECTION.
        WORKING-STORAGE SECTION.
      *****************************************************
      * Tuxedo definitions
      *****************************************************
        01  TPTYPE-REC. 
        COPY TPTYPE.
      *
        01  TPSTATUS-REC. 
        COPY TPSTATUS.
      *
        01  TPSVCDEF-REC. 
        COPY TPSVCDEF.
      *
        01  TPINFDEF-REC VALUE LOW-VALUES.
        COPY TPINFDEF.
      *****************************************************
      * Log messages definitions
      *****************************************************
        01  LOGMSG.
            05  FILLER		PIC X(8) VALUE  "CSIMPCL:".
            05  LOGMSG-TEXT	PIC X(50).
        01  LOGMSG-LEN		PIC S9(9)  COMP-5.
      *
        01  USER-DATA-REC	PIC X(75).
        01  SEND-STRING		PIC X(100) VALUE SPACES.
        01  RECV-STRING		PIC X(100) VALUE SPACES.
      ******************************************************
      * Start program with command line args
      ******************************************************
        PROCEDURE DIVISION.
        START-CSIMPCL.
          MOVE LENGTH OF LOGMSG TO LOGMSG-LEN. 
          ACCEPT SEND-STRING FROM COMMAND-LINE.
          DISPLAY "SEND-STRING:" SEND-STRING.
      
          MOVE "Started" TO LOGMSG-TEXT.
          PERFORM DO-USERLOG.
      
          PERFORM DO-TPINIT. 
          PERFORM DO-TPCALL. 
          DISPLAY "RECV-STRING:" RECV-STRING.
          PERFORM DO-TPTERM. 
          PERFORM EXIT-PROGRAM. 
      
      *****************************************************
      * Now register the client with the system.
      *****************************************************
        DO-TPINIT.
          MOVE SPACES TO USRNAME.
          MOVE SPACES TO CLTNAME.
          MOVE SPACES TO PASSWD.
          MOVE SPACES TO GRPNAME.
          MOVE ZERO TO DATALEN.
          SET TPU-DIP TO TRUE.
      *
          CALL "TPINITIALIZE" USING TPINFDEF-REC 
                USER-DATA-REC 
                TPSTATUS-REC.      
      
          IF NOT TPOK
                MOVE "TPINITIALIZE Failed" TO LOGMSG-TEXT
                PERFORM DO-USERLOG
                PERFORM EXIT-PROGRAM
          END-IF.
      
      *****************************************************
      *  Issue a TPCALL
      *****************************************************
        DO-TPCALL.
          MOVE 100 TO LEN.
          MOVE "STRING" TO REC-TYPE.
      
          MOVE "CSIMPSRV" TO SERVICE-NAME.
          SET TPBLOCK TO TRUE.
          SET TPNOTRAN TO TRUE.
          SET TPNOTIME TO TRUE.
          SET TPSIGRSTRT TO TRUE.
          SET TPCHANGE TO TRUE.
       
          CALL "TPCALL" USING TPSVCDEF-REC 
                TPTYPE-REC 
                SEND-STRING
                TPTYPE-REC 
                RECV-STRING
                TPSTATUS-REC. 
      
          IF NOT TPOK
                MOVE "TPCALL Failed" TO LOGMSG-TEXT
                PERFORM DO-USERLOG 
          END-IF.
      
      *****************************************************
      * Leave TUXEDO  
      *****************************************************
        DO-TPTERM.
          CALL "TPTERM" USING TPSTATUS-REC.      
          IF  NOT TPOK
                MOVE "TPTERM Failed" TO LOGMSG-TEXT
                PERFORM DO-USERLOG
          END-IF.
      
      *****************************************************
      * Log messages to the userlog 
      *****************************************************
        DO-USERLOG.
          CALL "USERLOG" USING LOGMSG 
                LOGMSG-LEN 
                TPSTATUS-REC.
      
      *****************************************************
      *Leave Application
      *****************************************************
        EXIT-PROGRAM.
          MOVE "Ended" TO LOGMSG-TEXT.
          PERFORM DO-USERLOG.
          STOP RUN.
