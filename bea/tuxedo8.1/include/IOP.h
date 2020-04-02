/*    Copyright (c) 1999 BEA Systems, Inc.                 */
/*    All Rights Reserved                                  */

/*    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF       */
/*    BEA Systems, Inc.                                    */
/*    The copyright notice above does not evidence any     */
/*    actual or intended publication of such source code.  */

/*
 * This module contains definitions and prototypes
 * for the data structures needed for IOP structures
 * used by request level interceptors.
 *
 */

#ifndef _IOP_h
#define _IOP_h

#include <string.h>
#include <CORBA.h>

class OBBEXPDLL IOP 
{
    public:
        typedef CORBA::ULong ProfileId;
        typedef CORBA::ULong_out ProfileId_out;
        static const CORBA::TypeCode_ptr _tc_ProfileId;
        static const ProfileId TAG_INTERNET_IOP ;
        static const ProfileId TAG_MULTIPLE_COMPONENTS ;


        struct  TaggedProfile {
             ProfileId tag;


            class OBBEXPDLL _1_profile_data
            {
                public:
                    _1_profile_data();

                    _1_profile_data(CORBA::ULong _max);

                    _1_profile_data
                    (
                        CORBA::ULong _max,
                        CORBA::ULong _length,
                        CORBA::Octet *_value,
                        CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_profile_data(const _1_profile_data &_ptr);

                    ~_1_profile_data();

                    _1_profile_data &operator=(const _1_profile_data& _ptr);

                    inline CORBA::ULong maximum() const {return _maximum;}

                    void length(CORBA::ULong);
                    inline CORBA::ULong length() const {return _current;}

                    inline CORBA::Octet &operator[](CORBA::ULong _index) {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    inline const CORBA::Octet &operator[](CORBA::ULong _index) const {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    static CORBA::Octet *allocbuf(CORBA::ULong _nelems);
                    static void freebuf(CORBA::Octet *_ptr);

                    inline CORBA::Octet * OBB__GetData() { return _data; }
                private:
                    CORBA::Octet *_data;
                    CORBA::ULong _maximum;
                    CORBA::ULong _current;
                    CORBA::Boolean _release;
            };  // class _1_profile_data

             _1_profile_data profile_data;
            TaggedProfile &operator=(const TaggedProfile &_obj);
        };
        typedef	TaggedProfile *	TaggedProfile_ptr;
        class OBBEXPDLL TaggedProfile_var
        {
            public:
                inline TaggedProfile_var() {_ptr = 0;}
                inline TaggedProfile_var(TaggedProfile *_obj) {_ptr = _obj;}
                TaggedProfile_var(const TaggedProfile_var &_obj) {_ptr = 0; *this = _obj;}
                ~TaggedProfile_var();
                TaggedProfile_var &operator=(TaggedProfile *);
                TaggedProfile_var &operator=(const TaggedProfile_var &);
                inline TaggedProfile *operator->() {return _ptr;}
                inline const TaggedProfile *operator->() const {return _ptr;}
                inline const TaggedProfile & in () const { return *_ptr; }
                inline TaggedProfile & inout () { return *_ptr; }
                TaggedProfile *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                TaggedProfile * _retn ()
                {
                    TaggedProfile *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline TaggedProfile_ptr & ptr() { return _ptr; }
                inline operator TaggedProfile&() { return *_ptr; }
                inline operator const TaggedProfile&() const { return *_ptr; }
                inline operator TaggedProfile_ptr &() { return _ptr; }
            private:
                TaggedProfile *_ptr;
        };  // class TaggedProfile_var

        class OBBEXPDLL TaggedProfile_out
        {
            public:
                TaggedProfile_out (TaggedProfile *& p) : ptr_(p) { ptr_ = 0; }
                TaggedProfile_out (TaggedProfile_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                TaggedProfile_out (const TaggedProfile_out & a) : ptr_(a.ptr_) {}
                TaggedProfile_out & operator=(const TaggedProfile_out & a) {
                    ptr_ = a.ptr_; return *this; }
                TaggedProfile_out & operator=(TaggedProfile * p) {
                    ptr_ = p; return *this; }
                inline operator TaggedProfile_ptr & () { return ptr_; }
                inline TaggedProfile_ptr & ptr () { return ptr_; }
                inline TaggedProfile_ptr operator->() { return ptr_; }
            private:
                TaggedProfile_ptr & ptr_;
                void operator=(const TaggedProfile_var &);

        };  // class TaggedProfile_out
        static const CORBA::TypeCode_ptr _tc_TaggedProfile;


        struct  IOR {
            CORBA::String_var type_id;


            class OBBEXPDLL _1_profiles
            {
                public:
                    _1_profiles();

                    _1_profiles(CORBA::ULong _max);

                    _1_profiles
                    (
                        CORBA::ULong _max,
                        CORBA::ULong _length,
                        TaggedProfile *_value,
                        CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_profiles(const _1_profiles &_ptr);

                    ~_1_profiles();

                    _1_profiles &operator=(const _1_profiles& _ptr);

                    inline CORBA::ULong maximum() const {return _maximum;}

                    void length(CORBA::ULong);
                    inline CORBA::ULong length() const {return _current;}

                    inline TaggedProfile &operator[](CORBA::ULong _index) {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    inline const TaggedProfile &operator[](CORBA::ULong _index) const {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    static TaggedProfile *allocbuf(CORBA::ULong _nelems);
                    static void freebuf(TaggedProfile *_ptr);

                    inline TaggedProfile * OBB__GetData() { return _data; }
                private:
                    TaggedProfile *_data;
                    CORBA::ULong _maximum;
                    CORBA::ULong _current;
                    CORBA::Boolean _release;
            };  // class _1_profiles

             _1_profiles profiles;
            IOR &operator=(const IOR &_obj);
        };
        typedef	IOR *	IOR_ptr;
        class OBBEXPDLL IOR_var
        {
            public:
                inline IOR_var() {_ptr = 0;}
                inline IOR_var(IOR *_obj) {_ptr = _obj;}
                IOR_var(const IOR_var &_obj) {_ptr = 0; *this = _obj;}
                ~IOR_var();
                IOR_var &operator=(IOR *);
                IOR_var &operator=(const IOR_var &);
                inline IOR *operator->() {return _ptr;}
                inline const IOR *operator->() const {return _ptr;}
                inline const IOR & in () const { return *_ptr; }
                inline IOR & inout () { return *_ptr; }
                IOR *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                IOR * _retn ()
                {
                    IOR *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline IOR_ptr & ptr() { return _ptr; }
                inline operator IOR&() { return *_ptr; }
                inline operator const IOR&() const { return *_ptr; }
                inline operator IOR_ptr &() { return _ptr; }
            private:
                IOR *_ptr;
        };  // class IOR_var

        class OBBEXPDLL IOR_out
        {
            public:
                IOR_out (IOR *& p) : ptr_(p) { ptr_ = 0; }
                IOR_out (IOR_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                IOR_out (const IOR_out & a) : ptr_(a.ptr_) {}
                IOR_out & operator=(const IOR_out & a) {
                    ptr_ = a.ptr_; return *this; }
                IOR_out & operator=(IOR * p) {
                    ptr_ = p; return *this; }
                inline operator IOR_ptr & () { return ptr_; }
                inline IOR_ptr & ptr () { return ptr_; }
                inline IOR_ptr operator->() { return ptr_; }
            private:
                IOR_ptr & ptr_;
                void operator=(const IOR_var &);

        };  // class IOR_out
        static const CORBA::TypeCode_ptr _tc_IOR;
        typedef CORBA::ULong ComponentId;
        typedef CORBA::ULong_out ComponentId_out;
        static const CORBA::TypeCode_ptr _tc_ComponentId;


        struct  TaggedComponent {
             ComponentId tag;


            class OBBEXPDLL _1_component_data
            {
                public:
                    _1_component_data();

                    _1_component_data(CORBA::ULong _max);

                    _1_component_data
                    (
                        CORBA::ULong _max,
                        CORBA::ULong _length,
                        CORBA::Octet *_value,
                        CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_component_data(const _1_component_data &_ptr);

                    ~_1_component_data();

                    _1_component_data &operator=(const _1_component_data& _ptr);

                    inline CORBA::ULong maximum() const {return _maximum;}

                    void length(CORBA::ULong);
                    inline CORBA::ULong length() const {return _current;}

                    inline CORBA::Octet &operator[](CORBA::ULong _index) {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    inline const CORBA::Octet &operator[](CORBA::ULong _index) const {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    static CORBA::Octet *allocbuf(CORBA::ULong _nelems);
                    static void freebuf(CORBA::Octet *_ptr);

                    inline CORBA::Octet * OBB__GetData() { return _data; }
                private:
                    CORBA::Octet *_data;
                    CORBA::ULong _maximum;
                    CORBA::ULong _current;
                    CORBA::Boolean _release;
            };  // class _1_component_data

             _1_component_data component_data;
            TaggedComponent &operator=(const TaggedComponent &_obj);
        };
        typedef	TaggedComponent *	TaggedComponent_ptr;
        class OBBEXPDLL TaggedComponent_var
        {
            public:
                inline TaggedComponent_var() {_ptr = 0;}
                inline TaggedComponent_var(TaggedComponent *_obj) {_ptr = _obj;}
                TaggedComponent_var(const TaggedComponent_var &_obj) {_ptr = 0; *this = _obj;}
                ~TaggedComponent_var();
                TaggedComponent_var &operator=(TaggedComponent *);
                TaggedComponent_var &operator=(const TaggedComponent_var &);
                inline TaggedComponent *operator->() {return _ptr;}
                inline const TaggedComponent *operator->() const {return _ptr;}
                inline const TaggedComponent & in () const { return *_ptr; }
                inline TaggedComponent & inout () { return *_ptr; }
                TaggedComponent *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                TaggedComponent * _retn ()
                {
                    TaggedComponent *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline TaggedComponent_ptr & ptr() { return _ptr; }
                inline operator TaggedComponent&() { return *_ptr; }
                inline operator const TaggedComponent&() const { return *_ptr; }
                inline operator TaggedComponent_ptr &() { return _ptr; }
            private:
                TaggedComponent *_ptr;
        };  // class TaggedComponent_var

        class OBBEXPDLL TaggedComponent_out
        {
            public:
                TaggedComponent_out (TaggedComponent *& p) : ptr_(p) { ptr_ = 0; }
                TaggedComponent_out (TaggedComponent_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                TaggedComponent_out (const TaggedComponent_out & a) : ptr_(a.ptr_) {}
                TaggedComponent_out & operator=(const TaggedComponent_out & a) {
                    ptr_ = a.ptr_; return *this; }
                TaggedComponent_out & operator=(TaggedComponent * p) {
                    ptr_ = p; return *this; }
                inline operator TaggedComponent_ptr & () { return ptr_; }
                inline TaggedComponent_ptr & ptr () { return ptr_; }
                inline TaggedComponent_ptr operator->() { return ptr_; }
            private:
                TaggedComponent_ptr & ptr_;
                void operator=(const TaggedComponent_var &);

        };  // class TaggedComponent_out
        static const CORBA::TypeCode_ptr _tc_TaggedComponent;


        class OBBEXPDLL MultipleComponentProfile
        {
            public:
                MultipleComponentProfile();

                MultipleComponentProfile(CORBA::ULong _max);

                MultipleComponentProfile
                (
                    CORBA::ULong _max,
                    CORBA::ULong _length,
                    TaggedComponent *_value,
                    CORBA::Boolean _relse = CORBA_FALSE
                );

                MultipleComponentProfile(const MultipleComponentProfile &_ptr);

                ~MultipleComponentProfile();

                MultipleComponentProfile &operator=(const MultipleComponentProfile& _ptr);

                inline CORBA::ULong maximum() const {return _maximum;}

                void length(CORBA::ULong);
                inline CORBA::ULong length() const {return _current;}

                inline TaggedComponent &operator[](CORBA::ULong _index) {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                inline const TaggedComponent &operator[](CORBA::ULong _index) const {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                static TaggedComponent *allocbuf(CORBA::ULong _nelems);
                static void freebuf(TaggedComponent *_ptr);

                inline TaggedComponent * OBB__GetData() { return _data; }
            private:
                TaggedComponent *_data;
                CORBA::ULong _maximum;
                CORBA::ULong _current;
                CORBA::Boolean _release;
        };  // class MultipleComponentProfile

        typedef	MultipleComponentProfile *	MultipleComponentProfile_ptr;
        class OBBEXPDLL MultipleComponentProfile_var
        {
            public:
                inline MultipleComponentProfile_var() {_ptr = 0;}
                inline MultipleComponentProfile_var(MultipleComponentProfile *_obj) {_ptr = _obj;}
                MultipleComponentProfile_var(const MultipleComponentProfile_var &_obj) {_ptr = 0; *this = _obj;}
                ~MultipleComponentProfile_var();
                MultipleComponentProfile_var &operator=(MultipleComponentProfile *);
                MultipleComponentProfile_var &operator=(const MultipleComponentProfile_var &);
                inline TaggedComponent &operator[](CORBA::ULong _index) {return (*_ptr)[_index];}
                inline MultipleComponentProfile *operator->() {return _ptr;}
                inline const MultipleComponentProfile *operator->() const {return _ptr;}
                inline const MultipleComponentProfile & in () const { return *_ptr; }
                inline MultipleComponentProfile & inout () { return *_ptr; }
                MultipleComponentProfile *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                MultipleComponentProfile * _retn ()
                {
                    MultipleComponentProfile *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline MultipleComponentProfile_ptr & ptr() { return _ptr; }
                inline operator MultipleComponentProfile&() { return *_ptr; }
                inline operator const MultipleComponentProfile&() const { return *_ptr; }
                inline operator MultipleComponentProfile_ptr &() { return _ptr; }
            private:
                MultipleComponentProfile *_ptr;
        };  // class MultipleComponentProfile_var

        class OBBEXPDLL MultipleComponentProfile_out
        {
            public:
                MultipleComponentProfile_out (MultipleComponentProfile *& p) : ptr_(p) { ptr_ = 0; }
                MultipleComponentProfile_out (MultipleComponentProfile_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                MultipleComponentProfile_out (const MultipleComponentProfile_out & a) : ptr_(a.ptr_) {}
                MultipleComponentProfile_out & operator=(const MultipleComponentProfile_out & a) {
                    ptr_ = a.ptr_; return *this; }
                MultipleComponentProfile_out & operator=(MultipleComponentProfile * p) {
                    ptr_ = p; return *this; }
                inline operator MultipleComponentProfile_ptr & () { return ptr_; }
                inline MultipleComponentProfile_ptr & ptr () { return ptr_; }
                inline MultipleComponentProfile_ptr operator->() { return ptr_; }
                inline TaggedComponent & operator[](CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                MultipleComponentProfile_ptr & ptr_;
                void operator=(const MultipleComponentProfile_var &);

        };  // class MultipleComponentProfile_out
        static const CORBA::TypeCode_ptr _tc_MultipleComponentProfile;
        static const ComponentId TAG_ORB_TYPE ;
        static const ComponentId TAG_CODE_SETS ;
        static const ComponentId TAG_POLICIES ;
        static const ComponentId TAG_ALTERNATE_IIOP_ADDRESS ;
        static const ComponentId TAG_ASSOCIATION_OPTIONS ;
        static const ComponentId TAG_SEC_NAME ;
        static const ComponentId TAG_SPKM_1_SEC_MECH ;
        static const ComponentId TAG_SPKM_2_SEC_MECH ;
        static const ComponentId TAG_KerberosV5_SEC_MECH ;
        static const ComponentId TAG_CSI_ECMA_Secret_SEC_MECH ;
        static const ComponentId TAG_CSI_ECMA_Hybrid_SEC_MECH ;
        static const ComponentId TAG_SSL_SEC_TRANS ;
        static const ComponentId TAG_CSI_ECMA_Public_SEC_MECH ;
        static const ComponentId TAG_GENERIC_SEC_MECH ;
        static const ComponentId TAG_COMPLETE_OBJECT_KEY ;
        static const ComponentId TAG_ENDPOINT_ID_POSITION ;
        static const ComponentId TAG_LOCATION_POLICY ;
        static const ComponentId TAG_DCE_STRING_BINDING ;
        static const ComponentId TAG_DCE_BINDING_NAME ;
        static const ComponentId TAG_DCE_NO_PIPES ;
        static const ComponentId TAG_DCE_SEC_MECH ;
	static const ComponentId TAG_WLS_CLUSTER_KEY ;
        typedef CORBA::ULong ServiceId;
        typedef CORBA::ULong_out ServiceId_out;
        static const CORBA::TypeCode_ptr _tc_ServiceId;


        struct  ServiceContext {
             ServiceId context_id;


            class OBBEXPDLL _1_context_data
            {
                public:
                    _1_context_data();

                    _1_context_data(CORBA::ULong _max);

                    _1_context_data
                    (
                        CORBA::ULong _max,
                        CORBA::ULong _length,
                        CORBA::Octet *_value,
                        CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_context_data(const _1_context_data &_ptr);

                    ~_1_context_data();

                    _1_context_data &operator=(const _1_context_data& _ptr);

                    inline CORBA::ULong maximum() const {return _maximum;}

                    void length(CORBA::ULong);
                    inline CORBA::ULong length() const {return _current;}

                    inline CORBA::Octet &operator[](CORBA::ULong _index) {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    inline const CORBA::Octet &operator[](CORBA::ULong _index) const {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                    static CORBA::Octet *allocbuf(CORBA::ULong _nelems);
                    static void freebuf(CORBA::Octet *_ptr);

                    inline CORBA::Octet * OBB__GetData() { return _data; }
                private:
                    CORBA::Octet *_data;
                    CORBA::ULong _maximum;
                    CORBA::ULong _current;
                    CORBA::Boolean _release;
            };  // class _1_context_data

             _1_context_data context_data;
            ServiceContext &operator=(const ServiceContext &_obj);
        };
        typedef	ServiceContext *	ServiceContext_ptr;
        class OBBEXPDLL ServiceContext_var
        {
            public:
                inline ServiceContext_var() {_ptr = 0;}
                inline ServiceContext_var(ServiceContext *_obj) {_ptr = _obj;}
                ServiceContext_var(const ServiceContext_var &_obj) {_ptr = 0; *this = _obj;}
                ~ServiceContext_var();
                ServiceContext_var &operator=(ServiceContext *);
                ServiceContext_var &operator=(const ServiceContext_var &);
                inline ServiceContext *operator->() {return _ptr;}
                inline const ServiceContext *operator->() const {return _ptr;}
                inline const ServiceContext & in () const { return *_ptr; }
                inline ServiceContext & inout () { return *_ptr; }
                ServiceContext *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ServiceContext * _retn ()
                {
                    ServiceContext *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ServiceContext_ptr & ptr() { return _ptr; }
                inline operator ServiceContext&() { return *_ptr; }
                inline operator const ServiceContext&() const { return *_ptr; }
                inline operator ServiceContext_ptr &() { return _ptr; }
            private:
                ServiceContext *_ptr;
        };  // class ServiceContext_var

        class OBBEXPDLL ServiceContext_out
        {
            public:
                ServiceContext_out (ServiceContext *& p) : ptr_(p) { ptr_ = 0; }
                ServiceContext_out (ServiceContext_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ServiceContext_out (const ServiceContext_out & a) : ptr_(a.ptr_) {}
                ServiceContext_out & operator=(const ServiceContext_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ServiceContext_out & operator=(ServiceContext * p) {
                    ptr_ = p; return *this; }
                inline operator ServiceContext_ptr & () { return ptr_; }
                inline ServiceContext_ptr & ptr () { return ptr_; }
                inline ServiceContext_ptr operator->() { return ptr_; }
            private:
                ServiceContext_ptr & ptr_;
                void operator=(const ServiceContext_var &);

        };  // class ServiceContext_out
        static const CORBA::TypeCode_ptr _tc_ServiceContext;


        class OBBEXPDLL ServiceContextList
        {
            public:
                ServiceContextList();

                ServiceContextList(CORBA::ULong _max);

                ServiceContextList
                (
                    CORBA::ULong _max,
                    CORBA::ULong _length,
                    ServiceContext *_value,
                    CORBA::Boolean _relse = CORBA_FALSE
                );

                ServiceContextList(const ServiceContextList &_ptr);

                ~ServiceContextList();

                ServiceContextList &operator=(const ServiceContextList& _ptr);

                inline CORBA::ULong maximum() const {return _maximum;}

                void length(CORBA::ULong);
                inline CORBA::ULong length() const {return _current;}

                inline ServiceContext &operator[](CORBA::ULong _index) {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                inline const ServiceContext &operator[](CORBA::ULong _index) const {if (_index > _maximum) throw CORBA::BAD_PARAM(); return _data[_index];}
                static ServiceContext *allocbuf(CORBA::ULong _nelems);
                static void freebuf(ServiceContext *_ptr);

                inline ServiceContext * OBB__GetData() { return _data; }
            private:
                ServiceContext *_data;
                CORBA::ULong _maximum;
                CORBA::ULong _current;
                CORBA::Boolean _release;
        };  // class ServiceContextList

        typedef	ServiceContextList *	ServiceContextList_ptr;
        class OBBEXPDLL ServiceContextList_var
        {
            public:
                inline ServiceContextList_var() {_ptr = 0;}
                inline ServiceContextList_var(ServiceContextList *_obj) {_ptr = _obj;}
                ServiceContextList_var(const ServiceContextList_var &_obj) {_ptr = 0; *this = _obj;}
                ~ServiceContextList_var();
                ServiceContextList_var &operator=(ServiceContextList *);
                ServiceContextList_var &operator=(const ServiceContextList_var &);
                inline ServiceContext &operator[](CORBA::ULong _index) {return (*_ptr)[_index];}
                inline ServiceContextList *operator->() {return _ptr;}
                inline const ServiceContextList *operator->() const {return _ptr;}
                inline const ServiceContextList & in () const { return *_ptr; }
                inline ServiceContextList & inout () { return *_ptr; }
                ServiceContextList *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ServiceContextList * _retn ()
                {
                    ServiceContextList *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ServiceContextList_ptr & ptr() { return _ptr; }
                inline operator ServiceContextList&() { return *_ptr; }
                inline operator const ServiceContextList&() const { return *_ptr; }
                inline operator ServiceContextList_ptr &() { return _ptr; }
            private:
                ServiceContextList *_ptr;
        };  // class ServiceContextList_var

        class OBBEXPDLL ServiceContextList_out
        {
            public:
                ServiceContextList_out (ServiceContextList *& p) : ptr_(p) { ptr_ = 0; }
                ServiceContextList_out (ServiceContextList_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ServiceContextList_out (const ServiceContextList_out & a) : ptr_(a.ptr_) {}
                ServiceContextList_out & operator=(const ServiceContextList_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ServiceContextList_out & operator=(ServiceContextList * p) {
                    ptr_ = p; return *this; }
                inline operator ServiceContextList_ptr & () { return ptr_; }
                inline ServiceContextList_ptr & ptr () { return ptr_; }
                inline ServiceContextList_ptr operator->() { return ptr_; }
                inline ServiceContext & operator[](CORBA::ULong _index) {return (*ptr_)[_index]; }
            private:
                ServiceContextList_ptr & ptr_;
                void operator=(const ServiceContextList_var &);

        };  // class ServiceContextList_out
        static const CORBA::TypeCode_ptr _tc_ServiceContextList;
        static const ServiceId TransactionService ;
        static const ServiceId CodeSets ;
        static const ServiceId ChainBypassCheck ;
        static const ServiceId ChainBypassInfo ;
        static const ServiceId LogicalThreadId ;
        static const ServiceId BI_DIR_IIOP ;
        static const ServiceId SendingContextRunTime ;
        static const ServiceId INVOCATION_POLICIES ;
        static const ServiceId UnknownExceptionInfo ;
};  // class IOP

void  operator<<=(CORBA::Any &a, const IOP::TaggedProfile &obj);
void  operator<<=(CORBA::Any &a, IOP::TaggedProfile *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, IOP::TaggedProfile *&obj);
void  operator<<=(CORBA::Any &a, const IOP::IOR &obj);
void  operator<<=(CORBA::Any &a, IOP::IOR *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, IOP::IOR *&obj);
void  operator<<=(CORBA::Any &a, const IOP::TaggedComponent &obj);
void  operator<<=(CORBA::Any &a, IOP::TaggedComponent *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, IOP::TaggedComponent *&obj);
void  operator<<=(CORBA::Any &a, const IOP::MultipleComponentProfile &obj);
void  operator<<=(CORBA::Any &a, IOP::MultipleComponentProfile *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, IOP::MultipleComponentProfile *&obj);
void  operator<<=(CORBA::Any &a, const IOP::ServiceContext &obj);
void  operator<<=(CORBA::Any &a, IOP::ServiceContext *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, IOP::ServiceContext *&obj);
void  operator<<=(CORBA::Any &a, const IOP::ServiceContextList &obj);
void  operator<<=(CORBA::Any &a, IOP::ServiceContextList *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, IOP::ServiceContextList *&obj);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, IOP::TaggedProfile &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, IOP::TaggedProfile &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, IOP::IOR &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, IOP::IOR &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, IOP::TaggedComponent &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, IOP::TaggedComponent &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, IOP::MultipleComponentProfile &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, IOP::MultipleComponentProfile &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, IOP::ServiceContext &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, IOP::ServiceContext &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, IOP::ServiceContextList &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, IOP::ServiceContextList &);

#endif /* _IOP_h */
