/*******************************************************************
 * Created Mon Jan 27 07:37:45 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (ots_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    Current
 *    TransactionFactory
 *    Control
 *    Terminator
 *    Coordinator
 *    RecoveryCoordinator
 *    Resource
 *    TransactionalObject
 *    Synchronization
 *    SubtransactionAwareResource
 *
 */


#ifndef _ots_c_H
#define _ots_c_H

#include <string.h>
#include <CORBA.h>
#include <orbgen.h>

#if defined(WIN32)
#pragma warning(disable:4250)
#endif


#ifndef EXPDLL_LIBOMG
#define ORB_IMPORT_DEFINED_ots_c
#ifdef WIN32 
#define EXPDLL_LIBOMG ORBIMPDLL
#else
#define EXPDLL_LIBOMG
#endif
#endif

class EXPDLL_LIBOMG CosTransactions
{
    public:
        class	Current;
        typedef	Current *	Current_ptr;
        class Current_out;

        class EXPDLL_LIBOMG Current_var : public ::CORBA::_var {
            public:
                Current_var();
                inline Current_var(Current_ptr p) {ptr_ = p; }
                Current_var(const Current_var &a);
                ~Current_var()
                    { free();}

                Current_var &operator=(Current_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Current_var &operator=(const Current_var &a);
                inline Current_ptr in () const { return ptr_; }
                inline Current_ptr & inout () { return ptr_; }
                Current_ptr & out ();
                Current_ptr _retn ();

                inline operator Current_ptr&() { return ptr_; }
                inline operator const Current_ptr&() const { return ptr_; }
                inline Current_ptr operator->() const { return ptr_; }

                inline Current_ptr & ptr () { return ptr_; }
            protected:
                Current_ptr ptr_;
                void free();
                void reset(Current_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class Current_var


        class	TransactionFactory;
        typedef	TransactionFactory *	TransactionFactory_ptr;
        class TransactionFactory_out;

        class EXPDLL_LIBOMG TransactionFactory_var : public ::CORBA::_var {
            public:
                TransactionFactory_var();
                inline TransactionFactory_var(TransactionFactory_ptr p) {ptr_ = p; }
                TransactionFactory_var(const TransactionFactory_var &a);
                ~TransactionFactory_var()
                    { free();}

                TransactionFactory_var &operator=(TransactionFactory_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                TransactionFactory_var &operator=(const TransactionFactory_var &a);
                inline TransactionFactory_ptr in () const { return ptr_; }
                inline TransactionFactory_ptr & inout () { return ptr_; }
                TransactionFactory_ptr & out ();
                TransactionFactory_ptr _retn ();

                inline operator TransactionFactory_ptr&() { return ptr_; }
                inline operator const TransactionFactory_ptr&() const { return ptr_; }
                inline TransactionFactory_ptr operator->() const { return ptr_; }

                inline TransactionFactory_ptr & ptr () { return ptr_; }
            protected:
                TransactionFactory_ptr ptr_;
                void free();
                void reset(TransactionFactory_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class TransactionFactory_var


        class	Control;
        typedef	Control *	Control_ptr;
        class Control_out;

        class EXPDLL_LIBOMG Control_var : public ::CORBA::_var {
            public:
                Control_var();
                inline Control_var(Control_ptr p) {ptr_ = p; }
                Control_var(const Control_var &a);
                ~Control_var()
                    { free();}

                Control_var &operator=(Control_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Control_var &operator=(const Control_var &a);
                inline Control_ptr in () const { return ptr_; }
                inline Control_ptr & inout () { return ptr_; }
                Control_ptr & out ();
                Control_ptr _retn ();

                inline operator Control_ptr&() { return ptr_; }
                inline operator const Control_ptr&() const { return ptr_; }
                inline Control_ptr operator->() const { return ptr_; }

                inline Control_ptr & ptr () { return ptr_; }
            protected:
                Control_ptr ptr_;
                void free();
                void reset(Control_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class Control_var


        class	Terminator;
        typedef	Terminator *	Terminator_ptr;
        class Terminator_out;

        class EXPDLL_LIBOMG Terminator_var : public ::CORBA::_var {
            public:
                Terminator_var();
                inline Terminator_var(Terminator_ptr p) {ptr_ = p; }
                Terminator_var(const Terminator_var &a);
                ~Terminator_var()
                    { free();}

                Terminator_var &operator=(Terminator_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Terminator_var &operator=(const Terminator_var &a);
                inline Terminator_ptr in () const { return ptr_; }
                inline Terminator_ptr & inout () { return ptr_; }
                Terminator_ptr & out ();
                Terminator_ptr _retn ();

                inline operator Terminator_ptr&() { return ptr_; }
                inline operator const Terminator_ptr&() const { return ptr_; }
                inline Terminator_ptr operator->() const { return ptr_; }

                inline Terminator_ptr & ptr () { return ptr_; }
            protected:
                Terminator_ptr ptr_;
                void free();
                void reset(Terminator_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class Terminator_var


        class	Coordinator;
        typedef	Coordinator *	Coordinator_ptr;
        class Coordinator_out;

        class EXPDLL_LIBOMG Coordinator_var : public ::CORBA::_var {
            public:
                Coordinator_var();
                inline Coordinator_var(Coordinator_ptr p) {ptr_ = p; }
                Coordinator_var(const Coordinator_var &a);
                ~Coordinator_var()
                    { free();}

                Coordinator_var &operator=(Coordinator_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Coordinator_var &operator=(const Coordinator_var &a);
                inline Coordinator_ptr in () const { return ptr_; }
                inline Coordinator_ptr & inout () { return ptr_; }
                Coordinator_ptr & out ();
                Coordinator_ptr _retn ();

                inline operator Coordinator_ptr&() { return ptr_; }
                inline operator const Coordinator_ptr&() const { return ptr_; }
                inline Coordinator_ptr operator->() const { return ptr_; }

                inline Coordinator_ptr & ptr () { return ptr_; }
            protected:
                Coordinator_ptr ptr_;
                void free();
                void reset(Coordinator_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class Coordinator_var


        class	RecoveryCoordinator;
        typedef	RecoveryCoordinator *	RecoveryCoordinator_ptr;
        class RecoveryCoordinator_out;

        class EXPDLL_LIBOMG RecoveryCoordinator_var : public ::CORBA::_var {
            public:
                RecoveryCoordinator_var();
                inline RecoveryCoordinator_var(RecoveryCoordinator_ptr p) {ptr_ = p; }
                RecoveryCoordinator_var(const RecoveryCoordinator_var &a);
                ~RecoveryCoordinator_var()
                    { free();}

                RecoveryCoordinator_var &operator=(RecoveryCoordinator_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                RecoveryCoordinator_var &operator=(const RecoveryCoordinator_var &a);
                inline RecoveryCoordinator_ptr in () const { return ptr_; }
                inline RecoveryCoordinator_ptr & inout () { return ptr_; }
                RecoveryCoordinator_ptr & out ();
                RecoveryCoordinator_ptr _retn ();

                inline operator RecoveryCoordinator_ptr&() { return ptr_; }
                inline operator const RecoveryCoordinator_ptr&() const { return ptr_; }
                inline RecoveryCoordinator_ptr operator->() const { return ptr_; }

                inline RecoveryCoordinator_ptr & ptr () { return ptr_; }
            protected:
                RecoveryCoordinator_ptr ptr_;
                void free();
                void reset(RecoveryCoordinator_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class RecoveryCoordinator_var


        class	Resource;
        typedef	Resource *	Resource_ptr;
        class Resource_out;

        class EXPDLL_LIBOMG Resource_var : public ::CORBA::_var {
            public:
                Resource_var();
                inline Resource_var(Resource_ptr p) {ptr_ = p; }
                Resource_var(const Resource_var &a);
                ~Resource_var()
                    { free();}

                Resource_var &operator=(Resource_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Resource_var &operator=(const Resource_var &a);
                inline Resource_ptr in () const { return ptr_; }
                inline Resource_ptr & inout () { return ptr_; }
                Resource_ptr & out ();
                Resource_ptr _retn ();

                inline operator Resource_ptr&() { return ptr_; }
                inline operator const Resource_ptr&() const { return ptr_; }
                inline Resource_ptr operator->() const { return ptr_; }

                inline Resource_ptr & ptr () { return ptr_; }
            protected:
                Resource_ptr ptr_;
                void free();
                void reset(Resource_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class Resource_var


        class	TransactionalObject;
        typedef	TransactionalObject *	TransactionalObject_ptr;
        class TransactionalObject_out;

        class EXPDLL_LIBOMG TransactionalObject_var : public ::CORBA::_var {
            public:
                TransactionalObject_var();
                inline TransactionalObject_var(TransactionalObject_ptr p) {ptr_ = p; }
                TransactionalObject_var(const TransactionalObject_var &a);
                ~TransactionalObject_var()
                    { free();}

                TransactionalObject_var &operator=(TransactionalObject_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                TransactionalObject_var &operator=(const TransactionalObject_var &a);
                inline TransactionalObject_ptr in () const { return ptr_; }
                inline TransactionalObject_ptr & inout () { return ptr_; }
                TransactionalObject_ptr & out ();
                TransactionalObject_ptr _retn ();

                inline operator TransactionalObject_ptr&() { return ptr_; }
                inline operator const TransactionalObject_ptr&() const { return ptr_; }
                inline TransactionalObject_ptr operator->() const { return ptr_; }

                inline TransactionalObject_ptr & ptr () { return ptr_; }
            protected:
                TransactionalObject_ptr ptr_;
                void free();
                void reset(TransactionalObject_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class TransactionalObject_var


        class	Synchronization;
        typedef	Synchronization *	Synchronization_ptr;
        class Synchronization_out;

        class EXPDLL_LIBOMG Synchronization_var : public ::CORBA::_var {
            public:
                Synchronization_var();
                inline Synchronization_var(Synchronization_ptr p) {ptr_ = p; }
                Synchronization_var(const Synchronization_var &a);
                ~Synchronization_var()
                    { free();}

                Synchronization_var &operator=(Synchronization_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                Synchronization_var &operator=(const Synchronization_var &a);
                inline Synchronization_ptr in () const { return ptr_; }
                inline Synchronization_ptr & inout () { return ptr_; }
                Synchronization_ptr & out ();
                Synchronization_ptr _retn ();

                inline operator Synchronization_ptr&() { return ptr_; }
                inline operator const Synchronization_ptr&() const { return ptr_; }
                inline Synchronization_ptr operator->() const { return ptr_; }

                inline Synchronization_ptr & ptr () { return ptr_; }
            protected:
                Synchronization_ptr ptr_;
                void free();
                void reset(Synchronization_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class Synchronization_var


        class	SubtransactionAwareResource;
        typedef	SubtransactionAwareResource *	SubtransactionAwareResource_ptr;
        class SubtransactionAwareResource_out;

        class EXPDLL_LIBOMG SubtransactionAwareResource_var : public ::CORBA::_var {
            public:
                SubtransactionAwareResource_var();
                inline SubtransactionAwareResource_var(SubtransactionAwareResource_ptr p) {ptr_ = p; }
                SubtransactionAwareResource_var(const SubtransactionAwareResource_var &a);
                ~SubtransactionAwareResource_var()
                    { free();}

                SubtransactionAwareResource_var &operator=(SubtransactionAwareResource_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                SubtransactionAwareResource_var &operator=(const SubtransactionAwareResource_var &a);
                inline SubtransactionAwareResource_ptr in () const { return ptr_; }
                inline SubtransactionAwareResource_ptr & inout () { return ptr_; }
                SubtransactionAwareResource_ptr & out ();
                SubtransactionAwareResource_ptr _retn ();

                inline operator SubtransactionAwareResource_ptr&() { return ptr_; }
                inline operator const SubtransactionAwareResource_ptr&() const { return ptr_; }
                inline SubtransactionAwareResource_ptr operator->() const { return ptr_; }

                inline SubtransactionAwareResource_ptr & ptr () { return ptr_; }
            protected:
                SubtransactionAwareResource_ptr ptr_;
                void free();
                void reset(SubtransactionAwareResource_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class SubtransactionAwareResource_var




        enum Status { StatusActive, StatusMarkedRollback, StatusPrepared, StatusCommitted, StatusRolledBack, StatusUnknown, StatusNoTransaction, StatusPreparing, StatusCommitting, StatusRollingBack };
        typedef Status & Status_out ;
        static const ::CORBA::TypeCode_ptr _tc_Status;


        enum Vote { VoteCommit, VoteRollback, VoteReadOnly };
        typedef Vote & Vote_out ;
        static const ::CORBA::TypeCode_ptr _tc_Vote;


        struct EXPDLL_LIBOMG otid_t {
             ::CORBA::Long formatID;
             ::CORBA::Long bqual_length;


            class EXPDLL_LIBOMG _1_tid
            {
                public:
                    _1_tid();

                    _1_tid(::CORBA::ULong _max);

                    _1_tid
                    (
                        ::CORBA::ULong _max,
                        ::CORBA::ULong _length,
                        ::CORBA::Octet *_value,
                        ::CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_tid(const _1_tid &_ptr);

                    ~_1_tid();

                    _1_tid &operator=(const _1_tid& _ptr);

                    inline ::CORBA::ULong maximum() const {return _maximum;}

                    void length(::CORBA::ULong);
                    inline ::CORBA::ULong length() const {return _current;}

                    inline ::CORBA::Octet &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                    inline const ::CORBA::Octet &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const ::CORBA::Octet &)_data[_index];}
#else
                            return _data[_index];}
#endif
                    static ::CORBA::Octet *allocbuf(::CORBA::ULong _nelems);
                    static void freebuf(::CORBA::Octet *_ptr);

                    inline ::CORBA::Octet * OBB__GetData() { return _data; }
                private:
                    ::CORBA::Octet *_data;
                    ::CORBA::ULong _maximum;
                    ::CORBA::ULong _current;
                    ::CORBA::Boolean _release;
            };  // class _1_tid

             _1_tid tid;
            otid_t &operator=(const otid_t &_obj);
        };
        typedef	otid_t *	otid_t_ptr;
        class EXPDLL_LIBOMG otid_t_var
        {
            public:
                inline otid_t_var() {_ptr = 0;}
                inline otid_t_var(otid_t *_obj) {_ptr = _obj;}
                otid_t_var(const otid_t_var &_obj) {_ptr = 0; *this = _obj;}
                ~otid_t_var();
                otid_t_var &operator=(otid_t *);
                otid_t_var &operator=(const otid_t_var &);
                inline otid_t *operator->() {return _ptr;}
                inline const otid_t *operator->() const {return _ptr;}
                inline const otid_t & in () const { return *_ptr; }
                inline otid_t & inout () { return *_ptr; }
                otid_t *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                otid_t * _retn ()
                {
                    otid_t *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline otid_t_ptr & ptr() { return _ptr; }
                inline operator otid_t&() { return *_ptr; }
                inline operator const otid_t&() const { return *_ptr; }
                inline operator otid_t_ptr &() { return _ptr; }
            private:
                otid_t *_ptr;
        };  // class otid_t_var

        class EXPDLL_LIBOMG otid_t_out
        {
            public:
                otid_t_out (otid_t *& p) : ptr_(p) { ptr_ = 0; }
                otid_t_out (otid_t_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                otid_t_out (const otid_t_out & a) : ptr_(a.ptr_) {}
                otid_t_out & operator=(const otid_t_out & a) {
                    ptr_ = a.ptr_; return *this; }
                otid_t_out & operator=(otid_t * p) {
                    ptr_ = p; return *this; }
                inline operator otid_t_ptr & () { return ptr_; }
                inline otid_t_ptr & ptr () { return ptr_; }
                inline otid_t_ptr operator->() { return ptr_; }
            private:
                otid_t_ptr & ptr_;
                void operator=(const otid_t_var &);

        };  // class otid_t_out
        static const ::CORBA::TypeCode_ptr _tc_otid_t;


        struct EXPDLL_LIBOMG TransIdentity {


             Coordinator_var coordinator;


             Terminator_var terminator;
             otid_t otid;
            TransIdentity &operator=(const TransIdentity &_obj);
        };
        typedef	TransIdentity *	TransIdentity_ptr;
        class EXPDLL_LIBOMG TransIdentity_var
        {
            public:
                inline TransIdentity_var() {_ptr = 0;}
                inline TransIdentity_var(TransIdentity *_obj) {_ptr = _obj;}
                TransIdentity_var(const TransIdentity_var &_obj) {_ptr = 0; *this = _obj;}
                ~TransIdentity_var();
                TransIdentity_var &operator=(TransIdentity *);
                TransIdentity_var &operator=(const TransIdentity_var &);
                inline TransIdentity *operator->() {return _ptr;}
                inline const TransIdentity *operator->() const {return _ptr;}
                inline const TransIdentity & in () const { return *_ptr; }
                inline TransIdentity & inout () { return *_ptr; }
                TransIdentity *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                TransIdentity * _retn ()
                {
                    TransIdentity *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline TransIdentity_ptr & ptr() { return _ptr; }
                inline operator TransIdentity&() { return *_ptr; }
                inline operator const TransIdentity&() const { return *_ptr; }
                inline operator TransIdentity_ptr &() { return _ptr; }
            private:
                TransIdentity *_ptr;
        };  // class TransIdentity_var

        class EXPDLL_LIBOMG TransIdentity_out
        {
            public:
                TransIdentity_out (TransIdentity *& p) : ptr_(p) { ptr_ = 0; }
                TransIdentity_out (TransIdentity_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                TransIdentity_out (const TransIdentity_out & a) : ptr_(a.ptr_) {}
                TransIdentity_out & operator=(const TransIdentity_out & a) {
                    ptr_ = a.ptr_; return *this; }
                TransIdentity_out & operator=(TransIdentity * p) {
                    ptr_ = p; return *this; }
                inline operator TransIdentity_ptr & () { return ptr_; }
                inline TransIdentity_ptr & ptr () { return ptr_; }
                inline TransIdentity_ptr operator->() { return ptr_; }
            private:
                TransIdentity_ptr & ptr_;
                void operator=(const TransIdentity_var &);

        };  // class TransIdentity_out
        static const ::CORBA::TypeCode_ptr _tc_TransIdentity;


        struct EXPDLL_LIBOMG PropagationContext {
             ::CORBA::ULong timeout;
             TransIdentity current;


            class EXPDLL_LIBOMG _1_parents
            {
                public:
                    _1_parents();

                    _1_parents(::CORBA::ULong _max);

                    _1_parents
                    (
                        ::CORBA::ULong _max,
                        ::CORBA::ULong _length,
                        TransIdentity *_value,
                        ::CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_parents(const _1_parents &_ptr);

                    ~_1_parents();

                    _1_parents &operator=(const _1_parents& _ptr);

                    inline ::CORBA::ULong maximum() const {return _maximum;}

                    void length(::CORBA::ULong);
                    inline ::CORBA::ULong length() const {return _current;}

                    inline TransIdentity &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                    inline const TransIdentity &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const TransIdentity &)_data[_index];}
#else
                            return _data[_index];}
#endif
                    static TransIdentity *allocbuf(::CORBA::ULong _nelems);
                    static void freebuf(TransIdentity *_ptr);

                    inline TransIdentity * OBB__GetData() { return _data; }
                private:
                    TransIdentity *_data;
                    ::CORBA::ULong _maximum;
                    ::CORBA::ULong _current;
                    ::CORBA::Boolean _release;
            };  // class _1_parents

             _1_parents parents;
             ::CORBA::Any implementation_specific_data;
            PropagationContext &operator=(const PropagationContext &_obj);
        };
        typedef	PropagationContext *	PropagationContext_ptr;
        class EXPDLL_LIBOMG PropagationContext_var
        {
            public:
                inline PropagationContext_var() {_ptr = 0;}
                inline PropagationContext_var(PropagationContext *_obj) {_ptr = _obj;}
                PropagationContext_var(const PropagationContext_var &_obj) {_ptr = 0; *this = _obj;}
                ~PropagationContext_var();
                PropagationContext_var &operator=(PropagationContext *);
                PropagationContext_var &operator=(const PropagationContext_var &);
                inline PropagationContext *operator->() {return _ptr;}
                inline const PropagationContext *operator->() const {return _ptr;}
                inline const PropagationContext & in () const { return *_ptr; }
                inline PropagationContext & inout () { return *_ptr; }
                PropagationContext *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                PropagationContext * _retn ()
                {
                    PropagationContext *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline PropagationContext_ptr & ptr() { return _ptr; }
                inline operator PropagationContext&() { return *_ptr; }
                inline operator const PropagationContext&() const { return *_ptr; }
                inline operator PropagationContext_ptr &() { return _ptr; }
            private:
                PropagationContext *_ptr;
        };  // class PropagationContext_var

        class EXPDLL_LIBOMG PropagationContext_out
        {
            public:
                PropagationContext_out (PropagationContext *& p) : ptr_(p) { ptr_ = 0; }
                PropagationContext_out (PropagationContext_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                PropagationContext_out (const PropagationContext_out & a) : ptr_(a.ptr_) {}
                PropagationContext_out & operator=(const PropagationContext_out & a) {
                    ptr_ = a.ptr_; return *this; }
                PropagationContext_out & operator=(PropagationContext * p) {
                    ptr_ = p; return *this; }
                inline operator PropagationContext_ptr & () { return ptr_; }
                inline PropagationContext_ptr & ptr () { return ptr_; }
                inline PropagationContext_ptr operator->() { return ptr_; }
            private:
                PropagationContext_ptr & ptr_;
                void operator=(const PropagationContext_var &);

        };  // class PropagationContext_out
        static const ::CORBA::TypeCode_ptr _tc_PropagationContext;
        class EXPDLL_LIBOMG HeuristicRollback : public ::CORBA::UserException
        {
            public:
                static HeuristicRollback * _narrow(::CORBA::Exception_ptr);
                HeuristicRollback ();
                HeuristicRollback (const HeuristicRollback &);
                ~HeuristicRollback ();
                HeuristicRollback & operator=(const HeuristicRollback &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/HeuristicRollback:1.0"; }

        };  // class HeuristicRollback


        typedef	HeuristicRollback *	HeuristicRollback_ptr;
        class EXPDLL_LIBOMG HeuristicRollback_var
        {
            public:
                inline HeuristicRollback_var() {_ptr = 0;}
                inline HeuristicRollback_var(HeuristicRollback *_obj) {_ptr = _obj;}
                HeuristicRollback_var(const HeuristicRollback_var &_obj) {_ptr = 0; *this = _obj;}
                ~HeuristicRollback_var();
                HeuristicRollback_var &operator=(HeuristicRollback *);
                HeuristicRollback_var &operator=(const HeuristicRollback_var &);
                inline HeuristicRollback *operator->() {return _ptr;}
                inline const HeuristicRollback *operator->() const {return _ptr;}
                inline const HeuristicRollback & in () const { return *_ptr; }
                inline HeuristicRollback & inout () { return *_ptr; }
                HeuristicRollback & out ()
                {
                    HeuristicRollback *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                HeuristicRollback & _retn ()
                {
                    HeuristicRollback *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline HeuristicRollback_ptr & ptr() { return _ptr; }
                inline operator HeuristicRollback&() { return *_ptr; }
                inline operator const HeuristicRollback&() const { return *_ptr; }
                inline operator HeuristicRollback_ptr &() { return _ptr; }
            private:
                HeuristicRollback *_ptr;
        };  // class HeuristicRollback_var

        class EXPDLL_LIBOMG HeuristicRollback_out
        {
            public:
                HeuristicRollback_out (HeuristicRollback *& p) : ptr_(p) { ptr_ = 0; }
                HeuristicRollback_out (HeuristicRollback_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                HeuristicRollback_out (const HeuristicRollback_out & a) : ptr_(a.ptr_) {}
                HeuristicRollback_out & operator=(const HeuristicRollback_out & a) {
                    ptr_ = a.ptr_; return *this; }
                HeuristicRollback_out & operator=(HeuristicRollback * p) {
                    ptr_ = p; return *this; }
                inline operator HeuristicRollback_ptr & () { return ptr_; }
                inline HeuristicRollback_ptr & ptr () { return ptr_; }
                inline HeuristicRollback_ptr operator->() { return ptr_; }
            private:
                HeuristicRollback_ptr & ptr_;
                void operator=(const HeuristicRollback_var &);

        };  // class HeuristicRollback_out
        static const ::CORBA::TypeCode_ptr _tc_HeuristicRollback;
        class EXPDLL_LIBOMG HeuristicCommit : public ::CORBA::UserException
        {
            public:
                static HeuristicCommit * _narrow(::CORBA::Exception_ptr);
                HeuristicCommit ();
                HeuristicCommit (const HeuristicCommit &);
                ~HeuristicCommit ();
                HeuristicCommit & operator=(const HeuristicCommit &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/HeuristicCommit:1.0"; }

        };  // class HeuristicCommit


        typedef	HeuristicCommit *	HeuristicCommit_ptr;
        class EXPDLL_LIBOMG HeuristicCommit_var
        {
            public:
                inline HeuristicCommit_var() {_ptr = 0;}
                inline HeuristicCommit_var(HeuristicCommit *_obj) {_ptr = _obj;}
                HeuristicCommit_var(const HeuristicCommit_var &_obj) {_ptr = 0; *this = _obj;}
                ~HeuristicCommit_var();
                HeuristicCommit_var &operator=(HeuristicCommit *);
                HeuristicCommit_var &operator=(const HeuristicCommit_var &);
                inline HeuristicCommit *operator->() {return _ptr;}
                inline const HeuristicCommit *operator->() const {return _ptr;}
                inline const HeuristicCommit & in () const { return *_ptr; }
                inline HeuristicCommit & inout () { return *_ptr; }
                HeuristicCommit & out ()
                {
                    HeuristicCommit *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                HeuristicCommit & _retn ()
                {
                    HeuristicCommit *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline HeuristicCommit_ptr & ptr() { return _ptr; }
                inline operator HeuristicCommit&() { return *_ptr; }
                inline operator const HeuristicCommit&() const { return *_ptr; }
                inline operator HeuristicCommit_ptr &() { return _ptr; }
            private:
                HeuristicCommit *_ptr;
        };  // class HeuristicCommit_var

        class EXPDLL_LIBOMG HeuristicCommit_out
        {
            public:
                HeuristicCommit_out (HeuristicCommit *& p) : ptr_(p) { ptr_ = 0; }
                HeuristicCommit_out (HeuristicCommit_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                HeuristicCommit_out (const HeuristicCommit_out & a) : ptr_(a.ptr_) {}
                HeuristicCommit_out & operator=(const HeuristicCommit_out & a) {
                    ptr_ = a.ptr_; return *this; }
                HeuristicCommit_out & operator=(HeuristicCommit * p) {
                    ptr_ = p; return *this; }
                inline operator HeuristicCommit_ptr & () { return ptr_; }
                inline HeuristicCommit_ptr & ptr () { return ptr_; }
                inline HeuristicCommit_ptr operator->() { return ptr_; }
            private:
                HeuristicCommit_ptr & ptr_;
                void operator=(const HeuristicCommit_var &);

        };  // class HeuristicCommit_out
        static const ::CORBA::TypeCode_ptr _tc_HeuristicCommit;
        class EXPDLL_LIBOMG HeuristicMixed : public ::CORBA::UserException
        {
            public:
                static HeuristicMixed * _narrow(::CORBA::Exception_ptr);
                HeuristicMixed ();
                HeuristicMixed (const HeuristicMixed &);
                ~HeuristicMixed ();
                HeuristicMixed & operator=(const HeuristicMixed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/HeuristicMixed:1.0"; }

        };  // class HeuristicMixed


        typedef	HeuristicMixed *	HeuristicMixed_ptr;
        class EXPDLL_LIBOMG HeuristicMixed_var
        {
            public:
                inline HeuristicMixed_var() {_ptr = 0;}
                inline HeuristicMixed_var(HeuristicMixed *_obj) {_ptr = _obj;}
                HeuristicMixed_var(const HeuristicMixed_var &_obj) {_ptr = 0; *this = _obj;}
                ~HeuristicMixed_var();
                HeuristicMixed_var &operator=(HeuristicMixed *);
                HeuristicMixed_var &operator=(const HeuristicMixed_var &);
                inline HeuristicMixed *operator->() {return _ptr;}
                inline const HeuristicMixed *operator->() const {return _ptr;}
                inline const HeuristicMixed & in () const { return *_ptr; }
                inline HeuristicMixed & inout () { return *_ptr; }
                HeuristicMixed & out ()
                {
                    HeuristicMixed *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                HeuristicMixed & _retn ()
                {
                    HeuristicMixed *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline HeuristicMixed_ptr & ptr() { return _ptr; }
                inline operator HeuristicMixed&() { return *_ptr; }
                inline operator const HeuristicMixed&() const { return *_ptr; }
                inline operator HeuristicMixed_ptr &() { return _ptr; }
            private:
                HeuristicMixed *_ptr;
        };  // class HeuristicMixed_var

        class EXPDLL_LIBOMG HeuristicMixed_out
        {
            public:
                HeuristicMixed_out (HeuristicMixed *& p) : ptr_(p) { ptr_ = 0; }
                HeuristicMixed_out (HeuristicMixed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                HeuristicMixed_out (const HeuristicMixed_out & a) : ptr_(a.ptr_) {}
                HeuristicMixed_out & operator=(const HeuristicMixed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                HeuristicMixed_out & operator=(HeuristicMixed * p) {
                    ptr_ = p; return *this; }
                inline operator HeuristicMixed_ptr & () { return ptr_; }
                inline HeuristicMixed_ptr & ptr () { return ptr_; }
                inline HeuristicMixed_ptr operator->() { return ptr_; }
            private:
                HeuristicMixed_ptr & ptr_;
                void operator=(const HeuristicMixed_var &);

        };  // class HeuristicMixed_out
        static const ::CORBA::TypeCode_ptr _tc_HeuristicMixed;
        class EXPDLL_LIBOMG HeuristicHazard : public ::CORBA::UserException
        {
            public:
                static HeuristicHazard * _narrow(::CORBA::Exception_ptr);
                HeuristicHazard ();
                HeuristicHazard (const HeuristicHazard &);
                ~HeuristicHazard ();
                HeuristicHazard & operator=(const HeuristicHazard &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/HeuristicHazard:1.0"; }

        };  // class HeuristicHazard


        typedef	HeuristicHazard *	HeuristicHazard_ptr;
        class EXPDLL_LIBOMG HeuristicHazard_var
        {
            public:
                inline HeuristicHazard_var() {_ptr = 0;}
                inline HeuristicHazard_var(HeuristicHazard *_obj) {_ptr = _obj;}
                HeuristicHazard_var(const HeuristicHazard_var &_obj) {_ptr = 0; *this = _obj;}
                ~HeuristicHazard_var();
                HeuristicHazard_var &operator=(HeuristicHazard *);
                HeuristicHazard_var &operator=(const HeuristicHazard_var &);
                inline HeuristicHazard *operator->() {return _ptr;}
                inline const HeuristicHazard *operator->() const {return _ptr;}
                inline const HeuristicHazard & in () const { return *_ptr; }
                inline HeuristicHazard & inout () { return *_ptr; }
                HeuristicHazard & out ()
                {
                    HeuristicHazard *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                HeuristicHazard & _retn ()
                {
                    HeuristicHazard *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline HeuristicHazard_ptr & ptr() { return _ptr; }
                inline operator HeuristicHazard&() { return *_ptr; }
                inline operator const HeuristicHazard&() const { return *_ptr; }
                inline operator HeuristicHazard_ptr &() { return _ptr; }
            private:
                HeuristicHazard *_ptr;
        };  // class HeuristicHazard_var

        class EXPDLL_LIBOMG HeuristicHazard_out
        {
            public:
                HeuristicHazard_out (HeuristicHazard *& p) : ptr_(p) { ptr_ = 0; }
                HeuristicHazard_out (HeuristicHazard_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                HeuristicHazard_out (const HeuristicHazard_out & a) : ptr_(a.ptr_) {}
                HeuristicHazard_out & operator=(const HeuristicHazard_out & a) {
                    ptr_ = a.ptr_; return *this; }
                HeuristicHazard_out & operator=(HeuristicHazard * p) {
                    ptr_ = p; return *this; }
                inline operator HeuristicHazard_ptr & () { return ptr_; }
                inline HeuristicHazard_ptr & ptr () { return ptr_; }
                inline HeuristicHazard_ptr operator->() { return ptr_; }
            private:
                HeuristicHazard_ptr & ptr_;
                void operator=(const HeuristicHazard_var &);

        };  // class HeuristicHazard_out
        static const ::CORBA::TypeCode_ptr _tc_HeuristicHazard;
        class EXPDLL_LIBOMG SubtransactionsUnavailable : public ::CORBA::UserException
        {
            public:
                static SubtransactionsUnavailable * _narrow(::CORBA::Exception_ptr);
                SubtransactionsUnavailable ();
                SubtransactionsUnavailable (const SubtransactionsUnavailable &);
                ~SubtransactionsUnavailable ();
                SubtransactionsUnavailable & operator=(const SubtransactionsUnavailable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/SubtransactionsUnavailable:1.0"; }

        };  // class SubtransactionsUnavailable


        typedef	SubtransactionsUnavailable *	SubtransactionsUnavailable_ptr;
        class EXPDLL_LIBOMG SubtransactionsUnavailable_var
        {
            public:
                inline SubtransactionsUnavailable_var() {_ptr = 0;}
                inline SubtransactionsUnavailable_var(SubtransactionsUnavailable *_obj) {_ptr = _obj;}
                SubtransactionsUnavailable_var(const SubtransactionsUnavailable_var &_obj) {_ptr = 0; *this = _obj;}
                ~SubtransactionsUnavailable_var();
                SubtransactionsUnavailable_var &operator=(SubtransactionsUnavailable *);
                SubtransactionsUnavailable_var &operator=(const SubtransactionsUnavailable_var &);
                inline SubtransactionsUnavailable *operator->() {return _ptr;}
                inline const SubtransactionsUnavailable *operator->() const {return _ptr;}
                inline const SubtransactionsUnavailable & in () const { return *_ptr; }
                inline SubtransactionsUnavailable & inout () { return *_ptr; }
                SubtransactionsUnavailable & out ()
                {
                    SubtransactionsUnavailable *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                SubtransactionsUnavailable & _retn ()
                {
                    SubtransactionsUnavailable *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline SubtransactionsUnavailable_ptr & ptr() { return _ptr; }
                inline operator SubtransactionsUnavailable&() { return *_ptr; }
                inline operator const SubtransactionsUnavailable&() const { return *_ptr; }
                inline operator SubtransactionsUnavailable_ptr &() { return _ptr; }
            private:
                SubtransactionsUnavailable *_ptr;
        };  // class SubtransactionsUnavailable_var

        class EXPDLL_LIBOMG SubtransactionsUnavailable_out
        {
            public:
                SubtransactionsUnavailable_out (SubtransactionsUnavailable *& p) : ptr_(p) { ptr_ = 0; }
                SubtransactionsUnavailable_out (SubtransactionsUnavailable_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                SubtransactionsUnavailable_out (const SubtransactionsUnavailable_out & a) : ptr_(a.ptr_) {}
                SubtransactionsUnavailable_out & operator=(const SubtransactionsUnavailable_out & a) {
                    ptr_ = a.ptr_; return *this; }
                SubtransactionsUnavailable_out & operator=(SubtransactionsUnavailable * p) {
                    ptr_ = p; return *this; }
                inline operator SubtransactionsUnavailable_ptr & () { return ptr_; }
                inline SubtransactionsUnavailable_ptr & ptr () { return ptr_; }
                inline SubtransactionsUnavailable_ptr operator->() { return ptr_; }
            private:
                SubtransactionsUnavailable_ptr & ptr_;
                void operator=(const SubtransactionsUnavailable_var &);

        };  // class SubtransactionsUnavailable_out
        static const ::CORBA::TypeCode_ptr _tc_SubtransactionsUnavailable;
        class EXPDLL_LIBOMG NotSubtransaction : public ::CORBA::UserException
        {
            public:
                static NotSubtransaction * _narrow(::CORBA::Exception_ptr);
                NotSubtransaction ();
                NotSubtransaction (const NotSubtransaction &);
                ~NotSubtransaction ();
                NotSubtransaction & operator=(const NotSubtransaction &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/NotSubtransaction:1.0"; }

        };  // class NotSubtransaction


        typedef	NotSubtransaction *	NotSubtransaction_ptr;
        class EXPDLL_LIBOMG NotSubtransaction_var
        {
            public:
                inline NotSubtransaction_var() {_ptr = 0;}
                inline NotSubtransaction_var(NotSubtransaction *_obj) {_ptr = _obj;}
                NotSubtransaction_var(const NotSubtransaction_var &_obj) {_ptr = 0; *this = _obj;}
                ~NotSubtransaction_var();
                NotSubtransaction_var &operator=(NotSubtransaction *);
                NotSubtransaction_var &operator=(const NotSubtransaction_var &);
                inline NotSubtransaction *operator->() {return _ptr;}
                inline const NotSubtransaction *operator->() const {return _ptr;}
                inline const NotSubtransaction & in () const { return *_ptr; }
                inline NotSubtransaction & inout () { return *_ptr; }
                NotSubtransaction & out ()
                {
                    NotSubtransaction *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                NotSubtransaction & _retn ()
                {
                    NotSubtransaction *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline NotSubtransaction_ptr & ptr() { return _ptr; }
                inline operator NotSubtransaction&() { return *_ptr; }
                inline operator const NotSubtransaction&() const { return *_ptr; }
                inline operator NotSubtransaction_ptr &() { return _ptr; }
            private:
                NotSubtransaction *_ptr;
        };  // class NotSubtransaction_var

        class EXPDLL_LIBOMG NotSubtransaction_out
        {
            public:
                NotSubtransaction_out (NotSubtransaction *& p) : ptr_(p) { ptr_ = 0; }
                NotSubtransaction_out (NotSubtransaction_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NotSubtransaction_out (const NotSubtransaction_out & a) : ptr_(a.ptr_) {}
                NotSubtransaction_out & operator=(const NotSubtransaction_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NotSubtransaction_out & operator=(NotSubtransaction * p) {
                    ptr_ = p; return *this; }
                inline operator NotSubtransaction_ptr & () { return ptr_; }
                inline NotSubtransaction_ptr & ptr () { return ptr_; }
                inline NotSubtransaction_ptr operator->() { return ptr_; }
            private:
                NotSubtransaction_ptr & ptr_;
                void operator=(const NotSubtransaction_var &);

        };  // class NotSubtransaction_out
        static const ::CORBA::TypeCode_ptr _tc_NotSubtransaction;
        class EXPDLL_LIBOMG Inactive : public ::CORBA::UserException
        {
            public:
                static Inactive * _narrow(::CORBA::Exception_ptr);
                Inactive ();
                Inactive (const Inactive &);
                ~Inactive ();
                Inactive & operator=(const Inactive &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/Inactive:1.0"; }

        };  // class Inactive


        typedef	Inactive *	Inactive_ptr;
        class EXPDLL_LIBOMG Inactive_var
        {
            public:
                inline Inactive_var() {_ptr = 0;}
                inline Inactive_var(Inactive *_obj) {_ptr = _obj;}
                Inactive_var(const Inactive_var &_obj) {_ptr = 0; *this = _obj;}
                ~Inactive_var();
                Inactive_var &operator=(Inactive *);
                Inactive_var &operator=(const Inactive_var &);
                inline Inactive *operator->() {return _ptr;}
                inline const Inactive *operator->() const {return _ptr;}
                inline const Inactive & in () const { return *_ptr; }
                inline Inactive & inout () { return *_ptr; }
                Inactive & out ()
                {
                    Inactive *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                Inactive & _retn ()
                {
                    Inactive *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline Inactive_ptr & ptr() { return _ptr; }
                inline operator Inactive&() { return *_ptr; }
                inline operator const Inactive&() const { return *_ptr; }
                inline operator Inactive_ptr &() { return _ptr; }
            private:
                Inactive *_ptr;
        };  // class Inactive_var

        class EXPDLL_LIBOMG Inactive_out
        {
            public:
                Inactive_out (Inactive *& p) : ptr_(p) { ptr_ = 0; }
                Inactive_out (Inactive_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                Inactive_out (const Inactive_out & a) : ptr_(a.ptr_) {}
                Inactive_out & operator=(const Inactive_out & a) {
                    ptr_ = a.ptr_; return *this; }
                Inactive_out & operator=(Inactive * p) {
                    ptr_ = p; return *this; }
                inline operator Inactive_ptr & () { return ptr_; }
                inline Inactive_ptr & ptr () { return ptr_; }
                inline Inactive_ptr operator->() { return ptr_; }
            private:
                Inactive_ptr & ptr_;
                void operator=(const Inactive_var &);

        };  // class Inactive_out
        static const ::CORBA::TypeCode_ptr _tc_Inactive;
        class EXPDLL_LIBOMG NotPrepared : public ::CORBA::UserException
        {
            public:
                static NotPrepared * _narrow(::CORBA::Exception_ptr);
                NotPrepared ();
                NotPrepared (const NotPrepared &);
                ~NotPrepared ();
                NotPrepared & operator=(const NotPrepared &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/NotPrepared:1.0"; }

        };  // class NotPrepared


        typedef	NotPrepared *	NotPrepared_ptr;
        class EXPDLL_LIBOMG NotPrepared_var
        {
            public:
                inline NotPrepared_var() {_ptr = 0;}
                inline NotPrepared_var(NotPrepared *_obj) {_ptr = _obj;}
                NotPrepared_var(const NotPrepared_var &_obj) {_ptr = 0; *this = _obj;}
                ~NotPrepared_var();
                NotPrepared_var &operator=(NotPrepared *);
                NotPrepared_var &operator=(const NotPrepared_var &);
                inline NotPrepared *operator->() {return _ptr;}
                inline const NotPrepared *operator->() const {return _ptr;}
                inline const NotPrepared & in () const { return *_ptr; }
                inline NotPrepared & inout () { return *_ptr; }
                NotPrepared & out ()
                {
                    NotPrepared *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                NotPrepared & _retn ()
                {
                    NotPrepared *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline NotPrepared_ptr & ptr() { return _ptr; }
                inline operator NotPrepared&() { return *_ptr; }
                inline operator const NotPrepared&() const { return *_ptr; }
                inline operator NotPrepared_ptr &() { return _ptr; }
            private:
                NotPrepared *_ptr;
        };  // class NotPrepared_var

        class EXPDLL_LIBOMG NotPrepared_out
        {
            public:
                NotPrepared_out (NotPrepared *& p) : ptr_(p) { ptr_ = 0; }
                NotPrepared_out (NotPrepared_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NotPrepared_out (const NotPrepared_out & a) : ptr_(a.ptr_) {}
                NotPrepared_out & operator=(const NotPrepared_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NotPrepared_out & operator=(NotPrepared * p) {
                    ptr_ = p; return *this; }
                inline operator NotPrepared_ptr & () { return ptr_; }
                inline NotPrepared_ptr & ptr () { return ptr_; }
                inline NotPrepared_ptr operator->() { return ptr_; }
            private:
                NotPrepared_ptr & ptr_;
                void operator=(const NotPrepared_var &);

        };  // class NotPrepared_out
        static const ::CORBA::TypeCode_ptr _tc_NotPrepared;
        class EXPDLL_LIBOMG NoTransaction : public ::CORBA::UserException
        {
            public:
                static NoTransaction * _narrow(::CORBA::Exception_ptr);
                NoTransaction ();
                NoTransaction (const NoTransaction &);
                ~NoTransaction ();
                NoTransaction & operator=(const NoTransaction &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/NoTransaction:1.0"; }

        };  // class NoTransaction


        typedef	NoTransaction *	NoTransaction_ptr;
        class EXPDLL_LIBOMG NoTransaction_var
        {
            public:
                inline NoTransaction_var() {_ptr = 0;}
                inline NoTransaction_var(NoTransaction *_obj) {_ptr = _obj;}
                NoTransaction_var(const NoTransaction_var &_obj) {_ptr = 0; *this = _obj;}
                ~NoTransaction_var();
                NoTransaction_var &operator=(NoTransaction *);
                NoTransaction_var &operator=(const NoTransaction_var &);
                inline NoTransaction *operator->() {return _ptr;}
                inline const NoTransaction *operator->() const {return _ptr;}
                inline const NoTransaction & in () const { return *_ptr; }
                inline NoTransaction & inout () { return *_ptr; }
                NoTransaction & out ()
                {
                    NoTransaction *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                NoTransaction & _retn ()
                {
                    NoTransaction *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline NoTransaction_ptr & ptr() { return _ptr; }
                inline operator NoTransaction&() { return *_ptr; }
                inline operator const NoTransaction&() const { return *_ptr; }
                inline operator NoTransaction_ptr &() { return _ptr; }
            private:
                NoTransaction *_ptr;
        };  // class NoTransaction_var

        class EXPDLL_LIBOMG NoTransaction_out
        {
            public:
                NoTransaction_out (NoTransaction *& p) : ptr_(p) { ptr_ = 0; }
                NoTransaction_out (NoTransaction_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NoTransaction_out (const NoTransaction_out & a) : ptr_(a.ptr_) {}
                NoTransaction_out & operator=(const NoTransaction_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NoTransaction_out & operator=(NoTransaction * p) {
                    ptr_ = p; return *this; }
                inline operator NoTransaction_ptr & () { return ptr_; }
                inline NoTransaction_ptr & ptr () { return ptr_; }
                inline NoTransaction_ptr operator->() { return ptr_; }
            private:
                NoTransaction_ptr & ptr_;
                void operator=(const NoTransaction_var &);

        };  // class NoTransaction_out
        static const ::CORBA::TypeCode_ptr _tc_NoTransaction;
        class EXPDLL_LIBOMG InvalidControl : public ::CORBA::UserException
        {
            public:
                static InvalidControl * _narrow(::CORBA::Exception_ptr);
                InvalidControl ();
                InvalidControl (const InvalidControl &);
                ~InvalidControl ();
                InvalidControl & operator=(const InvalidControl &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/InvalidControl:1.0"; }

        };  // class InvalidControl


        typedef	InvalidControl *	InvalidControl_ptr;
        class EXPDLL_LIBOMG InvalidControl_var
        {
            public:
                inline InvalidControl_var() {_ptr = 0;}
                inline InvalidControl_var(InvalidControl *_obj) {_ptr = _obj;}
                InvalidControl_var(const InvalidControl_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidControl_var();
                InvalidControl_var &operator=(InvalidControl *);
                InvalidControl_var &operator=(const InvalidControl_var &);
                inline InvalidControl *operator->() {return _ptr;}
                inline const InvalidControl *operator->() const {return _ptr;}
                inline const InvalidControl & in () const { return *_ptr; }
                inline InvalidControl & inout () { return *_ptr; }
                InvalidControl & out ()
                {
                    InvalidControl *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                InvalidControl & _retn ()
                {
                    InvalidControl *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline InvalidControl_ptr & ptr() { return _ptr; }
                inline operator InvalidControl&() { return *_ptr; }
                inline operator const InvalidControl&() const { return *_ptr; }
                inline operator InvalidControl_ptr &() { return _ptr; }
            private:
                InvalidControl *_ptr;
        };  // class InvalidControl_var

        class EXPDLL_LIBOMG InvalidControl_out
        {
            public:
                InvalidControl_out (InvalidControl *& p) : ptr_(p) { ptr_ = 0; }
                InvalidControl_out (InvalidControl_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidControl_out (const InvalidControl_out & a) : ptr_(a.ptr_) {}
                InvalidControl_out & operator=(const InvalidControl_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidControl_out & operator=(InvalidControl * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidControl_ptr & () { return ptr_; }
                inline InvalidControl_ptr & ptr () { return ptr_; }
                inline InvalidControl_ptr operator->() { return ptr_; }
            private:
                InvalidControl_ptr & ptr_;
                void operator=(const InvalidControl_var &);

        };  // class InvalidControl_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidControl;
        class EXPDLL_LIBOMG Unavailable : public ::CORBA::UserException
        {
            public:
                static Unavailable * _narrow(::CORBA::Exception_ptr);
                Unavailable ();
                Unavailable (const Unavailable &);
                ~Unavailable ();
                Unavailable & operator=(const Unavailable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/Unavailable:1.0"; }

        };  // class Unavailable


        typedef	Unavailable *	Unavailable_ptr;
        class EXPDLL_LIBOMG Unavailable_var
        {
            public:
                inline Unavailable_var() {_ptr = 0;}
                inline Unavailable_var(Unavailable *_obj) {_ptr = _obj;}
                Unavailable_var(const Unavailable_var &_obj) {_ptr = 0; *this = _obj;}
                ~Unavailable_var();
                Unavailable_var &operator=(Unavailable *);
                Unavailable_var &operator=(const Unavailable_var &);
                inline Unavailable *operator->() {return _ptr;}
                inline const Unavailable *operator->() const {return _ptr;}
                inline const Unavailable & in () const { return *_ptr; }
                inline Unavailable & inout () { return *_ptr; }
                Unavailable & out ()
                {
                    Unavailable *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                Unavailable & _retn ()
                {
                    Unavailable *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline Unavailable_ptr & ptr() { return _ptr; }
                inline operator Unavailable&() { return *_ptr; }
                inline operator const Unavailable&() const { return *_ptr; }
                inline operator Unavailable_ptr &() { return _ptr; }
            private:
                Unavailable *_ptr;
        };  // class Unavailable_var

        class EXPDLL_LIBOMG Unavailable_out
        {
            public:
                Unavailable_out (Unavailable *& p) : ptr_(p) { ptr_ = 0; }
                Unavailable_out (Unavailable_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                Unavailable_out (const Unavailable_out & a) : ptr_(a.ptr_) {}
                Unavailable_out & operator=(const Unavailable_out & a) {
                    ptr_ = a.ptr_; return *this; }
                Unavailable_out & operator=(Unavailable * p) {
                    ptr_ = p; return *this; }
                inline operator Unavailable_ptr & () { return ptr_; }
                inline Unavailable_ptr & ptr () { return ptr_; }
                inline Unavailable_ptr operator->() { return ptr_; }
            private:
                Unavailable_ptr & ptr_;
                void operator=(const Unavailable_var &);

        };  // class Unavailable_out
        static const ::CORBA::TypeCode_ptr _tc_Unavailable;
        class EXPDLL_LIBOMG SynchronizationUnavailable : public ::CORBA::UserException
        {
            public:
                static SynchronizationUnavailable * _narrow(::CORBA::Exception_ptr);
                SynchronizationUnavailable ();
                SynchronizationUnavailable (const SynchronizationUnavailable &);
                ~SynchronizationUnavailable ();
                SynchronizationUnavailable & operator=(const SynchronizationUnavailable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosTransactions/SynchronizationUnavailable:1.0"; }

        };  // class SynchronizationUnavailable


        typedef	SynchronizationUnavailable *	SynchronizationUnavailable_ptr;
        class EXPDLL_LIBOMG SynchronizationUnavailable_var
        {
            public:
                inline SynchronizationUnavailable_var() {_ptr = 0;}
                inline SynchronizationUnavailable_var(SynchronizationUnavailable *_obj) {_ptr = _obj;}
                SynchronizationUnavailable_var(const SynchronizationUnavailable_var &_obj) {_ptr = 0; *this = _obj;}
                ~SynchronizationUnavailable_var();
                SynchronizationUnavailable_var &operator=(SynchronizationUnavailable *);
                SynchronizationUnavailable_var &operator=(const SynchronizationUnavailable_var &);
                inline SynchronizationUnavailable *operator->() {return _ptr;}
                inline const SynchronizationUnavailable *operator->() const {return _ptr;}
                inline const SynchronizationUnavailable & in () const { return *_ptr; }
                inline SynchronizationUnavailable & inout () { return *_ptr; }
                SynchronizationUnavailable & out ()
                {
                    SynchronizationUnavailable *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                SynchronizationUnavailable & _retn ()
                {
                    SynchronizationUnavailable *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline SynchronizationUnavailable_ptr & ptr() { return _ptr; }
                inline operator SynchronizationUnavailable&() { return *_ptr; }
                inline operator const SynchronizationUnavailable&() const { return *_ptr; }
                inline operator SynchronizationUnavailable_ptr &() { return _ptr; }
            private:
                SynchronizationUnavailable *_ptr;
        };  // class SynchronizationUnavailable_var

        class EXPDLL_LIBOMG SynchronizationUnavailable_out
        {
            public:
                SynchronizationUnavailable_out (SynchronizationUnavailable *& p) : ptr_(p) { ptr_ = 0; }
                SynchronizationUnavailable_out (SynchronizationUnavailable_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                SynchronizationUnavailable_out (const SynchronizationUnavailable_out & a) : ptr_(a.ptr_) {}
                SynchronizationUnavailable_out & operator=(const SynchronizationUnavailable_out & a) {
                    ptr_ = a.ptr_; return *this; }
                SynchronizationUnavailable_out & operator=(SynchronizationUnavailable * p) {
                    ptr_ = p; return *this; }
                inline operator SynchronizationUnavailable_ptr & () { return ptr_; }
                inline SynchronizationUnavailable_ptr & ptr () { return ptr_; }
                inline SynchronizationUnavailable_ptr operator->() { return ptr_; }
            private:
                SynchronizationUnavailable_ptr & ptr_;
                void operator=(const SynchronizationUnavailable_var &);

        };  // class SynchronizationUnavailable_out
        static const ::CORBA::TypeCode_ptr _tc_SynchronizationUnavailable;


        static const ::CORBA::TypeCode_ptr _tc_Current;
        class EXPDLL_LIBOMG Current : public virtual ::CORBA::Object
         {
            public:
                static Current_ptr _duplicate(Current_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Current_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static Current_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual void begin (); 

                virtual void commit (
                    ::CORBA::Boolean report_heuristics); 

                virtual void rollback (); 

                virtual void rollback_only (); 

                virtual Status get_status (); 

                virtual ::CORBA::Char * get_transaction_name (); 

                virtual void set_timeout (
                    ::CORBA::ULong seconds); 

                virtual Control_ptr get_control (); 

                virtual Control_ptr suspend (); 

                virtual void resume (
                    Control_ptr which); 

            protected:
                Current(::CORBA::Object_ptr obj = 0);
                virtual ~Current(){ }

            private:
                Current( const Current&) { }
                void operator=(const Current&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class Current



        class EXPDLL_LIBOMG Current_out
         {
            public:
                Current_out (Current_ptr & p);
                Current_out (Current_var & p);
                Current_out (const Current_out & p) : ptr_(p.ptr_) {}
                Current_out & operator=(const Current_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Current_out & operator=(const Current_var & a);
                Current_out & operator=(Current_ptr p) {
                ptr_ = p; return *this;}
                inline operator Current_ptr & () { return ptr_; }
                inline Current_ptr & ptr () { return ptr_; }
                inline Current_ptr operator->() { return ptr_; }
            private:
                Current_ptr & ptr_;
        };  // class Current_out



        static const ::CORBA::TypeCode_ptr _tc_TransactionFactory;
        class EXPDLL_LIBOMG TransactionFactory : public virtual ::CORBA::Object
         {
            public:
                static TransactionFactory_ptr _duplicate(TransactionFactory_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static TransactionFactory_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static TransactionFactory_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Control_ptr create (
                    ::CORBA::ULong time_out); 

                virtual Control_ptr recreate (
                     const PropagationContext & ctx); 

            protected:
                TransactionFactory(::CORBA::Object_ptr obj = 0);
                virtual ~TransactionFactory(){ }

            private:
                TransactionFactory( const TransactionFactory&) { }
                void operator=(const TransactionFactory&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class TransactionFactory



        class EXPDLL_LIBOMG TransactionFactory_out
         {
            public:
                TransactionFactory_out (TransactionFactory_ptr & p);
                TransactionFactory_out (TransactionFactory_var & p);
                TransactionFactory_out (const TransactionFactory_out & p) : ptr_(p.ptr_) {}
                TransactionFactory_out & operator=(const TransactionFactory_out & a) {
                    ptr_ = a.ptr_; return *this;}
                TransactionFactory_out & operator=(const TransactionFactory_var & a);
                TransactionFactory_out & operator=(TransactionFactory_ptr p) {
                ptr_ = p; return *this;}
                inline operator TransactionFactory_ptr & () { return ptr_; }
                inline TransactionFactory_ptr & ptr () { return ptr_; }
                inline TransactionFactory_ptr operator->() { return ptr_; }
            private:
                TransactionFactory_ptr & ptr_;
        };  // class TransactionFactory_out



        static const ::CORBA::TypeCode_ptr _tc_Control;
        class EXPDLL_LIBOMG Control : public virtual ::CORBA::Object
         {
            public:
                static Control_ptr _duplicate(Control_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Control_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static Control_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Terminator_ptr get_terminator (); 

                virtual Coordinator_ptr get_coordinator (); 

            protected:
                Control(::CORBA::Object_ptr obj = 0);
                virtual ~Control(){ }

            private:
                Control( const Control&) { }
                void operator=(const Control&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class Control



        class EXPDLL_LIBOMG Control_out
         {
            public:
                Control_out (Control_ptr & p);
                Control_out (Control_var & p);
                Control_out (const Control_out & p) : ptr_(p.ptr_) {}
                Control_out & operator=(const Control_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Control_out & operator=(const Control_var & a);
                Control_out & operator=(Control_ptr p) {
                ptr_ = p; return *this;}
                inline operator Control_ptr & () { return ptr_; }
                inline Control_ptr & ptr () { return ptr_; }
                inline Control_ptr operator->() { return ptr_; }
            private:
                Control_ptr & ptr_;
        };  // class Control_out



        static const ::CORBA::TypeCode_ptr _tc_Terminator;
        class EXPDLL_LIBOMG Terminator : public virtual ::CORBA::Object
         {
            public:
                static Terminator_ptr _duplicate(Terminator_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Terminator_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static Terminator_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual void commit (
                    ::CORBA::Boolean report_heuristics); 

                virtual void rollback (); 

            protected:
                Terminator(::CORBA::Object_ptr obj = 0);
                virtual ~Terminator(){ }

            private:
                Terminator( const Terminator&) { }
                void operator=(const Terminator&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class Terminator



        class EXPDLL_LIBOMG Terminator_out
         {
            public:
                Terminator_out (Terminator_ptr & p);
                Terminator_out (Terminator_var & p);
                Terminator_out (const Terminator_out & p) : ptr_(p.ptr_) {}
                Terminator_out & operator=(const Terminator_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Terminator_out & operator=(const Terminator_var & a);
                Terminator_out & operator=(Terminator_ptr p) {
                ptr_ = p; return *this;}
                inline operator Terminator_ptr & () { return ptr_; }
                inline Terminator_ptr & ptr () { return ptr_; }
                inline Terminator_ptr operator->() { return ptr_; }
            private:
                Terminator_ptr & ptr_;
        };  // class Terminator_out



        static const ::CORBA::TypeCode_ptr _tc_Coordinator;
        class EXPDLL_LIBOMG Coordinator : public virtual ::CORBA::Object
         {
            public:
                static Coordinator_ptr _duplicate(Coordinator_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Coordinator_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static Coordinator_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Status get_status (); 

                virtual Status get_parent_status (); 

                virtual Status get_top_level_status (); 

                virtual ::CORBA::Boolean is_same_transaction (
                    Coordinator_ptr tc); 

                virtual ::CORBA::Boolean is_related_transaction (
                    Coordinator_ptr tc); 

                virtual ::CORBA::Boolean is_ancestor_transaction (
                    Coordinator_ptr tc); 

                virtual ::CORBA::Boolean is_descendant_transaction (
                    Coordinator_ptr tc); 

                virtual ::CORBA::Boolean is_top_level_transaction (); 

                virtual ::CORBA::ULong hash_transaction (); 

                virtual ::CORBA::ULong hash_top_level_tran (); 

                virtual RecoveryCoordinator_ptr register_resource (
                    Resource_ptr res); 

                virtual void register_synchronization (
                    Synchronization_ptr sync); 

                virtual void register_subtran_aware (
                    SubtransactionAwareResource_ptr res); 

                virtual void rollback_only (); 

                virtual ::CORBA::Char * get_transaction_name (); 

                virtual Control_ptr create_subtransaction (); 

                virtual PropagationContext * get_txcontext (); 

            protected:
                Coordinator(::CORBA::Object_ptr obj = 0);
                virtual ~Coordinator(){ }

            private:
                Coordinator( const Coordinator&) { }
                void operator=(const Coordinator&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class Coordinator



        class EXPDLL_LIBOMG Coordinator_out
         {
            public:
                Coordinator_out (Coordinator_ptr & p);
                Coordinator_out (Coordinator_var & p);
                Coordinator_out (const Coordinator_out & p) : ptr_(p.ptr_) {}
                Coordinator_out & operator=(const Coordinator_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Coordinator_out & operator=(const Coordinator_var & a);
                Coordinator_out & operator=(Coordinator_ptr p) {
                ptr_ = p; return *this;}
                inline operator Coordinator_ptr & () { return ptr_; }
                inline Coordinator_ptr & ptr () { return ptr_; }
                inline Coordinator_ptr operator->() { return ptr_; }
            private:
                Coordinator_ptr & ptr_;
        };  // class Coordinator_out



        static const ::CORBA::TypeCode_ptr _tc_RecoveryCoordinator;
        class EXPDLL_LIBOMG RecoveryCoordinator : public virtual ::CORBA::Object
         {
            public:
                static RecoveryCoordinator_ptr _duplicate(RecoveryCoordinator_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static RecoveryCoordinator_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static RecoveryCoordinator_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Status replay_completion (
                    Resource_ptr res); 

            protected:
                RecoveryCoordinator(::CORBA::Object_ptr obj = 0);
                virtual ~RecoveryCoordinator(){ }

            private:
                RecoveryCoordinator( const RecoveryCoordinator&) { }
                void operator=(const RecoveryCoordinator&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class RecoveryCoordinator



        class EXPDLL_LIBOMG RecoveryCoordinator_out
         {
            public:
                RecoveryCoordinator_out (RecoveryCoordinator_ptr & p);
                RecoveryCoordinator_out (RecoveryCoordinator_var & p);
                RecoveryCoordinator_out (const RecoveryCoordinator_out & p) : ptr_(p.ptr_) {}
                RecoveryCoordinator_out & operator=(const RecoveryCoordinator_out & a) {
                    ptr_ = a.ptr_; return *this;}
                RecoveryCoordinator_out & operator=(const RecoveryCoordinator_var & a);
                RecoveryCoordinator_out & operator=(RecoveryCoordinator_ptr p) {
                ptr_ = p; return *this;}
                inline operator RecoveryCoordinator_ptr & () { return ptr_; }
                inline RecoveryCoordinator_ptr & ptr () { return ptr_; }
                inline RecoveryCoordinator_ptr operator->() { return ptr_; }
            private:
                RecoveryCoordinator_ptr & ptr_;
        };  // class RecoveryCoordinator_out



        static const ::CORBA::TypeCode_ptr _tc_Resource;
        class EXPDLL_LIBOMG Resource : public virtual ::CORBA::Object
         {
            public:
                static Resource_ptr _duplicate(Resource_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Resource_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static Resource_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Vote prepare (); 

                virtual void rollback (); 

                virtual void commit (); 

                virtual void commit_one_phase (); 

                virtual void forget (); 

            protected:
                Resource(::CORBA::Object_ptr obj = 0);
                virtual ~Resource(){ }

            private:
                Resource( const Resource&) { }
                void operator=(const Resource&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class Resource



        class EXPDLL_LIBOMG Resource_out
         {
            public:
                Resource_out (Resource_ptr & p);
                Resource_out (Resource_var & p);
                Resource_out (const Resource_out & p) : ptr_(p.ptr_) {}
                Resource_out & operator=(const Resource_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Resource_out & operator=(const Resource_var & a);
                Resource_out & operator=(Resource_ptr p) {
                ptr_ = p; return *this;}
                inline operator Resource_ptr & () { return ptr_; }
                inline Resource_ptr & ptr () { return ptr_; }
                inline Resource_ptr operator->() { return ptr_; }
            private:
                Resource_ptr & ptr_;
        };  // class Resource_out



        static const ::CORBA::TypeCode_ptr _tc_TransactionalObject;
        class EXPDLL_LIBOMG TransactionalObject : public virtual ::CORBA::Object
         {
            public:
                static TransactionalObject_ptr _duplicate(TransactionalObject_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static TransactionalObject_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static TransactionalObject_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

            protected:
                TransactionalObject(::CORBA::Object_ptr obj = 0);
                virtual ~TransactionalObject(){ }

            private:
                TransactionalObject( const TransactionalObject&) { }
                void operator=(const TransactionalObject&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class TransactionalObject



        class EXPDLL_LIBOMG TransactionalObject_out
         {
            public:
                TransactionalObject_out (TransactionalObject_ptr & p);
                TransactionalObject_out (TransactionalObject_var & p);
                TransactionalObject_out (const TransactionalObject_out & p) : ptr_(p.ptr_) {}
                TransactionalObject_out & operator=(const TransactionalObject_out & a) {
                    ptr_ = a.ptr_; return *this;}
                TransactionalObject_out & operator=(const TransactionalObject_var & a);
                TransactionalObject_out & operator=(TransactionalObject_ptr p) {
                ptr_ = p; return *this;}
                inline operator TransactionalObject_ptr & () { return ptr_; }
                inline TransactionalObject_ptr & ptr () { return ptr_; }
                inline TransactionalObject_ptr operator->() { return ptr_; }
            private:
                TransactionalObject_ptr & ptr_;
        };  // class TransactionalObject_out



        static const ::CORBA::TypeCode_ptr _tc_Synchronization;
        class EXPDLL_LIBOMG Synchronization : public   TransactionalObject
         {
            public:
                static Synchronization_ptr _duplicate(Synchronization_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static Synchronization_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static Synchronization_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual void before_completion (); 

                virtual void after_completion (
                    Status status); 

            protected:
                Synchronization(::CORBA::Object_ptr obj = 0);
                virtual ~Synchronization(){ }

            private:
                Synchronization( const Synchronization&) { }
                void operator=(const Synchronization&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class Synchronization



        class EXPDLL_LIBOMG Synchronization_out
         {
            public:
                Synchronization_out (Synchronization_ptr & p);
                Synchronization_out (Synchronization_var & p);
                Synchronization_out (const Synchronization_out & p) : ptr_(p.ptr_) {}
                Synchronization_out & operator=(const Synchronization_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Synchronization_out & operator=(const Synchronization_var & a);
                Synchronization_out & operator=(Synchronization_ptr p) {
                ptr_ = p; return *this;}
                inline operator Synchronization_ptr & () { return ptr_; }
                inline Synchronization_ptr & ptr () { return ptr_; }
                inline Synchronization_ptr operator->() { return ptr_; }
            private:
                Synchronization_ptr & ptr_;
        };  // class Synchronization_out



        static const ::CORBA::TypeCode_ptr _tc_SubtransactionAwareResource;
        class EXPDLL_LIBOMG SubtransactionAwareResource : public   Resource
         {
            public:
                static SubtransactionAwareResource_ptr _duplicate(SubtransactionAwareResource_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static SubtransactionAwareResource_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static SubtransactionAwareResource_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual void commit_subtransaction (
                    Coordinator_ptr parent); 

                virtual void rollback_subtransaction (); 

            protected:
                SubtransactionAwareResource(::CORBA::Object_ptr obj = 0);
                virtual ~SubtransactionAwareResource(){ }

            private:
                SubtransactionAwareResource( const SubtransactionAwareResource&) { }
                void operator=(const SubtransactionAwareResource&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class SubtransactionAwareResource



        class EXPDLL_LIBOMG SubtransactionAwareResource_out
         {
            public:
                SubtransactionAwareResource_out (SubtransactionAwareResource_ptr & p);
                SubtransactionAwareResource_out (SubtransactionAwareResource_var & p);
                SubtransactionAwareResource_out (const SubtransactionAwareResource_out & p) : ptr_(p.ptr_) {}
                SubtransactionAwareResource_out & operator=(const SubtransactionAwareResource_out & a) {
                    ptr_ = a.ptr_; return *this;}
                SubtransactionAwareResource_out & operator=(const SubtransactionAwareResource_var & a);
                SubtransactionAwareResource_out & operator=(SubtransactionAwareResource_ptr p) {
                ptr_ = p; return *this;}
                inline operator SubtransactionAwareResource_ptr & () { return ptr_; }
                inline SubtransactionAwareResource_ptr & ptr () { return ptr_; }
                inline SubtransactionAwareResource_ptr operator->() { return ptr_; }
            private:
                SubtransactionAwareResource_ptr & ptr_;
        };  // class SubtransactionAwareResource_out

    };  // class CosTransactions

void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Status obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Status &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Vote obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Vote &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::otid_t &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::otid_t *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::otid_t *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::TransIdentity &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::TransIdentity *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::TransIdentity *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::PropagationContext &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::PropagationContext *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::PropagationContext *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::HeuristicRollback &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::HeuristicRollback *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::HeuristicRollback *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::HeuristicCommit &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::HeuristicCommit *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::HeuristicCommit *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::HeuristicMixed &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::HeuristicMixed *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::HeuristicMixed *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::HeuristicHazard &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::HeuristicHazard *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::HeuristicHazard *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::SubtransactionsUnavailable &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::SubtransactionsUnavailable *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::SubtransactionsUnavailable *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::NotSubtransaction &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::NotSubtransaction *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::NotSubtransaction *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::Inactive &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Inactive *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Inactive *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::NotPrepared &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::NotPrepared *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::NotPrepared *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::NoTransaction &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::NoTransaction *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::NoTransaction *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::InvalidControl &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::InvalidControl *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::InvalidControl *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::Unavailable &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Unavailable *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Unavailable *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosTransactions::SynchronizationUnavailable &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::SynchronizationUnavailable *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::SynchronizationUnavailable *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Current_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Current_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::TransactionFactory_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::TransactionFactory_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Control_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Control_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Terminator_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Terminator_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Coordinator_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Coordinator_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::RecoveryCoordinator_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::RecoveryCoordinator_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Resource_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Resource_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::TransactionalObject_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::TransactionalObject_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::Synchronization_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::Synchronization_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosTransactions::SubtransactionAwareResource_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosTransactions::SubtransactionAwareResource_ptr &obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::Status &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::Status &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::Vote &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::Vote &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::otid_t &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::otid_t &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::TransIdentity &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::TransIdentity &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::PropagationContext &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::PropagationContext &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::HeuristicRollback &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::HeuristicRollback &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::HeuristicCommit &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::HeuristicCommit &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::HeuristicMixed &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::HeuristicMixed &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::HeuristicHazard &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::HeuristicHazard &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::SubtransactionsUnavailable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::SubtransactionsUnavailable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::NotSubtransaction &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::NotSubtransaction &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::Inactive &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::Inactive &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::NotPrepared &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::NotPrepared &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::NoTransaction &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::NoTransaction &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::InvalidControl &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::InvalidControl &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::Unavailable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::Unavailable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosTransactions::SynchronizationUnavailable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosTransactions::SynchronizationUnavailable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::Current_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Current_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Current_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::TransactionFactory_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::TransactionFactory_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::TransactionFactory_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::Control_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Control_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Control_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::Terminator_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Terminator_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Terminator_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::Coordinator_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Coordinator_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Coordinator_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::RecoveryCoordinator_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::RecoveryCoordinator_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::RecoveryCoordinator_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::Resource_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Resource_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Resource_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::TransactionalObject_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::TransactionalObject_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::TransactionalObject_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::Synchronization_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Synchronization_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::Synchronization_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosTransactions::SubtransactionAwareResource_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::SubtransactionAwareResource_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosTransactions::SubtransactionAwareResource_var &_obj);
#ifdef ORB_IMPORT_DEFINED_ots_c
#undef ORB_IMPORT_DEFINED_ots_c
#undef EXPDLL_LIBOMG
#endif
#endif

