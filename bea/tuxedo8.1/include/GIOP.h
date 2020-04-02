/*    Copyright (c) 1999 BEA Systems, Inc.                 */
/*    All Rights Reserved                                  */

/*    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF       */
/*    BEA Systems, Inc.                                    */
/*    The copyright notice above does not evidence any     */
/*    actual or intended publication of such source code.  */

/*
 * This module contains definitions and prototypes
 * for the data structures needed for GIOP structures
 * used by request level interceptors.
 *
 */


#ifndef _GIOP_H
#define _GIOP_H

#include <string.h>
#include <CORBA.h>

#include "IOP.h"

class OBBEXPDLL GIOP
{
    public:
        struct  Version {
             CORBA::Octet major;
             CORBA::Octet minor;
        };
        typedef	Version *	Version_ptr;
        class OBBEXPDLL Version_var
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
        static const CORBA::TypeCode_ptr _tc_Version;

        enum MsgType_1_1 { Request, Reply, CancelRequest, LocateRequest, LocateReply, CloseConnection, MessageError, Fragment };
        typedef MsgType_1_1 & MsgType_1_1_out ;
        static const CORBA::TypeCode_ptr _tc_MsgType_1_1;

        struct  MessageHeader_1_0 {
            typedef CORBA::Char _1_magic[4];
            typedef CORBA::Char _1_magic_slice;
            typedef _1_magic_slice *_1_magic_slice_ptr;
            typedef const CORBA::Char _1_magic_slice_const;
            static _1_magic_slice * _1_magic_alloc(void);
            static _1_magic_slice * _1_magic_dup(const _1_magic_slice *);
            static void _1_magic_free(_1_magic_slice *data);
            class  _1_magic_forany  {
                private:
                    _1_magic_slice *_ptr;

                public:
                    _1_magic_forany();
                    _1_magic_forany(_1_magic_slice *, CORBA::Boolean _nocopy=CORBA_FALSE);
                    _1_magic_forany(const _1_magic_forany &);
                    ~_1_magic_forany();
                    _1_magic_forany &operator=(_1_magic_slice *);
                    _1_magic_forany &operator=(const _1_magic_forany &);
                    inline _1_magic_slice &  operator[](CORBA::ULong x) {return _ptr[x];}

                    inline

#ifndef _WIN32
                    const
#endif
                    _1_magic_slice &  operator[](CORBA::ULong x) const {return _ptr[x];}

                    const
                    _1_magic_slice * in () const { return (const _1_magic_slice *)_ptr; }
                    _1_magic_slice * inout () { return _ptr; }
                    _1_magic_slice * out () {
                         if (_ptr) _1_magic_free(_ptr);
                         _ptr = 0;
                         return _ptr;} 
                    _1_magic_slice * _retn () {
                         _1_magic_slice * tmp = _ptr;
                         _ptr = 0;
                         return tmp; }

