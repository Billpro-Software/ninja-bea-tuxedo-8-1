#ifndef OLEOSA_H
#define OLEOSA_H

//=============================================================================
//				ENUMERATIONS
//=============================================================================

typedef enum ExceptionTypeTag
{
	NO_EXCEPTION, SYSTEM_EXCEPTION, USER_EXCEPTION
} ExceptionType;

typedef enum CORBA_CompletionStatusTag
{
	COMPLETION_YES,
	COMPLETION_NO,
	COMPLETION_MAYBE
} CORBA_CompletionStatus;

typedef enum CORBATCKindTag
{
	tk_null = 0,
	tk_void,
	tk_short,
	tk_long,
	tk_ushort,
	tk_ulong,
	tk_float,
	tk_double,
	tk_octet,
	tk_any,
	tk_typeCode,
	tk_principal,
	tk_objref,
	tk_struct,
	tk_union,
	tk_enum,
	tk_string,
	tk_sequence,
	tk_array,
	tk_alias,
	tk_except
} CORBATCKind;

typedef enum CORBAAnyDataTagEnum
{
	anySimpleValTag,
	anyAnyValTag,
	anySeqValTag,
	anyStructValTag,
	anyUnionValTag,
	anyObjectValTag,
	anyInvalidTag = -1
} CORBAAnyDataTag;

// The following definition of VFACILITY macro and VTOleException enum
// is a duplicate of that in include\osa\oleutil.hh. Any modification to
// this definition must be also applied to the definition in oleutil.hh
#ifndef VFACILITY
#define VFACILITY(name,value)			\
	ITF_E_##name##		= ##value,\
	ITF_E_##name##_NO	= 0x80040000 | ##value,\
	ITF_E_##name##_YES	= 0x80041000 | ##value,\
	ITF_E_##name##_MAYBE	= 0x80042000 | ##value

enum VTOleException
{
	// Generic errors

	VFACILITY(UNKNOWN,		0x200),
	VFACILITY(BAD_PARAM,		0x201),
	VFACILITY(NO_MEMORY,		0x202),
	VFACILITY(IMP_LIMIT,		0x203),
	VFACILITY(COMM_FAILURE,		0x204),
	VFACILITY(INV_OBJREF,		0x205),
	VFACILITY(NO_PERMISSION,	0x206),
	VFACILITY(INTERNAL,		0x207),
	VFACILITY(MARSHAL,		0x208),
	VFACILITY(INITIALIZE,		0x209),
	VFACILITY(NO_IMPLEMENT,		0x20A),
	VFACILITY(BAD_TYPECODE,		0x20B),
	VFACILITY(BAD_OPERATION,	0x20C),
	VFACILITY(NO_RESOURCES,		0x20D),
	VFACILITY(NO_RESPONSE,		0x20E),
	VFACILITY(PERSIST_STORE,	0x20F),
	VFACILITY(BAD_INV_ORDER,	0x210),
	VFACILITY(TRANSIENT,		0x211),
	VFACILITY(FREE_MEM,		0x212),
	VFACILITY(INV_IDENT,		0x213),
	VFACILITY(INV_FLAG,		0x214),
	VFACILITY(INTF_REPOS,		0x215),
	VFACILITY(BAD_CONTEXT,		0x216),
	VFACILITY(OBJ_ADAPTER,		0x217),
	VFACILITY(DATA_CONVERSION,	0x218),
	VFACILITY(OBJECT_NOT_EXIST,	0x219),

	VFACILITY(BRIDGE_ERROR,		0x300)
};
#endif // VFACILITY

//=============================================================================
//		     FORWARD DECLARATION OF THE INTERFACES
//=============================================================================

interface IAnyFactory;
interface IMonikerProvider;
interface DIForeignComplexType;
interface DICORBAStruct;
interface DICORBAUnion;
interface DIForeignException;
interface DICORBAUserException;
interface DICORBASystemException;
interface DICORBATypeCode;
interface ICORBA_TypeCodeUserExceptions;
interface ICORBA_TypeCode;
interface DICORBAAny;
interface ICORBA_Any;
interface DICORBAFactory;
interface ICORBAFactory;
interface DICORBAFactoryEx;
interface IBridgeTypeFactory;
interface DIObjectBridgeFactory;
interface IObjectBridgeFactory;

//=============================================================================
//				STRUCTURES & ALIASES
//=============================================================================

typedef LPWSTR	RepositoryId;
typedef LPWSTR	Identifier;
typedef CORBATCKind TCKind;

