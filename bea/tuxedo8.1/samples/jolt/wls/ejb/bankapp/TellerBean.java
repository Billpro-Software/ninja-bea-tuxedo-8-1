package examples.jolt.ejb.bankapp;
/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */

import bea.jolt.pool.*;
import java.io.Serializable;
import java.rmi.RemoteException;
import java.util.*;
import javax.ejb.*;
import javax.naming.*;

/**
 * TellerBean is a stateful SessionBean. This EJBean illustrates:
 * <ul>
 * <li> Accessing a Jolt server
 * <li> Automatic persistence of state between calls to the SessionBean
 * <li> The statefulness of this EJBean is the teller's name
 *      and the current Transaction (if any)
 * <li> Application-defined exceptions
 * </ul>
 *
 * @author Copyright (c) 1999-2000 by BEA Systems, Inc. All Rights Reserved.
 */
public class TellerBean implements SessionBean {
  static  final     boolean        VERBOSE = true;

  // -----------------------------------------------------------------
  // private variables
  private SessionContext ctx;
  private Context        rootCtx;
  private transient InitialContext ic;
  private transient SessionPool    joltSession;
  private static    int            sessionTimeout;

  // public variables
  public  String                   tellerName;
  public  Transaction              tellerTransaction;

  // -----------------------------------------------------------------
  // SessionBean implementation

  /**
   * Called when the EJBEan is activated.
   * Establishes reference to Jolt session pool.
   *
   * @exception               java.rmi.RemoteException
   *                          if there is a communications or systems failure
   */
  public void ejbActivate() throws RemoteException {
    if (VERBOSE)
      System.out.println("ejbActivate called");
    try {
      initJoltPool();
    } 
    catch (Exception e) {
      throw new RemoteException("ejbActivate called: " + e);
    }
  }

  /**
   * Called when the EJBean is removed.
   * Removes reference to Jolt session pool.
   *
   */
  public void ejbRemove() {
    if (VERBOSE)
      System.out.println("ejbRemove called");
    joltSession = null;
  }

  /**
   * Called when the EJBEan is passivated.
   * Removes reference to Jolt session pool.
   *
   */
  public void ejbPassivate() {
    if (VERBOSE)
      System.out.println("ejbPassivate (" + tellerName + ")");
    joltSession = null;
  }

  /**
   * Sets the session context.
   *
   * @param ctx               SessionContext Context for session
   */
  public void setSessionContext(SessionContext ctx) {
    if (VERBOSE)
      System.out.println("setSessionContext called");
    this.ctx       = ctx;
  }

  // Interface exposed to EJBObject

  /**
   * This method corresponds to the create method in the home interface
   * "TellerHome.java".
   * The parameter sets of the two methods are identical. When the client calls
   * <code>TellerHome.create()</code>, the container allocates an instance of 
   * the EJBean and calls <code>ejbCreate()</code>.
   * <p>
   * It sets the name of the Teller and then attempts to get a session
   * from the Jolt session pool.
   *
   * @param tellerName        String Teller name
   * @exception               javax.ejb.CreateException
   *                          if there is an error while initializing the Jolt pool
   * @see                     examples.jolt.ejb.bankapp.Teller
   */
  public void ejbCreate(String tellerName) 
    throws CreateException
  {
    if (VERBOSE)
      System.out.println("ejbCreate (" + tellerName + ")");
    try {
      Properties p = new Properties();
      p.put(Context.INITIAL_CONTEXT_FACTORY,
        "weblogic.jndi.WLInitialContextFactory");

      ic = new InitialContext(p);
      rootCtx = (Context) ic.lookup( "java:comp/env");

      sessionTimeout = ((Integer)rootCtx.lookup("transactionSessionTimeout")).intValue();
    } catch (NamingException ne) {
      throw new CreateException("Could not look up context");
    }


    this.tellerName = tellerName;
    try {
      initJoltPool();
    } 
    catch (Exception e) {
      throw new CreateException("ejbCreate called: " + e);
    }

  }