                    inline _1_magic_slice_ptr &  ptr () { return _ptr; }
            };
             _1_magic magic;
             Version GIOP_version;
             CORBA::Boolean byte_order;
             CORBA::Octet message_type;
             CORBA::ULong message_size;
        };
        typedef	MessageHeader_1_0 *	MessageHeader_1_0_ptr;
        class OBBEXPDLL MessageHeader_1_0_var
        {
            public:
                inline MessageHeader_1_0_var() {_ptr = 0;}
                inline MessageHeader_1_0_var(MessageHeader_1_0 *_obj) {_ptr = _obj;}
                MessageHeader_1_0_var(const MessageHeader_1_0_var &_obj) {_ptr = 0; *this = _obj;}
                ~MessageHeader_1_0_var();
                MessageHeader_1_0_var &operator=(MessageHeader_1_0 *);
                MessageHeader_1_0_var &operator=(const MessageHeader_1_0_var &);
                inline MessageHeader_1_0 *operator->() {return _ptr;}
                inline const MessageHeader_1_0 *operator->() const {return _ptr;}
                inline const MessageHeader_1_0 & in () const { return *_ptr; }
                inline MessageHeader_1_0 & inout () { return *_ptr; }
                MessageHeader_1_0 & out ()
                {
                    MessageHeader_1_0 *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                MessageHeader_1_0 & _retn ()
                {
                    MessageHeader_1_0 *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline MessageHeader_1_0_ptr & ptr() { return _ptr; }
                inline operator MessageHeader_1_0&() { return *_ptr; }
                inline operator const MessageHeader_1_0&() const { return *_ptr; }
                inline operator MessageHeader_1_0_ptr &() { return _ptr; }
            private:
                MessageHeader_1_0 *_ptr;
        };  // class MessageHeader_1_0_var

        typedef MessageHeader_1_0& MessageHeader_1_0_out;
        static const CORBA::TypeCode_ptr _tc_MessageHeader_1_0;


        struct  MessageHeader_1_1 {


            typedef CORBA::Char _1_magic[4];
            typedef CORBA::Char _1_magic_slice;
            typedef _1_magic_slice *_1_magic_slice_ptr;
            typedef const CORBA::Char _1_magic_slice_const;
            static _1_magic_slice * _1_magic_alloc(void);
            static _1_magic_slice * _1_magic_dup(const _1_magic_slice *);
            static void _1_magic_free(_1_magic_slice *data);
            class OBBEXPDLL _1_magic_forany  {
                private:
                    _1_magic_slice *_ptr;

                public:
                    _1_magic_forany();
                    _1_magic_forany(_1_magic_slice *, CORBA::Boolean _nocopy=CORBA_FALSE);
                    _1_magic_forany(const _1_magic_forany &);
                    ~_1_magic_forany();
                    _1_magic_forany &operator=(_1_magic_slice *);
                    _1_magic_forany &operator=(const _1_magic_forany &);
                    inline _1_magic_slice &  operator[](CORBA::ULong x) {return _ptr[x];}

                    inline

#ifndef _WIN32
                    const
#endif
                    _1_magic_slice &  operator[](CORBA::ULong x) const {return _ptr[x];}

                    const
                    _1_magic_slice * in () const { return (const _1_magic_slice *)_ptr; }
                    _1_magic_slice * inout () { return _ptr; }
                    _1_magic_slice * out () {
                         if (_ptr) _1_magic_free(_ptr);
                         _ptr = 0;
                         return _ptr;} 
                    _1_magic_slice * _retn () {
                         _1_magic_slice * tmp = _ptr;
                         _ptr = 0;
                         return tmp; }

                    inline _1_magic_slice_ptr &  ptr () { return _ptr; }
            };
             _1_magic magic;
             Version GIOP_version;
             CORBA::Octet flags;
             CORBA::Octet message_type;
             CORBA::ULong message_size;
        };
        typedef	MessageHeader_1_1 *	MessageHeader_1_1_ptr;
        class OBBEXPDLL MessageHeader_1_1_var
        {
            public:
                inline MessageHeader_1_1_var() {_ptr = 0;}
                inline MessageHeader_1_1_var(MessageHeader_1_1 *_obj) {_ptr = _obj;}
                MessageHeader_1_1_var(const MessageHeader_1_1_var &_obj) {_ptr = 0; *this = _obj;}
                ~MessageHeader_1_1_var();
                MessageHeader_1_1_var &operator=(MessageHeader_1_1 *);
                MessageHeader_1_1_var &operator=(const MessageHeader_1_1_var &);
                inline MessageHeader_1_1 *operator->() {return _ptr;}
                inline const MessageHeader_1_1 *operator->() const {return _ptr;}
                inline const MessageHeader_1_1 & in () const { return *_ptr; }
                inline MessageHeader_1_1 & inout () { return *_ptr; }
                MessageHeader_1_1 & out ()
                {
                    MessageHeader_1_1 *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                MessageHeader_1_1 & _retn ()
                {
                    MessageHeader_1_1 *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline MessageHeader_1_1_ptr & ptr() { return _ptr; }
                inline operator MessageHeader_1_1&() { return *_ptr; }
                inline operator const MessageHeader_1_1&() const { return *_ptr; }
                inline operator MessageHeader_1_1_ptr &() { return _ptr; }
            private:
                MessageHeader_1_1 *_ptr;
        };  // class MessageHeader_1_1_var

        typedef MessageHeader_1_1& MessageHeader_1_1_out;
        static const CORBA::TypeCode_ptr _tc_MessageHeader_1_1;
        typedef MessageHeader_1_1 MessageHeader_1_2;
        typedef MessageHeader_1_1_out MessageHeader_1_2_out;
        typedef MessageHeader_1_1_var MessageHeader_1_2_var;
        static const CORBA::TypeCode_ptr _tc_MessageHeader_1_2;


        struct  RequestHeader_1_0 {


             IOP::ServiceContextList service_context;
             CORBA::ULong request_id;
             CORBA::Boolean response_expected;


            class OBBEXPDLL _1_object_key
            {
                public:
                    _1_object_key();

                    _1_object_key(CORBA::ULong _max);

                    _1_object_key
                    (
                        CORBA::ULong _max,
                        CORBA::ULong _length,
                        CORBA::Octet *_value,
                        CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_object_key(const _1_object_key &_ptr);

                    ~_1_object_key();

                    _1_object_key &operator=(const _1_object_key& _ptr);

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
            };  // class _1_object_key

             _1_object_key object_key;
            CORBA::String_var operation;


             CORBA::Principal_var requesting_principal;
            RequestHeader_1_0 &operator=(const RequestHeader_1_0 &_obj);
        };
        typedef	RequestHeader_1_0 *	RequestHeader_1_0_ptr;
        class OBBEXPDLL RequestHeader_1_0_var
        {
            public:
                inline RequestHeader_1_0_var() {_ptr = 0;}
                inline RequestHeader_1_0_var(RequestHeader_1_0 *_obj) {_ptr = _obj;}
                RequestHeader_1_0_var(const RequestHeader_1_0_var &_obj) {_ptr = 0; *this = _obj;}
                ~RequestHeader_1_0_var();
                RequestHeader_1_0_var &operator=(RequestHeader_1_0 *);
                RequestHeader_1_0_var &operator=(const RequestHeader_1_0_var &);
                inline RequestHeader_1_0 *operator->() {return _ptr;}
                inline const RequestHeader_1_0 *operator->() const {return _ptr;}
                inline const RequestHeader_1_0 & in () const { return *_ptr; }
                inline RequestHeader_1_0 & inout () { return *_ptr; }
                RequestHeader_1_0 *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                RequestHeader_1_0 * _retn ()
                {
                    RequestHeader_1_0 *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline RequestHeader_1_0_ptr & ptr() { return _ptr; }
                inline operator RequestHeader_1_0&() { return *_ptr; }
                inline operator const RequestHeader_1_0&() const { return *_ptr; }
                inline operator RequestHeader_1_0_ptr &() { return _ptr; }
            private:
                RequestHeader_1_0 *_ptr;
        };  // class RequestHeader_1_0_var

        class OBBEXPDLL RequestHeader_1_0_out
        {
            public:
                RequestHeader_1_0_out (RequestHeader_1_0 *& p) : ptr_(p) { ptr_ = 0; }
                RequestHeader_1_0_out (RequestHeader_1_0_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                RequestHeader_1_0_out (const RequestHeader_1_0_out & a) : ptr_(a.ptr_) {}
                RequestHeader_1_0_out & operator=(const RequestHeader_1_0_out & a) {
                    ptr_ = a.ptr_; return *this; }
                RequestHeader_1_0_out & operator=(RequestHeader_1_0 * p) {
                    ptr_ = p; return *this; }
                inline operator RequestHeader_1_0_ptr & () { return ptr_; }
                inline RequestHeader_1_0_ptr & ptr () { return ptr_; }
                inline RequestHeader_1_0_ptr operator->() { return ptr_; }
            private:
                RequestHeader_1_0_ptr & ptr_;
                void operator=(const RequestHeader_1_0_var &);

        };  // class RequestHeader_1_0_out
        static const CORBA::TypeCode_ptr _tc_RequestHeader_1_0;


        struct  RequestHeader_1_1 {


             IOP::ServiceContextList service_context;
             CORBA::ULong request_id;
             CORBA::Boolean response_expected;


            typedef CORBA::Octet _1_reserved[3];
            typedef CORBA::Octet _1_reserved_slice;
            typedef _1_reserved_slice *_1_reserved_slice_ptr;
            typedef const CORBA::Octet _1_reserved_slice_const;
            static _1_reserved_slice * _1_reserved_alloc(void);
            static _1_reserved_slice * _1_reserved_dup(const _1_reserved_slice *);
            static void _1_reserved_free(_1_reserved_slice *data);
            class OBBEXPDLL _1_reserved_forany  {
                private:
                    _1_reserved_slice *_ptr;

                public:
                    _1_reserved_forany();
                    _1_reserved_forany(_1_reserved_slice *, CORBA::Boolean _nocopy=CORBA_FALSE);
                    _1_reserved_forany(const _1_reserved_forany &);
                    ~_1_reserved_forany();
                    _1_reserved_forany &operator=(_1_reserved_slice *);
                    _1_reserved_forany &operator=(const _1_reserved_forany &);
                    inline _1_reserved_slice &  operator[](CORBA::ULong x) {return _ptr[x];}

                    inline

#ifndef _WIN32
                    const
#endif
                    _1_reserved_slice &  operator[](CORBA::ULong x) const {return _ptr[x];}

                    const
                    _1_reserved_slice * in () const { return (const _1_reserved_slice *)_ptr; }
                    _1_reserved_slice * inout () { return _ptr; }
                    _1_reserved_slice * out () {
                         if (_ptr) _1_reserved_free(_ptr);
                         _ptr = 0;
                         return _ptr;} 
                    _1_reserved_slice * _retn () {
                         _1_reserved_slice * tmp = _ptr;
                         _ptr = 0;
                         return tmp; }

                    inline _1_reserved_slice_ptr &  ptr () { return _ptr; }
            };
             _1_reserved reserved;


            class OBBEXPDLL _1_object_key
            {
                public:
                    _1_object_key();

                    _1_object_key(CORBA::ULong _max);

                    _1_object_key
                    (
                        CORBA::ULong _max,
                        CORBA::ULong _length,
                        CORBA::Octet *_value,
                        CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_object_key(const _1_object_key &_ptr);

                    ~_1_object_key();

                    _1_object_key &operator=(const _1_object_key& _ptr);

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
            };  // class _1_object_key

             _1_object_key object_key;
            CORBA::String_var operation;


             CORBA::Principal_var requesting_principal;
            RequestHeader_1_1 &operator=(const RequestHeader_1_1 &_obj);
        };
        typedef	RequestHeader_1_1 *	RequestHeader_1_1_ptr;
        class OBBEXPDLL RequestHeader_1_1_var
        {
            public:
                inline RequestHeader_1_1_var() {_ptr = 0;}
                inline RequestHeader_1_1_var(RequestHeader_1_1 *_obj) {_ptr = _obj;}
                RequestHeader_1_1_var(const RequestHeader_1_1_var &_obj) {_ptr = 0; *this = _obj;}
                ~RequestHeader_1_1_var();
                RequestHeader_1_1_var &operator=(RequestHeader_1_1 *);
                RequestHeader_1_1_var &operator=(const RequestHeader_1_1_var &);
                inline RequestHeader_1_1 *operator->() {return _ptr;}
                inline const RequestHeader_1_1 *operator->() const {return _ptr;}
                inline const RequestHeader_1_1 & in () const { return *_ptr; }
                inline RequestHeader_1_1 & inout () { return *_ptr; }
                RequestHeader_1_1 *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                RequestHeader_1_1 * _retn ()
                {
                    RequestHeader_1_1 *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline RequestHeader_1_1_ptr & ptr() { return _ptr; }
                inline operator RequestHeader_1_1&() { return *_ptr; }
                inline operator const RequestHeader_1_1&() const { return *_ptr; }
                inline operator RequestHeader_1_1_ptr &() { return _ptr; }
            private:
                RequestHeader_1_1 *_ptr;
        };  // class RequestHeader_1_1_var

        class OBBEXPDLL RequestHeader_1_1_out
        {
            public:
                RequestHeader_1_1_out (RequestHeader_1_1 *& p) : ptr_(p) { ptr_ = 0; }
                RequestHeader_1_1_out (RequestHeader_1_1_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                RequestHeader_1_1_out (const RequestHeader_1_1_out & a) : ptr_(a.ptr_) {}
                RequestHeader_1_1_out & operator=(const RequestHeader_1_1_out & a) {
                    ptr_ = a.ptr_; return *this; }
                RequestHeader_1_1_out & operator=(RequestHeader_1_1 * p) {
                    ptr_ = p; return *this; }
                inline operator RequestHeader_1_1_ptr & () { return ptr_; }
                inline RequestHeader_1_1_ptr & ptr () { return ptr_; }
                inline RequestHeader_1_1_ptr operator->() { return ptr_; }
            private:
                RequestHeader_1_1_ptr & ptr_;
                void operator=(const RequestHeader_1_1_var &);

        };  // class RequestHeader_1_1_out
        static const CORBA::TypeCode_ptr _tc_RequestHeader_1_1;
        typedef CORBA::Short AddressingDisposition;
        typedef CORBA::Short_out AddressingDisposition_out;
        static const CORBA::TypeCode_ptr _tc_AddressingDisposition;
        static const AddressingDisposition KeyAddr ;
        static const AddressingDisposition ProfileAddr ;
        static const AddressingDisposition ReferenceAddr ;


        struct  IORAddressingInfo {
             CORBA::ULong selected_profile_index;
             IOP::IOR ior;
            IORAddressingInfo &operator=(const IORAddressingInfo &_obj);
        };
        typedef	IORAddressingInfo *	IORAddressingInfo_ptr;
        class OBBEXPDLL IORAddressingInfo_var
        {
            public:
                inline IORAddressingInfo_var() {_ptr = 0;}
                inline IORAddressingInfo_var(IORAddressingInfo *_obj) {_ptr = _obj;}
                IORAddressingInfo_var(const IORAddressingInfo_var &_obj) {_ptr = 0; *this = _obj;}
                ~IORAddressingInfo_var();
                IORAddressingInfo_var &operator=(IORAddressingInfo *);
                IORAddressingInfo_var &operator=(const IORAddressingInfo_var &);
                inline IORAddressingInfo *operator->() {return _ptr;}
                inline const IORAddressingInfo *operator->() const {return _ptr;}
                inline const IORAddressingInfo & in () const { return *_ptr; }
                inline IORAddressingInfo & inout () { return *_ptr; }
                IORAddressingInfo *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                IORAddressingInfo * _retn ()
                {
                    IORAddressingInfo *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline IORAddressingInfo_ptr & ptr() { return _ptr; }
                inline operator IORAddressingInfo&() { return *_ptr; }
                inline operator const IORAddressingInfo&() const { return *_ptr; }
                inline operator IORAddressingInfo_ptr &() { return _ptr; }
            private:
                IORAddressingInfo *_ptr;
        };  // class IORAddressingInfo_var

        class OBBEXPDLL IORAddressingInfo_out
        {
            public:
                IORAddressingInfo_out (IORAddressingInfo *& p) : ptr_(p) { ptr_ = 0; }
                IORAddressingInfo_out (IORAddressingInfo_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                IORAddressingInfo_out (const IORAddressingInfo_out & a) : ptr_(a.ptr_) {}
                IORAddressingInfo_out & operator=(const IORAddressingInfo_out & a) {
                    ptr_ = a.ptr_; return *this; }
                IORAddressingInfo_out & operator=(IORAddressingInfo * p) {
                    ptr_ = p; return *this; }
                inline operator IORAddressingInfo_ptr & () { return ptr_; }
                inline IORAddressingInfo_ptr & ptr () { return ptr_; }
                inline IORAddressingInfo_ptr operator->() { return ptr_; }
            private:
                IORAddressingInfo_ptr & ptr_;
                void operator=(const IORAddressingInfo_var &);

        };  // class IORAddressingInfo_out
        static const CORBA::TypeCode_ptr _tc_IORAddressingInfo;


        class OBBEXPDLL TargetAddress
        {
            public:
                TargetAddress();
                TargetAddress( const TargetAddress &);
                ~TargetAddress();

                TargetAddress &operator=(const TargetAddress& _ptr);


                void  _d  ( AddressingDisposition);
                AddressingDisposition  _d  () const;

                void _default();


                class OBBEXPDLL _1_object_key
                {
                    public:
                        _1_object_key();

                        _1_object_key(CORBA::ULong _max);

                        _1_object_key
                        (
                            CORBA::ULong _max,
                            CORBA::ULong _length,
                            CORBA::Octet *_value,
                            CORBA::Boolean _relse = CORBA_FALSE
                        );

                        _1_object_key(const _1_object_key &_ptr);

                        ~_1_object_key();

                        _1_object_key &operator=(const _1_object_key& _ptr);

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
                };  // class _1_object_key

                void object_key (const _1_object_key &);
                const _1_object_key & object_key () const;
                _1_object_key & object_key ();

                void profile (const IOP::TaggedProfile &);
                const IOP::TaggedProfile & profile () const;
                IOP::TaggedProfile & profile ();

                void ior (const IORAddressingInfo &);
                const IORAddressingInfo & ior () const;
                IORAddressingInfo & ior ();

            private:
                CORBA::Boolean _disc_set;
                AddressingDisposition _discriminant;

                union _data {
                    _1_object_key * _object_key_elem;
                    IOP::TaggedProfile * _profile_elem;
                    IORAddressingInfo * _ior_elem;
                } _data;
                void _copy(const TargetAddress &);
                void _delete();

            };  // class TargetAddress

        typedef	TargetAddress *	TargetAddress_ptr;
        class OBBEXPDLL TargetAddress_var
        {
            public:
                inline TargetAddress_var() {_ptr = 0;}
                inline TargetAddress_var(TargetAddress *_obj) {_ptr = _obj;}
                TargetAddress_var(const TargetAddress_var &_obj) {_ptr = 0; *this = _obj;}
                ~TargetAddress_var();
                TargetAddress_var &operator=(TargetAddress *);
                TargetAddress_var &operator=(const TargetAddress_var &);
                inline TargetAddress *operator->() {return _ptr;}
                inline const TargetAddress *operator->() const {return _ptr;}
                inline const TargetAddress & in () const { return *_ptr; }
                inline TargetAddress & inout () { return *_ptr; }
                TargetAddress *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                TargetAddress * _retn ()
                {
                    TargetAddress *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline TargetAddress_ptr & ptr() { return _ptr; }
                inline operator TargetAddress&() { return *_ptr; }
                inline operator const TargetAddress&() const { return *_ptr; }
                inline operator TargetAddress_ptr &() { return _ptr; }
            private:
                TargetAddress *_ptr;
        };  // class TargetAddress_var

        class OBBEXPDLL TargetAddress_out
        {
            public:
                TargetAddress_out (TargetAddress *& p) : ptr_(p) { ptr_ = 0; }
                TargetAddress_out (TargetAddress_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                TargetAddress_out (const TargetAddress_out & a) : ptr_(a.ptr_) {}
                TargetAddress_out & operator=(const TargetAddress_out & a) {
                    ptr_ = a.ptr_; return *this; }
                TargetAddress_out & operator=(TargetAddress * p) {
                    ptr_ = p; return *this; }
                inline operator TargetAddress_ptr & () { return ptr_; }
                inline TargetAddress_ptr & ptr () { return ptr_; }
                inline TargetAddress_ptr operator->() { return ptr_; }
            private:
                TargetAddress_ptr & ptr_;
                void operator=(const TargetAddress_var &);

        };  // class TargetAddress_out
        static const CORBA::TypeCode_ptr _tc_TargetAddress;


        struct  RequestHeader_1_2 {
             CORBA::ULong request_id;
             CORBA::Octet response_flags;


            typedef CORBA::Octet _1_reserved[3];
            typedef CORBA::Octet _1_reserved_slice;
            typedef _1_reserved_slice *_1_reserved_slice_ptr;
            typedef const CORBA::Octet _1_reserved_slice_const;
            static _1_reserved_slice * _1_reserved_alloc(void);
            static _1_reserved_slice * _1_reserved_dup(const _1_reserved_slice *);
            static void _1_reserved_free(_1_reserved_slice *data);
            class OBBEXPDLL _1_reserved_forany  {
                private:
                    _1_reserved_slice *_ptr;

                public:
                    _1_reserved_forany();
                    _1_reserved_forany(_1_reserved_slice *, CORBA::Boolean _nocopy=CORBA_FALSE);
                    _1_reserved_forany(const _1_reserved_forany &);
                    ~_1_reserved_forany();
                    _1_reserved_forany &operator=(_1_reserved_slice *);
                    _1_reserved_forany &operator=(const _1_reserved_forany &);
                    inline _1_reserved_slice &  operator[](CORBA::ULong x) {return _ptr[x];}

                    inline

#ifndef _WIN32
                    const
#endif
                    _1_reserved_slice &  operator[](CORBA::ULong x) const {return _ptr[x];}

                    const
                    _1_reserved_slice * in () const { return (const _1_reserved_slice *)_ptr; }
                    _1_reserved_slice * inout () { return _ptr; }
                    _1_reserved_slice * out () {
                         if (_ptr) _1_reserved_free(_ptr);
                         _ptr = 0;
                         return _ptr;} 
                    _1_reserved_slice * _retn () {
                         _1_reserved_slice * tmp = _ptr;
                         _ptr = 0;
                         return tmp; }

                    inline _1_reserved_slice_ptr &  ptr () { return _ptr; }
            };
             _1_reserved reserved;


             TargetAddress target;
            CORBA::String_var operation;


             IOP::ServiceContextList service_context;
            RequestHeader_1_2 &operator=(const RequestHeader_1_2 &_obj);
        };
        typedef	RequestHeader_1_2 *	RequestHeader_1_2_ptr;
        class OBBEXPDLL RequestHeader_1_2_var
        {
            public:
                inline RequestHeader_1_2_var() {_ptr = 0;}
                inline RequestHeader_1_2_var(RequestHeader_1_2 *_obj) {_ptr = _obj;}
                RequestHeader_1_2_var(const RequestHeader_1_2_var &_obj) {_ptr = 0; *this = _obj;}
                ~RequestHeader_1_2_var();
                RequestHeader_1_2_var &operator=(RequestHeader_1_2 *);
                RequestHeader_1_2_var &operator=(const RequestHeader_1_2_var &);
                inline RequestHeader_1_2 *operator->() {return _ptr;}
                inline const RequestHeader_1_2 *operator->() const {return _ptr;}
                inline const RequestHeader_1_2 & in () const { return *_ptr; }
                inline RequestHeader_1_2 & inout () { return *_ptr; }
                RequestHeader_1_2 *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                RequestHeader_1_2 * _retn ()
                {
                    RequestHeader_1_2 *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline RequestHeader_1_2_ptr & ptr() { return _ptr; }
                inline operator RequestHeader_1_2&() { return *_ptr; }
                inline operator const RequestHeader_1_2&() const { return *_ptr; }
                inline operator RequestHeader_1_2_ptr &() { return _ptr; }
            private:
                RequestHeader_1_2 *_ptr;
        };  // class RequestHeader_1_2_var

        class OBBEXPDLL RequestHeader_1_2_out
        {
            public:
                RequestHeader_1_2_out (RequestHeader_1_2 *& p) : ptr_(p) { ptr_ = 0; }
                RequestHeader_1_2_out (RequestHeader_1_2_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                RequestHeader_1_2_out (const RequestHeader_1_2_out & a) : ptr_(a.ptr_) {}
                RequestHeader_1_2_out & operator=(const RequestHeader_1_2_out & a) {
                    ptr_ = a.ptr_; return *this; }
                RequestHeader_1_2_out & operator=(RequestHeader_1_2 * p) {
                    ptr_ = p; return *this; }
                inline operator RequestHeader_1_2_ptr & () { return ptr_; }
                inline RequestHeader_1_2_ptr & ptr () { return ptr_; }
                inline RequestHeader_1_2_ptr operator->() { return ptr_; }
            private:
                RequestHeader_1_2_ptr & ptr_;
                void operator=(const RequestHeader_1_2_var &);

        };  // class RequestHeader_1_2_out
        static const CORBA::TypeCode_ptr _tc_RequestHeader_1_2;


        enum ReplyStatusType_1_2 { NO_EXCEPTION, USER_EXCEPTION, SYSTEM_EXCEPTION, LOCATION_FORWARD, LOCATION_FORWARD_PERM, NEEDS_ADDRESSING_MODE };
        typedef ReplyStatusType_1_2 & ReplyStatusType_1_2_out ;
        static const CORBA::TypeCode_ptr _tc_ReplyStatusType_1_2;


        struct  ReplyHeader_1_2 {
             CORBA::ULong request_id;


             ReplyStatusType_1_2 reply_status;


             IOP::ServiceContextList service_context;
            ReplyHeader_1_2 &operator=(const ReplyHeader_1_2 &_obj);
        };
        typedef	ReplyHeader_1_2 *	ReplyHeader_1_2_ptr;
        class OBBEXPDLL ReplyHeader_1_2_var
        {
            public:
                inline ReplyHeader_1_2_var() {_ptr = 0;}
                inline ReplyHeader_1_2_var(ReplyHeader_1_2 *_obj) {_ptr = _obj;}
                ReplyHeader_1_2_var(const ReplyHeader_1_2_var &_obj) {_ptr = 0; *this = _obj;}
                ~ReplyHeader_1_2_var();
                ReplyHeader_1_2_var &operator=(ReplyHeader_1_2 *);
                ReplyHeader_1_2_var &operator=(const ReplyHeader_1_2_var &);
                inline ReplyHeader_1_2 *operator->() {return _ptr;}
                inline const ReplyHeader_1_2 *operator->() const {return _ptr;}
                inline const ReplyHeader_1_2 & in () const { return *_ptr; }
                inline ReplyHeader_1_2 & inout () { return *_ptr; }
                ReplyHeader_1_2 *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                ReplyHeader_1_2 * _retn ()
                {
                    ReplyHeader_1_2 *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline ReplyHeader_1_2_ptr & ptr() { return _ptr; }
                inline operator ReplyHeader_1_2&() { return *_ptr; }
                inline operator const ReplyHeader_1_2&() const { return *_ptr; }
                inline operator ReplyHeader_1_2_ptr &() { return _ptr; }
            private:
                ReplyHeader_1_2 *_ptr;
        };  // class ReplyHeader_1_2_var

        class OBBEXPDLL ReplyHeader_1_2_out
        {
            public:
                ReplyHeader_1_2_out (ReplyHeader_1_2 *& p) : ptr_(p) { ptr_ = 0; }
                ReplyHeader_1_2_out (ReplyHeader_1_2_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                ReplyHeader_1_2_out (const ReplyHeader_1_2_out & a) : ptr_(a.ptr_) {}
                ReplyHeader_1_2_out & operator=(const ReplyHeader_1_2_out & a) {
                    ptr_ = a.ptr_; return *this; }
                ReplyHeader_1_2_out & operator=(ReplyHeader_1_2 * p) {
                    ptr_ = p; return *this; }
                inline operator ReplyHeader_1_2_ptr & () { return ptr_; }
                inline ReplyHeader_1_2_ptr & ptr () { return ptr_; }
                inline ReplyHeader_1_2_ptr operator->() { return ptr_; }
            private:
                ReplyHeader_1_2_ptr & ptr_;
                void operator=(const ReplyHeader_1_2_var &);

        };  // class ReplyHeader_1_2_out
        static const CORBA::TypeCode_ptr _tc_ReplyHeader_1_2;


        struct  SystemExceptionReplyBody {
            CORBA::String_var exception_id;
             CORBA::ULong minor_code_value;
             CORBA::ULong completion_status;
            SystemExceptionReplyBody &operator=(const SystemExceptionReplyBody &_obj);
        };
        typedef	SystemExceptionReplyBody *	SystemExceptionReplyBody_ptr;
        class OBBEXPDLL SystemExceptionReplyBody_var
        {
            public:
                inline SystemExceptionReplyBody_var() {_ptr = 0;}
                inline SystemExceptionReplyBody_var(SystemExceptionReplyBody *_obj) {_ptr = _obj;}
                SystemExceptionReplyBody_var(const SystemExceptionReplyBody_var &_obj) {_ptr = 0; *this = _obj;}
                ~SystemExceptionReplyBody_var();
                SystemExceptionReplyBody_var &operator=(SystemExceptionReplyBody *);
                SystemExceptionReplyBody_var &operator=(const SystemExceptionReplyBody_var &);
                inline SystemExceptionReplyBody *operator->() {return _ptr;}
                inline const SystemExceptionReplyBody *operator->() const {return _ptr;}
                inline const SystemExceptionReplyBody & in () const { return *_ptr; }
                inline SystemExceptionReplyBody & inout () { return *_ptr; }
                SystemExceptionReplyBody *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                SystemExceptionReplyBody * _retn ()
                {
                    SystemExceptionReplyBody *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline SystemExceptionReplyBody_ptr & ptr() { return _ptr; }
                inline operator SystemExceptionReplyBody&() { return *_ptr; }
                inline operator const SystemExceptionReplyBody&() const { return *_ptr; }
                inline operator SystemExceptionReplyBody_ptr &() { return _ptr; }
            private:
                SystemExceptionReplyBody *_ptr;
        };  // class SystemExceptionReplyBody_var

        class OBBEXPDLL SystemExceptionReplyBody_out
        {
            public:
                SystemExceptionReplyBody_out (SystemExceptionReplyBody *& p) : ptr_(p) { ptr_ = 0; }
                SystemExceptionReplyBody_out (SystemExceptionReplyBody_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                SystemExceptionReplyBody_out (const SystemExceptionReplyBody_out & a) : ptr_(a.ptr_) {}
                SystemExceptionReplyBody_out & operator=(const SystemExceptionReplyBody_out & a) {
                    ptr_ = a.ptr_; return *this; }
                SystemExceptionReplyBody_out & operator=(SystemExceptionReplyBody * p) {
                    ptr_ = p; return *this; }
                inline operator SystemExceptionReplyBody_ptr & () { return ptr_; }
                inline SystemExceptionReplyBody_ptr & ptr () { return ptr_; }
                inline SystemExceptionReplyBody_ptr operator->() { return ptr_; }
            private:
                SystemExceptionReplyBody_ptr & ptr_;
                void operator=(const SystemExceptionReplyBody_var &);

        };  // class SystemExceptionReplyBody_out
        static const CORBA::TypeCode_ptr _tc_SystemExceptionReplyBody;


        struct  CancelRequestHeader {
             CORBA::ULong request_id;
        };
        typedef	CancelRequestHeader *	CancelRequestHeader_ptr;
        class OBBEXPDLL CancelRequestHeader_var
        {
            public:
                inline CancelRequestHeader_var() {_ptr = 0;}
                inline CancelRequestHeader_var(CancelRequestHeader *_obj) {_ptr = _obj;}
                CancelRequestHeader_var(const CancelRequestHeader_var &_obj) {_ptr = 0; *this = _obj;}
                ~CancelRequestHeader_var();
                CancelRequestHeader_var &operator=(CancelRequestHeader *);
                CancelRequestHeader_var &operator=(const CancelRequestHeader_var &);
                inline CancelRequestHeader *operator->() {return _ptr;}
                inline const CancelRequestHeader *operator->() const {return _ptr;}
                inline const CancelRequestHeader & in () const { return *_ptr; }
                inline CancelRequestHeader & inout () { return *_ptr; }
                CancelRequestHeader & out ()
                {
                    CancelRequestHeader *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                CancelRequestHeader & _retn ()
                {
                    CancelRequestHeader *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline CancelRequestHeader_ptr & ptr() { return _ptr; }
                inline operator CancelRequestHeader&() { return *_ptr; }
                inline operator const CancelRequestHeader&() const { return *_ptr; }
                inline operator CancelRequestHeader_ptr &() { return _ptr; }
            private:
                CancelRequestHeader *_ptr;
        };  // class CancelRequestHeader_var

        typedef CancelRequestHeader& CancelRequestHeader_out;
        static const CORBA::TypeCode_ptr _tc_CancelRequestHeader;


        struct  LocateRequestHeader_1_0 {
             CORBA::ULong request_id;


            class OBBEXPDLL _1_object_key
            {
                public:
                    _1_object_key();

                    _1_object_key(CORBA::ULong _max);

                    _1_object_key
                    (
                        CORBA::ULong _max,
                        CORBA::ULong _length,
                        CORBA::Octet *_value,
                        CORBA::Boolean _relse = CORBA_FALSE
                    );

                    _1_object_key(const _1_object_key &_ptr);

                    ~_1_object_key();

                    _1_object_key &operator=(const _1_object_key& _ptr);

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
            };  // class _1_object_key

             _1_object_key object_key;
            LocateRequestHeader_1_0 &operator=(const LocateRequestHeader_1_0 &_obj);
        };
        typedef	LocateRequestHeader_1_0 *	LocateRequestHeader_1_0_ptr;
        class OBBEXPDLL LocateRequestHeader_1_0_var
        {
            public:
                inline LocateRequestHeader_1_0_var() {_ptr = 0;}
                inline LocateRequestHeader_1_0_var(LocateRequestHeader_1_0 *_obj) {_ptr = _obj;}
                LocateRequestHeader_1_0_var(const LocateRequestHeader_1_0_var &_obj) {_ptr = 0; *this = _obj;}
                ~LocateRequestHeader_1_0_var();
                LocateRequestHeader_1_0_var &operator=(LocateRequestHeader_1_0 *);
                LocateRequestHeader_1_0_var &operator=(const LocateRequestHeader_1_0_var &);
                inline LocateRequestHeader_1_0 *operator->() {return _ptr;}
                inline const LocateRequestHeader_1_0 *operator->() const {return _ptr;}
                inline const LocateRequestHeader_1_0 & in () const { return *_ptr; }
                inline LocateRequestHeader_1_0 & inout () { return *_ptr; }
                LocateRequestHeader_1_0 *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                LocateRequestHeader_1_0 * _retn ()
                {
                    LocateRequestHeader_1_0 *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline LocateRequestHeader_1_0_ptr & ptr() { return _ptr; }
                inline operator LocateRequestHeader_1_0&() { return *_ptr; }
                inline operator const LocateRequestHeader_1_0&() const { return *_ptr; }
                inline operator LocateRequestHeader_1_0_ptr &() { return _ptr; }
            private:
                LocateRequestHeader_1_0 *_ptr;
        };  // class LocateRequestHeader_1_0_var

        class OBBEXPDLL LocateRequestHeader_1_0_out
        {
            public:
                LocateRequestHeader_1_0_out (LocateRequestHeader_1_0 *& p) : ptr_(p) { ptr_ = 0; }
                LocateRequestHeader_1_0_out (LocateRequestHeader_1_0_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                LocateRequestHeader_1_0_out (const LocateRequestHeader_1_0_out & a) : ptr_(a.ptr_) {}
                LocateRequestHeader_1_0_out & operator=(const LocateRequestHeader_1_0_out & a) {
                    ptr_ = a.ptr_; return *this; }
                LocateRequestHeader_1_0_out & operator=(LocateRequestHeader_1_0 * p) {
                    ptr_ = p; return *this; }
                inline operator LocateRequestHeader_1_0_ptr & () { return ptr_; }
                inline LocateRequestHeader_1_0_ptr & ptr () { return ptr_; }
                inline LocateRequestHeader_1_0_ptr operator->() { return ptr_; }
            private:
                LocateRequestHeader_1_0_ptr & ptr_;
                void operator=(const LocateRequestHeader_1_0_var &);

        };  // class LocateRequestHeader_1_0_out
        static const CORBA::TypeCode_ptr _tc_LocateRequestHeader_1_0;
        typedef LocateRequestHeader_1_0 LocateRequestHeader_1_1;
        typedef LocateRequestHeader_1_0_out LocateRequestHeader_1_1_out;
        typedef LocateRequestHeader_1_0_var LocateRequestHeader_1_1_var;
        static const CORBA::TypeCode_ptr _tc_LocateRequestHeader_1_1;


        struct  LocateRequestHeader_1_2 {
             CORBA::ULong request_id;


             TargetAddress target;
            LocateRequestHeader_1_2 &operator=(const LocateRequestHeader_1_2 &_obj);
        };
        typedef	LocateRequestHeader_1_2 *	LocateRequestHeader_1_2_ptr;
        class OBBEXPDLL LocateRequestHeader_1_2_var
        {
            public:
                inline LocateRequestHeader_1_2_var() {_ptr = 0;}
                inline LocateRequestHeader_1_2_var(LocateRequestHeader_1_2 *_obj) {_ptr = _obj;}
                LocateRequestHeader_1_2_var(const LocateRequestHeader_1_2_var &_obj) {_ptr = 0; *this = _obj;}
                ~LocateRequestHeader_1_2_var();
                LocateRequestHeader_1_2_var &operator=(LocateRequestHeader_1_2 *);
                LocateRequestHeader_1_2_var &operator=(const LocateRequestHeader_1_2_var &);
                inline LocateRequestHeader_1_2 *operator->() {return _ptr;}
                inline const LocateRequestHeader_1_2 *operator->() const {return _ptr;}
                inline const LocateRequestHeader_1_2 & in () const { return *_ptr; }
                inline LocateRequestHeader_1_2 & inout () { return *_ptr; }
                LocateRequestHeader_1_2 *& out ()
                {
                    delete _ptr;
                    _ptr=0;
                    return _ptr;
                }
                LocateRequestHeader_1_2 * _retn ()
                {
                    LocateRequestHeader_1_2 *tmp = _ptr;
                    _ptr = 0;
                    return tmp;
                }
                inline LocateRequestHeader_1_2_ptr & ptr() { return _ptr; }
                inline operator LocateRequestHeader_1_2&() { return *_ptr; }
                inline operator const LocateRequestHeader_1_2&() const { return *_ptr; }
                inline operator LocateRequestHeader_1_2_ptr &() { return _ptr; }
            private:
                LocateRequestHeader_1_2 *_ptr;
        };  // class LocateRequestHeader_1_2_var

        class OBBEXPDLL LocateRequestHeader_1_2_out
        {
            public:
                LocateRequestHeader_1_2_out (LocateRequestHeader_1_2 *& p) : ptr_(p) { ptr_ = 0; }
                LocateRequestHeader_1_2_out (LocateRequestHeader_1_2_var &p) : ptr_(p.ptr()) {
                    delete ptr_; ptr_ = 0; }
                LocateRequestHeader_1_2_out (const LocateRequestHeader_1_2_out & a) : ptr_(a.ptr_) {}
                LocateRequestHeader_1_2_out & operator=(const LocateRequestHeader_1_2_out & a) {
                    ptr_ = a.ptr_; return *this; }
                LocateRequestHeader_1_2_out & operator=(LocateRequestHeader_1_2 * p) {
                    ptr_ = p; return *this; }
                inline operator LocateRequestHeader_1_2_ptr & () { return ptr_; }
                inline LocateRequestHeader_1_2_ptr & ptr () { return ptr_; }
                inline LocateRequestHeader_1_2_ptr operator->() { return ptr_; }
            private:
                LocateRequestHeader_1_2_ptr & ptr_;
                void operator=(const LocateRequestHeader_1_2_var &);

        };  // class LocateRequestHeader_1_2_out
        static const CORBA::TypeCode_ptr _tc_LocateRequestHeader_1_2;


        enum LocateStatusType_1_2 { UNKNOWN_OBJECT, OBJECT_HERE, OBJECT_FORWARD, OBJECT_FORWARD_PERM, LOC_SYSTEM_EXCEPTION, LOC_NEEDS_ADDRESSING_MODE };
        typedef LocateStatusType_1_2 & LocateStatusType_1_2_out ;
        static const CORBA::TypeCode_ptr _tc_LocateStatusType_1_2;


        struct  LocateReplyHeader_1_2 {
             CORBA::ULong request_id;


             LocateStatusType_1_2 locate_status;
        };
        typedef	LocateReplyHeader_1_2 *	LocateReplyHeader_1_2_ptr;
        class OBBEXPDLL LocateReplyHeader_1_2_var
        {
            public:
                inline LocateReplyHeader_1_2_var() {_ptr = 0;}
                inline LocateReplyHeader_1_2_var(LocateReplyHeader_1_2 *_obj) {_ptr = _obj;}
                LocateReplyHeader_1_2_var(const LocateReplyHeader_1_2_var &_obj) {_ptr = 0; *this = _obj;}
                ~LocateReplyHeader_1_2_var();
                LocateReplyHeader_1_2_var &operator=(LocateReplyHeader_1_2 *);
                LocateReplyHeader_1_2_var &operator=(const LocateReplyHeader_1_2_var &);
                inline LocateReplyHeader_1_2 *operator->() {return _ptr;}
                inline const LocateReplyHeader_1_2 *operator->() const {return _ptr;}
                inline const LocateReplyHeader_1_2 & in () const { return *_ptr; }
                inline LocateReplyHeader_1_2 & inout () { return *_ptr; }
                LocateReplyHeader_1_2 & out ()
                {
                    LocateReplyHeader_1_2 *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                LocateReplyHeader_1_2 & _retn ()
                {
                    LocateReplyHeader_1_2 *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline LocateReplyHeader_1_2_ptr & ptr() { return _ptr; }
                inline operator LocateReplyHeader_1_2&() { return *_ptr; }
                inline operator const LocateReplyHeader_1_2&() const { return *_ptr; }
                inline operator LocateReplyHeader_1_2_ptr &() { return _ptr; }
            private:
                LocateReplyHeader_1_2 *_ptr;
        };  // class LocateReplyHeader_1_2_var

        typedef LocateReplyHeader_1_2& LocateReplyHeader_1_2_out;
        static const CORBA::TypeCode_ptr _tc_LocateReplyHeader_1_2;


        struct  FragmentHeader_1_2 {
             CORBA::ULong request_id;
        };
        typedef	FragmentHeader_1_2 *	FragmentHeader_1_2_ptr;
        class OBBEXPDLL FragmentHeader_1_2_var
        {
            public:
                inline FragmentHeader_1_2_var() {_ptr = 0;}
                inline FragmentHeader_1_2_var(FragmentHeader_1_2 *_obj) {_ptr = _obj;}
                FragmentHeader_1_2_var(const FragmentHeader_1_2_var &_obj) {_ptr = 0; *this = _obj;}
                ~FragmentHeader_1_2_var();
                FragmentHeader_1_2_var &operator=(FragmentHeader_1_2 *);
                FragmentHeader_1_2_var &operator=(const FragmentHeader_1_2_var &);
                inline FragmentHeader_1_2 *operator->() {return _ptr;}
                inline const FragmentHeader_1_2 *operator->() const {return _ptr;}
                inline const FragmentHeader_1_2 & in () const { return *_ptr; }
                inline FragmentHeader_1_2 & inout () { return *_ptr; }
                FragmentHeader_1_2 & out ()
                {
                    FragmentHeader_1_2 *tmp = _ptr;
                    _ptr=0;
                    return *tmp;
                }
                FragmentHeader_1_2 & _retn ()
                {
                    FragmentHeader_1_2 *tmp = _ptr;
                    _ptr = 0;
                    return *tmp;
                }
                inline FragmentHeader_1_2_ptr & ptr() { return _ptr; }
                inline operator FragmentHeader_1_2&() { return *_ptr; }
                inline operator const FragmentHeader_1_2&() const { return *_ptr; }
                inline operator FragmentHeader_1_2_ptr &() { return _ptr; }
            private:
                FragmentHeader_1_2 *_ptr;
        };  // class FragmentHeader_1_2_var

        typedef FragmentHeader_1_2& FragmentHeader_1_2_out;
        static const CORBA::TypeCode_ptr _tc_FragmentHeader_1_2;
};  // class GIOP

void  operator<<=(CORBA::Any &a, const GIOP::Version &obj);
void  operator<<=(CORBA::Any &a, GIOP::Version *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::Version *&obj);
void  operator<<=(CORBA::Any &a, GIOP::MsgType_1_1 obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::MsgType_1_1 &obj);
void  operator<<=(CORBA::Any &a, const GIOP::MessageHeader_1_0 &obj);
void  operator<<=(CORBA::Any &a, GIOP::MessageHeader_1_0 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::MessageHeader_1_0 *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::MessageHeader_1_1 &obj);
void  operator<<=(CORBA::Any &a, GIOP::MessageHeader_1_1 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::MessageHeader_1_1 *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::RequestHeader_1_0 &obj);
void  operator<<=(CORBA::Any &a, GIOP::RequestHeader_1_0 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::RequestHeader_1_0 *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::RequestHeader_1_1 &obj);
void  operator<<=(CORBA::Any &a, GIOP::RequestHeader_1_1 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::RequestHeader_1_1 *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::IORAddressingInfo &obj);
void  operator<<=(CORBA::Any &a, GIOP::IORAddressingInfo *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::IORAddressingInfo *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::TargetAddress &obj);
void  operator<<=(CORBA::Any &a, GIOP::TargetAddress *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::TargetAddress *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::RequestHeader_1_2 &obj);
void  operator<<=(CORBA::Any &a, GIOP::RequestHeader_1_2 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::RequestHeader_1_2 *&obj);
void  operator<<=(CORBA::Any &a, GIOP::ReplyStatusType_1_2 obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::ReplyStatusType_1_2 &obj);
void  operator<<=(CORBA::Any &a, const GIOP::ReplyHeader_1_2 &obj);
void  operator<<=(CORBA::Any &a, GIOP::ReplyHeader_1_2 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::ReplyHeader_1_2 *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::SystemExceptionReplyBody &obj);
void  operator<<=(CORBA::Any &a, GIOP::SystemExceptionReplyBody *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::SystemExceptionReplyBody *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::CancelRequestHeader &obj);
void  operator<<=(CORBA::Any &a, GIOP::CancelRequestHeader *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::CancelRequestHeader *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::LocateRequestHeader_1_0 &obj);
void  operator<<=(CORBA::Any &a, GIOP::LocateRequestHeader_1_0 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::LocateRequestHeader_1_0 *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::LocateRequestHeader_1_2 &obj);
void  operator<<=(CORBA::Any &a, GIOP::LocateRequestHeader_1_2 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::LocateRequestHeader_1_2 *&obj);
void  operator<<=(CORBA::Any &a, GIOP::LocateStatusType_1_2 obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::LocateStatusType_1_2 &obj);
void  operator<<=(CORBA::Any &a, const GIOP::LocateReplyHeader_1_2 &obj);
void  operator<<=(CORBA::Any &a, GIOP::LocateReplyHeader_1_2 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::LocateReplyHeader_1_2 *&obj);
void  operator<<=(CORBA::Any &a, const GIOP::FragmentHeader_1_2 &obj);
void  operator<<=(CORBA::Any &a, GIOP::FragmentHeader_1_2 *obj);
CORBA::Boolean  operator>>=(const CORBA::Any &a, GIOP::FragmentHeader_1_2 *&obj);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::Version &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::Version &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::MsgType_1_1 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::MsgType_1_1 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::MessageHeader_1_0 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::MessageHeader_1_0 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::MessageHeader_1_1 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::MessageHeader_1_1 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::RequestHeader_1_0 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::RequestHeader_1_0 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::RequestHeader_1_1 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::RequestHeader_1_1 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::IORAddressingInfo &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::IORAddressingInfo &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::TargetAddress &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::TargetAddress &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::RequestHeader_1_2 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::RequestHeader_1_2 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::ReplyStatusType_1_2 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::ReplyStatusType_1_2 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::ReplyHeader_1_2 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::ReplyHeader_1_2 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::SystemExceptionReplyBody &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::SystemExceptionReplyBody &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::CancelRequestHeader &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::CancelRequestHeader &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::LocateRequestHeader_1_0 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::LocateRequestHeader_1_0 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::LocateRequestHeader_1_2 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::LocateRequestHeader_1_2 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::LocateStatusType_1_2 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::LocateStatusType_1_2 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::LocateReplyHeader_1_2 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::LocateReplyHeader_1_2 &);
OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, GIOP::FragmentHeader_1_2 &);
OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, GIOP::FragmentHeader_1_2 &);

#endif /* _GIOP_H */
