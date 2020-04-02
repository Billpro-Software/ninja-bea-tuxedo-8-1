/*******************************************************************
 * Created Mon Jan 27 07:37:48 2003 by Tuxedo V8.0-01 (C++ Bindings)
 *******************************************************************
 */

/*
 * Client Stubs include file: (tobjin_c.h)
 * --------------------------------------------
 *
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    InitialReferences
 *    DelegatedCurrent
 *    DelegatedAuthenticator
 *    DelegatedBiDir
 *
 */


#ifndef _tobjin_c_H
#define _tobjin_c_H

#include <string.h>
#include <CORBA.h>
#include <orbgen.h>

#if defined(WIN32)
#pragma warning(disable:4250)
#endif


#ifndef EXPDLL_LIBENV
#define ORB_IMPORT_DEFINED_tobjin_c
#ifdef WIN32 
#define EXPDLL_LIBENV ORBIMPDLL
#else
#define EXPDLL_LIBENV
#endif
#endif

#include "tobj_c.h"
class EXPDLL_LIBENV TobjInternal
{
    public:
        class	InitialReferences;
        typedef	InitialReferences *	InitialReferences_ptr;
        class InitialReferences_out;

        class EXPDLL_LIBENV InitialReferences_var : public ::CORBA::_var {
            public:
                InitialReferences_var();
                inline InitialReferences_var(InitialReferences_ptr p) {ptr_ = p; }
                InitialReferences_var(const InitialReferences_var &a);
                ~InitialReferences_var()
                    { free();}

                InitialReferences_var &operator=(InitialReferences_ptr p)
                    { if (p != ptr_) reset(p);
                    return *this; }

                InitialReferences_var &operator=(const InitialReferences_var &a);
                inline InitialReferences_ptr in () const { return ptr_; }
                inline InitialReferences_ptr & inout () { return ptr_; }
                InitialReferences_ptr & out ();
                InitialReferences_ptr _retn ();

                inline operator InitialReferences_ptr&() { return ptr_; }
                inline operator const InitialReferences_ptr&() const { return ptr_; }
                inline InitialReferences_ptr operator->() const { return ptr_; }

                inline InitialReferences_ptr & ptr () { return ptr_; }
            protected:
                InitialReferences_ptr ptr_;
                void free();
                void reset(InitialReferences_ptr p) { free(); ptr_ = p; }

            private:
                void operator=(const ::CORBA::_var &);
        };  // class InitialReferences_var




