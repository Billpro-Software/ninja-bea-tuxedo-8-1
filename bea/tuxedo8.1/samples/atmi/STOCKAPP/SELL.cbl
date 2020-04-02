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
      * #ident	"@(#) samples/atmi/STOCKAPP/SELL.cbl	$Revision: 1.5 $" 
      * static	char	sccsid[] = "@(#) apps/STOCKAPP/SELL.cbl	$Revision: 1.5 $";
      *
	IDENTIFICATION DIVISION.
	PROGRAM-ID. SELL.
	AUTHOR. TUXEDO DEVELOPMENT.
	ENVIRONMENT DIVISION.
	CONFIGURATION SECTION.
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
		05  FILLER	PIC X(7) VALUE  "SELL =>".
		05  LOGMSG-TEXT	PIC X(50).
	01  LOGMSG-ERR.
		05  FILLER	PIC X(11) VALUE  "SELL ERR =>".
		05  LOG-ERR-ROUTINE PIC X(10).
		05  FILLER	PIC X(21) VALUE " FAILED: TP-STATUS = ".
		05  LOG-ERR-TP-STATUS PIC S9(9).
	01  LOGMSG-LEN		PIC S9(9)  COMP-5.
	01  LOGMSG-ERR-LEN	PIC S9(9)  COMP-5.
      *
	01  USER-DATA-REC 	PIC X(75).
      *****************************************************
      * This record will be sent to and from the server 
      * This is a VIEW record refer to cust file
      *****************************************************
	01 CUST-REC.
	COPY CUST.
      *
	77 REC-FOUND 		PIC S9(9) VALUE 1.
	77 REC-NOT-FOUND 	PIC S9(9) VALUE 2.
      *****************************************************
      * Screen definitions
      *****************************************************
	01 CUST-HEAD.
		05  FILLER	PIC X(20).
		05  ASK-HEAD	PIC X(14) VALUE "SELL FUND FORM".
		05  FILLER	PIC X(46).
      *
		05  ASK-ACCOUNT	PIC X(20) VALUE 
				"ACCOUNT [          ]".
		05  FILLER PIC	X(60).
      *
		05  ASK-FUND 	PIC X(23) VALUE 
				"FUND/STOCK [          ]".
		05  FILLER PIC	X(57).
      *
		05  ASK-AMOUNT 	PIC X(19) VALUE 
				"AMOUNT  [         ]".
		05  FILLER 	PIC X(61).
      *
		05  ASK-PRICE 	PIC X(19) VALUE 
				"PRICE   [         ]".
		05  FILLER	PIC X(61).
		05  FILLER	PIC X(80).
	01  ENTER-IT REDEFINES CUST-HEAD.
		05  FILLER	PIC X(80).
		05  FILLER	PIC X(9).
		05  CRT-ACCOUNT	PIC X(10).
		05  FILLER	PIC X(61).
		05  FILLER	PIC X(12).
		05  CRT-FUND	PIC X(10).
		05  FILLER	PIC X(58).
		05  FILLER	PIC X(9).
		05  CRT-AMOUNT	PIC ZZZZZZZZ9.
		05  FILLER 	PIC X(62).
		05  FILLER 	PIC X(9).
		05  CRT-PRICE 	PIC $$,$$9.99.
		05  FILLER 	PIC X(62).
		05  FILLER	PIC X(80).
      ******************************************************
	PROCEDURE DIVISION.
       START-SELL.
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
      * Display CUST PRICE SCREEN 
      *****************************************************
	DISPLAY SPACE.
	DISPLAY CUST-HEAD.
	MOVE SPACE TO ENTER-IT.

       ADD-ANOTHER.
	DISPLAY ENTER-IT.
      *****************************************************
      * Get the results from the screen
      *****************************************************
	ACCEPT ENTER-IT.
	IF CRT-ACCOUNT = SPACES
		PERFORM DO-TPTERM
		PERFORM EXIT-PROGRAM.
	IF CRT-FUND = SPACES
                MOVE "Fund Name is Blank" TO LOGMSG-ERR
                PERFORM DO-USERLOG-ERR
		PERFORM DO-TPTERM
		PERFORM EXIT-PROGRAM.
	MOVE CRT-ACCOUNT TO CUST-ACCOUNT.
	MOVE CRT-FUND TO CUST-FUND.
	MOVE CRT-AMOUNT TO CUST-AMOUNT.
      *****************************************************
      *  Issue a TPCALL
      *****************************************************
	MOVE LENGTH OF CUST-REC TO LEN.
	MOVE "VIEW" TO REC-TYPE.
	MOVE "cust" TO SUB-TYPE.

	MOVE "SELLSR" TO SERVICE-NAME.
	SET TPBLOCK TO TRUE.
	SET TPNOTRAN TO TRUE.
	SET TPNOTIME TO TRUE.
	SET TPSIGRSTRT TO TRUE.
	SET TPNOCHANGE TO TRUE.
       
	CALL "TPCALL" USING TPSVCDEF-REC 
			TPTYPE-REC 
			CUST-REC 
			TPTYPE-REC 
			CUST-REC 
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
		MOVE CUST-ACCOUNT TO CRT-ACCOUNT
		MOVE CUST-FUND TO CRT-FUND
		MOVE DEC-DGTS OF CUST-PRICE TO CRT-PRICE
		MOVE CUST-AMOUNT TO CRT-AMOUNT
		GO TO ADD-ANOTHER
	ELSE IF APPL-RETURN-CODE = REC-NOT-FOUND
		MOVE "Transaction Completed Record Not Found" TO 
			LOGMSG-TEXT
		PERFORM DO-USERLOG 
		MOVE SPACES TO CRT-ACCOUNT
		MOVE SPACES TO CRT-FUND
		MOVE ZEROS TO CRT-PRICE
		MOVE ZEROS TO CRT-AMOUNT
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
	DISPLAY SPACE.
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
