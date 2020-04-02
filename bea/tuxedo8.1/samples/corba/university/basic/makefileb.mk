#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefileb.mk
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

servers    : univb_server

ifrepos    : repository.ifr

cxxclient  : univb_client

javaclient : UnivBApplet.class

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS =               \
    $(UTILS)/log.cpp        \
    $(UTILS)/log_client.cpp \
    univb_c.cpp             \
    univb_utils.cpp         \
    univbc.cpp

univb_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ \
	    -f "$(CLIENT_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# Java Client
#---------------------------------------------------------------------

UnivBApplet.class: UnivBApplet.java univb.idl
	$(IDLTOJAVA) univb.idl
	javac -g UnivBApplet.java

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
    univb_c.cpp               \
    univb_s.cpp               \
    univb_utils.cpp           \
    univb_i.cpp               \
    univbs.cpp

univb_server: $(UNIV_SERVER_SRCS)
	buildobjserver -v -o $@ -r $(RM) \
	    -f "$(UNIV_SERVER_SRCS) $(CPPFLAGS)"

#----------------------------------------------------------------------
# Interface Repository file
#----------------------------------------------------------------------

repository.ifr : univb.idl
	idl2ir $(IDLFLAGS) $(TUXINC)/tobjin.idl univb.idl

#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

univb_c.cpp univb_c.h univb_s.cpp univb_s.h : univb.idl univb.icf
	idl $(IDLFLAGS) univb.idl univb.icf

#---------------------------------------------------------------------
# Initialize the database
#---------------------------------------------------------------------

LOADSCRIPT=     $(UTILS)/university.sql

initdb	:
	sqlplus $(USERID) @$(LOADSCRIPT) </dev/null

#---------------------------------------------------------------------
# Header file dependencies
#---------------------------------------------------------------------

univb_i.h               : univb_s.h $(UTILS)/samplesdb.h
univb_utils.h           : univb_c.h

$(UTILS)/samplesdbsql.h	: $(UTILS)/samplesdb.h

#---------------------------------------------------------------------
# Source file dependencies
#---------------------------------------------------------------------

univb_utils.cpp	         : univb_utils.h
univb_i.cpp              : $(UTILS)/log.h $(UTILS)/unique_id.h \
                           univb_utils.h univb_i.h
univbs.cpp               : $(UTILS)/log.h univb_i.h
univbc.cpp               : $(UTILS)/log.h univb_utils.h

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
	$(REMOVE) univb_c*
	$(REMOVE) univb_s*
	$(REMOVE) univb_client univb_server
	$(REMOVE) UniversityB/*
	$(REMOVE) Univ*.class
	$(REMOVE) repository*
	$(REMOVE) ULOG*
	$(REMOVE) *.dat
	$(REMOVE) stderr
	$(REMOVE) stdout

#----------------------------------------------------------------------
