#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefilet.mk
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

servers    : univt_server TMS_ORA

ifrepos    : repository.ifr

cxxclient  : univt_client

javaclient : UnivTApplet.class

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS =               \
    $(UTILS)/log.cpp        \
    $(UTILS)/log_client.cpp \
    univt_c.cpp             \
    univt_utils.cpp         \
    univtc.cpp

univt_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ \
	    -f "$(CLIENT_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# Java Client
#---------------------------------------------------------------------

UnivTApplet.class: UnivTApplet.java univt.idl
	$(IDLTOJAVA) univt.idl
	javac -g UnivTApplet.java

#---------------------------------------------------------------------
# C++ University Server
#---------------------------------------------------------------------

UNIV_SERVER_SRCS=             \
    $(UTILS)/log.cpp          \
    $(UTILS)/log_server.cpp   \
    $(UTILS)/unique_id.cpp    \
    $(UTILS)/samplesdb.cpp    \
    $(UTILS)/samplesdbsql.cpp \
    $(UTILS)/oranoconn.cpp    \
    univt_c.cpp               \
    univt_s.cpp               \
    univt_utils.cpp           \
    univt_i.cpp               \
    univts.cpp

univt_server: $(UNIV_SERVER_SRCS)
	buildobjserver -v -o $@ -r $(RM) \
	    -f "$(UNIV_SERVER_SRCS) $(CPPFLAGS)"

#----------------------------------------------------------------
#	Transaction management server
#----------------------------------------------------------------

TMS_ORA:
	buildtms -v -o $@ -r $(RM)

#----------------------------------------------------------------------
# Interface Repository file
#----------------------------------------------------------------------

repository.ifr : univt.idl
	idl2ir $(IDLFLAGS) $(TUXINC)/tobjin.idl univt.idl

#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

univt_c.cpp univt_c.h univt_s.cpp univt_s.h : univt.idl univt.icf
	idl $(IDLFLAGS) univt.idl univt.icf

#---------------------------------------------------------------------
# Initialize the database
#---------------------------------------------------------------------

LOADSCRIPT=     $(UTILS)/university.sql

initdb	:
	sqlplus $(USERID) @$(LOADSCRIPT) </dev/null

#---------------------------------------------------------------------
# Header file dependencies
#---------------------------------------------------------------------

univt_i.h               : univt_s.h $(UTILS)/samplesdb.h
univt_utils.h           : univt_c.h

$(UTILS)/samplesdbsql.h	: $(UTILS)/samplesdb.h

#---------------------------------------------------------------------
# Source file dependencies
#---------------------------------------------------------------------

univt_utils.cpp	         : univt_utils.h
univt_i.cpp              : $(UTILS)/log.h $(UTILS)/unique_id.h \
                           univt_utils.h univt_i.h
univts.cpp               : $(UTILS)/log.h univt_i.h
univtc.cpp               : $(UTILS)/log.h univt_utils.h

$(UTILS)/log.cpp         : $(UTILS)/log.h
$(UTILS)/log_client.cpp  : $(UTILS)/log.h
$(UTILS)/log_server.cpp  : $(UTILS)/log.h
$(UTILS)/samplesdb.cpp   : $(UTILS)/samplesdb.h
$(UTILS)/oranoconn.cpp   : $(UTILS)/samplesdbsql.h
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
	javac -g $<

#----------------------------------------------------------------------
# Housekeeping
#----------------------------------------------------------------------

clean:
	$(REMOVE) $(UTILS)/samplesdbsql.cpp
	$(REMOVE) *.o
	$(REMOVE) univt_c*
	$(REMOVE) univt_s*
	$(REMOVE) univt_client univt_server TMS_ORA
	$(REMOVE) UniversityT/*
	$(REMOVE) Univ*.class
	$(REMOVE) repository*
	$(REMOVE) ULOG*
	$(REMOVE) xa*.trc
	$(REMOVE) *.dat
	$(REMOVE) stderr
	$(REMOVE) stdout

#----------------------------------------------------------------------
