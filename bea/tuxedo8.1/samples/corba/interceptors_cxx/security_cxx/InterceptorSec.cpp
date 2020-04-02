//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// InterceptorSec.cpp
//
// C++ program for the security interceptor samples
//
// Implements the security interceptor client and target classes
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////
// For this version of Tuxedo, the ORB will always pass nil         //
// references for parameters ServiceContextList, and                //
// CORBA::DataOutputStream.  You should not use or reference        //
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
#include "InterceptorSec.h"

void OpenStream(char *, ofstream **);

#define SECURITY_BUFFSIZE   100

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

   FUNCTION NAME:       InterceptorSecInit
 
   FUNCTIONAL DESCRIPTION:
 
        Initialization routine called by the ORB during initialization.
        This routine will create and return instances of the 
        InterceptorSecClient and InterceptorSecTarget classes it supports.

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
InterceptorSecInit(
    CORBA::ORB_ptr                                       TheORB,
    RequestLevelInterceptor::ClientRequestInterceptor ** ClientPtr,
    RequestLevelInterceptor::TargetRequestInterceptor ** TargetPtr,
    CORBA::Boolean *                                     RetStatus)
{

    //
    //
    //  Create the Client object
    //
    InterceptorSecClient * client = new InterceptorSecClient(TheORB);
    if  (!client)
    {
        cout << 
                "InterceptorSecInit: Client class creation failed" << 
                endl << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }


    //
    // Open two output streams to log interceptor activity, one for the
    // client and one for the target.
    //
    OpenStream((char *)"Client", &client->m_outfile);
    if (!client->m_outfile)
    {
        //
        // this really won't get printed if this is in a Tuxedo server
        //
        cout << "InterceptorSecInit: ERROR Can't create client output stream to trace" << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }
    (*client->m_outfile) << "InterceptorSecInit called" << endl;
    

    //
    // Create the Target object.  This implementation provides a member
    // function that verifies the object was able to initialize properly.
    //
    InterceptorSecTarget * target = new InterceptorSecTarget(TheORB);
    if  (!target)
    {
        cout << "InterceptorSecInit: Target class creation failed" 
               << endl << endl;
        delete client;
        *RetStatus = CORBA_FALSE;
        return;
    }

    OpenStream((char *)"Target", &target->m_outfile);
    if (!target->m_outfile)
    {
        //
        // this really won't get printed if this is in a Tuxedo server
        //
        cout << "InterceptorSecInit: ERROR Can't create target output stream to trace" << endl;
        *RetStatus = CORBA_FALSE;
        return;
    }
    
    (*target->m_outfile) << "InterceptorSecInit called" << endl;

    *ClientPtr = client;
    *TargetPtr = target;
    *RetStatus = CORBA_TRUE;
    return;
}


/*************************************************************

   FUNCTION NAME:       InterceptorSecClient::shutdown
 
   FUNCTIONAL DESCRIPTION:
 
        The shutdown operation is used by the ORB to notify an 
        implementation of an interceptor that the interceptor 
        is being shutdown. The ORB will destroy the instance 
        of the interceptor once control is returned from the
        operation back to the ORB.

***************************************************************/

