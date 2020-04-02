@rem -----------------------------------------------------------------
@rem
@rem Chatsetup.cmd
@rem
@rem NT script to setup the environment for the BEA WLE Chat application
@rem You should copy the Chat directory from the WLE sample directory to
@rem   your own directory and then change to your directory. 
@rem Next, execute this command file. It will create further subdirectories 
@rem   as needed but expects expect that all the sources and command files
@rem   are at the right relative place; that is, they are in the same directory 
@rem   as this command file.
@rem
@rem -----------------------------------------------------------------

@echo Setting up the BEA WLE Chat application

@rem Check that the user properly called this script.
@if "%1" NEQ "" goto syntax_error

@rem Shortcut for calling "nmake".
@set MAKE=nmake/NOLOGO -f ChatRoom.nt

@rem Cleanup in case this isn't the first time this
@rem script is has been run.
@%MAKE% adminclean > NUL: 2>&1
@echo     Cleaned up the previous WLE administrative setup

@rem If this is the first time this file has been run, we
@rem need to create a subdirectory "Admin", which will 
@rem keep all the administrative parts of the application.
@if NOT EXIST Admin mkdir Admin

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

@rem APPDIR is a special environment variable that is used
@rem by WLE when running server apps.  It needs to be set
@rem to be set to the absolute pathname of the 
@rem Admin directory.  Since NT doesn't have a command
@rem to get the current Admin directory (like "pwd" on
@rem Unix), we've written a function to do it:
@call :compute_pwd
@set APPDIR=%PWD%\Admin

@rem TOBJADDR is another special environment variable that
@rem is used by WLE when running remote C++ clients.
@set TOBJADDR=//%HOST%:%PORT%

@rem Did we encounter an error while running this script?
@set ERROR=

@rem The pathname of the log file used to capture the
@rem output of running this script (except the build)
@set LOG=%APPDIR%\setup.log

@rem The pathname of the setenv.cmd file.
@set SETENV=%APPDIR%\setenv.cmd

@rem The pathname of the configuration file.
@set UBB=%APPDIR%\ubb

@rem TUXCONFIG is another special environment variable that
@rem is used by WLE to find the configuration file.
@set TUXCONFIG=%APPDIR%\tuxconfig

@rem Make sure that the proper WLE directories are
@rem in "PATH".
@set ADD_TO_PATH=%TUXDIR%\bin
@echo %PATH% | findstr %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%
@set ADD_TO_PATH=%TUXDIR%\lib
@echo %PATH% | findstr %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%

@rem Create a "setenv.cmd" file so that the user can
@rem manually build and run this sample later on.

@echo @rem File "setenv.cmd" is used to set environment without running WLEChatSetup again> %SETENV%
@echo @rem This file automatically generated from WLEChatSetup of the distribution CD>> %SETENV%
@echo @rem>>                                       %SETENV%
@echo @rem Pathname of the WLE installation must match "TUXDIR" in UBB>> %SETENV%
@echo @if defined TUXDIR goto tuxdir_set>>         %SETENV%
@echo @if defined TUXDIR goto tuxdir_set>>         %SETENV%
@echo @set TUXDIR=%TUXDIR%>>                       %SETENV%
@echo @echo Warning : TUXDIR not set.>>            %SETENV%
@echo @echo           Using %TUXDIR%>>             %SETENV%
@echo @:tuxdir_set>>                               %SETENV%
@echo @rem>>                                       %SETENV%
@echo @set TOBJADDR=%TOBJADDR%>>                   %SETENV%
@echo @rem>>                                       %SETENV%
@echo @rem Pathname of admin files for the application.>>        %SETENV%
@echo @rem Must match APPDIR in the config file (aka UBB file)>> %SETENV%
@echo @set APPDIR=%APPDIR%>>                       %SETENV%
@echo @rem>>                                       %SETENV%
@echo @rem Pathname of the app config file.>>      %SETENV%
@echo @rem Must match "TUXCONFIG" in UBB>>         %SETENV%
@echo @set TUXCONFIG=%TUXCONFIG%>>                 %SETENV%
@echo @rem>>                                       %SETENV%
@echo @rem Typical path>>                          %SETENV%
@echo @set PATH=%PATH%>>                           %SETENV%
@echo     Created file %SETENV% for running later

