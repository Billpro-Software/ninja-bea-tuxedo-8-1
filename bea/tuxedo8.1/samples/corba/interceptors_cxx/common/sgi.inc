#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# sgi.inc
#
# sgi make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on sgi.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.so
OBJEXT=.o
CPPCMD=$(CPPCMPL) -shared -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=ld -o32 -shared -exceptions -soname $@ -o $@ $(OBJS) -L${TUXDIR}/lib -lomg -lorb -lC
EXTRAFLAGS=

