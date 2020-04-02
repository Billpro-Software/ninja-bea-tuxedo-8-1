/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.portal.transfer;

import java.util.List;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import oracle.mds.core.MDSSession;
import oracle.mds.core.MetadataObject;
import oracle.mds.naming.DocumentName;
import oracle.mds.transfer.TransferUnitList;
import oracle.mds.transfer.TransferContext;
import oracle.xml.parser.v2.NodeFactory;
import oracle.xml.parser.v2.XMLDocument;


/**
** This is a sample <code>TransferListener</code> implementation that
** simulates portal deployment. This is used to deploy the contents
** packaged either by {@link PortalPackageInSourceListener} or
** {@link PortalPackageInTargetListener}
** <p>
** Portal deployment can be done as per the following steps:
** <br />
** <ol>
**  <li>
**  Before starting the deployment process, portal runtime plugs into the
**  deployment process by registering <code>TransferListener</code>
**  implementation with <code>MDSTransfer</code>. (PortalDeployListener
**  is a sample listener implementation for deployment).
**  </li>
**  <li>
**  Portal runtime invokes <code>MDSTransfer::transferFromStore()</code>
**  method to import (deploy) its documents to the target store.
**  </li>
**  <li>
**  <code>TransferListener::initOperation()</code> will be invoked
**  by <code>MDSTransfer</code> before the deployment process.
**  </li>
**  <li>
**  <code>MDSTransfer</code> performs actual import (deployment)
**  operation. But the MDS transaction is not committed.
**  </li>
**  <li>
**  <code>TransferListener::postOperation()</code> is invoked.
**  <code>TransferListener::postOperation()</code> implementation
**  provided by this class reads the portal combined MO from the
**  packaged store and composes the individual documents that were
**  used to create portal Combined MO in package operation.
**  Refer to {@link #postOperation} for more information.
**  </li>
**  <li>
**  MDS Transaction is commited / rolled back as applicable.
**  </li>
** </ol>
** <b>Note:</b> The steps explained above and the sample implementation
** provided by this class are purely for illustration purposes and need not
** be done in the same way in real time.
** </p>
**
** @see oracle.mds.transfer.MDSTransfer
** @see oracle.mds.transfer.TransferListener
** @see PortalPackageInSourceListener
** @see PortalPackageInTargetListener
**
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** pwhaley   09/25/07 - #(6400014) perf: use getNextSibling to tour DOM.
** rchalava  08/10/06 - (#5359760) Added new method called postCommit() on 
**                      TransferListner.
** lramados  07/05/05 - Minor javadoc fix
** lramados  05/25/05 - Rename TransferUnitList to TransferUnitList
** cbarrow   05/18/05 - Move to revised MDS Core API
** lramados  03/04/05 - lramados_listener_impl_1
** prasubra  02/25/05 - Creation.
** --------------------------------------------------------------------------->
*/
public class PortalDeployListener extends PortalTransferListenerBase
{
    //======================================================================
    // Constructor.
    //======================================================================

    /**
    ** Construct the listener instance.
    */
    public PortalDeployListener()
    {
        // Do something relevant.
    }


    //======================================================================
    // Instance methods.
    //======================================================================

    /** {@inheritDoc} */
    public TransferUnitList getAdditionalTransferUnitsToProcess()
    {
        return null;
    }


   /** {@inheritDoc} */
    public TransferUnitList getTransferUnitsNotToProcess()
    {
        return mTransferUnitsNotToProcess;
    }


    /** {@inheritDoc} */
    public void initOperation(TransferContext  transferContext,
                              TransferUnitList transferUnitList)
    {
        mTransferUnitsNotToProcess = transferUnitList;
    }


    /**
    ** This method performs the following operations:
    ** <br />
    ** <ol>
    **  <li>portal combined MO is read from source store.</li>
    **  <li>
    **  Individual documents (using which portal combined MO was
    **  composed) are composed by reading the contents of
    **  portal combined MO. These individual documents are then
    **  saved in target store.
    **  </li>
    ** </ol>
    ** @param transferContext  Transfer context
    ** @param transferUnitList List of documents
    ** @param docsBeingTransfered List of documents being tranfered
    */
    public void postOperation(TransferContext  transferContext,
                              TransferUnitList transferUnitList,
                              List             docsBeingTransfered)
    {
        try
        {
            MDSSession sourceMDSSession =
                transferContext.getSourceMDSSession();
            MDSSession targetMDSSession =
                transferContext.getTargetMDSSession();

            // Get the portal combined MO
            MetadataObject portalCombinedMO =
                sourceMDSSession.getMetadataObject(
                    sCombinedMODocumentName.getAbsoluteName());
            Document doc = portalCombinedMO.getDocument();

            // Read the DOM tree so that individual documents can
            // be constructed based on this DOM.
            Element docElement = doc.getDocumentElement();
            Node node = docElement.getFirstChild();

            int j = 0;
            while ( node != null )
            {
                if ( node.getNodeType() == Node.ELEMENT_NODE )
                {
                    DocumentName docName =
                            DocumentName.create(PORTAL_NAMESPACE
                                                + DOC_CONSTANT
                                                + j++
                                                + XML_EXTN);
                    createDocumentFromElement(targetMDSSession,
                                              node,
                                              docName);
                }
                node = node.getNextSibling();
            }
        }
        catch ( Exception ex )
        {
            throw new RuntimeException(ex);
        }
    }


    // Javadoc inherited from TransferListener
    /** {@inheritDoc} */
    public void postCommit(TransferContext  transferContext,
                           TransferUnitList curListenerDocsTransferred,
                           List             cumTransferUnitResultList)
    {

    }


   /** {@inheritDoc} */
    public void rollback(TransferContext  transferContext,
                         TransferUnitList curListenerDocsTransferred,
                         List             cumDocsTransferred)
    {
    }


    /**
    ** Creates a new Xml document in the given MDSSession keeping
    ** the given Node as root element of new Document.
    **
    ** @param mdsSession  Session being used to create the document
    ** @param rootNode    rootNode of the document.
    ** @param docName     name of the document.
    ** @throws Exception Not expected. Indicates something wrong if thrown.
    */
    private void createDocumentFromElement(MDSSession  mdsSession,
                                           Node         rootNode,
                                           DocumentName docName)
        throws Exception
    {
        NodeFactory nodeFactory = new NodeFactory();
        XMLDocument newDoc = nodeFactory.createDocument();
        Node targetNode = newDoc.importNode(rootNode, true);
        newDoc.appendChild(targetNode);
        saveDocument(mdsSession, newDoc, docName);
    }


    //======================================================================
    // Instance variables.
    //======================================================================

    /**
    ** List of documents that should not be processed (transferred).
    */
    private TransferUnitList mTransferUnitsNotToProcess;
}
