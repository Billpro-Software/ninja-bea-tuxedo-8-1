/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
//--------------------------------------------------------------------
//
// unique_id.h
//
// C++ UniqueId class header for the university sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifndef __UNIQUE_ID_H__
#define __UNIQUE_ID_H__

#include <iostream.h>

class UniqueIdInternals;

class UniqueId
{
public:
    static UniqueId generate();
    UniqueId();
    UniqueId(const UniqueId&);
    UniqueId& operator=(const UniqueId& rhs);
    ~UniqueId();
    int operator==(const UniqueId& rhs) const;
    int operator!=(const UniqueId& rhs) const
    {
        return !(*this == rhs);
    }
    int hash() const;
private:
    UniqueIdInternals* m_internals;
friend ostream& operator<<(ostream&, const UniqueId&);
friend istream& operator>>(istream&, UniqueId&);
};

extern ostream& operator<<(ostream&, const UniqueId&);
extern istream& operator>>(istream&, UniqueId&);

#endif // __UNIQUE_ID_H__