        struct EXPDLL_LIBENV Version {
             ::CORBA::Octet major;
             ::CORBA::Octet minor;
        };
        typedef	Version *	Version_ptr;
        class EXPDLL_LIBENV Version_var
        {
            public:
                inline Version_var() {_ptr = 0;}
                inline Version_var(Version *_obj) {_ptr = _obj;}
                Version_var(const Version_var &_obj) {_ptr = 0; *this = _obj;}
                ~Version_var();
                Version_var &operator=(Version *);
                Version_var &operator=(const Version_var &);
                inline Version *operator->() {return _ptr;}
                inline const Version *operator->() const {return _ptr;}
                inline const Version & in () const { return *_ptr; }
                inline Version & inout () { return *_ptr; }
                Version & out ()
                {
                    Version *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                Version & _retn ()
                {
                    Version *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline Version_ptr & ptr() { return _ptr; }
                inline operator Version&() { return *_ptr; }
                inline operator const Version&() const { return *_ptr; }
                inline operator Version_ptr &() { return _ptr; }
            private:
                Version *_ptr;
        };  // class Version_var

        typedef Version& Version_out;
        static const ::CORBA::TypeCode_ptr _tc_Version;


        struct EXPDLL_LIBENV InitRef {
            ::CORBA::String_var name;
            ::CORBA::String_var ref;
            InitRef &operator=(const InitRef &_obj);
        };
        typedef	InitRef *	InitRef_ptr;
        class EXPDLL_LIBENV InitRef_var
        {
            public:
                inline InitRef_var() {_ptr = 0;}
                inline InitRef_var(InitRef *_obj) {_ptr = _obj;}
                InitRef_var(const InitRef_var &_obj) {_ptr = 0; *this = _obj;}
                ~InitRef_var();
                InitRef_var &operator=(InitRef *);
                InitRef_var &operator=(const InitRef_var &);
                inline InitRef *operator->() {return _ptr;}
                inline const InitRef *operator->() const {return _ptr;}
                inline const InitRef & in () const { return *_ptr; }
                inline InitRef & inout () { return *_ptr; }
                InitRef *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InitRef * _retn ()
                {
                    InitRef *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InitRef_ptr & ptr() { return _ptr; }
                inline operator InitRef&() { return *_ptr; }
                inline operator const InitRef&() const { return *_ptr; }
                inline operator InitRef_ptr &() { return _ptr; }
            private:
                InitRef *_ptr;
        };  // class InitRef_var

        class EXPDLL_LIBENV InitRef_out
        {
            public:
                InitRef_out (InitRef *& p) : ptr_(p) { ptr_ = 0; }
                InitRef_out (InitRef_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InitRef_out (const InitRef_out & a) : ptr_(a.ptr_) {}
                InitRef_out & operator=(const InitRef_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InitRef_out & operator=(InitRef * p) {
                    ptr_ = p; return *this; }
                inline operator InitRef_ptr & () { return ptr_; }
                inline InitRef_ptr & ptr () { return ptr_; }
                inline InitRef_ptr operator->() { return ptr_; }
            private:
                InitRef_ptr & ptr_;
                void operator=(const InitRef_var &);

        };  // class InitRef_out
        static const ::CORBA::TypeCode_ptr _tc_InitRef;


        class EXPDLL_LIBENV InitRefList
        {
            public:
                InitRefList();

                InitRefList(::CORBA::ULong _max);

                InitRefList
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    InitRef *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                InitRefList(const InitRefList &_ptr);

                ~InitRefList();

                InitRefList &operator=(const InitRefList& _ptr);

                inline ::CORBA::ULong maximum() const {return _maximum;}

                void length(::CORBA::ULong);
                inline ::CORBA::ULong length() const {return _current;}

                inline InitRef &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                inline const InitRef &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const InitRef &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static InitRef *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(InitRef *_ptr);

                inline InitRef * OBB__GetData() { return _data; }
            private:
                InitRef *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
        };  // class InitRefList

        typedef	InitRefList *	InitRefList_ptr;
        class EXPDLL_LIBENV InitRefList_var
        {
            public:
                inline InitRefList_var() {_ptr = 0;}
                inline InitRefList_var(InitRefList *_obj) {_ptr = _obj;}
                InitRefList_var(const InitRefList_var &_obj) {_ptr = 0; *this = _obj;}
                ~InitRefList_var();
                InitRefList_var &operator=(InitRefList *);
                InitRefList_var &operator=(const InitRefList_var &);
                inline InitRef &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline InitRefList *operator->() {return _ptr;}
                inline const InitRefList *operator->() const {return _ptr;}
                inline const InitRefList & in () const { return *_ptr; }
                inline InitRefList & inout () { return *_ptr; }
                InitRefList *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InitRefList * _retn ()
                {
                    InitRefList *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InitRefList_ptr & ptr() { return _ptr; }
                inline operator InitRefList&() { return *_ptr; }
                inline operator const InitRefList&() const { return *_ptr; }
                inline operator InitRefList_ptr &() { return _ptr; }
            private:
                InitRefList *_ptr;
        };  // class InitRefList_var

        class EXPDLL_LIBENV InitRefList_out
        {
            public:
                InitRefList_out (InitRefList *& p) : ptr_(p) { ptr_ = 0; }
                InitRefList_out (InitRefList_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InitRefList_out (const InitRefList_out & a) : ptr_(a.ptr_) {}
                InitRefList_out & operator=(const InitRefList_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InitRefList_out & operator=(InitRefList * p) {
                    ptr_ = p; return *this; }
                inline operator InitRefList_ptr & () { return ptr_; }
                inline InitRefList_ptr & ptr () { return ptr_; }
                inline InitRefList_ptr operator->() { return ptr_; }
                inline InitRef & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                InitRefList_ptr & ptr_;
                void operator=(const InitRefList_var &);

        };  // class InitRefList_out
        static const ::CORBA::TypeCode_ptr _tc_InitRefList;


        struct EXPDLL_LIBENV InitObjRef {
            ::CORBA::String_var name;
            ::CORBA::String_var strref;


             ::CORBA::Object_var objref;
            InitObjRef &operator=(const InitObjRef &_obj);
        };
        typedef	InitObjRef *	InitObjRef_ptr;
        class EXPDLL_LIBENV InitObjRef_var
        {
            public:
                inline InitObjRef_var() {_ptr = 0;}
                inline InitObjRef_var(InitObjRef *_obj) {_ptr = _obj;}
                InitObjRef_var(const InitObjRef_var &_obj) {_ptr = 0; *this = _obj;}
                ~InitObjRef_var();
                InitObjRef_var &operator=(InitObjRef *);
                InitObjRef_var &operator=(const InitObjRef_var &);
                inline InitObjRef *operator->() {return _ptr;}
                inline const InitObjRef *operator->() const {return _ptr;}
                inline const InitObjRef & in () const { return *_ptr; }
                inline InitObjRef & inout () { return *_ptr; }
                InitObjRef *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InitObjRef * _retn ()
                {
                    InitObjRef *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InitObjRef_ptr & ptr() { return _ptr; }
                inline operator InitObjRef&() { return *_ptr; }
                inline operator const InitObjRef&() const { return *_ptr; }
                inline operator InitObjRef_ptr &() { return _ptr; }
            private:
                InitObjRef *_ptr;
        };  // class InitObjRef_var

        class EXPDLL_LIBENV InitObjRef_out
        {
            public:
                InitObjRef_out (InitObjRef *& p) : ptr_(p) { ptr_ = 0; }
                InitObjRef_out (InitObjRef_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InitObjRef_out (const InitObjRef_out & a) : ptr_(a.ptr_) {}
                InitObjRef_out & operator=(const InitObjRef_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InitObjRef_out & operator=(InitObjRef * p) {
                    ptr_ = p; return *this; }
                inline operator InitObjRef_ptr & () { return ptr_; }
                inline InitObjRef_ptr & ptr () { return ptr_; }
                inline InitObjRef_ptr operator->() { return ptr_; }
            private:
                InitObjRef_ptr & ptr_;
                void operator=(const InitObjRef_var &);

        };  // class InitObjRef_out
        static const ::CORBA::TypeCode_ptr _tc_InitObjRef;


        class EXPDLL_LIBENV InitObjRefList
        {
            public:
                InitObjRefList();

                InitObjRefList(::CORBA::ULong _max);

                InitObjRefList
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    InitObjRef *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                InitObjRefList(const InitObjRefList &_ptr);

                ~InitObjRefList();

                InitObjRefList &operator=(const InitObjRefList& _ptr);

                inline ::CORBA::ULong maximum() const {return _maximum;}

                void length(::CORBA::ULong);
                inline ::CORBA::ULong length() const {return _current;}

                inline InitObjRef &operator[](::CORBA::ULong _index) {if (_index > _maximum) throw ::CORBA::BAD_PARAM(); return _data[_index];}
                inline const InitObjRef &operator[](::CORBA::ULong _index) const {if (_index > _maximum) throw ::CORBA::BAD_PARAM();
#ifdef WIN32
                            return (const InitObjRef &)_data[_index];}
#else
                            return _data[_index];}
#endif
                static InitObjRef *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(InitObjRef *_ptr);

                inline InitObjRef * OBB__GetData() { return _data; }
            private:
                InitObjRef *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
        };  // class InitObjRefList

        typedef	InitObjRefList *	InitObjRefList_ptr;
        class EXPDLL_LIBENV InitObjRefList_var
        {
            public:
                inline InitObjRefList_var() {_ptr = 0;}
                inline InitObjRefList_var(InitObjRefList *_obj) {_ptr = _obj;}
                InitObjRefList_var(const InitObjRefList_var &_obj) {_ptr = 0; *this = _obj;}
                ~InitObjRefList_var();
                InitObjRefList_var &operator=(InitObjRefList *);
                InitObjRefList_var &operator=(const InitObjRefList_var &);
                inline InitObjRef &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline InitObjRefList *operator->() {return _ptr;}
                inline const InitObjRefList *operator->() const {return _ptr;}
                inline const InitObjRefList & in () const { return *_ptr; }
                inline InitObjRefList & inout () { return *_ptr; }
                InitObjRefList *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                InitObjRefList * _retn ()
                {
                    InitObjRefList *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline InitObjRefList_ptr & ptr() { return _ptr; }
                inline operator InitObjRefList&() { return *_ptr; }
                inline operator const InitObjRefList&() const { return *_ptr; }
                inline operator InitObjRefList_ptr &() { return _ptr; }
            private:
                InitObjRefList *_ptr;
        };  // class InitObjRefList_var

        class EXPDLL_LIBENV InitObjRefList_out
        {
            public:
                InitObjRefList_out (InitObjRefList *& p) : ptr_(p) { ptr_ = 0; }
                InitObjRefList_out (InitObjRefList_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                InitObjRefList_out (const InitObjRefList_out & a) : ptr_(a.ptr_) {}
                InitObjRefList_out & operator=(const InitObjRefList_out & a) {
                    ptr_ = a.ptr_; return *this; }
                InitObjRefList_out & operator=(InitObjRefList * p) {
                    ptr_ = p; return *this; }
                inline operator InitObjRefList_ptr & () { return ptr_; }
                inline InitObjRefList_ptr & ptr () { return ptr_; }
                inline InitObjRefList_ptr operator->() { return ptr_; }
                inline InitObjRef & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                InitObjRefList_ptr & ptr_;
                void operator=(const InitObjRefList_var &);

        };  // class InitObjRefList_out
        static const ::CORBA::TypeCode_ptr _tc_InitObjRefList;
        typedef ::CORBA::Char * ObjectId;
        typedef ::CORBA::String_out ObjectId_out;
        typedef ::CORBA::String_var ObjectId_var;
        static const ::CORBA::TypeCode_ptr _tc_ObjectId;


        class EXPDLL_LIBENV ObjectIdList
        {
            public:


                class EXPDLL_LIBENV _ForSeq_var
                {
                    public:
                        _ForSeq_var();

                        _ForSeq_var(ObjectId _ptr);

                        _ForSeq_var(const _ForSeq_var &_ptr);

                        ~_ForSeq_var();

                        _ForSeq_var &operator=(const _ForSeq_var& _ptr);

                        _ForSeq_var &operator=(ObjectId _ptr);
                        _ForSeq_var &operator=(const ::CORBA::Char * _ptr);
                        operator ObjectId() const;
                        operator ObjectId ();
                        void OBB__release(::CORBA::Boolean _relse);
                        ::CORBA::Boolean OBB__release();

                        static ObjectId allocbuf(::CORBA::ULong _nelems);
                        static void freebuf(ObjectId _ptr);

                    private:
                        ObjectId _data;
                        ::CORBA::Boolean _release;
                };  // class _ForSeq_var

                ObjectIdList();

                ObjectIdList(::CORBA::ULong _max);

                ObjectIdList
                (
                    ::CORBA::ULong _max,
                    ::CORBA::ULong _length,
                    ObjectId *_value,
                    ::CORBA::Boolean _relse = CORBA_FALSE
                );

                ObjectIdList(const ObjectIdList &_ptr);

                ~ObjectIdList();

                ObjectIdList &operator=(const ObjectIdList& _ptr);

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
                static ObjectId *allocbuf(::CORBA::ULong _nelems);
                static void freebuf(ObjectId *_ptr);

            private:
                _ForSeq_var *_data;
                ::CORBA::ULong _maximum;
                ::CORBA::ULong _current;
                ::CORBA::Boolean _release;
                static _ForSeq_var *OBB__allocbuf(::CORBA::ULong _nelems);
                static void OBB__freebuf(_ForSeq_var *_ptr);

        };  // class ObjectIdList

        typedef	ObjectIdList *	ObjectIdList_ptr;
        class EXPDLL_LIBENV ObjectIdList_var
        {
            public:
                inline ObjectIdList_var() {_ptr = 0;}
                inline ObjectIdList_var(ObjectIdList *_obj) {_ptr = _obj;}
                ObjectIdList_var(const ObjectIdList_var &_obj) {_ptr = 0; *this = _obj;}
                ~ObjectIdList_var();
                ObjectIdList_var &operator=(ObjectIdList *);
                ObjectIdList_var &operator=(const ObjectIdList_var &);
                inline ObjectIdList::_ForSeq_var &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                inline ObjectIdList *operator->() {return _ptr;}
                inline const ObjectIdList *operator->() const {return _ptr;}
                inline const ObjectIdList & in () const { return *_ptr; }
                inline ObjectIdList & inout () { return *_ptr; }
                ObjectIdList *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ObjectIdList * _retn ()
                {
                    ObjectIdList *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ObjectIdList_ptr & ptr() { return _ptr; }
                inline operator ObjectIdList&() { return *_ptr; }
                inline operator const ObjectIdList&() const { return *_ptr; }
                inline operator ObjectIdList_ptr &() { return _ptr; }
            private:
                ObjectIdList *_ptr;
        };  // class ObjectIdList_var

        class EXPDLL_LIBENV ObjectIdList_out
        {
            public:
                ObjectIdList_out (ObjectIdList *& p) : ptr_(p) { ptr_ = 0; }
                ObjectIdList_out (ObjectIdList_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ObjectIdList_out (const ObjectIdList_out & a) : ptr_(a.ptr_) {}
                ObjectIdList_out & operator=(const ObjectIdList_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ObjectIdList_out & operator=(ObjectIdList * p) {
                    ptr_ = p; return *this; }
                inline operator ObjectIdList_ptr & () { return ptr_; }
                inline ObjectIdList_ptr & ptr () { return ptr_; }
                inline ObjectIdList_ptr operator->() { return ptr_; }
                inline ObjectIdList::_ForSeq_var & operator[](::CORBA::ULong _index) {return ((*ptr_)[_index]);}
            private:
                ObjectIdList_ptr & ptr_;
                void operator=(const ObjectIdList_var &);

        };  // class ObjectIdList_out
        static const ::CORBA::TypeCode_ptr _tc_ObjectIdList;


        static const ::CORBA::TypeCode_ptr _tc_InitialReferences;
        class EXPDLL_LIBENV InitialReferences : public virtual ::CORBA::Object
         {
            public:
                static InitialReferences_ptr _duplicate(InitialReferences_ptr obj) 
                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                    return obj;}
                static InitialReferences_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                inline static InitialReferences_ptr _nil() { return 0; }
                static const char* _get_interface_name ();

                virtual ::CORBA::Object_ptr get (
                    const char * id); 

                virtual ObjectIdList * list (); 

                virtual void get_references (
                    Version & v,
                    InitRefList_out refs,
                    ::CORBA::String_out secUid); 

            protected:
                InitialReferences(::CORBA::Object_ptr obj = 0);
                virtual ~InitialReferences(){ }

            private:
                InitialReferences( const InitialReferences&) { }
                void operator=(const InitialReferences&) { }
                ::CORBA::ORB_ptr pORB;
        };  // class InitialReferences



        class EXPDLL_LIBENV InitialReferences_out
         {
            public:
                InitialReferences_out (InitialReferences_ptr & p);
                InitialReferences_out (InitialReferences_var & p);
                InitialReferences_out (const InitialReferences_out & p) : ptr_(p.ptr_) {}
                InitialReferences_out & operator=(const InitialReferences_out & a) {
                    ptr_ = a.ptr_; return *this;}
                InitialReferences_out & operator=(const InitialReferences_var & a);
                InitialReferences_out & operator=(InitialReferences_ptr p) {
                ptr_ = p; return *this;}
                inline operator InitialReferences_ptr & () { return ptr_; }
                inline InitialReferences_ptr & ptr () { return ptr_; }
                inline InitialReferences_ptr operator->() { return ptr_; }
            private:
                InitialReferences_ptr & ptr_;
        };  // class InitialReferences_out



        enum ATMIerrors { TPNOERROR, TPEABORT, TPEBADDESC, TPEBLOCK, TPEINVAL, TPELIMIT, TPENOENT, TPEOS, TPEPERM, TPEPROTO, TPESVCERR, TPESVCFAIL, TPESYSTEM, TPETIME, TPETRAN, TPGOTSIG, TPERMERR, TPEITYPE, TPEOTYPE, TPERELEASE, TPEHAZARD, TPEHEURISTIC, TPEEVENT, TPEMATCH, TPEDIAGNOSTIC, TPEMIB };
        typedef ATMIerrors & ATMIerrors_out ;
        static const ::CORBA::TypeCode_ptr _tc_ATMIerrors;
        class EXPDLL_LIBENV OTSImpl
        {
            public:
                class	DelegatedCurrent;
                typedef	DelegatedCurrent *	DelegatedCurrent_ptr;
                class DelegatedCurrent_out;

                class EXPDLL_LIBENV DelegatedCurrent_var : public ::CORBA::_var {
                    public:
                        DelegatedCurrent_var();
                        inline DelegatedCurrent_var(DelegatedCurrent_ptr p) {ptr_ = p; }
                        DelegatedCurrent_var(const DelegatedCurrent_var &a);
                        ~DelegatedCurrent_var()
                            { free();}

                        DelegatedCurrent_var &operator=(DelegatedCurrent_ptr p)
                            { if (p != ptr_) reset(p);
                            return *this; }

                        DelegatedCurrent_var &operator=(const DelegatedCurrent_var &a);
                        inline DelegatedCurrent_ptr in () const { return ptr_; }
                        inline DelegatedCurrent_ptr & inout () { return ptr_; }
                        DelegatedCurrent_ptr & out ();
                        DelegatedCurrent_ptr _retn ();

                        inline operator DelegatedCurrent_ptr&() { return ptr_; }
                        inline operator const DelegatedCurrent_ptr&() const { return ptr_; }
                        inline DelegatedCurrent_ptr operator->() const { return ptr_; }

                        inline DelegatedCurrent_ptr & ptr () { return ptr_; }
                    protected:
                        DelegatedCurrent_ptr ptr_;
                        void free();
                        void reset(DelegatedCurrent_ptr p) { free(); ptr_ = p; }

                    private:
                        void operator=(const ::CORBA::_var &);
                };  // class DelegatedCurrent_var




                enum TxStatus { TX_ERROR, TX_NO_TRANSACTION, TX_ACTIVE, TX_TIMEOUT_ROLLBACK_ONLY, TX_ROLLBACK_ONLY };
                typedef TxStatus & TxStatus_out ;
                static const ::CORBA::TypeCode_ptr _tc_TxStatus;


                class EXPDLL_LIBENV cntl
                {
                    public:
                        cntl();

                        cntl(::CORBA::ULong _max);

                        cntl
                        (
                            ::CORBA::ULong _max,
                            ::CORBA::ULong _length,
                            ::CORBA::Octet *_value,
                            ::CORBA::Boolean _relse = CORBA_FALSE
                        );

                        cntl(const cntl &_ptr);

                        ~cntl();

                        cntl &operator=(const cntl& _ptr);

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
                };  // class cntl

                typedef	cntl *	cntl_ptr;
                class EXPDLL_LIBENV cntl_var
                {
                    public:
                        inline cntl_var() {_ptr = 0;}
                        inline cntl_var(cntl *_obj) {_ptr = _obj;}
                        cntl_var(const cntl_var &_obj) {_ptr = 0; *this = _obj;}
                        ~cntl_var();
                        cntl_var &operator=(cntl *);
                        cntl_var &operator=(const cntl_var &);
                        inline ::CORBA::Octet &operator[](::CORBA::ULong _index) {return (*_ptr)[_index];}
                        inline cntl *operator->() {return _ptr;}
                        inline const cntl *operator->() const {return _ptr;}
                        inline const cntl & in () const { return *_ptr; }
                        inline cntl & inout () { return *_ptr; }
                        cntl *& out ()
                        {
                            delete _ptr;
                            _ptr=0;
                            return _ptr;
                        }
                        cntl * _retn ()
                        {
                            cntl *tmp = _ptr;
                            _ptr = 0;
                            return tmp;
                        }
                        inline cntl_ptr & ptr() { return _ptr; }
                        inline operator cntl&() { return *_ptr; }
                        inline operator const cntl&() const { return *_ptr; }
                        inline operator cntl_ptr &() { return _ptr; }
                    private:
                        cntl *_ptr;
                };  // class cntl_var

                class EXPDLL_LIBENV cntl_out
                {
                    public:
                        cntl_out (cntl *& p) : ptr_(p) { ptr_ = 0; }
                        cntl_out (cntl_var &p) : ptr_(p.ptr()) {
                            delete ptr_; ptr_ = 0; }
                        cntl_out (const cntl_out & a) : ptr_(a.ptr_) {}
                        cntl_out & operator=(const cntl_out & a) {
                            ptr_ = a.ptr_; return *this; }
                        cntl_out & operator=(cntl * p) {
                            ptr_ = p; return *this; }
                        inline operator cntl_ptr & () { return ptr_; }
                        inline cntl_ptr & ptr () { return ptr_; }
                        inline cntl_ptr operator->() { return ptr_; }
                        inline ::CORBA::Octet & operator[](::CORBA::ULong _index) {return (*ptr_)[_index]; }
                    private:
                        cntl_ptr & ptr_;
                        void operator=(const cntl_var &);

                };  // class cntl_out
                static const ::CORBA::TypeCode_ptr _tc_cntl;


                static const ::CORBA::TypeCode_ptr _tc_DelegatedCurrent;
                class EXPDLL_LIBENV DelegatedCurrent : public virtual ::CORBA::Object
                 {
                    public:
                        static DelegatedCurrent_ptr _duplicate(DelegatedCurrent_ptr obj) 
                            {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                            return obj;}
                        static DelegatedCurrent_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                        inline static DelegatedCurrent_ptr _nil() { return 0; }
                        static const char* _get_interface_name ();

                        virtual ATMIerrors begin (
                            ::CORBA::ULong seconds); 

                        virtual ATMIerrors commit (
                            ::CORBA::Boolean report_heuristic); 

                        virtual ATMIerrors rollback (); 

                        virtual ATMIerrors rollback_only (); 

                        virtual ATMIerrors get_status (
                            TxStatus_out status); 

                        virtual ATMIerrors get_transaction_name (
                            ::CORBA::String_out name); 

                        virtual ATMIerrors suspend (
                            cntl_out which); 

                        virtual ATMIerrors resume (
                             const cntl & which); 

                        virtual ATMIerrors get_control (
                            cntl_out which); 

                    protected:
                        DelegatedCurrent(::CORBA::Object_ptr obj = 0);
                        virtual ~DelegatedCurrent(){ }

                    private:
                        DelegatedCurrent( const DelegatedCurrent&) { }
                        void operator=(const DelegatedCurrent&) { }
                        ::CORBA::ORB_ptr pORB;
                };  // class DelegatedCurrent



                class EXPDLL_LIBENV DelegatedCurrent_out
                 {
                    public:
                        DelegatedCurrent_out (DelegatedCurrent_ptr & p);
                        DelegatedCurrent_out (DelegatedCurrent_var & p);
                        DelegatedCurrent_out (const DelegatedCurrent_out & p) : ptr_(p.ptr_) {}
                        DelegatedCurrent_out & operator=(const DelegatedCurrent_out & a) {
                            ptr_ = a.ptr_; return *this;}
                        DelegatedCurrent_out & operator=(const DelegatedCurrent_var & a);
                        DelegatedCurrent_out & operator=(DelegatedCurrent_ptr p) {
                        ptr_ = p; return *this;}
                        inline operator DelegatedCurrent_ptr & () { return ptr_; }
                        inline DelegatedCurrent_ptr & ptr () { return ptr_; }
                        inline DelegatedCurrent_ptr operator->() { return ptr_; }
                    private:
                        DelegatedCurrent_ptr & ptr_;
                };  // class DelegatedCurrent_out

            };  // class OTSImpl

            class EXPDLL_LIBENV SecImpl
            {
                public:
                    class	DelegatedAuthenticator;
                    typedef	DelegatedAuthenticator *	DelegatedAuthenticator_ptr;
                    class DelegatedAuthenticator_out;

                    class EXPDLL_LIBENV DelegatedAuthenticator_var : public ::CORBA::_var {
                        public:
                            DelegatedAuthenticator_var();
                            inline DelegatedAuthenticator_var(DelegatedAuthenticator_ptr p) {ptr_ = p; }
                            DelegatedAuthenticator_var(const DelegatedAuthenticator_var &a);
                            ~DelegatedAuthenticator_var()
                                { free();}

                            DelegatedAuthenticator_var &operator=(DelegatedAuthenticator_ptr p)
                                { if (p != ptr_) reset(p);
                                return *this; }

                            DelegatedAuthenticator_var &operator=(const DelegatedAuthenticator_var &a);
                            inline DelegatedAuthenticator_ptr in () const { return ptr_; }
                            inline DelegatedAuthenticator_ptr & inout () { return ptr_; }
                            DelegatedAuthenticator_ptr & out ();
                            DelegatedAuthenticator_ptr _retn ();

                            inline operator DelegatedAuthenticator_ptr&() { return ptr_; }
                            inline operator const DelegatedAuthenticator_ptr&() const { return ptr_; }
                            inline DelegatedAuthenticator_ptr operator->() const { return ptr_; }

                            inline DelegatedAuthenticator_ptr & ptr () { return ptr_; }
                        protected:
                            DelegatedAuthenticator_ptr ptr_;
                            void free();
                            void reset(DelegatedAuthenticator_ptr p) { free(); ptr_ = p; }

                        private:
                            void operator=(const ::CORBA::_var &);
                    };  // class DelegatedAuthenticator_var




                    static const ::CORBA::TypeCode_ptr _tc_DelegatedAuthenticator;
                    class EXPDLL_LIBENV DelegatedAuthenticator : public virtual ::CORBA::Object
                     {
                        public:
                            static DelegatedAuthenticator_ptr _duplicate(DelegatedAuthenticator_ptr obj) 
                                {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                                return obj;}
                            static DelegatedAuthenticator_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                            inline static DelegatedAuthenticator_ptr _nil() { return 0; }
                            static const char* _get_interface_name ();

                            virtual ATMIerrors get_auth (
                                ::Tobj::AuthType_out type); 

                            virtual ATMIerrors logon (
                                const char * user_name,
                                const char * client_name,
                                 const ::Tobj::UserAuthData & user_data,
                                 const ::Tobj::LogonData & logon_data); 

                            virtual ATMIerrors logoff (); 

                        protected:
                            DelegatedAuthenticator(::CORBA::Object_ptr obj = 0);
                            virtual ~DelegatedAuthenticator(){ }

                        private:
                            DelegatedAuthenticator( const DelegatedAuthenticator&) { }
                            void operator=(const DelegatedAuthenticator&) { }
                            ::CORBA::ORB_ptr pORB;
                    };  // class DelegatedAuthenticator



                    class EXPDLL_LIBENV DelegatedAuthenticator_out
                     {
                        public:
                            DelegatedAuthenticator_out (DelegatedAuthenticator_ptr & p);
                            DelegatedAuthenticator_out (DelegatedAuthenticator_var & p);
                            DelegatedAuthenticator_out (const DelegatedAuthenticator_out & p) : ptr_(p.ptr_) {}
                            DelegatedAuthenticator_out & operator=(const DelegatedAuthenticator_out & a) {
                                ptr_ = a.ptr_; return *this;}
                            DelegatedAuthenticator_out & operator=(const DelegatedAuthenticator_var & a);
                            DelegatedAuthenticator_out & operator=(DelegatedAuthenticator_ptr p) {
                            ptr_ = p; return *this;}
                            inline operator DelegatedAuthenticator_ptr & () { return ptr_; }
                            inline DelegatedAuthenticator_ptr & ptr () { return ptr_; }
                            inline DelegatedAuthenticator_ptr operator->() { return ptr_; }
                        private:
                            DelegatedAuthenticator_ptr & ptr_;
                    };  // class DelegatedAuthenticator_out

                };  // class SecImpl

                class EXPDLL_LIBENV CallbackImpl
                {
                    public:
                        class	DelegatedBiDir;
                        typedef	DelegatedBiDir *	DelegatedBiDir_ptr;
                        class DelegatedBiDir_out;

                        class EXPDLL_LIBENV DelegatedBiDir_var : public ::CORBA::_var {
                            public:
                                DelegatedBiDir_var();
                                inline DelegatedBiDir_var(DelegatedBiDir_ptr p) {ptr_ = p; }
                                DelegatedBiDir_var(const DelegatedBiDir_var &a);
                                ~DelegatedBiDir_var()
                                    { free();}

                                DelegatedBiDir_var &operator=(DelegatedBiDir_ptr p)
                                    { if (p != ptr_) reset(p);
                                    return *this; }

                                DelegatedBiDir_var &operator=(const DelegatedBiDir_var &a);
                                inline DelegatedBiDir_ptr in () const { return ptr_; }
                                inline DelegatedBiDir_ptr & inout () { return ptr_; }
                                DelegatedBiDir_ptr & out ();
                                DelegatedBiDir_ptr _retn ();

                                inline operator DelegatedBiDir_ptr&() { return ptr_; }
                                inline operator const DelegatedBiDir_ptr&() const { return ptr_; }
                                inline DelegatedBiDir_ptr operator->() const { return ptr_; }

                                inline DelegatedBiDir_ptr & ptr () { return ptr_; }
                            protected:
                                DelegatedBiDir_ptr ptr_;
                                void free();
                                void reset(DelegatedBiDir_ptr p) { free(); ptr_ = p; }

                            private:
                                void operator=(const ::CORBA::_var &);
                        };  // class DelegatedBiDir_var




                        static const ::CORBA::TypeCode_ptr _tc_DelegatedBiDir;
                        class EXPDLL_LIBENV DelegatedBiDir : public virtual ::CORBA::Object
                         {
                            public:
                                static DelegatedBiDir_ptr _duplicate(DelegatedBiDir_ptr obj) 
                                    {if (! ::CORBA::is_nil(obj)) obj->OBB__increment_refcount();
                                    return obj;}
                                static DelegatedBiDir_ptr _narrow(::CORBA::Object_ptr obj, ::CORBA::Boolean isa = CORBA_TRUE);
                                inline static DelegatedBiDir_ptr _nil() { return 0; }
                                static const char* _get_interface_name ();

                                virtual void register_callback_port (
                                    ::CORBA::Object_ptr objref); 

                            protected:
                                DelegatedBiDir(::CORBA::Object_ptr obj = 0);
                                virtual ~DelegatedBiDir(){ }

                            private:
                                DelegatedBiDir( const DelegatedBiDir&) { }
                                void operator=(const DelegatedBiDir&) { }
                                ::CORBA::ORB_ptr pORB;
                        };  // class DelegatedBiDir



                        class EXPDLL_LIBENV DelegatedBiDir_out
                         {
                            public:
                                DelegatedBiDir_out (DelegatedBiDir_ptr & p);
                                DelegatedBiDir_out (DelegatedBiDir_var & p);
                                DelegatedBiDir_out (const DelegatedBiDir_out & p) : ptr_(p.ptr_) {}
                                DelegatedBiDir_out & operator=(const DelegatedBiDir_out & a) {
                                    ptr_ = a.ptr_; return *this;}
                                DelegatedBiDir_out & operator=(const DelegatedBiDir_var & a);
                                DelegatedBiDir_out & operator=(DelegatedBiDir_ptr p) {
                                ptr_ = p; return *this;}
                                inline operator DelegatedBiDir_ptr & () { return ptr_; }
                                inline DelegatedBiDir_ptr & ptr () { return ptr_; }
                                inline DelegatedBiDir_ptr operator->() { return ptr_; }
                            private:
                                DelegatedBiDir_ptr & ptr_;
                        };  // class DelegatedBiDir_out

                    };  // class CallbackImpl

                };  // class TobjInternal

void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::TobjInternal::Version &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::Version *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::Version *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::TobjInternal::InitRef &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::InitRef *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::InitRef *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::TobjInternal::InitRefList &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::InitRefList *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::InitRefList *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::TobjInternal::InitObjRef &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::InitObjRef *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::InitObjRef *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::TobjInternal::InitObjRefList &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::InitObjRefList *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::InitObjRefList *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::TobjInternal::ObjectIdList &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::ObjectIdList *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::ObjectIdList *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::InitialReferences_ptr obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::InitialReferences_ptr &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::ATMIerrors obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::ATMIerrors &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::OTSImpl::TxStatus obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::OTSImpl::TxStatus &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, const ::TobjInternal::OTSImpl::cntl &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::OTSImpl::cntl *obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::OTSImpl::cntl *&obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::OTSImpl::DelegatedCurrent_ptr obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::OTSImpl::DelegatedCurrent_ptr &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::SecImpl::DelegatedAuthenticator_ptr obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::SecImpl::DelegatedAuthenticator_ptr &obj);
void EXPDLL_LIBENV operator<<=(::CORBA::Any &a, ::TobjInternal::CallbackImpl::DelegatedBiDir_ptr obj);
::CORBA::Boolean EXPDLL_LIBENV operator>>=(const ::CORBA::Any &a, ::TobjInternal::CallbackImpl::DelegatedBiDir_ptr &obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::Version &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::Version &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::InitRef &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::InitRef &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::InitRefList &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::InitRefList &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::InitObjRef &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::InitObjRef &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::InitObjRefList &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::InitObjRefList &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::ObjectIdList &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::ObjectIdList &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &mb, TobjInternal::InitialReferences_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::InitialReferences_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::InitialReferences_var &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::ATMIerrors &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::ATMIerrors &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::OTSImpl::TxStatus &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::OTSImpl::TxStatus &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &, ::TobjInternal::OTSImpl::cntl &);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &, ::TobjInternal::OTSImpl::cntl &);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &mb, TobjInternal::OTSImpl::DelegatedCurrent_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::OTSImpl::DelegatedCurrent_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::OTSImpl::DelegatedCurrent_var &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &mb, TobjInternal::SecImpl::DelegatedAuthenticator_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::SecImpl::DelegatedAuthenticator_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::SecImpl::DelegatedAuthenticator_var &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator<<(OBB::MarshalBuf &mb, TobjInternal::CallbackImpl::DelegatedBiDir_ptr _obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::CallbackImpl::DelegatedBiDir_ptr &_obj);
OBB::MarshalBuf EXPDLL_LIBENV &operator>>(OBB::MarshalBuf &mb, TobjInternal::CallbackImpl::DelegatedBiDir_var &_obj);
#ifdef ORB_IMPORT_DEFINED_tobjin_c
#undef ORB_IMPORT_DEFINED_tobjin_c
#undef EXPDLL_LIBENV
#endif
#endif

