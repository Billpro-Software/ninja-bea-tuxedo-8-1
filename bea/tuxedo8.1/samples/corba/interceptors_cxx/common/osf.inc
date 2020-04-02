#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# osf.inc
#
# OSF make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on OSF.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.so
OBJEXT=.o
CPPCMD=$(CPPCMPL) -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=ld -g -shared -soname $@ -o $@ $(OBJS) -lexc -lc -lcxx -L${TUXDIR}/lib -lomg -lorb 
EXTRAFLAGS=

