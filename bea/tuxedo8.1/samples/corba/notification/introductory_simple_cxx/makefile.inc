#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#--------------------------------------------------------------------
#
# makefile.inc
#
# common makefile for the introductory simple events c++ sample
#
# BEA Systems Inc. sample code
#
#--------------------------------------------------------------------

# introductory.inc contains the configuration build rules (targets).
# these rules are constant among the introductory samples except for
# the domain id

# introductory.inc is included after makefile.inc so that it can
# pick up the definition DOMAINID

CONFIG_TARGETS = \
  ubb            \
  tuxconfig

DOMAINID=events_intro_simple_cxx

#--------------------------------------------------------------------

ALL=                     \
  $(CONFIG_TARGETS)      \
  is_reporter$(EXEEXT)   \
  is_subscriber$(EXEEXT)

all: $(ALL)

#--------------------------------------------------------------------

# directory containing the notification idl files:
IDLDIR=$(TUXDIR)$(SLASH)include

#--------------------------------------------------------------------

# build the reporter (a pure client)

is_reporter$(EXEEXT):                                             \
  Reporter.cpp                                                    \
  $(COMMONDIR)$(SLASH)client_ex.h                                 \
  $(COMMONDIR)$(SLASH)ex.h
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosEventComm.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotification.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyComm.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_Events.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_SimpleEvents.idl
	buildobjclient -v -o $@                                   \
	  -f "                                                    \
	    $(EXTRAFLAGS)                                         \
	    -I$(COMMONDIR)                                        \
	    Reporter.cpp                                          \
	    CosEventComm_c.cpp                                    \
	    CosNotification_c.cpp                                 \
	    CosNotifyComm_c.cpp                                   \
	    Tobj_Events_c.cpp                                     \
	    Tobj_SimpleEvents_c.cpp                               \
          "

#--------------------------------------------------------------------

# build the subscriber (a joint client/server)

is_subscriber$(EXEEXT):                                           \
  Subscriber.cpp                                                  \
  NewsConsumer_i.h                                                \
  NewsConsumer_i.cpp                                              \
  $(COMMONDIR)$(SLASH)client_ex.h                                 \
  $(COMMONDIR)$(SLASH)ex.h
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)CosEventComm.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotification.idl
	idl -P -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyComm.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_Events.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_SimpleEvents.idl
	buildobjclient -v -P -o $@                                \
	  -f "                                                    \
	    $(EXTRAFLAGS)                                         \
	    -I$(COMMONDIR)                                        \
	    Subscriber.cpp                                        \
	    NewsConsumer_i.cpp                                    \
	    CosEventComm_c.cpp                                    \
	    CosNotification_c.cpp                                 \
	    CosNotifyComm_c.cpp                                   \
	    CosNotifyComm_s.cpp                                   \
	    Tobj_Events_c.cpp                                     \
	    Tobj_SimpleEvents_c.cpp                               \
	    $(PRELIB)beawrapper$(POSTLIB)                         \
	  "

#--------------------------------------------------------------------

clean:
	-$(RM)    $(ALL) $(TEMP_FILES) *_c.* *_s.*
	-$(RM)    stdout stderr ULOG* *.dat
	-$(RMDIR) .adm

#--------------------------------------------------------------------
