// Copyright (c) 1999 Quadralay Corporation.  All rights reserved.
//
// The information in this file is confidential and proprietary to
// Quadralay Corporation.  Unauthorized use or duplication is
// strictly prohibited.

hsmod[hsmod.length]="BEA Tuxedo Administration Console Help";

var wwhtop = foldersTree;

var wwh64361=new Folder("About This Online Help", "preface.htm#422572");
wwhtop.addChild(wwh64361);

var wwh64363=new Folder("How to Use the Online Help", "preface.htm#422575");
wwh64361.addChild(wwh64363);

wwh64363.addChild(new Item("Main Help Topics", "preface.htm#423440"));
wwh64363.addChild(new Item("Using Context-Sensitive Help", "preface.htm#423476"));
var wwh64369=new Folder("How to Print", "preface.htm#423621");
wwh64361.addChild(wwh64369);

wwh64369.addChild(new Item("How to Print the Current Topic", "preface.htm#423623"));
wwh64369.addChild(new Item("How to Print the Complete Book", "preface.htm#423628"));
wwh64361.addChild(new Item("Documentation Conventions", "preface.htm#423511"));
wwh64361.addChild(new Item("Where to Find Related Information", "preface.htm#422669"));
var wwh64379=new Folder("Contact Information", "preface.htm#423415");
wwh64361.addChild(wwh64379);

wwh64379.addChild(new Item("Documentation Support", "preface.htm#423398"));
wwh64379.addChild(new Item("Customer Support", "preface.htm#423411"));
var wwh64385=new Folder("BEA Tuxedo Administration Console Product Overview", "acoview.htm#424213");
wwhtop.addChild(wwh64385);

var wwh64387=new Folder("Administration Through the Web", "acoview.htm#427698");
wwh64385.addChild(wwh64387);

wwh64387.addChild(new Item("Where to Get More Information", "acoview.htm#428304"));
var wwh64391=new Folder("System Requirements", "acoview.htm#419979");
wwh64385.addChild(wwh64391);

wwh64391.addChild(new Item("Hardware Requirements", "acoview.htm#419981"));
wwh64391.addChild(new Item("Operating System Requirements", "acoview.htm#419986"));
wwh64391.addChild(new Item("Browser Requirements", "acoview.htm#420206"));
wwh64385.addChild(new Item("Installation", "acoview.htm#419975"));
var wwh64401=new Folder("Setting Up Your Environment for the BEA Tuxedo Administration Console", "acoview.htm#424348");
wwh64385.addChild(wwh64401);

wwh64401.addChild(new Item("Starting tuxwsvr", "acoview.htm#421104"));
wwh64401.addChild(new Item("Starting wlisten", "acoview.htm#421132"));
wwh64385.addChild(new Item("Configuring the Administration Console", "acoview.htm#433936"));
wwh64385.addChild(new Item("Starting the BEA Tuxedo Administration Console", "acoview.htm#423391"));
wwh64385.addChild(new Item("Exiting the BEA Tuxedo Administration Console", "acoview.htm#427152"));
var wwh64413=new Folder("BEA Tuxedo Administration Console Tutorial", "acoview.htm#423173");
wwh64385.addChild(wwh64413);

wwh64413.addChild(new Item("Step 1: Set Up Your Environment", "acoview.htm#420312"));
wwh64413.addChild(new Item("Step 2: Create a New Domain", "acoview.htm#423518"));
wwh64413.addChild(new Item("Step 3: Add GROUP1 to the simpapp Domain", "acoview.htm#426921"));
wwh64413.addChild(new Item("Step 4: Add Server simpserv to GROUP1", "acoview.htm#420418"));
wwh64413.addChild(new Item("Step 5: Activate the simpapp Domain", "acoview.htm#420439"));
wwh64413.addChild(new Item("Step 6: Run simpapp", "acoview.htm#420451"));
var wwh64427=new Folder("A Tour of the Main Window", "acmainw.htm#509573");
wwhtop.addChild(wwh64427);

var wwh64429=new Folder("Main Window", "acmainw.htm#481747");
wwh64427.addChild(wwh64429);

