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

#include "sysutils.h"

#ifdef _WIN32
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#else /* !_WIN32 */
#include <signal.h>
#include <unistd.h>
#ifdef __APPLE__
#include <sys/sysctl.h>
#else /* !__APPLE__, !_WIN32 */
#include <stdio.h>
#include <string.h>
#endif /* !__APPLE__, !_WIN32 */
#endif /* !_WIN32 */

#ifdef __sun
#include <sys/processor.h>
#endif

#include <cstdlib>
#include <iostream>

#ifdef HAVE_IPP
#include <ipp.h> // for static init
#endif

#ifdef HAVE_VDSP
#include <vecLib/vDSP.h>
#include <fenv.h>
#endif

#ifdef _WIN32
#include <fstream>
#endif


namespace RubberBand {

const char *
system_get_platform_tag()
{
#ifdef _WIN32
    return "win32";
#else /* !_WIN32 */
#ifdef __APPLE__
    return "osx";
#else /* !__APPLE__ */
#ifdef __LINUX__
    if (sizeof(long) == 8) {
        return "linux64";
    } else {
        return "linux";
    }
#else /* !__LINUX__ */
    return "posix";
#endif /* !__LINUX__ */
#endif /* !__APPLE__ */
#endif /* !_WIN32 */
}

bool
system_is_multiprocessor()
{
    static bool tested = false, mp = false;

    if (tested) return mp;
    int count = 0;

#ifdef _WIN32

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    count = sysinfo.dwNumberOfProcessors;

#else /* !_WIN32 */
#ifdef __APPLE__
    
    size_t sz = sizeof(count);
    if (sysctlbyname("hw.ncpu", &count, &sz, NULL, 0)) {
        count = 0;
        mp = false;
    } else {
        mp = (count > 1);
    }

#else /* !__APPLE__, !_WIN32 */
#ifdef __sun

    processorid_t i, n;
    n = sysconf(_SC_CPUID_MAX);
    for (i = 0; i <= n; ++i) {
        int status = p_online(i, P_STATUS);
        if (status == P_ONLINE) {
            ++count;
        }
        if (count > 1) break;
    }

#else /* !__sun, !__APPLE__, !_WIN32 */

    //...

    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (!cpuinfo) return false;

    char buf[256];
    while (!feof(cpuinfo)) {
        if (!fgets(buf, 256, cpuinfo)) break;
        if (!strncmp(buf, "processor", 9)) {
            ++count;
        }
        if (count > 1) break;
    }

    fclose(cpuinfo);

#endif /* !__sun, !__APPLE__, !_WIN32 */
#endif /* !__APPLE__, !_WIN32 */
#endif /* !_WIN32 */

    mp = (count > 1);
    tested = true;
    return mp;
}

#ifdef _WIN32

void gettimeofday(struct timeval *tv, void *tz)
{
    union { 
	long long ns100;  
	FILETIME ft; 
    } now; 
    
    ::GetSystemTimeAsFileTime(&now.ft); 
    tv->tv_usec = (long)((now.ns100 / 10LL) % 1000000LL); 
    tv->tv_sec = (long)((now.ns100 - 116444736000000000LL) / 10000000LL); 
}

void usleep(unsigned long usec)
{
    ::Sleep(usec == 0 ? 0 : usec < 1000 ? 1 : usec / 1000);
}

#endif

void system_specific_initialise()
{
#if defined HAVE_IPP
#ifndef USE_IPP_DYNAMIC_LIBS
//    std::cerr << "Calling ippStaticInit" << std::endl;
    ippStaticInit();
#endif
    ippSetDenormAreZeros(1);
#elif defined HAVE_VDSP
#if defined __i386__ || defined __x86_64__ 
    fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
#endif
#endif
}

void system_specific_application_initialise()
{
}


ProcessStatus
GetProcessStatus(int pid)
{
#ifdef _WIN32
    HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!handle) {
        return ProcessNotRunning;
    } else {
        CloseHandle(handle);
        return ProcessRunning;
    }
#else
    if (kill(getpid(), 0) == 0) {
        if (kill(pid, 0) == 0) {
            return ProcessRunning;
        } else {
            return ProcessNotRunning;
        }
    } else {
        return UnknownProcessStatus;
    }
#endif
}


}



