/*******************************************************************
 * Created Mon Jan 27 07:37:46 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (security_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    Current
 *    PrincipalAuthenticator
 *    Credentials
 *    Current
 *
 */


#ifndef _security_c_H
#define _security_c_H

#include <string.h>
#include <CORBA.h>
#include <orbgen.h>

#if defined(WIN32)
#pragma warning(disable:4250)
#endif


#ifndef EXPDLL_LIBOMG
#define ORB_IMPORT_DEFINED_security_c
#ifdef WIN32 
#define EXPDLL_LIBOMG ORBIMPDLL
#else
#define EXPDLL_LIBOMG
#endif
#endif

class EXPDLL_LIBOMG TimeBase
{
    public:


        struct EXPDLL_LIBOMG ulonglong {
             ::CORBA::ULong low;
             ::CORBA::ULong high;
        };
        typedef	ulonglong *	ulonglong_ptr;
        class EXPDLL_LIBOMG ulonglong_var
        {
            public:
                inline ulonglong_var() {_ptr = 0;}
                inline ulonglong_var(ulonglong *_obj) {_ptr = _obj;}
                ulonglong_var(const ulonglong_var &_obj) {_ptr = 0; *this = _obj;}
                ~ulonglong_var();
                ulonglong_var &operator=(ulonglong *);
                ulonglong_var &operator=(const ulonglong_var &);
                inline ulonglong *operator->() {return _ptr;}
                inline const ulonglong *operator->() const {return _ptr;}
                inline const ulonglong & in () const { return *_ptr; }
                inline ulonglong & inout () { return *_ptr; }
                ulonglong & out ()
                {
                    ulonglong *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                ulonglong & _retn ()
                {
                    ulonglong *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline ulonglong_ptr & ptr() { return _ptr; }
                inline operator ulonglong&() { return *_ptr; }
                inline operator const ulonglong&() const { return *_ptr; }
                inline operator ulonglong_ptr &() { return _ptr; }
            private:
                ulonglong *_ptr;
        };  // class ulonglong_var

        typedef ulonglong& ulonglong_out;
        static const ::CORBA::TypeCode_ptr _tc_ulonglong;
        typedef ulonglong TimeT;
        typedef ulonglong_out TimeT_out;
        typedef ulonglong_var TimeT_var;
        static const ::CORBA::TypeCode_ptr _tc_TimeT;
        typedef ::CORBA::Short TdfT;
        typedef ::CORBA::Short_out TdfT_out;
        static const ::CORBA::TypeCode_ptr _tc_TdfT;


        struct EXPDLL_LIBOMG UtcT {
             TimeT time;
             ::CORBA::ULong inacclo;
             ::CORBA::UShort inacchi;
             TdfT tdf;
        };
        typedef	UtcT *	UtcT_ptr;
        class EXPDLL_LIBOMG UtcT_var
        {
            public:
                inline UtcT_var() {_ptr = 0;}
                inline UtcT_var(UtcT *_obj) {_ptr = _obj;}
                UtcT_var(const UtcT_var &_obj) {_ptr = 0; *this = _obj;}
                ~UtcT_var();
                UtcT_var &operator=(UtcT *);
                UtcT_var &operator=(const UtcT_var &);
                inline UtcT *operator->() {return _ptr;}
                inline const UtcT *operator->() const {return _ptr;}
                inline const UtcT & in () const { return *_ptr; }
                inline UtcT & inout () { return *_ptr; }
                UtcT & out ()
                {
                    UtcT *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                UtcT & _retn ()
                {
                    UtcT *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline UtcT_ptr & ptr() { return _ptr; }
                inline operator UtcT&() { return *_ptr; }
                inline operator const UtcT&() const { return *_ptr; }
                inline operator UtcT_ptr &() { return _ptr; }
            private:
                UtcT *_ptr;
        };  // class UtcT_var

        typedef UtcT& UtcT_out;
        static const ::CORBA::TypeCode_ptr _tc_UtcT;
    };  // class TimeBase

    class EXPDLL_LIBOMG Security
    {
        public:


            class EXPDLL_LIBOMG Opaque
            {
                public:
                    Opaque();

                    Opaque(::CORBA::ULong _max);

                    Opaque
                    (
                        ::CORBA::ULong _max,
                        ::CORBA::ULong _length,
                        ::CORBA::Octet *_value,
                        ::CORBA::Boolean _relse = CORBA_FALSE
                    );

                    Opaque(const Opaque &_ptr);

                    ~Opaque();

                    Opaque &operator=(const Opaque& _ptr);

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
            };  // class Opaque

            typedef	Opaque *	Opaque_ptr;
            class EXPDLL_LIBOMG Opaque_var
            {
                public:
                    inline Opaque_var() {_ptr = 0;}
                    inline Opaque_var(Opaque *_obj) {_ptr = _obj;}
                    Opaque_var(const Opaque_var &_obj) {_ptr = 0; *this = _obj;}
                    ~Opaque_var();
                    Opaque_var &operator=(Opaque *);
                    Opaque_var &operator=(const Opaque_var &);
                    inline ::CORBA::Octet &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                    inline Opaque *operator->() {return _ptr;}
                    inline const Opaque *operator->() const {return _ptr;}
                    inline const Opaque & in () const { return *_ptr; }
                    inline Opaque & inout () { return *_ptr; }
                    Opaque *& out ()
                    {
                        delete _ptr;
                        _ptr=0;
                        return _ptr;
                    }
                    Opaque * _retn ()
                    {
                        Opaque *tmp = _ptr;
                        _ptr = 0;
                        return tmp;
                    }
                    inline Opaque_ptr & ptr() { return _ptr; }
                    inline operator Opaque&() { return *_ptr; }
                    inline operator const Opaque&() const { return *_ptr; }
                    inline operator Opaque_ptr &() { return _ptr; }
                private:
                    Opaque *_ptr;
            };  // class Opaque_var

            class EXPDLL_LIBOMG Opaque_out
            {
                public:
                    Opaque_out (Opaque *& p) : ptr_(p) { ptr_ = 0; }
                    Opaque_out (Opaque_var &p) : ptr_(p.ptr()) {
                        delete ptr_; ptr_ = 0; }
                    Opaque_out (const Opaque_out & a) : ptr_(a.ptr_) {}
                    Opaque_out & operator=(const Opaque_out & a) {
                        ptr_ = a.ptr_; return *this; }
                    Opaque_out & operator=(Opaque * p) {
                        ptr_ = p; return *this; }
                    inline operator Opaque_ptr & () { return ptr_; }
                    inline Opaque_ptr & ptr () { return ptr_; }
                    inline Opaque_ptr operator->() { return ptr_; }
                    inline ::CORBA::Octet & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
                private:
                    Opaque_ptr & ptr_;
                    void operator=(const Opaque_var &);

            };  // class Opaque_out
            static const ::CORBA::TypeCode_ptr _tc_Opaque;


            struct EXPDLL_LIBOMG ExtensibleFamily {
                 ::CORBA::UShort family_definer;
                 ::CORBA::UShort family;
            };
            typedef	ExtensibleFamily *	ExtensibleFamily_ptr;
            class EXPDLL_LIBOMG ExtensibleFamily_var
            {
                public:
                    inline ExtensibleFamily_var() {_ptr = 0;}
                    inline ExtensibleFamily_var(ExtensibleFamily *_obj) {_ptr = _obj;}
                    ExtensibleFamily_var(const ExtensibleFamily_var &_obj) {_ptr = 0; *this = _obj;}
                    ~ExtensibleFamily_var();
                    ExtensibleFamily_var &operator=(ExtensibleFamily *);
                    ExtensibleFamily_var &operator=(const ExtensibleFamily_var &);
                    inline ExtensibleFamily *operator->() {return _ptr;}
                    inline const ExtensibleFamily *operator->() const {return _ptr;}
                    inline const ExtensibleFamily & in () const { return *_ptr; }
                    inline ExtensibleFamily & inout () { return *_ptr; }
                    ExtensibleFamily & out ()
                    {
                        ExtensibleFamily *tmp = _ptr;
                        _ptr=0;
                        return *tmp;
                    }
                    ExtensibleFamily & _retn ()
                    {
                        ExtensibleFamily *tmp = _ptr;
                        _ptr = 0;
                        return *tmp;
                    }
                    inline ExtensibleFamily_ptr & ptr() { return _ptr; }
                    inline operator ExtensibleFamily&() { return *_ptr; }
                    inline operator const ExtensibleFamily&() const { return *_ptr; }
                    inline operator ExtensibleFamily_ptr &() { return _ptr; }
                private:
                    ExtensibleFamily *_ptr;
            };  // class ExtensibleFamily_var

            typedef ExtensibleFamily& ExtensibleFamily_out;
            static const ::CORBA::TypeCode_ptr _tc_ExtensibleFamily;
            typedef ::CORBA::ULong SecurityAttributeType;
            typedef ::CORBA::ULong_out SecurityAttributeType_out;
            static const ::CORBA::TypeCode_ptr _tc_SecurityAttributeType;
            static const SecurityAttributeType AuditId ;
            static const SecurityAttributeType AccountingId ;
            static const SecurityAttributeType NonRepudiationId ;
            static const SecurityAttributeType Public ;
            static const SecurityAttributeType AccessId ;
            static const SecurityAttributeType PrimaryGroupId ;
            static const SecurityAttributeType GroupId ;
            static const SecurityAttributeType Role ;
            static const SecurityAttributeType AttributeSet ;
            static const SecurityAttributeType Clearance ;
            static const SecurityAttributeType Capability ;


            struct EXPDLL_LIBOMG AttributeType {
                 ExtensibleFamily attribute_family;
                 SecurityAttributeType attribute_type;
            };
            typedef	AttributeType *	AttributeType_ptr;
            class EXPDLL_LIBOMG AttributeType_var
            {
                public:
                    inline AttributeType_var() {_ptr = 0;}
                    inline AttributeType_var(AttributeType *_obj) {_ptr = _obj;}
                    AttributeType_var(const AttributeType_var &_obj) {_ptr = 0; *this = _obj;}
                    ~AttributeType_var();
                    AttributeType_var &operator=(AttributeType *);
                    AttributeType_var &operator=(const AttributeType_var &);
                    inline AttributeType *operator->() {return _ptr;}
                    inline const AttributeType *operator->() const {return _ptr;}
                    inline const AttributeType & in () const { return *_ptr; }
                    inline AttributeType & inout () { return *_ptr; }
                    AttributeType & out ()
                    {
                        AttributeType *tmp = _ptr;
                        _ptr=0;
                        return *tmp;
                    }
                    AttributeType & _retn ()
                    {
                        AttributeType *tmp = _ptr;
                        _ptr = 0;
                        return *tmp;
                    }
                    inline AttributeType_ptr & ptr() { return _ptr; }
                    inline operator AttributeType&() { return *_ptr; }
                    inline operator const AttributeType&() const { return *_ptr; }
                    inline operator AttributeType_ptr &() { return _ptr; }
                private:
                    AttributeType *_ptr;
            };  // class AttributeType_var

            typedef AttributeType& AttributeType_out;
            static const ::CORBA::TypeCode_ptr _tc_AttributeType;


            class EXPDLL_LIBOMG AttributeTypeList
            {
                public:
                    AttributeTypeList();

                    AttributeTypeList(::CORBA::ULong _max);

                    AttributeTypeList
                    (
                        ::CORBA::ULong _max,
                        ::CORBA::ULong _length,
                        AttributeType *_value,
                        ::CORBA::Boolean _relse = CORBA_FALSE
                    );

                    AttributeTypeList(const AttributeTypeList &_ptr);

                    ~AttributeTypeList();

                    AttributeTypeList &operator=(const AttributeTypeList& _ptr);

                    inline ::CORBA::ULong maximum() const {return _maximum;}

                    void length(::CORBA::ULong);
                    inline ::CORBA::ULong length() const {return _current;}

                    inline AttributeType &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                    inline const AttributeType &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const AttributeType &)_data[_index];}
#else
                            return _data[_index];}
#endif
                    static AttributeType *allocbuf(::CORBA::ULong _nelems);
                    static void freebuf(AttributeType *_ptr);

                    inline AttributeType * OBB__GetData() { return _data; }
                private:
                    AttributeType *_data;
                    ::CORBA::ULong _maximum;
                    ::CORBA::ULong _current;
                    ::CORBA::Boolean _release;
            };  // class AttributeTypeList

