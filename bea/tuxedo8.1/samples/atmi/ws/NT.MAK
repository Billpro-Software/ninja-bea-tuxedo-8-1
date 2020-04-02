#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# Copyright (c) 1991 USL
# All rights reserved

# THIS IS UNPUBLISHED PROPRIETARY
# SOURCE CODE OF USL
# The copyright notice above does not
# evidence any actual or intended
# publication of such source code.
#
#ident	"@(#) samples/atmi/ws/NT.MAK	$Revision: 1.5 $"

# flags for dos, windows, OS2, PM
!include <ntwin32.mak>
NTFLAGS=-Zi -Od -Dtran -DWIN32

all:	bankappn.exe

# Windows NT APPLICATION
bankappn.exe:	bankappw.obj bankappw.res
	$(TUXDIR)\bin\buildclient -v -w -f "bankappw.obj bankappw.res" -v \
		-l "$(winlibs)" -obankappn.exe

bankappw.obj:	bankappw.c bankapp.h bankflds.h
	$(CC) -c -I$(TUXDIR)/include $(NTFLAGS) bankappw.c

bankappw.res:	bankappw.rc bankapp.h balance.dlg deposit.dlg transfer.dlg \
	withdraw.dlg money.ico close.dlg open.dlg
	rc -r bankappw.rc

money.ico: moneyico.Z uudecode.exe
	uudecode.exe moneyico.Z

bankflds.h:	bankflds
	$(TUXDIR)\bin\mkfldhdr bankflds

uudecode.exe:	uudecode.c
	$(CC) uudecode.c

# Miscellaneous
clean:
	del *.exe
	del *.obj
	del *.res
	del *.ico
