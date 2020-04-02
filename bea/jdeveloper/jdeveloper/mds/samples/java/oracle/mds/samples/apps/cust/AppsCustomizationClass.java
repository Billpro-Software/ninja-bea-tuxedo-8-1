/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.apps.cust;

import oracle.mds.core.MetadataObject;
import oracle.mds.core.RestrictedSession;
import oracle.mds.cust.CustomizationClass;
import oracle.mds.naming.MOName;
import oracle.mds.naming.ReferenceException;


/**
** A Customization Class which retrieves the named value from the
** customization context.
** <p>
** To support perInstance customizations, the returned base reference and
** value will take into account the customization context properties
** "baseMO" and "perInstance" accordingly.
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** cbarrow   01/03/06 - Accomodate changed return type of getBaseRef and comment
**                      it out for now until we figure out if we can support
**                      clients overriding getBaseRef.
** cbarrow   05/18/05 - Move to revised MDS Core API 
** cbarrow   03/10/05 - Avoid NPE when CustCtx not set on MDSCtx 
** ntriggs   01/28/05 - ntriggs_generic_cust
** ntriggs   09/17/04 - Created.
** --------------------------------------------------------------------------->
*/
public abstract class AppsCustomizationClass extends CustomizationClass
{
    //--------------------------------------------------------------------------
    // Public Methods
    //--------------------------------------------------------------------------
    /*
    ** Return a reference relative to which the CL is located. To support
    ** per-instance customizations, any baseMO stored as a session property is
    ** used in place of the default.
    **
    ** @param sess   - the MDS session
    ** @param baseMO - the metadata object
    ** @return - the reference to locate the CL relative to
    */
    /*
    ** NOTE: Commenting out for now until MDS can support overriding of
    **    of {@link oracle.mds.cust.CustomizationClass#getBaseRef getBaseRef}.
    */
/*
    public MOName getBaseRef(RestrictedSession sess,
                             MetadataObject baseMO)
    {
        String val = getCustContextValue(sess, "baseMO");

        if ( val == null )
        {
            return super.getBaseRef(sess, baseMO);
        }
        else
        {
            MOName baseMOName = null;
            try
            {
                baseMOName = (MOName)MOName.create(val);
            }
            catch (ReferenceException e)
            {
                throw new RuntimeException(e);
            }
            return baseMOName;
        }
    }
*/

    /**
    ** Return the value of this CC. To support per-instance customizations,
    ** if the property "perInstance" is set on the customization context,
    ** its value is added into the retun value.
    **
    ** @param sess   - the MDS session
    ** @param baseMO - the metadata object
    ** @return - the value of this CC
    */
    public String[] getValue(RestrictedSession sess, MetadataObject baseMO)
    {
        String val = getCustContextValue(sess, this.getName());
        if ( val == null )
        {
            return null;
        }

        CustomizationContext cctx = (CustomizationContext)sess.getProperty(
                                AppsCustomizationClass.CUSTOMIZATION_CONTEXT);
        String perInstance = (String)cctx.getProperty("perInstance");
        if ( perInstance != null )
        {
            if ( val.equals("") )
            {
                val = "perInstance/" + perInstance;
            }
            else
            {
                val = val + "/perInstance/" + perInstance;
            }
        }

        return new String[] {val};
    }

    //--------------------------------------------------------------------------
    // Protected Methods
    //--------------------------------------------------------------------------
    /**
    ** Internal method to return the value of the named value in the
    ** MDS customization context.
    **
    ** @param sess - the MDS session
    ** @param name - the name of the value on the context
    ** @return - the value on the customization context for this name
    */
    protected static String getCustContextValue(RestrictedSession sess,
                                                String name)
    {
        CustomizationContext cctx = (CustomizationContext)sess.getProperty(
                                AppsCustomizationClass.CUSTOMIZATION_CONTEXT);
        if ( cctx == null )
        {
            return null;
        }
        else
        {
            return (String)cctx.getProperty(name);
        }
    }

    public static final String CUSTOMIZATION_CONTEXT = "custContext";

}
