#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#	Copyright (c) 1996 BEA Systems, Inc.
#	All rights reserved
#
#	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF
#	BEA Systems, Inc.
#	The copyright notice above does not evidence any
#	actual or intended publication of such source code.
#
#
#ident	"@(#) samples/atmi/bankapp/nt/bankapp.mak	$Revision: 1.6 $"

#
#	ANAME -- Name of this application (e.g. bankapp).
#
ANAME = bankapp

#
#	CNAME -- Name of this component (e.g. engine).
#
CNAME = apps

#
#	MODE -- mode used to install targets.
MODE = 0444

#
#	PR -- name of command used to print source listings.
#	By default pr(1) is used; a good substitute is cpr(1).
#
PR = pr

#
#	PRFLAGS -- Flags for $(PR) command.
#
PRFLAGS =

#
# Root directory of TUXEDO System.  This file must either be edited to set
# this value correctly, or the correct value must be passed via "make -f
# bankapp.mk TUXDIR=/correct/TUXDIR", or the build of bankapp will fail.
#
TUXDIR=$(TUXDIR)

#
# Directory where the bankapp application source and executables live.
# This file must either be edited to set this value correctly, or the
# correct value must be passed via "make -f bankapp.mk
# APPDIR=\correct\appdir", or the build of bankapp will fail.
#
APPDIR=$(TUXDIR)\samples\atmi\bankapp
#
# Directory where the native side source files for CICS host live.
# This file must either be edited to set this value correctly, or the
# correct value must be passed via "make -f bankapp.mk
# NATIVE=\correct\native", or the build of bankapp will fail.
#
NATIVE=$(TUXDIR)\apps\hostapp\cics\native
#
#
# TUXEDO's include directory
#
INCDIR=$(TUXDIR)\include
#
# Library directory
#
LIBDIR=$(TUXDIR)\lib
SUF=.lib
DSUF=.lib
PRE=$(LIBDIR)\lib
LIBES=	$(LIBDIR)\libtux$(DSUF) \
	$(LIBDIR)\libbuft$(DSUF) $(LIBDIR)\libengine$(DSUF) \
	$(LIBDIR)\libfml$(DSUF)
#
# Resource Manager
#
RM=TUXEDO/SQL
#
#
CGFLAG=
#
# HOST - set to -DHOST if host credit card processing is desired
#HOST=-DHOST
HOST=
#
#
# To use FML32 instead of FML16:
# set FML32 to 32 to use the FML32 commands
# set DFML32 to -D_TMFML32
# set TMTYPESW to tmtypesw.obj, copy $TUXDIR\lib\tmtypesw.c to this directory
# change the ubb files to use FML32 instead of FML and VIEW32 instead of VIEW
FML32=
DFML32=
TMTYPESW=
#
# C compiler flags:  enable TUXEDO System Distributed Transaction
# Processing, search for C header files in TUXEDO's include directory
#

CFLAGS=-DWIN32 -MD -W3 -nologo $(HOST) -DNOWHAT=1 -I$(INCDIR) $(CGFLAG) $(DFML32) -D__STDC__
LINKFLAGS=-MD

#
# Lint program
#
LINT=lint
#
# Directory in which to find TUXEDO executables for use in the make process.
# It is called cross-compiler bin directory because when cross-compiling,
# this value may be something other than $(TUXDIR)\bin
#
XCBINDIR=$(TUXDIR)\bin
#
# See $APPDIR\bankvar file for explanations of the following variables
#
ENVFILE=$(APPDIR)\ENVFILE
FIELDTBLS=Usysflds,bankflds,creditflds,eventflds
FLDTBLDIR=$(TUXDIR)\udataobj;$(APPDIR)
MASKPATH=$(APPDIR)
VIEWDIR=$(APPDIR)
VIEWFILES=aud.vv
#
# Target name for $(ENVFILE), is the basename of $(ENVFILE)
#
ENVF=ENVFILE
#
# ENVFILE for the TMUSREVT server
#
USREVTENVF=TMUSREVT.ENV
#
# Shell scripts to be created
#
SCRIPTS = \
	crbankdb.exe \
	crtlog.exe \
	envfile.cmd \
	populate.cmd \
	cracl.exe \
	crqueue.exe \
	crusers.exe \
	showq.exe \
	usrevtf.cmd

#
# Files to be exported for UNIX
#
TOOLFILES=\
	TOOLS\ACTIVE.sh \
	TOOLS\CHKSYS.sh \
	TOOLS\hostaddr.c \
	TOOLS\ISBUILT.sh \
	TOOLS\ISPROP.sh \
	TOOLS\makefile \
	TOOLS\menudriver.c \
	TOOLS\PROP.sh \
	TOOLS\SETUP.sh \
	TOOLS\setvars.sh \
	TOOLS\tlcmd.c

