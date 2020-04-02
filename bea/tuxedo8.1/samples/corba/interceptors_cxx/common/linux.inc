#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# linux.inc
#
# Linux make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on Linux.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.so
OBJEXT=.o
CPPCMD=$(CPPCMPL) -shared -fPIC -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=$(CPPCMPL) -shared -fPIC -Wl,-G -o $@ $(OBJS) -L${TUXDIR}/lib -lorb
EXTRAFLAGS=
