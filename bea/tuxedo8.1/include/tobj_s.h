/*******************************************************************
 * Created Mon Jan 27 07:37:46 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Skeleton include file: (tobj_s.h)
 * ----------------------------------------------------------------
 *
 * This module contains definitions and prototypes for the skeleton
 * classes for the following interfaces:
 *
 *    FactoryFinder_i
 *    TransactionCurrent_i
 *    PrincipalAuthenticator_i

 *
 */
#ifndef _tobj_s_h
#define _tobj_s_h

#include <string.h>
#include "orbminor.h"
#include <Tobj_ServantBase.h>

#include "tobj_c.h"

class POA_Tobj
{
    public:
        class FactoryFinder : public Tobj_ServantBase 
        {
            public:

                virtual ::CosLifeCycle::Factories * find_factories (
                     const ::CosLifeCycle::Key & factory_key) = 0; 

                virtual ::CosLifeCycle::Factory_ptr find_one_factory (
                     const ::CosLifeCycle::Key & factory_key) = 0; 

                virtual ::CosLifeCycle::Factory_ptr find_one_factory_by_id (
                    const char * factory_id) = 0; 

                virtual ::CosLifeCycle::Factories * find_factories_by_id (
                    const char * factory_id) = 0; 

                virtual ::Tobj::FactoryListing * list_factories () = 0; 

                ::Tobj::FactoryFinder_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~FactoryFinder(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class TransactionCurrent : public Tobj_ServantBase 
        {
            public:

                virtual void begin () = 0; 

                virtual void commit (
                    ::CORBA::Boolean report_heuristics) = 0; 

                virtual void rollback () = 0; 

                virtual void rollback_only () = 0; 

                virtual ::CosTransactions::Status get_status () = 0; 

                virtual ::CORBA::Char * get_transaction_name () = 0; 

                virtual void set_timeout (
                    ::CORBA::ULong seconds) = 0; 

                virtual ::CosTransactions::Control_ptr get_control () = 0; 

                virtual ::CosTransactions::Control_ptr suspend () = 0; 

                virtual void resume (
                    ::CosTransactions::Control_ptr which) = 0; 

                virtual void open_xa_rm () = 0; 

                virtual void close_xa_rm () = 0; 

                ::Tobj::TransactionCurrent_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~TransactionCurrent(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class PrincipalAuthenticator : public Tobj_ServantBase 
        {
            public:

                virtual ::Security::AuthenticationStatus authenticate (
                    ::Security::AuthenticationMethod method,
                    const char * security_name,
                     const ::Security::Opaque & auth_data,
                     const ::Security::AttributeList & privileges,
                    ::SecurityLevel2::Credentials_out creds,
                    ::Security::Opaque_out continuation_data,
                    ::Security::Opaque_out auth_specific_data) = 0; 

                virtual ::Security::AuthenticationStatus continue_authentication (
                     const ::Security::Opaque & response_data,
                    ::SecurityLevel2::Credentials_ptr creds,
                    ::Security::Opaque_out continuation_data,
                    ::Security::Opaque_out auth_specific_data) = 0; 

                virtual ::Tobj::AuthType get_auth_type () = 0; 

                virtual ::Security::AuthenticationStatus logon (
                    const char * user_name,
                    const char * client_name,
                    const char * system_password,
                    const char * user_password,
                     const ::Tobj::UserAuthData & user_data) = 0; 

                virtual void logoff () = 0; 

                virtual void build_auth_data (
                    const char * user_name,
                    const char * client_name,
                    const char * system_password,
                    const char * user_password,
                     const ::Tobj::UserAuthData & user_data,
                    ::Security::Opaque_out auth_data,
                    ::Security::AttributeList_out privileges) = 0; 

                ::Tobj::PrincipalAuthenticator_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~PrincipalAuthenticator(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
};

#endif
