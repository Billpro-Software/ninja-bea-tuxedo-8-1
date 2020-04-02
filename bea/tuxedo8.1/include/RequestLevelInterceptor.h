/*    Copyright (c) 1999 BEA Systems, Inc.                 */
/*    All Rights Reserved                                  */

/*    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF       */
/*    BEA Systems, Inc.                                    */
/*    The copyright notice above does not evidence any     */
/*    actual or intended publication of such source code.  */

/*
 * This module contains definitions and prototypes
 * for the following Interfaces:
 *
 *    RequestLevelInterceptor::RequestInterceptor
 *    RequestLevelInterceptor::ClientRequestInterceptor
 *    RequestLevelInterceptor::TargetRequestInterceptor
 *
 */

#ifndef _RequestLevelInterceptor_h
#define _RequestLevelInterceptor_h

#include <CORBA.h>
#include <IOP.h>
#include <GIOP.h>
#include <Interceptors.h>

class OBBEXPDLL RequestLevelInterceptor
{

  public:
    class	ServiceContextList;
    typedef	ServiceContextList *	ServiceContextList_ptr;
    class ServiceContextList_out;

    class OBBEXPDLL ServiceContextList_var : public CORBA::_var {
        public:
            ServiceContextList_var();
            inline ServiceContextList_var(ServiceContextList_ptr p) {ptr_ = p; }
            ServiceContextList_var(const ServiceContextList_var &a);
            ~ServiceContextList_var()
                { free();}

            ServiceContextList_var &operator=(ServiceContextList_ptr p)
                { if (p != ptr_) reset(p);
                return *this; }

            ServiceContextList_var &operator=(const ServiceContextList_var &a);
            inline ServiceContextList_ptr in () const { return ptr_; }
            inline ServiceContextList_ptr & inout () { return ptr_; }
            ServiceContextList_ptr & out ();
            ServiceContextList_ptr _retn ();

            inline operator ServiceContextList_ptr&() { return ptr_; }
            inline operator const ServiceContextList_ptr&() const { return ptr_; }
            inline ServiceContextList_ptr operator->() const { return ptr_; }

            inline ServiceContextList_ptr & ptr () { return ptr_; }
        protected:
            ServiceContextList_ptr ptr_;
            void free();
            void reset(ServiceContextList_ptr p) { free(); ptr_ = p; }

        private:
            void operator=(const CORBA::_var &);
    };  // class ServiceContextList_var

    class	RequestInterceptor;
    typedef	RequestInterceptor *	RequestInterceptor_ptr;
    class RequestInterceptor_out;

    class OBBEXPDLL RequestInterceptor_var : public CORBA::_var {
        public:
            RequestInterceptor_var();
            inline RequestInterceptor_var(RequestInterceptor_ptr p) {ptr_ = p; }
            RequestInterceptor_var(const RequestInterceptor_var &a);
            ~RequestInterceptor_var()
                { free();}

            RequestInterceptor_var &operator=(RequestInterceptor_ptr p)
                { if (p != ptr_) reset(p);
                return *this; }

            RequestInterceptor_var &operator=(const RequestInterceptor_var &a);
            inline RequestInterceptor_ptr in () const { return ptr_; }
            inline RequestInterceptor_ptr & inout () { return ptr_; }
            RequestInterceptor_ptr & out ();
            RequestInterceptor_ptr _retn ();

            inline operator RequestInterceptor_ptr&() { return ptr_; }
            inline operator const RequestInterceptor_ptr&() const { return ptr_; }
            inline RequestInterceptor_ptr operator->() const { return ptr_; }

            inline RequestInterceptor_ptr & ptr () { return ptr_; }
        protected:
            RequestInterceptor_ptr ptr_;
            void free();
            void reset(RequestInterceptor_ptr p) { free(); ptr_ = p; }

        private:
            void operator=(const CORBA::_var &);
    };  // class RequestInterceptor_var

    class	ClientRequestInterceptor;
    typedef	ClientRequestInterceptor *	ClientRequestInterceptor_ptr;
    class ClientRequestInterceptor_out;

