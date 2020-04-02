package examples.jolt.ejb.bankapp;
/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */

import javax.ejb.*;
import java.rmi.RemoteException;

/**
 * This interface is the home interface for the TellerBean.java,
 * which in WebLogic is implemented by the code-generated container
 * class TellerBeanC. A home interface may support one or more create
 * methods, which must correspond to methods named "ejbCreate" in the EJBean.
 *
 * @author Copyright (c) 1999-2000 by BEA Systems, Inc. All Rights Reserved.
 */
public interface TellerHome extends EJBHome {

  /**
   * This method corresponds to the ejbCreate method in the bean
   * "TellerBean.java".
   * The parameter sets of the two methods are identical. When the client calls
   * <code>TellerHome.create()</code>, the container
   * allocates an instance of the EJBean and calls <code>ejbCreate()</code>.
   * <p>
   * It sets the name of the Teller and then attempts to get a session
   * from the Jolt session pool.
   *
   * @param tellerName        String Teller Name
   * @return                  Teller
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   * @exception               CreateException
   *                          if there is a error creating the bean
   * @see                     examples.jolt.ejb.bankapp.TellerBean#ejbCreate
   */
  Teller create(String tellerName) throws CreateException, RemoteException;
}
