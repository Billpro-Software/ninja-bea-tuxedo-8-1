#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#--------------------------------------------------------------------
#
# makefile.inc
#
# common makefile for the advanced cos notification c++ sample
#
# BEA Systems Inc. sample code
#
#--------------------------------------------------------------------

# advanced.inc contains the configuration build rules (targets).
# these rules are constant among the advanced samples except for the
# domain id and the wire service server's executable name and
# command line arguments

# advanced.inc is included after makefile.inc so that it can pick up
# the definitions of DOMAINID, WIRE_SERVICE_SERVER and
# WIRE_SERVICE_CLOPT

CONFIG_TARGETS = \
  envfile        \
  createtlog     \
  createqueues   \
  ubb            \
  tuxconfig      \
  TLOG           \
  QUE

DOMAINID=events_advanced_cos_cxx
WIRE_SERVICE_SERVER=AC_WIRESERVICE
WIRE_SERVICE_CLOPT=$(DQUOTE)-A$(DQUOTE)

#--------------------------------------------------------------------

ALL=                      \
  $(CONFIG_TARGETS)       \
  ac_reporter$(EXEEXT)    \
  ac_subscriber$(EXEEXT)  \
  AC_WIRESERVICE$(EXEEXT)

all: $(ALL)

#--------------------------------------------------------------------

# directory containing the notification idl files:
IDLDIR=$(TUXDIR)$(SLASH)include

#--------------------------------------------------------------------

# build the reporter (a pure client)

ac_reporter$(EXEEXT):                                                 \
  Reporter.cpp                                                        \
  $(COMMONDIR)$(SLASH)News.idl                                        \
  $(COMMONDIR)$(SLASH)client_ex.h                                     \
  $(COMMONDIR)$(SLASH)ex.h
	idl $(COMMONDIR)$(SLASH)News.idl
	buildobjclient -v -o $@                                       \
	  -f "                                                        \
	    $(EXTRAFLAGS)                                             \
	    -I$(COMMONDIR)                                            \
	    Reporter.cpp                                              \
	    News_c.cpp                                                \
          "

#--------------------------------------------------------------------

# build the subscriber (a joint client/server)

ac_subscriber$(EXEEXT):                                               \
  Subscriber.cpp                                                      \
  NewsConsumer_i.h                                                    \
  NewsConsumer_i.cpp                                                  \
  ShutdownConsumer_i.h                                                \
  ShutdownConsumer_i.cpp                                              \
  $(COMMONDIR)$(SLASH)client_ex.h                                     \
  $(COMMONDIR)$(SLASH)ex.h
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)CosEventComm.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)CosEventChannelAdmin.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotification.idl
	idl -P -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyComm.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyFilter.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyChannelAdmin.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_Events.idl
	idl    -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_Notification.idl
	buildobjclient -v -P -o $@                                    \
	  -f "                                                        \
	    $(EXTRAFLAGS)                                             \
	    -I$(COMMONDIR)                                            \
	    Subscriber.cpp                                            \
	    NewsConsumer_i.cpp                                        \
	    ShutdownConsumer_i.cpp                                    \
	    CosEventComm_c.cpp                                        \
	    CosEventChannelAdmin_c.cpp                                \
	    CosNotification_c.cpp                                     \
	    CosNotifyComm_c.cpp                                       \
	    CosNotifyComm_s.cpp                                       \
	    CosNotifyFilter_c.cpp                                     \
	    CosNotifyChannelAdmin_c.cpp                               \
	    Tobj_Events_c.cpp                                         \
	    Tobj_Notification_c.cpp                                   \
	    $(PRELIB)beawrapper$(POSTLIB)                             \
	  "

#--------------------------------------------------------------------

# build the wire service server (a server)

AC_WIRESERVICE$(EXEEXT):                                              \
  WireServiceServer.cpp                                               \
  WireService_i.h                                                     \
  WireService_i.cpp                                                   \
  News.icf                                                            \
  $(COMMONDIR)$(SLASH)News.idl                                        \
  $(COMMONDIR)$(SLASH)server_ex.h                                     \
  $(COMMONDIR)$(SLASH)ex.h
	idl $(COMMONDIR)$(SLASH)News.idl News.icf
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosEventComm.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosEventChannelAdmin.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotification.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyComm.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyFilter.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)CosNotifyChannelAdmin.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_Events.idl
	idl -I$(IDLDIR) $(IDLDIR)$(SLASH)Tobj_Notification.idl
	buildobjserver -v -o $@                                       \
	  -f "                                                        \
	    $(EXTRAFLAGS)                                             \
	    -I$(COMMONDIR)                                            \
	    WireServiceServer.cpp                                     \
	    WireService_i.cpp                                         \
	    News_c.cpp                                                \
	    News_s.cpp                                                \
	    CosEventComm_c.cpp                                        \
	    CosEventChannelAdmin_c.cpp                                \
	    CosNotification_c.cpp                                     \
	    CosNotifyComm_c.cpp                                       \
	    CosNotifyFilter_c.cpp                                     \
	    CosNotifyChannelAdmin_c.cpp                               \
	    Tobj_Events_c.cpp                                         \
	    Tobj_Notification_c.cpp                                   \
	  "

#--------------------------------------------------------------------

clean:
	-$(RM)    $(ALL) $(TEMP_FILES) *_c.* *_s.*
	-$(RM)    stdout stderr ULOG* *.dat *.pstore
	-$(RMDIR) .adm

#--------------------------------------------------------------------
