//    Copyright (c) 1999 BEA Systems, Inc.
//    All rights reserved
//
//    THIS IS UNPUBLISHED PROPRIETARY
//    SOURCE CODE OF BEA Systems, Inc.
//    The copyright notice above does not
//    evidence any actual or intended
//    publication of such source code.
//
// #ident     "@(#) objtm/beawrapper/beawrapper.cpp      $Revision: 1.2 $"

#include <iostream.h>
#include "beawrapper.h"

CORBA::ORB_ptr BEAWrapper::Callbacks::orb = CORBA::ORB::_nil();

PortableServer::POA_ptr 
BEAWrapper::Callbacks::root_poa = PortableServer::POA::_nil();

PortableServer::POA_ptr 
BEAWrapper::Callbacks::trasys_poa = PortableServer::POA::_nil();

PortableServer::POA_ptr 
BEAWrapper::Callbacks::persys_poa = PortableServer::POA::_nil();

PortableServer::POA_ptr 
BEAWrapper::Callbacks::peruser_poa = PortableServer::POA::_nil();


//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::ServantAlreadyActive::_narrow
//
//  FUNCTIONAL DESCRIPTION: 
//
//      Unlike the _narrow operation on object references the _narrow 
//  operation on exceptions returns a suitably typed pointer to the 
//  same exception parameter, not a pointer to a new exception.                
//  
//  If the parameter is a null pointer , the return type of _narrow is a 
//  null pointer. If the actual type of the parameter exception can be 
//  widened to the requested exception's type, then _narrow will return a
//  valid pointer to the parameter Exception. Otherwise, _narrow will 
//  return a null pointer.
//
//
BEAWrapper::Callbacks::ServantAlreadyActive * BEAWrapper::Callbacks::ServantAlreadyActive::_narrow(CORBA::Exception_ptr Exc)
{
    if (CORBA::UserException::_narrow(Exc) == 0 ||
        strcmp(Exc->OBB__id(), BEAWrapper::Callbacks::ServantAlreadyActive::_get_repos_id()) != 0)
	return 0;

    return (BEAWrapper::Callbacks::ServantAlreadyActive *) Exc;
}

//
//
//  FUNCTION NAME:
//      BEAWrapper::Callbacks::ServantAlreadyActive::ServantAlreadyActive
//
//  FUNCTIONAL DESCRIPTION:
//
//      Constructor for ServantAlreadyActive.
//

BEAWrapper::Callbacks::ServantAlreadyActive::ServantAlreadyActive ()
{
 OBB__id(BEAWrapper::Callbacks::ServantAlreadyActive::_get_repos_id());
}


//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::ServantAlreadyActive::operator=
//
//  FUNCTIONAL DESCRIPTION:
//
//      Assignment operator for ServantAlreadyActive class.
//

BEAWrapper::Callbacks::ServantAlreadyActive & 
BEAWrapper::Callbacks::ServantAlreadyActive::operator=(const BEAWrapper::Callbacks::ServantAlreadyActive &_obj)
{
   if (this == &_obj)
     return *this;
   OBB__id(_obj.OBB__id());
    return *this;
}


//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::ObjectAlreadyActive::_narrow
//
//  FUNCTIONAL DESCRIPTION:
//
//      Unlike the _narrow operation on object references the _narrow 
//  operation on exceptions returns a suitably typed pointer to the 
//  same exception parameter, not a pointer to a new exception.                
//  
//  If the parameter is a null pointer , the return type of _narrow is a 
//  null pointer. If the actual type of the parameter exception can be 
//  widened to the requested exception's type, then _narrow will return a
//  valid pointer to the parameter Exception. Otherwise, _narrow will 
//  return a null pointer.
//
//
BEAWrapper::Callbacks::ObjectAlreadyActive * BEAWrapper::Callbacks::ObjectAlreadyActive::_narrow(CORBA::Exception_ptr Exc)
{
    if (CORBA::UserException::_narrow(Exc) == 0 ||
        strcmp(Exc->OBB__id(), BEAWrapper::Callbacks::ObjectAlreadyActive::_get_repos_id()) != 0)
	return 0;

    return (BEAWrapper::Callbacks::ObjectAlreadyActive *) Exc;
}

