/**	(c) 2003 BEA Systems, Inc. All Rights Reserved. **/
package examples.jolt.ejb.bankapp;

import javax.ejb.*;
import javax.naming.*;
import java.rmi.RemoteException;
import java.util.Properties;

/**
 * This class illustrates using a stateful SessionBean that calls 
 * a public Jolt server at <tt>//TUXSERVER:6309</tt>:
 * <ul>
 * <li> It creates a teller, and perform repeated deposits and withdraws
 * <li> The statefulness of this EJBean is the teller's name
 *      and the current Transaction (if any)
 * <li> All calls to the Jolt server are performed by the EJBean
 * <li> Persistence of state between calls to the SessionBean;
 *      the client does not do anything to maintain state between calls
 * <li> How to search the JNDI tree for an appropriate container
 * <li> Application-defined exceptions
 * </ul>
 * <p>
 * You'll need to add a Jolt pool to your <tt>weblogic configuration</tt>:
 * <pre># Demo Jolt pool
 *
 * &lt;StartupClass
 * ClassName="bea.jolt.pool.servlet.weblogic.PoolManagerStartUp"
 * FailureIsFatal="false"
 * Name="MyStartup  Class"
 * Targets="myserver"
 * /&gt;
 * &lt;JoltConnectionPool
 * ApplicationPassword="tuxedo"
 * MaximumPoolSize="5"
 * MinimumPoolSize="3"
 * Name="MyJolt  Connection  Pool"
 * PrimaryAddresses="//TUXSERVER:6309"
 * RecvTimeout="300"
 * SecurityContextEnabled="false"
 * Targets="myserver"
 * UserName="joltuser"
 * UserPassword="jolttest"
 * UserRole="clt"
 * /&gt;
 * &lt;ShutdownClass
 * ClassName="bea.jolt.pool.servlet.weblogic.PoolManagerShutDown."
 * /&gt;
 *
 * @author Copyright (c) 1999-2000 by BEA Systems, Inc. All Rights Reserved.
 */
public class Client {

  static String url       = "t3://localhost:7001";
  static String user      = null;
  static String password  = null;

  /**
   * Runs this example from the command line. Example:
   * <p>
   * <tt>java examples.jolt.ejb.bankapp.Client "t3://localhost:7001" scott tiger</tt>
   * <p>
   * The parameters are optional, but if any are supplied,
   * they are interpreted in this order:
   * <p>
   * @param url               URL such as "t3://localhost:7001" of Server
   * @param user              User name, default null
   * @param password          User password, default null
   */
  public static void main(String[] args) {
    System.out.println("\nBeginning jolt.bankapp.Client...\n");

    // Parse the argument list 
    if ((args == null) || (args.length == 0)) {} 
      else
    for (int i = 0; i < args.length; i++) {
      switch(i) {
        case 0:
          url = args[i];
          break;
        case 1:
          user = args[i];
          break;
        case 2:
          password = args[i];
          break;
        default:
      }
    }

    String customerName = "Erin"; 
    int    account      = 10000;

    try {
      // Create a teller object, who'll later help us execute trades
      Context ctx          = getInitialContext();
      TellerHome brokerage = (TellerHome) ctx.lookup("bankapp.TellerHome");
      // Give our teller a name
      Teller teller = brokerage.create("Terry");

      System.out.println("\nCreated teller " + teller.getTellerName() + "\n");
   
      try {
        TellerResult tr;
        double       amount;

        // Current balance in account
        System.out.println("Getting current balance of Account " +
                           account + " for " + customerName);

        tr = teller.balance(account);
        System.out.println("Balance: " + tr.getBalance());

        // Transaction 1: Deposit
        System.out.println("\nStart Transaction 1 for " + customerName + "\n");

        amount = 100;
        System.out.println("  Depositing " + amount + " for " + customerName);

        tr = teller.deposit(account, amount);
        System.out.println("  Balance: " + tr.getBalance());

        System.out.println("\nEnd Transaction 1 for " + customerName +"\n");

        // Transaction 2: Deposit and then attempt an overdraft
        System.out.println("Start Transaction 2 for " + customerName +"\n");

        try {
          teller.begin();

          // Deposit
          amount = 200;
          System.out.println("  Depositing " + amount + " for " + customerName);

          tr = teller.deposit(account, amount);
          System.out.println("  Balance: " + tr.getBalance() + "\n");

          // Withdrawl: attempt to withdraw more than account balance
          // To see a transaction succeed, uncomment the line below
          // and then comment out the following line
          // amount = 100;

          amount = tr.getBalance() + 100;

          System.out.println("  Withdrawing " + amount + " for " + customerName);

          tr = teller.withdraw(account, amount);
          System.out.println("  Balance: " + tr.getBalance() + "\n");

          System.out.println("  Committing transaction for " + customerName);
          teller.commit();
        }
        catch (TransactionErrorException tee) {
          System.out.println("  Transaction error:\n  " + tee + "\n");
          System.out.println("  Rolling back transaction for " + customerName + "\n");
          teller.rollback();
        }
        System.out.println("End Transaction 2 for " + customerName + "\n");

        // Final balance in account
        System.out.println("Getting final balance of Account " +
                           account + " for " + customerName);
        System.out.println("Balance: " + teller.balance(account).getBalance() + "\n");
      }
      catch (ProcessingErrorException pe) {
        System.out.println("Processing Error: " + pe + "\n");
      }
      catch (Exception e) {
        System.out.println(":::::::::::::: Error :::::::::::::::::");
        e.printStackTrace();
      }

      if (teller != null) {
        try {
          // Remove teller
          System.out.println("Removing teller " + teller.getTellerName() + "\n");
          teller.remove();
        }
        catch (Exception e) {
          System.out.println("Error removing teller: ");
          e.printStackTrace();
        }
      }
    }
    catch (Exception e) {
      System.out.println(":::::::::::::: Error :::::::::::::::::");
      e.printStackTrace();
    }
    System.out.println("End jolt.bankapp.Client...\n");
  }
  
  /**
   * Gets an initial context.
   *
   * @return                  Context
   * @exception               java.lang.Exception if there is
   *                          an error in getting a Context
   */
  static public Context getInitialContext() throws Exception {
    Properties p = new Properties();
    p.put(Context.INITIAL_CONTEXT_FACTORY,
          "weblogic.jndi.WLInitialContextFactory");
    p.put(Context.PROVIDER_URL, url);
    if (user != null) {
      System.out.println ("user: " + user);
      p.put(Context.SECURITY_PRINCIPAL, user);
      if (password == null) 
      password = "";
      p.put(Context.SECURITY_CREDENTIALS, password);
    } 
    return new InitialContext(p);
  }
}