  /**
   * Deposits amount in account.
   *
   * @param accountNumber     int Account number
   * @param amount            double Amount to deposit
   * @return                  TellerResult Trade result
   * @exception               examples.jolt.ejb.bankapp.ProcessingErrorException
   *                          if there is an error making the deposit
   * @exception               examples.jolt.ejb.bankapp.TransactionErrorException
   *                          if there is an error making the deposit
   * @exception               java.rmi.RemoteException
   *                          if there is a communications or systems failure
   */
  public TellerResult deposit(int accountNumber, double amount)
    throws ProcessingErrorException,
           TransactionErrorException,
           RemoteException
  {
    if (VERBOSE) {
      System.out.println("Deposit (" + accountNumber + ", " + 
                         amount + ")");
    }
    DataSet request = new DataSet();
    request.setValue("ACCOUNT_ID", new Integer(accountNumber));
    request.setValue("SAMOUNT", new Double(amount).toString());
    return transact("DEPOSIT",request);
  }

  /**
   * Withdraws amount from account.
   *
   * @param accountNumber     int Account number
   * @param amount            double Amount to withdraw
   * @return                  TellerResult Trade result
   * @exception               examples.jolt.ejb.bankapp.ProcessingErrorException
   *                          if there is an error making the withdrawl
   * @exception               examples.jolt.ejb.bankapp.TransactionErrorException
   *                          if there is an error making the withdrawl
   * @exception               java.rmi.RemoteException
   *                          if there is a communications or systems failure
   */
  public TellerResult withdraw(int accountNumber, double amount)
    throws ProcessingErrorException,
           TransactionErrorException,
           RemoteException
  {
    if (VERBOSE) {
      System.out.println("Withdraw (" + accountNumber + ", " + 
                         amount + ")");
    }
    DataSet request = new DataSet();
    request.setValue("ACCOUNT_ID", new Integer(accountNumber));
    request.setValue("SAMOUNT", new Double(amount).toString());
    return transact("WITHDRAWAL", request);
  }

  /**
   * Returns the current balance for an Account.
   *
   * @param accountNumber     int Account number
   * @return                  TellerResult Trade result
   * @exception               examples.jolt.ejb.bankapp.ProcessingErrorException
   *                          if there is an error retrieving the balance
   * @exception               examples.jolt.ejb.bankapp.TransactionErrorException
   *                          if there is an error retrieving the balance
   */
  public TellerResult balance(int accountNumber) 
    throws ProcessingErrorException,
           TransactionErrorException
  {
    if (VERBOSE) {
      System.out.println("Inquiry (" + accountNumber + ")");
    }
    DataSet request = new DataSet();
    request.setValue("ACCOUNT_ID", new Integer(accountNumber));
    return transact("INQUIRY",request);
  }

  /**
   * Conducts a transaction on a request.
   *
   * @param transType         String Type of transaction
   * @param request           DataSet Data for transaction
   * @return                  TellerResult Result
   * @exception               examples.jolt.ejb.bankapp.ProcessingErrorException
   *                          if there is a
   *                          bea.jolt.SessionPoolException because all sessions are
   *                          busy, or a
   *                          bea.jolt.ServiceException from the Jolt Server
   *                          or any other errors while conducting the transaction
   * @exception               examples.jolt.ejb.bankapp.TransactionErrorException
   *                          if there is either a 
   *                          bea.jolt.ApplicationException or a
   *                          bea.jolt.TransactionException from the Jolt Server
   */
  private TellerResult transact(String transType, DataSet request)
    throws ProcessingErrorException,
           TransactionErrorException
  {
    Result result;
    if (VERBOSE) {
      System.out.println("Transaction (" + transType + ")");
    }
    try {
      result = joltSession.call(transType, request, tellerTransaction);
    }
    catch (SessionPoolException spe) {
      // All sessions are busy
      throw new ProcessingErrorException("Teller error: all sessions are busy " + spe);
    }
    catch (ApplicationException ae) {
      throw new TransactionErrorException("Teller error: application exception:\n" + 
                                          retreiveApplicationException(ae));
    }
    catch (ServiceException se) {
      throw new ProcessingErrorException("Teller error: service exception" + se);
    }
    catch (TransactionException te) {
      throw new TransactionErrorException("Teller error: transaction exception " + te);
    }
    catch (Exception e) {
      throw new ProcessingErrorException("Teller error: " + e);
    }
    if (result != null) {
      // As the Result object returned from the Jolt Server only has the parameters
      // that are marked as either "output" or "both" in the Jolt Repository,
      // we'll get the Account ID from our request parameter
      return new TellerResult((Integer) request.getValue("ACCOUNT_ID",null),
                              getDoubleFromString((String)result.getValue("SBALANCE",null)));

    } else {
      return new TellerResult();
    }
  }

