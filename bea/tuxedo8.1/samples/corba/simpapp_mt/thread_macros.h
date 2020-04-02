//	(c) 2003 BEA Systems, Inc. All Rights Reserved. 
//
//  Copyright (c) 2000 BEA Systems, Inc.
//  All Rights Reserved
//
//  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF BEA Systems, Inc.
//  The copyright notice above does not evidence any actual or intended
//  publication of such source code.
//
//  WARNING: The source code in this module is provided by BEA as 
//  unsupported example code only. BEA does not guarantee the 
//  correctness or suitability of this code. Use at your own risk. 
//
//  thread_macros.h
//
//  Example macros for thread portability.
//
//  These macros are designed to provide portability between 
//  environments that support multi-threading for the Tuxedo
//      sample applications.
//

#ifdef _AIX
#ifndef __unix
#define __unix
#endif
#endif

#ifdef __linux__
#ifndef __USE_UNIX98
#define __USE_UNIX98
#endif
#endif

#ifdef WIN32
#include <windows.h>
#include <process.h>    // For thread api
#else /* UNIX */
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#endif

#ifdef WIN32
typedef unsigned long SIMPTHR_ID;
typedef HANDLE SIMPTHR_HANDLE;
#define SIMPTHR_HANDLE_NULL ((HANDLE)NULL)
#define SIMPTHR_GETCURRENTTHREADID GetCurrentThreadId()
#define SIMPTHR_TRY_ENTER_CRITICAL_SECTION(_A_) TryEnterCriticalSection(&_A_)
#define SIMPTHR_ENTER_CRITICAL_SECTION(_A_) EnterCriticalSection(&_A_)
#define SIMPTHR_LEAVE_CRITICAL_SECTION(_A_) LeaveCriticalSection(&_A_)
#define SIMPTHR_INITIALIZE_CRITICAL_SECTION(_A_) InitializeCriticalSection(&_A_)
#define SIMPTHR_DELETE_CRITICAL_SECTION(_A_) DeleteCriticalSection(&_A_)
#define SIMPTHR_DECLARE_STATIC_CRITICAL_SECTION(_A_) static CRITICAL_SECTION _A_
#define SIMPTHR_DECLARE_CRITICAL_SECTION(_A_) CRITICAL_SECTION _A_
#define SIMPTHR_DECLARE_EXTERN_CRITICAL_SECTION(_A_) extern CRITICAL_SECTION _A_
#define SIMPTHR_THIS_ENTER_CRITICAL_SECTION EnterCriticalSection(&m_critical_section)
#define SIMPTHR_THIS_LEAVE_CRITICAL_SECTION LeaveCriticalSection(&m_critical_section)
#define SIMPTHR_THIS_INITIALIZE_CRITICAL_SECTION InitializeCriticalSection(&m_critical_section)
#define SIMPTHR_THIS_DELETE_CRITICAL_SECTION DeleteCriticalSection(&m_critical_section)
#define SIMPTHR_CLASSREF_ENTER_CRITICAL_SECTION(_A_) EnterCriticalSection(&_A_.m_critical_section)
#define SIMPTHR_CLASSREF_LEAVE_CRITICAL_SECTION(_A_) LeaveCriticalSection(&_A_.m_critical_section)
#define SIMPTHR_CLASSPTR_TRY_ENTER_CRITICAL_SECTION(_A_) TryEnterCriticalSection(&_A_->m_critical_section)
#define SIMPTHR_CLASSPTR_ENTER_CRITICAL_SECTION(_A_) EnterCriticalSection(&_A_->m_critical_section)
#define SIMPTHR_CLASSPTR_LEAVE_CRITICAL_SECTION(_A_) LeaveCriticalSection(&_A_->m_critical_section)
#define SIMPTHR_DECLARE_CLASS_CRITICAL_SECTION CRITICAL_SECTION m_critical_section
#define SIMPTHR_CREATE_THREAD(_HND_,_RTN_,_ARG_)\
    _HND_ = (HANDLE)_beginthread( _RTN_ , 0, (void *) _ARG_ )
#define SIMPTHR_THREAD_YIELD Sleep(0)
// No actions are needed because SIMPTHR_CREATE_THREAD creates detached threads
#define SIMPTHR_THREAD_DETACH 
#define SIMPTHR_THREAD_JOIN(_HND_) 
#endif /* WIN32 */

