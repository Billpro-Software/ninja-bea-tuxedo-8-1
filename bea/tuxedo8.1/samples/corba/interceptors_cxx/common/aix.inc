#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# aix.inc
#
# aix make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on aix.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.so.65
OBJEXT=.o
CPPCMD=$(CPPCMPL) -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=makeC++SharedLib -bM:SRE -p 0 -T512 -h%12 -bnoentry -o $@ $(OBJS) -L${TUXDIR}/lib -lomg -lorb 
EXTRAFLAGS=

