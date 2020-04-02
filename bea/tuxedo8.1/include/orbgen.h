//	Copyright (c) 1997 BEA Systems, Inc.
//	All rights reserved
//
//	THIS IS UNPUBLISHED PROPRIETARY
//	SOURCE CODE OF BEA Systems, Inc.
//	The copyright notice above does not
//	evidence any actual or intended
//	publication of such source code.
//
// #ident	"@(#) orb/src/orbgen.h	$Revision: 1.10 $"

#ifndef _orbgen_h
#define _orbgen_h

#include <obbmsg.h>

#ifndef CORBA_ARG_IN
#define CORBA_ARG_IN	1
#endif
#ifndef CORBA_ARG_INOUT
#define CORBA_ARG_INOUT 4
#endif
#ifndef CORBA_ARG_OUT
#define CORBA_ARG_OUT	2
#endif
#ifndef OBB_RESULT
#define OBB_RESULT	64
#endif

#ifndef CORBA_NO_EXCEPTION
#define CORBA_NO_EXCEPTION	0
#endif
#ifndef CORBA_SYSTEM_EXCEPTION
#define CORBA_SYSTEM_EXCEPTION 200
#endif
#ifndef CORBA_USER_EXCEPTION
#define CORBA_USER_EXCEPTION   400
#endif

#ifndef OBB_EXPORT
#define OBB_EXPORT
#endif

#ifndef OBB_ARG_CLIENT_SIDE
#define OBB_ARG_CLIENT_SIDE 128
#endif
#ifndef OBB_ARG_SERVER_SIDE
#define OBB_ARG_SERVER_SIDE 256
#endif
#ifndef OBB_ARG_IN_BUF
#define OBB_ARG_IN_BUF 512
#endif
#ifndef OBB_ARG_MEMORY_ALLOCATED
#define OBB_ARG_MEMORY_ALLOCATED 1024
#endif
#ifndef OBB_ARG_NO_STATE
#define OBB_ARG_NO_STATE 2048
#endif
typedef void *CORBA_Object;
typedef CORBA_Object CORBA_TypeCode;
typedef void *OBBMrshHandle;

#define _TC_HASH_null           0
#define _TC_HASH_void           -1
#define _TC_HASH_short          -2
#define _TC_HASH_long           -3
#define _TC_HASH_ushort         -4
#define _TC_HASH_ulong          -5
#define _TC_HASH_float          -6
#define _TC_HASH_double         -7
#define _TC_HASH_boolean        -8
#define _TC_HASH_char           -9
#define _TC_HASH_octet          -10
#define _TC_HASH_any            -11
#define _TC_HASH_TypeCode       -12
#define _TC_HASH_Principal      -13
#define _TC_HASH_objref         -14
#define _TC_HASH_Object         -14
#define _TC_HASH_struct         -15
#define _TC_HASH_union          -16
#define _TC_HASH_enum           -17
#define _TC_HASH_string         -18
#define _TC_HASH_sequence       -19
#define _TC_HASH_array          -20
#define _TC_HASH_alias          -21
#define _TC_HASH_except         -22
#define	_TC_HASH_longlong	-23
#define	_TC_HASH_ulonglong	-24
#define	_TC_HASH_longdouble	-25
#define	_TC_HASH_wchar		-26
#define	_TC_HASH_wstring	-27
#define	_TC_HASH_fixed		-28
#define	_TC_HASH_value		-29
#define	_TC_HASH_value_box	-30
#define	_TC_HASH_native 	-31
#define	_TC_HASH_abstract_interface -32

// DLL compilation macros

#if defined(WIN32)
#define ORBEXPDLL __declspec(dllexport)
#define ORBIMPDLL __declspec(dllimport)
#else
#define ORBEXPDLL
#define ORBIMPDLL
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


// Private flags
#define OBB__IOP_NO_REP_OPERATION	1

//
// Definitions used in Generated Dispatchers, TypeCode Lookup Routines,
// and Client Stubs
//


    //
    // Prototypes for routines to perform Marshalling, Unmarshalling,
    // Copying, and Deleting of User-Defined types using a TypeCode.
    //

    typedef OBB::Status (*OBB_TypeCodeMarshProc) (
	void * MarshHandle,
	void * ObjPtr);

    typedef OBB::Status (*OBB_TypeCodeUnMarshProc) (
	void * MarshHandle,
        void ** ObjPtr,
	CORBA::Flags Flags);

    typedef void (*OBB_TypeCodeDeleteProc) (
	void * ObjPtr);

    typedef void (*OBB_TypeCodeCopyProc) (
	void * ObjPtr,
        void ** NewObjPtr);

    typedef struct _TCTypeInfo {
	OBB_TypeCodeMarshProc MarshRtn;
        OBB_TypeCodeUnMarshProc UnMarshRtn;
	OBB_TypeCodeDeleteProc DeleteRtn;
	OBB_TypeCodeCopyProc CopyRtn;
	} OBB_TCTypeInfo;

#endif
