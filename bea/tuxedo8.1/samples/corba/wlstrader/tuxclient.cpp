/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
#include <wchar.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

#include "CosNaming_c.h"
#include "Trader_c.h"
#include "TraderHome_c.h"
#include "TradeResult_i.h"


int main(int argc, char** argv)
{
    char IOR_buf[1024];
    
    try {
	CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, OBB::BEA_IIOP_ID);
	//
	// Need to register value factories for all valuetypes we
	// might receive.
	//
	examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory* TRf = new examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory();
	orb->register_value_factory((char *const)examples::rmi_iiop::ejb::rmi_iiop::_tc_TradeResult->id(), TRf);
	//
	// Read the IOR from the file ior.txt
	//
	try {
	    ifstream IOR_file("ior.txt", ios::in);
	    IOR_file >> IOR_buf;
	}
	catch(...) {
	    cout << "Problem opening ior.txt" << endl;
	    return 1;
	}
	
	// Convert the IOR to an object
	CORBA::Object_ptr o = orb->string_to_object(IOR_buf);
	
	// obtain a naming context
	CosNaming::NamingContext_var context = CosNaming::NamingContext::_narrow(o);
	CosNaming::Name name;
	name.length(1);
	name[0].id = (const char *)"rmi_iiop.TraderHome";
	name[0].kind = (const char *)"";
	
	// resolve and narrow to RMI object
	CORBA::Object_var object = context->resolve(name);
	::examples::rmi_iiop::ejb::rmi_iiop::TraderHome_var home =
	    ::examples::rmi_iiop::ejb::rmi_iiop::TraderHome::_narrow(object);

	// Create a trader instance
	::examples::rmi_iiop::ejb::rmi_iiop::Trader_ptr trader = home->create();
	
	// Buy some shares
	CORBA::WStringValue_ptr BEASsym = new CORBA::WStringValue(CORBA::wstring_dup((wchar_t *)L"BEAS"));
	::examples::rmi_iiop::ejb::rmi_iiop::TradeResult_ptr result;
	cout << "Buying 3000 shares of BEAS" << endl;
	result = trader->buy(BEASsym, 3000);

	// Get the number of shares actually traded from the results valuetype.
	// The TraderResult Java class doesn't implement any interfaces besides
	// serializable, it won't have any methods generated on the valuetype.
	// And since the class' state is maintained in private instance members,
	// there isn't any default public access to the valuetype's state.
	// The value factory for TradeResult creates an instance of
	// examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i, we can safely dynamically
	// cast down to the concrete implementation class, which was extended
	// to provide public members to access the private state.
	//
	examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i* result_i;
	result_i = dynamic_cast<examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i*>(result);
	cout << result_i->get_numberTraded() << " shares bought" << endl;

	// Buy some more shares
	cout << "Buying 100 shares of PSFT" << endl;
	CORBA::WStringValue_ptr PSFTsym = new CORBA::WStringValue(CORBA::wstring_dup((wchar_t *)L"PSFT"));
	result = trader->buy(PSFTsym, 100);
	result_i = dynamic_cast<examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i*>(result);
	cout << result_i->get_numberTraded() << " shares bought" << endl;

	// Release the references to the various valuetypes
	result->_remove_ref();
	BEASsym->_remove_ref();
	PSFTsym->_remove_ref();
    }
    catch(const CORBA::Exception& e) {
	cout << "Caught exception: " << e.get_id() << endl;
    }
    catch(...) {
	cout << "Caught unexpected exception" << endl;
    }
    
    return 0;
}
