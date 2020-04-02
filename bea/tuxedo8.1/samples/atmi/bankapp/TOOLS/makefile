#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1994 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/bankapp/TOOLS/makefile	$Revision: 1.5 $"
#
# Shell scripts to be created
#
SCRIPTS = 		\
	ACTIVE		\
	CHKSYS		\
	ISBUILT		\
	ISPROP		\
	PROP		\
	SETUP		\
	setvars
#
# C executable files to create
#
OBJS = \
	hostaddr	\
	menudriver	\
	tlcmd
#
# List of all the source files in bankapp
#
SRC = \
	ACTIVE.sh	\
	CHKSYS.sh	\
	ISBUILT.sh	\
	ISPROP.sh	\
	PROP.sh		\
	SETUP.sh	\
	hostaddr.c	\
	makefile	\
	menudriver.c	\
	setvars.sh	\
	tlcmd.c

# Exhaustive list of targets to be made
#
INSTALL= $(SCRIPTS) $(OBJS)

all:	$(INSTALL)

install:	$(INSTALL)

#
# Rule for making scripts
#
$(SCRIPTS): $$(@F).sh
	rm -f $(@)
	chmod +x $(@F).sh
	ln $(@F).sh $(@)

# Rule for cleaning out generated files
#
clean:
	rm -f $(SCRIPTS) $(OBJS)

#
#	list -- Should produce a listing of every source file prepended
#	with the component and sub-component name.
#
list::
	@echo $(SRC) | tr ' ' '\012' | sed -e '/^$$/d' -e 's/^/TOOLS\//'
