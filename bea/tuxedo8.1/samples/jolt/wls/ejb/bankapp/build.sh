#!/bin/sh

# Copyright (c) 2003 BEA Systems, Inc. All Rights Reserved.
# You must set your environment by running the setExamplesEnv shell script 
# prior to executing this script.
# Create the build directory, and copy the deployment descriptors into it
mkdir -p build build/META-INF
cp -f ejb-jar.xml weblogic-ejb-jar.xml build/META-INF

# Compile EJB classes into the build directory (jar preparation)
javac -d build Teller.java TellerHome.java ProcessingErrorException.java TransactionErrorException.java TellerResult.java TellerBean.java

# Make a EJB jar file, including XML deployment descriptors
(cd build; jar cv0f std_ejb_jolt_bankapp.jar META-INF examples)
# Run EJBC on jar file
java -classpath $CLASSPATH weblogic.ejbc -compiler javac build/std_ejb_jolt_bankapp.jar $APPLICATIONS/ejb_jolt_bankapp.jar

# Compile EJB interfaces & client app into the clientclasses directory
javac -d $CLIENT_CLASSES Teller.java TellerHome.java TellerResult.java ProcessingErrorException.java TransactionErrorException.java Client.java

