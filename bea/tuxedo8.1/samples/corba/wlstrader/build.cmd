@REM Copyright (c) 2003 BEA Systems, Inc. All Rights Reserved.
@REM You must set your environment by running the setExamplesEnv script 
@REM prior to executing this script.

@REM Adjust these variables to match your environment
set TUXDIR=C:\TUXDIR
set IDL2CPP=%TUXDIR%\bin\idl -I%TUXDIR%\include -IidlSources

@REM Create the build directory, and copy the deployment descriptors into it
mkdir build build\META-INF build\images
copy *.xml build\META-INF
copy *.gif build\images

@REM Compile ejb classes into the build directory (jar preparation)
javac -d build Trader.java TraderHome.java TradeResult.java TraderBean.java

@REM Make a EJB jar file, including XML deployment descriptors
cd build
jar cv0f std_ejb_over_iiop.jar META-INF examples images
cd ..

@REM Run ejbc on jar file
java weblogic.ejbc -compiler javac -keepgenerated -idl -idlOverwrite -idlDirectory idlSources -iiop build\std_ejb_over_iiop.jar %APPLICATIONS%\ejb_over_iiop.jar

@REM Compile EJB interfaces & client app into the clientclasses directory
javac -d %CLIENT_CLASSES% Trader.java TraderHome.java TradeResult.java Client.java

@REM Run idl2cpp to create C++ sources
%IDL2CPP% idlSources\examples\rmi_iiop\ejb\rmi_iiop\Trader.idl
%IDL2CPP% -i idlSources\examples\rmi_iiop\ejb\rmi_iiop\TradeResult.idl
%IDL2CPP% idlSources\examples\rmi_iiop\ejb\rmi_iiop\TraderHome.idl
%IDL2CPP% idlSources\java\io\Serializable.idl
%IDL2CPP% idlSources\java\lang\Throwable.idl
%IDL2CPP% idlSources\java\lang\_Ex.idl
%IDL2CPP% idlSources\java\lang\_Exception.idl
%IDL2CPP% idlSources\java\lang\_Object.idl
%IDL2CPP% idlSources\java\rmi\Remote.idl
%IDL2CPP% idlSources\javax\ejb\CreateEx.idl
%IDL2CPP% idlSources\javax\ejb\CreateException.idl
%IDL2CPP% idlSources\javax\ejb\EJBHome.idl
%IDL2CPP% idlSources\javax\ejb\EJBMetaData.idl
%IDL2CPP% idlSources\javax\ejb\EJBObject.idl
%IDL2CPP% idlSources\javax\ejb\Handle.idl
%IDL2CPP% idlSources\javax\ejb\HomeHandle.idl
%IDL2CPP% idlSources\javax\ejb\RemoveEx.idl
%IDL2CPP% idlSources\javax\ejb\RemoveException.idl


@REM Build the Tuxedo/CORBA Client
%TUXDIR%\bin\buildobjclient -v -o tuxclient.exe -f "-Zi tuxclient.cpp Trader_c.cpp TradeResult_c.cpp TradeResult_i.cpp TraderHome_c.cpp Serializable_c.cpp Throwable_c.cpp _Ex_c.cpp _Exception_c.cpp _Object_c.cpp Remote_c.cpp CreateEx_c.cpp CreateException_c.cpp EJBHome_c.cpp EJBMetaData_c.cpp EJBObject_c.cpp Handle_c.cpp HomeHandle_c.cpp RemoveEx_c.cpp RemoveException_c.cpp"
