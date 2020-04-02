/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.mymusicindustry.mymusiccompany;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import oracle.mds.config.CustClassListMapping;
import oracle.mds.config.CustConfig;
import oracle.mds.core.IsolationLevel;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.MetadataObject;
import oracle.mds.core.SessionOptions;
import oracle.mds.core.ValidationType;
import oracle.mds.exception.MDSException;


public class CreateMetadataExample extends ReadMetadataExample
{
    /**
    ** Main method, illustrates creation of metadata objects.
    */
    public static void main(String[] args)
    {
        CreateMetadataExample ex = new CreateMetadataExample();
        /*
        ** Use the MDSInitializer helper class to instantiate an MDSInstance
        ** (Available in Appendix A4)
        */
        MDSInitializer  init = createMDSInitializer(args);
        MDSInstance     mds  = init.getMDSInstance();
        MDSSession          sess = null;
        try
        {
            // First ensure the object does not exist
            ex.deleteIfNec(mds);
            // Now create the new object
            sess = mds.createSession(
                      new SessionOptions(IsolationLevel.READ_COMMITTED,
                                 null,
                                 new CustConfig(new CustClassListMapping[]{})),
                      null);
            MetadataObject mo = sess.createMetadataObject(ex.getMOName(),
                                                          createDocument());
            sess.flushChanges(false, 
                              new ValidationType[]
                                  {ValidationType.RELATIONSHIP_VALIDATION});

            System.out.println("Metadata Object " + mo.getName() +
                               "\n  (type " + mo.getTypeName() +
                               ") has been successfully created and saved");
        }
        catch ( Exception ce )
        {
            System.err.println(ce.getLocalizedMessage());
        }
    }


    /**
    ** Returns the name of a metadata object used by this sample.
    ** @return Fully qualified name of a sample document.
    */
    protected String getMOName()
    {
        // The following document will be created by this program and is
        // therefore not part of the shipped MDS samples
        return "/musicindustry/mymusiccompany/provider.xml";
    }


    private static Document createDocument()
    {
        try
        {
            DocumentBuilder docBuilder = DocumentBuilderFactory.
                                         newInstance().newDocumentBuilder();
            Document newDoc = docBuilder.newDocument();
            Element pdkProvider = newDoc.createElementNS(
                        "http://xmlns.oracle.com/provider",
                        "pdkProvider");
            pdkProvider.setAttribute("xml:lang", "en-US");
            newDoc.appendChild(pdkProvider);
            Element pInfo = newDoc.createElementNS(
                        "http://xmlns.oracle.com/provider",
                        "providerInfo");
            pdkProvider.appendChild(pInfo);
            Element dInfo = newDoc.createElementNS(
                        "http://xmlns.oracle.com/provider",
                        "directoryInfo");
            dInfo.setAttribute("id", "dirInfo");
            dInfo.setAttribute("name", "Sample PDK Provider");
            dInfo.setAttribute("description", "This is a sample provider");
            dInfo.setAttribute("owner", "dechrist");
            pInfo.appendChild(dInfo);
            Element loc = newDoc.createElementNS(
                        "http://xmlns.oracle.com/provider",
                        "location");
            loc.setAttribute("id", "location");
            loc.setAttribute("accessUrl",
                             "http://webdbsvr1.us.oracle.com:3000");
            loc.setAttribute("path", "/oracle/portal/providers/sample1.xml");
            pInfo.appendChild(loc);
            return newDoc;
        }
        catch ( Exception e )
        {
            System.err.println(e.getLocalizedMessage());
        }
        return null;
    }


    // Ensure the metadata object we are going to create does not exist
    private void deleteIfNec(MDSInstance mds)
        throws MDSException
    {
        MDSSession sess = mds.createSession(
                            new SessionOptions(IsolationLevel.READ_COMMITTED,
                                               null, null), 
                            null);
        sess.deleteMetadataObject(sess.getMOReference(getMOName()));
        sess.flushChanges(false, 
                          new ValidationType[]
                              {ValidationType.RELATIONSHIP_VALIDATION});
    }
}
