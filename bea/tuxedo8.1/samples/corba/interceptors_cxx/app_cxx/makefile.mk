#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# makefile.mk
#
# Unix makefile for the interceptors c++ sample application
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

# check that "setenv.ksh" was run first:
.INIT:
	@ test ${INTERCEPTOR_CXX_SETUP};                 \
	if [ $$? -ne 0 ]; then                            \
		echo ERROR : setenv.ksh has not been run; \
		exit 1;                                   \
	fi

# platform specific constants:
include $(COMMONDIR)/common.mk
include $(COMMONDIR)/$(MAKEFILE_PREFIX).inc

# the build rules for this sample:
include makefile.inc

# configuration build rules common to the interceptor application samples:
include $(COMMONDIR)/app.inc
