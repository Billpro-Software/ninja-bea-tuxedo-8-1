#!/bin/sh
#
# upgmds.sh
#
# Copyright (c) 2007, 2010, Oracle and/or its affiliates. All rights reserved. 
#
#    NAME
#      upgmds.sh - Script to upgrade database schema for MDS repository
#
#    NOTES
#      The user login should have default database set to the one which will
#      be used by MDS.  The passed-in dbuser should have the default schema 
#      that MDS is going to use.
#  
#      This batch file should be invoked from db2 directory of the view in
#      which the SQL scripts exist.
#
#    USAGE
#       upgmds.sh user/password@'hostname:port:dbname' after RCU bug is fixed
#       upgmds.sh user/password@'hostname:port:database=dbname' before RCU fix
#
#    MODIFIED   (MM/DD/YY)
#    pwhaley     06/09/10 - XbranchMerge pwhaley_bug-9699967 from main
#    pwhaley     06/04/10 - #(9699967) set ALWAYS_BINARY_MODE for unix line ends.
#    pwhaley     04/19/10 - #(9585915) XbranchMerge pwhaley_upgmds_db2 from main
#    pwhaley     04/14/10 - #(9584856) Created from cremds.sh. 

usage()
{
    echo "USAGE: upgmds.sh username/password@'host:port;database=dbname'"
    echo "   or: upgmds.sh username/password@'host:port:dbname'"
    echo "  where:"
    echo "     username:    db user name created for MDS"
    echo "     password:    db user password"
    echo "     host:        db server host name"
    echo "     port:        db server port number"
    echo "     dbname:      database name"
    exit
}

if [ $# -ne 1 ]
then
    # Wrong number of arguments.
    usage
fi

OH=$ADE_VIEW_ROOT/oracle
PH=$OH/jdeveloper
RCU_HOME=$OH
RCU_CP=$PH/jlib/rcucommon.jar
MDS_CP=$PH/mds/bin/mdstools.jar
LIC_JAR=$OH/modules/com.bea.core.weblogic.workmanager_1.8.0.0.jar
JRE_DIR=$OH/jdk/jre

# Set the classpath
CLASSPATH=$RCU_CP:$LIC_JAR:$MDS_CP

# SQLCMD="$JRE_DIR/bin/java -agentlib:jdwp=transport=dt_socket,server=y,address=4000 -classpath $CLASSPATH -Dcontinue_on_errors=TRUE -DRCU_HOME=$RCU_HOME -DORACLE_HOME=$OH -Xmx128m oracle.sysman.assistants.common.dbutil.jdbc.JDBCEngine"
SQLCMD="$JRE_DIR/bin/java -classpath $CLASSPATH -Dcontinue_on_errors=TRUE -DRCU_HOME=$RCU_HOME -DORACLE_HOME=$OH -Xmx128m oracle.sysman.assistants.common.dbutil.jdbc.JDBCEngine"
SCRIPT_DIR=`pwd`

echo "========================="
echo "Upgrading the MDS schema."
echo "========================="
$SQLCMD $1 DB2_SCRIPT $SCRIPT_DIR/upgmds-rcu.db2 

exit



