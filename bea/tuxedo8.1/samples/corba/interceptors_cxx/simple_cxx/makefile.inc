#--------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.inc
#
# makefile for the C++ simple interceptor sample 
#
# BEA Systems Inc. sample code
#
#--------------------------------------------------------------------
#
# define the symbols for building this interceptor sample
#
SRC = InterceptorSimp.cpp
OBJ = InterceptorSimp$(OBJEXT)
OBJS = $(OBJ)
TARGET = InterceptorSimp

ALL = InterceptorSimp$(SHLIBEXT)

#--------------------------------------------------------------------
#
# default target for building 
#
all: $(ALL)

#--------------------------------------------------------------------
#
# build the InterceptorSimp shareable library 
#

InterceptorSimp$(SHLIBEXT) : InterceptorSimp$(OBJEXT)
	$(LNKSHARE)

InterceptorSimp$(OBJEXT) : $(SRC) InterceptorSimp.h
	$(CPPCMD)

#--------------------------------------------------------------------
#
# targets to register and unregister the simple interceptors
#
config : InterceptorSimp$(SHLIBEXT)
	epifreg -t bea/wle -i AppRequestInterceptor \
		-p ClientInterceptorSimp \
		-f $(APPDIR)/../simple_cxx/InterceptorSimp$(SHLIBEXT) \
		-e InterceptorSimpClientInit -u "DisplayName=SimpClient" -v 1.0
	epifreg -t bea/wle -i AppRequestInterceptor \
		-p TargetInterceptorSimp \
		-f $(APPDIR)/../simple_cxx/InterceptorSimp$(SHLIBEXT) \
		-e InterceptorSimpTargetInit -u "DisplayName=SimpTarget" -v 1.0

unconfig :
	epifunreg -t bea/wle -p ClientInterceptorSimp
	epifunreg -t bea/wle -p TargetInterceptorSimp


#--------------------------------------------------------------------
#
# target for cleaning up
#
clean :
	-$(RM)    $(TEMP_FILES) *$(SHLIBEXT) *.lib

#--------------------------------------------------------------------
