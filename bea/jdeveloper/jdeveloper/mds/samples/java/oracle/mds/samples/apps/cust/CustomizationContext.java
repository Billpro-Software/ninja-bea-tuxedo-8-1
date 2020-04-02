/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.apps.cust;


/**
** An interface that encapsulates the user's customization layer types and
** layer values. This information is used as criteria when querying up the
** customization metadata. MDS supports the following levels of customization
** in increasing order of precedence
** <p>
** <ul>
**    <li> Function: Allows the customization of form functions. </li>
**    <li> Verticalization: Allows a verticalization team to make
**         verticalization-level customizations in an application before
**         delivering the application to customers, i.e. to an automotive
**         industry. </li>
**    <li> Localization: Allows a localization team to make customizations for
**         a designated localization of the application. </li>
**    <li> Site: Allows customization of a single installation of the
**         application. </li>
**    <li> Org: Allows customization at an organizational or business unit
**         level. An org could be a division of a company, or even a complete
**         company. </li>
**    <li> Responsibility: Allows customization at a specific level of
**         authority, for example a payroll manager. </li>
**    <li> User: Allows customizations for an individual user. Each user can
**         have multiple views of user customization. </li>
**    <li> Seeded User: Used exclusively by Apps developers. This customization
**         is available to all users, appearing under the list of customization
**         views. However, it cannot be altered by a user. Instead, the seeded
**         view must be duplicated and the duplicate itself may be
**         altered. </li>
**    <li> Portlet: Allows the customization of metadata that is displayed in a
**         portlet.  </li>
*/
/*
** <!--------------------------------------------------------------------------
** MODIFIED    (MM/DD/YY)
** ntriggs      01/28/05  - ntriggs_generic_cust
** ntriggs      01/26/05  - Copy to samples package as will no longer be part
**                          of MDS
** ntriggs      11/04/04  - Refactor AttributeKey
** sudsrini     09/26/03  -  Remove unwanted imports, organize imports
** kaalvare     09/10/03  -  Added new method getLayers
** sudsrini     05/14/03  - #(2947823) Create new CustContext for invalidation
** kaalvare     01/02/03  -  Modify SEEDED_DEVELOPER, SEEDED_CUSTOMER constants
** kaalvare     10/14/02  -  Add SEEDED_DEVELOPER and SEEDED_CUSTOMER constants
** sudsrini     10/03/02  -  Change getKey to return AttributeKey
** kaalvare     08/29/02  -  Added GET_LAYER constant.
** kaalvare     08/28/02  -  Added PORTLET, GET_SEEDED. Removed extra constants.
**                           Changed layer properties from Object to String.
** sudsrini     05/02/02  -  Remove extra constants
** kaalvare     05/01/02  -  Modify customization level property names
** ssaxena      01/29/02  -  Creation
** --------------------------------------------------------------------------->
*/
public interface CustomizationContext
{

    /**
    ** Property ID for Function level customizations. Its value should be
    ** a Function Name (String).
    */
    public static final String FUNCTION           = "function";

    /**
    ** Property ID for Localization level customizations. Its value should be
    ** a Localization Code (String).
    */
    public static final String LOCALIZATION       = "localization";

    /**
    ** Property ID for Organization level customizations. Its value should be
    ** a Org ID (String).
    */
    public static final String ORG                = "org";

    /**
    ** Property ID for Portlet level customizations. Its value should be
    ** a Reference Path (String) which identifies the portlet instance.
    */
    public static final String PORTLET            = "portlet";

    /**
    ** Property ID for Responsibility level customizations. Its value should be
    ** a Responsibility ID (String).
    */
    public static final String RESPONSIBILITY     = "responsibility";

    /**
    ** Property ID for Site level customizations. Its value should be
    ** a Site ID (String).
    */
    public static final String SITE               = "site";

    /**
    ** Property ID for User level customizations. Its value should be
    ** a User ID (String), SEEDED_CUSTOMER, or SEEDED_DEVELOPER.
    */
    public static final String USER               = "user";

    /**
    ** Property ID for Verticalization level customizations. Its value should be
    ** a Verticalization ID (String).
    */
    public static final String VERTICALIZATION    = "verticalization";

    /**
    ** Property ID used in determining whether a single customization layer
    ** should be loaded, or all customization layers. Its value should be null
    ** if all layers should be retrieved. If a single layer should be retrieved,
    ** the PropertyID of that layer should be the value.
    */
    public static final Object GET_SINGLE_LAYER = new Object();

    /**
    **   Property value for USER, used to indicate a seeded user customization
    **   that is created at the customer site.
    */
    public static final String SEEDED_CUSTOMER  = "seededcustomer";

    /**
    **   Property value for USER, used to indicate a seeded user customization
    **   that is created in-house by a developer.
    */
    public static final String SEEDED_DEVELOPER = "seededdeveloper";


    /**
    **  Gets a customization layer value for the corresponding type.
    **
    **  @return String  layer value
    */
    public String getLayerValue(String layerType);


    /**
    ** Gets the customization key that is based on all the SHARED customization
    ** layers (such as org id, responsiblity id, site, etc).
    **
    ** @return String   representation of the shared customizations key
    */
    public String getKey();


    /**
    ** Returns the value of the specified property.
    **
    ** @param  propid    Property identifier
    ** @return Object    value of the property identified by the key
    */
    public Object getProperty(Object    propid);


    /**
    ** Gets the customization key that is based on the USER customization
    ** layer settings (like USER or PORTLET).
    **
    ** @return String   representation of the shared customizations key
    */
    public String getUserKey();


    /**
    ** Sets the value of the specified property.
    **
    ** @param propid    Property id
    ** @param value     Property value
    */
    public void setProperty(Object    propid, Object    value);


    /**
    ** An array of objects that contains Customization Layer Types in
    ** increasing order.
    */
    static final Object[]     CUST_LAYERS = new Object[]
    {
        CustomizationContext.FUNCTION,
        CustomizationContext.VERTICALIZATION,
        CustomizationContext.LOCALIZATION,
        CustomizationContext.SITE,
        CustomizationContext.ORG,
        CustomizationContext.RESPONSIBILITY,
    };
}
