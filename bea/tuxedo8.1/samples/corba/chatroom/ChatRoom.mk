#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# File: ChatRoom.mk
#
# Unix makefile for the Tuxedo ChatRoom: the callback sample application
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

#---------------------------------------------------------------------
# Declarations
#---------------------------------------------------------------------

REMOVE=-rm -f
RMDIR=-rm -rf


# C++ compiler stuff :
CPP=$(CPPCMPL)
CPPFLAGS= -D_REENTRANT -I. -I$(CPPINC) -I$(TUXDIR)/include

.SUFFIXES: .cpp .o

#---------------------------------------------------------------------
# target: "all"
#	Builds client and server
#---------------------------------------------------------------------

all : client server

client : ChatClient ChatClientW

server : ChatRoomServer

ClientSources = ChatClientMain.cpp ChatClient_s.cpp Listener_i.cpp \
			ChatClient_c.cpp ChatRoom_c.cpp KeyboardManager.cpp

ClientWObjects = ChatClientMainW.o ChatClient_c.o ChatClient_s.o \
			ChatRoom_c.o Listener_i.o KeyboardManager.o

ChatClientMainW.o : ChatClientMain.cpp
	$(CPP) $(CPPFLAGS) $(SYSFLAGS) -DBEA_WRAPPER -o $@ -c ChatClientMain.cpp

ServerSources = ChatRoomServer.cpp ChatRoom_s.cpp Moderator_i.cpp \
	ChatRoom_c.cpp ChatClient_c.cpp

#---------------------------------------------------------------------
# Client
#---------------------------------------------------------------------

ChatClient: $(ClientSources)
	buildobjclient -P -v -o $@ -f "$(ClientSources)"

ChatClientW: $(ClientWObjects)
	buildobjclient -P -v -o $@ -f "$(ClientWObjects) -lbeawrapper"


#---------------------------------------------------------------------
# Server
#---------------------------------------------------------------------

ChatRoomServer: $(ServerObjects)
	buildobjserver -v -o $@ -f "$(ServerSources)"


#----------------------------------------------------------------------
# IDL files
#----------------------------------------------------------------------

ChatClient_s.h ChatClient_c.h ChatClient_s.cpp ChatClient_c.cpp : ChatClient.idl
	idl -P ChatClient.idl

ChatRoom_s.h ChatRoom_c.h ChatRoom_s.cpp ChatRoom_c.cpp : ChatRoom.idl ChatRoom.icf
	idl ChatRoom.idl ChatRoom.icf

#----------------------
# target: "clean" 
#    gets rid of object files and cousins
#----------------------

clean:
	$(REMOVE) *.o
	$(REMOVE) ChatClient
	$(REMOVE) ChatClientW
	$(REMOVE) ChatRoomServer
	$(REMOVE) *.log
	$(REMOVE) stderr
	$(REMOVE) stdout

#----------------------
# target: "superclean" 
#    gets rid of object files and cousins, and then stubs and skeletons
#----------------------
superclean: clean adminclean
	$(REMOVE) *_c.*
	$(REMOVE) *_s.*

#----------------------
# target: "adminclean" 
# Removes Tuxedo admin files. After this, must run "ChatSetup.ksh" again.
#----------------------
adminclean:
	$(REMOVE) build.log
	$(REMOVE) Admin/*
	$(RMDIR) Admin/.adm
	$(RMDIR) Admin

