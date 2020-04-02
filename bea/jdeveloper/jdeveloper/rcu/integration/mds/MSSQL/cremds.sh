#!/bin/sh
#
# cremds.sh
#
# Copyright (c) 2007, 2009, Oracle and/or its affiliates. All rights reserved. 
#
#    NAME
#      cremds.sh - Script to create database schema for MDS repository
#
#    NOTES
#      The user login should have default database set to the one which will
#      be used by MDS.  The passed-in dbuser should have the default schema 
#      that MDS is going to use.
#  
#      This batch file should be invoked from MSSQL directory of the view in
#      which the SQL scripts exist.
#
#    USAGE
#       cremds.sh user/password@hostname:port [NonUnicode]
#
#       Specify NonUnicode to create tables and stored procedures that use
#       localized character sets.
#
#    MODIFIED   (MM/DD/YY)
#     pwhaley    12/07/09 - XbranchMerge pwhaley_db2_midtier_read from main
#     pwhaley    10/15/09 - ojdl moved again: use mdstools.jar for classpath
#     pwhaley    01/23/09 - Fixed path for ojdl.
#     rupandey   07/15/08 - Fixed path for Oracle Home reorg.
#     erwang     08/21/07 - fixed ojdl path to relfect the path changes
#     pwhaley    08/01/07 - fixed line endings, set ALWAYS_BINARY_MODE (sigh)
#     pwhaley    07/17/07 - #(6189386) Created.

usage()
{
    echo "USAGE: cremds.sh username/password@host[:port] [NonUnicode]"
    echo "  where:"
    echo "     username:    db user name created for MDS"
    echo "     password:    db user password"
    echo "     host:        db server host name"
    echo "     port:        db server port number"
    echo "     NonUnicode   If specified, MDS tables will be created"
    echo "                  using CHAR and VARCHAR etc. for text columns."
    echo "                  Without this flag, MDS tables will be created"
    echo "                  using NCHAR and NVARCHAR for text columns."
    exit
}

if [ $# -gt 2 -o $# -lt 1 ]
then
    # Wrong number of arguments.
    usage
fi

MDS_VARCHAR="NVARCHAR"
if [ $# -eq 2 ]
then
    if [ $2 != "NonUnicode" ]
    then
        # Second arg isn't correct.
        usage
    fi
    MDS_VARCHAR="VARCHAR"
fi

OH=$ADE_VIEW_ROOT/oracle
PH=$OH/jdeveloper
RCU_CP=$PH/jlib/rcucommon.jar
MDS_CP=$PH/mds/bin/mdstools.jar
JRE_DIR=$OH/jdk/jre

# Set the classpath
CLASSPATH=$RCU_CP:$MDS_CP

SQLCMD="$JRE_DIR/bin/java -classpath $CLASSPATH -Dcontinue_on_errors=TRUE -DRCU_HOME=$RCU_HOME -DORACLE_HOME=$OH -DLAUNCH_MODE=$LAUNCH_MODE -Xmx128m oracle.sysman.assistants.common.dbutil.jdbc.JDBCEngine"
SCRIPT_DIR=`pwd`

echo "========================================="
echo "Creating the tables, views, stored procedure etc."
echo "========================================="
$SQLCMD $1 SQLSERVER_SCRIPT $SCRIPT_DIR/cremds.sql -v MDS_VARCHAR=$MDS_VARCHAR

exit



