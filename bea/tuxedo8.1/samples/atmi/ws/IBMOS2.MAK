#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# Copyright (c) 1991 USL
# All rights reserved

# THIS IS UNPUBLISHED PROPRIETARY
# SOURCE CODE OF USL
# The copyright notice above does not
# evidence any actual or intended
# publication of such source code.
#
#ident	"@(#) samples/atmi/ws/IBMOS2.MAK	$Revision: 1.5 $"
CC=icc

# flags for dos, windows, OS2, PM
OCFLAGS=-Ti+ -Q+ -O- -Dtran -D_TM_OS2 -I$(TUXDIR)/include

# default sockets library for dos, windows, OS2

all:	bankappp.exe

bankflds.h:	bankflds
	$(TUXDIR)\bin\mkfldhdr bankflds
#
# OS2 APPLICATION using vio functions
BANKAPPO.EXE:	BANKAPPO.OBJ
	$(TUXDIR)\bin\buildclt -v -O -ci \
		-f "/NOI /ST:25000 /CO bankappo.obj" \
		-o bankappo.exe

BANKAPPO.OBJ:	BANKAPPO.C BANKFLDS.H
	$(CC) $(OCFLAGS) -c BANKAPPO.C

BANKAPPO.C:	BANKAPP.C
	IF EXIST BANKAPPO.C DEL BANKAPPO.C
	COPY BANKAPP.C BANKAPPO.C

#
# OS2 Presentation Manager
bankappp.exe: bankappp.obj bankappp.res bankappp.def dollar.ico
	$(TUXDIR)\bin\buildclt -v -P \
		-f "/CO /NOI bankappp.obj" \
		-d bankappp.def -o bankappp.exe
	rc bankappp.res

bankappp.obj:	bankappp.c bankflds.h bankapp.h
	$(CC) $(OCFLAGS) -c bankappp.c

bankappp.res:	bankappp.rc dollar.ico bankapp.h
	rc -r bankappp.rc

dollar.ico: dollaric.Z uudecode.exe
	uudecode.exe dollaric.Z

# Miscellaneous
clean:
	del *.exe
	del *.obj
	del *.res
