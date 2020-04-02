@ECHO OFF
SETLOCAL

SET JAVA_HOME=C:\bea\jdeveloper\jdk160_21
FOR %%i IN ("%JAVA_HOME%") DO SET JAVA_HOME=%%~fsi

SET JAVA=%1
IF DEFINED JAVA (
  SET JAVA=java
) ELSE (
  SET JAVA=javaw
)

"%JAVA_HOME%\bin\%JAVA%" -jar patch-client.jar %*

ENDLOCAL