#ifdef _AIX
typedef void * SIMPTHR_ID;
typedef pthread_t SIMPTHR_HANDLE;
#define SIMPTHR_HANDLE_NULL ((pthread_t)0)
#define SIMPTHRTIMESPEC timespec
#define SIMPTHR_SIGSETMASK( _A_, _B_, _C_ ) sigthreadmask( _A_ , _B_ , _C_ )
#define SIMPTHR_GETCURRENTTHREADID (void *)pthread_self()
#define SIMPTHR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ )
#define SIMPTHR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ )
#define SIMPTHR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ )
#define SIMPTHR_INITIALIZE_CRITICAL_SECTION( _A_ ) {\
    pthread_mutexattr_init(& _A_##attr);\
    pthread_mutex_init(& _A_ , & _A_##attr);}
#define SIMPTHR_THIS_INITIALIZE_CRITICAL_SECTION {\
    pthread_mutexattr_init(&m_critical_sectionattr);\
    pthread_mutex_init(&m_critical_section, &m_critical_sectionattr);}
#define SIMPTHR_DELETE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_destroy(& _A_ );\
    pthread_mutexattr_destroy(& _A_##attr)
#define SIMPTHR_DECLARE_STATIC_CRITICAL_SECTION( _A_ )\
    static pthread_mutex_t _A_ ;\
    static pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_t _A_ ;\
    pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_EXTERN_CRITICAL_SECTION( _A_ )\
    extern pthread_mutex_t _A_ ;\
    extern pthread_mutexattr_t _A_##attr
#define SIMPTHR_THIS_ENTER_CRITICAL_SECTION pthread_mutex_lock(&m_critical_section)
#define SIMPTHR_THIS_LEAVE_CRITICAL_SECTION pthread_mutex_unlock(&m_critical_section)
#define SIMPTHR_THIS_DELETE_CRITICAL_SECTION {\
    pthread_mutex_destroy(&m_critical_section);\
    pthread_mutexattr_destroy(&m_critical_sectionattr);}
#define SIMPTHR_CLASSREF_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSREF_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSPTR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ ->m_critical_section)
#define SIMPTHR_DECLARE_CLASS_CRITICAL_SECTION\
    pthread_mutex_t m_critical_section;\
    pthread_mutexattr_t m_critical_sectionattr
#define SIMPTHR_CREATE_THREAD(_HND_,_RTN_,_ARG_)\
    (void) pthread_create( & _HND_ , NULL,  _RTN_ , (void *) _ARG_ )
// The yield function is not listed MT safe and also requires libc.a to link
#define SIMPTHR_THREAD_YIELD sleep(0)
#define SIMPTHR_THREAD_DETACH (void) pthread_detach(pthread_self())
#define SIMPTHR_THREAD_JOIN(_HND_) { void * __SIMPTHR_THREAD_STATUS__; \
                        (void) pthread_join(_HND_,&__SIMPTHR_THREAD_STATUS__); }
#endif /* aix */

