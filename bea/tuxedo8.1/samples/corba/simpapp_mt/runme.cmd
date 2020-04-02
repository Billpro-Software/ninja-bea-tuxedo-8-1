@rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@rem -----------------------------------------------------------------
@rem
@rem runme.cmd
@rem
@rem NT script to build and run the simpapp_mt sample application
@rem
@rem BEA Systems Inc. sample code
@rem
@rem -----------------------------------------------------------------
@echo on
@rem Check that the user properly called this script.
@if "%1" NEQ "" goto syntax_error

@rem Check that the TUXDIR environment variable is defined.
@if NOT defined TUXDIR goto tuxdir_not_defined

@rem Check that TUXDIR is an absolute pathname
@rem (that is, it has ":\" in it).
@echo %TUXDIR% | findstr ":\\" > NUL: 2>&1
@if ERRORLEVEL 1 goto tuxdir_not_absolute_pathname

@rem If the user hasn't specified HOST, PORT or IPCKEY,
@rem then use these defaults.
@if NOT defined HOST   set HOST=%COMPUTERNAME%
@if NOT defined PORT   set PORT=2468
@if NOT defined IPCKEY set IPCKEY=55432

@echo Testing simpapp_mt

@rem APPDIR is a special environment variable that is used when
@rem running server apps. It needs to be set to the absolute
@rem pathname of the current working directory. Since NT doesn't
@rem have a command to get the current working directory (like
@rem "pwd" on Unix), we've written a function to do it:
@call :compute_pwd
@set APPDIR=%PWD%

@rem TOBJADDR is another special environment variable that
@rem is used when running remote C++ clients.
@set TOBJADDR=//%HOST%:%PORT%

@rem Set environment variables that are only used by this
@rem application.

@rem Did we encounter an error while running this script?
@set ERROR=

@rem Shortcut for calling "nmake".
@set MAKE=nmake -f makefile.nt

@rem The pathname of directory we're going to store the
@rem results of running this script in.
@set RESULTSDIR=%APPDIR%\results

@rem The pathname of the log file used to capture the
@rem output of running this script.
@set LOG=%RESULTSDIR%\log

@rem The pathname of the setenv.cmd file.
@set SETENV=%RESULTSDIR%\setenv.cmd

@rem The pathname of the configuration file.
@set UBB=%RESULTSDIR%\ubb

@rem The pathname of the client input file.
@set INPUT=%RESULTSDIR%\input

@rem The pathname of the client output file.
@set OUTPUT=%RESULTSDIR%\output

@rem The pathname of the expected client output file.
@set EXPECTED_OUTPUT=%RESULTSDIR%\expected_output

@rem TUXCONFIG is another special environment variable that
@rem is used to find the configuration file.
@set TUXCONFIG=%RESULTSDIR%\tuxconfig

@rem Make sure that the proper bin directories are in "PATH".
@set ADD_TO_PATH=%TUXDIR%\bin
@echo %PATH% | findstr %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%
@set ADD_TO_PATH=%TUXDIR%\lib
@echo %PATH% | findstr %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%

@rem Cleanup in case this isn't the first time this
@rem script is has been run.
@%MAKE% clean > NUL: 2>&1
@echo     cleaned up

@rem Make a directory to capture the results from running
@rem this script.
@mkdir %RESULTSDIR% > NUL: 2>> NUL:

@rem Make a "setenv.cmd" file so that the user can
@rem manually build and run this sample later on.
@echo @set TUXDIR=%TUXDIR%>          %SETENV%
@echo @set TOBJADDR=%TOBJADDR%>>     %SETENV%
@echo @set APPDIR=%APPDIR%>>         %SETENV%
@echo @set TUXCONFIG=%TUXCONFIG%>>   %SETENV%
@echo @set PATH=%PATH%>>             %SETENV%
@echo @set RESULTSDIR=%RESULTSDIR%>> %SETENV%

@rem Make the "ubb" configuration file for this sample.

@echo *RESOURCES                               > %UBB% 2>> %LOG%
@echo     IPCKEY    %IPCKEY%                  >> %UBB% 2>> %LOG%
@echo     DOMAINID  simpapp                   >> %UBB% 2>> %LOG%
@echo     MASTER    SITE1                     >> %UBB% 2>> %LOG%
@echo     MODEL     SHM                       >> %UBB% 2>> %LOG%
@echo     LDBAL     N                         >> %UBB% 2>> %LOG%
@echo *MACHINES                               >> %UBB% 2>> %LOG%
@echo     "%HOST%"                            >> %UBB% 2>> %LOG%
@echo         LMID         = SITE1            >> %UBB% 2>> %LOG%
@echo         APPDIR       = "%APPDIR%"       >> %UBB% 2>> %LOG%
@echo         TUXCONFIG    = "%TUXCONFIG%"    >> %UBB% 2>> %LOG%
@echo         TUXDIR       = "%TUXDIR%"       >> %UBB% 2>> %LOG%
@echo         MAXWSCLIENTS = 10               >> %UBB% 2>> %LOG%
@echo         MAXACCESSERS = 200              >> %UBB% 2>> %LOG%
@echo *GROUPS                                 >> %UBB% 2>> %LOG%
@echo     SYS_GRP                             >> %UBB% 2>> %LOG%
@echo         LMID    = SITE1                 >> %UBB% 2>> %LOG%
@echo         GRPNO   = 1                     >> %UBB% 2>> %LOG%
@echo     APP_GRP1                            >> %UBB% 2>> %LOG%
@echo         LMID    = SITE1                 >> %UBB% 2>> %LOG%
@echo         GRPNO   = 2                     >> %UBB% 2>> %LOG%
@echo     APP_GRP2                            >> %UBB% 2>> %LOG%
@echo         LMID    = SITE1                 >> %UBB% 2>> %LOG%
@echo         GRPNO   = 3                     >> %UBB% 2>> %LOG%
@echo *SERVERS                                >> %UBB% 2>> %LOG%
@echo     DEFAULT:                            >> %UBB% 2>> %LOG%
@echo         RESTART = Y                     >> %UBB% 2>> %LOG%
@echo         MAXGEN  = 5                     >> %UBB% 2>> %LOG%
@echo     TMSYSEVT                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 1                     >> %UBB% 2>> %LOG%
@echo     TMFFNAME                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 2                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -N -M"         >> %UBB% 2>> %LOG%
@echo     TMFFNAME                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 3                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -N"            >> %UBB% 2>> %LOG%
@echo     TMFFNAME                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 4                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -F"            >> %UBB% 2>> %LOG%
@echo    simple_per_object_server             >> %UBB% 2>> %LOG%
@echo         SRVGRP  = APP_GRP1              >> %UBB% 2>> %LOG%
@echo         SRVID   = 1                     >> %UBB% 2>> %LOG%
@echo         MINDISPATCHTHREADS = 10         >> %UBB% 2>> %LOG%
@echo         MAXDISPATCHTHREADS = 100        >> %UBB% 2>> %LOG%
@echo         CONCURR_STRATEGY = PER_OBJECT   >> %UBB% 2>> %LOG%
@echo         RESTART = N                     >> %UBB% 2>> %LOG%
@echo     simple_per_request_server           >> %UBB% 2>> %LOG%
@echo         SRVGRP  = APP_GRP2              >> %UBB% 2>> %LOG%
@echo         SRVID   = 2                     >> %UBB% 2>> %LOG%
@echo         MINDISPATCHTHREADS = 10         >> %UBB% 2>> %LOG%
@echo         MAXDISPATCHTHREADS = 100        >> %UBB% 2>> %LOG%
@echo         CONCURR_STRATEGY = PER_REQUEST  >> %UBB% 2>> %LOG%
@echo         RESTART = N                     >> %UBB% 2>> %LOG%
@echo     ISL                                 >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 5                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -n %TOBJADDR%" >> %UBB% 2>> %LOG%
@echo *SERVICES                               >> %UBB% 2>> %LOG%

@rem Make a file containing the user input for the client.
@echo 4 >                                                           %INPUT% 2>> %LOG%
@echo AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz>>        %INPUT% 2>> %LOG%
@echo AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz>>        %INPUT% 2>> %LOG%

@rem Make a file with the expected output from the client.
@echo native>                                                       %EXPECTED_OUTPUT% 2>> %LOG%
@echo Number of simultaneous requests to post (1-50)? String to convert using thread-per-request server?Sending 4 deferred forward_lower requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo Sending 4 deferred forward_upper requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo String to convert using thread-per-object server?Sending 4 deferred forward_lower requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo Sending 4 deferred forward_upper requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo remote>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo Number of simultaneous requests to post (1-50)? String to convert using thread-per-request server?Sending 4 deferred forward_lower requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo Sending 4 deferred forward_upper requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo String to convert using thread-per-object server?Sending 4 deferred forward_lower requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #0 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #1 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #2 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_lower request #3 returned:aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo Sending 4 deferred forward_upper requests>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #0 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #1 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #2 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%
@echo forward_upper request #3 returned: AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ>> %EXPECTED_OUTPUT% 2>> %LOG%

@echo     prepared

@rem Build the sample.
@%MAKE% >> %LOG% 2>&1
@if ERRORLEVEL 1 goto build_error
@echo     built

@rem Load the configuration file.
@tmloadcf -y %UBB% >> %LOG% 2>&1
@if ERRORLEVEL 1 goto ubb_error
@echo     loaded ubb

@rem Startup the server.
@tmboot -y >> %LOG% 2>&1
@if ERRORLEVEL 1 goto boot_error
@echo     booted

@rem Run the client and capture the output.
@echo native>                             %OUTPUT% 2>> %LOG%
@simple_client                 <%INPUT% >>%OUTPUT% 2>&1
@echo remote>>                            %OUTPUT% 2>> %LOG%
@simple_client -ORBid BEA_IIOP <%INPUT% >>%OUTPUT% 2>&1

@rem See if we got the expected output.
@rem Since comp asks if it should compare nore files,
@rem send in the answer "no".
@echo no | comp %OUTPUT% %EXPECTED_OUTPUT% > NUL: 2>&1
@if ERRORLEVEL 1 goto run_error
@echo     ran
@goto shutdown

:run_error
@echo     run error
@set ERROR=y
@goto shutdown

:boot_error
@echo     boot error
@set ERROR=y
@goto shutdown

:shutdown
@rem Shutdown the server
@tmshutdown -y >> %LOG% 2>&1
@if ERRORLEVEL 1 goto shutdown_error
@echo     shutdown
@goto end

:ubb_error
@echo     configuration error
@set ERROR=y
@goto end

:build_error
@echo     build error
@set ERROR=y
@goto end

:shutdown_error
@echo     shutdown error
@set ERROR=y
@goto end

:end
@rem Capture logs, etc. that are created when the sample is run.
@move ULOG*  %RESULTSDIR% > NUL: 2>&1
@move *.trc  %RESULTSDIR% > NUL: 2>&1
@move *.dat  %RESULTSDIR% > NUL: 2>&1
@move stdout %RESULTSDIR% > NUL: 2>&1
@move stderr %RESULTSDIR% > NUL: 2>&1
@echo     saved results

@rem Tell the user whether or not we successfully ran the sample.
@if     defined ERROR echo   FAILED
@if NOT defined ERROR echo   PASSED
@goto :EOF

:tuxdir_not_defined
@echo Error : The TUXDIR environment variable is not defined
@goto :EOF

:tuxdir_not_absolute_pathname
@echo Error : The TUXDIR environment variable is not an absolute pathname
@goto :EOF

:syntax_error
@echo Syntax : runme.cmd
@goto :EOF

@rem NOTE : The following section has nothing to do with
@rem developing applications and can be ignored.  It is used to
@rem compute the current working directory.
@rem
@rem The routine "compute_pwd" records the short name of the
@rem current working directory in the environment variable "PWD".
@rem It does this by running the "cd" command (which prints out
@rem the current directory) and capturing the output by using the
@rem "for" command.
@rem
@rem Since the current directory name can have spaces in it,
@rem it has to be converted to a "short" name.  This is done
@rem by using "%%~fsi". (%%i is the variable containing the
@rem working directory with spaces, f = full pathname,
@rem s = short name.)
@rem
@rem Notice that "tokens=*" is specified in the "for" command.
@rem This ensures that all of the characters in the results
@rem of "cd" are put in the variable %%i instead of all
@rem the characters up to the first space in the pathname.

:compute_pwd
@FOR /F "tokens=*" %%i in ('cd') DO @set PWD=%%~fsi
@goto :eof
