@ECHO OFF
SETLOCAL

"C:\bea\jdeveloper\utils\quickstart\quickstart.cmd" install.dir="C:\bea\jdeveloper\wlserver_10.3" product.alias.id="JDeveloper 11g (11.1.1.4.0) Studio Edition" product.alias.version="11.1.1.4" %*

EXIT /B %ERRORLEVEL%

ENDLOCAL  