typedef struct VComExcepProxyStructTag
{
	ExceptionType	type;
	LPWSTR		repositoryId;
	IUnknown	*piUserException;
} VComExcepProxyStruct;

typedef struct
{
	short notused;
} TypeCodeBounds;

typedef struct
{
	short notused;
} TypeCodeBadKind;

typedef struct 
{
	ExceptionType	type;
	LPWSTR		repositoryId;
	ICORBA_TypeCodeUserExceptions   *piUserException;
} CORBATypeCodeExceptions;

typedef struct CORBAAnyDataUnion
{
	CORBAAnyDataTag	whichOne;
	union
	{
		/* case anyAnyValTag: */
			ICORBA_Any *anyVal;

		/* case anySeqValTag:
		  case anyStructValTag: */
			struct
			{
				char *repositoryId;
				unsigned long cbMaxSize;
				unsigned long cbLengthUsed;
				struct CORBAAnyDataUnion *pVal;
			} multiVal;

		/* case anyUnionValTag: */
			struct
			{
				char *repositoryId;
				long disc;
				struct CORBAAnyDataUnion *value;
			} unionVal;

		/* case anyObjectValTag: */
			struct
			{
				char *repositoryId;
				VARIANT val;
			} objectVal;

		/* case anySimpleValTag: */
			VARIANT simpleVal;
	} tagged_union;	/* 'tagged_union' as generated by MIDL compiler. */
} CORBAAnyData;

typedef struct
{
	unsigned long	cbMaxSize;
	unsigned long	cbLengthUsed;
	long		*pValue;
} objSystemIDs;

typedef struct
{
	unsigned long	cbMaxSize;
	unsigned long	cbLengthUsed;
	LPSTR		*pValue;
} CORBA_ORBObjectIdList;

//=============================================================================
//				INTERFACES
//=============================================================================

//=============================================================
// ANY FACTORY INTERFACES
//=============================================================

interface IAnyFactory : public IUnknown
{
	STDMETHOD(CreateAny)(ICORBA_Any **rtrn) PURE;
};

//=============================================================
// MONIKER PROVIDER INTERFACES
//=============================================================

interface IMonikerProvider : public IUnknown
{
	STDMETHOD(get_moniker)(IMoniker **rtrn) PURE;
};

//=============================================================
// FOREIGN COMPLEX TYPE INTERFACES
//=============================================================

interface DIForeignComplexType : public IDispatch
{
	STDMETHOD(INSTANCE_repositoryId)(
		 BSTR		*IT_retval) PURE;

	STDMETHOD(INSTANCE_clone)(
		 IDispatch		**IT_retval) PURE;
};

//=============================================================
// CORBA STRUCT TYPE INTERFACES
//=============================================================

interface DICORBAStruct : public DIForeignComplexType
{
};

//=============================================================
// CORBA UNION TYPE INTERFACES
//=============================================================

interface DICORBAUnion : public DIForeignComplexType
{
};

//=============================================================
// FOREIGN EXCEPTIONS INTERFACES
//=============================================================

interface DIForeignException : public DIForeignComplexType
{
	STDMETHOD(EX_majorCode)(
			long		*IT_retval) PURE;
};

//=============================================================
// CORBA USER EXCEPTIONS INTERFACES
//=============================================================

interface DICORBAUserException : public DIForeignException
{
};

//=============================================================
// CORBA SYSTEM EXCEPTIONS INTERFACES
//=============================================================

interface DICORBASystemException : public DIForeignException
{
	STDMETHOD(EX_minorCode)(
			long	*IT_retval) PURE;

	STDMETHOD(EX_completionStatus)(
			long	*IT_retval) PURE;
};

//=============================================================
// TYPECODES INTERFACES
//=============================================================

interface DICORBATypeCode : public DIForeignComplexType
{
	STDMETHOD(kind)(CORBATCKind	*IT_retval) PURE;

	//----------------------------------------------------------
	// for tk_objref, tk_struct, tk_union, tk_alias, tk_except
	//----------------------------------------------------------

	STDMETHOD(id)(BSTR		*IT_retval) PURE;

	STDMETHOD(name)(BSTR		*IT_retval) PURE;

	//----------------------------------------------------------
	// for tk_struct, tk_union, tk_enum, tk_except
	//----------------------------------------------------------

	STDMETHOD(member_count)(long		*IT_retval) PURE;

	STDMETHOD(member_name)( long		index,
				BSTR		*IT_retval) PURE;