UFILES= \
	crbank.sh \
	crbankdb.sh \
	crtlog.sh \
	driver.sh \
	envfile.sh \
	populate.sh \
	run.sh \
	RUNME.sh \
	cracl.sh \
	crqueue.sh \
	crusers.sh \
	showq.sh \
	usrevtf.sh \
	$(TOOLFILES)
#
# Field header files to create
#
HEADERS = \
	bankflds.h  \
	creditflds.h \
	eventflds.h
#
VHEADERS = \
	aud.h
# Views to create
#
VIEWS = \
	aud.vv
#
# C executable files to create
#
OBJS = \
	BAL.exe \
	BALC.exe \
	BTADD.exe \
	ACCT.exe \
	AUDITC.exe \
	TLR.exe \
	XFER.exe \
	audit.exe \
	auditcon.exe \
	gentran.exe \
	gendata.exe \
	ACCTMGR.exe \
	bankmgr.exe \
	bankclt.exe \
	bankappn.exe

#
# List of all the source files in bankapp
#
SRC = \
	ACCT.ec \
	AUDITC.c \
	BAL.ec \
	BALC.ec \
	BTADD.ec \
	FILES \
	README \
	TLR.ec \
	XFER.c \
	appinit.c \
	aud.v \
	audit.c \
	auditcon.c \
	bankflds \
	bank.h \
	bankapp.mk \
	bankvar \
	nt\crbankdb.c \
	creditflds \
	nt\crtlog.c \
	nt\envfile.cmd \
	gendata.c \
	gentran.c \
	nt\populate.cmd \
	ubbmp \
	ubbshm \
	util.c \
	hostmk \
	$(MENUS) \
	ACCTMGR.c \
	bankmgr.c \
	bankclt.c \
	nt\cracl.c \
	nt\crqueue.c \
	nt\crusers.c \
	eventflds \
	nt\showq.c \
	nt\usrevtf.cmd \
	nt\client\balance.dlg \
	nt\client\bankapp.h \
	nt\client\bankappw.c \
	nt\client\bankappw.rc \
	nt\client\close.dlg \
	nt\client\deposit.dlg \
	nt\client\moneyico.Z \
	nt\client\client.mak \
	nt\client\open.dlg \
	nt\client\user.dlg \
	nt\client\uudecode.c \
	nt\client\transfer.dlg \
	nt\client\withdraw.dlg \
	$(UFILES)

#
# C functions 
#
CFUNC = \
	ACCT.c \
	AUDITC.c \
	BAL.c \
	BALC.c \
	BTADD.c \
	TLR.c \
	XFER.c \
	appinit.c \
	audit.c \
	auditcon.c \
	gendata.c \
	gentran.c \
	util.c \
	ACCTMGR.c \
	bankmgr.c \
	bankclt.c

#
# C functions that are generated from embedded SQL programs
#
CLFUNC = \
	BAL.c \
	BALC.c \
	BTADD.c \
	ACCT.c \
	TLR.c
#
#
# Object files (.obj)
#
COBJ =	\
	audit.obj \
	auditcon.obj \
	gentran.obj \
	gendata.obj \
	AUDITC.obj \
	BAL.obj \
	BALC.obj \
	BTADD.obj \
	ACCT.obj \
	appinit.obj \
	util.obj \
	XFER.obj \
	TLR.obj \
	ACCTMGR.obj \
	bankmgr.obj \
	bankclt.obj

#
# Script object files
SOBJ = \
	crbankdb.obj \
	crtlog.obj \
	cracl.obj \
	crqueue.obj \
	crusers.obj \
	showq.obj

# Exhaustive list of targets to be made
#
INSTALL= $(SCRIPTS) $(HEADERS) $(VIEWS) $(CLFUNC) $(OBJS) $(ENVF)  $(USREVTENVF)
INSTALLWS= driver populate.cmd envfile.cmd $(HEADERS) $(VIEWS) gendata.exe gentran.exe

all:	$(INSTALL) Complete

install:	$(INSTALL) Complete

installws:	$(INSTALLWS)

Complete:
	@echo $(ANAME) processing complete

host:	$(INSTALL)
	$(MAKE) -f hostmk TUXDIR=$(TUXDIR) LANG=$(LANG) APPDIR=$(APPDIR) \
		XCBINDIR=$(XCBINDIR) NATIVE=$(NATIVE) all

crbankdb.exe: crbankdb.obj $(TUXDIR)\lib\libengine.lib
	$(CC) -Fecrbankdb.exe crbankdb.obj $(TUXDIR)\lib\libengine.lib

