/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/


#	Copyright (c) 1990, 1994 Novell, Inc.
#	Copyright (c) 1994 Novell
#	  All Rights Reserved

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF
#	UNIX System Laboratories, Inc.
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.

#Copyright (c) 1994 Novell, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/creditapp/aud.h	$Revision: 1.5 $"

struct aud {
 /* View structure for audit information */
	long	b_id;		/* null=0 */
	float	balance;		/* null=0.000000 */
	char	ermsg[80];		/* null="\0" */
};