wwh64429.addChild(new Item("Why Are the Main Window Items Blank or Inactive?", "acmainw.htm#489212"));
wwh64429.addChild(new Item("Resizing the Tree View and Configuration Tool Panes", "acmainw.htm#456740"));
var wwh64435=new Folder("Parts of the Main Window", "acmainw.htm#453428");
wwh64427.addChild(wwh64435);

wwh64435.addChild(new Item("Menu Bar", "acmainw.htm#430770"));
wwh64435.addChild(new Item("Toolbar Buttons", "acmainw.htm#490069"));
var wwh64441=new Folder("The Tree View", "acmainw.htm#465436");
wwh64427.addChild(wwh64441);

var wwh64443=new Folder("Parts of the Tree View", "acmainw.htm#465457");
wwh64441.addChild(wwh64443);

wwh64443.addChild(new Item("Tree View Hierarchy", "acmainw.htm#477007"));
wwh64441.addChild(new Item("Expanding and Collapsing the Tree View", "acmainw.htm#504304"));
wwh64441.addChild(new Item("Searching for Objects in the Tree", "acmainw.htm#477737"));
var wwh64451=new Folder("The Tree View Quick Menu", "acmainw.htm#467218");
wwh64427.addChild(wwh64451);

wwh64451.addChild(new Item("Quick Menu Options", "acmainw.htm#493387"));
wwh64451.addChild(new Item(" About the New Option", "acmainw.htm#495732"));
wwh64451.addChild(new Item("Using the Folders Option to Display or Hide Tree Items", "acmainw.htm#481839"));
var wwh64459=new Folder("The Configuration Tool Pane", "acmainw.htm#479091");
wwh64427.addChild(wwh64459);

var wwh64461=new Folder("Accessing the Configuration Tool Information for a Tree Object", "acmainw.htm#440491");
wwh64459.addChild(wwh64461);

wwh64461.addChild(new Item("The Tab Pages", "acmainw.htm#440664"));
wwh64461.addChild(new Item("The Configuration Tool Buttons", "acmainw.htm#440676"));
var wwh64467=new Folder("Administration Tasks", "actasks.htm#649728");
wwhtop.addChild(wwh64467);

var wwh64469=new Folder("Setting Up Your BEA Tuxedo Administration Console", "actasks.htm#594213");
wwh64467.addChild(wwh64469);

wwh64469.addChild(new Item("Setting General Default Parameters", "actasks.htm#547443"));
wwh64469.addChild(new Item("Switching Edit and View Modes", "actasks.htm#599110"));
wwh64469.addChild(new Item("Controlling What the Tree Displays", "actasks.htm#600212"));
var wwh64477=new Folder("Creating Administrative Class Objects", "actasks.htm#544855");
wwh64467.addChild(wwh64477);

wwh64477.addChild(new Item("Adding New Administrative Objects", "actasks.htm#553002"));
wwh64467.addChild(new Item("Configuring Administrative Objects", "actasks.htm#625186"));
var wwh64483=new Folder("Connecting to and Disconnecting from a Domain", "actasks.htm#621784");
wwh64467.addChild(wwh64483);

wwh64483.addChild(new Item("How to Connect to a Domain", "actasks.htm#548485"));
wwh64483.addChild(new Item("How to Disconnect from a Domain", "actasks.htm#565752"));
var wwh64489=new Folder("Activating Your Domain and Domain Resources", "actasks.htm#642249");
wwh64467.addChild(wwh64489);

wwh64489.addChild(new Item("How to Activate a Domain", "actasks.htm#623421"));
wwh64489.addChild(new Item("How to Activate Class Objects", "actasks.htm#636382"));
wwh64489.addChild(new Item("Activating Only Administrative Servers", "actasks.htm#624896"));
wwh64489.addChild(new Item("How to Monitor the Progress of Activate", "actasks.htm#619890"));
var wwh64499=new Folder("Deactivating Your Domain", "actasks.htm#561178");
wwh64467.addChild(wwh64499);

wwh64499.addChild(new Item("How to Deactivate a Domain", "actasks.htm#637130"));
wwh64499.addChild(new Item("How to Deactivate Class Objects", "actasks.htm#638254"));
wwh64499.addChild(new Item("Deactivating Only Application Servers", "actasks.htm#631649"));
wwh64499.addChild(new Item("Forcing Deactivation", "actasks.htm#631813"));
wwh64499.addChild(new Item("How to Monitor the Progress of Deactivate", "actasks.htm#548688"));
var wwh64511=new Folder("Migrating Tree Objects", "actasks.htm#632475");
wwh64467.addChild(wwh64511);