    class OBBEXPDLL ClientRequestInterceptor_var : public CORBA::_var {
        public:
            ClientRequestInterceptor_var();
            inline ClientRequestInterceptor_var(ClientRequestInterceptor_ptr p) {ptr_ = p; }
            ClientRequestInterceptor_var(const ClientRequestInterceptor_var &a);
            ~ClientRequestInterceptor_var()
                { free();}

            ClientRequestInterceptor_var &operator=(ClientRequestInterceptor_ptr p)
                { if (p != ptr_) reset(p);
                return *this; }

            ClientRequestInterceptor_var &operator=(const ClientRequestInterceptor_var &a);
            inline ClientRequestInterceptor_ptr in () const { return ptr_; }
            inline ClientRequestInterceptor_ptr & inout () { return ptr_; }
            ClientRequestInterceptor_ptr & out ();
            ClientRequestInterceptor_ptr _retn ();

            inline operator ClientRequestInterceptor_ptr&() { return ptr_; }
            inline operator const ClientRequestInterceptor_ptr&() const { return ptr_; }
            inline ClientRequestInterceptor_ptr operator->() const { return ptr_; }

            inline ClientRequestInterceptor_ptr & ptr () { return ptr_; }
        protected:
            ClientRequestInterceptor_ptr ptr_;
            void free();
            void reset(ClientRequestInterceptor_ptr p) { free(); ptr_ = p; }

        private:
            void operator=(const CORBA::_var &);
    };  // class ClientRequestInterceptor_var

    class	TargetRequestInterceptor;
    typedef	TargetRequestInterceptor *	TargetRequestInterceptor_ptr;
    class TargetRequestInterceptor_out;

    class OBBEXPDLL TargetRequestInterceptor_var : public CORBA::_var {
        public:
            TargetRequestInterceptor_var();
            inline TargetRequestInterceptor_var(TargetRequestInterceptor_ptr p) {ptr_ = p; }
            TargetRequestInterceptor_var(const TargetRequestInterceptor_var &a);
            ~TargetRequestInterceptor_var()
                { free();}

            TargetRequestInterceptor_var &operator=(TargetRequestInterceptor_ptr p)
                { if (p != ptr_) reset(p);
                return *this; }

            TargetRequestInterceptor_var &operator=(const TargetRequestInterceptor_var &a);
            inline TargetRequestInterceptor_ptr in () const { return ptr_; }
            inline TargetRequestInterceptor_ptr & inout () { return ptr_; }
            TargetRequestInterceptor_ptr & out ();
            TargetRequestInterceptor_ptr _retn ();

            inline operator TargetRequestInterceptor_ptr&() { return ptr_; }
            inline operator const TargetRequestInterceptor_ptr&() const { return ptr_; }
            inline TargetRequestInterceptor_ptr operator->() const { return ptr_; }

            inline TargetRequestInterceptor_ptr & ptr () { return ptr_; }
        protected:
            TargetRequestInterceptor_ptr ptr_;
            void free();
            void reset(TargetRequestInterceptor_ptr p) { free(); ptr_ = p; }

        private:
            void operator=(const CORBA::_var &);
    };  // class TargetRequestInterceptor_var

    class OBBEXPDLL ServiceContextList : public virtual CORBA::LocalBase
     {
        public:
            class OBBEXPDLL NotFound : public CORBA::UserException
            {
                public:
                    static NotFound * _narrow(CORBA::Exception_ptr);
                    NotFound ();
                    ~NotFound ();
                    NotFound & operator=(const NotFound &);
                    void _raise();
                    static char * _get_repos_id() {
			return (char *)"IDL:omg.org/RequestLevelInterceptor/ServiceContextList/NotFound:1.0"; }
            };  // class NotFound

            typedef	NotFound *	NotFound_ptr;
            class OBBEXPDLL NotFound_var
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

            class OBBEXPDLL NotFound_out
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
            static const CORBA::TypeCode_ptr _tc_NotFound;
            static ServiceContextList_ptr _duplicate(ServiceContextList_ptr obj);
            static ServiceContextList_ptr _narrow(CORBA::Object_ptr obj);
            inline static ServiceContextList_ptr _nil() { return 0; }
            static const char* _get_interface_name ();

            virtual CORBA::DataOutputStream_ptr add_context (
                IOP::ServiceId context_id) = 0; 

