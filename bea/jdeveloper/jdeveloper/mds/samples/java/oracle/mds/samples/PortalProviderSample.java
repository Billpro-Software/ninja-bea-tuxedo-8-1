/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples;

import java.io.File;

import java.net.MalformedURLException;
import java.net.URL;

import java.util.Iterator;

import oracle.mds.config.MDSConfig;
import oracle.mds.config.MDSConfigurationException;
import oracle.mds.config.PConfig;
import oracle.mds.config.TypeConfig;
import oracle.mds.core.ExtendedMetadata;
import oracle.mds.core.IsolationLevel;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.MetadataNotFoundException;
import oracle.mds.core.MetadataObject;
import oracle.mds.core.RDFTriple;
import oracle.mds.core.SessionOptions;
import oracle.mds.exception.MDSException;
import oracle.mds.melement.MElement;
import oracle.mds.melement.MNodeList;
import oracle.mds.naming.ReferenceException;
import oracle.mds.persistence.MetadataStore;
import oracle.mds.persistence.stores.file.FileMetadataStore;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.commons.cli.PosixParser;

/**
** <b>This class represents a sample that provides usage examples of
** using Runtime MDS. Currently, the following examples are shown:
** <UL>
** <LI> Initializing the MDS Instance for file-based usage. </LI>
** <LI> Setting up the MDS Session </LI>
** <LI> Retrieving and printing out a basic metadata document </LI>
** <LI> Retrieving and printing out extended metadata or MDX </LI>
** </UL>
*/
/*
** <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** gkonduri  07/05/06 - Added DBARGS as a valid parameter. 
** cbarrow   12/20/05 - Stop using deprecated MDSInstance.createSession. 
** snoton    06/22/05 - Added extended metadata code
** cbarrow   05/09/05 - Move to revised MDS Core API
** gnagaraj  03/22/05 - PConfig API changes to associate it single MetadataStore
** hhsu      03/04/05 - Rewrite on top of new MDS Core API and move to
**                      oracle.mds.samples package.
** snoton    11/30/04 - Obsolete MetadataManager(Base) in favour of
**                      MDSInstance.
** snoton    11/22/04 - MDSContextImpl now renamed to MDSContext.
** ntriggs   11/01/04 -
** ntriggs   11/04/04 - Refactor AttributeKey
** cbarrow   06/11/04 - Change location of xml, xsd files from xml_files to xml,
**                      etc, avoid calls to deprecated methods like getGroupings
** kaalvare  04/05/04 - Added customization and implementation class examples
** kaalvare  03/      - Creation
** --------------------------------------------------------------------------->
*/
public class PortalProviderSample
{
  /**
  ** Constructor.
  */
  public PortalProviderSample()
  {
  }

  /**
  ** Initialize MDS with a FileMetadataStore and given XSD for type information.
  */
  public void initMDS(String mdsXMLPath, String providerXSD)
  {
      try
      {
      // Register the XSD.
      File f =
          new File(providerXSD);
      URL[] providerXSDs = new URL[1];
      providerXSDs[0] = f.toURL();
      TypeConfig tConfig = new TypeConfig(providerXSDs);

      // Create the filesystem metadata store.
      MetadataStore fileStore = new FileMetadataStore(mdsXMLPath,
                                                      false);  // Not writable
      PConfig pConfig = new PConfig(fileStore);

      // Create the MDS Config Object.
      MDSConfig mdsConfig = new MDSConfig(tConfig, pConfig, null);

      // Create the MDS Instance with the MDS Context and
      mMDSInstance =
          MDSInstance.getOrCreateInstance("myinstance",
                          mdsConfig);
      }
      catch ( MalformedURLException e )
      {
      System.out.println("MalformedURLException");
      }
      catch ( MDSConfigurationException e )
      {
      System.out.println("MDSConfigurationException");
      }
      catch ( MDSException e )
      {
      System.out.println("MDSException");
      }
  }

  /**
  ** Gets a MDSSesssion created with no CustomizationClassList and locale.
  ** @return MDSSession instance.
  */
  public MDSSession getMDSSession()
  {
      return mMDSInstance.createSession(
                 new SessionOptions(IsolationLevel.READ_COMMITTED,
                                    null,  // locale
                                    null),  // customization class list
                 null); // UserStateHandler
  }

