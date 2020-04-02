#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# Copyright (c) 1991 USL
# All rights reserved

# THIS IS UNPUBLISHED PROPRIETARY
# SOURCE CODE OF USL
# The copyright notice above does not
# evidence any actual or intended
# publication of such source code.
#
#ident	"@(#) samples/atmi/ws/MSC.MAK	$Revision: 1.5 $"
CC=cl
MODEL=L
OS2MODEL=L
INCPATH=c:\windev\include

# flags for dos, windows, OS2, PM
CFLAGS= -Zi -A$(MODEL) -Od -Dtran
CWFLAGS=-Zi -A$(MODEL) -Od -Dtran -G2sw -Zp -D_TM_WIN
OCFLAGS=-Zi -A$(OS2MODEL) -Od -Dtran -D_TM_OS2
PCFLAGS=-Zi -A$(OS2MODEL) -Od -Dtran -Od -Zd -G2sw -D_TM_OS2

# default sockets library for dos, windows, OS2
LIBNET=-l$(MODEL)libsock.lib
#
# SPX libraries for dos:
# LIBNET=-l$(MODEL)tli.lib -l$(MODEL)nwipxsp.lib

all:	bankapp.exe

#
# DOS APPLICATION USING MICROSOFT graphics/font files
# EXPECTS HELVB.FON to be in the current directory
# (normally located in \msvc\lib\font)
bankapp.exe: bankapp.obj
	$(TUXDIR)\bin\buildclt -m$(MODEL) -cm -f "/SE:200 /ST:15000 /CO bankapp.obj" -lgraphics.lib \
		$(LIBNET) -o bankapp.exe

bankapp.obj:	bankapp.c bankflds.h
	$(CC) $(CFLAGS) -c bankapp.c

bankflds.h:	bankflds
	$(TUXDIR)\bin\mkfldhdr bankflds

#
# WINDOWS APPLICATION
bankappw.exe:	bankappw.obj bankappw.res bankappw.def
	$(TUXDIR)\bin\buildclt -W -m$(MODEL) -cm \
		-f "/CO bankappw.obj" -v \
		-dbankappw.def -obankappw.exe
	rc -k bankappw.res bankappw.exe

bankappw.obj:	bankappw.c bankapp.h bankflds.h
	$(CC) -c $(CWFLAGS) bankappw.c

bankappw.res:	bankappw.rc bankapp.h balance.dlg deposit.dlg transfer.dlg \
	withdraw.dlg money.ico close.dlg open.dlg
	rc -r -i$(INCPATH) bankappw.rc

money.ico: moneyico.Z uudecode.exe
	uudecode.exe moneyico.Z

uudecode.exe:	uudecode.c
	$(CC) -A$(MODEL) uudecode.c

#
# OS2 APPLICATION using vio functions
BANKAPPO.EXE:	BANKAPPO.OBJ
	$(TUXDIR)\bin\buildclt -v -O -m$(OS2MODEL) -cm \
		-f "/NOI /SE:200 /ST:15000 /CO bankappo.obj" \
		-o bankappo.exe

BANKAPPO.OBJ:	BANKAPPO.C BANKFLDS.H
	$(CC) $(OCFLAGS) -c BANKAPPO.C

BANKAPPO.C:	BANKAPP.C
	IF EXIST BANKAPPO.C DEL BANKAPPO.C
	COPY BANKAPP.C BANKAPPO.C
#
# OS2 Presentation Manager
bankappp.exe: bankappp.obj bankappp.res bankmsc.def dollar.ico
	$(TUXDIR)\bin\buildclt -v -P -m$(OS2MODEL) -cm \
		-f "/CO /NOI bankappp.obj" \
		-d bankmsc.def -o bankappp.exe
	rc bankappp.res

bankappp.obj:	bankappp.c bankflds.h bankapp.h
	$(CC) $(PCFLAGS) -c bankappp.c

bankappp.res:	bankappp.rc dollar.ico bankapp.h
	rc -r bankappp.rc

dollar.ico: dollaric.Z uudecode.exe
	uudecode.exe dollaric.Z

# Miscellaneous
clean:
	del *.exe
	del *.obj
	del *.res
