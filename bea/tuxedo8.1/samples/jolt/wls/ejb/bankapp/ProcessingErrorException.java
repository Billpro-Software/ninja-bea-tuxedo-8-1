package examples.jolt.ejb.bankapp;
/**	(c) 2003 BEA Systems, Inc. All Rights Reserved. **/

/**
 * This class is used with the examples.jolt.ejb.bankapp package.
 * ProcessingErrorException is thrown if an error occurs while
 * processing a business method.
 *
 * @author Copyright (c) 1999-2000 by BEA Systems, Inc. All Rights Reserved.
 */
public class ProcessingErrorException extends Exception {

  /**
   * Catches exceptions without a specified string
   *
   */
  public ProcessingErrorException() {}

  /**
   * Constructs the appropriate exception with the specified string
   *
   * @param message           Exception message
   */
  public ProcessingErrorException(String message) {super(message);}
}
