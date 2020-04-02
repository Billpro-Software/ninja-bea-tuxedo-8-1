#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#Copyright (c) 1990 Unix System Laboratories, Inc.
#All rights reserved
#ident	"@(#) samples/atmi/STOCKAPP/STOCKAPP.mk	$Revision: 1.5 $"

#
# Root directory of TUXEDO System.  This file must either be edited to set
# this value correctly, or the correct value must be passed via "make -f
# STOCKAPP.mk TUXDIR=/correct/rootdir", or the build of STOCKAPP will fail.
#
TUXDIR=../..
#
# Directory where the STOCKAPP application source and executables live.
# This file must either be edited to set this value correctly, or the
# correct value must be passed via "make -f STOCKAPP.mk
#
APPDIR=${TUXDIR}/apps/STOCKAPP


TUXCONFIG: UBBCBSHM
	tmloadcf -y UBBCBSHM

#
# Build views 
#

QUOTE.cbl: quote
	viewc -C -n quote

CUST.cbl: cust
	viewc -C -n cust

#
# Build all the clients 
#

BUY: CUST.cbl BUY.cbl
	buildclient -C -o BUY  -f BUY.cbl 

SELL: CUST.cbl SELL.cbl
	buildclient -C -o SELL -f SELL.cbl 

FUNDPR: QUOTE.cbl FUNDPR.cbl
	buildclient -C -o FUNDPR  -f FUNDPR.cbl 

FUNDUP: QUOTE.cbl FUNDUP.cbl
	buildclient -C -o FUNDUP  -f FUNDUP.cbl 

#
# Build all the servers
#

FUNDUPSR: QUOTE.cbl FUNDUPSR.cbl 
	buildserver -C -o FUNDUPSR \
		-s FUNDUPSR \
		-f FUNDUPSR.cbl 

FUNDPRSR: QUOTE.cbl FUNDPRSR.cbl 
	buildserver -C -o FUNDPRSR \
		 -s FUNDPRSR \
		-f FUNDPRSR.cbl 

BUYSELL: CUST.cbl BUYSR.cbl SELLSR.cbl
	buildserver -C -o BUYSELL \
		 -s SELLSR  -f SELLSR.cbl \
		 -s BUYSR  -f BUYSR.cbl 

#
# Make all 
#
install: TUXCONFIG QUOTE.cbl CUST.cbl \
	 BUY SELL FUNDPR FUNDUP  \
	 BUYSELL FUNDPRSR FUNDUPSR

#
# Clean the directory
#
clean:
	rm -f TUXCONFIG \
		BUY SELL FUNDPR FUNDUP \
		BUYSELL FUNDPRSR FUNDUPSR \
		BUY.o  SELL.o  FUNDPR.o  FUNDUP.o  \
		BUYSR.o  SELLSR.o \
		FUNDPRSR.o  FUNDUPSR.o  \
		CUST.cbl cust.V cust.h \
		QUOTE.cbl quote.V quote.h \
                BUY.idy BUY.int \
                BUYSR.idy BUYSR.int \
                BUYSELL.idy BUYSELL.int  \
                SELL.idy SELL.int \
                SELLSR.idy SELLSR.int \
                FUNDPR.idy FUNDPR.int \
                FUNDUP.idy FUNDUP.int \
                FUNDUPSR.idy FUNDUPSR.int \
                FUNDPRSR.idy FUNDPRSR.int \
                ULOG.*
