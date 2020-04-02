#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefiles.mk
#
# Unix makefile for the university sample application
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

REMOVE=rm -f

#---------------------------------------------------------------------
# Declarations
#---------------------------------------------------------------------

# ORACLE stuff :
ORAINC=$(ORACLE_HOME)/precomp/public
PROC=$(ORACLE_HOME)/bin/proc
PRECOMPPUBLIC=-I$(ORAINC)
RM=Oracle_XA

# TUXDIR related stuff :
TUXINC=$(TUXDIR)/include

# Application specific stuff :
UTILS=$(APPDIR)/../utils

# Oracle SQL Precompiler stuff :
PROCPLSFLAGS= sqlcheck=full userid=$(USERID)
PROCPPFLAGS=  code=cpp include=/usr/include      \
     include=$(CPPINC) include=$(ORAINC)         \
     include=$(TUXINC) include=$(UTILS)

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

servers    : univs_server

ifrepos    : repository.ifr

cxxclient  : univs_client

javaclient : UnivSApplet.class

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS =               \
    $(UTILS)/log.cpp        \
    $(UTILS)/log_client.cpp \
    univs_c.cpp             \
    univs_utils.cpp         \
    univsc.cpp

univs_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ \
	    -f "$(CLIENT_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# Java Client
#---------------------------------------------------------------------

UnivSApplet.class: UnivSApplet.java univs.idl
	$(IDLTOJAVA) univs.idl
	javac -g UnivSApplet.java

#---------------------------------------------------------------------
# C++ University Server
#---------------------------------------------------------------------

UNIV_SERVER_SRCS=             \
    $(UTILS)/log.cpp          \
    $(UTILS)/log_server.cpp   \
    $(UTILS)/unique_id.cpp    \
    $(UTILS)/samplesdb.cpp    \
    $(UTILS)/samplesdbsql.cpp \
    $(UTILS)/oradbconn.cpp    \
    univs_c.cpp               \
    univs_s.cpp               \
    univs_utils.cpp           \
    univs_i.cpp               \
    univss.cpp

univs_server: $(UNIV_SERVER_SRCS)
	buildobjserver -v -o $@ -r $(RM) \
	    -f "$(UNIV_SERVER_SRCS) $(CPPFLAGS)"

#----------------------------------------------------------------------
# Interface Repository file
#----------------------------------------------------------------------

repository.ifr : univs.idl
	idl2ir $(IDLFLAGS) $(TUXINC)/tobjin.idl univs.idl

#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

univs_c.cpp univs_c.h univs_s.cpp univs_s.h : univs.idl univs.icf
	idl $(IDLFLAGS) univs.idl univs.icf

#---------------------------------------------------------------------
# Initialize the database
#---------------------------------------------------------------------

LOADSCRIPT=     $(UTILS)/university.sql

initdb	:
	sqlplus $(USERID) @$(LOADSCRIPT) </dev/null

#---------------------------------------------------------------------
# Header file dependencies
#---------------------------------------------------------------------

univs_i.h               : univs_s.h $(UTILS)/samplesdb.h
univs_utils.h           : univs_c.h

$(UTILS)/samplesdbsql.h	: $(UTILS)/samplesdb.h

#---------------------------------------------------------------------
# Source file dependencies
#---------------------------------------------------------------------

univs_utils.cpp	         : univs_utils.h
univs_i.cpp              : $(UTILS)/log.h $(UTILS)/unique_id.h \
                           univs_utils.h univs_i.h
univss.cpp               : $(UTILS)/log.h univs_i.h
univsc.cpp               : $(UTILS)/log.h univs_utils.h

$(UTILS)/log.cpp         : $(UTILS)/log.h
$(UTILS)/log_client.cpp  : $(UTILS)/log.h
$(UTILS)/log_server.cpp  : $(UTILS)/log.h
$(UTILS)/samplesdb.cpp   : $(UTILS)/samplesdb.h
$(UTILS)/oradbconn.cpp   : $(UTILS)/samplesdbsql.h
$(UTILS)/samplesdbsql.cpp: $(UTILS)/samplesdbsql.pc
$(UTILS)/samplesdbsql.pc : $(UTILS)/samplesdbsql.h

#----------------------------------------------------------------------
# Valid suffixes
#----------------------------------------------------------------------
.SUFFIXES:      .pc .cpp .java .class

#----------------------------------------------------------------------
# Suffix rules
#----------------------------------------------------------------------

.pc.cpp:
	$(PROC) $(PROCPLSFLAGS) $(PROCPPFLAGS) iname=$*.pc oname=$*.cpp

.java.class:
	javac -g  $<

#----------------------------------------------------------------------
# Housekeeping
#----------------------------------------------------------------------

clean:
	$(REMOVE) $(UTILS)/samplesdbsql.cpp
	$(REMOVE) *.o
	$(REMOVE) univs_c*
	$(REMOVE) univs_s*
	$(REMOVE) univs_client univs_server
	$(REMOVE) UniversityS/*
	$(REMOVE) Univ*.class
	$(REMOVE) repository*
	$(REMOVE) ULOG*
	$(REMOVE) *.dat
	$(REMOVE) stderr
	$(REMOVE) stdout

#----------------------------------------------------------------------
