//	Copyright (c) 1999 BEA Systems, Inc.
//	All rights reserved
//
//	THIS IS UNPUBLISHED PROPRIETARY
//	SOURCE CODE OF BEA Systems, Inc.
//	The copyright notice above does not
//	evidence any actual or intended
//	publication of such source code.
//
// #ident	"@(#) objtm/beawrapper/beawrapper.h	$Revision: 1.2 $"

#ifndef _beawrapper_h
#define _beawrapper_h

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef	_CORBA_h
#include <CORBA.h>
#endif

#ifndef	_PortableServer_h
#include <PortableServer.h>
#endif

#if defined(WIN32)
# if defined(BEAWRAPPEREXPORTAPI)
#  define BEAWRAPPEREXPDLL __declspec(dllexport)
# else
#  define BEAWRAPPEREXPDLL __declspec(dllimport)
# endif
#else
# define BEAWRAPPEREXPDLL
#endif

class BEAWRAPPEREXPDLL BEAWrapper
{
    public:
        class BEAWRAPPEREXPDLL Callbacks 
         {
            public:
                class BEAWRAPPEREXPDLL ServantAlreadyActive : public CORBA::UserException
                {
                    public:
                        static ServantAlreadyActive * _narrow(CORBA::Exception_ptr);
                        ServantAlreadyActive ();
                        ~ServantAlreadyActive () { }
                        ServantAlreadyActive & operator=(const ServantAlreadyActive &);
                    protected:
                        inline static const char * _get_repos_id() { return "IDL:beasys.com/BEAWrapper/Callbacks/ServantAlreadyActive:1.0"; }

                };  // class ServantAlreadyActive


                class BEAWRAPPEREXPDLL ObjectAlreadyActive : public CORBA::UserException
                {
                    public:
                        static ObjectAlreadyActive * _narrow(CORBA::Exception_ptr);
                        ObjectAlreadyActive ();
                        ~ObjectAlreadyActive () { }
                        ObjectAlreadyActive & operator=(const ObjectAlreadyActive &);
                    protected:
                        inline static const char * _get_repos_id() { return "IDL:beasys.com/BEAWrapper/Callbacks/ObjectAlreadyActive:1.0"; }

                };  // class ObjectAlreadyActive


                class BEAWRAPPEREXPDLL NotInRequest : public CORBA::UserException
                {
                    public:
                        static NotInRequest * _narrow(CORBA::Exception_ptr);
                        NotInRequest ();
                        ~NotInRequest () { }
                        NotInRequest & operator=(const NotInRequest &);

                  protected:
                        inline static const char * _get_repos_id() { return "IDL:beasys.com/BEAWrapper/Callbacks/NotInRequest:1.0"; }

                };  // class NotInRequest

                Callbacks(CORBA::ORB_ptr init_orb);

                CORBA::Object_ptr start_transient (
                    PortableServer::Servant servant,
                    const char * rep_id); 

                CORBA::Object_ptr start_persistent_systemid (
                    PortableServer::Servant servant,
                    const char * rep_id,
                    char * & stroid); 

                CORBA::Object_ptr restart_persistent_systemid (
                    PortableServer::Servant servant,
                    const char * rep_id,
                    const char * stroid); 

                CORBA::Object_ptr start_persistent_userid (
                    PortableServer::Servant servant,
                    const char * rep_id,
                    const char * oid); 

                void stop_object (
                    PortableServer::Servant servant); 

                void stop_all_objects (); 

                char * get_string_oid (); 

                ~Callbacks();

            private:
                Callbacks(){ }
                Callbacks( const Callbacks&) { }
                void operator=(const Callbacks&) { }

                static CORBA::ORB_ptr orb;
                static PortableServer::POA_ptr root_poa;
                static PortableServer::POA_ptr trasys_poa;
                static PortableServer::POA_ptr persys_poa;
                static PortableServer::POA_ptr peruser_poa;
                
        };  // class Callbacks



};  // class BEAWrapper

#endif



