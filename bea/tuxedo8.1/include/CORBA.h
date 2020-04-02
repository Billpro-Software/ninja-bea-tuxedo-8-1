//	Copyright (c) 1997 BEA Systems, Inc.
//	All rights reserved
//
//	THIS IS UNPUBLISHED PROPRIETARY
//	SOURCE CODE OF BEA Systems, Inc.
//	The copyright notice above does not
//	evidence any actual or intended
//	publication of such source code.
//
// #ident	"@(#) orb/src/CORBA.h	$Revision: 1.52 $"

#ifndef	_CORBA_h
#define	_CORBA_h
//
// MODULE NAME:
//
//	CORBA.h
//
// FACILITY:
//
//	ObjectBroker IOP component
//
// ABSTRACT:
//
//	This include file contains the CORBA and OBB C++ class definitions for
//	ObjectBroker IOP applications.
//
// CLASSES CONTAINED IN THIS MODULE:
//    CORBA:: classes
//    OBB:: classes
//
// CREATION DATE: 5-Feb-1997
//
//
#if !defined(M3_NO_UNICODE_SUPPORT)
#include <wchar.h>
#endif
#include <tmenv.h>

// on some systems minor is defined as a cpp macro in sys/types which
// sometimes gets pulled in before this file.  And since we have
// a couple of methods called minor .....
#undef minor

#if defined(_WIN32)
# if defined(OBBEXPORTAPI)
#  define OBBEXPDLL __declspec(dllexport)
# else
#  define OBBEXPDLL __declspec(dllimport)
# endif
#else
#define OBBEXPDLL
#endif


// In conformance with the ANSI C++ standard, newer C++ compilers throw an
// out of memory exception when the 'new' operator is unable to allocate
// memory.  Use the (std::nothrow) or (nothrow) modifier to prevent this.
//
#if !defined(ORBNEWTHROW)
#if (defined(__sun) && __SUNPRO_CC_COMPAT >= 5)

#include <new>
#define ORBNEWTHROW (std::nothrow)

#elif defined(__HP_aCC)

#include <new>
#define ORBNEWTHROW (nothrow)

#else

#define ORBNEWTHROW

#endif
#endif

 
#ifdef OBBXYZZY
#define OBBCONSTDATA
#else
#define OBBCONSTDATA const
#endif

//    The pseudo object classes defined in the submission are included in the
//    CORBA "namespace" (nested in the CORBA class).
//    The OBB pseudo object classes that are defined as extensions are included
//    here in the OBB "namespace" (nested in the OBB class).

#ifndef CORBA_TRUE
#define CORBA_TRUE 1
#endif

#ifndef CORBA_FALSE
#define CORBA_FALSE 0
#endif

class ObjRef;

class OBBEXPDLL CORBA
{
public:

    // forward references for OBB internal classes
    class _var;

    // CORBA object forward references
    class Context;
    class Environment;
    class NamedValue;
    class NVList;
    class Object;
    class ORB;
    class Principal;
    class Request;
    class TypeCode;
    class ExceptionList;
    class ContextList;
    class Current;
    class Policy;
    class ServerRequest;

    // forward references for predefined CORBA classes
    class Exception;
    class String_var;
    class String_out;
#if !defined(M3_NO_UNICODE_SUPPORT)
    class WString_var;
    class WString_out;
#endif
    class Any;
    class Any_var;
    class Any_out;
    class SystemException;
    class UserException;
    class InterfaceDef;
    class OperationDef;
    class AnySeq;
    class BooleanSeq;
    class CharSeq;
#if !defined(M3_NO_UNICODE_SUPPORT)
    class WCharSeq;
#endif
    class OctetSeq;
    class ShortSeq;
    class UShortSeq;
    class LongSeq;
    class ULongSeq;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
    class LongLongSeq;
    class ULongLongSeq;
#endif
    class FloatSeq;
    class DoubleSeq;
#if defined(M3_LONG_DOUBLE_SUPPORT)
    class LongDoubleSeq;
#endif
    class AbstractBase;
    class ValueBase;
    class ValueFactoryBase;
    class LocalBase;
    class StringValue;
#if !defined(M3_NO_UNICODE_SUPPORT)
    class WStringValue;
#endif
    class DataOutputStream;
    class DataInputStream;
    class CustomMarshal;


    // Typedefs
    typedef char Char;
#if !defined(M3_NO_UNICODE_SUPPORT)
    typedef wchar_t WChar;
#endif
    typedef char Boolean;
    typedef unsigned char Octet;
    typedef short Short;
    typedef unsigned short UShort;
	typedef TM32I Long;
	typedef TM32U ULong;
	typedef TM32U Flags;
    typedef float Float;
    typedef double Double;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
#if defined(_WIN32)
    typedef __int64 LongLong;
    typedef unsigned __int64 ULongLong;
#else
#ifdef _TMLONG64
    typedef long LongLong;
    typedef unsigned long ULongLong;
#else
    typedef long long LongLong;
    typedef unsigned long long ULongLong;
#endif
#endif
#endif
#if defined(M3_LONG_DOUBLE_SUPPORT)
    typedef long double LongDouble;
#endif
    typedef void Status;
    typedef char * Identifier;
    typedef char * ScopedName;
    typedef char * RepositoryId;
    typedef UShort ServiceType;
    typedef ULong ServiceOption;
    typedef ULong ServiceDetailType;

    typedef Boolean & Boolean_out;
    typedef Char & Char_out;
#if !defined(M3_NO_UNICODE_SUPPORT)
    typedef WChar & WChar_out;
#endif
    typedef Octet & Octet_out;
    typedef Short & Short_out;
    typedef UShort & UShort_out;
    typedef Long & Long_out;
    typedef ULong & ULong_out;
    typedef Float & Float_out;
    typedef Double & Double_out;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
    typedef LongLong & LongLong_out;
    typedef ULongLong & ULongLong_out;
#endif
#if defined(M3_LONG_DOUBLE_SUPPORT)
    typedef LongDouble & LongDouble_out;
#endif
    typedef UShort_out ServiceType_out;
    typedef ULong_out ServiceOption_out;
    typedef ULong_out ServiceDetailType_out;

    // NOTE: tk_null must be first and be equal to 0, and the order of the
    // rest must be match the order defined in the [classic] C bindings so
    // that the values of each of the following always match their CORBA_tk_
    // equivelents
    enum TCKind {
	tk_null = 0, tk_void, tk_short, tk_long, tk_ushort, tk_ulong,
	tk_float, tk_double, tk_boolean, tk_char, tk_octet, tk_any,
	tk_TypeCode, tk_Principal, tk_objref, tk_struct, tk_union,
	tk_enum, tk_string, tk_sequence, tk_array, tk_alias, tk_except,
	tk_longlong, tk_ulonglong, tk_longdouble, tk_wchar, tk_wstring,
	tk_fixed, tk_value, tk_value_box, tk_native, tk_abstract_interface,
	tk_local_interface
    };

    // CORBA::String is not a real CORBA type.  It's use therefore is
    // being deprecated, but will remain for now to ease migration
    typedef char * String;
    typedef Char * ORBid;
#if !defined(M3_NO_UNICODE_SUPPORT)
    typedef wchar_t * WString;
#endif

    // object _ptr typedefs...
    typedef Object * Object_ptr;
    typedef Environment * Environment_ptr;
    typedef Principal * Principal_ptr;
    typedef NamedValue * NamedValue_ptr;
    typedef NVList * NVList_ptr;
    typedef Request * Request_ptr;
    typedef Context * Context_ptr;
    typedef TypeCode * TypeCode_ptr;
    typedef ORB * ORB_ptr;
    typedef Exception * Exception_ptr;
    typedef Current * Current_ptr;
    typedef Policy * Policy_ptr;
    typedef ServerRequest * ServerRequest_ptr;

    typedef InterfaceDef * InterfaceDef_ptr;
    typedef OperationDef * OperationDef_ptr;
    typedef ExceptionList * ExceptionList_ptr;
    typedef ContextList * ContextList_ptr;
    typedef Any *Any_ptr;
    typedef AnySeq * AnySeq_ptr;
    typedef BooleanSeq * BooleanSeq_ptr;
    typedef CharSeq * CharSeq_ptr;
#if !defined(M3_NO_UNICODE_SUPPORT)
    typedef WCharSeq * WCharSeq_ptr;
#endif
    typedef OctetSeq * OctetSeq_ptr;
    typedef ShortSeq * ShortSeq_ptr;
    typedef UShortSeq * UShortSeq_ptr;
    typedef LongSeq * LongSeq_ptr;
    typedef ULongSeq * ULongSeq_ptr;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
    typedef LongLongSeq * LongLongSeq_ptr;
    typedef ULongLongSeq * ULongLongSeq_ptr;
#endif
    typedef FloatSeq * FloatSeq_ptr;
    typedef DoubleSeq * DoubleSeq_ptr;
#if defined(M3_LONG_DOUBLE_SUPPORT)
    typedef LongDoubleSeq * LongDoubleSeq_ptr;
#endif
    typedef AbstractBase * AbstractBase_ptr;
    typedef ValueBase * ValueBase_ptr;
    typedef ValueFactoryBase * ValueFactory;
    typedef LocalBase * LocalBase_ptr;
    typedef StringValue * StringValue_ptr;
#if !defined(M3_NO_UNICODE_SUPPORT)
    typedef WStringValue * WStringValue_ptr;
#endif
    typedef DataOutputStream * DataOutputStream_ptr;
    typedef DataInputStream * DataInputStream_ptr;
    typedef CustomMarshal * CustomMarshal_ptr;

    // Some T_var classes
    class Object_var;
    class Environment_var;
    class Principal_var;
    class NamedValue_var;
    class NVList_var;
    class Request_var;
    class Context_var;
    class TypeCode_var;
    class ORB_var;
    class ExceptionList_var;
    class ContextList_var;
    class Policy_var;
    class AnySeq_var;
    class BooleanSeq_var;
    class CharSeq_var;
#if !defined(M3_NO_UNICODE_SUPPORT)
    class WCharSeq_var;
#endif
    class OctetSeq_var;
    class ShortSeq_var;
    class UShortSeq_var;
    class LongSeq_var;
    class ULongSeq_var;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
    class LongLongSeq_var;
    class ULongLongSeq_var;
#endif
    class FloatSeq_var;
    class DoubleSeq_var;
#if defined(M3_LONG_DOUBLE_SUPPORT)
    class LongDoubleSeq_var;
#endif
    class AbstractBase_var;
    class LocalBase_var;
    class ValueBase_var;
    class StringValue_var;
#if !defined(M3_NO_UNICODE_SUPPORT)
    class WStringValue_var;
#endif

    // Some T_out classes
    class Object_out;
    class Environment_out;
    class Principal_out;
    class NamedValue_out;
    class NVList_out;
    class Request_out;
    class Context_out;
    class TypeCode_out;
    class ORB_out;
    class ExceptionList_out;
    class ContextList_out;
    class Policy_out;
    class AnySeq_out;
    class BooleanSeq_out;
    class CharSeq_out;
#if !defined(M3_NO_UNICODE_SUPPORT)
    class WCharSeq_out;
#endif
    class OctetSeq_out;
    class ShortSeq_out;
    class UShortSeq_out;
    class LongSeq_out;
    class ULongSeq_out;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
    class LongLongSeq_out;
    class ULongLongSeq_out;
#endif
    class FloatSeq_out;
    class DoubleSeq_out;
#if defined(M3_LONG_DOUBLE_SUPPORT)
    class LongDoubleSeq_out;
#endif
    class AbstractBase_out;
    class LocalBase_out;
    class ValueBase_out;
    class StringValue_out;
#if !defined(M3_NO_UNICODE_SUPPORT)
    class WStringValue_out;
#endif

    // PolicyType
    typedef ULong PolicyType;
    typedef ULong_out PolicyType_out;

    // Overloaded release operations
    static void release(Environment_ptr);
    static void release(NamedValue_ptr);
    static void release(NVList_ptr);
    static void release(Request_ptr);
    static void release(Context_ptr);
    static void release(Principal_ptr);
    static void release(TypeCode_ptr);
    static void release(ORB_ptr);
    static void release(Object_ptr);
    static void release(ExceptionList_ptr);
    static void release(ContextList_ptr);
    static void release(AbstractBase_ptr);
    static void release(LocalBase_ptr);
    static void release(DataOutputStream_ptr);
    static void release(DataInputStream_ptr);

    // Overloaded is_nil operations
    static Boolean is_nil(Environment_ptr);
    static Boolean is_nil(NamedValue_ptr);
    static Boolean is_nil(NVList_ptr);
    static Boolean is_nil(Request_ptr);
    static Boolean is_nil(Context_ptr);
    static Boolean is_nil(Principal_ptr);
    static Boolean is_nil(TypeCode_ptr);
    static Boolean is_nil(ORB_ptr);
    static Boolean is_nil(Object_ptr);
    static Boolean is_nil(ExceptionList_ptr);
    static Boolean is_nil(ContextList_ptr);
    static Boolean is_nil(AbstractBase_ptr);
    static Boolean is_nil(LocalBase_ptr);
    static Boolean is_nil(DataOutputStream_ptr);
    static Boolean is_nil(DataInputStream_ptr);

    // String utility routines
    static char * string_alloc(ULong len);
    static void string_free(char * p);
    static char * string_dup(const char *);
#if !defined(M3_NO_UNICODE_SUPPORT)
    static WChar * wstring_alloc(ULong len);
    static WChar * wstring_dup(const wchar_t *);
    static void wstring_free(WChar * p);
#endif

    // Predefined TypeCode constants
    static TypeCode_ptr _tc_null;
    static TypeCode_ptr _tc_void;
    static TypeCode_ptr _tc_short;
    static TypeCode_ptr _tc_long;
    static TypeCode_ptr _tc_ushort;
    static TypeCode_ptr _tc_ulong;
    static TypeCode_ptr _tc_float;
    static TypeCode_ptr _tc_double;
    static TypeCode_ptr _tc_boolean;
    static TypeCode_ptr _tc_char;
    static TypeCode_ptr _tc_octet;
    static TypeCode_ptr _tc_any;
    static TypeCode_ptr _tc_TypeCode;
    static TypeCode_ptr _tc_Principal;
    static TypeCode_ptr _tc_Object;
    static TypeCode_ptr _tc_string;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
    static TypeCode_ptr _tc_longlong;
    static TypeCode_ptr _tc_ulonglong;
#endif
    static TypeCode_ptr _tc_longdouble;
#if !defined(M3_NO_UNICODE_SUPPORT)
    static TypeCode_ptr _tc_wchar;
    static TypeCode_ptr _tc_wstring;
    static TypeCode_ptr _tc_WStringValue;
#endif
    static TypeCode_ptr _tc_value_box;
    static TypeCode_ptr _tc_ValueBase;
    static TypeCode_ptr _tc_StringValue;

//   static TypeCode_ptr _tc_NamedValue;
    static TypeCode_ptr _tc_SystemException;

    static TypeCode_ptr _tc_PolicyType;
    static TypeCode_ptr _tc_PolicyErrorCode;
    static TypeCode_ptr _tc_ServiceDetail;
    static TypeCode_ptr _tc_ServiceInformation;
    static TypeCode_ptr _tc_ServiceType;
    static TypeCode_ptr _tc_ServiceOption;
    static TypeCode_ptr _tc_ServiceDetailType;
    static TypeCode_ptr _tc_AnySeq;
    static TypeCode_ptr _tc_BooleanSeq;
    static TypeCode_ptr _tc_CharSeq;
#if !defined(M3_NO_UNICODE_SUPPORT)
    static TypeCode_ptr _tc_WCharSeq;
#endif
    static TypeCode_ptr _tc_OctetSeq;
    static TypeCode_ptr _tc_ShortSeq;
    static TypeCode_ptr _tc_UShortSeq;
    static TypeCode_ptr _tc_LongSeq;
    static TypeCode_ptr _tc_ULongSeq;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
    static TypeCode_ptr _tc_LongLongSeq;
    static TypeCode_ptr _tc_ULongLongSeq;
#endif
    static TypeCode_ptr _tc_FloatSeq;
    static TypeCode_ptr _tc_DoubleSeq;
    static TypeCode_ptr _tc_LongDoubleSeq;

    static OBBCONSTDATA ULong OMGVMCID;
    static OBBCONSTDATA ServiceType Security;

    // Other constants
    static OBBCONSTDATA Flags CTX_RESTRICT_SCOPE;
    static OBBCONSTDATA Flags CTX_DELETE_DESCENDENTS;
    static OBBCONSTDATA Flags ARG_IN;
    static OBBCONSTDATA Flags ARG_OUT;
    static OBBCONSTDATA Flags ARG_INOUT;
    static OBBCONSTDATA Flags IN_COPY_VALUE;
    static OBBCONSTDATA Flags DEPENDENT_LIST;
    static OBBCONSTDATA Flags INV_NO_RESPONSE;
    static OBBCONSTDATA Flags INV_TERM_ON_ERR;
    static OBBCONSTDATA Flags RESP_NO_WAIT;
    static OBBCONSTDATA Flags OUT_LIST_MEMORY;
    static OBBCONSTDATA Flags VALIDATE_REQUEST;

    static OBBCONSTDATA String OBBCURRENT_INITNAME;
    static OBBCONSTDATA String POACURRENT_INITNAME;
    static OBBCONSTDATA String ROOTPOA_INITNAME;
    static OBBCONSTDATA String NAMESERVICE_INITNAME;
    static OBBCONSTDATA String REPOSITORY_INITNAME;

    static ORB_ptr ORB_init( int& Argc,
                             char** Argv,
                             const char* ORBIdentifier = 0);


    // _var class - for OBB internal use, all _var classes inherit from
    // this class
    // NOTE, this class may be for internal use only, but we need to export
    // it or NT complains that the base class is not exported even though
    // classes dervived from it are.
    class OBBEXPDLL _var
    {
    protected:
	_var();
	virtual ~_var();
    };

    class OBBEXPDLL Exception
    {
    public:
	virtual ~Exception();
	virtual void _raise() = 0;
	
	// Extension to get id
	const char * get_id() const;

	// OBB internal use functions
	const char * OBB__id() const;
	void OBB__id(const char *id);
	virtual Boolean OBB__is_system_exception() const;

    protected:
	Exception();
	Exception & operator=(const Exception & rhs);

    private:
	const char *_id;
    };

    class OBBEXPDLL String_var : public _var
    {
    public:
	String_var () { _string = 0; }
	String_var (char *p) { _string = p; }
	String_var (const char *p) { _string = 0; *this = p; }
	String_var (const String_var &s) { _string = 0; *this = s; }
	~String_var () { if (_string) string_free(_string); }
	String_var & operator=(char *p);
	String_var & operator=(const char *p);
	String_var & operator=(const String_var &s);
	inline operator const char* () const { return _string; }
	inline operator char* () { return _string; }
        inline const char * in() const { return _string; }
        inline char *& inout () { return _string; }
        inline char *& out ()
	    { string_free(_string); _string = 0; return _string; }
        inline char * _retn ()
	    { char * val = _string; _string = 0; return val; }
	inline char*& ptr() { return _string; }
	char & operator[] (ULong index);
	char operator[] (ULong index) const;
    private:
	char *_string;
    };
    typedef Char *Char_ptr;
    class OBBEXPDLL String_out
    {
    public:
	String_out(char*& p) : ptr_(p) { ptr_ = 0; }
	String_out(String_var& p) : ptr_(p.ptr())
	    { string_free(ptr_); ptr_ = 0; }
	String_out(const String_out& s) : ptr_(s.ptr_) {}

	inline String_out& operator=(const String_out& _s)
	    { ptr_ = _s.ptr_; return *this; }
	inline String_out& operator=(char* p)
	    { ptr_ = p; return *this; }
	inline String_out& operator=(const char* p)
	    { ptr_ = string_dup(p); return *this; }

	inline operator Char_ptr&() { return ptr_; }
	inline char*& ptr() { return ptr_; }
    private:
	char*& ptr_;
	// Assignment from String_var disallowed
	void operator=(const String_var&);
    };

    typedef String_var RepositoryId_var;
    typedef String_out RepositoryId_out;
    typedef String_var Identifier_var;
    typedef String_out Identifier_out;
    
#if !defined(M3_NO_UNICODE_SUPPORT)
    class OBBEXPDLL WString_var : public _var
    {
    public:
	WString_var () { _string = 0; }
	WString_var (WChar *p) { _string = p; }
	WString_var (const WChar *p) { _string = 0; *this = p; }
	WString_var (const WString_var &s) { _string = 0; *this = s; }
	~WString_var () { if (_string) wstring_free(_string); }
	WString_var & operator=(WChar *p);
	WString_var & operator=(const WChar *p);
	WString_var & operator=(const WString_var &s);
	inline operator const WChar * () const { return _string; }
	inline operator WChar * () { return _string; }
        inline const WChar * in() const { return _string; }
        inline WChar *& inout () { return _string; }
        inline WChar *& out ()
	    { wstring_free(_string); _string = 0; return _string; }
        inline WChar * _retn ()
	    { WChar * val = _string; _string = 0; return val; }
	inline WChar*& ptr() { return _string; }
	WChar & operator[] (ULong index);
	WChar operator[] (ULong index) const;
    private:
	WChar *_string;
    };
    typedef WChar *WChar_ptr;

    class OBBEXPDLL WString_out
    {
    public:
	WString_out(WChar*& p) : ptr_(p) { ptr_ = 0; }
	WString_out(WString_var& p) : ptr_(p.ptr())
	    { wstring_free(ptr_); ptr_ = 0; }
	WString_out(const WString_out& s) : ptr_(s.ptr_) {}

	inline WString_out& operator=(const WString_out& _s)
	    { ptr_ = _s.ptr_; return *this; }
	inline WString_out& operator=(WChar* p)
	    { ptr_ = p; return *this; }
	inline WString_out& operator=(const WChar* p)
	    { ptr_ = wstring_dup(p); return *this; }

	inline operator WChar_ptr&() { return ptr_; }
	inline WChar*& ptr() { return ptr_; }
    private:
	WChar*& ptr_;
	// Assignment from WString_var disallowed
	void operator=(const WString_var&);
    };
#endif

