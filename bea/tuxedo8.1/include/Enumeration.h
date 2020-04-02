/*	Copyright (c) 1997 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) objtm/include/Enumeration.h	$Revision: 1.3 $" */


#ifndef _ENUMERATION_H
#define _ENUMERATION_H

#ifndef NOWHAT
static char h_enumeration[] = "@(#)iceberg:include/Enumeration.h  $Revision: 1.3 $";
#endif

#include <TobjS_c.h>

// ***********************************************************
// Classes : Entry + Enumeration
// Purpose : NameManager maintains the Named-to-Object binding
//           that is stored in NamedObject in a round-robin
//           queue
// ***********************************************************

#if defined(WIN32)
#pragma warning(disable : 4290)	// warning C4290: C++ Exception Specification ignored
#endif

// ***********************************************
// Class   : NamedObject
// Purpose : These are the Name-to-Object Bindings
// ***********************************************

class Entry {
public:

	// -----  Instance Accessors  -----

	void*		data() const;
	
private:

	friend class Enumeration;	// only Enumeration creates these instances!

	// -----  Instance Variables  -----

	void*		m_data;
	Entry*		m_next;				// for a linked list

	// -----  Instance Constructors/Destructors  -----

	Entry(void* v);
	~Entry();

	// -----  Instance Accessors  -----

	void		data(void* v);
	void		next(Entry* v);
	Entry*		next() const;
};

// ****************************************************
// Class   : NameManager
// Purpose : Manage NamedObjects in a round-robin queue
// ****************************************************

class Enumeration {
public:

	// -----  Instance Constructors/Destructos  -----

	Enumeration();
	~Enumeration();

	// -----  Instance Accessing  -----

	int size() const;

	// -----  Instance List Traversal  -----

	int			hasMoreElements() const;
	void*		nextElement();

	// -----  Instance List Management  -----

	void		addElement(void* dp);

private:
	
	// -----  Instance Variables  -----

	Entry*		m_front;
	Entry*		m_back;
	Entry*		m_current;
	int			m_size;

	// -----  Instance Accessors  -----

	void		front(Entry* v);
	Entry*		front() const;
	void		back(Entry* v);
	Entry*		back() const;
	void		current(Entry* v);
	Entry*		current() const;
	void		size(const int v);
};

#endif	// _ENUMERATION_H
