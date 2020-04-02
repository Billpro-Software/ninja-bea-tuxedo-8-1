 /* Copyright (c) 2004, 2009, Oracle and/or its affiliates. 
All rights reserved. */
 
package oracle.mds.samples;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Source;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import oracle.xml.parser.schema.XMLSchema;
import oracle.xml.parser.schema.XSDBuilder;
import oracle.xml.parser.v2.DOMParser;
import oracle.xml.parser.v2.XMLParseException;
import oracle.xml.parser.v2.XMLParser;

/**
** Driver used to validate XSDs and instance documents.
** <p>
** Running this class without any input parameters will give you sample usage.
** <p>
** The class requires xmlparserv2.jar to be on the classpath.
*/
/*
** <!--------------------------------------------------------------------------
** MODIFIED  (MM/DD/YY)
** sudsrini  03/16/06 - Creation.
** --------------------------------------------------------------------------->
*/
public class XSDTester
{
    public static void main(String[] args) throws Exception 
    {    
        if ( args == null || args.length == 0 )
        {
            System.out.println("Driver program to validate XSDs and " +
                            "instance XML documents.");
            System.out.println("This program tests validation using both the" +
            " Oracle XDK and the J2SE 5.0 Validator FWK.");                
            System.out.println("Usage: java XSDTester <schema_file> <xml_file>");
            System.out.println("An example: java XSDTester C:\\myXSD.xsd" +
            " C:\\myXMLInstanceDoc.xml");
            System.out.println("Note that the XML File is optional. " +
            "If not provided, only the " +
            "schema is validated.");
            return;
        }    
        validate(args);
    }


    public static void validate(String[] args) throws Exception
    {
        validateUsingXDK(args);
        validateUsingJ2SE(args);
    }
    
    
    // Helper method to create a URL from a file name
    private static URL createURL(String fileName)
    {
        URL url = null;
        try
        {
            url = new URL(fileName);
        }
        catch ( MalformedURLException ex )
        {
            File f = new File(fileName);
            try
            {
                String path = f.getAbsolutePath();
                // This is a bunch of weird code that is required to
                // make a valid URL on the Windows platform, due
                // to inconsistencies in what getAbsolutePath returns.
                String fs = System.getProperty("file.separator");
                if ( fs.length() == 1 )
                {
                    char sep = fs.charAt(0);
                    if ( sep != '/' )
                    {
                        path = path.replace(sep, '/');
                    }
                    if ( path.charAt(0) != '/' )
                    {
                        path = '/' + path;
                    }
                }
                path = "file://" + path;
                url = new URL(path);
            }
            catch ( MalformedURLException e )
            {
                System.out.println("Cannot create url for: " + fileName);
                System.exit(0);
            }
        }
        return url;
    }
    
    
    private static void validateUsingJ2SE(String[] args) throws Exception
    {
        // parse an XML document into a DOM tree
        System.out.println("\n");
        System.out.println("Validating using J2SE:");

        DocumentBuilder parser   = DocumentBuilderFactory.newInstance().
                                    newDocumentBuilder();        

        // create a SchemaFactory capable of understanding WXS schemas
        SchemaFactory   factory  = SchemaFactory.
                                newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);

        // load a WXS schema, represented by a Schema instance
        Source          schemaFile1 = new StreamSource(new File(args[0]));
        System.out.println("Validating schema "+ args[0] + " using J2SE");
        Schema          schema      = factory.newSchema(schemaFile1);
        System.out.println("J2SE reported no issues with the schema.");
        if ( args.length == 1 || args[1] == null )
        {
            return;
        }
        Document        document = parser.parse(new File(args[1]));
        // create a Validator instance, which can be used to validate an 
        // instance document
        System.out.println("Validating "+ args[1] + " using J2SE");
        Validator validator = schema.newValidator();

        // validate the DOM tree
        try 
        {
            validator.validate(new DOMSource(document));
            System.out.println("With J2SE, the input instance document " +
            "<"+args[1]+"> parsed without " + " errors.");
        } 
        catch ( SAXException e ) 
        {
            System.out.println("SAX Exception " + e.getMessage());
        }    
    }
    
    
    private static void validateUsingXDK(String[] args) throws Exception 
    {
        System.out.println("Validating using Oracle XDK:");
        XSDBuilder builder = new XSDBuilder();
        URL    urlSchema =  createURL(args[0]);       

        // Build XML Schema Object
         System.out.println("Validating schema "+ args[0] + 
                " using Oracle XDK");
        XMLSchema schemadoc = (XMLSchema)builder.build(urlSchema); 
        System.out.println("Oracle XDK reported no issues with the schema.");
        if ( args.length == 1 || args[1] == null )
        {
            return;
        }
        DOMParser dp  = new DOMParser();
        URL       urlXML = createURL (args[1]);
      
        // Set Schema Object for Validation
        dp.setXMLSchema(schemadoc);
        dp.setValidationMode(XMLParser.SCHEMA_VALIDATION);
        dp.setPreserveWhitespace (true);
      
        dp.setErrorStream (System.out);
      
        try 
        {
            System.out.println("Validating "+ args[1] + " using Oracle XDK");
            dp.parse (urlXML);
            System.out.println("With Oracle XDK, the input instance document " +
            "<"+args[1]+"> parsed without " + " errors.");
        }
        catch ( XMLParseException pe ) 
        {
            System.out.println("Parser Exception: " + pe.getMessage());
        }
        catch ( Exception e ) 
        { 
            System.out.println ("NonParserException: " + e.getMessage()); 
        }
    }
}