wwh64511.addChild(new Item("Before Starting a Migrate Task", "actasks.htm#548703"));
wwh64511.addChild(new Item("Displaying the Migrate Objects Window", "actasks.htm#577558"));
wwh64511.addChild(new Item("Migrating a Server Group from One Machine to Another", "actasks.htm#646071"));
wwh64511.addChild(new Item("Migrating All Servers from One Machine to Another Machine", "actasks.htm#577197"));
wwh64511.addChild(new Item("Monitoring the Progress of Migrate", "actasks.htm#576770"));
var wwh64523=new Folder("Swapping the Master and Backup Machines", "actasks.htm#548736");
wwh64467.addChild(wwh64523);

wwh64523.addChild(new Item("Setting up Master and Backup Machines", "actasks.htm#644853"));
var wwh64527=new Folder("Cleaning a Machine", "actasks.htm#548743");
wwh64467.addChild(wwh64527);

wwh64527.addChild(new Item("How to Clean a Machine", "actasks.htm#548752"));
var wwh64531=new Folder("Advertising, Unadvertising, Suspending, and Resuming Services", "actasks.htm#548756");
wwh64467.addChild(wwh64531);

wwh64531.addChild(new Item("Advertise a Service", "actasks.htm#548780"));
wwh64531.addChild(new Item("Unadvertise a Service", "actasks.htm#548791"));
wwh64531.addChild(new Item("Suspend a Service", "actasks.htm#635846"));
wwh64531.addChild(new Item("Resume a Suspended Service", "actasks.htm#548798"));
var wwh64541=new Folder("Suspending, Resuming, and Killing Clients", "actasks.htm#548804");
wwh64467.addChild(wwh64541);

wwh64541.addChild(new Item("Suspend a Client", "actasks.htm#548823"));
wwh64541.addChild(new Item("Resume a Suspended Client", "actasks.htm#548835"));
wwh64541.addChild(new Item("Kill a Client", "actasks.htm#548838"));
var wwh64549=new Folder("Suspending, Resuming, and Killing Workstation Handlers", "actasks.htm#548848");
wwh64467.addChild(wwh64549);

wwh64549.addChild(new Item("Suspending Workstation Handlers", "actasks.htm#548867"));
wwh64549.addChild(new Item("Suspend a Workstation Handler", "actasks.htm#548876"));
wwh64549.addChild(new Item("Resume a Suspended Workstation Handler", "actasks.htm#548880"));
wwh64549.addChild(new Item("Kill a Workstation Handler", "actasks.htm#548883"));
var wwh64559=new Folder("Opening and Closing Application Queue Spaces", "actasks.htm#548892");
wwh64467.addChild(wwh64559);

wwh64559.addChild(new Item("Open an Application Queue Space", "actasks.htm#548895"));
wwh64559.addChild(new Item("Close an Application Queue Space", "actasks.htm#548898"));
var wwh64565=new Folder("Deleting Application Queue Messages", "actasks.htm#548901");
wwh64467.addChild(wwh64565);

wwh64565.addChild(new Item("Delete Application Queue Messages", "actasks.htm#548906"));
wwh64467.addChild(new Item("Aborting Transactions", "actasks.htm#548909"));
var wwh64571=new Folder("Creating Bridges Between Machines", "actasks.htm#548919");
wwh64467.addChild(wwh64571);

wwh64571.addChild(new Item("Create a Bridge", "actasks.htm#639818"));
wwh64571.addChild(new Item("Suspend a Bridge", "actasks.htm#639870"));
wwh64571.addChild(new Item("Resume a Suspended Bridge", "actasks.htm#639951"));
wwh64571.addChild(new Item("Deactivate a Bridge", "actasks.htm#640034"));
var wwh64581=new Folder("Security Administration", "actasks.htm#592522");
wwh64467.addChild(wwh64581);

