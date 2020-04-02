//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//
//  Copyright (c) 2000 BEA Systems, Inc.
//  All Rights Reserved
//
//    THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
//  The copyright notice above does not evidence any actual or intended
//  publication of such source code.
//
//  WARNING: The source code in this module is provided by BEA as 
//  unsupported example code only. BEA does not guarantee the 
//  correctness or suitability of this code. Use at your own risk. 
//
//  thread_macros.cpp
//
//  Thread portability wrapper implementations.
//
//  These wrappers are designed to provide portability between 
//  environments that support multi-threading for the Tuxedo
//  sample applications.
//

#include "thread_macros.h"

#ifdef WIN32
SIMPTHREvent::SIMPTHREvent(int reset) :
    m_init_done(0), m_manual_reset(reset)
{
    m_event = CreateEvent(NULL,         // no security attributes
                          (BOOL)reset,  // use specified reset value
                          FALSE,        // initial state is not signalled
                          NULL);        // no name
    if (m_event == (HANDLE)NULL)
      return;

    m_init_done = 1;
}

SIMPTHREvent::~SIMPTHREvent()
{
    if (m_init_done == 1)
      CloseHandle(m_event);
}

SIMPTHREvent::EventStatus SIMPTHREvent::WaitForSignal(int, int Timeout)
{
    EventStatus ret_value = SIGNALED;
    DWORD wait_result;
    if  (Timeout)
        wait_result = WaitForSingleObject(m_event, Timeout*1000);
    else
        wait_result = WaitForSingleObject(m_event, INFINITE);
    switch (wait_result)
    {
    case WAIT_ABANDONED:
        break;
    case WAIT_OBJECT_0:
        break;
    case WAIT_TIMEOUT:
        ret_value = TIMEDOUT;
        break;
    default:
        ret_value = FAILED;
        break;
    }
    return ret_value;
}
#endif /* WIN32 */

#ifdef __unix
SIMPTHREvent::SIMPTHREvent(int reset) :
    m_event_really_signaled(0),
    m_init_done(0),
    m_manual_reset(reset)
{
    if  (pthread_mutexattr_init(&m_event_mutexattr))
        return;
#ifndef    _AIX
#if    (defined(__alpha) && defined(__osf__))
    if  (pthread_mutexattr_settype(&m_event_mutexattr, PTHREAD_MUTEX_NORMAL))
#elif    defined(__linux__)
    if  (pthread_mutexattr_settype(&m_event_mutexattr, PTHREAD_MUTEX_FAST_NP))
#else    /* alpha_osf || __linux__ */
    if  (pthread_mutexattr_setpshared(&m_event_mutexattr, PTHREAD_PROCESS_PRIVATE))
#endif    /* alpha_osf || __linux__ */
        return;
#endif    /* aix */
    if  (pthread_mutex_init(&m_event_mutex, &m_event_mutexattr))
    {
        pthread_mutexattr_destroy(&m_event_mutexattr);
            return;
    }
    if  (pthread_condattr_init(&m_eventattr))
    {
        pthread_mutex_destroy(&m_event_mutex);
        pthread_mutexattr_destroy(&m_event_mutexattr);
            return;
    }
#ifndef    _AIX
#if    (!(defined(__alpha) && defined(__osf__)) && !defined(__linux__))
    if  (pthread_condattr_setpshared(&m_eventattr, PTHREAD_PROCESS_PRIVATE))
    {
        pthread_mutex_destroy(&m_event_mutex);
        pthread_mutexattr_destroy(&m_event_mutexattr);
            return;
    }
#endif    /* !alpha_osf */
#endif    /* !aix */
    if  (pthread_cond_init(&m_event, &m_eventattr))
    {
        pthread_condattr_destroy(&m_eventattr);
        pthread_mutex_destroy(&m_event_mutex);
        pthread_mutexattr_destroy(&m_event_mutexattr);
        return;
    }
    m_init_done = 1;
}

SIMPTHREvent::~SIMPTHREvent()
{
    if  (m_init_done == 1)
    {
        pthread_cond_destroy(&m_event);
        pthread_condattr_destroy(&m_eventattr);
        pthread_mutex_destroy(&m_event_mutex);
        pthread_mutexattr_destroy(&m_event_mutexattr);
    }
}

void SIMPTHREvent::SignalEvent(int Broadcast)
{
    pthread_mutex_lock(&m_event_mutex);
    m_event_really_signaled = 1;
    if  (Broadcast)
        pthread_cond_broadcast(&m_event);
    else
        pthread_cond_signal(&m_event);
    pthread_mutex_unlock(&m_event_mutex);
}

void SIMPTHREvent::Reset()
{
    pthread_mutex_lock(&m_event_mutex);
    m_event_really_signaled = 0;
    pthread_mutex_unlock(&m_event_mutex);
}

SIMPTHREvent::EventStatus SIMPTHREvent::WaitForSignal(int ReturnForAll, int Timeout)
{
    EventStatus ret_value = SIGNALED;
    int error_num = 0;
    SIMPTHRTIMESPEC time_val;

    if (Timeout)
    {
        time_val.tv_sec = time(NULL) + Timeout;
        time_val.tv_nsec = 0;
    }

    pthread_mutex_lock( &m_event_mutex );

    // Wait for the event to be signaled
    while  (m_event_really_signaled == 0)
    {
        if (Timeout)
          error_num = pthread_cond_timedwait( &m_event, &m_event_mutex, &time_val );
        else
          error_num = pthread_cond_wait( &m_event, &m_event_mutex );

        // Exit when requested to return for all...
        if (ReturnForAll) break;

        // If we get interrupted ignore the interrupts.
        if ((error_num != 0) && (error_num != EINTR))
            break;
    }
    if  (error_num == 0)
    {
        // Reset the event to unsignaled when not manual...
        if (m_manual_reset == 0)
          m_event_really_signaled = 0;
        pthread_mutex_unlock( &m_event_mutex );
    }
    else if  (error_num == ETIMEDOUT)
    {
        pthread_mutex_unlock( &m_event_mutex );
        ret_value = TIMEDOUT;
    }
    else if  (error_num == EINTR)
    {
        pthread_mutex_unlock( &m_event_mutex );
        ret_value = INTERRUPTED;
    }
    //
    // If another error, we don't own the mutex
    //
    else
    {
        ret_value = FAILED;
    }

    return ret_value;
}
#endif /* unix */

//
// Tell the base class to use a manual reset
// via the member initializer list...
//
SIMPTHRReadyGo::SIMPTHRReadyGo() :
    SIMPTHREvent(1)
{
}
