/* Copyright (c) 2006, 2009, Oracle and/or its affiliates. 
All rights reserved. */

package oracle.mds.samples.versioning;

import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.StringTokenizer;

import oracle.mds.config.MDSConfig;
import oracle.mds.config.PConfig;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.MOReference;
import oracle.mds.core.MetadataObject;
import oracle.mds.core.SessionOptions;
import oracle.mds.core.ValidationType;
import oracle.mds.exception.InvalidNamespaceException;
import oracle.mds.exception.MDSException;
import oracle.mds.naming.Namespace;
import oracle.mds.persistence.MetadataStore;
import oracle.mds.persistence.stores.db.DBMetadataStore;
import oracle.mds.versioning.LabelUsage;
import oracle.mds.versioning.VersionContext;
import oracle.mds.versioning.VersionHelper;

import oracle.xml.parser.v2.DOMParser;

import oracle.xml.parser.v2.XMLDocument;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.commons.cli.PosixParser;

import org.w3c.dom.Attr;
import org.w3c.dom.Document;

/**
 * This sample exercises the base versioning functionality in MDS.
 * It demonstrates how multiple versions of an MOPart can be saved to
 * a DB store, and how older versions of MO's can be accessed using
 * Labels.
 * 
 **/
 
 /*
  * TODO
  * Enhancements to be done:
  * Scenario 1:
  * 1) Store /versioning/orders/Order1.xml and 
  *    /versioning/shared/customers/Customer1.xml in separate partitions
  * 2) Change the config to reflect the same.
  *    /versioning/orders -> partition1, /versioning/shared -> partition2
  * 3) Create label only for the partition which has Customer1.xml 
  * 4) Update Order1.xml as well to demonstrate that each MO can be associated 
  *    with a label given the above configuration.
  * Scenario 2:
  * 1) Use a programmatic/declarative configuration on the MDSInstance to 
  *    access label-based metadata.
  */
  
 /*
 ** <!-------------------------------------------------------------------------
 ** MODIFIED (MM/DD/YY)
 ** pwhaley   07/15/09 - XbranchMerge pwhaley_db2db from main
 ** pwhaley   07/14/09 - Update for IBM DB2.
 ** erwang    10/06/08 - Update jdbc:datadirect ot jdbc:weblogic
 ** dklein    01/25/08 - #(6668812) Add default SQLServer port if none specified
 ** jejames   12/06/07 - #(5842897) Removed the commented reference to
 **                      the deprecated PartitionHelper class.
 ** dklein    09/18/07 - Comment out call to System.exit at the end of the main
 **                      method, as it exits cleanly without this
 ** erwang    06/01/07 - Add SQLServer datadirect driver support
 ** smunugot  11/30/06 - Added exit statement to exit properly
 ** ykosuru   08/04/06 - Change parameter in call to vh.createVersionContext
 ** rchalava  07/25/06 - Handle the exception from VersionHelper.deleteLabel().
 ** gkonduri  07/05/06 - 
 ** gkonduri  07/03/06 - Created.
 ** -------------------------------------------------------------------------->
 */
 
public class VersioningSample {


    public static void main(String[] args) 
    {
        simpleVersioningSample(args);
        //Thread is not terminating properly.. so, calling
        //exit() to terminate properly..
        //System.exit(0);
    }
    
    
    /**
     * Creates the MDSInstance for the sample.
     * @return
     */
    private static MDSInstance createMDSInstance(String[] args) 
                                   throws MDSException
    {
        MDSInstance mInstance = null;
        MDSConfig config = getMDSConfig(args);

        mInstance = MDSInstance.
                     getOrCreateInstance("versioningSampleInstance", config);
        return mInstance;        
    }
    
    
    /**
     * Creates the customer and order MO's.
     * @param tipSession An MDSSession
     */
    private static void createMOs(MDSSession tipSession) 
    {
        try
        {
            Document custDom = getDocFromString(CUSTOMER_DOC);
            System.out.println("Saving ver-1 of Customer xml as:");
            printDOM((XMLDocument)custDom);
            tipSession.createMetadataObject(CUSTOMER_MONAME, custDom);
            Document orderDom = getDocFromString(ORDER_DOC);
            System.out.println("Saving the initial version of Order xml as:");
            printDOM((XMLDocument)orderDom);
            tipSession.createMetadataObject(ORDER_MONAME, orderDom);
            tipSession.flushChanges(false, 
                                    new ValidationType[] {});
        }
        catch (Exception ex) 
        {
            System.out.println(ex.getLocalizedMessage());       
        }  
    }
    
    
    private static Option createOption(String optionName) 
    {
        Option option = OptionBuilder.withLongOpt(optionName).
            hasArg().create();
        return option;
    }
    
