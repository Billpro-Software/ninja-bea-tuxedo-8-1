/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.portal.transfer;

import java.util.Iterator;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import oracle.mds.core.MDSSession;
import oracle.mds.core.MOReference;
import oracle.mds.core.MetadataObject;
import oracle.mds.core.ValidationType;
import oracle.mds.internal.persistence.PContextImpl;
import oracle.mds.naming.DocumentName;
import oracle.mds.persistence.PContext;
import oracle.mds.persistence.PDocument;
import oracle.mds.persistence.PManager;
import oracle.mds.persistence.PTransaction;
import oracle.mds.transfer.TransferListener;
import oracle.mds.transfer.TransferUnit;
import oracle.mds.transfer.TransferUnitList;
import oracle.xml.parser.v2.NodeFactory;
import oracle.xml.parser.v2.XMLDocument;

/**
** Abstract base class that provides common functionality needed
** for Portal package and deploy listener sample implementations.
** Refer to API documentation for {@link PortalPackageInSourceListener},
** {@link PortalPackageInTargetListener} and {@link PortalDeployListener} to
** know more about the listener sample implementations.
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** gnagaraj  04/27/06 - (5190646) Don't use createElement() and then 
**                      setAttribute("xmlns"..)
** rchalava  04/17/06 - Use other variant of flushChanges(), to skip the type 
**                      validation.
** kselvara  03/10/06 - Use PContextImpl as PContext. 
** lramados  06/30/05 - Add  createPortalCombinedMO() method.
** cbarrow   05/19/05 - Move to revised MDS Core API
** gnagaraj  03/22/05 - PTransaction API changes to not require store parameter.
** lramados  03/04/05 - lramados_listener_impl_1
** prasubra  02/25/05 - Creation.
** --------------------------------------------------------------------------->
*/
public abstract class PortalTransferListenerBase extends TransferListener
{
    //======================================================================
    // Instance methods.
    //======================================================================

    /**
    ** Creates a XMLDocument with elements. Each element contains the contents
    ** of the document associated with <code>TransferUnit</code> in the given
    ** <code>TransferUnitList</code>.
    **
    ** @param transferUnitList   The <code>TransferUnitList</code> instance.
    ** @param sourceSession      The <code>MDSSession</code> instance.
    **
    ** @return XMLDocument - The <code>XMLDocument</code> instance.
    */
    protected XMLDocument createPortalCombinedMO(
            TransferUnitList transferUnitList,
            MDSSession       sourceSession)
    {
        XMLDocument newDoc = null;
        try
        {
            // Create new DOM document and import the XML tree cotained
            // in the transferUnitList as a child element of the new document's
            // root element.

            NodeFactory nodeFactory = new NodeFactory();
            newDoc = nodeFactory.createDocument();

            Element rootNode =
                   newDoc.createElementNS("http://xmlns.oracle.com/portal", 
                                          "portalCombinedMO");
            rootNode.setAttribute("name", "PortalCombinedMO");
            Iterator transferUnitIter = transferUnitList.iterator();

            while ( transferUnitIter.hasNext() )
            {
                TransferUnit transferUnit =
                        (TransferUnit)transferUnitIter.next();

                if ( transferUnit.shouldTransferTUDocument() )
                {
                    String docName = null;
                    MOReference ref = transferUnit.getMOReference();
                    if ( ref != null )
                    {
                        docName = ref.getName();
                    }
                    else
                    {
                        docName = transferUnit.getDocumentName().getAbsoluteName();
                    }

                    MetadataObject mo =
                            sourceSession.getMetadataObject(docName);
                    Document doc =
                            (Document)mo.getDocument();
                    Element docElement = doc.getDocumentElement();
                    Node targetNode = newDoc.importNode(docElement, true);
                    rootNode.appendChild(targetNode);
                }
            }

            // Append the root node to new document.
            newDoc.appendChild(rootNode);
        }
        catch ( Exception ex )
        {
            throw new RuntimeException(ex);
        }

        return newDoc;
    }


    /**
    ** Method used to save the dirty XML Document in the given MDSSession
    ** using the document name given by docName argument.
    **
    ** @param mdsSession using which the document is created.
    ** @param dirtyDocument document to be saved.
    ** @param docName name of the document.
    **
    ** @throws Exception if save document fails for some reason.
    */
    protected void saveDocument(MDSSession   mdsSession,
                                XMLDocument  dirtyDocument,
                                DocumentName docName) throws Exception
    {
        mdsSession.createMetadataObject(docName.getAbsoluteName(),
                                  dirtyDocument);       
        mdsSession.flushChanges(false, 
                                new ValidationType[]
                                    {ValidationType.RELATIONSHIP_VALIDATION});
    }


    /**
    ** Deletes the given document from the given MDSSession.
    **
    ** @param mdsSession MDSSession to delete from
    ** @param docName     document to be deleted.
    ** @throws Exception  if delete document fails for some reason.
    */
    protected void deleteDocument(MDSSession   mdsSession,
                                  DocumentName docName) throws Exception
    {
        PTransaction pt = mdsSession.getPTransaction();
        PManager pm = mdsSession.getMDSInstance().getPersistenceManager();
        PDocument pdoc = pm.getDocument(mCurrentPContext, docName);
        pt.deleteDocument(pdoc, false);
        mdsSession.flushChanges(false, 
                                new ValidationType[]
                                    {ValidationType.RELATIONSHIP_VALIDATION});
    }


    //======================================================================
    // Static variables.
    //======================================================================

    /**
    ** Portal namespace.
    */
    public static final String PORTAL_NAMESPACE = "/oracle/portal/";

    /**
    ** Constant denoting "PortalDoc".
    */
    public static final String DOC_CONSTANT = "PortalDoc";


    /**
    ** Xml file extension.
    */
    protected static final String XML_EXTN = ".xml";


    /**
    ** Portal combined MO Name.
    */
    public static final String COMBINED_MO_NAME =
            PORTAL_NAMESPACE + "PortalCombinedMO" + XML_EXTN;


    /**
    ** DocumentName for portal Combined MO.
    */
    protected static DocumentName sCombinedMODocumentName;


    //======================================================================
    // Static block.
    //======================================================================

    static
    {
        try
        {
            sCombinedMODocumentName =
                    DocumentName.create(COMBINED_MO_NAME);
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }


    //======================================================================
    // Instance variables.
    //======================================================================

    /**
    ** Current PContext.
    */
    private PContext mCurrentPContext = new PContextImpl();
}
