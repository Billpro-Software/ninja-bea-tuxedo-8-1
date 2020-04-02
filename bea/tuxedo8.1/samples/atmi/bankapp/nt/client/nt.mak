#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#	Copyright (c) 1995 Novell, Inc.	
#	  All Rights Reserved 	 

#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF 
#	Novell, Inc.  
#	The copyright notice above does not evidence any  
#	actual or intended publication of such source code.

#Copyright (c) 1995 Novell, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/nt/client/nt.mak	$Revision: 1.4 $"

!include <ntwin32.mak>

# flags for dos, windows, OS2, PM
CCFLAGS=-MD -Zi -Od -Dtran -D "NOWHAT=1" -DWIN32 -DNULL=0

!IF "$(CPU)" == "i386"
CCFLAGS=$(CCFLAGS) -D_X86_=1
MACH=IX86
!ELSE
!IF "$(CPU)" == "ALPHA"
CCFLAGS=$(CCFLAGS) -D_ALPHA_=1
MACH=ALPHA
!ENDIF
!ENDIF

all:	bankappn.exe wbankappn.exe

# Windows NT APPLICATION
bankappn.exe:	bankappw.obj bankappn.res bankappn.rbj
	$(TUXDIR)\bin\buildclient -f "bankappw.obj bankappn.rbj" -v \
		-o bankappn.exe
	copy bankappn.exe ..\..\bankappn.exe

# /WS client on NT or Win95
wbankappn.exe:	bankappw.obj bankappn.res bankappn.rbj
	$(TUXDIR)\bin\buildclient -f "bankappw.obj bankappn.rbj" -v -w \
		-o wbankappn.exe
	copy wbankappn.exe ..\..\wbankappn.exe

bankappw.obj:	bankappw.c bankapp.h bankflds.h
	$(CC) -c -I$(TUXDIR)/include $(cflags) $(CCFLAGS) bankappw.c

bankappn.res:	bankappw.rc bankapp.h balance.dlg deposit.dlg transfer.dlg \
	withdraw.dlg money.ico close.dlg open.dlg
	rc -D "NOWHAT=1" -r bankappw.rc

bankappn.rbj: bankappw.res
    cvtres -machine:$(MACH) -nologo bankappw.res -out:bankappn.rbj

money.ico: moneyico.Z uudecode.exe
	uudecode.exe moneyico.Z

uudecode.exe:	uudecode.c
	$(CC) -c -D "NOWHAT=1" uudecode.c
	link -out:uudecode.exe -subsystem:console uudecode.obj libc.lib kernel32.lib

bankflds.h: ..\..\bankflds.h
	copy ..\..\bankflds.h bankflds.h

# Miscellaneous
clean:
	del *.exe
	del *.obj
	del *.res
	del *.ico
	del *.rbj
