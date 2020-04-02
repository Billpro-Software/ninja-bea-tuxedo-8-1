#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#---------------------------------------------------------------------
#
# advanced.inc
#
# Platform independent makefile fragment which defines the
# administrative build rules common to the advanced samples.
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

# When data filtering is used, the developer must create Tuxedo FML
# field definition files that describe the fields to be filtered on.
# The developer must also tell the notification service where these
# field definition files reside.  Create an environment file with
# this information.  The ubb file will pass this file into the
# appropriate notification servers.

envfile :
	>$@ echo FLDTBLDIR32=$(FLDTBLDIR32)
	>>$@ echo FIELDTBLS32=$(FIELDTBLS32)

#---------------------------------------------------------------------

# When persistent events are used, the queuing system system must
# be booted.  The queuing system requires the user to create a
# transaction long (via tmadmin).  This makefile target creates a
# file containing the command line input for the tmadmin command.

createtlog :
	>$@ echo echo
	>>$@ echo crdl -b 100 -z $(APPDIR)$(SLASH)TLOG
	>>$@ echo crlog -m SITE1
	>>$@ echo quit

#---------------------------------------------------------------------

# When persistent events are used, a queue must be created to hold
# then events.  This queue is created by using the qmadmin.  This
# makefile target creates a file containing the command line input for
# the qmadmin command.

createqueues :
#
#	turn on command echoing
#
	echo echo
#
#
#	create a device on disk for the queue space.  Set the size
#	to 300 disk pages and start at an offset of 0 pages.
#
	>>$@ echo crdl $(QMCONFIG) 0 300
#
#
#	now that we've allocated disk space for the queue space,
#	configure that space.
#
#
#	make a queue space.
#
	>>$@ echo qspacecreate
#
#
#	specify the queue space's name:
#	note : the administrator gets to pick this name
#
	>>$@ echo TMNTSQS
#
#
#	specify the queue space's IPC key:
#
	>>$@ echo $(QUE_IPCKEY)
#
#
#	specify the queue space's size in disk pages:
#
	>>$@ echo 200
#
#
#	specify that there are 2 queues
#	(one for the persistent events, one for undelivered events)
#
	>>$@ echo 2
#
#
#	specify the number of concurrent transactions on the queue space:
#
	>>$@ echo 10
#
#
#	specify the number of concurrent processes that
#	can access the queue space:
#
	>>$@ echo 10
#
#
#	specify the maximum number of events that may be stored in
#	the queue space:
#
	>>$@ echo 200
#
#
#	specify the name of the error queue:
#	note : it MUST be TMNTSFWD_E
#
	>>$@ echo TMNTSFWD_E
#
#
#	specify that the extents should be initialized:
#
	>>$@ echo y
#
#
#	specify the blocking factory:
#
	>>$@ echo 16
#
#
#	open the queue space and create the queues
#
	>>$@ echo qopen
#
#
#	specify the queue space name:
#	note : the qspace name MUST match the one selected above (TMNTSQS)
#
	>>$@ echo TMNTSQS
#
#
#	create the persistent event queue
#
	>>$@ echo qcreate
#
#
#	specify the name of the persistent event queue.
#	note : it MUST be TMNTSFWD_P
#
	>>$@ echo TMNTSFWD_P
#
#
#	specify the queueing order (= first in, first out):
#
	>>$@ echo fifo
#
#
#	specify how to handle out of order enqueueing:
#
	>>$@ echo none
#
#
#	specify the retry limit (that is, how many times to try
#	to deliver an event before moving it to the error queue):
#
	>>$@ echo 5
#
#
#	specify how long to wait (in seconds) before trying to
#	re-deliver an event after an unsuccessful delivery
#	attempt:
#
	>>$@ echo 3
#
#
#	specify how full the queue can get before requiring
#	administrative intervention:
#
	>>$@ echo 80$(PERCENT)
#
#
#	specify how low the queue must get after getting full
#	before new administrative intervention must be performed:
#
	>>$@ echo 0$(PERCENT)