            typedef	AttributeTypeList *	AttributeTypeList_ptr;
            class EXPDLL_LIBOMG AttributeTypeList_var
            {
                public:
                    inline AttributeTypeList_var() {_ptr = 0;}
                    inline AttributeTypeList_var(AttributeTypeList *_obj) {_ptr = _obj;}
                    AttributeTypeList_var(const AttributeTypeList_var &_obj) {_ptr = 0; *this = _obj;}
                    ~AttributeTypeList_var();
                    AttributeTypeList_var &operator=(AttributeTypeList *);
                    AttributeTypeList_var &operator=(const AttributeTypeList_var &);
                    inline AttributeType &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                    inline AttributeTypeList *operator->() {return _ptr;}
                    inline const AttributeTypeList *operator->() const {return _ptr;}
                    inline const AttributeTypeList & in () const { return *_ptr; }
                    inline AttributeTypeList & inout () { return *_ptr; }
                    AttributeTypeList *& out ()
                    {
                        delete _ptr;
                        _ptr=0;
                        return _ptr;
                    }
                    AttributeTypeList * _retn ()
                    {
                        AttributeTypeList *tmp = _ptr;
                        _ptr = 0;
                        return tmp;
                    }
                    inline AttributeTypeList_ptr & ptr() { return _ptr; }
                    inline operator AttributeTypeList&() { return *_ptr; }
                    inline operator const AttributeTypeList&() const { return *_ptr; }
                    inline operator AttributeTypeList_ptr &() { return _ptr; }
                private:
                    AttributeTypeList *_ptr;
            };  // class AttributeTypeList_var

