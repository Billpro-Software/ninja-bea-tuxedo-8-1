#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/driver.sh	$Revision: 1.5 $"

if [ -z "${TUXDIR}" ] ; then
	if [ ! -z "${ROOTDIR}" ] ; then
		TUXDIR=$ROOTDIR
		export TUXDIR
	fi
fi

############################################################
# NOTE: If authentication is configured, set the enviroment
# variable APP_PW to the application password and export it.
# This password must be the same as that specified when the 
# TUXEDO source configuration file was compiled using
# tmloadcf(1).
# Example: Bourne shell/Korn shell users would type
#	$ APP_PW=<application_passwd> ; export APP_PW
# See ud (1)
############################################################

gentran $* | ud -t 30 2>&1 | tee driv.out
