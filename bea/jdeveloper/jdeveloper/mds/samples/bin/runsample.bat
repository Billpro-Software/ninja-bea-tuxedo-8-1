@echo off
REM    runsample.bat
REM
REM  DESCRIPTION
REM    Run one or all of the MDS sample programs that illustrate the use of
REM    the MDS core API to initialize the MDSInstance, register XSD files
REM    and metadata stores, and read and update metadata objects.
REM
REM  MODIFIED (MM/DD/YY)
REM  snoton    08/24/09 - #(8808215) use mds-tools.jar instead of 
REM                       setMDSclasspath
REM  dklein    04/06/09 - #(8406848) Bypass customization restrictions
REM  dklein    10/15/08 - #(7483381) Remove sample 9
REM  pwhaley   07/07/08 - Note dependency of script 4 on 3.
REM  dklein    07/01/08 - New location of javac.exe and java.exe
REM  gnagaraj  07/10/07 - Fix location of classes dir
REM  dklein    06/05/07 - New location for setMDSclasspath.bat
REM                       Remove use of JDEV_ROOT
REM  erwang    09/21/06 - Added UseExternConnectionsXMLSample
REM  erwang    08/16/06 - Added UseOraMDSProtocolSample
REM  gkonduri  07/05/06 - Remove -source 1.4, Add VersioningSample
REM  cxlewis   01/27/06 - Use file to specify include/exclude for code 
REM                       coverage 
REM  jhsi      11/07/05 - #(4640591) - compile with -source 1.4 
REM  cxlewis   10/10/05 - #(4659797) - run all tests 
REM  cxlewis   09/21/05 - Add code coverage facility 
REM  cbarrow   06/15/05 - cbarrow_custkeysample
REM  cbarrow   06/13/05 - Created (from rtmdssample.bat, now removed)

@setlocal


REM
REM List of sample programs (add new ones here)
REM
set SAMPLE1=oracle.mds.samples.PortalProviderSample
set SAMPLE2=oracle.mds.samples.mymusicindustry.mymusiccompany.ReadMetadataExample
set SAMPLE3=oracle.mds.samples.mymusicindustry.mymusiccompany.CreateMetadataExample
set SAMPLE4=oracle.mds.samples.mymusicindustry.mymusiccompany.WriteMetadataExample
set SAMPLE5=oracle.mds.samples.mymusicindustry.mymusiccompany.TypeInfoExample
set SAMPLE6=oracle.mds.samples.mymusicindustry.mymusiccompany.PortalCustKeyExample
set SAMPLE7=oracle.mds.samples.versioning.VersioningSample
set SAMPLE8=oracle.mds.samples.UseOraMDSProtocolSample

REM
REM Branch to usage if requested
REM
if "%1"=="/?" goto usage
if "%1"=="" goto usage


:: ------------------------------------------------------------------
:: --------- COMPUTE DELIVER. DO NOT CHANGE THIS VALUE !! ---------
:: -- DELIVER directory
:: Set DELIVER to the value of the BUILT environment setting if present (means
:: this script was called by rtmdstest.bat).  
:: Otherwise, compute it by assuming this script is being called from the
:: jdev\bin\test subdir of the DELIVER directory.
set DELIVER=%BUILT%
if "%LOGPROPSFILE%"=="" set LOGPROPSFILE=mdstestlog.properties
if "%BUILT%"=="" set DELIVER=%~d0%~p0..\..\..

::-------------------------------------------------------------------
:: Code Coverage
:: if CODECOV is set, then use EMMA package to get code coverage figures
::
:: We want to gather stats for the following directories/packages
:: oracle\mds
::
:: To add additional options, set the environment variable CODECOV_OPTIONS as 
:: appropriate.  For example
:: CODECOV_OPTIONS=-f
:: Will generate a report showing all classes in the classpath
::
if not "%CODECOV%"=="true" goto nocodecov
set EMMAJAR=%ADE_VIEW_ROOT%\jtmds\src\devutils\codecov\emma.jar
set SILENT=-Demma.verbosity.level=silent

:: pre-instrument the mds classes...
%DELIVER%\jdk\bin\java %SILENT% -cp %EMMAJAR% emma instr -d %ADE_VIEW_ROOT%\jtmds\src\java\instr -ip %DELIVER%\..\classes -ix @%ADE_VIEW_ROOT%\jtmds\src\devutils\codecov\mdsfilters.txt

set CODECOV_CP=%ADE_VIEW_ROOT%\jtmds\src\java\instr
:nocodecov


REM
REM set up MDS_CP environment var
REM
set MDS_CP=%DELIVER%\mds\bin\mdstools.jar

REM Set up source path
set SRCDIR=%DELIVER%\mds\samples\java

REM Set up XSD path
set XSDDIR=%DELIVER%\mds\samples\xsd

REM Set up where to compile samples to.
REM Use jdev\classes if it exists.
set CLASSDIR=%DELIVER%\jdev\classes
REM Else use classes dir under view root (DELIVER\..\..)
REM for use by internal MDS developers
if not exist %CLASSDIR% set CLASSDIR=%DELIVER%\built\stub-mds\classes
REM Else fall back on source dir
if not exist %CLASSDIR% set CLASSDIR=%SRCDIR%

