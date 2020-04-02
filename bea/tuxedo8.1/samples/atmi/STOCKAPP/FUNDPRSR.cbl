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
      * #ident	"@(#) samples/atmi/STOCKAPP/FUNDPRSR.cbl	$Revision: 1.5 $" 
      * static	char	sccsid[] = "@(#) samples/atmi/STOCKAPP/FUNDPRSR.cbl	$Revision: 1.5 $";
      *
	IDENTIFICATION DIVISION.
	PROGRAM-ID. FUNDPRSR.
	AUTHOR. TUXEDO DEVELOPMENT.
	ENVIRONMENT DIVISION.
	CONFIGURATION SECTION.
      *
	INPUT-OUTPUT SECTION.
	FILE-CONTROL.
	SELECT QUOTE-FILE ASSIGN "QUOTE.IT"
		ORGANIZATION INDEXED
		ACCESS DYNAMIC
		RECORD KEY FILE-QUOTE-FUND
		STATUS FILE-STATUS.
	DATA DIVISION.
	FILE SECTION.
	FD  QUOTE-FILE; RECORD 28.
	01  QUOTE-ITEM.
		02  FILE-QUOTE-FUND 		PIC X(10).
		02  FILE-QUOTE-SELL-PRICE 	PIC 9(7)V99.
		02  FILE-QUOTE-BUY-PRICE 	PIC 9(7)V99.
	WORKING-STORAGE SECTION.
      ******************************************************
      * Tuxedo definitions 
      ******************************************************
	01  TPSVCRET-REC.
	COPY TPSVCRET.
      *
       	01  TPTYPE-REC.
       	COPY TPTYPE.
      *
       	01 TPSTATUS-REC.
       	COPY TPSTATUS.
      *
       	01  TPSVCDEF-REC.
       	COPY TPSVCDEF.
      ******************************************************
      * Log message definitions 
      ******************************************************
	01  LOGREC-REQ.
		05  FILLER	PIC X(33) VALUE  
			"REQUESTING QUOTE FOR FUND NAME =>".
		05  REQ-FUND	PIC x(10).
	01  LOGREC.
		05  FILLER	PIC X(12) VALUE  
			"PRICE QUOTE ".
		05  FILLER	PIC X(12) VALUE  
			"FUND NAME =>".
		05  REC-FUND	PIC x(10).
		05  FILLER	PIC X(14) VALUE  
			" SELL-PRICE =>".
		05  REC-SELL-PRICE	PIC $$$$$$9.99.
		05  FILLER	PIC X(13) VALUE  
			" BUY-PRICE =>".
		05  REC-BUY-PRICE	PIC $$$$$$9.99.
      *
	01  LOGMSG.
		05  FILLER	PIC X(14) VALUE  
			"FUNDPRSR    =>".
		05  LOGMSG-TEXT	PIC X(50).
	01  LOGMSG-ERR.
		05  FILLER	PIC X(15) VALUE  
			"FUNDPRSR ERR =>".
		05  LOG-ERR-ROUTINE PIC X(10).
		05  FILLER	PIC X(21) VALUE  
			" FAILED: TP-STATUS = ".
		05  LOG-ERR-TP-STATUS PIC S9(9).
      *
	01  LOGREQ-LEN		PIC S9(9)  COMP-5.
	01  LOGREC-LEN		PIC S9(9)  COMP-5.
	01  LOGMSG-LEN		PIC S9(9)  COMP-5.
	01  LOGMSG-ERR-LEN	PIC S9(9)  COMP-5.
      ******************************************************
      * File status 
      ******************************************************
 	01  FILE-STATUS.
           	05  STATUS-1	PIC X.
           	05  STATUS-2	PIC X.
      ******************************************************
      * User defined data records 
      ******************************************************
       	01 QUOTE-REC.
	COPY QUOTE.
      *
	77 REC-FOUND		PIC S9(9) COMP-5 VALUE 1.
	77 REC-NOT-FOUND	PIC S9(9) COMP-5 VALUE 2.
      *
       	LINKAGE SECTION.
      *
       	PROCEDURE DIVISION.
      *
       START-FUNDPRSR.
	MOVE LENGTH OF LOGREC TO LOGREC-LEN. 
	MOVE LENGTH OF LOGREC-REQ TO LOGREQ-LEN. 
	MOVE LENGTH OF LOGMSG TO LOGMSG-LEN. 
	MOVE LENGTH OF LOGMSG-ERR TO LOGMSG-ERR-LEN. 
	OPEN I-O QUOTE-FILE.
      ******************************************************
      * Get the data that was sent by the client
      ******************************************************
	MOVE "Started" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG. 
	MOVE LENGTH OF QUOTE-REC TO LEN.
	CALL "TPSVCSTART" USING TPSVCDEF-REC 
			TPTYPE-REC 
			QUOTE-REC  
			TPSTATUS-REC.      
	IF NOT TPOK
		MOVE "TPSVCSTART" TO LOG-ERR-ROUTINE
		MOVE TP-STATUS TO LOG-ERR-TP-STATUS
	    	PERFORM DO-USERLOG-ERR 
		MOVE "Exiting without Attempting to Find" TO 
			LOGMSG-TEXT
		PERFORM DO-USERLOG
		CLOSE QUOTE-FILE
		SET TPFAIL TO TRUE
		PERFORM DO-TPRETURN.
      ******************************************************
      *  Move data from receive record to I/O record 
      ******************************************************
	MOVE QUOTE-FUND TO FILE-QUOTE-FUND.
      ******************************************************
      * Log Input Request 
      ******************************************************
	MOVE QUOTE-FUND TO REQ-FUND.
	PERFORM DO-USERLOG-REQ.
      ******************************************************
      *  Check if record exits 
      ******************************************************
	READ QUOTE-FILE.
	IF STATUS-1 = "0"
		MOVE "Record Exists" TO LOGMSG-TEXT
	    	PERFORM DO-USERLOG
		MOVE REC-FOUND TO APPL-CODE
		SET TPSUCCESS TO TRUE
	ELSE IF STATUS-1 = "2"
		MOVE "Record Does Not Exists" TO LOGMSG-ERR 
	    	PERFORM DO-USERLOG-ERR
		MOVE REC-NOT-FOUND TO APPL-CODE
		SET TPSUCCESS TO TRUE
	ELSE
      *         ********************************************
      *         * READ Failed Log Message and Leave 
      *         ********************************************
		MOVE "READ" TO LOG-ERR-ROUTINE
		MOVE STATUS-1 TO LOG-ERR-TP-STATUS
		PERFORM DO-USERLOG-ERR
		CLOSE QUOTE-FILE
		SET TPFAIL TO TRUE
       		PERFORM DO-TPRETURN.
      ******************************************************
      * Log Response 
      ******************************************************
	MOVE FILE-QUOTE-FUND TO REC-FUND.
	MOVE FILE-QUOTE-SELL-PRICE TO REC-SELL-PRICE.
	MOVE FILE-QUOTE-BUY-PRICE TO REC-BUY-PRICE.
	PERFORM DO-USERLOG-REC.
      ******************************************************
      * Prepare Response 
      ******************************************************
	MOVE FILE-QUOTE-FUND TO QUOTE-FUND.
	MOVE FILE-QUOTE-SELL-PRICE TO DEC-DGTS OF QUOTE-SELL-PRICE.
	MOVE FILE-QUOTE-BUY-PRICE TO DEC-DGTS OF QUOTE-BUY-PRICE.
      ******************************************************
      *  Read  OK  Leave
      ******************************************************
	CLOSE QUOTE-FILE.
	MOVE "Exiting" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
	PERFORM DO-TPRETURN.
      ******************************************************
      * set up TPRETURN 
      ******************************************************
       DO-TPRETURN.
	COPY TPRETURN REPLACING 
			DATA-REC BY QUOTE-REC.
      ******************************************************
      * Write out a log err messages
      ******************************************************
       DO-USERLOG-ERR.
	CALL "USERLOG" USING LOGMSG-ERR 
		LOGMSG-ERR-LEN 
		TPSTATUS-REC.
       DO-USERLOG.
	CALL "USERLOG" USING LOGMSG 
		LOGMSG-LEN 
		TPSTATUS-REC.
       DO-USERLOG-REC.
	CALL "USERLOG" USING LOGREC 
			LOGREC-LEN 
			TPSTATUS-REC.
       DO-USERLOG-REQ.
	CALL "USERLOG" USING LOGREC-REQ 
			LOGREQ-LEN 
			TPSTATUS-REC.
