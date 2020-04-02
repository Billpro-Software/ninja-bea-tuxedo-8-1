//	Copyright (c) 1997 BEA Systems, Inc.
//	All rights reserved
//
//	THIS IS UNPUBLISHED PROPRIETARY
//	SOURCE CODE OF BEA Systems, Inc.
//	The copyright notice above does not
//	evidence any actual or intended
//	publication of such source code.
//
// #ident	"@(#) orb/src/PortableServer.h	$Revision: 1.10 $"

#ifndef	_PortableServer_h
#define	_PortableServer_h

//
//      Copyright (c) 1997 BEA Systems, Inc. All rights reserved.
//

//
// MODULE NAME:
//
//	PortableServer.h
//
// FACILITY:
//
//	ObjectBroker IOP component
//
// ABSTRACT:
//
//	This include file contains the PortableServer C++ class definitions for
//	ObjectBroker IOP applications.
//
// CLASSES CONTAINED IN THIS MODULE:
//	PortableServer:: classes
//
// CREATION DATE: 7-May-1997
//
//

#include <CORBA.h>

#if defined(WIN32)
# ifndef IOPPOAEXPDLL
#  if defined(IOPPOAEXPORTAPI)
#   define IOPPOAEXPDLL __declspec(dllexport)
#  else
#   define IOPPOAEXPDLL __declspec(dllimport)
#  endif
# endif
#else
# define IOPPOAEXPDLL
#endif

class IOPPOAEXPDLL PortableServer
{
public:
    //
    // Portable Server object forward references
    //
    class ThreadPolicy;
    class LifespanPolicy;
    class IdUniquenessPolicy;
    class IdAssignmentPolicy;
    class ImplicitActivationPolicy;
    class ServantRetentionPolicy;
    class RequestProcessingPolicy;
    class StateControlPolicy;
    class ConcurrencyStrategyPolicy;
    class POAManager;
    class AdapterActivator;
    class ServantManager;
    class ServantActivator;
    class ServantLocator;
    class POA;
    class Current;

    //
    // Portable Server object _out forward references
    //
    class ThreadPolicy_out;
    class LifespanPolicy_out;
    class IdUniquenessPolicy_out;
    class IdAssignmentPolicy_out;
    class ImplicitActivationPolicy_out;
    class ServantRetentionPolicy_out;
    class RequestProcessingPolicy_out;
    class StateControlPolicy_out;
    class ConcurrencyStrategyPolicy_out;
    class POAManager_out;
    class AdapterActivator_out;
    class ServantManager_out;
    class ServantActivator_out;
    class ServantLocator_out;
    class POA_out;
    class Current_out;

    //
    // Object Id Sequence Class
    //
    class IOPPOAEXPDLL ObjectId
    {
	public:
	    ObjectId();
	    ObjectId(CORBA::ULong _max);
	    ObjectId (CORBA::ULong _max, CORBA::ULong _length,
		CORBA::Octet *_value, CORBA::Boolean _relse = CORBA_FALSE);

	    ObjectId(const ObjectId &_ptr);
	    ~ObjectId();
	    ObjectId &operator=(const ObjectId& _ptr);
	    CORBA::ULong maximum() const;
	    void length(CORBA::ULong);
	    CORBA::ULong length() const;
	    CORBA::Octet &operator[](CORBA::ULong _index);

	    const CORBA::Octet &operator[](CORBA::ULong _index) const;

	    static CORBA::Octet *allocbuf(CORBA::ULong _nelems);
	    static void freebuf(CORBA::Octet *_ptr);

	    // OBB internal use only
	    CORBA::Octet * OBB__data() const;

	private:
	    CORBA::Octet *_data;
	    CORBA::ULong _maximum;
	    CORBA::ULong _current;
	    CORBA::Boolean _release;
    };  // class ObjectId
    typedef ObjectId * ObjectId_ptr;
    
    class IOPPOAEXPDLL ObjectId_var
    {
	public:
	    ObjectId_var();
	    ObjectId_var(ObjectId *);
	    ObjectId_var(const ObjectId_var &);
	    ~ObjectId_var();
	    ObjectId_var &operator=(ObjectId *);
	    ObjectId_var &operator=(const ObjectId_var &);
	    CORBA::Octet &operator[](CORBA::ULong _index);
	    inline ObjectId in() const { return *ptr_; }
	    inline ObjectId & inout() { return *ptr_; }
	    inline ObjectId *& out() { if (ptr_) delete ptr_; return ptr_; }
	    inline ObjectId * _retn() { ObjectId * val = ptr_; ptr_ = 0; return val; }
	    inline operator ObjectId_ptr &() { return ptr_; }
	    inline operator ObjectId &() { return *ptr_; }
	    inline operator const ObjectId &() const { return *ptr_; }
	    ObjectId *operator->();
	    const ObjectId *operator->() const;
	    inline ObjectId*& ptr() { return ptr_; }
	private:
	    ObjectId *ptr_;
    };  // class ObjectId_var

    class IOPPOAEXPDLL ObjectId_out
    {
	public:
	    ObjectId_out(ObjectId*& p) : ptr_(p) { ptr_ = 0; }
	    ObjectId_out(ObjectId_var& p) : ptr_(p.ptr())
		{ delete ptr_; ptr_ = 0; }
	    ObjectId_out(const ObjectId_out& p) : ptr_(p.ptr_) {}
	    inline ObjectId_out& operator=(ObjectId_out& p)
		{ ptr_ = p.ptr_; return *this; }
	    inline ObjectId_out& operator=(ObjectId* p)
		{ ptr_ = p; return *this; }

	    inline operator ObjectId_ptr& () { return ptr_; }
	    inline ObjectId*& ptr() { return ptr_; }
	    inline CORBA::Octet& operator[](CORBA::ULong _index)
		{ return (*ptr_)[_index]; }

	private:
	    ObjectId *& ptr_;

	    // assignment from ObjectId_var not allowed
	    void operator=(const ObjectId_var&);
    };  // class ObjectId_out

    //
    // Portable Server object _ptr typedefs.
    //
    typedef ThreadPolicy *	ThreadPolicy_ptr;
    typedef LifespanPolicy *	LifespanPolicy_ptr;
    typedef IdUniquenessPolicy *	IdUniquenessPolicy_ptr;
    typedef IdAssignmentPolicy *	IdAssignmentPolicy_ptr;
    typedef ImplicitActivationPolicy *	ImplicitActivationPolicy_ptr;
    typedef ServantRetentionPolicy *	ServantRetentionPolicy_ptr;
    typedef RequestProcessingPolicy *	RequestProcessingPolicy_ptr;
    typedef StateControlPolicy *	StateControlPolicy_ptr;
    typedef ConcurrencyStrategyPolicy *	ConcurrencyStrategyPolicy_ptr;
    typedef POAManager *	POAManager_ptr;
    typedef AdapterActivator *	AdapterActivator_ptr;
    typedef ServantManager *	ServantManager_ptr;
    typedef ServantActivator *	ServantActivator_ptr;
    typedef ServantLocator *	ServantLocator_ptr;
    typedef POA *	POA_ptr;
    typedef Current *	Current_ptr;

    //
    // Language Specific Bindings
    //
    class IOPPOAEXPDLL ServantBase : public OBB::ServantBase
    {
	public:
	    virtual ~ ServantBase();


	    virtual POA_ptr _default_POA();

	    virtual void invoke (
		CORBA::ServerRequest_ptr request) = 0;

	    virtual CORBA::RepositoryId _primary_interface (
		const ObjectId & oid,
		POA_ptr poa) = 0;

		virtual void _add_ref();
		virtual void _remove_ref();

	protected:
	    ServantBase();
	    ServantBase(const ServantBase&);
	    ServantBase & operator=(const ServantBase&);
	    CORBA::Object_ptr OBB__this();

    }; // ServantBase


    class IOPPOAEXPDLL ServantBase_var
    {
	public:
	    ServantBase_var() { ptr_ = 0; }
	    ServantBase_var(ServantBase* p) { ptr_ = p; }
	    ServantBase_var(const ServantBase_var &b) : ptr_(b.ptr_) 
		{ if (ptr_) ptr_->_add_ref(); }
	    ~ServantBase_var()
		{ if (ptr_) ptr_->_remove_ref(); }

	    inline ServantBase_var& operator=(ServantBase* p)
		{ if (ptr_) ptr_->_remove_ref(); ptr_ = p; return *this; }
	    
		inline ServantBase_var& operator=(const ServantBase_var& b)
		{ if (ptr_ != b.ptr_)
			{if (ptr_) ptr_->_remove_ref(); if ((ptr_ = b.ptr_) != 0) ptr_->_add_ref(); }
			return *this; }

	    inline ServantBase* operator->() { return ptr_; }
	    inline const ServantBase* operator->() const { return ptr_; }

	    inline ServantBase* in() const { return ptr_; }
	    inline ServantBase*& inout() { return ptr_; }
	    inline ServantBase*& out()
		{ if (ptr_) ptr_->_remove_ref(); ptr_ = 0; return ptr_; }
	    inline ServantBase* _retn()
		{ ServantBase* val = ptr_; ptr_ = 0; return val; }

	private:
	    ServantBase* ptr_;
    };  // class ServantBase_var

    class IOPPOAEXPDLL RefCountServantBase : public ServantBase
    {
	public:
	    virtual ~ RefCountServantBase();


		virtual void _add_ref();
		virtual void _remove_ref();

	protected:
		RefCountServantBase();
	    
		RefCountServantBase(const RefCountServantBase&);

	    RefCountServantBase & operator=(const RefCountServantBase&);

	private:
		CORBA::ULong	_ref_count;

    }; // RefCountServantBase

    //
    // Class to get around signature differences between _add_ref in ValueBase and ServantBase
    class IOPPOAEXPDLL ValueCountBase : public virtual CORBA::ValueBase
    {
	public:
	    virtual CORBA::ValueBase_ptr _add_ref() {_addref(); return this;}

