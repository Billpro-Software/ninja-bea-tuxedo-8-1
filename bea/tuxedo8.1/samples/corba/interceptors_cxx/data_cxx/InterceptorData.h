//--------------------------------------------------------------------
//	(c) 2003 BEA Systems, Inc. All Rights Reserved.
//
// InterceptorData.h
//
// C++ include for the data stream interceptor samples
//
// Defines the data stream interceptor client and target classes
//
// BEA Systems Inc. sample code
//
//--------------------------------------------------------------------

#include <CORBA.h>
#include <RequestLevelInterceptor.h>

//
// This class is used to identify the operation and process the
// interceptor's CORBA::DataInputStream parameters. The contents
// of the DataInputStream is specific to the interface and operation being
// invoked upon;  this class is responsible for "knowing" the PersonQuery
// interface provided with the interceptor samples.
class PQ
{
public:
        PQ() {}
        virtual ~PQ() {}

        // the operations of the PersonQuery interface.
        enum op_key {Unknown, ByPerson, ByName, ByAddress, BySS, ByAge, BySex,
                     ByMarriage, ByHobby, Bydob, ByHeight, ByWeight,
                     ByHairColor, BySkinColor, ByEyeColor, ByOther, Exit};

        // function to figure out which operation is being invoked upon.  The
        // DataInputStream is specific to the operation.
        op_key MapOperation(const char *op);

        void GetPossibles(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::Possibles_ptr *p,
                         CORBA::Boolean             *r);

        void GetByPerson(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::Person        *p);

        void GetByNameOrSS(
                         CORBA::DataInputStream_ptr s, 
                         char                       **str);

        void GetByAddress(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::Address       *addr);

        void GetBySex(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::SEX           *sex);

        void GetByAgeOrHeight(
                         CORBA::DataInputStream_ptr s, 
                         CORBA::Short               *age);

        void GetByMarriage(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::MARRIAGE      *mar);

        void GetByHobby(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::HOBBIES       *hob);

        void GetByDob(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::Date          *d);

        void GetByWeight(
                         CORBA::DataInputStream_ptr s, 
                         CORBA::Long                *wt);

        void GetByColor(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::COLOR         *color);

        void GetByOther(
                         CORBA::DataInputStream_ptr s, 
                         PersonQuery::MARKINGS      *marks);


private:
        void get_addr(CORBA::DataInputStream_ptr s,
                      PersonQuery::Address *a);
        void get_dob (CORBA::DataInputStream_ptr s,
                      PersonQuery::Date *d);

};
 
//
// RequestInfo holds the information needed to track a request
//

class RequestInfo
{
    public:
        RequestInfo(CORBA::ULong id, const char * op, const char * intf)
          : m_req_id(id), m_operation(op), m_interface_id(intf), m_next(0) { }

        inline CORBA::ULong id() const   { return m_req_id;            }
        inline const char * op() const   { return m_operation.in();    }
        inline const char * intf() const { return m_interface_id.in(); }

        inline RequestInfo * next() { return m_next; }
        inline void next(RequestInfo * next) { m_next = next; }

    private:
        RequestInfo * m_next;
        CORBA::ULong m_req_id;
        CORBA::String_var m_operation;
        CORBA::String_var m_interface_id;
};


//
// TrackRequests allows multiple requests to be tracked
//

class TrackRequests
{
    public:
        TrackRequests(const char * id) : m_id(id), m_list(0) { }
        ~TrackRequests();

        RequestInfo * StartRequest(
          const RequestLevelInterceptor::RequestContext& request_context);

        RequestInfo * CompleteRequest(
          const RequestLevelInterceptor::ReplyContext& reply_context);

    private:
        CORBA::String_var m_id;
        RequestInfo * m_list;
};

class ClientInterceptorData : public virtual RequestLevelInterceptor::ClientRequestInterceptor
{
    public:
        ClientInterceptorData(CORBA::ORB_ptr TheOrb,
                              TrackRequests *tracker) :
                                        m_orb(TheOrb),
                                        m_tracker(tracker) {}
        ~ClientInterceptorData() {if (m_tracker) delete m_tracker;} 

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

        // output stream for data collection
        ofstream m_outfile;

    private:
        ClientInterceptorData() {}
        CORBA::ORB_ptr  m_orb;
	TrackRequests   *m_tracker;
};

class TargetInterceptorData : public virtual RequestLevelInterceptor::TargetRequestInterceptor
{
    public:
        TargetInterceptorData(CORBA::ORB_ptr TheOrb,
                              TrackRequests *tracker) :
                                       m_orb(TheOrb), m_tracker(tracker) {}
        ~TargetInterceptorData() { if (m_tracker) delete m_tracker;}

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

        // output stream for data collection
        ofstream m_outfile;

    private:
        TargetInterceptorData() {}
        CORBA::ORB_ptr  m_orb;
	TrackRequests   *m_tracker;
};