    class OBBEXPDLL Any
    {
    public:
	Any ();
	Any (const Any&);
	Any (TypeCode_ptr tc, void *value, Boolean release = CORBA_FALSE);
	~Any ();
	Any & operator=(const Any&);
	void operator<<=(Short);
	void operator<<=(UShort);
	void operator<<=(Long);
	void operator<<=(ULong);
	void operator<<=(Float);
	void operator<<=(Double);
	void operator<<=(const Any&);
	void operator<<=(const char*);
	void operator<<=(const String_var&);
#if !defined(M3_NO_UNICODE_SUPPORT)
	void operator<<=(const WString_var&);
#endif
	void operator<<=(Object_ptr);
	void operator<<=(TypeCode_ptr);
#if !defined(M3_NO_LONG_LONG_SUPPORT)
	void operator<<=(LongLong);
	void operator<<=(ULongLong);
#endif
#if defined(M3_LONG_DOUBLE_SUPPORT)
	void operator<<=(LongDouble);
#endif
#if !defined(M3_NO_UNICODE_SUPPORT)
	void operator<<=(const WChar*);
#endif
	Boolean operator>>=(Short&) const;
	Boolean operator>>=(UShort&) const;
	Boolean operator>>=(Long&) const;
	Boolean operator>>=(ULong&) const;
	Boolean operator>>=(Float&) const;
	Boolean operator>>=(Double&) const;
	Boolean operator>>=(Any&) const;
	Boolean operator>>=(char*&) const;
	Boolean operator>>=(Object_ptr&);
	Boolean operator>>=(TypeCode_ptr&);
#if !defined(M3_NO_LONG_LONG_SUPPORT)
	Boolean operator>>=(LongLong&) const;
	Boolean operator>>=(ULongLong&) const;
#endif
#if defined(M3_LONG_DOUBLE_SUPPORT)
	Boolean operator>>=(LongDouble&) const;
#endif
#if !defined(M3_NO_UNICODE_SUPPORT)
	Boolean operator>>=(WChar*&) const;
#endif
	// special types needed for boolean, octet, char insertion
	// these are suggested implementations only
	struct from_boolean {
	    from_boolean (Boolean b) : val (b) {}
	    Boolean val;
	};
	struct from_octet {
	    from_octet (Octet o) : val (o) {}
	    Octet val;
	};
	struct from_char {
	    from_char (Char c) : val (c) {}
	    Char val;
	};
#if !defined(M3_NO_UNICODE_SUPPORT)
	struct from_wchar {
	    from_wchar (WChar c) : val (c) {}
	    WChar val;
	};
#endif
	void operator<<=(from_boolean);
	void operator<<=(from_char);
#if !defined(M3_NO_UNICODE_SUPPORT)
	void operator<<=(from_wchar);
#endif
	void operator<<=(from_octet);
	// special types needed for boolean, octet, char extraction
	// these are suggested implementations only
	struct to_boolean {
	    to_boolean (Boolean &b) : ref (b) {}
	    Boolean &ref;
	};
	struct to_char {
	    to_char (Char &c) : ref (c) {}
	    Char &ref;
	};
#if !defined(M3_NO_UNICODE_SUPPORT)
	struct to_wchar {
	    to_wchar (WChar &c) : ref (c) {}
	    WChar &ref;
	};
#endif
	struct to_octet {
	    to_octet (Octet &o) : ref (o) {}
	    Octet &ref;
	};
        struct to_object {
            to_object(Object_ptr &obj) : ref(obj) {}
            Object_ptr & ref;
        };
        struct to_string { 
            to_string(String & s, ULong b) : val (s), bound(b) {}
            String & val;
            ULong bound;
        };
#if !defined(M3_NO_UNICODE_SUPPORT)
        struct to_wstring { 
            to_wstring(WString & s, ULong b) : val (s), bound(b) {}
            WString & val;
            ULong bound;
        };
#endif
	Boolean operator>>= (to_boolean) const;
	Boolean operator>>= (to_char) const;
	Boolean operator>>= (to_octet) const;
	Boolean operator>>= (to_object) const;
	Boolean operator>>= (to_string) const;
#if !defined(M3_NO_UNICODE_SUPPORT)
	Boolean operator>>= (to_wchar) const;
	Boolean operator>>= (to_wstring) const;
#endif
	void replace(TypeCode_ptr tc, void *value,
				Boolean release);
	void replace(TypeCode_ptr tc, void *value);
	TypeCode_ptr type () const;
	const void * value () const;

	// OBB internal use functions
	Long OBB__len(TCKind) const;
	void OBB__delete();

    private:
	// these are hidden and should not be implemented
	// so as to catch erroneous attempts to insert or extract
	// multiple IDL types mapped to unsigned char
	void operator<<=(unsigned char);
	Boolean operator>>=(unsigned char&) const;
	Boolean		_release;
	TypeCode_ptr	_typecode_ptr;
	void *		_value;
	union
	{
	    Boolean _boolean;
	    Char _char;
	    Double _double;
	    Float _float;
	    Long _long;
	    ULong _ulong;
	    Short _short;
	    UShort _ushort;
	    Octet _octet;
#if !defined(M3_NO_LONG_LONG_SUPPORT)
	    LongLong _longlong;
	    ULongLong _ulonglong;
#endif
#if defined(M3_LONG_DOUBLE_SUPPORT)
	    LongDouble _longdouble;
#endif
#if !defined(M3_NO_UNICODE_SUPPORT)
	    wchar_t _wchar;
	    wchar_t * _wstr;
#endif
	    char *_str;
	    Object_ptr _objref;
	    Principal_ptr _prin;
	    TypeCode_ptr _typecode;
	    ValueBase_ptr _valuebase;
	    void *_voidptr;
	} _data;
    };

    class OBBEXPDLL Any_var : public _var
    {
    public:
	Any_var () { ptr_ = 0; }
	Any_var (Any *a) { ptr_ = a; }
	Any_var (const Any_var &a) { *ptr_= * ((Any *) a); }
	~Any_var () { delete ptr_; }
	inline Any_var & operator=(Any *a)
	    { delete ptr_; ptr_ = a; return(*this); }
	inline Any_var & operator=(const Any_var &a)
	   { if (this != &a) *ptr_=* ((Any *) a); return(*this); }
	inline Any *operator->() { return ptr_; }
        inline const Any & in () const { return *ptr_; }
        inline Any & inout () { return *ptr_; }
        inline Any *& out () { return ptr_; }
	inline Any *_retn() { Any * val = ptr_; ptr_ = 0; return val; }
        inline Any *& ptr() { return ptr_; }
	inline operator Any *() const { return ptr_; }
    private:
	Any *ptr_;
    };

    class OBBEXPDLL Any_out
    {
    public:
	Any_out (Any_ptr &p) : ptr_(p) { ptr_ = 0; }
	Any_out (Any_var &p) : ptr_(p.ptr())
	    { delete ptr_; ptr_ = 0; }
	Any_out (const Any_out & a) : ptr_(a.ptr_) {}
	inline Any_out& operator=(const Any_out & a)
	    { ptr_ = a.ptr_; return *this; }
	inline Any_out & operator=(Any_ptr p) { ptr_ = p; return *this; }
	inline operator Any_ptr&() {return ptr_; }
	inline Any_ptr& ptr() { return ptr_;}
	inline Any_ptr operator->() { return ptr_; }
    private:
	Any_ptr& ptr_;
	// Assignment from Any_var disallowed
	void operator=(const Any_var&);
    };

    enum CompletionStatus { COMPLETED_YES, COMPLETED_NO, COMPLETED_MAYBE };
    class OBBEXPDLL SystemException : public Exception
    {
    public:
	SystemException ();
	SystemException (const SystemException &);
	SystemException(ULong minor, CompletionStatus status);
	~SystemException();
	virtual void _raise();

	CompletionStatus completed() const;
	void completed (CompletionStatus status);

	ULong minor() const;
	void minor(ULong minor);

	SystemException & operator=(const SystemException &se);

	static SystemException * _narrow(Exception_ptr);

	// OBB extension to get additional errortext information

	const char * OBB_errortext() const;

	// OBB internal use functions
	void OBB__errortext(const char * errortext);

	virtual Boolean OBB__is_system_exception() const;

    private:
	ULong m_minor;
	CompletionStatus m_completed;

	char * _errortext;
    };

    class OBBEXPDLL UserException : public Exception
    {
    public:
	UserException () {}
	UserException (const UserException &e) : Exception(e) {}
	~UserException() {}
	virtual void _raise();

	static UserException * _narrow (Exception_ptr);

	// OBB internal use functions
	virtual Boolean OBB__is_system_exception() const;
    };

#ifdef TBD_UnknownUserException
    class OBBEXPDLL UnknownUserException : public UserException
    {
    public:
	UnknownUserException();
	UnknownUserException(Any * AnyPtr);
	UnknownUserException(const UnknownUserException&);
	UnknownUserException& operator=(const UnknownUserException&);
	~UnknownUserException();

	Any &exception();

	static UnknownUserException * _narrow (Exception_ptr);
	virtual void _raise();
    private:
	Any_var _exception;
    };
#endif

