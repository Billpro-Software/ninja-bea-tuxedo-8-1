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
      * #ident	"@(#) samples/atmi/STOCKAPP/FUNDUPSR.cbl	$Revision: 1.5 $" 
      * static	char	sccsid[] = "@(#) samples/atmi/STOCKAPP/FUNDUPSR.cbl	$Revision: 1.5 $";
      *
	IDENTIFICATION DIVISION.
	PROGRAM-ID. FUNDUPSR.
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
	01  LOGREC.
		05  FILLER	PIC X(7) VALUE  
			"UPDATE ".
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
			"FUNDUPSR    =>".
		05  LOGMSG-TEXT	PIC X(50).
	01  LOGMSG-ERR.
		05  FILLER	PIC X(15) VALUE  
			"FUNDUPSR ERR =>".
		05  LOG-ERR-ROUTINE PIC X(10).
		05  FILLER	PIC X(21) VALUE  
			" FAILED: TP-STATUS = ".
		05  LOG-ERR-TP-STATUS PIC S9(9).
      *
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
       	LINKAGE SECTION.
      *
       	PROCEDURE DIVISION.
      *
       START-FUNDUPSR.
	MOVE LENGTH OF LOGREC TO LOGREC-LEN. 
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
		PERFORM A-999-EXIT.
      ******************************************************
      *  Move data from receive record to I/O record 
      ******************************************************
	MOVE QUOTE-FUND TO FILE-QUOTE-FUND.
	MOVE DEC-DGTS OF QUOTE-SELL-PRICE TO FILE-QUOTE-SELL-PRICE.
	MOVE DEC-DGTS OF QUOTE-BUY-PRICE TO FILE-QUOTE-BUY-PRICE.
      ******************************************************
      * LOG the request 
      ******************************************************
	MOVE QUOTE-FUND TO REC-FUND.
	MOVE DEC-DGTS OF QUOTE-SELL-PRICE TO REC-SELL-PRICE.
	MOVE DEC-DGTS OF QUOTE-BUY-PRICE TO REC-BUY-PRICE.
	CALL "USERLOG" USING LOGREC 
			LOGREC-LEN 
			TPSTATUS-REC.
      ******************************************************
      *  Check if record exits 
      ******************************************************
	READ QUOTE-FILE.
	IF STATUS-1 = "0"
		MOVE "Record Exists Update It" TO LOGMSG-TEXT
	    	PERFORM DO-USERLOG
		PERFORM DELETE-REC
      		PERFORM WRITE-REC
	ELSE IF STATUS-1 = "2"
		MOVE "Record Does Not Exists Add It" TO LOGMSG-TEXT
	    	PERFORM DO-USERLOG
		PERFORM WRITE-REC
	ELSE
		MOVE "READ" TO LOG-ERR-ROUTINE
		MOVE STATUS-1 TO LOG-ERR-TP-STATUS
		PERFORM DO-USERLOG-ERR
		PERFORM WRITEIT-ERROR.
	
      ******************************************************
      *  Update OK  
      ******************************************************
	CLOSE QUOTE-FILE.
	MOVE 0 TO APPL-CODE. 
	SET TPSUCCESS TO TRUE.
	MOVE "Update completed" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
	PERFORM DO-TPRETURN.
      ******************************************************
      *  Close FIle and Leave
      ******************************************************
       WRITEIT-ERROR.
	CLOSE QUOTE-FILE.
	MOVE 1 TO APPL-CODE. 
	SET TPFAIL TO TRUE.
	MOVE "Update Failed" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
	PERFORM DO-TPRETURN.
      ******************************************************
      * Leave
      ******************************************************
       A-999-EXIT.
	MOVE "Exiting without Update" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
	PERFORM DO-TPRETURN.
      *
      ******************************************************
      *  Add record to File
      ******************************************************
       WRITE-REC.
	MOVE QUOTE-FUND TO FILE-QUOTE-FUND.
	MOVE DEC-DGTS OF QUOTE-SELL-PRICE TO FILE-QUOTE-SELL-PRICE.
	MOVE DEC-DGTS OF QUOTE-BUY-PRICE TO FILE-QUOTE-BUY-PRICE.
	WRITE QUOTE-ITEM.
	IF STATUS-1 NOT = "0"
		MOVE "WRITE" TO LOG-ERR-ROUTINE
		MOVE STATUS-1 TO LOG-ERR-TP-STATUS
	    	PERFORM DO-USERLOG-ERR 
		PERFORM WRITEIT-ERROR.
      ******************************************************
      *  Delete record from File
      ******************************************************
       DELETE-REC.
	DELETE QUOTE-FILE.
	IF STATUS-1 NOT = "0"
		MOVE "DELETE" TO LOG-ERR-ROUTINE
		MOVE STATUS-1 TO LOG-ERR-TP-STATUS
	    	PERFORM DO-USERLOG-ERR 
		PERFORM WRITEIT-ERROR.
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
