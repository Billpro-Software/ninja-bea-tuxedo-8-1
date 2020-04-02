#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.mk
#
# Unix makefile for the simpapp_mt sample application
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

#---------------------------------------------------------------------
# Declarations
#---------------------------------------------------------------------

REMOVE=-rm -f

RMDIR=-rm -rf

#---------------------------------------------------------------------
# Main build rules
#---------------------------------------------------------------------

all: simple_client simple_per_object_server simple_per_request_server

#---------------------------------------------------------------------
# C++ Client
#---------------------------------------------------------------------

CLIENT_SRCS = simple_c.cpp simple_client.cpp

simple_client: $(CLIENT_SRCS)
	buildobjclient -v -o $@ -f "$(CLIENT_SRCS)"

#---------------------------------------------------------------------
# C++ Servers
#---------------------------------------------------------------------

SPO_SRCS= simple_c.cpp simple_s.cpp simple_per_object_i.cpp simple_per_object_server.cpp thread_macros.cpp

simple_per_object_server: $(SPO_SRCS)
	buildobjserver -v -t -o $@ -f "$(SPO_SRCS)"

SPR_SRCS= simple_c.cpp simple_s.cpp simple_per_request_i.cpp simple_per_request_server.cpp thread_macros.cpp

simple_per_request_server: $(SPR_SRCS)
	buildobjserver -v -t -b simple_per_request_server -o $@ -f "$(SPR_SRCS)"

#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

simple_c.cpp simple_c.h simple_s.cpp simple_s.h : simple.idl
	idl simple.idl

#---------------------------------------------------------------------
# File dependencies
#---------------------------------------------------------------------

simple_per_object_i.h : simple_s.h
simple_per_object_i.cpp : simple_per_object_i.h
simple_per_object_server.cpp : simple_per_object_i.h
simple_per_request_i.h : simple_s.h
simple_per_request_i.cpp : simple_per_request_i.h
simple_per_request_server.cpp : simple_per_request_i.h
simple_client.cpp : simple_c.h

#----------------------------------------------------------------------
# Housekeeping
#----------------------------------------------------------------------

clean:
	$(REMOVE) OBB*
	$(REMOVE) *.o
	$(REMOVE) simple_c.*
	$(REMOVE) simple_s.*
	$(REMOVE) ULOG*
	$(REMOVE) *.dat
	$(REMOVE) stderr
	$(REMOVE) stdout
	$(REMOVE) simple_client
	$(REMOVE) simple_per_request_server
	$(REMOVE) simple_per_object_server
	$(RMDIR)  $(RESULTSDIR)

#----------------------------------------------------------------------