            class EXPDLL_LIBOMG AttributeTypeList_out
            {
                public:
                    AttributeTypeList_out (AttributeTypeList *& p) : ptr_(p) { ptr_ = 0; }
                    AttributeTypeList_out (AttributeTypeList_var &p) : ptr_(p.ptr()) {
                        delete ptr_; ptr_ = 0; }
                    AttributeTypeList_out (const AttributeTypeList_out & a) : ptr_(a.ptr_) {}
                    AttributeTypeList_out & operator=(const AttributeTypeList_out & a) {
                        ptr_ = a.ptr_; return *this; }
                    AttributeTypeList_out & operator=(AttributeTypeList * p) {
                        ptr_ = p; return *this; }
                    inline operator AttributeTypeList_ptr & () { return ptr_; }
                    inline AttributeTypeList_ptr & ptr () { return ptr_; }
                    inline AttributeTypeList_ptr operator->() { return ptr_; }
                    inline AttributeType & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
                private:
                    AttributeTypeList_ptr & ptr_;
                    void operator=(const AttributeTypeList_var &);

            };  // class AttributeTypeList_out
            static const ::CORBA::TypeCode_ptr _tc_AttributeTypeList;


            struct EXPDLL_LIBOMG SecAttribute {
                 AttributeType attribute_type;


