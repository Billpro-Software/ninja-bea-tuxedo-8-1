#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# Copyright (c) 1991 USL
# All rights reserved

# THIS IS UNPUBLISHED PROPRIETARY
# SOURCE CODE OF USL
# The copyright notice above does not
# evidence any actual or intended
# publication of such source code.
#
#ident	"@(#) samples/atmi/ws/BC.MAK	$Revision: 1.5 $"
.SWAP
CC=bcc
MODEL=m
BORLANDC=C:\BC4
INCPATH=$(BORLANDC)\include
CFLAGS=-v -m$(MODEL) -I$(INCPATH) -I$(TUXDIR)\include -Dtran


all:	bankappw.exe

#
# DOS APPLICATION PROGRAM
# Note:  Borland is not a supported compiler for DOS
#        because of static library linking conflicts.

#
# WINDOWS APPLICATION PROGRAM
bankappw.exe:	bankappw.obj bankappw.res bankappw.def
	$(TUXDIR)\bin\buildclt -W -m$(MODEL) -cb -f "-ln -l-c -v bankappw.obj" -v \
		-dbankappw.def -obankappw.exe
	rc -k bankappw.res bankappw.exe

bankappw.obj:	bankappw.c bankapp.h bankflds.h
	$(CC) -c -W $(CFLAGS) -D_TM_WIN bankappw.c

bankflds.h:	bankflds
	$(TUXDIR)\bin\mkfldhdr bankflds

bankappw.res:	bankappw.rc bankapp.h balance.dlg deposit.dlg transfer.dlg \
	withdraw.dlg money.ico close.dlg open.dlg
	rc -r -i$(INCPATH) bankappw.rc

money.ico: moneyico.Z uudecode.exe
	uudecode.exe moneyico.Z

uudecode.exe:	uudecode.c
	$(CC) $(CFLAGS) uudecode.c

clean:
	del bankappw.exe
	del uudecode.exe
	del money.ico
	del bankflds.h
	del *.obj
	del *.res