#
#
#	specify the command to run when administrative intervention
#	is required.  For this sample, specify a command that does
#	nothing.
#
	>>$@ echo $(NOOPCMD)
#
#
#	create the error queue.  persistent events that can't be
#	delivered are moved to this queue.  The administrator must
#	either delete them or move them back to the persistent
#	event queue for redelivery.  This is done with the
#	"ntsadmin" tool.
#
	>>$@ echo qcreate
#
#
#	specify the queue name:
#	note : it MUST be TMNTSFWD_E
#
	>>$@ echo TMNTSFWD_E
#
#
#	specify the enqueing order (= fifo):
#
	>>$@ echo fifo
#
#
#	specify how to handle out of order enqueueing:
#
	>>$@ echo none
#
#
#	specify how many times to retry an event before moving it
#	to the error queue.  This number is irrelevant since we're
#	creating the error queue!
#
	>>$@ echo 2
#
#
#	specify how long to wait between retries.  This number is
#	irrelevant since we're creating the error queue!
#
	>>$@ echo 30
#
#
#	specify how full the queue can get before administrative
#	intervention is required:
#
	>>$@ echo 80$(PERCENT)
#
#
#	specify how empty the queue must get after it got full
#	before new administrative intervention is required:
#
	>>$@ echo 0$(PERCENT)
#
#
#	specify the command to run when administrative intervention
#	is required.  For this sample, specify a command that does
#	nothing.
#
	>>$@ echo $(NOOPCMD)
#
#
#	whew! all done
#
	>>$@ echo q

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
#######	since we're using persistent events, we need a transaction log
	>>$@ echo     TLOGDEVICE   = $(DQUOTE)$(APPDIR)$(SLASH)TLOG$(DQUOTE)
	>>$@ echo     TLOGSIZE     = 10
#
	>>$@ echo *GROUPS
#
	>>$@ echo   SYS_GRP
	>>$@ echo     LMID     = SITE1
	>>$@ echo     GRPNO    = 1
#
#	create a null transactional group for the notification service servers
	>>$@ echo   NTS_GRP
	>>$@ echo     LMID     = SITE1
	>>$@ echo     GRPNO    = 2
	>>$@ echo     TMSNAME  = TMS
	>>$@ echo     TMSCOUNT = 2
#
#	since we're using persistent events, we need a persistent queue
#	create a queue transactional group for the queue servers
	>>$@ echo   QUE_GRP
	>>$@ echo     LMID     = SITE1
	>>$@ echo     GRPNO    = 3
	>>$@ echo     TMSNAME  = TMS_QM
	>>$@ echo     TMSCOUNT = 2
#######	make the queue group manage the QUE space we create
####### note : the qspace name MUST match the one selected above (TMNTSQS)
	>>$@ echo     OPENINFO = $(DQUOTE)TUXEDO/QM:$(QMCONFIG)$(SEPARATOR)TMNTSQS$(DQUOTE)
#
#	create a null transactional group for the wire service server
	>>$@ echo   APP_GRP
	>>$@ echo     LMID     = SITE1
	>>$@ echo     GRPNO    = 4
	>>$@ echo     TMSNAME  = TMS
	>>$@ echo     TMSCOUNT = 2
#
	>>$@ echo *SERVERS
#
	>>$@ echo   DEFAULT:
	>>$@ echo     CLOPT = $(DQUOTE)-A$(DQUOTE)
#
#	start the queue server
	>>$@ echo   TMQUEUE
	>>$@ echo     SRVGRP  = QUE_GRP
	>>$@ echo     SRVID   = 1
####### note : the qspace name MUST match the one selected above (TMNTSQS)
	>>$@ echo     CLOPT   = $(DQUOTE)-s TMNTSQS:TMQUEUE --  $(DQUOTE)
#
#	start the queue forwarder, have it forward events to the
#	notification service persistent forwarder
	>>$@ echo   TMQFORWARD
	>>$@ echo     SRVGRP  = QUE_GRP
	>>$@ echo     SRVID   = 2
