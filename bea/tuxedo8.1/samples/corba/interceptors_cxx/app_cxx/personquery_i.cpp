//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// PersonQuery_i.cpp
//
// BEA Systems Inc. sample code.
// C++ PersonQuery implementation for the C++ Interceptor sample application.
//
//--------------------------------------------------------------------
//
// The code in this file implements the PersonQuery interface for the
// C++ interceptors sample application.  It contains a small database of
// informations which is searched to satisfy queries from the PersonQuery
// client.  The database is an array of PersonQuery::Person data structures.
//
// This implementation has many helper functions to determine whether a
// database entry satisfies the query.  These are named according to their
// function.  For example, a function named "MatchName" would attempt to
// match the name field of the incoming query to the name field of a
// database entry.  The "Pull" functions match the search criterium against
// a database entry, and if the entry satisfies the criterium, they copy
// the entry to a PersonQuery::Person structure for return to the client.
// The "Count" functions just count the number of entries in the database
// which satisfy the search criteria.  These are used by the PersonQuery_i
// CORBA methods to determine how much memory to allocate for the returned
// data.
//  
// The "dump" functions are for debugging.
//

//#define DEBUG 1
#ifdef DEBUG
#include <stdio.h>
#endif
#include <TP.h>
#include "personquery_i.h"

/*
 * Construct the data base.
 */
static CORBA::ULong init_db_buffer(PersonQuery::Person **data);
#ifdef DEBUG
void dumpMarriage(PersonQuery::MARRIAGE mar);
void dumpSex(PersonQuery::SEX sex);
void dumpHobby(PersonQuery::HOBBIES hob);
void dumpColor(PersonQuery::COLOR col);
void dumpPerson(PersonQuery::Person p);
void dumpDB(PersonQuery::Possibles *db);
#endif


/*
 *
 *  FUNCTION NAME:       PersonQuery_i
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *     Constructor for Implementation: PersonQuery_i
 *
 */

PersonQuery_i::PersonQuery_i ()
{
  PersonQuery::Possibles *tmp;
  PersonQuery::Person *data;
  CORBA::ULong entry_count;

  entry_count = init_db_buffer(&data);
  tmp = new PersonQuery::Possibles (entry_count, entry_count, data, CORBA_TRUE);
  this->DB = *tmp;
  delete tmp;
#ifdef DEBUG
  dumpDB(&this->DB);
#endif
}

/*
 *
 *  FUNCTION NAME:       ~PersonQuery_i
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *     Destructor for Implementation: PersonQuery_i
 *
 */

PersonQuery_i::~PersonQuery_i ()
{
}

/*
 * Non-CORBA additional implementation functions
 */

//
// The Match functions must handle two cases:  either they are called to
// find entries that match only the specific criterium (like the name), or
// they are called in conjunction with another Match function to handle
// multiple criteria (like name and hair color).
//
// The 'must_match' flag specifies whether this match must match exactly
// (for example, the name field in the database entry must exactly match
// the PersonQuery::Person name field.  This is the case if 'must_match'
// is TRUE.
//
// However, when 'must_match' is FALSE, then the match has two possible
// cases which satisfy the search criteria.  If the Match function has been
// called as part of a multiple item search, then the search criteria may
// include "don't care" values for some items.  This is how a match is done
// for a query which specifies more than one criterium; criteria not explicitly
// requested contain "don't care" values.
//
// So, when 'must_match' is FALSE, then both an exact match or a don't care
// will report the match as TRUE.
//

int  
PersonQuery_i::MatchName(const PersonQuery::Person *in,
                         PersonQuery::Person *entry,
                         int must_match)
{
    int ret_val = FALSE;

    if (must_match)
       ret_val = (strlen(in->name.in()) > 0) &&
                 (strcmp(in->name.in(), entry->name.in()) == 0);
    else ret_val = (strlen(in->name.in()) == 0) ||
                   (strcmp(in->name.in(), entry->name.in()) == 0);

    return ret_val;
}

int  
PersonQuery_i::MatchAddress(const PersonQuery::Person *in, 
                            PersonQuery::Person *entry,
                            int must_match)
{
    int ret_val = FALSE;

    int dont_care = FALSE;
    int exact_match = FALSE;

    if ( (in->addr.number == 0) &&
         (strlen(in->addr.street.in()) == 0) &&
         (strlen(in->addr.town.in()) == 0) &&
         (strlen(in->addr.state.in()) == 0) &&
         (strlen(in->addr.country.in()) == 0) )
      dont_care = TRUE;

    if ( (in->addr.number == entry->addr.number) &&
         (strcmp(in->addr.street.in(), entry->addr.street.in()) == 0) &&
         (strcmp(in->addr.town.in(), entry->addr.town.in()) == 0) &&
         (strcmp(in->addr.state.in(), entry->addr.state.in()) == 0) &&
         (strcmp(in->addr.country.in(), entry->addr.country.in()) == 0) )
      exact_match = TRUE;

    if (must_match)
        ret_val = (!dont_care) && exact_match;
    else ret_val = dont_care || exact_match;

    return ret_val;
}

int  
PersonQuery_i::MatchSS(const PersonQuery::Person *in,
                         PersonQuery::Person *entry,
                         int must_match)
{
    int ret_val = FALSE;

    if (must_match)
       ret_val = (strlen(in->ss.in()) > 0) &&
                 (strcmp(in->ss.in(), entry->ss.in()) == 0);
    else ret_val = (strlen(in->ss.in()) == 0) ||
                   (strcmp(in->ss.in(), entry->ss.in()) == 0);

    return ret_val;
}

int  
PersonQuery_i::MatchSex(const PersonQuery::Person *in, 
                        PersonQuery::Person *entry,
                        int must_match)
{
    int ret_val = FALSE;
    
    if (must_match)
       ret_val = (in->sex != 0) && (in->sex == entry->sex);
    else ret_val = (in->sex == 0) || (in->sex == entry->sex);

    return ret_val; 
}

