#!/bin/sh
#
# $Header: cremds.sh 26-sep-2006.09:40:56 rupandey Exp $
#
# cremds.sh
#
# Copyright (c) 2008, Oracle. All rights reserved.  
#
#    NAME
#      cremds.sh - Script to create database schema for MDS repository
#
#    NOTES
#    The database user must have grant to create sequence in order to 
#    successfully use the MDS Repository.
#
#    This script should be invoked from the same directory in which 
#    the SQL scripts exist.
# 
#    This script is needed to be created to run the SQL scripts.
#    In order to be a part of the APPS ARU, all of the SQL scripts 
#    have an EXIT command; which means that we would only be able to
#    run one SQL script before SQLPLUS exited. Hence this script is 
#    used to invoke all the SQL scripts individually.
#
#    MODIFIED   (MM/DD/YY)
#    gnagaraj    07/31/08 - #(7377948) Moved XDB scripts to oraclexdb directory
#    abhatt      07/12/07 - #(6135856) Update comments, remove dbms_lock notes
#    erwang      07/06/07 - #(5528236) quit sqlplus immediately upon login
#    rupandey    05/09/07 - Modified script to create xdb tables only for MDS 
#                           development environment.
#    rupandey    09/26/06 - This script act as a wrapper and invokes cremds.sql now. 
#	   		    Any new sql script, pls script or invocation of a 
#                           procedure should be added to cremds.sql.
#    rupandey    08/24/06 - Added call to PL/SQL to load data in 
#                           MDS_XDB_TRANSFORMS table.
#    gnagaraj    06/17/06 - Move shredded tables to separate script.
#    gnagaraj    05/21/06 - Introduce mds_internal_common package.
#    abhatt      04/11/06 - Creation

#############################################################################
##   This file should be in sync with the "cremds.bat" windows batch       ##
##   file. Please update "cremds.bat" when updating this file.             ##
#############################################################################


# Check  to see if there are any Arguments

if [ $# -ge 1 ]
then 
    if [ $# -eq 2 ]
	then 
	if [ $2 = "xdb" ]
	    then
	    echo "========================================="
            echo "Creating MDS repository with XDB tables (for internal"
            echo "use by MDS development only)"
	    echo "========================================="
            # #(7377948) Create the Shredded & XDB schema
            # (note that oraclexdb dir only exists in the source control)
            cd ../oraclexdb
	    sqlplus -L -S $1 @cremds_xdb.sql
	fi
    else
	echo "========================================="
	echo "Creating MDS Repository."
	echo "========================================="
	sqlplus -L -S $1 @cremds.sql
    fi
else
    echo "Script for creating schema for the MDS repository"
    echo "Copyright(c) 2008, Oracle Corporation. All rights reserved."
    echo "Usage :"
    echo "cremds.sh the_connect_string (i.e. username/password@tnsname) "
    exit
fi
