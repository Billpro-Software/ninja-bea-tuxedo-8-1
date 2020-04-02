#!/bin/sh
#
# cremds_nonrcu.sh
#
# Copyright (c) 2007, 2010, Oracle and/or its affiliates. All rights reserved. 
#
#    NAME
#      cremds_nonrcu.sh - Script to create database schema for MDS repository
#
#    NOTES
#      This batch file should be invoked from DB2 directory of the view in
#      which the SQL scripts exist.
#
#      When entering the ADE view, the user has to issue 'source db2cshrc'
#      before issuing cremds_nonrcu.sh script.  db2cshrc can be found in
#      your db2 installation home.
#
#    USAGE
#       cremds_nonrcu.sh database user password
#
#    MODIFIED   (MM/DD/YY)
#     pwhaley    04/19/10 - #(9585915) XbranchMerge pwhaley_upgmds_db2 from main
#     erwang     09/10/09 - Set ALWAYS_BINARY_MODE property for the script
#     pwhaley    04/19/10 - XbranchMerge pwhaley_upgmds_db2 from main
#     pwhaley    04/14/10 - #(9584856) Split dropping for upgrade.
#     erwang     08/28/09 - Add commit at the end
#     erwang     07/20/09 - Set property for shell script
#     erwang     07/15/09 - Created.

usage()
{
    echo "USAGE: cremds_nonrcu.sh database username password"
    echo "  where:"
    echo "     database:    database name"
    echo "     username:    db user name created for MDS"
    echo "     password:    db user password"
    exit
}

if [ $# -gt 3 -o $# -lt 2 ]
then
    # Wrong number of arguments.
    usage
fi

SQLCMD="db2 -td@ -vf"
SCRIPT_DIR=`pwd`
PREP_DIR=$ADE_VIEW_ROOT/jtmds/src/tools

echo "========================================="
echo "Creating the tables, views, stored procedure etc."
echo "========================================="

if [ $# -eq  2 ]
then
    db2 connect to $1 user $2
else
    db2 connect to $1 user $2 using $3
fi

# Drop tables and procedures etc.
$SQLCMD $SCRIPT_DIR/dropmds.db2
$SQLCMD $SCRIPT_DIR/droptabs.db2

# Create tables and indexes
perl $PREP_DIR/prep.pl -v IN_TABLESPACE "" <$SCRIPT_DIR/cremdcmtbs.db2> $SCRIPT_DIR/cremdcmtbs.sql

$SQLCMD $SCRIPT_DIR/cremdcmtbs.sql

rm $SCRIPT_DIR/cremdcmtbs.sql

perl $PREP_DIR/prep.pl -v IN_TABLESPACE "" <$SCRIPT_DIR/cremdsrtbs.db2> $SCRIPT_DIR/cremdsrtbs.sql

$SQLCMD $SCRIPT_DIR/cremdsrtbs.sql

rm $SCRIPT_DIR/cremdsrtbs.sql

perl $PREP_DIR/prep.pl <$SCRIPT_DIR/cremdsinds.db2> $SCRIPT_DIR/cremdsinds.sql

$SQLCMD $SCRIPT_DIR/cremdsinds.sql

rm $SCRIPT_DIR/cremdsinds.sql

# Create MDS Procedures and Functions

perl $PREP_DIR/prep.pl <$SCRIPT_DIR/mdsinc.db2> $SCRIPT_DIR/mdsinc.sql

$SQLCMD $SCRIPT_DIR/mdsinc.sql

rm $SCRIPT_DIR/mdsinc.sql

perl $PREP_DIR/prep.pl <$SCRIPT_DIR/mdsinsr.db2> $SCRIPT_DIR/mdsinsr.sql

$SQLCMD $SCRIPT_DIR/mdsinsr.sql

rm $SCRIPT_DIR/mdsinsr.sql

# commit the changes
db2 commit

# disconnect
db2 connect reset

exit



