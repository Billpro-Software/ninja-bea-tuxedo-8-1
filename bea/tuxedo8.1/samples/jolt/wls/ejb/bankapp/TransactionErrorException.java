package examples.jolt.ejb.bankapp;
/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */

/**
 * This class is used with the examples.jolt.ejb.bankapp package.
 * TransactionErrorException is thrown if an error occurs while
 * conducting a transaction.
 *
 * @author Copyright (c) 1999-2000 by BEA Systems, Inc. All Rights Reserved.
 */
public class TransactionErrorException extends Exception {

  /**
   * Catches exceptions without a specified string
   *
   */
  public TransactionErrorException() {}

  /**
   * Constructs the appropriate exception with the specified string
   *
   * @param message           Exception message
   */
  public TransactionErrorException(String message) {super(message);}
}