int  
PersonQuery_i::MatchAge(const PersonQuery::Person *in, 
                        PersonQuery::Person *entry,
                        int must_match)
{
    int ret_val = FALSE;
    
    if (must_match)
       ret_val = (in->age != 0) && (in->age == entry->age);
    else ret_val = (in->age == 0) || (in->age == entry->age);

    return ret_val; 
}

int  
PersonQuery_i::MatchMarriage(const PersonQuery::Person *in, 
                        PersonQuery::Person *entry,
                        int must_match)
{
    int ret_val = FALSE;
    
    if (must_match)
       ret_val = (in->mar != 0) && (in->mar == entry->mar);
    else ret_val = (in->mar == 0) || (in->mar == entry->mar);

    return ret_val; 
}

int  
PersonQuery_i::MatchHobby(const PersonQuery::Person *in, 
                        PersonQuery::Person *entry,
                        int must_match)
{
    int ret_val = FALSE;
    
    if (must_match)
       ret_val = (in->rec != 0) && (in->rec == entry->rec);
    else ret_val = (in->rec == 0) || (in->rec == entry->rec);

    return ret_val; 
}

int  
PersonQuery_i::Matchdob(const PersonQuery::Person *in, 
                        PersonQuery::Person *entry,
                        int must_match)
{
    int  ret_val = FALSE;

    int  dont_care = FALSE;
    int  exact_match = FALSE;

    if ((in->dob.month == PersonQuery::Empty) &&
        (in->dob.day  == 0) &&
        (in->dob.year == 0))
       dont_care = TRUE;

    if ((in->dob.month == entry->dob.month) &&
        (in->dob.day == entry->dob.day) &&
        (in->dob.year == entry->dob.year)) 
       exact_match = TRUE;

    if (must_match)
       ret_val = (!dont_care) && exact_match;
    else ret_val = dont_care || exact_match;

    return ret_val; 
}

int  
PersonQuery_i::MatchHt(const PersonQuery::Person *in, 
                       PersonQuery::Person *entry,
                       int must_match)
{
    int  ret_val = FALSE;

    if (must_match)
       ret_val = (in->ht != 0) && (in->ht == entry->ht);
    else ret_val = (in->ht == 0) || (in->ht == entry->ht);

    return ret_val; 
}

int  
PersonQuery_i::MatchWt(const PersonQuery::Person *in, 
                       PersonQuery::Person *entry,
                       int must_match)
{
    int ret_val = FALSE;

    if (must_match)
       ret_val = (in->wt != 0) && (in->wt == entry->wt);
    else ret_val = (in->wt == 0) || (in->wt == entry->wt);

    return ret_val; 
}

int  
PersonQuery_i::MatchHair(const PersonQuery::Person *in, 
                         PersonQuery::Person *entry,
                         int must_match)
{
    int ret_val = FALSE;

    if (must_match)
       ret_val = (in->hair != PersonQuery::dontcare) &&
                 (in->hair == entry->hair);
    else ret_val = (in->hair == PersonQuery::dontcare) ||
                   (in->hair == entry->hair);

    return ret_val; 
}

int  
PersonQuery_i::MatchEye(const PersonQuery::Person *in, 
                        PersonQuery::Person *entry,
                        int must_match)
{
    int ret_val = FALSE;

    if (must_match)
       ret_val = (in->eyes != PersonQuery::dontcare) &&
                 (in->eyes == entry->eyes);
    else ret_val = (in->eyes == PersonQuery::dontcare) ||
                   (in->eyes == entry->eyes);

    return ret_val; 
}

int  
PersonQuery_i::MatchSkin(const PersonQuery::Person *in, 
                         PersonQuery::Person *entry,
                         int must_match)
{
    int ret_val = FALSE;

    if (must_match)
       ret_val = (in->skin != PersonQuery::dontcare) &&
                 (in->skin == entry->skin);
    else ret_val = (in->skin == PersonQuery::dontcare) ||
                   (in->skin == entry->skin);

    return ret_val; 
}

int
PersonQuery_i::MatchOther(const PersonQuery::Person *in, 
                          PersonQuery::Person *entry,
                          int must_match)
{
    int ret_val = FALSE;

    if (must_match)
       ret_val = (in->other != PersonQuery::dont_care) &&
                 (in->other == entry->other);
    else ret_val = (in->other == PersonQuery::dont_care) ||
                   (in->other == entry->other);

    return ret_val;
}

//
// The "Count functions
//
// These functions count the number of database entries which "Match" the
// search criteria. CountMatches handles matches with multiple criteria; the
// other "Count" functions all handle a single criterium match.
//
// These functions only count, they make no attempted to tag entries that
// matched.
//
short 
PersonQuery_i::CountMatches(const PersonQuery::Person *in)
{
    /*
     * this function counts the number of entries which match multiple
     * criteria.  It counts a single entry in the database, as long as
     * the criteria either match the database entry or contain
     * "don't care" values.
     */
    CORBA::ULong i;
    short        count = 0;

    for (i = 0; i < this->DB.length(); i++)
    {
       if ( (MatchName(in, &this->DB[i], FALSE)) &&
            (MatchAddress(in, &this->DB[i], FALSE)) &&
            (MatchSS(in, &this->DB[i], FALSE)) &&
            (MatchSex(in, &this->DB[i], FALSE)) &&
            (MatchAge(in, &this->DB[i], FALSE)) &&
            (MatchMarriage(in, &this->DB[i], FALSE)) &&
            (MatchHobby(in, &this->DB[i], FALSE)) &&
            (Matchdob(in, &this->DB[i], FALSE)) &&
            (MatchHt(in, &this->DB[i], FALSE)) &&
            (MatchWt(in, &this->DB[i], FALSE)) &&
            (MatchHair(in, &this->DB[i], FALSE)) &&
            (MatchEye(in, &this->DB[i], FALSE)) &&
            (MatchSkin(in, &this->DB[i], FALSE)) &&
            (MatchOther(in, &this->DB[i], FALSE)) )
             count++;         
    }
    return count;
}

