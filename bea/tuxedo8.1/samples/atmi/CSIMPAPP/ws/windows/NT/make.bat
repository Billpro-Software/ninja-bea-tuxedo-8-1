REM #	(c) 2003 BEA Systems, Inc. All Rights Reserved.
REM #ident	"@(#) samples/atmi/CSIMPAPP/ws/windows/NT/make.bat	$Revision: 1.5 $"
REM
REM Assume Windows NT 3.5, MS Visual C++ 2.0, and 
REM Micro Focus Cobol V3G19 (Intel or Alpha).
REM
REM replace \tuxedo with %TUXDIR% if needed, and make sure 
REM LIB env var is set to include %TUXDIR%\lib
REM
set cobcpy=\tuxedo\cobinc
cobol csimpcl.cbl omf(obj) litlink;
REM *******************************************
REM due to a problem with MF SDK, the following 
REM works for Intel platform only
REM *******************************************
cblnames -mcsimpcl csimpcl.obj 
link -subsystem:console -out:csimpcl.exe csimpcl.obj cbllds.obj cobws.lib ncobatmi.lib wtuxws32.lib mfrts32.lib LIBCMT.LIB USER32.LIB 
REM *******************************************
REM due to a problem with MF SDK, the following 
REM works for Alpha platform only
REM *******************************************
REM cbllink /mcsimpcl /ocsimpcl.exe csimpcl.obj cobws.lib ncobatmi.lib wtuxws32.lib libcmt.lib user32.lib