	protected:

	private:
	    ValueCountBase & operator=(const ValueCountBase&);
	    virtual void _addref() = 0;


    }; // ValueCountBase



    class IOPPOAEXPDLL ValueRefCountBase : public virtual ValueCountBase, 
					   public virtual RefCountServantBase
    {
	public:
	    virtual ~ ValueRefCountBase();


		virtual void _remove_ref();
		virtual CORBA::ULong _refcount_value() {return _ref_count;}

	protected:
		ValueRefCountBase();
	    
		ValueRefCountBase(const ValueRefCountBase&);

	    ValueRefCountBase & operator=(const ValueRefCountBase&);

	private:
		virtual void	_addref();
		CORBA::ULong	_ref_count;

    }; // ValueRefCountBase


    
    class IOPPOAEXPDLL DynamicImplementation : public ServantBase
    {
	public:
	    CORBA::Object_ptr _this();

	protected:
	    DynamicImplementation();
	    virtual ~DynamicImplementation();
    }; // DynamicImplementation

    typedef ServantBase * Servant;
    typedef void * Cookie;
    typedef Cookie& Cookie_out;

    //
    // ForwardRequest Exception
    //
    class IOPPOAEXPDLL ForwardRequest : public CORBA::SystemException
    {
	public:
	    static ForwardRequest * _narrow(CORBA::Exception_ptr);
	    void _raise();

	    ForwardRequest ( CORBA::Object_ptr _forward_reference);
	    ForwardRequest ();
	    ForwardRequest (const ForwardRequest &);
	    ~ForwardRequest ();
	    ForwardRequest & operator=(const ForwardRequest &);

	    CORBA::Object_var forward_reference;
    };  // class ForwardRequest


    class IOPPOAEXPDLL ForwardRequest_var
    {
	public:
	    ForwardRequest_var() { ptr_ = 0; }
	    ForwardRequest_var(ForwardRequest* t) { ptr_ = t; }
	    ForwardRequest_var(const ForwardRequest_var &t) : ptr_(t.ptr_) {}
	    ~ForwardRequest_var()
		{ if (ptr_) delete ptr_; }

	    inline ForwardRequest_var& operator=(ForwardRequest* t)
		{ if (ptr_) delete ptr_; ptr_ = t; return *this; }
	    inline ForwardRequest_var& operator=(const ForwardRequest_var& t)
		{ if (ptr_) { delete ptr_; ptr_ = 0; }
		  if (t.ptr_) ptr_ = new ORBNEWTHROW ForwardRequest(*t.ptr_);
		  return *this; }

	    inline ForwardRequest* operator->() { return ptr_; }
	    inline const ForwardRequest* operator->() const { return ptr_; }

	    inline ForwardRequest* in() const { return ptr_; }
	    inline ForwardRequest*& inout() { return ptr_; }
	    inline ForwardRequest*& out()
		{ if (ptr_) delete ptr_; return ptr_; }
	    inline ForwardRequest* _retn()
		{ ForwardRequest* val = ptr_; ptr_ = 0; return val; }
	private:
	    ForwardRequest* ptr_;
    };  // class ForwardRequest_var