    /**
     * Cleans up any MO's created from previous runs of this sample.
     * @param sessionToCleanup An MDSSession.
     */
    private static void doCleanup(MDSSession sessionToCleanup) 
    {
        try
        {
            sessionToCleanup.deleteMetadataObject(
                               MOReference.create(CUSTOMER_MONAME));
            sessionToCleanup.deleteMetadataObject(
                               MOReference.create(ORDER_MONAME));
            sessionToCleanup.flushChanges(false, 
                                          new ValidationType[] {});
        }
        catch (Exception ex) 
        {
            System.out.println(ex.getLocalizedMessage());    
        }
        
        VersionHelper vHelper = VersionHelper.get(sessionToCleanup.getMDSInstance());
        try
        {
            Namespace namespace = Namespace.create("/");
            vHelper.deleteLabel(LABEL1, namespace);
            vHelper.deleteLabel(LABEL2, namespace);
        }
        catch ( InvalidNamespaceException e )
        {
            // wouldn't happen
            throw new RuntimeException(e);
        }
    }
    
    
    /**
     * Returns the DBMetadataStore instance.
     * @return
     */
    private static MetadataStore getDBMetadataStore(String[] args) 
                       throws MDSException
    {
        //String myHost   = "dfcsol-sun";
        //String myPort   = "1521";
        //String mySID    = "dfc102db";
        //String myUser   = "gkonduri";
        //String myPasswd = "x";
        
        // Parse the commandline options to get the DBARGS.
        Options options = new Options();
        options.addOption(createOption("DBARGS"));
        options.addOption(createOption("BUILD_ROOT"));

        CommandLineParser parser = new PosixParser();
        CommandLine cmd = null;
        try
        {
            cmd = parser.parse(options, args);
        }
        catch (ParseException e)
        {
            System.out.println("ParseException" + e.getMessage());
            throw new MDSException (new IllegalArgumentException(
                                      "Illegal arguments. Check with usage"));   

        }

        String dbargs   = cmd.getOptionValue("DBARGS");
        StringTokenizer dbargsTokens = new StringTokenizer(dbargs);
        Hashtable<String, String> argMap = new Hashtable<String, String>();
        while (dbargsTokens.hasMoreTokens()) 
        {
            String dbarg = dbargsTokens.nextToken();
            StringTokenizer dbargParts = new StringTokenizer(dbarg, "=");
            argMap.put(dbargParts.nextToken().toLowerCase(), dbargParts.nextToken());
        }
        
        String myHost   = argMap.get("host"); //"dfcsol-sun";
        String myPort   = argMap.get("port"); //"1521";
        String mySID    = argMap.get("sid"); //"dfc102db";
        String myUser   = argMap.get("username"); //"gkonduri";
        String myPasswd = argMap.get("password"); //"x";
        String myDB     = argMap.get("database"); // "mds";
        String dbVendor = argMap.get("dbvendor"); // Mssql_dd.
        
        DBVENDOR vendor = DBVENDOR.UNKNOWN;

        // Try dbvender if it dbVendor is null or empty.
        if ( dbVendor == null || dbVendor.trim().length() == 0)
        {
            dbVendor = argMap.get("dbvender");
        }

        // Decide DB Vendor.
        if ( dbVendor != null )
        {
            dbVendor = dbVendor.toLowerCase();
            if ( dbVendor.startsWith("oracle") )
            {
                vendor = DBVENDOR.ORACLE;
            }
            else if ( dbVendor.startsWith("mssql") )
            {
                vendor = DBVENDOR.MSSQL;
                
                // #(6668812) set SQL server default port number
                if ( myPort == null || myPort == "" )
                {
                    myPort = "1433";
                }
            }
            else if ( dbVendor.startsWith("ibmdb2") )
            {
                vendor = DBVENDOR.IBMDB2;
                if ( myPort == null || myPort == "" )
                {
                    myPort = "50000";
                }
            }
        }
        
        if ( vendor == DBVENDOR.UNKNOWN )
        {
            vendor =  ( mySID == null ) ? DBVENDOR.MSSQL : DBVENDOR.ORACLE;
        }
 

        if ( myUser == null || myPasswd == null || myHost == null ||
            myPort == null || (vendor == DBVENDOR.ORACLE && mySID == null) || 
            (vendor != DBVENDOR.ORACLE && myDB == null) )
        {
            throw new MDSException (new IllegalArgumentException(
                                    "Some argument is null. Illegal arguments. " 
                                    + "Check with usage"));   
        }

        
        String myJDBCURL = null;
        
        // For Oracle, we use Oracle's thin driver.  For SQL server,
        // we use datadirect jdbc driver.
        if ( vendor == DBVENDOR.ORACLE )
        {
            myJDBCURL = "jdbc:oracle:thin:@" + myHost + ":"
                                 + myPort + ":" + mySID;                        
        }
        else if ( vendor == DBVENDOR.MSSQL )
        {
            myJDBCURL = "jdbc:weblogic:sqlserver://" + myHost + ":"
                                 + myPort + ";database=" + myDB;
        }
        else // DBVENDOR.IBMDB2
        {
            myJDBCURL = "jdbc:weblogic:db2://" + myHost + ":"
                         + myPort + ";DatabaseName=" + myDB;
        }

        System.out.println("Connecting to db " + myJDBCURL);
        MetadataStore store = null;
        store = new DBMetadataStore(myUser, 
                                    myPasswd, 
                                    myJDBCURL, 
                                    MY_PARTITION);
        return store;
    }
    
    
    /**
     * Creates the DOM document from the string variables stored in the sample.
     * @param xmlContents
     * @return
     */
    private static Document getDocFromString(String xmlContents) 
    {
        StringReader sr = new StringReader(xmlContents);
        DOMParser domP = new DOMParser();
        try
        {
            domP.parse(sr);
        }
        catch (Exception ex) 
        {
            System.err.println(ex.getLocalizedMessage());
        }
        Document doc = domP.getDocument();
        return doc;
    }
    
    
    /**
     * Sets up the MDSConfig. 
     * Uses null for type and cust config. 
     * Uses a mapping of "/" to DBStore for PConfig.
     * @return
     */
    private static MDSConfig getMDSConfig(String[] args) 
                              throws MDSException
    {
        MetadataStore store = getDBMetadataStore(args);
        PConfig pConfig = new PConfig(store);
        MDSConfig mConfig = new MDSConfig(null, pConfig, null); 
        //Null cust and type config.
        
        return mConfig;    
    }
    
    
    /**
     * This method accesses the "customerMO" from the provided session
     * and returns the membership type on that customer MO.
     * @param sess An MDSSession to access the customerMO.
     * @return String value of the membership type or null.
     */
    private static String getMembershipType(MDSSession sess) 
    {
        MetadataObject custMO = null;
        try
        {
            custMO = sess.getMetadataObject(CUSTOMER_MONAME);
        }
        catch (Exception ex) 
        {
            System.out.println(ex.getLocalizedMessage());    
        }
        if (custMO != null)
        {
            Document custDom = custMO.getDocument();
            Attr attr = (custDom.getDocumentElement()).
                                getAttributeNode("membershipType");
            String membershipType = attr.getValue();
            return membershipType;
        }
        else 
        {
            return null;
        }
    }
    
    
    
