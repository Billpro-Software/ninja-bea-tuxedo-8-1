//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// billp_i.h
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

#ifndef _billp_i_h
#define _billp_i_h

//--------------------------------------------------------------------

#include <fml32.h>
#include "billp_s.h"

//--------------------------------------------------------------------

class Teller_i :
    public POA_BillingP::Teller
{
  public:

    Teller_i();

    virtual ~Teller_i();

    virtual CORBA::Double
    get_balance(
        BillingP::AccountNumber account
    );

    virtual void
    credit(
        BillingP::AccountNumber account,
        CORBA::Double           amount
    );

    virtual void
    debit(
        BillingP::AccountNumber account,
        CORBA::Double           amount
    );

  private:
    // fielded buffer of encoded message :
    FBFR32* m_tuxbuf;
};

//--------------------------------------------------------------------

class TellerFactory_i :
    public POA_BillingP::TellerFactory
{
  public:
    TellerFactory_i();

    virtual ~TellerFactory_i();

    virtual BillingP::Teller_ptr find_teller(
        BillingP::AccountNumber account
    );
};

//--------------------------------------------------------------------

#endif