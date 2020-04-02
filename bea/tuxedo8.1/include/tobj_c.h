/*******************************************************************
 * Created Mon Jan 27 07:37:46 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (tobj_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    FactoryFinder
 *    TransactionCurrent
 *    PrincipalAuthenticator
 *
 */


#ifndef _tobj_c_H
#define _tobj_c_H

#include <string.h>
#include <CORBA.h>
#include <orbgen.h>

#if defined(WIN32)
#pragma warning(disable:4250)
#endif


#ifndef EXPDLL_LIBENV
#define ORB_IMPORT_DEFINED_tobj_c
#ifdef WIN32 
#define EXPDLL_LIBENV ORBIMPDLL
#else
#define EXPDLL_LIBENV
#endif
#endif

#include "lcs_c.h"
#include "ots_c.h"
#include "security_c.h"
class EXPDLL_LIBENV Tobj
{
    public:
        class	FactoryFinder;
        typedef	FactoryFinder *	FactoryFinder_ptr;
        class FactoryFinder_out;

        class EXPDLL_LIBENV FactoryFinder_var : public ::CORBA::_var {
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


        class	TransactionCurrent;
        typedef	TransactionCurrent *	TransactionCurrent_ptr;
        class TransactionCurrent_out;

        class EXPDLL_LIBENV TransactionCurrent_var : public ::CORBA::_var {
            public:
                TransactionCurrent_var();
                inline TransactionCurrent_var(TransactionCurrent_ptr p) {ptr_ = p; }
                TransactionCurrent_var(const TransactionCurrent_var &a);
                ~TransactionCurrent_var()
                    { free();}

