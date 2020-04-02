/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples.mymusicindustry.mymusiccompany;

import java.util.Locale;
import oracle.mds.core.IsolationLevel;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.MetadataNotFoundException;
import oracle.mds.core.MetadataObject;
import oracle.mds.core.RestrictedSession;
import oracle.mds.core.SessionOptions;
import oracle.mds.cust.CustClassList;
import oracle.mds.cust.CustomizationClass;
import oracle.mds.cust.CustomizationManager;
import oracle.mds.naming.ReferenceException;
import oracle.mds.samples.mymusicindustry.mymusiccompany.cust.SiteCC;
import oracle.mds.samples.mymusicindustry.mymusiccompany.cust.UserCC;

/**
** This class illustrates how one can build a key uniquely identifying one
** customized and translated variant of a metadata object.  The key includes
** the name of the metadata object, the requested locale (as set on the
** MDSSession, and any customization layers which will be applied to the
** object, given the current environment (session properties, customization
** configuration as set on the MDS instance and/or the session, etc).
*/

public class PortalCustKeyExample extends ReadMetadataExample
{
    /**
    ** Main method, illustrates building a key uniquely identifying one
    ** customized and translated variant of a metadata object.
    */
    public static void main(String[] args)
    {
        /*
        ** Use the MDSInitializer helper class to instantiate an MDSInstance
        ** (Available in Appendix A4)
        */
        MDSInitializer  init = createMDSInitializer(args);
        MDSInstance     mds  = init.getMDSInstance();
        //
        // Get custKey using the default customization configuration as set up
        // on the MDSInstance (applies site plus user customizations)
        //
        MDSSession  sess = mds.createSession(
                               new SessionOptions(IsolationLevel.READ_COMMITTED,
                                                  null,
                                                  null),
                               null);
        PortalCustKeyExample ex = new PortalCustKeyExample();
        String key;
        // The customization classes SiteCC and UserCC will return nothing
        // at present because the site and user properties are as yet unset
        key = PortalCustKeyExample.getCustKey(ex.getMOName(), sess);
        System.out.println("custKey with no trans or cust: \n  " + key);

        // Now set the site property to "turn on" siteCC.
        // Setting it to "" causes a single unique site layer to be applied
        sess.setProperty(new SiteCC().getName(), "");
        key = PortalCustKeyExample.getCustKey(ex.getMOName(), sess);
        System.out.println("custKey with site cust: \n  " + key);

        // "Turn on" the UserCC by setting the user
        sess.setProperty(new UserCC().getName(), "fred");
        key = PortalCustKeyExample.getCustKey(ex.getMOName(), sess);
        System.out.println("custKey with site and user=fred: \n  " + key);

        //
        // Now use a session with the locale set (for translations)
        //
        sess = mds.createSession(
                             new SessionOptions(IsolationLevel.READ_COMMITTED,
                                                new Locale("fr", "FR"),
                                                null), // CustConfig override
                             null); // UserStateHandler
        key = PortalCustKeyExample.getCustKey(ex.getMOName(), sess);
        System.out.println("custKey with locale fr_FR: \n  " + key);

        sess.setProperty(new SiteCC().getName(), "");
        key = PortalCustKeyExample.getCustKey(ex.getMOName(), sess);
        System.out.println("custKey with fr_FR + site cust: \n  " + key);

        // "Turn on" the UserCC by setting the user
        sess.setProperty(new UserCC().getName(), "Fred^E.|Smith");
        key = PortalCustKeyExample.getCustKey(ex.getMOName(), sess);
        System.out.println("custKey with fr_FR + site + "
                           + "user=Fred^E.|Smith: \n  "
                           + key);
    }

    /**
    ** Creates a unique key based on the CustClass and locale the session
    ** is configured with.
    ** @return Unique key as describe above.
    */
    public static String getCustKey(String     moName,
                                    MDSSession sess)
    {
        //
        // First get the base (uncustomized, untranslated) MO by passing
        // in explicit custClassList and locale parameters as null
        //
        MetadataObject baseMO = null;
        try
        {
            baseMO = sess.getMetadataObject(moName, null, null);
        }
        catch (ReferenceException e)
        {
            throw new RuntimeException(e);
        }
        catch (MetadataNotFoundException  e)
        {
            throw new RuntimeException(e);
        }

        //
        // Now get the custClassList which would normally be applied to the
        // metadata object (i.e. which would be applied by a getMetadataObject
        // call without the custClassList and locale parameters)
        //
        CustomizationManager custMgr =
                     sess.getMDSInstance().getCustomizationManager();
        CustClassList custList = custMgr.getCustClassList(
                                       sess.getSessionOptions().getCustConfig(),
                                       baseMO);

        //
        // Build the key based on the MO name, the MDS session's locale setting,
        // and the results of executing the customization classes
        //
        StringBuffer key = new StringBuffer(100);

        // Note: if the key is to be unique only within the scope of the
        //       given MO the following line can be removed:
        key.append(moName);

        // Append the locale
        appendKeyPart(key, sess.getSessionOptions().getLocale());

        // Append the customization layers
        if ( custList != null )
        {
            int ccCount = custList.size();

            for ( int ccIndex = 0; ccIndex < ccCount; ccIndex++ )
            {
                CustomizationClass custClass = custList.item(ccIndex);
                appendKeyPart(key, custClass, baseMO, sess);
            }
        }
        return key.toString();
    }


    // Include the given locale in the key
    private static void appendKeyPart(StringBuffer key,
                                      Locale       locale)
    {
        key.append(LOCALE_SEPARATOR);
        if ( locale != null )
        {
            key.append(escape(locale.toString(), LOCALE_SEPARATOR));
        }
    }


    // Include the layers returned by the given customization class in the key
    private static void appendKeyPart(StringBuffer        key,
                                      CustomizationClass  custClass,
                                      MetadataObject      baseMO,
                                      MDSSession          sess)
    {
        String name = custClass.getName();
        RestrictedSession rsess = sess.getRestrictedSession();
        String[] vals = custClass.getValue(rsess, baseMO);
        if ( vals != null )
        {
            for ( int i = 0; i < vals.length; i++ )
            {
                key.append(CUST_LAYER_SEPARATOR);
                String layerKey;
                String val = vals[i];
                if ( val == null | val.equals("") )
                {
                    layerKey = name;
                }
                else
                {
                    layerKey = escape(name, CUST_NAME_VALUE_SEPARATOR) +
                               CUST_NAME_VALUE_SEPARATOR +
                               escape(val,  CUST_NAME_VALUE_SEPARATOR);
                }
                key.append(escape(layerKey, CUST_LAYER_SEPARATOR));
            }
        }
    }


    private static String escape(String in, char separator)
    {
        // Escape the separator if it's not alphabetic in case it's
        // a special regular expression character like '^'
        String sep = Character.toString(separator);
        String regExp = Character.isLetter(separator) ?
                         sep :
                         "\\" + separator;
        return in.replaceAll(regExp, sep+sep);
    }


    private static final char LOCALE_SEPARATOR = ':';
    private static final char CUST_LAYER_SEPARATOR = '^';
    private static final char CUST_NAME_VALUE_SEPARATOR = '|';
}
