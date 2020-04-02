/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.apps.cust;

import oracle.mds.cust.CustClassList;
import oracle.mds.cust.CustomizationClass;

/**
** A CustClassList for Apps.
**
** This class will provide a global list of CustomizationsClasses (CCs)
** corresponding to the customization types in 9.0.5.
** As Apps customization types are global (i.e. are the same for all MOs)
** the list is stored as a static list.
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** ntriggs   01/28/05 - ntriggs_generic_cust
** ntriggs   09/17/04 - Created.
** --------------------------------------------------------------------------->
*/
public class AppsCustClassList extends CustClassList
{
    //--------------------------------------------------------------------------
    // Constructors
    //--------------------------------------------------------------------------
    /**
    ** Create a CustClassList containing the Apps customization types.
    */
    public AppsCustClassList()
    {
        /*
        ** Create a global, static list of CustClasss
        */
        super(APPS_CUST_CLASS_LIST);
    }

    private static final CustomizationClass[] APPS_CUST_CLASS_LIST =
                                      new CustomizationClass[]{new FunctionCC(),
                                      new VerticalizationCC(),
                                      new LocalizationCC(),
                                      new SiteCC(),
                                      new OrgCC(),
                                      new ResponsibilityCC(),
                                      new UserCC(),
                                      new PortalCC()};
}
