@rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@rem -----------------------------------------------------------------
@rem
@rem setenvs.cmd
@rem
@rem NT script to set environment variables needed to build and
@rem run the university sample application
@rem
@rem Edit any item beginning with the text "MY_" to reflect your
@rem particular site configuration data.
@rem
@rem Also, check that the values of TUXDIR, ORACLE_HOME
@rem and JDKDIR are correct (this file contains typical values)
@rem
@rem BEA Systems Inc. sample code
@rem
@rem -----------------------------------------------------------------

@rem Pathname of your copy of this sample application.
@rem Must match "APPDIR" in "ubb_s.nt"
@set APPDIR=C:\MY_APP_DIR

@rem Pathname of the tuxconfig file.
@rem Must match "TUXCONFIG" in "ubb_s.nt"
@set TUXCONFIG=%APPDIR%\tuxconfig

@rem Pathname of the Tuxedo installation.
@rem Must match "TUXDIR" in "ubb_s.nt"
@if defined TUXDIR goto tuxdir_set
@set TUXDIR=C:\Tuxdir
@echo Warning : TUXDIR not set.
@echo           Using %TUXDIR%
:tuxdir_set

@rem Root of the Visual C++ installation
@rem Note that the Oracle Pro*C/C++ compiler uses short (8 char) directory
@rem names. Hence 'Program Files' is changed to 'Progra~1`
@if defined MSVCDIR goto msvcdir_set
@set MSVCDIR=C:\Progra~1\DevStu~1\Vc
@echo Warning : MSVCDIR not set.
@echo           Using %MSVCDIR%
:msvcdir_set

@rem Directory of the ORACLE installation.
@if defined ORACLE_HOME goto oracle_home_set
@set ORACLE_HOME=C:\Orant
@echo Warning : ORACLE_HOME not set.
@echo           Using %ORACLE_HOME%
:oracle_home_set

@rem Name of the ORACLE Programmer C/C++ SQL Precompiler.
@if exist %ORACLE_HOME%\Bin\Proc.exe   set PROC=Proc
@if exist %ORACLE_HOME%\Bin\Proc22.exe set PROC=Proc22
@if exist %ORACLE_HOME%\Bin\Proc80.exe set PROC=Proc80

@rem Directory of the ORACLE Programmer C/C++ SQL Precompiler.
@if "%PROC%" == "Proc"   @set PRODIR=Proc
@if "%PROC%" == "Proc22" @set PRODIR=Pro22
@if "%PROC%" == "Proc80" @set PRODIR=Pro80

@rem Userid/Password of the default ORACLE database.
@if defined USERID goto userid_set
@set USERID=scott/tiger
@echo Warning : USERID not set.
@echo           Using %USERID%
:userid_set

@rem Directory of the JDK 1.2 installation
@if defined JDKDIR goto jdkdir_1_2_set
@set JDKDIR=C:\jdk1.2
@echo Warning : JDKDIR not set.
@echo           Using %JDKDIR%
:jdkdir_1_2_set

@rem Typical path
@set PATH=%ORACLE_HOME%\bin;%PATH%
@set PATH=%JDKDIR%\bin;%PATH%
@set PATH=%TUXDIR%\bin;%TUXDIR%\lib;%PATH%
@set PATH=%APPDIR%;%PATH%

@rem Typical class path
@set CLASSPATH=.;%CLASSPATH%
@set CLASSPATH=%TUXDIR%\udataobj\java\jdk\m3envobj.jar;%CLASSPATH%
@set CLASSPATH=%APPDIR%;%CLASSPATH%

@set IDLTOJAVA=idltojava

@rem For client-only machines, the address of the server's
@rem listener must be specified in the "TOBJADDR" environment
@rem variable.  It must exactly match (including case)
@rem the host and port specified in the server's ubb file.
@set TOBJADDR=//MY_MACHINE:MY_PORT_NUMBER