@rem Create the "ubb" configuration file for this sample.
@echo #Configuration file for the Chat example.                  > %UBB% 2>  %LOG%
@echo #This file automatically generated from WLEChatSetup       >> %UBB% 2>> %LOG%
@echo #  command; change at your own risk.                      >> %UBB% 2>> %LOG%
@echo #                                                         >> %UBB% 2>> %LOG%
@echo *RESOURCES                              >> %UBB% 2>> %LOG%
@echo     IPCKEY    %IPCKEY%                  >> %UBB% 2>> %LOG%
@echo     DOMAINID  chatapp                   >> %UBB% 2>> %LOG%
@echo     MASTER    SITE1                     >> %UBB% 2>> %LOG%
@echo     MODEL     SHM                       >> %UBB% 2>> %LOG%
@echo     LDBAL     N                         >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo *MACHINES                               >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo #   The name of the server machine      >> %UBB% 2>> %LOG%
@echo     "%HOST%"                            >> %UBB% 2>> %LOG%
@echo         LMID         = SITE1            >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo #   Pathname of default startup directory for the appl.   >> %UBB% 2>> %LOG%
@echo #   Must match "APPDIR" in the environment variables      >> %UBB% 2>> %LOG%
@echo         APPDIR       = "%APPDIR%"       >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo #   Pathname of the tuxconfig file.     >> %UBB% 2>> %LOG%
@echo #   Must match "TUXCONFIG" in the environment variables   >> %UBB% 2>> %LOG%
@echo         TUXCONFIG    = "%TUXCONFIG%"    >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo #   Pathname of the WLE installation.    >> %UBB% 2>> %LOG%
@echo #   Must match "TUXDIR" in the environment variables      >> %UBB% 2>> %LOG%
@echo         TUXDIR       = "%TUXDIR%"       >> %UBB% 2>> %LOG%
@echo         MAXWSCLIENTS = 10               >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo *GROUPS                                 >> %UBB% 2>> %LOG%
@echo     SYS_GRP                             >> %UBB% 2>> %LOG%
@echo         LMID    = SITE1                 >> %UBB% 2>> %LOG%
@echo         GRPNO   = 1                     >> %UBB% 2>> %LOG%
@echo     CHAT_GRP                            >> %UBB% 2>> %LOG%
@echo         LMID    = SITE1                 >> %UBB% 2>> %LOG%
@echo         GRPNO   = 2                     >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo *SERVERS                                >> %UBB% 2>> %LOG%
@echo # List of servers started automatically at tmboot time    >> %UBB% 2>> %LOG%
@echo #                                                         >> %UBB% 2>> %LOG%
@echo # By default, restart a server if it crashes,             >> %UBB% 2>> %LOG%
@echo #   up to 5 times in 24 hours.          >> %UBB% 2>> %LOG%
@echo     DEFAULT:                            >> %UBB% 2>> %LOG%
@echo         RESTART = Y                     >> %UBB% 2>> %LOG%
@echo         MAXGEN  = 5                     >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # The first set of servers are systems servers, the same  >> %UBB% 2>> %LOG%
@echo #   for every WLE application            >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # The first server is the BEA WLE provided System Event    >> %UBB% 2>> %LOG%
@echo #   Broker. It must be started before the NameManager     >> %UBB% 2>> %LOG%
@echo #   Service servers.                    >> %UBB% 2>> %LOG%
@echo     TMSYSEVT                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 1                     >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # TMFFNAME is a BEA M3 provided server that runs the      >> %UBB% 2>> %LOG%
@echo # FactoryFinder and supporting NameManager services       >> %UBB% 2>> %LOG% 
@echo # which maintain a mapping of application-supplied        >> %UBB% 2>> %LOG% 
@echo # names to object references.                             >> %UBB% 2>> %LOG%
@echo #                                                         >> %UBB% 2>> %LOG%
@echo # Start the NameManager Service (-N option).              >> %UBB% 2>> %LOG%
@echo #   It is being started as a Master (-M option).          >> %UBB% 2>> %LOG%
@echo     TMFFNAME                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 2                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -N -M"         >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # Start a slave NameManager Service     >> %UBB% 2>> %LOG%
@echo     TMFFNAME                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 3                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -N"            >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # Start the FactoryFinder (-F) service  >> %UBB% 2>> %LOG%
@echo     TMFFNAME                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 4                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -F"            >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # Start the Interface Repository Server >> %UBB% 2>> %LOG%
@echo     TMIFRSVR                            >> %UBB% 2>> %LOG%
@echo         SRVGRP  = SYS_GRP               >> %UBB% 2>> %LOG%
@echo         SRVID   = 6                     >> %UBB% 2>> %LOG%
@echo         CLOPT   = "-A -- -f chat.ifr" >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # Listener for IIOP clients             >> %UBB% 2>> %LOG%
@echo #   This specifies the current machine  >> %UBB% 2>> %LOG%
@echo #    port number 2500 is typical        >> %UBB% 2>> %LOG%
@echo     ISL                                 >> %UBB% 2>> %LOG%
@echo        SRVGRP  = SYS_GRP                >> %UBB% 2>> %LOG%
@echo        SRVID   = 5                      >> %UBB% 2>> %LOG%
@echo        CLOPT   = "-A -- -n %TOBJADDR% -O"  >> %UBB% 2>> %LOG%
@echo        MIN     = 1                      >> %UBB% 2>> %LOG%
@echo        MAX     = 1                      >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # Server for the Chat example           >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo # The chat server takes no parameters   >> %UBB% 2>> %LOG%
@echo     "%PWD%\ChatRoomServer.exe"          >> %UBB% 2>> %LOG%
@echo         SRVGRP  = CHAT_GRP              >> %UBB% 2>> %LOG%
@echo         SRVID   = 1                     >> %UBB% 2>> %LOG%
@echo         RESTART = N                     >> %UBB% 2>> %LOG%
@echo #                                       >> %UBB% 2>> %LOG%
@echo *SERVICES                               >> %UBB% 2>> %LOG%
@echo # empty                                 >> %UBB% 2>> %LOG%
@echo     Created an WLE configuration file in %UBB%