    /**
     * Prints the dom document to the System.out
     * @param doc
     */
    private static void printDOM(XMLDocument doc) {
        try
        {
            doc.print(System.out);
        }
        catch (IOException ex) {
            System.out.println(ex.getLocalizedMessage());
        }
    }
    
    
    /**
     * Simple Versioning Sample does the following:
     * - Cleanup MO's from previous runs
     * - Create MO's and create label
     * - Update MO's
     * - Access tip versions using a session.
     * - Access old versions using a session and a old label.
     * @param args
     */
    private static void simpleVersioningSample(String[] args)
    {
        
        // Step1: Create MDSInstance with mappings to a versioned store (DB)
        MDSInstance mInstance = null;
        try
        {
            mInstance = createMDSInstance(args);
        }
        catch (MDSException ex) 
        {
            System.out.println(ex.getLocalizedMessage());
            System.out.println("Usage \"java VersioningSample "+
              "--DBARGS \"username=x password=x host=x port=x sid=x\" \"");
            System.out.println("  or  \"java VersioningSample "+
              "--DBARGS \"username=x password=x host=x port=x database=x dbvendor=mssql\" \"");
            System.exit(1);
        }
        // Step 1.1: Setup, delete the labels and MOs we will create in the
        // course of this sample.
        SessionOptions tipOptions = new SessionOptions(
                                          null, 
                                          null, 
                                          null);
        MDSSession sessionToCleanup = mInstance.createSession(tipOptions, null);
        doCleanup(sessionToCleanup);
                
        // Step2: Create MDSSession with no VersionContext (tip access).
        MDSSession tipSession = mInstance.createSession(tipOptions, null);

        // Step3: Create the first version of the MO's
        createMOs(tipSession);
        
        // Step4: Create a label so that we can access these versions 
        // of the objects created above later on even if there are newer
        // versions of the same objects available.
        // Using this label, for ex, will always show that the membershipType
        // of Customer1.xml is "Silver" even if it is changed in later versions.
        VersionHelper vHelper = VersionHelper.get(mInstance);
        try
        {
            vHelper.createLabel(LABEL1, "my description", Namespace.create("/"));
        }
        catch (Exception ex) 
        {
            System.out.println(ex.getLocalizedMessage());
        }
        
        // Step5: Update Customer1.xml MO so that it creates a new
        // version of the base MOPart.
        // This step changes the membershipType of Customer1.xml to
        // "Gold" from "Silver".
        MDSSession tipSession1 = mInstance.createSession(tipOptions, null);
        updateMOs(tipSession1);
        
        // Step6: Similar to step4, another label can be created here,
        // if other new versions of the MOs are created after this 
        // point in time.
        // vHelper.createLabel(LABEL1, "my description", "/");
        
        // Step7: Create a session to access the "tip" version of metadata.
        MDSSession tipSession2 = mInstance.createSession(tipOptions, null);
        
        // MembershipType should be "Gold" since we updated it on tip version.
        System.out.println("Membership type obtained from a session accessing"+
                           " tip versions is " 
                           + getMembershipType(tipSession2));

        // Step8: Create MDSSession using label from step4 and access MO        
        try
        {
            LabelUsage labelUsage = new LabelUsage(LABEL1, 
                                        new Namespace[] {Namespace.create("/")});
            List<LabelUsage> labelUsageList = new ArrayList<LabelUsage>(1);
            labelUsageList.add(labelUsage);
            VersionContext vctx = vHelper.createVersionContext(labelUsageList);
            SessionOptions labelAccess = new SessionOptions(
                                          null, 
                                          null, 
                                          null,
                                          vctx,
                                          null);        
             MDSSession labelAccessSession = mInstance.createSession(
                                                        labelAccess, 
                                                        null);
             // Should be "Silver" as we are using an old version.
             System.out.println("Membership type obtained from a session " +
                                "accessing old label's versions is " + 
                                getMembershipType(labelAccessSession));
        }
        catch (Exception ex) 
        {
            System.out.println(ex.getLocalizedMessage());            
        }        
    }
    
    
    /**
     * Updates the customer MO to change the membershipType to "Gold"
     * @param tipSession An MDSSession
     */
    private static void updateMOs(MDSSession tipSession)
    {
        try
        {
            MetadataObject custMO = tipSession.getMutableMO(
                                       MOReference.create(CUSTOMER_MONAME));

            Document custDom = custMO.getDocument();
            Attr attr = (custDom.getDocumentElement()).
                                    getAttributeNode("membershipType");
            attr.setValue("Gold");
            
            System.out.println("Saving the next version of Customer xml as:");
            printDOM((XMLDocument)custDom);
            tipSession.flushChanges(false, 
                                    new ValidationType[] {});
        }
        catch (Exception ex)
        {
            System.out.println(ex.getLocalizedMessage());       
        }
    }
    

