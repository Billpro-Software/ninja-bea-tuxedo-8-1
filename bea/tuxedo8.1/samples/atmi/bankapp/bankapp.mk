#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved

#
#	ANAME -- Name of this application (e.g. bankapp).
#
ANAME = bankapp

#
#	CNAME -- Name of this component (e.g. engine).
#
CNAME = samples

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
# bankapp.mk TUXDIR=/correct/rootdir", or the build of bankapp will fail.
#
TUXDIR=../../..

#
# Directory where the bankapp application source and executables live.
# This file must either be edited to set this value correctly, or the
# correct value must be passed via "make -f bankapp.mk
# APPDIR=/correct/appdir", or the build of bankapp will fail.
#
APPDIR=$(TUXDIR)/samples/atmi/bankapp
#
#
# TUXEDO's include directory
#
INCDIR=$(TUXDIR)/include
#
# Library directory
#
LIBDIR=$(TUXDIR)/lib
SUF=.a
DSUF=.a
PRE=$(LIBDIR)/lib
#
# Resource Manager
#
RM=TUXEDO/SQL
#
#
CGFLAG=
#
#
# To use FML32 instead of FML16:
# set FML32 to 32 to use the FML32 commands
# set DFML32 to -D_TMFML32
# set TMTYPESW to tmtypesw.o, copy $TUXDIR/lib/tmtypesw.c to this directory
# change the ubb files to use FML32 instead of FML and VIEW32 instead of VIEW
FML32=
DFML32=
TMTYPESW=
#
# C compiler flags:  enable TUXEDO System Distributed Transaction
# Processing, search for C header files in TUXEDO's include directory
#
CFLAGS= -DNOWHAT=1 -I$(INCDIR) $(CGFLAG) $(DFML32)
#
# Lint program
#
LINT=lint
#
# Directory in which to find TUXEDO executables for use in the make process.
# It is called cross-compiler bin directory because when cross-compiling,
# this value may be something other than $(TUXDIR)/bin
#
XCBINDIR=$(TUXDIR)/bin
#
# See $APPDIR/bankvar file for explanations of the following variables
#
ENVFILE=$(APPDIR)/ENVFILE
#
FIELDTBLS=Usysflds,bankflds,creditflds,eventflds
FLDTBLDIR=$(TUXDIR)/udataobj:$(APPDIR)
MASKPATH=$(APPDIR)
VIEWDIR=$(APPDIR)
VIEWFILES=aud.V
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
	crbank \
	crbankdb \
	crtlog \
	driver \
	envfile \
	populate \
	RUNME \
	cracl \
	crqueue \
	crusers \
	showq \
	usrevtf
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
	aud.V
#
# C executable files to create
#
OBJS = \
	BAL \
	BALC \
	BTADD \
	ACCT \
	AUDITC \
	TLR \
	XFER \
	audit \
	auditcon \
	gentran \
	gendata \
	ACCTMGR \
	bankmgr \
	bankclt

#
# Menus used by RUNME.sh and menudriver
#
MENUS = \
	MENUS/AUDIT \
	MENUS/CLN.MAIN \
	MENUS/CLN.RUNTIM \
	MENUS/INIT.CONFIG \
	MENUS/INIT.MAIN \
	MENUS/INIT.RUNTIM \
	MENUS/MAIN \
	MENUS/RSH

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
	RUNME.sh \
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
	crbank.sh \
	crbankdb.sh \
	creditflds \
	crtlog.sh \
	driver.sh \
	envfile.sh \
	gendata.c \
	gentran.c \
	populate.sh \
	ubbmp \
	ubbshm \
	util.c \
	$(MENUS) \
	ACCTMGR.c \
	bankmgr.c \
	cracl.sh \
	crqueue.sh \
	crusers.sh \
	eventflds \
	showq.sh \
	usrevtf.sh \
	bankclt.c


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
# Object files (.o)
#
COBJ =	\
	audit.o \
	auditcon.o \
	gentran.o \
	gendata.o \
	AUDITC.o \
	BAL.o \
	BALC.o \
	BTADD.o \
	ACCT.o \
	appinit.o \
	util.o \
	XFER.o \
	TLR.o \
	ACCTMGR.o \
	bankmgr.o \
	bankclt.o

# Exhaustive list of targets to be made
#
INSTALL= $(SCRIPTS) $(HEADERS) $(VIEWS) $(CLFUNC) $(OBJS) $(ENVF) $(USREVTENVF)
INSTALLWS= driver populate envfile $(HEADERS) $(VIEWS) gendata gentran

all:	$(INSTALL) Complete

install:	$(INSTALL) Complete

installws:	$(INSTALLWS)

Complete:
	@echo "$(ANAME).mk processing complete"

#
# Rule for linting source
#
lint:
	-LIBDIR= $(LINT) $(LINTOPTS) -DNOWHAT -I$(INCDIR) $(CFUNC)

# Rule for cleaning out generated files
#
clean:
	rm -f $(SCRIPTS) $(HEADERS) $(VIEWS) $(CLFUNC) $(OBJS) \
		$(COBJ) $(ENVF) $(USREVTENVF) $(VHEADERS)

