
//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// InterceptorSimp.h
//
// C++ include for the simple interceptor samples
//
// Defines the simple interceptor client and target classes
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <CORBA.h>
#include <RequestLevelInterceptor.h>

class ClientInterceptorSimp : public virtual RequestLevelInterceptor::ClientRequestInterceptor
{
    public:
        ClientInterceptorSimp(CORBA::ORB_ptr TheOrb) :
                                        m_orb(TheOrb) {}
        ~ClientInterceptorSimp() {}

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
        ofstream m_outfile;

    private:
        ClientInterceptorSimp() {}
        CORBA::ORB_ptr  m_orb;
};

class TargetInterceptorSimp : public virtual RequestLevelInterceptor::TargetRequestInterceptor
{
    public:
        TargetInterceptorSimp(CORBA::ORB_ptr TheOrb) :
                                       m_orb(TheOrb) {}
        ~TargetInterceptorSimp() {  }

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
        ofstream m_outfile;

    private:
        TargetInterceptorSimp() {}
        CORBA::ORB_ptr  m_orb;
};