//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::ObjectAlreadyActive 
//
//  FUNCTIONAL DESCRIPTION:
//
//      Constructor for ObjectAlreadyActive.
//

BEAWrapper::Callbacks::ObjectAlreadyActive::ObjectAlreadyActive ()
{
 OBB__id(BEAWrapper::Callbacks::ObjectAlreadyActive::_get_repos_id());
}



//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::ObjectAlreadyActive::operator=
//
//  FUNCTIONAL DESCRIPTION:
//
//      Assignment operator for ObjectAlreadyActive class
//

BEAWrapper::Callbacks::ObjectAlreadyActive & 
BEAWrapper::Callbacks::ObjectAlreadyActive::operator=(const BEAWrapper::Callbacks::ObjectAlreadyActive &_obj)
{
   if (this == &_obj)
     return *this;
   OBB__id(_obj.OBB__id());
    return *this;
}



//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::NotInRequest::_narrow
//
//  FUNCTIONAL DESCRIPTION:
//
//      Unlike the _narrow operation on object references the _narrow 
//  operation on exceptions returns a suitably typed pointer to the 
//  same exception parameter, not a pointer to a new exception.                
//  
//  If the parameter is a null pointer , the return type of _narrow is a 
//  null pointer. If the actual type of the parameter exception can be 
//  widened to the requested exception's type, then _narrow will return a
//  valid pointer to the parameter Exception. Otherwise, _narrow will 
//  return a null pointer.
//
//

BEAWrapper::Callbacks::NotInRequest * BEAWrapper::Callbacks::NotInRequest::_narrow(CORBA::Exception_ptr Exc)
{
    if (CORBA::UserException::_narrow(Exc) == 0 ||
        strcmp(Exc->OBB__id(), BEAWrapper::Callbacks::NotInRequest::_get_repos_id()) != 0)
	return 0;

    return (BEAWrapper::Callbacks::NotInRequest *) Exc;
}


//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::NotInRequest
//
//  FUNCTIONAL DESCRIPTION:
//
//      Constructor for NotInRequest class.
//

BEAWrapper::Callbacks::NotInRequest::NotInRequest ()
{
 OBB__id(BEAWrapper::Callbacks::NotInRequest::_get_repos_id());
}



//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::NotInRequest::operator=
//
//  FUNCTIONAL DESCRIPTION:
//
//      Assignment operator for NotInRequest class.
//

BEAWrapper::Callbacks::NotInRequest & 
BEAWrapper::Callbacks::NotInRequest::operator=(const BEAWrapper::Callbacks::NotInRequest &_obj)
{
   if (this == &_obj)
     return *this;
   OBB__id(_obj.OBB__id());
    return *this;
}


//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::Callbacks
//
//  FUNCTIONAL DESCRIPTION: 
//
//      Check if the orb_ptr is set, if not initialize the orb_ptr with the 
//  init_orb passed in by the user. It duplicates the pointer. If the orb_ptr 
//  is set throw an exception of CORBA::IMP_LIMIT. 
//
//      Check if the root_poa is nil, if so then obtain an object reference 
//  for the RootPOA by invoking resolve_initial_references on the ORB and
//  save the reference in root_poa. Thereafter invoke activate on the POA
//  manager of the root_poa. 
//
//
BEAWrapper::Callbacks::Callbacks (CORBA::ORB_ptr init_orb)
{
    if (CORBA::is_nil(orb))
    {
        orb = CORBA::ORB::_duplicate(init_orb);
    }
    else
    {
        throw CORBA::IMP_LIMIT();
    }
    if (CORBA::is_nil(root_poa))
    {
        CORBA::Object_ptr poa_obj_ptr = 0;
        try
        {
            poa_obj_ptr =  orb->resolve_initial_references("RootPOA");
        }
        catch (const CORBA::SystemException &)
        {

#ifdef BEAWRAPPER_DEBUG
            cout << "resolve_initial_references failed " << endl;
#endif
            throw ;
        }
        
        if (poa_obj_ptr == 0)
        {
            throw CORBA::INTERNAL();
        }
        
        root_poa = PortableServer::POA::_narrow (poa_obj_ptr);
        if (CORBA::is_nil(root_poa))
        {
            throw CORBA::INTERNAL();
        }
        CORBA::release(poa_obj_ptr);
        
        // Get the POA manager for root POA
        PortableServer::POAManager_ptr 
            root_mgr = root_poa->the_POAManager ();
        root_mgr->activate ();        
    }
}



