/*	Copyright (c) 1997 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) objtm/include/NamesLib.h	$Revision: 1.10 $" */


#ifndef _NAMES_LIB_H
#define _NAMES_LIB_H

#ifndef NOWHAT
static char h_names_lib[] = "@(#)iceberg:include/NamesLib.h  $Revision: 1.10 $";
#endif

// *****************************************************************
// Classes : LNameComponent & LName
// Purpose : Both of these classes are defined in the Naming Service
//           "Names Library". Basically, an LName is a list of
//           LNameComponents
// *****************************************************************

#if defined(WIN32)
#pragma warning(disable : 4290)	// warning C4290: C++ Exception Specification ignored
#endif

#include <orbiop.h>

#include <ns_c.h>

#if defined(WIN32)
# if defined(EXPDLL_LIBENV)
#  define OBBEXPDLLUSER __declspec(dllexport)
# else
#  define OBBEXPDLLUSER __declspec(dllimport)
# endif
#else
# define OBBEXPDLLUSER
#endif

const char* const LNAME_COMPONENT_EMPTY_ID = "";  // dont care about ID field of an LNameComponent

const int LNAME_MAX_STRLEN = 128;                 // maximum string length

// ***************************************************
// Class   : LNameComponent
// Purpose : Implements Naming Service "Names Library"
// ***************************************************

class OBBEXPDLLUSER LNameComponent {
public:

	// -----  Class Exceptions  -----

	class NotSet{ };
	class OverFlow{ };
	class NullPointer{ };

	// -----  Class Methods  -----

	static LNameComponent* create_lname_component();

	// -----  Instance Destruction  -----
	
	void	destroy();

	// -----  Instance Accessors  -----

	const char*	get_id() const;
	void		set_id(const char* i);
	const char*	get_kind() const;
	void		set_kind(const char* k);

	// ===============  BEA Extensions  ===============

	NS_CORBA(Boolean)	equal(const LNameComponent* lnc) const;
	NS_CORBA(Boolean)	equalKind(const LNameComponent* lnc) const;
	const char*			displayString() const;

private:

	char* m_id;
	char* m_kind;

	// -----  Instance Construction/Destruction  -----

	LNameComponent();
	~LNameComponent();

#ifdef __linux__
    friend class FalseFriend_orbiop;
#endif
};

// ***************************************************
// Class   : LName
// Purpose : Implements Naming Service "Names Library"
// ***************************************************

class OBBEXPDLLUSER LName {
public:

	// -----  Class Exceptions  -----

	class NoComponent{ };
	class OverFlow{ };
	class InvalidName{ };
	class NotImplemented{ };

	// -----  Class Testing  -----

	static NS_CORBA(Boolean)
		is_valid_string(const char* s);

	// -----  Class Constructor for Instance  -----

	static LName* create_lname();


	// -----  Instance Construction/Destruction  -----

	void destroy();		// PIDL destructor

	// -----  Instance Operations based on NamSvc Spec  -----

	LName*
		insert_component(const unsigned long i, LNameComponent* n);
	const LNameComponent*
		get_component(const unsigned long i) const;
	const LNameComponent*
		delete_component(const unsigned long i);
	unsigned long
		num_components() const;
	NS_CORBA(Boolean)
		equal(const LName* ln) const;
	NS_CORBA(Boolean)
		less_than(const LName* ln) const;
	NS_NS(Name*)
		to_idl_form();
	void
		from_idl_form(const NS_NS(Name&) nr);

	// ===============  BEA Extensions  ===============

	static NS_CORBA(Boolean)
		is_valid_name(const NS_NS(Name&) nr);

	NS_CORBA(Boolean)
		equalKind(const LName* ln) const;
	NS_CORBA(Boolean)
		match(const NS_NS(Name&) nr) const;
	const char*
		displayString() const;

	const char*
		lname_to_string() const;
	void
		string_to_lname(const char* s);

private:

	// -----  Constructors/Destructors  -----

	LName(const int = 0);
	~LName();

	// -----  Instance Variables  -----

	LNameComponent**	m_tbl;
	int					m_length;
	int					m_size;

	// -----  Instance Accessors  -----

	void				tbl(LNameComponent** t);
	LNameComponent**	tbl() const;
	void				length(const int n);
	int					length() const;
	void				size(const int n);
	int					size() const;
	
	// -----  Instance List Manipulation  -----

	LNameComponent*		at(const int n) const;
	void				atput(const int n, LNameComponent* i);

	// -----  Instance List Contruction/Destruction Utilities  -----

	void				buildUp(const int n);
	void				tearDown();

#ifdef __linux__
    friend class FalseFriend_orbiop;
#endif
};

#undef OBBEXPDLLUSER

#endif	// _NAMES_LIB_H
