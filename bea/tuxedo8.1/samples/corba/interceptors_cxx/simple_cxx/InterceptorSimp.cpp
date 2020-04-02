//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// InterceptorSimp.cpp
//
// C++ program for the simple interceptor samples 
//
// Implements the simple interceptor client and target classes 
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////
// For this version of Tuxedo, the ORB will always pass nil         //
// references for parameters ServiceContextList, and                //
// CORBA::DataOutputStream.  You should not use or reference those  //
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
#include "InterceptorSimp.h"

int  OpenStream(char *, ofstream *);

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

/*************************************************************

   FUNCTION NAME:       InterceptorSimpClientInit
 
   FUNCTIONAL DESCRIPTION:
 
        Initialization routine called by the ORB during initialization.
        This routine will create and return an instance of the 
        ClientInterceptorSimp class.

        An interceptor library can support more than one set of
        interceptors by supplying multiple initialization entry 
        points (each initialization entry must be specified separately 
	in the registry).

***************************************************************/
#ifdef  WIN32
extern "C" __declspec(dllexport) void __cdecl
#else
extern "C" void
#endif
InterceptorSimpClientInit(
    CORBA::ORB_ptr                                       TheORB,
    RequestLevelInterceptor::ClientRequestInterceptor ** ClientPtr,
    RequestLevelInterceptor::TargetRequestInterceptor ** TargetPtr,
    CORBA::Boolean *                                     RetStatus)
{

    //
    // Create the Client object
    //
    ClientInterceptorSimp * client = new ClientInterceptorSimp(TheORB); 
    if  (!client)
    {
        cout << "InterceptorSimpClientInit: Client alloc failed" 
             << endl << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }
    
    //
    // Open output stream for the client interceptor.
    //
    if (!OpenStream((char *)"Client", &client->m_outfile))
    {
        //
        // this really won't get printed if this is in a Tuxedo server
        //
        cout << "InterceptorSimpClientInit: ERROR Can't create client output stream to trace" << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }

    client->m_outfile << "InterceptorSimpClientInit called" << endl;

    *ClientPtr = client;
    *TargetPtr = 0;
    *RetStatus = CORBA_TRUE;
    return;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSimpTargetInit
 
   FUNCTIONAL DESCRIPTION:
 
        Initialization routine called by the ORB during initialization.
        This routine will create and return an instance of the 
        TargetInterceptorSimp class.

        An interceptor library can support more than one set of
        interceptors by supplying multiple initialization entry 
        points (each initialization entry must be specified separately 
	in the registry).


***************************************************************/
#ifdef  WIN32
extern "C" __declspec(dllexport) void __cdecl
#else
extern "C" void
#endif
InterceptorSimpTargetInit(
    CORBA::ORB_ptr                                       TheORB,
    RequestLevelInterceptor::ClientRequestInterceptor ** ClientPtr,
    RequestLevelInterceptor::TargetRequestInterceptor ** TargetPtr,
    CORBA::Boolean *                                     RetStatus)
{

    //
    // Create the Target object.
    //
    TargetInterceptorSimp * target = new TargetInterceptorSimp(TheORB);
    if  (!target)
    {
        cout << "InterceptorSimpTargetInit: Target alloc failed" 
             << endl << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }
    
    //
    // Open output stream for the client interceptor.
    //
    if (!OpenStream((char *)"Target", &target->m_outfile))
    {
        //
        // this really won't get printed if this is in a Tuxedo server
        //
        cout << "InterceptorSimpTargetInit: ERROR Can't create target output stream to trace" << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }

    target->m_outfile << "InterceptorSimpTargetInit called" << endl;

    *ClientPtr = 0;
    *TargetPtr = target;
    *RetStatus = CORBA_TRUE;
    return;
}


/*************************************************************

   FUNCTION NAME:       ClientInterceptorSimp::shutdown
 
   FUNCTIONAL DESCRIPTION:
 
        The shutdown operation is used by the ORB to notify an 
        implementation of an interceptor that the interceptor 
        is being shutdown. The ORB will destroy the instance 
        of the interceptor once control is returned from the
        operation back to the ORB.

***************************************************************/
Interceptors::ShutdownReturnStatus ClientInterceptorSimp::shutdown(
    Interceptors::ShutdownReason    reason,
    CORBA::Exception_ptr &          excep_val)
{
    Interceptors::ShutdownReturnStatus ret_status = 
                          Interceptors::SHUTDOWN_NO_EXCEPTION;

    m_outfile << "ClientInterceptorSimp::shutdown called" << endl;

    //
    // Output the reason for shutdown.  Usually, it doesn't matter why
    // shutdown is happening, unless there are resources to release.
    // Here is an example of the reasons why shutdown could occur.
    //

    m_outfile << "Shutdown reason: ";
    switch (reason)
    {
    case Interceptors::ORB_SHUTDOWN:
        m_outfile << "ORB_SHUTDOWN" << endl;
        break;
    case Interceptors::CONNECTION_ABORTED:
        m_outfile << "CONNECTION_ABORTED" << endl;
        break;
    case Interceptors::RESOURCES_EXCEEDED:
        m_outfile << "RESOURCES_EXCEEDED" << endl;
        break;
    }
    m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorSimp::id
 
   FUNCTIONAL DESCRIPTION:
        The id accessor operation is used by the ORB to obtain 
        the vendor assigned identity of the interceptor as a string 
        value. This attribute is used primarily for debugging and 
        tracing of operations on the interceptors called by the ORB.
 
***************************************************************/
CORBA::String ClientInterceptorSimp::id()
{
    m_outfile << "ClientInterceptorSimp::id called" << endl << endl;

    //
    // Return a string which identifies this object.
    //
    return CORBA::string_dup("ClientInterceptorSimp");
}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorSimp::exception_occurred 
 
   FUNCTIONAL DESCRIPTION:

        The exception_occurred operation is called on a request-level 
        interceptor implementation when an exception occurred. 
        It is called instead of the <xxx>_response 
        method of that interceptor. The ORB calls this operation to 
        allow the interceptor implementation to clean-up any state 
        that it might have been managing that is specific to a request.
 
***************************************************************/
void ClientInterceptorSimp::exception_occurred (
        const RequestLevelInterceptor::ReplyContext &   reply_context,
        CORBA::Exception_ptr                            excep_val)
{
    m_outfile << "ClientInterceptorSimp::exception_occurred called" << endl;
    m_outfile << "   exception: ";
    if  (excep_val)
       m_outfile << excep_val->get_id() << endl << endl;
    else m_outfile << "NULL exception" << endl << endl;
}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorSimp::client_invoke
 
   FUNCTIONAL DESCRIPTION:

        This operation is called by the ORB anytime that an 
        invocation is being sent to a target object, regardless 
        of whether the target object is in a different address 
        space or the same address space as the target object.

***************************************************************/
Interceptors::InvokeReturnStatus ClientInterceptorSimp::client_invoke (
        const RequestLevelInterceptor::RequestContext &     request_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          request_arg_stream,
        CORBA::DataOutputStream_ptr                         reply_arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{
    Interceptors::InvokeReturnStatus ret_status = 
                       Interceptors::INVOKE_NO_EXCEPTION;

    m_outfile << "ClientInterceptorSimp::client_invoke called" << endl;
    
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
    // The following section shows how to access the data of the
    // request context.  The first part shows the simple data elements
    // of the context.
    //
    m_outfile << "   Request Id = " << request_context.request_id << endl;
    m_outfile << "   Response flags = ";
    if (request_context.response_flags & 0x01)
        m_outfile << "RESPONSE EXPECTED";
    else m_outfile << "NO RESPONSE EXPECTED";
    m_outfile << endl;
    
    m_outfile << "   Interface Id = " << 
                 request_context.interface_id.in() << endl;
    
    m_outfile << "   Operation = " << request_context.operation.in() << endl;
    
    //
    // This part shows how to process the target information contained
    // in the request context. The target information is a discriminated
    // union, with the discriminator indicating the form of the target
    // addressing.
    //
    switch ((CORBA::Short)request_context.target._d())
    {
    case 0:
        {
        //
        // Target addressing is KeyAddr.  Get the object_key and print it out.
        //

        CORBA::ULong buf_size = request_context.target.object_key().length();
        m_outfile << "    KeyAddr address disposition, size = " << buf_size << " data = ";
        char temp_char;
        for (CORBA::ULong j = 0; j < buf_size; j++)
        {
            temp_char = (char) request_context.target.object_key()[j];
            m_outfile << (isprint(temp_char) ? temp_char : '.');
        }
        m_outfile << endl;
        break;
        }
    case 1:
        //
        // Target addressing is ProfileAddr
        //
        m_outfile << "    ProfileAddr address disposition" << endl;
        break;
    case 2:
        //
        // Target addressing is ReferenceAddr
        //
        m_outfile << "    ReferenceAddr address disposition" << endl;
        break;
    default:
        m_outfile << "    UNKNOWN TARGET ADDRESS DISPOSITION" << endl;
        break;
    }
    
    m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       ClientInterceptorSimp::client_response 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that a reply 
        to an invocation is being received by the initiator of 
        the request, regardless of whether the initiator is in 
        a different address space or the same address space as 
        the target object.
  
***************************************************************/
Interceptors::ResponseReturnStatus ClientInterceptorSimp::client_response (
        const RequestLevelInterceptor::ReplyContext &       reply_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{
    Interceptors::ResponseReturnStatus ret_status = 
                          Interceptors::RESPONSE_NO_EXCEPTION;

    m_outfile << "ClientInterceptorSimp::client_response called" << endl;

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
    // The following section shows how to access the data of the
    // reply context.  The first part shows the simple data elements
    // of the context.
    //
    m_outfile << "   Request Id = " << reply_context.request_id << endl;
    m_outfile << "   ReplyStatus = ";
    switch (reply_context.reply_status)
    {
    case GIOP::NO_EXCEPTION:
        m_outfile << "GIOP::NO_EXCEPTION";
        break;
    case GIOP::USER_EXCEPTION:
        m_outfile << "GIOP::USER_EXCEPTION";
        break;
    case GIOP::SYSTEM_EXCEPTION:
        m_outfile << "GIOP::SYSTEM_EXCEPTION";
        break;
    case GIOP::LOCATION_FORWARD:
        m_outfile << "GIOP::LOCATION_FORWARD";
        break;
    case GIOP::LOCATION_FORWARD_PERM:
        m_outfile << "GIOP::LOCATION_FORWARD_PERM";
        break;
    case GIOP::NEEDS_ADDRESSING_MODE:
        m_outfile << "GIOP::NEEDS_ADDRESSING_MODE";
        break;
    default:
        m_outfile << "UNKNOWN";
        break;
    }
    m_outfile << endl << endl;
    
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorSimp::shutdown
 
   FUNCTIONAL DESCRIPTION:

        The shutdown operation is used by the ORB to notify an 
        implementation of an interceptor that the interceptor 
        is being shutdown. The ORB will destroy the instance 
        of the interceptor once control is returned from the
        operation back to the ORB.
 
***************************************************************/
Interceptors::ShutdownReturnStatus TargetInterceptorSimp::shutdown(
        Interceptors::ShutdownReason    reason,
        CORBA::Exception_ptr &          excep_val)
{
    Interceptors::ShutdownReturnStatus ret_status = 
                            Interceptors::SHUTDOWN_NO_EXCEPTION;

    m_outfile << "TargetInterceptorSimp::shutdown called" << endl;

    //
    //  This shows an example of processing the shutdown reasons.  Usually,
    //  the reason for shutdown doesn't matter too much unless the
    //  interceptor has resources to return.
    //

    m_outfile << "Shutdown reason: ";
    switch (reason)
    {
    case Interceptors::ORB_SHUTDOWN:
        m_outfile << "ORB_SHUTDOWN" << endl;
        break;
    case Interceptors::CONNECTION_ABORTED:
        m_outfile << "CONNECTION_ABORTED" << endl;
        break;
    case Interceptors::RESOURCES_EXCEEDED:
        m_outfile << "RESOURCES_EXCEEDED" << endl;
        break;
    }
    m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorSimp::id
 
   FUNCTIONAL DESCRIPTION:

        The id accessor operation is used by the ORB to obtain 
        the vendor assigned identity of the interceptor as a string 
        value. This attribute is used primarily for debugging and 
        tracing of operations on the interceptors called by the ORB.
 
***************************************************************/
CORBA::String TargetInterceptorSimp::id()
{
    m_outfile << "TargetInterceptorSimp::id called" << endl << endl;
    return CORBA::string_dup("TargetInterceptorSimp");
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorSimp::exception_occurred
 
   FUNCTIONAL DESCRIPTION:

        The exception_occurred operation is called on a request-level 
        interceptor implementation when an exception occurs.
        It is called instead of the <xxx>_response 
        method of that interceptor. The ORB calls this operation to 
        allow the interceptor implementation to clean-up any state 
        that it might have been managing that is specific to a request.
 
***************************************************************/
void TargetInterceptorSimp::exception_occurred (
                const RequestLevelInterceptor::ReplyContext &   reply_context,
                CORBA::Exception_ptr                            excep_val)
{
    m_outfile << "TargetInterceptorSimp::exception_occurred called" << endl;
    if  (excep_val)
       m_outfile << "   exception: " << excep_val->get_id() << endl;
    else m_outfile << "   exception: " << "NULL exception " << endl;
    m_outfile << endl;
    return;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorSimp::target_invoke 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that an 
        invocation is being received by a target object, 
        regardless of whether the target object is in a 
        different address space or the same address space 
        as the target object.
 
***************************************************************/
Interceptors::InvokeReturnStatus TargetInterceptorSimp::target_invoke (
        const RequestLevelInterceptor::RequestContext &     request_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          request_arg_stream,
        CORBA::DataOutputStream_ptr                         reply_arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{

    //
    // This interception implementation demonstrates how to access the
    // information available through this function's parameters.  
    // It looks at them, and then returns a status which allows the 
    // invocation to go through.
    //

    Interceptors::InvokeReturnStatus ret_status = 
                            Interceptors::INVOKE_NO_EXCEPTION;

    m_outfile << "TargetInterceptorSimp::target_invoke called" << endl;

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
    // This section shows how to access the fields of the request context.
    // The first part shows access of the simple fields.
    //
    m_outfile << "   Request Id = " << request_context.request_id << endl;
    m_outfile << "   Response flags = ";
    if (request_context.response_flags & 0x01)
        m_outfile << "RESPONSE EXPECTED";
    else m_outfile << "NO RESPONSE EXPECTED";
    m_outfile << endl;
    
    m_outfile << "   Interface Id = " 
              << request_context.interface_id.in() << endl;
    m_outfile << "   Operation = " 
              << request_context.operation.in() << endl;
    

    //
    // This part shows how to process the target information contained
    // in the request context. The target information is a discriminated
    // union, with the discriminator indicating the form of the target
    // addressing.
    //
    switch ((CORBA::Short)request_context.target._d())
    {
    case 0:
        {
        //
        // KeyAddr addressing disposition
        //

        CORBA::ULong buf_size = request_context.target.object_key().length();
        m_outfile << "    KeyAddr address disposition, size = " 
                << buf_size << " data = ";
        char temp_char;
        for (CORBA::ULong j = 0; j < buf_size; j++)
        {
            temp_char = (char) request_context.target.object_key()[j];
            m_outfile << (isprint(temp_char) ? temp_char : '.');
        }
        m_outfile << endl;
        break;
        }
    case 1:
        //
        // ProfileAddr addressing disposition
        //
        m_outfile << "    ProfileAddr address disposition" << endl;
        break;
    case 2:
        //
        // ReferenceAddr addressing disposition
        //
        m_outfile << "    ReferenceAddr address disposition" << endl;
        break;
    default:
        m_outfile << "    UNKNOWN TARGET ADDRESS DISPOSITION" << endl;
        break;
    }
    
    m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       TargetInterceptorSimp::target_response 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that a reply 
        to an invocation is being sent to the initiator of the 
        request, regardless of whether the initiator is in a 
        different address space or the same address space as 
        the target object.
 
***************************************************************/
Interceptors::ResponseReturnStatus TargetInterceptorSimp::target_response (
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

    m_outfile << "TargetInterceptorSimp::target_response called" << endl;
    

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
    // This section shows an example of accessing the fields of the reply
    // context.  They are all simple data types.
    //
    m_outfile << "   Request Id = " << reply_context.request_id << endl;
    
    m_outfile << "   ReplyStatus = ";
    switch (reply_context.reply_status)
    {
    case GIOP::NO_EXCEPTION:
        m_outfile << "GIOP::NO_EXCEPTION";
        break;
    case GIOP::USER_EXCEPTION:
        m_outfile << "GIOP::USER_EXCEPTION";
        break;
    case GIOP::SYSTEM_EXCEPTION:
        m_outfile << "GIOP::SYSTEM_EXCEPTION";
        break;
    case GIOP::LOCATION_FORWARD:
        m_outfile << "GIOP::LOCATION_FORWARD";
        break;
    case GIOP::LOCATION_FORWARD_PERM:
        m_outfile << "GIOP::LOCATION_FORWARD_PERM";
        break;
    case GIOP::NEEDS_ADDRESSING_MODE:
        m_outfile << "GIOP::NEEDS_ADDRESSING_MODE";
        break;
    default:
        m_outfile << "UNKNOWN";
        break;
    }
    m_outfile << endl << endl;
    
    return ret_status;
}


/*************************************************************

   FUNCTION NAME:       OpenStream

   FUNCTIONAL DESCRIPTION:
        Opens the output stream for logging interceptor activity.

***************************************************************/
int  OpenStream(char *InterceptorType, ofstream *outfile)
{
    char outfilename_prefix[] = "InterceptorSimp";
    char outfilename[100];
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
    strcat (outfilename, InterceptorType);
    strcat (outfilename, unique_ascii);
    strcat (outfilename, ".out");

    outfile->open( outfilename, (ios::out ) );

    // This shouldn't happen, but we're paranoid
    if  (!outfile->rdbuf() || !outfile->rdbuf()->is_open()) {
        //
        // this really won't get printed if this is in a Tuxedo server
        //
        cout <<
          "Interceptor INIT: ERROR Can't create output stream to trace" <<
          endl;
        return CORBA_FALSE;
     }
    return CORBA_TRUE;

}


