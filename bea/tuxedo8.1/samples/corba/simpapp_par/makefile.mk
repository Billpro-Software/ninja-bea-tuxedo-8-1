#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.mk
#
# Unix makefile for the simpapp_par sample application
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

#---------------------------------------------------------------------
# Declarations
#---------------------------------------------------------------------

REMOVE=-rm -f

RMDIR=-rm -rf

RESULTSDIR=results

#---------------------------------------------------------------------
# Main build rules
#---------------------------------------------------------------------

all: simple_client simple_server simple_factory

java_all: all SimpleClient.jar

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS = simple_c.cpp simplec.cpp simplef_c.cpp

simple_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ -f "$(CLIENT_SRCS)"

#---------------------------------------------------------------------
# C++ Server
#---------------------------------------------------------------------

SERVER_SRCS= simple_c.cpp simple_s.cpp simple_i.cpp simples.cpp
FACTORY_SRCS= simplef_c.cpp simplef_s.cpp simplef_i.cpp simplefs.cpp simple_c.cpp

simple_server: $(SERVER_SRCS)
	buildobjserver -v -o $@ -f "$(SERVER_SRCS) $(CPPFLAGS)"

simple_factory: $(FACTORY_SRCS)
	buildobjserver -v -o $@ -f "$(FACTORY_SRCS) $(CPPFLAGS)"

#----------------------------------------------------------------------
# C++ IDL files
#----------------------------------------------------------------------

simple_c.cpp simple_c.h simple_s.cpp simple_s.h : simple.idl simple.icf
	idl simple.idl simple.icf

simplef_c.cpp simplef_c.h simplef_s.cpp simplef_s.h : simplef.idl
	idl simplef.idl

#---------------------------------------------------------------------
# C++ File dependencies
#---------------------------------------------------------------------

simple_i.h   : simple_s.h
simple_i.cpp : simple_i.h
simples.cpp  : simple_i.h
simplec.cpp  : simple_c.h

#---------------------------------------------------------------------
# Java IDL Files
#---------------------------------------------------------------------

JAVAIDLFILES =  SimpleFactory.java \
                SimpleFactoryHelper.java \
                SimpleFactoryHolder.java \
                _SimpleFactoryStub.java \
                Simple.java \
                SimpleHelper.java \
                SimpleHolder.java \
                _SimpleStub.java

JAVAIDLCLASSES= $(JAVAIDLFILES:.java=.class)

$(JAVAIDLFILES) : simple.idl simplef.idl
	idltojava simple.idl
	idltojava simplef.idl

#---------------------------------------------------------------------
# Java Client
#---------------------------------------------------------------------

$(JAVAIDLCLASSES): $(JAVAIDLFILES)

SimpleClient.class: SimpleClient.java $(JAVAIDLCLASSES)

#---------------------------------------------------------------------
# Java Client JAR
#---------------------------------------------------------------------

CLIENTJARCLASSES = $(JAVAIDLCLASSES) \
                   SimpleClient.class

SimpleClient.jar: $(CLIENTJARCLASSES)
	jar cvf SimpleClient.jar $(CLIENTJARCLASSES)

#----------------------------------------------------------------------
# Java Suffix rules
#----------------------------------------------------------------------

.SUFFIXES: .class .java

.java.class:
	javac -classpath $(CLASSPATH) $<

#----------------------------------------------------------------------
# Housekeeping
#----------------------------------------------------------------------

clean:
	$(REMOVE) *.o
	$(REMOVE) *.class
	$(REMOVE) simple_c*
	$(REMOVE) simple_s*
	$(REMOVE) simple_f*
	$(REMOVE) simplef_c*
	$(REMOVE) simplef_s*
	$(REMOVE) $(JAVAIDLFILES)
	$(REMOVE) *ImplBase.java
	$(REMOVE) SimpleClient.jar
	$(REMOVE) ULOG*
	$(REMOVE) *.dat
	$(REMOVE) stderr
	$(REMOVE) stdout
	$(RMDIR)  .adm
	$(RMDIR)  $(RESULTSDIR)

#----------------------------------------------------------------------
