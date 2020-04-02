//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// InterceptorData.cpp
//
// C++ program for the data stream interceptor samples 
//
// Implements the data stream interceptor client and target classes 
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////
// For this version of Tuxedo, the ORB will always pass nil         //
// references for parameters ServiceContextList, and                //
// Corba::DataOutputStream.  You should not use or reference those  //
// parameters.  You should not test those parameters for nil        //
// because this restriction may change in a future version.         //
//////////////////////////////////////////////////////////////////////


#if defined(WIN32)
#include <windows.h>
#endif

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#if defined(WIN32)
#include <strstrea.h>
#else
#include <strstream.h>
#include <unistd.h>
#endif

#include <ctype.h>
#include "personquery_c.h"
#include "InterceptorData.h"

#if defined(WIN32)
BOOL WINAPI DllMain( HANDLE hDLL,
             DWORD  dwReason,
             LPVOID lpReserved )
{
    switch( dwReason )
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_PROCESS_DETACH:
            break;
    case DLL_THREAD_ATTACH:
            break;
    case DLL_THREAD_DETACH:
            break;
    }

    // Return that operation was successful
    return( TRUE );
    }
#endif  /* WIN32 */

/*
 * The following functions output the datatype to the output stream.
 * The output stream is a log file which is opened in the interceptor's
 * initialization function.
 */
static ostream& operator<<(ostream& os, PersonQuery::Possibles_ptr& Pos);
static ostream& operator<<(ostream& os, PersonQuery::Person &P);
static ostream& operator<<(ostream& os, PersonQuery::Date &D);
static ostream& operator<<(ostream& os, PersonQuery::COLOR &C);
static ostream& operator<<(ostream& os, PersonQuery::MARKINGS &M);
static ostream& operator<<(ostream& os, PersonQuery::HOBBIES &H);
static ostream& operator<<(ostream& os, PersonQuery::MARRIAGE &Ma);
static ostream& operator<<(ostream& os, PersonQuery::SEX &Se);
static void OutputReplyStatus(ostream& os, const RequestLevelInterceptor::ReplyStatus &status);
static void OutputSecurePossibles(ostream& os, PersonQuery::Possibles_ptr P);
static void OutputSecurePerson(ostream& os, PersonQuery::Person &P);



/*************************************************************

   FUNCTION NAME:       InterceptorDataClientInit
 
   FUNCTIONAL DESCRIPTION:
 
        Initialization routine called by the ORB during initialization.
        This routine will create and return an instance of the 
        ClientInterceptorData class that it supports.

        An interceptor library can support more than one set of
        interceptors by supplying multiple initialization entry 
        points (each initialization entry must be specified separately 
	in the registry). This initialization function supports only
        the client interceptor.

***************************************************************/
#ifdef  WIN32
extern "C" __declspec(dllexport) void __cdecl
#else
extern "C" void
#endif
InterceptorDataClientInit(
    CORBA::ORB_ptr                                       TheORB,
    RequestLevelInterceptor::ClientRequestInterceptor ** ClientPtr,
    RequestLevelInterceptor::TargetRequestInterceptor ** TargetPtr,
    CORBA::Boolean *                                     RetStatus)
{
    ofstream tmpfile;
    char outfilename_prefix[] = "InterceptorDataClient";
    char outfilename[50];
    char  unique_ascii [10];
    unsigned long unique = 0;
    

    //
    // create a unique file name for the client interceptor.  This Interceptor
    // example will write all data for the client interceptor to this file.
    //
    // The filename has the form <interceptor-class>xx.out, where 'xx'
    // is the process id of the process within which this interceptor
    // is running.
#ifdef WIN32
    unique = GetCurrentProcessId();
#else
    unique = getpid();
#endif
    sprintf (unique_ascii, "%d", unique);

    strcpy (outfilename, outfilename_prefix);
    strcat (outfilename, unique_ascii);
    strcat (outfilename, ".out");
   
    //
    // Now that we have the filename, open the file.
    //
    // However, we have a interesting situation.  Since the client and
    // target interceptor classes will write in two different files, the
    // output stream is held in the class instance.  But, if we fail
    // to create the class instance we have to let the user know.
    //
    // So, create the output file stream
    // in a temporary local variable for reporting errors within this specific
    // function.  Once we have the class instance, create the output file
    // stream which will contain the data stream info.  Both output streams
    // are named the same, but the temporary (the first one) will be
    // overwritten if initialization succeeds.

    tmpfile.open( outfilename, ( ios::out ) );

    // This shouldn't happen, but we're paranoid
    if  (!tmpfile.rdbuf() || !tmpfile.rdbuf()->is_open()) {
       //
       // this really won't get printed if this is in a Tuxedo server
       //
       cout << "InterceptorDataClientInit: ERROR Can't create output stream to trace" << endl;

       *RetStatus = CORBA_FALSE;
       return;
    }

    tmpfile << "InterceptorDataClientInit called" << endl;

    //
    // Create the Client object
    //
    TrackRequests *tracker = new TrackRequests("InterceptorDataClient");
    if (!tracker)
    {
        tmpfile << "InterceptorDataClientInit: TrackRequests alloc failed" 
                << endl << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }
    ClientInterceptorData * client = new ClientInterceptorData(TheORB, tracker);
    if  (!client)
    {
        tmpfile << "InterceptorDataClientInit: Client alloc failed" 
                << endl << endl;
        *RetStatus = CORBA_FALSE;
        delete tracker;
        return;
    }

    //
    // ok, we can open the "real" log file now.  Close the temporary,
    // since we don't need it and we want to overwrite it.
    //
    tmpfile.close();
    client->m_outfile.open( outfilename, ( ios::out ) );

    // This shouldn't happen, but we're paranoid
    if  (!client->m_outfile.rdbuf() || !client->m_outfile.rdbuf()->is_open()) {
       //
       // this really won't get printed if this is in a Tuxedo server
       //
       cout << "InterceptorDataClientInit: ERROR Can't create output stream to trace" << endl;

       *RetStatus = CORBA_FALSE;
       return;
    }

    client->m_outfile << "InterceptorDataClientInit called" << endl;

    *ClientPtr = client;
    *TargetPtr = 0;
    *RetStatus = CORBA_TRUE;
    return;
}