//
//
//  FUNCTION NAME: BEAWrapper::Callbacks::start_transient
//
//  FUNCTIONAL DESCRIPTION:
//
//      If the rep_id is an empty string or the servant is nil it raises 
//  an exception of BAD_PARAM. If the root_poa is nil it returns a nil
//  object reference.
//
//      If the trasys_poa is nil, create a child POA by calling create_POA
// on the root_poa with a name for the child POA, the POA manager of the 
// root_poa & the policies(nil in this case) as its argument and
// save  the reference to the POA so obtained in trasys_poa. Then
// activate the servant by invoking activate_object on the POA with the 
// servant as its argument. Activating the servant generates an ObjectId, 
// which is passed on to the POA's create_reference_with_id  method together 
// with the rep_id passed in by the user to get an object reference to be 
// returned to the user. 
//
//      Since the POA's object ID uniqueness policy is UNIQUE_ID by default,
// this implies that activate_object cannot be invoked on the same servant 
// twice and it would raise ServantAlreadyActive exception.
//
CORBA::Object_ptr BEAWrapper::Callbacks::start_transient (
    PortableServer::Servant servant,
    const char * rep_id)

{
  CORBA::Object_ptr                 _resultval = CORBA::Object::_nil();
  CORBA::PolicyList pol_list; 

  if ((!rep_id) || (!servant))
  {
      throw CORBA::BAD_PARAM();
  }

  if (!CORBA::is_nil(root_poa))
  {
      PortableServer::POAManager_ptr 
          root_mgr = root_poa->the_POAManager ();
      
      try
      {
          if (CORBA::is_nil(trasys_poa))
          {
              trasys_poa = root_poa->find_POA("BEA:TRANSIENT", CORBA_FALSE);
              if (CORBA::is_nil(trasys_poa))
              {
                  trasys_poa = root_poa->create_POA 
                      ("BEA:TRANSIENT", root_mgr, pol_list);
              }
          }
          
          PortableServer::ObjectId * objectid = 
              trasys_poa->activate_object(servant);
	  PortableServer::ObjectId_var objectid_var = objectid; 
          _resultval = 
              trasys_poa->create_reference_with_id(*objectid, rep_id);      
	  root_mgr->activate ();
      }

      catch (PortableServer::POA::ServantAlreadyActive &)
      {
          throw BEAWrapper::Callbacks::ServantAlreadyActive();          
      }
      catch (PortableServer::POA::AdapterAlreadyExists &)
      {
          throw CORBA::INTERNAL();   
      }
      catch (PortableServer::POA::InvalidPolicy &)
      {
          throw CORBA::INTERNAL();   
      }
      catch (PortableServer::POA::WrongPolicy &)
      {
          throw CORBA::INTERNAL();
      }
     
  }
  
 return _resultval;

}

//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::start_persistent_systemid
//
//  FUNCTIONAL DESCRIPTION:
//
//      If the rep_id is an empty string or the servant is nil it raises an 
// exception of BAD_PARAM. 
//       
//      If persys_poa is nil, then create a list of policies to be set
// on the child POA, by invoking create_lifespan_policy on the POA with the
// appropriate arguments. Next create a child POA with the above policies, by 
// calling create_POA on the root_poa with a name for the child POA, the POA 
// manager of the root_poa & the desired policies as its argument and save the
// reference to the POA so obtained in persys_poa.
//
//      Now activate the servant by invoking activate_object on the child POA 
// with the servant as its argument.  Activating the servant generates an 
// ObjectId, which is passed on to the POA's create_reference_with_id method 
// together with the rep_id passed in by the user  to get an object reference
// to be returned to the user. Convert the ObjectId to string format by 
// invoking PortableServer::ObjectId_to_string  to be returned to the user. 
//     
//      Since the POA's object ID uniqueness policy is UNIQUE_ID by default, 
//  this implies that activate_object cannot be invoked on the same servant
//  twice and it would raise ServantAlreadyActive exception.
//
CORBA::Object_ptr BEAWrapper::Callbacks::start_persistent_systemid (
    PortableServer::Servant servant,
    const char * rep_id,
    char * & stroid )

