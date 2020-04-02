/*******************************************************************
 * Created Mon Jan 27 07:37:44 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (ns_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    NamingContext
 *    BindingIterator
 *    NamingContextExt
 *
 */


#ifndef _ns_c_H
#define _ns_c_H

#include <string.h>
#include <CORBA.h>
#include <orbgen.h>

#if defined(WIN32)
#pragma warning(disable:4250)
#endif


#ifndef EXPDLL_LIBOMG
#define ORB_IMPORT_DEFINED_ns_c
#ifdef WIN32 
#define EXPDLL_LIBOMG ORBIMPDLL
#else
#define EXPDLL_LIBOMG
#endif
#endif

class EXPDLL_LIBOMG CosNaming
{
    public:
        class	NamingContext;
        typedef	NamingContext *	NamingContext_ptr;
        class NamingContext_out;

        class EXPDLL_LIBOMG NamingContext_var : public ::CORBA::_var {
            public:
                NamingContext_var();
                inline NamingContext_var(NamingContext_ptr p) {ptr_ = p; }
                NamingContext_var(const NamingContext_var &a);
                ~NamingContext_var()
                    { free();}

                NamingContext_var &operator=(NamingContext_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                NamingContext_var &operator=(const NamingContext_var &a);
                inline NamingContext_ptr in () const { return ptr_; }
                inline NamingContext_ptr & inout () { return ptr_; }
                NamingContext_ptr & out ();
                NamingContext_ptr _retn ();

                inline operator NamingContext_ptr&() { return ptr_; }
                inline operator const NamingContext_ptr&() const { return ptr_; }
                inline NamingContext_ptr operator->() const { return ptr_; }

                inline NamingContext_ptr & ptr () { return ptr_; }
            protected:
                NamingContext_ptr ptr_;
                void free();
                void reset(NamingContext_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class NamingContext_var


        class	BindingIterator;
        typedef	BindingIterator *	BindingIterator_ptr;
        class BindingIterator_out;

        class EXPDLL_LIBOMG BindingIterator_var : public ::CORBA::_var {
            public:
                BindingIterator_var();
                inline BindingIterator_var(BindingIterator_ptr p) {ptr_ = p; }
                BindingIterator_var(const BindingIterator_var &a);
                ~BindingIterator_var()
                    { free();}

                BindingIterator_var &operator=(BindingIterator_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                BindingIterator_var &operator=(const BindingIterator_var &a);
                inline BindingIterator_ptr in () const { return ptr_; }
                inline BindingIterator_ptr & inout () { return ptr_; }
                BindingIterator_ptr & out ();
                BindingIterator_ptr _retn ();

                inline operator BindingIterator_ptr&() { return ptr_; }
                inline operator const BindingIterator_ptr&() const { return ptr_; }
                inline BindingIterator_ptr operator->() const { return ptr_; }

                inline BindingIterator_ptr & ptr () { return ptr_; }
            protected:
                BindingIterator_ptr ptr_;
                void free();
                void reset(BindingIterator_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class BindingIterator_var


        class	NamingContextExt;
        typedef	NamingContextExt *	NamingContextExt_ptr;
        class NamingContextExt_out;

        class EXPDLL_LIBOMG NamingContextExt_var : public ::CORBA::_var {
            public:
                NamingContextExt_var();
                inline NamingContextExt_var(NamingContextExt_ptr p) {ptr_ = p; }
                NamingContextExt_var(const NamingContextExt_var &a);
                ~NamingContextExt_var()
                    { free();}

                NamingContextExt_var &operator=(NamingContextExt_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                NamingContextExt_var &operator=(const NamingContextExt_var &a);
                inline NamingContextExt_ptr in () const { return ptr_; }
                inline NamingContextExt_ptr & inout () { return ptr_; }
                NamingContextExt_ptr & out ();
                NamingContextExt_ptr _retn ();

                inline operator NamingContextExt_ptr&() { return ptr_; }
                inline operator const NamingContextExt_ptr&() const { return ptr_; }
                inline NamingContextExt_ptr operator->() const { return ptr_; }

                inline NamingContextExt_ptr & ptr () { return ptr_; }
            protected:
                NamingContextExt_ptr ptr_;
                void free();
                void reset(NamingContextExt_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class NamingContextExt_var


        typedef ::CORBA::Char * Istring;
        typedef ::CORBA::String_out Istring_out;
        typedef ::CORBA::String_var Istring_var;
        static const ::CORBA::TypeCode_ptr _tc_Istring;


        struct EXPDLL_LIBOMG NameComponent {
            ::CORBA::String_var id;
            ::CORBA::String_var kind;
            NameComponent &operator=(const NameComponent &_obj);
        };
        typedef	NameComponent *	NameComponent_ptr;
        class EXPDLL_LIBOMG NameComponent_var
        {
            public:
                inline NameComponent_var() {_ptr = 0;}
                inline NameComponent_var(NameComponent *_obj) {_ptr = _obj;}
                NameComponent_var(const NameComponent_var &_obj) {_ptr = 0; *this = _obj;}
                ~NameComponent_var();
                NameComponent_var &operator=(NameComponent *);
                NameComponent_var &operator=(const NameComponent_var &);
                inline NameComponent *operator->() {return _ptr;}
                inline const NameComponent *operator->() const {return _ptr;}
                inline const NameComponent & in () const { return *_ptr; }
                inline NameComponent & inout () { return *_ptr; }
                NameComponent *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                NameComponent * _retn ()
                {
                    NameComponent *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline NameComponent_ptr & ptr() { return _ptr; }
                inline operator NameComponent&() { return *_ptr; }
                inline operator const NameComponent&() const { return *_ptr; }
                inline operator NameComponent_ptr &() { return _ptr; }
            private:
                NameComponent *_ptr;
        };  // class NameComponent_var

        class EXPDLL_LIBOMG NameComponent_out
        {
            public:
                NameComponent_out (NameComponent *& p) : ptr_(p) { ptr_ = 0; }
                NameComponent_out (NameComponent_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                NameComponent_out (const NameComponent_out & a) : ptr_(a.ptr_) {}
                NameComponent_out & operator=(const NameComponent_out & a) {
                    ptr_ = a.ptr_; return *this; }
                NameComponent_out & operator=(NameComponent * p) {
                    ptr_ = p; return *this; }
                inline operator NameComponent_ptr & () { return ptr_; }
                inline NameComponent_ptr & ptr () { return ptr_; }
                inline NameComponent_ptr operator->() { return ptr_; }
            private:
                NameComponent_ptr & ptr_;
                void operator=(const NameComponent_var &);

        };  // class NameComponent_out
        static const ::CORBA::TypeCode_ptr _tc_NameComponent;


        class EXPDLL_LIBOMG Name
        {
            public:
                Name();

                Name(::CORBA::ULong _max);

                Name
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    NameComponent *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                Name(const Name &_ptr);

                ~Name();

                Name &operator=(const Name& _ptr);

                inline ::CORBA::ULong maximum() const {return _maximum;}

                void length(::CORBA::ULong);
                inline ::CORBA::ULong length() const {return _current;}

                inline NameComponent &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                inline const NameComponent &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const NameComponent &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static NameComponent *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(NameComponent *_ptr);

                inline NameComponent * OBB__GetData() { return _data; }
            private:
                NameComponent *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
        };  // class Name

        typedef	Name *	Name_ptr;
        class EXPDLL_LIBOMG Name_var
        {
            public:
                inline Name_var() {_ptr = 0;}
                inline Name_var(Name *_obj) {_ptr = _obj;}
                Name_var(const Name_var &_obj) {_ptr = 0; *this = _obj;}
                ~Name_var();
                Name_var &operator=(Name *);
                Name_var &operator=(const Name_var &);
                inline NameComponent &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline Name *operator->() {return _ptr;}
                inline const Name *operator->() const {return _ptr;}
                inline const Name & in () const { return *_ptr; }
                inline Name & inout () { return *_ptr; }
                Name *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                Name * _retn ()
                {
                    Name *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline Name_ptr & ptr() { return _ptr; }
                inline operator Name&() { return *_ptr; }
                inline operator const Name&() const { return *_ptr; }
                inline operator Name_ptr &() { return _ptr; }
            private:
                Name *_ptr;
        };  // class Name_var

        class EXPDLL_LIBOMG Name_out
        {
            public:
                Name_out (Name *& p) : ptr_(p) { ptr_ = 0; }
                Name_out (Name_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                Name_out (const Name_out & a) : ptr_(a.ptr_) {}
                Name_out & operator=(const Name_out & a) {
                    ptr_ = a.ptr_; return *this; }
                Name_out & operator=(Name * p) {
                    ptr_ = p; return *this; }
                inline operator Name_ptr & () { return ptr_; }
                inline Name_ptr & ptr () { return ptr_; }
                inline Name_ptr operator->() { return ptr_; }
                inline NameComponent & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                Name_ptr & ptr_;
                void operator=(const Name_var &);

        };  // class Name_out
        static const ::CORBA::TypeCode_ptr _tc_Name;


        enum BindingType { nobject, ncontext };
        typedef BindingType & BindingType_out ;
        static const ::CORBA::TypeCode_ptr _tc_BindingType;


        struct EXPDLL_LIBOMG Binding {


             Name binding_name;


             BindingType binding_type;
            Binding &operator=(const Binding &_obj);
        };
        typedef	Binding *	Binding_ptr;
        class EXPDLL_LIBOMG Binding_var
        {
            public:
                inline Binding_var() {_ptr = 0;}
                inline Binding_var(Binding *_obj) {_ptr = _obj;}
                Binding_var(const Binding_var &_obj) {_ptr = 0; *this = _obj;}
                ~Binding_var();
                Binding_var &operator=(Binding *);
                Binding_var &operator=(const Binding_var &);
                inline Binding *operator->() {return _ptr;}
                inline const Binding *operator->() const {return _ptr;}
                inline const Binding & in () const { return *_ptr; }
                inline Binding & inout () { return *_ptr; }
                Binding *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                Binding * _retn ()
                {
                    Binding *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline Binding_ptr & ptr() { return _ptr; }
                inline operator Binding&() { return *_ptr; }
                inline operator const Binding&() const { return *_ptr; }
                inline operator Binding_ptr &() { return _ptr; }
            private:
                Binding *_ptr;
        };  // class Binding_var

        class EXPDLL_LIBOMG Binding_out
        {
            public:
                Binding_out (Binding *& p) : ptr_(p) { ptr_ = 0; }
                Binding_out (Binding_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                Binding_out (const Binding_out & a) : ptr_(a.ptr_) {}
                Binding_out & operator=(const Binding_out & a) {
                    ptr_ = a.ptr_; return *this; }
                Binding_out & operator=(Binding * p) {
                    ptr_ = p; return *this; }
                inline operator Binding_ptr & () { return ptr_; }
                inline Binding_ptr & ptr () { return ptr_; }
                inline Binding_ptr operator->() { return ptr_; }
            private:
                Binding_ptr & ptr_;
                void operator=(const Binding_var &);

        };  // class Binding_out
        static const ::CORBA::TypeCode_ptr _tc_Binding;


        class EXPDLL_LIBOMG BindingList
        {
            public:
                BindingList();

                BindingList(::CORBA::ULong _max);

                BindingList
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    Binding *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                BindingList(const BindingList &_ptr);

                ~BindingList();

                BindingList &operator=(const BindingList& _ptr);

                inline ::CORBA::ULong maximum() const {return _maximum;}

                void length(::CORBA::ULong);
                inline ::CORBA::ULong length() const {return _current;}

                inline Binding &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                inline const Binding &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const Binding &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static Binding *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(Binding *_ptr);

                inline Binding * OBB__GetData() { return _data; }
            private:
                Binding *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
        };  // class BindingList

        typedef	BindingList *	BindingList_ptr;
        class EXPDLL_LIBOMG BindingList_var
        {
            public:
                inline BindingList_var() {_ptr = 0;}
                inline BindingList_var(BindingList *_obj) {_ptr = _obj;}
                BindingList_var(const BindingList_var &_obj) {_ptr = 0; *this = _obj;}
                ~BindingList_var();
                BindingList_var &operator=(BindingList *);
                BindingList_var &operator=(const BindingList_var &);
                inline Binding &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline BindingList *operator->() {return _ptr;}
                inline const BindingList *operator->() const {return _ptr;}
                inline const BindingList & in () const { return *_ptr; }
                inline BindingList & inout () { return *_ptr; }
                BindingList *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                BindingList * _retn ()
                {
                    BindingList *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline BindingList_ptr & ptr() { return _ptr; }
                inline operator BindingList&() { return *_ptr; }
                inline operator const BindingList&() const { return *_ptr; }
                inline operator BindingList_ptr &() { return _ptr; }
            private:
                BindingList *_ptr;
        };  // class BindingList_var

        class EXPDLL_LIBOMG BindingList_out
        {
            public:
                BindingList_out (BindingList *& p) : ptr_(p) { ptr_ = 0; }
                BindingList_out (BindingList_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                BindingList_out (const BindingList_out & a) : ptr_(a.ptr_) {}
                BindingList_out & operator=(const BindingList_out & a) {
                    ptr_ = a.ptr_; return *this; }
                BindingList_out & operator=(BindingList * p) {
                    ptr_ = p; return *this; }
                inline operator BindingList_ptr & () { return ptr_; }
                inline BindingList_ptr & ptr () { return ptr_; }
                inline BindingList_ptr operator->() { return ptr_; }
                inline Binding & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                BindingList_ptr & ptr_;
                void operator=(const BindingList_var &);

        };  // class BindingList_out
        static const ::CORBA::TypeCode_ptr _tc_BindingList;


        static const ::CORBA::TypeCode_ptr _tc_NamingContext;
        class EXPDLL_LIBOMG NamingContext : public virtual ::CORBA::Object
         {
            public:


                enum NotFoundReason { missing_node, not_context, not_object };
                typedef NotFoundReason & NotFoundReason_out ;
                static const ::CORBA::TypeCode_ptr _tc_NotFoundReason;
                class EXPDLL_LIBOMG NotFound : public ::CORBA::UserException
                {
                    public:
                        static NotFound * _narrow(::CORBA::Exception_ptr);
                        NotFound ( NotFoundReason _x_why,
                             Name _x_rest_of_name);
                        NotFound ();
                        NotFound (const NotFound &);
                        ~NotFound ();
                        NotFound & operator=(const NotFound &);
                        void _raise();
                        static char * _get_repos_id() { return (char *)"IDL:omg.org/CosNaming/NamingContext/NotFound:1.0"; }



                         NotFoundReason why;


                         Name rest_of_name;
                };  // class NotFound


                typedef	NotFound *	NotFound_ptr;
                class EXPDLL_LIBOMG NotFound_var
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
                        NotFound *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        NotFound * _retn ()
                        {
                            NotFound *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline NotFound_ptr & ptr() { return _ptr; }
                        inline operator NotFound&() { return *_ptr; }
                        inline operator const NotFound&() const { return *_ptr; }
                        inline operator NotFound_ptr &() { return _ptr; }
                    private:
                        NotFound *_ptr;
                };  // class NotFound_var

                class EXPDLL_LIBOMG NotFound_out
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
                class EXPDLL_LIBOMG CannotProceed : public ::CORBA::UserException
                {
                    public:
                        static CannotProceed * _narrow(::CORBA::Exception_ptr);
                        CannotProceed ( NamingContext_ptr _x_cxt,
                             Name _x_rest_of_name);
                        CannotProceed ();
                        CannotProceed (const CannotProceed &);
                        ~CannotProceed ();
                        CannotProceed & operator=(const CannotProceed &);
                        void _raise();
                        static char * _get_repos_id() { return (char *)"IDL:omg.org/CosNaming/NamingContext/CannotProceed:1.0"; }



                         NamingContext_var cxt;


                         Name rest_of_name;
                };  // class CannotProceed


                typedef	CannotProceed *	CannotProceed_ptr;
                class EXPDLL_LIBOMG CannotProceed_var
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
                        CannotProceed *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        CannotProceed * _retn ()
                        {
                            CannotProceed *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline CannotProceed_ptr & ptr() { return _ptr; }
                        inline operator CannotProceed&() { return *_ptr; }
                        inline operator const CannotProceed&() const { return *_ptr; }
                        inline operator CannotProceed_ptr &() { return _ptr; }
                    private:
                        CannotProceed *_ptr;
                };  // class CannotProceed_var

                class EXPDLL_LIBOMG CannotProceed_out
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
                class EXPDLL_LIBOMG InvalidName : public ::CORBA::UserException
                {
                    public:
                        static InvalidName * _narrow(::CORBA::Exception_ptr);
                        InvalidName ();
                        InvalidName (const InvalidName &);
                        ~InvalidName ();
                        InvalidName & operator=(const InvalidName &);
                        void _raise();
                        static char * _get_repos_id() { return (char *)"IDL:omg.org/CosNaming/NamingContext/InvalidName:1.0"; }

                };  // class InvalidName


                typedef	InvalidName *	InvalidName_ptr;
                class EXPDLL_LIBOMG InvalidName_var
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

                class EXPDLL_LIBOMG InvalidName_out
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
                class EXPDLL_LIBOMG AlreadyBound : public ::CORBA::UserException
                {
                    public:
                        static AlreadyBound * _narrow(::CORBA::Exception_ptr);
                        AlreadyBound ();
                        AlreadyBound (const AlreadyBound &);
                        ~AlreadyBound ();
                        AlreadyBound & operator=(const AlreadyBound &);
                        void _raise();
                        static char * _get_repos_id() { return (char *)"IDL:omg.org/CosNaming/NamingContext/AlreadyBound:1.0"; }

                };  // class AlreadyBound


                typedef	AlreadyBound *	AlreadyBound_ptr;
                class EXPDLL_LIBOMG AlreadyBound_var
                {
                    public:
                        inline AlreadyBound_var() {_ptr = 0;}
                        inline AlreadyBound_var(AlreadyBound *_obj) {_ptr = _obj;}
                        AlreadyBound_var(const AlreadyBound_var &_obj) {_ptr = 0; *this = _obj;}
                        ~AlreadyBound_var();
                        AlreadyBound_var &operator=(AlreadyBound *);
                        AlreadyBound_var &operator=(const AlreadyBound_var &);
                        inline AlreadyBound *operator->() {return _ptr;}
                        inline const AlreadyBound *operator->() const {return _ptr;}
                        inline const AlreadyBound & in () const { return *_ptr; }
                        inline AlreadyBound & inout () { return *_ptr; }
                        AlreadyBound & out ()
                        {
                            AlreadyBound *tmp = _ptr;
                            _ptr=0;
                            return *tmp;
                        }
                        AlreadyBound & _retn ()
                        {
                            AlreadyBound *tmp = _ptr;
                            _ptr = 0;
                            return *tmp;
                        }
                        inline AlreadyBound_ptr & ptr() { return _ptr; }
                        inline operator AlreadyBound&() { return *_ptr; }
                        inline operator const AlreadyBound&() const { return *_ptr; }
                        inline operator AlreadyBound_ptr &() { return _ptr; }
                    private:
                        AlreadyBound *_ptr;
                };  // class AlreadyBound_var

                class EXPDLL_LIBOMG AlreadyBound_out
                {
                    public:
                        AlreadyBound_out (AlreadyBound *& p) : ptr_(p) { ptr_ = 0; }
                        AlreadyBound_out (AlreadyBound_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        AlreadyBound_out (const AlreadyBound_out & a) : ptr_(a.ptr_) {}
                        AlreadyBound_out & operator=(const AlreadyBound_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        AlreadyBound_out & operator=(AlreadyBound * p) {
                            ptr_ = p; return *this; }
                        inline operator AlreadyBound_ptr & () { return ptr_; }
                        inline AlreadyBound_ptr & ptr () { return ptr_; }
                        inline AlreadyBound_ptr operator->() { return ptr_; }
                    private:
                        AlreadyBound_ptr & ptr_;
                        void operator=(const AlreadyBound_var &);

                };  // class AlreadyBound_out
                static const ::CORBA::TypeCode_ptr _tc_AlreadyBound;
                class EXPDLL_LIBOMG NotEmpty : public ::CORBA::UserException
                {
                    public:
                        static NotEmpty * _narrow(::CORBA::Exception_ptr);
                        NotEmpty ();
                        NotEmpty (const NotEmpty &);
                        ~NotEmpty ();
                        NotEmpty & operator=(const NotEmpty &);
                        void _raise();
                        static char * _get_repos_id() { return (char *)"IDL:omg.org/CosNaming/NamingContext/NotEmpty:1.0"; }

                };  // class NotEmpty


                typedef	NotEmpty *	NotEmpty_ptr;
                class EXPDLL_LIBOMG NotEmpty_var
                {
                    public:
                        inline NotEmpty_var() {_ptr = 0;}
                        inline NotEmpty_var(NotEmpty *_obj) {_ptr = _obj;}
                        NotEmpty_var(const NotEmpty_var &_obj) {_ptr = 0; *this = _obj;}
                        ~NotEmpty_var();
                        NotEmpty_var &operator=(NotEmpty *);
                        NotEmpty_var &operator=(const NotEmpty_var &);
                        inline NotEmpty *operator->() {return _ptr;}
                        inline const NotEmpty *operator->() const {return _ptr;}
                        inline const NotEmpty & in () const { return *_ptr; }
                        inline NotEmpty & inout () { return *_ptr; }
                        NotEmpty & out ()
                        {
                            NotEmpty *tmp = _ptr;
                            _ptr=0;
                            return *tmp;
                        }
                        NotEmpty & _retn ()
                        {
                            NotEmpty *tmp = _ptr;
                            _ptr = 0;
                            return *tmp;
                        }
                        inline NotEmpty_ptr & ptr() { return _ptr; }
                        inline operator NotEmpty&() { return *_ptr; }
                        inline operator const NotEmpty&() const { return *_ptr; }
                        inline operator NotEmpty_ptr &() { return _ptr; }
                    private:
                        NotEmpty *_ptr;
                };  // class NotEmpty_var

                class EXPDLL_LIBOMG NotEmpty_out
                {
                    public:
                        NotEmpty_out (NotEmpty *& p) : ptr_(p) { ptr_ = 0; }
                        NotEmpty_out (NotEmpty_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        NotEmpty_out (const NotEmpty_out & a) : ptr_(a.ptr_) {}
                        NotEmpty_out & operator=(const NotEmpty_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        NotEmpty_out & operator=(NotEmpty * p) {
                            ptr_ = p; return *this; }
                        inline operator NotEmpty_ptr & () { return ptr_; }
                        inline NotEmpty_ptr & ptr () { return ptr_; }
                        inline NotEmpty_ptr operator->() { return ptr_; }
                    private:
                        NotEmpty_ptr & ptr_;
                        void operator=(const NotEmpty_var &);

                };  // class NotEmpty_out
                static const ::CORBA::TypeCode_ptr _tc_NotEmpty;
                static NamingContext_ptr _duplicate(NamingContext_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static NamingContext_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static NamingContext_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual void bind (
                     const Name & n,
                    ::CORBA::Object_ptr obj); 

                virtual void rebind (
                     const Name & n,
                    ::CORBA::Object_ptr obj); 

                virtual void bind_context (
                     const Name & n,
                    NamingContext_ptr nc); 

                virtual void rebind_context (
                     const Name & n,
                    NamingContext_ptr nc); 

                virtual ::CORBA::Object_ptr resolve (
                     const Name & n); 

                virtual void unbind (
                     const Name & n); 

                virtual NamingContext_ptr new_context (); 

                virtual NamingContext_ptr bind_new_context (
                     const Name & n); 

                virtual void destroy (); 

                virtual void list (
                    ::CORBA::ULong how_many,
                    BindingList_out bl,
                    BindingIterator_out bi); 

            protected:
                NamingContext(::CORBA::Object_ptr obj = 0);
                virtual ~NamingContext(){ }

            private:
                NamingContext( const NamingContext&) { }
                void operator=(const NamingContext&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class NamingContext



        class EXPDLL_LIBOMG NamingContext_out
         {
            public:
                NamingContext_out (NamingContext_ptr & p);
                NamingContext_out (NamingContext_var & p);
                NamingContext_out (const NamingContext_out & p) : ptr_(p.ptr_) {}
                NamingContext_out & operator=(const NamingContext_out & a) {
                    ptr_ = a.ptr_; return *this;}
                NamingContext_out & operator=(const NamingContext_var & a);
                NamingContext_out & operator=(NamingContext_ptr p) {
                ptr_ = p; return *this;}
                inline operator NamingContext_ptr & () { return ptr_; }
                inline NamingContext_ptr & ptr () { return ptr_; }
                inline NamingContext_ptr operator->() { return ptr_; }
            private:
                NamingContext_ptr & ptr_;
        };  // class NamingContext_out



        static const ::CORBA::TypeCode_ptr _tc_BindingIterator;
        class EXPDLL_LIBOMG BindingIterator : public virtual ::CORBA::Object
         {
            public:
                static BindingIterator_ptr _duplicate(BindingIterator_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static BindingIterator_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static BindingIterator_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ::CORBA::Boolean next_one (
                    Binding_out b); 

                virtual ::CORBA::Boolean next_n (
                    ::CORBA::ULong how_many,
                    BindingList_out bl); 

                virtual void destroy (); 

            protected:
                BindingIterator(::CORBA::Object_ptr obj = 0);
                virtual ~BindingIterator(){ }

            private:
                BindingIterator( const BindingIterator&) { }
                void operator=(const BindingIterator&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class BindingIterator



        class EXPDLL_LIBOMG BindingIterator_out
         {
            public:
                BindingIterator_out (BindingIterator_ptr & p);
                BindingIterator_out (BindingIterator_var & p);
                BindingIterator_out (const BindingIterator_out & p) : ptr_(p.ptr_) {}
                BindingIterator_out & operator=(const BindingIterator_out & a) {
                    ptr_ = a.ptr_; return *this;}
                BindingIterator_out & operator=(const BindingIterator_var & a);
                BindingIterator_out & operator=(BindingIterator_ptr p) {
                ptr_ = p; return *this;}
                inline operator BindingIterator_ptr & () { return ptr_; }
                inline BindingIterator_ptr & ptr () { return ptr_; }
                inline BindingIterator_ptr operator->() { return ptr_; }
            private:
                BindingIterator_ptr & ptr_;
        };  // class BindingIterator_out



        static const ::CORBA::TypeCode_ptr _tc_NamingContextExt;
        class EXPDLL_LIBOMG NamingContextExt : public   NamingContext
         {
            public:
                typedef ::CORBA::Char * StringName;
                typedef ::CORBA::String_out StringName_out;
                typedef ::CORBA::String_var StringName_var;
                static const ::CORBA::TypeCode_ptr _tc_StringName;
                typedef ::CORBA::Char * Address;
                typedef ::CORBA::String_out Address_out;
                typedef ::CORBA::String_var Address_var;
                static const ::CORBA::TypeCode_ptr _tc_Address;
                typedef ::CORBA::Char * URLString;
                typedef ::CORBA::String_out URLString_out;
                typedef ::CORBA::String_var URLString_var;
                static const ::CORBA::TypeCode_ptr _tc_URLString;
                class EXPDLL_LIBOMG InvalidAddress : public ::CORBA::UserException
                {
                    public:
                        static InvalidAddress * _narrow(::CORBA::Exception_ptr);
                        InvalidAddress ();
                        InvalidAddress (const InvalidAddress &);
                        ~InvalidAddress ();
                        InvalidAddress & operator=(const InvalidAddress &);
                        void _raise();
                        static char * _get_repos_id() { return (char *)"IDL:omg.org/CosNaming/NamingContextExt/InvalidAddress:1.0"; }

                };  // class InvalidAddress


                typedef	InvalidAddress *	InvalidAddress_ptr;
                class EXPDLL_LIBOMG InvalidAddress_var
                {
                    public:
                        inline InvalidAddress_var() {_ptr = 0;}
                        inline InvalidAddress_var(InvalidAddress *_obj) {_ptr = _obj;}
                        InvalidAddress_var(const InvalidAddress_var &_obj) {_ptr = 0; *this = _obj;}
                        ~InvalidAddress_var();
                        InvalidAddress_var &operator=(InvalidAddress *);
                        InvalidAddress_var &operator=(const InvalidAddress_var &);
                        inline InvalidAddress *operator->() {return _ptr;}
                        inline const InvalidAddress *operator->() const {return _ptr;}
                        inline const InvalidAddress & in () const { return *_ptr; }
                        inline InvalidAddress & inout () { return *_ptr; }
                        InvalidAddress & out ()
                        {
                            InvalidAddress *tmp = _ptr;
                            _ptr=0;
                            return *tmp;
                        }
                        InvalidAddress & _retn ()
                        {
                            InvalidAddress *tmp = _ptr;
                            _ptr = 0;
                            return *tmp;
                        }
                        inline InvalidAddress_ptr & ptr() { return _ptr; }
                        inline operator InvalidAddress&() { return *_ptr; }
                        inline operator const InvalidAddress&() const { return *_ptr; }
                        inline operator InvalidAddress_ptr &() { return _ptr; }
                    private:
                        InvalidAddress *_ptr;
                };  // class InvalidAddress_var

                class EXPDLL_LIBOMG InvalidAddress_out
                {
                    public:
                        InvalidAddress_out (InvalidAddress *& p) : ptr_(p) { ptr_ = 0; }
                        InvalidAddress_out (InvalidAddress_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        InvalidAddress_out (const InvalidAddress_out & a) : ptr_(a.ptr_) {}
                        InvalidAddress_out & operator=(const InvalidAddress_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        InvalidAddress_out & operator=(InvalidAddress * p) {
                            ptr_ = p; return *this; }
                        inline operator InvalidAddress_ptr & () { return ptr_; }
                        inline InvalidAddress_ptr & ptr () { return ptr_; }
                        inline InvalidAddress_ptr operator->() { return ptr_; }
                    private:
                        InvalidAddress_ptr & ptr_;
                        void operator=(const InvalidAddress_var &);

                };  // class InvalidAddress_out
                static const ::CORBA::TypeCode_ptr _tc_InvalidAddress;
                static NamingContextExt_ptr _duplicate(NamingContextExt_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static NamingContextExt_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static NamingContextExt_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual StringName to_string (
                     const Name & n); 

                virtual Name * to_name (
                    const char * sn); 

                virtual URLString to_url (
                    const char * addr,
                    const char * sn); 

                virtual ::CORBA::Object_ptr resolve_str (
                    const char * n); 

            protected:
                NamingContextExt(::CORBA::Object_ptr obj = 0);
                virtual ~NamingContextExt(){ }

            private:
                NamingContextExt( const NamingContextExt&) { }
                void operator=(const NamingContextExt&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class NamingContextExt



        class EXPDLL_LIBOMG NamingContextExt_out
         {
            public:
                NamingContextExt_out (NamingContextExt_ptr & p);
                NamingContextExt_out (NamingContextExt_var & p);
                NamingContextExt_out (const NamingContextExt_out & p) : ptr_(p.ptr_) {}
                NamingContextExt_out & operator=(const NamingContextExt_out & a) {
                    ptr_ = a.ptr_; return *this;}
                NamingContextExt_out & operator=(const NamingContextExt_var & a);
                NamingContextExt_out & operator=(NamingContextExt_ptr p) {
                ptr_ = p; return *this;}
                inline operator NamingContextExt_ptr & () { return ptr_; }
                inline NamingContextExt_ptr & ptr () { return ptr_; }
                inline NamingContextExt_ptr operator->() { return ptr_; }
            private:
                NamingContextExt_ptr & ptr_;
        };  // class NamingContextExt_out

    };  // class CosNaming

void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::NameComponent &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NameComponent *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NameComponent *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::Name &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::Name *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::Name *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::BindingType obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::BindingType &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::Binding &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::Binding *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::Binding *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::BindingList &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::BindingList *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::BindingList *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContext_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContext_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContext::NotFoundReason obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContext::NotFoundReason &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::NamingContext::NotFound &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContext::NotFound *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContext::NotFound *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::NamingContext::CannotProceed &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContext::CannotProceed *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContext::CannotProceed *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::NamingContext::InvalidName &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContext::InvalidName *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContext::InvalidName *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::NamingContext::AlreadyBound &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContext::AlreadyBound *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContext::AlreadyBound *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::NamingContext::NotEmpty &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContext::NotEmpty *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContext::NotEmpty *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::BindingIterator_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::BindingIterator_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContextExt_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContextExt_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::CosNaming::NamingContextExt::InvalidAddress &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::CosNaming::NamingContextExt::InvalidAddress *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::CosNaming::NamingContextExt::InvalidAddress *&obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NameComponent &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NameComponent &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::Name &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::Name &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::BindingType &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::BindingType &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::Binding &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::Binding &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::BindingList &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::BindingList &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosNaming::NamingContext_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosNaming::NamingContext_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosNaming::NamingContext_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NamingContext::NotFoundReason &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NamingContext::NotFoundReason &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NamingContext::NotFound &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NamingContext::NotFound &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NamingContext::CannotProceed &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NamingContext::CannotProceed &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NamingContext::InvalidName &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NamingContext::InvalidName &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NamingContext::AlreadyBound &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NamingContext::AlreadyBound &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NamingContext::NotEmpty &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NamingContext::NotEmpty &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosNaming::BindingIterator_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosNaming::BindingIterator_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosNaming::BindingIterator_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, CosNaming::NamingContextExt_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosNaming::NamingContextExt_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, CosNaming::NamingContextExt_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::CosNaming::NamingContextExt::InvalidAddress &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::CosNaming::NamingContextExt::InvalidAddress &);
#ifdef ORB_IMPORT_DEFINED_ns_c
#undef ORB_IMPORT_DEFINED_ns_c
#undef EXPDLL_LIBOMG
#endif
#endif