	STDMETHOD(member_type)( long		index,
				IDispatch	**IT_retval) PURE;

	//----------------------------------------------------------
	// for tk_union
	//----------------------------------------------------------

	STDMETHOD(member_label)(long		index,
				VARIANT		*IT_retval) PURE;

	STDMETHOD(discriminator_type)(IDispatch	**IT_retval) PURE;

	STDMETHOD(default_index)(long		*IT_retval) PURE;

	//----------------------------------------------------------
	// for tk_string, tk_array, tk_sequence
	//----------------------------------------------------------

	STDMETHOD(length)(long		*IT_retval) PURE;

	//----------------------------------------------------------
	// for tk_sequence, tk_array, tk_alias
	//----------------------------------------------------------

	STDMETHOD(content_type)(IDispatch	**IT_retval) PURE;
};

interface ICORBA_TypeCodeUserExceptions : public IUnknown
{
	STDMETHOD(get_Bounds)(  TypeCodeBounds *ExceptionBody) PURE;
	STDMETHOD(get_BadKind)(  TypeCodeBadKind *pExceptionBody) PURE;
};

interface ICORBA_TypeCode : public IUnknown
{
	STDMETHOD(equal)(  
		 ICORBA_TypeCode		*piTc,
		 boolean			*pbRetVal) PURE;

	STDMETHOD(kind)(
		 TCKind				*pRetVal) PURE;

	//----------------------------------------------------------
	// for tk_objref, tk_struct, tk_union, tk_alias, tk_except
	//----------------------------------------------------------