{
    CORBA::Object_ptr                 _resultval = CORBA::Object::_nil();
    
    if ((!rep_id) || (!servant))
    {
        throw CORBA::BAD_PARAM();
    }
    
    if (!CORBA::is_nil(root_poa))
    {
        PortableServer::POAManager_ptr 
            root_mgr = root_poa->the_POAManager ();
        try
        {
            if (CORBA::is_nil(persys_poa))
            {
                persys_poa = root_poa->
                    find_POA("BEA:PERSISTENT_SYSTEMID", CORBA_FALSE);
              if (CORBA::is_nil(persys_poa))
              {
                  CORBA::PolicyList pol_list(1); 
                  pol_list.length(1);
                  pol_list[0] = 
                  root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
                  persys_poa = root_poa->create_POA 
                      ("BEA:PERSISTENT_SYSTEMID", root_mgr, pol_list);
              }
                
            }
            PortableServer::ObjectId * objectid = 
                persys_poa->activate_object(servant);
	    PortableServer::ObjectId_var objectid_var = objectid; 
            _resultval = 
                persys_poa->create_reference_with_id(*objectid, rep_id); 
	    CORBA::ULong len = objectid->length();
	    stroid = CORBA::string_alloc(len);
	    if (!stroid)
	      {
		throw CORBA::NO_MEMORY();
	      }
	    strncpy(stroid, (const char *)objectid->OBB__data(), len);
	    stroid[len] = '\0';
            root_mgr->activate ();
        }

      catch (PortableServer::POA::ServantAlreadyActive &)
      {
          throw BEAWrapper::Callbacks::ServantAlreadyActive();          
      }
      catch (PortableServer::POA::AdapterAlreadyExists &)
      {
          throw CORBA::INTERNAL();   
      }
      catch (PortableServer::POA::InvalidPolicy &)
      {
          throw CORBA::INTERNAL();   
      }
      catch (PortableServer::POA::WrongPolicy &)
      {
          throw CORBA::INTERNAL();
      }

    }    
    return _resultval;
    
}

//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::restart_persistent_systemid
//
//  FUNCTIONAL DESCRIPTION:
//
//      If the rep_id is an empty string or the servant is nil or the ObjectId
// passed in by the user is an empty string  or the ObjectId passed in by the
// user was not previously assigned by this POA it raises an exception of
// BAD_PARAM.
//
//      If  persys_poa is nil, then create a list of policies to be set 
// on the child POA, by invoking create_lifespan_policy on the POA with the
// appropriate arguments. Next create a child POA with the above policies, by 
// calling create_POA on the root_poa with a name for the child POA, the POA 
// manager of the root_poa & the desired policies as its argument and save the
// reference to the POA so obtained in persys_poa.
//
//      Convert the stringified ObjectId  passed in by the user by invoking 
// PortableServer::string_to_ObjectId to the ObjectId(i.e a sequence of octet)
// format. Using the ObjectId so obtained activate the servant by invoking 
// activate_object_with_id on  the childPOA. The ObjectId and the rep_id 
// provided  by the user is then passed on to the child POA's 
// create_reference_with_id  method to get an object reference to be returned 
// to the user. 
//        
//      Since the POA's object ID uniqueness policy is UNIQUE_ID by default, 
// this implies that  activate_object_with_id cannot be invoked on the same 
// servant twice and it would raise the ServantAlreadyActive exception. If the
// object denoted by the ObjectId value is already active in this POA , the
// ObjectAlreadyActive exception is raised.
//
//

CORBA::Object_ptr BEAWrapper::Callbacks::restart_persistent_systemid (
    PortableServer::Servant servant,
    const char * rep_id,
    const char * stroid)

