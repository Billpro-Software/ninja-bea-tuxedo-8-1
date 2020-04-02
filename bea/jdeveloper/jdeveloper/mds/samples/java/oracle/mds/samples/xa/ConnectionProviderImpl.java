package oracle.mds.samples.xa;

import java.sql.Connection;

import java.sql.SQLException;

import javax.sql.XAConnection;

import oracle.mds.persistence.stores.db.xa.ConnectionProvider;


/* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */

/*
** <!--------------------------------------------------------------------------
** MODIFIED    (MM/DD/YY) 
** jejames     03/25/06 - Creation
 */

/**
 ** The implementations of this interface are required to be provided for the 
 ** MDS transactions to participate in a distributed transaction( JTA ).
 ** 
 ** MDS will retrieve the SQL Connection object by calling 
 ** getConnection(). Following are the important points that needs to be 
 ** followed while implementing the ConnectionProvider.
 ** <p>
 ** <li><i>The SQL connection returned by the implementations must 
 ** correspond to the XAResource enrolled in the distributed transaction.
 ** </i></li>
 ** <li><i>MDS Clients should ensure that the retrieved SQL Connection will be
 ** closed after the transaction is completed
 ** </i></li>
 ** <li><i>Implementations must be thread-safe</i></li>
 ** 
 ** @see oracle.mds.persistence.stores.db.DBMetadataStore
 ** @see oracle.mds.internal.persistence.xdb.XDBMetadataStore
 ** 
*/

 public class ConnectionProviderImpl implements ConnectionProvider 
 {
    public ConnectionProviderImpl(XAConnection xaconnection) 
    {
        try
        {
            m_Connection = xaconnection.getConnection();
        }
        catch(SQLException e) 
        {
            System.out.println("SQLException");
        }
    }
    
     /**
     ** Returns the Connection object
     ** 
     ** @return the Connection object.
     */
     public Connection getConnection()
     {
         return m_Connection;
     }
     
     public String toString() 
     {
         return m_Connection.toString();
     }
     
     private Connection m_Connection;
 }
