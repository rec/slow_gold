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

#ifndef _RUBBERBAND_SYSUTILS_H_
#define _RUBBERBAND_SYSUTILS_H_

#ifdef __MSVC__
#include "float_cast/float_cast.h"
#define R__ __restrict
#endif

#ifdef __GNUC__
#define R__ __restrict__
#endif

#ifndef R__
#define R__
#endif

#ifdef __MINGW32__
#include <malloc.h>
#else
#ifndef __MSVC__
#include <alloca.h>
#endif
#endif

#ifdef __MSVC__
#include <malloc.h>
#include <process.h>
#define alloca _alloca
#define getpid _getpid
#endif

#ifdef __MSVC__
#define uint8_t unsigned __int8
#define uint16_t unsigned __int16
#define uint32_t unsigned __int32
#define ssize_t long
#else
#include <stdint.h>
#endif

#include <math.h>

namespace RubberBand {

extern const char *system_get_platform_tag();
extern bool system_is_multiprocessor();
extern void system_specific_initialise();
extern void system_specific_application_initialise();

enum ProcessStatus { ProcessRunning, ProcessNotRunning, UnknownProcessStatus };
extern ProcessStatus system_get_process_status(int pid);

#ifdef _WIN32

struct timeval { long tv_sec; long tv_usec; };
void gettimeofday(struct timeval *p, void *tz);

struct timespec { long tv_sec; long tv_nsec; };
// always uses GetPerformanceCounter, does not check whether it's valid or not:
void clock_gettime(int clk_id, struct timespec *p);
#define CLOCK_MONOTONIC 1

#endif

#ifdef __MSVC__

void usleep(unsigned long);

#endif

inline double mod(double x, double y) { return x - (y * floor(x / y)); }
inline float modf(float x, float y) { return x - (y * float(floor(x / y))); }

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline double princarg(double a) { return mod(a + M_PI, -2.0 * M_PI) + M_PI; }
inline float princargf(float a) { return modf(a + (float)M_PI, -2.f * (float)M_PI) + (float)M_PI; }

} // end namespace

// The following should be functions in the RubberBand namespace, really

#ifdef _WIN32

#define MLOCK(a,b)   1
#define MUNLOCK(a,b) 1
#define MUNLOCK_SAMPLEBLOCK(a) 1

#define MBARRIER()   MemoryBarrier() 

#define DLOPEN(a,b)  LoadLibrary((a).toStdWString().c_str())
#define DLSYM(a,b)   GetProcAddress((HINSTANCE)(a),(b))
#define DLCLOSE(a)   FreeLibrary((HINSTANCE)(a))
#define DLERROR()    ""

#else

#include <sys/mman.h>
#include <dlfcn.h>
#include <stdio.h>

#define MLOCK(a,b)   ::mlock((char *)(a),(b))
#define MUNLOCK(a,b) (::munlock((char *)(a),(b)) ? (::perror("munlock failed"), 0) : 0)
#define MUNLOCK_SAMPLEBLOCK(a) do { if (!(a).empty()) { const float &b = *(a).begin(); MUNLOCK(&b, (a).capacity() * sizeof(float)); } } while(0);

#ifdef __APPLE__
#include <libkern/OSAtomic.h>
#define MBARRIER() OSMemoryBarrier()
#else
#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
#define MBARRIER() __sync_synchronize()
#else
extern void system_memorybarrier();
#define MBARRIER() system_memorybarrier()
#endif
#endif

#define DLOPEN(a,b)  dlopen((a).toStdString().c_str(),(b))
#define DLSYM(a,b)   dlsym((a),(b))
#define DLCLOSE(a)   dlclose((a))
#define DLERROR()    dlerror()

#endif

#endif
