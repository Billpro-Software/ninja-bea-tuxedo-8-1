//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// SimpleClient.java
//
// BEA Systems Inc. sample code.
// Java client program for the Java simple sample application.
//
// #ident	"@(#) samples/corba/cnssimpapp/SimpleClient.java   $Revision: 1.2 $"
//--------------------------------------------------------------------

import java.io.*;
import java.util.Properties;
import org.omg.CORBA.*;
import com.beasys.Tobj.*;
import com.beasys.*;
import org.omg.CosNaming.*;

/**
 * The SimpleClient class provides code for the Simpapp Java client.
 */
public class SimpleClient
{

    /**
     * This is the main code for the Simpapp Java client.
     */
	public static void main(String args[])
	{
		// Set things up to read lines of text from the user.
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

		try {
        	// Initialize the ORB.
        	ORB orb = ORB.init(args, null);

        	// Create the bootstrap object,
        	// the TOBJADDR property contains host and port to connect to.
        	Tobj_Bootstrap bootstrap = new Tobj_Bootstrap(orb, "");

		// retrieve the name service root obj ref - for now
		// we pull it from a file and when resolve_initial_references
		// supports "NameService" we can use that

		// BufferedReader inFile = 
		//     new BufferedReader(new FileReader ("cnsroot.dat"));

		// String root_ior_string = inFile.readLine ();

		// convert the string ior to an object reference and
		// narrow it to a NamingContextExt

		// org.omg.CORBA.Object ns_obj = 
		//     orb.string_to_object (root_ior_string);

		// get the Name Service reference
		org.omg.CORBA.Object ns_obj =
		    bootstrap.resolve_initial_references("NameService");

		org.omg.CosNaming.NamingContextExt ns_root = 
		    org.omg.CosNaming.NamingContextExtHelper.narrow (ns_obj);

		// resolve the simple factory in the name service
		// via the string name

        	org.omg.CORBA.Object simple_fact_oref =
		    ns_root.resolve_str ("simple_factory");

        	// Narrow the simple factory.
        	SimpleFactory simple_factory_ref =
        	    SimpleFactoryHelper.narrow(simple_fact_oref);

        	// Find the simple object.
        	Simple simple = simple_factory_ref.find_simple();

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

        	// everything succeeded.
        }
        catch (InvalidDomain e) {
            System.err.println("Can't connect to the domain: " +e);
            System.exit(1);
        }
        catch (org.omg.CORBA.BAD_PARAM e) {
            System.err.println("Invalid TOBJADDR=//host:port property specified: " +e);
            e.printStackTrace();
            System.exit(1);
        }
	catch (org.omg.CosNaming.NamingContextPackage.NotFound e)
	{
            System.err.println("Can't resolve name in name service");
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
