@echo off

rem #
rem # UpdateLicense.cmd
rem # 
rem # How to 
rem # Execute:      UpdateLicense <new_license_file>
rem # 
rem # Prerequisite 
rem # Environment:  This cmdfile must be executed from the directory
rem #               containing your license.bea (BEA Home directory).
rem #               java (Java2) must be located in your path.
rem # 
rem # Function:     Update current license.bea with new license sections.
rem #               Invokes LicenseMerger <existing_license> <new_license>.
rem #               This will result in merged license containing both existing
rem #               and new license sections.
rem #

SETLOCAL

if "%1" == "" ( goto :USAGE )

java -cp .\utils\bsu\3rdparty.jar;.\utils\utils.jar com.bea.plateng.common.registry.LicenseMerger license.bea %1

goto :_the_end

:USAGE
  set NEWFILE="<new_license_file>"
  @echo %0: missing new license file argument
  @echo Usage: %0 "<new_license_file>"
  goto :_the_end

:_the_end

ENDLOCAL
