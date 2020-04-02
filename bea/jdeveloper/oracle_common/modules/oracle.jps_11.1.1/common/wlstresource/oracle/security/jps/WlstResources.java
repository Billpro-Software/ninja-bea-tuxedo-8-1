/* $Header: jazn/jps/jrf/common/wlstresource/oracle/security/jps/WlstResources.java /st_entsec_11.1.1.4.0/5 2010/09/20 13:00:51 amitaga Exp $ */

/* Copyright (c) 2009, 2010, Oracle and/or its affiliates. 
All rights reserved. */

/*
   DESCRIPTION
    <short description of component this file declares/defines>

   PRIVATE CLASSES
    <list of private classes defined - with one-line descriptions>

   NOTES
    <other useful comments, qualifications, etc.>

   MODIFIED    (MM/DD/YY)
    amitaga     09/17/10 - XbranchMerge amitaga_bug-10114315 from main
    amitaga     09/14/10 - remove farm from messages
    amitaga     08/25/10 - XbranchMerge amitaga_rename_fks_commands from main
    amitaga     07/25/10 - update message to make it more generic
    yiwawang    07/22/10 - XbranchMerge yiwawang_bug-9905976 from main
    amitaga     07/15/10 - update message to make it more generic
    yiwawang    07/13/10 - XbranchMerge yiwawang_bug-9866178 from main
    yiwawang    07/02/10 - added MSG_WLST_INVALID_STORE_TYPE
    dramakri    06/03/10 - Add error messages
    yiwawang    05/09/10 - make re-association info generic to ldap and db
    lappanmu    12/16/09 - Adding messages for configureidstore
    aqin        03/11/10 - Add ps2 upgrade messages.
    vigarg      02/02/09 - Creation
 */

/**
 *  @version $Header: jazn/jps/jrf/common/wlstresource/oracle/security/jps/WlstResources.java st_oam_amitaga_rename_fks_commands/3 2010/08/03 18:26:16 amitaga Exp $
 *  @author  vigarg  
 *  @since   release specific (what release of product did this appear in)
 */
package oracle.security.jps;

import java.util.ListResourceBundle;

public class WlstResources extends ListResourceBundle implements WlstMessages {

    public Object[][] getContents() {
        return contents;
    }
    
    static final Object[][] contents =
    { 
        {MSG_WLST_COMMAND_FAILED, "Command FAILED, Reason: "},
        {MSG_WLST_UNKNOWN_REASON, "COMMAND FAILED due to an unknown reason, Check the stack trace for details"},
        {MSG_WLST_APP_NOT_FOUND, "Application not found: "},
        {MSG_WLST_CRED_NOT_FOUND, "Credential either does not exist or cannot be listed if it is of type \"generic\""},
        {MSG_WLST_REQUIRED_ARG_MISSING, "Following required argument(s) not passed: "},
        {MSG_WLST_GROUP_ARG_MISSING, "Only few arguments supplied in the following group: "},
        {MSG_WLST_CONFLICTING_ARG, "Following conflicting arguments supplied: "},
        {MSG_WLST_BOOLEAN_ARG, "Should have only one of the following values: true, false"},
        {MSG_WLST_POLICY_STORE_REASS_START, "Starting policy store reassociation."},
        {MSG_WLST_POLICY_STORE_REASS_END, "Policy store reassociation done."},
        {MSG_WLST_CRED_STORE_REASS_START, "Starting credential store reassociation"},
        {MSG_WLST_CRED_STORE_REASS_END, "Credential store reassociation done"},
        {MSG_WLST_KEY_STORE_REASS_START, "Starting Keystore reassociation"},
        {MSG_WLST_KEY_STORE_REASS_END, "Keystore reassociation done"},
        {MSG_WLST_CONFIG_CHANGE_REASS, "Jps Configuration has been changed. Please restart the application server."},
        {MSG_WLST_LDAP_SERVER_SETUP_DONE, "The store and ServiceConfigurator setup done."},
        {MSG_WLST_LDAP_SCHEMA_SEEDED, "Schema is seeded into the store"},
        {MSG_WLST_DATA_MIGRATED, "Data is migrated to the store"},
        {MSG_WLST_SERVICE_POST_MIGRATION_OK, "Data in the store after migration has been tested to be available"},
        {MSG_WLST_JPS_CONFIGURATION_DONE, "Update of in-memory jps configuration is done"},
        {MSG_WLST_FKS_CREATE_KS_DONE, "Keystore created"},
        {MSG_WLST_FKS_DELETE_KS_DONE, "Keystore deleted"},
        {MSG_WLST_FKS_CHANGE_KS_PWD_DONE, "Keystore password changed"},
        {MSG_WLST_FKS_CREATE_KP_DONE, "Key pair generated"},
        {MSG_WLST_FKS_CREATE_SK_DONE, "Secret key generated"},
        {MSG_WLST_FKS_CHANGE_KEY_PWD_DONE, "Keystore key password changed"},
        {MSG_WLST_FKS_CERT_REQ_EXPORTED, "Certificate request exported."},
        {MSG_WLST_FKS_CERT_REQ_FAILED, "Certificate request generation failed."},
        {MSG_WLST_FKS_CERT_EXPORTED, "Certificate exported."},
        {MSG_WLST_FKS_CERT_FAILED, "Certificate export failed."},
        {MSG_WLST_FKS_IMPORT_CERT_DONE, "Certificate imported."},
        {MSG_WLST_FKS_DELETE_ENTRY_DONE, "Keystore entry deleted."},
        {MSG_WLST_FKS_EXPORT_KS_DONE, "Keystore exported."},
        {MSG_WLST_FKS_IMPORT_KS_DONE, "Keystore imported."},
        {MSG_WLST_EMPTY_PROP_FILE, "Provide a valid properties file"},
        {MSG_WLST_ARG_NOVAL, "Following argument has no value supplied: "},
        {MSG_WLST_ARG_REPEATED, "Following argument is repeated more than once: "},
        {MSG_WLST_ARG_UNSUPPORTED, "Following argument(s) are not supported: "},
        {MSG_UPGRADE_BEGIN, "Starting upgrade of jps configuration and security stores."},
        {MSG_UPGRADE_END, "Upgrade of jps configuration and security stores is done."},
        {MSG_WLST_INVALID_STORE_TYPE, "The store type is invalid: "},
        {MSG_INVALID_SERVICE_NAME, "The service name is invalid"},
        {MSG_INVALID_COMMAND_NAME, "The command name is invalid"},
    };
}
