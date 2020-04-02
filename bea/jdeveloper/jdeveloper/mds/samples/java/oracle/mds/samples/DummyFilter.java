/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */
package oracle.mds.samples;

import java.io.IOException;

import java.lang.reflect.Method;

import java.util.Locale;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

import oracle.mds.core.IsolationLevel;
import oracle.mds.core.MDSInstance;
import oracle.mds.core.MDSSession;
import oracle.mds.core.SessionOptions;
import oracle.mds.exception.MDSRuntimeException;
import oracle.mds.jsp.JSPHelper;
import oracle.mds.samples.apps.cust.AppsCustomizationClass;
import oracle.mds.samples.apps.cust.CustContextImpl;
import oracle.mds.samples.apps.cust.CustomizationContext;


/**
** This filter creates a MDSSession.
** It performs the same task as the ADF Filter, but in a much simpler form.
** NOTE: This is not the recommended way to get an MDSSession, which is
** <code>
** <br/> ADFContext context = ADFContext.getCurrent();
** <br/> MDSSession session = (MDSSession)context.getMDSSessionAsObject();
** </code>
*/
/*
** <!--------------------------------------------------------------------------
** MODIFIED (MM/DD/YY)
** dklein    10/10/08 - Add comment to discourage usage
** dklein    07/10/07 - Get ServletContext
** dklein    03/13/07 - Get instance from ADFContext
** dklein    02/07/07 - Add mInstanceName - prevent two apps using this filter
**                      in the same OC4J sharing same instance
** cxlewis   01/05/06 - configurable id changes 
** cbarrow   12/20/05 - Stop using deprecated MDSInstance.createSession 
** cxlewis   06/07/05 - #(4414292) - use path relative to application
** cxlewis   06/02/05 - Created.
*/

public class DummyFilter implements Filter
{
    // Javadoc inhertited from Filter
    /** {@inheritDoc} */
    public void doFilter(ServletRequest req,
               ServletResponse res,
               FilterChain chain)
               throws IOException, ServletException
    {
        String                     site = "";
        String                     user = "";
        CustomizationContext       custContext;
        Locale                     locale;

        site = req.getParameter("site");
        user = req.getParameter("user");

        /* Create an Apps-style customization context */
        custContext = new CustContextImpl();

        if ( site != "" )
        {
            custContext.setProperty(CustomizationContext.SITE, site);
        }
        if ( user != "" )
        {
            custContext.setProperty(CustomizationContext.USER, user);
        }

        locale = new Locale("en", "US");

        /*
        ** get the MDSInstance, create a session and store it on the JSPHelper
        */
        MDSInstance instance;

        /*
        ** To avoid a circular build dependency on ADFShare use introspection.
        */
        try
        {
            Thread cThread = Thread.currentThread();
            ClassLoader cl = cThread.getContextClassLoader();
            Class    adfContext =
                     Class.forName("oracle.adf.share.ADFContext",
                                   true,
                                   cl);
            Object   adf;
            Class[]  argTypes = new Class[] {};
            Object[] arguments = new Object[] {};
            Method   m;

            /*
            ** ADFContext is abstract, so we can't just go diving in
            ** and call getMDSInstanceAsObject().
            ** First we call static getCurrent()
            */
            m = adfContext.getMethod("getCurrent", argTypes);
            adf = m.invoke(null, arguments);

            /* now that we've got it, execute getMDSInstanceAsObject() */
            m  = adfContext.getMethod("getMDSInstanceAsObject", argTypes);
            instance = (MDSInstance)m.invoke(adf, arguments);
        }
        catch (Exception e)
        {
            throw new MDSRuntimeException(e);
        }

        MDSSession sess = createMDSSession(instance, custContext, locale);
        JSPHelper.setMDSSession(sess);
        
        System.out.println("DummyFilter - created MDSSession: user="
                           + user + ", site=" + site);
        chain.doFilter(req, res);
    }


    // Javadoc inhertited from Filter
    /** {@inheritDoc} */
    public void destroy()
    {
        /* Nothing to do */
    }


    // Javadoc inhertited from Filter
    /** {@inheritDoc} */
    public void init(FilterConfig p0) throws ServletException
    {
        mServletContext = p0.getServletContext();
    }


    /**
    ** Creates the MDSSession for a request.
    ** @param mds             the MDS mInstance
    ** @param custContext     the customization context
    ** @param locale          the locale
    */
    private MDSSession createMDSSession(MDSInstance mds,
                                        CustomizationContext custContext,
                                        Locale locale)
    {
        SessionOptions opts = new SessionOptions(IsolationLevel.READ_COMMITTED,
                                                 locale, null, null, null, null,
                                                 mServletContext);
        MDSSession     sess = mds.createSession(opts, null);

        sess.setProperty(AppsCustomizationClass.CUSTOMIZATION_CONTEXT,
                            custContext);
        return sess;
    }
    
    private ServletContext mServletContext;
}
