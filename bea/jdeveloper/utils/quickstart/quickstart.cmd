@ECHO OFF
REM Recommended arguments to Quickstart are
REM install.dir="product-install-dir"
REM product.alias.id="product-alias-id"
REM product.alias.version="product-alias-version"

SETLOCAL

@REM Set JAVA HOME
set  JAVA_HOME=C:\bea\jdeveloper\jdk160_21
FOR %%i IN ("%JAVA_HOME%") DO SET JAVA_HOME=%%~fsi

@REM Set BEA Home
SET BEAHOME=C:\bea\jdeveloper
FOR %%i IN ("%BEAHOME%") DO SET BEA_HOME=%%~fsi

SET JAVA=%1
IF DEFINED JAVA (
  SET JAVA=java
) ELSE (
  SET JAVA=javaw
)

cd "%BEAHOME%\utils\quickstart"

"%JAVA_HOME%\bin\%JAVA%" %JAVA_VM% -Djava.library.path="%BEAHOME%\utils\quickstart" -jar "%BEAHOME%\utils\quickstart\quickstart.jar" %*

EXIT /B %ERRORLEVEL%

ENDLOCAL
