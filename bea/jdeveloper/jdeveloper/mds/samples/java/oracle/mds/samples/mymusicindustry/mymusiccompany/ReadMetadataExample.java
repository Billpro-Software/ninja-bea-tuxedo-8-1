/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.mymusicindustry.mymusiccompany;

import java.io.File;
import oracle.mds.core.IsolationLevel;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.MetadataNotFoundException;
import oracle.mds.core.MetadataObject;
import oracle.mds.core.SessionOptions;
import oracle.mds.melement.MElement;
import oracle.mds.naming.ReferenceException;

public class ReadMetadataExample
{

    /**
    ** Main method, illustrates reading existing metadata objects.
    */
    public static void main(String[] args)
    {
        /*
        ** Use the MDSInitializer helper class to instantiate an MDSInstance
        ** (Available in Appendix A4)
        */
        MDSInitializer  init = createMDSInitializer(args);
        MDSInstance mds  = init.getMDSInstance();
        MDSSession  sess = mds.createSession(
                              new SessionOptions(IsolationLevel.READ_COMMITTED,
                                                 null,
                                                 null),
                              null);
        ReadMetadataExample ex = new ReadMetadataExample();
        MetadataObject mo = ex.getMetadataObject(sess, ex.getMOName());
        MElement melem    = mo.getMElement();
        MElement dirInfo  = mo.getMElement(melem, "dirInfo");
        Object   owner    = dirInfo.getAttributeValue("owner");
        System.out.println("Got dirInfo with owner = " + owner);
    }


    /**
    ** Get the MetadataObject with given name.
    ** @return MetadataObject.
    */
    protected MetadataObject getMetadataObject(MDSSession sess,
                                               String     name)
    {
        try
        {
            return sess.getMetadataObject(name);
        }
        catch ( MetadataNotFoundException mnfe )
        {
            System.err.println(mnfe.getLocalizedMessage());
        }
        catch ( ReferenceException re )
        {
            System.err.println(re.getLocalizedMessage());
        }
        return null;
    }


    /**
    ** Returns the name of a metadata object used by this sample.
    ** @return Fully qualified name of a sample document.
    */
    protected String getMOName()
    {
        // The following document is part of the shipped MDS samples:
        return "/oracle/portal/providers/providerSample.xml";
    }

    /**
    ** Creates the MDSInitializer helper class.
    ** @return MDSInitializer instance.
    */
    protected static MDSInitializer createMDSInitializer(String[] args)
    {
        if ( args.length < 2 || !args[0].matches("-*BUILD_ROOT") )
        {
            System.out.println("ERROR: Missing --BUILD_ROOT parameter, " +
                               "unable to execute sample program ");
            System.out.println("Usage:\n");
            System.out.println("  java ...etc... --BUILD_ROOT {oracle_home}");
            System.exit(1);
        }
        /*
        ** Use the MDSInitializer helper class to instantiate an MDSInstance
        ** (Available in Appendix A4)
        */
        String buildRoot = args[1];
        String mdsXMLPath = buildRoot + File.separator + "mds" +
                            File.separator + "samples" +
                            File.separator + "xml";
        MDSInitializer  init = new MDSInitializer(mdsXMLPath);
        return init;
    }

}