{
    CORBA::Object_ptr                 _resultval = CORBA::Object::_nil();
    if ((!rep_id) || (!servant) || (!stroid))
    {
        throw CORBA::BAD_PARAM();
    }

    if (!CORBA::is_nil(root_poa))
    {
        PortableServer::POAManager_ptr 
            root_mgr = root_poa->the_POAManager ();
        try
        {
            if (CORBA::is_nil(persys_poa))
            {
                persys_poa = root_poa->
                    find_POA("BEA:PERSISTENT_SYSTEMID", CORBA_FALSE);
                    if (CORBA::is_nil(persys_poa))
                    {
                        CORBA::PolicyList pol_list(1); 
                        pol_list.length(1);
                        pol_list[0] = 
                  root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
                        persys_poa = root_poa->create_POA 
                            ("BEA:PERSISTENT_SYSTEMID", root_mgr, pol_list);
                    }
            }
	    
	    CORBA::ULong len = strlen(stroid);
	    CORBA::Octet * buf_ptr = PortableServer::ObjectId::allocbuf (len);
	    if( ! buf_ptr )
	      throw CORBA::NO_MEMORY();
	    memcpy (buf_ptr, stroid, len);
	    PortableServer::ObjectId * objectid
	      = new ORBNEWTHROW PortableServer::ObjectId(len, len, buf_ptr, CORBA_TRUE);
	    if( ! objectid )
	      {
		PortableServer::ObjectId::freebuf(buf_ptr);
		throw CORBA::NO_MEMORY();
	      }

	    PortableServer::ObjectId_var objectid_var = objectid; 
            persys_poa->activate_object_with_id(*objectid, servant);
            _resultval = 
                persys_poa->create_reference_with_id(*objectid, rep_id);
            root_mgr->activate ();
        }
        catch (PortableServer::POA::ServantAlreadyActive &)
        {
            throw BEAWrapper::Callbacks::ServantAlreadyActive();
            
        }        
        catch (PortableServer::POA::ObjectAlreadyActive &)
        {
            throw BEAWrapper::Callbacks::ObjectAlreadyActive();
            
        }
        catch (PortableServer::POA::AdapterAlreadyExists &)
        {
            throw CORBA::INTERNAL();   
        }
        catch (PortableServer::POA::InvalidPolicy &)
        {
            throw CORBA::INTERNAL();   
        }
        catch (PortableServer::POA::WrongPolicy &)
        {
            throw CORBA::INTERNAL();
        }
    }

    return _resultval;
    
}

//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::start_persistent_userid
//
//  FUNCTIONAL DESCRIPTION:
//
//      If the rep_id is an empty string or the servant is nil or the ObjectId
// passed in by the user is an empty string  it raises an exception of
// BAD_PARAM.
//    
//      If peruser_poa is nil, if so create a list of policies to be set on the
// child POA, by invoking create_lifespan_policy & create_id_assignment_policy
// on the POA with the appropriate arguments. Next create a child POA with the
// above policies, by calling create_POA on the root_poa with a name for the 
// child POA, the POA manager of the root_poa & the policies as its argument
// and save a reference to the POA so obtained in peruser_poa. 
//
//      Convert the stringified ObjectId  passed in by the user by invoking 
// PortableServer::string_to_ObjectId to the ObjectId(i.e a sequence of octet)
// format. Using the ObjectId so obtained activate the servant by invoking 
// activate_object_with_id on the child POA with the servant and the ObjectId
// passed in by the user as its argument. The ObjectId and the rep_id provided
// in by the user is then passed on to the child POA's
// create_reference_with_id  method to get an object reference to be 
// returned to the user. 
//      
//      Since the POA's object ID uniqueness policy is UNIQUE_ID by default,
// this implies that  activate_object_with_id cannot be invoked on the same 
// servant twice and it would raise the ServantAlreadyActive exception. If the
// object denoted by the ObjectId value is already active in this POA, the 
// ObjectAlreadyActive exception is raised.
//

CORBA::Object_ptr BEAWrapper::Callbacks::start_persistent_userid (
    PortableServer::Servant servant,
    const char * rep_id,
    const char * oid)

