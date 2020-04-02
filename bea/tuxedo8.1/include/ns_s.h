/*******************************************************************
 * Created Mon Jan 27 07:37:44 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Skeleton include file: (ns_s.h)
 * ----------------------------------------------------------------
 *
 * This module contains definitions and prototypes for the skeleton
 * classes for the following interfaces:
 *
 *    NamingContext_i
 *    BindingIterator_i
 *    NamingContextExt_i

 *
 */
#ifndef _ns_s_h
#define _ns_s_h

#include <string.h>
#include "orbminor.h"
#include <PortableServer.h>

#include "ns_c.h"

class POA_CosNaming
{
    public:
        class NamingContext : public PortableServer::RefCountServantBase 
        {
            public:

                virtual void bind (
                     const ::CosNaming::Name & n,
                    ::CORBA::Object_ptr obj) = 0; 

                virtual void rebind (
                     const ::CosNaming::Name & n,
                    ::CORBA::Object_ptr obj) = 0; 

                virtual void bind_context (
                     const ::CosNaming::Name & n,
                    ::CosNaming::NamingContext_ptr nc) = 0; 

                virtual void rebind_context (
                     const ::CosNaming::Name & n,
                    ::CosNaming::NamingContext_ptr nc) = 0; 

                virtual ::CORBA::Object_ptr resolve (
                     const ::CosNaming::Name & n) = 0; 

                virtual void unbind (
                     const ::CosNaming::Name & n) = 0; 

                virtual ::CosNaming::NamingContext_ptr new_context () = 0; 

                virtual ::CosNaming::NamingContext_ptr bind_new_context (
                     const ::CosNaming::Name & n) = 0; 

                virtual void destroy () = 0; 

                virtual void list (
                    ::CORBA::ULong how_many,
                    ::CosNaming::BindingList_out bl,
                    ::CosNaming::BindingIterator_out bi) = 0; 

                ::CosNaming::NamingContext_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~NamingContext(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class BindingIterator : public PortableServer::RefCountServantBase 
        {
            public:

                virtual ::CORBA::Boolean next_one (
                    ::CosNaming::Binding_out b) = 0; 

                virtual ::CORBA::Boolean next_n (
                    ::CORBA::ULong how_many,
                    ::CosNaming::BindingList_out bl) = 0; 

                virtual void destroy () = 0; 

                ::CosNaming::BindingIterator_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~BindingIterator(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class NamingContextExt : public PortableServer::RefCountServantBase 
        {
            public:

                virtual void bind (
                     const ::CosNaming::Name & n,
                    ::CORBA::Object_ptr obj) = 0; 

                virtual void rebind (
                     const ::CosNaming::Name & n,
                    ::CORBA::Object_ptr obj) = 0; 

                virtual void bind_context (
                     const ::CosNaming::Name & n,
                    ::CosNaming::NamingContext_ptr nc) = 0; 

                virtual void rebind_context (
                     const ::CosNaming::Name & n,
                    ::CosNaming::NamingContext_ptr nc) = 0; 

                virtual ::CORBA::Object_ptr resolve (
                     const ::CosNaming::Name & n) = 0; 

                virtual void unbind (
                     const ::CosNaming::Name & n) = 0; 

                virtual ::CosNaming::NamingContext_ptr new_context () = 0; 

                virtual ::CosNaming::NamingContext_ptr bind_new_context (
                     const ::CosNaming::Name & n) = 0; 

                virtual void destroy () = 0; 

                virtual void list (
                    ::CORBA::ULong how_many,
                    ::CosNaming::BindingList_out bl,
                    ::CosNaming::BindingIterator_out bi) = 0; 

                virtual ::CosNaming::NamingContextExt::StringName to_string (
                     const ::CosNaming::Name & n) = 0; 

                virtual ::CosNaming::Name * to_name (
                    const char * sn) = 0; 

                virtual ::CosNaming::NamingContextExt::URLString to_url (
                    const char * addr,
                    const char * sn) = 0; 

                virtual ::CORBA::Object_ptr resolve_str (
                    const char * n) = 0; 

                ::CosNaming::NamingContextExt_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~NamingContextExt(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
};

#endif
