
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# Copyright (c) 1999 BEA Systems, Inc.
# All rights reserved

# THIS IS UNPUBLISHED PROPRIETARY
# SOURCE CODE OF USL
# The copyright notice above does not
# evidence any actual or intended
# publication of such source code.
#
#ident	"@(#) samples/atmi/qsample/makefile	$Revision: 1.5 $"

#
#TUXDIR=<full path of TUXEDO software>
INCDIR=$(TUXDIR)/include
BINDIR=$(TUXDIR)/bin
CFLAGS= -I$(INCDIR)
CC = cc

CSRC = \
	client.c \
	server.c

COBJ = $(CSRC:.c=.o)

OBJS = \
	client \
	server

all:	$(COBJ) $(OBJS) 

server:	server.o
	$(BINDIR)/buildserver -v -o server \
		-s STRING -f server.o 
client:	client.o
	$(BINDIR)/buildclient -o client -f client.o

clean: 
	rm -f $(COBJ) $(OBJS) 

lint:
	lint -u -D NOWHAT -I. -I$(INCDIR) $(CSRC)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