    //
    // Classes for system exceptions
    //
    class OBBEXPDLL UNKNOWN : public SystemException
    {
    public:
	UNKNOWN();
	~UNKNOWN();
	UNKNOWN(const UNKNOWN &);
	UNKNOWN(ULong minor, CompletionStatus status);
	void _raise();
	static UNKNOWN * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL BAD_PARAM : public SystemException
    {
    public:
	BAD_PARAM();
	~BAD_PARAM();
	BAD_PARAM(const BAD_PARAM &);
	BAD_PARAM(ULong minor, CompletionStatus status);
	void _raise();
	static BAD_PARAM * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL NO_MEMORY : public SystemException
    {
    public:
	NO_MEMORY();
	~NO_MEMORY();
	NO_MEMORY(const NO_MEMORY &);
	NO_MEMORY(ULong minor, CompletionStatus status);
	void _raise();
	static NO_MEMORY * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL IMP_LIMIT : public SystemException
    {
    public:
	IMP_LIMIT();
	~IMP_LIMIT();
	IMP_LIMIT(const IMP_LIMIT &);
	IMP_LIMIT(ULong minor, CompletionStatus status);
	void _raise();
	static IMP_LIMIT * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL COMM_FAILURE : public SystemException
    {
    public:
	COMM_FAILURE();
	~COMM_FAILURE();
	COMM_FAILURE(const COMM_FAILURE &);
	COMM_FAILURE(ULong minor, CompletionStatus status);
	void _raise();
	static COMM_FAILURE * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INV_OBJREF : public SystemException
    {
    public:
	INV_OBJREF();
	~INV_OBJREF();
	INV_OBJREF(const INV_OBJREF &);
	INV_OBJREF(ULong minor, CompletionStatus status);
	void _raise();
	static INV_OBJREF * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL NO_PERMISSION : public SystemException
    {
    public:
	NO_PERMISSION();
	~NO_PERMISSION();
	NO_PERMISSION(const NO_PERMISSION &);
	NO_PERMISSION(ULong minor, CompletionStatus status);
	void _raise();
	static NO_PERMISSION * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INTERNAL : public SystemException
    {
    public:
	INTERNAL();
	~INTERNAL();
	INTERNAL(const INTERNAL &);
	INTERNAL(ULong minor, CompletionStatus status);
	void _raise();
	static INTERNAL * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL MARSHAL : public SystemException
    {
    public:
	MARSHAL();
	~MARSHAL();
	MARSHAL(const MARSHAL &);
	MARSHAL(ULong minor, CompletionStatus status);
	void _raise();
	static MARSHAL * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INITIALIZE : public SystemException
    {
    public:
	INITIALIZE();
	~INITIALIZE();
	INITIALIZE(const INITIALIZE &);
	INITIALIZE(ULong minor, CompletionStatus status);
	void _raise();
	static INITIALIZE * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL NO_IMPLEMENT : public SystemException
    {
    public:
	NO_IMPLEMENT();
	~NO_IMPLEMENT();
	NO_IMPLEMENT(const NO_IMPLEMENT &);
	NO_IMPLEMENT(ULong minor, CompletionStatus status);
	void _raise();
	static NO_IMPLEMENT * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL BAD_TYPECODE : public SystemException
    {
    public:
	BAD_TYPECODE();
	~BAD_TYPECODE();
	BAD_TYPECODE(const BAD_TYPECODE &);
	BAD_TYPECODE(ULong minor, CompletionStatus status);
	void _raise();
	static BAD_TYPECODE * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL BAD_OPERATION : public SystemException
    {
    public:
	BAD_OPERATION();
	~BAD_OPERATION();
	BAD_OPERATION(const BAD_OPERATION &);
	BAD_OPERATION(ULong minor, CompletionStatus status);
	void _raise();
	static BAD_OPERATION * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL NO_RESOURCES : public SystemException
    {
    public:
	NO_RESOURCES();
	~NO_RESOURCES();
	NO_RESOURCES(const NO_RESOURCES &);
	NO_RESOURCES(ULong minor, CompletionStatus status);
	void _raise();
	static NO_RESOURCES * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL NO_RESPONSE : public SystemException
    {
    public:
	NO_RESPONSE();
	~NO_RESPONSE();
	NO_RESPONSE(const NO_RESPONSE &);
	NO_RESPONSE(ULong minor, CompletionStatus status);
	void _raise();
	static NO_RESPONSE * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL PERSIST_STORE : public SystemException
    {
    public:
	PERSIST_STORE();
	~PERSIST_STORE();
	PERSIST_STORE(const PERSIST_STORE &);
	PERSIST_STORE(ULong minor, CompletionStatus status);
	void _raise();
	static PERSIST_STORE * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL BAD_INV_ORDER : public SystemException
    {
    public:
	BAD_INV_ORDER();
	~BAD_INV_ORDER();
	BAD_INV_ORDER(const BAD_INV_ORDER &);
	BAD_INV_ORDER(ULong minor, CompletionStatus status);
	void _raise();
	static BAD_INV_ORDER * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL TRANSIENT : public SystemException
    {
    public:
	TRANSIENT();
	~TRANSIENT();
	TRANSIENT(const TRANSIENT &);
	TRANSIENT(ULong minor, CompletionStatus status);
	void _raise();
	static TRANSIENT * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL FREE_MEM : public SystemException
    {
    public:
	FREE_MEM();
	~FREE_MEM();
	FREE_MEM(const FREE_MEM &);
	FREE_MEM(ULong minor, CompletionStatus status);
	void _raise();
	static FREE_MEM * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INV_IDENT : public SystemException
    {
    public:
	INV_IDENT();
	~INV_IDENT();
	INV_IDENT(const INV_IDENT &);
	INV_IDENT(ULong minor, CompletionStatus status);
	void _raise();
	static INV_IDENT * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INV_FLAG : public SystemException
    {
    public:
	INV_FLAG();
	~INV_FLAG();
	INV_FLAG(const INV_FLAG &);
	INV_FLAG(ULong minor, CompletionStatus status);
	void _raise();
	static INV_FLAG * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INTF_REPOS : public SystemException
    {
    public:
	INTF_REPOS();
	~INTF_REPOS();
	INTF_REPOS(const INTF_REPOS &);
	INTF_REPOS(ULong minor, CompletionStatus status);
	void _raise();
	static INTF_REPOS * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL BAD_CONTEXT : public SystemException
    {
    public:
	BAD_CONTEXT();
	~BAD_CONTEXT();
	BAD_CONTEXT(const BAD_CONTEXT &);
	BAD_CONTEXT(ULong minor, CompletionStatus status);
	void _raise();
	static BAD_CONTEXT * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL OBJ_ADAPTER : public SystemException
    {
    public:
	OBJ_ADAPTER();
	~OBJ_ADAPTER();
	OBJ_ADAPTER(const OBJ_ADAPTER &);
	OBJ_ADAPTER(ULong minor, CompletionStatus status);
	void _raise();
	static OBJ_ADAPTER * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL DATA_CONVERSION : public SystemException
    {
    public:
	DATA_CONVERSION();
	~DATA_CONVERSION();
	DATA_CONVERSION(const DATA_CONVERSION &);
	DATA_CONVERSION(ULong minor, CompletionStatus status);
	void _raise();
	static DATA_CONVERSION * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL OBJECT_NOT_EXIST : public SystemException
    {
    public:
	OBJECT_NOT_EXIST();
	~OBJECT_NOT_EXIST();
	OBJECT_NOT_EXIST(const OBJECT_NOT_EXIST &);
	OBJECT_NOT_EXIST(ULong minor, CompletionStatus status);
	void _raise();
	static OBJECT_NOT_EXIST * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL TRANSACTION_REQUIRED : public SystemException
    {
    public:
	TRANSACTION_REQUIRED();
	~TRANSACTION_REQUIRED();
	TRANSACTION_REQUIRED(const TRANSACTION_REQUIRED &);
	TRANSACTION_REQUIRED(ULong minor, CompletionStatus status);
	void _raise();
	static TRANSACTION_REQUIRED * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL TRANSACTION_ROLLEDBACK : public SystemException
    {
    public:
	TRANSACTION_ROLLEDBACK();
	~TRANSACTION_ROLLEDBACK();
	TRANSACTION_ROLLEDBACK(const TRANSACTION_ROLLEDBACK &);
	TRANSACTION_ROLLEDBACK(ULong minor, CompletionStatus status);
	void _raise();
	static TRANSACTION_ROLLEDBACK * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INVALID_TRANSACTION : public SystemException
    {
    public:
	INVALID_TRANSACTION();
	~INVALID_TRANSACTION();
	INVALID_TRANSACTION(const INVALID_TRANSACTION &);
	INVALID_TRANSACTION(ULong minor, CompletionStatus status);
	void _raise();
	static INVALID_TRANSACTION * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL INV_POLICY : public SystemException
    {
    public:
	INV_POLICY();
	~INV_POLICY();
	INV_POLICY(const INV_POLICY &);
	INV_POLICY(ULong minor, CompletionStatus status);
	void _raise();
	static INV_POLICY * _narrow(Exception_ptr Exc);
    };

    class OBBEXPDLL CODESET_INCOMPATIBLE : public SystemException
    {
    public:
	CODESET_INCOMPATIBLE();
	~CODESET_INCOMPATIBLE();
	CODESET_INCOMPATIBLE(const CODESET_INCOMPATIBLE &);
	CODESET_INCOMPATIBLE(ULong minor, CompletionStatus status);
	void _raise();
	static CODESET_INCOMPATIBLE * _narrow(Exception_ptr Exc);
    };

// object classes

    class OBBEXPDLL Environment
    {
	friend class CORBA;

	public:
	    Environment();
	    ~Environment();

	    void clear ();

	    void exception (Exception_ptr);
	    Exception_ptr exception () const;

	    inline static Environment_ptr _nil () {return 0;}
	    static Environment_ptr _duplicate (Environment_ptr);

	    // OBB internal use only method (NO ONE ELSE SHOULD USE THIS!!!)
	    Exception_ptr OBB__exception_assume();

	private:
	    Exception_ptr _exception;
	    unsigned long refcnt;
	    void IncrementRefCount();
    };

    class OBBEXPDLL Environment_var : public _var
    {
    public:
	Environment_var() { ptr_ = Environment::_nil(); }
	Environment_var(Environment_ptr Env) { ptr_ = Env; }
	Environment_var(const Environment_var &Envv)
	    { ptr_ = Environment::_duplicate(Environment_ptr(Envv)); }
	~Environment_var() { release(ptr_); }
	inline Environment_var & operator=(Environment_ptr Env)
	    { release(ptr_); ptr_ = Env; return *this; }
	inline Environment_var & operator=(const Environment_var &Envv)
	    { if (this != &Envv) { release(ptr_);
	      ptr_ = Environment::_duplicate(Environment_ptr(Envv)); }
	      return *this; }
	inline Environment_ptr in() const { return ptr_; }
	inline Environment_ptr& inout() { return ptr_; }
	inline Environment_ptr& out()
	    { release(ptr_); ptr_ = Environment::_nil(); return ptr_; }
	inline Environment_ptr _retn()
	    { Environment_ptr val = ptr_; ptr_ = Environment::_nil(); return val; }
	inline Environment_ptr& ptr() { return ptr_; }
	inline operator Environment_ptr&() { return ptr_; }
	inline operator const Environment_ptr& () const { return ptr_; }
	inline Environment_ptr operator->() const { return ptr_; }
    private:
	Environment_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	Environment_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL Environment_out
    {
    public:
        Environment_out(Environment *& p) : ptr_(p) { ptr_ = 0; }
        Environment_out(Environment_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        Environment_out (const Environment_out & p) : ptr_(p.ptr_) {}
        inline Environment_out & operator=(const Environment_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline Environment_out& operator=(const Environment_var& a)
	    { ptr_ = Environment::_duplicate(Environment_ptr(a)); return *this; }
        inline Environment_out & operator=(Environment * p) { ptr_ = p; return *this; }
        inline operator Environment_ptr &() { return ptr_; }
        inline Environment_ptr & ptr() { return ptr_; }
        inline Environment_ptr operator->() { return ptr_; }
    private:
        Environment_ptr & ptr_;
    };


    class OBBEXPDLL Context
    {
    public:
	virtual const char * context_name() const = 0;
	virtual Context_ptr parent () const = 0;

	virtual Status create_child (const char *, Context_out) = 0;

	virtual Status set_one_value (const char *, const Any &) = 0;
	virtual Status set_values (NVList_ptr) = 0;
	virtual Status delete_values (const char *) = 0;
	virtual Status get_values (
			const char *, Flags, const char *, NVList_out) = 0;


	static Context_ptr _duplicate (Context_ptr Ctx);
	inline static Context_ptr _nil() {return 0;}

    protected:
	Context();
	virtual ~Context();
    };


    class OBBEXPDLL Context_var : public _var
    {
    public:
	Context_var() { ptr_ = Context::_nil(); }
	Context_var(Context_ptr Ctx) { ptr_ = Ctx; }
	Context_var(const Context_var &Ctxv)
		{ ptr_ = Context::_duplicate(Context_ptr(Ctxv)); }
	~Context_var() { release(ptr_); }
	Context_var & operator=(Context_ptr Ctx);
	Context_var & operator=(const Context_var &Ctxv)
	    { if (this != &Ctxv) { release(ptr_);
	      ptr_ = Context::_duplicate(Context_ptr(Ctxv)); }
	      return *this; }
	inline Context_ptr in() const { return ptr_; }
	inline Context_ptr& inout() { return ptr_; }
	inline Context_ptr& out()
	    { release(ptr_); ptr_ = Context::_nil(); return ptr_; }
	inline Context_ptr _retn()
	    { Context_ptr val = ptr_; ptr_ = Context::_nil(); return val; }
	inline Context_ptr& ptr() { return ptr_; }
	inline operator Context_ptr&() { return ptr_; }
	inline operator const Context_ptr& () const { return ptr_; }
	inline Context_ptr operator->() const { return ptr_; }
    private:
	Context_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	Context_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL Context_out
    {
    public:
        Context_out(Context *& p) : ptr_(p) { ptr_ = 0; }
        Context_out(Context_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        Context_out (const Context_out & p) : ptr_(p.ptr_) {}
        inline Context_out & operator=(const Context_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline Context_out& operator=(const Context_var& a)
	    { ptr_ = Context::_duplicate(Context_ptr(a)); return *this; }
        inline Context_out & operator=(Context * p) { ptr_ = p; return *this; }
        inline operator Context_ptr &() { return ptr_; }
        inline Context_ptr & ptr() { return ptr_; }
        inline Context_ptr operator->() { return ptr_; }
    private:
        Context_ptr & ptr_;
    };


 

    class OBBEXPDLL NamedValue
    {
	public:
	    virtual Flags flags () const = 0;
	    virtual const char * name () const = 0;
	    virtual Any * value () = 0;

	    static NamedValue_ptr _duplicate (NamedValue_ptr);
	    inline static NamedValue_ptr _nil() {return 0;}

	protected:
	    NamedValue() {}
	    virtual ~NamedValue() {}
    };

    class OBBEXPDLL NamedValue_var : public _var
    {
    public:
	NamedValue_var() {ptr_ = NamedValue::_nil();}
	NamedValue_var(NamedValue_ptr Nv) { ptr_ = Nv; }
	NamedValue_var(const NamedValue_var &Nvv)
		{ptr_ = NamedValue::_duplicate(NamedValue_ptr(Nvv));}
	~NamedValue_var() {release(ptr_);}
	NamedValue_var & operator=(NamedValue_ptr Nv);
	inline NamedValue_var & operator=(const NamedValue_var &Nvv)
	    { if (this != &Nvv) { release(ptr_);
	      ptr_ = NamedValue::_duplicate(NamedValue_ptr(Nvv)); }
	      return *this; }
	inline NamedValue_ptr in() const { return ptr_; }
	inline NamedValue_ptr& inout() { return ptr_; }
	inline NamedValue_ptr& out()
	    { release(ptr_); ptr_ = NamedValue::_nil(); return ptr_; }
	inline NamedValue_ptr _retn()
	    { NamedValue_ptr val = ptr_; ptr_ = NamedValue::_nil(); return val; }
	inline NamedValue_ptr& ptr() { return ptr_; }
	inline operator NamedValue_ptr&() {return ptr_;}
	inline operator const NamedValue_ptr& () const {return ptr_;}
	inline NamedValue_ptr operator->() const {return ptr_;}
    private:
	NamedValue_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	NamedValue_var & operator=(const _var &Varv);
    };
    class OBBEXPDLL NamedValue_out
    {
    public:
        NamedValue_out(NamedValue_ptr & p) : ptr_(p) { ptr_ = 0; }
        NamedValue_out(NamedValue_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        NamedValue_out (const NamedValue_out & p) : ptr_(p.ptr_) {}
        inline NamedValue_out & operator=(const NamedValue_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline NamedValue_out& operator=(const NamedValue_var& a)
	    { ptr_ = NamedValue::_duplicate(NamedValue_ptr(a)); return *this; }
        inline NamedValue_out & operator=(NamedValue * p) { ptr_ = p; return *this; }
        inline operator NamedValue_ptr & () { return ptr_; }
        inline NamedValue_ptr & ptr() { return ptr_; }
        inline NamedValue_ptr  operator->() { return ptr_; }
    private:
        NamedValue_ptr & ptr_;
    };



    class OBBEXPDLL NVList
    {
    public:
	virtual NamedValue_ptr add (Flags) = 0;
	virtual NamedValue_ptr add_item (const char *, Flags) = 0;
	virtual NamedValue_ptr add_value (const char *,
						const Any&,
						Flags) = 0;

	virtual ULong count () const = 0;
	virtual NamedValue_ptr item (ULong) = 0;
	virtual Status remove (ULong) = 0;

	static NVList_ptr _duplicate (NVList_ptr Nvl);
	inline static NVList_ptr _nil() {return 0;}

    protected:
	virtual ~NVList() {}
	inline NVList() {}
	inline NVList(ULong) {}
    };

    class OBBEXPDLL NVList_var : public _var
    {
    public:
	NVList_var() {ptr_ = NVList::_nil();}
	NVList_var(NVList_ptr Nvl) {ptr_ = Nvl;}
	NVList_var(const NVList_var &Nvlv)
		{ptr_ = NVList::_duplicate(NVList_ptr(Nvlv));}
	~NVList_var() {release(ptr_);}
	NVList_var & operator=(NVList_ptr Nvl);
	inline NVList_var & operator=(const NVList_var &Nvlv)
	    { if (this != &Nvlv) { release(ptr_);
	      ptr_ = NVList::_duplicate(NVList_ptr(Nvlv)); }
	      return *this; }
	inline NVList_ptr in() const { return ptr_; }
	inline NVList_ptr& inout() { return ptr_; }
	inline NVList_ptr& out()
	    { release(ptr_); ptr_ = NVList::_nil(); return ptr_; }
	inline NVList_ptr _retn()
	    { NVList_ptr val = ptr_; ptr_ = NVList::_nil(); return val; }
	inline NVList_ptr& ptr() { return ptr_; }
	inline operator NVList_ptr&() { return ptr_; }
	inline operator const NVList_ptr&() const { return ptr_; }
	inline NVList_ptr operator->() const { return ptr_; }
    private:
	NVList_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	NVList_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL NVList_out
    {
    public:
        NVList_out(NVList_ptr & p) : ptr_(p) { ptr_ = 0; }
        NVList_out(NVList_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        NVList_out (const NVList_out & p) : ptr_(p.ptr_) {}
        inline NVList_out & operator=(const NVList_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline NVList_out& operator=(const NVList_var& a)
	    { ptr_ = NVList::_duplicate(NVList_ptr(a)); return *this; }
        inline NVList_out & operator=(NVList * p) { ptr_ = p; return *this; }
        inline operator NVList_ptr &() { return ptr_; }
        inline NVList_ptr & ptr() { return ptr_; }
        inline NVList_ptr  operator->() { return ptr_; }
    private:
        NVList_ptr & ptr_;
    };


    // class Object

    class OBBEXPDLL Object
    {
    public:
	Status _create_request (
	    Context_ptr ctx,
	    const char * operation,
	    NVList_ptr arg_list,
	    NamedValue_ptr result,
	    Request_out equest,
	    Flags req_flags);
	Status _create_request (
	    Context_ptr ctx,
	    const char * operation,
	    NVList_ptr arg_list,
	    NamedValue_ptr result,
	    ExceptionList_ptr excep_list,
            ContextList_ptr ctx_list,
	    Request_out equest,
	    Flags req_flags);
	InterfaceDef_ptr _get_interface();
	Request_ptr _request (const char * operation);

	static Object_ptr _duplicate(Object_ptr obj);
	inline static Object_ptr _nil() {return 0;}
	Boolean _is_a (const char * repositoryId);
	Boolean _non_existent();
	Boolean _is_equivalent(Object_ptr other_obj);
	ULong _hash(ULong max_bound);

	// OBB Internal routines
	ObjRef *OBB__GetObjRef();
	void OBB__SetObjRef(ObjRef * obj_ref);
        static Object_ptr OBB__Create(ObjRef * obj_ref);
	char *OBB__GetObjectType() const;
	void OBB__SetObjectType(const char * object_type);
	ULong OBB__decrement_refcount();
        void OBB__increment_refcount();
        ULong OBB__refcount();
	static void OBB__delete( Object_ptr obj);
        ORB_ptr OBB__get_orb();
	void OBB__SetObjectPtr(void * ObjPtr);
	void * OBB__is_a_local (const char * repositoryId);
	char *OBB__GetInterfaceId() const;
	void OBB__SetBaseClass(const char * RepId);
	inline Boolean OBB__GetManagedObj() { return m_managed_obj; }
	inline Octet OBB__GetMagic() { return m_magic; }
	Boolean OBB__IsMarshalable();

    private:

	ULong		m_refcount;
	ObjRef		* m_objref;
	char		* m_object_type;
	void		* m_object_ptr;
	const char	* m_base_id_ptr;

    protected:
	Object();
	Object(ObjRef *);
	virtual ~Object();
	Boolean		m_managed_obj;
	Octet		m_magic;
    };

    class OBBEXPDLL Object_var : public _var
    {
    public:
	Object_var() { ptr_ = Object::_nil(); }
	Object_var(Object_ptr Obj) { ptr_ = Obj; }
	Object_var(const Object_var &Objv)
	    { ptr_ = Object::_duplicate(Object_ptr(Objv)); }
	~Object_var() { release(ptr_); }
	Object_var & operator=(Object_ptr Obj);
	Object_var& operator=(const Object_var& Objv);
	inline Object_ptr in() const { return ptr_; }
	inline Object_ptr& inout() { return ptr_; }
	inline Object_ptr& out()
	    { release(ptr_); ptr_ = Object::_nil(); return ptr_; }
	inline Object_ptr _retn()
	    { Object_ptr val = ptr_; ptr_ = Object::_nil(); return val; }
	inline Object_ptr& ptr() { return ptr_; }
	operator Object_ptr&();
	operator const Object_ptr& () const;
	Object_ptr operator->() const;
    private:
	Object_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	Object_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL Object_out
    {
	public:
	    Object_out(Object_ptr& Obj) : ptr_(Obj) { ptr_ = Object::_nil(); }
	    Object_out(Object_var& Obj) : ptr_(Obj.ptr())
		{ release(ptr_); ptr_ = Object::_nil(); }
	    Object_out(const Object_out& a) : ptr_(a.ptr_) {}
	    inline Object_out& operator=(const Object_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline Object_out& operator=(const Object_var& a)
		{ ptr_ = Object::_duplicate(Object_ptr(a)); return *this; }
	    inline Object_out& operator=(Object_ptr p) { ptr_ = p; return *this; }
	    inline operator Object_ptr&() { return ptr_; }
	    inline Object_ptr& ptr() { return ptr_; }
	    inline Object_ptr operator->() { return ptr_; }

	private:
	    Object_ptr& ptr_;
    };

    class OBBEXPDLL ORB
    {
    public:
        typedef char * ObjectId;
	typedef long Ctx;

#if defined(_WIN32)
	typedef ULong TID;
#else
#if (defined(__alpha) && defined(__osf__)) || (defined(_AIX) && !defined(__64BIT__))
	typedef void * TID;
#else
	typedef ULong TID;
#endif
#endif
	class OBBEXPDLL RequestSeq
	{
	public:
	    class OBBEXPDLL _ForSeq_var : public _var
	    {
	    public:
		_ForSeq_var();
		_ForSeq_var(Request_ptr Req) { _release = 1; ptr = Req; }
		_ForSeq_var(const _ForSeq_var &Reqv);
		~_ForSeq_var();
		_ForSeq_var & operator=(Request_ptr Req);
		inline operator const Request_ptr&() const { return ptr; }
		inline operator Request_ptr&() { return ptr; }
		inline Request_ptr operator->() const { return ptr; } 

		inline void OBB__release(Boolean release) { _release = release; }
		inline Boolean OBB__release() { return _release; }
	    private:
		Request_ptr ptr;
		Boolean _release;
		// hidden assignment operator to cause compile time error...
		_ForSeq_var & operator=(const _ForSeq_var &Reqv);
		_ForSeq_var & operator=(const _var &Varv);
	    };

	    RequestSeq();
	    RequestSeq(ULong maxlen);
	    RequestSeq(ULong maxlen, ULong len,
		       Request_ptr *reqptr,
		       Boolean release = CORBA_FALSE);
	    RequestSeq(const RequestSeq &);
	    ~RequestSeq();

	    RequestSeq &operator=(const RequestSeq&);

	    inline ULong maximum() const { return _maximum; }
	    void length(ULong);
	    inline ULong length() const { return _length; }

	    _ForSeq_var & operator[](ULong);
	    const _ForSeq_var &operator[](ULong) const;

	    static Request_ptr *allocbuf(ULong nelems);
	    static void freebuf(Request_ptr *data);

	private:
	    static _ForSeq_var *OBB__allocbuf(ULong nelems, Boolean release);
	    static void OBB__freebuf(_ForSeq_var *data);

	    ULong		_maximum;
	    ULong		_length;
	    _ForSeq_var		*_data;
	    Boolean		_release;
	};

        class OBBEXPDLL ObjectIdList
        {
        public:
            class OBBEXPDLL _ForSeq_var : public _var
            {
            public:
                _ForSeq_var() { _release = CORBA_TRUE; _data = 0; }
                _ForSeq_var(ObjectId _str)
			{ _release = CORBA_TRUE; _data = CORBA::string_dup(_str); }
                _ForSeq_var(const _ForSeq_var &_fsv)
			{ _release = CORBA_TRUE; _data = CORBA::string_dup(_fsv._data); }
                ~_ForSeq_var();
                _ForSeq_var &operator=(ObjectId _ptr);
                inline operator ObjectId() const { return _data; }
                inline operator ObjectId () { return _data; }
                inline void OBB__release(Boolean _relse) { _release = _relse; }
                inline Boolean OBB__release() { return _release; }
                static ObjectId allocbuf(ULong _nelems);
                static void freebuf(ObjectId _ptr);

            private:
                ObjectId _data;
                Boolean _release;
                // hidden assignment operator to cause compile time error...
                _ForSeq_var & operator=(const _ForSeq_var &_ptr);
            };  // class _ForSeq_var

            ObjectIdList();
            ObjectIdList(ULong _max);
            ObjectIdList(ULong _max,
                         ULong _length,
                         ObjectId *_value,
                         Boolean _relse = CORBA_FALSE);
            ObjectIdList(const ObjectIdList &_ptr);
            ~ObjectIdList();

            ObjectIdList & operator=(const ObjectIdList& _ptr);

            inline ULong maximum() const { return _maximum; }
            void length(ULong);
            inline ULong length() const { return _current; }

            inline _ForSeq_var & operator[](ULong _index)
			{ return (_data[_index]); }
            const _ForSeq_var & operator[](ULong _index) const;
            static ObjectId *allocbuf(ULong _nelems);
            static void freebuf(ObjectId *data);

         private:
             static _ForSeq_var *OBB__allocbuf(ULong _nelems);
             static void OBB__freebuf(_ForSeq_var *data);

             _ForSeq_var *_data;
             ULong _maximum;
             ULong _current;
             Boolean _release;
        };  // class ObjectIdList


        class OBBEXPDLL ObjectIdList_var
        {
        public:
            ObjectIdList_var() { _ptr = 0; }
            ObjectIdList_var(ObjectIdList * ObjIdListPtr)
		{ _ptr = ObjIdListPtr; }
            ObjectIdList_var(const ObjectIdList_var & ObjIdListref)
		{ *this = ObjIdListref; }
            ~ObjectIdList_var();
            ObjectIdList_var & operator=(ObjectIdList *);
            ObjectIdList_var &operator=(const ObjectIdList_var &);
            inline ObjectIdList::_ForSeq_var & operator[](ULong _index)
		{ return ((*_ptr)[_index]); }
            inline ObjectIdList * operator->() { return _ptr; }
            inline ObjectIdList * operator->() const { return _ptr; }
        private:
            ObjectIdList *_ptr;
        };  // class ObjectIdList_var

        class OBBEXPDLL InvalidName : public UserException
        {
        public:
            static InvalidName * _narrow(Exception_ptr);
            InvalidName ();
            InvalidName (const InvalidName & InvNamRef)
		{ *this = InvNamRef; }
            ~InvalidName () {}
            inline InvalidName & operator=(const InvalidName &)
		{ return *this; }
        };  // class InvalidName


        class OBBEXPDLL InvalidName_var
        {
        public:
            InvalidName_var() { _ptr = 0; }
            InvalidName_var(InvalidName * InvNamPtr) { _ptr = InvNamPtr; } 
            InvalidName_var(const InvalidName_var & InvNamVarRef)
		{ _ptr = 0; *this = InvNamVarRef; }
            ~InvalidName_var();
            InvalidName_var & operator=(InvalidName *);
            InvalidName_var & operator=(const InvalidName_var &);
            inline InvalidName * operator->() { return _ptr; }
            inline InvalidName * operator->() const { return _ptr; }
        private:
            InvalidName *_ptr;
        };  // class InvalidName_var

	virtual Status create_environment (Environment_out) = 0;
	virtual Status create_list (Long Count,
        				NVList_out List) = 0;
	virtual Status create_exception_list( ExceptionList_out List) = 0;
	virtual Status create_context_list( ContextList_out List) = 0;
	virtual Status create_named_value(NamedValue_out NewNamedValue) = 0;
	virtual Status create_operation_list (OperationDef_ptr Operation,
					NVList_out List) = 0;

	virtual Status get_default_context (Context_out DefCtxObject) = 0;
	virtual Status get_next_response (Request_out Req) = 0;

	virtual char * object_to_string (Object_ptr Obj) = 0;

	virtual Boolean poll_next_response () = 0;

	virtual Status send_multiple_requests_oneway (
	    				const RequestSeq &SeqOfReq) = 0;
	virtual Status send_multiple_requests_deferred (
	    				const RequestSeq &SeqOfReq) = 0;

	virtual Object_ptr string_to_object (const char *StrToConvert) = 0;

	static ORB_ptr _duplicate (ORB_ptr Orb);
	inline static ORB_ptr _nil() { return 0; }

        virtual ObjectIdList * list_initial_services () = 0;

        virtual Object_ptr resolve_initial_references (
                    			const char * Ident) = 0;

	virtual Boolean work_pending () = 0;
	virtual void perform_work () = 0;
	virtual void run () = 0;
	virtual void shutdown (Boolean WaitForCompletion) = 0;

        virtual Policy_ptr create_policy (PolicyType type, const Any & val) = 0; 



	virtual ValueFactory register_value_factory(const RepositoryId id,
						    const ValueFactory factory) = 0;
	virtual void unregister_value_factory(const RepositoryId id) = 0;
	virtual ValueFactory lookup_value_factory(const RepositoryId id) = 0;

	virtual void destroy () = 0;

	// Extensions to support sharing context between threads
	virtual Ctx get_ctx() = 0;
	virtual void set_ctx(Ctx) = 0;
	virtual void clear_ctx() = 0;

	// Thread extensions
	virtual void inform_thread_exit(TID) = 0;

	// OBB internal use functions
	static NamedValue_ptr create_named_value(const char *Name,
	    				Any *Value,
                                        Flags Flgs);

	// OBB internal use functions
	static void OBB__PrintTrackedObjects();
    protected:
	ORB() {}
        virtual ~ORB() {}

    private:
	// Hidden functions to disallow direct copy.
	ORB( const ORB& t);
	void operator=(const ORB&);

    };

    class OBBEXPDLL ORB_var : public _var
    {
    public:
	ORB_var() { ptr_ = ORB::_nil(); }
	ORB_var(ORB_ptr Orb) { ptr_ = Orb; }
	ORB_var(const ORB_var &Orbv)
		{ ptr_ = ORB::_duplicate(ORB_ptr(Orbv)); }
	~ORB_var() { release(ptr_); }
	ORB_var & operator=(ORB_ptr Orb);
	inline ORB_var & operator=(const ORB_var &Orbv)
	    { if (this != &Orbv) { release(ptr_);
	      ptr_ = ORB::_duplicate(ORB_ptr(Orbv)); }
	      return *this; }
	inline ORB_ptr in() const { return ptr_; }
	inline ORB_ptr& inout() { return ptr_; }
	inline ORB_ptr& out()
	    { release(ptr_); ptr_ = ORB::_nil(); return ptr_; }
	inline ORB_ptr _retn()
	    { ORB_ptr val = ptr_; ptr_ = ORB::_nil(); return val; }
	inline ORB_ptr& ptr() { return ptr_; }
	inline operator ORB_ptr&() { return ptr_; }
	inline operator const ORB_ptr& () const { return ptr_; }
	inline ORB_ptr operator->() const { return ptr_; }
    private:
	ORB_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	ORB_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL ORB_out
    {
	public:
	    ORB_out(ORB_ptr& Obj) : ptr_(Obj) { ptr_ = ORB::_nil(); }
	    ORB_out(ORB_var& Obj) : ptr_(Obj.ptr())
		{ release(ptr_); ptr_ = ORB::_nil(); }
	    ORB_out(const ORB_out& a) : ptr_(a.ptr_) {}
	    inline ORB_out& operator=(const ORB_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline ORB_out& operator=(const ORB_var& a)
		{ ptr_ = ORB::_duplicate(ORB_ptr(a)); return *this; }
	    inline ORB_out& operator=(ORB_ptr p) { ptr_ = p; return *this; }
	    inline operator ORB_ptr&() { return ptr_; }
	    inline ORB_ptr& ptr() { return ptr_; }
	    inline ORB_ptr operator->() { return ptr_; }

	private:
	    ORB_ptr& ptr_;
    };

    class OBBEXPDLL Principal
    {
    public:
	static Principal_ptr _duplicate (Principal_ptr Prin);
	inline static Principal_ptr _nil() {return 0;}

    protected:
	Principal() {}
	virtual ~Principal() {}

    };

    class OBBEXPDLL Principal_var : public _var
    {
    public:
	Principal_var() { ptr_ = Principal::_nil(); }
	Principal_var(Principal_ptr Prin) { ptr_ = Prin; }
	Principal_var(const Principal_var &Prinv)
		{ ptr_ = Principal::_duplicate(Principal_ptr(Prinv)); }
	~Principal_var() { release(ptr_); }
	Principal_var & operator=(Principal_ptr Prin);
	inline Principal_var & operator=(const Principal_var &Prinv)
	    { if (this != &Prinv) { release(ptr_);
	      ptr_ = Principal::_duplicate(Principal_ptr(Prinv)); }
	      return *this; }
	inline Principal_ptr in() const { return ptr_; }
	inline Principal_ptr& inout() { return ptr_; }
	inline Principal_ptr& out()
	    { release(ptr_); ptr_ = Principal::_nil(); return ptr_; }
	inline Principal_ptr _retn()
	    { Principal_ptr val = ptr_; ptr_ = Principal::_nil(); return val; }
	inline Principal_ptr& ptr() { return ptr_; }
	inline operator Principal_ptr&() { return ptr_; }
	inline operator const Principal_ptr&() const { return ptr_; }
	inline Principal_ptr operator->() const { return ptr_; }
    private:
	Principal_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	Principal_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL Principal_out
    {
	public:
	    Principal_out(Principal_ptr& Obj) : ptr_(Obj) { ptr_ = Principal::_nil(); }
	    Principal_out(Principal_var& Obj) : ptr_(Obj.ptr())
		{ release(ptr_); ptr_ = Principal::_nil(); }
	    Principal_out(const Principal_out& a) : ptr_(a.ptr_) {}
	    inline Principal_out& operator=(const Principal_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline Principal_out& operator=(const Principal_var& a)
		{ ptr_ = Principal::_duplicate(Principal_ptr(a)); return *this; }
	    inline Principal_out& operator=(Principal_ptr p) { ptr_ = p; return *this; }
	    inline operator Principal_ptr&() { return ptr_; }
	    inline Principal_ptr& ptr() { return ptr_; }
	    inline Principal_ptr operator->() { return ptr_; }

	private:
	    Principal_ptr& ptr_;
    };

    class OBBEXPDLL ExceptionList
    {
    public:

	virtual ULong count () = 0;

	virtual void add (TypeCode_ptr TC) = 0;

	virtual void add_consume (TypeCode_ptr TC) = 0;

	virtual TypeCode_ptr item (ULong Index) = 0;

	virtual Status remove (ULong Index) = 0;

	static ExceptionList_ptr _duplicate (ExceptionList_ptr CtxL);
	inline static ExceptionList_ptr _nil() {return 0;}

    protected:
        virtual ~ExceptionList() {}

    };

    class OBBEXPDLL ExceptionList_var : public _var
    {
    public:
	ExceptionList_var() { ptr_ = ExceptionList::_nil(); }
	ExceptionList_var(ExceptionList_ptr EList) { ptr_ = EList; }
	ExceptionList_var(const ExceptionList_var &Listv)
		{ ptr_ = ExceptionList::_duplicate(ExceptionList_ptr(Listv)); }
	~ExceptionList_var() { release(ptr_); }
	ExceptionList_var & operator=(ExceptionList_ptr EList);
	inline ExceptionList_var & operator=(const ExceptionList_var &EListv)
	    { if (this != &EListv) { release(ptr_);
	      ptr_ = ExceptionList::_duplicate(ExceptionList_ptr(EListv)); }
	      return *this; }
	inline ExceptionList_ptr in() const { return ptr_; }
	inline ExceptionList_ptr& inout() { return ptr_; }
	inline ExceptionList_ptr& out()
	    { release(ptr_); ptr_ = ExceptionList::_nil(); return ptr_; }
	inline ExceptionList_ptr _retn()
	    { ExceptionList_ptr val = ptr_; ptr_ = ExceptionList::_nil(); return val; }
	inline ExceptionList_ptr& ptr() { return ptr_; }
	inline operator ExceptionList_ptr&() { return ptr_; }
	inline operator const ExceptionList_ptr&() const { return ptr_; }
	inline ExceptionList_ptr operator->() const { return ptr_; }
    private:
	ExceptionList_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	ExceptionList_var & operator=(const _var &Varv);
    };
    class OBBEXPDLL ExceptionList_out
    {
    public:
        ExceptionList_out(ExceptionList *& p) : ptr_(p) { ptr_ = 0; }
        ExceptionList_out(ExceptionList_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        ExceptionList_out (const ExceptionList_out & p) : ptr_(p.ptr_) {}
        inline ExceptionList_out & operator=(const ExceptionList_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline ExceptionList_out& operator=(const ExceptionList_var& a)
	    { ptr_ = ExceptionList::_duplicate(ExceptionList_ptr(a)); return *this; }
        inline ExceptionList_out & operator=(ExceptionList * p) { ptr_ = p; return *this; }
        inline operator ExceptionList_ptr &() { return ptr_; }
        inline ExceptionList_ptr & ptr() { return ptr_; }
        inline ExceptionList_ptr operator->() { return ptr_; }
    private:
        ExceptionList_ptr & ptr_;
    };


    class OBBEXPDLL ContextList
    {
    public:

	virtual ULong count () = 0;

	virtual void add (const char* CtxtString) = 0;

	virtual void add_consume (char * CtxtString) = 0;

	virtual const char * item (ULong Index) = 0;

	virtual Status remove (ULong Index) = 0;

	static ContextList_ptr _duplicate (ContextList_ptr CtxL);
	inline static ContextList_ptr _nil() {return 0;}

	static ContextList * OBB__static_items( ULong count,
        					char ** Values);

    protected:

        virtual ~ContextList() {}
    };

    class OBBEXPDLL ContextList_var : public _var
    {
    public:
	ContextList_var() { ptr_ = ContextList::_nil(); }
	ContextList_var(ContextList_ptr CList) { ptr_ = CList; }
	ContextList_var(const ContextList_var &CList)
		{ ptr_ = ContextList::_duplicate(ContextList_ptr(CList)); }
	~ContextList_var() { release(ptr_); }
	ContextList_var & operator=(ContextList_ptr CList);
	inline ContextList_var & operator=(const ContextList_var &CListv)
	    { if (this != &CListv) { release(ptr_);
	      ptr_ = ContextList::_duplicate(ContextList_ptr(CListv)); }
	      return *this; }
	inline ContextList_ptr in() const { return ptr_; }
	inline ContextList_ptr& inout() { return ptr_; }
	inline ContextList_ptr& out()
	    { release(ptr_); ptr_ = ContextList::_nil(); return ptr_; }
	inline ContextList_ptr _retn()
	    { ContextList_ptr val = ptr_; ptr_ = ContextList::_nil(); return val; }
	inline ContextList_ptr& ptr() { return ptr_; }
	inline operator ContextList_ptr&() { return ptr_; }
	inline operator const ContextList_ptr& () const { return ptr_; }
	inline ContextList_ptr operator->() const { return ptr_; }
    private:
	ContextList_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	ContextList_var & operator=(const _var &Varv);
    }; 
    class OBBEXPDLL ContextList_out
    {
    public:
        ContextList_out(ContextList *& p) : ptr_(p) { ptr_ = 0; }
        ContextList_out(ContextList_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        ContextList_out (const ContextList_out & p) : ptr_(p.ptr_) {}
        inline ContextList_out & operator=(const ContextList_out & p)
	    { ptr_ = p.ptr_; return *this; } 
	inline ContextList_out& operator=(const ContextList_var& a)
	    { ptr_ = ContextList::_duplicate(ContextList_ptr(a)); return *this; }
        inline ContextList_out & operator=(ContextList * p) { ptr_ = p; return *this; }
        inline operator ContextList_ptr &() { return ptr_; }
        inline ContextList_ptr & ptr() { return ptr_; }
        inline ContextList_ptr operator->() { return ptr_; }
    private:
        ContextList_ptr & ptr_;
    };



    class OBBEXPDLL Request
    {
    friend class Object;

    public:

	virtual Object_ptr target () const = 0;

	virtual const char * operation () const = 0;

	virtual NVList_ptr arguments () = 0;

	virtual NamedValue_ptr result () = 0;

	virtual Environment_ptr env () = 0;

	virtual ExceptionList_ptr exceptions () = 0;

	virtual ContextList_ptr contexts() = 0;


	virtual void ctx (Context_ptr) = 0;

	virtual Context_ptr ctx () const = 0;


	// argument manipulation helper functions
	virtual Any & add_in_arg () = 0;

	virtual Any & add_in_arg (const char * Name) = 0;

	virtual Any & add_inout_arg () = 0;

	virtual Any & add_inout_arg (const char * Name) = 0;

	virtual Any & add_out_arg () = 0;

	virtual Any & add_out_arg (const char * Name) = 0;

	virtual void set_return_type ( TypeCode_ptr TC) = 0;

	virtual Any & return_value() = 0;



	virtual Status invoke () = 0;

	virtual Status send_oneway () = 0;

	virtual Status send_deferred () = 0;

	virtual Status get_response () = 0;

	virtual Boolean poll_response () = 0;


	static Request_ptr _duplicate (Request_ptr Req);
	inline static Request_ptr _nil() {return 0;}

	// Internal use only
	virtual void OBB__invoke () = 0;


    protected:

        virtual ~Request() {}

    };

    class OBBEXPDLL Request_var : public _var
    {
    public:
	Request_var() { ptr_ = Request::_nil(); }
	Request_var(Request_ptr Req) { ptr_ = Req; }
	Request_var(const Request_var &Reqv)
		{ ptr_ = Request::_duplicate(Request_ptr(Reqv)); }
	~Request_var() { release(ptr_); }
	Request_var & operator=(Request_ptr Req);
	inline Request_var & operator=(const Request_var &Reqv)
	    { if (this != &Reqv) { release(ptr_);
	      ptr_ = Request::_duplicate(Request_ptr(Reqv)); }
	      return *this; }
	inline Request_ptr in() const { return ptr_; }
	inline Request_ptr& inout() { return ptr_; }
	inline Request_ptr& out()
	    { release(ptr_); ptr_ = Request::_nil(); return ptr_; }
	inline Request_ptr _retn()
	    { Request_ptr val = ptr_; ptr_ = Request::_nil(); return val; }
	inline Request_ptr& ptr() { return ptr_; }
	inline operator Request_ptr&() { return ptr_; }
	inline operator const Request_ptr& () const { return ptr_; }
	inline Request_ptr operator->() const { return ptr_; }
    private:
	Request_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	Request_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL Request_out
    {
    public:
        Request_out(Request *& p) : ptr_(p) { ptr_ = 0; }
        Request_out(Request_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        Request_out (const Request_out & p) : ptr_(p.ptr_) {}
        inline Request_out & operator=(const Request_out & p)
	    { ptr_ = p.ptr_; return *this; } 
	inline Request_out& operator=(const Request_var& a)
	    { ptr_ = Request::_duplicate(Request_ptr(a)); return *this; }
        inline Request_out & operator=(Request * p) { ptr_ = p; return *this; }
        inline operator Request_ptr &() { return ptr_; }
        inline Request_ptr & ptr() { return ptr_; }
        inline Request_ptr  operator->() { return ptr_; }
    private:
        Request_ptr & ptr_;
    };

    class OBBEXPDLL TypeCode
    {
    public:
	virtual Boolean equal (TypeCode_ptr) const = 0;
	virtual TCKind kind () const = 0;
	virtual const char * id () const = 0;
	virtual Any * parameter (Long) const = 0;
	virtual Long param_count () const = 0;

	static TypeCode_ptr _duplicate (TypeCode_ptr Typ);
	inline static TypeCode_ptr _nil() {return 0;}

    protected:
	TypeCode() {}
	virtual ~TypeCode() {}
    };

    class OBBEXPDLL TypeCode_var : public _var
    {
    public:
	TypeCode_var() { ptr_ = TypeCode::_nil(); }
	TypeCode_var(TypeCode_ptr Tc) { ptr_ = Tc; }
	TypeCode_var(const TypeCode_var &Tcv)
		{ ptr_ = TypeCode::_duplicate(TypeCode_ptr(Tcv)); }
	~TypeCode_var() { release(ptr_); }
	TypeCode_var & operator=(TypeCode_ptr Tc);
	inline TypeCode_var & operator=(const TypeCode_var &Tcv)
	    { if (this != &Tcv) { release(ptr_);
	      ptr_ = TypeCode::_duplicate(TypeCode_ptr(Tcv)); }
	      return *this; }
	inline TypeCode_ptr in() const { return ptr_; }
	inline TypeCode_ptr& inout() { return ptr_; }
	inline TypeCode_ptr& out()
	    { release(ptr_); ptr_ = TypeCode::_nil(); return ptr_; }
	inline TypeCode_ptr _retn()
	    { TypeCode_ptr val = ptr_; ptr_ = TypeCode::_nil(); return val; }
	inline TypeCode_ptr& ptr() { return ptr_; }
	inline operator TypeCode_ptr&() { return ptr_; }
	inline operator const TypeCode_ptr& () const { return ptr_; }
	inline TypeCode_ptr operator->() const { return ptr_; }
    private:
	TypeCode_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	TypeCode_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL TypeCode_out
    {
	public:
	    TypeCode_out(TypeCode_ptr& Obj) : ptr_(Obj) { ptr_ = TypeCode::_nil(); }
	    TypeCode_out(TypeCode_var& Obj) : ptr_(Obj.ptr())
		{ release(ptr_); ptr_ = TypeCode::_nil(); }
	    TypeCode_out(const TypeCode_out& a) : ptr_(a.ptr_) {}
	    inline TypeCode_out& operator=(const TypeCode_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline TypeCode_out& operator=(const TypeCode_var& a)
		{ ptr_ = TypeCode::_duplicate(TypeCode_ptr(a)); return *this; }
	    inline TypeCode_out& operator=(TypeCode_ptr p) { ptr_ = p; return *this; }
	    inline operator TypeCode_ptr&() { return ptr_; }
	    inline TypeCode_ptr& ptr() { return ptr_; }
	    inline TypeCode_ptr operator->() { return ptr_; }

	private:
	    TypeCode_ptr& ptr_;
    };

    // CORBA::Current
    class OBBEXPDLL Current : public Object
    {
    public:
	static Current_ptr _duplicate (Current_ptr Prin);
	inline static Current_ptr _nil() {return 0;}

    protected:
	Current() {}
	virtual ~Current() {};
    };

    // No CORBA::Current_var as per-process singleton object


    // CORBA::Policy
    class OBBEXPDLL Policy
    {
    public:
	inline static Policy_ptr _nil () { return 0;}

        virtual Policy_ptr copy () = 0;
        virtual void destroy () = 0;
        inline virtual PolicyType policy_type () { return (PolicyType) OBB__id(); }

	// OBB internal use functions
	virtual ULong OBB__id() const = 0;

    protected:
	Policy() {}
	virtual ~Policy() {};
    };

    // CORBA::Policy_var
    class OBBEXPDLL Policy_var : public _var
    {
    public:
	Policy_var() { ptr_ = 0; }
	Policy_var(Policy_ptr Pol) { ptr_ = Pol; }
	Policy_var(const Policy_var &Polv);
	~Policy_var() { if (ptr_) ptr_->destroy(); }
	Policy_var & operator=(Policy_ptr Pol);
	inline Policy_var & operator=(const Policy_var &Polv)
	    { if (this != &Polv) { if (Policy_ptr(Polv))
		ptr_ = Policy_ptr(Polv)->copy(); }
	      return *this; }
	inline Policy_ptr in() const { return ptr_; }
	inline Policy_ptr& inout() { return ptr_; }
	inline Policy_ptr& out()
	    { if (ptr_) ptr_->destroy(); ptr_ = Policy::_nil(); return ptr_; }
	inline Policy_ptr _retn()
	    { Policy_ptr val = ptr_; ptr_ = Policy::_nil(); return val; }
	inline Policy_ptr& ptr() { return ptr_; }
	inline operator Policy_ptr&() { return ptr_; }
	inline operator const Policy_ptr& () const { return ptr_; }
	inline Policy_ptr operator->() const { return ptr_; }
    private:
	Policy_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	Policy_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL Policy_out
    {
    public:
        Policy_out(Policy *& p) : ptr_(p) { ptr_ = Policy::_nil(); }
        Policy_out(Policy_var & p) : ptr_(p.ptr())
	    { if (ptr_) ptr_->destroy(); ptr_ = Policy::_nil(); }
        Policy_out (const Policy_out & p) : ptr_(p.ptr_) {}
        inline Policy_out & operator=(const Policy_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline Policy_out& operator=(const Policy_var& a)
	    { ptr_ = Policy::_nil(); Policy_ptr p_ptr = a.in();
	      if (p_ptr) ptr_ = p_ptr->copy(); return *this; }
        inline Policy_out & operator=(Policy * p) { ptr_ = p; return *this; }
        inline operator Policy_ptr &() { return ptr_; }
        inline Policy_ptr & ptr() { return ptr_; }
        inline Policy_ptr operator->() { return ptr_; }
    private:
        Policy_ptr & ptr_;
    };

    // CORBA::PolicyList
    class OBBEXPDLL PolicyList
    {
    public:
	class OBBEXPDLL _ForSeq_var : public _var
	{
	public:
	    _ForSeq_var() { _release = CORBA_TRUE; _data = 0; }
	    _ForSeq_var(Policy_ptr _ptr);
	    _ForSeq_var(const _ForSeq_var &_ptr);
	    ~_ForSeq_var();
	    _ForSeq_var &operator=(Policy_ptr _ptr);
	    operator Policy_ptr() const {return _data; }
	    inline operator Policy_ptr &() { return _data; }
	    inline Policy_ptr operator->() { return _data; }

	    inline void OBB__release(Boolean _relse) {_release = _relse; }
	    inline Boolean OBB__release() { return _release; }

	private:
	    Policy_ptr _data;
	    Boolean _release;
	};  // class _ForSeq_var

	PolicyList();
	PolicyList(ULong _max);
	PolicyList (
	    ULong _max,
	    ULong _length,
	    Policy_ptr *_value,
	    Boolean _relse = CORBA_FALSE);
	PolicyList(const PolicyList &_ptr);
	~PolicyList();

	PolicyList & operator=(const PolicyList& _ptr);

	inline ULong maximum() const { return _maximum; }

	void length(ULong);
	inline ULong length() const { return _current; }

	_ForSeq_var & operator[](ULong _index);
	const _ForSeq_var & operator[](ULong _index) const;

	static Policy_ptr *allocbuf(ULong _nelems);
	static void freebuf(Policy_ptr *_ptr);

    private:
	static _ForSeq_var *OBB__allocbuf(ULong _nelems);
	static void OBB__freebuf(_ForSeq_var *_ptr);

	_ForSeq_var *_data;
	ULong _maximum;
	ULong _current;
	Boolean _release;
    };  // class PolicyList
    typedef PolicyList * PolicyList_ptr;
    
    // CORBA::PolicyList_var
    class OBBEXPDLL PolicyList_var
    {
    public:
	PolicyList_var() { ptr_ = 0; }
	PolicyList_var(PolicyList * PolicyListPtr) { ptr_ = PolicyListPtr; }
	PolicyList_var(const PolicyList_var & PolicyListRef)
		{ *this = PolicyListRef; }
	~PolicyList_var() { if (ptr_ != 0) delete ptr_; }
	PolicyList_var &operator=(PolicyList *);
	PolicyList_var &operator=(const PolicyList_var &);
	inline PolicyList::_ForSeq_var &operator[](ULong _index)
		{ return ((*ptr_)[_index]); }
	inline PolicyList in() const { return *ptr_; }
	inline PolicyList& inout() { return *ptr_; }
	inline PolicyList*& out() { if (ptr_) delete ptr_; return ptr_; }
	inline PolicyList* _retn()
	    { PolicyList * val = ptr_; ptr_ = 0; return val; }
	inline PolicyList*& ptr() { return ptr_; }
	inline operator PolicyList_ptr&() { return ptr_; }
	inline operator PolicyList&() { return *ptr_; }
	inline PolicyList *operator->() { return ptr_; }
	inline PolicyList *operator->() const { return ptr_; }
    private:
	PolicyList *ptr_;
    };  // class PolicyList_var

    class OBBEXPDLL PolicyList_out
    {
    public:
	PolicyList_out(PolicyList*& p) : ptr_(p) { ptr_ = 0; }
	PolicyList_out(PolicyList_var& p) : ptr_(p.ptr())
	    { delete ptr_; ptr_ = 0; }
	PolicyList_out(const PolicyList_out& p) : ptr_(p.ptr_) {}
	inline PolicyList_out& operator=(const PolicyList_out& p)
	    { ptr_ = p.ptr_; return *this; }
	inline PolicyList_out& operator=(PolicyList* p)
	    { ptr_ = p; return *this; }

	inline operator PolicyList_ptr&() { return ptr_; }
	inline PolicyList_ptr& ptr() { return ptr_; }
	inline PolicyList::_ForSeq_var& operator[](ULong _index)
	    { return (*ptr_)[_index]; }
    private:
	PolicyList*& ptr_;
	// assignment from PolicyList_var not allowed
	void operator=(const PolicyList_var&);
    };

    // Create Policy
    typedef Short PolicyErrorCode;
    typedef Short_out PolicyErrorCode_out;
    static OBBCONSTDATA PolicyErrorCode BAD_POLICY ;
    static OBBCONSTDATA PolicyErrorCode UNSUPPORTED_POLICY ;
    static OBBCONSTDATA PolicyErrorCode BAD_POLICY_TYPE ;
    static OBBCONSTDATA PolicyErrorCode BAD_POLICY_VALUE ;
    static OBBCONSTDATA PolicyErrorCode UNSUPPORTED_POLICY_VALUE ;

    class OBBEXPDLL PolicyError : public UserException
    {
    public:
        static PolicyError * _narrow(Exception_ptr);
        PolicyError ( PolicyErrorCode _reason);
        PolicyError ();
        PolicyError (const PolicyError & PolicyErrorExc) { *this = PolicyErrorExc; }
        ~PolicyError () {}
        PolicyError & operator=(const PolicyError &);
        void _raise();
        static char * _get_repos_id() { return (char *)"IDL:CORBA/PolicyError:1.0"; }

        PolicyErrorCode reason;
    };  // class PolicyError


    typedef	PolicyError *	PolicyError_ptr;
    class OBBEXPDLL PolicyError_var
    {
    public:
        inline PolicyError_var() {_ptr = 0;}
        inline PolicyError_var(PolicyError *_obj) {_ptr = _obj;}
        PolicyError_var(const PolicyError_var &_obj) {_ptr = 0; *this = _obj;}
        ~PolicyError_var() { if (_ptr) delete _ptr; }
        PolicyError_var &operator=(PolicyError *t)
	    { if (_ptr) delete _ptr; _ptr = t; return *this; }
        PolicyError_var &operator=(const PolicyError_var &t)
	    { if (_ptr) { delete _ptr; _ptr = 0; }
	      if (t._ptr) _ptr = new ORBNEWTHROW PolicyError(*t._ptr);
	      return *this; }
	
	inline PolicyError *operator->() {return _ptr;}
        inline const PolicyError *operator->() const {return _ptr;}
        inline const PolicyError & in () const { return *_ptr; }
        inline PolicyError & inout () { return *_ptr; }
        PolicyError & out ()
        {
            PolicyError *tmp = _ptr;
                _ptr=0;
                return *tmp;
            }
            PolicyError & _retn ()
            {
                PolicyError *tmp = _ptr;
                _ptr = 0;
                return *tmp;
            }
            inline PolicyError_ptr & ptr() { return _ptr; }
            inline operator PolicyError&() { return *_ptr; }
            inline operator const PolicyError&() const { return *_ptr; }
            inline operator PolicyError_ptr &() { return _ptr; }
        private:
            PolicyError *_ptr;
    };  // class PolicyError_var

    class OBBEXPDLL PolicyError_out
    {
    public:
        PolicyError_out (PolicyError *& p) : ptr_(p) { ptr_ = 0; }
        PolicyError_out (PolicyError_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        PolicyError_out (const PolicyError_out & a) : ptr_(a.ptr_) {}
        PolicyError_out & operator=(const PolicyError_out & a) {
            ptr_ = a.ptr_; return *this; }
        PolicyError_out & operator=(PolicyError * p) {
            ptr_ = p; return *this; }
        inline operator PolicyError_ptr & () { return ptr_; }
        inline PolicyError_ptr & ptr () { return ptr_; }
        inline PolicyError_ptr operator->() { return ptr_; }
    private:
        PolicyError_ptr & ptr_;
        void operator=(const PolicyError_var &);
    };  // class PolicyError_out

    // CORBA::ServerRequest
    class OBBEXPDLL ServerRequest
    {
    public:
        virtual const char * operation () const = 0;
        virtual void arguments (
	    NVList_ptr & parameters) = 0;
        virtual Context_ptr ctx () = 0;
        virtual void set_result (
	    const Any& value) = 0;
        virtual void set_exception (
	    const Any& value) = 0;


    protected:
	ServerRequest() {}
	virtual ~ServerRequest() {};
    };

    class OBBEXPDLL AnySeq
    {
    public:
        AnySeq();
        AnySeq(ULong _max);
        AnySeq
        (
            ULong _max,
            ULong _length,
            Any *_value,
            Boolean _relse = CORBA_FALSE
        );
        AnySeq(const AnySeq &_ptr);
        ~AnySeq();
        AnySeq &operator=(const AnySeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Any &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Any &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Any *allocbuf(ULong _nelems);
        static void freebuf(Any *_ptr);
        inline Any * OBB__GetData() const { return _data; }
    private:
        Any *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class AnySeq

    class OBBEXPDLL AnySeq_var
    {
    public:
        inline AnySeq_var() {_ptr = 0;}
        inline AnySeq_var(AnySeq *_obj) {_ptr = _obj;}
        AnySeq_var(const AnySeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~AnySeq_var();
        AnySeq_var &operator=(AnySeq *);
        AnySeq_var &operator=(const AnySeq_var &);
        inline Any &operator[](ULong _index) {return (*_ptr)[_index];}
        inline AnySeq *operator->() {return _ptr;}
        inline const AnySeq *operator->() const {return _ptr;}
        inline const AnySeq & in () const { return *_ptr; }
        inline AnySeq & inout () { return *_ptr; }
        AnySeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        AnySeq * _retn ()
        {
            AnySeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline AnySeq_ptr & ptr() { return _ptr; }
        inline operator AnySeq&() { return *_ptr; }
        inline operator const AnySeq&() const { return *_ptr; }
        inline operator AnySeq_ptr &() { return _ptr; }
    private:
        AnySeq *_ptr;
    };  // class AnySeq_var

    class OBBEXPDLL AnySeq_out
    {
    public:
        AnySeq_out (AnySeq *& p) : ptr_(p) { ptr_ = 0; }
        AnySeq_out (AnySeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        AnySeq_out (const AnySeq_out & a) : ptr_(a.ptr_) {}
        AnySeq_out & operator=(const AnySeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        AnySeq_out & operator=(AnySeq * p) {
            ptr_ = p; return *this; }
        inline operator AnySeq_ptr & () { return ptr_; }
        inline AnySeq_ptr & ptr () { return ptr_; }
        inline AnySeq_ptr operator->() { return ptr_; }
        inline Any & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        AnySeq_ptr & ptr_;
        void operator=(const AnySeq_var &);

    };  // class AnySeq_out


    class OBBEXPDLL BooleanSeq
    {
    public:
        BooleanSeq();
        BooleanSeq(ULong _max);
        BooleanSeq
        (
            ULong _max,
            ULong _length,
            Boolean *_value,
            Boolean _relse = CORBA_FALSE
        );
        BooleanSeq(const BooleanSeq &_ptr);
        ~BooleanSeq();
        BooleanSeq &operator=(const BooleanSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Boolean &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Boolean &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Boolean *allocbuf(ULong _nelems);
        static void freebuf(Boolean *_ptr);
        inline Boolean * OBB__GetData() const { return _data; }
    private:
        Boolean *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class BooleanSeq

    class OBBEXPDLL BooleanSeq_var
    {
    public:
        inline BooleanSeq_var() {_ptr = 0;}
        inline BooleanSeq_var(BooleanSeq *_obj) {_ptr = _obj;}
        BooleanSeq_var(const BooleanSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~BooleanSeq_var();
        BooleanSeq_var &operator=(BooleanSeq *);
        BooleanSeq_var &operator=(const BooleanSeq_var &);
        inline Boolean &operator[](ULong _index) {return (*_ptr)[_index];}
        inline BooleanSeq *operator->() {return _ptr;}
        inline const BooleanSeq *operator->() const {return _ptr;}
        inline const BooleanSeq & in () const { return *_ptr; }
        inline BooleanSeq & inout () { return *_ptr; }
        BooleanSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        BooleanSeq * _retn ()
        {
            BooleanSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline BooleanSeq_ptr & ptr() { return _ptr; }
        inline operator BooleanSeq&() { return *_ptr; }
        inline operator const BooleanSeq&() const { return *_ptr; }
        inline operator BooleanSeq_ptr &() { return _ptr; }
    private:
        BooleanSeq *_ptr;
    };  // class BooleanSeq_var

    class OBBEXPDLL BooleanSeq_out
    {
    public:
        BooleanSeq_out (BooleanSeq *& p) : ptr_(p) { ptr_ = 0; }
        BooleanSeq_out (BooleanSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        BooleanSeq_out (const BooleanSeq_out & a) : ptr_(a.ptr_) {}
        BooleanSeq_out & operator=(const BooleanSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        BooleanSeq_out & operator=(BooleanSeq * p) {
            ptr_ = p; return *this; }
        inline operator BooleanSeq_ptr & () { return ptr_; }
        inline BooleanSeq_ptr & ptr () { return ptr_; }
        inline BooleanSeq_ptr operator->() { return ptr_; }
        inline Boolean & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        BooleanSeq_ptr & ptr_;
        void operator=(const BooleanSeq_var &);
    };  // class BooleanSeq_out


    class OBBEXPDLL CharSeq
    {
    public:
        CharSeq();
        CharSeq(ULong _max);
        CharSeq
        (
            ULong _max,
            ULong _length,
            Char *_value,
            Boolean _relse = CORBA_FALSE
        );
        CharSeq(const CharSeq &_ptr);
        ~CharSeq();
        CharSeq &operator=(const CharSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Char &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Char &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Char *allocbuf(ULong _nelems);
        static void freebuf(Char *_ptr);
        inline Char * OBB__GetData() const { return _data; }
    private:
        Char *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class CharSeq

    class OBBEXPDLL CharSeq_var
    {
    public:
        inline CharSeq_var() {_ptr = 0;}
        inline CharSeq_var(CharSeq *_obj) {_ptr = _obj;}
        CharSeq_var(const CharSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~CharSeq_var();
        CharSeq_var &operator=(CharSeq *);
        CharSeq_var &operator=(const CharSeq_var &);
        inline Char &operator[](ULong _index) {return (*_ptr)[_index];}
        inline CharSeq *operator->() {return _ptr;}
        inline const CharSeq *operator->() const {return _ptr;}
        inline const CharSeq & in () const { return *_ptr; }
        inline CharSeq & inout () { return *_ptr; }
        CharSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        CharSeq * _retn ()
        {
            CharSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline CharSeq_ptr & ptr() { return _ptr; }
        inline operator CharSeq&() { return *_ptr; }
        inline operator const CharSeq&() const { return *_ptr; }
        inline operator CharSeq_ptr &() { return _ptr; }
    private:
        CharSeq *_ptr;
    };  // class CharSeq_var

    class OBBEXPDLL CharSeq_out
    {
    public:
        CharSeq_out (CharSeq *& p) : ptr_(p) { ptr_ = 0; }
        CharSeq_out (CharSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        CharSeq_out (const CharSeq_out & a) : ptr_(a.ptr_) {}
        CharSeq_out & operator=(const CharSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        CharSeq_out & operator=(CharSeq * p) {
            ptr_ = p; return *this; }
        inline operator CharSeq_ptr & () { return ptr_; }
        inline CharSeq_ptr & ptr () { return ptr_; }
        inline CharSeq_ptr operator->() { return ptr_; }
        inline Char & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        CharSeq_ptr & ptr_;
        void operator=(const CharSeq_var &);
    };  // class CharSeq_out

#if !defined(M3_NO_UNICODE_SUPPORT)

    class OBBEXPDLL WCharSeq
    {
    public:
        WCharSeq();
        WCharSeq(ULong _max);
        WCharSeq
        (
            ULong _max,
            ULong _length,
            WChar *_value,
            Boolean _relse = CORBA_FALSE
        );
        WCharSeq(const WCharSeq &_ptr);
        ~WCharSeq();
        WCharSeq &operator=(const WCharSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline WChar &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const WChar &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static WChar *allocbuf(ULong _nelems);
        static void freebuf(WChar *_ptr);
        inline WChar * OBB__GetData() const { return _data; }
    private:
        WChar *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class WCharSeq

    class OBBEXPDLL WCharSeq_var
    {
    public:
        inline WCharSeq_var() {_ptr = 0;}
        inline WCharSeq_var(WCharSeq *_obj) {_ptr = _obj;}
        WCharSeq_var(const WCharSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~WCharSeq_var();
        WCharSeq_var &operator=(WCharSeq *);
        WCharSeq_var &operator=(const WCharSeq_var &);
        inline WChar &operator[](ULong _index) {return (*_ptr)[_index];}
        inline WCharSeq *operator->() {return _ptr;}
        inline const WCharSeq *operator->() const {return _ptr;}
        inline const WCharSeq & in () const { return *_ptr; }
        inline WCharSeq & inout () { return *_ptr; }
        WCharSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        WCharSeq * _retn ()
        {
            WCharSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline WCharSeq_ptr & ptr() { return _ptr; }
        inline operator WCharSeq&() { return *_ptr; }
        inline operator const WCharSeq&() const { return *_ptr; }
        inline operator WCharSeq_ptr &() { return _ptr; }
    private:
        WCharSeq *_ptr;
    };  // class WCharSeq_var

    class OBBEXPDLL WCharSeq_out
    {
    public:
        WCharSeq_out (WCharSeq *& p) : ptr_(p) { ptr_ = 0; }
        WCharSeq_out (WCharSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        WCharSeq_out (const WCharSeq_out & a) : ptr_(a.ptr_) {}
        WCharSeq_out & operator=(const WCharSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        WCharSeq_out & operator=(WCharSeq * p) {
            ptr_ = p; return *this; }
        inline operator WCharSeq_ptr & () { return ptr_; }
        inline WCharSeq_ptr & ptr () { return ptr_; }
        inline WCharSeq_ptr operator->() { return ptr_; }
        inline WChar & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        WCharSeq_ptr & ptr_;
        void operator=(const WCharSeq_var &);
    };  // class WCharSeq_out

#endif	// !defined(M3_NO_UNICODE_SUPPORT)

    class OBBEXPDLL OctetSeq
    {
    public:
        OctetSeq();
        OctetSeq(ULong _max);
        OctetSeq
        (
            ULong _max,
            ULong _length,
            Octet *_value,
            Boolean _relse = CORBA_FALSE
        );
        OctetSeq(const OctetSeq &_ptr);
        ~OctetSeq();
        OctetSeq &operator=(const OctetSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Octet &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Octet &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Octet *allocbuf(ULong _nelems);
        static void freebuf(Octet *_ptr);
        inline Octet * OBB__GetData() const { return _data; }
    private:
        Octet *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class OctetSeq

    class OBBEXPDLL OctetSeq_var
    {
    public:
        inline OctetSeq_var() {_ptr = 0;}
        inline OctetSeq_var(OctetSeq *_obj) {_ptr = _obj;}
        OctetSeq_var(const OctetSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~OctetSeq_var();
        OctetSeq_var &operator=(OctetSeq *);
        OctetSeq_var &operator=(const OctetSeq_var &);
        inline Octet &operator[](ULong _index) {return (*_ptr)[_index];}
        inline OctetSeq *operator->() {return _ptr;}
        inline const OctetSeq *operator->() const {return _ptr;}
        inline const OctetSeq & in () const { return *_ptr; }
        inline OctetSeq & inout () { return *_ptr; }
        OctetSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        OctetSeq * _retn ()
        {
            OctetSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline OctetSeq_ptr & ptr() { return _ptr; }
        inline operator OctetSeq&() { return *_ptr; }
        inline operator const OctetSeq&() const { return *_ptr; }
        inline operator OctetSeq_ptr &() { return _ptr; }
    private:
        OctetSeq *_ptr;
    };  // class OctetSeq_var

    class OBBEXPDLL OctetSeq_out
    {
    public:
        OctetSeq_out (OctetSeq *& p) : ptr_(p) { ptr_ = 0; }
        OctetSeq_out (OctetSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        OctetSeq_out (const OctetSeq_out & a) : ptr_(a.ptr_) {}
        OctetSeq_out & operator=(const OctetSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        OctetSeq_out & operator=(OctetSeq * p) {
            ptr_ = p; return *this; }
        inline operator OctetSeq_ptr & () { return ptr_; }
        inline OctetSeq_ptr & ptr () { return ptr_; }
        inline OctetSeq_ptr operator->() { return ptr_; }
        inline Octet & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        OctetSeq_ptr & ptr_;
        void operator=(const OctetSeq_var &);
    };  // class OctetSeq_out

    class OBBEXPDLL ShortSeq
    {
    public:
        ShortSeq();
        ShortSeq(ULong _max);
        ShortSeq
        (
            ULong _max,
            ULong _length,
            Short *_value,
            Boolean _relse = CORBA_FALSE
        );
        ShortSeq(const ShortSeq &_ptr);
        ~ShortSeq();
        ShortSeq &operator=(const ShortSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Short &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Short &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Short *allocbuf(ULong _nelems);
        static void freebuf(Short *_ptr);
        inline Short * OBB__GetData() const { return _data; }
    private:
        Short *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class ShortSeq

    class OBBEXPDLL ShortSeq_var
    {
    public:
        inline ShortSeq_var() {_ptr = 0;}
        inline ShortSeq_var(ShortSeq *_obj) {_ptr = _obj;}
        ShortSeq_var(const ShortSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~ShortSeq_var();
        ShortSeq_var &operator=(ShortSeq *);
        ShortSeq_var &operator=(const ShortSeq_var &);
        inline Short &operator[](ULong _index) {return (*_ptr)[_index];}
        inline ShortSeq *operator->() {return _ptr;}
        inline const ShortSeq *operator->() const {return _ptr;}
        inline const ShortSeq & in () const { return *_ptr; }
        inline ShortSeq & inout () { return *_ptr; }
        ShortSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        ShortSeq * _retn ()
        {
            ShortSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline ShortSeq_ptr & ptr() { return _ptr; }
        inline operator ShortSeq&() { return *_ptr; }
        inline operator const ShortSeq&() const { return *_ptr; }
        inline operator ShortSeq_ptr &() { return _ptr; }
    private:
        ShortSeq *_ptr;
    };  // class ShortSeq_var

    class OBBEXPDLL ShortSeq_out
    {
    public:
        ShortSeq_out (ShortSeq *& p) : ptr_(p) { ptr_ = 0; }
        ShortSeq_out (ShortSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        ShortSeq_out (const ShortSeq_out & a) : ptr_(a.ptr_) {}
        ShortSeq_out & operator=(const ShortSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        ShortSeq_out & operator=(ShortSeq * p) {
            ptr_ = p; return *this; }
        inline operator ShortSeq_ptr & () { return ptr_; }
        inline ShortSeq_ptr & ptr () { return ptr_; }
        inline ShortSeq_ptr operator->() { return ptr_; }
        inline Short & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        ShortSeq_ptr & ptr_;
        void operator=(const ShortSeq_var &);
    };  // class ShortSeq_out

    class OBBEXPDLL UShortSeq
    {
    public:
        UShortSeq();
        UShortSeq(ULong _max);
        UShortSeq
        (
            ULong _max,
            ULong _length,
            UShort *_value,
            Boolean _relse = CORBA_FALSE
        );
        UShortSeq(const UShortSeq &_ptr);
        ~UShortSeq();
        UShortSeq &operator=(const UShortSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline UShort &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const UShort &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static UShort *allocbuf(ULong _nelems);
        static void freebuf(UShort *_ptr);
        inline UShort * OBB__GetData() const { return _data; }
    private:
        UShort *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class UShortSeq

    class OBBEXPDLL UShortSeq_var
    {
    public:
        inline UShortSeq_var() {_ptr = 0;}
        inline UShortSeq_var(UShortSeq *_obj) {_ptr = _obj;}
        UShortSeq_var(const UShortSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~UShortSeq_var();
        UShortSeq_var &operator=(UShortSeq *);
        UShortSeq_var &operator=(const UShortSeq_var &);
        inline UShort &operator[](ULong _index) {return (*_ptr)[_index];}
        inline UShortSeq *operator->() {return _ptr;}
        inline const UShortSeq *operator->() const {return _ptr;}
        inline const UShortSeq & in () const { return *_ptr; }
        inline UShortSeq & inout () { return *_ptr; }
        UShortSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        UShortSeq * _retn ()
        {
            UShortSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline UShortSeq_ptr & ptr() { return _ptr; }
        inline operator UShortSeq&() { return *_ptr; }
        inline operator const UShortSeq&() const { return *_ptr; }
        inline operator UShortSeq_ptr &() { return _ptr; }
    private:
        UShortSeq *_ptr;
    };  // class UShortSeq_var

    class OBBEXPDLL UShortSeq_out
    {
    public:
        UShortSeq_out (UShortSeq *& p) : ptr_(p) { ptr_ = 0; }
        UShortSeq_out (UShortSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        UShortSeq_out (const UShortSeq_out & a) : ptr_(a.ptr_) {}
        UShortSeq_out & operator=(const UShortSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        UShortSeq_out & operator=(UShortSeq * p) {
            ptr_ = p; return *this; }
        inline operator UShortSeq_ptr & () { return ptr_; }
        inline UShortSeq_ptr & ptr () { return ptr_; }
        inline UShortSeq_ptr operator->() { return ptr_; }
        inline UShort & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        UShortSeq_ptr & ptr_;
        void operator=(const UShortSeq_var &);
    };  // class UShortSeq_out

    class OBBEXPDLL LongSeq
    {
    public:
        LongSeq();
        LongSeq(ULong _max);
        LongSeq
        (
            ULong _max,
            ULong _length,
            Long *_value,
            Boolean _relse = CORBA_FALSE
        );
        LongSeq(const LongSeq &_ptr);
        ~LongSeq();
        LongSeq &operator=(const LongSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Long &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Long &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Long *allocbuf(ULong _nelems);
        static void freebuf(Long *_ptr);
        inline Long * OBB__GetData() const { return _data; }
    private:
        Long *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class LongSeq

    class OBBEXPDLL LongSeq_var
    {
    public:
        inline LongSeq_var() {_ptr = 0;}
        inline LongSeq_var(LongSeq *_obj) {_ptr = _obj;}
        LongSeq_var(const LongSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~LongSeq_var();
        LongSeq_var &operator=(LongSeq *);
        LongSeq_var &operator=(const LongSeq_var &);
        inline Long &operator[](ULong _index) {return (*_ptr)[_index];}
        inline LongSeq *operator->() {return _ptr;}
        inline const LongSeq *operator->() const {return _ptr;}
        inline const LongSeq & in () const { return *_ptr; }
        inline LongSeq & inout () { return *_ptr; }
        LongSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        LongSeq * _retn ()
        {
            LongSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline LongSeq_ptr & ptr() { return _ptr; }
        inline operator LongSeq&() { return *_ptr; }
        inline operator const LongSeq&() const { return *_ptr; }
        inline operator LongSeq_ptr &() { return _ptr; }
    private:
        LongSeq *_ptr;
    };  // class LongSeq_var

    class OBBEXPDLL LongSeq_out
    {
    public:
        LongSeq_out (LongSeq *& p) : ptr_(p) { ptr_ = 0; }
        LongSeq_out (LongSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        LongSeq_out (const LongSeq_out & a) : ptr_(a.ptr_) {}
        LongSeq_out & operator=(const LongSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        LongSeq_out & operator=(LongSeq * p) {
            ptr_ = p; return *this; }
        inline operator LongSeq_ptr & () { return ptr_; }
        inline LongSeq_ptr & ptr () { return ptr_; }
        inline LongSeq_ptr operator->() { return ptr_; }
        inline Long & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        LongSeq_ptr & ptr_;
        void operator=(const LongSeq_var &);
    };  // class LongSeq_out

    class OBBEXPDLL ULongSeq
    {
    public:
        ULongSeq();
        ULongSeq(ULong _max);
        ULongSeq
        (
            ULong _max,
            ULong _length,
            ULong *_value,
            Boolean _relse = CORBA_FALSE
        );
        ULongSeq(const ULongSeq &_ptr);
        ~ULongSeq();
        ULongSeq &operator=(const ULongSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline ULong &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const ULong &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static ULong *allocbuf(ULong _nelems);
        static void freebuf(ULong *_ptr);
        inline ULong * OBB__GetData() const { return _data; }
    private:
        ULong *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class ULongSeq

    class OBBEXPDLL ULongSeq_var
    {
    public:
        inline ULongSeq_var() {_ptr = 0;}
        inline ULongSeq_var(ULongSeq *_obj) {_ptr = _obj;}
        ULongSeq_var(const ULongSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~ULongSeq_var();
        ULongSeq_var &operator=(ULongSeq *);
        ULongSeq_var &operator=(const ULongSeq_var &);
        inline ULong &operator[](ULong _index) {return (*_ptr)[_index];}
        inline ULongSeq *operator->() {return _ptr;}
        inline const ULongSeq *operator->() const {return _ptr;}
        inline const ULongSeq & in () const { return *_ptr; }
        inline ULongSeq & inout () { return *_ptr; }
        ULongSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        ULongSeq * _retn ()
        {
            ULongSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline ULongSeq_ptr & ptr() { return _ptr; }
        inline operator ULongSeq&() { return *_ptr; }
        inline operator const ULongSeq&() const { return *_ptr; }
        inline operator ULongSeq_ptr &() { return _ptr; }
    private:
        ULongSeq *_ptr;
    };  // class ULongSeq_var

    class OBBEXPDLL ULongSeq_out
    {
    public:
        ULongSeq_out (ULongSeq *& p) : ptr_(p) { ptr_ = 0; }
        ULongSeq_out (ULongSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        ULongSeq_out (const ULongSeq_out & a) : ptr_(a.ptr_) {}
        ULongSeq_out & operator=(const ULongSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        ULongSeq_out & operator=(ULongSeq * p) {
            ptr_ = p; return *this; }
        inline operator ULongSeq_ptr & () { return ptr_; }
        inline ULongSeq_ptr & ptr () { return ptr_; }
        inline ULongSeq_ptr operator->() { return ptr_; }
        inline ULong & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        ULongSeq_ptr & ptr_;
        void operator=(const ULongSeq_var &);
    };  // class ULongSeq_out

#if !defined(M3_NO_LONG_LONG_SUPPORT)
    class OBBEXPDLL LongLongSeq
    {
    public:
        LongLongSeq();
        LongLongSeq(ULong _max);
        LongLongSeq
        (
            ULong _max,
            ULong _length,
            LongLong *_value,
            Boolean _relse = CORBA_FALSE
        );
        LongLongSeq(const LongLongSeq &_ptr);
        ~LongLongSeq();
        LongLongSeq &operator=(const LongLongSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline LongLong &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const LongLong &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static LongLong *allocbuf(ULong _nelems);
        static void freebuf(LongLong *_ptr);
        inline LongLong * OBB__GetData() const { return _data; }
    private:
        LongLong *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class LongLongSeq

    class OBBEXPDLL LongLongSeq_var
    {
    public:
        inline LongLongSeq_var() {_ptr = 0;}
        inline LongLongSeq_var(LongLongSeq *_obj) {_ptr = _obj;}
        LongLongSeq_var(const LongLongSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~LongLongSeq_var();
        LongLongSeq_var &operator=(LongLongSeq *);
        LongLongSeq_var &operator=(const LongLongSeq_var &);
        inline LongLong &operator[](ULong _index) {return (*_ptr)[_index];}
        inline LongLongSeq *operator->() {return _ptr;}
        inline const LongLongSeq *operator->() const {return _ptr;}
        inline const LongLongSeq & in () const { return *_ptr; }
        inline LongLongSeq & inout () { return *_ptr; }
        LongLongSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        LongLongSeq * _retn ()
        {
            LongLongSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline LongLongSeq_ptr & ptr() { return _ptr; }
        inline operator LongLongSeq&() { return *_ptr; }
        inline operator const LongLongSeq&() const { return *_ptr; }
        inline operator LongLongSeq_ptr &() { return _ptr; }
    private:
        LongLongSeq *_ptr;
    };  // class LongLongSeq_var

    class OBBEXPDLL LongLongSeq_out
    {
    public:
        LongLongSeq_out (LongLongSeq *& p) : ptr_(p) { ptr_ = 0; }
        LongLongSeq_out (LongLongSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        LongLongSeq_out (const LongLongSeq_out & a) : ptr_(a.ptr_) {}
        LongLongSeq_out & operator=(const LongLongSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        LongLongSeq_out & operator=(LongLongSeq * p) {
            ptr_ = p; return *this; }
        inline operator LongLongSeq_ptr & () { return ptr_; }
        inline LongLongSeq_ptr & ptr () { return ptr_; }
        inline LongLongSeq_ptr operator->() { return ptr_; }
        inline LongLong & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        LongLongSeq_ptr & ptr_;
        void operator=(const LongLongSeq_var &);
    };  // class LongLongSeq_out

    class OBBEXPDLL ULongLongSeq
    {
    public:
        ULongLongSeq();
        ULongLongSeq(ULong _max);
        ULongLongSeq
        (
            ULong _max,
            ULong _length,
            ULongLong *_value,
            Boolean _relse = CORBA_FALSE
        );
        ULongLongSeq(const ULongLongSeq &_ptr);
        ~ULongLongSeq();
        ULongLongSeq &operator=(const ULongLongSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline ULongLong &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const ULongLong &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static ULongLong *allocbuf(ULong _nelems);
        static void freebuf(ULongLong *_ptr);
        inline ULongLong * OBB__GetData() const { return _data; }
    private:
        ULongLong *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class ULongLongSeq

    class OBBEXPDLL ULongLongSeq_var
    {
    public:
        inline ULongLongSeq_var() {_ptr = 0;}
        inline ULongLongSeq_var(ULongLongSeq *_obj) {_ptr = _obj;}
        ULongLongSeq_var(const ULongLongSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~ULongLongSeq_var();
        ULongLongSeq_var &operator=(ULongLongSeq *);
        ULongLongSeq_var &operator=(const ULongLongSeq_var &);
        inline ULongLong &operator[](ULong _index) {return (*_ptr)[_index];}
        inline ULongLongSeq *operator->() {return _ptr;}
        inline const ULongLongSeq *operator->() const {return _ptr;}
        inline const ULongLongSeq & in () const { return *_ptr; }
        inline ULongLongSeq & inout () { return *_ptr; }
        ULongLongSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        ULongLongSeq * _retn ()
        {
            ULongLongSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline ULongLongSeq_ptr & ptr() { return _ptr; }
        inline operator ULongLongSeq&() { return *_ptr; }
        inline operator const ULongLongSeq&() const { return *_ptr; }
        inline operator ULongLongSeq_ptr &() { return _ptr; }
    private:
        ULongLongSeq *_ptr;
    };  // class ULongLongSeq_var

    class OBBEXPDLL ULongLongSeq_out
    {
    public:
        ULongLongSeq_out (ULongLongSeq *& p) : ptr_(p) { ptr_ = 0; }
        ULongLongSeq_out (ULongLongSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        ULongLongSeq_out (const ULongLongSeq_out & a) : ptr_(a.ptr_) {}
        ULongLongSeq_out & operator=(const ULongLongSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        ULongLongSeq_out & operator=(ULongLongSeq * p) {
            ptr_ = p; return *this; }
        inline operator ULongLongSeq_ptr & () { return ptr_; }
        inline ULongLongSeq_ptr & ptr () { return ptr_; }
        inline ULongLongSeq_ptr operator->() { return ptr_; }
        inline ULongLong & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        ULongLongSeq_ptr & ptr_;
        void operator=(const ULongLongSeq_var &);
    };  // class ULongLongSeq_out

#endif // !defined(M3_NO_LONG_LONG_SUPPORT)

    class OBBEXPDLL FloatSeq
    {
    public:
        FloatSeq();
        FloatSeq(ULong _max);
        FloatSeq
        (
            ULong _max,
            ULong _length,
            Float *_value,
            Boolean _relse = CORBA_FALSE
        );
        FloatSeq(const FloatSeq &_ptr);
        ~FloatSeq();
        FloatSeq &operator=(const FloatSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Float &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Float &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Float *allocbuf(ULong _nelems);
        static void freebuf(Float *_ptr);
        inline Float * OBB__GetData() const { return _data; }
    private:
        Float *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class FloatSeq

    class OBBEXPDLL FloatSeq_var
    {
    public:
        inline FloatSeq_var() {_ptr = 0;}
        inline FloatSeq_var(FloatSeq *_obj) {_ptr = _obj;}
        FloatSeq_var(const FloatSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~FloatSeq_var();
        FloatSeq_var &operator=(FloatSeq *);
        FloatSeq_var &operator=(const FloatSeq_var &);
        inline Float &operator[](ULong _index) {return (*_ptr)[_index];}
        inline FloatSeq *operator->() {return _ptr;}
        inline const FloatSeq *operator->() const {return _ptr;}
        inline const FloatSeq & in () const { return *_ptr; }
        inline FloatSeq & inout () { return *_ptr; }
        FloatSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        FloatSeq * _retn ()
        {
            FloatSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline FloatSeq_ptr & ptr() { return _ptr; }
        inline operator FloatSeq&() { return *_ptr; }
        inline operator const FloatSeq&() const { return *_ptr; }
        inline operator FloatSeq_ptr &() { return _ptr; }
    private:
        FloatSeq *_ptr;
    };  // class FloatSeq_var

    class OBBEXPDLL FloatSeq_out
    {
    public:
        FloatSeq_out (FloatSeq *& p) : ptr_(p) { ptr_ = 0; }
        FloatSeq_out (FloatSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        FloatSeq_out (const FloatSeq_out & a) : ptr_(a.ptr_) {}
        FloatSeq_out & operator=(const FloatSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        FloatSeq_out & operator=(FloatSeq * p) {
            ptr_ = p; return *this; }
        inline operator FloatSeq_ptr & () { return ptr_; }
        inline FloatSeq_ptr & ptr () { return ptr_; }
        inline FloatSeq_ptr operator->() { return ptr_; }
        inline Float & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        FloatSeq_ptr & ptr_;
        void operator=(const FloatSeq_var &);
    };  // class FloatSeq_out

    class OBBEXPDLL DoubleSeq
    {
    public:
        DoubleSeq();
        DoubleSeq(ULong _max);
        DoubleSeq
        (
            ULong _max,
            ULong _length,
            Double *_value,
            Boolean _relse = CORBA_FALSE
        );
        DoubleSeq(const DoubleSeq &_ptr);
        ~DoubleSeq();
        DoubleSeq &operator=(const DoubleSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline Double &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const Double &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static Double *allocbuf(ULong _nelems);
        static void freebuf(Double *_ptr);
        inline Double * OBB__GetData() const { return _data; }
    private:
        Double *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class DoubleSeq

    class OBBEXPDLL DoubleSeq_var
    {
    public:
        inline DoubleSeq_var() {_ptr = 0;}
        inline DoubleSeq_var(DoubleSeq *_obj) {_ptr = _obj;}
        DoubleSeq_var(const DoubleSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~DoubleSeq_var();
        DoubleSeq_var &operator=(DoubleSeq *);
        DoubleSeq_var &operator=(const DoubleSeq_var &);
        inline Double &operator[](ULong _index) {return (*_ptr)[_index];}
        inline DoubleSeq *operator->() {return _ptr;}
        inline const DoubleSeq *operator->() const {return _ptr;}
        inline const DoubleSeq & in () const { return *_ptr; }
        inline DoubleSeq & inout () { return *_ptr; }
        DoubleSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        DoubleSeq * _retn ()
        {
            DoubleSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline DoubleSeq_ptr & ptr() { return _ptr; }
        inline operator DoubleSeq&() { return *_ptr; }
        inline operator const DoubleSeq&() const { return *_ptr; }
        inline operator DoubleSeq_ptr &() { return _ptr; }
    private:
        DoubleSeq *_ptr;
    };  // class DoubleSeq_var

   class OBBEXPDLL DoubleSeq_out
   {
    public:
        DoubleSeq_out (DoubleSeq *& p) : ptr_(p) { ptr_ = 0; }
        DoubleSeq_out (DoubleSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        DoubleSeq_out (const DoubleSeq_out & a) : ptr_(a.ptr_) {}
        DoubleSeq_out & operator=(const DoubleSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        DoubleSeq_out & operator=(DoubleSeq * p) {
            ptr_ = p; return *this; }
        inline operator DoubleSeq_ptr & () { return ptr_; }
        inline DoubleSeq_ptr & ptr () { return ptr_; }
        inline DoubleSeq_ptr operator->() { return ptr_; }
        inline Double & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        DoubleSeq_ptr & ptr_;
        void operator=(const DoubleSeq_var &);
    };  // class DoubleSeq_out

#if defined(M3_LONG_DOUBLE_SUPPORT)

    class OBBEXPDLL LongDoubleSeq
    {
    public:
        LongDoubleSeq();
        LongDoubleSeq(ULong _max);
        LongDoubleSeq
        (
            ULong _max,
            ULong _length,
            LongDouble *_value,
            Boolean _relse = CORBA_FALSE
        );
        LongDoubleSeq(const LongDoubleSeq &_ptr);
        ~LongDoubleSeq();
        LongDoubleSeq &operator=(const LongDoubleSeq& _ptr);
        inline ULong maximum() const {return _maximum;}
        void length(ULong);
        inline ULong length() const {return _current;}
        inline LongDouble &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        inline const LongDouble &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
        static LongDouble *allocbuf(ULong _nelems);
        static void freebuf(LongDouble *_ptr);
        inline LongDouble * OBB__GetData() const { return _data; }
    private:
        LongDouble *_data;
        ULong _maximum;
        ULong _current;
        Boolean _release;
    };  // class LongDoubleSeq

    class OBBEXPDLL LongDoubleSeq_var
    {
    public:
        inline LongDoubleSeq_var() {_ptr = 0;}
        inline LongDoubleSeq_var(LongDoubleSeq *_obj) {_ptr = _obj;}
        LongDoubleSeq_var(const LongDoubleSeq_var &_obj) {_ptr = 0; *this = _obj;}
        ~LongDoubleSeq_var();
        LongDoubleSeq_var &operator=(LongDoubleSeq *);
        LongDoubleSeq_var &operator=(const LongDoubleSeq_var &);
        inline LongDouble &operator[](ULong _index) {return (*_ptr)[_index];}
        inline LongDoubleSeq *operator->() {return _ptr;}
        inline const LongDoubleSeq *operator->() const {return _ptr;}
        inline const LongDoubleSeq & in () const { return *_ptr; }
        inline LongDoubleSeq & inout () { return *_ptr; }
        LongDoubleSeq *& out ()
        {
            delete _ptr;
            _ptr=0;
            return _ptr;
        }
        LongDoubleSeq * _retn ()
        {
            LongDoubleSeq *tmp = _ptr;
            _ptr = 0;
            return tmp;
        }
        inline LongDoubleSeq_ptr & ptr() { return _ptr; }
        inline operator LongDoubleSeq&() { return *_ptr; }
        inline operator const LongDoubleSeq&() const { return *_ptr; }
        inline operator LongDoubleSeq_ptr &() { return _ptr; }
    private:
        LongDoubleSeq *_ptr;
    };  // class LongDoubleSeq_var

   class OBBEXPDLL LongDoubleSeq_out
   {
    public:
        LongDoubleSeq_out (LongDoubleSeq *& p) : ptr_(p) { ptr_ = 0; }
        LongDoubleSeq_out (LongDoubleSeq_var &p) : ptr_(p.ptr()) {
            delete ptr_; ptr_ = 0; }
        LongDoubleSeq_out (const LongDoubleSeq_out & a) : ptr_(a.ptr_) {}
        LongDoubleSeq_out & operator=(const LongDoubleSeq_out & a) {
            ptr_ = a.ptr_; return *this; }
        LongDoubleSeq_out & operator=(LongDoubleSeq * p) {
            ptr_ = p; return *this; }
        inline operator LongDoubleSeq_ptr & () { return ptr_; }
        inline LongDoubleSeq_ptr & ptr () { return ptr_; }
        inline LongDoubleSeq_ptr operator->() { return ptr_; }
        inline LongDouble & operator[](ULong _index) {return (*ptr_)[_index]; }
    private:
        LongDoubleSeq_ptr & ptr_;
        void operator=(const LongDoubleSeq_var &);
    };  // class LongDoubleSeq_out

#endif	// defined(M3_LONG_DOUBLE_SUPPORT)


    class OBBEXPDLL ValueFactoryBase
    {
     public:
	virtual void _add_ref();
	virtual void _remove_ref();
	static ValueFactory _downcast(ValueFactory vf);
        static ValueBase* _OBB__create_value(ValueFactory vf);

     protected:
	ValueFactoryBase();
#if defined(_AIX)
	virtual ~ValueFactoryBase() {}
#else
	virtual ~ValueFactoryBase() = 0;
#endif

     private:
	virtual ValueBase* create_for_unmarshal() = 0;
	ULong _ref_count;
    };	// class ValueFactoryBase


    class OBBEXPDLL ValueFactoryBase_var : public _var
    {
    public:
	ValueFactoryBase_var() { ptr_ = NULL; }
	ValueFactoryBase_var(ValueFactory VFBase) { ptr_ = VFBase; }
	ValueFactoryBase_var(const ValueFactoryBase_var &VFBasev)
	{ if (ptr_) ptr_->_remove_ref();
	  *this = VFBasev; }
	virtual ~ValueFactoryBase_var() { if (ptr_) ptr_->_remove_ref(); }
	virtual ValueFactoryBase_var & operator=(ValueFactory VFBase)
	{ if (ptr_) ptr_->_remove_ref();
	    ptr_ = VFBase;
	    return *this; }
	virtual ValueFactoryBase_var & operator=(const ValueFactoryBase_var &VFBasev)
	    { if (this != &VFBasev)
		{ ptr_->_remove_ref();
		  *this = VFBasev; }
	      return *this; }
	virtual inline ValueFactory in() const { return ptr_; }
	virtual inline ValueFactory& inout() { return ptr_; }
	virtual inline ValueFactory& out()
	    { ptr_->_remove_ref(); ptr_ = NULL; return ptr_; }
	virtual inline ValueFactory _retn()
	    { ValueFactory val = ptr_; ptr_ = NULL; return val; }
	virtual inline ValueFactory& ptr() { return ptr_; }
	virtual inline operator ValueFactory&() { return ptr_; }
	virtual inline operator const ValueFactory& () const { return ptr_; }
	virtual inline ValueFactory operator->() const { return ptr_; }
    private:
	ValueFactory ptr_;
	// hidden assignment operator to cause compile time error...
	ValueFactoryBase_var & operator=(const _var &Varv);
    };

    
    class OBBEXPDLL ValueBase {
    public:
	virtual ValueBase_ptr _add_ref() = 0;
	virtual void _remove_ref() = 0;
	virtual ValueBase_ptr _copy_value() = 0;
	virtual ULong _refcount_value() = 0;
	static ValueBase_ptr _downcast(ValueBase_ptr);
        virtual RepositoryId _OBB__get_id() = 0;
        virtual ULong _OBB__get_id_list(RepositoryId*&) = 0;
    protected:
	ValueBase();
	ValueBase(const ValueBase&);
	virtual ~ValueBase();
    private:
	void operator=(const ValueBase&);
    };

    static void add_ref(ValueBase_ptr vb) { if (vb != 0) vb->_add_ref(); }
    static void remove_ref(ValueBase_ptr vb) { if (vb != 0) vb->_remove_ref(); }

    class OBBEXPDLL ValueBase_var : public _var
    {
    public:
	ValueBase_var() { ptr_ = NULL; }
	ValueBase_var(ValueBase_ptr VBase) { ptr_ = VBase; }
	ValueBase_var(const ValueBase_var &VBasev)
	    { ptr_ = VBasev->_copy_value(); }
	virtual ~ValueBase_var() { if (ptr_) ptr_->_remove_ref(); }
	virtual ValueBase_var & operator=(ValueBase_ptr VBase)
	{ if (ptr_) ptr_->_remove_ref();
	    ptr_ = VBase;
	    return *this; }
	virtual ValueBase_var & operator=(const ValueBase_var &VBasev)
	    { if (this != &VBasev) { ptr_->_remove_ref();
	      ptr_ = VBasev->_copy_value(); }
	      return *this; }
	virtual inline ValueBase_ptr in() const { return ptr_; }
	virtual inline ValueBase_ptr& inout() { return ptr_; }
	virtual inline ValueBase_ptr& out()
	    { ptr_->_remove_ref(); ptr_ = NULL; return ptr_; }
	virtual inline ValueBase_ptr _retn()
	    { ValueBase_ptr val = ptr_; ptr_ = NULL; return val; }
	virtual inline ValueBase_ptr& ptr() { return ptr_; }
	virtual inline operator ValueBase_ptr&() { return ptr_; }
	virtual inline operator const ValueBase_ptr& () const { return ptr_; }
	virtual inline ValueBase_ptr operator->() const { return ptr_; }
    private:
	ValueBase_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	ValueBase_var & operator=(const _var &Varv);
    };


    class OBBEXPDLL DefaultValueRefCountBase : public virtual ValueBase
    {
     public:
	virtual ValueBase* _add_ref();
	virtual void _remove_ref();
	virtual ULong _refcount_value() { return m_refcount; }
     protected:
	DefaultValueRefCountBase();
	DefaultValueRefCountBase(const DefaultValueRefCountBase&) { }
#if defined(_AIX)
	virtual ~DefaultValueRefCountBase() {}
#else
	virtual ~DefaultValueRefCountBase() = 0;
#endif
	unsigned long m_refcount;
     private:
	 void operator=(const DefaultValueRefCountBase&);
    };


    class OBBEXPDLL AbstractBase {
    friend class CORBA;
    public:
	static AbstractBase_ptr _duplicate(AbstractBase_ptr);
	static AbstractBase_ptr _narrow(AbstractBase_ptr);
	static AbstractBase_ptr _nil();
    protected:
	AbstractBase();
	AbstractBase(const AbstractBase& val);
	virtual ~AbstractBase() { }
	unsigned long m_refcount;
    };

    class OBBEXPDLL AbstractBase_var : public _var
    {
    public:
	AbstractBase_var() { ptr_ = AbstractBase::_nil(); }
	AbstractBase_var(AbstractBase_ptr LBase) { ptr_ = LBase; }
	AbstractBase_var(const AbstractBase_var &LBasev)
		{ ptr_ = AbstractBase::_duplicate(AbstractBase_ptr(LBasev)); }
	~AbstractBase_var() { release(ptr_); }
	AbstractBase_var & operator=(AbstractBase_ptr LBase);
	AbstractBase_var & operator=(const AbstractBase_var &LBasev)
	    { if (this != &LBasev) { release(ptr_);
	      ptr_ = AbstractBase::_duplicate(AbstractBase_ptr(LBasev)); }
	      return *this; }
	inline AbstractBase_ptr in() const { return ptr_; }
	inline AbstractBase_ptr& inout() { return ptr_; }
	inline AbstractBase_ptr& out()
	    { release(ptr_); ptr_ = AbstractBase::_nil(); return ptr_; }
	inline AbstractBase_ptr _retn()
	    { AbstractBase_ptr val = ptr_; ptr_ = AbstractBase::_nil(); return val; }
	inline AbstractBase_ptr& ptr() { return ptr_; }
	inline operator AbstractBase_ptr&() { return ptr_; }
	inline operator const AbstractBase_ptr& () const { return ptr_; }
	inline AbstractBase_ptr operator->() const { return ptr_; }
    private:
	AbstractBase_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	AbstractBase_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL AbstractBase_out
    {
    public:
        AbstractBase_out(AbstractBase *& p) : ptr_(p) { ptr_ = 0; }
        AbstractBase_out(AbstractBase_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        AbstractBase_out (const AbstractBase_out & p) : ptr_(p.ptr_) {}
        inline AbstractBase_out & operator=(const AbstractBase_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline AbstractBase_out& operator=(const AbstractBase_var& a)
	    { ptr_ = AbstractBase::_duplicate(AbstractBase_ptr(a)); return *this; }
        inline AbstractBase_out & operator=(AbstractBase * p) { ptr_ = p; return *this; }
        inline operator AbstractBase_ptr &() { return ptr_; }
        inline AbstractBase_ptr & ptr() { return ptr_; }
        inline AbstractBase_ptr operator->() { return ptr_; }
    private:
        AbstractBase_ptr & ptr_;
    };

    class OBBEXPDLL LocalBase
    {
    friend class CORBA;
    public:
	static LocalBase_ptr _duplicate (LocalBase_ptr);
	static LocalBase_ptr _narrow (LocalBase_ptr);
	static LocalBase_ptr _nil();
    protected:
	LocalBase();
	LocalBase(const LocalBase&) { }
#if defined(_AIX)
	virtual ~LocalBase() {}
#else
	virtual ~LocalBase() = 0;
#endif
	unsigned long m_refcount;
    };

    class OBBEXPDLL LocalBase_var : public _var
    {
    public:
	LocalBase_var() { ptr_ = LocalBase::_nil(); }
	LocalBase_var(LocalBase_ptr LBase) { ptr_ = LBase; }
	LocalBase_var(const LocalBase_var &LBasev)
		{ ptr_ = LocalBase::_duplicate(LocalBase_ptr(LBasev)); }
	~LocalBase_var() { release(ptr_); }
	LocalBase_var & operator=(LocalBase_ptr LBase);
	LocalBase_var & operator=(const LocalBase_var &LBasev)
	    { if (this != &LBasev) { release(ptr_);
	      ptr_ = LocalBase::_duplicate(LocalBase_ptr(LBasev)); }
	      return *this; }
	inline LocalBase_ptr in() const { return ptr_; }
	inline LocalBase_ptr& inout() { return ptr_; }
	inline LocalBase_ptr& out()
	    { release(ptr_); ptr_ = LocalBase::_nil(); return ptr_; }
	inline LocalBase_ptr _retn()
	    { LocalBase_ptr val = ptr_; ptr_ = LocalBase::_nil(); return val; }
	inline LocalBase_ptr& ptr() { return ptr_; }
	inline operator LocalBase_ptr&() { return ptr_; }
	inline operator const LocalBase_ptr& () const { return ptr_; }
	inline LocalBase_ptr operator->() const { return ptr_; }
    private:
	LocalBase_ptr ptr_;
	// hidden assignment operator to cause compile time error...
	LocalBase_var & operator=(const _var &Varv);
    };

    class OBBEXPDLL LocalBase_out
    {
    public:
        LocalBase_out(LocalBase *& p) : ptr_(p) { ptr_ = 0; }
        LocalBase_out(LocalBase_var & p) : ptr_(p.ptr())
	    { release ( ptr_ ); ptr_ = 0; }
        LocalBase_out (const LocalBase_out & p) : ptr_(p.ptr_) {}
        inline LocalBase_out & operator=(const LocalBase_out & p)
	    { ptr_ = p.ptr_; return *this; }
	inline LocalBase_out& operator=(const LocalBase_var& a)
	    { ptr_ = LocalBase::_duplicate(LocalBase_ptr(a)); return *this; }
        inline LocalBase_out & operator=(LocalBase * p) { ptr_ = p; return *this; }
        inline operator LocalBase_ptr &() { return ptr_; }
        inline LocalBase_ptr & ptr() { return ptr_; }
        inline LocalBase_ptr operator->() { return ptr_; }
    private:
        LocalBase_ptr & ptr_;
    };

    class OBBEXPDLL CustomMarshal : public virtual ValueBase
    {
    public:
	virtual void marshal (DataOutputStream_ptr os) = 0;
	virtual void unmarshal (DataInputStream_ptr is) = 0;
    };


    struct  ServiceDetail {
        ServiceDetailType service_detail_type;
        class  _1_service_detail
        {
            public:
                _1_service_detail();
                _1_service_detail(ULong _max);
                _1_service_detail
                (
                    ULong _max,
                    ULong _length,
                    Octet *_value,
                    Boolean _relse = CORBA_FALSE
                );
                _1_service_detail(const _1_service_detail &_ptr);
                ~_1_service_detail();
                _1_service_detail &operator=(const _1_service_detail& _ptr);
                inline ULong maximum() const {return _maximum;}
                void length(ULong);
                inline ULong length() const {return _current;}
                inline Octet &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const Octet &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                static Octet *allocbuf(ULong _nelems);
                static void freebuf(Octet *_ptr);
                inline Octet * OBB__GetData() const { return _data; }
            private:
                Octet *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class _1_service_detail
        _1_service_detail service_detail;
        ServiceDetail &operator=(const ServiceDetail &_obj);
    };
    typedef	ServiceDetail *	ServiceDetail_ptr;
    class OBBEXPDLL ServiceDetail_var
    {
        public:
            inline ServiceDetail_var() {_ptr = 0;}
            inline ServiceDetail_var(ServiceDetail *_obj) {_ptr = _obj;}
            ServiceDetail_var(const ServiceDetail_var &_obj) {_ptr = 0; *this = _obj;}
            ~ServiceDetail_var();
            ServiceDetail_var &operator=(ServiceDetail *);
            ServiceDetail_var &operator=(const ServiceDetail_var &);
            inline ServiceDetail *operator->() {return _ptr;}
            inline const ServiceDetail *operator->() const {return _ptr;}
            inline const ServiceDetail & in () const { return *_ptr; }
            inline ServiceDetail & inout () { return *_ptr; }
            ServiceDetail *& out ()
            {
                delete _ptr;
                _ptr=0;
                return _ptr;
            }
            ServiceDetail * _retn ()
            {
                ServiceDetail *tmp = _ptr;
                _ptr = 0;
                return tmp;
            }
            inline ServiceDetail_ptr & ptr() { return _ptr; }
            inline operator ServiceDetail&() { return *_ptr; }
            inline operator const ServiceDetail&() const { return *_ptr; }
            inline operator ServiceDetail_ptr &() { return _ptr; }
        private:
            ServiceDetail *_ptr;
    };  // class ServiceDetail_var
    class OBBEXPDLL ServiceDetail_out
    {
        public:
            ServiceDetail_out (ServiceDetail *& p) : ptr_(p) { ptr_ = 0; }
            ServiceDetail_out (ServiceDetail_var &p) : ptr_(p.ptr()) {
                delete ptr_; ptr_ = 0; }
            ServiceDetail_out (const ServiceDetail_out & a) : ptr_(a.ptr_) {}
            ServiceDetail_out & operator=(const ServiceDetail_out & a) {
                ptr_ = a.ptr_; return *this; }
            ServiceDetail_out & operator=(ServiceDetail * p) {
                ptr_ = p; return *this; }
            inline operator ServiceDetail_ptr & () { return ptr_; }
            inline ServiceDetail_ptr & ptr () { return ptr_; }
            inline ServiceDetail_ptr operator->() { return ptr_; }
        private:
            ServiceDetail_ptr & ptr_;
            void operator=(const ServiceDetail_var &);
    };  // class ServiceDetail_out


    struct  ServiceInformation {
        class  _1_service_options
        {
            public:
                _1_service_options();
                _1_service_options(ULong _max);
                _1_service_options
                (
                    ULong _max,
                    ULong _length,
                    ServiceOption *_value,
                    Boolean _relse = CORBA_FALSE
                );
                _1_service_options(const _1_service_options &_ptr);
                ~_1_service_options();
                _1_service_options &operator=(const _1_service_options& _ptr);
                inline ULong maximum() const {return _maximum;}
                void length(ULong);
                inline ULong length() const {return _current;}
                inline ServiceOption &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const ServiceOption &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                static ServiceOption *allocbuf(ULong _nelems);
                static void freebuf(ServiceOption *_ptr);
                inline ServiceOption * OBB__GetData() const { return _data; }
            private:
                ServiceOption *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class _1_service_options
        _1_service_options service_options;
        class OBBEXPDLL _1_service_details
        {
            public:
                _1_service_details();
                _1_service_details(ULong _max);
                _1_service_details
                (
                    ULong _max,
                    ULong _length,
                    ServiceDetail *_value,
                    Boolean _relse = CORBA_FALSE
                );
                _1_service_details(const _1_service_details &_ptr);
                ~_1_service_details();
                _1_service_details &operator=(const _1_service_details& _ptr);
                inline ULong maximum() const {return _maximum;}
                void length(ULong);
                inline ULong length() const {return _current;}
                inline ServiceDetail &operator[](ULong _index) {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                inline const ServiceDetail &operator[](ULong _index) const {if (_index > _maximum) throw BAD_PARAM(); return _data[_index];}
                static ServiceDetail *allocbuf(ULong _nelems);
                static void freebuf(ServiceDetail *_ptr);
                inline ServiceDetail * OBB__GetData() const { return _data; }
            private:
                ServiceDetail *_data;
                ULong _maximum;
                ULong _current;
                Boolean _release;
        };  // class _1_service_details
        _1_service_details service_details;
        ServiceInformation &operator=(const ServiceInformation &_obj);
    };
    typedef	ServiceInformation *	ServiceInformation_ptr;
    class OBBEXPDLL ServiceInformation_var
    {
        public:
            inline ServiceInformation_var() {_ptr = 0;}
            inline ServiceInformation_var(ServiceInformation *_obj) {_ptr = _obj;}
            ServiceInformation_var(const ServiceInformation_var &_obj) {_ptr = 0; *this = _obj;}
            ~ServiceInformation_var();
            ServiceInformation_var &operator=(ServiceInformation *);
            ServiceInformation_var &operator=(const ServiceInformation_var &);
            inline ServiceInformation *operator->() {return _ptr;}
            inline const ServiceInformation *operator->() const {return _ptr;}
            inline const ServiceInformation & in () const { return *_ptr; }
            inline ServiceInformation & inout () { return *_ptr; }
            ServiceInformation *& out ()
            {
                delete _ptr;
                _ptr=0;
                return _ptr;
            }
            ServiceInformation * _retn ()
            {
                ServiceInformation *tmp = _ptr;
                _ptr = 0;
                return tmp;
            }
            inline ServiceInformation_ptr & ptr() { return _ptr; }
            inline operator ServiceInformation&() { return *_ptr; }
            inline operator const ServiceInformation&() const { return *_ptr; }
            inline operator ServiceInformation_ptr &() { return _ptr; }
        private:
            ServiceInformation *_ptr;
    };  // class ServiceInformation_var
    class OBBEXPDLL ServiceInformation_out
    {
        public:
            ServiceInformation_out (ServiceInformation *& p) : ptr_(p) { ptr_ = 0; }
            ServiceInformation_out (ServiceInformation_var &p) : ptr_(p.ptr()) {
                delete ptr_; ptr_ = 0; }
            ServiceInformation_out (const ServiceInformation_out & a) : ptr_(a.ptr_) {}
            ServiceInformation_out & operator=(const ServiceInformation_out & a) {
                ptr_ = a.ptr_; return *this; }
            ServiceInformation_out & operator=(ServiceInformation * p) {
                ptr_ = p; return *this; }
            inline operator ServiceInformation_ptr & () { return ptr_; }
            inline ServiceInformation_ptr & ptr () { return ptr_; }
            inline ServiceInformation_ptr operator->() { return ptr_; }
        private:
            ServiceInformation_ptr & ptr_;
            void operator=(const ServiceInformation_var &);
    };  // class ServiceInformation_out

    class OBBEXPDLL DataOutputStream : public virtual ValueBase
     {
        public:
            static DataOutputStream_ptr _downcast(ValueBase_ptr obj);

            virtual void write_any (const Any & value) = 0; 
            virtual void write_boolean (Boolean value) = 0; 
            virtual void write_char (Char value) = 0; 
#if !defined(M3_NO_UNICODE_SUPPORT)
            virtual void write_wchar (WChar value) = 0; 
#endif
            virtual void write_octet (Octet value) = 0; 
            virtual void write_short (Short value) = 0; 
            virtual void write_ushort (UShort value) = 0; 
            virtual void write_long (Long value) = 0; 
            virtual void write_ulong (ULong value) = 0; 
#if !defined(M3_NO_LONG_LONG_SUPPORT)
            virtual void write_longlong (LongLong value) = 0; 
            virtual void write_ulonglong (ULongLong value) = 0; 
#endif
            virtual void write_float (Float value) = 0; 
            virtual void write_double (Double value) = 0; 
#if defined(M3_LONG_DOUBLE_SUPPORT)
	    virtual void write_longdouble (LongDouble value) = 0;
#endif
            virtual void write_string (const char * value) = 0; 
#if !defined(M3_NO_UNICODE_SUPPORT)
            virtual void write_wstring (const WChar * value) = 0; 
#endif
            virtual void write_Object (Object_ptr value) = 0; 
	    virtual void write_Abstract (AbstractBase_ptr value) = 0;
	    virtual void write_Value (ValueBase_ptr value) = 0;
            virtual void write_TypeCode (TypeCode_ptr value) = 0; 

            virtual void write_any_array (
		 const AnySeq & seq,
		ULong offset,
		ULong length) = 0;

            virtual void write_boolean_array (
                 const BooleanSeq & seq,
		ULong offset,
		ULong length) = 0; 

            virtual void write_char_array (
                 const CharSeq & seq,
                ULong offset,
                ULong length) = 0; 

#if !defined(M3_NO_UNICODE_SUPPORT)
            virtual void write_wchar_array (
                 const WCharSeq & seq,
                ULong offset,
                ULong length) = 0; 
#endif

            virtual void write_octet_array (
                 const OctetSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void write_short_array (
                 const ShortSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void write_ushort_array (
                 const UShortSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void write_long_array (
                 const LongSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void write_ulong_array (
                 const ULongSeq & seq,
                ULong offset,
                ULong length) = 0; 

#if !defined(M3_NO_LONG_LONG_SUPPORT)
            virtual void write_ulonglong_array (
                 const ULongLongSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void write_longlong_array (
                 const LongLongSeq & seq,
                ULong offset,
                ULong length) = 0; 
#endif

            virtual void write_float_array (
                 const FloatSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void write_double_array (
                 const DoubleSeq & seq,
                ULong offset,
                ULong length) = 0; 

#if defined(M3_LONG_DOUBLE_SUPPORT)
            virtual void write_long_double_array (
                 const LongDoubleSeq & seq,
                ULong offset,
                ULong length) = 0; 
#endif

        protected:
            DataOutputStream() { }
            virtual ~DataOutputStream(){ }

        private:
            void operator=(const DataOutputStream&) { }
    };  // class DataOutputStream

    class OBBEXPDLL DataInputStream : public virtual ValueBase
    {
       public:
            static DataInputStream_ptr _downcast(ValueBase_ptr obj);

            virtual Any * read_any () = 0; 
            virtual Boolean read_boolean () = 0; 
            virtual Char read_char () = 0; 
#if !defined(M3_NO_UNICODE_SUPPORT)
            virtual WChar read_wchar () = 0; 
#endif
            virtual Octet read_octet () = 0; 
            virtual Short read_short () = 0; 
            virtual UShort read_ushort () = 0; 
            virtual Long read_long () = 0; 
            virtual ULong read_ulong () = 0; 
#if !defined(M3_NO_LONG_LONG_SUPPORT)
            virtual LongLong read_longlong () = 0; 
            virtual ULongLong read_ulonglong () = 0; 
#endif
            virtual Float read_float () = 0; 
            virtual Double read_double () = 0; 
#if defined(M3_LONG_DOUBLE_SUPPORT)
	    virtual LongDouble read_longdouble () = 0;
#endif
            virtual Char * read_string () = 0; 
#if !defined(M3_NO_UNICODE_SUPPORT)
            virtual WChar * read_wstring () = 0; 
#endif
            virtual Object_ptr read_Object () = 0; 
	    virtual AbstractBase_ptr read_Abstract() = 0;
	    virtual ValueBase_ptr read_Value() = 0;
            virtual TypeCode_ptr read_TypeCode () = 0; 

            virtual void read_any_array (
                AnySeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_boolean_array (
                BooleanSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_char_array (
                CharSeq & seq,
                ULong offset,
                ULong length) = 0; 

#if !defined(M3_NO_UNICODE_SUPPORT)
            virtual void read_wchar_array (
                WCharSeq & seq,
                ULong offset,
                ULong length) = 0; 
#endif

            virtual void read_octet_array (
                OctetSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_short_array (
                ShortSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_ushort_array (
                UShortSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_long_array (
                LongSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_ulong_array (
                ULongSeq & seq,
                ULong offset,
                ULong length) = 0; 

#if !defined(M3_NO_LONG_LONG_SUPPORT)
            virtual void read_ulonglong_array (
                ULongLongSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_longlong_array (
                LongLongSeq & seq,
                ULong offset,
                ULong length) = 0; 
#endif

            virtual void read_float_array (
                FloatSeq & seq,
                ULong offset,
                ULong length) = 0; 

            virtual void read_double_array (
                DoubleSeq & seq,
                ULong offset,
                ULong length) = 0; 

#if defined(M3_LONG_DOUBLE_SUPPORT)
            virtual void read_long_double_array (
                LongDoubleSeq & seq,
                ULong offset,
                ULong length) = 0; 
#endif

        protected:
            DataInputStream() { }
            virtual ~DataInputStream() { }

        private:
            void operator=(const DataInputStream&) { }
    };  // class DataInputStream

#if defined(ORB_INCLUDE_REPOSITORY)
#include <ir_c.h>
#else
#if !defined(_WIN32)
    class InterfaceDef {};
    class OperationDef {};
#endif
#endif

    class OBBEXPDLL StringValue : public ValueBase
    {
        public:
            StringValue();
            StringValue(const StringValue& val);
            StringValue(char* str);
            StringValue(const char* str);
            StringValue(const String_var& var); 
            StringValue& operator=(char* str);
            StringValue& operator=(const char* str);
            StringValue& operator=(const String_var& var);
            const char* _value() const;
            void _value(char* str);
            void _value(const char* str);
            void _value(const String_var& var );
            const char* _boxed_in() const;
            char*& _boxed_inout();
            char*& _boxed_out();
            ValueBase* _copy_value();
            static StringValue* _downcast(ValueBase* base);
            RepositoryId _OBB__get_id();
            ULong _OBB__get_id_list(RepositoryId*&);
            ValueBase* _add_ref();
            void _remove_ref();
            ULong _refcount_value();
        protected:
            ~StringValue();
        private:
            void operator=(const StringValue& val);
            char* m_string;
            unsigned long m_refcount;
    };

    class OBBEXPDLL StringValue_out 
    {
        public:
            StringValue_out(StringValue*& p) : ptr_(p) { ptr_ = 0; }
            StringValue_out(const StringValue_out& s) : ptr_(s.ptr_) {}
            inline StringValue_out& operator=(const StringValue_out& _s)
              { ptr_ = _s.ptr_; return *this; }
            inline StringValue_out& operator=(StringValue* p)
              { ptr_ = p; return *this; }
            inline StringValue_out& operator=(const StringValue* p)
              { ptr_ = new StringValue(p->_boxed_in()); return *this; }
            inline operator StringValue *&() { return ptr_; }
            inline StringValue *& ptr() { return ptr_; }
        private:
            StringValue*& ptr_;
    };

    class OBBEXPDLL StringValue_var : public _var
    {
        public:
            StringValue_var() { ptr_ = NULL; }
            inline StringValue_var(StringValue_ptr p) { ptr_ = p; }
            StringValue_var(const StringValue_var &a) { ptr_ = StringValue::_downcast (a->_copy_value()); }
            ~StringValue_var() { free();}
            StringValue_var &operator=(StringValue_ptr p)
              { if (p != ptr_) reset(p); return *this; }
            StringValue_var &operator=(const StringValue_var &a);
            inline StringValue_ptr in () const { return ptr_; }
            inline StringValue_ptr & inout () { return ptr_; }
            StringValue_ptr & out ()
	        { if (ptr_) ptr_->_remove_ref(); ptr_ = NULL; return ptr_; }
            StringValue_ptr _retn ()
	        { StringValue_ptr val = ptr_; ptr_ = NULL; return val; }
            inline operator StringValue_ptr&() { return ptr_; }
            inline operator const StringValue_ptr&() const { return ptr_; }
            inline StringValue_ptr operator->() const { return ptr_; }
            inline StringValue_ptr & ptr () { return ptr_; }
        protected:
            StringValue_ptr ptr_;
            void free();
            void reset(StringValue_ptr p) { free(); ptr_ = p; }
        private:
            void operator=(const _var &);
    };

    class OBBEXPDLL StringValue_init : public ValueFactoryBase
    {
        public:
            StringValue_init() {}
            virtual ~StringValue_init() {}
            static StringValue_init* _downcast(ValueFactory);
        private:
            virtual ValueBase* create_for_unmarshal();
    };

#if !defined(M3_NO_UNICODE_SUPPORT)
    class OBBEXPDLL WStringValue : public ValueBase
    {
        public:
            WStringValue();
            WStringValue(const WStringValue & val);
            WStringValue(wchar_t * str);
            WStringValue(const wchar_t * str);
            WStringValue(const WString_var & var);
            WStringValue & operator=(wchar_t * str);
            WStringValue & operator=(const wchar_t * str);
            WStringValue & operator=(const WString_var & var);
            const wchar_t * _value() const;
            void _value(wchar_t * str);
            void _value(const wchar_t * str);
            void _value(const WString_var & var );
            const wchar_t * _boxed_in() const;
            wchar_t*& _boxed_inout();
            wchar_t*& _boxed_out();
            ValueBase* _copy_value();
            static WStringValue* _downcast(ValueBase* base);
            RepositoryId _OBB__get_id();
            ULong _OBB__get_id_list(RepositoryId*&);
            ValueBase* _add_ref();
            void _remove_ref();
            ULong _refcount_value();
        protected:
            ~WStringValue();
        private:
            void operator=(const WStringValue & val);
            wchar_t * m_string;
            unsigned long m_refcount;
    };

    class OBBEXPDLL WStringValue_out
    {
        public:
	    WStringValue_out(WStringValue*& p) : ptr_(p) { ptr_ = 0; }
	    WStringValue_out(const WStringValue_out& s) : ptr_(s.ptr_) {}

	    inline WStringValue_out& operator=(const WStringValue_out& _s)
	        { ptr_ = _s.ptr_; return *this; }
	    inline WStringValue_out& operator=(WStringValue* p)
	        { ptr_ = p; return *this; }
	    inline WStringValue_out& operator=(const WStringValue* p)
	        { ptr_ = new WStringValue(p->_boxed_in()); return *this; }

	    inline operator WStringValue *&() { return ptr_; }
	    inline WStringValue *& ptr() { return ptr_; }
        private:
            WStringValue*& ptr_;
    };

    class OBBEXPDLL WStringValue_var : public _var
    {
        public:
            WStringValue_var() { ptr_ = NULL; }
            inline WStringValue_var(WStringValue_ptr p) { ptr_ = p; }
            WStringValue_var(const WStringValue_var &a) { ptr_ = WStringValue::_downcast (a->_copy_value()); }
            ~WStringValue_var() { free();}
            WStringValue_var &operator=(WStringValue_ptr p)
              { if (p != ptr_) reset(p); return *this; }
            WStringValue_var &operator=(const WStringValue_var &a);
            inline WStringValue_ptr in () const { return ptr_; }
            inline WStringValue_ptr & inout () { return ptr_; }
            WStringValue_ptr & out ()
	        { if (ptr_) ptr_->_remove_ref(); ptr_ = NULL; return ptr_; }
            WStringValue_ptr _retn ()
	        { WStringValue_ptr val = ptr_; ptr_ = NULL; return val; }
            inline operator WStringValue_ptr&() { return ptr_; }
            inline operator const WStringValue_ptr&() const { return ptr_; }
            inline WStringValue_ptr operator->() const { return ptr_; }
            inline WStringValue_ptr & ptr () { return ptr_; }
        protected:
            WStringValue_ptr ptr_;
            void free();
            void reset(WStringValue_ptr p) { free(); ptr_ = p; }
        private:
            void operator=(const _var &);
    };

    class OBBEXPDLL WStringValue_init : public ValueFactoryBase
    {
        public:
            WStringValue_init() {}
            virtual ~WStringValue_init() {}
            static WStringValue_init* _downcast(ValueFactory);
        private:
            virtual ValueBase* create_for_unmarshal();
    };
#endif

}; // end of CORBA class

// Overloaded operators
OBBEXPDLL void operator<<=(CORBA::Any & AnyObj,
    const CORBA::SystemException & ObjPtr);
OBBEXPDLL CORBA::Boolean operator>>=(const CORBA::Any &AnyObj,
    CORBA::SystemException *& ObjPtr);

//
// Definitions used in Generated Dispatchers, TypeCode Lookup Routines,
// and Client Stubs
//

    typedef struct _OBBHashTableEntry {
	CORBA::Short StartId;		/* Starting Id for bucket   */
	CORBA::UShort BucketIndex;	/* Index into bucket table.	*/
    } OBBHashTableEntry;

    typedef struct _OBBArgument {
	CORBA::Flags Flags;
	char * Name;
	const void * ValuePtr;
	CORBA::TypeCode_ptr TC;
	union {
	    CORBA::Short Sht;
	    CORBA::Long Lng;
	    CORBA::UShort USht;
	    CORBA::ULong ULng;
	    CORBA::Float Flt;
	    CORBA::Double Dbl;
	    CORBA::Boolean Booln;
	    CORBA::Char Chr;
	    CORBA::Octet Oct;
#if !defined(M3_NO_UNICODE_SUPPORT)
            CORBA::WChar WChr;
#endif
#if !defined(M3_NO_LONG_LONG_SUPPORT)
	    CORBA::LongLong LngLng;
	    CORBA::ULongLong ULngLng;
#endif
	    void * Ptr;
	} Value;
    } OBBArgument;

    //
    // Prototypes for routines to perform Marshalling, Unmarshalling,
    // Copying, and Deleting of User-Defined types using a TypeCode.
    //

    typedef CORBA::TypeCode_ptr (*OBB_TypeCodeLookupProc)(
	const char * TypeCodeID,
        void * TypeRtnInfo);

//
// OBB Extensions to CORBA
//
class OBBEXPDLL OBB
{
public:

    // OBB object forward references
    class ServerRequest;
    class OBBArgumentList;
    class Current;
    class OBBRegisteredTypeIds;
    class OBBRegisteredTCRtns;
    class OBBInterfaceDescriptor;
    class IntfDescriptorHolder;

    // Typedefs
    typedef ServerRequest * ServerRequest_ptr;
    typedef Current * Current_ptr;
    typedef OBBArgumentList * OBBArgumentList_ptr;
    typedef OBBRegisteredTypeIds * OBBRegisteredTypeIds_ptr;
    typedef OBBRegisteredTCRtns * OBBRegisteredTCRtns_ptr;
    typedef unsigned Status;
	typedef TM32U MinorCode;

    // Constants
    // OBB::BEA_IIOP_ID and OBB::BEA_TOBJ_ID are ORBids that can
    // be passed to CORBA::ORB_init()
    static OBBCONSTDATA char * BEA_IIOP_ID;
    static OBBCONSTDATA char * BEA_TOBJ_ID;

    class OBBEXPDLL ServantBase
    {
    public:
	// OBB internal use functions
	CORBA::ULong OBB__id() const;
	void OBB__id(CORBA::ULong Id);
	void * OBB__poa();
	void OBB__poa(void * POA);
	void * OBB__servantId();

    protected:
	ServantBase();
	virtual ~ServantBase();

    private:
	CORBA::ULong _id;
	void * _poa;
	void * _servantid;
    };

    class OBBEXPDLL ServantManager : public CORBA::Object
    {
	public:
	protected:
	    ServantManager() {}
	    virtual ~ServantManager() {}

	private:
	    // Hidden functions to disallow direct copy.
	    ServantManager( const ServantManager& t);
	    void operator=(const ServantManager&);
    };  // class ServantManager


    // OBB internal use class to handle marshalling, unmarshalling

    class OBBEXPDLL MarshalBuf
    {
    public:
	// Types

	// Constructors/Destructors

	MarshalBuf();
	MarshalBuf(void *);
	~MarshalBuf();

	// Operators

	// Encoding datatypes
	MarshalBuf &operator<<(const CORBA::Short);
	MarshalBuf &operator<<(const CORBA::Long);
	MarshalBuf &operator<<(const CORBA::UShort);
	MarshalBuf &operator<<(const CORBA::ULong);
	MarshalBuf &operator<<(const CORBA::Float);
	MarshalBuf &operator<<(const CORBA::Double);
	MarshalBuf &operator<<(const CORBA::Octet);
	MarshalBuf &operator<<(const CORBA::Any &);
	MarshalBuf &operator<<(const CORBA::TypeCode_ptr);
	MarshalBuf &operator<<(const CORBA::Principal_ptr);
	MarshalBuf &operator<<(const CORBA::Object_ptr);
	MarshalBuf &operator<<(const CORBA::TypeCode_var &);
	MarshalBuf &operator<<(const CORBA::Object_var &);
	MarshalBuf &operator<<(const char *);
	MarshalBuf &operator<<(const CORBA::String_var &);
#if !defined(M3_NO_LONG_LONG_SUPPORT)
	MarshalBuf &operator<<(const CORBA::LongLong);
	MarshalBuf &operator<<(const CORBA::ULongLong);
#endif
#if defined(M3_LONG_DOUBLE_SUPPORT)
	MarshalBuf &operator<<(const CORBA::LongDouble);
#endif
#if !defined(M3_NO_UNICODE_SUPPORT)
	MarshalBuf &operator<<(const wchar_t *);
	MarshalBuf &operator<<(const CORBA::WString_var &);
#endif
	inline MarshalBuf &operator<<(MarshalBuf &) { return (*this); };
	void MarshalValue(CORBA::TypeCode_ptr, CORBA::ValueBase_ptr);
	void UnMarshalValue(CORBA::TypeCode_ptr, CORBA::ValueBase_ptr&);
	void MarshalCustom(CORBA::CustomMarshal_ptr);
	void UnMarshalCustom(CORBA::CustomMarshal_ptr);

	// Decoding datatypes
	MarshalBuf &operator>>(CORBA::Short &);
	MarshalBuf &operator>>(CORBA::Long &);
	MarshalBuf &operator>>(CORBA::UShort &);
	MarshalBuf &operator>>(CORBA::ULong &);
	MarshalBuf &operator>>(CORBA::Float &);
	MarshalBuf &operator>>(CORBA::Double &);
	MarshalBuf &operator>>(CORBA::Octet &);
	MarshalBuf &operator>>(CORBA::Any &);
	MarshalBuf &operator>>(CORBA::TypeCode_ptr &);
	MarshalBuf &operator>>(CORBA::Principal_ptr &);
	MarshalBuf &operator>>(CORBA::Object_ptr &);
	MarshalBuf &operator>>(CORBA::TypeCode_var &);
	MarshalBuf &operator>>(CORBA::Object_var &);
	MarshalBuf &operator>>(char * &);
	MarshalBuf &operator>>(CORBA::String_var &);
#if !defined(M3_NO_LONG_LONG_SUPPORT)
	MarshalBuf &operator>>(CORBA::LongLong &);
	MarshalBuf &operator>>(CORBA::ULongLong &);
#endif
#if defined(M3_LONG_DOUBLE_SUPPORT)
	MarshalBuf &operator>>(CORBA::LongDouble &);
#endif
#if !defined(M3_NO_UNICODE_SUPPORT)
	MarshalBuf &operator>>(wchar_t * &);
	MarshalBuf &operator>>(CORBA::WString_var &);
#endif
	inline MarshalBuf &operator>>(MarshalBuf &)	{ return (*this); };

	// Accessors
	inline Status status() const { return m_status; };
	inline void * marsh_handle() const { return m_coder; };
	inline CORBA::ORB_ptr OBB__get_orb() const { return m_orb; };

	// Modifiers
	inline void status(Status st) { m_status = st; };
	inline void marsh_handle(void * mh) { m_coder = mh; };

	// Special member functions for CORBA::Boolean, CORBA::Char
	//     Bounded strings.
	MarshalBuf & from_boolean (const CORBA::Boolean Dtp);
	MarshalBuf & from_char (const CORBA::Char Dtp);
	MarshalBuf & from_bndstr (const char * Dtp,
					     const CORBA::ULong Bnd);
	MarshalBuf & from_bndstr (const CORBA::String_var &Dtp,
					     const CORBA::ULong Bnd);
#if !defined(M3_NO_UNICODE_SUPPORT)
	MarshalBuf & from_wchar (const CORBA::WChar Dtp);
	MarshalBuf & from_bndwstr (const wchar_t * Dtp,
					     const CORBA::ULong Bnd);
	MarshalBuf & from_bndwstr (const CORBA::WString_var &Dtp,
					     const CORBA::ULong Bnd);
#endif
	MarshalBuf & to_boolean (CORBA::Boolean &Dtp);
	MarshalBuf & to_char (CORBA::Char &Dtp);
	MarshalBuf & to_bndstr (char * &Dtp,
					   CORBA::ULong Bnd);
	MarshalBuf & to_bndstr (CORBA::String_var &Dtp,
					   CORBA::ULong Bnd);
#if !defined(M3_NO_UNICODE_SUPPORT)
	MarshalBuf & to_wchar (CORBA::WChar &Dtp);
	MarshalBuf & to_bndwstr (wchar_t * &Dtp,
					   CORBA::ULong Bnd);
	MarshalBuf & to_bndwstr (CORBA::WString_var &Dtp,
					   CORBA::ULong Bnd);
#endif

	// Utility routines
	CORBA::Boolean IsSameEndian();
	CORBA::Boolean IsSameFloat();
	void DecodeBuffer(CORBA::ULong Length, CORBA::ULong Align,
			  unsigned char * Data);
	void EncodeBuffer(CORBA::ULong Length, CORBA::ULong Align,
			  unsigned char * Data);

    private:
	void * m_coder;			// Encoding or Decoding class
	Status m_status;		// Return status
	CORBA::ORB_ptr m_orb;		// Pointer to current ORB
    };

    // OBB::OBBArgumentList
    class OBBEXPDLL OBBArgumentList
    {
    public:
	// Accessors
	virtual CORBA::ULong GetCount() = 0;
	virtual CORBA::Flags GetFlags (const CORBA::ULong Index) = 0;
	virtual const char * GetName (const CORBA::ULong Index) = 0;
	virtual const void * GetValue (const CORBA::ULong Index) = 0;
	virtual CORBA::TypeCode_ptr GetTypeCode (const CORBA::ULong Index) = 0;
	// Modifiers
	virtual void SetFlags (const CORBA::ULong Index, CORBA::Flags FlagsValue
			      ) = 0;
	virtual void SetValue (const CORBA::ULong Index, const void * Value
			      )=0;
	virtual void SetTypeCode (const CORBA::ULong Index, CORBA::TypeCode_ptr
			          TypeCodePtr) = 0;

	// Member functions

    protected:
	// Constructors/Destructors
	OBBArgumentList() {};
	virtual ~OBBArgumentList() {};

    private:

    };

    // OBB::ServerRequest
    class OBBEXPDLL ServerRequest : public CORBA::ServerRequest
    {
    public:
        virtual void OBB__arguments (
            OBBArgumentList_ptr parameters) = 0;
        virtual void OBB__arguments () = 0;
        virtual void OBB__set_exception_from_minor (
            MinorCode &code) = 0;
	virtual void OBB__set_exception(
	    const CORBA::Exception& value) = 0;

	virtual OBBArgumentList_ptr OBB__create_argument_list(
	    const CORBA::ULong) = 0;

	virtual OBBArgument * OBB__create_argument_info(
	    const CORBA::ULong) = 0;

	virtual CORBA::Context_ptr OBB__ctx() = 0;

	inline static ServerRequest_ptr OBB__convert_scope
	    (CORBA::ServerRequest_ptr aSvr)
		{ return (OBB::ServerRequest_ptr) aSvr; }
        virtual CORBA::ORB_ptr OBB__get_orb() = 0;
	virtual CORBA::Boolean OBB__exception_set() = 0;
	virtual CORBA::Boolean OBB__is_oneway() = 0;

    protected:
	ServerRequest() {}
	virtual ~ServerRequest() {};
    };

    // OBB::Current
    class OBBEXPDLL Current : public CORBA::Current
    {
    public:
	// Typedefs
	typedef CORBA::Long IPTimeOut;
	typedef CORBA::Long IPAddressFilterSeq;
	typedef CORBA::Long IPPortRangeSeq;
	enum SingleFloatFlag { FLOAT_F, FLOAT_IEEES };
	enum DoubleFloatFlag { DOUBLE_G, DOUBLE_D, DOUBLE_IEEET };

	virtual CORBA::Boolean tgiop_timeout_enabled() = 0;
	virtual IPTimeOut request_timeout() = 0;
	virtual IPTimeOut ip_connect_timeout() = 0;
	virtual IPAddressFilterSeq ip_include_address_filter() = 0;
	virtual IPAddressFilterSeq ip_exclude_address_filter() = 0;
	virtual IPPortRangeSeq ip_port_range() = 0;
	virtual SingleFloatFlag single_float_type() = 0;
	virtual DoubleFloatFlag double_float_type() = 0;
	virtual char * peek_servant_id() = 0;
	virtual void tgiop_timeout_enabled(CORBA::Boolean) = 0;
	virtual void request_timeout(IPTimeOut) = 0;
	virtual void ip_connect_timeout(IPTimeOut) = 0;
	virtual void ip_include_address_filter(IPAddressFilterSeq) = 0;
	virtual void ip_exclude_address_filter(IPAddressFilterSeq) = 0;
	virtual void ip_port_range(IPPortRangeSeq) = 0;
	virtual void single_float_type(SingleFloatFlag) = 0;
	virtual void double_float_type(DoubleFloatFlag) = 0;
	virtual void register_tc_lookup_rtn(OBB_TypeCodeLookupProc) = 0;
	virtual CORBA::Boolean default_ior_enabled() = 0;
	virtual void default_ior_enabled(CORBA::Boolean) = 0;
	virtual void push_servant_id(char *) = 0;
	virtual void pop_servant_id() = 0;

	static Current_ptr _narrow(CORBA::Object_ptr);
	static Current_ptr _narrow(CORBA::Current_ptr);
	static Current_ptr _duplicate (Current_ptr);
	inline static Current_ptr _nil() {return 0;}

    protected:
	Current() {}
	virtual ~Current() {};
    };


    // Utility class - internal use only
    class OBBEXPDLL OBBRegisteredTypeIds
    {
    public:
	struct ListEntry { const char * id; const char ** list; };
	OBBRegisteredTypeIds( const char * TypeId, const char ** List);
	~OBBRegisteredTypeIds();
	static CORBA::Boolean OBB__is_a( const char * TypeId, const char * IsAId );
	static CORBA::Boolean OBB__exists( const char * TypeId );

    protected:
	OBBRegisteredTypeIds() {};
    };


    // Utility class - internal use only
    class OBBEXPDLL OBBRegisteredTCRtns
    {
    public:
	OBBRegisteredTCRtns(OBB_TypeCodeLookupProc);
	~OBBRegisteredTCRtns();

    protected:
	OBBRegisteredTCRtns() {};
    };


    // Utility routines - internal use only
    static CORBA::TypeCode_ptr OBB__create_tc(
	const CORBA::Octet * BufPtr,
	const char * Id=0);
    static CORBA::Short OBB__method_hash (
	const char * Id,
	CORBA::Short TableSize,
	OBBHashTableEntry * HashTable,
	const char * BucketTable);
    static void OBB__hash_name (
	const char * Name,
	unsigned int * HashIndex);
    static CORBA::TypeCode_ptr OBB__get_base_type(
        CORBA::Short index);
    static OBBArgumentList_ptr OBB__create_argument_list(
        const CORBA::ULong);

    static void OBB__get_object_key_encap (
	const CORBA::Object_ptr ObjPtr,
        CORBA::ULong & ObjKeySize,
	CORBA::Octet * & ObjKeyEncapPtr);

    static void OBB__create_request (
	    CORBA::Object_ptr obj,
	    CORBA::Context_ptr ctx,
	    const char * operation,
	    CORBA::ULong arg_count,
	    OBBArgument * arg_list,
	    CORBA::ExceptionList_ptr excep_list,
            CORBA::ContextList_ptr ctx_list,
	    CORBA::Request_out request,
	    CORBA::Flags req_flags);

    static CORBA::Request_ptr OBB__create_request (
	    CORBA::Object_ptr obj,
	    CORBA::ULong operation_length,
	    const char * operation,
	    CORBA::ULong arg_count,
	    OBBArgument * arg_list,
	    CORBA::Boolean response_expected,
	    CORBA::Context_ptr ctx,
            CORBA::ContextList_ptr ctx_list);

	// Utility class - internal use only, for registering
	// implementations of interfaces in server
	
	typedef struct interface_info
	{
		char * interface_id;
		char * impl_id;
		unsigned long   act_policy;
		unsigned long   trans_policy;
	} OBBInterfaceInfo, *OBBInterfaceInfoPtr;

        typedef struct interface_info_entry
        {
           OBBInterfaceInfo      intf_data;
           struct interface_info_entry *next_entry;
        } OBBInterfaceInfoEntry;

	class OBBEXPDLL OBBInterfaceDescriptor
	{
	public:
		virtual void get_interface(
			char **, char **, unsigned long *, unsigned long *);
		virtual CORBA::ULong get_count ();
		~OBBInterfaceDescriptor() {}
		OBBInterfaceDescriptor(OBBInterfaceInfo *p, CORBA::ULong i);
	private:
		OBBInterfaceInfo	*_ptr;
		CORBA::ULong		_count;
		CORBA::ULong next_entry;
	};

#define IOP_MAX_HASH_IMPL_ID 33
#define IOP_MAX_INTERFACE_ID 128

	class OBBEXPDLL IntfDescriptorHolder
	{
	public:
		static void insert_intf_descriptor(OBBInterfaceDescriptor *ptr);
		static CORBA::Boolean get_intf_descriptor(
                                char interface_id[IOP_MAX_INTERFACE_ID],
                                char hash_impl_id[IOP_MAX_HASH_IMPL_ID],
                                int &act_policy,
                                int &trans_policy);
	private:
		static OBBInterfaceInfoEntry	*intf_list_head;
		static OBBInterfaceInfoEntry	*intf_list_tail;
	};
}; // end OBB class

class OBBEXPDLL BiDirPolicy
{
public:
    typedef CORBA::UShort BidirectionalPolicyValue;
    typedef BidirectionalPolicyValue& BidirectionalPolicyValue_out;
    static OBBCONSTDATA BidirectionalPolicyValue NORMAL;
    static OBBCONSTDATA BidirectionalPolicyValue BOTH;
    static OBBCONSTDATA CORBA::PolicyType BIDIRECTIONAL_POLICY_TYPE;

    class BidirectionalPolicy;
    typedef BidirectionalPolicy * BidirectionalPolicy_ptr;

    class OBBEXPDLL BidirectionalPolicy : public CORBA::Policy
    {
    public:
	static BidirectionalPolicy_ptr _duplicate(
	    BidirectionalPolicy_ptr obj);
	inline static BidirectionalPolicy_ptr _nil() { return (BidirectionalPolicy_ptr) 0;}

	virtual CORBA::Policy_ptr copy () = 0;
	virtual void destroy () = 0;
	virtual BidirectionalPolicyValue value () const = 0;
	virtual CORBA::ULong OBB__id() const = 0;

	protected:
	    BidirectionalPolicy() {};
	    virtual ~BidirectionalPolicy() {};

	private:
	    // Hidden functions to disallow direct copy.
	    BidirectionalPolicy (const BidirectionalPolicy& t);
	    void operator=(const BidirectionalPolicy&);
    };  // class BidirectionalPolicy

    class OBBEXPDLL BidirectionalPolicy_var : public CORBA::_var {
	public:
	    BidirectionalPolicy_var()
		{ ptr_ = BiDirPolicy::BidirectionalPolicy::_nil(); };
	    BidirectionalPolicy_var(BidirectionalPolicy_ptr p) { ptr_ = p; }
	    BidirectionalPolicy_var(const BidirectionalPolicy_var &v)
		{ ptr_ = BiDirPolicy::BidirectionalPolicy::_duplicate(
		  BiDirPolicy::BidirectionalPolicy_ptr(v)); }
	    ~BidirectionalPolicy_var() { free(); }
	    inline BidirectionalPolicy_var &operator=(BidirectionalPolicy_ptr p)
		{ if (p != ptr_) reset(p); return *this; }
	    inline BidirectionalPolicy_var &operator=(const BidirectionalPolicy_var& a)
		{ if (this != &a) { free();
		    ptr_ = BiDirPolicy::BidirectionalPolicy::_duplicate(
		    BiDirPolicy::BidirectionalPolicy_ptr(a)); }
		  return *this; }
      	    inline BidirectionalPolicy_ptr in() const { return ptr_; }
	    inline BidirectionalPolicy_ptr& inout() { return ptr_; }
	    inline BidirectionalPolicy_ptr& out()
		{ reset(BiDirPolicy::BidirectionalPolicy::_nil()); return ptr_; }
    	    inline BidirectionalPolicy_ptr _retn()
		{ BidirectionalPolicy_ptr val = ptr_;
		  ptr_ = BiDirPolicy::BidirectionalPolicy::_nil(); return val; }
	    inline BidirectionalPolicy_ptr& ptr() { return ptr_; }
	    inline operator BidirectionalPolicy_ptr&() { return ptr_; }
	    inline operator const BidirectionalPolicy_ptr&() const { return ptr_; }
	    inline BidirectionalPolicy_ptr operator->() const { return ptr_; }

	private:
	    BidirectionalPolicy_ptr ptr_;
	    inline void free() { if (ptr_) ptr_->destroy(); }
	    inline void reset(BidirectionalPolicy_ptr p) { free(); ptr_ = p; }
	    void operator=(const CORBA::_var &);
    };  // class BidirectionalPolicy_var


    class OBBEXPDLL BidirectionalPolicy_out {
	public:
	    BidirectionalPolicy_out(BidirectionalPolicy_ptr& p) : ptr_(p)
		{ ptr_ = BiDirPolicy::BidirectionalPolicy::_nil(); }
	    BidirectionalPolicy_out(BidirectionalPolicy_var& p) : ptr_(p.ptr())
		{ if (ptr_) ptr_->destroy(); ptr_ = BidirectionalPolicy::_nil(); }
	    BidirectionalPolicy_out(const BidirectionalPolicy_out& a) : ptr_(a.ptr_) {}
	    inline BidirectionalPolicy_out& operator=(BidirectionalPolicy_out& a)
		{ ptr_ = a.ptr_; return *this; }
	    inline BidirectionalPolicy_out& operator=(const BidirectionalPolicy_var& a)
		{ ptr_ = BiDirPolicy::BidirectionalPolicy::_duplicate(
		  BidirectionalPolicy_ptr(a)); return *this; }
	    inline BidirectionalPolicy_out& operator=(BidirectionalPolicy_ptr p)
		{ ptr_ = p; return *this; }
	    inline operator BidirectionalPolicy_ptr&() { return ptr_; }
	    inline BidirectionalPolicy_ptr& ptr() { return ptr_; }
	    inline BidirectionalPolicy_ptr operator->() { return ptr_; }

	private:
	    BidirectionalPolicy_ptr& ptr_;
    };  // class BidirectionalPolicy_out

    
}; // end BiDirPolicy class

#ifdef ORB_INCLUDE_REPOSITORY
#include <ir_opr_c.h>
#endif

void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ServiceDetail &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ServiceDetail *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ServiceDetail *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ServiceInformation &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ServiceInformation *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ServiceInformation *&obj);
//void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::PolicyError &obj);
//void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::PolicyError *obj);
//CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::PolicyError *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::AnySeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::AnySeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::AnySeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::BooleanSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::BooleanSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::BooleanSeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::CharSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::CharSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::CharSeq *&obj);
#if !defined(M3_NO_UNICODE_SUPPORT)
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::WCharSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::WCharSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::WCharSeq *&obj);
#endif
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::OctetSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::OctetSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::OctetSeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ShortSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ShortSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ShortSeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::UShortSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::UShortSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::UShortSeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::LongSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::LongSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::LongSeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ULongSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ULongSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ULongSeq *&obj);
#if !defined(M3_NO_LONG_LONG_SUPPORT)
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::LongLongSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::LongLongSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::LongLongSeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::ULongLongSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::ULongLongSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::ULongLongSeq *&obj);
#endif
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::FloatSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::FloatSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::FloatSeq *&obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::DoubleSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::DoubleSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::DoubleSeq *&obj);
#if defined(M3_LONG_DOUBLE_SUPPORT)
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::LongDoubleSeq &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::LongDoubleSeq *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::LongDoubleSeq *&obj);
#endif
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::StringValue &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::StringValue *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::StringValue *&obj);
#if !defined(M3_NO_UNICODE_SUPPORT)
void  OBBEXPDLL operator<<=(CORBA::Any &a, const CORBA::WStringValue &obj);
void  OBBEXPDLL operator<<=(CORBA::Any &a, CORBA::WStringValue *obj);
CORBA::Boolean  OBBEXPDLL operator>>=(const CORBA::Any &a, CORBA::WStringValue *&obj);
#endif
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ServiceDetail &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ServiceDetail &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ServiceInformation &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ServiceInformation &);
//OBB::MarshalBuf  &operator<<(OBB::MarshalBuf &, CORBA::PolicyError &);
//OBB::MarshalBuf  &operator>>(OBB::MarshalBuf &, CORBA::PolicyError &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::AnySeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::AnySeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::BooleanSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::BooleanSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::CharSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::CharSeq &);
#if !defined(M3_NO_UNICODE_SUPPORT)
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::WCharSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::WCharSeq &);
#endif
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::OctetSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::OctetSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ShortSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ShortSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::UShortSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::UShortSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::LongSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::LongSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ULongSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ULongSeq &);
#if !defined(M3_NO_LONG_LONG_SUPPORT)
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::LongLongSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::LongLongSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::ULongLongSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::ULongLongSeq &);
#endif
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::FloatSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::FloatSeq &);
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::DoubleSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::DoubleSeq &);
#if defined(M3_LONG_DOUBLE_SUPPORT)
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::LongDoubleSeq &);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::LongDoubleSeq &);
#endif
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::StringValue_ptr);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::StringValue_ptr&);
#if !defined(M3_NO_UNICODE_SUPPORT)
OBB::MarshalBuf OBBEXPDLL &operator<<(OBB::MarshalBuf &, CORBA::WStringValue_ptr);
OBB::MarshalBuf OBBEXPDLL &operator>>(OBB::MarshalBuf &, CORBA::WStringValue_ptr&);
#endif
#endif /* _CORBA_h */


