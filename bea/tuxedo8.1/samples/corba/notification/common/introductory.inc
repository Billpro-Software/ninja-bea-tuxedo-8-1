#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#---------------------------------------------------------------------
#
# introductory.inc
#
# Platform independent makefile fragment which defines the
# administrative build rules common to the introductory samples.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

# Create the ubb configuration file

ubb:
	>$@  echo *RESOURCES
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
#	since we're using transient events, the group need not be transactional
	>>$@ echo *GROUPS
#
	>>$@ echo   SYS_GRP 
	>>$@ echo     LMID     = SITE1 
	>>$@ echo     GRPNO    = 1
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
#	start the user event broker
	>>$@ echo   TMUSREVT
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 2
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 3
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -N -M$(DQUOTE)
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 4
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -N$(DQUOTE)
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 5
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -F$(DQUOTE)
#
#	start the notification service server
	>>$@ echo   TMNTS
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 6
#
#	start the notification service transient event forwarder
	>>$@ echo   TMNTSFWD_T
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 7
	>>$@ echo     REPLYQ  = Y
#
#	start the ISL with -O since we're using callbacks to clients
	>>$@ echo   ISL
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 8
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -O -n $(TOBJADDR)$(DQUOTE)
#
	>>$@ echo *SERVICES

#---------------------------------------------------------------------

# Create the the tux configuration file from the ubb file

tuxconfig: ubb
	tmloadcf -y ubb

#---------------------------------------------------------------------

