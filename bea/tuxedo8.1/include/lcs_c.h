/*******************************************************************
 * Created Mon Jan 27 07:37:44 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (lcs_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    FactoryFinder
 *    LifeCycleObject
 *    GenericFactory
 *
 */


#ifndef _lcs_c_H
#define _lcs_c_H

#include <string.h>
#include <CORBA.h>
#include <orbgen.h>

#if defined(WIN32)
#pragma warning(disable:4250)
#endif


#ifndef EXPDLL_LIBOMG
#define ORB_IMPORT_DEFINED_lcs_c
#ifdef WIN32 
#define EXPDLL_LIBOMG ORBIMPDLL
#else
#define EXPDLL_LIBOMG
#endif
#endif

#include "ns_c.h"
class EXPDLL_LIBOMG CosLifeCycle
{
    public:
        class	FactoryFinder;
        typedef	FactoryFinder *	FactoryFinder_ptr;
        class FactoryFinder_out;

        class EXPDLL_LIBOMG FactoryFinder_var : public ::CORBA::_var {
            public:
                FactoryFinder_var();
                inline FactoryFinder_var(FactoryFinder_ptr p) {ptr_ = p; }
                FactoryFinder_var(const FactoryFinder_var &a);
                ~FactoryFinder_var()
                    { free();}

