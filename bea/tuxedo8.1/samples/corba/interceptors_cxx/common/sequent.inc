#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# sequent.inc
#
# sequent make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on sequent.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.so
OBJEXT=.o
CPPCMD=$(CPPCMPL) -shared -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=c++ -G -version3 -eh -std -KPIC -Dsys5 -tpautooff -o $@ $(OBJS) -L${TUXDIR}/lib -lomg -lorb -ldl
EXTRAFLAGS=