/*************************************************************

   FUNCTION NAME:       InterceptorDataTargetInit
 
   FUNCTIONAL DESCRIPTION:
 
        Initialization routine called by the ORB during initialization.
        This routine will create and return an instance of the 
        TargetInterceptorData class that it supports.

        An interceptor library can support more than one set of
        interceptors by supplying multiple initialization entry 
        points (each initialization entry must be specified separately 
	in the registry). This initialization function supports
        the target interceptor.


***************************************************************/
#ifdef  WIN32
extern "C" __declspec(dllexport) void __cdecl
#else
extern "C" void
#endif
InterceptorDataTargetInit(
    CORBA::ORB_ptr                                       TheORB,
    RequestLevelInterceptor::ClientRequestInterceptor ** ClientPtr,
    RequestLevelInterceptor::TargetRequestInterceptor ** TargetPtr,
    CORBA::Boolean *                                     RetStatus)
{
    ofstream tmpfile;
    char outfilename_prefix[] = "InterceptorDataTarget";
    char outfilename[50];
    char  unique_ascii [10];
    unsigned long unique = 0;
    

    //
    // create a unique file name for this process.  This Interceptor
    // example will write all data for this process to this file.
    //
    // The filename has the form <interceptor-class>xx.out, where 'xx'
    // is the process id of the process within which this interceptor
    // is running.
    //

#ifdef WIN32
    unique = GetCurrentProcessId();
#else
    unique = getpid();
#endif
    sprintf (unique_ascii, "%d", unique);

    strcpy (outfilename, outfilename_prefix);
    strcat (outfilename, unique_ascii);
    strcat (outfilename, ".out");
   
    //
    // Now that we have the filename, open the file.
    //
    // However, we have a interesting situation.  Since the client and
    // target interceptor classes will write in two different files, the
    // output stream is held in the class instance.  But, if we fail
    // to create the class instance
    //
    // So, create the output file stream
    // in a temporary local variable for reporting errors within this specific
    // function.  Once we have the class instance, create the output file
    // stream which will contain the data stream info.  Both output streams
    // are named the same, but the temporary (the first one) will be
    // overwritten if initialization succeeds.

    tmpfile.open( outfilename, ( ios::out ) );

    // This shouldn't happen, but we're paranoid
    if  (!tmpfile.rdbuf() || !tmpfile.rdbuf()->is_open()) {
       //
       // this really won't get printed if this is in a Tuxedo server
       //
       cout << "InterceptorDataTargetInit: ERROR Can't create output stream to trace" << endl;

       *RetStatus = CORBA_FALSE;
       return;
    }

    tmpfile << "InterceptorDataTargetInit called" << endl;

    //
    // Create the Target object.
    //
    TrackRequests *tracker = new TrackRequests("InterceptorDataClient");
    if (!tracker)
    {
        tmpfile << "InterceptorDataClientInit: TrackRequests alloc failed" 
                << endl << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }
    TargetInterceptorData * target = new TargetInterceptorData(TheORB, tracker);
    if  (!target)
    {
        tmpfile << "InterceptorDataTargetInit: Target alloc failed" 
                << endl << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }

    //
    // ok, we can open the "real" log file now.  Close the temporary,
    // since we don't need it and we want to overwrite it.
    //
    tmpfile.close();
    target->m_outfile.open( outfilename, ( ios::out ) );

    // This shouldn't happen, but we're paranoid
    if  (!target->m_outfile.rdbuf() || !target->m_outfile.rdbuf()->is_open()) {
       //
       // this really won't get printed if this is in a Tuxedo server
       //
       cout << "InterceptorDataTargetInit: ERROR Can't create output stream to trace" << endl;

       *RetStatus = CORBA_FALSE;
       return;
    }

    target->m_outfile << "InterceptorDataTargetInit called" << endl;
    
    *ClientPtr = 0;
    *TargetPtr = target;
    *RetStatus = CORBA_TRUE;
    return;
}


