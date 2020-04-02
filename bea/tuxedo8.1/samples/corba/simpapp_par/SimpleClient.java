//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// SimpleClient.java
//
// Java client program for the simpapp_par sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

import java.io.*;
import java.util.Properties;
import org.omg.CORBA.*;
import com.beasys.Tobj.*;
import com.beasys.*;

/**
 * The SimpleClient class provides code for the Simpapp_par Java client.
 */
public class SimpleClient
{
    /**
     * This is the main code for the Simpapp_par Java client.
     */

    public static void main(String args[])
    {
        // Set things up to read lines of text from the user.
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        
        try {
            // Initialize the ORB.
            Properties Prop;
            Prop = new Properties();
            Prop.put("org.omg.CORBA.ORBClass",
                     "com.beasys.CORBA.iiop.ORB");
            Prop.put("org.omg.CORBA.ORBSingletonClass",
                     "com.beasys.CORBA.idl.ORBSingleton");
            System.setProperty("org.omg.CORBA.ORBSingletonClass",
                     "com.beasys.CORBA.idl.ORBSingleton");

            ORB orb = ORB.init(args, Prop);

            // Create the bootstrap object,
            // the TOBJADDR property contains host and port to connect to.
            Tobj_Bootstrap bootstrap = new Tobj_Bootstrap(orb, "");

            // Use the bootstrap object to find the factory finder.
            org.omg.CORBA.Object fact_finder_oref =
                bootstrap.resolve_initial_references("FactoryFinder");

            // Narrow the factory finder.
            FactoryFinder fact_finder_ref =
                FactoryFinderHelper.narrow(fact_finder_oref);

            // Use the factory finder to find the simple factory.
            org.omg.CORBA.Object simple_fact_oref =
                fact_finder_ref.find_one_factory_by_id(SimpleFactoryHelper.id());

            // Narrow the simple factory.
            SimpleFactory simple_factory_ref =
                SimpleFactoryHelper.narrow(simple_fact_oref);
                
            // Find the simple object.
            Simple simple = simple_factory_ref.find_simple();

            // Invoke the s_pid method 5 times and output the returned pid of 
            // the server used to process each request.
            for (int idx=0; idx<5; idx++)
            {
                System.out.println("ProcessID:  " + simple.s_pid());
            }
                
            // Get a string from the user.
            System.out.println("String?");
            String mixed = in.readLine();
                
            // Convert the string to upper case.
            org.omg.CORBA.StringHolder buf = 
                new org.omg.CORBA.StringHolder(mixed);
            simple.to_upper(buf);
            System.out.println(buf.value);
                
            // Convert the string to lower case.
            String lower = simple.to_lower(mixed);
            System.out.println(lower);
        }
        catch (org.omg.CosLifeCycle.NoFactory e) {
            System.err.println("Can't find the simple factory: " +e);
            System.exit(1);
        }
        catch (CannotProceed e) {
            System.err.println("FactoryFinder internal error: " +e);
            System.exit(1);
        }
        catch (RegistrarNotAvailable e) {
            System.err.println("FactoryFinder Registrar not available: " +e);
            System.exit(1);
        }
        catch (InvalidDomain e) {
            System.err.println("Can't connect to the domain: " +e);
            System.exit(1);
        }
        catch (InvalidName e) {
            System.err.println("Invalid name from resolve_initial_reference(): " +e);
            System.exit(1);
        }
        catch (org.omg.CORBA.BAD_PARAM e) {
            System.err.println("Invalid TOBJADDR=//host:port property specified: " +e);
            e.printStackTrace();
            System.exit(1);
        }
        catch (org.omg.CORBA.UserException e) {
            System.err.println("Unexpected CORBA user exception: " +e);
            e.printStackTrace();
            System.exit(1);
        }
        catch (org.omg.CORBA.SystemException e) {
            System.err.println("CORBA system exception: " +e);
            e.printStackTrace();
            System.exit(1);
        }
        catch (IOException e) {
            System.err.println("IO exception: " +e);
            e.printStackTrace();
            System.exit(1);
        }
    }
}
