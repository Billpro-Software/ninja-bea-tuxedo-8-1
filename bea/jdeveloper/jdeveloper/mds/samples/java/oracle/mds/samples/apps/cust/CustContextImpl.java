/* Copyright (c) 2001, 2008, Oracle and/or its affiliates. All rights reserved.*/
package oracle.mds.samples.apps.cust;

import java.util.HashMap;

/**
** CustContextImpl is an ArrayMap implementation of CustomizationContext.
*/
/* <!--------------------------------------------------------------------------
** MODIFIED    (MM/DD/YY)
** erwang       09/16/08   - Clean up internal references in comments 
** ntriggs      07/11/05   - Fix coding violations 
** gnagaraj     07/09/05   - Coding standards compliance
** ntriggs      01/28/05   - ntriggs_generic_cust
** ntriggs      01/26/05  -  Created cut-down version im sample package
** ntriggs      11/04/04  -  Refactor AttributeKey
** cbarrow      05/14/04  -  Set mUserKey to null in setProperty as well as mKey
** cbarrow      02/13/04  -  Add clone method, implement Cloneable
** kaalvare     09/10/03  -  Add new constructor and getLayers method
** cbarrow      05/27/03  -  Javadoc improvements
** sudsrini     04/29/03  -  Be resilient to the existence of
**                           underscores in layer values
** cbarrow      01/30/03  -  Make getPrecedence static
** sudsrini     10/31/02  -  Get and set methods for User Cust Flags
** kaalvare     10/22/02  -  Check whether Cust Key is null
** sudsrini     10/01/02  -  Store Cust Key as member variable
** kaalvare     08/29/02  -  Changed internal structure from ArrayMap to HashMap
** sudsrini     08/29/02  -  Added getPrecedence
** sudsrini     04/30/02  -  Customization support
** mjakobis     02/05/02  -  Creation.
** --------------------------------------------------------------------------->
** @see java.util.HashMap
*/
public class CustContextImpl implements CustomizationContext, Cloneable
{

    //-------------------------------------------------------------------------
    // Public Methods
    //-------------------------------------------------------------------------
    /**
    ** Constructor taking initial number of layers.
    ** @deprecated
    */
    public CustContextImpl(int level)
    {
        this();
    }



    /**
    ** Constructor taking no customization layers.
    */
    public CustContextImpl()
    {
        mMap      = new HashMap(10);
        mLayerMap = new HashMap(10);
    }


    /**
    ** Returns a new CustContextImpl which is a copy of this one, with all Maps
    ** (and subsidiary Maps and MElementLists) cloned so that the new
    ** ElementData can be updated without affecting the old one.  Note that we
    ** don't clone the child MElements.
    ** @return Object   A copy of this ElementData.
    */
    public Object clone()
    {
        CustContextImpl newOne = null;
        try
        {
            newOne = (CustContextImpl)super.clone();
        }
        catch ( CloneNotSupportedException e )
        {
            //Cannot happen since we extend Object and implement Cloneable
            throw new RuntimeException(e);
        }
        //
        // We now have a "shallow" clone.  Reset all the Map member variables
        // to cloned Maps, since the original is (unfortunately) mutable.
        //

        newOne.mLayerMap = (HashMap)((HashMap)mLayerMap).clone();
        return newOne;
    }


    /**
    ** Given a customization Layer Name, this returns its precedence.
    ** See Valid custTypes in CustomizationContext
    ** @param custType   Customization Layer Name
    **
    ** @return Integer representing the precendence of the customization
    **         layer. Larger the value of the integer returned, the higher the
    **         precedence. Returns -1 if an invalid custType is provided.
    */
    public static int getPrecedence(Object custType)
    {
        int level = -1;
        if ( FUNCTION.equals(custType) )
        {
            level = 1;
        }
        else if ( VERTICALIZATION.equals(custType) )
        {
            level = 2;
        }
        else if ( LOCALIZATION.equals(custType) )
        {
            level = 3;
        }
        else if ( SITE.equals(custType) )
        {
            level = 4;
        }
        else if ( ORG.equals(custType) )
        {
            level = 5;
        }
        else if ( RESPONSIBILITY.equals(custType) )
        {
            level = 6;
        }
        return level;
    }


    //-------------------------------------------------------------------------
    // Interface - CustomizationContext
    //-------------------------------------------------------------------------

    /** {@inheritDoc} */
    public String getLayerValue(String layerType)
    {
        return (String)mLayerMap.get(layerType);
    }