                 Opaque defining_authority;


                 Opaque value;
                SecAttribute &operator=(const SecAttribute &_obj);
            };
            typedef	SecAttribute *	SecAttribute_ptr;
            class EXPDLL_LIBOMG SecAttribute_var
            {
                public:
                    inline SecAttribute_var() {_ptr = 0;}
                    inline SecAttribute_var(SecAttribute *_obj) {_ptr = _obj;}
                    SecAttribute_var(const SecAttribute_var &_obj) {_ptr = 0; *this = _obj;}
                    ~SecAttribute_var();
                    SecAttribute_var &operator=(SecAttribute *);
                    SecAttribute_var &operator=(const SecAttribute_var &);
                    inline SecAttribute *operator->() {return _ptr;}
                    inline const SecAttribute *operator->() const {return _ptr;}
                    inline const SecAttribute & in () const { return *_ptr; }
                    inline SecAttribute & inout () { return *_ptr; }
                    SecAttribute *& out ()
                    {
                        delete _ptr;
                        _ptr=0;
                        return _ptr;
                    }
                    SecAttribute * _retn ()
                    {
                        SecAttribute *tmp = _ptr;
                        _ptr = 0;
                        return tmp;
                    }
                    inline SecAttribute_ptr & ptr() { return _ptr; }
                    inline operator SecAttribute&() { return *_ptr; }
                    inline operator const SecAttribute&() const { return *_ptr; }
                    inline operator SecAttribute_ptr &() { return _ptr; }
                private:
                    SecAttribute *_ptr;
            };  // class SecAttribute_var

