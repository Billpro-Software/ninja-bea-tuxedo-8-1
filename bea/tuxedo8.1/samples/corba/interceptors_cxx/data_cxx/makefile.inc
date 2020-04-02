#--------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.inc
#
# makefile for the C++ data interceptor sample 
#
# BEA Systems Inc. sample code
#
#--------------------------------------------------------------------
#
# define symbols for building this interceptor sample
#
SRC = InterceptorData.cpp
OBJ = InterceptorData$(OBJEXT)
OBJS = $(OBJ) $(COMMONDIR)$(SLASH)personquery_c$(OBJEXT)
TARGET = InterceptorData

ALL = InterceptorData$(SHLIBEXT)

#--------------------------------------------------------------------
#
# default target for building
#
all: $(ALL)


#--------------------------------------------------------------------
#
# build the InterceptorData shareable library 
#
InterceptorData$(SHLIBEXT) : $(OBJS)
	$(LNKSHARE)

InterceptorData$(OBJEXT) : $(SRC) InterceptorData.h
	$(CPPCMD)

#--------------------------------------------------------------------
#
# targets to register and unregister the simple interceptors
#
config: InterceptorData$(SHLIBEXT)
	epifreg -t bea/wle -i AppRequestInterceptor \
		-p ClientInterceptorData \
		-f $(APPDIR)/../data_cxx/InterceptorData$(SHLIBEXT) \
		-e InterceptorDataClientInit -u "DisplayName=DataClient" -v 1.0
	epifreg -t bea/wle -i AppRequestInterceptor \
		-p TargetInterceptorData \
		-f $(APPDIR)/../data_cxx/InterceptorData$(SHLIBEXT) \
		-e InterceptorDataTargetInit -u "DisplayName=DataTarget" -v 1.0

unconfig:
	epifunreg -t bea/wle -p ClientInterceptorData
	epifunreg -t bea/wle -p TargetInterceptorData

#--------------------------------------------------------------------
#
# target for cleaning up
#
clean:
	-$(RM)    $(TEMP_FILES) *$(SHLIBEXT) *.lib

#--------------------------------------------------------------------