  /**
   * Begins a transaction. If the bean already has a transaction,
   * it is used and a new one is not started.
   *
   * @return                  TellerResult Trade result
   * @exception               TransactionErrorException if there is
   *                          an error beginning the transaction
   */
  public void begin() 
    throws TransactionErrorException
  {
    if (VERBOSE) {
      System.out.println("Beginning transaction");
    }
    if (tellerTransaction == null) {
      try {
        tellerTransaction = joltSession.startTransaction(sessionTimeout);
      }
      catch (Exception e) {
        throw new TransactionErrorException("Teller error starting transaction: " + e);
      }
    }
  }

  /**
   * Commits the current transaction.
   *
   * @return                  TellerResult Trade result
   * @exception               TransactionErrorException if there is
   *                          an error committing the transaction
   *                          or there is no transaction to commit
   */
  public void commit()
    throws TransactionErrorException
  {
    if (VERBOSE) {
      System.out.println("Committing transaction");
    }
    int iResult = 0;
    if (tellerTransaction != null) {
      try {
        iResult = tellerTransaction.commit();
        tellerTransaction = null;
      }
      catch (Exception e) {
        throw new TransactionErrorException("Transaction failed to commit: " + e);
      }
      finally {
        if (iResult != 0)
          throw new TransactionErrorException("Transaction failed to commit; return code: " + iResult);
      }
    }
    else {
      throw new TransactionErrorException("No transaction to commit");
    }
  }

  /**
   * Rolls back the current transaction.
   *
   * @return                  TellerResult Trade result
   * @exception               TransactionErrorException if there is
   *                          an error rolling back the transaction
   *                          or there is no transaction to rollback
   */
  public void rollback()
    throws TransactionErrorException
  {
    if (VERBOSE) {
      System.out.println("Rolling back transaction");
    }
    int iResult = 0;
    if (tellerTransaction != null) {
      try {
        iResult = tellerTransaction.rollback();
        tellerTransaction = null;
      }
      catch (Exception e) {
        throw new TransactionErrorException("Transaction failed to rollback: " + e);
      }
      finally {
        if (iResult != 0)
          throw new TransactionErrorException("Transaction failed to rollback; return code: " + iResult);
      }
    }
    else {
      throw new TransactionErrorException("No transaction to rollback");
    }
  }

  /**
   * Returns the name of this Teller.
   *
   * @return                  String tellerName
   */
  public String getTellerName() {
    return this.tellerName;
  }

// Private methods

  /**
   * Returns the Jolt pool name.
   *
   * @return                  String Jolt pool name
   */
  private String getJoltPoolName() {
    try {
      return (String) rootCtx.lookup("joltPoolName");
    } catch (NamingException ne) {
      return null;
    }
  }

  /**
   * Returns the application exception information
   * in the status line of the Result object embedded in
   * the Application Exception.
   *
   * @param ae                ApplicationException Application exception
   * @return                  String Application status STATLIN
   */
  private String retreiveApplicationException(ApplicationException ae) {
    return (String) ae.getResult().getValue("STATLIN",null);
  }

  /**
   * Converts a String with formatting to a Double.
   *
   * @param value             String Value to be converted
   * @return                  double Transaction limit
   */
  private Double getDoubleFromString(String Value) {
    try {
      String sValue = java.text.NumberFormat.getCurrencyInstance(java.util.Locale.US).parse(Value).toString();
      return new Double(sValue);
    }
    catch (java.text.ParseException jtpe) {
      return null;
    }
  }

  /**
   * Initializes a Jolt session pool.
   * The SessionPool is retained in the
   * joltSession instance attribute.
   * It is nulled when the bean is passivated and
   * a new session is initiated when the bean is activated.
   */
  private void initJoltPool() throws Exception {
    SessionPoolManager sPoolManager =
      (SessionPoolManager) SessionPoolManager.poolmgr;
    joltSession = (SessionPool) sPoolManager.getSessionPool("joltpool");
    if (joltSession == null) {
      throw new Exception("Error intializing Jolt session pool");
    }
  }

}