wwh64581.addChild(new Item("Creating ACL Groups", "actasks.htm#594742"));
var wwh64585=new Folder("Managing Tuxedo CORBA Resources", "actasks.htm#657731");
wwh64467.addChild(wwh64585);

var wwh64587=new Folder("Suspending and Resuming Interfaces", "actasks.htm#657759");
wwh64585.addChild(wwh64587);

wwh64587.addChild(new Item("Suspending a CORBA Interface", "actasks.htm#657776"));
wwh64587.addChild(new Item("Resuming a Suspended CORBA Interface", "actasks.htm#657790"));
var wwh64593=new Folder("Suspending and Resuming Interface Queues", "actasks.htm#657800");
wwh64585.addChild(wwh64593);

wwh64593.addChild(new Item("Suspending a CORBA Interface Queue", "actasks.htm#657817"));
wwh64593.addChild(new Item("Resuming a Suspended CORBA Interface Queue", "actasks.htm#657831"));
wwh64585.addChild(new Item("Viewing Attributes for Factories", "actasks.htm#657841"));
var wwh64601=new Folder("Monitoring System Events", "actasks.htm#659234");
wwh64467.addChild(wwh64601);

var wwh64603=new Folder("Viewing System Statistics", "actasks.htm#558710");
wwh64601.addChild(wwh64603);

wwh64603.addChild(new Item("Displaying the Statistics Tool Window", "actasks.htm#578445"));
wwh64603.addChild(new Item("Changing the Refresh Rate", "actasks.htm#558757"));
wwh64603.addChild(new Item("Changing the Bar Graph View", "actasks.htm#581707"));
wwh64603.addChild(new Item("Displaying More Statistics", "actasks.htm#581700"));
wwh64601.addChild(new Item("Viewing System Events", "actasks.htm#579229"));
var wwh64615=new Folder("Viewing a ULOG File", "actasks.htm#634643");
wwh64601.addChild(wwh64615);

wwh64615.addChild(new Item("Displaying the Logfile Tool Window", "actasks.htm#580407"));
wwh64615.addChild(new Item("Selecting a Machine to View its ULOG File", "actasks.htm#588294"));
wwh64615.addChild(new Item("Taking a Snapshot of the ULOG File", "actasks.htm#588592"));
wwh64615.addChild(new Item("Setting the Format for the ULOG file", "actasks.htm#588588"));
wwh64615.addChild(new Item("Customizing the Logfile Tool Options", "actasks.htm#634846"));
var wwh64627=new Folder("Creating and Configuring Core Administrative Resources", "accore.htm#1556096");
wwhtop.addChild(wwh64627);

wwh64627.addChild(new Item("Opening an Existing Domain", "accore.htm#1978880"));
var wwh64631=new Folder("Creating a New Domain", "accore.htm#1851641");
wwh64627.addChild(wwh64631);

wwh64631.addChild(new Item("Hexadecimal Addresses", "accore.htm#1076477"));
var wwh64635=new Folder("Configuring Domain Resources (T_DOMAIN Class)", "accore.htm#1076074");
wwh64627.addChild(wwh64635);

wwh64635.addChild(new Item("General Tab", "accore.htm#895114"));
wwh64635.addChild(new Item("Security Tab", "accore.htm#895202"));
wwh64635.addChild(new Item("Limits 1 Tab", "accore.htm#895324"));
wwh64635.addChild(new Item("Limits 2 Tab", "accore.htm#895422"));
wwh64635.addChild(new Item("Timers Tab", "accore.htm#895517"));
wwh64635.addChild(new Item("System Parameters Tab", "accore.htm#895591"));
wwh64635.addChild(new Item("Statistics 1 Tab", "accore.htm#895671"));
wwh64635.addChild(new Item("Statistics 2 Tab", "accore.htm#895724"));
wwh64627.addChild(new Item("Creating Machines", "accore.htm#920534"));
var wwh64655=new Folder("Configuring Machines (T_MACHINE Class)", "accore.htm#463295");
wwh64627.addChild(wwh64655);