            class EXPDLL_LIBOMG SecAttribute_out
            {
                public:
                    SecAttribute_out (SecAttribute *& p) : ptr_(p) { ptr_ = 0; }
                    SecAttribute_out (SecAttribute_var &p) : ptr_(p.ptr()) {
                        delete ptr_; ptr_ = 0; }
                    SecAttribute_out (const SecAttribute_out & a) : ptr_(a.ptr_) {}
                    SecAttribute_out & operator=(const SecAttribute_out & a) {
                        ptr_ = a.ptr_; return *this; }
                    SecAttribute_out & operator=(SecAttribute * p) {
                        ptr_ = p; return *this; }
                    inline operator SecAttribute_ptr & () { return ptr_; }
                    inline SecAttribute_ptr & ptr () { return ptr_; }
                    inline SecAttribute_ptr operator->() { return ptr_; }
                private:
                    SecAttribute_ptr & ptr_;
                    void operator=(const SecAttribute_var &);

            };  // class SecAttribute_out
            static const ::CORBA::TypeCode_ptr _tc_SecAttribute;


            class EXPDLL_LIBOMG AttributeList
            {
                public:
                    AttributeList();

                    AttributeList(::CORBA::ULong _max);

                    AttributeList
                    (
                        ::CORBA::ULong _max,
                        ::CORBA::ULong _length,
                        SecAttribute *_value,
                        ::CORBA::Boolean _relse = CORBA_FALSE
                    );

                    AttributeList(const AttributeList &_ptr);

                    ~AttributeList();

                    AttributeList &operator=(const AttributeList& _ptr);

                    inline ::CORBA::ULong maximum() const {return _maximum;}

                    void length(::CORBA::ULong);
                    inline ::CORBA::ULong length() const {return _current;}

                    inline SecAttribute &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                    inline const SecAttribute &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const SecAttribute &)_data[_index];}
#else
                            return _data[_index];}
