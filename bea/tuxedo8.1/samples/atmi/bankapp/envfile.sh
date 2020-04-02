#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/envfile.sh	$Revision: 1.5 $"

#
# File to create ENVFILE file for use by tmloadcf(1)
#
cat <<! >${ENVFILE}
FIELDTBLS=${FIELDTBLS}
FLDTBLDIR=${FLDTBLDIR}
VIEWDIR=${VIEWDIR}
VIEWFILES=${VIEWFILES}
MASKPATH=${MASKPATH}
!
