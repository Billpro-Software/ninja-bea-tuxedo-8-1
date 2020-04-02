/*******************************************************************
 * Created Mon Jan 27 07:37:46 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Skeleton include file: (security_s.h)
 * ----------------------------------------------------------------
 *
 * This module contains definitions and prototypes for the skeleton
 * classes for the following interfaces:
 *
 *    Current_i
 *    PrincipalAuthenticator_i
 *    Credentials_i
 *    Current_i

 *
 */
#ifndef _security_s_h
#define _security_s_h

#include <string.h>
#include "orbminor.h"
#include <Tobj_ServantBase.h>

#include "security_c.h"

class POA_SecurityLevel1
{
    public:
        class Current : public Tobj_ServantBase 
        {
            public:

                virtual ::Security::AttributeList * get_attributes (
                     const ::Security::AttributeTypeList & attributes) = 0; 

                ::SecurityLevel1::Current_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Current(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
};

class POA_SecurityLevel2
{
    public:
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

                ::SecurityLevel2::PrincipalAuthenticator_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~PrincipalAuthenticator(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class Credentials : public Tobj_ServantBase 
        {
            public:

                virtual ::Security::AttributeList * get_attributes (
                     const ::Security::AttributeTypeList & attributes) = 0; 

                virtual ::CORBA::Boolean is_valid (
                    ::Security::UtcT_out expiry_time) = 0; 

                virtual ::Security::AssociationOptions invocation_options_supported () = 0; 

                virtual void invocation_options_supported (
                    ::Security::AssociationOptions invocation_options_supported) = 0; 

                virtual ::Security::AssociationOptions invocation_options_required () = 0; 

                virtual void invocation_options_required (
                    ::Security::AssociationOptions invocation_options_required) = 0; 

                ::SecurityLevel2::Credentials_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Credentials(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class Current : public Tobj_ServantBase 
        {
            public:

                virtual ::Security::AttributeList * get_attributes (
                     const ::Security::AttributeTypeList & attributes) = 0; 

                virtual void set_credentials (
                    ::Security::CredentialType cred_type,
                    ::SecurityLevel2::Credentials_ptr cred) = 0; 

                virtual ::SecurityLevel2::Credentials_ptr get_credentials (
                    ::Security::CredentialType cred_type) = 0; 

                virtual ::SecurityLevel2::PrincipalAuthenticator_ptr principal_authenticator () = 0; 

                ::SecurityLevel2::Current_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Current(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
};

#endif
