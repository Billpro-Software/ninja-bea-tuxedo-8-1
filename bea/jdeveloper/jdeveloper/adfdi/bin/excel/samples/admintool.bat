:::
:::   NAME
:::      admintool.bat
:::
:::   DESCRIPTION
:::      Sample ADF Desktop Integration Excel Workbook Admin Tool Script
:::
@echo off
setlocal

::: usage check (use ~1 to expand and strip quotes)
if "%~1"=="" goto USAGE
if /i "%~1"=="-help" goto USAGE
if /i "%~1"=="-h" goto USAGE

::: the path to this batch script file is assumed to be %ORACLE_HOME%\adfdi\bin\excel\samples\admintool.bat
::: the path to the jar file is assumed to be %ORACLE_HOME%\adfdi\lib\adf-desktop-integration-admin-tool.jar
java -cp ..\..\..\lib\adf-desktop-integration-admin-tool.jar oracle.adf.desktopintegration.admintool.WorkbookAdminTool %*
goto :END

:USAGE
@echo.
@echo Usage: %~n0 [arg(s)]
@echo    eg: %~n0 -w sample.xlsx -r http://localhost:8988/MasterPriceList -m DT -o mySample.xlsx
@echo.
@echo   [arg(s)] is one of the following commands, in no particular order, along with any
@echo       required or optional arguments:
@echo. 
@echo   -workbook (-w) [Excel-workbook]
@echo       Required. Change the full path to the workbook to update
@echo. 
@echo   -root (-r) [root]
@echo       Optional. Change web application root to [root]
@echo. 
@echo   -mode (-m) [mode]
@echo       Optional. Change workbook mode to [mode]. [mode]={RT, DT, TST}
@echo. 
@echo   -out (-o) [output file name]
@echo       Required. Set the output file path.
@echo. 
@echo   Alternate command line:
@echo. 
@echo   %~n0 -help (-h)
@echo       Prints usage information. 
goto END

:END
endlocal
