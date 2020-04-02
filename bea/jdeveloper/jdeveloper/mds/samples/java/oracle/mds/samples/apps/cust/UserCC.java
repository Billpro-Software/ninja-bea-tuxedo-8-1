/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.apps.cust;

import java.util.ArrayList;

import oracle.mds.core.MetadataObject;
import oracle.mds.core.RestrictedSession;
import oracle.mds.cust.CacheHint;

/**
** A Customization Class which retrieves the value of User from the
** customization context, plus the 2 seeded users.
** Customization layers will have cache hint SESSION.
** <p>
** To support perInstance customizations, the returned base reference and
** value will take into account the customization context properties
** "baseMO" and "perInstance" accordingly.
*/
/* <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** cbarrow   05/09/05 - Move to revised MDS Core API 
** cbarrow   03/07/05 - Move CacheHint out of CustomizationClass 
** ntriggs   01/28/05 - ntriggs_generic_cust
** ntriggs   09/17/04 - Created.
** --------------------------------------------------------------------------->
*/
public class UserCC extends AppsCustomizationClass
{

    /**
    ** {@inheritDoc}
    */
    public CacheHint getCacheHint()
    {
        return CacheHint.USER;
    }


    /**
    ** {@inheritDoc}
    */
    public String getName()
    {
        return "user";
    }


    /**
    ** Gets the value of this customization class.
    ** <p>
    ** This will be null if no user is set on the customization context, or it
    ** will be 3 values coresponding to the user on the context plus the 2
    ** seeded users.
    ** @param sess - the MDS session (in restricted form)
    ** @param mo   - the metadata object being customized
    ** @return an array of values
    */
    public String[] getValue(RestrictedSession sess, MetadataObject mo)
    {
        String val = getCustContextValue(sess, this.getName());
        if ( val == null )
        {
            return null;
        }

        ArrayList results = new ArrayList(NO_VALUES);

        CustomizationContext cctx = (CustomizationContext)sess.getProperty(
                                AppsCustomizationClass.CUSTOMIZATION_CONTEXT);
        String perInstance = (String)cctx.getProperty("perInstance");
        if ( perInstance == null )
        {
            perInstance = "";
        }
        else
        {
            perInstance = "/perInstance/" + perInstance;
        }

        return new String[] {val + perInstance,
                             "seededuser" + perInstance,
                             "seededdeveloper" + perInstance};

    }

    /**
    ** If this customization class returns any values there will be 3: one for
    ** the user plus 1 each for the 2 seeded users.
    */
    private static final int NO_VALUES = 3;
}
