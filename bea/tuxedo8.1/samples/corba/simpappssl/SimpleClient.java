//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// SimpleClient.java
//
// Java client program for the simple SSL sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

import java.io.*;
import java.util.Properties;
import org.omg.CORBA.*;
import org.omg.Security.*;
import org.omg.SecurityLevel2.*;
import com.beasys.Tobj.*;
import com.beasys.*;

/**
 * The SimpleClient class provides code for the SSL Simpapp Java client
 */
public class SimpleClient
{
    /**
     * This is the main code for the Simpapp Java client
     */

    public static void main(String args[])
    {
        // Set things up to read lines of text from the user.
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        
        try
        {
            /**
             * Initialize the ORB
             */
            Properties property = new Properties(System.getProperties());
            property.put("org.omg.CORBA.ORBClass", "com.beasys.CORBA.iiop.ORB");
            property.put("org.omg.CORBA.ORBSingletonClass", "com.beasys.CORBA.idl.ORBSingleton");
            System.setProperties(property);

            ORB orb = ORB.init(args, null);
            
            /**
             * Create the bootstrap object,
             * the TOBJADDR property contains host and port to connect to.
             */
            String tobjaddr = property.getProperty("TOBJADDR");
            if(tobjaddr == null)
            {
                System.err.println("ERROR: TOBJADDR environment variable not set or provided to client");
                System.err.println("       java -DTOBJADDR=%TOBJADDR% SimpleClient");
                System.exit(1);
            }
            Tobj_Bootstrap bootstrap = new Tobj_Bootstrap(orb, "");
            
            /**
             * Determine if client certificate validation enabled,
             * the TUXCERT property should contain the string "YES"
             */
            String certEnabled = property.getProperty("TUXCERT");
            if((certEnabled != null) && (certEnabled.equalsIgnoreCase("YES")))
            {
                System.out.println("Client Certificate Validation Enabled");
                
                /**
                 * This code can be used when certificate based authentication 
                 * is required. To enable certificate based authentication, 
                 * enable this code, specify the principal name definition and
                 * the password pass phrase for the principal private key
                 */

                // Verify that all SSL required definitions can be resolved
                String authEmail = property.getProperty("TUX_EMAIL");
                String authPassword = property.getProperty("TUX_PASSWORD");
                if((authEmail == null) || (authPassword == null))
                {
                    System.err.println("Required SSL definitions TUX_EMAIL and TUX_PASSWORD not specified");
                    System.exit(1);
                }
                byte[] authPasswordBytes = authPassword.getBytes("UTF8");
                
                // Get BEA ORB SecurityCurrent
                org.omg.SecurityLevel2.Current securityCurrent = null;
                try
                {
                    org.omg.CORBA.Object secCurObjRef =
                        bootstrap.resolve_initial_references("SecurityCurrent");
                    if(secCurObjRef == null)
                    {
                        System.err.println("ERROR: No SecurityCurrent present");  
                        System.exit(1);
                    }
                    securityCurrent = org.omg.SecurityLevel2.CurrentHelper.narrow(secCurObjRef);
                }
                catch(Exception ex)
                {
                    System.err.println("ERROR: bootstrap.resolve_initial_references threw exception");
                    System.err.println(ex.toString());
                    System.exit(1);
                }

                // Get principal security authenticator
                com.beasys.Tobj.PrincipalAuthenticator principalAuthenticator =
                    (com.beasys.Tobj.PrincipalAuthenticator) securityCurrent.principal_authenticator();

                /**
                 * Authenticate email/password
                 */
                OpaqueHolder authData = new OpaqueHolder();
                authData.value = authPasswordBytes;
                AttributeListHolder privileges =  new AttributeListHolder();
                CredentialsHolder credentials = new CredentialsHolder();
                OpaqueHolder continuationData = new OpaqueHolder();
                OpaqueHolder authSpecificData = new OpaqueHolder();

                AuthenticationStatus authStatus = principalAuthenticator.authenticate(
                    CertificateBased.value,
                    authEmail,                  // TUX_EMAIL property
                    authData.value,             // TUX_PASSWORD property
                    privileges.value,
                    credentials,
                    continuationData,
                    authSpecificData);
                
                while(authStatus.value() == AuthenticationStatus.SecAuthContinue.value())
                {
                    byte[] responseData = null;
                    
                    // Retry authentication
                    authStatus = principalAuthenticator.continue_authentication(
                        responseData,
                        credentials,
                        continuationData,
                        authSpecificData);
                }
                
                if(authStatus.value() != AuthenticationStatus.SecAuthSuccess.value())
                {
                    System.err.println("Authenticate failed with status: " + authStatus.value());
                    System.exit(1);
                }
                else
                    System.out.println("Client Certificate Authentication Successful");
            }

            // Use the bootstrap object to find the factory finder.
            org.omg.CORBA.Object factoryFinderObjRef =
                bootstrap.resolve_initial_references("FactoryFinder");
            if(factoryFinderObjRef == null)
            {
                System.err.println("ERROR: No FactoryFinder present");  
                System.exit(1);
            }

            // Narrow the factory finder.
            FactoryFinder factoryFinderRef =
                FactoryFinderHelper.narrow(factoryFinderObjRef);

            // Use the factory finder to find the simple factory.
            org.omg.CORBA.Object simpleFactoryObjRef =
                factoryFinderRef.find_one_factory_by_id(SimpleFactoryHelper.id());

            // Narrow the simple factory.
            SimpleFactory simpleFactoryRef =
                SimpleFactoryHelper.narrow(simpleFactoryObjRef);
            
            // Find the simple object.
            Simple simple = simpleFactoryRef.find_simple();
            
            // Get a string from the user.
            System.out.println("String?");
            String mixed = in.readLine();
            
            // Convert the string to upper case.
            org.omg.CORBA.StringHolder buf = new org.omg.CORBA.StringHolder(mixed);
            simple.to_upper(buf);
            System.out.println(buf.value);
            
            // Convert the string to lower case.
            String lower = simple.to_lower(mixed);
            System.out.println(lower);
        }
        catch (org.omg.CosLifeCycle.NoFactory e)
        {
            System.err.println("Can't find the simple factory: " +e);
            System.exit(1);
        }
        catch (CannotProceed e)
        {
            System.err.println("FactoryFinder internal error: " +e);
            System.exit(1);
        }
        catch (RegistrarNotAvailable e)
        {
            System.err.println("FactoryFinder Registrar not available: " +e);
            System.exit(1);
        }
        catch (InvalidDomain e)
        {
            System.err.println("Can't connect to the domain: " +e);
            System.exit(1);
        }
        catch (InvalidName e)
        {
            System.err.println("Invalid name from resolve_initial_reference(): " +e);
            System.exit(1);
        }
        catch (org.omg.CORBA.BAD_PARAM e)
        {
            System.err.println("Invalid TOBJADDR=//host:port property specified: " +e);
            e.printStackTrace();
            System.exit(1);
        }
        catch (org.omg.CORBA.UserException e)
        {
            System.err.println("Unexpected CORBA user exception: " +e);
            e.printStackTrace();
            System.exit(1);
        }
        catch (org.omg.CORBA.SystemException e)
        {
            System.err.println("CORBA system exception: " +e);
            e.printStackTrace();
            System.exit(1);
        }
        catch (IOException e)
        {
            System.err.println("IO exception: " +e);
            e.printStackTrace();
            System.exit(1);
        }
    }
}
