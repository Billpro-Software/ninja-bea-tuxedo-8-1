Mission Control
===============
JRockit Mission Control includes tools to monitor, manage, profile, and 
find memory leaks in your Java application without introducing the 
performance overhead normally associated with tools of this type.

The JRockit Management Console
==============================
The JRockit Management Console is used to monitor and manage multiple JRockit
instances. It captures and presents live data about GC pauses, memory and CPU
usage, as well as information from any JMX MBean deployed in the JVM's 
internal MBean server. JVM management includes dynamic control over CPU 
affinity, garbage collection strategy, memory pool sizes and more.

The JRockit Runtime Analyzer
============================
The JRockit Runtime Analyzer (JRA) is an on-demand 'flight recorder' that 
produces detailed recordings about the JVM and the application it is running.
The recorded profile can later be analyzed off line, using the JRA 
application. Recorded data includes profiling of methods and locks, as well 
as garbage collection statistics, optimization decisions, and object 
statistics.

The Memory Leak Detector
========================
This is a tool for discovering, and finding the cause for, memory leaks. The
JRockit Memory Leak Detector's trend analyzer can discover very slow leaks,
it shows you detailed heap statistics including referring types and instances
to leaking objects, allocation sites, and provides quick drill down to the
cause of the leak. The Memory Leak Detector uses advanced graphical 
presentation techniques to make it easier to navigate and understand the 
sometimes complex information.

If you don’t have a Mission Control license for JRockit, please visit
http://dev2dev.bea.com/jrockit/tools.html for instructions on how to obtain 
a license.

Known Issues
============


Kind regards,
The JRPG Tools Team