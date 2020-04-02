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
      * #ident	"@(#) samples/atmi/STOCKAPP/FUNDPR.cbl	$Revision: 1.6 $" 
      * static	char	sccsid[] = "@(#) samples/atmi/STOCKAPP/FUNDPR.cbl	$Revision: 1.6 $";
      *
	IDENTIFICATION DIVISION.
	PROGRAM-ID. FUNDPR.
	AUTHOR. TUXEDO DEVELOPMENT.
	ENVIRONMENT DIVISION.
	CONFIGURATION SECTION.
	SOURCE-COMPUTER.  USL-486.
	OBJECT-COMPUTER.  USL-486.
      *
	SPECIAL-NAMES. CONSOLE IS CRT.
      *
	WORKING-STORAGE SECTION.
      *****************************************************
      * Tuxedo definitions
      *****************************************************
	01  TPTYPE-REC. 
	COPY TPTYPE.
      *
	01 TPSTATUS-REC. 
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
		05  FILLER	PIC X(12) VALUE  
			"FUNDPR    =>".
		05  LOGMSG-TEXT	PIC X(50).
	01  LOGMSG-ERR.
		05  FILLER	PIC X(13) VALUE  
			"FUNDPR ERR =>".
		05  LOG-ERR-ROUTINE PIC X(10).
		05  FILLER	PIC X(21) VALUE  
			" FAILED: TP-STATUS = ".
		05  LOG-ERR-TP-STATUS PIC S9(9).
	01  LOGMSG-LEN		PIC S9(9)  COMP-5.
	01  LOGMSG-ERR-LEN	PIC S9(9)  COMP-5.
      *
	01  USER-DATA-REC 	PIC X(75).
      *****************************************************
      * This record will be sent to and from the server 
      * This is a VIEW record refer to quote file
      *****************************************************
	01 QUOTE-REC.
	COPY QUOTE.
      *
        77 REC-FOUND            PIC S9(9) COMP-5 VALUE 1.
        77 REC-NOT-FOUND        PIC S9(9) COMP-5 VALUE 2.
      *****************************************************
      * Screen definitions
      *****************************************************
	01 QUOTE-HEAD.
		05  FILLER		PIC X(20).
		05  ASK-HEAD		PIC X(16) VALUE
				"FUND PRICE  FORM".
		05  FILLER		PIC X(44).
		05  ASK-FUND PIC 	X(23) VALUE 
				"FUND/STOCK [          ]".
		05  FILLER PIC 		X(57).
		05  ASK-BUY-PRICE 	PIC X(22) VALUE 
				"BUY PRICE  [         ]".
		05  FILLER 		PIC X(58).
		05  ASK-SELL-PRICE 	PIC X(22) VALUE 
				"SELL PRICE [         ]".
		05  FILLER		PIC X(58).
		05  FILLER		PIC X(80).
	01  ENTER-IT REDEFINES QUOTE-HEAD.
		05  FILLER		PIC X(80).
		05  FILLER		PIC X(12).
		05  CRT-FUND		PIC X(10).
		05  FILLER		PIC X(58).
		05  FILLER		PIC X(12).
		05  CRT-BUY-PRICE	PIC $$$$$9.99.
		05  FILLER 		PIC X(59).
		05  FILLER 		PIC X(12).
		05  CRT-SELL-PRICE 	PIC $$$$$9.99.
		05  FILLER 		PIC X(59).
		05  FILLER		PIC X(80).
      ******************************************************
	PROCEDURE DIVISION.
       START-FUNDPR.
	MOVE LENGTH OF LOGMSG TO LOGMSG-LEN. 
	MOVE LENGTH OF LOGMSG-ERR TO LOGMSG-ERR-LEN. 
      *
	MOVE "Started" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
      *****************************************************
      * Now register the client with the system.
      *****************************************************
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
		MOVE "TPINITIALI" TO LOG-ERR-ROUTINE
		MOVE TP-STATUS TO LOG-ERR-TP-STATUS
		PERFORM DO-USERLOG-ERR
		PERFORM EXIT-PROGRAM.
      *****************************************************
      * Display QUOTE PRICE SCREEN 
      *****************************************************
	DISPLAY SPACE.
	DISPLAY QUOTE-HEAD.
	MOVE SPACE TO ENTER-IT.

       ADD-ANOTHER.
	DISPLAY ENTER-IT.
      *****************************************************
      * Get the results from the screen
      *****************************************************
	ACCEPT ENTER-IT.
	IF CRT-FUND = SPACES
		PERFORM DO-TPTERM
		PERFORM EXIT-PROGRAM.
	MOVE CRT-FUND TO QUOTE-FUND.
        MOVE ZEROS TO CRT-BUY-PRICE.
        MOVE ZEROS TO CRT-SELL-PRICE.
      *****************************************************
      *  Issue a TPCALL
      *****************************************************
	MOVE LENGTH OF QUOTE-REC TO LEN.
	MOVE "VIEW" TO REC-TYPE.
	MOVE "quote" TO SUB-TYPE.

	MOVE "FUNDPRSR" TO SERVICE-NAME.
	SET TPBLOCK TO TRUE.
	SET TPNOTRAN TO TRUE.
	SET TPNOTIME TO TRUE.
	SET TPSIGRSTRT TO TRUE.
	SET TPNOCHANGE TO TRUE.
       
	CALL "TPCALL" USING TPSVCDEF-REC 
			TPTYPE-REC 
			QUOTE-REC 
			TPTYPE-REC 
			QUOTE-REC 
			TPSTATUS-REC. 
	IF NOT TPOK
		MOVE "TPCALL" TO LOG-ERR-ROUTINE
		MOVE TP-STATUS TO LOG-ERR-TP-STATUS
	    	PERFORM DO-USERLOG-ERR
		MOVE "Transaction Failed" TO LOGMSG-TEXT
		PERFORM DO-USERLOG 
		PERFORM DO-TPTERM
		PERFORM EXIT-PROGRAM.

      *****************************************************
      * Check if the server found the record 
      *****************************************************
	IF APPL-RETURN-CODE = REC-FOUND
		MOVE "Transaction Completed Record Found" TO LOGMSG-TEXT
		PERFORM DO-USERLOG 
		MOVE QUOTE-FUND TO CRT-FUND
		MOVE DEC-DGTS OF QUOTE-SELL-PRICE TO CRT-SELL-PRICE
		MOVE DEC-DGTS OF QUOTE-BUY-PRICE TO CRT-BUY-PRICE
		GO TO ADD-ANOTHER
	ELSE IF APPL-RETURN-CODE = REC-NOT-FOUND
		MOVE "Transaction Completed Record Not Found" TO 
			LOGMSG-TEXT
		PERFORM DO-USERLOG 
		MOVE SPACES TO CRT-FUND
		MOVE ZEROS TO CRT-SELL-PRICE
		MOVE ZEROS TO CRT-BUY-PRICE
		GO TO ADD-ANOTHER
	ELSE
		MOVE "Transaction Failed Server Did Not set Retrun" TO 
			LOGMSG-TEXT
		PERFORM DO-USERLOG 
		PERFORM DO-TPTERM
		PERFORM EXIT-PROGRAM.
      *****************************************************
      *Leave 
      *****************************************************
       EXIT-PROGRAM.
        STOP RUN.
      *****************************************************
      * Clean up 
      *****************************************************
       DO-TPTERM.
	CALL "TPTERM" USING TPSTATUS-REC.      
	IF  NOT TPOK
		MOVE "TPTERM " TO LOG-ERR-ROUTINE
		MOVE TP-STATUS TO LOG-ERR-TP-STATUS
		PERFORM DO-USERLOG-ERR. 
	MOVE "Ended" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
      *****************************************************
      * Log messages to the userlog 
      *****************************************************
       DO-USERLOG.
	CALL "USERLOG" USING LOGMSG 
		LOGMSG-LEN 
		TPSTATUS-REC.
       DO-USERLOG-ERR.
	CALL "USERLOG" USING LOGMSG-ERR 
		LOGMSG-ERR-LEN 
		TPSTATUS-REC.
