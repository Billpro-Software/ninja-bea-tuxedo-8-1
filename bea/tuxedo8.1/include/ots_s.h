/*******************************************************************
 * Created Mon Jan 27 07:37:45 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Skeleton include file: (ots_s.h)
 * ----------------------------------------------------------------
 *
 * This module contains definitions and prototypes for the skeleton
 * classes for the following interfaces:
 *
 *    Current_i
 *    TransactionFactory_i
 *    Control_i
 *    Terminator_i
 *    Coordinator_i
 *    RecoveryCoordinator_i
 *    Resource_i
 *    TransactionalObject_i
 *    Synchronization_i
 *    SubtransactionAwareResource_i

 *
 */
#ifndef _ots_s_h
#define _ots_s_h

#include <string.h>
#include "orbminor.h"
#include <Tobj_ServantBase.h>

#include "ots_c.h"

class POA_CosTransactions
{
    public:
        class Current : public Tobj_ServantBase 
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

                ::CosTransactions::Current_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Current(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class TransactionFactory : public Tobj_ServantBase 
        {
            public:

                virtual ::CosTransactions::Control_ptr create (
                    ::CORBA::ULong time_out) = 0; 

                virtual ::CosTransactions::Control_ptr recreate (
                     const ::CosTransactions::PropagationContext & ctx) = 0; 

                ::CosTransactions::TransactionFactory_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~TransactionFactory(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class Control : public Tobj_ServantBase 
        {
            public:

                virtual ::CosTransactions::Terminator_ptr get_terminator () = 0; 

                virtual ::CosTransactions::Coordinator_ptr get_coordinator () = 0; 

                ::CosTransactions::Control_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Control(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class Terminator : public Tobj_ServantBase 
        {
            public:

                virtual void commit (
                    ::CORBA::Boolean report_heuristics) = 0; 

                virtual void rollback () = 0; 

                ::CosTransactions::Terminator_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Terminator(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class Coordinator : public Tobj_ServantBase 
        {
            public:

                virtual ::CosTransactions::Status get_status () = 0; 

                virtual ::CosTransactions::Status get_parent_status () = 0; 

                virtual ::CosTransactions::Status get_top_level_status () = 0; 

                virtual ::CORBA::Boolean is_same_transaction (
                    ::CosTransactions::Coordinator_ptr tc) = 0; 

                virtual ::CORBA::Boolean is_related_transaction (
                    ::CosTransactions::Coordinator_ptr tc) = 0; 

                virtual ::CORBA::Boolean is_ancestor_transaction (
                    ::CosTransactions::Coordinator_ptr tc) = 0; 

                virtual ::CORBA::Boolean is_descendant_transaction (
                    ::CosTransactions::Coordinator_ptr tc) = 0; 

                virtual ::CORBA::Boolean is_top_level_transaction () = 0; 

                virtual ::CORBA::ULong hash_transaction () = 0; 

                virtual ::CORBA::ULong hash_top_level_tran () = 0; 

                virtual ::CosTransactions::RecoveryCoordinator_ptr register_resource (
                    ::CosTransactions::Resource_ptr res) = 0; 

                virtual void register_synchronization (
                    ::CosTransactions::Synchronization_ptr sync) = 0; 

                virtual void register_subtran_aware (
                    ::CosTransactions::SubtransactionAwareResource_ptr res) = 0; 

                virtual void rollback_only () = 0; 

                virtual ::CORBA::Char * get_transaction_name () = 0; 

                virtual ::CosTransactions::Control_ptr create_subtransaction () = 0; 

                virtual ::CosTransactions::PropagationContext * get_txcontext () = 0; 

                ::CosTransactions::Coordinator_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Coordinator(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class RecoveryCoordinator : public Tobj_ServantBase 
        {
            public:

                virtual ::CosTransactions::Status replay_completion (
                    ::CosTransactions::Resource_ptr res) = 0; 

                ::CosTransactions::RecoveryCoordinator_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~RecoveryCoordinator(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class Resource : public Tobj_ServantBase 
        {
            public:

                virtual ::CosTransactions::Vote prepare () = 0; 

                virtual void rollback () = 0; 

                virtual void commit () = 0; 

                virtual void commit_one_phase () = 0; 

                virtual void forget () = 0; 

                ::CosTransactions::Resource_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Resource(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class TransactionalObject : public Tobj_ServantBase 
        {
            public:

                ::CosTransactions::TransactionalObject_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~TransactionalObject(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class Synchronization : public Tobj_ServantBase 
        {
            public:

                virtual void before_completion () = 0; 

                virtual void after_completion (
                    ::CosTransactions::Status status) = 0; 

                ::CosTransactions::Synchronization_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~Synchronization(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
        class SubtransactionAwareResource : public Tobj_ServantBase 
        {
            public:

                virtual ::CosTransactions::Vote prepare () = 0; 

                virtual void rollback () = 0; 

                virtual void commit () = 0; 

                virtual void commit_one_phase () = 0; 

                virtual void forget () = 0; 

                virtual void commit_subtransaction (
                    ::CosTransactions::Coordinator_ptr parent) = 0; 

                virtual void rollback_subtransaction () = 0; 

                ::CosTransactions::SubtransactionAwareResource_ptr _this();

                void invoke (::CORBA::ServerRequest_ptr _nasreq);

                ::CORBA::RepositoryId _primary_interface (
                const PortableServer::ObjectId &,
                    PortableServer::POA_ptr);

            protected:
                virtual ~SubtransactionAwareResource(){ }

            private:
                OBBArgument *getparams (::CORBA::Short, OBB::ServerRequest * SrvReq, ::CORBA::ULong & ArgCnt);

        };
};

#endif
