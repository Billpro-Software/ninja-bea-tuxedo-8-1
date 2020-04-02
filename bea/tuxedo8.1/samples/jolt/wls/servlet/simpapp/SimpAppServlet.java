/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
package examples.jolt.servlet.simpapp;

import bea.jolt.pool.servlet.weblogic.PoolManagerStartUp;
import bea.jolt.pool.servlet.*;
import bea.jolt.pool.ApplicationException;
import bea.jolt.pool.SessionPoolException;
import bea.jolt.pool.ServiceException;
import bea.jolt.pool.SessionPoolManager;

import java.util.Hashtable;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.naming.*;
/*import weblogic.jndi.*; */

/**
 * This example demonstrates how a WebLogic Servlet may connect to TUXEDO 
 * and call upon one of its services; it should be invoked from the 
 * <i>simpapp.html</i> file. The servlet creates a session pool
 * manager, which is used to obtain a session when the 
 * <tt>doPost()</tt> method is invoked. This session is used to connect to a service
 * in TUXEDO with a name described by the posted "SVCNAME" argument. In this 
 * example the service is called "TOUPPER", which transposes the posted 
 * "STRING" argument text into uppercase, and returns the result. This is 
 * returned to the client browser within some generated HTML.
 * THIS IS SOURCE CODE PUBLISHED FOR DEMONSTRATION PURPOSES
 *
 * @author Copyright (c) 1998-2000 BEA Systems, Inc.  All rights reserved.
 */
public class SimpAppServlet extends HttpServlet {

  /**
   * Private variable to hold the 
   * pool manager object.
   */
  private ServletSessionPoolManager b_mgr = (ServletSessionPoolManager) SessionPoolManager.poolmgr;
  
  /**
   * Initializes the servlet.  The session pool manager and the
   * simpapp session pool have been established during the startup.
   * 
   * @param config            Servlet configuration
   * @exception               ServletException if the servlet fails
   */
  public void init(ServletConfig config) throws ServletException {

    super.init(config);
  }
  
  /**
   * Destroys this servlet. The ServletSessionPoolManager
   * resource is deallocated.
   */
  public void destroy() {
    b_mgr = null;
  }
  
  /**
   * Implements the HttpServlet <tt>doPost()</tt> method. 
   * This method expects POSTed arguments for:
   * <dl>
   * <dt>"SVCNAME"<dd>The name of the service to be invoked in TUXEDO.
   * <dt>"STRING"<dd>The text to be transposed to uppercase. 
   * </dl> 
   * 
   * <p> See the provided simpapp.html for the HTML form
   * used to submit the data. 
   */
  public void doPost(HttpServletRequest req, HttpServletResponse resp)
       throws ServletException, IOException
  {
    ServletResult result;
    ServletOutputStream out = resp.getOutputStream();
    
    out.println("<html><head><title>Jolt SimpApp Example Response</title></head>");
    out.println("<body><font face=\"Helvetica\">" +
                "<h2><font color=#DB1260>" + 
                "This is the response from the SimpAppServlet:" +
                "</font></h2>");

    // Get the "demojoltpool" session pool
    ServletSessionPool session = (ServletSessionPool)
      b_mgr.getSessionPool("demojoltpool");

    if (session == null) {
      out.println("The servlet failed to obtain a SessionPool for simpapp. "+
                  "<br>"+
                  "Possibly the TUXEDO server is not running, "+
                  "or there is a configuration problem."+
                  "</font></body></html>");
      out.close();
      return;
    }
    
    String svcnm[] = req.getParameterValues("SVCNAME");
    
    // Invoke a service and get the result.  Process the
    // template with input and result if there is no error.
    try {
      result = session.call(svcnm[0], req);
      
      // No error; present the result page.
      out.println("svcnm[] = " + svcnm[0]);
      out.println("The simpapp sevice was successfully called, and "+
                  "responded with the output string: ");
      out.println("<p><center><font size=+1><b>"+
                  result.getValue("STRING", "")+
                  "</b></font></center><p><hr width=80%>");
    }
    catch (SessionPoolException e) {
      // All sessions are busy.
      out.println("Your request cannot be completed at this moment.\n"+
                  "<p>Diagnostic Message is: "+e.getMessage()+"<p>\n"+
                  "<font color=blue>Possible reasons:<br></font><ul>\n"+
                  "<li>No sessions are available\n"+
                  "<li>The session pool is suspended\n"+
                  "<li>The session pool is shutdown</ul>\n"+
                  "<p>Please resubmit your request later.");
    }
    catch (ServiceException e) {
      // There is a Service Exception.
      out.println("<dl><dt>Service exception</dt>"+
                  "<dd>Error message:"+e.getMessage()+
                  "<p>Error number:"+e.getErrno()+
                  "</dl>");
    }
    catch (ApplicationException e) {
      // There is an application error.
      result = (ServletResult) e.getResult();
      
      out.println("<h3>Application error</h3>\n"+
                  "<p>Application code is "+result.getApplicationCode());
    }
    catch (Exception e) {
      out.println("<h3>Unexpected exception</h3>"+
                  "<p>Exception is "+
                  "<br><font face=\"Courier New\" size=-1"+e+"</font>");
    }
    
    out.println("</font></body></html>\n");
    out.close();
  }
  
  /**
   * Implements the <tt>doGet</tt> HttpServlet method. This simply
   * invokes the <tt>doPost</tt> method.
   */
  public void doGet(HttpServletRequest req, HttpServletResponse resp)
       throws ServletException, IOException
  {
    doPost(req, resp);
  }

/*  public void service(HttpServletRequest req, HttpServletResponse res)
        throws IOException
  {
    PrintWriter out  = res.getWriter();

    out.flush();
    out.println("<title> SimpAppServlet </title>");
  } */
}
