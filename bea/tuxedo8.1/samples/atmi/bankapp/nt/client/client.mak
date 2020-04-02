#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#	Copyright (c) 1995 BEA Systems, Inc.
#	All rights reserved
#
#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF
#	BEA Systems, Inc.
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.
#
#
#ident	"@(#) samples/atmi/bankapp/nt/client/client.mak	$Revision: 1.4 $"

!include <ntwin32.mak>

CCFLAGS=-MD -Zi -Od -Dtran -DNOWHAT=1 -DWIN32 -DNULL=0

!IF "$(CPU)" == "i386"
CCFLAGS=$(CCFLAGS) -D_X86_=1
MACH=IX86
!ELSE
!IF "$(CPU)" == "ALPHA"
CCFLAGS=$(CCFLAGS) -D_ALPHA_=1
MACH=ALPHA
!ENDIF
!ENDIF

all:	bankappn.exe

# Windows NT APPLICATION
bankappn.exe:	bankappw.obj bankappn.res bankappn.rbj
	$(TUXDIR)\bin\buildclient -f "bankappw.obj bankappn.rbj" -v \
		-o bankappn.exe
	copy bankappn.exe ..\..\bankappn.exe

bankappw.obj:	bankappw.c bankapp.h bankflds.h
	$(CC) -c -I$(TUXDIR)/include $(cflags) $(CCFLAGS) bankappw.c

bankappn.res:	bankappw.rc bankapp.h balance.dlg deposit.dlg transfer.dlg \
	withdraw.dlg money.ico close.dlg open.dlg user.dlg
	rc -DNOWHAT=1 -r bankappw.rc

bankappn.rbj: bankappw.res
	cvtres -machine:$(MACH) -nologo bankappw.res -out:bankappn.rbj

money.ico: moneyico.Z uudecode.exe
	uudecode.exe moneyico.Z

uudecode.exe:	uudecode.c
	$(CC) -c -DNOWHAT=1 uudecode.c
	link -out:uudecode.exe -subsystem:console uudecode.obj libc.lib kernel32.lib

bankflds.h: ..\..\bankflds.h
	copy ..\..\bankflds.h bankflds.h

# Miscellaneous
clean:
	@echo off & for %%i in (*.exe *.obj *.res *.ico *.rbj *.pdb bankflds.h) do \
	if exist %%i del %%i
