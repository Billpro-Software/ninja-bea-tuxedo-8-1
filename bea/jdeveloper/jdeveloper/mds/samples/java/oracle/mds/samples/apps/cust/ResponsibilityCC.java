/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.apps.cust;

import oracle.mds.cust.CacheHint;

/**
** A Customization Class which retrieves the value of Responsibility from the
** customization context. Customization layers will have cache hint
** ALL_USERS.
** <p>
** To support perInstance customizations, the returned base reference and
** value will take into account the customization context properties
** "baseMO" and "perInstance" accordingly.
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** mafox     04/20/06 - JOC integration (make cache hint MULTI_USER) 
** cbarrow   03/07/05 - Move CacheHint out of CustomizationClass 
** ntriggs   01/28/05 - ntriggs_generic_cust
** ntriggs   09/17/04 - Created.
** --------------------------------------------------------------------------->
*/
public class ResponsibilityCC extends AppsCustomizationClass
{

    /**
    ** {@inheritDoc}
    */
    public CacheHint getCacheHint()
    {
        return CacheHint.MULTI_USER;
    }


    /**
    ** {@inheritDoc}
    */
    public String getName()
    {
        return "responsibility";
    }

}
