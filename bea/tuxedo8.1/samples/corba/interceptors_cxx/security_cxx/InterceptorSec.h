
//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// InterceptorSec.h
//
// C++ include for the security interceptor samples
//
// Defines the security interceptor client and target classes
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <CORBA.h>
#include <RequestLevelInterceptor.h>
#include <security_c.h>

class InterceptorSecClient : public virtual RequestLevelInterceptor::ClientRequestInterceptor
{

public:
    InterceptorSecClient(CORBA::ORB_ptr TheOrb) : 
                    m_outfile(0), m_orb(TheOrb) {}
    ~InterceptorSecClient() { if (m_outfile) delete m_outfile; }
    Interceptors::ShutdownReturnStatus shutdown(
        Interceptors::ShutdownReason reason,
        CORBA::Exception_ptr & excep_val);
    CORBA::String id();
    void exception_occurred (
        const RequestLevelInterceptor::ReplyContext & reply_context,
        CORBA::Exception_ptr excep_val);
    Interceptors::InvokeReturnStatus client_invoke (
        const RequestLevelInterceptor::RequestContext & request_context,
        RequestLevelInterceptor::ServiceContextList_ptr service_context,
        CORBA::DataInputStream_ptr request_arg_stream,
        CORBA::DataOutputStream_ptr reply_arg_stream,
        CORBA::Exception_ptr & excep_val);
    Interceptors::ResponseReturnStatus client_response (
        const RequestLevelInterceptor::ReplyContext & reply_context,
        RequestLevelInterceptor::ServiceContextList_ptr service_context,
        CORBA::DataInputStream_ptr arg_stream,
        CORBA::Exception_ptr & excep_val);

    ofstream *m_outfile;
    
private:
    InterceptorSecClient() {}
    CORBA::ORB_ptr  m_orb;
};

class InterceptorSecTarget : public virtual RequestLevelInterceptor::TargetRequestInterceptor
{

public:
    InterceptorSecTarget(CORBA::ORB_ptr TheOrb); 
    ~InterceptorSecTarget();
    Interceptors::ShutdownReturnStatus shutdown(
        Interceptors::ShutdownReason reason,
        CORBA::Exception_ptr & excep_val);
    CORBA::String id();
    void exception_occurred (
        const RequestLevelInterceptor::ReplyContext & reply_context,
        CORBA::Exception_ptr excep_val);
    Interceptors::InvokeReturnStatus target_invoke (
        const RequestLevelInterceptor::RequestContext & request_context,
        RequestLevelInterceptor::ServiceContextList_ptr service_context,
        CORBA::DataInputStream_ptr request_arg_stream,
        CORBA::DataOutputStream_ptr reply_arg_stream,
        CORBA::Exception_ptr & excep_val);
    Interceptors::ResponseReturnStatus target_response (
        const RequestLevelInterceptor::ReplyContext & reply_context,
        RequestLevelInterceptor::ServiceContextList_ptr service_context,
        CORBA::DataInputStream_ptr arg_stream,
        CORBA::Exception_ptr & excep_val);
    
    ofstream *m_outfile;

private:
    InterceptorSecTarget() {}
    CORBA::ORB_ptr  m_orb;
    SecurityLevel1::Current_ptr m_security_current;
    Security::AttributeTypeList * m_attributes_to_get;

};

