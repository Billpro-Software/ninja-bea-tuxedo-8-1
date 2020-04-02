/* Copyright (c) 2007, 2009, Oracle and/or its affiliates. 
All rights reserved. */

package oracle.mds.samples.mymusicindustry.mymusiccompany;

import java.util.Collection;
import java.util.Iterator;
import java.util.Stack;

import oracle.bali.xml.grammar.AttributeDef;
import oracle.bali.xml.grammar.ElementDef;

import oracle.mds.core.MDSInstance;
import oracle.mds.type.TypeManager;

public class TypeInfoExample extends ReadMetadataExample
{

    /**
    ** A simple example that loops through all of the typed components and
    ** prints out attributes.
    */
    public static void main(String[] args)
    {
        /*
        ** Use the MDSInitializer helper class to instantiate an MDSInstance
        ** (Available in Appendix A4)
        */
        MDSInitializer  init = createMDSInitializer(args);
        MDSInstance     mds  = init.getMDSInstance();

        TypeManager    tMgr = mds.getTypeManager();
        ElementDef     eDef = tMgr.getElementDef(
                              "http://xmlns.oracle.com/provider",
                              "pdkProvider");
        Stack<ElementDef> stack = new Stack<ElementDef>();
        stack.push(eDef);
        while ( !stack.empty() )
        {
            eDef                = (ElementDef)stack.pop();
            System.out.println(" Printing attributes for : " + eDef);
            Collection  coll    = eDef.getElementDefs();
            Iterator    iter    = coll.iterator();
            while ( iter != null && iter.hasNext() )
            {
                stack.push((ElementDef)(iter.next()));
            }
            coll    = eDef.getAttributeDefs();
            iter    = coll.iterator();
            while ( iter != null && iter.hasNext() )
            {
                AttributeDef aDef = (AttributeDef)iter.next();
                System.out.println(" Attribute Name :  " + aDef);
            }
        }
    }

}
