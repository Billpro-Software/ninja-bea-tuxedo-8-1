/*******************************************************************
 * Created Mon Jan 27 07:37:48 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (TobjS_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    TobjS
 *
 */


#ifndef _TobjS_c_H
#define _TobjS_c_H

#include <string.h>
#include <CORBA.h>
#include <orbgen.h>

#if defined(WIN32)
#pragma warning(disable:4250)
#endif


#ifndef EXPDLL_LIBNATIVE
#define ORB_IMPORT_DEFINED_TobjS_c
#ifdef WIN32 
#define EXPDLL_LIBNATIVE ORBIMPDLL
#else
#define EXPDLL_LIBNATIVE
#endif
#endif



class	TobjS;
typedef	TobjS *	TobjS_ptr;
class TobjS_out;

class EXPDLL_LIBNATIVE TobjS_var : public ::CORBA::_var {
    public:
        TobjS_var();
        inline TobjS_var(TobjS_ptr p) {ptr_ = p; }
        TobjS_var(const TobjS_var &a);
        ~TobjS_var()
            { free();}

        TobjS_var &operator=(TobjS_ptr p)
            { if (p != ptr_) reset(p);
            return *this; }

        TobjS_var &operator=(const TobjS_var &a);
        inline TobjS_ptr in () const { return ptr_; }
        inline TobjS_ptr & inout () { return ptr_; }
        TobjS_ptr & out ();
        TobjS_ptr _retn ();

        inline operator TobjS_ptr&() { return ptr_; }
        inline operator const TobjS_ptr&() const { return ptr_; }
        inline TobjS_ptr operator->() const { return ptr_; }

        inline TobjS_ptr & ptr () { return ptr_; }
    protected:
        TobjS_ptr ptr_;
        void free();
        void reset(TobjS_ptr p) { free(); ptr_ = p; }

    private:
        void operator=(const ::CORBA::_var &);
};  // class TobjS_var


