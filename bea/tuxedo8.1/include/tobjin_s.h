/*******************************************************************
 * Created Mon Jan 27 07:37:48 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Skeleton include file: (tobjin_s.h)
 * ----------------------------------------------------------------
 *
 * This module contains definitions and prototypes for the skeleton
 * classes for the following interfaces:
 *
 *    InitialReferences_i
 *    DelegatedCurrent_i
 *    DelegatedAuthenticator_i
 *    DelegatedBiDir_i

 *
 */
#ifndef _tobjin_s_h
#define _tobjin_s_h

#include <string.h>
#include "orbminor.h"
#include <Tobj_ServantBase.h>

#include "tobjin_c.h"

class POA_TobjInternal
{
    public:
        class InitialReferences : public Tobj_ServantBase 
        {
            public:

                virtual ::CORBA::Object_ptr get (
                    const char * id) = 0; 

                virtual ::TobjInternal::ObjectIdList * list () = 0; 

                virtual void get_references (
                    ::TobjInternal::Version & v,
                    ::TobjInternal::InitRefList_out refs,
                    ::CORBA::String_out secUid) = 0; 

                ::TobjInternal::InitialReferences_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~InitialReferences(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
            class OTSImpl
            {
                public:
                    class DelegatedCurrent : public Tobj_ServantBase 
                    {
                        public:

                            virtual ::TobjInternal::ATMIerrors begin (
                                ::CORBA::ULong seconds) = 0; 

                            virtual ::TobjInternal::ATMIerrors commit (
                                ::CORBA::Boolean report_heuristic) = 0; 

                            virtual ::TobjInternal::ATMIerrors rollback () = 0; 

                            virtual ::TobjInternal::ATMIerrors rollback_only () = 0; 

                            virtual ::TobjInternal::ATMIerrors get_status (
                                ::TobjInternal::OTSImpl::TxStatus_out status) = 0; 

                            virtual ::TobjInternal::ATMIerrors get_transaction_name (
                                ::CORBA::String_out name) = 0; 

                            virtual ::TobjInternal::ATMIerrors suspend (
                                ::TobjInternal::OTSImpl::cntl_out which) = 0; 

                            virtual ::TobjInternal::ATMIerrors resume (
                                 const ::TobjInternal::OTSImpl::cntl & which) = 0; 

                            virtual ::TobjInternal::ATMIerrors get_control (
                                ::TobjInternal::OTSImpl::cntl_out which) = 0; 

                            ::TobjInternal::OTSImpl::DelegatedCurrent_ptr _this();

                            void invoke (::CORBA::ServerRequest_ptr _nasreq);

                            ::CORBA::RepositoryId _primary_interface (
                            const PortableServer::ObjectId &,
                                PortableServer::POA_ptr);

                        protected:
                            virtual ~DelegatedCurrent(){ }

                        private:
                            OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

                    };
            };

            class SecImpl
            {
                public:
                    class DelegatedAuthenticator : public Tobj_ServantBase 
                    {
                        public:

                            virtual ::TobjInternal::ATMIerrors get_auth (
                                ::Tobj::AuthType_out type) = 0; 

                            virtual ::TobjInternal::ATMIerrors logon (
                                const char * user_name,
                                const char * client_name,
                                 const ::Tobj::UserAuthData & user_data,
                                 const ::Tobj::LogonData & logon_data) = 0; 

                            virtual ::TobjInternal::ATMIerrors logoff () = 0; 

                            ::TobjInternal::SecImpl::DelegatedAuthenticator_ptr _this();

                            void invoke (::CORBA::ServerRequest_ptr _nasreq);

                            ::CORBA::RepositoryId _primary_interface (
                            const PortableServer::ObjectId &,
                                PortableServer::POA_ptr);

                        protected:
                            virtual ~DelegatedAuthenticator(){ }

                        private:
                            OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

                    };
            };

            class CallbackImpl
            {
                public:
                    class DelegatedBiDir : public Tobj_ServantBase 
                    {
                        public:

                            virtual void register_callback_port (
                                ::CORBA::Object_ptr objref) = 0; 

                            ::TobjInternal::CallbackImpl::DelegatedBiDir_ptr _this();

                            void invoke (::CORBA::ServerRequest_ptr _nasreq);

                            ::CORBA::RepositoryId _primary_interface (
                            const PortableServer::ObjectId &,
                                PortableServer::POA_ptr);

                        protected:
                            virtual ~DelegatedBiDir(){ }

                        private:
                            OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

                    };
            };

};

#endif
