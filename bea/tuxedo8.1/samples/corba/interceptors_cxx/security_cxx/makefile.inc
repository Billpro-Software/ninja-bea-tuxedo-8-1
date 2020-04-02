#--------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.inc
#
# makefile for the C++ security interceptor sample 
#
# BEA Systems Inc. sample code
#
#--------------------------------------------------------------------
#
# define symbols for this interceptor sample
#
SRC = InterceptorSec.cpp
OBJ = InterceptorSec$(OBJEXT)
OBJS = $(OBJ) $(COMMONDIR)$(SLASH)personquery_c$(OBJEXT)
TARGET = InterceptorSec

ALL = InterceptorSec$(SHLIBEXT)

#--------------------------------------------------------------------
#
# default target for building
#
all: $(ALL)

#--------------------------------------------------------------------
#
# build the InterceptorSec shareable library 
#
InterceptorSec$(SHLIBEXT) : InterceptorSec$(OBJEXT)
	$(LNKSHARE)

InterceptorSec$(OBJEXT) : $(SRC) InterceptorSec.h
	$(CPPCMD)

#--------------------------------------------------------------------
#
# targets to register and unregister the simple interceptors
#
config: InterceptorSec$(SHLIBEXT)
	epifreg -t bea/wle -i AppRequestInterceptor \
		-p InterceptorSec \
		-f $(APPDIR)/../security_cxx/InterceptorSec$(SHLIBEXT) \
		-e InterceptorSecInit -u "DisplayName=SecurityInterceptors" \
                -v 1.0

unconfig:
	epifunreg -t bea/wle -p InterceptorSec

#--------------------------------------------------------------------
#
# target for cleaning up
#
clean:
	-$(RM)    $(TEMP_FILES) *$(SHLIBEXT) *.lib

#--------------------------------------------------------------------