Interceptors::ShutdownReturnStatus InterceptorSecClient::shutdown(
    Interceptors::ShutdownReason    reason,
    CORBA::Exception_ptr &          excep_val)
{
    Interceptors::ShutdownReturnStatus ret_status = Interceptors::SHUTDOWN_NO_EXCEPTION;
    *m_outfile << "InterceptorSecClient::shutdown called" << endl;

    //
    // Output the reason for shutdown.  Usually, it doesn't matter why
    // shutdown is happening, unless there are resources to release.
    // Here is an example of the reasons why shutdown could occur.
    //
    *m_outfile << "Shutdown reason: ";
    switch (reason)
    {
    case Interceptors::ORB_SHUTDOWN:
        *m_outfile << "ORB_SHUTDOWN" << endl;
        break;
    case Interceptors::CONNECTION_ABORTED:
        *m_outfile << "CONNECTION_ABORTED" << endl;
        break;
    case Interceptors::RESOURCES_EXCEEDED:
        *m_outfile << "RESOURCES_EXCEEDED" << endl;
        break;
    }
    *m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecClient::id
 
   FUNCTIONAL DESCRIPTION:
        The id accessor operation is used by the ORB to obtain 
        the vendor assigned identity of the interceptor as a string 
        value. This attribute is used primarily for debugging and 
        tracing of operations on the interceptors called by the ORB.
 
***************************************************************/
CORBA::String InterceptorSecClient::id()
{
    *m_outfile << "InterceptorSecClient::id called" << endl << endl;

    //
    // Return a string which identifies this object.
    //
    return CORBA::string_dup("InterceptorSecClient");
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecClient::exception_occurred 
 
   FUNCTIONAL DESCRIPTION:

        The exception_occurred operation is called on a request-level 
        interceptor implementation when an exception occurs.
        It is called instead of the <xxx>_response 
        method of that interceptor. The ORB calls this operation to 
        allow the interceptor implementation to clean-up any state 
        that it might have been managing that is specific to a request.
 
***************************************************************/
void InterceptorSecClient::exception_occurred (
        const RequestLevelInterceptor::ReplyContext &   reply_context,
        CORBA::Exception_ptr                            excep_val)
{
    *m_outfile << "InterceptorSecClient::exception_occurred called" << endl;
    *m_outfile << "    exception: ";
    if (excep_val)
       *m_outfile << excep_val->get_id() << endl << endl;
    else *m_outfile << "NULL exception" << endl << endl;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecClient::client_invoke
 
   FUNCTIONAL DESCRIPTION:

        This operation is called by the ORB anytime that an 
        invocation is being sent to a target object, regardless 
        of whether the target object is in a different address 
        space or the same address space as the target object.

***************************************************************/
Interceptors::InvokeReturnStatus InterceptorSecClient::client_invoke (
        const RequestLevelInterceptor::RequestContext &   request_context,
        RequestLevelInterceptor::ServiceContextList_ptr   service_context,
        CORBA::DataInputStream_ptr                        request_arg_stream,
        CORBA::DataOutputStream_ptr                       reply_arg_stream,
        CORBA::Exception_ptr &                            excep_val)
{
    Interceptors::InvokeReturnStatus ret_status = 
                          Interceptors::INVOKE_NO_EXCEPTION;

    *m_outfile << "InterceptorSecClient::client_invoke called" << endl;

    //
    // If major version is more than we support, we can't make any 
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions 
    // to the structure should be at the end and we should be able 
    // to look at the pieces we know about.
    //
    if  (request_context.struct_version.major_version > 1)
    {
        *m_outfile << "ERROR: Struct major version greater than the supported version" << endl << endl;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::REPLY_EXCEPTION;
    }
    else if  (request_context.struct_version.minor_version > 0)
        *m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;

    //
    // The following section shows how to access the data of the
    // request context.  The first part shows the simple data elements
    // of the context.
    //
    *m_outfile << "   Request Id = " << request_context.request_id << endl;
    *m_outfile << "   Response flags = ";
    if (request_context.response_flags & 0x01)
        *m_outfile << "RESPONSE EXPECTED";
    else *m_outfile << "NO RESPONSE EXPECTED";
    *m_outfile << endl;

    *m_outfile << "   Interface Id = " << request_context.interface_id << endl;

    *m_outfile << "   Operation = " << request_context.operation << endl;

    *m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecClient::client_response 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that a reply 
        to an invocation is being received by the initiator of 
        the request, regardless of whether the initiator is in 
        a different address space or the same address space as 
        the target object.
  
***************************************************************/
Interceptors::ResponseReturnStatus InterceptorSecClient::client_response (
        const RequestLevelInterceptor::ReplyContext &     reply_context,
        RequestLevelInterceptor::ServiceContextList_ptr   service_context,
        CORBA::DataInputStream_ptr                        arg_stream,
        CORBA::Exception_ptr &                            excep_val)
{
    Interceptors::ResponseReturnStatus ret_status = 
                       Interceptors::RESPONSE_NO_EXCEPTION;

    *m_outfile << "InterceptorSecClient::client_response called" << endl;

    //
    // If major version is more than we support, we can't make any 
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions 
    // to the structure should be at the end and we should be able 
    // to look at the pieces we know about.
    //
    if  (reply_context.struct_version.major_version > 1)
    {
        *m_outfile << "ERROR: Struct major version greater than the supported version" << endl << endl;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::RESPONSE_EXCEPTION;
    }
    else if  (reply_context.struct_version.minor_version > 0)
        *m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;


    //
    // The following section shows how to access the data of the
    // reply context.  The first part shows the simple data elements
    // of the context.
    //

    *m_outfile << "   Request Id = " << reply_context.request_id << endl;
    *m_outfile << "   ReplyStatus = ";
    switch (reply_context.reply_status)
    {
    case GIOP::NO_EXCEPTION:
        *m_outfile << "GIOP::NO_EXCEPTION";
        break;
    case GIOP::USER_EXCEPTION:
        *m_outfile << "GIOP::USER_EXCEPTION";
        break;
    case GIOP::SYSTEM_EXCEPTION:
        *m_outfile << "GIOP::SYSTEM_EXCEPTION";
        break;
    case GIOP::LOCATION_FORWARD:
        *m_outfile << "GIOP::LOCATION_FORWARD";
        break;
    case GIOP::LOCATION_FORWARD_PERM:
        *m_outfile << "GIOP::LOCATION_FORWARD_PERM";
        break;
    case GIOP::NEEDS_ADDRESSING_MODE:
        *m_outfile << "GIOP::NEEDS_ADDRESSING_MODE";
        break;
    default:
        *m_outfile << "UNKNOWN";
        break;
    }
    *m_outfile << endl << endl;

    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecTarget constructor
 
   FUNCTIONAL DESCRIPTION:
  
	This implementation shows an example of obtaining user
	information for verification before dispatching to the
        server's method.  To do this, the constructor defines
	the security attributes that will be obtained in order
	to verify the user wanting to access the server
	implementation.
	

***************************************************************/
InterceptorSecTarget::InterceptorSecTarget(
                           CORBA::ORB_ptr TheOrb) :
    m_orb(TheOrb),
    m_security_current(0),
    m_attributes_to_get(0),
    m_outfile(0)
{

    //
    // Create the list of attributes that is used to query the security
    // information during an invoke.
    //
    Security::AttributeTypeList_var attr = new Security::AttributeTypeList(2);
    if (!attr.ptr())
    {
        cout << 
                "ERROR: can't allocation security list: Out of memory" 
                << endl << endl << flush;
        return;
    }
    attr.inout().length(2);
    attr[(CORBA::ULong)0].attribute_family.family_definer = 0;
    attr[(CORBA::ULong)0].attribute_family.family = 1;
    attr[(CORBA::ULong)0].attribute_type = Security::PrimaryGroupId;
    attr[(CORBA::ULong)1].attribute_family.family_definer = 0;
    attr[(CORBA::ULong)1].attribute_family.family = 1;
    attr[(CORBA::ULong)1].attribute_type = Security::AccessId;
    m_attributes_to_get = attr._retn();
    return;
}


/*************************************************************

   FUNCTION NAME:       InterceptorSecTarget::shutdown
 
   FUNCTIONAL DESCRIPTION:

        The shutdown operation is used by the ORB to notify an 
        implementation of an interceptor that the interceptor 
        is being shutdown. The ORB will destroy the instance 
        of the interceptor once control is returned from the
        operation back to the ORB.
 
***************************************************************/
Interceptors::ShutdownReturnStatus InterceptorSecTarget::shutdown(
        Interceptors::ShutdownReason    reason,
        CORBA::Exception_ptr &          excep_val)
{
    Interceptors::ShutdownReturnStatus ret_status = 
                               Interceptors::SHUTDOWN_NO_EXCEPTION;
    *m_outfile << "InterceptorSecTarget::shutdown called" << endl;

    //
    //  This shows an example of processing the shutdown reasons.  Usually,
    //  the reason for shutdown doesn't matter too much unless the
    //  interceptor has resources to return.
    //
 
    *m_outfile << "Shutdown reason: ";
    switch (reason)
    {
    case Interceptors::ORB_SHUTDOWN:
        *m_outfile << "ORB_SHUTDOWN" << endl;
        break;
    case Interceptors::CONNECTION_ABORTED:
        *m_outfile << "CONNECTION_ABORTED" << endl;
        break;
    case Interceptors::RESOURCES_EXCEEDED:
        *m_outfile << "RESOURCES_EXCEEDED" << endl;
        break;
    }
    *m_outfile << endl;
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecTarget::id
 
   FUNCTIONAL DESCRIPTION:

        The id accessor operation is used by the ORB to obtain 
        the vendor assigned identity of the interceptor as a string 
        value. This attribute is used primarily for debugging and 
        tracing of operations on the interceptors called by the ORB.
 
***************************************************************/
CORBA::String InterceptorSecTarget::id()
{
    *m_outfile << "InterceptorSecTarget::id called" << endl << endl;
    return CORBA::string_dup("InterceptorSecTarget");
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecTarget::exception_occurred
 
   FUNCTIONAL DESCRIPTION:

        The exception_occurred operation is called on a request-level 
        interceptor implementation when another interceptor sets an 
        exception (rather than an exception being generated by the 
        ORB or the method). It is called instead of the <xxx>_response 
        method of that interceptor. The ORB calls this operation to 
        allow the interceptor implementation to clean-up any state 
        that it might have been managing that is specific to a request.
 
***************************************************************/
void InterceptorSecTarget::exception_occurred (
        const RequestLevelInterceptor::ReplyContext &   reply_context,
        CORBA::Exception_ptr                            excep_val)
{
    *m_outfile << "InterceptorSecTarget::exception_occurred called" << endl;
    *m_outfile << "   exception: ";
    if  (excep_val)
       *m_outfile << excep_val->get_id() << endl << endl;
    else *m_outfile << "NULL exception " << endl << endl;
    return;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecTarget::target_invoke 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that an 
        invocation is being received by a target object, 
        regardless of whether the target object is in a 
        different address space or the same address space 
        as the target object.
 
***************************************************************/
Interceptors::InvokeReturnStatus InterceptorSecTarget::target_invoke (
        const RequestLevelInterceptor::RequestContext &     request_context,
        RequestLevelInterceptor::ServiceContextList_ptr     service_context,
        CORBA::DataInputStream_ptr                          request_arg_stream,
        CORBA::DataOutputStream_ptr                         reply_arg_stream,
        CORBA::Exception_ptr &                              excep_val)
{

    //
    // Set the return status to assume the invocation should go through.
    //
    Interceptors::InvokeReturnStatus ret_status = 
                                Interceptors::INVOKE_NO_EXCEPTION;
    int intf_auth = CORBA_FALSE;
    int username_ok = 0;
    int clientname_ok = 0;

    *m_outfile << "InterceptorSecTarget::target_invoke called" << endl;

    //
    // We only do authorization with the interceptor
    // sample application.  Check the interface being called.
    // Update to use get_interface method!
    //
    intf_auth = (strcmp(request_context.interface_id.in(), 
                        PersonQuery::_get_interface_name()) == 0);

    // Get the security current if we don't have it yet.
    // NOTE! This interceptor will ONLY work with the NATIVE server 
    // since that is the only one that will register a SecurityCurrent 
    // with the ORB.
    if  ((!m_security_current) && intf_auth)
    {
        CORBA::Object_var sec_current = 0;
        
        //
        // The return status for any exceptions tells the ORB that
        // an exception has occurred and that the invocation should
        // not take place.
        //
        try
        {
            sec_current = m_orb->resolve_initial_references("SecurityCurrent");
        }
        catch (...)
        {
            *m_outfile << 
                    "ERROR: ORB::resolve_initial_references threw exception" 
                    << endl << endl << flush;
            excep_val = new CORBA::UNKNOWN();
            return Interceptors::REPLY_EXCEPTION;
        }
        
        if  (CORBA::is_nil(sec_current.in()))
        {
            *m_outfile << "ERROR: No SecurityCurrent present"  
                    << endl << endl << flush;
            excep_val = new CORBA::NO_PERMISSION();
            return Interceptors::REPLY_EXCEPTION;
        }
        
        m_security_current = SecurityLevel1::Current::_narrow(sec_current.in());
        if  (!m_security_current)
        {
            *m_outfile << "ERROR: Couldn't narrow security current to SecurityLevel1::Current" 
                    << endl << endl << flush;
            excep_val = new CORBA::NO_PERMISSION();
            return Interceptors::REPLY_EXCEPTION;
        }
        
        *m_outfile << "   Successfully retrieved and narrowed SecurityCurrent" << endl;
    }

    // If major version is more than we support, we can't make any 
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions 
    // to the structure should be at the end and we should be able to 
    // look at the pieces we know about.
    if  (request_context.struct_version.major_version > 1)
    {
        *m_outfile << "ERROR: Struct major version greater than the supported version"             << endl << endl << flush;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::REPLY_EXCEPTION;
    }
    else if  (request_context.struct_version.minor_version > 0)
        *m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;
    
    //
    // This section shows how to access the fields of the request context.
    // The first part shows access of the simple fields.
    //
    *m_outfile << "   Request Id = " << request_context.request_id << endl;
    *m_outfile << "   Response flags = ";
    if (request_context.response_flags & 0x01)
        *m_outfile << "RESPONSE EXPECTED";
    else *m_outfile << "NO RESPONSE EXPECTED";
    *m_outfile << endl;

    *m_outfile << "   Interface Id = " 
               << request_context.interface_id.in() << endl;
    *m_outfile << "   Operation = " << request_context.operation.in() << endl;
    
    //
    // This interceptor only authorizes users for one specific interface.
    // Any other interface usage is allowed to go thru.
    //
    if (intf_auth)
    {
       // Verify the information from the security current matches what we
       // are expecting.
    
       // Get the attributes that correspond to the information that we need to
       // do an authorization check:
       //      PrimaryGroupId (clientname of the logged in client)
       //      AccessId (username of the logged in client)
       Security::AttributeList_var client_attr = 0;
       try
       {
           //
           // In the constructor, we initialized the attributes to get 
           // only the ones we are interested in, however, if the 
           // allocation failed, just get them all here, by setting
           // the attribute list to zero.
           //
           if (!m_attributes_to_get)
           {
             Security::AttributeTypeList attr;
             const Security::AttributeTypeList * attr_ptr = &attr;
	     attr.length(0);
             client_attr = m_security_current->get_attributes(attr);
           }
           else {
             client_attr = 
                m_security_current->get_attributes(*m_attributes_to_get);
           }
             
       }
       catch (CORBA::SystemException & exc)
       {
           *m_outfile << "    CORBA::SystemException caught during get_attributes call" << endl;
           *m_outfile << "      exception: " << exc.get_id() << endl << endl << flush;
           excep_val = new CORBA::SystemException(exc);
           return Interceptors::REPLY_EXCEPTION;
       }
       catch (...)
       {
           *m_outfile << "    Unknown Exception caught during get_attributes call" 
                   << endl << endl << flush;
           excep_val = new CORBA::UNKNOWN();
           return Interceptors::REPLY_EXCEPTION;
       }
    
       //
       // Since this is an example of one possible use of interceptors, we
       // could validate the security attributes as shown below. However,
       // this implementation doesn't store access control information and so
       // cannot do a reasonable verification for all possible users.  It is
       // likely that this interceptor will reject all comers, since it
       // compares against a single randomly chosen username and groupname.
       // If you want to see this actually work, you should use your own
       // user and group names.
       // 
       if  ((!client_attr.ptr()) || (client_attr->length() == 0))
       {
           //
           // This condition short-circuits the invocation, because it
           // returns an exception on the reply.
           //
           *m_outfile << "    ERROR: Security attributes not retrieved" 
                   << endl << endl << flush;
           excep_val = new CORBA::NO_PERMISSION();
           return Interceptors::REPLY_EXCEPTION;
       }
    
       //
       // Show how many attributes were returned, just for curiosity sake.
       //
       *m_outfile << "   " << client_attr->length() << 
                     " attributes were returned." << endl;

       //
       // This section shows how to verify the attributes returned.
       // Note that if there were no attributes returned, this loop will do
       // nothing.
       //
       char value_buffer[SECURITY_BUFFSIZE];

       for  (CORBA::ULong i=0; i<client_attr->length(); i++)
       {
           // Verify the family and definer are valid
           if  ((client_attr[i].attribute_type.attribute_family.family != 1) ||
               (client_attr[i].attribute_type.attribute_family.family_definer != 0))
           {
               *m_outfile << "    ERROR: Invalid attribute type returned." 
                       << endl << endl << flush;
               continue;
           }
        
           //
           // Now check the values. Note a real implementation would have 
           // more elaborate checks here. It could say that a specific 
           // user can access certain methods on certain interfaces, 
           // for example.
           //
           //
           // Check the length of the attribute returned.  If it is zero,
           // this attribute contains nothing.  Just skip it and go on to
           // the next one.
           //
           CORBA::ULong ll = client_attr[i].value.length();
           if ( ll <= 0 )
             continue;

           //
           // Get a copy of the attribute value, for simpler handling.
           //
           for (CORBA::ULong k=0; k < ll; k++)
            value_buffer[k] = client_attr[i].value[k];


           //
           // The verification depends upon what type of attribute this element
           // contains.
           //
           if  (client_attr[i].attribute_type.attribute_type == Security::PrimaryGroupId)
           {
               //
               // This attribute is the client name. Compare to a name value. 
               // For this example, we're going to accept anything with
               // an 'r' in it, or a NULL string.  You will want to compare
               // the client name to some set of values you have authorized.
               //
               if  ((strlen(value_buffer) == 0) ||
                    (strchr(value_buffer, 'r') != 0))
               { 
                   *m_outfile << "    INFO: Valid client name found: " 
                              << value_buffer << endl;
                   clientname_ok = 1;
               }
               else
               {
                   *m_outfile << "    ERROR: Invalid client name found: " 
                           << value_buffer << endl;
               }
           }
           else if (client_attr[i].attribute_type.attribute_type == Security::AccessId)
           {
               // This attribute is the user name.  We're arbitrarily
               // choosing to authorize anyone who has an 'r', 'n', or 'p'
               // in their user id.  You will likely want to choose
               // some other criteria for authorization.
               //
               if  ((strchr(value_buffer, 'r') != 0) ||
                    (strchr(value_buffer, 'R') != 0) ||
                    (strchr(value_buffer, 'P') != 0) ||
                    (strchr(value_buffer, 'p') != 0) ||
                    (strchr(value_buffer, 'N') != 0) ||
                    (strchr(value_buffer, 'n') != 0))
               {
                   *m_outfile << "    INFO: Valid username found: " 
                              << value_buffer << endl;
                   username_ok = 1;
               }
               else
               {
                   *m_outfile << "    ERROR: Invalid username found: " 
                              << value_buffer << endl;
               }
           }
       }
    }
    else {
       //
       // This is not an interface we care about, so allow the invoke
       // thru.  This looks contradictory, but this particular interceptor
       // cares about authorizing users for a specific interface.  This
       // will allow applications that don't call this interface to work
       // as they normally would.  Some other interceptor may implement
       // authorization for them.
       //
       username_ok = 1;
       clientname_ok = 1;
    }
    
    //
    // Since this is an example implementation of a target interceptor, we
    // could post different kinds of errors.  The important point is how to
    // notify the ORB that this interceptor detected an exception and that
    // the invocation should not go through.
    //
    // A security interceptor should decide at this point whether verification
    // succeeded.  If you did not update the user and client to which the
    // security attributes were compared, you will get an error output from
    // the following code.  This short-circuits the invocation and the
    // server method is not called.
    //
    
    if  ((username_ok == 0) || (clientname_ok == 0))
    {
        *m_outfile << "    ERROR: Username and/or Clientname not authorized for access" << endl << endl << flush;
        excep_val = new CORBA::NO_PERMISSION();
        return Interceptors::REPLY_EXCEPTION;
    }
    
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecTarget::target_response 
 
   FUNCTIONAL DESCRIPTION:

        The operation is called by the ORB anytime that a reply 
        to an invocation is being sent to the initiator of the 
        request, regardless of whether the initiator is in a 
        different address space or the same address space as 
        the target object.
 
***************************************************************/
Interceptors::ResponseReturnStatus InterceptorSecTarget::target_response (
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

    *m_outfile << "InterceptorSecTarget::target_response called" << endl;

    // If major version is more than we support, we can't make any 
    // assumptions about compatability so this is an error.
    // If minor version is more than we support, then any additions 
    // to the structure should be at the end and we should be able to 
    // look at the pieces we know about.
    if  (reply_context.struct_version.major_version > 1)
    {
        *m_outfile << "ERROR: Struct major version greater than the supported version" << endl << endl << flush;
        excep_val = new CORBA::NO_IMPLEMENT();
        return Interceptors::RESPONSE_EXCEPTION;
    }
    else if  (reply_context.struct_version.minor_version > 0)
        *m_outfile << "WARNING: Struct minor version greater than the supported version" << endl;
    


    //
    // This section shows an example of accessing the fields of the reply
    // context.  They are all simple data types.
    //
    *m_outfile << "   Request Id = " << reply_context.request_id << endl;
    
    *m_outfile << "   ReplyStatus = ";
    switch (reply_context.reply_status)
    {
    case GIOP::NO_EXCEPTION:
        *m_outfile << "GIOP::NO_EXCEPTION";
        break;
    case GIOP::USER_EXCEPTION:
        *m_outfile << "GIOP::USER_EXCEPTION";
        break;
    case GIOP::SYSTEM_EXCEPTION:
        *m_outfile << "GIOP::SYSTEM_EXCEPTION";
        break;
    case GIOP::LOCATION_FORWARD:
        *m_outfile << "GIOP::LOCATION_FORWARD";
        break;
    case GIOP::LOCATION_FORWARD_PERM:
        *m_outfile << "GIOP::LOCATION_FORWARD_PERM";
        break;
    case GIOP::NEEDS_ADDRESSING_MODE:
        *m_outfile << "GIOP::NEEDS_ADDRESSING_MODE";
        break;
    default:
        *m_outfile << "UNKNOWN";
        break;
    }
    *m_outfile << endl << endl;
    
    return ret_status;
}

/*************************************************************

   FUNCTION NAME:       InterceptorSecTarget destructor
 
   FUNCTIONAL DESCRIPTION:
 
***************************************************************/
InterceptorSecTarget::~InterceptorSecTarget()
{
    if  (m_attributes_to_get)
        delete m_attributes_to_get;
    if (m_outfile)
        delete m_outfile;
    CORBA::release(m_security_current);
}

/*************************************************************

   FUNCTION NAME:       OpenStream
 
   FUNCTIONAL DESCRIPTION:
	Opens the output stream for logging interceptor activity.
 
***************************************************************/
void OpenStream(char *InterceptorType,  ofstream **outfile)
{
    char outfilename_prefix[] = "InterceptorSec";
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

    (*outfile) = new  ofstream();
    if (!(*outfile))
    {
        cout << 
          "Interceptor INIT: ERROR: Can't create output stream for tracing" << 
          endl;
        return;
    }  

    (*outfile)->open( outfilename, ( ios::out ) );

    // This shouldn't happen, but we're paranoid
    if  (!(*outfile)->rdbuf() || !(*outfile)->rdbuf()->is_open()) {
        //
        // this really won't get printed if this is in a Tuxedo server
        //
        cout << 
          "Interceptor INIT: ERROR Can't create output stream to trace" << 
          endl;
        *outfile = NULL;
     }
    return;

}

