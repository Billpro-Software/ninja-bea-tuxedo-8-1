#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# hpux.inc
#
# hpux make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on hpux.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.sl
OBJEXT=.o
CPPCMD=$(CPPCMPL) -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=aCC -b -Wl,+s +eh -o $@ $(OBJS) -lc -lcxx -L${TUXDIR}/lib -lomg -lorb -ldld
EXTRAFLAGS=

