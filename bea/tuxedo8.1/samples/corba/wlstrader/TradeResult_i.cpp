/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*******************************************************************
 * Created Thu May 24 14:32:50 2001 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Example Implementation Functions: (TradeResult_i.cpp)
 * -----------------------------------------------------------------------
 *
 * This module contains example function implementations for the following
 * Implementations:
 *
 *
 */


/* M3_PRESERVE_BEGIN(INCLUDES) */
    /* Insert code that you want preserved here */
#include "TradeResult_i.h"
    /* This section can be used to preserve any #include directives,
       global data, function prototypes, etc */
/* M3_PRESERVE_END(INCLUDES) */
/*
 * Constructor for value type
 * examples::rmi_iiop::ejb::rmi_iiop::TradeResult
 */
examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i ()
{

/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::defaultconstructor) */
    /* Insert code that you want preserved here */


/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::defaultconstructor) */

}

/*
 * Constructor for value type
 * examples::rmi_iiop::ejb::rmi_iiop::TradeResult
 */
examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i (    ::CORBA::Long _in_numberTraded_,
    ::CORBA::WStringValue * _in_stockSymbol_)
{

/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::constructor) */
    /* Insert code that you want preserved here */

    numberTraded(_in_numberTraded_);
    stockSymbol(_in_stockSymbol_);

/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::constructor) */

}

/*
 * Implementation of _copy_value() for value type
 * examples::rmi_iiop::ejb::rmi_iiop::TradeResult
 */
CORBA::ValueBase* examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::_copy_value ()
{
/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::_copy_value) */
    /* Insert code that you want preserved here */

    return new examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i(
                      numberTraded(),
                      stockSymbol());

/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i::_copy_value) */
}

/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i) */
    /* Insert code that you want preserved here */


/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i) */

/*
 * Constructor for value type
 * examples::rmi_iiop::ejb::rmi_iiop::TradeResult factory class
 */
examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory ()
{
    _ref_count = 1;

/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::defaultconstructor) */
    /* Insert code that you want preserved here */


/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::defaultconstructor) */

}

/*
 * Constructor for value type
 * examples::rmi_iiop::ejb::rmi_iiop::TradeResult factory class
 */
examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::~examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory ()
{

/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::defaultdestructor) */
    /* Insert code that you want preserved here */


/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::defaultdestructor) */

}

void examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::_add_ref()
{
    _ref_count++;
}

void examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::_remove_ref()
{
    if(--_ref_count == 0)
        delete this;
}

examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory* examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::_downcast(::CORBA::ValueFactory _arg)
{
    return dynamic_cast<examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory*>(_arg);
}

/*
 * Implementation of the factory create_for_unmarshal for value type
 * examples::rmi_iiop::ejb::rmi_iiop::TradeResult
 */
CORBA::ValueBase* examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::create_for_unmarshal()
{
/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::create_for_unmarshal) */
    /* Insert code that you want preserved here */

    return new examples_rmi_iiop_ejb_rmi_iiop_TradeResult_i();

/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory::create_for_unmarshal) */
}


/* M3_PRESERVE_BEGIN(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory) */
    /* Insert code that you want preserved here */


/* M3_PRESERVE_END(examples_rmi_iiop_ejb_rmi_iiop_TradeResult_factory) */



/* M3_PRESERVE_BEGIN(TRAILER) */
    /* Insert code that you want preserved here */
    /* This section can be used to preserve any
        additional non-generated functions */

/* M3_PRESERVE_END(TRAILER) */