	STDMETHOD(id)(
		 RepositoryId			*pszRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	STDMETHOD(name)(
		 Identifier			*pszRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	//----------------------------------------------------------
	// for tk_struct, tk_union, tk_enum, tk_except
	//----------------------------------------------------------

	STDMETHOD(member_count)(
		 unsigned long			*pulRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	STDMETHOD(member_name)(
		 unsigned long			ulIndex,
		 Identifier			*pszRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	STDMETHOD(member_type)(
		 unsigned long		ulIndex,
		 ICORBA_TypeCode		**ppRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	//----------------------------------------------------------
	// for tk_union
	//----------------------------------------------------------

	STDMETHOD(member_label)(
		 unsigned long			ulIndex,
		 ICORBA_Any			**ppRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	STDMETHOD(discriminator_type)(
		 ICORBA_TypeCode		**ppRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	STDMETHOD(default_index)(
		 long				*plRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	//----------------------------------------------------------
	// for tk_string, tk_array, tk_sequence
	//----------------------------------------------------------

	STDMETHOD(length)(
		 unsigned long			*pulRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;

	//----------------------------------------------------------
	// for tk_sequence, tk_array, tk_alias
	//----------------------------------------------------------

	STDMETHOD(content_type)(
		 ICORBA_TypeCode		**ppRetVal,
		 CORBATypeCodeExceptions	**ppUserExceptions) PURE;
};

//=============================================================
// ANY INTERFACES
//=============================================================

interface DICORBAAny : public DIForeignComplexType
{
	STDMETHOD(get_value)(
			VARIANT		*IT_retval) PURE;
	STDMETHOD(put_value)(
			VARIANT		value) PURE;

	STDMETHOD(typeCode)(
			DICORBATypeCode	**IT_retval) PURE;
};

interface ICORBA_Any : public IUnknown
{
	STDMETHOD(_get_value)(VARIANT *val) PURE;
	STDMETHOD(_put_value)(VARIANT val) PURE;

	STDMETHOD(_get_CORBAAnyData)(CORBAAnyData *val) PURE;
	STDMETHOD(_put_CORBAAnyData)(CORBAAnyData val) PURE;

	STDMETHOD(_get_typeCode)(ICORBA_TypeCode **tc) PURE;
};

//=============================================================
// BRIDGE DIRECTORY INTERFACES
//=============================================================
interface DICORBAFactory : public IDispatch
{
	STDMETHOD(CreateObject)(
			BSTR		factoryName, 
			IDispatch	**rtrn) PURE;

	STDMETHOD(GetObject)(
			BSTR		objectName, 
			IDispatch	**rtrn) PURE;
};

interface ICORBAFactory : public IUnknown
{
	STDMETHOD(CreateObject)(
			LPWSTR		factoryName,
			IUnknown	**rtrn) PURE;

	STDMETHOD(GetObject)(
			LPWSTR		objectName, 
			IUnknown	**rtrn) PURE;
};

//=============================================================
// INITIAL IN-PARAMETER INTERFACES
//=============================================================
interface DICORBAFactoryEx : public DICORBAFactory
{
	STDMETHOD(CreateType)(
			IDispatch	*scopingObject,
			BSTR		typeName,
			VARIANT		*IT_retval) PURE;

	STDMETHOD(CreateTypeById)(
			IDispatch	*scopingObject,
			BSTR		repositoryId,
			VARIANT		*IT_retval) PURE;
};

//=============================================================
// CORBA FACTORY INTERFACES
//=============================================================
typedef ICORBAFactory    IBRIDGEDirectory;
typedef DICORBAFactory   DIBRIDGEDirectory;
typedef DICORBAFactoryEx DIBRIDGEDirectoryEx;

//=============================================================
// OBJECT BRIDGE FACTORY INTERFACES
//=============================================================
interface DIObjectBridgeFactory : public DICORBAFactoryEx
{
	STDMETHOD(LoadAdapter)(
			BSTR		adapterName) PURE;
};

interface IObjectBridgeFactory : public ICORBAFactory
{
	STDMETHOD(LoadAdapter)(
			LPWSTR		adapterName) PURE;
};

//=============================================================
// INITIAL IN-PARAMETER INTERFACES
//=============================================================
interface IBridgeTypeFactory : public IUnknown
{
	STDMETHOD(CreateType)(
			LPSTR		typeName,
			VARIANT		*IT_retval) PURE;

	STDMETHOD(CreateTypeById)(
			RepositoryId	repositoryId,
			VARIANT		*IT_retval) PURE;
};

//=============================================================
// INITIAL IN-PARAMETER INTERFACES
//=============================================================
interface IForeignObject : public IUnknown
{
	STDMETHOD(GetForeignReference)(
			objSystemIDs	systemIDs,
			long		*systemID,
			LPSTR		*objRef) PURE;

	STDMETHOD(GetRepositoryId)(
			RepositoryId	*repositoryId) PURE;
};

interface ICORBAObject : public IUnknown
{
	STDMETHOD(GetInterface)(
			IUnknown	**val) PURE;

	STDMETHOD(GetImplementation)(
			IUnknown	**val) PURE;

	STDMETHOD(IsA)(
			RepositoryId	repositoryId,
			boolean		*itIsA) PURE;

	STDMETHOD(IsNil)(
			boolean		*itIsNil) PURE;

	STDMETHOD(IsEquivalent)(
			IUnknown	*obj,
			boolean		*val) PURE;

	STDMETHOD(NonExistent)(
			boolean		*val) PURE;

	STDMETHOD(Hash)(
			long		*val) PURE;
};

interface DICORBAObject : public IDispatch
{
	STDMETHOD(GetInterface)(
			IDispatch	**val) PURE;

	STDMETHOD(GetImplementation)(
			IDispatch	**val) PURE;

	STDMETHOD(IsA)(
			BSTR		repositoryID,
			boolean		*itIsA) PURE;

	STDMETHOD(IsNil)(
			boolean		*itIsNil) PURE;

	STDMETHOD(IsEquivalent)(
			IDispatch	*obj,
			boolean		*val) PURE;

	STDMETHOD(NonExistent)(
			boolean		*val) PURE;

	STDMETHOD(Hash)(
			long		*val) PURE;
};

interface IORBObject : public IUnknown
{
	STDMETHOD(ObjectToString)(
			IUnknown	*obj,
			LPSTR		*val) PURE;

	STDMETHOD(StringToObject)(
			LPSTR		ref,
			IUnknown	**val) PURE;

	STDMETHOD(GetInitialReference)(
			CORBA_ORBObjectIdList *val) PURE;

	STDMETHOD(ResolveInitialReference)(
			LPSTR		name,
			IUnknown	**val) PURE;
};

interface DIORBObject : public IDispatch
{
	STDMETHOD(ObjectToString)(
			IDispatch	*obj,
			BSTR		*val) PURE;

	STDMETHOD(StringToObject)(
			BSTR		ref,
			IDispatch	**val) PURE;

	STDMETHOD(GetInitialReference)(
			SAFEARRAY	**val) PURE;

	STDMETHOD(ResolveInitialReference)(
			BSTR		name,
			IDispatch	**val) PURE;

	STDMETHOD(GetCORBAObject)(
			IDispatch	*obj,
			DICORBAObject	**val) PURE;
};

#endif // OLEOSA_H