crbankdb.obj: nt\crbankdb.c
	$(CC) -c $(CFLAGS) nt\crbankdb.c

crtlog.exe: crtlog.obj $(TUXDIR)\lib\libengine.lib
	$(CC) -Fecrtlog.exe crtlog.obj $(TUXDIR)\lib\libengine.lib

crtlog.obj: nt\crtlog.c
	$(CC) -c $(CFLAGS) nt\crtlog.c

cracl.exe: cracl.obj $(TUXDIR)\lib\libengine.lib
	$(CC) -Fecracl.exe cracl.obj $(TUXDIR)\lib\libengine.lib

cracl.obj: nt\cracl.c
	$(CC) -c $(CFLAGS) nt\cracl.c

crqueue.exe: crqueue.obj $(TUXDIR)\lib\libengine.lib
	$(CC) -Fecrqueue.exe crqueue.obj $(TUXDIR)\lib\libengine.lib

crqueue.obj: nt\crqueue.c
	$(CC) -c $(CFLAGS) nt\crqueue.c

crusers.exe: crusers.obj $(TUXDIR)\lib\libengine.lib
	$(CC) -Fecrusers.exe crusers.obj $(TUXDIR)\lib\libengine.lib advapi32.lib

crusers.obj: nt\crusers.c
	$(CC) -c $(CFLAGS) nt\crusers.c

showq.exe: showq.obj $(TUXDIR)\lib\libengine.lib
	$(CC) -Feshowq.exe showq.obj $(TUXDIR)\lib\libengine.lib

showq.obj: nt\showq.c
	$(CC) -c $(CFLAGS) nt\showq.c

envfile.cmd: nt\envfile.cmd
	if exist envfile.cmd del envfile.cmd
	copy nt\envfile.cmd

usrevtf.cmd: nt\usrevtf.cmd
	if exist usrevtf.cmd del usrevtf.cmd
	copy nt\usrevtf.cmd

populate.cmd: nt\populate.cmd
	if exist populate.cmd del populate.cmd
	copy nt\populate.cmd
#
# Rule for linting source
#
lint:
	-LIBDIR= $(LINT) $(LINTOPTS) -DNOWHAT -I$(INCDIR) $(CFUNC)

# Rule for cleaning out generated files
#
clean:
	@echo off & for %%i in ($(SCRIPTS) $(HEADERS) $(VIEWS) $(CLFUNC) \
	$(OBJS) $(COBJ) $(SOBJ) $(ENVF) $(USREVTENVF) $(VHEADERS)) \
	do if exist %%i del %%i
	cd nt\client
	$(MAKE) -f client.mak clean
	cd ..\..

#
#	clobber -- Should remove everything which was installed
#	(i.e., inverse of install).
#
clobber:	clean
	@echo off & for %%i in ($(INSTALL)) do if exist %%i del %%i

#
#	print -- Should produce a complete source listing of the
#	files in the directory.
#
print::
	@$(PR) $(PRFLAGS) $(SRC)

#
#	list -- Should produce a listing of every source file prepended
#	with the component and sub-component name.
#
list::
	@echo off & for %%i in ($(SRC)) do echo $(CNAME)\$(ANAME)\%%i

# This section contains rules for building bankapp servers
# 
ACCT.exe:	ACCT.obj appinit.obj util.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) -s OPEN_ACCT -s CLOSE_ACCT \
		-o ACCT -f ACCT.obj -f appinit.obj -f util.obj -f "$(TMTYPESW)"

BAL.exe:	BAL.obj appinit.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) -s ABAL -s TBAL -s ABAL_BID \
		-s TBAL_BID -o BAL -f BAL.obj -f appinit.obj  -f "$(TMTYPESW)"

BALC.exe:	BALC.obj appinit.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) -s ABALC_BID -s TBALC_BID \
		-o BALC -f BALC.obj -f appinit.obj  -f "$(TMTYPESW)"

BTADD.exe:	BTADD.obj appinit.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) -s BR_ADD -s TLR_ADD -o BTADD \
		-f BTADD.obj -f appinit.obj  -f "$(TMTYPESW)"

TLR.exe:	TLR.obj util.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) -s DEPOSIT -s WITHDRAWAL \
		-s INQUIRY -o TLR -f TLR.obj -f util.obj -f "$(TMTYPESW)"

XFER.exe:	XFER.obj appinit.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) -s TRANSFER -o XFER \
		-f XFER.obj  -f appinit.obj -f "$(TMTYPESW)"

AUDITC.exe:	AUDITC.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) -s AUDITC -o AUDITC \
		-f AUDITC.obj -f "$(TMTYPESW)"