            virtual CORBA::DataInputStream_ptr find_context (
                IOP::ServiceId context_id) = 0; 

            virtual CORBA::DataInputStream_ptr get_context (
                CORBA::ULong index) = 0; 

            virtual CORBA::ULong count () = 0; 

        protected:
            ServiceContextList(CORBA::LocalBase_ptr obj = 0);
            virtual ~ServiceContextList(){ }

        private:
            ServiceContextList( const ServiceContextList&) { }
            void operator=(const ServiceContextList&) { }
    };  // class ServiceContextList

    class OBBEXPDLL ServiceContextList_out
     {
        public:
            ServiceContextList_out (ServiceContextList_ptr & p);
            ServiceContextList_out (ServiceContextList_var & p);
            ServiceContextList_out (const ServiceContextList_out & p) : ptr_(p.ptr_) {}
            ServiceContextList_out & operator=(const ServiceContextList_out & a) {
                ptr_ = a.ptr_; return *this;}
            ServiceContextList_out & operator=(const ServiceContextList_var & a);
            ServiceContextList_out & operator=(ServiceContextList_ptr p) {
            ptr_ = p; return *this;}
            inline operator ServiceContextList_ptr & () { return ptr_; }
            inline ServiceContextList_ptr & ptr () { return ptr_; }
            inline ServiceContextList_ptr operator->() { return ptr_; }
        private:
            ServiceContextList_ptr & ptr_;
    };  // class ServiceContextList_out

    struct  RequestContext {
        Interceptors::Version struct_version;
        CORBA::ULong request_id;
        CORBA::Octet response_flags;
        GIOP::TargetAddress target;
        CORBA::String_var interface_id;
        CORBA::String_var operation;
        RequestContext &operator=(const RequestContext &_obj);
    };

    typedef	RequestContext *	RequestContext_ptr;
    class OBBEXPDLL RequestContext_var
    {
        public:
            inline RequestContext_var() {_ptr = 0;}
            inline RequestContext_var(RequestContext *_obj) {_ptr = _obj;}
            RequestContext_var(const RequestContext_var &_obj) {_ptr = 0; *this = _obj;}
            ~RequestContext_var();
            RequestContext_var &operator=(RequestContext *);
            RequestContext_var &operator=(const RequestContext_var &);
            inline RequestContext *operator->() {return _ptr;}
            inline const RequestContext *operator->() const {return _ptr;}
            inline const RequestContext & in () const { return *_ptr; }
            inline RequestContext & inout () { return *_ptr; }
            RequestContext *& out ()
            {
                delete _ptr;
                _ptr=0;
                return _ptr;
            }
            RequestContext * _retn ()
            {
                RequestContext *tmp = _ptr;
                _ptr = 0;
                return tmp;
            }
            inline RequestContext_ptr & ptr() { return _ptr; }
            inline operator RequestContext&() { return *_ptr; }
            inline operator const RequestContext&() const { return *_ptr; }
            inline operator RequestContext_ptr &() { return _ptr; }
        private:
            RequestContext *_ptr;
    };  // class RequestContext_var

    class OBBEXPDLL RequestContext_out
    {
        public:
            RequestContext_out (RequestContext *& p) : ptr_(p) { ptr_ = 0; }
            RequestContext_out (RequestContext_var &p) : ptr_(p.ptr()) {
                delete ptr_; ptr_ = 0; }
            RequestContext_out (const RequestContext_out & a) : ptr_(a.ptr_) {}
            RequestContext_out & operator=(const RequestContext_out & a) {
                ptr_ = a.ptr_; return *this; }
            RequestContext_out & operator=(RequestContext * p) {
                ptr_ = p; return *this; }
            inline operator RequestContext_ptr & () { return ptr_; }
            inline RequestContext_ptr & ptr () { return ptr_; }
            inline RequestContext_ptr operator->() { return ptr_; }
        private:
            RequestContext_ptr & ptr_;
            void operator=(const RequestContext_var &);
    };  // class RequestContext_out
    typedef GIOP::ReplyStatusType_1_2 ReplyStatus;
    typedef GIOP::ReplyStatusType_1_2_out ReplyStatus_out;