@rem Load the configuration file.
@tmloadcf -y %UBB% >> %LOG% 2>&1
@if ERRORLEVEL 1 goto ubb_error
@echo     WLE loaded the configuration file successfully

@rem Build the application
@echo Starting to build the application

@%MAKE%  >> build.log 2>&1
@if ERRORLEVEL 1 goto make_error
@echo ...
@echo Chat example code built successfully. Now type:
@echo       tmboot -y
@echo Then start a chat client, giving a chat room name. For example, 
@echo       ChatClient Woods
@echo You will be asked to give a handle. You might enter "Smokey".
@echo After you're signed on, enter messages. 
@echo You'll see messages from other chatters in that same chat room.
@echo You can start several clients from different windows.
@echo When you're done chatting, enter a backslash (\) and you'll be signed off.
@echo When all chatters are signed off and you're done with the application, 
@echo   to stop the application, type
@echo       tmshutdown -y
@goto end

:ubb_error
@echo     WLE configuration error
@set ERROR=y
@goto end

:end

@goto :EOF

:tuxdir_not_defined
@echo Error : The TUXDIR environment variable is not defined
@goto :EOF

:tuxdir_not_absolute_pathname
@echo Error : The TUXDIR environment variable is not an absolute pathname
@goto :EOF

:syntax_error
@echo Syntax : WLEChatSetup.cmd
@goto :EOF

:make_error
@echo Error: Build failed. Check "build.log" to see how far it got.
@echo   The build command was:
@echo       %MAKE%
@goto :EOF


@rem NOTE : The following section has nothing to do with
@rem developing WLE applications and can be ignored.  It
@rem is used to compute the current working directory.
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
