/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*******************************************************************
 * Created Thu May 24 14:32:50 2001 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Example Implementation include file: (TradeResult_i.h)
 * ---------------------------------------------------------------------
 *
 * This module contains example definitions
 * for the following Implementations:
 *

 *
 */
#ifndef _TradeResult_i_h
#define _TradeResult_i_h


/* M3_PRESERVE_BEGIN(INCLUDES) */
    /* Insert code that you want preserved here */
    /* This section can be used to preserve any #include directives,
       global data, function prototypes, etc */

#include "TradeResult_s.h"
/* M3_PRESERVE_END(INCLUDES) */

//
// The implementation class definition for the value type 
// examples::rmi_iiop::ejb::rmi_iiop::TradeResult.
//

class examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i :
    virtual public OBV_examples::rmi_iiop::ejb::rmi_iiop::TradeResult,
    virtual public CORBA::DefaultValueRefCountBase
{
    public:
        examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i();
        examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i(
            ::CORBA::Long,
            ::CORBA::WStringValue *);
        CORBA::ValueBase* _copy_value();
/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i) */
    /* Insert code that you want preserved here */
	//
	// Since TradeResult declared its state members as private, provide
	// accessors to allow setting/getting the state of the trade using
	// the protected OBV class members
	//
	::CORBA::Long get_numberTraded() const {return numberTraded();}
	void set_numberTraded(::CORBA::Long _val) {numberTraded(_val);}
	::CORBA::WStringValue * get_stockSymbol() const {return stockSymbol();}
	void set_stockSymbol(::CORBA::WStringValue * _val) {stockSymbol(_val);}

/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i) */


};
//
// The implementation class definition for the factory for the
// value type examples::rmi_iiop::ejb::rmi_iiop::TradeResult.
//

class examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory :
    virtual public ::CORBA::ValueFactoryBase
{
    public:
        examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory();
        examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::~examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory();
        void _add_ref();
        void _remove_ref();
        static examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory* _downcast(::CORBA::ValueFactory vf);
        ::CORBA::ValueBase * create_for_unmarshal ();
    private:
        ::CORBA::ULong _ref_count;

/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory) */
    /* Insert code that you want preserved here */


/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory) */


};
#endif


/* M3_PRESERVE_BEGIN(TRAILER) */
    /* Insert code that you want preserved here */
    /* This section can be used to preserve any
        additional non-generated functions */

    // Create a factory that can be registered with the ORB

/* M3_PRESERVE_END(TRAILER) */
