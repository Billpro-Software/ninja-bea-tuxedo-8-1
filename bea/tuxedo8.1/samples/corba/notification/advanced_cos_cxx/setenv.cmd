@rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@rem ---------------------------------------------------------------------
@rem
@rem setenv.cmd
@rem
@rem Windows script which sets the environment variables needed to build
@rem and run the advanced cos notification c++ sample
@rem
@rem BEA Systems Inc. sample code
@rem
@rem ---------------------------------------------------------------------

@rem make sure that TUXDIR has been set
@if defined TUXDIR goto SETENV
@echo ERROR : The TUXDIR environment variable is not defined
@goto :EOF

:SETENV

@rem setup the standard environment variables

@rem compute the current directory
@FOR /F "tokens=*" %%i in ('cd') DO @set APPDIR=%%~fsi

@set HOST=%COMPUTERNAME%
@set DOMAIN_PORT=2365
@set DOMAIN_IPCKEY=52365
@set NLSPATH=%TUXDIR%\locale\C
@set TOBJADDR=//%HOST%:%DOMAIN_PORT%
@set TUXCONFIG=%APPDIR%\tuxconfig

@rem make sure the appropriate directories are in the search path

@set ADD_TO_PATH=%APPDIR%
@echo %PATH% | findstr /L %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%

@set ADD_TO_PATH=%TUXDIR%\bin
@echo %PATH% | findstr /L %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%

@rem the notification samples' common directory:
@set COMMONDIR=%APPDIR%\..\common

@rem variables for setting up the queues
@set QUE_IPCKEY=52465
@set QMCONFIG=%APPDIR%\QUE

@rem variables for locating the FML field definitions (enables data filtering)
@set FLDTBLDIR32=%COMMONDIR%
@set FIELDTBLS32=news_flds

@rem export a variable which indicates that this script has been run
@rem the makefiles check that this variable has been set
@set ADVANCED_COS_CXX_SETUP=yes