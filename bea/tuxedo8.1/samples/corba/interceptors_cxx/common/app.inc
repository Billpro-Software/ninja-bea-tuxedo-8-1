#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# app.inc
#
# Platform independent makefile fragment which defines the
# administrative build rules common to the interceptor samples.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

# Create the ubb configuration file

ubb :
	>$@ echo *RESOURCES
	>>$@ echo   IPCKEY    $(DOMAIN_IPCKEY)
	>>$@ echo   DOMAINID  $(DOMAINID)
	>>$@ echo   MASTER    SITE1
	>>$@ echo   MODEL     SHM
#
	>>$@ echo *MACHINES
	>>$@ echo   $(DQUOTE)$(HOST)$(DQUOTE)
	>>$@ echo     LMID         = SITE1
	>>$@ echo     APPDIR       = $(DQUOTE)$(APPDIR)$(DQUOTE)
	>>$@ echo     TUXCONFIG    = $(DQUOTE)$(TUXCONFIG)$(DQUOTE)
	>>$@ echo     TUXDIR       = $(DQUOTE)$(TUXDIR)$(DQUOTE)
	>>$@ echo     MAXWSCLIENTS = 10
	>>$@ echo     ULOGPFX      = $(DQUOTE)$(APPDIR)$(SLASH)ULOG$(DQUOTE)
#
	>>$@ echo *GROUPS
#
	>>$@ echo   SYS_GRP
	>>$@ echo     LMID     = SITE1
	>>$@ echo     GRPNO    = 1
#
	>>$@ echo   APP_GRP
	>>$@ echo     LMID     = SITE1
	>>$@ echo     GRPNO    = 2
#
	>>$@ echo *SERVERS
#
	>>$@ echo   DEFAULT:
	>>$@ echo     CLOPT = $(DQUOTE)-A$(DQUOTE)
#
	>>$@ echo   TMSYSEVT
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 1
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 2
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -N -M$(DQUOTE)
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 3
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -N$(DQUOTE)
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 4
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -F$(DQUOTE)
#
#	start the interceptor sample service server. Have the sample's makefile
#	define two variables (APP_SERVICE_SERVER) and (APP_SERVICE_CLOPT)
#	to specify the name of the server and its command line options.
	>>$@ echo   $(APP_SERVICE_SERVER)
	>>$@ echo     SRVGRP  = APP_GRP
	>>$@ echo     SRVID   = 1
	>>$@ echo     CLOPT   = $(APP_SERVICE_CLOPT)
#
	>>$@ echo   ISL
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 5
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -n $(TOBJADDR)$(DQUOTE)
#
	>>$@ echo *SERVICES

#---------------------------------------------------------------------

# Create the the tux configuration file from the ubb file

tuxconfig: ubb
	tmloadcf -y ubb

#----------------------------------------------------------------------