wwh64655.addChild(new Item("General Tab", "accore.htm#463299"));
wwh64655.addChild(new Item("Networking Tab", "accore.htm#473746"));
wwh64655.addChild(new Item("Security Tab", "accore.htm#1360279"));
wwh64655.addChild(new Item("Limits Tab", "accore.htm#463805"));
wwh64655.addChild(new Item("Transaction Log Tab", "accore.htm#522086"));
wwh64655.addChild(new Item("Statistics 1 Tab", "accore.htm#1360105"));
wwh64655.addChild(new Item("Statistics 2 Tab", "accore.htm#464141"));
wwh64655.addChild(new Item("Statistics 3 Tab", "accore.htm#464239"));
wwh64655.addChild(new Item("ACL Statistics Tab", "accore.htm#2045276"));
var wwh64675=new Folder("Configuring Transactions (T_TRANSACTION Class)", "accore.htm#2006141");
wwh64627.addChild(wwh64675);

wwh64675.addChild(new Item("General Tab", "accore.htm#1389786"));
wwh64675.addChild(new Item("Miscellaneous Tab", "accore.htm#490565"));
wwh64627.addChild(new Item("Creating Groups", "accore.htm#887038"));
var wwh64683=new Folder("Configuring Groups (T_GROUP Class)", "accore.htm#1396638");
wwh64627.addChild(wwh64683);

wwh64683.addChild(new Item("General Tab", "accore.htm#476789"));
wwh64683.addChild(new Item("TMS Tab", "accore.htm#476890"));
wwh64683.addChild(new Item("Args Tab", "accore.htm#476944"));
wwh64627.addChild(new Item("Creating Servers", "accore.htm#888017"));
var wwh64693=new Folder("Configuring Servers (T_SERVER Class)", "accore.htm#1952265");
wwh64627.addChild(wwh64693);

wwh64693.addChild(new Item("General Tab", "accore.htm#514889"));
wwh64693.addChild(new Item("Args Tab", "accore.htm#1445485"));
wwh64693.addChild(new Item("Commands Tab", "accore.htm#1446036"));
wwh64693.addChild(new Item("System Parameters Tab", "accore.htm#515198"));
wwh64693.addChild(new Item("Statistics 1 Tab", "accore.htm#522513"));
wwh64693.addChild(new Item("Statistics 2 Tab", "accore.htm#519270"));
wwh64693.addChild(new Item("Statistics 3 Tab", "accore.htm#2055197"));
wwh64627.addChild(new Item("Creating Routing Tables", "accore.htm#1493358"));
var wwh64711=new Folder("Configuring Routing Tables (T_ROUTING Class)", "accore.htm#892330");
wwh64627.addChild(wwh64711);

wwh64711.addChild(new Item("General Tab", "accore.htm#515516"));
wwh64627.addChild(new Item("Creating Service Defaults", "accore.htm#1503425"));
var wwh64717=new Folder("Configuring Service Defaults (T_SERVICE Class)", "accore.htm#1918266");
wwh64627.addChild(wwh64717);

wwh64717.addChild(new Item("General Tab", "accore.htm#515616"));
wwh64717.addChild(new Item("System Parameters Tab", "accore.htm#515689"));
wwh64627.addChild(new Item("Creating Services", "accore.htm#1572323"));
var wwh64725=new Folder("Configuring Services (T_SVCGRP Class)", "accore.htm#1572089");
wwh64627.addChild(wwh64725);

wwh64725.addChild(new Item("General Tab", "accore.htm#515812"));
wwh64725.addChild(new Item("System Parameters Tab", "accore.htm#2195385"));
wwh64627.addChild(new Item("Creating Devices", "accore.htm#894515"));
var wwh64733=new Folder("Configuring Devices (T_DEVICE Class)", "accore.htm#515971");
wwh64627.addChild(wwh64733);

wwh64733.addChild(new Item("General Tab", "accore.htm#515974"));
var wwh64737=new Folder("Configuring Clients (T_CLIENT Class)", "accore.htm#1919549");
wwh64627.addChild(wwh64737);

wwh64737.addChild(new Item("General Tab", "accore.htm#516117"));
wwh64737.addChild(new Item("System Parameters Tab", "accore.htm#522986"));
wwh64737.addChild(new Item("Statistics Tab", "accore.htm#1531604"));
var wwh64745=new Folder("Configuring Bridges (T_BRIDGE Class)", "accore.htm#520218");
wwh64627.addChild(wwh64745);