{
    CORBA::Object_ptr                 _resultval = CORBA::Object::_nil();
    
    if ((!rep_id) || (!servant) || (!oid))
    {
        throw CORBA::BAD_PARAM();
    }
    
    if (!CORBA::is_nil(root_poa))
    {
        PortableServer::POAManager_ptr 
            root_mgr = root_poa->the_POAManager ();
        try
        {   
            if (CORBA::is_nil(peruser_poa))
            {
                peruser_poa = root_poa->
                    find_POA("BEA:PERSISTENT_USERID", CORBA_FALSE);
                if (CORBA::is_nil(peruser_poa))
                {
                    CORBA::PolicyList pol_list(2);
                    pol_list.length(2);
                    pol_list[0] = 
                        root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
                    pol_list[1] = 
                        root_poa->create_id_assignment_policy(PortableServer::USER_ID);
                    peruser_poa = root_poa->create_POA 
                        ("BEA:PERSISTENT_USERID", root_mgr, pol_list);
                }
            }
            PortableServer::ObjectId * objectid = 
                PortableServer::string_to_ObjectId(oid);
	     PortableServer::ObjectId_var objectid_var = objectid; 
            peruser_poa->activate_object_with_id(*objectid, servant);
            _resultval = 
                peruser_poa->create_reference_with_id(*objectid, rep_id); 
            root_mgr->activate ();
        }

        catch (PortableServer::POA::ServantAlreadyActive &)
        {
            throw BEAWrapper::Callbacks::ServantAlreadyActive();
        }        
        catch (PortableServer::POA::ObjectAlreadyActive &)
        {
            throw BEAWrapper::Callbacks::ObjectAlreadyActive();
            
        }
        catch (PortableServer::POA::AdapterAlreadyExists &)
        {
            throw CORBA::INTERNAL();   
        }
        catch (PortableServer::POA::InvalidPolicy &)
        {
            throw CORBA::INTERNAL();   
        }
        catch (PortableServer::POA::WrongPolicy &)
        {
            throw CORBA::INTERNAL();
        }
    }

    return _resultval;

}

//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::stop_object
//
//  FUNCTIONAL DESCRIPTION:
//
//      As there is no information about which of the three child POA's 
//  activated this servant. This operation calls each of the child POA's 
//  servant_to_id method with the servant that was passed in by the user as
//  an argument. The child POA raises an exception of  ServantNotActive if
//  that was not the child POA that was associated with this servant.
//  Otherwise the child POA returns an ObjectId which is passed to 
//  deactivate_object.  If there is no active object associated with the 
//  specified ObjectID, deactivate_object raises an ObjectNotActive exception
//  which will be ignored.
//
//      Also the same servant could be active in more than one POA so it
//  needs to be deactivated from all the POA's. 
//
//
void BEAWrapper::Callbacks::stop_object (
    PortableServer::Servant servant)

{
    PortableServer::ObjectId * objectid = 0;
    try
    {
        if (!CORBA::is_nil(trasys_poa))
        {   
            try
            {
                objectid = trasys_poa->servant_to_id(servant);
            }
            catch (CORBA::SystemException & exc)
            {
                if (strcmp(exc.get_id(),
                   "IDL:omg.org/PortableServer/POA/ServantNotActive:1.0") != 0)
                {
                    throw;
                }
            }

            if (objectid != 0)
            {
                trasys_poa->deactivate_object(*objectid);
		delete objectid;
                objectid = 0;

#ifdef BEAWRAPPER_DEBUG
                cout << "Deactivated in transient " << endl;
#endif
            }
            
        }
        if (!CORBA::is_nil(persys_poa))
        {
            try
            {
                objectid = persys_poa->servant_to_id(servant);
            }
            catch (CORBA::SystemException & exc)
            {
                if (strcmp(exc.get_id(),
                   "IDL:omg.org/PortableServer/POA/ServantNotActive:1.0") != 0)
                {
                    throw;
                }
             
            }
            if (objectid != 0)
            {
                persys_poa->deactivate_object(*objectid);
		delete objectid;
                objectid = 0;
#ifdef BEAWRAPPER_DEBUG
                cout << "Deactivated in persistent/system " << endl;
#endif
            }
        }
        if (!CORBA::is_nil(peruser_poa))
        {
            try
            {
                objectid = peruser_poa->servant_to_id(servant);
            }
            catch (CORBA::SystemException & exc)
            {
                if (strcmp(exc.get_id(),
                 "IDL:omg.org/PortableServer/POA/ServantNotActive:1.0") != 0)
                {
                    throw;
                }
            }

            if (objectid != 0)
            {
                peruser_poa->deactivate_object(*objectid);
		delete objectid;
#ifdef BEAWRAPPER_DEBUG
                cout << "Deactivated in persistent/user " << endl;
#endif
                return;
            }
        }
    }
    catch (CORBA::SystemException & exc)
    {
        if (strcmp(exc.get_id(),
                   "IDL:omg.org/PortableServer/POA/ObjectNotActive:1.0") == 0)
        {
#ifdef BEAWRAPPER_DEBUG
            cout << "Caught but ignored exception -  " ;
            cout << exc.get_id() << endl;
#endif
        }
    }
 return;

}



