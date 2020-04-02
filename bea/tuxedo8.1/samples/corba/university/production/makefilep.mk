#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefilep.mk
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
UTILS= $(APPDIR)/../utils

# Oracle SQL Precompiler stuff :
PROCPLSFLAGS= sqlcheck=full userid=$(USERID)
PROCPPFLAGS=  code=cpp include=/usr/include      \
     include=$(CPPINC) include=$(ORAINC)         \
     include=$(TUXINC) include=$(UTILS)

PROCFLAGS=    code=ansi_c include=/usr/include  \
     include=$(CPPINC) include=$(ORAINC)        \
     include=$(TUXINC) include=$(UTILS)

# CORBA IDL compiler stuff :
IDLFLAGS=-D_TOBJ -I$(TUXINC)

# C compiler stuff :
#CC=$(CCMPL)
CFLAGS=$(SYSFLAGS) $(ANCFLAGS) -I. $(PRECOMPPUBLIC) -I$(UTILS)

# C++ compiler stuff :
CPP=$(CPPCMPL)
CPPFLAGS=$(SYSFLAGS) $(CXXFLAGS) -I. $(PRECOMPPUBLIC) -I$(UTILS) -DNO_TRACING

#---------------------------------------------------------------------
# Main build rules
#---------------------------------------------------------------------

# by default, don't build the java client:
all        : servers ifrepos cxxclient

servers    : univp_server billp_server tellp_server TMS_ORA

ifrepos    : repository.ifr

cxxclient  : univp_client

javaclient : UnivPApplet.class

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS =               \
    $(UTILS)/log.cpp        \
    $(UTILS)/log_client.cpp \
    univp_c.cpp             \
    univp_utils.cpp         \
    univpc.cpp

univp_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ \
	    -f "$(CLIENT_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# Java Client
#---------------------------------------------------------------------

UnivPApplet.class: UnivPApplet.java univp.idl
	$(IDLTOJAVA) univp.idl
	javac -g UnivPApplet.java

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
    billp_c.cpp               \
    univp_c.cpp               \
    univp_s.cpp               \
    univp_utils.cpp           \
    univp_i.cpp               \
    univps.cpp

univp_server: $(UNIV_SERVER_SRCS)
	buildobjserver -v -o $@ -r $(RM) \
	    -f "$(UNIV_SERVER_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# C Tuxedo Teller Server
#---------------------------------------------------------------------

TELL_SERVER_SRCS= \
    tellp_u.c     \
    tellps.c

tellp_server: $(TELL_SERVER_SRCS)
	CC="$(CCMPL)" buildserver -v -o $@ -r $(RM)          \
	    -s DEBIT -s CREDIT -s CURRBALANCE  \
	    -f "$(TELL_SERVER_SRCS) $(CFLAGS)"

#---------------------------------------------------------------------
# C++ Billing Server
#---------------------------------------------------------------------

BILL_SERVER_SRCS=           \
    $(UTILS)/log.cpp        \
    $(UTILS)/log_server.cpp \
    $(UTILS)/unique_id.cpp  \
    billp_c.cpp             \
    billp_s.cpp             \
    billp_i.cpp             \
    billps.cpp

billp_server: $(BILL_SERVER_SRCS)
	buildobjserver -v -o $@ \
            -f "$(BILL_SERVER_SRCS) $(CPPFLAGS)"

#----------------------------------------------------------------
#	Transaction management server
#----------------------------------------------------------------

TMS_ORA:
	buildtms -v -o $@ -r $(RM)

#----------------------------------------------------------------------
# Interface Repository file
#----------------------------------------------------------------------

repository.ifr : univp.idl
	idl2ir $(IDLFLAGS) $(TUXINC)/tobjin.idl univp.idl

#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

tellp_flds.h : tellp_flds
	mkfldhdr32 tellp_flds

billp_c.cpp billp_c.h billp_s.cpp billp_s.h : billp.idl billp.icf
	idl $(IDLFLAGS) billp.idl billp.icf

univp_c.cpp univp_c.h univp_s.cpp univp_s.h : univp.idl univp.icf
	idl $(IDLFLAGS) univp.idl univp.icf

#---------------------------------------------------------------------
# Initialize the database
#---------------------------------------------------------------------

LOADSCRIPT=     $(UTILS)/university.sql

initdb	:
	sqlplus $(USERID) @$(LOADSCRIPT) </dev/null

#---------------------------------------------------------------------
# Header file dependencies
#---------------------------------------------------------------------

univp_i.h               : univp_s.h $(UTILS)/samplesdb.h
univp_utils.h           : univp_c.h

$(UTILS)/samplesdbsql.h	: $(UTILS)/samplesdb.h

#---------------------------------------------------------------------
# Source file dependencies
#---------------------------------------------------------------------

tellp_u.c                : tellp_u.h tellp_flds.h
tellps.c		 : tellps.ec
tellps.ec                : tellp_u.h tellp_flds.h

billp_i.cpp              : $(UTILS)/log.h tellp_flds.h billp_i.h
billps.cpp               : $(UTILS)/log.h billp_i.h

univp_utils.cpp	         : univp_utils.h
univp_i.cpp              : $(UTILS)/log.h $(UTILS)/unique_id.h \
                           univp_utils.h univp_i.h
univps.cpp               : $(UTILS)/log.h univp_i.h
univpc.cpp               : $(UTILS)/log.h univp_utils.h

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
.SUFFIXES:      .pc .ec .cpp .c .java .class

#----------------------------------------------------------------------
# Suffix rules
#----------------------------------------------------------------------

.pc.cpp:
	$(PROC) $(PROCPLSFLAGS) $(PROCPPFLAGS) iname=$*.pc oname=$*.cpp

.ec.c:
	$(PROC) $(PROCPLSFLAGS) $(PROCFLAGS) iname=$*.ec

.java.class:
	javac -g $<

#----------------------------------------------------------------------
# Housekeeping
#----------------------------------------------------------------------

clean:
	$(REMOVE) $(UTILS)/samplesdbsql.cpp
	$(REMOVE) tellp_flds.h
	$(REMOVE) tellps.c
	$(REMOVE) *.o
	$(REMOVE) univp_c*
	$(REMOVE) univp_s*
	$(REMOVE) billp_c*
	$(REMOVE) billp_s*
	$(REMOVE) univp_client univp_server billp_server tellp_server TMS_ORA
	$(REMOVE) UniversityP/*
	$(REMOVE) Univ*.class
	$(REMOVE) repository*

#----------------------------------------------------------------------