    //
    // PortableServer::ThreadPolicy related items
    //
    enum ThreadPolicyValue { ORB_CTRL_MODEL, SINGLE_THREAD_MODEL };
    typedef ThreadPolicyValue& ThreadPolicyValue_out;
    class IOPPOAEXPDLL ThreadPolicy : public CORBA::Policy
    {
    public:
	static ThreadPolicy_ptr _duplicate(
	    ThreadPolicy_ptr obj);
	inline static ThreadPolicy_ptr _nil() { return (ThreadPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual ThreadPolicyValue value () = 0;

	protected:
	    ThreadPolicy() {};
	    virtual ~ThreadPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    ThreadPolicy (const ThreadPolicy& t);
	    void operator=(const ThreadPolicy&);

    };  // class ThreadPolicy

    class IOPPOAEXPDLL ThreadPolicy_var : public CORBA::_var {
	public:
	    ThreadPolicy_var()
		{ ptr_ = PortableServer::ThreadPolicy::_nil(); };
	    ThreadPolicy_var(ThreadPolicy_ptr p) { ptr_ = p; }
	    ThreadPolicy_var(const ThreadPolicy_var &v)
		{ ptr_ = PortableServer::ThreadPolicy::_duplicate(
		  PortableServer::ThreadPolicy_ptr(v)); }
	    ~ThreadPolicy_var() { free(); }
	    inline ThreadPolicy_var &operator=(ThreadPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline ThreadPolicy_var &operator=(const ThreadPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::ThreadPolicy::_duplicate(
		    PortableServer::ThreadPolicy_ptr(a)); }
		  return *this; }
      	    inline ThreadPolicy_ptr in() const { return ptr_; }
	    inline ThreadPolicy_ptr& inout() { return ptr_; }
	    inline ThreadPolicy_ptr& out()
		{ reset(PortableServer::ThreadPolicy::_nil()); return ptr_; }
    	    inline ThreadPolicy_ptr _retn()
		{ ThreadPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::ThreadPolicy::_nil(); return val; }
	    inline ThreadPolicy_ptr& ptr() { return ptr_; }
	    inline operator ThreadPolicy_ptr&() { return ptr_; }
	    inline operator const ThreadPolicy_ptr&() const { return ptr_; }
	    inline ThreadPolicy_ptr operator->() const { return ptr_; }

	private:
	    ThreadPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(ThreadPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class ThreadPolicy_var


    class IOPPOAEXPDLL ThreadPolicy_out {
	public:
	    ThreadPolicy_out(ThreadPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::ThreadPolicy::_nil(); }
	    ThreadPolicy_out(ThreadPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = ThreadPolicy::_nil(); }
	    ThreadPolicy_out(const ThreadPolicy_out& a) : ptr_(a.ptr_) {}
	    inline ThreadPolicy_out& operator=(ThreadPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ThreadPolicy_out& operator=(const ThreadPolicy_var& a)
		{ ptr_ = PortableServer::ThreadPolicy::_duplicate(
		  ThreadPolicy_ptr(a)); return *this; }
	    inline ThreadPolicy_out& operator=(ThreadPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator ThreadPolicy_ptr&() { return ptr_; }
	    inline ThreadPolicy_ptr& ptr() { return ptr_; }
	    inline ThreadPolicy_ptr operator->() { return ptr_; }

	private:
	    ThreadPolicy_ptr& ptr_;
    };  // class ThreadPolicy_out

    //
    // PortableServer::LifeSpanPolicy related items
    //
    enum  LifespanPolicyValue { TRANSIENT, PERSISTENT };
    typedef LifespanPolicyValue& LifespanPolicyValue_out;
    class IOPPOAEXPDLL LifespanPolicy : public CORBA::Policy
    {
    public:
	static LifespanPolicy_ptr _duplicate(
	    LifespanPolicy_ptr obj);
	inline static LifespanPolicy_ptr _nil() { return (LifespanPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual LifespanPolicyValue value () = 0;

	protected:
	    LifespanPolicy() {};
	    virtual ~LifespanPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    LifespanPolicy (const LifespanPolicy& t);
	    void operator=(const LifespanPolicy&);

    };  // class LifespanPolicy

    class IOPPOAEXPDLL LifespanPolicy_var : public CORBA::_var {
	public:
	    LifespanPolicy_var()
		{ ptr_ = PortableServer::LifespanPolicy::_nil(); };
	    LifespanPolicy_var(LifespanPolicy_ptr p) { ptr_ = p; }
	    LifespanPolicy_var(const LifespanPolicy_var &v)
		{ ptr_ = PortableServer::LifespanPolicy::_duplicate(
		  PortableServer::LifespanPolicy_ptr(v)); }
	    ~LifespanPolicy_var() { free(); }
	    inline LifespanPolicy_var &operator=(LifespanPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline LifespanPolicy_var &operator=(const LifespanPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::LifespanPolicy::_duplicate(
		    PortableServer::LifespanPolicy_ptr(a)); }
		  return *this; }
      	    inline LifespanPolicy_ptr in() const { return ptr_; }
	    inline LifespanPolicy_ptr& inout() { return ptr_; }
	    inline LifespanPolicy_ptr& out()
		{ reset(PortableServer::LifespanPolicy::_nil()); return ptr_; }
    	    inline LifespanPolicy_ptr _retn()
		{ LifespanPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::LifespanPolicy::_nil(); return val; }
	    inline LifespanPolicy_ptr& ptr() { return ptr_; }
	    inline operator LifespanPolicy_ptr&() { return ptr_; }
	    inline operator const LifespanPolicy_ptr&() const { return ptr_; }
	    inline LifespanPolicy_ptr operator->() const { return ptr_; }

	private:
	    LifespanPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(LifespanPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class LifespanPolicy_var


    class IOPPOAEXPDLL LifespanPolicy_out {
	public:
	    LifespanPolicy_out(LifespanPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::LifespanPolicy::_nil(); }
	    LifespanPolicy_out(LifespanPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = LifespanPolicy::_nil(); }
	    LifespanPolicy_out(const LifespanPolicy_out& a) : ptr_(a.ptr_) {}
	    inline LifespanPolicy_out& operator=(LifespanPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline LifespanPolicy_out& operator=(const LifespanPolicy_var& a)
		{ ptr_ = PortableServer::LifespanPolicy::_duplicate(
		  LifespanPolicy_ptr(a)); return *this; }
	    inline LifespanPolicy_out& operator=(LifespanPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator LifespanPolicy_ptr&() { return ptr_; }
	    inline LifespanPolicy_ptr& ptr() { return ptr_; }
	    inline LifespanPolicy_ptr operator->() { return ptr_; }

	private:
	    LifespanPolicy_ptr& ptr_;
    };  // class LifespanPolicy_out

    //
    // PortableServer::IdUniquenessPolicy related items
    //
    enum  IdUniquenessPolicyValue {UNIQUE_ID, MULTIPLE_ID };
    typedef IdUniquenessPolicyValue& IdUniquenessPolicyValue_out;
    class IOPPOAEXPDLL IdUniquenessPolicy : public CORBA::Policy
    {
    public:
	static IdUniquenessPolicy_ptr _duplicate(
	    IdUniquenessPolicy_ptr obj);
	inline static IdUniquenessPolicy_ptr _nil()
	    { return (IdUniquenessPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual IdUniquenessPolicyValue value () = 0;

	protected:
	    IdUniquenessPolicy() {};
	    virtual ~IdUniquenessPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    IdUniquenessPolicy (const IdUniquenessPolicy& t);
	    void operator=(const IdUniquenessPolicy&);

    };  // class IdUniquenessPolicy

    class IOPPOAEXPDLL IdUniquenessPolicy_var : public CORBA::_var {
	public:
	    IdUniquenessPolicy_var()
		{ ptr_ = PortableServer::IdUniquenessPolicy::_nil(); };
	    IdUniquenessPolicy_var(IdUniquenessPolicy_ptr p) { ptr_ = p; }
	    IdUniquenessPolicy_var(const IdUniquenessPolicy_var &v)
		{ ptr_ = PortableServer::IdUniquenessPolicy::_duplicate(
		  PortableServer::IdUniquenessPolicy_ptr(v)); }
	    ~IdUniquenessPolicy_var() { free(); }
	    inline IdUniquenessPolicy_var &operator=(IdUniquenessPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline IdUniquenessPolicy_var &operator=(const IdUniquenessPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::IdUniquenessPolicy::_duplicate(
		    PortableServer::IdUniquenessPolicy_ptr(a)); }
		  return *this; }
      	    inline IdUniquenessPolicy_ptr in() const { return ptr_; }
	    inline IdUniquenessPolicy_ptr& inout() { return ptr_; }
	    inline IdUniquenessPolicy_ptr& out()
		{ reset(PortableServer::IdUniquenessPolicy::_nil()); return ptr_; }
    	    inline IdUniquenessPolicy_ptr _retn()
		{ IdUniquenessPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::IdUniquenessPolicy::_nil(); return val; }
	    inline IdUniquenessPolicy_ptr& ptr() { return ptr_; }
	    inline operator IdUniquenessPolicy_ptr&() { return ptr_; }
	    inline operator const IdUniquenessPolicy_ptr& () const { return ptr_; }
	    inline IdUniquenessPolicy_ptr operator->() const { return ptr_; }

	private:
	    IdUniquenessPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(IdUniquenessPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class IdUniquenessPolicy_var


    class IOPPOAEXPDLL IdUniquenessPolicy_out {
	public:
	    IdUniquenessPolicy_out(IdUniquenessPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::IdUniquenessPolicy::_nil(); }
	    IdUniquenessPolicy_out(IdUniquenessPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = IdUniquenessPolicy::_nil(); }
	    IdUniquenessPolicy_out(const IdUniquenessPolicy_out& a) : ptr_(a.ptr_) {}
	    inline IdUniquenessPolicy_out& operator=(IdUniquenessPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline IdUniquenessPolicy_out& operator=(const IdUniquenessPolicy_var& a)
		{ ptr_ = PortableServer::IdUniquenessPolicy::_duplicate(
		  IdUniquenessPolicy_ptr(a)); return *this; }
	    inline IdUniquenessPolicy_out& operator=(IdUniquenessPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator IdUniquenessPolicy_ptr&() { return ptr_; }
	    inline IdUniquenessPolicy_ptr& ptr() { return ptr_; }
	    inline IdUniquenessPolicy_ptr operator->() { return ptr_; }

	private:
	    IdUniquenessPolicy_ptr& ptr_;
    };  // class IdUniquenessPolicy_out


    //
    // PortableServer::IdAssignmentPolicy related items
    //
    enum  IdAssignmentPolicyValue {USER_ID, SYSTEM_ID };
    typedef IdAssignmentPolicyValue& IdAssignmentPolicyValue_out;
    class IOPPOAEXPDLL IdAssignmentPolicy : public CORBA::Policy
    {
    public:
	static IdAssignmentPolicy_ptr _duplicate(
	    IdAssignmentPolicy_ptr obj);
	inline static IdAssignmentPolicy_ptr _nil()
	    { return (IdAssignmentPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual IdAssignmentPolicyValue value () = 0;

	protected:
	    IdAssignmentPolicy() {};
	    virtual ~IdAssignmentPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    IdAssignmentPolicy (const IdAssignmentPolicy& t);
	    void operator=(const IdAssignmentPolicy&);

    };  // class IdAssignmentPolicy

    class IOPPOAEXPDLL IdAssignmentPolicy_var : public CORBA::_var {
	public:
	    IdAssignmentPolicy_var()
		{ ptr_ = PortableServer::IdAssignmentPolicy::_nil(); };
	    IdAssignmentPolicy_var(IdAssignmentPolicy_ptr p) { ptr_ = p; }
	    IdAssignmentPolicy_var(const IdAssignmentPolicy_var &v)
		{ ptr_ = PortableServer::IdAssignmentPolicy::_duplicate(
		  PortableServer::IdAssignmentPolicy_ptr(v)); }
	    ~IdAssignmentPolicy_var() { free(); }
	    inline IdAssignmentPolicy_var &operator=(IdAssignmentPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
 	    inline IdAssignmentPolicy_var &operator=(const IdAssignmentPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::IdAssignmentPolicy::_duplicate(
		    PortableServer::IdAssignmentPolicy_ptr(a)); }
		  return *this; }
      	    inline IdAssignmentPolicy_ptr in() const { return ptr_; }
	    inline IdAssignmentPolicy_ptr& inout() { return ptr_; }
	    inline IdAssignmentPolicy_ptr& out()
		{ reset(PortableServer::IdAssignmentPolicy::_nil()); return ptr_; }
    	    inline IdAssignmentPolicy_ptr _retn()
		{ IdAssignmentPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::IdAssignmentPolicy::_nil(); return val; }
	    inline IdAssignmentPolicy_ptr& ptr() { return ptr_; }
	    inline operator IdAssignmentPolicy_ptr&() { return ptr_; }
	    inline operator const IdAssignmentPolicy_ptr& () const { return ptr_; }
	    inline IdAssignmentPolicy_ptr operator->() const { return ptr_; }

	private:
	    IdAssignmentPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(IdAssignmentPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class IdAssignmentPolicy_var


    class IOPPOAEXPDLL IdAssignmentPolicy_out {
	public:
	    IdAssignmentPolicy_out(IdAssignmentPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::IdAssignmentPolicy::_nil(); }
	    IdAssignmentPolicy_out(IdAssignmentPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = IdAssignmentPolicy::_nil(); }
	    IdAssignmentPolicy_out(const IdAssignmentPolicy_out& a) : ptr_(a.ptr_) {}
	    inline IdAssignmentPolicy_out& operator=(IdAssignmentPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline IdAssignmentPolicy_out& operator=(const IdAssignmentPolicy_var& a)
		{ ptr_ = PortableServer::IdAssignmentPolicy::_duplicate(
		  IdAssignmentPolicy_ptr(a)); return *this; }
	    inline IdAssignmentPolicy_out& operator=(IdAssignmentPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator IdAssignmentPolicy_ptr&() { return ptr_; }
	    inline IdAssignmentPolicy_ptr& ptr() { return ptr_; }
	    inline IdAssignmentPolicy_ptr operator->() { return ptr_; }

	private:
	    IdAssignmentPolicy_ptr& ptr_;
    };  // class IdAssignmentPolicy_out


    //
    // PortableServer::ImplicitActivationPolicy related items
    //
    enum  ImplicitActivationPolicyValue {
	    IMPLICIT_ACTIVATION, NO_IMPLICIT_ACTIVATION };
    typedef ImplicitActivationPolicyValue& ImplicitActivationPolicyValue_out;
    class IOPPOAEXPDLL ImplicitActivationPolicy : public CORBA::Policy
    {
    public:
	static ImplicitActivationPolicy_ptr _duplicate(
	    ImplicitActivationPolicy_ptr obj);
	inline static ImplicitActivationPolicy_ptr _nil()
	    { return (ImplicitActivationPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual ImplicitActivationPolicyValue value () = 0;

	protected:
	    ImplicitActivationPolicy() {};
	    virtual ~ImplicitActivationPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    ImplicitActivationPolicy (const ImplicitActivationPolicy& t);
	    void operator=(const ImplicitActivationPolicy&);

    };  // class ImplicitActivationPolicy

    class IOPPOAEXPDLL ImplicitActivationPolicy_var : public CORBA::_var {
	public:
	    ImplicitActivationPolicy_var()
		{ ptr_ = PortableServer::ImplicitActivationPolicy::_nil(); };
	    ImplicitActivationPolicy_var(ImplicitActivationPolicy_ptr p)
		{ ptr_ = p; }
	    ImplicitActivationPolicy_var(const ImplicitActivationPolicy_var &v)
		{ ptr_ = PortableServer::ImplicitActivationPolicy::_duplicate(
		  PortableServer::ImplicitActivationPolicy_ptr(v)); }
	    ~ImplicitActivationPolicy_var() { free(); }
	    inline ImplicitActivationPolicy_var &operator=(ImplicitActivationPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline ImplicitActivationPolicy_var &operator=(const ImplicitActivationPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::ImplicitActivationPolicy::_duplicate(
		    PortableServer::ImplicitActivationPolicy_ptr(a)); }
		  return *this; }
      	    inline ImplicitActivationPolicy_ptr in() const { return ptr_; }
	    inline ImplicitActivationPolicy_ptr& inout() { return ptr_; }
	    inline ImplicitActivationPolicy_ptr& out()
		{ reset(PortableServer::ImplicitActivationPolicy::_nil()); return ptr_; }
    	    inline ImplicitActivationPolicy_ptr _retn()
		{ ImplicitActivationPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::ImplicitActivationPolicy::_nil(); return val; }
	    inline ImplicitActivationPolicy_ptr& ptr() { return ptr_; }
	    inline operator ImplicitActivationPolicy_ptr&() { return ptr_; }
	    inline operator const ImplicitActivationPolicy_ptr& () const { return ptr_; }
	    inline ImplicitActivationPolicy_ptr operator->() const { return ptr_; }

	private:
	    ImplicitActivationPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(ImplicitActivationPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class ImplicitActivationPolicy_var

    class IOPPOAEXPDLL ImplicitActivationPolicy_out {
	public:
	    ImplicitActivationPolicy_out(ImplicitActivationPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::ImplicitActivationPolicy::_nil(); }
	    ImplicitActivationPolicy_out(ImplicitActivationPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = ImplicitActivationPolicy::_nil(); }
	    ImplicitActivationPolicy_out(const ImplicitActivationPolicy_out& a) : ptr_(a.ptr_) {}
	    inline ImplicitActivationPolicy_out& operator=(ImplicitActivationPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ImplicitActivationPolicy_out& operator=(const ImplicitActivationPolicy_var& a)
		{ ptr_ = PortableServer::ImplicitActivationPolicy::_duplicate(
		  ImplicitActivationPolicy_ptr(a)); return *this; }
	    inline ImplicitActivationPolicy_out& operator=(ImplicitActivationPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator ImplicitActivationPolicy_ptr&() { return ptr_; }
	    inline ImplicitActivationPolicy_ptr& ptr() { return ptr_; }
	    inline ImplicitActivationPolicy_ptr operator->() { return ptr_; }

	private:
	    ImplicitActivationPolicy_ptr& ptr_;
    };  // class ImplicitActivationPolicy_out


    //
    // PortableServer::ServantRetentionPolicy related items
    //
    enum  ServantRetentionPolicyValue {RETAIN, NON_RETAIN };
    typedef ServantRetentionPolicyValue& ServantRetentionPolicyValue_out;
    class IOPPOAEXPDLL ServantRetentionPolicy : public CORBA::Policy
    {
    public:
	static ServantRetentionPolicy_ptr _duplicate(
	    ServantRetentionPolicy_ptr obj);
	inline static ServantRetentionPolicy_ptr _nil() { return (ServantRetentionPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual ServantRetentionPolicyValue value () = 0;

	protected:
	    ServantRetentionPolicy() {};
	    virtual ~ServantRetentionPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    ServantRetentionPolicy (const ServantRetentionPolicy& t);
	    void operator=(const ServantRetentionPolicy&);

    };  // class ServantRetentionPolicy

    class IOPPOAEXPDLL ServantRetentionPolicy_var : public CORBA::_var {
	public:
	    ServantRetentionPolicy_var()
		{ ptr_ = PortableServer::ServantRetentionPolicy::_nil(); };
	    ServantRetentionPolicy_var(ServantRetentionPolicy_ptr p)
		{ ptr_ = p; }
	    ServantRetentionPolicy_var(const ServantRetentionPolicy_var &v)
		{ ptr_ = PortableServer::ServantRetentionPolicy::_duplicate(
		  PortableServer::ServantRetentionPolicy_ptr(v)); }
	    ~ServantRetentionPolicy_var() { free(); }
	    inline ServantRetentionPolicy_var &operator=(ServantRetentionPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline ServantRetentionPolicy_var &operator=(const ServantRetentionPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::ServantRetentionPolicy::_duplicate(
		    PortableServer::ServantRetentionPolicy_ptr(a)); }
		  return *this; }
      	    inline ServantRetentionPolicy_ptr in() const { return ptr_; }
	    inline ServantRetentionPolicy_ptr& inout() { return ptr_; }
	    inline ServantRetentionPolicy_ptr& out()
		{ reset(PortableServer::ServantRetentionPolicy::_nil()); return ptr_; }
    	    inline ServantRetentionPolicy_ptr _retn()
		{ ServantRetentionPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::ServantRetentionPolicy::_nil(); return val; }
	    inline ServantRetentionPolicy_ptr& ptr() { return ptr_; }
	    inline operator ServantRetentionPolicy_ptr&() { return ptr_; }
	    inline operator const ServantRetentionPolicy_ptr& () const { return ptr_; }
	    inline ServantRetentionPolicy_ptr operator->() const { return ptr_; }

	private:
	    ServantRetentionPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(ServantRetentionPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class ServantRetentionPolicy_var

    class IOPPOAEXPDLL ServantRetentionPolicy_out {
	public:
	    ServantRetentionPolicy_out(ServantRetentionPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::ServantRetentionPolicy::_nil(); }
	    ServantRetentionPolicy_out(ServantRetentionPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = ServantRetentionPolicy::_nil(); }
	    ServantRetentionPolicy_out(const ServantRetentionPolicy_out& a) : ptr_(a.ptr_) {}
	    inline ServantRetentionPolicy_out& operator=(ServantRetentionPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ServantRetentionPolicy_out& operator=(const ServantRetentionPolicy_var& a)
		{ ptr_ = PortableServer::ServantRetentionPolicy::_duplicate(
		  ServantRetentionPolicy_ptr(a)); return *this; }
	    inline ServantRetentionPolicy_out& operator=(ServantRetentionPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator ServantRetentionPolicy_ptr&() { return ptr_; }
	    inline ServantRetentionPolicy_ptr& ptr() { return ptr_; }
	    inline ServantRetentionPolicy_ptr operator->() { return ptr_; }

	private:
	    ServantRetentionPolicy_ptr& ptr_;
    };  // class ServantRetentionPolicy_out


    //
    // PortableServer::RequestProcessingPolicy related items
    //
    enum  RequestProcessingPolicyValue {
	USE_ACTIVE_OBJECT_MAP_ONLY, USE_DEFAULT_SERVANT, USE_SERVANT_MANAGER };
    typedef RequestProcessingPolicyValue& RequestProcessingPolicyValue_out;
    class IOPPOAEXPDLL RequestProcessingPolicy : public CORBA::Policy
    {
    public:
	static RequestProcessingPolicy_ptr _duplicate(
	    RequestProcessingPolicy_ptr obj);
	inline static RequestProcessingPolicy_ptr _nil()
	    { return (RequestProcessingPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual RequestProcessingPolicyValue value () = 0;

	protected:
	    RequestProcessingPolicy() {};
	    virtual ~RequestProcessingPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    RequestProcessingPolicy (const RequestProcessingPolicy& t);
	    void operator=(const RequestProcessingPolicy&);

    };  // class RequestProcessingPolicy

    class IOPPOAEXPDLL RequestProcessingPolicy_var : public CORBA::_var {
	public:
	    RequestProcessingPolicy_var()
		{ ptr_ = PortableServer::RequestProcessingPolicy::_nil(); };
	    RequestProcessingPolicy_var(RequestProcessingPolicy_ptr p)
		{ ptr_ = p; }
	    RequestProcessingPolicy_var(const RequestProcessingPolicy_var &v)
		{ ptr_ = PortableServer::RequestProcessingPolicy::_duplicate(
		  PortableServer::RequestProcessingPolicy_ptr(v)); }
	    ~RequestProcessingPolicy_var() { free(); }
	    inline RequestProcessingPolicy_var &operator=(RequestProcessingPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline RequestProcessingPolicy_var &operator=(const RequestProcessingPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::RequestProcessingPolicy::_duplicate(
		    PortableServer::RequestProcessingPolicy_ptr(a)); }
		  return *this; }
      	    inline RequestProcessingPolicy_ptr in() const { return ptr_; }
	    inline RequestProcessingPolicy_ptr& inout() { return ptr_; }
	    inline RequestProcessingPolicy_ptr& out()
		{ reset(PortableServer::RequestProcessingPolicy::_nil()); return ptr_; }
    	    inline RequestProcessingPolicy_ptr _retn()
		{ RequestProcessingPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::RequestProcessingPolicy::_nil(); return val; }
	    inline RequestProcessingPolicy_ptr& ptr() { return ptr_; }
	    inline operator RequestProcessingPolicy_ptr&() { return ptr_; }
	    inline operator const RequestProcessingPolicy_ptr& () const { return ptr_; }
	    inline RequestProcessingPolicy_ptr operator->() const { return ptr_; }

	private:
	    RequestProcessingPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(RequestProcessingPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class RequestProcessingPolicy_var

    class IOPPOAEXPDLL RequestProcessingPolicy_out {
	public:
	    RequestProcessingPolicy_out(RequestProcessingPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::RequestProcessingPolicy::_nil(); }
	    RequestProcessingPolicy_out(RequestProcessingPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = RequestProcessingPolicy::_nil(); }
	    RequestProcessingPolicy_out(const RequestProcessingPolicy_out& a) : ptr_(a.ptr_) {}
	    inline RequestProcessingPolicy_out& operator=(RequestProcessingPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline RequestProcessingPolicy_out& operator=(const RequestProcessingPolicy_var& a)
		{ ptr_ = PortableServer::RequestProcessingPolicy::_duplicate(
		  RequestProcessingPolicy_ptr(a)); return *this; }
	    inline RequestProcessingPolicy_out& operator=(RequestProcessingPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator RequestProcessingPolicy_ptr&() { return ptr_; }
	    inline RequestProcessingPolicy_ptr& ptr() { return ptr_; }
	    inline RequestProcessingPolicy_ptr operator->() { return ptr_; }

	private:
	    RequestProcessingPolicy_ptr& ptr_;
    };  // class RequestProcessingPolicy_out


    //
    // PortableServer::StateControlPolicy related items
    //
    enum  StateControlPolicyValue { STATEFUL, STATELESS };
    typedef StateControlPolicyValue& StateControlPolicyValue_out;
    class IOPPOAEXPDLL StateControlPolicy : public CORBA::Policy
    {
    public:
	static StateControlPolicy_ptr _duplicate(
	    StateControlPolicy_ptr obj);
	inline static StateControlPolicy_ptr _nil()
	    { return (StateControlPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual StateControlPolicyValue value () = 0;

	protected:
	    StateControlPolicy() {};
	    virtual ~StateControlPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    StateControlPolicy (const StateControlPolicy& t);
	    void operator=(const StateControlPolicy&);

    };  // class StateControlPolicy

    class IOPPOAEXPDLL StateControlPolicy_var : public CORBA::_var {
	public:
	    StateControlPolicy_var()
		{ ptr_ = PortableServer::StateControlPolicy::_nil(); };
	    StateControlPolicy_var(StateControlPolicy_ptr p)
		{ ptr_ = p; }
	    StateControlPolicy_var(const StateControlPolicy_var &v)
		{ ptr_ = PortableServer::StateControlPolicy::_duplicate(
		  PortableServer::StateControlPolicy_ptr(v)); }
	    ~StateControlPolicy_var() { free(); }
	    inline StateControlPolicy_var &operator=(StateControlPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline StateControlPolicy_var &operator=(const StateControlPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::StateControlPolicy::_duplicate(
		    PortableServer::StateControlPolicy_ptr(a)); }
		  return *this; }
      	    inline StateControlPolicy_ptr in() const { return ptr_; }
	    inline StateControlPolicy_ptr& inout() { return ptr_; }
	    inline StateControlPolicy_ptr& out()
		{ reset(PortableServer::StateControlPolicy::_nil()); return ptr_; }
    	    inline StateControlPolicy_ptr _retn()
		{ StateControlPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::StateControlPolicy::_nil(); return val; }
	    inline StateControlPolicy_ptr& ptr() { return ptr_; }
	    inline operator StateControlPolicy_ptr&() { return ptr_; }
	    inline operator const StateControlPolicy_ptr& () const { return ptr_; }
	    inline StateControlPolicy_ptr operator->() const { return ptr_; }

	private:
	    StateControlPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(StateControlPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class StateControlPolicy_var

    class IOPPOAEXPDLL StateControlPolicy_out {
	public:
	    StateControlPolicy_out(StateControlPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::StateControlPolicy::_nil(); }
	    StateControlPolicy_out(StateControlPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = StateControlPolicy::_nil(); }
	    StateControlPolicy_out(const StateControlPolicy_out& a) : ptr_(a.ptr_) {}
	    inline StateControlPolicy_out& operator=(StateControlPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline StateControlPolicy_out& operator=(const StateControlPolicy_var& a)
		{ ptr_ = PortableServer::StateControlPolicy::_duplicate(
		  StateControlPolicy_ptr(a)); return *this; }
	    inline StateControlPolicy_out& operator=(StateControlPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator StateControlPolicy_ptr&() { return ptr_; }
	    inline StateControlPolicy_ptr& ptr() { return ptr_; }
	    inline StateControlPolicy_ptr operator->() { return ptr_; }

	private:
	    StateControlPolicy_ptr& ptr_;
    };  // class StateControlPolicy_out


    //
    // PortableServer::ConcurrencyStrategyPolicy related items
    //
    enum  ConcurrencyStrategyPolicyValue { PER_REQUEST, PER_OBJECT };
    typedef ConcurrencyStrategyPolicyValue& ConcurrencyStrategyPolicyValue_out;
    class IOPPOAEXPDLL ConcurrencyStrategyPolicy : public CORBA::Policy
    {
    public:
	static ConcurrencyStrategyPolicy_ptr _duplicate(
	    ConcurrencyStrategyPolicy_ptr obj);
	inline static ConcurrencyStrategyPolicy_ptr _nil()
	    { return (ConcurrencyStrategyPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual ConcurrencyStrategyPolicyValue value () = 0;

	protected:
	    ConcurrencyStrategyPolicy() {};
	    virtual ~ConcurrencyStrategyPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    ConcurrencyStrategyPolicy (const ConcurrencyStrategyPolicy& t);
	    void operator=(const ConcurrencyStrategyPolicy&);

    };  // class ConcurrencyStrategyPolicy

    class IOPPOAEXPDLL ConcurrencyStrategyPolicy_var : public CORBA::_var {
	public:
	   ConcurrencyStrategyPolicy_var()
		{ ptr_ = PortableServer::ConcurrencyStrategyPolicy::_nil(); };
	    ConcurrencyStrategyPolicy_var(ConcurrencyStrategyPolicy_ptr p)
		{ ptr_ = p; }
	    ConcurrencyStrategyPolicy_var(const ConcurrencyStrategyPolicy_var &v)
		{ ptr_ = PortableServer::ConcurrencyStrategyPolicy::_duplicate(
		  PortableServer::ConcurrencyStrategyPolicy_ptr(v)); }
	    ~ConcurrencyStrategyPolicy_var() { free(); }
	    inline ConcurrencyStrategyPolicy_var &operator=(ConcurrencyStrategyPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline ConcurrencyStrategyPolicy_var &operator=(const ConcurrencyStrategyPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::ConcurrencyStrategyPolicy::_duplicate(
		    PortableServer::ConcurrencyStrategyPolicy_ptr(a)); }
		  return *this; }
      	    inline ConcurrencyStrategyPolicy_ptr in() const { return ptr_; }
	    inline ConcurrencyStrategyPolicy_ptr& inout() { return ptr_; }
	    inline ConcurrencyStrategyPolicy_ptr& out()
		{ reset(PortableServer::ConcurrencyStrategyPolicy::_nil()); return ptr_; }
    	    inline ConcurrencyStrategyPolicy_ptr _retn()
		{ ConcurrencyStrategyPolicy_ptr val = ptr_;
		  ptr_ = PortableServer::ConcurrencyStrategyPolicy::_nil(); return val; }
	    inline ConcurrencyStrategyPolicy_ptr& ptr() { return ptr_; }
	    inline operator ConcurrencyStrategyPolicy_ptr&() { return ptr_; }
	    inline operator const ConcurrencyStrategyPolicy_ptr& () const { return ptr_; }
	    inline ConcurrencyStrategyPolicy_ptr operator->() const { return ptr_; }

	private:
	    ConcurrencyStrategyPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(ConcurrencyStrategyPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class ConcurrencyStrategyPolicy_var

    class IOPPOAEXPDLL ConcurrencyStrategyPolicy_out {
	public:
	    ConcurrencyStrategyPolicy_out(ConcurrencyStrategyPolicy_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::ConcurrencyStrategyPolicy::_nil(); }
	    ConcurrencyStrategyPolicy_out(ConcurrencyStrategyPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = ConcurrencyStrategyPolicy::_nil(); }
	    ConcurrencyStrategyPolicy_out(const ConcurrencyStrategyPolicy_out& a) : ptr_(a.ptr_) {}
	    inline ConcurrencyStrategyPolicy_out& operator=(ConcurrencyStrategyPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ConcurrencyStrategyPolicy_out& operator=(const ConcurrencyStrategyPolicy_var& a)
		{ ptr_ = PortableServer::ConcurrencyStrategyPolicy::_duplicate(
		  ConcurrencyStrategyPolicy_ptr(a)); return *this; }
	    inline ConcurrencyStrategyPolicy_out& operator=(ConcurrencyStrategyPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator ConcurrencyStrategyPolicy_ptr&() { return ptr_; }
	    inline ConcurrencyStrategyPolicy_ptr& ptr() { return ptr_; }
	    inline ConcurrencyStrategyPolicy_ptr operator->() { return ptr_; }

	private:
	    ConcurrencyStrategyPolicy_ptr& ptr_;
    };  // class ConcurrencyStrategyPolicy_out

    //
    // PortableServer::POAManager related items
    //
    class IOPPOAEXPDLL POAManager : public CORBA::Object
    {
	public:
	    static POAManager_ptr _duplicate(
		POAManager_ptr obj);
	    inline static POAManager_ptr _nil() { return (POAManager_ptr) 0; }

	    class IOPPOAEXPDLL AdapterInactive : public CORBA::SystemException
	    {
		public:
		    static AdapterInactive * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    AdapterInactive ();
		    AdapterInactive (const AdapterInactive &);
		    ~AdapterInactive ();
		    AdapterInactive & operator=(const AdapterInactive &);
	    };  // class AdapterInactive


	    virtual void activate () = 0;

	    virtual void hold_requests (
		CORBA::Boolean wait_for_completion) = 0;

	    virtual void discard_requests (
		CORBA::Boolean wait_for_completion) = 0;

	    virtual void deactivate (
		CORBA::Boolean etherealize_objects,
		CORBA::Boolean wait_for_completion) = 0;

	protected:
	    POAManager() {m_managed_obj = CORBA_TRUE;}
	    virtual ~POAManager() {}

	private:
	    // Hidden functions to disallow direct copy.
	    POAManager( const POAManager& t);
	    void operator=(const POAManager&);
    };  // class POAManager

    class IOPPOAEXPDLL POAManager_var : public CORBA::_var {
	public:
	    POAManager_var();
	    POAManager_var(POAManager_ptr p) {ptr_ = p; }
	    POAManager_var(const POAManager_var &a);
	    ~POAManager_var() { free();}

	    inline POAManager_var& operator=(POAManager_ptr p)
		{ if (p != ptr_) reset(p);
		  return *this; }

	    inline POAManager_var& operator=(const POAManager_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::POAManager::_duplicate(
		    PortableServer::POAManager_ptr(a)); }
		  return *this; }
	    inline POAManager_ptr in() const { return ptr_; }
	    inline POAManager_ptr& inout() { return ptr_; }
	    inline POAManager_ptr& out()
		{ reset(PortableServer::POAManager::_nil()); return ptr_; }
	    inline POAManager_ptr _retn()
		{ POAManager_ptr val = ptr_;
		  ptr_ = PortableServer::POAManager::_nil(); return val; }
	    inline POAManager_ptr& ptr() { return ptr_; }
	    inline operator POAManager_ptr&() { return ptr_; }
	    inline operator const POAManager_ptr&() const { return ptr_; }
	    inline POAManager_ptr operator->() const { return ptr_; }

	protected:
	    POAManager_ptr ptr_;
	    inline void free() { CORBA::release(ptr_); }
	    inline void reset(POAManager_ptr p) { free(); ptr_ = p; }

	private:
	    void operator=(const CORBA::_var &);
    };  // class POAManager_var

    class IOPPOAEXPDLL POAManager_out {
	public:
	    POAManager_out(POAManager_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::POAManager::_nil(); }
	    POAManager_out(POAManager_var& p) : ptr_(p.ptr())
		{ CORBA::release(ptr_); ptr_ = POAManager::_nil(); }
	    POAManager_out(const POAManager_out& a) : ptr_(a.ptr_) {}
	    inline POAManager_out& operator=(POAManager_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline POAManager_out& operator=(const POAManager_var& a)
		{ ptr_ = PortableServer::POAManager::_duplicate(
		  POAManager_ptr(a)); return *this; }
	    inline POAManager_out& operator=(POAManager_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator POAManager_ptr&() { return ptr_; }
	    inline POAManager_ptr& ptr() { return ptr_; }
	    inline POAManager_ptr operator->() { return ptr_; }

	private:
	    POAManager_ptr& ptr_;
    };  // class POAManager_out

    //
    // PortableServer::AdapterActivator related items
    //
    class IOPPOAEXPDLL AdapterActivator : public virtual CORBA::Object
     {
	public:
	    static AdapterActivator_ptr _duplicate(
		AdapterActivator_ptr obj);
	    inline static AdapterActivator_ptr _nil()
		{ return (AdapterActivator_ptr) 0;}

	    virtual CORBA::Boolean unknown_adapter (
		POA_ptr parent,
		const char * name) = 0;

	protected:
	    AdapterActivator();
	    virtual ~AdapterActivator() {}

	private:
	    // Hidden functions to disallow direct copy.
	    AdapterActivator( const AdapterActivator& t);
	    void operator=(const AdapterActivator&);
    };  // class AdapterActivator

    class IOPPOAEXPDLL AdapterActivator_var : public CORBA::_var {
	public:
	    AdapterActivator_var()
		{ ptr_ = PortableServer::AdapterActivator::_nil(); };
	    AdapterActivator_var(AdapterActivator_ptr p) { ptr_ = p; }
	    AdapterActivator_var(const AdapterActivator_var &v)
		{ ptr_ = PortableServer::AdapterActivator::_duplicate(
		  PortableServer::AdapterActivator_ptr(v)); }
	    ~AdapterActivator_var() { free(); }
	    inline AdapterActivator_var &operator=(AdapterActivator_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline AdapterActivator_var &operator=(const AdapterActivator_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::AdapterActivator::_duplicate(
		    PortableServer::AdapterActivator_ptr(a)); }
		  return *this; }
      	    inline AdapterActivator_ptr in() const { return ptr_; }
	    inline AdapterActivator_ptr& inout() { return ptr_; }
	    inline AdapterActivator_ptr& out()
		{ reset(PortableServer::AdapterActivator::_nil()); return ptr_; }
    	    inline AdapterActivator_ptr _retn()
		{ AdapterActivator_ptr val = ptr_;
		  ptr_ = PortableServer::AdapterActivator::_nil(); return val; }
	    inline AdapterActivator_ptr& ptr() { return ptr_; }
	    inline operator AdapterActivator_ptr&() { return ptr_; }
	    inline operator const AdapterActivator_ptr& () const { return ptr_; }
	    inline AdapterActivator_ptr operator->() const { return ptr_; }

	private:
	    AdapterActivator_ptr ptr_;
	    inline void free() { CORBA::release(ptr_); }
	    inline void reset(AdapterActivator_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class AdapterActivator_var

    class IOPPOAEXPDLL AdapterActivator_out {
	public:
	    AdapterActivator_out(AdapterActivator_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::AdapterActivator::_nil(); }
	    AdapterActivator_out(AdapterActivator_var& p) : ptr_(p.ptr())
		{ CORBA::release(ptr_); ptr_ = AdapterActivator::_nil(); }
	    AdapterActivator_out(const AdapterActivator_out& a) : ptr_(a.ptr_) {}
	    inline AdapterActivator_out& operator=(AdapterActivator_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline AdapterActivator_out& operator=(const AdapterActivator_var& a)
		{ ptr_ = PortableServer::AdapterActivator::_duplicate(
		  AdapterActivator_ptr(a)); return *this; }
	    inline AdapterActivator_out& operator=(AdapterActivator_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator AdapterActivator_ptr&() { return ptr_; }
	    inline AdapterActivator_ptr& ptr() { return ptr_; }
	    inline AdapterActivator_ptr operator->() { return ptr_; }

	private:
	    AdapterActivator_ptr& ptr_;
    };  // class AdapterActivator_out


    //
    // PortableServer::ServantManager related items
    //
    class IOPPOAEXPDLL ServantManager : public OBB::ServantManager
    {
	public:
	    static ServantManager_ptr _duplicate(
		ServantManager_ptr obj);
	    inline static ServantManager_ptr _nil() { return (ServantManager_ptr) 0;}

	protected:
	    ServantManager() {}
	    virtual ~ServantManager() {}

	private:
	    // Hidden functions to disallow direct copy.
	    ServantManager( const ServantManager& t);
	    void operator=(const ServantManager&);
    };  // class ServantManager


    class IOPPOAEXPDLL ServantManager_var : public CORBA::_var {
	public:
	    ServantManager_var();
	    ServantManager_var(ServantManager_ptr p) {ptr_ = p; }
	    ServantManager_var(const ServantManager_var &a);
	    ~ServantManager_var() { free();}

	    inline ServantManager_var &operator=(ServantManager_ptr p)
		{ if (p != ptr_) reset(p);
		  return *this; }
	    inline ServantManager_var &operator=(const ServantManager_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::ServantManager::_duplicate(
		    PortableServer::ServantManager_ptr(a)); }
		  return *this; }
      	    inline ServantManager_ptr in() const { return ptr_; }
	    inline ServantManager_ptr& inout() { return ptr_; }
	    inline ServantManager_ptr& out()
		{ reset(PortableServer::ServantManager::_nil()); return ptr_; }
    	    inline ServantManager_ptr _retn()
		{ ServantManager_ptr val = ptr_;
		  ptr_ = PortableServer::ServantManager::_nil(); return val; }
	    inline ServantManager_ptr& ptr() { return ptr_; }

	    inline operator ServantManager_ptr&() { return ptr_; }
	    inline operator const ServantManager_ptr& () const { return ptr_; }
	    inline ServantManager_ptr operator->() const { return ptr_; }

	protected:
	    ServantManager_ptr ptr_;
	    inline void free()	{ CORBA::release(ptr_); }
	    inline void reset(ServantManager_ptr p) { free(); ptr_ = p; }

	private:
	    void operator=(const CORBA::_var &);
    };  // class ServantManager_var

    class IOPPOAEXPDLL ServantManager_out {
	public:
	    ServantManager_out(ServantManager_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::ServantManager::_nil(); }
	    ServantManager_out(ServantManager_var& p) : ptr_(p.ptr())
		{ CORBA::release(ptr_); ptr_ = ServantManager::_nil(); }
	    ServantManager_out(const ServantManager_out& a) : ptr_(a.ptr_) {}
	    inline ServantManager_out& operator=(ServantManager_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ServantManager_out& operator=(const ServantManager_var& a)
		{ ptr_ = PortableServer::ServantManager::_duplicate(
		  ServantManager_ptr(a)); return *this; }
	    inline ServantManager_out& operator=(ServantManager_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator ServantManager_ptr&() { return ptr_; }
	    inline ServantManager_ptr& ptr() { return ptr_; }
	    inline ServantManager_ptr operator->() { return ptr_; }

	private:
	    ServantManager_ptr& ptr_;
    };  // class ServantManager_out



    //
    // PortableServer::ServantActivator related items
    //
    class IOPPOAEXPDLL ServantActivator : public ServantManager
     {
	public:
	    static ServantActivator_ptr _duplicate(
		ServantActivator_ptr obj);
	    inline static ServantActivator_ptr _nil()
		{ return (ServantActivator_ptr) 0;}

	    virtual Servant incarnate (
		 const ObjectId & oid,
		POA_ptr adapter) = 0;


	    virtual void etherealize (
		 const ObjectId & oid,
		POA_ptr adapter,
		Servant serv,
		CORBA::Boolean cleanup_in_progress,
		CORBA::Boolean remaining_activations) = 0;

	protected:
	    ServantActivator();
	    virtual ~ServantActivator() {}

	private:
	    // Hidden functions to disallow direct copy.
	    ServantActivator( const ServantActivator& t);
	    void operator=(const ServantActivator&);
    };  // class ServantActivator

    class IOPPOAEXPDLL ServantActivator_var : public CORBA::_var {
	public:
	    ServantActivator_var();
	    ServantActivator_var(ServantActivator_ptr p) {ptr_ = p; }
	    ServantActivator_var(const ServantActivator_var &a);
	    ~ServantActivator_var() { free();}

	    inline ServantActivator_var &operator=(ServantActivator_ptr p)
		{ if (p != ptr_) reset(p);
		  return *this; }
 
	    inline ServantActivator_var &operator=(const ServantActivator_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::ServantActivator::_duplicate(
		    PortableServer::ServantActivator_ptr(a)); }
		  return *this; }
      	    inline ServantActivator_ptr in() const { return ptr_; }
	    inline ServantActivator_ptr& inout() { return ptr_; }
	    inline ServantActivator_ptr& out()
		{ reset(PortableServer::ServantActivator::_nil()); return ptr_; }
    	    inline ServantActivator_ptr _retn()
		{ ServantActivator_ptr val = ptr_;
		  ptr_ = PortableServer::ServantActivator::_nil(); return val; }
	    inline ServantActivator_ptr& ptr() { return ptr_; }

	    inline operator ServantActivator_ptr&() { return ptr_; }
	    inline operator const ServantActivator_ptr& () const { return ptr_; }
	    inline ServantActivator_ptr operator->() const { return ptr_; }

	protected:
	    ServantActivator_ptr ptr_;
	    inline void free() { CORBA::release(ptr_); }
	    inline void reset(ServantActivator_ptr p) { free(); ptr_ = p; }

	private:
	    void operator=(const CORBA::_var &);
    };  // class ServantActivator_var

    class IOPPOAEXPDLL ServantActivator_out {
	public:
	    ServantActivator_out(ServantActivator_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::ServantActivator::_nil(); }
	    ServantActivator_out(ServantActivator_var& p) : ptr_(p.ptr())
		{ CORBA::release(ptr_); ptr_ = ServantActivator::_nil(); }
	    ServantActivator_out(const ServantActivator_out& a) : ptr_(a.ptr_) {}
	    inline ServantActivator_out& operator=(ServantActivator_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ServantActivator_out& operator=(const ServantActivator_var& a)
		{ ptr_ = PortableServer::ServantActivator::_duplicate(
		  ServantActivator_ptr(a)); return *this; }
	    inline ServantActivator_out& operator=(ServantActivator_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator ServantActivator_ptr&() { return ptr_; }
	    inline ServantActivator_ptr& ptr() { return ptr_; }
	    inline ServantActivator_ptr operator->() { return ptr_; }

	private:
	    ServantActivator_ptr& ptr_;
    };  // class ServantActivator_out




    //
    // PortableServer::ServantLocator related items
    //
    class IOPPOAEXPDLL ServantLocator : public ServantManager
     {
	public:
	    static ServantLocator_ptr _duplicate(
		ServantLocator_ptr obj);
	    inline static ServantLocator_ptr _nil() { return (ServantLocator_ptr) 0;}

	    virtual Servant preinvoke (
		const ObjectId & oid,
		POA_ptr adapter,
		const char * operation,
		Cookie_out the_cookie) = 0;

	    virtual void postinvoke (
		const ObjectId & oid,
		POA_ptr adapter,
		const char * operation,
		Cookie the_cookie,
		Servant the_servant) = 0;

	protected:
	    ServantLocator();
	    virtual ~ServantLocator() {}

	private:
	    // Hidden functions to disallow direct copy.
	    ServantLocator( const ServantLocator& t);
	    void operator=(const ServantLocator&);
    };  // class ServantLocator


    class IOPPOAEXPDLL ServantLocator_var : public CORBA::_var {
	public:
	    ServantLocator_var();
	    ServantLocator_var(ServantLocator_ptr p) {ptr_ = p; }
	    ServantLocator_var(const ServantLocator_var &a);
	    ~ServantLocator_var() { free();}

	    inline ServantLocator_var &operator=(ServantLocator_ptr p)
		{ if (p != ptr_) reset(p);
		  return *this; }

	    inline ServantLocator_var &operator=(const ServantLocator_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::ServantLocator::_duplicate(
		    PortableServer::ServantLocator_ptr(a)); }
		  return *this; }
      	    inline ServantLocator_ptr in() const { return ptr_; }
	    inline ServantLocator_ptr& inout() { return ptr_; }
	    inline ServantLocator_ptr& out()
		{ reset(PortableServer::ServantLocator::_nil()); return ptr_; }
    	    inline ServantLocator_ptr _retn()
		{ ServantLocator_ptr val = ptr_;
		  ptr_ = PortableServer::ServantLocator::_nil(); return val; }
	    inline ServantLocator_ptr& ptr() { return ptr_; }

	    inline operator ServantLocator_ptr&() { return ptr_; }
	    inline operator const ServantLocator_ptr& () const { return ptr_; }
	    inline ServantLocator_ptr operator->() const { return ptr_; }

	protected:
	    ServantLocator_ptr ptr_;
	    inline void free() { CORBA::release(ptr_); }
	    inline void reset(ServantLocator_ptr p) { free(); ptr_ = p; }

	private:
	    void operator=(const CORBA::_var &);
    };  // class ServantLocator_var

    class IOPPOAEXPDLL ServantLocator_out {
	public:
	    ServantLocator_out(ServantLocator_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::ServantLocator::_nil(); }
	    ServantLocator_out(ServantLocator_var& p) : ptr_(p.ptr())
		{ CORBA::release(ptr_); ptr_ = ServantLocator::_nil(); }
	    ServantLocator_out(const ServantLocator_out& a) : ptr_(a.ptr_) {}
	    inline ServantLocator_out& operator=(ServantLocator_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ServantLocator_out& operator=(const ServantLocator_var& a)
		{ ptr_ = PortableServer::ServantLocator::_duplicate(
		  ServantLocator_ptr(a)); return *this; }
	    inline ServantLocator_out& operator=(ServantLocator_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator ServantLocator_ptr&() { return ptr_; }
	    inline ServantLocator_ptr& ptr() { return ptr_; }
	    inline ServantLocator_ptr operator->() { return ptr_; }

	private:
	    ServantLocator_ptr& ptr_;
    };  // class ServantLocator_out



    //
    // PortableServer::POA related items
    //
    class IOPPOAEXPDLL POA : public CORBA::Object
    {
	public:
	    class IOPPOAEXPDLL AdapterAlreadyExists : public CORBA::SystemException
	    {
		public:
		    static AdapterAlreadyExists * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    AdapterAlreadyExists ();
		    AdapterAlreadyExists (const AdapterAlreadyExists &);
		    ~AdapterAlreadyExists ();
		    AdapterAlreadyExists & operator=(const AdapterAlreadyExists &);
	    };  // class AdapterAlreadyExists


	    class IOPPOAEXPDLL AdapterInactive : public CORBA::SystemException
	    {
		public:
		    static AdapterInactive * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    AdapterInactive ();
		    AdapterInactive (const AdapterInactive &);
		    ~AdapterInactive ();
		    AdapterInactive & operator=(const AdapterInactive &);
	    };  // class AdapterInactive


	    class IOPPOAEXPDLL AdapterNonExistent : public CORBA::SystemException
	    {
		public:
		    static AdapterNonExistent * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    AdapterNonExistent ();
		    AdapterNonExistent (const AdapterNonExistent &);
		    ~AdapterNonExistent ();
		    AdapterNonExistent & operator=(const AdapterNonExistent &);
	    };  // class AdapterNonExistent


	    class IOPPOAEXPDLL InvalidPolicy : public CORBA::SystemException
	    {
		public:
		    static InvalidPolicy * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    InvalidPolicy ( CORBA::UShort _index);
		    InvalidPolicy ();
		    InvalidPolicy (const InvalidPolicy &);
		    ~InvalidPolicy ();
		    InvalidPolicy & operator=(const InvalidPolicy &);

		    CORBA::UShort index;
	    };  // class InvalidPolicy


	    class IOPPOAEXPDLL NoServant : public CORBA::SystemException
	    {
		public:
		    static NoServant * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    NoServant ();
		    NoServant (const NoServant &);
		    ~NoServant ();
		    NoServant & operator=(const NoServant &);
	    };  // class NoServant


	    class IOPPOAEXPDLL ObjectAlreadyActive : public CORBA::SystemException
	    {
		public:
		    static ObjectAlreadyActive * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    ObjectAlreadyActive ();
		    ObjectAlreadyActive (const ObjectAlreadyActive &);
		    ~ObjectAlreadyActive ();
		    ObjectAlreadyActive & operator=(const ObjectAlreadyActive &);
	    };  // class ObjectAlreadyActive


	    class IOPPOAEXPDLL ObjectNotActive : public CORBA::SystemException
	    {
		public:
		    static ObjectNotActive * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    ObjectNotActive ();
		    ObjectNotActive (const ObjectNotActive &);
		    ~ObjectNotActive ();
		    ObjectNotActive & operator=(const ObjectNotActive &);
	    };  // class ObjectNotActive


	    class IOPPOAEXPDLL ServantAlreadyActive : public CORBA::SystemException
	    {
		public:
		    static ServantAlreadyActive * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    ServantAlreadyActive ();
		    ServantAlreadyActive (const ServantAlreadyActive &);
		    ~ServantAlreadyActive ();
		    ServantAlreadyActive & operator=(const ServantAlreadyActive &);
	    };  // class ServantAlreadyActive


	    class IOPPOAEXPDLL ServantNotActive : public CORBA::SystemException
	    {
		public:
		    static ServantNotActive * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    ServantNotActive ();
		    ServantNotActive (const ServantNotActive &);
		    ~ServantNotActive ();
		    ServantNotActive & operator=(const ServantNotActive &);
	    };  // class ServantNotActive


	    class IOPPOAEXPDLL WrongAdapter : public CORBA::SystemException
	    {
		public:
		    static WrongAdapter * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    WrongAdapter ();
		    WrongAdapter (const WrongAdapter &);
		    ~WrongAdapter ();
		    WrongAdapter & operator=(const WrongAdapter &);
	    };  // class WrongAdapter


	    class IOPPOAEXPDLL WrongPolicy : public CORBA::SystemException
	    {
		public:
		    static WrongPolicy * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    WrongPolicy ();
		    WrongPolicy (const WrongPolicy &);
		    ~WrongPolicy ();
		    WrongPolicy & operator=(const WrongPolicy &);
	    };  // class WrongPolicy

	    static POA_ptr _duplicate(POA_ptr obj);
	    inline static POA_ptr _nil() { return (POA_ptr) 0;}
            static POA_ptr _narrow(CORBA::Object_ptr obj);

	    virtual POA_ptr create_POA (
		const char * adapter_name,
		POAManager_ptr a_POAManager,
		const CORBA::PolicyList & policies) = 0;

	    virtual POA_ptr OBB__create_wellknown_POA (
		unsigned char WellKnownOAType,
		POAManager_ptr a_POAManager,
		const CORBA::PolicyList & policies) = 0;

	    virtual POA_ptr find_POA (
		const char * adapter_name,
		CORBA::Boolean activate_it) = 0;

	    virtual void destroy (
		CORBA::Boolean etherealize_objects,
		CORBA::Boolean wait_for_completion) = 0;

	    virtual ThreadPolicy_ptr create_thread_policy (
		ThreadPolicyValue value) = 0;

	    virtual LifespanPolicy_ptr create_lifespan_policy (
		LifespanPolicyValue value) = 0;

	    virtual IdUniquenessPolicy_ptr create_id_uniqueness_policy (
		IdUniquenessPolicyValue value) = 0;

	    virtual IdAssignmentPolicy_ptr create_id_assignment_policy (
		IdAssignmentPolicyValue value) = 0;

	    virtual ImplicitActivationPolicy_ptr create_implicit_activation_policy (
		ImplicitActivationPolicyValue value) = 0;

	    virtual ServantRetentionPolicy_ptr create_servant_retention_policy (
		ServantRetentionPolicyValue value) = 0;

	    virtual RequestProcessingPolicy_ptr create_request_processing_policy (
		RequestProcessingPolicyValue value) = 0;

	    virtual StateControlPolicy_ptr create_state_control_policy (
		StateControlPolicyValue value) = 0;

	    virtual ConcurrencyStrategyPolicy_ptr create_concurrency_strategy_policy (
		ConcurrencyStrategyPolicyValue value) = 0;

	    virtual ServantManager_ptr get_servant_manager () = 0;

	    virtual void set_servant_manager (
		ServantManager_ptr imgr) = 0;

	    virtual Servant get_servant () = 0;

	    virtual void set_servant (
		Servant p_servant) = 0;

	    virtual ObjectId * activate_object (
		Servant p_servant) = 0;

	    virtual void activate_object_with_id (
		 const ObjectId & id,
		Servant p_servant) = 0;

	    virtual void deactivate_object (
		 const ObjectId & oid) = 0;

	    virtual CORBA::Object_ptr create_reference (
		 const char * intf) = 0;

	    virtual CORBA::Object_ptr create_reference_with_id (
		 const ObjectId & oid,
		 const char * intf) = 0;

	    virtual CORBA::Object_ptr create_reference_with_criteria (
		 const ObjectId & oid,
		 const char * intf,
		 const CORBA::NVList_ptr criteria) = 0;

	    virtual ObjectId * servant_to_id (
		Servant p_servant) = 0;

	    virtual CORBA::Object_ptr servant_to_reference (
		Servant p_servant) = 0;

	    virtual Servant reference_to_servant (
		CORBA::Object_ptr reference) = 0;

	    virtual ObjectId * reference_to_id (
		CORBA::Object_ptr reference) = 0;

	    virtual Servant id_to_servant (
		 const ObjectId & oid) = 0;

	    virtual CORBA::Object_ptr id_to_reference (
		 const ObjectId & oid) = 0;

	    virtual char * the_name () = 0;

	    virtual POA_ptr the_parent () = 0;

	    virtual POAManager_ptr the_POAManager () = 0;

	    virtual AdapterActivator_ptr the_activator () = 0;

	    virtual void the_activator (
		AdapterActivator_ptr the_activator) = 0;

	protected:
	    POA() {m_managed_obj = CORBA_TRUE;}
	    virtual ~POA() {}

	private:
	    POA( const POA& t);
	    void operator=(const POA&);
    };  // class POA

    class IOPPOAEXPDLL POA_var : public CORBA::_var {
	public:
	    POA_var() { ptr_ = 0; }
	    POA_var(POA_ptr p) {ptr_ = p; }
	    POA_var(const POA_var &a);
	    ~POA_var() { free();}

	    inline POA_var& operator=(POA_ptr p)
		{ if (p != ptr_) reset(p);
		  return *this; }

	    inline POA_var& operator=(const POA_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::POA::_duplicate(
		    PortableServer::POA_ptr(a)); }
		  return *this; }
	    inline POA_ptr in() const { return ptr_; }
	    inline POA_ptr& inout() { return ptr_; }
	    inline POA_ptr& out()
		{ reset(PortableServer::POA::_nil()); return ptr_; }
	    inline POA_ptr _retn()
		{ POA_ptr val = ptr_;
		  ptr_ = PortableServer::POA::_nil(); return val; }
	    inline POA_ptr& ptr() { return ptr_; }
	    inline operator POA_ptr&() { return ptr_; }
	    inline operator const POA_ptr&() const { return ptr_; }
	    inline POA_ptr operator->() const { return ptr_; }

	protected:
	    POA_ptr ptr_;
	    inline void free() { CORBA::release(ptr_); }
	    inline void reset(POA_ptr p) { free(); ptr_ = p; }

	private:
	    void operator=(const CORBA::_var &);
    };  // class POA_var

    class IOPPOAEXPDLL POA_out {
	public:
	    POA_out(POA_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::POA::_nil(); }
	    POA_out(POA_var& p) : ptr_(p.ptr())
		{ CORBA::release(ptr_); ptr_ = POA::_nil(); }
	    POA_out(const POA_out& a) : ptr_(a.ptr_) {}
	    inline POA_out& operator=(POA_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline POA_out& operator=(const POA_var& a)
		{ ptr_ = PortableServer::POA::_duplicate(
		  POA_ptr(a)); return *this; }
	    inline POA_out& operator=(POA_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator POA_ptr&() { return ptr_; }
	    inline POA_ptr& ptr() { return ptr_; }
	    inline POA_ptr operator->() { return ptr_; }

	private:
	    POA_ptr& ptr_;
    };  // class POA_out


    //
    // PortableServer::Current related items
    //
    class IOPPOAEXPDLL Current : public CORBA::Current
    {
	public:
	    class IOPPOAEXPDLL NoContext : public CORBA::SystemException
	    {
		public:
		    static NoContext * _narrow(CORBA::Exception_ptr);
		    void _raise();
		    NoContext ();
		    NoContext (const NoContext &);
		    ~NoContext ();
		    NoContext & operator=(const NoContext &);
	    };  // class NoContext


	    static Current_ptr _duplicate(
		Current_ptr obj);
	    inline static Current_ptr _nil() { return (Current_ptr) 0;}
            static Current_ptr _narrow(CORBA::Object_ptr obj);

	    virtual POA_ptr get_POA () = 0;
	    virtual ObjectId * get_object_id () = 0;
            virtual char * get_interface_id () = 0;

	    // Internal only functions
	    virtual void OBB__get_object_id (const void *& OIDPtr, 
		    CORBA::ULong & OIDLen, 
		    const void *& AppOIDPtr, 
		    CORBA::ULong & AppOIDLen) = 0;
            virtual const char * OBB__get_interface_id () = 0;
	    
	protected:
	    Current() {}
	    virtual ~Current() {}

	private:
	    Current( const Current& t);
	    void operator=(const Current&);
    };  // class Current

    class IOPPOAEXPDLL Current_var : public CORBA::_var {
	public:
	    Current_var();
	    Current_var(Current_ptr p) {ptr_ = p; }
	    Current_var(const Current_var &a);
	    ~Current_var() { free();}

	    inline Current_var& operator=(Current_ptr p)
		{ if (p != ptr_) reset(p);
		  return *this; }

	    inline Current_var& operator=(const Current_var& a)
		{ if (this != &a) { free();
		    ptr_ = PortableServer::Current::_duplicate(
		    PortableServer::Current_ptr(a)); }
		  return *this; }
	    inline Current_ptr in() const { return ptr_; }
	    inline Current_ptr& inout() { return ptr_; }
	    inline Current_ptr& out()
		{ reset(PortableServer::Current::_nil()); return ptr_; }
	    inline Current_ptr _retn()
		{ Current_ptr val = ptr_;
		  ptr_ = PortableServer::Current::_nil(); return val; }
	    inline Current_ptr& ptr() { return ptr_; }
	    inline operator Current_ptr&() { return ptr_; }
	    inline operator const Current_ptr&() const { return ptr_; }
	    inline Current_ptr operator->() const { return ptr_; }

	protected:
	    Current_ptr ptr_;
	    inline void free() { CORBA::release(ptr_); }
	    inline void reset(Current_ptr p) { free(); ptr_ = p; }

	private:
	    void operator=(const CORBA::_var &);
    };  // class Current_var

    class IOPPOAEXPDLL Current_out {
	public:
	    Current_out(Current_ptr& p) : ptr_(p)
		{ ptr_ = PortableServer::Current::_nil(); }
	    Current_out(Current_var& p) : ptr_(p.ptr())
		{ CORBA::release(ptr_); ptr_ = Current::_nil(); }
	    Current_out(const Current_out& a) : ptr_(a.ptr_) {}
	    inline Current_out& operator=(Current_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline Current_out& operator=(const Current_var& a)
		{ ptr_ = PortableServer::Current::_duplicate(
		  Current_ptr(a)); return *this; }
	    inline Current_out& operator=(Current_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator Current_ptr&() { return ptr_; }
	    inline Current_ptr& ptr() { return ptr_; }
	    inline Current_ptr operator->() { return ptr_; }

	private:
	    Current_ptr& ptr_;
    };  // class Current_out

    static char * ObjectId_to_string(const ObjectId & ObjId);
    static ObjectId * string_to_ObjectId (const char * ObjIdStr);
    
};  // class PortableServer

#endif

