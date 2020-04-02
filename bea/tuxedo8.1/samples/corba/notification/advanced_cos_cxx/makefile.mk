#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.mk
#
# Unix makefile for the advanced cos notification c++ sample
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

# check that "setenv.ksh" was run first:
.INIT:
	@ test ${ADVANCED_COS_CXX_SETUP};                 \
	if [ $$? -ne 0 ]; then                            \
		echo ERROR : setenv.ksh has not been run; \
		exit 1;                                   \
	fi

# platform specific constants:
include $(COMMONDIR)/common.mk

# the build rules for this sample:
include makefile.inc

# configuration build rules common to all the advanced samples:
include $(COMMONDIR)/advanced.inc