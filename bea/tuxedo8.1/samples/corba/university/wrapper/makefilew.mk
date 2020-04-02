#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefilew.mk
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
PROCPPFLAGS=  code=cpp include=/usr/include     \
     include=$(CPPINC) include=$(ORAINC)        \
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
CPPFLAGS=$(SYSFLAGS) $(CXXFLAGS) -I. $(PRECOMPPUBLIC) -I$(UTILS)

#---------------------------------------------------------------------
# Main build rules
#---------------------------------------------------------------------

# by default, don't build the java client:
all        : servers ifrepos cxxclient

servers    : univw_server billw_server tellw_server TMS_ORA

ifrepos    : repository.ifr

cxxclient  : univw_client

javaclient : UnivWApplet.class

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS =               \
    $(UTILS)/log.cpp        \
    $(UTILS)/log_client.cpp \
    univw_c.cpp             \
    univw_utils.cpp         \
    univwc.cpp

univw_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ \
	    -f "$(CLIENT_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# Java Client
#---------------------------------------------------------------------

UnivWApplet.class: UnivWApplet.java univw.idl
	$(IDLTOJAVA) univw.idl
	javac -g UnivWApplet.java

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
    billw_c.cpp               \
    univw_c.cpp               \
    univw_s.cpp               \
    univw_utils.cpp           \
    univw_i.cpp               \
    univws.cpp

univw_server: $(UNIV_SERVER_SRCS)
	buildobjserver -v -o $@ -r $(RM) \
	    -f "$(UNIV_SERVER_SRCS) $(CPPFLAGS)"

#---------------------------------------------------------------------
# C Tuxedo Teller Server
#---------------------------------------------------------------------

TELL_SERVER_SRCS= \
    tellw_u.c     \
    tellws.c

tellw_server: $(TELL_SERVER_SRCS)
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
    billw_c.cpp             \
    billw_s.cpp             \
    billw_i.cpp             \
    billws.cpp

billw_server: $(BILL_SERVER_SRCS)
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

repository.ifr : univw.idl
	idl2ir $(IDLFLAGS) $(TUXINC)/tobjin.idl univw.idl

#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

tellw_flds.h : tellw_flds
	mkfldhdr32 tellw_flds

billw_c.cpp billw_c.h billw_s.cpp billw_s.h : billw.idl billw.icf
	idl $(IDLFLAGS) billw.idl billw.icf

univw_c.cpp univw_c.h univw_s.cpp univw_s.h : univw.idl univw.icf
	idl $(IDLFLAGS) univw.idl univw.icf

#---------------------------------------------------------------------
# Initialize the database
#---------------------------------------------------------------------

LOADSCRIPT=     $(UTILS)/university.sql

initdb	:
	sqlplus $(USERID) @$(LOADSCRIPT) </dev/null

#---------------------------------------------------------------------
# Header file dependencies
#---------------------------------------------------------------------

univw_i.h               : univw_s.h $(UTILS)/samplesdb.h
univw_utils.h           : univw_c.h

$(UTILS)/samplesdbsql.h	: $(UTILS)/samplesdb.h

#---------------------------------------------------------------------
# Source file dependencies
#---------------------------------------------------------------------

tellw_u.c                : tellw_u.h tellw_flds.h
tellws.c		 : tellws.ec
tellws.ec                : tellw_u.h tellw_flds.h

billw_i.cpp              : $(UTILS)/log.h tellw_flds.h billw_i.h
billws.cpp               : $(UTILS)/log.h billw_i.h

univw_utils.cpp	         : univw_utils.h
univw_i.cpp              : $(UTILS)/log.h $(UTILS)/unique_id.h \
                           univw_utils.h univw_i.h
univws.cpp               : $(UTILS)/log.h univw_i.h
univwc.cpp               : $(UTILS)/log.h univw_utils.h

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
	$(REMOVE) tellw_flds.h
	$(REMOVE) tellws.c
	$(REMOVE) *.o
	$(REMOVE) univw_c*
	$(REMOVE) univw_s*
	$(REMOVE) billw_c*
	$(REMOVE) billw_s*
	$(REMOVE) univw_client univw_server billw_server tellw_server TMS_ORA
	$(REMOVE) UniversityW/*
	$(REMOVE) Univ*.class
	$(REMOVE) repository*
	$(REMOVE) ULOG*
	$(REMOVE) xa*.trc
	$(REMOVE) *.dat
	$(REMOVE) stderr
	$(REMOVE) stdout

#----------------------------------------------------------------------