REM
REM Process run or compile parameter (if present)
REM
set ACTION=both
if "%2"=="" goto prog_param
if "%1"=="run"     set ACTION=%1
if "%1"=="compile" set ACTION=%1
if "%ACTION%"=="both" goto usage
shift

REM
REM Process program parameter (add new ones here)
REM
:prog_param
if "%1"=="" goto :usage
set PROG=
set NUM=%1
if "%1"=="1" set PROG=%SAMPLE1%
if "%1"=="2" set PROG=%SAMPLE2%
if "%1"=="3" set PROG=%SAMPLE3%
if "%1"=="4" set PROG=%SAMPLE4%
if "%1"=="5" set PROG=%SAMPLE5%
if "%1"=="6" set PROG=%SAMPLE6%
if "%1"=="7" set PROG=%SAMPLE7%
if "%1"=="8" set PROG=%SAMPLE8%
if "%1"=="all" set PROG=all
if "%PROG%"=="" goto usage

if "%PROG%"=="all" goto :all

REM Do requested action for one program
if "%ACTION%"=="run"     goto :run
if "%ACTION%"=="compile" goto :compile
if "%ACTION%"=="both"    goto :both

goto usage

:all
if "%ACTION%"=="both" set ACTION=
REM So we can call this script back:
set THIS=%~d0%~p0%runsample
call %THIS% %ACTION% 1
call %THIS% %ACTION% 2
call %THIS% %ACTION% 3
call %THIS% %ACTION% 4
call %THIS% %ACTION% 5
call %THIS% %ACTION% 6
call %THIS% %ACTION% 7
call %THIS% %ACTION% 8
goto :EOF

:usage
echo USAGE
echo    runsample           - display usage
echo    runsample {program}         - compile and run a sample program
echo    runsample compile {program} - compile a sample programs
echo    runsample run     {program} - run a sample programs without compiling
echo  where {program} indicates the sample program to run, as follows:
echo    1  - %SAMPLE1%
echo    2  - %SAMPLE2%
echo    3  - %SAMPLE3%
echo    4  - %SAMPLE4%
echo         (must be preceeded by 3 to create data) 
echo    5  - %SAMPLE5%
echo    6  - %SAMPLE6%
echo    7  - %SAMPLE7%
echo    8  - %SAMPLE8%
echo   all - Run and/or compile all the sample programmes
echo PURPOSE
echo    Run one of the samples programs illustrating usage of the MDS Runtime API.
echo EXAMPLES
echo    runsample 1
echo    runsample all
echo PREREQUISITES
echo 1. The mdstools.jar file must be available in the directory
echo    this script is run from
echo 2. The following environment variable may be set to run the sample
echo    program against an MDS Repository:
echo      DBARGS  - Database connection details.
echo      Example:
echo        set DBARGS=username=mdsrepos password=secret sid=ORA8 host=myhost.mycorp.com port=1521
echo 3. The following environment variable may be set to turn on verbose mode
echo    (prints the java and/or javac commands to the console)
echo      set VERBOSE=1
goto :EOF

REM Usage: call :compile {program}
:compile
echo ------------------------
echo Compiling sample program %PROG:.=\%.java
echo ------------------------
set TARGET=%SRCDIR%\%PROG:.=\%.java
set ERR=ERROR: program source %TARGET% not found, unable to compile
if not exist %TARGET% goto error
set CMD=%DELIVER%\..\jdk\bin\javac -classpath %MDS_CP% -d %CLASSDIR% -sourcepath %SRCDIR% %TARGET%
if "%VERBOSE%"=="1" echo %CMD%
%CMD%
goto :EOF

:run
echo ------------------------
echo Running sample program %PROG:\=.%
echo ------------------------
set TARGET=%CLASSDIR%\%PROG:.=\%.class
set ERR=ERROR: compiled sample program %TARGET% not found, unable to run
if not exist %TARGET% goto error
set CMD=%DELIVER%\..\jdk\bin\java -Doracle.mds.bypassCustRestrict=true -Djava.protocol.handler.pkgs=oracle.mds.net.protocol -classpath %CODECOV_CP%;%CLASSDIR%;%XSDDIR%;%MDS_CP%;%EMMAJAR% %SILENT% %PROG% --BUILD_ROOT %DELIVER% --DBARGS "%DBARGS%"
if "%VERBOSE%"=="1" echo %CMD%
%CMD%

REM if CODEVOV then generate the coverage report...
if "%CODECOV%"=="true" %DELIVER%\jdk\bin\java -Djava.protocol.handler.pkgs=oracle.mds.net.protocol -cp %EMMAJAR% %SILENT% emma report -r html -sp %ADE_VIEW_ROOT%\jtmds\src\java\ -Dreport.html.out.dir=%ADE_VIEW_ROOT%\jtmds\tests\bin\coverage\sample -Dreport.sort=+name,+block,+method,+class -in coverage.em -in coverage.ec %SILENT%

if "%CODECOV%"=="true" move coverage.ec Sample%NUM%.es

goto :EOF

:both
call :compile
call :run
goto :EOF

:error
echo %ERR%
goto :EOF
