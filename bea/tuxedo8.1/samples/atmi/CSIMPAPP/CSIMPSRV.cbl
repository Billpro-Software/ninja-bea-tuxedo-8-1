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
      * #ident	"@(#) samples/atmi/CSIMPAPP/CSIMPSRV.cbl	$Revision: 1.5 $" 
      * static	char	sccsid[] = "@(#) samples/atmi/CSIMPAPP/CSIMPSRV.cbl	$Revision: 1.5 $";
      *	
	IDENTIFICATION DIVISION.
	PROGRAM-ID. CSIMPSRV.
	AUTHOR. TUXEDO DEVELOPMENT.
	ENVIRONMENT DIVISION.
	CONFIGURATION SECTION.

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
	01  LOGMSG.
		05  FILLER	PIC X(10) VALUE  
			"CSIMPSRV :".
		05  LOGMSG-TEXT	PIC X(50).
	01  LOGMSG-LEN		PIC S9(9)  COMP-5.
      ******************************************************
      * User defined data records 
      ******************************************************
       	01 RECV-STRING 		PIC X(100).
       	01 SEND-STRING 		PIC X(100).
      *
       	LINKAGE SECTION.
      *
       	PROCEDURE DIVISION.
      *
       START-FUNDUPSR.
	MOVE LENGTH OF LOGMSG TO LOGMSG-LEN. 
	MOVE "Started" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG. 

      ******************************************************
      * Get the data that was sent by the client
      ******************************************************
	MOVE LENGTH OF RECV-STRING TO LEN.
	CALL "TPSVCSTART" USING TPSVCDEF-REC 
			TPTYPE-REC 
			RECV-STRING
			TPSTATUS-REC.      
	IF NOT TPOK
		MOVE "TPSVCSTART Failed" TO LOGMSG-TEXT
	    	PERFORM DO-USERLOG 
		PERFORM EXIT-PROGRAM 
	END-IF.

	IF TPTRUNCATE 
		MOVE "Data was truncated" TO LOGMSG-TEXT
	    	PERFORM DO-USERLOG 
		PERFORM EXIT-PROGRAM 
	END-IF.

	INSPECT RECV-STRING CONVERTING
	"abcdefghijklmnopqrstuvwxyz" TO
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ".
	MOVE "Success" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
	SET TPSUCCESS TO TRUE.
	COPY TPRETURN REPLACING 
		DATA-REC BY RECV-STRING.

      ******************************************************
      * Write out a log err messages
      ******************************************************
       DO-USERLOG.
	CALL "USERLOG" USING LOGMSG 
		LOGMSG-LEN 
		TPSTATUS-REC.
      ******************************************************
      * EXIT PROGRAM 
      ******************************************************
       EXIT-PROGRAM.
	MOVE "Failed" TO LOGMSG-TEXT.
	PERFORM DO-USERLOG.
	SET TPFAIL TO TRUE.
	COPY TPRETURN REPLACING 
		DATA-REC BY RECV-STRING.