extern const ::CORBA::TypeCode_ptr _tc_TobjS;
class EXPDLL_LIBNATIVE TobjS : public virtual ::CORBA::Object
 {
    public:


        enum DeactivateReasonValue { DR_METHOD_END, DR_SERVER_SHUTDOWN, DR_TRANS_COMMITTING, DR_TRANS_ABORTED, DR_EXPLICIT_DEACTIVATE };
        typedef DeactivateReasonValue & DeactivateReasonValue_out ;
        static const ::CORBA::TypeCode_ptr _tc_DeactivateReasonValue;
        class EXPDLL_LIBNATIVE AlreadyRegistered : public ::CORBA::UserException
        {
            public:
                static AlreadyRegistered * _narrow(::CORBA::Exception_ptr);
                AlreadyRegistered ();
                AlreadyRegistered (const AlreadyRegistered &);
                ~AlreadyRegistered ();
                AlreadyRegistered & operator=(const AlreadyRegistered &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/AlreadyRegistered:1.0"; }

        };  // class AlreadyRegistered


        typedef	AlreadyRegistered *	AlreadyRegistered_ptr;
        class EXPDLL_LIBNATIVE AlreadyRegistered_var
        {
            public:
                inline AlreadyRegistered_var() {_ptr = 0;}
                inline AlreadyRegistered_var(AlreadyRegistered *_obj) {_ptr = _obj;}
                AlreadyRegistered_var(const AlreadyRegistered_var &_obj) {_ptr = 0; *this = _obj;}
                ~AlreadyRegistered_var();
                AlreadyRegistered_var &operator=(AlreadyRegistered *);
                AlreadyRegistered_var &operator=(const AlreadyRegistered_var &);
                inline AlreadyRegistered *operator->() {return _ptr;}
                inline const AlreadyRegistered *operator->() const {return _ptr;}
                inline const AlreadyRegistered & in () const { return *_ptr; }
                inline AlreadyRegistered & inout () { return *_ptr; }
                AlreadyRegistered & out ()
                {
                    AlreadyRegistered *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                AlreadyRegistered & _retn ()
                {
                    AlreadyRegistered *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline AlreadyRegistered_ptr & ptr() { return _ptr; }
                inline operator AlreadyRegistered&() { return *_ptr; }
                inline operator const AlreadyRegistered&() const { return *_ptr; }
                inline operator AlreadyRegistered_ptr &() { return _ptr; }
            private:
                AlreadyRegistered *_ptr;
        };  // class AlreadyRegistered_var

        class EXPDLL_LIBNATIVE AlreadyRegistered_out
        {
            public:
                AlreadyRegistered_out (AlreadyRegistered *& p) : ptr_(p) { ptr_ = 0; }
                AlreadyRegistered_out (AlreadyRegistered_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                AlreadyRegistered_out (const AlreadyRegistered_out & a) : ptr_(a.ptr_) {}
                AlreadyRegistered_out & operator=(const AlreadyRegistered_out & a) {
                    ptr_ = a.ptr_; return *this; }
                AlreadyRegistered_out & operator=(AlreadyRegistered * p) {
                    ptr_ = p; return *this; }
                inline operator AlreadyRegistered_ptr & () { return ptr_; }
                inline AlreadyRegistered_ptr & ptr () { return ptr_; }
                inline AlreadyRegistered_ptr operator->() { return ptr_; }
            private:
                AlreadyRegistered_ptr & ptr_;
                void operator=(const AlreadyRegistered_var &);

        };  // class AlreadyRegistered_out
        static const ::CORBA::TypeCode_ptr _tc_AlreadyRegistered;
        class EXPDLL_LIBNATIVE ActivateObjectFailed : public ::CORBA::UserException
        {
            public:
                static ActivateObjectFailed * _narrow(::CORBA::Exception_ptr);
                ActivateObjectFailed ( const char * _x_reason);
                ActivateObjectFailed ();
                ActivateObjectFailed (const ActivateObjectFailed &);
                ~ActivateObjectFailed ();
                ActivateObjectFailed & operator=(const ActivateObjectFailed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/ActivateObjectFailed:1.0"; }

                ::CORBA::String_var reason;
        };  // class ActivateObjectFailed


        typedef	ActivateObjectFailed *	ActivateObjectFailed_ptr;
        class EXPDLL_LIBNATIVE ActivateObjectFailed_var
        {
            public:
                inline ActivateObjectFailed_var() {_ptr = 0;}
                inline ActivateObjectFailed_var(ActivateObjectFailed *_obj) {_ptr = _obj;}
                ActivateObjectFailed_var(const ActivateObjectFailed_var &_obj) {_ptr = 0; *this = _obj;}
                ~ActivateObjectFailed_var();
                ActivateObjectFailed_var &operator=(ActivateObjectFailed *);
                ActivateObjectFailed_var &operator=(const ActivateObjectFailed_var &);
                inline ActivateObjectFailed *operator->() {return _ptr;}
                inline const ActivateObjectFailed *operator->() const {return _ptr;}
                inline const ActivateObjectFailed & in () const { return *_ptr; }
                inline ActivateObjectFailed & inout () { return *_ptr; }
                ActivateObjectFailed *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ActivateObjectFailed * _retn ()
                {
                    ActivateObjectFailed *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ActivateObjectFailed_ptr & ptr() { return _ptr; }
                inline operator ActivateObjectFailed&() { return *_ptr; }
                inline operator const ActivateObjectFailed&() const { return *_ptr; }
                inline operator ActivateObjectFailed_ptr &() { return _ptr; }
            private:
                ActivateObjectFailed *_ptr;
        };  // class ActivateObjectFailed_var

        class EXPDLL_LIBNATIVE ActivateObjectFailed_out
        {
            public:
                ActivateObjectFailed_out (ActivateObjectFailed *& p) : ptr_(p) { ptr_ = 0; }
                ActivateObjectFailed_out (ActivateObjectFailed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ActivateObjectFailed_out (const ActivateObjectFailed_out & a) : ptr_(a.ptr_) {}
                ActivateObjectFailed_out & operator=(const ActivateObjectFailed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ActivateObjectFailed_out & operator=(ActivateObjectFailed * p) {
                    ptr_ = p; return *this; }
                inline operator ActivateObjectFailed_ptr & () { return ptr_; }
                inline ActivateObjectFailed_ptr & ptr () { return ptr_; }
                inline ActivateObjectFailed_ptr operator->() { return ptr_; }
            private:
                ActivateObjectFailed_ptr & ptr_;
                void operator=(const ActivateObjectFailed_var &);

        };  // class ActivateObjectFailed_out
        static const ::CORBA::TypeCode_ptr _tc_ActivateObjectFailed;
        class EXPDLL_LIBNATIVE ApplicationProblem : public ::CORBA::UserException
        {
            public:
                static ApplicationProblem * _narrow(::CORBA::Exception_ptr);
                ApplicationProblem ();
                ApplicationProblem (const ApplicationProblem &);
                ~ApplicationProblem ();
                ApplicationProblem & operator=(const ApplicationProblem &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/ApplicationProblem:1.0"; }

        };  // class ApplicationProblem


        typedef	ApplicationProblem *	ApplicationProblem_ptr;
        class EXPDLL_LIBNATIVE ApplicationProblem_var
        {
            public:
                inline ApplicationProblem_var() {_ptr = 0;}
                inline ApplicationProblem_var(ApplicationProblem *_obj) {_ptr = _obj;}
                ApplicationProblem_var(const ApplicationProblem_var &_obj) {_ptr = 0; *this = _obj;}
                ~ApplicationProblem_var();
                ApplicationProblem_var &operator=(ApplicationProblem *);
                ApplicationProblem_var &operator=(const ApplicationProblem_var &);
                inline ApplicationProblem *operator->() {return _ptr;}
                inline const ApplicationProblem *operator->() const {return _ptr;}
                inline const ApplicationProblem & in () const { return *_ptr; }
                inline ApplicationProblem & inout () { return *_ptr; }
                ApplicationProblem & out ()
                {
                    ApplicationProblem *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                ApplicationProblem & _retn ()
                {
                    ApplicationProblem *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline ApplicationProblem_ptr & ptr() { return _ptr; }
                inline operator ApplicationProblem&() { return *_ptr; }
                inline operator const ApplicationProblem&() const { return *_ptr; }
                inline operator ApplicationProblem_ptr &() { return _ptr; }
            private:
                ApplicationProblem *_ptr;
        };  // class ApplicationProblem_var

        class EXPDLL_LIBNATIVE ApplicationProblem_out
        {
            public:
                ApplicationProblem_out (ApplicationProblem *& p) : ptr_(p) { ptr_ = 0; }
                ApplicationProblem_out (ApplicationProblem_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ApplicationProblem_out (const ApplicationProblem_out & a) : ptr_(a.ptr_) {}
                ApplicationProblem_out & operator=(const ApplicationProblem_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ApplicationProblem_out & operator=(ApplicationProblem * p) {
                    ptr_ = p; return *this; }
                inline operator ApplicationProblem_ptr & () { return ptr_; }
                inline ApplicationProblem_ptr & ptr () { return ptr_; }
                inline ApplicationProblem_ptr operator->() { return ptr_; }
            private:
                ApplicationProblem_ptr & ptr_;
                void operator=(const ApplicationProblem_var &);

        };  // class ApplicationProblem_out
        static const ::CORBA::TypeCode_ptr _tc_ApplicationProblem;
        class EXPDLL_LIBNATIVE CannotProceed : public ::CORBA::UserException
        {
            public:
                static CannotProceed * _narrow(::CORBA::Exception_ptr);
                CannotProceed ();
                CannotProceed (const CannotProceed &);
                ~CannotProceed ();
                CannotProceed & operator=(const CannotProceed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/CannotProceed:1.0"; }

        };  // class CannotProceed


        typedef	CannotProceed *	CannotProceed_ptr;
        class EXPDLL_LIBNATIVE CannotProceed_var
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

        class EXPDLL_LIBNATIVE CannotProceed_out
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
        class EXPDLL_LIBNATIVE CreateServantFailed : public ::CORBA::UserException
        {
            public:
                static CreateServantFailed * _narrow(::CORBA::Exception_ptr);
                CreateServantFailed ( const char * _x_reason);
                CreateServantFailed ();
                CreateServantFailed (const CreateServantFailed &);
                ~CreateServantFailed ();
                CreateServantFailed & operator=(const CreateServantFailed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/CreateServantFailed:1.0"; }

                ::CORBA::String_var reason;
        };  // class CreateServantFailed


        typedef	CreateServantFailed *	CreateServantFailed_ptr;
        class EXPDLL_LIBNATIVE CreateServantFailed_var
        {
            public:
                inline CreateServantFailed_var() {_ptr = 0;}
                inline CreateServantFailed_var(CreateServantFailed *_obj) {_ptr = _obj;}
                CreateServantFailed_var(const CreateServantFailed_var &_obj) {_ptr = 0; *this = _obj;}
                ~CreateServantFailed_var();
                CreateServantFailed_var &operator=(CreateServantFailed *);
                CreateServantFailed_var &operator=(const CreateServantFailed_var &);
                inline CreateServantFailed *operator->() {return _ptr;}
                inline const CreateServantFailed *operator->() const {return _ptr;}
                inline const CreateServantFailed & in () const { return *_ptr; }
                inline CreateServantFailed & inout () { return *_ptr; }
                CreateServantFailed *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                CreateServantFailed * _retn ()
                {
                    CreateServantFailed *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline CreateServantFailed_ptr & ptr() { return _ptr; }
                inline operator CreateServantFailed&() { return *_ptr; }
                inline operator const CreateServantFailed&() const { return *_ptr; }
                inline operator CreateServantFailed_ptr &() { return _ptr; }
            private:
                CreateServantFailed *_ptr;
        };  // class CreateServantFailed_var

        class EXPDLL_LIBNATIVE CreateServantFailed_out
        {
            public:
                CreateServantFailed_out (CreateServantFailed *& p) : ptr_(p) { ptr_ = 0; }
                CreateServantFailed_out (CreateServantFailed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                CreateServantFailed_out (const CreateServantFailed_out & a) : ptr_(a.ptr_) {}
                CreateServantFailed_out & operator=(const CreateServantFailed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                CreateServantFailed_out & operator=(CreateServantFailed * p) {
                    ptr_ = p; return *this; }
                inline operator CreateServantFailed_ptr & () { return ptr_; }
                inline CreateServantFailed_ptr & ptr () { return ptr_; }
                inline CreateServantFailed_ptr operator->() { return ptr_; }
            private:
                CreateServantFailed_ptr & ptr_;
                void operator=(const CreateServantFailed_var &);

        };  // class CreateServantFailed_out
        static const ::CORBA::TypeCode_ptr _tc_CreateServantFailed;
        class EXPDLL_LIBNATIVE DeactivateObjectFailed : public ::CORBA::UserException
        {
            public:
                static DeactivateObjectFailed * _narrow(::CORBA::Exception_ptr);
                DeactivateObjectFailed ( const char * _x_reason);
                DeactivateObjectFailed ();
                DeactivateObjectFailed (const DeactivateObjectFailed &);
                ~DeactivateObjectFailed ();
                DeactivateObjectFailed & operator=(const DeactivateObjectFailed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/DeactivateObjectFailed:1.0"; }

                ::CORBA::String_var reason;
        };  // class DeactivateObjectFailed


        typedef	DeactivateObjectFailed *	DeactivateObjectFailed_ptr;
        class EXPDLL_LIBNATIVE DeactivateObjectFailed_var
        {
            public:
                inline DeactivateObjectFailed_var() {_ptr = 0;}
                inline DeactivateObjectFailed_var(DeactivateObjectFailed *_obj) {_ptr = _obj;}
                DeactivateObjectFailed_var(const DeactivateObjectFailed_var &_obj) {_ptr = 0; *this = _obj;}
                ~DeactivateObjectFailed_var();
                DeactivateObjectFailed_var &operator=(DeactivateObjectFailed *);
                DeactivateObjectFailed_var &operator=(const DeactivateObjectFailed_var &);
                inline DeactivateObjectFailed *operator->() {return _ptr;}
                inline const DeactivateObjectFailed *operator->() const {return _ptr;}
                inline const DeactivateObjectFailed & in () const { return *_ptr; }
                inline DeactivateObjectFailed & inout () { return *_ptr; }
                DeactivateObjectFailed *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                DeactivateObjectFailed * _retn ()
                {
                    DeactivateObjectFailed *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline DeactivateObjectFailed_ptr & ptr() { return _ptr; }
                inline operator DeactivateObjectFailed&() { return *_ptr; }
                inline operator const DeactivateObjectFailed&() const { return *_ptr; }
                inline operator DeactivateObjectFailed_ptr &() { return _ptr; }
            private:
                DeactivateObjectFailed *_ptr;
        };  // class DeactivateObjectFailed_var

        class EXPDLL_LIBNATIVE DeactivateObjectFailed_out
        {
            public:
                DeactivateObjectFailed_out (DeactivateObjectFailed *& p) : ptr_(p) { ptr_ = 0; }
                DeactivateObjectFailed_out (DeactivateObjectFailed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                DeactivateObjectFailed_out (const DeactivateObjectFailed_out & a) : ptr_(a.ptr_) {}
                DeactivateObjectFailed_out & operator=(const DeactivateObjectFailed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                DeactivateObjectFailed_out & operator=(DeactivateObjectFailed * p) {
                    ptr_ = p; return *this; }
                inline operator DeactivateObjectFailed_ptr & () { return ptr_; }
                inline DeactivateObjectFailed_ptr & ptr () { return ptr_; }
                inline DeactivateObjectFailed_ptr operator->() { return ptr_; }
            private:
                DeactivateObjectFailed_ptr & ptr_;
                void operator=(const DeactivateObjectFailed_var &);

        };  // class DeactivateObjectFailed_out
        static const ::CORBA::TypeCode_ptr _tc_DeactivateObjectFailed;
        class EXPDLL_LIBNATIVE IllegalInterface : public ::CORBA::UserException
        {
            public:
                static IllegalInterface * _narrow(::CORBA::Exception_ptr);
                IllegalInterface ();
                IllegalInterface (const IllegalInterface &);
                ~IllegalInterface ();
                IllegalInterface & operator=(const IllegalInterface &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/IllegalInterface:1.0"; }

        };  // class IllegalInterface


        typedef	IllegalInterface *	IllegalInterface_ptr;
        class EXPDLL_LIBNATIVE IllegalInterface_var
        {
            public:
                inline IllegalInterface_var() {_ptr = 0;}
                inline IllegalInterface_var(IllegalInterface *_obj) {_ptr = _obj;}
                IllegalInterface_var(const IllegalInterface_var &_obj) {_ptr = 0; *this = _obj;}
                ~IllegalInterface_var();
                IllegalInterface_var &operator=(IllegalInterface *);
                IllegalInterface_var &operator=(const IllegalInterface_var &);
                inline IllegalInterface *operator->() {return _ptr;}
                inline const IllegalInterface *operator->() const {return _ptr;}
                inline const IllegalInterface & in () const { return *_ptr; }
                inline IllegalInterface & inout () { return *_ptr; }
                IllegalInterface & out ()
                {
                    IllegalInterface *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                IllegalInterface & _retn ()
                {
                    IllegalInterface *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline IllegalInterface_ptr & ptr() { return _ptr; }
                inline operator IllegalInterface&() { return *_ptr; }
                inline operator const IllegalInterface&() const { return *_ptr; }
                inline operator IllegalInterface_ptr &() { return _ptr; }
            private:
                IllegalInterface *_ptr;
        };  // class IllegalInterface_var

        class EXPDLL_LIBNATIVE IllegalInterface_out
        {
            public:
                IllegalInterface_out (IllegalInterface *& p) : ptr_(p) { ptr_ = 0; }
                IllegalInterface_out (IllegalInterface_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                IllegalInterface_out (const IllegalInterface_out & a) : ptr_(a.ptr_) {}
                IllegalInterface_out & operator=(const IllegalInterface_out & a) {
                    ptr_ = a.ptr_; return *this; }
                IllegalInterface_out & operator=(IllegalInterface * p) {
                    ptr_ = p; return *this; }
                inline operator IllegalInterface_ptr & () { return ptr_; }
                inline IllegalInterface_ptr & ptr () { return ptr_; }
                inline IllegalInterface_ptr operator->() { return ptr_; }
            private:
                IllegalInterface_ptr & ptr_;
                void operator=(const IllegalInterface_var &);

        };  // class IllegalInterface_out
        static const ::CORBA::TypeCode_ptr _tc_IllegalInterface;
        class EXPDLL_LIBNATIVE IllegalOperation : public ::CORBA::UserException
        {
            public:
                static IllegalOperation * _narrow(::CORBA::Exception_ptr);
                IllegalOperation ();
                IllegalOperation (const IllegalOperation &);
                ~IllegalOperation ();
                IllegalOperation & operator=(const IllegalOperation &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/IllegalOperation:1.0"; }

        };  // class IllegalOperation


        typedef	IllegalOperation *	IllegalOperation_ptr;
        class EXPDLL_LIBNATIVE IllegalOperation_var
        {
            public:
                inline IllegalOperation_var() {_ptr = 0;}
                inline IllegalOperation_var(IllegalOperation *_obj) {_ptr = _obj;}
                IllegalOperation_var(const IllegalOperation_var &_obj) {_ptr = 0; *this = _obj;}
                ~IllegalOperation_var();
                IllegalOperation_var &operator=(IllegalOperation *);
                IllegalOperation_var &operator=(const IllegalOperation_var &);
                inline IllegalOperation *operator->() {return _ptr;}
                inline const IllegalOperation *operator->() const {return _ptr;}
                inline const IllegalOperation & in () const { return *_ptr; }
                inline IllegalOperation & inout () { return *_ptr; }
                IllegalOperation & out ()
                {
                    IllegalOperation *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                IllegalOperation & _retn ()
                {
                    IllegalOperation *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline IllegalOperation_ptr & ptr() { return _ptr; }
                inline operator IllegalOperation&() { return *_ptr; }
                inline operator const IllegalOperation&() const { return *_ptr; }
                inline operator IllegalOperation_ptr &() { return _ptr; }
            private:
                IllegalOperation *_ptr;
        };  // class IllegalOperation_var

        class EXPDLL_LIBNATIVE IllegalOperation_out
        {
            public:
                IllegalOperation_out (IllegalOperation *& p) : ptr_(p) { ptr_ = 0; }
                IllegalOperation_out (IllegalOperation_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                IllegalOperation_out (const IllegalOperation_out & a) : ptr_(a.ptr_) {}
                IllegalOperation_out & operator=(const IllegalOperation_out & a) {
                    ptr_ = a.ptr_; return *this; }
                IllegalOperation_out & operator=(IllegalOperation * p) {
                    ptr_ = p; return *this; }
                inline operator IllegalOperation_ptr & () { return ptr_; }
                inline IllegalOperation_ptr & ptr () { return ptr_; }
                inline IllegalOperation_ptr operator->() { return ptr_; }
            private:
                IllegalOperation_ptr & ptr_;
                void operator=(const IllegalOperation_var &);

        };  // class IllegalOperation_out
        static const ::CORBA::TypeCode_ptr _tc_IllegalOperation;
        class EXPDLL_LIBNATIVE InitializeFailed : public ::CORBA::UserException
        {
            public:
                static InitializeFailed * _narrow(::CORBA::Exception_ptr);
                InitializeFailed ( const char * _x_reason);
                InitializeFailed ();
                InitializeFailed (const InitializeFailed &);
                ~InitializeFailed ();
                InitializeFailed & operator=(const InitializeFailed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/InitializeFailed:1.0"; }

                ::CORBA::String_var reason;
        };  // class InitializeFailed


        typedef	InitializeFailed *	InitializeFailed_ptr;
        class EXPDLL_LIBNATIVE InitializeFailed_var
        {
            public:
                inline InitializeFailed_var() {_ptr = 0;}
                inline InitializeFailed_var(InitializeFailed *_obj) {_ptr = _obj;}
                InitializeFailed_var(const InitializeFailed_var &_obj) {_ptr = 0; *this = _obj;}
                ~InitializeFailed_var();
                InitializeFailed_var &operator=(InitializeFailed *);
                InitializeFailed_var &operator=(const InitializeFailed_var &);
                inline InitializeFailed *operator->() {return _ptr;}
                inline const InitializeFailed *operator->() const {return _ptr;}
                inline const InitializeFailed & in () const { return *_ptr; }
                inline InitializeFailed & inout () { return *_ptr; }
                InitializeFailed *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InitializeFailed * _retn ()
                {
                    InitializeFailed *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InitializeFailed_ptr & ptr() { return _ptr; }
                inline operator InitializeFailed&() { return *_ptr; }
                inline operator const InitializeFailed&() const { return *_ptr; }
                inline operator InitializeFailed_ptr &() { return _ptr; }
            private:
                InitializeFailed *_ptr;
        };  // class InitializeFailed_var

        class EXPDLL_LIBNATIVE InitializeFailed_out
        {
            public:
                InitializeFailed_out (InitializeFailed *& p) : ptr_(p) { ptr_ = 0; }
                InitializeFailed_out (InitializeFailed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InitializeFailed_out (const InitializeFailed_out & a) : ptr_(a.ptr_) {}
                InitializeFailed_out & operator=(const InitializeFailed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InitializeFailed_out & operator=(InitializeFailed * p) {
                    ptr_ = p; return *this; }
                inline operator InitializeFailed_ptr & () { return ptr_; }
                inline InitializeFailed_ptr & ptr () { return ptr_; }
                inline InitializeFailed_ptr operator->() { return ptr_; }
            private:
                InitializeFailed_ptr & ptr_;
                void operator=(const InitializeFailed_var &);

        };  // class InitializeFailed_out
        static const ::CORBA::TypeCode_ptr _tc_InitializeFailed;
        class EXPDLL_LIBNATIVE InvalidDomain : public ::CORBA::UserException
        {
            public:
                static InvalidDomain * _narrow(::CORBA::Exception_ptr);
                InvalidDomain ();
                InvalidDomain (const InvalidDomain &);
                ~InvalidDomain ();
                InvalidDomain & operator=(const InvalidDomain &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/InvalidDomain:1.0"; }

        };  // class InvalidDomain


        typedef	InvalidDomain *	InvalidDomain_ptr;
        class EXPDLL_LIBNATIVE InvalidDomain_var
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

        class EXPDLL_LIBNATIVE InvalidDomain_out
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
        class EXPDLL_LIBNATIVE InvalidInterface : public ::CORBA::UserException
        {
            public:
                static InvalidInterface * _narrow(::CORBA::Exception_ptr);
                InvalidInterface ();
                InvalidInterface (const InvalidInterface &);
                ~InvalidInterface ();
                InvalidInterface & operator=(const InvalidInterface &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/InvalidInterface:1.0"; }

        };  // class InvalidInterface


        typedef	InvalidInterface *	InvalidInterface_ptr;
        class EXPDLL_LIBNATIVE InvalidInterface_var
        {
            public:
                inline InvalidInterface_var() {_ptr = 0;}
                inline InvalidInterface_var(InvalidInterface *_obj) {_ptr = _obj;}
                InvalidInterface_var(const InvalidInterface_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidInterface_var();
                InvalidInterface_var &operator=(InvalidInterface *);
                InvalidInterface_var &operator=(const InvalidInterface_var &);
                inline InvalidInterface *operator->() {return _ptr;}
                inline const InvalidInterface *operator->() const {return _ptr;}
                inline const InvalidInterface & in () const { return *_ptr; }
                inline InvalidInterface & inout () { return *_ptr; }
                InvalidInterface & out ()
                {
                    InvalidInterface *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                InvalidInterface & _retn ()
                {
                    InvalidInterface *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline InvalidInterface_ptr & ptr() { return _ptr; }
                inline operator InvalidInterface&() { return *_ptr; }
                inline operator const InvalidInterface&() const { return *_ptr; }
                inline operator InvalidInterface_ptr &() { return _ptr; }
            private:
                InvalidInterface *_ptr;
        };  // class InvalidInterface_var

        class EXPDLL_LIBNATIVE InvalidInterface_out
        {
            public:
                InvalidInterface_out (InvalidInterface *& p) : ptr_(p) { ptr_ = 0; }
                InvalidInterface_out (InvalidInterface_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidInterface_out (const InvalidInterface_out & a) : ptr_(a.ptr_) {}
                InvalidInterface_out & operator=(const InvalidInterface_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidInterface_out & operator=(InvalidInterface * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidInterface_ptr & () { return ptr_; }
                inline InvalidInterface_ptr & ptr () { return ptr_; }
                inline InvalidInterface_ptr operator->() { return ptr_; }
            private:
                InvalidInterface_ptr & ptr_;
                void operator=(const InvalidInterface_var &);

        };  // class InvalidInterface_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidInterface;
        class EXPDLL_LIBNATIVE InvalidName : public ::CORBA::UserException
        {
            public:
                static InvalidName * _narrow(::CORBA::Exception_ptr);
                InvalidName ();
                InvalidName (const InvalidName &);
                ~InvalidName ();
                InvalidName & operator=(const InvalidName &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/InvalidName:1.0"; }

        };  // class InvalidName


        typedef	InvalidName *	InvalidName_ptr;
        class EXPDLL_LIBNATIVE InvalidName_var
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

        class EXPDLL_LIBNATIVE InvalidName_out
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
        class EXPDLL_LIBNATIVE InvalidObject : public ::CORBA::UserException
        {
            public:
                static InvalidObject * _narrow(::CORBA::Exception_ptr);
                InvalidObject ();
                InvalidObject (const InvalidObject &);
                ~InvalidObject ();
                InvalidObject & operator=(const InvalidObject &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/InvalidObject:1.0"; }

        };  // class InvalidObject


        typedef	InvalidObject *	InvalidObject_ptr;
        class EXPDLL_LIBNATIVE InvalidObject_var
        {
            public:
                inline InvalidObject_var() {_ptr = 0;}
                inline InvalidObject_var(InvalidObject *_obj) {_ptr = _obj;}
                InvalidObject_var(const InvalidObject_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidObject_var();
                InvalidObject_var &operator=(InvalidObject *);
                InvalidObject_var &operator=(const InvalidObject_var &);
                inline InvalidObject *operator->() {return _ptr;}
                inline const InvalidObject *operator->() const {return _ptr;}
                inline const InvalidObject & in () const { return *_ptr; }
                inline InvalidObject & inout () { return *_ptr; }
                InvalidObject & out ()
                {
                    InvalidObject *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                InvalidObject & _retn ()
                {
                    InvalidObject *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline InvalidObject_ptr & ptr() { return _ptr; }
                inline operator InvalidObject&() { return *_ptr; }
                inline operator const InvalidObject&() const { return *_ptr; }
                inline operator InvalidObject_ptr &() { return _ptr; }
            private:
                InvalidObject *_ptr;
        };  // class InvalidObject_var

        class EXPDLL_LIBNATIVE InvalidObject_out
        {
            public:
                InvalidObject_out (InvalidObject *& p) : ptr_(p) { ptr_ = 0; }
                InvalidObject_out (InvalidObject_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidObject_out (const InvalidObject_out & a) : ptr_(a.ptr_) {}
                InvalidObject_out & operator=(const InvalidObject_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidObject_out & operator=(InvalidObject * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidObject_ptr & () { return ptr_; }
                inline InvalidObject_ptr & ptr () { return ptr_; }
                inline InvalidObject_ptr operator->() { return ptr_; }
            private:
                InvalidObject_ptr & ptr_;
                void operator=(const InvalidObject_var &);

        };  // class InvalidObject_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidObject;
        class EXPDLL_LIBNATIVE InvalidObjectId : public ::CORBA::UserException
        {
            public:
                static InvalidObjectId * _narrow(::CORBA::Exception_ptr);
                InvalidObjectId ();
                InvalidObjectId (const InvalidObjectId &);
                ~InvalidObjectId ();
                InvalidObjectId & operator=(const InvalidObjectId &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/InvalidObjectId:1.0"; }

        };  // class InvalidObjectId


        typedef	InvalidObjectId *	InvalidObjectId_ptr;
        class EXPDLL_LIBNATIVE InvalidObjectId_var
        {
            public:
                inline InvalidObjectId_var() {_ptr = 0;}
                inline InvalidObjectId_var(InvalidObjectId *_obj) {_ptr = _obj;}
                InvalidObjectId_var(const InvalidObjectId_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidObjectId_var();
                InvalidObjectId_var &operator=(InvalidObjectId *);
                InvalidObjectId_var &operator=(const InvalidObjectId_var &);
                inline InvalidObjectId *operator->() {return _ptr;}
                inline const InvalidObjectId *operator->() const {return _ptr;}
                inline const InvalidObjectId & in () const { return *_ptr; }
                inline InvalidObjectId & inout () { return *_ptr; }
                InvalidObjectId & out ()
                {
                    InvalidObjectId *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                InvalidObjectId & _retn ()
                {
                    InvalidObjectId *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline InvalidObjectId_ptr & ptr() { return _ptr; }
                inline operator InvalidObjectId&() { return *_ptr; }
                inline operator const InvalidObjectId&() const { return *_ptr; }
                inline operator InvalidObjectId_ptr &() { return _ptr; }
            private:
                InvalidObjectId *_ptr;
        };  // class InvalidObjectId_var

        class EXPDLL_LIBNATIVE InvalidObjectId_out
        {
            public:
                InvalidObjectId_out (InvalidObjectId *& p) : ptr_(p) { ptr_ = 0; }
                InvalidObjectId_out (InvalidObjectId_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidObjectId_out (const InvalidObjectId_out & a) : ptr_(a.ptr_) {}
                InvalidObjectId_out & operator=(const InvalidObjectId_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidObjectId_out & operator=(InvalidObjectId * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidObjectId_ptr & () { return ptr_; }
                inline InvalidObjectId_ptr & ptr () { return ptr_; }
                inline InvalidObjectId_ptr operator->() { return ptr_; }
            private:
                InvalidObjectId_ptr & ptr_;
                void operator=(const InvalidObjectId_var &);

        };  // class InvalidObjectId_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidObjectId;
        class EXPDLL_LIBNATIVE InvalidServant : public ::CORBA::UserException
        {
            public:
                static InvalidServant * _narrow(::CORBA::Exception_ptr);
                InvalidServant ();
                InvalidServant (const InvalidServant &);
                ~InvalidServant ();
                InvalidServant & operator=(const InvalidServant &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/InvalidServant:1.0"; }

        };  // class InvalidServant


        typedef	InvalidServant *	InvalidServant_ptr;
        class EXPDLL_LIBNATIVE InvalidServant_var
        {
            public:
                inline InvalidServant_var() {_ptr = 0;}
                inline InvalidServant_var(InvalidServant *_obj) {_ptr = _obj;}
                InvalidServant_var(const InvalidServant_var &_obj) {_ptr = 0; *this = _obj;}
                ~InvalidServant_var();
                InvalidServant_var &operator=(InvalidServant *);
                InvalidServant_var &operator=(const InvalidServant_var &);
                inline InvalidServant *operator->() {return _ptr;}
                inline const InvalidServant *operator->() const {return _ptr;}
                inline const InvalidServant & in () const { return *_ptr; }
                inline InvalidServant & inout () { return *_ptr; }
                InvalidServant & out ()
                {
                    InvalidServant *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                InvalidServant & _retn ()
                {
                    InvalidServant *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline InvalidServant_ptr & ptr() { return _ptr; }
                inline operator InvalidServant&() { return *_ptr; }
                inline operator const InvalidServant&() const { return *_ptr; }
                inline operator InvalidServant_ptr &() { return _ptr; }
            private:
                InvalidServant *_ptr;
        };  // class InvalidServant_var

        class EXPDLL_LIBNATIVE InvalidServant_out
        {
            public:
                InvalidServant_out (InvalidServant *& p) : ptr_(p) { ptr_ = 0; }
                InvalidServant_out (InvalidServant_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InvalidServant_out (const InvalidServant_out & a) : ptr_(a.ptr_) {}
                InvalidServant_out & operator=(const InvalidServant_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InvalidServant_out & operator=(InvalidServant * p) {
                    ptr_ = p; return *this; }
                inline operator InvalidServant_ptr & () { return ptr_; }
                inline InvalidServant_ptr & ptr () { return ptr_; }
                inline InvalidServant_ptr operator->() { return ptr_; }
            private:
                InvalidServant_ptr & ptr_;
                void operator=(const InvalidServant_var &);

        };  // class InvalidServant_out
        static const ::CORBA::TypeCode_ptr _tc_InvalidServant;
        class EXPDLL_LIBNATIVE NilObject : public ::CORBA::UserException
        {
            public:
                static NilObject * _narrow(::CORBA::Exception_ptr);
                NilObject ( const char * _x_reason);
                NilObject ();
                NilObject (const NilObject &);
                ~NilObject ();
                NilObject & operator=(const NilObject &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/NilObject:1.0"; }

                ::CORBA::String_var reason;
        };  // class NilObject


        typedef	NilObject *	NilObject_ptr;
        class EXPDLL_LIBNATIVE NilObject_var
        {
            public:
                inline NilObject_var() {_ptr = 0;}
                inline NilObject_var(NilObject *_obj) {_ptr = _obj;}
                NilObject_var(const NilObject_var &_obj) {_ptr = 0; *this = _obj;}
                ~NilObject_var();
                NilObject_var &operator=(NilObject *);
                NilObject_var &operator=(const NilObject_var &);
                inline NilObject *operator->() {return _ptr;}
                inline const NilObject *operator->() const {return _ptr;}
                inline const NilObject & in () const { return *_ptr; }
                inline NilObject & inout () { return *_ptr; }
                NilObject *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                NilObject * _retn ()
                {
                    NilObject *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline NilObject_ptr & ptr() { return _ptr; }
                inline operator NilObject&() { return *_ptr; }
                inline operator const NilObject&() const { return *_ptr; }
                inline operator NilObject_ptr &() { return _ptr; }
            private:
                NilObject *_ptr;
        };  // class NilObject_var

        class EXPDLL_LIBNATIVE NilObject_out
        {
            public:
                NilObject_out (NilObject *& p) : ptr_(p) { ptr_ = 0; }
                NilObject_out (NilObject_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NilObject_out (const NilObject_out & a) : ptr_(a.ptr_) {}
                NilObject_out & operator=(const NilObject_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NilObject_out & operator=(NilObject * p) {
                    ptr_ = p; return *this; }
                inline operator NilObject_ptr & () { return ptr_; }
                inline NilObject_ptr & ptr () { return ptr_; }
                inline NilObject_ptr operator->() { return ptr_; }
            private:
                NilObject_ptr & ptr_;
                void operator=(const NilObject_var &);

        };  // class NilObject_out
        static const ::CORBA::TypeCode_ptr _tc_NilObject;
        class EXPDLL_LIBNATIVE NoSuchElement : public ::CORBA::UserException
        {
            public:
                static NoSuchElement * _narrow(::CORBA::Exception_ptr);
                NoSuchElement ();
                NoSuchElement (const NoSuchElement &);
                ~NoSuchElement ();
                NoSuchElement & operator=(const NoSuchElement &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/NoSuchElement:1.0"; }

        };  // class NoSuchElement


        typedef	NoSuchElement *	NoSuchElement_ptr;
        class EXPDLL_LIBNATIVE NoSuchElement_var
        {
            public:
                inline NoSuchElement_var() {_ptr = 0;}
                inline NoSuchElement_var(NoSuchElement *_obj) {_ptr = _obj;}
                NoSuchElement_var(const NoSuchElement_var &_obj) {_ptr = 0; *this = _obj;}
                ~NoSuchElement_var();
                NoSuchElement_var &operator=(NoSuchElement *);
                NoSuchElement_var &operator=(const NoSuchElement_var &);
                inline NoSuchElement *operator->() {return _ptr;}
                inline const NoSuchElement *operator->() const {return _ptr;}
                inline const NoSuchElement & in () const { return *_ptr; }
                inline NoSuchElement & inout () { return *_ptr; }
                NoSuchElement & out ()
                {
                    NoSuchElement *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                NoSuchElement & _retn ()
                {
                    NoSuchElement *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline NoSuchElement_ptr & ptr() { return _ptr; }
                inline operator NoSuchElement&() { return *_ptr; }
                inline operator const NoSuchElement&() const { return *_ptr; }
                inline operator NoSuchElement_ptr &() { return _ptr; }
            private:
                NoSuchElement *_ptr;
        };  // class NoSuchElement_var

        class EXPDLL_LIBNATIVE NoSuchElement_out
        {
            public:
                NoSuchElement_out (NoSuchElement *& p) : ptr_(p) { ptr_ = 0; }
                NoSuchElement_out (NoSuchElement_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NoSuchElement_out (const NoSuchElement_out & a) : ptr_(a.ptr_) {}
                NoSuchElement_out & operator=(const NoSuchElement_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NoSuchElement_out & operator=(NoSuchElement * p) {
                    ptr_ = p; return *this; }
                inline operator NoSuchElement_ptr & () { return ptr_; }
                inline NoSuchElement_ptr & ptr () { return ptr_; }
                inline NoSuchElement_ptr operator->() { return ptr_; }
            private:
                NoSuchElement_ptr & ptr_;
                void operator=(const NoSuchElement_var &);

        };  // class NoSuchElement_out
        static const ::CORBA::TypeCode_ptr _tc_NoSuchElement;
        class EXPDLL_LIBNATIVE NotFound : public ::CORBA::UserException
        {
            public:
                static NotFound * _narrow(::CORBA::Exception_ptr);
                NotFound ();
                NotFound (const NotFound &);
                ~NotFound ();
                NotFound & operator=(const NotFound &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/NotFound:1.0"; }

        };  // class NotFound


        typedef	NotFound *	NotFound_ptr;
        class EXPDLL_LIBNATIVE NotFound_var
        {
            public:
                inline NotFound_var() {_ptr = 0;}
                inline NotFound_var(NotFound *_obj) {_ptr = _obj;}
                NotFound_var(const NotFound_var &_obj) {_ptr = 0; *this = _obj;}
                ~NotFound_var();
                NotFound_var &operator=(NotFound *);
                NotFound_var &operator=(const NotFound_var &);
                inline NotFound *operator->() {return _ptr;}
                inline const NotFound *operator->() const {return _ptr;}
                inline const NotFound & in () const { return *_ptr; }
                inline NotFound & inout () { return *_ptr; }
                NotFound & out ()
                {
                    NotFound *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                NotFound & _retn ()
                {
                    NotFound *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline NotFound_ptr & ptr() { return _ptr; }
                inline operator NotFound&() { return *_ptr; }
                inline operator const NotFound&() const { return *_ptr; }
                inline operator NotFound_ptr &() { return _ptr; }
            private:
                NotFound *_ptr;
        };  // class NotFound_var

        class EXPDLL_LIBNATIVE NotFound_out
        {
            public:
                NotFound_out (NotFound *& p) : ptr_(p) { ptr_ = 0; }
                NotFound_out (NotFound_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NotFound_out (const NotFound_out & a) : ptr_(a.ptr_) {}
                NotFound_out & operator=(const NotFound_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NotFound_out & operator=(NotFound * p) {
                    ptr_ = p; return *this; }
                inline operator NotFound_ptr & () { return ptr_; }
                inline NotFound_ptr & ptr () { return ptr_; }
                inline NotFound_ptr operator->() { return ptr_; }
            private:
                NotFound_ptr & ptr_;
                void operator=(const NotFound_var &);

        };  // class NotFound_out
        static const ::CORBA::TypeCode_ptr _tc_NotFound;
        class EXPDLL_LIBNATIVE ObjectAlreadyActive : public ::CORBA::UserException
        {
            public:
                static ObjectAlreadyActive * _narrow(::CORBA::Exception_ptr);
                ObjectAlreadyActive ();
                ObjectAlreadyActive (const ObjectAlreadyActive &);
                ~ObjectAlreadyActive ();
                ObjectAlreadyActive & operator=(const ObjectAlreadyActive &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/ObjectAlreadyActive:1.0"; }

        };  // class ObjectAlreadyActive


        typedef	ObjectAlreadyActive *	ObjectAlreadyActive_ptr;
        class EXPDLL_LIBNATIVE ObjectAlreadyActive_var
        {
            public:
                inline ObjectAlreadyActive_var() {_ptr = 0;}
                inline ObjectAlreadyActive_var(ObjectAlreadyActive *_obj) {_ptr = _obj;}
                ObjectAlreadyActive_var(const ObjectAlreadyActive_var &_obj) {_ptr = 0; *this = _obj;}
                ~ObjectAlreadyActive_var();
                ObjectAlreadyActive_var &operator=(ObjectAlreadyActive *);
                ObjectAlreadyActive_var &operator=(const ObjectAlreadyActive_var &);
                inline ObjectAlreadyActive *operator->() {return _ptr;}
                inline const ObjectAlreadyActive *operator->() const {return _ptr;}
                inline const ObjectAlreadyActive & in () const { return *_ptr; }
                inline ObjectAlreadyActive & inout () { return *_ptr; }
                ObjectAlreadyActive & out ()
                {
                    ObjectAlreadyActive *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                ObjectAlreadyActive & _retn ()
                {
                    ObjectAlreadyActive *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline ObjectAlreadyActive_ptr & ptr() { return _ptr; }
                inline operator ObjectAlreadyActive&() { return *_ptr; }
                inline operator const ObjectAlreadyActive&() const { return *_ptr; }
                inline operator ObjectAlreadyActive_ptr &() { return _ptr; }
            private:
                ObjectAlreadyActive *_ptr;
        };  // class ObjectAlreadyActive_var

        class EXPDLL_LIBNATIVE ObjectAlreadyActive_out
        {
            public:
                ObjectAlreadyActive_out (ObjectAlreadyActive *& p) : ptr_(p) { ptr_ = 0; }
                ObjectAlreadyActive_out (ObjectAlreadyActive_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ObjectAlreadyActive_out (const ObjectAlreadyActive_out & a) : ptr_(a.ptr_) {}
                ObjectAlreadyActive_out & operator=(const ObjectAlreadyActive_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ObjectAlreadyActive_out & operator=(ObjectAlreadyActive * p) {
                    ptr_ = p; return *this; }
                inline operator ObjectAlreadyActive_ptr & () { return ptr_; }
                inline ObjectAlreadyActive_ptr & ptr () { return ptr_; }
                inline ObjectAlreadyActive_ptr operator->() { return ptr_; }
            private:
                ObjectAlreadyActive_ptr & ptr_;
                void operator=(const ObjectAlreadyActive_var &);

        };  // class ObjectAlreadyActive_out
        static const ::CORBA::TypeCode_ptr _tc_ObjectAlreadyActive;
        class EXPDLL_LIBNATIVE ObjectNotActive : public ::CORBA::UserException
        {
            public:
                static ObjectNotActive * _narrow(::CORBA::Exception_ptr);
                ObjectNotActive ();
                ObjectNotActive (const ObjectNotActive &);
                ~ObjectNotActive ();
                ObjectNotActive & operator=(const ObjectNotActive &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/ObjectNotActive:1.0"; }

        };  // class ObjectNotActive


        typedef	ObjectNotActive *	ObjectNotActive_ptr;
        class EXPDLL_LIBNATIVE ObjectNotActive_var
        {
            public:
                inline ObjectNotActive_var() {_ptr = 0;}
                inline ObjectNotActive_var(ObjectNotActive *_obj) {_ptr = _obj;}
                ObjectNotActive_var(const ObjectNotActive_var &_obj) {_ptr = 0; *this = _obj;}
                ~ObjectNotActive_var();
                ObjectNotActive_var &operator=(ObjectNotActive *);
                ObjectNotActive_var &operator=(const ObjectNotActive_var &);
                inline ObjectNotActive *operator->() {return _ptr;}
                inline const ObjectNotActive *operator->() const {return _ptr;}
                inline const ObjectNotActive & in () const { return *_ptr; }
                inline ObjectNotActive & inout () { return *_ptr; }
                ObjectNotActive & out ()
                {
                    ObjectNotActive *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                ObjectNotActive & _retn ()
                {
                    ObjectNotActive *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline ObjectNotActive_ptr & ptr() { return _ptr; }
                inline operator ObjectNotActive&() { return *_ptr; }
                inline operator const ObjectNotActive&() const { return *_ptr; }
                inline operator ObjectNotActive_ptr &() { return _ptr; }
            private:
                ObjectNotActive *_ptr;
        };  // class ObjectNotActive_var

        class EXPDLL_LIBNATIVE ObjectNotActive_out
        {
            public:
                ObjectNotActive_out (ObjectNotActive *& p) : ptr_(p) { ptr_ = 0; }
                ObjectNotActive_out (ObjectNotActive_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ObjectNotActive_out (const ObjectNotActive_out & a) : ptr_(a.ptr_) {}
                ObjectNotActive_out & operator=(const ObjectNotActive_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ObjectNotActive_out & operator=(ObjectNotActive * p) {
                    ptr_ = p; return *this; }
                inline operator ObjectNotActive_ptr & () { return ptr_; }
                inline ObjectNotActive_ptr & ptr () { return ptr_; }
                inline ObjectNotActive_ptr operator->() { return ptr_; }
            private:
                ObjectNotActive_ptr & ptr_;
                void operator=(const ObjectNotActive_var &);

        };  // class ObjectNotActive_out
        static const ::CORBA::TypeCode_ptr _tc_ObjectNotActive;
        class EXPDLL_LIBNATIVE OrbProblem : public ::CORBA::UserException
        {
            public:
                static OrbProblem * _narrow(::CORBA::Exception_ptr);
                OrbProblem ();
                OrbProblem (const OrbProblem &);
                ~OrbProblem ();
                OrbProblem & operator=(const OrbProblem &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/OrbProblem:1.0"; }

        };  // class OrbProblem


        typedef	OrbProblem *	OrbProblem_ptr;
        class EXPDLL_LIBNATIVE OrbProblem_var
        {
            public:
                inline OrbProblem_var() {_ptr = 0;}
                inline OrbProblem_var(OrbProblem *_obj) {_ptr = _obj;}
                OrbProblem_var(const OrbProblem_var &_obj) {_ptr = 0; *this = _obj;}
                ~OrbProblem_var();
                OrbProblem_var &operator=(OrbProblem *);
                OrbProblem_var &operator=(const OrbProblem_var &);
                inline OrbProblem *operator->() {return _ptr;}
                inline const OrbProblem *operator->() const {return _ptr;}
                inline const OrbProblem & in () const { return *_ptr; }
                inline OrbProblem & inout () { return *_ptr; }
                OrbProblem & out ()
                {
                    OrbProblem *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                OrbProblem & _retn ()
                {
                    OrbProblem *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline OrbProblem_ptr & ptr() { return _ptr; }
                inline operator OrbProblem&() { return *_ptr; }
                inline operator const OrbProblem&() const { return *_ptr; }
                inline operator OrbProblem_ptr &() { return _ptr; }
            private:
                OrbProblem *_ptr;
        };  // class OrbProblem_var

        class EXPDLL_LIBNATIVE OrbProblem_out
        {
            public:
                OrbProblem_out (OrbProblem *& p) : ptr_(p) { ptr_ = 0; }
                OrbProblem_out (OrbProblem_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                OrbProblem_out (const OrbProblem_out & a) : ptr_(a.ptr_) {}
                OrbProblem_out & operator=(const OrbProblem_out & a) {
                    ptr_ = a.ptr_; return *this; }
                OrbProblem_out & operator=(OrbProblem * p) {
                    ptr_ = p; return *this; }
                inline operator OrbProblem_ptr & () { return ptr_; }
                inline OrbProblem_ptr & ptr () { return ptr_; }
                inline OrbProblem_ptr operator->() { return ptr_; }
            private:
                OrbProblem_ptr & ptr_;
                void operator=(const OrbProblem_var &);

        };  // class OrbProblem_out
        static const ::CORBA::TypeCode_ptr _tc_OrbProblem;
        class EXPDLL_LIBNATIVE OutOfMemory : public ::CORBA::UserException
        {
            public:
                static OutOfMemory * _narrow(::CORBA::Exception_ptr);
                OutOfMemory ();
                OutOfMemory (const OutOfMemory &);
                ~OutOfMemory ();
                OutOfMemory & operator=(const OutOfMemory &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/OutOfMemory:1.0"; }

        };  // class OutOfMemory


        typedef	OutOfMemory *	OutOfMemory_ptr;
        class EXPDLL_LIBNATIVE OutOfMemory_var
        {
            public:
                inline OutOfMemory_var() {_ptr = 0;}
                inline OutOfMemory_var(OutOfMemory *_obj) {_ptr = _obj;}
                OutOfMemory_var(const OutOfMemory_var &_obj) {_ptr = 0; *this = _obj;}
                ~OutOfMemory_var();
                OutOfMemory_var &operator=(OutOfMemory *);
                OutOfMemory_var &operator=(const OutOfMemory_var &);
                inline OutOfMemory *operator->() {return _ptr;}
                inline const OutOfMemory *operator->() const {return _ptr;}
                inline const OutOfMemory & in () const { return *_ptr; }
                inline OutOfMemory & inout () { return *_ptr; }
                OutOfMemory & out ()
                {
                    OutOfMemory *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                OutOfMemory & _retn ()
                {
                    OutOfMemory *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline OutOfMemory_ptr & ptr() { return _ptr; }
                inline operator OutOfMemory&() { return *_ptr; }
                inline operator const OutOfMemory&() const { return *_ptr; }
                inline operator OutOfMemory_ptr &() { return _ptr; }
            private:
                OutOfMemory *_ptr;
        };  // class OutOfMemory_var

        class EXPDLL_LIBNATIVE OutOfMemory_out
        {
            public:
                OutOfMemory_out (OutOfMemory *& p) : ptr_(p) { ptr_ = 0; }
                OutOfMemory_out (OutOfMemory_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                OutOfMemory_out (const OutOfMemory_out & a) : ptr_(a.ptr_) {}
                OutOfMemory_out & operator=(const OutOfMemory_out & a) {
                    ptr_ = a.ptr_; return *this; }
                OutOfMemory_out & operator=(OutOfMemory * p) {
                    ptr_ = p; return *this; }
                inline operator OutOfMemory_ptr & () { return ptr_; }
                inline OutOfMemory_ptr & ptr () { return ptr_; }
                inline OutOfMemory_ptr operator->() { return ptr_; }
            private:
                OutOfMemory_ptr & ptr_;
                void operator=(const OutOfMemory_var &);

        };  // class OutOfMemory_out
        static const ::CORBA::TypeCode_ptr _tc_OutOfMemory;
        class EXPDLL_LIBNATIVE OverFlow : public ::CORBA::UserException
        {
            public:
                static OverFlow * _narrow(::CORBA::Exception_ptr);
                OverFlow ();
                OverFlow (const OverFlow &);
                ~OverFlow ();
                OverFlow & operator=(const OverFlow &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/OverFlow:1.0"; }

        };  // class OverFlow


        typedef	OverFlow *	OverFlow_ptr;
        class EXPDLL_LIBNATIVE OverFlow_var
        {
            public:
                inline OverFlow_var() {_ptr = 0;}
                inline OverFlow_var(OverFlow *_obj) {_ptr = _obj;}
                OverFlow_var(const OverFlow_var &_obj) {_ptr = 0; *this = _obj;}
                ~OverFlow_var();
                OverFlow_var &operator=(OverFlow *);
                OverFlow_var &operator=(const OverFlow_var &);
                inline OverFlow *operator->() {return _ptr;}
                inline const OverFlow *operator->() const {return _ptr;}
                inline const OverFlow & in () const { return *_ptr; }
                inline OverFlow & inout () { return *_ptr; }
                OverFlow & out ()
                {
                    OverFlow *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                OverFlow & _retn ()
                {
                    OverFlow *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline OverFlow_ptr & ptr() { return _ptr; }
                inline operator OverFlow&() { return *_ptr; }
                inline operator const OverFlow&() const { return *_ptr; }
                inline operator OverFlow_ptr &() { return _ptr; }
            private:
                OverFlow *_ptr;
        };  // class OverFlow_var

        class EXPDLL_LIBNATIVE OverFlow_out
        {
            public:
                OverFlow_out (OverFlow *& p) : ptr_(p) { ptr_ = 0; }
                OverFlow_out (OverFlow_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                OverFlow_out (const OverFlow_out & a) : ptr_(a.ptr_) {}
                OverFlow_out & operator=(const OverFlow_out & a) {
                    ptr_ = a.ptr_; return *this; }
                OverFlow_out & operator=(OverFlow * p) {
                    ptr_ = p; return *this; }
                inline operator OverFlow_ptr & () { return ptr_; }
                inline OverFlow_ptr & ptr () { return ptr_; }
                inline OverFlow_ptr operator->() { return ptr_; }
            private:
                OverFlow_ptr & ptr_;
                void operator=(const OverFlow_var &);

        };  // class OverFlow_out
        static const ::CORBA::TypeCode_ptr _tc_OverFlow;
        class EXPDLL_LIBNATIVE RegistrarNotAvailable : public ::CORBA::UserException
        {
            public:
                static RegistrarNotAvailable * _narrow(::CORBA::Exception_ptr);
                RegistrarNotAvailable ();
                RegistrarNotAvailable (const RegistrarNotAvailable &);
                ~RegistrarNotAvailable ();
                RegistrarNotAvailable & operator=(const RegistrarNotAvailable &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/RegistrarNotAvailable:1.0"; }

        };  // class RegistrarNotAvailable


        typedef	RegistrarNotAvailable *	RegistrarNotAvailable_ptr;
        class EXPDLL_LIBNATIVE RegistrarNotAvailable_var
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

        class EXPDLL_LIBNATIVE RegistrarNotAvailable_out
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
        class EXPDLL_LIBNATIVE ReleaseFailed : public ::CORBA::UserException
        {
            public:
                static ReleaseFailed * _narrow(::CORBA::Exception_ptr);
                ReleaseFailed ( const char * _x_reason);
                ReleaseFailed ();
                ReleaseFailed (const ReleaseFailed &);
                ~ReleaseFailed ();
                ReleaseFailed & operator=(const ReleaseFailed &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/ReleaseFailed:1.0"; }

                ::CORBA::String_var reason;
        };  // class ReleaseFailed


        typedef	ReleaseFailed *	ReleaseFailed_ptr;
        class EXPDLL_LIBNATIVE ReleaseFailed_var
        {
            public:
                inline ReleaseFailed_var() {_ptr = 0;}
                inline ReleaseFailed_var(ReleaseFailed *_obj) {_ptr = _obj;}
                ReleaseFailed_var(const ReleaseFailed_var &_obj) {_ptr = 0; *this = _obj;}
                ~ReleaseFailed_var();
                ReleaseFailed_var &operator=(ReleaseFailed *);
                ReleaseFailed_var &operator=(const ReleaseFailed_var &);
                inline ReleaseFailed *operator->() {return _ptr;}
                inline const ReleaseFailed *operator->() const {return _ptr;}
                inline const ReleaseFailed & in () const { return *_ptr; }
                inline ReleaseFailed & inout () { return *_ptr; }
                ReleaseFailed *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ReleaseFailed * _retn ()
                {
                    ReleaseFailed *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ReleaseFailed_ptr & ptr() { return _ptr; }
                inline operator ReleaseFailed&() { return *_ptr; }
                inline operator const ReleaseFailed&() const { return *_ptr; }
                inline operator ReleaseFailed_ptr &() { return _ptr; }
            private:
                ReleaseFailed *_ptr;
        };  // class ReleaseFailed_var

        class EXPDLL_LIBNATIVE ReleaseFailed_out
        {
            public:
                ReleaseFailed_out (ReleaseFailed *& p) : ptr_(p) { ptr_ = 0; }
                ReleaseFailed_out (ReleaseFailed_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ReleaseFailed_out (const ReleaseFailed_out & a) : ptr_(a.ptr_) {}
                ReleaseFailed_out & operator=(const ReleaseFailed_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ReleaseFailed_out & operator=(ReleaseFailed * p) {
                    ptr_ = p; return *this; }
                inline operator ReleaseFailed_ptr & () { return ptr_; }
                inline ReleaseFailed_ptr & ptr () { return ptr_; }
                inline ReleaseFailed_ptr operator->() { return ptr_; }
            private:
                ReleaseFailed_ptr & ptr_;
                void operator=(const ReleaseFailed_var &);

        };  // class ReleaseFailed_out
        static const ::CORBA::TypeCode_ptr _tc_ReleaseFailed;
        class EXPDLL_LIBNATIVE ServantAlreadyActive : public ::CORBA::UserException
        {
            public:
                static ServantAlreadyActive * _narrow(::CORBA::Exception_ptr);
                ServantAlreadyActive ();
                ServantAlreadyActive (const ServantAlreadyActive &);
                ~ServantAlreadyActive ();
                ServantAlreadyActive & operator=(const ServantAlreadyActive &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/ServantAlreadyActive:1.0"; }

        };  // class ServantAlreadyActive


        typedef	ServantAlreadyActive *	ServantAlreadyActive_ptr;
        class EXPDLL_LIBNATIVE ServantAlreadyActive_var
        {
            public:
                inline ServantAlreadyActive_var() {_ptr = 0;}
                inline ServantAlreadyActive_var(ServantAlreadyActive *_obj) {_ptr = _obj;}
                ServantAlreadyActive_var(const ServantAlreadyActive_var &_obj) {_ptr = 0; *this = _obj;}
                ~ServantAlreadyActive_var();
                ServantAlreadyActive_var &operator=(ServantAlreadyActive *);
                ServantAlreadyActive_var &operator=(const ServantAlreadyActive_var &);
                inline ServantAlreadyActive *operator->() {return _ptr;}
                inline const ServantAlreadyActive *operator->() const {return _ptr;}
                inline const ServantAlreadyActive & in () const { return *_ptr; }
                inline ServantAlreadyActive & inout () { return *_ptr; }
                ServantAlreadyActive & out ()
                {
                    ServantAlreadyActive *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                ServantAlreadyActive & _retn ()
                {
                    ServantAlreadyActive *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline ServantAlreadyActive_ptr & ptr() { return _ptr; }
                inline operator ServantAlreadyActive&() { return *_ptr; }
                inline operator const ServantAlreadyActive&() const { return *_ptr; }
                inline operator ServantAlreadyActive_ptr &() { return _ptr; }
            private:
                ServantAlreadyActive *_ptr;
        };  // class ServantAlreadyActive_var

        class EXPDLL_LIBNATIVE ServantAlreadyActive_out
        {
            public:
                ServantAlreadyActive_out (ServantAlreadyActive *& p) : ptr_(p) { ptr_ = 0; }
                ServantAlreadyActive_out (ServantAlreadyActive_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ServantAlreadyActive_out (const ServantAlreadyActive_out & a) : ptr_(a.ptr_) {}
                ServantAlreadyActive_out & operator=(const ServantAlreadyActive_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ServantAlreadyActive_out & operator=(ServantAlreadyActive * p) {
                    ptr_ = p; return *this; }
                inline operator ServantAlreadyActive_ptr & () { return ptr_; }
                inline ServantAlreadyActive_ptr & ptr () { return ptr_; }
                inline ServantAlreadyActive_ptr operator->() { return ptr_; }
            private:
                ServantAlreadyActive_ptr & ptr_;
                void operator=(const ServantAlreadyActive_var &);

        };  // class ServantAlreadyActive_out
        static const ::CORBA::TypeCode_ptr _tc_ServantAlreadyActive;
        class EXPDLL_LIBNATIVE TpfProblem : public ::CORBA::UserException
        {
            public:
                static TpfProblem * _narrow(::CORBA::Exception_ptr);
                TpfProblem ();
                TpfProblem (const TpfProblem &);
                ~TpfProblem ();
                TpfProblem & operator=(const TpfProblem &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/TpfProblem:1.0"; }

        };  // class TpfProblem


        typedef	TpfProblem *	TpfProblem_ptr;
        class EXPDLL_LIBNATIVE TpfProblem_var
        {
            public:
                inline TpfProblem_var() {_ptr = 0;}
                inline TpfProblem_var(TpfProblem *_obj) {_ptr = _obj;}
                TpfProblem_var(const TpfProblem_var &_obj) {_ptr = 0; *this = _obj;}
                ~TpfProblem_var();
                TpfProblem_var &operator=(TpfProblem *);
                TpfProblem_var &operator=(const TpfProblem_var &);
                inline TpfProblem *operator->() {return _ptr;}
                inline const TpfProblem *operator->() const {return _ptr;}
                inline const TpfProblem & in () const { return *_ptr; }
                inline TpfProblem & inout () { return *_ptr; }
                TpfProblem & out ()
                {
                    TpfProblem *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                TpfProblem & _retn ()
                {
                    TpfProblem *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline TpfProblem_ptr & ptr() { return _ptr; }
                inline operator TpfProblem&() { return *_ptr; }
                inline operator const TpfProblem&() const { return *_ptr; }
                inline operator TpfProblem_ptr &() { return _ptr; }
            private:
                TpfProblem *_ptr;
        };  // class TpfProblem_var

        class EXPDLL_LIBNATIVE TpfProblem_out
        {
            public:
                TpfProblem_out (TpfProblem *& p) : ptr_(p) { ptr_ = 0; }
                TpfProblem_out (TpfProblem_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                TpfProblem_out (const TpfProblem_out & a) : ptr_(a.ptr_) {}
                TpfProblem_out & operator=(const TpfProblem_out & a) {
                    ptr_ = a.ptr_; return *this; }
                TpfProblem_out & operator=(TpfProblem * p) {
                    ptr_ = p; return *this; }
                inline operator TpfProblem_ptr & () { return ptr_; }
                inline TpfProblem_ptr & ptr () { return ptr_; }
                inline TpfProblem_ptr operator->() { return ptr_; }
            private:
                TpfProblem_ptr & ptr_;
                void operator=(const TpfProblem_var &);

        };  // class TpfProblem_out
        static const ::CORBA::TypeCode_ptr _tc_TpfProblem;
        class EXPDLL_LIBNATIVE UnknownInterface : public ::CORBA::UserException
        {
            public:
                static UnknownInterface * _narrow(::CORBA::Exception_ptr);
                UnknownInterface ();
                UnknownInterface (const UnknownInterface &);
                ~UnknownInterface ();
                UnknownInterface & operator=(const UnknownInterface &);
                void _raise();
                static char * _get_repos_id() { return (char *)"IDL:beasys.com/TobjS/UnknownInterface:1.0"; }

        };  // class UnknownInterface


        typedef	UnknownInterface *	UnknownInterface_ptr;
        class EXPDLL_LIBNATIVE UnknownInterface_var
        {
            public:
                inline UnknownInterface_var() {_ptr = 0;}
                inline UnknownInterface_var(UnknownInterface *_obj) {_ptr = _obj;}
                UnknownInterface_var(const UnknownInterface_var &_obj) {_ptr = 0; *this = _obj;}
                ~UnknownInterface_var();
                UnknownInterface_var &operator=(UnknownInterface *);
                UnknownInterface_var &operator=(const UnknownInterface_var &);
                inline UnknownInterface *operator->() {return _ptr;}
                inline const UnknownInterface *operator->() const {return _ptr;}
                inline const UnknownInterface & in () const { return *_ptr; }
                inline UnknownInterface & inout () { return *_ptr; }
                UnknownInterface & out ()
                {
                    UnknownInterface *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                UnknownInterface & _retn ()
                {
                    UnknownInterface *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline UnknownInterface_ptr & ptr() { return _ptr; }
                inline operator UnknownInterface&() { return *_ptr; }
                inline operator const UnknownInterface&() const { return *_ptr; }
                inline operator UnknownInterface_ptr &() { return _ptr; }
            private:
                UnknownInterface *_ptr;
        };  // class UnknownInterface_var

        class EXPDLL_LIBNATIVE UnknownInterface_out
        {
            public:
                UnknownInterface_out (UnknownInterface *& p) : ptr_(p) { ptr_ = 0; }
                UnknownInterface_out (UnknownInterface_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                UnknownInterface_out (const UnknownInterface_out & a) : ptr_(a.ptr_) {}
                UnknownInterface_out & operator=(const UnknownInterface_out & a) {
                    ptr_ = a.ptr_; return *this; }
                UnknownInterface_out & operator=(UnknownInterface * p) {
                    ptr_ = p; return *this; }
                inline operator UnknownInterface_ptr & () { return ptr_; }
                inline UnknownInterface_ptr & ptr () { return ptr_; }
                inline UnknownInterface_ptr operator->() { return ptr_; }
            private:
                UnknownInterface_ptr & ptr_;
                void operator=(const UnknownInterface_var &);

        };  // class UnknownInterface_out
        static const ::CORBA::TypeCode_ptr _tc_UnknownInterface;
        static TobjS_ptr _duplicate(TobjS_ptr obj) 
            {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
            return obj;}
        static TobjS_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
        inline static TobjS_ptr _nil() { return 0; }
        static const char* _get_interface_name ();

    protected:
        TobjS(::CORBA::Object_ptr obj = 0);
        virtual ~TobjS(){ }

    private:
        TobjS( const TobjS&) { }
        void operator=(const TobjS&) { }
        ::CORBA::ORB_ptr pORB;
};  // class TobjS



class EXPDLL_LIBNATIVE TobjS_out
 {
    public:
        TobjS_out (TobjS_ptr & p);
        TobjS_out (TobjS_var & p);
        TobjS_out (const TobjS_out & p) : ptr_(p.ptr_) {}
        TobjS_out & operator=(const TobjS_out & a) {
            ptr_ = a.ptr_; return *this;}
        TobjS_out & operator=(const TobjS_var & a);
        TobjS_out & operator=(TobjS_ptr p) {
        ptr_ = p; return *this;}
        inline operator TobjS_ptr & () { return ptr_; }
        inline TobjS_ptr & ptr () { return ptr_; }
        inline TobjS_ptr operator->() { return ptr_; }
    private:
        TobjS_ptr & ptr_;
};  // class TobjS_out

void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS_ptr obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS_ptr &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::DeactivateReasonValue obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::DeactivateReasonValue &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::AlreadyRegistered &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::AlreadyRegistered *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::AlreadyRegistered *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::ActivateObjectFailed &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::ActivateObjectFailed *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::ActivateObjectFailed *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::ApplicationProblem &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::ApplicationProblem *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::ApplicationProblem *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::CannotProceed &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::CannotProceed *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::CannotProceed *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::CreateServantFailed &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::CreateServantFailed *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::CreateServantFailed *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::DeactivateObjectFailed &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::DeactivateObjectFailed *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::DeactivateObjectFailed *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::IllegalInterface &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::IllegalInterface *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::IllegalInterface *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::IllegalOperation &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::IllegalOperation *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::IllegalOperation *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::InitializeFailed &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::InitializeFailed *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::InitializeFailed *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::InvalidDomain &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::InvalidDomain *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::InvalidDomain *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::InvalidInterface &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::InvalidInterface *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::InvalidInterface *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::InvalidName &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::InvalidName *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::InvalidName *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::InvalidObject &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::InvalidObject *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::InvalidObject *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::InvalidObjectId &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::InvalidObjectId *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::InvalidObjectId *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::InvalidServant &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::InvalidServant *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::InvalidServant *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::NilObject &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::NilObject *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::NilObject *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::NoSuchElement &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::NoSuchElement *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::NoSuchElement *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::NotFound &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::NotFound *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::NotFound *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::ObjectAlreadyActive &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::ObjectAlreadyActive *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::ObjectAlreadyActive *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::ObjectNotActive &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::ObjectNotActive *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::ObjectNotActive *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::OrbProblem &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::OrbProblem *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::OrbProblem *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::OutOfMemory &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::OutOfMemory *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::OutOfMemory *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::OverFlow &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::OverFlow *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::OverFlow *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::RegistrarNotAvailable &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::RegistrarNotAvailable *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::RegistrarNotAvailable *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::ReleaseFailed &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::ReleaseFailed *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::ReleaseFailed *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::ServantAlreadyActive &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::ServantAlreadyActive *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::ServantAlreadyActive *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::TpfProblem &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::TpfProblem *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::TpfProblem *&obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, const ::TobjS::UnknownInterface &obj);
void EXPDLL_LIBNATIVE operator<<=(::CORBA::Any &a, ::TobjS::UnknownInterface *obj);
::CORBA::Boolean EXPDLL_LIBNATIVE operator>>=(const ::CORBA::Any &a, ::TobjS::UnknownInterface *&obj);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &mb, TobjS_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &mb, TobjS_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &mb, TobjS_var &_obj);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::DeactivateReasonValue &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::DeactivateReasonValue &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::AlreadyRegistered &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::AlreadyRegistered &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::ActivateObjectFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::ActivateObjectFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::ApplicationProblem &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::ApplicationProblem &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::CannotProceed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::CannotProceed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::CreateServantFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::CreateServantFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::DeactivateObjectFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::DeactivateObjectFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::IllegalInterface &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::IllegalInterface &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::IllegalOperation &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::IllegalOperation &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::InitializeFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::InitializeFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::InvalidDomain &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::InvalidDomain &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::InvalidInterface &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::InvalidInterface &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::InvalidName &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::InvalidName &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::InvalidObject &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::InvalidObject &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::InvalidObjectId &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::InvalidObjectId &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::InvalidServant &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::InvalidServant &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::NilObject &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::NilObject &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::NoSuchElement &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::NoSuchElement &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::NotFound &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::NotFound &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::ObjectAlreadyActive &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::ObjectAlreadyActive &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::ObjectNotActive &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::ObjectNotActive &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::OrbProblem &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::OrbProblem &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::OutOfMemory &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::OutOfMemory &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::OverFlow &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::OverFlow &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::RegistrarNotAvailable &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::RegistrarNotAvailable &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::ReleaseFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::ReleaseFailed &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::ServantAlreadyActive &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::ServantAlreadyActive &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::TpfProblem &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::TpfProblem &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator<<(OBB::MarshalBuf &, ::TobjS::UnknownInterface &);
OBB::MarshalBuf EXPDLL_LIBNATIVE &operator>>(OBB::MarshalBuf &, ::TobjS::UnknownInterface &);
#ifdef ORB_IMPORT_DEFINED_TobjS_c
#undef ORB_IMPORT_DEFINED_TobjS_c
#undef EXPDLL_LIBNATIVE
#endif
#endif

