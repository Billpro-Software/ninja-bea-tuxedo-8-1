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
      * #ident	"@(#) samples/atmi/STOCKAPP/BUYSR.cbl	$Revision: 1.5 $" 
      * static	char	sccsid[] = "@(#) samples/atmi/STOCKAPP/BUYSR.cbl	$Revision: 1.5 $";
      *
	IDENTIFICATION DIVISION.
	PROGRAM-ID. BUYSR.
	AUTHOR. TUXEDO DEVELOPMENT.
	ENVIRONMENT DIVISION.
	CONFIGURATION SECTION.
	SOURCE-COMPUTER.  USL-486.
	OBJECT-COMPUTER.  USL-486.
      *
	INPUT-OUTPUT SECTION.
	FILE-CONTROL.
	SELECT CUST-FILE ASSIGN "CUST.IT"
		ORGANIZATION INDEXED
		ACCESS DYNAMIC
		RECORD KEY FILE-CUST-KEY
		STATUS FILE-STATUS.
	DATA DIVISION.
	FILE SECTION.
	FD  CUST-FILE; RECORD 29.
	01  CUST-ITEM.
	     03 FILE-CUST-KEY.
		05  FILE-CUST-ACCOUNT 		PIC X(10).
		05  FILE-CUST-FUND 		PIC X(10).
	     03  FILE-CUST-AMOUNT 		PIC 9(9).
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
      * Used for TPCALL to get price of fund  
      ******************************************************
       	01  QTPSVCDEF-REC.
       	COPY TPSVCDEF.
      *
       	01  QTPTYPE-REC.
       	COPY TPTYPE.
      ******************************************************
      * Log message definitions 
      ******************************************************
	01  LOGREC.
		05  FILLER	PIC X(7) VALUE  "BUY ".
		05  FILLER	PIC X(11) VALUE  " ACCOUNT =>".
		05  REC-ACCOUNT	PIC x(10).
		05  FILLER	PIC X(8) VALUE  " FUND =>".
		05  REC-FUND	PIC x(10).
		05  FILLER	PIC X(13) VALUE  " BUY PRICE =>".
		05  REC-PRICE	PIC $$$$$$9.99.
		05  FILLER	PIC X(10) VALUE  " AMOUNT =>".
		05  REC-AMOUNT 	PIC 999999999.
      *
	01  LOGMSG.
		05  FILLER	PIC X(8) VALUE  
			"BUYSR =>".
		05  LOGMSG-TEXT	PIC X(50).
	01  LOGMSG-ERR.
		05  FILLER	PIC X(13) VALUE  
			"BUYSR ERR =>".
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
       	01 CUST-REC.
	COPY CUST.
       	01 QUOTE-REC.
	COPY QUOTE.
        77 REC-FOUND            PIC S9(9) COMP-5 VALUE 1.
        77 REC-NOT-FOUND        PIC S9(9) COMP-5 VALUE 2.
      *
       	LINKAGE SECTION.
      *
       	PROCEDURE DIVISION.
      *
       START-BUYSR.
	MOVE LENGTH OF LOGREC TO LOGREC-LEN. 
	MOVE LENGTH OF LOGMSG TO LOGMSG-LEN. 
	MOVE LENGTH OF LOGMSG-ERR TO LOGMSG-ERR-LEN. 
	OPEN I-O CUST-FILE.
      ******************************************************
      * Get the data that was sent by the client
      ******************************************************
	MOVE "Started" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG. 
	MOVE LENGTH OF CUST-REC TO LEN IN TPTYPE-REC.
	CALL "TPSVCSTART" USING TPSVCDEF-REC 
			TPTYPE-REC 
			CUST-REC  
			TPSTATUS-REC.      
	IF NOT TPOK
		MOVE "TPSVCSTART" TO LOG-ERR-ROUTINE
		MOVE TP-STATUS TO LOG-ERR-TP-STATUS
	    	PERFORM DO-USERLOG-ERR 
		PERFORM A-999-EXIT.
      ******************************************************
      *  Get the price of the fund 
      ******************************************************
	MOVE CUST-FUND TO QUOTE-FUND.
	MOVE ZEROS TO QUOTE-BUY-PRICE.
	MOVE ZEROS TO QUOTE-SELL-PRICE.
      *****************************************************
      *  Issue a TPCALL to FUNDPR Service
      *****************************************************
	MOVE LENGTH OF QUOTE-REC TO LEN IN QTPTYPE-REC.
	MOVE "VIEW" TO REC-TYPE IN QTPTYPE-REC.
	MOVE "quote" TO SUB-TYPE IN QTPTYPE-REC.

	MOVE "FUNDPRSR" TO SERVICE-NAME IN QTPSVCDEF-REC.
	SET TPBLOCK IN QTPSVCDEF-REC TO TRUE.
	SET TPNOTRAN IN QTPSVCDEF-REC TO TRUE.
	SET TPNOTIME IN QTPSVCDEF-REC TO TRUE.
	SET TPSIGRSTRT IN QTPSVCDEF-REC TO TRUE.
	SET TPNOCHANGE IN QTPSVCDEF-REC TO TRUE .
       
	CALL "TPCALL" USING QTPSVCDEF-REC 
			QTPTYPE-REC 
			QUOTE-REC 
			QTPTYPE-REC 
			QUOTE-REC 
			TPSTATUS-REC. 
	IF NOT TPOK
		MOVE "TPCALL" TO LOG-ERR-ROUTINE
		MOVE TP-STATUS TO LOG-ERR-TP-STATUS
	    	PERFORM DO-USERLOG-ERR
		MOVE "Transaction Failed" TO LOGMSG-TEXT
		PERFORM DO-USERLOG 
      		PERFORM WRITEIT-ERROR.

	MOVE APPL-RETURN-CODE TO APPL-CODE.
      *****************************************************
      * Check if the server found the record 
      *****************************************************
	IF APPL-RETURN-CODE = REC-FOUND
		MOVE "Fund exists " TO LOGMSG-TEXT
		PERFORM DO-USERLOG 
		MOVE DEC-DGTS OF QUOTE-BUY-PRICE TO
                    DEC-DGTS OF CUST-PRICE
	ELSE IF APPL-RETURN-CODE = REC-NOT-FOUND
		MOVE "Fund Does not Exist Leave" TO LOGMSG-TEXT
		PERFORM DO-USERLOG 
		MOVE ZERO TO CUST-PRICE
      		PERFORM WRITEIT-ERROR
	ELSE
		MOVE "Service Did Not set Retrun" TO LOGMSG-TEXT
		PERFORM DO-USERLOG 
		MOVE -1 TO CUST-PRICE
      		PERFORM WRITEIT-ERROR.
      ******************************************************
      *  Move data from receive record to I/O record 
      ******************************************************
	MOVE CUST-ACCOUNT TO FILE-CUST-ACCOUNT.
	MOVE CUST-FUND TO FILE-CUST-FUND.
	MOVE CUST-AMOUNT TO FILE-CUST-AMOUNT.
      ******************************************************
      * LOG the request 
      ******************************************************
	MOVE CUST-ACCOUNT TO REC-ACCOUNT.
	MOVE CUST-FUND TO REC-FUND.
	MOVE CUST-AMOUNT TO REC-AMOUNT.
	MOVE DEC-DGTS OF CUST-PRICE TO REC-PRICE.
	CALL "USERLOG" USING LOGREC 
			LOGREC-LEN 
			TPSTATUS-REC.
      ******************************************************
      *  Check if record exits 
      ******************************************************
	READ CUST-FILE.
	IF STATUS-1 = "0"
		MOVE "Record Exists Update It" TO LOGMSG-TEXT
	    	PERFORM DO-USERLOG
		PERFORM DELETE-REC
		ADD CUST-AMOUNT TO FILE-CUST-AMOUNT
      		PERFORM WRITE-REC
	ELSE IF STATUS-1 = "2"
		MOVE "Record Does Not Exists Add It" TO LOGMSG-TEXT
	    	PERFORM DO-USERLOG
		MOVE CUST-AMOUNT TO FILE-CUST-AMOUNT
		PERFORM WRITE-REC
	ELSE
		MOVE "READ" TO LOG-ERR-ROUTINE
		MOVE STATUS-1 TO LOG-ERR-TP-STATUS
		MOVE REC-NOT-FOUND TO APPL-CODE 
		PERFORM DO-USERLOG-ERR
		PERFORM WRITEIT-ERROR.
	
      ******************************************************
      *  Update OK  
      ******************************************************
	CLOSE CUST-FILE.
	SET TPSUCCESS TO TRUE.
	MOVE "Update completed" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
	PERFORM DO-TPRETURN.
      ******************************************************
      *  Close FIle and Leave
      ******************************************************
       WRITEIT-ERROR.
	CLOSE CUST-FILE.
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
	MOVE CUST-ACCOUNT TO FILE-CUST-ACCOUNT.
	MOVE CUST-FUND TO FILE-CUST-FUND.
	MOVE REC-FOUND TO APPL-CODE.
	WRITE CUST-ITEM.
	IF STATUS-1 NOT = "0"
		MOVE "WRITE" TO LOG-ERR-ROUTINE
		MOVE STATUS-1 TO LOG-ERR-TP-STATUS
	    	PERFORM DO-USERLOG-ERR 
		PERFORM WRITEIT-ERROR.
      ******************************************************
      *  Delete record from File
      ******************************************************
       DELETE-REC.
	DELETE CUST-FILE.
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
			DATA-REC BY CUST-REC.
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
