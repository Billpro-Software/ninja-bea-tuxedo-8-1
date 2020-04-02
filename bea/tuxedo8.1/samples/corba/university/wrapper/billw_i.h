//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// billw_i.h
//
// Declares the C++ billing servant implementations for the university
// sample declaration.
//
// Classes declared :
//
//   Teller_i
//   TellerFactory_i
//
// This file was originally generated by using the "-i" idl switch,
// then edited by hand.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _billw_i_h
#define _billw_i_h

//--------------------------------------------------------------------

#include <fml32.h>
#include "billw_s.h"

//--------------------------------------------------------------------

class Teller_i :
    public POA_BillingW::Teller
{
  public:

    Teller_i();

    virtual ~Teller_i();

    virtual CORBA::Double
    get_balance(
        BillingW::AccountNumber account
    );

    virtual void
    credit(
        BillingW::AccountNumber account,
        CORBA::Double           amount
    );

    virtual void
    debit(
        BillingW::AccountNumber account,
        CORBA::Double           amount
    );

  private:
    // fielded buffer of encoded message :
    FBFR32* m_tuxbuf;
};

//--------------------------------------------------------------------

class TellerFactory_i :
    public POA_BillingW::TellerFactory
{
  public:
    TellerFactory_i();

    virtual ~TellerFactory_i();

    virtual BillingW::Teller_ptr find_teller(
    );
};

//--------------------------------------------------------------------

#endif
