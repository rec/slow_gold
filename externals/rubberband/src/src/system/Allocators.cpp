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

#include "Allocators.h"

#ifdef HAVE_IPP
#include <ipps.h>
#endif

#include <iostream>
using std::cerr;
using std::endl;

namespace RubberBand {

#ifdef HAVE_IPP

template <>
float *allocate(size_t count)
{
    float *ptr = ippsMalloc_32f(count);
    if (!ptr) throw (std::bad_alloc());
    return ptr;
}

template <>
double *allocate(size_t count)
{
    double *ptr = ippsMalloc_64f(count);
    if (!ptr) throw (std::bad_alloc());
    return ptr;
}

template <>
void deallocate(float *ptr)
{
    if (ptr) ippsFree((void *)ptr);
}

template <>
void deallocate(double *ptr)
{
    if (ptr) ippsFree((void *)ptr);
}

#endif

}