  private void printElement(MElement elem, int level)
  {
      StringBuffer indentBuff = new StringBuffer("");
      for ( int i = 0; i < level; i++ )
      {
      indentBuff.append("  ");
      }
      String indent = indentBuff.toString();

      // Print tag name of element.
      String ln = elem.getLocalName();
      System.out.println(indent + "Element " + ln);
      String attrIndent = indent + " -";

      if (ln.equals("directoryInfo"))
      {
      String provName = (String)elem.getAttributeValue("name");
      System.out.println(attrIndent + "Name = " + provName);
      String provDesc = (String)elem.getAttributeValue("description");
      System.out.println(attrIndent + "Description = " + provDesc);
      String provOwner = (String)elem.getAttributeValue("owner");
      System.out.println(attrIndent + "Owner = " + provOwner);
      }
      else if (ln.equals("location"))
      {
      String provUrl = (String)elem.getAttributeValue("accessUrl");
      System.out.println(attrIndent + "AccessURL = " + provUrl);
      String provPath = (String)elem.getAttributeValue("path");
      System.out.println(attrIndent + "Path = " + provPath);
      }

      MNodeList kids = elem.getChildren();
      for (int i = 0; kids != null && i < kids.length(); i++)
      {
      printElement((MElement)kids.item(i), level+level);
      }
  }

  /**
  **
  ** @param args
  */
  public static void main(String[] args)
  {
      try
      {
          // Parse the commandline options to get the BUILD_ROOT.
          Options options = new Options();
          Option option = OptionBuilder.withLongOpt("BUILD_ROOT")
              .hasArg().withDescription("Build Root").create();
          options.addOption(option);
          
          option = OptionBuilder.withLongOpt("DBARGS")
              .hasArg().withDescription("DB ARGS").create();
          options.addOption(option);

          CommandLineParser parser = new PosixParser();
          CommandLine cmd = parser.parse(options, args);
          String buildRoot = cmd.getOptionValue("BUILD_ROOT");

          if ( buildRoot == null )
          {
              System.out.println("BUILD_ROOT is null. Please ensure BUILD_ROOT"
                    + " is set as follows...");
              System.out.println("    --BUILD_ROOT=\"d:\\dir1\\dir2\"");
          }

          // Create the MDS XML path and provider XSD path.
          String mdsXMLPath = buildRoot + File.separator + "mds" +
              File.separator + "samples" +
              File.separator + "xml";
          String providerXSD = buildRoot + File.separator + "mds" +
              File.separator + "samples" +
              File.separator + "xsd" +
              File.separator + "provider.xsd";
          PortalProviderSample sample = new PortalProviderSample();

          // Initialize MDS
          sample.initMDS(mdsXMLPath, providerXSD);

          // Start an MDS session
          MDSSession sess = sample.getMDSSession();

          // Get the readonly Metadata Object.
          MetadataObject mo =
              sess.getMetadataObject("/oracle/portal/providers/"
                                     + "providerSample.xml");

          // Get the MElement content.
          MElement top =
              (MElement)mo.getMElement();

          // Print the XML structure.
          sample.printElement(top, 2);

          // get the extended metadata...
          ExtendedMetadata mdx = mo.getExtendedMetadata();

          Iterator iter = mdx.iterator();
          boolean mdxLocated = false;
          while ( iter.hasNext() )
          {
              RDFTriple triple = (RDFTriple)iter.next();
              if ( !mdxLocated )
              {
                  System.out.println("\nRetrieving extended metadata for"
                                     + " " + triple.getSubject());
                  mdxLocated = true;
              }
              System.out.println("  " + triple.getPredicate() + " = "
                                 + triple.getValue());
          }
          if ( mdxLocated )
          {
              System.out.println("End of extended metadata.");
          }
      }
      catch (MetadataNotFoundException e)
      {
          System.out.println("MetadataNotFoundException" + e.getErrorMessage());
      }
      catch (ReferenceException e)
      {
          System.out.println("ReferenceException" + e.getErrorMessage());
      }
      catch (ParseException e)
      {
          System.out.println("ParseException" + e.getMessage());
      }
  }

    private MDSInstance mMDSInstance;
}