#
#	clobber -- Should remove everything which was installed
#	(i.e., inverse of install).
#
clobber:	clean
	-rm -f $(INSTALL)

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
	@echo $(SRC) `make -f TOOLS/makefile list` | \
	sed -e 's/^/$(CNAME)\/$(ANAME)\//' \
	-e 's/ / $(CNAME)\/$(ANAME)\//g'|tr ' ' '\012' | sed '/^$$/d'

# This section contains rules for building bankapp servers
# 
ACCT:	ACCT.o appinit.o util.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s OPEN_ACCT -s CLOSE_ACCT \
		-o ACCT \
		-f ACCT.o -f appinit.o -f util.o -f "$(TMTYPESW)"

BAL:	BAL.o appinit.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s ABAL -s TBAL -s ABAL_BID -s TBAL_BID \
		-o BAL \
		-f BAL.o -f appinit.o  -f "$(TMTYPESW)"

BALC:	BALC.o appinit.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s ABALC_BID -s TBALC_BID \
		-o BALC \
		-f BALC.o -f appinit.o  -f "$(TMTYPESW)"

BTADD:	BTADD.o appinit.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s BR_ADD -s TLR_ADD \
		-o BTADD \
		-f BTADD.o -f appinit.o  -f "$(TMTYPESW)"

TLR:	TLR.o util.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s DEPOSIT -s WITHDRAWAL  -s INQUIRY \
		-o TLR \
		-f TLR.o -f util.o -f -lm -f "$(TMTYPESW)"

XFER:	XFER.o appinit.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s TRANSFER \
		-o XFER \
		-f XFER.o  -f appinit.o -f "$(TMTYPESW)"

AUDITC:	AUDITC.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s AUDITC \
		-o AUDITC \
		-f AUDITC.o -f "$(TMTYPESW)"

ACCTMGR:ACCTMGR.o $(TMTYPESW)
	CFLAGS="$(CFLAGS)" \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildserver -r $(RM) \
		-s WATCHDOG -s Q_OPENACCT_LOG \
		-o ACCTMGR \
		-f ACCTMGR.o  -f "$(TMTYPESW)"
 

# User-defined client audit
#
audit:	audit.o
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildclient -o audit -f audit.o

# User-defined client bankmgr
#
bankmgr:	bankmgr.o
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildclient -o bankmgr -f bankmgr.o

# bankclt program
#
bankclt:	bankclt.o
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildclient -o bankclt -f bankclt.o

# User-defined client conversational audit
#
auditcon:	auditcon.o
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/buildclient -o auditcon -f auditcon.o

# Stand-alone C programs to generate ud input
#
gentran gendata:
	$(CC) $(CFLAGS) -o $@ $@.c

# Rule for creating field header file
#
bankflds.h:	bankflds 
	$(XCBINDIR)/mkfldhdr$(FML32) bankflds
#
creditflds.h:	creditflds 
	$(XCBINDIR)/mkfldhdr$(FML32) creditflds
#
eventflds.h:	eventflds
	$(XCBINDIR)/mkfldhdr$(FML32) eventflds

# Rule for generating ENVFILE
#
$(ENVF):	envfile
	ENVFILE=$(ENVFILE) \
	FIELDTBLS=$(FIELDTBLS) \
	FLDTBLDIR=$(FLDTBLDIR) \
	MASKPATH=$(MASKPATH) \
	VIEWDIR=$(VIEWDIR) \
	VIEWFILES=$(VIEWFILES) \
	sh envfile

# Rule for generating TMUSREVT.ENV
#
$(USREVTENVF):	usrevtf
	ENVFILE=$(USREVTENVF) \
	FIELDTBLS=$(FIELDTBLS) \
	FLDTBLDIR=$(FLDTBLDIR) \
	sh usrevtf

.SUFFIXES:	.v .V .ec .c .o .sh

# Rule for creating view
#
.v.V:
	FIELDTBLS=$(FIELDTBLS) \
	FLDTBLDIR=$(FLDTBLDIR) \
	VIEWFILES=$(VIEWFILES) \
	VIEWDIR=$(VIEWDIR) \
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/viewc$(FML32) $*.v


# Rule for creating C programs from embedded SQL programs
#
.ec.c:
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/esqlc -c 30 $*.ec

# Rule for creating object files from C programs
#
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# Rule for creating object files from embedded SQL programs
#
.ec.o:
	TUXDIR=$(TUXDIR) \
	$(XCBINDIR)/esqlc $*.ec
	$(CC) $(CFLAGS) -c $*.c

# Rule for creating executable shell scripts from shell script source
#
.sh:
	rm -f $@
	cat $< >$@
	chmod 0555 $@

# --*--DEPENDENCIES--*--

audit.o BAL_BID.o ACCT.o appinit.o TLR.o BALC.o BAL.o XFER.o BTADD.o:	bankflds.h

AUDITC.o audit.o BAL_BID.o ACCT.o appinit.o TLR.o BALC.o BAL.o XFER.o BTADD.o:	bank.h

ACCT.o TLR.o ACCTMGR.o bankmgr.o: eventflds
