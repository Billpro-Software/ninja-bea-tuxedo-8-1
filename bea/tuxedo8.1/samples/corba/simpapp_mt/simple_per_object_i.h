//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simple_per_object_i.h
//
// The simpapp_mt sample application provides two different implementations
// of the Simple interface. This source file includes declarations for
// Simple and SimplePerObjectFactory servants which will be included in
// a reentrant server which will be started using a Thread-per-Object 
// concurrency policy.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _simple_per_object_i_h
#define _simple_per_object_i_h

#include "simple_s.h"
extern char* generate_unique_id();           // Generate unique uuids

class Simple_i : public POA_Simple
{
  public:
    // Application methods we implement
    virtual CORBA::Char* to_lower(const char* val);
    virtual CORBA::Char* to_upper(const char* val);
    virtual CORBA::Char* forward_lower (const char* val); 
    virtual CORBA::Char* forward_upper (const char* val);

    // Now the Framework methods we implement
    virtual void activate_object  (const char* stroid);
    virtual void deactivate_object(const char* stroid,
                                   TobjS::DeactivateReasonValue reason);
};

class SimplePerObjectFactory_i : public POA_SimplePerObjectFactory
{
  public:
    virtual Simple_ptr find_simple();
};

#endif