//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::stop_all_objects
//
//  FUNCTIONAL DESCRIPTION:
//
//      Check to see if each of the poa pointers are set then call the 
//  destroy operation for  each one that is set. This could cause undefined 
//  behavior if this class has been instantiated more than once since there
//  are only three child POA's created and these are destroyed. The POA 
//  manager of the RootPoa is deactivated & the Root POA is destroyed by the
//  ORB when ORB::shutdown is called.  
//
//
void BEAWrapper::Callbacks::stop_all_objects ()

{

    if (!CORBA::is_nil(trasys_poa))
    {
        trasys_poa->destroy(CORBA_TRUE, CORBA_TRUE);
        trasys_poa = PortableServer::POA::_nil();
    }
    if (!CORBA::is_nil(persys_poa))
    {
        persys_poa->destroy(CORBA_TRUE, CORBA_TRUE);
        persys_poa = PortableServer::POA::_nil();
    }
    if (!CORBA::is_nil(peruser_poa))
    {
        peruser_poa->destroy(CORBA_TRUE, CORBA_TRUE);
        peruser_poa = PortableServer::POA::_nil();
    }

    
    return;
}

//
//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::get_string_oid
//
//  FUNCTIONAL DESCRIPTION:
//
//       First obtain an instance of Current by invoking 
//  CORBA::ORB::resolve_initial_references("POACurrent") on the ORB. Next get
//  the ObjectID  identifying the object in whose context it is called by 
//  calling  get_object_id on POACurrent. Then invoke the static member 
//  function PortableServer::ObjectId_to_string passing in the ObjectID 
//  returned from the previous operation to obtain a string version of the
//  ObjectID. The string version of the ObjectID needs to be freed by the 
//  user using CORBA::string_free. The string returned by get_string_oid
//  is meaningful to users only in the case when the object reference was
//  created by the start_persistent_userid function. However the 
//  get_string_oid operation is valid on all POA's.
//
//
//  The function PortableServer::ObjectId_to_string can throw BAD_PARAM and
//  NO_MEMORY exceptions which are thrown back to the user. The get_object_id 
//  call can return a NoContext exception if called outside the context of a 
//  POA-dispatched operation. In such a situation this operation will throw a 
//  NotInRequest exception.
//
//

char * BEAWrapper::Callbacks::get_string_oid ()

{
    char * stroid = 0;
    
    CORBA::Object_ptr current_obj_ptr = 
        orb->resolve_initial_references("POACurrent");
    if (current_obj_ptr == 0)
    {
        return stroid;
    }
    PortableServer::Current_ptr curr_ptr = PortableServer::Current::_narrow (
        current_obj_ptr);
    if (curr_ptr == 0)
    {
        return stroid;
    }
    
    try
    {
        PortableServer::ObjectId * objectid = curr_ptr->get_object_id();
	PortableServer::ObjectId_var objectid_var = objectid;
	CORBA::ULong len = objectid->length();
	stroid = CORBA::string_alloc(len);
	if (!stroid)
	  {
	    throw CORBA::NO_MEMORY();
	  }
	strncpy(stroid, (const char *)objectid->OBB__data(), len);
	stroid[len] = '\0';
    }
    catch (PortableServer::Current::NoContext &)
    {
      throw BEAWrapper::Callbacks::NotInRequest();
    }
    
    return stroid;
    
}



//
//  FUNCTION NAME: 	BEAWrapper::Callbacks::~Callbacks
//
//  FUNCTIONAL DESCRIPTION:
//
//      This calls the stop_all_objects operation.  
//
//

BEAWrapper::Callbacks::~Callbacks ()

{
    trasys_poa = PortableServer::POA::_nil();
    persys_poa = PortableServer::POA::_nil();
    peruser_poa = PortableServer::POA::_nil();

    root_poa = PortableServer::POA::_nil();

    CORBA::release (orb);
    orb = CORBA::ORB::_nil();

}



