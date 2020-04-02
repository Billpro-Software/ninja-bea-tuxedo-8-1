#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#ident	"@(#) samples/atmi/apps.mk	$Revision: 1.4 $" 
#

ARGS = all
MAKE = make
INCDIR=$(TUXDIR)/include
LIBDIR=$(TUXDIR)/lib
BINDIR=$(TUXDIR)/bin
XCBINDIR=$(TUXDIR)/bin
CGFLAG=
CC=cc
AR=ar
ARFLAGS=lrv
SUF=.a
DSUF=.a
PRE=$(LIBDIR)/lib

ALL=bankapp simpapp
all:	$(ALL)
	@:

$(ALL)::
	/bin/sh -c 'cd $(@); $(MAKE) -f $(@).mk  \
		MAKE=$(MAKE) SUF=$(SUF) DSUF=$(DSUF) PRE=$(PRE) \
		TUXDIR=$(TUXDIR) \
		INCDIR=$(INCDIR) LIBDIR=$(LIBDIR) \
		BINDIR=$(BINDIR) XCBINDIR=$(XCBINDIR) \
		CGFLAG="$(CGFLAG)" CC=$(CC) AR=$(AR) ARFLAGS="$(ARFLAGS)" $(ARGS)'

install clean clobber depend lint:
	$(MAKE) -f apps.mk ARGS=$@ \
		MAKE=$(MAKE) SUF=$(SUF) DSUF=$(DSUF) PRE=$(PRE) \
		TUXDIR=$(TUXDIR) \
		INCDIR=$(INCDIR) LIBDIR=$(LIBDIR) \
		BINDIR=$(BINDIR) XCBINDIR=$(XCBINDIR) \
		CGFLAG="$(CGFLAG)" CC=$(CC) AR=$(AR) ARFLAGS="$(ARFLAGS)"

list:
	@echo apps/apps.mk
	$(MAKE) -f apps.mk ARGS=list

print:
	@echo apps/apps.mk
	$(MAKE) -f apps.mk ARGS=print
