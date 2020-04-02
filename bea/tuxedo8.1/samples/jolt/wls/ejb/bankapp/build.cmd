@rem	(c) 2003 BEA Systems, Inc. All Rights Reserved.
@REM Copyright (c) 2000 BEA Systems, Inc. All Rights Reserved.
@REM You must set your environment by running the setEnv shell script
@REM prior to executing this script. Make sure that WLHOME and JAVA_HOME are
@REM set and pointing to the correct directory.

@REM Add jolt classes to the classpath
set MYCLASSPATH=%WL_HOME%\lib\jolt.jar;%WL_HOME%\lib\joltjse.jar;%WL_HOME%\lib\joltwls.jar;%CLASSPATH%

@REM Create the build directory, and copy the deployment descriptors into it
mkdir build build\META-INF 
copy *.xml build\META-INF

@REM Compile ejb classes into the build directory (jar preparation)
javac -d build -classpath %MYCLASSPATH% Teller.java TellerHome.java TellerResult.java ProcessingErrorException.java TransactionErrorException.java TellerBean.java

@REM Make a standard ejb jar file, including XML deployment descriptors
cd build
jar cv0f std_ejb_jolt_bankapp.jar META-INF examples
cd ..

@REM Run ejbc to create the deployable jar file
java -classpath %WL_HOME%/lib/weblogic_sp.jar;%WL_HOME%/lib/weblogic.jar;%WL_HOME%/lib/jolt.jar;%WL_HOME%/lib/joltjse.jar;%WL_HOME%/lib/joltwls.jar weblogic.ejbc -compiler javac build\std_ejb_jolt_bankapp.jar %APPLICATIONS%\ejb_jolt_bankapp.jar

@REM Compile ejb interfaces & client app into the clientclasses directory
javac -d %CLIENT_CLASSES% -classpath %MYCLASSPATH% Teller.java TellerHome.java TellerResult.java ProcessingErrorException.java TransactionErrorException.java Client.java