#if (defined(__alpha) && defined(__osf__))
typedef void * SIMPTHR_ID;
typedef pthread_t SIMPTHR_HANDLE;
#define SIMPTHR_HANDLE_NULL ((pthread_t)0)
#define SIMPTHRTIMESPEC timespec_t
#define SIMPTHR_SIGSETMASK( _A_, _B_, _C_ ) pthread_sigmask( _A_ , _B_ , _C_ )
#define SIMPTHR_GETCURRENTTHREADID (void *)pthread_self()
#define SIMPTHR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ )
#define SIMPTHR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ )
#define SIMPTHR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ )
#define SIMPTHR_INITIALIZE_CRITICAL_SECTION( _A_ ) {\
    pthread_mutexattr_init(& _A_##attr);\
    pthread_mutexattr_settype(& _A_##attr, PTHREAD_MUTEX_NORMAL);\
    pthread_mutex_init(& _A_ , & _A_##attr);}
#define SIMPTHR_THIS_INITIALIZE_CRITICAL_SECTION {\
    pthread_mutexattr_init(&m_critical_sectionattr);\
    pthread_mutexattr_settype(&m_critical_sectionattr, PTHREAD_MUTEX_NORMAL);\
    pthread_mutex_init(&m_critical_section, &m_critical_sectionattr);}
#define SIMPTHR_DELETE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_destroy(& _A_ );\
    pthread_mutexattr_destroy(& _A_##attr)
#define SIMPTHR_DECLARE_STATIC_CRITICAL_SECTION( _A_ )\
    static pthread_mutex_t _A_ ;\
    static pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_t _A_ ;\
    pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_EXTERN_CRITICAL_SECTION( _A_ )\
    extern pthread_mutex_t _A_ ;\
    extern pthread_mutexattr_t _A_##attr
#define SIMPTHR_THIS_ENTER_CRITICAL_SECTION pthread_mutex_lock(&m_critical_section)
#define SIMPTHR_THIS_LEAVE_CRITICAL_SECTION pthread_mutex_unlock(&m_critical_section)
#define SIMPTHR_THIS_DELETE_CRITICAL_SECTION {\
    pthread_mutex_destroy(&m_critical_section);\
    pthread_mutexattr_destroy(&m_critical_sectionattr);}
#define SIMPTHR_CLASSREF_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSREF_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSPTR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ ->m_critical_section)
#define SIMPTHR_DECLARE_CLASS_CRITICAL_SECTION\
    pthread_mutex_t m_critical_section;\
    pthread_mutexattr_t m_critical_sectionattr
#define SIMPTHR_CREATE_THREAD(_HND_,_RTN_,_ARG_)\
    (void) pthread_create( & _HND_ , NULL,  _RTN_ , (void *) _ARG_ )
#define SIMPTHR_THREAD_YIELD sched_yield()
#define SIMPTHR_THREAD_DETACH (void) pthread_detach(pthread_self())
#define SIMPTHR_THREAD_JOIN(_HND_) { void * __SIMPTHR_THREAD_STATUS__; \
                 (void) pthread_join(_HND_,&__SIMPTHR_THREAD_STATUS__); }
#endif /* alpha_osf */

#ifdef __linux__
typedef unsigned long SIMPTHR_ID;
typedef pthread_t SIMPTHR_HANDLE;
#define SIMPTHR_HANDLE_NULL ((pthread_t)0)
#define SIMPTHRTIMESPEC timespec
#define SIMPTHR_SIGSETMASK( _A_, _B_, _C_ ) pthread_sigmask( _A_ , _B_ , _C_ )
#define SIMPTHR_GETCURRENTTHREADID pthread_self()
#define SIMPTHR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ )
#define SIMPTHR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ )
#define SIMPTHR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ )
#define SIMPTHR_INITIALIZE_CRITICAL_SECTION( _A_ ) {\
    pthread_mutexattr_init(& _A_##attr);\
    pthread_mutex_init(& _A_ , & _A_##attr);}
#define SIMPTHR_THIS_INITIALIZE_CRITICAL_SECTION {\
    pthread_mutexattr_init(&m_critical_sectionattr);\
    pthread_mutex_init(&m_critical_section, &m_critical_sectionattr);}
#define SIMPTHR_DELETE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_destroy(& _A_ );\
    pthread_mutexattr_destroy(& _A_##attr)
#define SIMPTHR_DECLARE_STATIC_CRITICAL_SECTION( _A_ )\
    static pthread_mutex_t _A_ ;\
    static pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_t _A_ ;\
    pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_EXTERN_CRITICAL_SECTION( _A_ )\
    extern pthread_mutex_t _A_ ;\
    extern pthread_mutexattr_t _A_##attr
#define SIMPTHR_THIS_ENTER_CRITICAL_SECTION pthread_mutex_lock(&m_critical_section)
#define SIMPTHR_THIS_LEAVE_CRITICAL_SECTION pthread_mutex_unlock(&m_critical_section)
#define SIMPTHR_THIS_DELETE_CRITICAL_SECTION {\
    pthread_mutex_destroy(&m_critical_section);\
    pthread_mutexattr_destroy(&m_critical_sectionattr);}
#define SIMPTHR_CLASSREF_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSREF_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSPTR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ ->m_critical_section)
#define SIMPTHR_DECLARE_CLASS_CRITICAL_SECTION\
    pthread_mutex_t m_critical_section;\
    pthread_mutexattr_t m_critical_sectionattr
#define SIMPTHR_CREATE_THREAD(_HND_,_RTN_,_ARG_)\
    (void) pthread_create( & _HND_ , NULL,  _RTN_ , (void *) _ARG_ )
// The yield function is not listed MT safe and also requires libc.a to link
#define SIMPTHR_THREAD_YIELD sleep(0)
#define SIMPTHR_THREAD_DETACH (void) pthread_detach(pthread_self())
#define SIMPTHR_THREAD_JOIN(_HND_) { void * __SIMPTHR_THREAD_STATUS__; \
                                 (void) pthread_join(_HND_,&__SIMPTHR_THREAD_STATUS__); }
#endif /* __linux__ */

#ifdef __sun
typedef unsigned long SIMPTHR_ID;
typedef pthread_t SIMPTHR_HANDLE;
#define SIMPTHR_HANDLE_NULL ((pthread_t)0)
#define SIMPTHRTIMESPEC timespec_t
#define SIMPTHR_SIGSETMASK( _A_, _B_, _C_ )    pthread_sigmask( _A_ , _B_ , _C_ )
#define SIMPTHR_GETCURRENTTHREADID pthread_self()
#define SIMPTHR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ )
#define SIMPTHR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ )
#define SIMPTHR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ )
#define SIMPTHR_INITIALIZE_CRITICAL_SECTION( _A_ ) {\
    pthread_mutexattr_init(& _A_##attr);\
    pthread_mutexattr_setpshared(& _A_##attr, PTHREAD_PROCESS_PRIVATE);\
    pthread_mutex_init(& _A_ , & _A_##attr);}
#define SIMPTHR_DELETE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_destroy(& _A_ );\
    pthread_mutexattr_destroy(& _A_##attr)
#define SIMPTHR_DECLARE_STATIC_CRITICAL_SECTION( _A_ )\
    static pthread_mutex_t _A_ ;\
    static pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_t _A_ ;\
    pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_EXTERN_CRITICAL_SECTION( _A_ )\
    extern pthread_mutex_t _A_ ;\
    extern pthread_mutexattr_t _A_##attr
#define SIMPTHR_THIS_ENTER_CRITICAL_SECTION pthread_mutex_lock(&m_critical_section)
#define SIMPTHR_THIS_LEAVE_CRITICAL_SECTION pthread_mutex_unlock(&m_critical_section)
#define SIMPTHR_THIS_INITIALIZE_CRITICAL_SECTION {\
    pthread_mutexattr_init(&m_critical_sectionattr);\
    pthread_mutexattr_setpshared(&m_critical_sectionattr, PTHREAD_PROCESS_PRIVATE);\
    pthread_mutex_init(&m_critical_section, &m_critical_sectionattr);}
#define SIMPTHR_THIS_DELETE_CRITICAL_SECTION {\
    pthread_mutex_destroy(&m_critical_section);\
    pthread_mutexattr_destroy(&m_critical_sectionattr);}
#define SIMPTHR_CLASSREF_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSREF_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSPTR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ ->m_critical_section)
#define SIMPTHR_DECLARE_CLASS_CRITICAL_SECTION\
    pthread_mutex_t m_critical_section;\
    pthread_mutexattr_t m_critical_sectionattr
#define SIMPTHR_CREATE_THREAD(_HND_,_RTN_,_ARG_)\
    (void) pthread_create( & _HND_ , NULL,  _RTN_ , (void *) _ARG_ )
// The yield function is not supported and also requires libposix4 to link
#define SIMPTHR_THREAD_YIELD sleep(0)
#define SIMPTHR_THREAD_DETACH (void) pthread_detach(pthread_self())
#define SIMPTHR_THREAD_JOIN(_HND_) { void * __SIMPTHR_THREAD_STATUS__; \
                 (void) pthread_join(_HND_,&__SIMPTHR_THREAD_STATUS__); }
#endif /* solaris */

#ifdef __hpux
typedef unsigned long SIMPTHR_ID;
typedef pthread_t SIMPTHR_HANDLE;
#define SIMPTHR_HANDLE_NULL ((pthread_t)0)
#define SIMPTHRTIMESPEC timespec
#define SIMPTHR_SIGSETMASK( _A_, _B_, _C_ )    pthread_sigmask( _A_ , _B_ , _C_ )
#define SIMPTHR_GETCURRENTTHREADID pthread_self()
#define SIMPTHR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ )
#define SIMPTHR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ )
#define SIMPTHR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ )
#define SIMPTHR_INITIALIZE_CRITICAL_SECTION( _A_ ) {\
    pthread_mutexattr_init(& _A_##attr);\
    pthread_mutexattr_setpshared(& _A_##attr, PTHREAD_PROCESS_PRIVATE);\
    pthread_mutex_init(& _A_ , & _A_##attr);}
#define SIMPTHR_DELETE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_destroy(& _A_ );\
    pthread_mutexattr_destroy(& _A_##attr)
#define SIMPTHR_DECLARE_STATIC_CRITICAL_SECTION( _A_ )\
    static pthread_mutex_t _A_ ;\
    static pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_CRITICAL_SECTION( _A_ )\
    pthread_mutex_t _A_ ;\
    pthread_mutexattr_t _A_##attr
#define SIMPTHR_DECLARE_EXTERN_CRITICAL_SECTION( _A_ )\
    extern pthread_mutex_t _A_ ;\
    extern pthread_mutexattr_t _A_##attr
#define SIMPTHR_THIS_ENTER_CRITICAL_SECTION pthread_mutex_lock(&m_critical_section)
#define SIMPTHR_THIS_LEAVE_CRITICAL_SECTION pthread_mutex_unlock(&m_critical_section)
#define SIMPTHR_THIS_INITIALIZE_CRITICAL_SECTION {\
    pthread_mutexattr_init(&m_critical_sectionattr);\
    pthread_mutexattr_setpshared(&m_critical_sectionattr, PTHREAD_PROCESS_PRIVATE);\
    pthread_mutex_init(&m_critical_section, &m_critical_sectionattr);}
#define SIMPTHR_THIS_DELETE_CRITICAL_SECTION {\
    pthread_mutex_destroy(&m_critical_section);\
    pthread_mutexattr_destroy(&m_critical_sectionattr);}
#define SIMPTHR_CLASSREF_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSREF_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ .m_critical_section)
#define SIMPTHR_CLASSPTR_TRY_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_trylock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_ENTER_CRITICAL_SECTION( _A_ ) pthread_mutex_lock(& _A_ ->m_critical_section)
#define SIMPTHR_CLASSPTR_LEAVE_CRITICAL_SECTION( _A_ ) pthread_mutex_unlock(& _A_ ->m_critical_section)
#define SIMPTHR_DECLARE_CLASS_CRITICAL_SECTION\
    pthread_mutex_t m_critical_section;\
    pthread_mutexattr_t m_critical_sectionattr
#define SIMPTHR_CREATE_THREAD(_HND_,_RTN_,_ARG_)\
    (void) pthread_create( & _HND_ , NULL,  _RTN_ , (void *) _ARG_ )
#define SIMPTHR_THREAD_YIELD sched_yield()
#define SIMPTHR_THREAD_DETACH (void) pthread_detach(pthread_self())
#define SIMPTHR_THREAD_JOIN(_HND_) { void * __SIMPTHR_THREAD_STATUS__; \
                 (void) pthread_join(_HND_,&__SIMPTHR_THREAD_STATUS__); }
#endif /* hpux */

//
// A sleep with zero seconds on Windows is used to volintarily give
// up control to another thread. The sleep macro simulates this when
// using the pthreads API.
//
#ifdef WIN32
#define SIMPTHR_SLEEP(n) Sleep(n*1000)
#else /* UNIX */
#define SIMPTHR_SLEEP(n) (n == 0) ? SIMPTHR_THREAD_YIELD : sleep(n)
#endif

#ifdef WIN32
extern "C" { typedef void (*SIMPTHR_THREAD_ROUTINE)(void *); }
#define SIMPTHR_THREAD_ROUTINE_RETURN void _cdecl
#define SIMPTHR_RETURN_FROM_THREAD_ROUTINE(_A_) return;
#else /* UNIX */
extern "C" { typedef void *(*SIMPTHR_THREAD_ROUTINE)(void *); }
#define SIMPTHR_THREAD_ROUTINE_RETURN void *
#define SIMPTHR_RETURN_FROM_THREAD_ROUTINE(_A_) return _A_ ;
#endif

class SIMPTHREvent
{
    public:
    SIMPTHREvent(int reset = 0);
    ~SIMPTHREvent();
    enum EventStatus {TIMEDOUT, FAILED, SIGNALED, INTERRUPTED};
    inline int Initialized() { return m_init_done; }
    protected:
    EventStatus WaitForSignal(int ReturnForAll, int Timeout = 0);
    int m_init_done;
    int m_manual_reset;

#ifdef WIN32
    protected:
    inline void SignalEvent(int = 1) { SetEvent(m_event); }
    inline void Reset() { ResetEvent(m_event); }
    void * m_event;
#endif /* WIN32 */

#ifdef __unix
    protected:
    void SignalEvent(int Broadcast = 1);
    void Reset();
    pthread_mutexattr_t    m_event_mutexattr;
    pthread_mutex_t        m_event_mutex;
    pthread_condattr_t    m_eventattr;
    pthread_cond_t        m_event;
    int            m_event_really_signaled;
#endif /* unix */
};

class SIMPTHRSignalWait : public SIMPTHREvent
{
    public:
    inline void Signal() { SignalEvent(0); }
    inline EventStatus Wait(int timeout = 0) { return WaitForSignal(0,timeout); }
};

class SIMPTHRReadyGo : public SIMPTHREvent
{
    public:
    SIMPTHRReadyGo();
    inline void Go() { SignalEvent(1); }
    inline void Ready() { WaitForSignal(0,0); }
    inline void Stop() { Reset(); }
};
