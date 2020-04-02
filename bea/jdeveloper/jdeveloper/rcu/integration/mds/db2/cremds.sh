#!/bin/sh
#
# cremds.sh
#
# Copyright (c) 2007, 2010, Oracle and/or its affiliates. All rights reserved. 
#
#    NAME
#      cremds.sh - Script to create database schema for MDS repository
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
#       cremds.sh user/password@'hostname:port:dbname'
#
#       Specify NonUnicode to create tables and stored procedures that use
#       localized character sets.
#
#    MODIFIED   (MM/DD/YY)
#      erwang    03/26/10 - Set binary mode 
#      erwang    12/14/09 - Created.

usage()
{
    echo "USAGE: cremds.sh username/password@'host:port:dbname'"
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

SQLCMD="$JRE_DIR/bin/java -classpath $CLASSPATH -Dcontinue_on_errors=TRUE -DRCU_HOME=$RCU_HOME -DORACLE_HOME=$OH -Xmx128m oracle.sysman.assistants.common.dbutil.jdbc.JDBCEngine"
SCRIPT_DIR=`pwd`

echo "========================================="
echo "Creating the tables, views, stored procedure etc."
echo "========================================="
$SQLCMD $1 DB2_SCRIPT $SCRIPT_DIR/cremds.db2 

exit



