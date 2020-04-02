/*******************************************************************
 * Created Mon Jan 27 07:37:44 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Skeleton include file: (lcs_s.h)
 * ----------------------------------------------------------------
 *
 * This module contains definitions and prototypes for the skeleton
 * classes for the following interfaces:
 *
 *    FactoryFinder_i
 *    LifeCycleObject_i
 *    GenericFactory_i

 *
 */
#ifndef _lcs_s_h
#define _lcs_s_h

#include <string.h>
#include "orbminor.h"
#include <Tobj_ServantBase.h>

#include "lcs_c.h"

class POA_CosLifeCycle
{
    public:
        class FactoryFinder : public Tobj_ServantBase 
        {
            public:

                virtual ::CosLifeCycle::Factories * find_factories (
                     const ::CosLifeCycle::Key & factory_key) = 0; 

                ::CosLifeCycle::FactoryFinder_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~FactoryFinder(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class LifeCycleObject : public Tobj_ServantBase 
        {
            public:

                virtual ::CosLifeCycle::LifeCycleObject_ptr copy (
                    ::CosLifeCycle::FactoryFinder_ptr there,
                     const ::CosLifeCycle::Criteria & the_criteria) = 0; 

                virtual void move (
                    ::CosLifeCycle::FactoryFinder_ptr there,
                     const ::CosLifeCycle::Criteria & the_criteria) = 0; 

                virtual void remove () = 0; 

                ::CosLifeCycle::LifeCycleObject_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~LifeCycleObject(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class GenericFactory : public Tobj_ServantBase 
        {
            public:

                virtual ::CORBA::Boolean supports (
                     const ::CosLifeCycle::Key & k) = 0; 

                virtual ::CORBA::Object_ptr create_object (
                     const ::CosLifeCycle::Key & k,
                     const ::CosLifeCycle::Criteria & the_criteria) = 0; 

                ::CosLifeCycle::GenericFactory_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~GenericFactory(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
};

#endif
