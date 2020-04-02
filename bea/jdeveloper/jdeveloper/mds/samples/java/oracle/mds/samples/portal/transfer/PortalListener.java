/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.portal.transfer;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import oracle.mds.cust.CustClassList;
import oracle.mds.cust.CustomizationClass;
import oracle.mds.transfer.CustOption;
import oracle.mds.transfer.TransferContext;
import oracle.mds.transfer.TransferListener;
import oracle.mds.transfer.TransferOption;
import oracle.mds.transfer.TransferOptions;
import oracle.mds.transfer.TransferUnit;
import oracle.mds.transfer.TransferUnitList;

/**
** This is a sample <code>TransferListener</code> implementation that is used
** to remove user customization class from the <code>TransferOption</code>
** associated with <code>TransferUnit</code> instances.
**
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** rchalava  08/10/06 - (#5359760) Added new method called postCommit() on 
**                      TransferListner.
** lramados  07/22/05 - lramados_validate_parameter_file
** prasubra  07/20/05 - Creation.
** --------------------------------------------------------------------------->
*/
public class PortalListener extends TransferListener
{
    //======================================================================
    // Constructor.
    //======================================================================

    /**
    ** Construct the listener instance.
    */
    public PortalListener()
    {
    }


    //======================================================================
    // Instance methods.
    //======================================================================

    /** {@inheritDoc} */
    public TransferUnitList getAdditionalTransferUnitsToProcess()
    {
        return mAdditionalTransferUnitsToProcess;
    }


   /** {@inheritDoc} */
    public TransferUnitList getTransferUnitsNotToProcess()
    {
        return mTransferUnitsNotToProcess;
    }


    /**
    ** The following operations are performed for removing user customization
    ** classes.
    ** <ul>
    **    <li> Get the <code>TransferOptions</code> from each 
    **         <code>TransferUnit</code>
    **    </li>
    **    <li> Iterate <code>TransferOptions</code> list and check whether 
    **          <code>CustOption</code> instance exists.
    **    </li>
    **    <li> Get <code>CustClassList</code> instance from CustOption and
    **         remove the required CustClassList if the 
    **         <code>CustClassList</code> contains them and add the new 
    **         CustOption instance to the new TransferOption list.
    **    </li>
    **    <li> Craete new TransferOptions with the new TransferOption list and 
    **         create new TransferUnit with the new TransferOptions.
    **    </li>
    **    <li> Add the newly created TransferUnit to the list of TransferUnit 
    **         instance that need to be processed and add the old TransferUnit
    **         to the list of TransferUnit instances that need not to be 
    **         processed.
    **    </li>
    ** </ul>   
    **
    ** @param transferContext  The <code>TransferContext</code> instance.
    ** @param transferUnitList The <code> TransferUnitList</code> instance.
    */
    public void initOperation(TransferContext  transferContext,
                              TransferUnitList transferUnitList)
    {
        mTransferUnitsNotToProcess        = TransferUnitList.create();
        mAdditionalTransferUnitsToProcess = TransferUnitList.create();
 
        Iterator iterator = transferUnitList.iterator();

        while ( iterator.hasNext() )
        {
            TransferUnit tu = (TransferUnit)iterator.next();

            if ( tu.getTransferOptions() != null )
            {
                // Remove the user customization class from the customization 
                // option if exists, create a new TransferOptions, create a new 
                // TransferUnit and set the new TransferOption in it. 
                TransferOptions transferOptions = tu.getTransferOptions();
                List newTransferOptions = new ArrayList();

                Iterator transferOptionsIterator = transferOptions.iterator();

                if ( transferOptionsIterator.hasNext() )
                {
                    TransferOption transferOption =
                            (TransferOption)transferOptionsIterator.next();

                    if ( transferOption instanceof CustOption )
                    {
                        CustOption custOption = (CustOption)transferOption;
                        List custClass = new ArrayList();
                        CustClassList ccList =
                                custOption.getOverriddenCustClassList();

                        // Remove the user customization class if exists.
                        if ( ccList != null )
                        {
                            for ( int i = 0; i < ccList.size(); i++ )
                            {
                                if ( !ccList.item(i).getName().equals("user") )
                                {
                                    custClass.add(ccList.item(i));
                                }
                            }

                            // Create new CustOption instance
                            CustomizationClass[] cc =
                                 (CustomizationClass[])custClass.toArray(
                                      new CustomizationClass[custClass.size()]);

                            CustOption custOption1 =
                                    new CustOption(
                                            new CustClassList(cc),
                                            custOption.getTransOption(),
                                            custOption.shouldUseCustConfig());

                            newTransferOptions.add(custOption1);
                        }
                        else
                        {
                            newTransferOptions.add(transferOption);
                        }
                    }
                    else
                    {
                        newTransferOptions.add(transferOption);
                    }
                }

                // Create new TransferOptions instance with the new 
                // TransferOption list.
                TransferOptions tuOptions =
                        new TransferOptions(
                             (TransferOption[])newTransferOptions.toArray(
                                new TransferOption[newTransferOptions.size()]));

                // Craete new TransferUnit instance with the new TransferOptions
                // instance and add it to the list of TransferUnit instances
                // which are the additional units that need to be processed.
                mAdditionalTransferUnitsToProcess.add(
                        TransferUnit.create(tu.getMOReference(),
                                            tuOptions,
                                            tu.shouldTransferTUDocument()));

                mTransferUnitsNotToProcess.add(tu);
            }
        }
    }


    /** {@inheritDoc} */
    public void postOperation(TransferContext  transferContext,
                              TransferUnitList transferUnitList,
                              List             docsBeingTransfered)
    {

    }


    /** {@inheritDoc} */
    public void postCommit(TransferContext  transferContext,
                           TransferUnitList transferUnitList,
                           List             docsBeingTransfered)
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


    /**
    ** Additional list of documents that should be processed (transferred).
    */
    private TransferUnitList mAdditionalTransferUnitsToProcess;
}