    /**
    ** Gets the customization key that is based on various properties such
    ** as org id, repsonsiblity id, etc. Returns null if the customization
    ** context has not yet been set.
    **
    ** @return String  representation of the customization key
    */
    public String getKey()
    {
        /*
        ** ### Handling of null case is inefficient - we test all the layers
        ** ### each time
        */
        if ( mKey == null )
        {
            StringBuffer sBuff        = new StringBuffer(32);
            String       funcName     = getLayerValue(FUNCTION);
            String       vertId       = getLayerValue(VERTICALIZATION);
            String       localCode    = getLayerValue(LOCALIZATION);
            String       siteId       = getLayerValue(SITE);
            String       orgId        = getLayerValue(ORG);
            String       respId       = getLayerValue(RESPONSIBILITY);
            if ( funcName  == null &&
                 vertId    == null &&
                 localCode == null &&
                 siteId    == null &&
                 orgId     == null &&
                 respId    == null )
            {
                return mKey;
            }
            /*
            ** If any of the properties contain a '^', replace all occurrences
            ** with a '#', since the caret is treated as a delimiter between
            ** layer values
            */
            if ( funcName != null )
            {
                funcName = funcName.replace(OLD_CHAR, NEW_CHAR);
            }
            if ( vertId != null )
            {
                vertId = vertId.replace(OLD_CHAR, NEW_CHAR);
            }
            if ( localCode != null )
            {
                localCode = localCode.replace(OLD_CHAR, NEW_CHAR);
            }
            if ( siteId != null )
            {
                siteId = siteId.replace(OLD_CHAR, NEW_CHAR);
            }
            if ( orgId != null )
            {
                orgId = orgId.replace(OLD_CHAR, NEW_CHAR);
            }
            if ( respId != null )
            {
                respId = respId.replace(OLD_CHAR, NEW_CHAR);
            }
            /*
            ** Finally, now that we have ensured that there are no clashes,
            ** construct the concatenated key
            */
            sBuff.append(funcName);
            sBuff.append(OLD_CHAR);
            sBuff.append(vertId);
            sBuff.append(OLD_CHAR);
            sBuff.append(localCode);
            sBuff.append(OLD_CHAR);
            sBuff.append(siteId);
            sBuff.append(OLD_CHAR);
            sBuff.append(orgId);
            sBuff.append(OLD_CHAR);
            sBuff.append(respId);
            mKey = sBuff.toString();
        }
        return mKey;
    }


    /**
    ** Returns the value of the specified property.
    ** If propid is null, return null.
    **
    ** @param  propid    Property identifier
    ** @return Object    value of the property identified by the key
    */
    public Object getProperty(Object propid)
    {
        if ( propid != null )
        {
            return mMap.get(propid);
        }
        return null;
    }


    /**
    ** Returns the user Customizable Flag.
    ** If false, user customized values are not returned by MDS
    ** @return User customizable flag.
    */
    public final boolean getUserCustFlag()
    {
        return mUserCustFlag;
    }


    // Javadoc inherited from interface
    /** {@inheritDoc} */
    public String getUserKey()
    {
        /*
        ** ### Handling of null case is inefficient - we test all the layers
        ** ### each time
        */
        if ( mUserKey == null )
        {
            StringBuffer sBuff        = new StringBuffer(32);
            String       portlet     = getLayerValue(PORTLET);
            String       user       = getLayerValue(USER);
            if ( portlet  == null &&
                 user    == null )
            {
                return mUserKey;
            }
            /*
            ** If any of the properties contain a '^', replace all occurrences
            ** with a '#', since the caret is treated as a delimiter between
            ** layer values
            */
            if ( portlet != null )
            {
                portlet = portlet.replace(OLD_CHAR, NEW_CHAR);
            }
            if ( user != null )
            {
                user = user.replace(OLD_CHAR, NEW_CHAR);
            }
            /*
            ** Finally, now that we have ensured that there are no clashes,
            ** construct the concatenated key
            */
            sBuff.append(user);
            sBuff.append(OLD_CHAR);
            sBuff.append(portlet);
            mUserKey = sBuff.toString();
        }
        return mUserKey;
    }


    /**
    ** Sets the value of the specified property.
    ** If propid is null, setProperty silently fails.
    **
    ** @param propid    Property id
    ** @param value     Property value
    */
    public void setProperty(Object propid, Object value)
    {
        if ( propid != null)
        {
            mMap.put(propid, value);
            mKey     = null;    // these line should be removed once
            mUserKey = null;    // customization layers can only be set
                                // on the constructor
        }
        // Save layer values in mLayerMap, for backwards compatibility. This
        // should be removed once the framework makes the necessary changes
        // to set the customization layers on the constructor.
        mLayerMap.put(propid, value);
    }


    /**
    ** Sets the user Customizable Flag.
    ** If false, user customized values are not returned by MDS
    */
    public final void setUserCustFlag(boolean value)
    {
        mUserCustFlag = value;
    }


    //-------------------------------------------------------------------------
    // Private Member Variables
    //-------------------------------------------------------------------------
    private HashMap              mMap;
    private HashMap              mLayerMap;
    private String               mKey;
    private String               mUserKey;
    private boolean              mUserCustFlag    = true;


    //-------------------------------------------------------------------------
    // Private Static Member Variables
    //-------------------------------------------------------------------------
    private static final   char OLD_CHAR  = '^';
    private static final   char NEW_CHAR  = '#';

}
