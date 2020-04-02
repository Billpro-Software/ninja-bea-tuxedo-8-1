#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/usrevtf.sh	$Revision: 1.5 $"

#
# File to create ENVFILE for use by TMUSREVT server
#
cat <<! >${ENVFILE}
FIELDTBLS=${FIELDTBLS}
FLDTBLDIR=${FLDTBLDIR}
!
