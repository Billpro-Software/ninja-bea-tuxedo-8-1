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
 *    Interceptors::Interceptor
 *
 */

#ifndef _INTERCEPTORS_H
#define _INTERCEPTORS_H

#include <string.h>
#include <CORBA.h>

class OBBEXPDLL Interceptors
{
    public:

	class Interceptor;
	typedef Interceptor * Interceptor_ptr;

	enum InvokeReturnStatus
	{
	    INVOKE_NO_EXCEPTION,	// proceed normally
	    REPLY_NO_EXCEPTION,		// stop proceeding; start reply processing
	    REPLY_EXCEPTION		// stop proceeding; reply with exception
	};
        typedef InvokeReturnStatus & InvokeReturnStatus_out ;

	enum ResponseReturnStatus
	{
	    RESPONSE_NO_EXCEPTION,	// proceed normally
	    RESPONSE_EXCEPTION		
	};
        typedef ResponseReturnStatus & ResponseReturnStatus_out ;

	enum ShutdownReturnStatus
	{
	    SHUTDOWN_NO_EXCEPTION,
	    SHUTDOWN_EXCEPTION
	};
        typedef ShutdownReturnStatus & ShutdownReturnStatus_out ;

	enum ShutdownReason
	{
	    ORB_SHUTDOWN,
	    CONNECTION_ABORTED,
	    RESOURCES_EXCEEDED
	};
        typedef ShutdownReason & ShutdownReason_out ;

	struct Version
	{
	    CORBA::Octet	major_version;
	    CORBA::Octet	minor_version;
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

	//+
	// Abstract base interface for all Interceptors
	//-
	class OBBEXPDLL Interceptor : public virtual CORBA::LocalBase
	{ 
	    public:
		static Interceptor_ptr _duplicate(Interceptor_ptr obj);
                static Interceptor_ptr _narrow(Interceptor_ptr obj);
		static Interceptor_ptr _nil();

		virtual ShutdownReturnStatus shutdown(ShutdownReason reason,
						      CORBA::Exception_ptr & excep_val) = 0;
		virtual CORBA::String id() = 0;


	    protected:
		Interceptor();
		virtual ~Interceptor();
	};

	class OBBEXPDLL Interceptor_var : public CORBA::_var
	{
	    public:
		Interceptor_var() { ptr_ = Interceptor::_nil(); }
		Interceptor_var(Interceptor_ptr Intr) { ptr_ = Intr; }
		Interceptor_var(const Interceptor_var &Intrv)
			{ ptr_ = Interceptor::_duplicate(Interceptor_ptr(Intrv)); }
		~Interceptor_var() { CORBA::release(ptr_); }
		Interceptor_var & operator=(Interceptor_ptr Intr);
		Interceptor_var & operator=(const Interceptor_var &Intrv)
		    { if (this != &Intrv) { CORBA::release(ptr_);
		      ptr_ = Interceptor::_duplicate(Interceptor_ptr(Intrv)); }
		      return *this; }
		inline Interceptor_ptr in() const { return ptr_; }
		inline Interceptor_ptr& inout() { return ptr_; }
		inline Interceptor_ptr& out()
		    { CORBA::release(ptr_); ptr_ = Interceptor::_nil(); return ptr_; }
		inline Interceptor_ptr _retn()
		    { Interceptor_ptr val = ptr_; ptr_ = Interceptor::_nil(); return val; }
		inline Interceptor_ptr& ptr() { return ptr_; }
		inline operator Interceptor_ptr&() { return ptr_; }
		inline operator const Interceptor_ptr& () const { return ptr_; }
		inline Interceptor_ptr operator->() { return ptr_; }
	    private:
		Interceptor_ptr ptr_;
		// hidden assignment operator to cause compile time error...
		Interceptor_var & operator=(const CORBA::_var &Varv);
	};
        class OBBEXPDLL Interceptor_out
         {
            public:
                Interceptor_out (Interceptor_ptr & p);
                Interceptor_out (Interceptor_var & p);
                Interceptor_out (const Interceptor_out & p) : ptr_(p.ptr_) {}
                Interceptor_out & operator=(const Interceptor_out & a) {
                    ptr_ = a.ptr_; return *this;}
                Interceptor_out & operator=(const Interceptor_var & a);
                Interceptor_out & operator=(Interceptor_ptr p) {
                ptr_ = p; return *this;}
                inline operator Interceptor_ptr & () { return ptr_; }
                inline Interceptor_ptr & ptr () { return ptr_; }
                inline Interceptor_ptr operator->() { return ptr_; }
            private:
                Interceptor_ptr & ptr_;
        };  // class Interceptor_out

};
#endif /* _INTERCEPTORS_H */
