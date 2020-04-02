//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// PersonQuery_i.h
//
// BEA Systems Inc. sample code.
// C++ implementation definitions for the C++ Interceptor sample application.
//
//--------------------------------------------------------------------
#ifndef _PersonQuery_i_h
#define _PersonQuery_i_h

#include "personquery_s.h"
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

//
// The following class definition is a servant which
// derives from the generated POA skeleton for the PersonQuery
// interface. It implements the PersonQuery interface.
//

class PersonQuery_i : public POA_PersonQuery {
    public:

        PersonQuery_i ();
        virtual ~PersonQuery_i();

   private:

//
// The following methods are local, that is, the PersonQuery client can
// not invoke upon them.  They are used by the OMG idl specified methods
// below to implement the PersonQuery interface.

	// Local database of data which is searched to satisfy a query.
        PersonQuery::Possibles  DB;

        // Count the number of DB entries which satisfy multiple
        // search criteria.
        short CountMatches   (const PersonQuery::Person *in);

        // Count the number of DB entries which satisfy a 
        // single search criterium.
        short CountByName    (const char *name);
        short CountByAddress (PersonQuery::Address addr);
        short CountBySS      (const char *ss);
        short CountBySex     (PersonQuery::SEX sex);
        short CountByAge     (short age);
        short CountByMarriage(PersonQuery::MARRIAGE mar);
        short CountByHobby   (PersonQuery::HOBBIES hob);
        short CountBydob     (PersonQuery::Date dob);
        short CountByHt      (short ht);
        short CountByWt      (long  wt);
        short CountByHair    (PersonQuery::COLOR hair);
        short CountByEye     (PersonQuery::COLOR eye);
        short CountBySkin    (PersonQuery::COLOR skin);
        short CountByOther   (PersonQuery::MARKINGS other);

        // Copy the DB entries which satisfy the single search criterium
        // into a sequence suitable for sending back to the client.
        void PullByName    (const char *name, 
                             PersonQuery::Person *list);
        void PullByAddress (PersonQuery::Address addr, 
                             PersonQuery::Person *list);
        void PullBySS      (const char *ss, 
                             PersonQuery::Person *list);
        void PullBySex     (PersonQuery::SEX sex, 
                             PersonQuery::Person *list);
        void PullByAge     (short age, 
                             PersonQuery::Person *list);
        void PullByMarriage(PersonQuery::MARRIAGE mar, 
                             PersonQuery::Person *list);
        void PullByHobby   (PersonQuery::HOBBIES mar, 
                             PersonQuery::Person *list);
        void PullBydob     (PersonQuery::Date dob, 
                             PersonQuery::Person *list);
        void PullByHt      (short ht, 
                             PersonQuery::Person *list);
        void PullByWt      (long  wt, 
                             PersonQuery::Person *list);
        void PullByHair    (PersonQuery::COLOR hair, 
                             PersonQuery::Person *list);
        void PullByEye     (PersonQuery::COLOR eye, 
                             PersonQuery::Person *list);
        void PullBySkin    (PersonQuery::COLOR skin, 
                             PersonQuery::Person *list);
        void PullByOther   (PersonQuery::MARKINGS other, 
                             PersonQuery::Person *list);

        // Copy the DB entries which satisfy multiple search criteria
        // into a sequence suitable for sending back to the client.
        void PullMatches   (const PersonQuery::Person *in,
                            PersonQuery::Person *list);


        // Compare a DB entry to the single search criterium.  Return
        // TRUE if there is a match, FALSE if there is not.
        int  MatchName    (const PersonQuery::Person *in, 
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchAddress (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchSS      (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchSex     (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchAge     (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchMarriage(const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchHobby   (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  Matchdob     (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchHt      (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchWt      (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchHair    (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchEye     (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchSkin    (const PersonQuery::Person *in, 
                            PersonQuery::Person *entry,
                            int must_match);
        int  MatchOther   (const PersonQuery::Person *in,
                            PersonQuery::Person *entry,
                            int must_match);
 

   public:

//
// The following methods are defined in the PersonQuery interface.  This
// servant implements these functions, using the local functions defined
// above.

        CORBA::Boolean findPerson (
             const PersonQuery::Person & who,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByName (
            const char * name,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByAddress (
             const PersonQuery::Address & addr,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonBySS (
             const char * ss_num,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonBySex (
             PersonQuery::SEX sex,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByAge (
            CORBA::Short age,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByMarriage (
            PersonQuery::MARRIAGE mar,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByHobby (
            PersonQuery::HOBBIES hob,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonBydob (
             const PersonQuery::Date & dob,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByHeight (
            CORBA::Short ht,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByWeight (
            CORBA::Long wt,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByHairColor (
            PersonQuery::COLOR col,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonBySkinColor (
            PersonQuery::COLOR col,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByEyeColor (
            PersonQuery::COLOR col,
            PersonQuery::Possibles_out hits); 

        CORBA::Boolean findPersonByOther (
            PersonQuery::MARKINGS other,
            PersonQuery::Possibles_out hits); 

        void exit ();

};
//
// The following class definition is a servant which
// obtains an object reference for the PersonQuery interface.
//

class QueryFactory_i : public POA_QueryFactory {
    public:

        QueryFactory_i ();
        virtual ~QueryFactory_i();


        PersonQuery_ptr createQuery (
            const char * name); 

};
#endif

