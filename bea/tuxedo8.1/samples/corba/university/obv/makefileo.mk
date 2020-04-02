#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefileo.mk
#
# NT makefile for the university sample application. Builds using the in memory
# database and demonstrates passing objects by value.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

REMOVE=rm -f

#---------------------------------------------------------------------
# Declarations
#---------------------------------------------------------------------

# M3 stuff :
TUXINC=$(TUXDIR)/include

# Application specific stuff :
UTILS=$(APPDIR)/../utils

# CORBA IDL compiler stuff :
IDLFLAGS=-D_TOBJ -I$(TUXINC)

# C++ compiler stuff :
CPP=$(CPPCMPL)
CPPFLAGS=$(SYSFLAGS) $(CXXFLAGS) -I. $(PRECOMPPUBLIC) -I$(UTILS)

#---------------------------------------------------------------------
# Main build rules
#---------------------------------------------------------------------

# by default, don't build the java client:
all        : servers ifrepos cxxclient

servers    : univo_server

ifrepos    : repository.ifr

cxxclient  : univo_client

javaclient : UnivOApplet.class

initdb :

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS =               \
    $(UTILS)/log.cpp        \
    $(UTILS)/log_client.cpp \
    univo_c.cpp             \
    univo_utils.cpp         \
    univoc.cpp              \
    valuetypes_i.cpp

univo_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ \
	    -f "$(CLIENT_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# Java Client
#---------------------------------------------------------------------

UnivOApplet.class: UnivOApplet.java univo.idl
	$(IDLTOJAVA) univo.idl
	javac -g UnivOApplet.java

#---------------------------------------------------------------------
# C++ University Server
#---------------------------------------------------------------------

UNIV_SERVER_SRCS=             \
    $(UTILS)/log.cpp          \
    $(UTILS)/log_server.cpp   \
    $(UTILS)/unique_id.cpp    \
    $(UTILS)/samplesdb.cpp    \
    $(UTILS)/samplesdbim.cpp \
    univo_c.cpp               \
    univo_s.cpp               \
    univo_utils.cpp           \
    univo_i.cpp               \
    univos.cpp		      \
    valuetypes_i.cpp

univo_server: $(UNIV_SERVER_SRCS)
	buildobjserver -v -o $@ \
	    -f "$(UNIV_SERVER_SRCS) $(CPPFLAGS)"

#----------------------------------------------------------------------
# Interface Repository file
#----------------------------------------------------------------------

repository.ifr : univo.idl
	idl2ir $(IDLFLAGS) $(TUXINC)/tobjin.idl univo.idl

#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

univo_c.cpp univo_c.h univo_s.cpp univo_s.h : univo.idl univo.icf
	idl $(IDLFLAGS) univo.idl univo.icf

#---------------------------------------------------------------------
# Header file dependencies
#---------------------------------------------------------------------

univo_i.h               : univo_s.h $(UTILS)/samplesdb.h
univo_utils.h           : univo_c.h

$(UTILS)/samplesdbim.h	: $(UTILS)/samplesdb.h

#---------------------------------------------------------------------
# Source file dependencies
#---------------------------------------------------------------------

univo_utils.cpp	       : univo_utils.h
univo_i.cpp              : $(UTILS)/log.h $(UTILS)/unique_id.h \
                           univo_utils.h univo_i.h
univos.cpp               : $(UTILS)/log.h univo_i.h
univoc.cpp               : $(UTILS)/log.h univo_utils.h

$(UTILS)/log.cpp         : $(UTILS)/log.h
$(UTILS)/log_client.cpp  : $(UTILS)/log.h
$(UTILS)/log_server.cpp  : $(UTILS)/log.h
$(UTILS)/samplesdb.cpp   : $(UTILS)/samplesdb.h
$(UTILS)/samplesdbim.cpp : $(UTILS)/samplesdbim.h

#----------------------------------------------------------------------
# Valid suffixes
#----------------------------------------------------------------------
.SUFFIXES:      .cpp .java .class

#----------------------------------------------------------------------
# Suffix rules
#----------------------------------------------------------------------

.java.class:
	javac -g  $<

#----------------------------------------------------------------------
# Housekeeping
#----------------------------------------------------------------------

clean:
	$(REMOVE) *.o
	$(REMOVE) univo_c*
	$(REMOVE) univo_s*
	$(REMOVE) univo_client univo_server
	$(REMOVE) UniversityO/*
	$(REMOVE) Univ*.class
	$(REMOVE) repository*
	$(REMOVE) ULOG*
	$(REMOVE) *.dat
	$(REMOVE) stderr
	$(REMOVE) stdout

#----------------------------------------------------------------------
