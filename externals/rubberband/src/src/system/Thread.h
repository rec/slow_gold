/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Rubber Band
    An audio time-stretching and pitch-shifting library.
    Copyright 2007-2011 Chris Cannam.

    This is the commercial edition of Rubber Band.  This software may be
    used and distributed only in accordance with the terms under which it
    was licensed to you.  In particular, you may NOT
      - distribute any part of this source code to any third party
      - link this software against other code that is licensed under
        the GPL (e.g. libsamplerate or FFTW) unless you have obtained
        a proprietary license for that software as well
*/

#ifndef _RUBBERBAND_THREAD_H_
#define _RUBBERBAND_THREAD_H_

#ifdef _WIN32
#include <windows.h>
#else /* !_WIN32 */
#ifdef USE_PTHREADS
#include <pthread.h>
#else /* !USE_PTHREADS */
#error No thread implementation selected
#endif /* !USE_PTHREADS */
#endif /* !_WIN32 */

#include <string>

//#define DEBUG_THREAD 1
//#define DEBUG_MUTEX 1
//#define DEBUG_CONDITION 1

namespace RubberBand
{

class Thread
{
public:
#ifdef _WIN32
    typedef HANDLE Id;
#else
#ifdef USE_PTHREADS
    typedef pthread_t Id;
#endif
#endif

    Thread();
    virtual ~Thread();

    Id id();

    void start();
    void wait();

    static bool threadingAvailable();

protected:
    virtual void run() = 0;

private:
#ifdef _WIN32
    HANDLE m_id;
    bool m_extant;
    static DWORD WINAPI staticRun(LPVOID lpParam);
#else
#ifdef USE_PTHREADS
    pthread_t m_id;
    bool m_extant;
    static void *staticRun(void *);
#endif
#endif
};

class Mutex
{
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();
    bool trylock();

private:
#ifdef _WIN32
    HANDLE m_mutex;
#ifndef NO_THREAD_CHECKS
    DWORD m_lockedBy;
#endif
#else
#ifdef USE_PTHREADS
    pthread_mutex_t m_mutex;
#ifndef NO_THREAD_CHECKS
    pthread_t m_lockedBy;
    bool m_locked;
#endif
#endif
#endif
};

class MutexLocker
{
public:
    MutexLocker(Mutex *);
    ~MutexLocker();

private:
    Mutex *m_mutex;
};

/**
  The Condition class bundles a condition variable and mutex.

  To wait on a condition, call lock(), test the termination condition
  if desired, then wait().  The condition will be unlocked during the
  wait and re-locked when wait() returns (which will happen when the
  condition is signalled or the timer times out).

  To signal a condition, call signal().  If the condition is signalled
  between lock() and wait(), the signal may be missed by the waiting
  thread.  To avoid this, the signalling thread should also lock the
  condition before calling signal() and unlock it afterwards.
*/

class Condition
{
public:
    Condition(std::string name);
    ~Condition();
    
    void lock();
    void unlock();
    void wait(int us = 0);

    void signal();
    
private:

#ifdef _WIN32
    HANDLE m_mutex;
    HANDLE m_condition;
    bool m_locked;
#else
#ifdef USE_PTHREADS
    pthread_mutex_t m_mutex;
    pthread_cond_t m_condition;
    bool m_locked;
#endif
#endif
#ifdef DEBUG_CONDITION
    std::string m_name;
#endif
};

}

#endif
