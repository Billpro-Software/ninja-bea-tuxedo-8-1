      *	(c) 2003 BEA Systems, Inc. All Rights Reserved.
      *
      *	Copyright (c) 1992 USL
      * All rights reserved
      *
      *	THIS IS UNPUBLISHED PROPRIETARY
      *	SOURCE CODE OF USL
      *	The copyright notice above does not
      *	evidence any actual or intended
      *	publication of such source code.
      *
      * #ident	"@(#) samples/atmi/CSIMPAPP/TPSVRINIT.cbl	$Revision: 1.5 $" 
      * static	char	sccsid[] = "@(#) samples/atmi/CSIMPAPP/TPSVRINIT.cbl	$Revision: 1.5 $";
      *
       IDENTIFICATION DIVISION. 
       PROGRAM-ID.  TPSVRINIT. 
       ENVIRONMENT DIVISION.
       CONFIGURATION SECTION.
      *
       DATA DIVISION.
       WORKING-STORAGE SECTION.
      *
       01  LOGMSG.
	   05  FILLER		PIC X(11) VALUE  "TPSVRINIT :".
	   05  LOGMSG-TEXT	PIC X(50).
       01  LOGMSG-LEN 		PIC S9(9)  COMP-5.
      *
       01 TPSTATUS-REC.
       COPY TPSTATUS.
      *********************************************************
       LINKAGE SECTION.
       01  CMD-LINE.
          05 ARGC  PIC 9(4) COMP-5.
          05 ARG.
             10 ARGS PIC X OCCURS 0 TO 9999 DEPENDING ON ARGC.
      *
       01  SERVER-INIT-STATUS.
       COPY TPSTATUS.
      ***********************************************************
       PROCEDURE DIVISION USING CMD-LINE SERVER-INIT-STATUS.
       A-000.
	MOVE LENGTH OF LOGMSG TO LOGMSG-LEN.
      ***********************************************************
      * There are no command line parameters in this TPSVRINIT
      ***********************************************************
	IF ARG NOT EQUAL TO SPACES 
		MOVE "TPSVRINIT failed" TO LOGMSG-TEXT
		CALL "USERLOG" USING  LOGMSG 
			LOGMSG-LEN 
			TPSTATUS-REC
	ELSE
		MOVE "Welcome to the simple service" TO LOGMSG-TEXT
		CALL "USERLOG" USING  LOGMSG 
			LOGMSG-LEN 
			TPSTATUS-REC
	END-IF.
      *
        SET TPOK IN SERVER-INIT-STATUS TO TRUE. 
      *
        EXIT PROGRAM.
