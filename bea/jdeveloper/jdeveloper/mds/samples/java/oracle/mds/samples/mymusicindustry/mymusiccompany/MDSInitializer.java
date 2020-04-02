/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.mymusicindustry.mymusiccompany;

import java.io.File;

import java.net.MalformedURLException;
import java.net.URL;

import oracle.mds.samples.mymusicindustry.mymusiccompany.cust.SiteCC;
import oracle.mds.samples.mymusicindustry.mymusiccompany.cust.UserCC;
import oracle.mds.config.CustClassListMapping;
import oracle.mds.config.CustConfig;
import oracle.mds.config.MDSConfig;
import oracle.mds.config.MDSConfigurationException;
import oracle.mds.config.PConfig;
import oracle.mds.config.TypeConfig;
import oracle.mds.core.MDSInstance;
import oracle.mds.cust.CustClassList;
import oracle.mds.cust.CustomizationClass;
import oracle.mds.exception.MDSException;
import oracle.mds.persistence.MetadataStore;
import oracle.mds.persistence.stores.file.FileMetadataStore;

public class MDSInitializer
{

    /**
    ** Constructor.
    */
    public MDSInitializer(String metadataPath)
    {
        mMetadataPath = metadataPath;
    }

    /**
    ** Creates and configures an MDSInstance object (if one already does not
    ** exist).
    **
    **
    ** @throws oracle.mds.config.MDSConfigurationException
    ** @return  MDSInstance to used by the application
    */
    public MDSInstance getMDSInstance()

    {
      if ( mInstance != null )
      {
        return mInstance;
      }

      try
      {
        MDSConfig config = getMDSConfig();

        mInstance = MDSInstance.
                   getOrCreateInstance("myInstance", config);
      }
      catch ( MDSConfigurationException ce )
      {
        System.err.println(ce.getLocalizedMessage());
      }
      return mInstance;
    }


    /**
    ** Returns an instance of MDSConfig. If it is not already created,
    ** creates one based on a pre-defined provider.xsd and two
    ** CustomizationClass types.
    **
    ** @throws MDSConfigurationException If the metadata path is invalid
    ** @return   MDSConfig instance
    */
    protected MDSConfig getMDSConfig()
                  throws MDSConfigurationException
    {
      if ( mConfig != null )
      {
        return mConfig;
      }

      ClassLoader cl   = Thread.currentThread().getContextClassLoader();
      CustomizationClass[] musicCustClassList =
                                      new CustomizationClass[]{
                                      new SiteCC(),
                                      new UserCC()};
      CustClassList musicCCList =
                                 new CustClassList(musicCustClassList);
      CustClassListMapping musicMapping =
                   new CustClassListMapping("/musicindustry/mymusiccompany/",
                                             null,
                                             null,
                                             musicCCList);
      CustClassListMapping portalMapping =
                   new CustClassListMapping("/oracle/portal/",
                                             null,
                                             null,
                                             musicCCList);
      CustClassListMapping[] mappings = new CustClassListMapping[]
                                                           {musicMapping,
                                                            portalMapping};

      CustConfig custConfig = new CustConfig(mappings);


      URL           provider = getProviderSchemaURL();
      URL[]         urls     = new URL[]{provider};
      TypeConfig    tConfig  = new TypeConfig(urls);

      MetadataStore store = null;
      try
      {
        // Uncomment and change the following to use a database repository
/*
        String myHost   = "my-machine";
        String myPort   = "1521";
        String mySID    = "ora1012";
        String myUser   = "fred";
        String myPasswd = "topSecret";
        String myJDBCURL = "jdbc:oracle:thin:@" + myHost + ":"
                                 + myPort + ":" + mySID;
        store = new DBMetadataStore(myUser, myPasswd, myJDBCURL);
*/
        // Default to using the file system
        if ( store == null )
        {
            store = new FileMetadataStore(mMetadataPath);
        }
      }
      catch ( MDSException e )
      {
        throw new MDSConfigurationException(e);
      }
      PConfig pConfig = new PConfig(store);
      mConfig = new MDSConfig(tConfig, pConfig, custConfig);
      return mConfig;
    }
    
    /**
     * This method creates an URL object for the provider.xsd file that will be
     * used for building the type configuration. 
     * @return URL object for the provider.xsd
     */
    private URL getProviderSchemaURL()
    {
    
            final String schemaName    = "provider.xsd";
            
            URL          schemaURL      = null;
            ClassLoader  classLoader    = 
                                Thread.currentThread().getContextClassLoader();
            
            schemaURL = classLoader.getResource(schemaName);
            
            /*
             * This check acts as a fallback if the previous method of loading 
             * the schema file from the classpath fails. If this method fails
             * then the schema file is loaded from the file system.
             */
            if ( schemaURL == null )
            {
                String path = mMetadataPath;
                int index = path.lastIndexOf(File.separator);
                if ( index != -1 )
                {
                    path = path.substring(0, index);
                }
                
                path = path + File.separator + "xsd" 
                    + File.separator + schemaName;
               
                File file = new File(path);
                try 
                {
                    schemaURL = file.toURL();
                } 
                catch ( MalformedURLException e ) 
                {
                    //Do Nothing
                }
            }
            
            return schemaURL;
        }

    private MDSConfig   mConfig;
    private MDSInstance mInstance;
    private String      mMetadataPath;
}
