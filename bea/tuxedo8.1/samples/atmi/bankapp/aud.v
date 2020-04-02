#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/aud.v	$Revision: 1.5 $"

VIEW aud
$ /* View structure for audit information */
#type  cname fbname count flag size null
long    b_id     BRANCH_ID  1  -    -    0
float   balance  BALANCE    1  -    -    0.0
string  ermsg    STATLIN    1  -    80   ""
END