wwh64745.addChild(new Item("General Tab", "accore.htm#516994"));
wwh64745.addChild(new Item("Timers Tab", "accore.htm#517014"));
wwh64745.addChild(new Item("Statistics Tab", "accore.htm#517042"));
var wwh64753=new Folder("Creating and Configuring Application Queues", "acappq.htm#981564");
wwhtop.addChild(wwh64753);

wwh64753.addChild(new Item("Application Queues", "acappq.htm#882082"));
wwh64753.addChild(new Item("Creating Application Queues", "acappq.htm#949317"));
var wwh64759=new Folder("Configuring Application Queues (T_APPQ Class)", "acappq.htm#949206");
wwh64753.addChild(wwh64759);

wwh64759.addChild(new Item("General Tab", "acappq.htm#946673"));
wwh64759.addChild(new Item("Queue Message Tab", "acappq.htm#947733"));
wwh64759.addChild(new Item("Retries Tab", "acappq.htm#947786"));
wwh64759.addChild(new Item("Command Tab", "acappq.htm#947903"));
wwh64753.addChild(new Item("Application Queue Spaces", "acappq.htm#882579"));
wwh64753.addChild(new Item("Creating Application Queue Spaces", "acappq.htm#946848"));
var wwh64773=new Folder("Configuring Application Queue Spaces (T_APPQSPACE Class)", "acappq.htm#954064");
wwh64753.addChild(wwh64773);

wwh64773.addChild(new Item("General Tab", "acappq.htm#950225"));
wwh64773.addChild(new Item("Disk/Pages Tab", "acappq.htm#876483"));
wwh64773.addChild(new Item("Queue Tab", "acappq.htm#876526"));
wwh64773.addChild(new Item("Transaction Tab", "acappq.htm#876549"));
wwh64773.addChild(new Item("Process Tab", "acappq.htm#876572"));
wwh64773.addChild(new Item("Message Tab", "acappq.htm#876595"));
wwh64753.addChild(new Item("Application Queue Messages", "acappq.htm#883074"));
var wwh64789=new Folder("Configuring Application Queue Messages (T_APPQMSG Class)", "acappq.htm#876623");
wwh64753.addChild(wwh64789);

wwh64789.addChild(new Item("General Tab", "acappq.htm#876625"));
wwh64789.addChild(new Item("Queue Message Tab", "acappq.htm#876659"));
wwh64789.addChild(new Item("Statistics Tab", "acappq.htm#876716"));
wwh64753.addChild(new Item("Application Queue Transactions", "acappq.htm#956358"));
var wwh64799=new Folder("Configuring Application Queue Transactions (T_APPQTRANS Class)", "acappq.htm#876743");
wwh64753.addChild(wwh64799);

wwh64799.addChild(new Item("General Tab", "acappq.htm#953980"));
var wwh64803=new Folder("Creating and Configuring Workstation Listeners and Handlers", "acwsl.htm#522992");
wwhtop.addChild(wwh64803);

wwh64803.addChild(new Item("Workstation Listeners (WSLs)", "acwsl.htm#878229"));
wwh64803.addChild(new Item("Creating Workstation Listeners", "acwsl.htm#875183"));
var wwh64809=new Folder("Configuring Workstation Listeners (T_WSL Class)", "acwsl.htm#907197");
wwh64803.addChild(wwh64809);

wwh64809.addChild(new Item("General Tab", "acwsl.htm#872942"));
wwh64809.addChild(new Item("Options Tab", "acwsl.htm#873039"));
wwh64809.addChild(new Item("System Parameters Tab", "acwsl.htm#873107"));
wwh64809.addChild(new Item("Statistics Tab", "acwsl.htm#873204"));
wwh64803.addChild(new Item("Workstation Handlers (WSHs)", "acwsl.htm#880602"));
var wwh64821=new Folder("Configuring Workstation Handlers (T_WSH Class)", "acwsl.htm#876517");
wwh64803.addChild(wwh64821);

wwh64821.addChild(new Item("General Tab", "acwsl.htm#876519"));
wwh64821.addChild(new Item("Handler Info Tab", "acwsl.htm#876564"));
wwh64821.addChild(new Item("Statistics Tab", "acwsl.htm#876609"));
var wwh64829=new Folder("Creating and Configuring Access Control Lists", "acacls.htm#874809");
wwhtop.addChild(wwh64829);

