#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# nt.inc
#
# Windows make include file for the interceptor samples
# This file defines specific symbols needed to build interceptor
# shareable libraries on NT.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
SHLIBEXT=.dll
OBJEXT=.obj
CPPCMD=$(CPPCMPL) -c $(CPPFLAGS) -o $@ $(SRC)
LNKSHARE=link -out:$@ -dll $(OBJS) /debug:full -libpath:%TUXDIR%\lib liborb.lib libomg.lib 

