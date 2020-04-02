#--------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.inc
#
# common makefile for the  interceptor c++ sample application
#
# BEA Systems Inc. sample code
#
#--------------------------------------------------------------------
#
# makefile.inc contains the rules for building the common files.
# Common files are those shared among the c++ interceptor samples.
#
#--------------------------------------------------------------------
#
# define symbols for building this directories targets
#
SRC = personquery_c.cpp
OBJ = personquery_c$(OBJEXT)
OBJS = $(OBJ)

ALL = $(OBJ)


#--------------------------------------------------------------------
#
# define default target 
#
all: $(ALL)

#--------------------------------------------------------------------
#
# Compile the idl
#
personquery_c.cpp : personquery.idl
	idl personquery.idl

#--------------------------------------------------------------------
#
# Compile the C++ file; it will be linked in from other directories
#
personquery_c$(OBJEXT) : personquery_c.cpp
	$(CPPCMD)

#--------------------------------------------------------------------
#
# Define a target for cleaning up
#
clean:
	-$(RM)    $(ALL) $(TEMP_FILES) *_c.* *_s.*
	-$(RM)    stderr ULOG* *out *.dat

#--------------------------------------------------------------------