wwh64829.addChild(new Item("ACL Groups", "acacls.htm#870471"));
wwh64829.addChild(new Item("Creating ACL Groups", "acacls.htm#877167"));
var wwh64835=new Folder("Configuring ACL Groups (T_ACLGROUP Class)", "acacls.htm#879772");
wwh64829.addChild(wwh64835);

wwh64835.addChild(new Item("General Tab", "acacls.htm#878824"));
wwh64829.addChild(new Item("ACL Principals", "acacls.htm#873645"));
wwh64829.addChild(new Item("Creating ACL Principals", "acacls.htm#894785"));
var wwh64843=new Folder("Configuring ACL Principals (T_ACLPRINCIPAL Class)", "acacls.htm#518216");
wwh64829.addChild(wwh64843);

wwh64843.addChild(new Item("General Tab", "acacls.htm#874290"));
wwh64829.addChild(new Item("ACLs", "acacls.htm#874334"));
wwh64829.addChild(new Item("Creating ACLs", "acacls.htm#872302"));
var wwh64851=new Folder("Configuring ACLs (T_ACLPERM Class)", "acacls.htm#889917");
wwh64829.addChild(wwh64851);

wwh64851.addChild(new Item("General Tab", "acacls.htm#891754"));
var wwh64855=new Folder("Creating and Configuring Tuxedo CORBA Resources", "accorba.htm#1701431");
wwhtop.addChild(wwh64855);

wwh64855.addChild(new Item("CORBA Interfaces (T_INTERFACE)", "accorba.htm#1704933"));
wwh64855.addChild(new Item("Creating a New CORBA Interface", "accorba.htm#894943"));
var wwh64861=new Folder("Configuring a CORBA Interface (T_INTERFACE)", "accorba.htm#1076074");
wwh64855.addChild(wwh64861);

wwh64861.addChild(new Item("General Tab", "accorba.htm#1623635"));
wwh64861.addChild(new Item("System Parameters Tab", "accorba.htm#895114"));
wwh64861.addChild(new Item("Policies Tab", "accorba.htm#1624457"));
wwh64861.addChild(new Item("Statistics Tab", "accorba.htm#1684666"));
wwh64855.addChild(new Item("CORBA Interface Queues (T_IFQUEUE)", "accorba.htm#1661604"));
var wwh64873=new Folder("Viewing a CORBA Interface Queue Configuration (IF_QUEUE)", "accorba.htm#1685120");
wwh64855.addChild(wwh64873);

wwh64873.addChild(new Item("General Tab", "accorba.htm#1646659"));
wwh64873.addChild(new Item("Policies Tab", "accorba.htm#1655474"));
wwh64873.addChild(new Item("System Parameters Tab", "accorba.htm#1632083"));
wwh64873.addChild(new Item("Statistics Tab", "accorba.htm#1655734"));
wwh64855.addChild(new Item("CORBA Factories (T_FACTORY)", "accorba.htm#1651093"));
var wwh64885=new Folder("Viewing a CORBA Factory Configuration", "accorba.htm#1651242");
wwh64855.addChild(wwh64885);

wwh64885.addChild(new Item("General Tab", "accorba.htm#1634054"));
var wwh64889=new Folder("Architecture and Implementation", "acapximp.htm#10346");
wwhtop.addChild(wwh64889);

wwh64889.addChild(new Item("Architecture Overview", "acapximp.htm#417926"));
wwh64889.addChild(new Item("Running the Web Server", "acapximp.htm#419229"));
wwh64889.addChild(new Item("Configuring the BEA Tuxedo Administration Console", "acapximp.htm#418017"));
wwh64889.addChild(new Item("Running wlisten", "acapximp.htm#418051"));
wwh64889.addChild(new Item("Starting the BEA Tuxedo Administration Console (for Nonexpert Users)", "acapximp.htm#420208"));
wwh64889.addChild(new Item("Starting the BEA Tuxedo Administration Console (for Developers)", "acapximp.htm#418072"));
wwh64889.addChild(new Item("Using Appletviewer", "acapximp.htm#418504"));