ACCTMGR.exe:	ACCTMGR.obj $(LIBES) $(TMTYPESW)
	(set CFLAGS="$(CFLAGS)") & (set TUXDIR=$(TUXDIR)) &\
	$(XCBINDIR)\buildserver -r $(RM) \
		-s WATCHDOG -s Q_OPENACCT_LOG \
		-o ACCTMGR \
		-f ACCTMGR.obj  -f "$(TMTYPESW)"
 
bankappn.exe: nt\client\bankappn.exe
	copy nt\client\bankappn.exe bankappn.exe

nt\client\bankappn.exe:
	cd nt\client
	$(MAKE) -f client.mak
	cd ..\..

# User-defined client audit
#
audit.exe:	audit.obj util.obj $(LIBES)
	(set TUXDIR=$(TUXDIR)) & $(XCBINDIR)\buildclient -o audit -f "audit.obj util.obj"

# User-defined client bankmgr
#
bankmgr.exe:	bankmgr.obj util.obj $(LIBES)
	(set TUXDIR=$(TUXDIR)) & $(XCBINDIR)\buildclient -o bankmgr -f "bankmgr.obj util.obj"

# Ascii Bankapp client
#
bankclt.exe:	bankclt.obj $(LIBES)
	(set TUXDIR=$(TUXDIR)) & $(XCBINDIR)\buildclient -o bankclt -f bankclt.obj

# User-defined client conversational audit
#
auditcon.exe:	auditcon.obj util.obj $(LIBES)
	(set TUXDIR=$(TUXDIR)) & $(XCBINDIR)\buildclient -o auditcon -f "auditcon.obj util.obj"

# Stand-alone C programs to generate ud input
#
gentran.exe: gentran.c $(LIBDIR)\libengine$(DSUF)
	$(CC) $(CFLAGS) -Fe$@ gentran.c $(LIBDIR)\libengine$(DSUF)

gendata.exe:	gendata.c $(LIBDIR)\libengine$(DSUF)
	$(CC) $(CFLAGS) -Fe$@ gendata.c $(LIBDIR)\libengine$(DSUF)

# Rule for creating field header file
#
bankflds.h:	bankflds 
	$(XCBINDIR)\mkfldhdr$(FML32) bankflds
#
creditflds.h:	creditflds 
	$(XCBINDIR)\mkfldhdr$(FML32) creditflds
#
eventflds.h:	eventflds
	$(XCBINDIR)\mkfldhdr$(FML32) eventflds

# Rule for generating ENVFILE
#
$(ENVF):	envfile.cmd
	(set ENVFILE=$(ENVFILE)) & (set FIELDTBLS=$(FIELDTBLS)) &\
	(set FLDTBLDIR=$(FLDTBLDIR)) & (set VIEWDIR=$(VIEWDIR)) &\
	(set VIEWFILES=$(VIEWFILES)) & envfile

# Rule for generating TMUSREVT.ENV
#
$(USREVTENVF):	usrevtf.cmd
	(set ENVFILE=$(USREVTENVF)) & (set FIELDTBLS=$(FIELDTBLS)) &\
	(set FLDTBLDIR=$(FLDTBLDIR)) & usrevtf

.SUFFIXES:	.v .V .ec .c .obj .sh

# Rule for creating view
#
.v.vv:
	(set FIELDTBLS=$(FIELDTBLS)) & (set FLDTBLDIR=$(FLDTBLDIR)) &\
	(set VIEWFILES=$(VIEWFILES)) & (set VIEWDIR=$(VIEWDIR)) &\
	(set TUXDIR=$(TUXDIR)) & $(XCBINDIR)\viewc$(FML32) $*.v

# Rule for creating C programs from embedded SQL programs
#
.ec.c:
	(set TUXDIR=$(TUXDIR)) & $(XCBINDIR)\esqlc -c 30 $*.ec

# Rule for creating object files from C programs
#
.c.obj:
	$(CC) $(CFLAGS) -c $*.c

# Rule for creating object files from embedded SQL programs
#
.ec.obj:
	(set TUXDIR=$(TUXDIR)) & $(XCBINDIR)\esqlc $*.ec
	$(CC) $(CFLAGS) -c $*.c

# --*--DEPENDENCIES--*--

audit.obj BAL_BID.obj ACCT.obj appinit.obj TLR.obj BALC.obj BAL.obj XFER.obj BTADD.obj:	bankflds.h

AUDITC.obj audit.obj BAL_BID.obj ACCT.obj appinit.obj TLR.obj BALC.obj BAL.obj XFER.obj BTADD.obj:	bank.h
