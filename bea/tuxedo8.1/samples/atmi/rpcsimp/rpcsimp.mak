#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#	Copyright (c) 1993 Unix System Laboratories, Inc.
#	All rights reserved
#
#	THIS IS UNPUBLISHED PROPRIETARY
#	SOURCE CODE OF Unix System Laboratories, Inc.
#	The copyright notice above does not
#	evidence any actual or intended
#	publication of such source code.
#
#ident	"@(#) samples/atmi/rpcsimp/rpcsimp.mak	$Revision: 1.5 $"
# Model for dos and windows client
MODEL=L
WINMODEL=M
CCFLAGS=-I$(TUXDIR)/include
# Generate DOS Client
dos: client.exe

simp.c:	simp.IDL
	TIDL -cstub simp.c -keep c_source -server none simp.IDL
client.obj: client.c
	CL $(CCFLAGS) -I. -c -A$(MODEL) client.c
simp.obj: simp.c
	CL $(CCFLAGS) -I. -c -A$(MODEL) simp.c
client.exe: simp.obj client.obj
	buildclt -v -m$(MODEL) -cm -o client.exe -f "/ST:15000 /CO" -f client.obj -f simp.obj -f$(MODEL)trpc.lib -l$(MODEL)libsock.lib

# Generate Windows client using MSC QuickWin
win: wclient.exe
wsimp.C:	simp.IDL
	TIDL -cstub wsimp.c -keep c_source -server none simp.IDL
wclient.c:	client.c
	copy client.c wclient.c
wclient.obj: wclient.c
	CL $(CCFLAGS) /mQ -A$(WINMODEL) -I. -D_TM_WIN -Od -c wclient.C
wsimp.obj: wsimp.c
	CL $(CCFLAGS) /mQ -A$(WINMODEL) -I. -D_TM_WIN -Od -c wsimp.C
wclient.exe: wsimp.obj wclient.obj
	link wclient.obj wsimp.obj, wclient.exe , NUL, /NOD wtrpc wtuxws libw $(WINMODEL)libcewq ,wclient.def

# Generate DLL
# Must be build with large model
dll:	WSIMPDLL.DLL
simpdll.C:	simp.IDL
	TIDL -cstub simpdll.c -keep c_source -server none simp.IDL
simpdll.OBJ:	simpdll.C
	CL $(CCFLAGS) -D_TMX="_far _pascal" -AL -I. -Aw -G2swx -Zp -D_TM_WIN -Od -c simpdll.C

WSIMPDLL.DLL:	simpdll.OBJ 
	LINK  simpdll.OBJ , WSIMPDLL.DLL /CO /ALIGN:16, NUL,  /NOD WTRPC WTUXWS LIBW LDLLCEW, WSIMPDLL.DEF
	RC -K WSIMPDLL.DLL
	IMPLIB WSIMPDLL.LIB WSIMPDLL.DLL

# Generate Windows NT client
nt: ntclient.exe
ntsimp.C:	simp.IDL
	TIDL -cstub ntsimp.c -keep c_source -server none simp.IDL
ntclient.c:	client.c
	copy client.c ntclient.c
ntclient.obj: ntclient.c
	CL $(CCFLAGS) -I. -DWIN32 -Od -c ntclient.C
ntsimp.obj: ntsimp.c
	CL $(CCFLAGS) -I. -DWIN32 -Od -c ntsimp.C
ntclient.exe: ntsimp.obj ntclient.obj
	link32 /SUBSYSTEM:CONSOLE /OUT:NTCLIENT.EXE NTCLIENT.OBJ NTSIMP.OBJ WTRPC32.LIB WTUXWS32.LIB LIBCMT.LIB

# Generate a Windows NT DLL
ntdll:	NSIMPDLL.DLL
nsimpdll.C:	simp.IDL
	TIDL -cstub nsimpdll.c -keep c_source -server none simp.IDL
nsimpdll.OBJ:	nsimpdll.C
	CL $(CCFLAGS) -I. -LD -DWIN32 -c nsimpdll.C
NSIMPDLL.DLL: NSIMPDLL.OBJ NSIMPDLL.DEF NSIMPDLL.EXP
	link32 -DLL -OUT:NSIMPDLL.DLL \
	-SUBSYSTEM:WINDOWS NSIMPDLL.OBJ NSIMPDLL.EXP WTRPC32.LIB WTUXWS32.LIB
NSIMPDLL.LIB NSIMPDLL.EXP: nsimpdll.obj nsimpdll.def
	lib32 -OUT:NSIMPDLL.LIB -DEF:NSIMPDLL.DEF NSIMPDLL.OBJ

# Generate OS/2 16 bit client for the MSC compiler
os2_16: oclient.exe
osimp.c:	simp.IDL
	TIDL -cstub osimp.c -keep c_source -server none simp.IDL
oclient.c: client.c
	copy client.c oclient.c
oclient.obj: oclient.c
	CL $(CFLAGS) -I. -D_TM_OS2 -c -AL oclient.c
osimp.obj: osimp.c
	CL $(CFLAGS) -I. -D_TM_OS2 -c -AL osimp.c
oclient.exe: osimp.obj oclient.obj
	buildclt -v -mL -cm -O -o oclient.exe -f "/ST:15000 /CO" -f oclient.obj -f osimp.obj -fOtrpc.lib

# Generate OS/2 16 bit client for the MSC compiler
os2_32: pclient.exe
psimp.c:	simp.IDL
	TIDL -cstub psimp.c -keep c_source -server none simp.IDL
pclient.c: client.c
	copy client.c pclient.c
pclient.obj: pclient.c
	ICC -Q+ $(CCFLAGS) -I. -D_TM_OS2 -c pclient.c
psimp.obj: psimp.c
	ICC -Q+ $(CCFLAGS) -I. -D_TM_OS2 -c psimp.c
pclient.exe: psimp.obj pclient.obj
	buildclt -v -ci -O -o pclient.exe -f "/ST:15000 /CO" -f pclient.obj -f psimp.obj -fOtrpc.lib

clean:
	if exist resptmp del resptmp
	if exist simp.c del simp.c
	if exist simp.h del simp.h
	if exist wsimp.c del wsimp.c
	if exist wclient.c del wclient.c
	if exist osimp.c del osimp.c
	if exist oclient.c del oclient.c
	if exist psimp.c del psimp.c
	if exist pclient.c del pclient.c
	if exist ntsimp.c del ntsimp.c
	if exist ntclient.c del ntclient.c
	if exist simpdll.c del simpdll.c
	if exist nsimpdll.c del nsimpdll.c
	del *.obj
	del *.exe
	if exist wsimpdll.lib del wsimpdll.lib
	if exist wsimpdll.dll del wsimpdll.dll
	if exist nsimpdll.lib del nsimpdll.lib
	if exist nsimpdll.dll del nsimpdll.dll