    struct  ReplyContext {
         Interceptors::Version struct_version;
         CORBA::ULong request_id;
         ReplyStatus reply_status;
    };
    typedef	ReplyContext *	ReplyContext_ptr;
    class OBBEXPDLL ReplyContext_var
    {
        public:
            inline ReplyContext_var() {_ptr = 0;}
            inline ReplyContext_var(ReplyContext *_obj) {_ptr = _obj;}
            ReplyContext_var(const ReplyContext_var &_obj) {_ptr = 0; *this = _obj;}
            ~ReplyContext_var();
            ReplyContext_var &operator=(ReplyContext *);
            ReplyContext_var &operator=(const ReplyContext_var &);
            inline ReplyContext *operator->() {return _ptr;}
            inline const ReplyContext *operator->() const {return _ptr;}
            inline const ReplyContext & in () const { return *_ptr; }
            inline ReplyContext & inout () { return *_ptr; }
            ReplyContext & out ()
            {
                ReplyContext *tmp = _ptr;
                _ptr=0;
                return *tmp;
            }
            ReplyContext & _retn ()
            {
                ReplyContext *tmp = _ptr;
                _ptr = 0;
                return *tmp;
            }
            inline ReplyContext_ptr & ptr() { return _ptr; }
            inline operator ReplyContext&() { return *_ptr; }
            inline operator const ReplyContext&() const { return *_ptr; }
            inline operator ReplyContext_ptr &() { return _ptr; }
        private:
            ReplyContext *_ptr;
    };  // class ReplyContext_var

    typedef ReplyContext& ReplyContext_out;
    class OBBEXPDLL RequestInterceptor : public virtual  Interceptors::Interceptor
    {
        public:
            static RequestInterceptor_ptr _duplicate(RequestInterceptor_ptr obj);
            static RequestInterceptor_ptr _narrow(RequestInterceptor_ptr obj);
            inline static RequestInterceptor_ptr _nil() { return 0; }

            virtual void exception_occurred (
                const ReplyContext & reply_context,
                CORBA::Exception_ptr excep_val) = 0; 

        protected:
            RequestInterceptor(CORBA::LocalBase_ptr obj = 0) { }
            virtual ~RequestInterceptor(){ }

        private:
            RequestInterceptor( const RequestInterceptor&) { }
            void operator=(const RequestInterceptor&) { }
    };  // class RequestInterceptor

    class OBBEXPDLL RequestInterceptor_out
     {
        public:
            RequestInterceptor_out (RequestInterceptor_ptr & p);
            RequestInterceptor_out (RequestInterceptor_var & p);
            RequestInterceptor_out (const RequestInterceptor_out & p) : ptr_(p.ptr_) {}
            RequestInterceptor_out & operator=(const RequestInterceptor_out & a) {
                ptr_ = a.ptr_; return *this;}
            RequestInterceptor_out & operator=(const RequestInterceptor_var & a);
            RequestInterceptor_out & operator=(RequestInterceptor_ptr p) {
            ptr_ = p; return *this;}
            inline operator RequestInterceptor_ptr & () { return ptr_; }
            inline RequestInterceptor_ptr & ptr () { return ptr_; }
            inline RequestInterceptor_ptr operator->() { return ptr_; }
        private:
            RequestInterceptor_ptr & ptr_;
    };  // class RequestInterceptor_out

    class OBBEXPDLL ClientRequestInterceptor : public virtual  RequestInterceptor
     {
        public:
            static ClientRequestInterceptor_ptr _duplicate(ClientRequestInterceptor_ptr obj);
            static ClientRequestInterceptor_ptr _narrow(ClientRequestInterceptor_ptr obj);
            inline static ClientRequestInterceptor_ptr _nil() { return 0; }

            virtual Interceptors::InvokeReturnStatus client_invoke (
                const RequestContext & request_context,
                ServiceContextList_ptr service_context,
                CORBA::DataInputStream_ptr request_arg_stream,
                CORBA::DataOutputStream_ptr reply_arg_stream,
                CORBA::Exception_ptr & excep_val) = 0; 

            virtual Interceptors::ResponseReturnStatus client_response (
                const ReplyContext & reply_context,
                ServiceContextList_ptr service_context,
                CORBA::DataInputStream_ptr arg_stream,
                CORBA::Exception_ptr & excep_val) = 0; 

