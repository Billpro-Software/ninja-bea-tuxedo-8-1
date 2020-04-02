#---------------------------------------------------------------------
#
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
# makefile.mk
#
# Unix makefile for the interceptors samples 
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------
#
# check that "setenv.ksh" was run first:
#
.INIT:
	@ test ${INTERCEPTOR_CXX_SETUP};                 \
	if [ $$? -ne 0 ]; then                            \
		echo ERROR : setenv.ksh has not been run; \
		exit 1;                                   \
	fi

#---------------------------------------------------------------------
#
# define symbols for building all interceptor samples directories
#
ARGS=all

ALL=common simple_cxx security_cxx data_cxx app_cxx

#---------------------------------------------------------------------
#
# default target for building
#

all: $(ALL)

$(ALL)::
	cd $(@) ; \
	$(MAKE) -f makefile.mk $(ARGS) ; \
	cd .. ;

#--------------------------------------------------------------------
#
# target for cleaning up subdirectories
#
clean :
	$(MAKE) -f makefile.mk ARGS=$@

#--------------------------------------------------------------------