/*************************************************************

   FUNCTION NAME:       ClientInterceptorData::shutdown
 
   FUNCTIONAL DESCRIPTION:
 
        The shutdown operation is used by the ORB to notify an 
        implementation of an interceptor that the interceptor 
        is being shutdown. The ORB will destroy the instance 
        of the interceptor once control is returned from the
        operation back to the ORB.

***************************************************************/
Interceptors::ShutdownReturnStatus ClientInterceptorData::shutdown(
    Interceptors::ShutdownReason    reason,
    CORBA::Exception_ptr &          excep_val)
{
    Interceptors::ShutdownReturnStatus ret_status = 
                          Interceptors::SHUTDOWN_NO_EXCEPTION;

    m_outfile << "ClientInterceptorData::shutdown called" << endl;

    //
    // Output the reason for shutdown.  Usually, it doesn't matter why
    // shutdown is happening, unless there are resources to release.
    // Here is an example of the reasons why shutdown could occur.
    //

    switch (reason)
    {
    case Interceptors::ORB_SHUTDOWN:
        m_outfile << "   Reason:         ORB_SHUTDOWN" << endl;
        break;
    case Interceptors::CONNECTION_ABORTED:
        m_outfile << "   Reason:         CONNECTION_ABORTED" << endl;
        break;
    case Interceptors::RESOURCES_EXCEEDED:
        m_outfile << "   Reason:         RESOURCES_EXCEEDED" << endl;
        break;
    }
    m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorData::id
 
   FUNCTIONAL DESCRIPTION:
        The id accessor operation is used by the ORB to obtain 
        the vendor assigned identity of the interceptor as a string 
        value. This attribute is used primarily for debugging and 
        tracing of operations on the interceptors called by the ORB.
 
***************************************************************/
CORBA::String ClientInterceptorData::id()
{
    m_outfile << "ClientInterceptorData::id called" << endl << endl;

    //
    // Return a string which identifies this object.
    //
    return CORBA::string_dup("ClientInterceptorData");
}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorData::exception_occurred 
 
   FUNCTIONAL DESCRIPTION:

        The exception_occurred operation is called on a request-level 
        interceptor implementation when an exception occurs.
        It is called instead of the <xxx>_response 
        method of that interceptor. The ORB calls this operation to 
        allow the interceptor implementation to clean-up any state 
        that it might have been managing that is specific to a request.
 
***************************************************************/
void ClientInterceptorData::exception_occurred (
        const RequestLevelInterceptor::ReplyContext &   reply_context,
        CORBA::Exception_ptr                            excep_val)
{
    m_outfile << "ClientInterceptorData::exception_occurred called" << endl;
    m_outfile << "   exception: ";
    if  (excep_val)
       m_outfile << excep_val->get_id() << endl << endl;
    else m_outfile << "NULL exception" << endl << endl;

    /*
     * The request has completed, although perhaps not successfully.
     * Remove the request from the list of replies we are expecting.
     */
    RequestInfo *info = m_tracker->CompleteRequest(reply_context);
    if (info)
    {
       m_outfile << "   operation: " << info->op() << endl;
       delete info;
    }

}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorData::client_invoke
 
   FUNCTIONAL DESCRIPTION:

        This operation is called by the ORB anytime that an 
        invocation is being sent to a target object, regardless 
        of whether the target object is in a different address 
        space or the same address space as the target object.

***************************************************************/
Interceptors::InvokeReturnStatus ClientInterceptorData::client_invoke (
        const RequestLevelInterceptor::RequestContext &     request_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          request_arg_stream,
        CORBA::DataOutputStream_ptr                         reply_arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{
    Interceptors::InvokeReturnStatus ret_status = 
                       Interceptors::INVOKE_NO_EXCEPTION;

    m_outfile << "ClientInterceptorData::client_invoke called" << endl;
    
    //
    // If major version is more than we support, we can't make any
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions
    // to the structure should be at the end and we should be able
    // to look at the pieces we know about.
    //
    if  (request_context.struct_version.major_version > 1)
    {
        m_outfile << "ERROR: Struct major version greater than the supported version" << endl << endl;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::REPLY_EXCEPTION;
    }
    else if  (request_context.struct_version.minor_version > 0)
        m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;
    
    //
    // Since this interceptor will be parsing the DataInputStream, it must
    // "know" the interface.  Otherwise, it cannot figure out what kind
    // of data is in the stream.  Find out if we were called on the interface
    // we are interested in.  If not, just return and let some other
    // interceptor have a shot at it.

    if (strcmp(request_context.interface_id.in(), 
               PersonQuery::_get_interface_name()) != 0)
       return ret_status;

    // Output the request id, so it is easy to match in the log
    // when the reply data comes back.  Then add this request to the
    // lists of requests we are tracking in this interceptor.

    m_outfile << "   Request Id:     " << request_context.request_id << endl;
    m_outfile << "   Interface:      " 
              << request_context.interface_id.in() << endl;
 
    RequestInfo *req_info = m_tracker->StartRequest(request_context);
    if (!req_info) 
    {
       m_outfile << "   ERROR:  unable to create request tracker" << endl;
       excep_val = new CORBA::NO_MEMORY(); 
       return Interceptors::REPLY_EXCEPTION;
    }


    // This is the interface we are expecting.  Now identify the operation
    // being invoked, so we can parse the request parameters.

    m_outfile << "   Operation:      " 
              << request_context.operation.in() << endl;
    PQ parser;
    PQ::op_key key = parser.MapOperation(request_context.operation.in());
    switch (key)
    {
        default:
          m_outfile << "    ERROR: operation is not member of " 
                  << request_context.interface_id.in() << endl;
          excep_val = new CORBA::BAD_OPERATION();
          return Interceptors::REPLY_EXCEPTION;

        case PQ::Exit:
          m_outfile << endl;
          return  ret_status;

        case PQ::ByPerson:
          {
             PersonQuery::Person per;
             parser.GetByPerson(request_arg_stream, &per);
             m_outfile << "   Parameters:" << endl;
             m_outfile << per << endl;
          }
          break;

        case PQ::ByName:
          {
             char *name;
             parser.GetByNameOrSS(request_arg_stream, &name);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   name: " << name << endl;
             CORBA::string_free(name);
          }
          break;

        case PQ::ByAddress:
          {
             PersonQuery::Address addr;
             parser.GetByAddress(request_arg_stream, &addr);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   address: " << addr.number
                                                         << " " 
                                                         << addr.street.in() 
                                                         << endl;
             m_outfile << "                            " << addr.town.in() 
                                                         << " " 
                                                         << addr.state.in()  
                                                         << " " 
                                                         << addr.country.in()
                                                         << endl;
          }
          break;

        case PQ::BySS:
          {
             char *ss;
             parser.GetByNameOrSS(request_arg_stream, &ss);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   ss: " << ss << endl;
          }
          break;

        case PQ::ByAge:
          {
             CORBA::Short age;
             parser.GetByAgeOrHeight(request_arg_stream, &age);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   age(yrs.): " << age << endl;
          }
          break;

        case PQ::BySex:
          {
             PersonQuery::SEX sex;
             parser.GetBySex(request_arg_stream, &sex);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   sex: " << sex << endl;
          }
          break;

        case PQ::ByMarriage:
          {
             PersonQuery::MARRIAGE mar;
             parser.GetByMarriage(request_arg_stream, &mar);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   marital status: " << mar << endl;
          }
          break;

        case PQ::ByHobby:
          {
             PersonQuery::HOBBIES hob;
             parser.GetByHobby(request_arg_stream, &hob);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   hobby: " << hob << endl;
          }
          break;

        case PQ::Bydob:
          {
             PersonQuery::Date date;
             parser.GetByDob(request_arg_stream, &date);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   dob: " << date << endl;
          }
          break;

        case PQ::ByHeight:
          {
             CORBA::Short ht;
             parser.GetByAgeOrHeight(request_arg_stream, &ht);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   height(ins.): " << ht << endl;
          }
          break;

        case PQ::ByWeight:
          {
             CORBA::Long wt;
             parser.GetByWeight(request_arg_stream, &wt);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   weight(lbs.): " << wt << endl;
          }
          break;

        case PQ::ByHairColor:
          {
             PersonQuery::COLOR col;
             parser.GetByColor(request_arg_stream, &col);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   hair color: " << col << endl;
          }
          break;

        case PQ::BySkinColor:
          {
             PersonQuery::COLOR col;
             parser.GetByColor(request_arg_stream, &col);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   skin color: " << col << endl;
          }
          break;

        case PQ::ByEyeColor:
          {
             PersonQuery::COLOR col;
             parser.GetByColor(request_arg_stream, &col);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   eye color: " << col << endl;
          }
          break;

        case PQ::ByOther:
          {
             PersonQuery::MARKINGS mark;
             parser.GetByOther(request_arg_stream, &mark);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   other: " << mark << endl;
          }
          break;
    }
    
    m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorData::client_response 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that a reply 
        to an invocation is being received by the initiator of 
        the request, regardless of whether the initiator is in 
        a different address space or the same address space as 
        the target object.
  
***************************************************************/
Interceptors::ResponseReturnStatus ClientInterceptorData::client_response (
        const RequestLevelInterceptor::ReplyContext &       reply_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{
    Interceptors::ResponseReturnStatus ret_status = 
                          Interceptors::RESPONSE_NO_EXCEPTION;

    m_outfile << "ClientInterceptorData::client_response called" << endl;

    //
    // If major version is more than we support, we can't make any
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions
    // to the structure should be at the end and we should be able
    // to look at the pieces we know about.
    //
    if  (reply_context.struct_version.major_version > 1)
    {
        m_outfile << "ERROR: Struct major version greater than the supported version" << endl << endl;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::RESPONSE_EXCEPTION;
    }
    else if  (reply_context.struct_version.minor_version > 0)
        m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;
    

    //
    // Find the request that this reply is associated with.  If we can
    // find it, we know what to do with the parameters.
    //
    m_outfile << "   Request Id:     " << reply_context.request_id << endl;
    RequestInfo * req_info = m_tracker->CompleteRequest(reply_context);
    if (!req_info)
    {
       m_outfile << "   unable to find request for this reply (must not be one we care about)" << endl << endl;
       return Interceptors::RESPONSE_NO_EXCEPTION;
    }

    //
    // This is the interface we are expecting.  Now identify the operation
    // being invoked, so we can parse the request parameters.
    //

    m_outfile << "   ReplyStatus:    ";
    OutputReplyStatus(m_outfile, reply_context.reply_status);
    m_outfile << endl;
    m_outfile << "   Interface:      " << req_info->intf() << endl;
    m_outfile << "   Operation:      " << req_info->op() << endl;

    // 
    // If the reply is valid, then parse the request parameters.
    // 

    if (GIOP::NO_EXCEPTION == reply_context.reply_status)
    { 
    	PQ parser;
    	PQ::op_key key = parser.MapOperation(req_info->op());
        switch (key)
        {
            default:
              m_outfile << "    ERROR: operation is not member of " 
                      << req_info->intf() << endl;
              excep_val = new CORBA::BAD_OPERATION();
              ret_status = Interceptors::RESPONSE_EXCEPTION;

            case PQ::Exit:
              m_outfile << endl;
              break;

            case PQ::ByPerson:
            case PQ::ByName:
            case PQ::ByAddress:
            case PQ::BySS:
            case PQ::ByAge:
            case PQ::BySex:
            case PQ::ByMarriage:
            case PQ::ByHobby:
            case PQ::Bydob:
            case PQ::ByHeight:
            case PQ::ByWeight:
            case PQ::ByHairColor:
            case PQ::BySkinColor:
            case PQ::ByEyeColor:
            case PQ::ByOther:
              {
                 PersonQuery::Possibles_ptr hits;
                 CORBA::Boolean result;
                 parser.GetPossibles(arg_stream, &hits, &result);
                 if (!hits)
                 {
                    m_outfile << "  ERROR:  constructing PersonQuery::Possibles" << endl;
                    excep_val = new CORBA::NO_MEMORY();
                    ret_status = Interceptors::RESPONSE_EXCEPTION;
                 }
                 m_outfile << "   Method Result:  " <<
                              (result ? "TRUE" : "FALSE") << endl;
                 m_outfile << "   Parameters:" << endl;
                 m_outfile << hits << endl;
                 delete hits;
              }
              break;

        }

    }

    delete req_info;
    
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorData::shutdown
 
   FUNCTIONAL DESCRIPTION:

        The shutdown operation is used by the ORB to notify an 
        implementation of an interceptor that the interceptor 
        is being shutdown. The ORB will destroy the instance 
        of the interceptor once control is returned from the
        operation back to the ORB.
 
***************************************************************/
Interceptors::ShutdownReturnStatus TargetInterceptorData::shutdown(
        Interceptors::ShutdownReason    reason,
        CORBA::Exception_ptr &          excep_val)
{
    Interceptors::ShutdownReturnStatus ret_status = 
                            Interceptors::SHUTDOWN_NO_EXCEPTION;

    m_outfile << "TargetInterceptorData::shutdown called" << endl;

    //
    //  This shows an example of processing the shutdown reasons.  Usually,
    //  the reason for shutdown doesn't matter too much unless the
    //  interceptor has resources to return.
    //

    switch (reason)
    {
    case Interceptors::ORB_SHUTDOWN:
        m_outfile << "   Reason:         ORB_SHUTDOWN" << endl;
        break;
    case Interceptors::CONNECTION_ABORTED:
        m_outfile << "   Reason:         CONNECTION_ABORTED" << endl;
        break;
    case Interceptors::RESOURCES_EXCEEDED:
        m_outfile << "   Reason:         RESOURCES_EXCEEDED" << endl;
        break;
    }
    m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorData::id
 
   FUNCTIONAL DESCRIPTION:

        The id accessor operation is used by the ORB to obtain 
        the vendor assigned identity of the interceptor as a string 
        value. This attribute is used primarily for debugging and 
        tracing of operations on the interceptors called by the ORB.
 
***************************************************************/
CORBA::String TargetInterceptorData::id()
{
    m_outfile << "TargetInterceptorData::id called" << endl << endl;
    //
    // Return a string which identifies this object.
    //
    return CORBA::string_dup("TargetInterceptorData");
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorData::exception_occurred
 
   FUNCTIONAL DESCRIPTION:

        The exception_occurred operation is called on a request-level 
        interceptor implementation when an exception occurs.
        It is called instead of the <xxx>_response 
        method of that interceptor. The ORB calls this operation to 
        allow the interceptor implementation to clean-up any state 
        that it might have been managing that is specific to a request.
 
***************************************************************/
void TargetInterceptorData::exception_occurred (
                const RequestLevelInterceptor::ReplyContext &   reply_context,
                CORBA::Exception_ptr                            excep_val)
{
    m_outfile << "TargetInterceptorData::exception_occurred called" << endl;
    if  (excep_val)
       m_outfile << "   exception: " << excep_val->get_id() << endl;
    else m_outfile << "   exception: " << "NULL exception " << endl;
    m_outfile << endl;

    /*
     * The request has completed, although perhaps not successfully.
     * Remove the request from the list of replies we are expecting.
     */
    RequestInfo *info = m_tracker->CompleteRequest(reply_context);
    if (info)
    {
       m_outfile << "   operation: " << info->op() << endl;
       delete info;
    }
    return;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorData::target_invoke 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that an 
        invocation is being received by a target object, 
        regardless of whether the target object is in a 
        different address space or the same address space 
        as the target object.
 
***************************************************************/
Interceptors::InvokeReturnStatus TargetInterceptorData::target_invoke (
        const RequestLevelInterceptor::RequestContext &     request_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          request_arg_stream,
        CORBA::DataOutputStream_ptr                         reply_arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{

    //
    // This interception implementation demonstrates how to access the
    // information available through the parameters.  It looks at them,
    // and then returns a status which allows the invocation to go
    // through.
    //

    Interceptors::InvokeReturnStatus ret_status = 
                            Interceptors::INVOKE_NO_EXCEPTION;

    m_outfile << "TargetInterceptorData::target_invoke called" << endl;

    // If major version is more than we support, we can't make any
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions
    // to the structure should be at the end and we should be able to
    // look at the pieces we know about.

    if  (request_context.struct_version.major_version > 1)
    {
        m_outfile << "ERROR: Struct major version greater than the supported version" << endl;
        m_outfile << endl;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::REPLY_EXCEPTION;
    }
    else if  (request_context.struct_version.minor_version > 0)
        m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;
    
    //
    // Since this interceptor will be parsing the DataInputStream, it must
    // "know" the interface.  Otherwise, it cannot figure out what kind
    // of data is in the stream.  Find out if we were called on the interface
    // we are interested in.  If not, just return and let some other
    // interceptor have a shot at it.

    if (strcmp(request_context.interface_id.in(), 
               PersonQuery::_get_interface_name()) != 0)
       return ret_status;

    //
    // This section shows how to access the fields of the request context.
    // The first part shows access of the simple fields.
    //
    m_outfile << "   Request Id:     " << request_context.request_id << endl;
    RequestInfo *req_info = m_tracker->StartRequest(request_context);
    if (!req_info) 
    {
       m_outfile << "   ERROR:  unable to create request tracker" << endl;
       excep_val = new CORBA::NO_MEMORY();
       return Interceptors::REPLY_EXCEPTION;
    }

    m_outfile << "   Response flags: ";
    if (request_context.response_flags & 0x01)
        m_outfile << "RESPONSE EXPECTED";
    else m_outfile << "NO RESPONSE EXPECTED";
    m_outfile << endl;
    
    m_outfile << "   Interface Id:   " 
              << request_context.interface_id.in() << endl;
    m_outfile << "   Operation:      " 
              << request_context.operation.in() << endl;
    
    PQ parser;
    PQ::op_key key = parser.MapOperation(request_context.operation.in());
    switch (key)
    {
        default:
          m_outfile << "    ERROR: operation is not member of "
                  << request_context.interface_id.in() << endl;
          excep_val = new CORBA::BAD_OPERATION();
          ret_status = Interceptors::REPLY_EXCEPTION;
          break;

        case PQ::Exit:
          m_outfile << endl;
          break;

        case PQ::ByPerson:
          {
             PersonQuery::Person per;
             parser.GetByPerson(request_arg_stream, &per);
             m_outfile << "   Parameters:" << endl;
             m_outfile << per << endl;
          }
          break;

        case PQ::ByName:
          {
             char *name;
             parser.GetByNameOrSS(request_arg_stream, &name);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   name: " << name << endl;
             m_outfile << endl;
             CORBA::string_free(name);
          }
          break;

        case PQ::ByAddress:
          {
             PersonQuery::Address addr;
             parser.GetByAddress(request_arg_stream, &addr);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   address: " << addr.number
                                                         << " " 
                                                         << addr.street.in() 
                                                         << endl;
             m_outfile << "                            " << addr.town.in() 
                                                         << " " 
                                                         << addr.state.in()  
                                                         << " " 
                                                         << addr.country.in()
                                                         << endl << endl;
          }
          break;

        case PQ::BySS:
          {
             char *ss;
             parser.GetByNameOrSS(request_arg_stream, &ss);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   ss: " << ss << endl;
             m_outfile << endl;
             CORBA::string_free(ss);
          }
          break;

        case PQ::ByAge:
          {
             CORBA::Short age;
             parser.GetByAgeOrHeight(request_arg_stream, &age);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   age(yrs.): " << age << endl;
             m_outfile << endl;
          }
          break;

        case PQ::BySex:
          {
             PersonQuery::SEX sex;
             parser.GetBySex(request_arg_stream, &sex);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   sex: " << sex << endl;
             m_outfile << endl;
          }
          break;

        case PQ::ByMarriage:
          {
             PersonQuery::MARRIAGE mar;
             parser.GetByMarriage(request_arg_stream, &mar);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   marital status: " << mar << endl;
             m_outfile << endl;
          }
          break;

        case PQ::ByHobby:
          {
             PersonQuery::HOBBIES hob;
             parser.GetByHobby(request_arg_stream, &hob);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   hobby: " << hob << endl;
             m_outfile << endl;
          }
          break;

        case PQ::Bydob:
          {
             PersonQuery::Date date;
             parser.GetByDob(request_arg_stream, &date);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   dob: " << date << endl;
             m_outfile << endl;
          }
          break;

        case PQ::ByHeight:
          {
             CORBA::Short ht;
             parser.GetByAgeOrHeight(request_arg_stream, &ht);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   height(in.): " << ht << endl;
             m_outfile << endl;
          }
          break;


        case PQ::ByWeight:
          {
             CORBA::Long wt;
             parser.GetByWeight(request_arg_stream, &wt);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   weight(lbs.): " << wt << endl;
             m_outfile << endl;
          }
          break;

        case PQ::ByHairColor:
          {
             PersonQuery::COLOR col;
             parser.GetByColor(request_arg_stream, &col);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   hair color: " << col << endl;
             m_outfile << endl;
          }
          break;

        case PQ::BySkinColor:
          {
             PersonQuery::COLOR col;
             parser.GetByColor(request_arg_stream, &col);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   skin color: " << col  << endl;
             m_outfile << endl;
          }
          break;

        case PQ::ByEyeColor:
          {
             PersonQuery::COLOR col;
             parser.GetByColor(request_arg_stream, &col);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   eye color: " << col << endl;
             m_outfile << endl;
          }
          break;

        case PQ::ByOther:
          {
             PersonQuery::MARKINGS mark;
             parser.GetByOther(request_arg_stream, &mark);
             m_outfile << "   Parameters:" << endl;
             m_outfile << "                   other: " << mark << endl;
             m_outfile << endl;
          }
          break;
    }

    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorData::target_response 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that a reply 
        to an invocation is being sent to the initiator of the 
        request, regardless of whether the initiator is in a 
        different address space or the same address space as 
        the target object.
 
***************************************************************/
Interceptors::ResponseReturnStatus TargetInterceptorData::target_response (
        const RequestLevelInterceptor::ReplyContext &       reply_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{

    //
    // Assume the reply will be sent back to the client
    //
    Interceptors::ResponseReturnStatus ret_status = 
                           Interceptors::RESPONSE_NO_EXCEPTION;

    m_outfile << "TargetInterceptorData::target_response called" << endl;
    

    // If major version is more than we support, we can't make any
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions
    // to the structure should be at the end and we should be able to
    // look at the pieces we know about.
    if  (reply_context.struct_version.major_version > 1)
    {
        m_outfile << "ERROR: Struct major version greater than the supported version" << endl;
        m_outfile << endl;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::RESPONSE_EXCEPTION;
    }
    else if  (reply_context.struct_version.minor_version > 0)
        m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;
    
    //
    // Show the id of the request we have interceptedi, then store the
    // request, the interface, and the operation, so we have that data
    // when the response comes in.
    //
    m_outfile << "   Request Id:     " << reply_context.request_id << endl;
    RequestInfo * req_info = m_tracker->CompleteRequest(reply_context);
    if (!req_info)
    {
       m_outfile << "   unable to find request for this reply (must not be one we care about)" << endl << endl;
       return Interceptors::RESPONSE_NO_EXCEPTION;
    }

    //
    // This is the interface we are expecting.  Output the information
    // we have about the request, and identify the operation
    // being invoked, so we can parse the request parameters.
    //

    m_outfile << "   ReplyStatus:    ";
    OutputReplyStatus(m_outfile, reply_context.reply_status);
    m_outfile << endl;
    m_outfile << "   Interface:      " << req_info->intf() << endl;
    m_outfile << "   Operation:      " << req_info->op() << endl;
    PQ parser;
    PQ::op_key key = parser.MapOperation(req_info->op());
    switch (key)
    {
        default:
          m_outfile << "    ERROR: operation is not member of "
                  << req_info->intf() << endl;
          excep_val = new CORBA::BAD_OPERATION();
          ret_status = Interceptors::RESPONSE_EXCEPTION;
          break;

        case PQ::Exit:
          m_outfile << endl;
          break;

        case PQ::ByPerson:
        case PQ::BySS:
        case PQ::ByAge:
        case PQ::BySex:
        case PQ::ByMarriage:
        case PQ::Bydob:
        case PQ::BySkinColor:
        case PQ::ByName:
        case PQ::ByAddress:
        case PQ::ByHobby:
        case PQ::ByHeight:
        case PQ::ByWeight:
        case PQ::ByHairColor:
        case PQ::ByEyeColor:
        case PQ::ByOther:
          {
             PersonQuery::Possibles_ptr hits;
             CORBA::Boolean result;
             parser.GetPossibles(arg_stream, &hits, &result);
             if (!hits)
             {
                m_outfile << "  ERROR:  constructing PersonQuery::Possibles" << endl;
                excep_val = new CORBA::NO_MEMORY();
                ret_status = Interceptors::RESPONSE_EXCEPTION;
             }
             else {
                m_outfile << "   Method Result:  "
                          << (result ? "TRUE" : "FALSE") << endl;
                m_outfile << "   Parameters:" << endl;
                OutputSecurePossibles(m_outfile, hits);
                delete hits;
             }
          }
          break;

    }
    m_outfile << endl;

    delete req_info;

    return ret_status;
}


/*************************************************************

 The following functions implement the PQ class, which read
 the CORBA::DataInputStream and create data structures
 from the stream.

 ************************************************************/

/*************************************************************

   FUNCTION NAME:       PQ::get_addr

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will get a PersonQuery::Address structure
        from the CORBA::DataInputStream.

**************************************************************/

void PQ::get_addr(CORBA::DataInputStream_ptr S, 
                  PersonQuery::Address *addr)
{
    addr->number = S->read_short();
    addr->street = S->read_string();
    addr->town = S->read_string();
    addr->state = S->read_string();
    addr->country = S->read_string();
}

/*************************************************************

   FUNCTION NAME:       PQ::get_dob

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will get a PersonQuery::Date structure
        from the CORBA::DataInputStream.

**************************************************************/

void PQ::get_dob(CORBA::DataInputStream_ptr S, 
                  PersonQuery::Date *dob)
{
    dob->month = (PersonQuery::MONTHS)S->read_ulong();
    dob->day = S->read_short();
    dob->year = S->read_short();
}

/*************************************************************

   FUNCTION NAME:       PQ::MapOperation

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will map the operation name of an invocation
	to a integer value.  It also determines whether the operation
	is supported by the data stream interceptor.

**************************************************************/

PQ::op_key PQ::MapOperation(const char *op)
{
    if (op == NULL)
      return PQ::Unknown;

    if (strcmp(op, "findPerson") == 0)
      return PQ::ByPerson;
    else if (strcmp(op, "findPersonByName") == 0)
      return PQ::ByName;
    else if (strcmp(op, "findPersonByAddress") == 0)
      return PQ::ByAddress;
    else if (strcmp(op, "findPersonBySS") == 0)
      return PQ::BySS;
    else if (strcmp(op, "findPersonBySex") == 0)
      return PQ::BySex;
    else if (strcmp(op, "findPersonByAge") == 0)
      return PQ::ByAge;
    else if (strcmp(op, "findPersonByMarriage") == 0)
      return PQ::ByMarriage;
    else if (strcmp(op, "findPersonByHobby") == 0)
      return PQ::ByHobby;
    else if (strcmp(op, "findPersonBydob") == 0)
      return PQ::Bydob;
    else if (strcmp(op, "findPersonByHeight") == 0)
      return PQ::ByHeight;
    else if (strcmp(op, "findPersonByWeight") == 0)
      return PQ::ByWeight;
    else if (strcmp(op, "findPersonByHairColor") == 0)
      return PQ::ByHairColor;
    else if (strcmp(op, "findPersonByEyeColor") == 0)
      return PQ::ByEyeColor;
    else if (strcmp(op, "findPersonBySkinColor") == 0)
      return PQ::BySkinColor;
    else if (strcmp(op, "findPersonByOther") == 0)
      return PQ::ByOther;
    else if (strcmp(op, "exit") == 0)
      return PQ::Exit;
    else return PQ::Unknown;
    
}


/*************************************************************

   FUNCTION NAME:       PQ::GetPossibles

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract the
	results of invoking on the PersonQuery::findPersonByName
        operation.

**************************************************************/
void PQ::GetPossibles(
                   CORBA::DataInputStream_ptr S,
                   PersonQuery::Possibles_ptr *P,
                   CORBA::Boolean             *R)
{
    CORBA::ULong len;
    char *str;

    // Get the result of the method.
    *R = S->read_boolean();
    
    // get the length of the sequence contained in the input stream
    len = S->read_ulong();

    // allocate a sequence buffer to hold the Person structures we'll
    // read out of the input stream.
    PersonQuery::Person *per = PersonQuery::Possibles::allocbuf(len);
    if (!per)
       throw CORBA::NO_MEMORY();

    PersonQuery::Person *data = per;
    for (CORBA::ULong i = 0; i < len; i++, data++)
    {
        // get the person name
        str = S->read_string();
        if (!str)
        {
           PersonQuery::Possibles::freebuf(per);
           throw CORBA::NO_MEMORY();
        } 	
        data->name = str;

        // get the address
        try {
           get_addr(S, &data->addr);
        } catch (...)
        {
           PersonQuery::Possibles::freebuf(per);
           throw; 
        }

	// get the social security number
        str = S->read_string();
        if (!str)
        {
           PersonQuery::Possibles::freebuf(per);
           throw CORBA::NO_MEMORY();
        } 	
        data->ss = str;

	// get the person's sex
        data->sex = (PersonQuery::SEX)S->read_ulong();
        
        // get the person's age;
        data->age = S->read_short();

        // get the person's marriage status
        data->mar = (PersonQuery::MARRIAGE)S->read_long();

        // get the person's hobby
        data->rec = (PersonQuery::HOBBIES)S->read_long();

        // get the person's date of birth
        try {
           get_dob(S, &data->dob);
        } catch (...)
        {
           PersonQuery::Possibles::freebuf(per);
           throw; 
        }

        // get the person's height
        data->ht = S->read_short();

        // get the person's weight
        data->wt = S->read_long();

        // get the person's hair color
        data->hair = (PersonQuery::COLOR)S->read_long();

        // get the person's eye color
        data->eyes = (PersonQuery::COLOR)S->read_long();

        // get the person's skin color
        data->skin = (PersonQuery::COLOR)S->read_long();

        // get the person's other characteristics
        data->other = (PersonQuery::MARKINGS)S->read_long();
      
    }
    *P = new PersonQuery::Possibles(len, len, per, CORBA_TRUE);
    return;
}

/*************************************************************

   FUNCTION NAME:       PQ::GetByPerson

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Person" parameter.

**************************************************************/
void PQ::GetByPerson(CORBA::DataInputStream_ptr S,
                     PersonQuery::Person        *P)
{ 
    char *tmp;

    GetByNameOrSS   (S, &tmp);
    P->name = tmp;
    GetByAddress    (S, &(P->addr));
    GetByNameOrSS   (S, &tmp);
    P->ss = tmp;
    GetBySex        (S, &(P->sex));
    GetByAgeOrHeight(S, &(P->age));
    GetByMarriage   (S, &(P->mar));
    GetByHobby      (S, &(P->rec));
    GetByDob        (S, &(P->dob));
    GetByAgeOrHeight(S, &(P->ht));
    GetByWeight     (S, &(P->wt));
    GetByColor      (S, &(P->hair));
    GetByColor      (S, &(P->eyes));
    GetByColor      (S, &(P->skin));
    GetByOther      (S, &(P->other));
    return;
}

/*************************************************************

   FUNCTION NAME:       PQ::GetByNameOrSS

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Name" or "SS" parameter.

**************************************************************/
void PQ::GetByNameOrSS(CORBA::DataInputStream_ptr S,
                       char **Str)
{
    *Str = S->read_string();
    return;
}

/*************************************************************

   FUNCTION NAME:       PQ::GetByAddress

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Address" parameter.

**************************************************************/
void PQ::GetByAddress(CORBA::DataInputStream_ptr S,
                      PersonQuery::Address *Addr)
{
    Addr->number = S->read_short();
    Addr->street = S->read_string();
    Addr->town = S->read_string();
    Addr->state = S->read_string();
    Addr->country = S->read_string();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetBySex

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Sex" parameter.

**************************************************************/
void PQ::GetBySex(CORBA::DataInputStream_ptr S,
                  PersonQuery::SEX *Sex)
{
    *Sex = (PersonQuery::SEX) S->read_ulong();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetByAgeOrHeight

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Age" or "Height" parameter.

**************************************************************/
void PQ::GetByAgeOrHeight(CORBA::DataInputStream_ptr S,
                          CORBA::Short *P)
{
    *P = S->read_short();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetByMarriage

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Marriage" parameter.

**************************************************************/
void PQ::GetByMarriage(CORBA::DataInputStream_ptr S,
                       PersonQuery::MARRIAGE *M)
{
    *M = (PersonQuery::MARRIAGE)S->read_ulong();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetByHobby

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Hobby" parameter.

**************************************************************/
void PQ::GetByHobby(CORBA::DataInputStream_ptr S,
                    PersonQuery::HOBBIES *H)
{
    *H = (PersonQuery::HOBBIES)S->read_ulong();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetByDob

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Date of Birth" parameter.

**************************************************************/
void PQ::GetByDob(CORBA::DataInputStream_ptr S,
                  PersonQuery::Date *D)
{
    D->month = (PersonQuery::MONTHS)S->read_ulong();
    D->day   = S->read_short();
    D->year  = S->read_short();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetByWeight

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Weight" parameter.

**************************************************************/
void PQ::GetByWeight(CORBA::DataInputStream_ptr S,
                     CORBA::Long *D)
{
    *D = S->read_long();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetByColor

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Hair", "Skin", or "Eye" parameter.

**************************************************************/
void PQ::GetByColor(CORBA::DataInputStream_ptr S,
                    PersonQuery::COLOR *Color)
{
    *Color = (PersonQuery::COLOR)S->read_ulong();
    return;
}


/*************************************************************

   FUNCTION NAME:       PQ::GetByOther

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will parse the input stream and extract 
        the "Other" parameter.

**************************************************************/
void PQ::GetByOther(CORBA::DataInputStream_ptr S,
                    PersonQuery::MARKINGS *M)
{
    *M = (PersonQuery::MARKINGS)S->read_ulong();
    return;
}


/*************************************************************

 The following functions implement the TrackRequests class.
 This class is needed because the ReplyContext identifies the
 request to which it is a response by the RequestId.
 
 When a request is intercepted by the client interceptor, a
 node is added to the list of requests being tracked by the
 TrackRequests instance. The node is initialized with the
 request id of the request, the interface and the operation.
 Then when the reply is intercepted, the list of nodes managed
 by the TrackRequests instance is searched for the appropriate
 request.  This allows the interceptors' response functions (and 
 exception_occurred functions) to log which request has completed
 in a form easily understood by humans.

 ************************************************************/

/*************************************************************

   FUNCTION NAME:       TrackRequests::StartRequest

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will add a node to the request tracking list.

**************************************************************/
RequestInfo * TrackRequests::StartRequest(
        const RequestLevelInterceptor::RequestContext& request_context)
{
  RequestInfo * info = (RequestInfo *) 0;

  // Make sure structure is valid...
  if (request_context.struct_version.major_version > 1)
    return info;


  // Allocate an information block...
  if ( request_context.interface_id.in() && request_context.operation.in() )
  {
    info = new RequestInfo(request_context.request_id,
                           request_context.operation.in(),
                           request_context.interface_id.in());
  }
  else
  {
    // Supply empty strings so string functions will not crash...
    info = new RequestInfo(request_context.request_id,
                           (const char *)"",
                           (const char *)"");
  }

  // When no response is expected do not add to the list...
  if ( !(request_context.response_flags & 0x01) )
    return info;

  // Add to the list...
  if (info) { info->next(m_list); m_list = info; }

  // Done.
  return info;
}


/*************************************************************

   FUNCTION NAME:       TrackRequests::CompleteRequest

 
   FUNCTIONAL DESCRIPTION:
 
        This routine will find the request in the node list
        which is associated with supplied reply.

**************************************************************/
RequestInfo * TrackRequests::CompleteRequest(
        const RequestLevelInterceptor::ReplyContext& reply_context)
{
  // Make sure structure is vaild...
  if (reply_context.struct_version.major_version > 1)
    return (RequestInfo *) 0;

  // Initialize...
  RequestInfo * prev_entry = 0;
  RequestInfo * entry = m_list;

  // Loop through the list to find entry and remove from chain...
  while (entry)
  {
    if (entry->id() == reply_context.request_id)
    {
      // Grab next entry when match...
      RequestInfo * next_entry = entry->next();

      // Remove current entry from list...
      if (prev_entry)
        prev_entry->next(next_entry);
      else
        m_list = next_entry;

      // Done...
      break;
    }

    // No match then move along little doggie...
    prev_entry = entry;
    entry = entry->next();
  }

  // Hasta La Vista...
  return entry;
}

/*************************************************************

   FUNCTION NAME:       TrackRequests::~TrackRequests

 
   FUNCTIONAL DESCRIPTION:
 
        Destructor for the TrackRequests class.

**************************************************************/
TrackRequests::~TrackRequests()
{
  // Loop through the list to output information and delete...
  RequestInfo * entry = m_list;
  while (entry)
  {
    // Get next entry...
    m_list = entry->next();

    // Remove entry...
    delete entry;
    entry = m_list;
  }
}

/*************************************************************
 *
 * The following utility functions allow the interceptors to log
 * the request parameters and results to the interceptor log files.
 *
 * There are functions which handle each constructed data type
 * of the PersonQuery interface.  The constructed data types are
 * broken down into simple data types, which are output by library
 * provided functions.
 */

 
/*
 * Output the sequence of PersonQuery::Person structures
 */
static ostream& operator<<(ostream& os, PersonQuery::Possibles_ptr& Pos)
{
  os << "                   Maximum: " << Pos->maximum() << endl;
  os << "                   Length:  " << Pos->length() << endl << endl;
  for (CORBA::ULong i = 0; i < Pos->length(); i++)
  {
  os << "                   Item " << i << endl;
     os << (*Pos)[i] << endl;
  }
 
  return os;
}

/*
 * Output a single PersonQuery::Person structure
 */
static ostream& operator<<(ostream& os, PersonQuery::Person &P)
{
  os << "                            name:           "; 
  if ((!P.name.in()) || strlen(P.name.in()) == 0)
     os << "no value supplied" << endl;
  else
     os << P.name.in() << endl;

  os << "                            address:        "; 
  if (((!P.addr.street.in())  || (strlen(P.addr.street.in()) == 0))  && 
      ((!P.addr.town.in())    || (strlen(P.addr.town.in()) == 0))    &&
      ((!P.addr.state.in())   || (strlen(P.addr.state.in()) == 0))   &&
      ((!P.addr.country.in()) || (strlen(P.addr.country.in()) == 0)))

     os << "no value supplied" << endl;
  else {
     os << P.addr.number << " " << P.addr.street.in() << endl;
     os << "                                            " << P.addr.town.in() 
                                                          << " " 
                                                          << P.addr.state.in()  
                                                          << " " 
                                                          << P.addr.country.in()
                                                          << endl;
  }

  os << "                            ss:             "; 
  if ((!P.ss.in()) || (strlen(P.ss.in()) == 0))
     os << "no value supplied" << endl;
  else 
     os << P.ss.in() << endl;


  os << "                            sex:            " << P.sex << endl;
  os << "                            age(yrs.):      " << P.age << endl;
  os << "                            marital status: " << P.mar << endl;
  os << "                            hobby:          " << P.rec << endl;
  os << "                            date-of-birth:  " << P.dob << endl;
  os << "                            height(in.):    " << P.ht << endl;
  os << "                            weight(lbs.):   " << P.wt << endl;
  os << "                            hair color:     " << P.hair << endl;
  os << "                            eye color:      " << P.eyes << endl;
  os << "                            skin color:     " << P.skin << endl;
  os << "                            other markings: " << P.other << endl;
  return os;
}

/*
 * Output a PersonQuery::Data structure. This structure consists of
 * ints and strings, so it uses the library provided overloaded functions
 */
static ostream& operator<<(ostream& os, PersonQuery::Date &D)
{
  os << D.month << "/" << D.day << "/" << D.year;
  return os;
}

/*
 * Output a PersonQuery::COLOR.  Translate the enum value to a
 * string and output the string.
 */
static ostream& operator<<(ostream& os, PersonQuery::COLOR &C)
{
  switch (C)
  {
     case PersonQuery::dontcare:
     default:
	os << "don't care";
        break;
     case PersonQuery::white:
	os << "white";
        break;
     case PersonQuery::black:
	os << "black";
        break;
     case PersonQuery::brown:
	os << "brown";
        break;
     case PersonQuery::yellow:
	os << "yellow";
        break;
     case PersonQuery::red:
	os << "red";
        break;
     case PersonQuery::green:
	os << "green";
        break;
     case PersonQuery::blue:
	os << "blue";
        break;
     case PersonQuery::gray:
	os << "gray";
        break;
     case PersonQuery::violet:
	os << "violet";
        break;
     case PersonQuery::hazel:
	os << "hazel";
        break;
     case PersonQuery::unknown:
	os << "unknown";
        break;
  }
  return os;
}
/*
 * Output the PersonQuery::MARKINGS enum.  Translate the enum value
 * to a string and output it.
 */
static ostream& operator<<(ostream& os, PersonQuery::MARKINGS &M)
{
  switch(M)
  {
     case PersonQuery::dont_care:
     default:
        os << "don't care";
        break;
     case PersonQuery::tattoo:
        os << "tattoo";
        break;
     case PersonQuery::scar:
        os << "scar";
        break;
     case PersonQuery::missing_limb:
        os << "missing limb";
        break;
     case PersonQuery::none:
        os << "none";
        break;
  }
  return os;
}
/*
 * Output the PersonQuery::HOBBIES enum.  Translate the enum value
 * to a string and output it.
 */
static ostream& operator<<(ostream& os, PersonQuery::HOBBIES &H)
{
  switch (H)
  {
     case PersonQuery::who_cares:
     default:
        os << "who cares";
        break;
     case PersonQuery::rocks:
        os << "rock climbing";
        break;
     case PersonQuery::swim:
        os << "swimming";
        break;
     case PersonQuery::tv:
        os << "television";
        break;
     case PersonQuery::stamps:
        os << "stamp collecting";
        break;
     case PersonQuery::photo:
        os << "photography";
        break;
     case PersonQuery::weaving:
        os << "weaving";
        break;
  }
  return os;
}
/*
 * Output the PersonQuery::MARRIAGE enum.  Translate the enum value
 * to a string and output it.
 */
static ostream& operator<<(ostream& os, PersonQuery::MARRIAGE &Ma)
{
  switch(Ma)
  {
     case PersonQuery::not_known:
     default:
        os << "not known";
        break;
     case PersonQuery::single:
        os << "single";
        break;
     case PersonQuery::married:
        os << "married";
        break;
     case PersonQuery::divorced:
        os << "divorced";
        break;
  }
  return os;
}
/*
 * Output the PersonQuery::SEX enum.  Translate the enum value
 * to a string and output it.
 */
static ostream& operator<<(ostream& os, PersonQuery::SEX &Se)
{
  switch (Se)
  {
     case PersonQuery::cant_tell:
     default:
        os << "can't tell";
        break;
     case PersonQuery::male:
        os << "male";
        break;
     case PersonQuery::female:
        os << "female";
        break;
  }
  return os;
}

/*
 * Output the the status returned in the ReplyContext. Translate the status
 * to a string and output it.
 */
static void OutputReplyStatus(
                      ostream& os, 
                      const RequestLevelInterceptor::ReplyStatus &status)
{
   switch (status)
   {
      case GIOP::NO_EXCEPTION:
         os << "GIOP::NO_EXCEPTION";
         break;
      case GIOP::USER_EXCEPTION:
         os << "GIOP::USER_EXCEPTION";
         break;
      case GIOP::SYSTEM_EXCEPTION:
         os << "GIOP::SYSTEM_EXCEPTION";
         break;
      case GIOP::LOCATION_FORWARD:
         os << "GIOP::LOCATION_FORWARD";
         break;
      case GIOP::LOCATION_FORWARD_PERM:
         os << "GIOP::LOCATION_FORWARD_PERM";
         break;
      case GIOP::NEEDS_ADDRESSING_MODE:
         os << "GIOP::NEEDS_ADDRESSING_MODE";
         break;
      default:
         os << "UNKNOWN";
         break;
  }
  return;
}
/*
 * Output a sequence of PersonQuery::Person structures.  This function
 * does not log the "secure" data fields, such as marital status and
 * sex.  It is called by the Target interceptors target_response function
 */
static void OutputSecurePossibles(ostream& os, PersonQuery::Possibles_ptr Pos)
{
  os << "                   Maximum: " << Pos->maximum() << endl;
  os << "                   Length:  " << Pos->length() << endl << endl;
  for (CORBA::ULong i = 0; i < Pos->length(); i++)
  {
     os << "                   Item " << i << endl;
     OutputSecurePerson(os, (*Pos)[i]);
  }
}
/*
 * Output a single PersonQuery::Person structure.  This function
 * does not log the "secure" data fields, such as marital status and
 * sex.
 */
static void OutputSecurePerson(ostream& os, PersonQuery::Person &P)
{
  os << "                            name:           " << P.name.in() << endl;
  os << "                            address:        " << P.addr.number 
                                                       << " " 
                                                       << P.addr.street.in() 
                                                       << endl;
  os << "                                            " << P.addr.town.in() 
                                                       << " " 
                                                       << P.addr.state.in()  
                                                       << " " 
                                                       << P.addr.country.in()
                                                       << endl;
  os << "                            ss:             NO PRIVILEDGE" << endl;
  os << "                            sex:            NO PRIVILEDGE" << endl;
  os << "                            age (years):    NO PRIVILEDGE" << endl;
  os << "                            marital status: NO PRIVILEDGE" << endl;
  os << "                            hobby:          " << P.rec << endl;
  os << "                            date-of-birth:  NO PRIVILEDGE" << endl;
  os << "                            height (in.):   " << P.ht << endl;
  os << "                            weight (lbs.):  " << P.wt << endl;
  os << "                            hair color:     " << P.hair << endl;
  os << "                            eye color:      " << P.eyes << endl;
  os << "                            skin color:     NO PRIVILEDGE" << endl;
  os << "                            other markings: " << P.other << endl;
}

