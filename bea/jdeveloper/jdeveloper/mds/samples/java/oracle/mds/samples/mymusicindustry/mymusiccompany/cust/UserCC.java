/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.mymusicindustry.mymusiccompany.cust;

import oracle.mds.core.MetadataObject;
import oracle.mds.core.RestrictedSession;
import oracle.mds.cust.CacheHint;
import oracle.mds.cust.CustomizationClass;


public class UserCC extends CustomizationClass
{
    /** {@inheritDoc} */
    public CacheHint getCacheHint()
    {
        return CacheHint.USER;
    }


    /** {@inheritDoc} */
    public String getName()
    {
        return "user";
    }


    /** {@inheritDoc} */
    public String[] getValue(RestrictedSession rs,
                             MetadataObject metadataObject)
    {
        String val = (String)rs.getProperty(getName());
        return ( val == null ? null : new String[]{val} );
    }
}
