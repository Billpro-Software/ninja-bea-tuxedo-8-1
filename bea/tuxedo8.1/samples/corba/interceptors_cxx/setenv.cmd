@rem ---------------------------------------------------------------------
@rem (c) 2003 BEA Systems, Inc. All Rights Reserved.
@rem setenv.cmd
@rem
@rem Windows script which sets the environment variables needed to build
@rem and run the interceptor c++ samples
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

@set APPDIR=%APPDIR%\app_cxx
@set HOST=%COMPUTERNAME%
@set DOMAIN_PORT=2365
@set DOMAIN_IPCKEY=42365
@set NLSPATH=%TUXDIR%\locale\C
@set TOBJADDR=//%HOST%:%DOMAIN_PORT%
@set TUXCONFIG=%APPDIR%\tuxconfig

@rem the C++ interceptors samples' common directory:
@set COMMONDIR=%APPDIR%\..\common

@rem
@rem symbols defined for building samples
@rem
@set MAKEFILE_PREFIX=nt
@set CPPCMPL=cl
@set CPPINC=-I. -I$(TUXDIR)/include
@set SYSFLAGS=-D_TOBJ -W3 -DWIN32 -DNULL=0 -MD -nologo -GX -GR -Od -Zi
@set CPPFLAGS=-D_TOBJ -W3 -DWIN32 -DNULL=0 -MD -nologo -GX -GR -Od -Zi -I. -I$(TUXDIR)/include -I$(COMMONDIR)

@rem
@rem make sure the appropriate directories are in the search path
@rem
@set ADD_TO_PATH=%APPDIR%
@echo %PATH% | findstr /L %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%

@set ADD_TO_PATH=%TUXDIR%\bin
@echo %PATH% | findstr /L %ADD_TO_PATH% > NUL: 2>&1
@if ERRORLEVEL 1 set PATH=%ADD_TO_PATH%;%PATH%

@rem export a variable which indicates that this script has been run
@rem the makefiles check that this variable has been set
@set INTERCEPTOR_CXX_SETUP=yes
