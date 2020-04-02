#---------------------------------------------------------------------
#	(c) 2003 BEA Systems, Inc. All Rights Reserved.
#
# ubb_p.mk
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
    IPCKEY      55432
    DOMAINID    university
    MASTER      SITE1
    MODEL       SHM
    LDBAL       N
    SECURITY    APP_PW	
    MAXSERVICES 200

#---------------------------------------------------------------------

*MACHINES

#   Specify the name of your server machine
#
    MY_SERVER_MACHINE
        LMID = SITE1

#   Pathname of your copy of this sample application.
#   Must match "APPDIR" in "setenv.sh"
#
    APPDIR = "/usr/users/my_samples_dir/production"

#   Pathname of the tuxconfig file.
#   Must match "TUXCONFIG" in "setenv.sh"
# 
    TUXCONFIG="/usr/users/my_samples_dir/production/tuxconfig"

#   Pathname of the transaction log.
#   Must match "TLOGDEVICE" in "setenv.sh"
#
    TLOGDEVICE="/usr/users/my_samples_dir/production/TLOG"
#
    TLOGNAME=TLOG

#   Pathname of the Tuxedo installation.
#   Must match "TUXDIR" in "setenv.sh"
#
    TUXDIR="/usr/local/tuxdir"

    MAXACCESSERS=1100
    MAXWSCLIENTS=1000

#---------------------------------------------------------------------

*GROUPS

    SYS_GRP
        LMID      = SITE1
        GRPNO     = 1

    APP_GRP1
        LMID      = SITE1
        GRPNO     = 2
        TMSNAME   = TMS

    APP_GRP2
        LMID      = SITE1
        GRPNO     = 3
        TMSNAME   = TMS

    ORA_GRP1
        LMID      = SITE1
        GRPNO     = 4
#       
#       You will need to specify SqlNet=<Remote Instance ID> for access
#       to a remote database.
#       OPENINFO  = "ORACLE_XA:Oracle_XA+SqlNet=ORCL+Acc=P/scott/tiger+SesTm=100+LogDir=.+MaxCur=5"
        OPENINFO  = "ORACLE_XA:Oracle_XA+Acc=P/scott/tiger+SesTm=100+LogDir=.+MaxCur=5"
        CLOSEINFO = ""
        TMSNAME   = "TMS_ORA"

    ORA_GRP2
        LMID      = SITE1
        GRPNO     = 5
#       
#       You will need to specify SqlNet=<Remote Instance ID> for access
#       to a remote database.
#       OPENINFO  = "ORACLE_XA:Oracle_XA+SqlNet=ORCL+Acc=P/scott/tiger+SesTm=100+LogDir=.+MaxCur=5"
        OPENINFO  = "ORACLE_XA:Oracle_XA+Acc=P/scott/tiger+SesTm=100+LogDir=.+MaxCur=5"
        CLOSEINFO = ""
        TMSNAME   = "TMS_ORA"

#---------------------------------------------------------------------

*SERVERS

    # By default, restart a server if it crashes, up to 5 times in
    # 24 hours. Also, activate 2 instances of each server
    # and allow the administrator to activate up to 5 instances of
    # each server
    DEFAULT:
        RESTART = Y
        MAXGEN  = 5
        MIN     = 2
        MAX     = 5

    # Start the Tuxedo System Event Broker.  This event broker must
    # be started before any servers providing the NameManager Service
    #
    TMSYSEVT
        SRVGRP  = SYS_GRP
        SRVID   = 10
        MIN     = 1
        MAX     = 1

    # TMFFNAME is a Tuxedo provided server that runs the 
    # FactoryFinder and supporting NameManager services 
    # which maintain a mapping of application-supplied 
    # names to object references.

    # Start the NameManager Service (-N option).  This name manager
    # is being started as a Master (-M option).
    #
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 20
        CLOPT   = "-A -- -N -M"
        MIN     = 1
        MAX     = 1

    # Start a slave NameManager Service
    #
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 30
        CLOPT   = "-A -- -N"

    # Start the FactoryFinder (-F) service
    #
    TMFFNAME
        SRVGRP  = SYS_GRP
        SRVID   = 40
        CLOPT   = "-A -- -F"

    # Start the interface repository server
    #
    TMIFRSVR
        SRVGRP  = SYS_GRP
        SRVID   = 50

    # Start the teller tuxedo servers
    #
    tellp_server
        SRVGRP  = ORA_GRP1
        SRVID   = 10
        RESTART = N
    tellp_server
        SRVGRP  = ORA_GRP2
        SRVID   = 10
        RESTART = N

    # Start the billing tuxedo wrapper servers
    #
    billp_server
        SRVGRP  = APP_GRP1
        SRVID   = 10
        RESTART = N
    billp_server
        SRVGRP  = APP_GRP2
        SRVID   = 10
        RESTART = N

    # Start the university servers
    #
    univp_server
        SRVGRP  = ORA_GRP1
        SRVID   = 20
        RESTART = N
    univp_server
        SRVGRP  = ORA_GRP2
        SRVID   = 20
        RESTART = N

    # Start the listener for IIOP clients
    #
    # Specify the host name of your server machine as
    # well as the port.  A typical port number is 2500
    #
    ISL
        SRVGRP  = SYS_GRP
        SRVID   = 60
        CLOPT   = "-A -- -n //MY_MACHINE:MY_PORT_NUMBER -d /dev/tcp"
        MIN     = 1
        MAX     = 1

#---------------------------------------------------------------------

*SERVICES

    # Publish Tuxedo Teller application services
    #
    DEBIT
        AUTOTRAN=Y
    CREDIT
        AUTOTRAN=Y
    CURRBALANCE
        AUTOTRAN=Y

#---------------------------------------------------------------------

*INTERFACES

#---------------------------------------------------------------------

    "IDL:beasys.com/UniversityP/Registrar:1.0"
        FACTORYROUTING = STU_ID

    "IDL:beasys.com/BillingP/Teller:1.0"
        FACTORYROUTING = ACT_NUM

#---------------------------------------------------------------------

*ROUTING

    STU_ID
        FIELD     = "student_id"
        TYPE      = FACTORY
        FIELDTYPE = LONG
        RANGES    = "100001-100005:ORA_GRP1,100006-100010:ORA_GRP2"

    ACT_NUM
        FIELD     = "account_number"
        TYPE      = FACTORY
        FIELDTYPE = LONG
        RANGES    = "200010-200014:APP_GRP1,200015-200019:APP_GRP2"

#---------------------------------------------------------------------