    private static String ORDER_MONAME   
                             = "/versioning/orders/Order1.xml";
    private static String CUSTOMER_MONAME 
                             = "/versioning/shared/customers/Customer1.xml";
                             
    private static String LABEL1 = "versioning_sample_label1";
    private static String LABEL2 = "versioning_sample_label2";
    private static String MY_PARTITION = "versioningPartition";

    private enum DBVENDOR {UNKNOWN, ORACLE, MSSQL, IBMDB2};
    
    private static String CUSTOMER_DOC =
    "<?xml version='1.0' encoding='UTF-8' ?>\n" + 
    "<customer xmlns=\"http://www.oracle.com/mds/versioningsamples\""+
    "  membershipType=\"Silver\" >\n" + 
    "  <firstName>John</firstName>\n" + 
    "  <lastName>Doe</lastName>\n" + 
    "  <!-- The membershipType can change from version to version -->\n" + 
    "</customer>";
    
    private static String ORDER_DOC = 
    "<?xml version='1.0' encoding='UTF-8' ?>\n" + 
    "<order xmlns=\"http://www.oracle.com/mds/versioningsamples\"\n" + 
    "       customerRef=\"/versioning/shared/customers/customer1.xml\">\n" + 
    "  <orderDetail id=\"a\" quantity=\"1\"\n" + 
    "               itemNumber=\"101\"/>\n" + 
    "  <orderDetail id=\"b\" quantity=\"1\"\n" + 
    "               itemNumber=\"102\"/>\n" + 
    "</order>";
}
