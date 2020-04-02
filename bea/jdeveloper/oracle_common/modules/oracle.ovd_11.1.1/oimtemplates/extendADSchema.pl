#!/usr/local/bin/perl
# 
# $Header: ovd/dist/oracle.idm.ovd/ovd/oimtemplates/extendADSchema.pl /st_ovd_11.1.1.4.0/1 2010/10/18 12:31:20 jxwei Exp $
#
# extendADSchema.pl
# 
# Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved. 
#
#    NAME
#      extendADSchema.pl - <one-line expansion of the name>
#
#    DESCRIPTION
#      This tool is used to generate AD schema ldif file based on the specified template ldif file
#
#    NOTES
#      <other useful comments, qualifications, etc.>
#
#    MODIFIED   (MM/DD/YY)
#    jxwei       10/06/10 - Creation
# 

use Getopt::Long; # get the long options package

################################################################
################################################################
## usage function
################################################################
################################################################
## standard usage file 
sub usage
{
  print qq@
    Usage : $0 -h host -p port -D bind_dn -w bind_pwd [-AD ad_domain_name] [-o output_dir] 
               [-f list_of_files | -OAM enableOAM | -lov languages [-lovOID startOID]]

        where

          host           : AD host name
          port           : AD port number. Default 389
          bind_dn        : AD Administrator DN
          bind_pwd       : AD administrator password
          ad_domain_name : The AD domain name. For example: dc=acme,dc=com
          output_dir     : Directory to put the generated AD Schema ldif files. Default: ./ldifDir4AD
          list_of_files  : Comma seperated list of AD schema ldif templates
          enableOAM      : Enable OAM schema in AD? Allowed values: true/false. Default: false
          languages      : Comma seperated list of languages to be supported in addition to default ones.
          startOID       : Integer used for LOV schema OIDs. Its value should make sure that
                           OID of format 2.16.840.1.113894.200.<oid>.<1-300> are available 
                           to define new schema. Here 
                           startOID <= <oid> <= startOID+number_of_languages_in_LOV 
                           and <1-300> means any interger between 1 -- 300. Default 60

    Example:
      $0 -h myADHost -p 389 -D "administrator\@mydomain.com" -w myAdminPwd
         -AD dc=mydomain,dc=com -f s1.ldif,s2.ldif -o "/tmp/result" 
      \n@;
  exit();
}

################################################################
## main logic
################################################################

if ($ENV{'ORACLE_HOME'})
{
   $my_oh = $ENV{'ORACLE_HOME'};
} else
{
   print "Environment variable ORACLE_HOME is not set. Set $ORACLE_HOME and retry.\n";
   exit();
}

if (!$ENV{'JAVA_HOME'})
{
   $ENV{'JAVA_HOME'} = "$ENV{'ORACLE_HOME'}/jdk";
}

if (-d $ENV{'JAVA_HOME'})
{
   $my_javaHome = $ENV{'JAVA_HOME'};
} else
{
   print "$ENV{'JAVA_HOME'} does not exist. Set JAVA_HOME and retry.\n";
   exit();
}

# get the options
my ($ad_host, $ad_admin, $ad_pwd, $ad_domain);
my $ad_port = '389';
my ($oam_enable, $schema_templates, $out_dir, $lov, $lov_starting_oid); 

$result = GetOptions (
            'usage|help'  => sub { usage; },
            'host|h=s' => \$ad_host,      # AD host name
            'port|p:s' => \$ad_port,      # AD nonSSL LDAP port
            'DN|D=s'   => \$ad_admin,     # AD bind dn
            'password|w=s' => \$ad_pwd,   # AD bind pwd
            'AD:s'         => \$ad_domain,    # AD domain
            'OAM'          => sub { $oam_enable = 'true' },   # enable OAM
            'outDir|o:s'     => \$out_dir,  # Dirtory to put the generated AD schema ldif files  
            'schemaFiles|f:s' => \$schema_templates, # comma separated of schema ldif names
            'LOV:s'        => \$lov,      # comma separated list of languages subtypes
            'LOVOID:i'     => \$lov_starting_oid  # integer used for LOV schema OIDs 
           );

if (!$result || !$ad_host || !$ad_admin || !$ad_pwd)
{
  usage;
}

$jar = $my_oh."/ovd/jlib/ovdcommon.jar";
$my_class = "com.octetstring.vde.util.ADSchemaExtendUtil";

$options = "-h $ad_host -p $ad_port -D $ad_admin -w $ad_pwd ";
if ($ad_domain)
{
  $options = $options." -AD $ad_domain";
}

if ($out_dir)
{
  $options = $options." -outDir $out_dir";
}

if ($schema_templates)
{
   $options = $options." -schemaFiles $schema_templates";
}

if ( $oam_enable)
{
   $options = $options." -OAM $oam_enable";
}

if ($lov)
{
  $options = $options." -LOV $lov";
  if ($lov_starting_oid)
  {
     $options = $options."  -LOVOID $lov_starting_oid";
  }
}

$program = $ENV{'JAVA_HOME'}."/bin/java -classpath $jar $my_class $options";

print "\n commmand to run is: \n $program \n\n";

exec ($program);
 
print "\nCompleted extending AD schema.\n\n";