short
PersonQuery_i::CountByName(const char *name)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.name = name;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchName(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByAddress(PersonQuery::Address addr)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.addr = addr;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchAddress(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountBySS(const char *ss)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.ss = ss;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchSS(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountBySex(PersonQuery::SEX sex)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.sex = sex;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchSex(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByAge(short age)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.age = age;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchAge(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByMarriage(PersonQuery::MARRIAGE mar)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.mar = mar;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchMarriage(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByHobby(PersonQuery::HOBBIES rec)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.rec = rec;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchHobby(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountBydob(PersonQuery::Date date)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.dob = date;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (Matchdob(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByHt(short ht)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.ht = ht;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchHt(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByWt(long wt)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.wt = wt;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchWt(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByHair(PersonQuery::COLOR hair)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.hair = hair;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchHair(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByEye(PersonQuery::COLOR eyes)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.eyes = eyes;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchEye(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountBySkin(PersonQuery::COLOR skin)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.skin = skin;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchSkin(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

short
PersonQuery_i::CountByOther(PersonQuery::MARKINGS other)
{
    CORBA::ULong i;
    short        count = 0;
    PersonQuery::Person per;

    per.other = other;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchOther(&per, &this->DB[i], TRUE))
         count++;         
    }
    return count;
}

//
// The "Pull" functions.
//
// These functions find the entries in the database which match the
// search criteria and copy them to the PersonQuery::Person list.
// The list has already been allocated with enough entries to hold
// the number of matches that will be found.  (The methods that call
// these functions are responsible for having counted and allocated
// appropriately before calling these functions.)
//
void
PersonQuery_i::PullByName(const char * name,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.name = name;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchName(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}

void
PersonQuery_i::PullByAddress(PersonQuery::Address addr,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.addr = addr;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchAddress(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullBySS(const char * ss,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.ss = ss;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchSS(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullBySex(PersonQuery::SEX sex,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.sex = sex;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchSex(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByAge(short age,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.age = age;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchAge(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByMarriage(PersonQuery::MARRIAGE mar,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.mar = mar;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchMarriage(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByHobby(PersonQuery::HOBBIES rec,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.rec = rec;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchHobby(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullBydob( PersonQuery::Date dob,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.dob = dob;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (Matchdob(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByHt( short ht,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.ht = ht;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchHt(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByWt( long wt,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.wt = wt;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchWt(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByHair(PersonQuery::COLOR hair,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.hair = hair;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchHair(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByEye(PersonQuery::COLOR eyes,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.eyes = eyes;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchEye(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullBySkin(PersonQuery::COLOR skin,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.skin = skin;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchSkin(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}


void
PersonQuery_i::PullByOther(PersonQuery::MARKINGS other,
                          PersonQuery::Person *list)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;
    PersonQuery::Person per;

    per.other = other;
    for (i = 0; i < this->DB.length(); i++)
    {
       if (MatchOther(&per, &this->DB[i], TRUE))
       {
          list[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}

void
PersonQuery_i::PullMatches(const PersonQuery::Person *in,
                           PersonQuery::Person *List)
{
    CORBA::ULong i;
    CORBA::ULong new_index = 0;

    for (i = 0; i < this->DB.length(); i++)
    {
       if ( (MatchName(in, &this->DB[i], FALSE)) &&
            (MatchAddress(in, &this->DB[i], FALSE)) &&
            (MatchSS(in, &this->DB[i], FALSE)) &&
            (MatchSex(in, &this->DB[i], FALSE)) &&
            (MatchAge(in, &this->DB[i], FALSE)) &&
            (MatchMarriage(in, &this->DB[i], FALSE)) &&
            (MatchHobby(in, &this->DB[i], FALSE)) &&
            (Matchdob(in, &this->DB[i], FALSE)) &&
            (MatchHt(in, &this->DB[i], FALSE)) &&
            (MatchWt(in, &this->DB[i], FALSE)) &&
            (MatchHair(in, &this->DB[i], FALSE)) &&
            (MatchEye(in, &this->DB[i], FALSE)) &&
            (MatchSkin(in, &this->DB[i], FALSE)) &&
            (MatchOther(in, &this->DB[i], FALSE)) )
       {
          List[new_index] = this->DB[i];
          new_index++;
       }
    }
    return;
}




//
// The following functions are all implementations of the PersonQuery
// interface operations.  They are called by the POA skeleton to service
// the CORBA requests invoked by the PersonQuery client on the PersonQuery
// interface.
//
/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPerson
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPerson.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPerson (
     const PersonQuery::Person & who,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountMatches(&who);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
            PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
         throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullMatches(&who, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
         throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
         throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByName
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByName.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByName (
    const char * name,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByName(name);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
             PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByName(name, the_data);


       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByAddress
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByAddress.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByAddress (
     const PersonQuery::Address & addr,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByAddress(addr);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
            PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByAddress(addr, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
    return _method_result;
}

/*
 *
 *  FUNCTION NAME:      PersonQuery_i::findPersonBySS
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonBySS.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonBySS (
    const char * ss,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountBySS(ss);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
            PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullBySS(ss, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }

    return _method_result;
}

/*
 *
 *  FUNCTION NAME:      PersonQuery_i::findPersonBySex
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonBySex.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonBySex (
    PersonQuery::SEX sex,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountBySex(sex);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
            PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullBySex(sex, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }

    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByAge
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByAge.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByAge (
    CORBA::Short age,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByAge(age);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
           PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByAge(age, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME:      PersonQuery_i::findPersonByMarriage
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByMarriage.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByMarriage (
    PersonQuery::MARRIAGE mar,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByMarriage(mar);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
           PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByMarriage(mar, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}


/*
 *
 *  FUNCTION NAME:      PersonQuery_i::findPersonByHobby
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByHobby.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByHobby(
    PersonQuery::HOBBIES hob,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByHobby(hob);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
           PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByHobby(hob, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}


/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonBydob
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonBydob.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonBydob (
     const PersonQuery::Date & dob,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountBydob(dob);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
           PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullBydob(dob, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByHeight
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByHeight.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByHeight (
    CORBA::Short ht,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByHt(ht);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
            PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByHt(ht, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByWeight
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByWeight.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByWeight (
    CORBA::Long wt,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByWt(wt);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
               PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByWt(wt, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByHairColor
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByHairColor.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByHairColor (
    PersonQuery::COLOR col,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByHair(col);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
              PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByHair(col, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonBySkinColor
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonBySkinColor.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonBySkinColor (
    PersonQuery::COLOR col,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountBySkin(col);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
            PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullBySkin(col, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByEyeColor
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByEyeColor.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByEyeColor (
    PersonQuery::COLOR col,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByEye(col);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
              PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByEye(col, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::findPersonByOther
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for findPersonByOther.
 *       (Implementation : PersonQuery_i)
 *
 */


CORBA::Boolean PersonQuery_i::findPersonByOther (
    PersonQuery::MARKINGS other,
    PersonQuery::Possibles_out hits)
{
    CORBA::Boolean _method_result = (CORBA::Boolean) 0;

    // Count how many database entries satisfy this query.
    short cnt = CountByOther(other);
    if (cnt > 0)
    {
       // allocate memory to return the found entries.
       PersonQuery::Person *the_data = 
            PersonQuery::Possibles::allocbuf((CORBA::ULong)cnt);
       if (!the_data)
          throw CORBA::NO_MEMORY();

       // copy the entries which match.
       PullByOther(other, the_data);

       // allocate a sequence to return the found entries
       hits = new PersonQuery::Possibles (cnt, cnt, the_data, CORBA_TRUE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
       _method_result = CORBA_TRUE;
    }
    else {
       // no entries satisfy the search criteria; CORBA requires a
       // non-NULL sequence to return.
       hits = new PersonQuery::Possibles (0, 0, NULL, CORBA_FALSE);
       if (!hits.ptr())
          throw CORBA::NO_MEMORY();
    }
     
    return _method_result;
}

/*
 *
 *  FUNCTION NAME: 	PersonQuery_i::exit
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for exit.
 *       (Implementation : PersonQuery_i)
 *
 */


void PersonQuery_i::exit ()
{
    return ;
}


/*
 *
 *  FUNCTION NAME:       QueryFactory_i
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *     Constructor for Implementation: QueryFactory_i
 *
 */

QueryFactory_i::QueryFactory_i ()
{
}

/*
 *
 *  FUNCTION NAME:       ~QueryFactory_i
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *     Destructor for Implementation: QueryFactory_i
 *
 */

QueryFactory_i::~QueryFactory_i ()
{
}

/*
 *
 *  FUNCTION NAME: 	QueryFactory_i::createQuery
 *
 *  FUNCTIONAL DESCRIPTION:
 *
 *      Method function for createQuery.
 *       (Implementation : QueryFactory_i)
 *
 */


PersonQuery_ptr QueryFactory_i::createQuery (
    const char * name)
{
    PersonQuery_ptr _method_result  = PersonQuery::_nil();
    CORBA::Object_ptr   PersonObjRef = CORBA::Object::_nil();

    try
    {
        // Create  object reference and register with Finder
        //
        // TP::create_object_reference() throws:
        //                      TobjS::IllegalInterface
        //                      TobjS::InvalidInterface
        //                      TobjS::InvalidObjectId

        PersonObjRef = TP::create_object_reference (
            PersonQuery::_get_interface_name (),       // Interface Name
            name,              // Unique Object Id (string)
            0 );                        // Criteria

        if ( CORBA::is_nil ( PersonObjRef ) )
            return _method_result;

        _method_result = PersonQuery::_narrow ( PersonObjRef );
        CORBA::release ( PersonObjRef );
    }

    catch (...)
    {
        // TP::userlog allows messages to be written to the ULOG file

        TP::userlog (
           "ERROR: exception raised in QueryFactory_i::createQuery ()" );
        CORBA::release ( PersonObjRef );
        return _method_result;
    }

    return _method_result;
}


//
// This section contains the database structure definition and the
// raw data.  Note that a database entry is a PersonQuery::Person data
// structure, however, since PersonQuery::Person contains memory 
// managing fields (such as CORBA::String_var), the static object which 
// holds the raw data cannot use the PersonQuery::Person type to define
// its structure.  So, there is a typedef, which mirrors the
// PersonQuery::Person structure, but uses non-memory managing fields to
// hold the static data.
//
// At server startup, the actual database is constructed using the
// PersonQuery::Person type.  This way, the "Pull" functions can easily
// copy an entry for return to the client.
//
typedef struct db_stuff {
   char *  name;
   struct {
      short  number;
      char   *street;
      char   *town;
      char   *state;
      char   *country;
   } addr;
   char *  ss;
   PersonQuery::SEX sex;
   short   age;
   PersonQuery::MARRIAGE mar;
   PersonQuery::HOBBIES rec;
   struct {
      PersonQuery::MONTHS  month;
      short  day;
      short  year;
   }  dob;
   short     ht;
   long      wt;
   PersonQuery::COLOR hair;
   PersonQuery::COLOR eyes;
   PersonQuery::COLOR skin;
   PersonQuery::MARKINGS other;
}  db_struct;   

#define DB_SIZE 31
static db_struct db_data[DB_SIZE] = 
{
  {(char *)"FRED MURTZ", 
           {436, (char *)"AMHERST ST.", 
                 (char *)"NASHUA", (char *)"NH", (char *)"USA"}, 
           (char *)"999-99-9999", PersonQuery::male, 75,
           PersonQuery::married, PersonQuery::tv,
           {PersonQuery::Jan, 1, 1924}, 
           62, 115, 
           PersonQuery::black, PersonQuery::hazel, 
           PersonQuery::black, PersonQuery::scar
  },
  {(char *)"ALISTER LANCASHIRE", 
           {3, (char *)"PENNY LANE",
               (char *)"LONDON", (char *)"GB", (char *)"UK"}, 
           (char *)"999-99-9999", PersonQuery::cant_tell, 85,
           PersonQuery::single, PersonQuery::stamps,
           {PersonQuery::Nov, 25, 1913}, 
           32, 57, 
           PersonQuery::unknown, PersonQuery::blue, 
           PersonQuery::white, PersonQuery::missing_limb
  },
  {(char *)"LAMAR MANDELA",  
           {2456, (char *)"PINE ST.",
                  (char *) "MILWAUKEE", (char *)"WI", (char *)"USA"}, 
           (char *)"123-45-6789", PersonQuery::male, 15,
           PersonQuery::single, PersonQuery::who_cares,
           {PersonQuery::Apr, 15, 1984}, 
           68, 175, 
           PersonQuery::green, PersonQuery::black, 
           PersonQuery::yellow, PersonQuery::scar
  },
  {(char *)"DOTTY ALEXANDER", 
           {1, (char *)"PRIDE ST.", 
                  (char *)"FOX HOLLOW", (char *)"TN", (char *)"USA"}, 
           (char *)"000-00-0002", PersonQuery::female, 143,
           PersonQuery::single, PersonQuery::rocks,
           {PersonQuery::May, 1, 1856}, 
           48, 56, 
           PersonQuery::blue, PersonQuery::blue, 
           PersonQuery::white, PersonQuery::none
  },
  {(char *)"STEPHANIE CURTIS", 
           {4537, (char *)"PARK AVE.", 
                  (char *)"NEW YORK", (char *)"NY", (char *)"USA"}, 
           (char *)"000-00-0002", PersonQuery::female, 3,
           PersonQuery::single, PersonQuery::tv,
           {PersonQuery::Jan, 31, 1996}, 
           36, 31, 
           PersonQuery::black, PersonQuery::black, 
           PersonQuery::black, PersonQuery::none
  },
  {(char *)"PAMELA CURTIS", 
           {4537, (char *)"PARK AVE.", 
                  (char *)"NEW YORK", (char *)"NY", (char *)"USA"}, 
           (char *)"000-00-3451", PersonQuery::female, 23,
           PersonQuery::divorced, PersonQuery::who_cares,
           {PersonQuery::Jan, 31, 1976}, 
           62, 103, 
           PersonQuery::black, PersonQuery::hazel, 
           PersonQuery::black, PersonQuery::scar
  },
  {(char *)"PAUL MOSKOWITZ", 
           {13206, (char *)"LAKE MICHIGAN DR.", 
                  (char *)"CHICAGO", (char *)"IL", (char *)"USA"}, 
           (char *)"333-00-3451", PersonQuery::male, 56,
           PersonQuery::divorced, PersonQuery::tv,
           {PersonQuery::Oct, 1, 1943}, 
           78, 1000, 
           PersonQuery::red, PersonQuery::green, 
           PersonQuery::yellow, PersonQuery::tattoo
  },
  {(char *)"CRIMINAL WASTE", 
           {25506, (char *)"RODEO DR.", 
                  (char *)"BEVERLY HILLS", (char *)"CA", (char *)"USA"}, 
           (char *)"000-00-5000", PersonQuery::male, 18,
           PersonQuery::divorced, PersonQuery::tv,
           {PersonQuery::Feb, 28, 1981}, 
           72, 105, 
           PersonQuery::blue, PersonQuery::gray, 
           PersonQuery::white, PersonQuery::tattoo
  },
  {(char *)"SALLY SMALL", 
           {3, (char *)"PRETTY POND RD.", 
                  (char *)"SOUTHEAST HARBOR", (char *)"ME", (char *)"USA"}, 
           (char *)"321-00-5000", PersonQuery::female, 45,
           PersonQuery::divorced, PersonQuery::tv,
           {PersonQuery::Aug, 23, 1954}, 
           48, 75, 
           PersonQuery::white, PersonQuery::hazel, 
           PersonQuery::brown, PersonQuery::none
  },
  {(char *)"CAROLINE MANYJARS", 
           {45, (char *)"YOYODINE ST.", 
                  (char *)"WAPPINGER FALLS", (char *)"NY", (char *)"USA"}, 
           (char *)"321-45-5000", PersonQuery::female, 16,
           PersonQuery::single, PersonQuery::weaving,
           {PersonQuery::Jan, 1, 1983}, 
           64, 120, 
           PersonQuery::blue, PersonQuery::hazel, 
           PersonQuery::red, PersonQuery::none
  },
  {(char *)"CAROLINE MANYBELLS", 
           {45, (char *)"YOYODINE ST.", 
                  (char *)"WAPPINGER FALLS", (char *)"NY", (char *)"USA"}, 
           (char *)"621-45-5001", PersonQuery::female, 16,
           PersonQuery::single, PersonQuery::weaving,
           {PersonQuery::Feb, 1, 1983}, 
           64, 135, 
           PersonQuery::blue, PersonQuery::hazel, 
           PersonQuery::red, PersonQuery::none
  },
  {(char *)"CAROLINE SMALLBERRIES", 
           {45, (char *)"YOYODINE ST.", 
                  (char *)"WAPPINGER FALLS", (char *)"NY", (char *)"USA"}, 
           (char *)"621-45-5002", PersonQuery::female, 16,
           PersonQuery::single, PersonQuery::weaving,
           {PersonQuery::Mar, 1, 1983}, 
           63, 130, 
           PersonQuery::blue, PersonQuery::hazel, 
           PersonQuery::red, PersonQuery::none
  },
  {(char *)"PRETTY PENNY", 
           {45, (char *)"YOYODINE ST.", 
                  (char *)"WAPPINGER FALLS", (char *)"NY", (char *)"USA"}, 
           (char *)"456-45-9999", PersonQuery::female, 16,
           PersonQuery::single, PersonQuery::rocks,
           {PersonQuery::Oct, 31, 1983}, 
           64, 115, 
           PersonQuery::white, PersonQuery::blue, 
           PersonQuery::white, PersonQuery::none
  },
  {(char *)"JUSTIN POWERS", 
           {436, (char *)"AMHERST ST.", 
                  (char *)"ST. LOUIS", (char *)"MO", (char *)"USA"}, 
           (char *)"123-45-9999", PersonQuery::male, 24,
           PersonQuery::single, PersonQuery::rocks,
           {PersonQuery::Dec, 1, 1975}, 
           50, 567, 
           PersonQuery::red, PersonQuery::hazel, 
           PersonQuery::white, PersonQuery::missing_limb
  },
  {(char *)"BLANCHE BOUGANVILLE", 
           {24, (char *)"MARKET ST.", 
                  (char *)"NEW ORLEANS", (char *)"LA", (char *)"USA"}, 
           (char *)"000-00-1000", PersonQuery::female, 75,
           PersonQuery::single, PersonQuery::rocks,
           {PersonQuery::Jul, 2, 1924}, 
           46, 67, 
           PersonQuery::black, PersonQuery::blue, 
           PersonQuery::black, PersonQuery::scar
  },
  {(char *)"SAMANTHA DOGGER", 
           {7831, (char *)"TELEVISION ST.", 
                  (char *)"LOS ANGELES", (char *)"CA", (char *)"USA"}, 
           (char *)"768-12-1000", PersonQuery::female, 35,
           PersonQuery::divorced, PersonQuery::tv,
           {PersonQuery::Apr, 20, 1964}, 
           72, 125, 
           PersonQuery::brown, PersonQuery::hazel, 
           PersonQuery::brown, PersonQuery::none
  },
  {(char *)"STEPHANIE POWERFUL", 
           {1, (char *)"PERSONALITY ST.", 
                  (char *)"NEW YORK", (char *)"NY", (char *)"USA"}, 
           (char *)"768-44-5678", PersonQuery::female, 32,
           PersonQuery::divorced, PersonQuery::tv,
           {PersonQuery::Oct, 10, 1967}, 
           64, 115, 
           PersonQuery::blue, PersonQuery::violet, 
           PersonQuery::green, PersonQuery::tattoo
  },
  {(char *)"PAUL REMORSE", 
           {2598, (char *)"MOUNTAIN WAY", 
                  (char *)"PORTLAND", (char *)"OR", (char *)"USA"}, 
           (char *)"946-44-6285", PersonQuery::cant_tell, 44,
           PersonQuery::divorced, PersonQuery::tv,
           {PersonQuery::Dec, 31, 1955}, 
           77, 300, 
           PersonQuery::unknown, PersonQuery::black, 
           PersonQuery::black, PersonQuery::scar
  },
  {(char *)"SIGMUND VERSIMILITUDE", 
           {14, (char *)"STEVEN KING DR.", 
                  (char *)"PORTLAND", (char *)"MA", (char *)"USA"}, 
           (char *)"000-00-0000", PersonQuery::male, 144,
           PersonQuery::not_known, PersonQuery::photo,
           {PersonQuery::Mar, 1, 1855}, 
           67, 140, 
           PersonQuery::unknown, PersonQuery::black, 
           PersonQuery::black, PersonQuery::none
  },
  {(char *)"BABY DOLL", 
           {3, (char *)"PRETTY LANE", 
                  (char *)"NASHUA", (char *)"NH", (char *)"USA"}, 
           (char *)"888-88-8888", PersonQuery::female, 1,
           PersonQuery::single, PersonQuery::stamps,
           {PersonQuery::May, 18, 1998}, 
           12, 15, 
           PersonQuery::red, PersonQuery::blue, 
           PersonQuery::white, PersonQuery::none
  },
  {(char *)"BARBARA KUTCHIE", 
           {1783, (char *)"MANHATTAN RD.", 
                  (char *)"GRAND RAPIDS", (char *)"MI", (char *)"USA"}, 
           (char *)"777-77-7777", PersonQuery::female, 86,
           PersonQuery::single, PersonQuery::stamps,
           {PersonQuery::Jun, 30, 1913}, 
           64, 115, 
           PersonQuery::white, PersonQuery::blue, 
           PersonQuery::white, PersonQuery::none
  },
  {(char *)"PENELOPE JOHNSON", 
           {1783, (char *)"MANHATTAN RD.", 
                  (char *)"GRAND RAPIDS", (char *)"MI", (char *)"USA"}, 
           (char *)"666-66-6666", PersonQuery::female, 49,
           PersonQuery::single, PersonQuery::weaving,
           {PersonQuery::Mar, 15, 1950}, 
           64, 140, 
           PersonQuery::brown, PersonQuery::brown, 
           PersonQuery::white, PersonQuery::none
  },
  {(char *)"BOB WHITE", 
           {17, (char *)"NORTH CHELMSFORD RD.", 
                  (char *)"CHELMSFORD", (char *)"MA", (char *)"USA"}, 
           (char *)"555-55-5555", PersonQuery::male, 62,
           PersonQuery::married, PersonQuery::weaving,
           {PersonQuery::Nov, 26, 1937}, 
           62, 315, 
           PersonQuery::black, PersonQuery::green, 
           PersonQuery::white, PersonQuery::missing_limb
  },
  {(char *)"CALLIE MURTZ", 
           {4364, (char *)"FOOTHILLS RD.", 
                  (char *)"BOULDER", (char *)"CO", (char *)"USA"}, 
           (char *)"444-44-4444", PersonQuery::female, 32,
           PersonQuery::married, PersonQuery::weaving,
           {PersonQuery::Mar, 11, 1967}, 
           72, 175, 
           PersonQuery::red, PersonQuery::blue, 
           PersonQuery::white, PersonQuery::tattoo
  },
  {(char *)"FANCY PANTS", 
           {13, (char *)"BOWERY ST.", 
                  (char *)"NEW YORK", (char *)"NY", (char *)"USA"}, 
           (char *)"555-44-4444", PersonQuery::female, 13,
           PersonQuery::not_known, PersonQuery::who_cares,
           {PersonQuery::May, 21, 1986}, 
           50, 175, 
           PersonQuery::red, PersonQuery::green, 
           PersonQuery::white, PersonQuery::scar
  },
  {(char *)"PERSON FORMERLY KNOWN AS PETER", 
           {13, (char *)"BOWERY ST.", 
                  (char *)"NEW YORK", (char *)"NY", (char *)"USA"}, 
           (char *)"xxx-xx-xxxx", PersonQuery::cant_tell, 23,
           PersonQuery::not_known, PersonQuery::who_cares,
           {PersonQuery::Jul, 31, 1972}, 
           70, 115, 
           PersonQuery::blue, PersonQuery::violet, 
           PersonQuery::brown, PersonQuery::tattoo
  },
  {(char *)"PETER GONZALEZ", 
           {1, (char *)"WINDY RD.", 
                  (char *)"WINDYVILLE", (char *)"MS", (char *)"USA"}, 
           (char *)"111-11-1111", PersonQuery::male, 55,
           PersonQuery::not_known, PersonQuery::tv,
           {PersonQuery::Oct, 4, 1944}, 
           74, 413, 
           PersonQuery::gray, PersonQuery::violet, 
           PersonQuery::brown, PersonQuery::tattoo
  },
  {(char *)"FRED MURTZ", 
           {9436, (char *)"CATTLE DR.", 
                  (char *)"SAN ANTONIO", (char *)"TX", (char *)"USA"}, 
           (char *)"111-222-3333", PersonQuery::male, 14,
           PersonQuery::single, PersonQuery::tv,
           {PersonQuery::Sep, 22, 1985}, 
           75, 250, 
           PersonQuery::gray, PersonQuery::blue, 
           PersonQuery::yellow, PersonQuery::none
  },
  {(char *)"FRED MURTZ", 
           {5555, (char *)"WIDE BLVD.", 
                  (char *)"BORINGVILLE", (char *)"NJ", (char *)"USA"}, 
           (char *)"333-22-1111", PersonQuery::male, 25,
           PersonQuery::single, PersonQuery::tv,
           {PersonQuery::Jun, 13, 1964}, 
           68, 516, 
           PersonQuery::brown, PersonQuery::brown, 
           PersonQuery::green, PersonQuery::missing_limb
  },
  {(char *)"BETTY WONDERFUL", 
           {1, (char *)"COLD RD.", 
                  (char *)"HAPPYVILLE", (char *)"MT", (char *)"USA"}, 
           (char *)"000-00-0003", PersonQuery::female, 104,
           PersonQuery::single, PersonQuery::weaving,
           {PersonQuery::Jan, 19, 1895}, 
           62, 175, 
           PersonQuery::white, PersonQuery::gray, 
           PersonQuery::red, PersonQuery::none
  },
  {(char *)"JESUS HERNANDEZ", 
           {18, (char *)"LOCO LN.", 
                  (char *)"CIUDAD JUAREZ", (char *)"JUAREZ", (char *)"MX"}, 
           (char *)"999-00-0003", PersonQuery::male, 33,
           PersonQuery::married, PersonQuery::swim,
           {PersonQuery::Oct, 31, 1966}, 
           72, 175, 
           PersonQuery::black, PersonQuery::black, 
           PersonQuery::brown, PersonQuery::none
  }
};

//
// function to initialize the local database.  It copies the static data
// into a list of PersonQuery::Person objects.
//
static CORBA::ULong init_db_buffer(PersonQuery::Person **data)
{
  CORBA::ULong i;
  PersonQuery::Person *tmp;

  tmp = PersonQuery::Possibles::allocbuf((CORBA::ULong)DB_SIZE);

  for (i = 0; i < (CORBA::ULong)DB_SIZE; i++)
    {
      tmp[i].name        = CORBA::string_dup(db_data[i].name);
      tmp[i].addr.number = db_data[i].addr.number;
      tmp[i].addr.street = CORBA::string_dup(db_data[i].addr.street);
      tmp[i].addr.town   = CORBA::string_dup(db_data[i].addr.town);
      tmp[i].addr.state  = CORBA::string_dup(db_data[i].addr.state);
      tmp[i].addr.country= CORBA::string_dup(db_data[i].addr.country);
      tmp[i].ss         = CORBA::string_dup(db_data[i].ss);
      tmp[i].sex         = db_data[i].sex;
      tmp[i].age         = db_data[i].age;
      tmp[i].mar         = db_data[i].mar;
      tmp[i].rec         = db_data[i].rec;
      tmp[i].dob.month   = db_data[i].dob.month;
      tmp[i].dob.day     = db_data[i].dob.day;
      tmp[i].dob.year    = db_data[i].dob.year;
      tmp[i].ht          = db_data[i].ht;
      tmp[i].wt          = db_data[i].wt;
      tmp[i].hair        = db_data[i].hair;
      tmp[i].eyes        = db_data[i].eyes;
      tmp[i].skin        = db_data[i].skin;
      tmp[i].other       = db_data[i].other;
    }
  *data = tmp;
  return DB_SIZE;
}

//
// This section contains utility functions to help debug the implementation.
// The function dump specific fields of the database to standard out.
//
#ifdef DEBUG
void dumpHobby(PersonQuery::HOBBIES rec)
{
      switch (rec)
      {
         default:
           printf("ERROR: illegal hobby value: %d\n", rec);
           break;
         case PersonQuery::who_cares:
           printf("who_cares\n");
           break;
         case PersonQuery::rocks:
           printf("rock climbing\n");
           break;
         case PersonQuery::swim:
           printf("swimming\n");
           break;
         case PersonQuery::tv:
           printf("watching tv\n");
           break;
         case PersonQuery::stamps:
           printf("collecting stamps\n");
           break;
         case PersonQuery::photo:
           printf("photography\n");
           break;
         case PersonQuery::weaving:
           printf("weaving\n");
           break;
      }
}
void dumpMarriage(PersonQuery::MARRIAGE mar)
{
      switch (mar)
      {
         default:
           printf("ERROR: illegal marriage value: %d\n", mar);
           break;
         case PersonQuery::not_known:
           printf("not_known\n");
           break;
         case PersonQuery::single:
           printf("single\n");
           break;
         case PersonQuery::married:
           printf("married\n");
           break;
         case PersonQuery::divorced:
           printf("divorced\n");
           break;
      }
}
void dumpSex(PersonQuery::SEX sex)
{
      switch (sex)
      {
         default:
           printf("ERROR: illegal sex value: %d\n", sex);
           break;
         case PersonQuery::cant_tell:
           printf("cant_tell\n");
           break;
         case PersonQuery::male:
           printf("male\n");
           break;
         case PersonQuery::female:
           printf("female\n");
           break;
      }
}
void dumpOther(PersonQuery::MARKINGS other)
{
      switch (other)
      {
         default:
           printf("ERROR: illegal marking: %d\n", other);
           break;
         case PersonQuery::dont_care:
           printf("dont_care\n");
           break;
         case PersonQuery::tattoo:
           printf("tattoo\n");
           break;
         case PersonQuery::missing_limb:
           printf("missing_limb\n");
           break;
         case PersonQuery::scar:
           printf("scar\n");
           break;
         case PersonQuery::none:
           printf("none\n");
           break;
      }
}
void dumpColor(PersonQuery::COLOR col)
{
      switch (col)
      {
         default:
           printf("ERROR: illegal color: %d\n", col);
           break;
         case PersonQuery::white:
           printf("white\n");
           break;
         case PersonQuery::black:
           printf("black\n");
           break;
         case PersonQuery::red:
           printf("red\n");
           break;
         case PersonQuery::brown:
           printf("brown\n");
           break;
         case PersonQuery::green:
           printf("green\n");
           break;
         case PersonQuery::violet:
           printf("violet\n");
           break;
         case PersonQuery::blue:
           printf("blue\n");
           break;
         case PersonQuery::gray:
           printf("gray\n");
           break;
         case PersonQuery::unknown:
           printf("unknown\n");
           break;
         case PersonQuery::yellow:
           printf("yellow\n");
           break;
         case PersonQuery::hazel:
           printf("hazel\n");
           break;
         case PersonQuery::dontcare:
           printf("dontcare\n");
           break;
      }
}
void dumpPerson(PersonQuery::Person p)
{
      printf("\t\t\tname:  %s\n", p.name.in());
      printf("\t\t\taddr:  %d %s\n", p.addr.number, p.addr.street.in());
      printf("\t\t\t       %s %s %s\n", p.addr.town.in(), p.addr.state.in(), p.addr.country.in());
      printf("\t\t\tss:    %s\n", p.ss.in());
      printf("\t\t\tsex: ");
      dumpSex(p.sex);
      printf("\t\t\tage:   %d\n", p.age);
      printf("\t\t\tmarriage: ");
      dumpMarriage(p.mar);
      printf("\t\t\thobbies: ");
      dumpHobby(p.rec);
      printf("\t\t\tdob:   %d/%d/%d\n", p.dob.month, 
                                       p.dob.day, p.dob.year);
      printf("\t\t\tht:    %d inches\n", p.ht);
      printf("\t\t\twt:    %d pounds\n", p.wt);
      printf("\t\t\thair:  ");
      dumpColor(p.hair);
      printf("\t\t\teyes:  ");
      dumpColor(p.eyes);
      printf("\t\t\tskin:  ");
      dumpColor(p.skin);
      printf("\t\t\tother: ");
      dumpOther(p.other);
}
void dumpDB(PersonQuery::Possibles *db)
{
   CORBA::ULong i;
   printf ("Dumping service database....\n");
   if (db == NULL)
   {
     printf("ERROR:  database pointer is null\n");
     return;
   }

   printf ("\tmax: %ld\n", db->maximum());
   printf ("\tlen: %ld\n", db->length());
   PersonQuery::Person *entry = db->OBB__GetData();
   for (i = 0; i < db->length(); i++, entry++)
   {
      printf("\t\tentry:   %ld\n", i);
      dumpPerson(*entry);
   }
   return;
}
#endif
