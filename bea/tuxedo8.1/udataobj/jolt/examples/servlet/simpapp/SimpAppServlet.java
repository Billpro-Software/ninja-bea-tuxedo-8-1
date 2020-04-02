package examples.jolt.servlet.simpapp;

import bea.jolt.pool.servlet.*;
import bea.jolt.pool.ApplicationException;
import bea.jolt.pool.SessionPoolException;
import bea.jolt.pool.ServiceException;

import java.util.Properties;
import java.util.Hashtable;
import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;

/**
 * This example demonstrates how a Servlet may connect to Tuxedo 
 * and call upon one of its services; it should be invoked from the 
 * <i>simpapp.html</i> file. The servlet creates a session pool
 * manager at initialization, which is used to obtain a session when the 
 * <tt>doPost()</tt> method is invoked. This session is used to connect to a service
 * in Tuxedo with a name described by the posted "SVCNAME" argument. In this 
 * example the service is called "TOUPPER", which transposes the posted 
 * "STRING" argument text into uppercase, and returns the result. This is 
 * returned to the client browser within some generated HTML.
 * THIS IS SOURCE CODE PUBLISHED FOR DEMONSTRATION PURPOSES
 *
 * @author Copyright (c) 1999 BEA Systems, Inc.  All rights reserved.
 */
public class SimpAppServlet extends HttpServlet {

  /**
   * Private variable to hold the pool manager object.
   */
  private ServletSessionPoolManager b_mgr;
  
  /**
   * Initializes the servlet.  The session pool manager and the
   * simpapp session pool is established here.  The properties of
   * the session pool is specified through an external property
   * file whose path comes from the servlet initial parameter "properties".
   * 
   * @param config            Servlet configuration
   * @exception               ServletException if the servlet fails
   */
  public void init(ServletConfig config) throws ServletException {
    super.init(config);
    
    try {
      // Create a session pool and get the session pool manager through
      // a property file.
      String path = config.getServletContext().getRealPath("/") +
		    "simpapp.properties";
      Properties prop = ServletPoolManagerConfig.load(path);
      if (prop == null)
	throw new ServletException(path + " not found");
      ServletPoolManagerConfig.startup(prop);
      
      b_mgr = ServletPoolManagerConfig.getSessionPoolManager();
    }
    catch (Exception e) {
      throw new ServletException(e.toString());
    }
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
   * <dt>"SVCNAME"<dd>The name of the service to be invoked in Tuxedo.
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
    // Get the "simpapp" session pool
    ServletSessionPool session = (ServletSessionPool)
      b_mgr.getSessionPool("simpapp");
    if (session == null) {
      out.println("The servlet failed to obtain a SessionPool for simpapp. "+
                  "<br>"+
                  "Possibly the Tuxedo server is not running, "+
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
}



