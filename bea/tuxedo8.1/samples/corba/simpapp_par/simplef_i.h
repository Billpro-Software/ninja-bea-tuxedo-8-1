//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//--------------------------------------------------------------------
//
// simplef_i.h
//
// C++ servant declarations for the simpapp_par sample factory.
//
// This file was originally generated by using the "-i" idl switch,
// then edited by hand.
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef _simplef_i_h
#define _simplef_i_h

#include "simplef_s.h"

class SimpleFactory_i : public POA_SimpleFactory
{
  public:
    virtual Simple_ptr find_simple();
};

#endif
