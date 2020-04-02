/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */

package oracle.mds.samples.mymusicindustry.mymusiccompany;

import java.util.Locale;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import oracle.mds.config.CustClassListMapping;
import oracle.mds.config.CustConfig;
import oracle.mds.core.IsolationLevel;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.MetadataObject;
import oracle.mds.core.ConcurrentMOChangeException;
import oracle.mds.core.MetadataNotFoundException;
import oracle.mds.core.SessionOptions;
import oracle.mds.core.ValidationException;
import oracle.mds.core.ValidationType;
import oracle.mds.exception.UnsupportedUpdateException;
import oracle.mds.persistence.MDSIOException;

public class WriteMetadataExample extends ReadMetadataExample
{

    /**
    ** Main method, illustrates updating existing metadata objects.
    */
    public static void main(String[] args)
    {
        WriteMetadataExample ex   = new WriteMetadataExample();
        /*
        ** Use the MDSInitializer helper class to instantiate an MDSInstance
        ** (Available in Appendix A4)
        */
        MDSInitializer  init = createMDSInitializer(args);
        MDSInstance     mds  = init.getMDSInstance();
        MDSSession          sess = null;
        try
        {
            sess = mds.createSession(
                      new SessionOptions(IsolationLevel.READ_COMMITTED,
                                 null,
                                 new CustConfig(new CustClassListMapping[]{})),
                      null);

            /*
            ** Base Metadata is updated
            */
            ex.doUpdates(sess, "Base updated");

            sess = mds.createSession(
                     new SessionOptions(IsolationLevel.READ_COMMITTED,
                                new Locale("es", "MX"),
                                new CustConfig(new CustClassListMapping[]{})),
                     null);
            /*
            ** Spanish translations
            */
            ex.doUpdates(sess, "Spanish translation of Base metadata");

            sess = mds.createSession(
                     new SessionOptions(IsolationLevel.READ_COMMITTED,
                                        new Locale("en", "US"),
                                        null),
                     null);
            sess.setProperty("user", "tom");
            /*
            ** User customization is created
            */
            ex.doUpdates(sess, "User Customization created");
        }
        catch ( Exception ce )
        {
            System.err.println(ce.getLocalizedMessage());
        }
    }

    /**
    ** Updates value of an attribute in the metadata object to given value.
    */
    protected void doUpdates(MDSSession sess, String updatedValue)
    {
        MetadataObject mo = getMetadataObject(sess,
                                              getMOName());
        if ( mo == null )
        {
            System.err.println("MetadataObject " + getMOName() + "not found; " +
                               "please run CreateMetadataSample to created it");
            System.exit(1);
        }
        try
        {
            mo = sess.getMutableMO(mo.getReference());
        }
        catch ( MetadataNotFoundException mnfe )
        {
            System.err.println(mnfe.getLocalizedMessage());
        }
        catch ( UnsupportedUpdateException uue )
        {
            System.err.println(uue.getLocalizedMessage());
            System.err.println("Mutable MetadataObject  " + getMOName() 
                + " cannot be obtained from MetadataStore specified since"
                + " there are pending writes to other MetadataStores."
                + " Do flushChanges/cancelChanges on MDSSession to proceed");
            System.exit(1);
        }        
        Document doc = mo.getDocument();

        NodeList list = doc.getElementsByTagName("directoryInfo");
        Element el;
        for ( int i = list.getLength(); i > 0; i-- )
        {
            el = (Element)list.item(i-1);
            el.setAttribute("description", updatedValue);
        }
        try
        {
            sess.flushChanges(false, 
                              new ValidationType[]
                                  {ValidationType.RELATIONSHIP_VALIDATION});
            System.out.println("description successfully updated to: " +
                               updatedValue);
        }
        catch ( MDSIOException mioe )
        {
            System.err.println(mioe.getLocalizedMessage());
        }
        catch ( ValidationException valEx )
        {
            System.err.println(valEx.getLocalizedMessage());
        }
        catch ( ConcurrentMOChangeException mocsge )
        {
            System.err.println(mocsge.getLocalizedMessage());
        }
    }

    /**
    ** Returns the name of a metadata object used by this sample.
    ** @return Fully qualified name of a sample document.
    */
    protected String getMOName()
    {
        // The following document will be updated by this program.  It must
        // first be created by running CreateMetadataSample.
        return "/musicindustry/mymusiccompany/provider.xml";
    }

}