                TransactionCurrent_var &operator=(TransactionCurrent_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                TransactionCurrent_var &operator=(const TransactionCurrent_var &a);
                inline TransactionCurrent_ptr in () const { return ptr_; }
                inline TransactionCurrent_ptr & inout () { return ptr_; }
                TransactionCurrent_ptr & out ();
                TransactionCurrent_ptr _retn ();

                inline operator TransactionCurrent_ptr&() { return ptr_; }
                inline operator const TransactionCurrent_ptr&() const { return ptr_; }
                inline TransactionCurrent_ptr operator->() const { return ptr_; }

                inline TransactionCurrent_ptr & ptr () { return ptr_; }
            protected:
                TransactionCurrent_ptr ptr_;
                void free();
                void reset(TransactionCurrent_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class TransactionCurrent_var


        class	PrincipalAuthenticator;
        typedef	PrincipalAuthenticator *	PrincipalAuthenticator_ptr;
        class PrincipalAuthenticator_out;

        class EXPDLL_LIBENV PrincipalAuthenticator_var : public ::CORBA::_var {
            public:
                PrincipalAuthenticator_var();
                inline PrincipalAuthenticator_var(PrincipalAuthenticator_ptr p) {ptr_ = p; }
                PrincipalAuthenticator_var(const PrincipalAuthenticator_var &a);
                ~PrincipalAuthenticator_var()
                    { free();}

                PrincipalAuthenticator_var &operator=(PrincipalAuthenticator_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                PrincipalAuthenticator_var &operator=(const PrincipalAuthenticator_var &a);
                inline PrincipalAuthenticator_ptr in () const { return ptr_; }
                inline PrincipalAuthenticator_ptr & inout () { return ptr_; }
                PrincipalAuthenticator_ptr & out ();
                PrincipalAuthenticator_ptr _retn ();

                inline operator PrincipalAuthenticator_ptr&() { return ptr_; }
                inline operator const PrincipalAuthenticator_ptr&() const { return ptr_; }
                inline PrincipalAuthenticator_ptr operator->() const { return ptr_; }

                inline PrincipalAuthenticator_ptr & ptr () { return ptr_; }
            protected:
                PrincipalAuthenticator_ptr ptr_;
                void free();
                void reset(PrincipalAuthenticator_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class PrincipalAuthenticator_var


        static const  char *const  FACTORY_KIND ;
        class EXPDLL_LIBENV CannotProceed : public ::CORBA::UserException
        {
            public:
                static CannotProceed * _narrow(::CORBA::Exception_ptr);
                CannotProceed ();
                CannotProceed (const CannotProceed &);
                ~CannotProceed ();
                CannotProceed & operator=(const CannotProceed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/Tobj/CannotProceed:1.0"; }

        };  // class CannotProceed


        typedef	CannotProceed *	CannotProceed_ptr;
        class EXPDLL_LIBENV CannotProceed_var
        {
            public:
                inline CannotProceed_var() {_ptr = 0;}
                inline CannotProceed_var(CannotProceed *_obj) {_ptr = _obj;}
                CannotProceed_var(const CannotProceed_var &_obj) {_ptr = 0; *this = _obj;}
                ~CannotProceed_var();
                CannotProceed_var &operator=(CannotProceed *);
                CannotProceed_var &operator=(const CannotProceed_var &);
                inline CannotProceed *operator->() {return _ptr;}
                inline const CannotProceed *operator->() const {return _ptr;}
                inline const CannotProceed & in () const { return *_ptr; }
                inline CannotProceed & inout () { return *_ptr; }
                CannotProceed & out ()
                {
                    CannotProceed *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                CannotProceed & _retn ()
                {
                    CannotProceed *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline CannotProceed_ptr & ptr() { return _ptr; }
                inline operator CannotProceed&() { return *_ptr; }
                inline operator const CannotProceed&() const { return *_ptr; }
                inline operator CannotProceed_ptr &() { return _ptr; }
            private:
                CannotProceed *_ptr;
        };  // class CannotProceed_var

        class EXPDLL_LIBENV CannotProceed_out
        {
            public:
                CannotProceed_out (CannotProceed *& p) : ptr_(p) { ptr_ = 0; }
                CannotProceed_out (CannotProceed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                CannotProceed_out (const CannotProceed_out & a) : ptr_(a.ptr_) {}
                CannotProceed_out & operator=(const CannotProceed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                CannotProceed_out & operator=(CannotProceed * p) {
                    ptr_ = p; return *this; }
                inline operator CannotProceed_ptr & () { return ptr_; }
                inline CannotProceed_ptr & ptr () { return ptr_; }
                inline CannotProceed_ptr operator->() { return ptr_; }
            private:
                CannotProceed_ptr & ptr_;
                void operator=(const CannotProceed_var &);

        };  // class CannotProceed_out
        static const ::CORBA::TypeCode_ptr _tc_CannotProceed;
        class EXPDLL_LIBENV InvalidDomain : public ::CORBA::UserException
        {
            public:
                static InvalidDomain * _narrow(::CORBA::Exception_ptr);
                InvalidDomain ();
                InvalidDomain (const InvalidDomain &);
                ~InvalidDomain ();
                InvalidDomain & operator=(const InvalidDomain &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/Tobj/InvalidDomain:1.0"; }

        };  // class InvalidDomain


        typedef	InvalidDomain *	InvalidDomain_ptr;
        class EXPDLL_LIBENV InvalidDomain_var
        {
            public:
                inline InvalidDomain_var() {_ptr = 0;}
                inline InvalidDomain_var(InvalidDomain *_obj) {_ptr = _obj;}
                InvalidDomain_var(const InvalidDomain_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidDomain_var();
                InvalidDomain_var &operator=(InvalidDomain *);
                InvalidDomain_var &operator=(const InvalidDomain_var &);
                inline InvalidDomain *operator->() {return _ptr;}
                inline const InvalidDomain *operator->() const {return _ptr;}
                inline const InvalidDomain & in () const { return *_ptr; }
                inline InvalidDomain & inout () { return *_ptr; }
                InvalidDomain & out ()
                {
                    InvalidDomain *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                InvalidDomain & _retn ()
                {
                    InvalidDomain *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline InvalidDomain_ptr & ptr() { return _ptr; }
                inline operator InvalidDomain&() { return *_ptr; }
                inline operator const InvalidDomain&() const { return *_ptr; }
                inline operator InvalidDomain_ptr &() { return _ptr; }
            private:
                InvalidDomain *_ptr;
        };  // class InvalidDomain_var

        class EXPDLL_LIBENV InvalidDomain_out
        {
            public:
                InvalidDomain_out (InvalidDomain *& p) : ptr_(p) { ptr_ = 0; }
                InvalidDomain_out (InvalidDomain_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidDomain_out (const InvalidDomain_out & a) : ptr_(a.ptr_) {}
                InvalidDomain_out & operator=(const InvalidDomain_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidDomain_out & operator=(InvalidDomain * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidDomain_ptr & () { return ptr_; }
                inline InvalidDomain_ptr & ptr () { return ptr_; }
                inline InvalidDomain_ptr operator->() { return ptr_; }
            private:
                InvalidDomain_ptr & ptr_;
                void operator=(const InvalidDomain_var &);

        };  // class InvalidDomain_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidDomain;
        class EXPDLL_LIBENV InvalidName : public ::CORBA::UserException
        {
            public:
                static InvalidName * _narrow(::CORBA::Exception_ptr);
                InvalidName ();
                InvalidName (const InvalidName &);
                ~InvalidName ();
                InvalidName & operator=(const InvalidName &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/Tobj/InvalidName:1.0"; }

        };  // class InvalidName


        typedef	InvalidName *	InvalidName_ptr;
        class EXPDLL_LIBENV InvalidName_var
        {
            public:
                inline InvalidName_var() {_ptr = 0;}
                inline InvalidName_var(InvalidName *_obj) {_ptr = _obj;}
                InvalidName_var(const InvalidName_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidName_var();
                InvalidName_var &operator=(InvalidName *);
                InvalidName_var &operator=(const InvalidName_var &);
                inline InvalidName *operator->() {return _ptr;}
                inline const InvalidName *operator->() const {return _ptr;}
                inline const InvalidName & in () const { return *_ptr; }
                inline InvalidName & inout () { return *_ptr; }
                InvalidName & out ()
                {
                    InvalidName *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                InvalidName & _retn ()
                {
                    InvalidName *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline InvalidName_ptr & ptr() { return _ptr; }
                inline operator InvalidName&() { return *_ptr; }
                inline operator const InvalidName&() const { return *_ptr; }
                inline operator InvalidName_ptr &() { return _ptr; }
            private:
                InvalidName *_ptr;
        };  // class InvalidName_var

        class EXPDLL_LIBENV InvalidName_out
        {
            public:
                InvalidName_out (InvalidName *& p) : ptr_(p) { ptr_ = 0; }
                InvalidName_out (InvalidName_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidName_out (const InvalidName_out & a) : ptr_(a.ptr_) {}
                InvalidName_out & operator=(const InvalidName_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidName_out & operator=(InvalidName * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidName_ptr & () { return ptr_; }
                inline InvalidName_ptr & ptr () { return ptr_; }
                inline InvalidName_ptr operator->() { return ptr_; }
            private:
                InvalidName_ptr & ptr_;
                void operator=(const InvalidName_var &);

        };  // class InvalidName_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidName;
        class EXPDLL_LIBENV RegistrarNotAvailable : public ::CORBA::UserException
        {
            public:
                static RegistrarNotAvailable * _narrow(::CORBA::Exception_ptr);
                RegistrarNotAvailable ();
                RegistrarNotAvailable (const RegistrarNotAvailable &);
                ~RegistrarNotAvailable ();
                RegistrarNotAvailable & operator=(const RegistrarNotAvailable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/Tobj/RegistrarNotAvailable:1.0"; }

        };  // class RegistrarNotAvailable


        typedef	RegistrarNotAvailable *	RegistrarNotAvailable_ptr;
        class EXPDLL_LIBENV RegistrarNotAvailable_var
        {
            public:
                inline RegistrarNotAvailable_var() {_ptr = 0;}
                inline RegistrarNotAvailable_var(RegistrarNotAvailable *_obj) {_ptr = _obj;}
                RegistrarNotAvailable_var(const RegistrarNotAvailable_var &_obj) {_ptr = 0; *this = _obj;}
                ~RegistrarNotAvailable_var();
                RegistrarNotAvailable_var &operator=(RegistrarNotAvailable *);
                RegistrarNotAvailable_var &operator=(const RegistrarNotAvailable_var &);
                inline RegistrarNotAvailable *operator->() {return _ptr;}
                inline const RegistrarNotAvailable *operator->() const {return _ptr;}
                inline const RegistrarNotAvailable & in () const { return *_ptr; }
                inline RegistrarNotAvailable & inout () { return *_ptr; }
                RegistrarNotAvailable & out ()
                {
                    RegistrarNotAvailable *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                RegistrarNotAvailable & _retn ()
                {
                    RegistrarNotAvailable *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline RegistrarNotAvailable_ptr & ptr() { return _ptr; }
                inline operator RegistrarNotAvailable&() { return *_ptr; }
                inline operator const RegistrarNotAvailable&() const { return *_ptr; }
                inline operator RegistrarNotAvailable_ptr &() { return _ptr; }
            private:
                RegistrarNotAvailable *_ptr;
        };  // class RegistrarNotAvailable_var

        class EXPDLL_LIBENV RegistrarNotAvailable_out
        {
            public:
                RegistrarNotAvailable_out (RegistrarNotAvailable *& p) : ptr_(p) { ptr_ = 0; }
                RegistrarNotAvailable_out (RegistrarNotAvailable_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                RegistrarNotAvailable_out (const RegistrarNotAvailable_out & a) : ptr_(a.ptr_) {}
                RegistrarNotAvailable_out & operator=(const RegistrarNotAvailable_out & a) {
                    ptr_ = a.ptr_; return *this; }
                RegistrarNotAvailable_out & operator=(RegistrarNotAvailable * p) {
                    ptr_ = p; return *this; }
                inline operator RegistrarNotAvailable_ptr & () { return ptr_; }
                inline RegistrarNotAvailable_ptr & ptr () { return ptr_; }
                inline RegistrarNotAvailable_ptr operator->() { return ptr_; }
            private:
                RegistrarNotAvailable_ptr & ptr_;
                void operator=(const RegistrarNotAvailable_var &);

        };  // class RegistrarNotAvailable_out
        static const ::CORBA::TypeCode_ptr _tc_RegistrarNotAvailable;
        class EXPDLL_LIBENV RMfailed : public ::CORBA::UserException
        {
            public:
                static RMfailed * _narrow(::CORBA::Exception_ptr);
                RMfailed ();
                RMfailed (const RMfailed &);
                ~RMfailed ();
                RMfailed & operator=(const RMfailed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/Tobj/RMfailed:1.0"; }

        };  // class RMfailed


        typedef	RMfailed *	RMfailed_ptr;
        class EXPDLL_LIBENV RMfailed_var
        {
            public:
                inline RMfailed_var() {_ptr = 0;}
                inline RMfailed_var(RMfailed *_obj) {_ptr = _obj;}
                RMfailed_var(const RMfailed_var &_obj) {_ptr = 0; *this = _obj;}
                ~RMfailed_var();
                RMfailed_var &operator=(RMfailed *);
                RMfailed_var &operator=(const RMfailed_var &);
                inline RMfailed *operator->() {return _ptr;}
                inline const RMfailed *operator->() const {return _ptr;}
                inline const RMfailed & in () const { return *_ptr; }
                inline RMfailed & inout () { return *_ptr; }
                RMfailed & out ()
                {
                    RMfailed *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                RMfailed & _retn ()
                {
                    RMfailed *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline RMfailed_ptr & ptr() { return _ptr; }
                inline operator RMfailed&() { return *_ptr; }
                inline operator const RMfailed&() const { return *_ptr; }
                inline operator RMfailed_ptr &() { return _ptr; }
            private:
                RMfailed *_ptr;
        };  // class RMfailed_var

        class EXPDLL_LIBENV RMfailed_out
        {
            public:
                RMfailed_out (RMfailed *& p) : ptr_(p) { ptr_ = 0; }
                RMfailed_out (RMfailed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                RMfailed_out (const RMfailed_out & a) : ptr_(a.ptr_) {}
                RMfailed_out & operator=(const RMfailed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                RMfailed_out & operator=(RMfailed * p) {
                    ptr_ = p; return *this; }
                inline operator RMfailed_ptr & () { return ptr_; }
                inline RMfailed_ptr & ptr () { return ptr_; }
                inline RMfailed_ptr operator->() { return ptr_; }
            private:
                RMfailed_ptr & ptr_;
                void operator=(const RMfailed_var &);

        };  // class RMfailed_out
        static const ::CORBA::TypeCode_ptr _tc_RMfailed;


        struct EXPDLL_LIBENV FactoryComponent {


             ::CosLifeCycle::Key factory_key;


             ::CosLifeCycle::Factory_var factory_ior;
            FactoryComponent &operator=(const FactoryComponent &_obj);
        };
        typedef	FactoryComponent *	FactoryComponent_ptr;
        class EXPDLL_LIBENV FactoryComponent_var
        {
            public:
                inline FactoryComponent_var() {_ptr = 0;}
                inline FactoryComponent_var(FactoryComponent *_obj) {_ptr = _obj;}
                FactoryComponent_var(const FactoryComponent_var &_obj) {_ptr = 0; *this = _obj;}
                ~FactoryComponent_var();
                FactoryComponent_var &operator=(FactoryComponent *);
                FactoryComponent_var &operator=(const FactoryComponent_var &);
                inline FactoryComponent *operator->() {return _ptr;}
                inline const FactoryComponent *operator->() const {return _ptr;}
                inline const FactoryComponent & in () const { return *_ptr; }
                inline FactoryComponent & inout () { return *_ptr; }
                FactoryComponent *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                FactoryComponent * _retn ()
                {
                    FactoryComponent *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline FactoryComponent_ptr & ptr() { return _ptr; }
                inline operator FactoryComponent&() { return *_ptr; }
                inline operator const FactoryComponent&() const { return *_ptr; }
                inline operator FactoryComponent_ptr &() { return _ptr; }
            private:
                FactoryComponent *_ptr;
        };  // class FactoryComponent_var

        class EXPDLL_LIBENV FactoryComponent_out
        {
            public:
                FactoryComponent_out (FactoryComponent *& p) : ptr_(p) { ptr_ = 0; }
                FactoryComponent_out (FactoryComponent_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                FactoryComponent_out (const FactoryComponent_out & a) : ptr_(a.ptr_) {}
                FactoryComponent_out & operator=(const FactoryComponent_out & a) {
                    ptr_ = a.ptr_; return *this; }
                FactoryComponent_out & operator=(FactoryComponent * p) {
                    ptr_ = p; return *this; }
                inline operator FactoryComponent_ptr & () { return ptr_; }
                inline FactoryComponent_ptr & ptr () { return ptr_; }
                inline FactoryComponent_ptr operator->() { return ptr_; }
            private:
                FactoryComponent_ptr & ptr_;
                void operator=(const FactoryComponent_var &);

        };  // class FactoryComponent_out
        static const ::CORBA::TypeCode_ptr _tc_FactoryComponent;


        class EXPDLL_LIBENV FactoryListing
        {
            public:
                FactoryListing();

                FactoryListing(::CORBA::ULong _max);

                FactoryListing
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    FactoryComponent *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                FactoryListing(const FactoryListing &_ptr);

                ~FactoryListing();

                FactoryListing &operator=(const FactoryListing& _ptr);

                inline ::CORBA::ULong maximum() const {return _maximum;}

                void length(::CORBA::ULong);
                inline ::CORBA::ULong length() const {return _current;}

                inline FactoryComponent &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                inline const FactoryComponent &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const FactoryComponent &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static FactoryComponent *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(FactoryComponent *_ptr);

                inline FactoryComponent * OBB__GetData() { return _data; }
            private:
                FactoryComponent *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
        };  // class FactoryListing

        typedef	FactoryListing *	FactoryListing_ptr;
        class EXPDLL_LIBENV FactoryListing_var
        {
            public:
                inline FactoryListing_var() {_ptr = 0;}
                inline FactoryListing_var(FactoryListing *_obj) {_ptr = _obj;}
                FactoryListing_var(const FactoryListing_var &_obj) {_ptr = 0; *this = _obj;}
                ~FactoryListing_var();
                FactoryListing_var &operator=(FactoryListing *);
                FactoryListing_var &operator=(const FactoryListing_var &);
                inline FactoryComponent &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline FactoryListing *operator->() {return _ptr;}
                inline const FactoryListing *operator->() const {return _ptr;}
                inline const FactoryListing & in () const { return *_ptr; }
                inline FactoryListing & inout () { return *_ptr; }
                FactoryListing *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                FactoryListing * _retn ()
                {
                    FactoryListing *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline FactoryListing_ptr & ptr() { return _ptr; }
                inline operator FactoryListing&() { return *_ptr; }
                inline operator const FactoryListing&() const { return *_ptr; }
                inline operator FactoryListing_ptr &() { return _ptr; }
            private:
                FactoryListing *_ptr;
        };  // class FactoryListing_var

        class EXPDLL_LIBENV FactoryListing_out
        {
            public:
                FactoryListing_out (FactoryListing *& p) : ptr_(p) { ptr_ = 0; }
                FactoryListing_out (FactoryListing_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                FactoryListing_out (const FactoryListing_out & a) : ptr_(a.ptr_) {}
                FactoryListing_out & operator=(const FactoryListing_out & a) {
                    ptr_ = a.ptr_; return *this; }
                FactoryListing_out & operator=(FactoryListing * p) {
                    ptr_ = p; return *this; }
                inline operator FactoryListing_ptr & () { return ptr_; }
                inline FactoryListing_ptr & ptr () { return ptr_; }
                inline FactoryListing_ptr operator->() { return ptr_; }
                inline FactoryComponent & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                FactoryListing_ptr & ptr_;
                void operator=(const FactoryListing_var &);

        };  // class FactoryListing_out
        static const ::CORBA::TypeCode_ptr _tc_FactoryListing;


        static const ::CORBA::TypeCode_ptr _tc_FactoryFinder;
        class EXPDLL_LIBENV FactoryFinder : public   ::CosLifeCycle::FactoryFinder
         {
            public:
                static FactoryFinder_ptr _duplicate(FactoryFinder_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static FactoryFinder_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static FactoryFinder_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ::CosLifeCycle::Factory_ptr find_one_factory (
                     const ::CosLifeCycle::Key & factory_key); 

                virtual ::CosLifeCycle::Factory_ptr find_one_factory_by_id (
                    const char * factory_id); 

                virtual ::CosLifeCycle::Factories * find_factories_by_id (
                    const char * factory_id); 

                virtual FactoryListing * list_factories (); 

            protected:
                FactoryFinder(::CORBA::Object_ptr obj = 0);
                virtual ~FactoryFinder(){ }

            private:
                FactoryFinder( const FactoryFinder&) { }
                void operator=(const FactoryFinder&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class FactoryFinder



        class EXPDLL_LIBENV FactoryFinder_out
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



        static const ::CORBA::TypeCode_ptr _tc_TransactionCurrent;
        class EXPDLL_LIBENV TransactionCurrent : public   ::CosTransactions::Current
         {
            public:
                static TransactionCurrent_ptr _duplicate(TransactionCurrent_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static TransactionCurrent_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static TransactionCurrent_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual void open_xa_rm (); 

                virtual void close_xa_rm (); 

            protected:
                TransactionCurrent(::CORBA::Object_ptr obj = 0);
                virtual ~TransactionCurrent(){ }

            private:
                TransactionCurrent( const TransactionCurrent&) { }
                void operator=(const TransactionCurrent&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class TransactionCurrent



        class EXPDLL_LIBENV TransactionCurrent_out
         {
            public:
                TransactionCurrent_out (TransactionCurrent_ptr & p);
                TransactionCurrent_out (TransactionCurrent_var & p);
                TransactionCurrent_out (const TransactionCurrent_out & p) : ptr_(p.ptr_) {}
                TransactionCurrent_out & operator=(const TransactionCurrent_out & a) {
                    ptr_ = a.ptr_; return *this;}
                TransactionCurrent_out & operator=(const TransactionCurrent_var & a);
                TransactionCurrent_out & operator=(TransactionCurrent_ptr p) {
                ptr_ = p; return *this;}
                inline operator TransactionCurrent_ptr & () { return ptr_; }
                inline TransactionCurrent_ptr & ptr () { return ptr_; }
                inline TransactionCurrent_ptr operator->() { return ptr_; }
            private:
                TransactionCurrent_ptr & ptr_;
        };  // class TransactionCurrent_out

        static const ::Security::AuthenticationMethod TuxedoSecurity ;
        static const ::Security::AuthenticationMethod CertificateBased ;


        enum AuthType { TOBJ_NOAUTH, TOBJ_SYSAUTH, TOBJ_APPAUTH };
        typedef AuthType & AuthType_out ;
        static const ::CORBA::TypeCode_ptr _tc_AuthType;


        class EXPDLL_LIBENV UserAuthData
        {
            public:
                UserAuthData();

                UserAuthData(::CORBA::ULong _max);

                UserAuthData
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    ::CORBA::Octet *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                UserAuthData(const UserAuthData &_ptr);

                ~UserAuthData();

                UserAuthData &operator=(const UserAuthData& _ptr);

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
        };  // class UserAuthData

        typedef	UserAuthData *	UserAuthData_ptr;
        class EXPDLL_LIBENV UserAuthData_var
        {
            public:
                inline UserAuthData_var() {_ptr = 0;}
                inline UserAuthData_var(UserAuthData *_obj) {_ptr = _obj;}
                UserAuthData_var(const UserAuthData_var &_obj) {_ptr = 0; *this = _obj;}
                ~UserAuthData_var();
                UserAuthData_var &operator=(UserAuthData *);
                UserAuthData_var &operator=(const UserAuthData_var &);
                inline ::CORBA::Octet &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline UserAuthData *operator->() {return _ptr;}
                inline const UserAuthData *operator->() const {return _ptr;}
                inline const UserAuthData & in () const { return *_ptr; }
                inline UserAuthData & inout () { return *_ptr; }
                UserAuthData *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                UserAuthData * _retn ()
                {
                    UserAuthData *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline UserAuthData_ptr & ptr() { return _ptr; }
                inline operator UserAuthData&() { return *_ptr; }
                inline operator const UserAuthData&() const { return *_ptr; }
                inline operator UserAuthData_ptr &() { return _ptr; }
            private:
                UserAuthData *_ptr;
        };  // class UserAuthData_var

        class EXPDLL_LIBENV UserAuthData_out
        {
            public:
                UserAuthData_out (UserAuthData *& p) : ptr_(p) { ptr_ = 0; }
                UserAuthData_out (UserAuthData_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                UserAuthData_out (const UserAuthData_out & a) : ptr_(a.ptr_) {}
                UserAuthData_out & operator=(const UserAuthData_out & a) {
                    ptr_ = a.ptr_; return *this; }
                UserAuthData_out & operator=(UserAuthData * p) {
                    ptr_ = p; return *this; }
                inline operator UserAuthData_ptr & () { return ptr_; }
                inline UserAuthData_ptr & ptr () { return ptr_; }
                inline UserAuthData_ptr operator->() { return ptr_; }
                inline ::CORBA::Octet & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                UserAuthData_ptr & ptr_;
                void operator=(const UserAuthData_var &);

        };  // class UserAuthData_out
        static const ::CORBA::TypeCode_ptr _tc_UserAuthData;


        class EXPDLL_LIBENV LogonData
        {
            public:
                LogonData();

                LogonData(::CORBA::ULong _max);

                LogonData
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    ::CORBA::Octet *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                LogonData(const LogonData &_ptr);

                ~LogonData();

                LogonData &operator=(const LogonData& _ptr);

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
        };  // class LogonData

        typedef	LogonData *	LogonData_ptr;
        class EXPDLL_LIBENV LogonData_var
        {
            public:
                inline LogonData_var() {_ptr = 0;}
                inline LogonData_var(LogonData *_obj) {_ptr = _obj;}
                LogonData_var(const LogonData_var &_obj) {_ptr = 0; *this = _obj;}
                ~LogonData_var();
                LogonData_var &operator=(LogonData *);
                LogonData_var &operator=(const LogonData_var &);
                inline ::CORBA::Octet &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline LogonData *operator->() {return _ptr;}
                inline const LogonData *operator->() const {return _ptr;}
                inline const LogonData & in () const { return *_ptr; }
                inline LogonData & inout () { return *_ptr; }
                LogonData *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                LogonData * _retn ()
                {
                    LogonData *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline LogonData_ptr & ptr() { return _ptr; }
                inline operator LogonData&() { return *_ptr; }
                inline operator const LogonData&() const { return *_ptr; }
                inline operator LogonData_ptr &() { return _ptr; }
            private:
                LogonData *_ptr;
        };  // class LogonData_var

        class EXPDLL_LIBENV LogonData_out
        {
            public:
                LogonData_out (LogonData *& p) : ptr_(p) { ptr_ = 0; }
                LogonData_out (LogonData_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                LogonData_out (const LogonData_out & a) : ptr_(a.ptr_) {}
                LogonData_out & operator=(const LogonData_out & a) {
                    ptr_ = a.ptr_; return *this; }
                LogonData_out & operator=(LogonData * p) {
                    ptr_ = p; return *this; }
                inline operator LogonData_ptr & () { return ptr_; }
                inline LogonData_ptr & ptr () { return ptr_; }
                inline LogonData_ptr operator->() { return ptr_; }
                inline ::CORBA::Octet & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                LogonData_ptr & ptr_;
                void operator=(const LogonData_var &);

        };  // class LogonData_out
        static const ::CORBA::TypeCode_ptr _tc_LogonData;


        static const ::CORBA::TypeCode_ptr _tc_PrincipalAuthenticator;
        class EXPDLL_LIBENV PrincipalAuthenticator : public   ::SecurityLevel2::PrincipalAuthenticator
         {
            public:
                static PrincipalAuthenticator_ptr _duplicate(PrincipalAuthenticator_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static PrincipalAuthenticator_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static PrincipalAuthenticator_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual AuthType get_auth_type (); 

                virtual ::Security::AuthenticationStatus logon (
                    const char * user_name,
                    const char * client_name,
                    const char * system_password,
                    const char * user_password,
                     const UserAuthData & user_data); 

                virtual void logoff (); 

                virtual void build_auth_data (
                    const char * user_name,
                    const char * client_name,
                    const char * system_password,
                    const char * user_password,
                     const UserAuthData & user_data,
                    ::Security::Opaque_out auth_data,
                    ::Security::AttributeList_out privileges); 

            protected:
                PrincipalAuthenticator(::CORBA::Object_ptr obj = 0);
                virtual ~PrincipalAuthenticator(){ }

            private:
                PrincipalAuthenticator( const PrincipalAuthenticator&) { }
                void operator=(const PrincipalAuthenticator&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class PrincipalAuthenticator



        class EXPDLL_LIBENV PrincipalAuthenticator_out
         {
            public:
                PrincipalAuthenticator_out (PrincipalAuthenticator_ptr & p);
                PrincipalAuthenticator_out (PrincipalAuthenticator_var & p);
                PrincipalAuthenticator_out (const PrincipalAuthenticator_out & p) : ptr_(p.ptr_) {}
                PrincipalAuthenticator_out & operator=(const PrincipalAuthenticator_out & a) {
                    ptr_ = a.ptr_; return *this;}
                PrincipalAuthenticator_out & operator=(const PrincipalAuthenticator_var & a);
                PrincipalAuthenticator_out & operator=(PrincipalAuthenticator_ptr p) {
                ptr_ = p; return *this;}
                inline operator PrincipalAuthenticator_ptr & () { return ptr_; }
                inline PrincipalAuthenticator_ptr & ptr () { return ptr_; }
                inline PrincipalAuthenticator_ptr operator->() { return ptr_; }
            private:
                PrincipalAuthenticator_ptr & ptr_;
        };  // class PrincipalAuthenticator_out

    };  // class Tobj

void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::CannotProceed &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::CannotProceed *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::CannotProceed *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::InvalidDomain &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::InvalidDomain *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::InvalidDomain *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::InvalidName &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::InvalidName *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::InvalidName *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::RegistrarNotAvailable &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::RegistrarNotAvailable *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::RegistrarNotAvailable *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::RMfailed &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::RMfailed *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::RMfailed *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::FactoryComponent &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::FactoryComponent *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::FactoryComponent *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::FactoryListing &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::FactoryListing *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::FactoryListing *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::FactoryFinder_ptr obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::FactoryFinder_ptr &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::TransactionCurrent_ptr obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::TransactionCurrent_ptr &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::AuthType obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::AuthType &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::UserAuthData &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::UserAuthData *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::UserAuthData *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::Tobj::LogonData &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::LogonData *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::LogonData *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::Tobj::PrincipalAuthenticator_ptr obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::Tobj::PrincipalAuthenticator_ptr &obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::CannotProceed &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::CannotProceed &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::InvalidDomain &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::InvalidDomain &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::InvalidName &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::InvalidName &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::RegistrarNotAvailable &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::RegistrarNotAvailable &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::RMfailed &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::RMfailed &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::FactoryComponent &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::FactoryComponent &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::FactoryListing &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::FactoryListing &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &mb, Tobj::FactoryFinder_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, Tobj::FactoryFinder_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, Tobj::FactoryFinder_var &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &mb, Tobj::TransactionCurrent_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, Tobj::TransactionCurrent_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, Tobj::TransactionCurrent_var &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::AuthType &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::AuthType &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::UserAuthData &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::UserAuthData &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::Tobj::LogonData &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::Tobj::LogonData &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &mb, Tobj::PrincipalAuthenticator_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, Tobj::PrincipalAuthenticator_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, Tobj::PrincipalAuthenticator_var &_obj);
#ifdef ORB_IMPORT_DEFINED_tobj_c
#undef ORB_IMPORT_DEFINED_tobj_c
#undef EXPDLL_LIBENV
#endif
#endif

