#--------------------------------------------------------------------------
#
#  Oracle JDeveloper Boot Configuration File
#  Copyright 2000-2008 Oracle Corporation.
#  All Rights Reserved.
#
#--------------------------------------------------------------------------
include ../../ide/bin/ide.boot

#
# The extension ID of the extension that has the <product-hook>
# with the IDE product's branding information. Users of JDeveloper
# should not change this property.
#
ide.product = oracle.jdeveloper

#
# Fallback list of extension IDs that represent the different
# product editions. Users of JDeveloper should not change this
# property.
#
ide.editions = oracle.studio, oracle.j2ee, oracle.jdeveloper

#
# The image file for the splash screen. This should generally not
# be changed by end users.
#
ide.splash.screen = splash.gif

#
# The ide.user.dir.var specifies the name of the environment variable
# that points to the root directory for user files.  The system and
# mywork directories will be created there.  If not defined, the IDE
# product will use its base directory as the user directory.
#
ide.user.dir.var = JDEV_USER_HOME,JDEV_USER_DIR

#
# The location of the patches directory, relative to the Oracle Home
# directory.
#
ide.patches.dir = jdev/lib/patches

#
# This will enable a "virtual" file system feature within JDeveloper.
# This can help performance for projects with a lot of files,
# particularly under source control.  For non-Windows platforms however,
# any file changes made outside of JDeveloper, or by deployment for
# example, may not be picked by the "virtual" file system feature.  Do
# not enable this for example, on a Linux OS if you use an external editor.
#
#VFS_ENABLE = true

#
# If set to true, prevent laucher from checking/setting the shell
# integration mechanism. Shell integration on Windows associates 
# files with JDeveloper.
#
# The shell integration feature is enabled by default
#
#no.shell.integration = true

#
# Text buffer deadlock detection setting (OFF by default.)  Uncomment
# out the following option if encountering deadlocks that you suspect
# buffer deadlocks that may be due to locks not being released properly.
#
#buffer.deadlock.detection = true

#
# If you need to connect to OC4J 10.1.2 from JDeveloper, uncomment the
# following option. Note, however, that enabling this option will prevent
# JDeveloper from connecting to OC4J 10.1.3.
#
#rmi.disablePropagation = true

#
# This option controls the parser delay (i.e., for Java error underlining)
# for "small" Java files (<20k).  The delay is in milliseconds.  Files 
# between the "small" (<20k) and "large" (>100k) range will scale the
# parser delay accordingly between the two delay numbers.
#
# The minimum value of this delay is 100 (ms), the default is 300 (ms).
#
ceditor.java.parse.small = 300

#
# This option controls the parser delay (i.e., for Java error underlining)
# for "large" Java files (>100k).  The delay is in milliseconds.
#
# The minimum value for this delay is 500 (ms), the default is 1500 (ms).
#
ceditor.java.parse.large = 1500

#
# This option is to pass additional vm arguments to the out-of-process
# java compiler used to build the project(s).  The arguments
# are used for both Ojc & Javac.
#
compiler.vmargs = -Xmx512m

#
# Additional (product specific) places to look for extension jars.
#
ide.extension.search.path=jdev/extensions:sqldeveloper/extensions

#
# Additional (product specific) places to look for roles.
#
ide.extension.role.search.path=jdev/roles

#
# Tell code insight to suppress @hidden elements 
#
insight.suppresshidden=true

#
# Disable Feedback Manager. The feedback manager is for internal use
# only.
#
feedbackmanager.disable=false

#
# Sets the maximum java.version that is supported by this product. The
# "Unsupported JDK" alert will appear on startup if the java version is
# greater than or equal to the version specified here.
#
# Changing this value does not make JDeveloper supported on later JDK
# versions - it just suppresses the message.
#
ide.java.maxversion=1.7

#
# Prevents the product from showing translations for languages other
# than english (en) and japanese (ja). The IDE core is translated into
# other languages, but other parts of JDeveloper are not. To avoid
# partial translations, we throttle all locales other than en and ja.
#
ide.throttleLocale=true

#
# Specifies the locales that we support translations for when 
# ide.throttleLocale is true. This is a comma separated list of 
# languages. The default value is en,ja.
#
# ide.supportedLocales=en,ja

#
# Specifies the maximum number of JAR file handles that will be kept
# open by the IDE class loader.  A lower number keeps JDeveloper from
# opening too many file handles, but can reduce performance.
#
ide.max.jar.handles=500
