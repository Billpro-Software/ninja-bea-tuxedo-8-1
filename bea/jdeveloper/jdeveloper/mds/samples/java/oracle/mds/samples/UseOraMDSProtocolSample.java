/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples;

/**
** <b>This class represents a sample that provides usage examples of</b>
** MDS "oramds:" protocol. Currently, the following examples are shown:
** <UL>
** <LI> Use oramds: protocol to get InputStream of an MDS object. </LI>
** </UL>
** 
** <p>
** To use oramds: protocol, for a stand-alone application, MDS user 
** should register <code>oracle.classloader.util.URLHandlerFactory</code> once 
** using URL.setURLStreamHandlerFactory(URLStreamHandlerFactory fac) method. 
** "-Djava.protocol.handler.pkgs=oracle.mds.net.protocol" has to be added as
** command line option when starting Java virtual machine.  If the application 
** is running under oc4j container, oc4j container will take care of these 
** setup.
** 
*/

/*
** <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** dklein   05/01/07 - Removed initial slash before sStoreLocation so store is
**                     created where the program is run and not in the root dir.
** erwang   08/18/06 - Created.
** --------------------------------------------------------------------------->
*/

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

import java.io.OutputStream;

import java.net.MalformedURLException;
import java.net.URL;

/*
 * Follwing import statement has to be uncommented before using this sample.
 */
//import oracle.classloader.util.URLHandlerFactory;

import oracle.mds.config.MDSConfig;
import oracle.mds.config.MDSConfigurationException;
import oracle.mds.config.PConfig;
import oracle.mds.core.IsolationLevel;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.MOReference;
import oracle.mds.core.SessionOptions;
import oracle.mds.exception.MDSException;
import oracle.mds.net.MDSURLHelper;
import oracle.mds.persistence.MetadataStore;
import oracle.mds.persistence.stores.file.FileMetadataStore;

public class UseOraMDSProtocolSample
{
  /**
   * Default constructor.
   */
  public UseOraMDSProtocolSample()
  {
      
  }



  /**
   * the main method.
   * 
   * @param args
   */
  public static void main(String[] args)
  {
      /*
       * One time registration of Oracle URLHandlerFactory.
       *
       * To compile this sample, the following URLHandlerFactory registration 
       * code has to be uncommented.
       *
       * URL.setURLStreamHandlerFactory(new URLHandlerFactory());
       */
      
      UseOraMDSProtocolSample sample = 
                                  new UseOraMDSProtocolSample();
      if ( !sample.initData() )
      {
          System.out.println("Initialization failed.");
          return;          
      }
      
      sample.useOraMDSProtocol();    
      
      // Clean up.
      sample.cleanUp();
  }

  /**
   * delete the directory that was created by the sample program.
   */
  private void cleanUp()
  {
      try
      {
          // Only delete the file not folder to avoid mistakenly delete
          // some others' file.
          File file = new File(sStoreLocation + "/" + sFileName);
          file.delete();
      }
      catch ( Exception e )
      {
          System.out.println("Can't delete " + sStoreLocation);
      }
  }
  
  /**
   * Initialize for the sample.
   */
  private boolean initData()
  {
      try
      {
          File file = new File(sStoreLocation);
          if ( !file.exists() )
          {
              if ( !file.mkdirs())
              {
                  return false;
              }
              System.out.println("Created sample store at: " + 
                                            file.getAbsolutePath());
          }
          
          OutputStream os = new BufferedOutputStream(
                                      new FileOutputStream(sStoreLocation + 
                                              File.separator + sFileName));
          byte[] docContent = sXMLDoc.getBytes("UTF-8");
          os.write(docContent);
          os.close();
          
      }
      catch ( Exception e )
      {
          System.out.println("Exception");
          return false;
      }
      return true;
  }
  
  /**
  ** Sample code to use oramds: protocol.
  */
  private void useOraMDSProtocol()
  {
      try
      {
          MetadataStore fileStore = new FileMetadataStore(sStoreLocation, 
                                                                   false);
          PConfig pConfig = new PConfig(fileStore);

          // Create the MDS Config Object.
          MDSConfig mdsConfig = new MDSConfig(null, pConfig, null);

          // Create the MDS Instance with the MDS Context and
          MDSInstance mds  = MDSInstance.getOrCreateInstance("myinstance",
                                                              mdsConfig);
          MDSSession sess  = mds.createSession(
                         new SessionOptions(IsolationLevel.READ_COMMITTED,
                                            null,   // locale
                                            null),  // customization class list
                                null); // UserStateHandler
                                
          MDSURLHelper.setMDSSession(sess);
          
          MOReference moRef = MOReference.create(sFileName);
          
          // Demostrate using MDSURLHelper function to get url string.
          String sUrl = MDSURLHelper.getURLString(moRef);
          
          URL url = new URL(sUrl);
          
          InputStream is = url.openStream();
          byte[] buffer = new byte[sXMLDoc.length() * 2];

          int size = is.read(buffer);            
          is.close();            
          
          String sContent = new String(buffer, 0, size, "UTF-8");
          
          System.out.println("Content from the document: ");
          System.out.println(sContent);
      }
      catch ( MalformedURLException e )
      {
          System.out.println("MalformedURLException: " + e.getMessage());
      }
      catch ( MDSConfigurationException e )
      {
          System.out.println("MDSConfigurationException: " + e.getMessage());
      }
      catch ( MDSException e )
      {
          System.out.println("MDSException: " + e.getMessage());
      }      
      catch ( Exception e )
      {
          System.out.println("Exception: " + e.getMessage());
      }
      finally
      {            
          MDSURLHelper.removeMDSSession();           
      }
  }

  private static String sStoreLocation = "MDSSampleStore";
  private static String sFileName      = "/mydocument.xml";
  private static String sXMLDoc        =
  "<?xml version = '1.0' encoding = 'UTF-8'?> \n"   +
  "<bookstore xml:lang=\"en-US\" xmlns=\"http://xmlns.oracle.com/books\"> \n" +
  "    <book category=\"references\" pages=\"500\"> \n" +
  "      <author>cornell</author> \n" +
  "      <title> Java </title> \n" +
  "      <preference> Paperback  preference test <type> \n" +
  "        Technical</type></preference> \n" +
  "   </book>  \n" +
  "   <book category=\"fiction\"> \n" +
  "      <author>Evelyn</author> \n" +
  "      <title>Sword of Honour</title> \n" +
  "   </book> \n" +
  "</bookstore> \n";
  
}