#endif
                    static SecAttribute *allocbuf(::CORBA::ULong _nelems);
                    static void freebuf(SecAttribute *_ptr);

                    inline SecAttribute * OBB__GetData() { return _data; }
                private:
                    SecAttribute *_data;
                    ::CORBA::ULong _maximum;
                    ::CORBA::ULong _current;
                    ::CORBA::Boolean _release;
            };  // class AttributeList

            typedef	AttributeList *	AttributeList_ptr;
            class EXPDLL_LIBOMG AttributeList_var
            {
                public:
                    inline AttributeList_var() {_ptr = 0;}
                    inline AttributeList_var(AttributeList *_obj) {_ptr = _obj;}
                    AttributeList_var(const AttributeList_var &_obj) {_ptr = 0; *this = _obj;}
                    ~AttributeList_var();
                    AttributeList_var &operator=(AttributeList *);
                    AttributeList_var &operator=(const AttributeList_var &);
                    inline SecAttribute &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                    inline AttributeList *operator->() {return _ptr;}
                    inline const AttributeList *operator->() const {return _ptr;}
                    inline const AttributeList & in () const { return *_ptr; }
                    inline AttributeList & inout () { return *_ptr; }
                    AttributeList *& out ()
                    {
                        delete _ptr;
                        _ptr=0;
                        return _ptr;
                    }
                    AttributeList * _retn ()
                    {
                        AttributeList *tmp = _ptr;
                        _ptr = 0;
                        return tmp;
                    }
                    inline AttributeList_ptr & ptr() { return _ptr; }
                    inline operator AttributeList&() { return *_ptr; }
                    inline operator const AttributeList&() const { return *_ptr; }
                    inline operator AttributeList_ptr &() { return _ptr; }
                private:
                    AttributeList *_ptr;
            };  // class AttributeList_var

            class EXPDLL_LIBOMG AttributeList_out
            {
                public:
                    AttributeList_out (AttributeList *& p) : ptr_(p) { ptr_ = 0; }
                    AttributeList_out (AttributeList_var &p) : ptr_(p.ptr()) {
                        delete ptr_; ptr_ = 0; }
                    AttributeList_out (const AttributeList_out & a) : ptr_(a.ptr_) {}
                    AttributeList_out & operator=(const AttributeList_out & a) {
                        ptr_ = a.ptr_; return *this; }
                    AttributeList_out & operator=(AttributeList * p) {
                        ptr_ = p; return *this; }
                    inline operator AttributeList_ptr & () { return ptr_; }
                    inline AttributeList_ptr & ptr () { return ptr_; }
                    inline AttributeList_ptr operator->() { return ptr_; }
                    inline SecAttribute & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
                private:
                    AttributeList_ptr & ptr_;
                    void operator=(const AttributeList_var &);

            };  // class AttributeList_out
            static const ::CORBA::TypeCode_ptr _tc_AttributeList;


            enum AuthenticationStatus { SecAuthSuccess, SecAuthFailure, SecAuthContinue, SecAuthExpired };
            typedef AuthenticationStatus & AuthenticationStatus_out ;
            static const ::CORBA::TypeCode_ptr _tc_AuthenticationStatus;
            typedef ::CORBA::ULong AuthenticationMethod;
            typedef ::CORBA::ULong_out AuthenticationMethod_out;
            static const ::CORBA::TypeCode_ptr _tc_AuthenticationMethod;


            enum CredentialType { SecInvocationCredentials, SecOwnCredentials, SecNRCredentials };
            typedef CredentialType & CredentialType_out ;
            static const ::CORBA::TypeCode_ptr _tc_CredentialType;
            typedef ::TimeBase::UtcT UtcT;
            typedef ::TimeBase::UtcT_out UtcT_out;
            typedef ::TimeBase::UtcT_var UtcT_var;
            static const ::CORBA::TypeCode_ptr _tc_UtcT;
            typedef ::CORBA::UShort AssociationOptions;
            typedef ::CORBA::UShort_out AssociationOptions_out;
            static const ::CORBA::TypeCode_ptr _tc_AssociationOptions;
            static const AssociationOptions NoProtection ;
            static const AssociationOptions Integrity ;
            static const AssociationOptions Confidentiality ;
            static const AssociationOptions DetectReplay ;
            static const AssociationOptions DetectMisordering ;
            static const AssociationOptions EstablishTrustInTarget ;
            static const AssociationOptions EstablishTrustInClient ;
            static const AssociationOptions NoDelegation ;
            static const AssociationOptions SimpleDelegation ;
            static const AssociationOptions CompositeDelegation ;
        };  // class Security

        class EXPDLL_LIBOMG SecurityLevel1
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

                        virtual ::Security::AttributeList * get_attributes (
                             const ::Security::AttributeTypeList & attributes); 

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

            };  // class SecurityLevel1

            class EXPDLL_LIBOMG SecurityLevel2
            {
                public:
                    class	PrincipalAuthenticator;
                    typedef	PrincipalAuthenticator *	PrincipalAuthenticator_ptr;
                    class PrincipalAuthenticator_out;

                    class EXPDLL_LIBOMG PrincipalAuthenticator_var : public ::CORBA::_var {
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


                    class	Credentials;
                    typedef	Credentials *	Credentials_ptr;
                    class Credentials_out;

                    class EXPDLL_LIBOMG Credentials_var : public ::CORBA::_var {
                        public:
                            Credentials_var();
                            inline Credentials_var(Credentials_ptr p) {ptr_ = p; }
                            Credentials_var(const Credentials_var &a);
                            ~Credentials_var()
                                { free();}

                            Credentials_var &operator=(Credentials_ptr p)
                                { if (p != ptr_) reset(p);
                                return *this; }

                            Credentials_var &operator=(const Credentials_var &a);
                            inline Credentials_ptr in () const { return ptr_; }
                            inline Credentials_ptr & inout () { return ptr_; }
                            Credentials_ptr & out ();
                            Credentials_ptr _retn ();

                            inline operator Credentials_ptr&() { return ptr_; }
                            inline operator const Credentials_ptr&() const { return ptr_; }
                            inline Credentials_ptr operator->() const { return ptr_; }

                            inline Credentials_ptr & ptr () { return ptr_; }
                        protected:
                            Credentials_ptr ptr_;
                            void free();
                            void reset(Credentials_ptr p) { free(); ptr_ = p; }

                        private:
                            void operator=(const ::CORBA::_var &);
                    };  // class Credentials_var


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




                    static const ::CORBA::TypeCode_ptr _tc_PrincipalAuthenticator;
                    class EXPDLL_LIBOMG PrincipalAuthenticator : public virtual ::CORBA::Object
                     {
                        public:
                            static PrincipalAuthenticator_ptr _duplicate(PrincipalAuthenticator_ptr obj) 
                                {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                                return obj;}
                            static PrincipalAuthenticator_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                            inline static PrincipalAuthenticator_ptr _nil() { return 0; }
                            static const char* _get_interface_name ();

                            virtual ::Security::AuthenticationStatus authenticate (
                                ::Security::AuthenticationMethod method,
                                const char * security_name,
                                 const ::Security::Opaque & auth_data,
                                 const ::Security::AttributeList & privileges,
                                Credentials_out creds,
                                ::Security::Opaque_out continuation_data,
                                ::Security::Opaque_out auth_specific_data); 

                            virtual ::Security::AuthenticationStatus continue_authentication (
                                 const ::Security::Opaque & response_data,
                                Credentials_ptr creds,
                                ::Security::Opaque_out continuation_data,
                                ::Security::Opaque_out auth_specific_data); 

                        protected:
                            PrincipalAuthenticator(::CORBA::Object_ptr obj = 0);
                            virtual ~PrincipalAuthenticator(){ }

                        private:
                            PrincipalAuthenticator( const PrincipalAuthenticator&) { }
                            void operator=(const PrincipalAuthenticator&) { }
                            ::CORBA::ORB_ptr pORB;
                    };  // class PrincipalAuthenticator



                    class EXPDLL_LIBOMG PrincipalAuthenticator_out
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



                    static const ::CORBA::TypeCode_ptr _tc_Credentials;
                    class EXPDLL_LIBOMG Credentials : public virtual ::CORBA::Object
                     {
                        public:
                            static Credentials_ptr _duplicate(Credentials_ptr obj) 
                                {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                                return obj;}
                            static Credentials_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                            inline static Credentials_ptr _nil() { return 0; }
                            static const char* _get_interface_name ();

                            virtual ::Security::AttributeList * get_attributes (
                                 const ::Security::AttributeTypeList & attributes); 

                            virtual ::CORBA::Boolean is_valid (
                                ::Security::UtcT_out expiry_time); 

                            virtual ::Security::AssociationOptions invocation_options_supported (); 

                            virtual void invocation_options_supported (
                                ::Security::AssociationOptions invocation_options_supported); 

                            virtual ::Security::AssociationOptions invocation_options_required (); 

                            virtual void invocation_options_required (
                                ::Security::AssociationOptions invocation_options_required); 

                        protected:
                            Credentials(::CORBA::Object_ptr obj = 0);
                            virtual ~Credentials(){ }

                        private:
                            Credentials( const Credentials&) { }
                            void operator=(const Credentials&) { }
                            ::CORBA::ORB_ptr pORB;
                    };  // class Credentials



                    class EXPDLL_LIBOMG Credentials_out
                     {
                        public:
                            Credentials_out (Credentials_ptr & p);
                            Credentials_out (Credentials_var & p);
                            Credentials_out (const Credentials_out & p) : ptr_(p.ptr_) {}
                            Credentials_out & operator=(const Credentials_out & a) {
                                ptr_ = a.ptr_; return *this;}
                            Credentials_out & operator=(const Credentials_var & a);
                            Credentials_out & operator=(Credentials_ptr p) {
                            ptr_ = p; return *this;}
                            inline operator Credentials_ptr & () { return ptr_; }
                            inline Credentials_ptr & ptr () { return ptr_; }
                            inline Credentials_ptr operator->() { return ptr_; }
                        private:
                            Credentials_ptr & ptr_;
                    };  // class Credentials_out



                    static const ::CORBA::TypeCode_ptr _tc_Current;
                    class EXPDLL_LIBOMG Current : public   ::SecurityLevel1::Current
                     {
                        public:
                            static Current_ptr _duplicate(Current_ptr obj) 
                                {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                                return obj;}
                            static Current_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                            inline static Current_ptr _nil() { return 0; }
                            static const char* _get_interface_name ();

                            virtual void set_credentials (
                                ::Security::CredentialType cred_type,
                                Credentials_ptr cred); 

                            virtual Credentials_ptr get_credentials (
                                ::Security::CredentialType cred_type); 

                            virtual PrincipalAuthenticator_ptr principal_authenticator (); 

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

                };  // class SecurityLevel2

void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::TimeBase::ulonglong &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::TimeBase::ulonglong *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::TimeBase::ulonglong *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::TimeBase::UtcT &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::TimeBase::UtcT *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::TimeBase::UtcT *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::Security::Opaque &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::Opaque *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::Opaque *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::Security::ExtensibleFamily &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::ExtensibleFamily *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::ExtensibleFamily *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::Security::AttributeType &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::AttributeType *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::AttributeType *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::Security::AttributeTypeList &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::AttributeTypeList *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::AttributeTypeList *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::Security::SecAttribute &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::SecAttribute *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::SecAttribute *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, const ::Security::AttributeList &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::AttributeList *obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::AttributeList *&obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::AuthenticationStatus obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::AuthenticationStatus &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::Security::CredentialType obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::Security::CredentialType &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::SecurityLevel1::Current_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::SecurityLevel1::Current_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::SecurityLevel2::PrincipalAuthenticator_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::SecurityLevel2::PrincipalAuthenticator_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::SecurityLevel2::Credentials_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::SecurityLevel2::Credentials_ptr &obj);
void EXPDLL_LIBOMG operator<<=(::CORBA::Any &a, ::SecurityLevel2::Current_ptr obj);
::CORBA::Boolean EXPDLL_LIBOMG operator>>=(const ::CORBA::Any &a, ::SecurityLevel2::Current_ptr &obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::TimeBase::ulonglong &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::TimeBase::ulonglong &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::TimeBase::UtcT &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::TimeBase::UtcT &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::Opaque &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::Opaque &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::ExtensibleFamily &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::ExtensibleFamily &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::AttributeType &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::AttributeType &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::AttributeTypeList &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::AttributeTypeList &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::SecAttribute &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::SecAttribute &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::AttributeList &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::AttributeList &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::AuthenticationStatus &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::AuthenticationStatus &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &, ::Security::CredentialType &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &, ::Security::CredentialType &);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, SecurityLevel1::Current_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel1::Current_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel1::Current_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, SecurityLevel2::PrincipalAuthenticator_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel2::PrincipalAuthenticator_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel2::PrincipalAuthenticator_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, SecurityLevel2::Credentials_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel2::Credentials_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel2::Credentials_var &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator<<(OBB::MarshalBuf &mb, SecurityLevel2::Current_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel2::Current_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBOMG &operator>>(OBB::MarshalBuf &mb, SecurityLevel2::Current_var &_obj);
#ifdef ORB_IMPORT_DEFINED_security_c
#undef ORB_IMPORT_DEFINED_security_c
#undef EXPDLL_LIBOMG
#endif
#endif

