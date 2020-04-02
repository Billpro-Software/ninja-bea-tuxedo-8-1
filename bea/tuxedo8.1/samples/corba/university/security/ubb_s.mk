#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# ubb_s.mk
#
# Unix template onfiguration file for the university sample application
#
# Edit any item beginning with the text "MY_" to reflect your
# particular site configuration data.
#
# Also, check that the value of TUXDIR is correct.
# (this file contains typical values)
#
# For more information on the contents of this file, refer to
# the document "BEA Administering Tuxedo Systems"
#
# BEA Systems Inc. sample code
#
#---------------------------------------------------------------------

*RESOURCES
    IPCKEY    55432
    DOMAINID  university
    MASTER    SITE1
    MODEL     SHM
    LDBAL     N
    SECURITY  APP_PW	

#---------------------------------------------------------------------

*MACHINES

#   Specify the name of your server machine
#
    MY_SERVER_MACHINE
        LMID = SITE1

#   Pathname of your copy of this sample application.
#   Must match "APPDIR" in "setenv.sh"
#
    APPDIR = "/usr/users/my_samples_dir/security"

#   Pathname of the tuxconfig file.
#   Must match "TUXCONFIG" in "setenv.sh"
# 
    TUXCONFIG="/usr/users/my_samples_dir/security/tuxconfig"

#   Pathname of the Tuxedo installation.
#   Must match "TUXDIR" in "setenv.sh"
#
    TUXDIR="/usr/local/tuxdir"

    MAXWSCLIENTS=10

#---------------------------------------------------------------------

*GROUPS

    SYS_GRP
        LMID    = SITE1
        GRPNO   = 1

    ORA_GRP
        LMID    = SITE1
        GRPNO   = 2

#---------------------------------------------------------------------

*SERVERS

    # By default, restart a server if it crashes, up to 5 times in
    # 24 hours.
    DEFAULT:
        RESTART = Y
        MAXGEN  = 5

    # Start the Tuxedo System Event Broker.  This event broker must
    # be started before any servers providing the NameManager Service
    #
    TMSYSEVT
        SRVGRP  = SYS_GRP
        SRVID   = 1

    # TMFFNAME is a BEA Tuxedo provided server that runs the 
    # FactoryFinder and supporting NameManager services 
    # which maintain a mapping of application-supplied 
    # names to object references.

    # Start the NameManager Service (-N option).  This name manager
    # is being started as a Master (-M option).
    #
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 2
        CLOPT   = "-A -- -N -M"

    # Start a slave NameManager Service
    #
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 3
        CLOPT   = "-A -- -N"

    # Start the FactoryFinder (-F) service
    #
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 4
        CLOPT   = "-A -- -F"

    # Start the interface repository server
    #
    TMIFRSVR
        SRVGRP  = SYS_GRP
        SRVID   = 5

    # Start the university server
    #
    univs_server
        SRVGRP  = ORA_GRP
        SRVID   = 1
        RESTART = N

    # Start the listener for IIOP clients
    #
    # Specify the host name of your server machine as
    # well as the port.  A typical port number is 2500
    #
    ISL
        SRVGRP  = SYS_GRP
        SRVID   = 6
        CLOPT   = "-A -- -n //MY_MACHINE:MY_PORT_NUMBER -d /dev/tcp"

#---------------------------------------------------------------------

*SERVICES

#---------------------------------------------------------------------