                FactoryFinder_var &operator=(FactoryFinder_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                FactoryFinder_var &operator=(const FactoryFinder_var &a);
                inline FactoryFinder_ptr in () const { return ptr_; }
                inline FactoryFinder_ptr & inout () { return ptr_; }
                FactoryFinder_ptr & out ();
                FactoryFinder_ptr _retn ();

                inline operator FactoryFinder_ptr&() { return ptr_; }
                inline operator const FactoryFinder_ptr&() const { return ptr_; }
                inline FactoryFinder_ptr operator->() const { return ptr_; }

                inline FactoryFinder_ptr & ptr () { return ptr_; }
            protected:
                FactoryFinder_ptr ptr_;
                void free();
                void reset(FactoryFinder_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class FactoryFinder_var


        class	LifeCycleObject;
        typedef	LifeCycleObject *	LifeCycleObject_ptr;
        class LifeCycleObject_out;

        class EXPDLL_LIBOMG LifeCycleObject_var : public ::CORBA::_var {
            public:
                LifeCycleObject_var();
                inline LifeCycleObject_var(LifeCycleObject_ptr p) {ptr_ = p; }
                LifeCycleObject_var(const LifeCycleObject_var &a);
                ~LifeCycleObject_var()
                    { free();}

                LifeCycleObject_var &operator=(LifeCycleObject_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                LifeCycleObject_var &operator=(const LifeCycleObject_var &a);
                inline LifeCycleObject_ptr in () const { return ptr_; }
                inline LifeCycleObject_ptr & inout () { return ptr_; }
                LifeCycleObject_ptr & out ();
                LifeCycleObject_ptr _retn ();

                inline operator LifeCycleObject_ptr&() { return ptr_; }
                inline operator const LifeCycleObject_ptr&() const { return ptr_; }
                inline LifeCycleObject_ptr operator->() const { return ptr_; }

                inline LifeCycleObject_ptr & ptr () { return ptr_; }
            protected:
                LifeCycleObject_ptr ptr_;
                void free();
                void reset(LifeCycleObject_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class LifeCycleObject_var


        class	GenericFactory;
        typedef	GenericFactory *	GenericFactory_ptr;
        class GenericFactory_out;

        class EXPDLL_LIBOMG GenericFactory_var : public ::CORBA::_var {
            public:
                GenericFactory_var();
                inline GenericFactory_var(GenericFactory_ptr p) {ptr_ = p; }
                GenericFactory_var(const GenericFactory_var &a);
                ~GenericFactory_var()
                    { free();}

                GenericFactory_var &operator=(GenericFactory_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                GenericFactory_var &operator=(const GenericFactory_var &a);
                inline GenericFactory_ptr in () const { return ptr_; }
                inline GenericFactory_ptr & inout () { return ptr_; }
                GenericFactory_ptr & out ();
                GenericFactory_ptr _retn ();

                inline operator GenericFactory_ptr&() { return ptr_; }
                inline operator const GenericFactory_ptr&() const { return ptr_; }
                inline GenericFactory_ptr operator->() const { return ptr_; }

                inline GenericFactory_ptr & ptr () { return ptr_; }
            protected:
                GenericFactory_ptr ptr_;
                void free();
                void reset(GenericFactory_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class GenericFactory_var


        typedef ::CosNaming::Name Key;
        typedef ::CosNaming::Name_out Key_out;
        typedef ::CosNaming::Name_var Key_var;
        static const ::CORBA::TypeCode_ptr _tc_Key;
        typedef ::CORBA::Object Factory;
        typedef ::CORBA::Object_ptr Factory_ptr;
        typedef ::CORBA::Object_out Factory_out;
        typedef ::CORBA::Object_var Factory_var;
        static const ::CORBA::TypeCode_ptr _tc_Factory;


        class EXPDLL_LIBOMG Factories
        {
            public:


                class EXPDLL_LIBOMG _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(Factory_ptr _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(Factory_ptr _ptr);
                        operator Factory_ptr() const;
                        operator Factory_ptr &();
                        Factory_ptr operator->();

                        void OBB__release(::CORBA::Boolean _relse);
                        ::CORBA::Boolean OBB__release();

                        static Factory_ptr allocbuf(::CORBA::ULong _nelems);
                        static void freebuf(Factory_ptr _ptr);

                    private:
                        Factory_ptr _data;
                        ::CORBA::Boolean _release;
                };  // class _ForSeq_var

                Factories();

                Factories(::CORBA::ULong _max);

                Factories
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    Factory_ptr *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                Factories(const Factories &_ptr);

                ~Factories();

                Factories &operator=(const Factories& _ptr);

                inline ::CORBA::ULong maximum() const {return _maximum;}

                void length(::CORBA::ULong);
                inline ::CORBA::ULong length() const {return _current;}

                inline _ForSeq_var &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                inline const _ForSeq_var &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const _ForSeq_var &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static Factory_ptr *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(Factory_ptr *_ptr);

            private:
                _ForSeq_var *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
                static _ForSeq_var *OBB__allocbuf(::CORBA::ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class Factories

        typedef	Factories *	Factories_ptr;
        class EXPDLL_LIBOMG Factories_var
        {
            public:
                inline Factories_var() {_ptr = 0;}
                inline Factories_var(Factories *_obj) {_ptr = _obj;}
                Factories_var(const Factories_var &_obj) {_ptr = 0; *this = _obj;}
                ~Factories_var();
                Factories_var &operator=(Factories *);
                Factories_var &operator=(const Factories_var &);
                inline Factories::_ForSeq_var &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline Factories *operator->() {return _ptr;}
                inline const Factories *operator->() const {return _ptr;}
                inline const Factories & in () const { return *_ptr; }
                inline Factories & inout () { return *_ptr; }
                Factories *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                Factories * _retn ()
                {
                    Factories *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline Factories_ptr & ptr() { return _ptr; }
                inline operator Factories&() { return *_ptr; }
                inline operator const Factories&() const { return *_ptr; }
                inline operator Factories_ptr &() { return _ptr; }
            private:
                Factories *_ptr;
        };  // class Factories_var

        class EXPDLL_LIBOMG Factories_out
        {
            public:
                Factories_out (Factories *& p) : ptr_(p) { ptr_ = 0; }
                Factories_out (Factories_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                Factories_out (const Factories_out & a) : ptr_(a.ptr_) {}
                Factories_out & operator=(const Factories_out & a) {
                    ptr_ = a.ptr_; return *this; }
                Factories_out & operator=(Factories * p) {
                    ptr_ = p; return *this; }
                inline operator Factories_ptr & () { return ptr_; }
                inline Factories_ptr & ptr () { return ptr_; }
                inline Factories_ptr operator->() { return ptr_; }
                inline Factories::_ForSeq_var & operator[](::CORBA::ULong _index) {return ((*ptr_)[_index]);}
            private:
                Factories_ptr & ptr_;
                void operator=(const Factories_var &);

        };  // class Factories_out
        static const ::CORBA::TypeCode_ptr _tc_Factories;


        struct EXPDLL_LIBOMG NVP {
            ::CORBA::String_var name;
             ::CORBA::Any value;
            NVP &operator=(const NVP &_obj);
        };
        typedef	NVP *	NVP_ptr;
        class EXPDLL_LIBOMG NVP_var
        {
            public:
                inline NVP_var() {_ptr = 0;}
                inline NVP_var(NVP *_obj) {_ptr = _obj;}
                NVP_var(const NVP_var &_obj) {_ptr = 0; *this = _obj;}
                ~NVP_var();
                NVP_var &operator=(NVP *);
                NVP_var &operator=(const NVP_var &);
                inline NVP *operator->() {return _ptr;}
                inline const NVP *operator->() const {return _ptr;}
                inline const NVP & in () const { return *_ptr; }
                inline NVP & inout () { return *_ptr; }
                NVP *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                NVP * _retn ()
                {
                    NVP *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline NVP_ptr & ptr() { return _ptr; }
                inline operator NVP&() { return *_ptr; }
                inline operator const NVP&() const { return *_ptr; }
                inline operator NVP_ptr &() { return _ptr; }
            private:
                NVP *_ptr;
        };  // class NVP_var

        class EXPDLL_LIBOMG NVP_out
        {
            public:
                NVP_out (NVP *& p) : ptr_(p) { ptr_ = 0; }
                NVP_out (NVP_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NVP_out (const NVP_out & a) : ptr_(a.ptr_) {}
                NVP_out & operator=(const NVP_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NVP_out & operator=(NVP * p) {
                    ptr_ = p; return *this; }
                inline operator NVP_ptr & () { return ptr_; }
                inline NVP_ptr & ptr () { return ptr_; }
                inline NVP_ptr operator->() { return ptr_; }
            private:
                NVP_ptr & ptr_;
                void operator=(const NVP_var &);

        };  // class NVP_out
        static const ::CORBA::TypeCode_ptr _tc_NVP;
        typedef NVP NameValuePair;
        typedef NVP_out NameValuePair_out;
        typedef NVP_var NameValuePair_var;
        static const ::CORBA::TypeCode_ptr _tc_NameValuePair;


        class EXPDLL_LIBOMG Criteria
        {
            public:
                Criteria();

                Criteria(::CORBA::ULong _max);

                Criteria
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    NameValuePair *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                Criteria(const Criteria &_ptr);

                ~Criteria();

                Criteria &operator=(const Criteria& _ptr);

                inline ::CORBA::ULong maximum() const {return _maximum;}

                void length(::CORBA::ULong);
                inline ::CORBA::ULong length() const {return _current;}

                inline NameValuePair &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                inline const NameValuePair &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const NameValuePair &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static NameValuePair *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(NameValuePair *_ptr);

                inline NameValuePair * OBB__GetData() { return _data; }
            private:
                NameValuePair *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
        };  // class Criteria

        typedef	Criteria *	Criteria_ptr;
        class EXPDLL_LIBOMG Criteria_var
        {
            public:
                inline Criteria_var() {_ptr = 0;}
                inline Criteria_var(Criteria *_obj) {_ptr = _obj;}
                Criteria_var(const Criteria_var &_obj) {_ptr = 0; *this = _obj;}
                ~Criteria_var();
                Criteria_var &operator=(Criteria *);
                Criteria_var &operator=(const Criteria_var &);
                inline NameValuePair &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline Criteria *operator->() {return _ptr;}
                inline const Criteria *operator->() const {return _ptr;}
                inline const Criteria & in () const { return *_ptr; }
                inline Criteria & inout () { return *_ptr; }
                Criteria *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                Criteria * _retn ()
                {
                    Criteria *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline Criteria_ptr & ptr() { return _ptr; }
                inline operator Criteria&() { return *_ptr; }
                inline operator const Criteria&() const { return *_ptr; }
                inline operator Criteria_ptr &() { return _ptr; }
            private:
                Criteria *_ptr;
        };  // class Criteria_var

        class EXPDLL_LIBOMG Criteria_out
        {
            public:
                Criteria_out (Criteria *& p) : ptr_(p) { ptr_ = 0; }
                Criteria_out (Criteria_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                Criteria_out (const Criteria_out & a) : ptr_(a.ptr_) {}
                Criteria_out & operator=(const Criteria_out & a) {
                    ptr_ = a.ptr_; return *this; }
                Criteria_out & operator=(Criteria * p) {
                    ptr_ = p; return *this; }
                inline operator Criteria_ptr & () { return ptr_; }
                inline Criteria_ptr & ptr () { return ptr_; }
                inline Criteria_ptr operator->() { return ptr_; }
                inline NameValuePair & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                Criteria_ptr & ptr_;
                void operator=(const Criteria_var &);

        };  // class Criteria_out
        static const ::CORBA::TypeCode_ptr _tc_Criteria;
        class EXPDLL_LIBOMG NoFactory : public ::CORBA::UserException
        {
            public:
                static NoFactory * _narrow(::CORBA::Exception_ptr);
                NoFactory ( Key _x_search_key);
                NoFactory ();
                NoFactory (const NoFactory &);
                ~NoFactory ();
                NoFactory & operator=(const NoFactory &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosLifeCycle/NoFactory:1.0"; }



                 Key search_key;
        };  // class NoFactory


        typedef	NoFactory *	NoFactory_ptr;
        class EXPDLL_LIBOMG NoFactory_var
        {
            public:
                inline NoFactory_var() {_ptr = 0;}
                inline NoFactory_var(NoFactory *_obj) {_ptr = _obj;}
                NoFactory_var(const NoFactory_var &_obj) {_ptr = 0; *this = _obj;}
                ~NoFactory_var();
                NoFactory_var &operator=(NoFactory *);
                NoFactory_var &operator=(const NoFactory_var &);
                inline NoFactory *operator->() {return _ptr;}
                inline const NoFactory *operator->() const {return _ptr;}
                inline const NoFactory & in () const { return *_ptr; }
                inline NoFactory & inout () { return *_ptr; }
                NoFactory *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                NoFactory * _retn ()
                {
                    NoFactory *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline NoFactory_ptr & ptr() { return _ptr; }
                inline operator NoFactory&() { return *_ptr; }
                inline operator const NoFactory&() const { return *_ptr; }
                inline operator NoFactory_ptr &() { return _ptr; }
            private:
                NoFactory *_ptr;
        };  // class NoFactory_var

        class EXPDLL_LIBOMG NoFactory_out
        {
            public:
                NoFactory_out (NoFactory *& p) : ptr_(p) { ptr_ = 0; }
                NoFactory_out (NoFactory_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NoFactory_out (const NoFactory_out & a) : ptr_(a.ptr_) {}
                NoFactory_out & operator=(const NoFactory_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NoFactory_out & operator=(NoFactory * p) {
                    ptr_ = p; return *this; }
                inline operator NoFactory_ptr & () { return ptr_; }
                inline NoFactory_ptr & ptr () { return ptr_; }
                inline NoFactory_ptr operator->() { return ptr_; }
            private:
                NoFactory_ptr & ptr_;
                void operator=(const NoFactory_var &);

        };  // class NoFactory_out
        static const ::CORBA::TypeCode_ptr _tc_NoFactory;
        class EXPDLL_LIBOMG NotCopyable : public ::CORBA::UserException
        {
            public:
                static NotCopyable * _narrow(::CORBA::Exception_ptr);
                NotCopyable ( const char * _x_reason);
                NotCopyable ();
                NotCopyable (const NotCopyable &);
                ~NotCopyable ();
                NotCopyable & operator=(const NotCopyable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosLifeCycle/NotCopyable:1.0"; }

                ::CORBA::String_var reason;
        };  // class NotCopyable


        typedef	NotCopyable *	NotCopyable_ptr;
        class EXPDLL_LIBOMG NotCopyable_var
        {
            public:
                inline NotCopyable_var() {_ptr = 0;}
                inline NotCopyable_var(NotCopyable *_obj) {_ptr = _obj;}
                NotCopyable_var(const NotCopyable_var &_obj) {_ptr = 0; *this = _obj;}
                ~NotCopyable_var();
                NotCopyable_var &operator=(NotCopyable *);
                NotCopyable_var &operator=(const NotCopyable_var &);
                inline NotCopyable *operator->() {return _ptr;}
                inline const NotCopyable *operator->() const {return _ptr;}
                inline const NotCopyable & in () const { return *_ptr; }
                inline NotCopyable & inout () { return *_ptr; }
                NotCopyable *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                NotCopyable * _retn ()
                {
                    NotCopyable *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline NotCopyable_ptr & ptr() { return _ptr; }
                inline operator NotCopyable&() { return *_ptr; }
                inline operator const NotCopyable&() const { return *_ptr; }
                inline operator NotCopyable_ptr &() { return _ptr; }
            private:
                NotCopyable *_ptr;
        };  // class NotCopyable_var

        class EXPDLL_LIBOMG NotCopyable_out
        {
            public:
                NotCopyable_out (NotCopyable *& p) : ptr_(p) { ptr_ = 0; }
                NotCopyable_out (NotCopyable_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NotCopyable_out (const NotCopyable_out & a) : ptr_(a.ptr_) {}
                NotCopyable_out & operator=(const NotCopyable_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NotCopyable_out & operator=(NotCopyable * p) {
                    ptr_ = p; return *this; }
                inline operator NotCopyable_ptr & () { return ptr_; }
                inline NotCopyable_ptr & ptr () { return ptr_; }
                inline NotCopyable_ptr operator->() { return ptr_; }
            private:
                NotCopyable_ptr & ptr_;
                void operator=(const NotCopyable_var &);

        };  // class NotCopyable_out
        static const ::CORBA::TypeCode_ptr _tc_NotCopyable;
        class EXPDLL_LIBOMG NotMovable : public ::CORBA::UserException
        {
            public:
                static NotMovable * _narrow(::CORBA::Exception_ptr);
                NotMovable ( const char * _x_reason);
                NotMovable ();
                NotMovable (const NotMovable &);
                ~NotMovable ();
                NotMovable & operator=(const NotMovable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosLifeCycle/NotMovable:1.0"; }

                ::CORBA::String_var reason;
        };  // class NotMovable


        typedef	NotMovable *	NotMovable_ptr;
        class EXPDLL_LIBOMG NotMovable_var
        {
            public:
                inline NotMovable_var() {_ptr = 0;}
                inline NotMovable_var(NotMovable *_obj) {_ptr = _obj;}
                NotMovable_var(const NotMovable_var &_obj) {_ptr = 0; *this = _obj;}
                ~NotMovable_var();
                NotMovable_var &operator=(NotMovable *);
                NotMovable_var &operator=(const NotMovable_var &);
                inline NotMovable *operator->() {return _ptr;}
                inline const NotMovable *operator->() const {return _ptr;}
                inline const NotMovable & in () const { return *_ptr; }
                inline NotMovable & inout () { return *_ptr; }
                NotMovable *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                NotMovable * _retn ()
                {
                    NotMovable *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline NotMovable_ptr & ptr() { return _ptr; }
                inline operator NotMovable&() { return *_ptr; }
                inline operator const NotMovable&() const { return *_ptr; }
                inline operator NotMovable_ptr &() { return _ptr; }
            private:
                NotMovable *_ptr;
        };  // class NotMovable_var

        class EXPDLL_LIBOMG NotMovable_out
        {
            public:
                NotMovable_out (NotMovable *& p) : ptr_(p) { ptr_ = 0; }
                NotMovable_out (NotMovable_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NotMovable_out (const NotMovable_out & a) : ptr_(a.ptr_) {}
                NotMovable_out & operator=(const NotMovable_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NotMovable_out & operator=(NotMovable * p) {
                    ptr_ = p; return *this; }
                inline operator NotMovable_ptr & () { return ptr_; }
                inline NotMovable_ptr & ptr () { return ptr_; }
                inline NotMovable_ptr operator->() { return ptr_; }
            private:
                NotMovable_ptr & ptr_;
                void operator=(const NotMovable_var &);

        };  // class NotMovable_out
        static const ::CORBA::TypeCode_ptr _tc_NotMovable;
        class EXPDLL_LIBOMG NotRemovable : public ::CORBA::UserException
        {
            public:
                static NotRemovable * _narrow(::CORBA::Exception_ptr);
                NotRemovable ( const char * _x_reason);
                NotRemovable ();
                NotRemovable (const NotRemovable &);
                ~NotRemovable ();
                NotRemovable & operator=(const NotRemovable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosLifeCycle/NotRemovable:1.0"; }

                ::CORBA::String_var reason;
        };  // class NotRemovable


        typedef	NotRemovable *	NotRemovable_ptr;
        class EXPDLL_LIBOMG NotRemovable_var
        {
            public:
                inline NotRemovable_var() {_ptr = 0;}
                inline NotRemovable_var(NotRemovable *_obj) {_ptr = _obj;}
                NotRemovable_var(const NotRemovable_var &_obj) {_ptr = 0; *this = _obj;}
                ~NotRemovable_var();
                NotRemovable_var &operator=(NotRemovable *);
                NotRemovable_var &operator=(const NotRemovable_var &);
                inline NotRemovable *operator->() {return _ptr;}
                inline const NotRemovable *operator->() const {return _ptr;}
                inline const NotRemovable & in () const { return *_ptr; }
                inline NotRemovable & inout () { return *_ptr; }
                NotRemovable *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                NotRemovable * _retn ()
                {
                    NotRemovable *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline NotRemovable_ptr & ptr() { return _ptr; }
                inline operator NotRemovable&() { return *_ptr; }
                inline operator const NotRemovable&() const { return *_ptr; }
                inline operator NotRemovable_ptr &() { return _ptr; }
            private:
                NotRemovable *_ptr;
        };  // class NotRemovable_var

        class EXPDLL_LIBOMG NotRemovable_out
        {
            public:
                NotRemovable_out (NotRemovable *& p) : ptr_(p) { ptr_ = 0; }
                NotRemovable_out (NotRemovable_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NotRemovable_out (const NotRemovable_out & a) : ptr_(a.ptr_) {}
                NotRemovable_out & operator=(const NotRemovable_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NotRemovable_out & operator=(NotRemovable * p) {
                    ptr_ = p; return *this; }
                inline operator NotRemovable_ptr & () { return ptr_; }
                inline NotRemovable_ptr & ptr () { return ptr_; }
                inline NotRemovable_ptr operator->() { return ptr_; }
            private:
                NotRemovable_ptr & ptr_;
                void operator=(const NotRemovable_var &);

        };  // class NotRemovable_out
        static const ::CORBA::TypeCode_ptr _tc_NotRemovable;
        class EXPDLL_LIBOMG InvalidCriteria : public ::CORBA::UserException
        {
            public:
                static InvalidCriteria * _narrow(::CORBA::Exception_ptr);
                InvalidCriteria ( Criteria _x_invalid_criteria);
                InvalidCriteria ();
                InvalidCriteria (const InvalidCriteria &);
                ~InvalidCriteria ();
                InvalidCriteria & operator=(const InvalidCriteria &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosLifeCycle/InvalidCriteria:1.0"; }



                 Criteria invalid_criteria;
        };  // class InvalidCriteria


        typedef	InvalidCriteria *	InvalidCriteria_ptr;
        class EXPDLL_LIBOMG InvalidCriteria_var
        {
            public:
                inline InvalidCriteria_var() {_ptr = 0;}
                inline InvalidCriteria_var(InvalidCriteria *_obj) {_ptr = _obj;}
                InvalidCriteria_var(const InvalidCriteria_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidCriteria_var();
                InvalidCriteria_var &operator=(InvalidCriteria *);
                InvalidCriteria_var &operator=(const InvalidCriteria_var &);
                inline InvalidCriteria *operator->() {return _ptr;}
                inline const InvalidCriteria *operator->() const {return _ptr;}
                inline const InvalidCriteria & in () const { return *_ptr; }
                inline InvalidCriteria & inout () { return *_ptr; }
                InvalidCriteria *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InvalidCriteria * _retn ()
                {
                    InvalidCriteria *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InvalidCriteria_ptr & ptr() { return _ptr; }
                inline operator InvalidCriteria&() { return *_ptr; }
                inline operator const InvalidCriteria&() const { return *_ptr; }
                inline operator InvalidCriteria_ptr &() { return _ptr; }
            private:
                InvalidCriteria *_ptr;
        };  // class InvalidCriteria_var

        class EXPDLL_LIBOMG InvalidCriteria_out
        {
            public:
                InvalidCriteria_out (InvalidCriteria *& p) : ptr_(p) { ptr_ = 0; }
                InvalidCriteria_out (InvalidCriteria_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidCriteria_out (const InvalidCriteria_out & a) : ptr_(a.ptr_) {}
                InvalidCriteria_out & operator=(const InvalidCriteria_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidCriteria_out & operator=(InvalidCriteria * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidCriteria_ptr & () { return ptr_; }
                inline InvalidCriteria_ptr & ptr () { return ptr_; }
                inline InvalidCriteria_ptr operator->() { return ptr_; }
            private:
                InvalidCriteria_ptr & ptr_;
                void operator=(const InvalidCriteria_var &);

        };  // class InvalidCriteria_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidCriteria;
        class EXPDLL_LIBOMG CannotMeetCriteria : public ::CORBA::UserException
        {
            public:
                static CannotMeetCriteria * _narrow(::CORBA::Exception_ptr);
                CannotMeetCriteria ( Criteria _x_unmet_criteria);
                CannotMeetCriteria ();
                CannotMeetCriteria (const CannotMeetCriteria &);
                ~CannotMeetCriteria ();
                CannotMeetCriteria & operator=(const CannotMeetCriteria &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosLifeCycle/CannotMeetCriteria:1.0"; }



                 Criteria unmet_criteria;
        };  // class CannotMeetCriteria


        typedef	CannotMeetCriteria *	CannotMeetCriteria_ptr;
        class EXPDLL_LIBOMG CannotMeetCriteria_var
        {
            public:
                inline CannotMeetCriteria_var() {_ptr = 0;}
                inline CannotMeetCriteria_var(CannotMeetCriteria *_obj) {_ptr = _obj;}
                CannotMeetCriteria_var(const CannotMeetCriteria_var &_obj) {_ptr = 0; *this = _obj;}
                ~CannotMeetCriteria_var();
                CannotMeetCriteria_var &operator=(CannotMeetCriteria *);
                CannotMeetCriteria_var &operator=(const CannotMeetCriteria_var &);
                inline CannotMeetCriteria *operator->() {return _ptr;}
                inline const CannotMeetCriteria *operator->() const {return _ptr;}
                inline const CannotMeetCriteria & in () const { return *_ptr; }
                inline CannotMeetCriteria & inout () { return *_ptr; }
                CannotMeetCriteria *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                CannotMeetCriteria * _retn ()
                {
                    CannotMeetCriteria *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline CannotMeetCriteria_ptr & ptr() { return _ptr; }
                inline operator CannotMeetCriteria&() { return *_ptr; }
                inline operator const CannotMeetCriteria&() const { return *_ptr; }
                inline operator CannotMeetCriteria_ptr &() { return _ptr; }
            private:
                CannotMeetCriteria *_ptr;
        };  // class CannotMeetCriteria_var

        class EXPDLL_LIBOMG CannotMeetCriteria_out
        {
            public:
                CannotMeetCriteria_out (CannotMeetCriteria *& p) : ptr_(p) { ptr_ = 0; }
                CannotMeetCriteria_out (CannotMeetCriteria_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                CannotMeetCriteria_out (const CannotMeetCriteria_out & a) : ptr_(a.ptr_) {}
                CannotMeetCriteria_out & operator=(const CannotMeetCriteria_out & a) {
                    ptr_ = a.ptr_; return *this; }
                CannotMeetCriteria_out & operator=(CannotMeetCriteria * p) {
                    ptr_ = p; return *this; }
                inline operator CannotMeetCriteria_ptr & () { return ptr_; }
                inline CannotMeetCriteria_ptr & ptr () { return ptr_; }
                inline CannotMeetCriteria_ptr operator->() { return ptr_; }
            private:
                CannotMeetCriteria_ptr & ptr_;
                void operator=(const CannotMeetCriteria_var &);

        };  // class CannotMeetCriteria_out
        static const ::CORBA::TypeCode_ptr _tc_CannotMeetCriteria;
        class EXPDLL_LIBOMG NotImplemented : public ::CORBA::UserException
        {
            public:
                static NotImplemented * _narrow(::CORBA::Exception_ptr);
                NotImplemented ();
                NotImplemented (const NotImplemented &);
                ~NotImplemented ();
                NotImplemented & operator=(const NotImplemented &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:omg.org/CosLifeCycle/NotImplemented:1.0"; }

        };  // class NotImplemented


        typedef	NotImplemented *	NotImplemented_ptr;
        class EXPDLL_LIBOMG NotImplemented_var
        {
            public:
                inline NotImplemented_var() {_ptr = 0;}
                inline NotImplemented_var(NotImplemented *_obj) {_ptr = _obj;}
                NotImplemented_var(const NotImplemented_var &_obj) {_ptr = 0; *this = _obj;}
                ~NotImplemented_var();
                NotImplemented_var &operator=(NotImplemented *);
                NotImplemented_var &operator=(const NotImplemented_var &);
                inline NotImplemented *operator->() {return _ptr;}
                inline const NotImplemented *operator->() const {return _ptr;}
                inline const NotImplemented & in () const { return *_ptr; }
                inline NotImplemented & inout () { return *_ptr; }
                NotImplemented & out ()
                {
                    NotImplemented *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                NotImplemented & _retn ()
                {
                    NotImplemented *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline NotImplemented_ptr & ptr() { return _ptr; }
                inline operator NotImplemented&() { return *_ptr; }
                inline operator const NotImplemented&() const { return *_ptr; }
                inline operator NotImplemented_ptr &() { return _ptr; }
            private:
                NotImplemented *_ptr;
        };  // class NotImplemented_var

        class EXPDLL_LIBOMG NotImplemented_out
        {
            public:
                NotImplemented_out (NotImplemented *& p) : ptr_(p) { ptr_ = 0; }
                NotImplemented_out (NotImplemented_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NotImplemented_out (const NotImplemented_out & a) : ptr_(a.ptr_) {}
                NotImplemented_out & operator=(const NotImplemented_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NotImplemented_out & operator=(NotImplemented * p) {
                    ptr_ = p; return *this; }
                inline operator NotImplemented_ptr & () { return ptr_; }
                inline NotImplemented_ptr & ptr () { return ptr_; }
                inline NotImplemented_ptr operator->() { return ptr_; }
            private:
                NotImplemented_ptr & ptr_;
                void operator=(const NotImplemented_var &);

        };  // class NotImplemented_out
        static const ::CORBA::TypeCode_ptr _tc_NotImplemented;


        static const ::CORBA::TypeCode_ptr _tc_FactoryFinder;
        class EXPDLL_LIBOMG FactoryFinder : public virtual ::CORBA::Object
         {
            public:
                static FactoryFinder_ptr _duplicate(FactoryFinder_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static FactoryFinder_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static FactoryFinder_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual Factories * find_factories (
                     const Key & factory_key); 

            protected:
                FactoryFinder(::CORBA::Object_ptr obj = 0);
                virtual ~FactoryFinder(){ }

            private:
                FactoryFinder( const FactoryFinder&) { }
                void operator=(const FactoryFinder&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class FactoryFinder



        class EXPDLL_LIBOMG FactoryFinder_out
         {
            public:
                FactoryFinder_out (FactoryFinder_ptr & p);
                FactoryFinder_out (FactoryFinder_var & p);
                FactoryFinder_out (const FactoryFinder_out & p) : ptr_(p.ptr_) {}
                FactoryFinder_out & operator=(const FactoryFinder_out & a) {
                    ptr_ = a.ptr_; return *this;}
                FactoryFinder_out & operator=(const FactoryFinder_var & a);
                FactoryFinder_out & operator=(FactoryFinder_ptr p) {
                ptr_ = p; return *this;}
                inline operator FactoryFinder_ptr & () { return ptr_; }
                inline FactoryFinder_ptr & ptr () { return ptr_; }
                inline FactoryFinder_ptr operator->() { return ptr_; }
            private:
                FactoryFinder_ptr & ptr_;
        };  // class FactoryFinder_out



        static const ::CORBA::TypeCode_ptr _tc_LifeCycleObject;
        class EXPDLL_LIBOMG LifeCycleObject : public virtual ::CORBA::Object
         {
            public:
                static LifeCycleObject_ptr _duplicate(LifeCycleObject_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static LifeCycleObject_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static LifeCycleObject_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual LifeCycleObject_ptr copy (
                    FactoryFinder_ptr there,
                     const Criteria & the_criteria); 

                virtual void move (
                    FactoryFinder_ptr there,
                     const Criteria & the_criteria); 

                virtual void remove (); 

            protected:
                LifeCycleObject(::CORBA::Object_ptr obj = 0);
                virtual ~LifeCycleObject(){ }

            private:
                LifeCycleObject( const LifeCycleObject&) { }
                void operator=(const LifeCycleObject&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class LifeCycleObject



        class EXPDLL_LIBOMG LifeCycleObject_out
         {
            public:
                LifeCycleObject_out (LifeCycleObject_ptr & p);
                LifeCycleObject_out (LifeCycleObject_var & p);
                LifeCycleObject_out (const LifeCycleObject_out & p) : ptr_(p.ptr_) {}
                LifeCycleObject_out & operator=(const LifeCycleObject_out & a) {
                    ptr_ = a.ptr_; return *this;}
                LifeCycleObject_out & operator=(const LifeCycleObject_var & a);
                LifeCycleObject_out & operator=(LifeCycleObject_ptr p) {
                ptr_ = p; return *this;}
                inline operator LifeCycleObject_ptr & () { return ptr_; }
                inline LifeCycleObject_ptr & ptr () { return ptr_; }
                inline LifeCycleObject_ptr operator->() { return ptr_; }
            private:
                LifeCycleObject_ptr & ptr_;
        };  // class LifeCycleObject_out



        static const ::CORBA::TypeCode_ptr _tc_GenericFactory;
        class EXPDLL_LIBOMG GenericFactory : public virtual ::CORBA::Object
         {
            public:
                static GenericFactory_ptr _duplicate(GenericFactory_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static GenericFactory_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static GenericFactory_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ::CORBA::Boolean supports (
                     const Key & k); 

                virtual ::CORBA::Object_ptr create_object (
                     const Key & k,
                     const Criteria & the_criteria); 

            protected:
                GenericFactory(::CORBA::Object_ptr obj = 0);
                virtual ~GenericFactory(){ }

            private:
                GenericFactory( const GenericFactory&) { }
                void operator=(const GenericFactory&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class GenericFactory



        class EXPDLL_LIBOMG GenericFactory_out
         {
            public:
                GenericFactory_out (GenericFactory_ptr & p);
                GenericFactory_out (GenericFactory_var & p);
                GenericFactory_out (const GenericFactory_out & p) : ptr_(p.ptr_) {}
                GenericFactory_out & operator=(const GenericFactory_out & a) {
                    ptr_ = a.ptr_; return *this;}
                GenericFactory_out & operator=(const GenericFactory_var & a);
                GenericFactory_out & operator=(GenericFactory_ptr p) {
                ptr_ = p; return *this;}
                inline operator GenericFactory_ptr & () { return ptr_; }
                inline GenericFactory_ptr & ptr () { return ptr_; }
                inline GenericFactory_ptr operator->() { return ptr_; }
            private:
                GenericFactory_ptr & ptr_;
        };  // class GenericFactory_out

    };  // class CosLifeCycle

void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::Factories &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::Factories *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::Factories *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::NVP &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::NVP *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::NVP *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::Criteria &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::Criteria *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::Criteria *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::NoFactory &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::NoFactory *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::NoFactory *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::NotCopyable &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::NotCopyable *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::NotCopyable *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::NotMovable &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::NotMovable *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::NotMovable *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::NotRemovable &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::NotRemovable *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::NotRemovable *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::InvalidCriteria &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::InvalidCriteria *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::InvalidCriteria *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::CannotMeetCriteria &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::CannotMeetCriteria *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::CannotMeetCriteria *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosLifeCycle::NotImplemented &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::NotImplemented *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::NotImplemented *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::FactoryFinder_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::FactoryFinder_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::LifeCycleObject_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::LifeCycleObject_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosLifeCycle::GenericFactory_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosLifeCycle::GenericFactory_ptr &obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::Factories &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::Factories &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::NVP &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::NVP &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::Criteria &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::Criteria &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::NoFactory &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::NoFactory &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::NotCopyable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::NotCopyable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::NotMovable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::NotMovable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::NotRemovable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::NotRemovable &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::InvalidCriteria &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::InvalidCriteria &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::CannotMeetCriteria &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::CannotMeetCriteria &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosLifeCycle::NotImplemented &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosLifeCycle::NotImplemented &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosLifeCycle::FactoryFinder_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosLifeCycle::FactoryFinder_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosLifeCycle::FactoryFinder_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosLifeCycle::LifeCycleObject_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosLifeCycle::LifeCycleObject_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosLifeCycle::LifeCycleObject_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosLifeCycle::GenericFactory_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosLifeCycle::GenericFactory_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosLifeCycle::GenericFactory_var &_obj);
#ifdef ORB_IMPORT_DEFINED_lcs_c
#undef ORB_IMPORT_DEFINED_lcs_c
#undef EXPDLL_LIBOMG
#endif
#endif