        protected:
            ClientRequestInterceptor(CORBA::LocalBase_ptr obj = 0) { }
            virtual ~ClientRequestInterceptor(){ }

        private:
            ClientRequestInterceptor( const ClientRequestInterceptor&) { }
            void operator=(const ClientRequestInterceptor&) { }
    };  // class ClientRequestInterceptor

    class OBBEXPDLL ClientRequestInterceptor_out
    {
        public:
            ClientRequestInterceptor_out (ClientRequestInterceptor_ptr & p);
            ClientRequestInterceptor_out (ClientRequestInterceptor_var & p);
            ClientRequestInterceptor_out (const ClientRequestInterceptor_out & p) : ptr_(p.ptr_) {}
            ClientRequestInterceptor_out & operator=(const ClientRequestInterceptor_out & a) {
                ptr_ = a.ptr_; return *this;}
            ClientRequestInterceptor_out & operator=(const ClientRequestInterceptor_var & a);
            ClientRequestInterceptor_out & operator=(ClientRequestInterceptor_ptr p) {
            ptr_ = p; return *this;}
            inline operator ClientRequestInterceptor_ptr & () { return ptr_; }
            inline ClientRequestInterceptor_ptr & ptr () { return ptr_; }
            inline ClientRequestInterceptor_ptr operator->() { return ptr_; }
        private:
            ClientRequestInterceptor_ptr & ptr_;
    };  // class ClientRequestInterceptor_out

    class OBBEXPDLL TargetRequestInterceptor : public virtual  RequestInterceptor
     {
        public:
            static TargetRequestInterceptor_ptr _duplicate(TargetRequestInterceptor_ptr obj);
            static TargetRequestInterceptor_ptr _narrow(TargetRequestInterceptor_ptr obj);
            inline static TargetRequestInterceptor_ptr _nil() { return 0; }

            virtual Interceptors::InvokeReturnStatus target_invoke (
                const RequestContext & request_context,
                ServiceContextList_ptr service_context,
                CORBA::DataInputStream_ptr request_arg_stream,
                CORBA::DataOutputStream_ptr reply_arg_stream,
                CORBA::Exception_ptr & excep_val) = 0; 

            virtual Interceptors::ResponseReturnStatus target_response (
                const ReplyContext & reply_context,
                ServiceContextList_ptr service_context,
                CORBA::DataInputStream_ptr arg_stream,
                CORBA::Exception_ptr & excep_val) = 0; 

        protected:
            TargetRequestInterceptor(CORBA::LocalBase_ptr obj = 0) { }
            virtual ~TargetRequestInterceptor(){ }
     private:
        TargetRequestInterceptor( const TargetRequestInterceptor&) { }
        void operator=(const TargetRequestInterceptor&) { }
    };  // class TargetRequestInterceptor

    class OBBEXPDLL TargetRequestInterceptor_out
    {
        public:
            TargetRequestInterceptor_out (TargetRequestInterceptor_ptr & p);
            TargetRequestInterceptor_out (TargetRequestInterceptor_var & p);
            TargetRequestInterceptor_out (const TargetRequestInterceptor_out & p) : ptr_(p.ptr_) {}
            TargetRequestInterceptor_out & operator=(const TargetRequestInterceptor_out & a) {
                ptr_ = a.ptr_; return *this;}
            TargetRequestInterceptor_out & operator=(const TargetRequestInterceptor_var & a);
            TargetRequestInterceptor_out & operator=(TargetRequestInterceptor_ptr p) {
            ptr_ = p; return *this;}
            inline operator TargetRequestInterceptor_ptr & () { return ptr_; }
            inline TargetRequestInterceptor_ptr & ptr () { return ptr_; }
            inline TargetRequestInterceptor_ptr operator->() { return ptr_; }
        private:
            TargetRequestInterceptor_ptr & ptr_;
    };  // class TargetRequestInterceptor_out

};

typedef void (*AppRequestInterceptorInit)(
		CORBA::ORB_ptr,
		RequestLevelInterceptor::ClientRequestInterceptor **,
		RequestLevelInterceptor::TargetRequestInterceptor **,
		CORBA::Boolean *);

#endif /* _RequestLevelInterceptor_h */
