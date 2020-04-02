package examples.jolt.ejb.bankapp;
/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */

import javax.ejb.*;
import java.rmi.RemoteException;

/**
 * The methods in this interface are the public face of TellerBean.
 * The signatures of the methods are identical to those of the EJBean, except
 * that these methods throw a java.rmi.RemoteException.
 * Note that the EJBean does not implement this interface. The corresponding
 * code-generated EJBObject, TellerBeanE, implements this interface and
 * delegates to the bean.
 *
 * @author Copyright (c) 1999-2000 by BEA Systems, Inc. All Rights Reserved.
 */
public interface Teller extends EJBObject {

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
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   * @see                     examples.jolt.ejb.bankapp.TellerBean#transact
   */
  public TellerResult deposit(int accountNumber, double amount)
    throws ProcessingErrorException, TransactionErrorException, RemoteException;

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
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   * @see                     examples.jolt.ejb.bankapp.TellerBean#transact
   */
  public TellerResult withdraw(int accountNumber, double amount)
    throws ProcessingErrorException, TransactionErrorException, RemoteException;

  /**
   * Returns the current balance for an Account.
   *
   * @param accountNumber     int Account number
   * @return                  TellerResult Trade result
   * @exception               examples.jolt.ejb.bankapp.ProcessingErrorException
   *                          if there is an error retrieving the balance
   * @exception               examples.jolt.ejb.bankapp.TransactionErrorException
   *                          if there is an error retrieving the balance
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   * @see                     examples.jolt.ejb.bankapp.TellerBean#transact
   */
  public TellerResult balance(int accountNumber) 
    throws ProcessingErrorException, TransactionErrorException, RemoteException;

  /**
   * Returns the name of this Teller.
   *
   * @return                  String Teller Name
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   */
  public String getTellerName() 
    throws RemoteException;

  /**
   * Begins a transaction. If the bean already has a transaction,
   * it is used and a new one is not started.
   *
   * @return                  TellerResult Trade result
   * @exception               TransactionErrorException if there is
   *                          an error beginning the transaction
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   */
  public void begin()
    throws TransactionErrorException, RemoteException;

  /**
   * Commits the current transaction.
   *
   * @return                  TellerResult Trade result
   * @exception               TransactionErrorException if there is
   *                          an error committing the transaction
   *                          or there is no transaction to commit
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   */
  public void commit() 
    throws TransactionErrorException, RemoteException;

  /**
   * Rolls back the current transaction.
   *
   * @return                  TellerResult Trade result
   * @exception               TransactionErrorException if there is
   *                          an error rolling back the transaction
   *                          or there is no transaction to rollback
   * @exception               RemoteException if there is
   *                          a communications or systems failure
   */
  public void rollback()
    throws TransactionErrorException, RemoteException;
}