####### note : the qname MUST be TMNTSFWD_P
	>>$@ echo     CLOPT   = $(DQUOTE)-- -i 2 -q TMNTSFWD_P$(DQUOTE)
#
	>>$@ echo   TMSYSEVT
	>>$@ echo     SRVGRP  = NTS_GRP
	>>$@ echo     SRVID   = 1
#
#	start the user event broker. pass in the environment file
#	so that the user event broker can find the "Story" fml field
#	definition.  This allows the user event broker to perform
#	data filtering.
	>>$@ echo   TMUSREVT
	>>$@ echo     SRVGRP  = NTS_GRP
	>>$@ echo     SRVID   = 2
	>>$@ echo     ENVFILE = $(DQUOTE)$(APPDIR)$(SLASH)envfile$(DQUOTE)
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 1
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -N -M$(DQUOTE)
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 2
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -N$(DQUOTE)
#
	>>$@ echo   TMFFNAME
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 3
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -F$(DQUOTE)
#
#	start the notification service server.  Pass in the environment
#	file so that the notification server can perform data filtering.
#	the -s option specifies the name of the queue space.  This option
#	must be specified since we're using persistent events.  It must
#	match the name of the queue space you created (see the
#	"createqueues" build rule above).
	>>$@ echo   TMNTS
	>>$@ echo     SRVGRP  = NTS_GRP
	>>$@ echo     SRVID   = 3
	>>$@ echo     ENVFILE = $(DQUOTE)$(APPDIR)$(SLASH)envfile$(DQUOTE)
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -s TMNTSQS$(DQUOTE)
#
#	start the notification service transient event forwarder.
#	Pass in the environment file so that the server can perform
#	data filtering.
	>>$@ echo   TMNTSFWD_T
	>>$@ echo     SRVGRP  = NTS_GRP
	>>$@ echo     SRVID   = 4
	>>$@ echo     REPLYQ  = Y
	>>$@ echo     ENVFILE = $(DQUOTE)$(APPDIR)$(SLASH)envfile$(DQUOTE)
#
#	start the notification service persistent event forwarder.
#	Pass in the environment file so that the server can perform
#	data filtering.
	>>$@ echo   TMNTSFWD_P
	>>$@ echo     SRVGRP  = NTS_GRP
	>>$@ echo     SRVID   = 5
	>>$@ echo     ENVFILE = $(DQUOTE)$(APPDIR)$(SLASH)envfile$(DQUOTE)
#
#	start the wire service server.  Since the exact command varies
#	with each advanced notification sample, have each sample's makefile
#	define two variables (WIRE_SERVICE_SERVER) and (WIRE_SERVICE_CLOPT)
#	to specify the name of the server and its command line options.
	>>$@ echo   $(WIRE_SERVICE_SERVER)
	>>$@ echo     SRVGRP  = APP_GRP
	>>$@ echo     SRVID   = 1
	>>$@ echo     CLOPT   = $(WIRE_SERVICE_CLOPT)
#
#	start the ISL with -O since we're using callbacks to clients
	>>$@ echo   ISL
	>>$@ echo     SRVGRP  = SYS_GRP
	>>$@ echo     SRVID   = 4
	>>$@ echo     CLOPT   = $(DQUOTE)-A -- -O -n $(TOBJADDR)$(DQUOTE)
#
	>>$@ echo *SERVICES

#---------------------------------------------------------------------

# Create the the tux configuration file from the ubb file

tuxconfig: ubb
	tmloadcf -y ubb

#---------------------------------------------------------------------

# Create the transaction log (using the command line input file
# generated above).  This is only necessary if persistent events
# are being used.

TLOG: createtlog
	tmadmin < createtlog

#---------------------------------------------------------------------

# Create the transaction log (using the command line input file
# generated above).  This is only necessary if persistent events
# are being used.

QUE: createqueues
	-$(RM) $@
	qmadmin $(APPDIR)$(SLASH)$(@) < createqueues

#----------------------------------------------------------------------
