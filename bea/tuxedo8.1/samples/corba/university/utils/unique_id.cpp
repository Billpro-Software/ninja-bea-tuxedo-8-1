/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
//--------------------------------------------------------------------
//
// unique_id.cpp
//
// C++ UniqueId class routines for the university sample application
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#ifdef WIN32
#include <windows.h>
#include <time.h>
#include <strstrea.h>
#else
#include <sys/time.h>
#include <time.h>
#include <strstream.h>
#endif

#include "unique_id.h"

//--------------------------------------------------------------------

class UniqueIdInternals
{
  public:
    unsigned long sec;
    unsigned long usec;
    // generated copy constructor and assignment operator ok
};

//--------------------------------------------------------------------

UniqueId UniqueId::generate()
{
    UniqueId uid;
#ifdef WIN32
    uid.m_internals->sec  = time(NULL);
    uid.m_internals->usec = GetCurrentTime();
#else
    struct timeval  tv;
    struct timezone tz;
    // assume it succeeds:
    gettimeofday(&tv, &tz);
    uid.m_internals->sec  = tv.tv_sec;
    uid.m_internals->usec = tv.tv_usec;
#endif
    return uid;
}

//--------------------------------------------------------------------

UniqueId::UniqueId(const UniqueId& rhs) :
    m_internals(new UniqueIdInternals(*(rhs.m_internals)))
{
}

//--------------------------------------------------------------------

UniqueId& UniqueId::operator=(const UniqueId& rhs)
{
    if (this != &rhs) {
        *(this->m_internals) = *(rhs.m_internals);
    }
    return *this;
}

//--------------------------------------------------------------------

int UniqueId::operator==(const UniqueId& rhs) const
{
    return
    (
        this->m_internals->sec  == rhs.m_internals->sec  &&
        this->m_internals->usec == rhs.m_internals->usec
    ) ? 1 : 0;
}

//--------------------------------------------------------------------

int UniqueId::hash() const
{
    return int(this->m_internals->sec | this->m_internals->usec);
}

//--------------------------------------------------------------------

UniqueId::UniqueId() :
    m_internals(new UniqueIdInternals)
{
    m_internals->sec  = 0;
    m_internals->usec = 0;
}

//--------------------------------------------------------------------

UniqueId::~UniqueId()
{
    delete m_internals;
}

//--------------------------------------------------------------------

ostream& operator<<(ostream& os, const UniqueId& uid)
{
    return os << uid.m_internals->sec << ' ' << uid.m_internals->usec;
}

//--------------------------------------------------------------------

istream& operator>>(istream& is, UniqueId& uid)
{
    return is >> uid.m_internals->sec >> uid.m_internals->usec;
}
