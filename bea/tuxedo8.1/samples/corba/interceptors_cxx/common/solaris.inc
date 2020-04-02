#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# solaris.inc
#
# Solaris/SunOS make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on Solaris/SunOS.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.so.65
OBJEXT=.o
CPPCMD=$(CPPCMPL) -G -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=ld -shared -G -o $@ $(OBJS) -L${TUXDIR}/lib -lorb
EXTRAFLAGS=
