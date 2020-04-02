#--------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.inc
#
# makefile for the interceptor c++ sample application
#
# BEA Systems Inc. sample code
#
#--------------------------------------------------------------------
#
# app.inc contains the configuration build rules (targets).
# It is included after makefile.inc so that it can pick up
# the definitions of DOMAINID, APP_SERVICE_SERVER and
# APP_SERVICE_CLOPT

CONFIG_TARGETS = \
  ubb            \
  tuxconfig

DOMAINID=interceptor_app_cxx
APP_SERVICE_SERVER=PersonQueryServer
APP_SERVICE_CLOPT=$(DQUOTE)-A$(DQUOTE)

#--------------------------------------------------------------------
#
# define symbols for building the sample interceptor application
# (client and server).  Also define default target.
#
ALL=                      \
  PersonQueryClient$(EXEEXT)    \
  PersonQueryServer$(EXEEXT)    \
  $(CONFIG_TARGETS)

all: $(ALL)

#--------------------------------------------------------------------
#
# build the PersonQuery client executable
#
PersonQueryClient$(EXEEXT):                             \
  personqueryc.cpp                                      \
  $(COMMONDIR)$(SLASH)personquery_c.cpp                 \
  ex.h
	buildobjclient -v -o $@                         \
	  -f "                                          \
	    $(EXTRAFLAGS)                               \
	    -I$(COMMONDIR)                              \
	    personqueryc.cpp                            \
	    $(COMMONDIR)$(SLASH)personquery_c.cpp       \
          "

#--------------------------------------------------------------------
#
# build the PersonQuery server executable
#
PersonQueryServer$(EXEEXT):                             \
  personquerys.cpp                                      \
  personquery_i.h                                       \
  personquery_i.cpp                                     \
  $(COMMONDIR)$(SLASH)personquery_c.cpp                 \
  $(COMMONDIR)$(SLASH)personquery_s.cpp
	buildobjserver -v -o $@                         \
	  -f "                                          \
	    $(EXTRAFLAGS)                               \
	    -I$(COMMONDIR)                              \
	    personquerys.cpp                            \
	    personquery_i.cpp                           \
	    $(COMMONDIR)$(SLASH)personquery_c.cpp       \
	    $(COMMONDIR)$(SLASH)personquery_s.cpp       \
	  "

#--------------------------------------------------------------------
#
# target for cleaning up
#
clean:
	-$(RM)    $(ALL) $(TEMP_FILES) *_c.* *_s.*
	-$(RM)    stderr ULOG* *out *.dat *.log
	-$(RMDIR) .adm

#--------------------------------------------------------------------
