package examples.jolt.ejb.bankapp;
/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */

import java.io.Serializable;

/**
 * This class reflects the results of a transaction.
 *
 * @author Copyright (c) 1999-2000 by BEA Systems, Inc. All Rights Reserved.
 */
public final class TellerResult implements Serializable {
  public int     account;    // Account ID
  public double  balance;    // Balance in account

  /**
   * The account ID and balance of a transaction
   * are returned from the EJBean in a TellerResult object.
   *
   * @return                  TellerResult
   */
  public TellerResult() {
  }

  /**
   * The account ID and balance of a transaction 
   * are returned from the EJBean in a TellerResult object.
   *
   * @param account           Integer Account ID
   * @param balance           Double Balance in account
   * @return                  TellerResult
   */
  public TellerResult(Integer Account, Double Balance) {
    this.account = Account.intValue();
    this.balance = Balance.doubleValue();
  }

  /**
   * Returns the Account ID.
   *
   * @return                  int Account ID
   */
  public int getAccount() {
    return this.account;
  }

  /**
   * Returns the balance.
   *
   * @return                  double Balance in account
   */
  public double getBalance() {
    return this.balance;
  }

}
