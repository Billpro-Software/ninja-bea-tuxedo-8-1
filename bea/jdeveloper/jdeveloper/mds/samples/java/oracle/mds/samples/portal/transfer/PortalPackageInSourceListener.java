/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.portal.transfer;

import java.util.List;

import oracle.mds.core.MDSSession;
import oracle.mds.transfer.TransferUnit;
import oracle.mds.transfer.TransferUnitList;
import oracle.mds.transfer.TransferContext;
import oracle.xml.parser.v2.XMLDocument;

/**
** This is a sample <code>TransferListener</code> implementation that
** simulates portal packaging. This is used to package the contents
** so that it can be deployed later by {@link PortalDeployListener}.
** <p>
** Portal packaging can be done as per the following steps:
** <br />
** <ol>
**  <li>
**  Before starting the packaging process, portal runtime plugs into the
**  package process by registering <code>TransferListener</code>
**  implementation with <code>MDSTransfer</code>
**  (PortalPackageInSourceListener and PortalPackageInTargetListener are
**  sample listener implementation for packaging).
**  </li>
**  <li>
**  Portal runtime invokes <code>MDSTransfer::transferToStore()</code>
**  method to export (package) its documents to the target package store.
**  </li>
**  <li>
**  <code>TransferListener::initOperation()</code> will be invoked
**  by <code>MDSTransfer</code> before the packaging process.
**  <code>TransferListener::initOperation()</code> implementation
**  provided by this class reads the documents to be exported, creates
**  a portal combined MO and removes the original documents from the export
**  list. Refer to {@link #initOperation} for more information.
**  </li>
**  <li>
**  Then <code>MDSTransfer</code> performs the export (packaging) operation,
**  but the changes are not yet written to disk (i.e. flushChanges is not yet
**  called on the MDS session).
**  </li>
**  <li>
**  <code>TransferListener::postOperation()</code> is invoked, where the
**  implementation can perform any clean up needed.
**  </li>
**  <li>
**  The changes on the session are flushed or cancelled as applicable.
**  </li>
** </ol>
** <b>Note:</b> The steps explained above and the sample implementation
** provided by this class are purely for illustration purposes and need not
** be done in the same way in real time. For example, portal can choose to
** create portal combined MO in <code>TransferListener::initOperation()
** </code> and split it up directly in the deployment store in
** <code>TransferListener::postOperation()</code> when transferring from
** one DB store to another DB store.
** </p>
** @see oracle.mds.transfer.MDSTransfer
** @see oracle.mds.transfer.TransferListener
** @see PortalDeployListener
**
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** gnagaraj  08/22/06 - Create the combined MO in target store.
** rchalava  08/10/06 - (#5359760) Added new method called postCommit() on
**                      TransferListner.
** lramados  07/08/05 - lramados_portal_usecase_update
** lramados  06/30/05 - Store the PortalCombinedMO in source instance without
**                      using the static int variable.
** lramados  06/17/05 - Modify TransferUnit creation methods.
** lramados  05/25/05 - Rename TransferUnitList to TransferUnitList
** cbarrow   05/12/05 - Revised core API
** cbarrow   05/09/05 - Move to revised MDS Core API
** lramados  03/23/05 - Modify constructor as empty constructor
** lramados  03/04/05 - lramados_listener_impl_1
** prasubra  02/25/05 - Creation.
** --------------------------------------------------------------------------->
*/
public class PortalPackageInSourceListener extends PortalTransferListenerBase
{
    //======================================================================
    // Constructor.
    //======================================================================

    /**
    ** Construct the listener instance.
    */
    public PortalPackageInSourceListener()
    {
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


    /**
    ** The following operations are performed in initOperation:
    ** <br />
    ** <ol>
    **  <li>
    **   Documents specified by transferUnitList are read.
    **  </li>
    **  <li>
    **   Portal Combined MO is created by reading the contents of
    **   documents specified by transferUnitList. This combined MO will
    **   contain the XML tree of each document as an immediate child
    **   element of the root element. Portal Combined MO is then
    **   stored in the target store. It is created in source
    **   <code>MDSInstance</code> and returned by
    **   <code>getAdditionalTransferUnitsToProcess()</code> method so that
    **   export operation will transfer it to target store.
    ** </ol>
    **
    ** @param transferContext  The <code>TransferContext</code> instance.
    ** @param transferUnitList The <code> TransferUnitList</code> instance.
    */
    public void initOperation(TransferContext  transferContext,
                              TransferUnitList transferUnitList)
    {
        MDSSession sourceSession =
            transferContext.getSourceMDSSession();

        // transferUnitList is stored in member variable so that documents in
        // the transferUnitList can be excluded in
        // getTransferUnitsNotToProcess() method.
        mTransferUnitsNotToProcess = transferUnitList;

        MDSSession mdsSessionForNewMO = null;

        mdsSessionForNewMO = transferContext.getTargetMDSSession();

        try
        {
            XMLDocument newDoc =
                    createPortalCombinedMO(mTransferUnitsNotToProcess,
                                           sourceSession);

            // Save the document in metadata store.
            saveDocument(mdsSessionForNewMO,
                         newDoc,
                         sCombinedMODocumentName);
        }
        catch ( Exception ex )
        {
            throw new RuntimeException(ex);
        }
    }


    /** {@inheritDoc} */
    public void postOperation(TransferContext  transferContext,
                              TransferUnitList transferUnitList,
                              List             docsBeingTransfered)
    {

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

    //======================================================================
    // Instance variables.
    //======================================================================

    /**
    ** List of documents that should not be processed (transferred).
    */
    private TransferUnitList mTransferUnitsNotToProcess;
}
