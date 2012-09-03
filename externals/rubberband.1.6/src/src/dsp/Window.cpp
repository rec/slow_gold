/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Rubber Band
    An audio time-stretching and pitch-shifting library.
    Copyright 2007-2009 Chris Cannam.

    This is the commercial edition of Rubber Band.  This software may be
    used and distributed only in accordance with the terms under which it
    was licensed to you.  In particular, you may NOT
      - distribute any part of this source code to any third party
      - link this software against other code that is licensed under
        the GPL (e.g. libsamplerate or FFTW) unless you have obtained
        a proprietary license for that software as well
*/

#include "Window.h"

#ifdef HAVE_IPP

#include <ipps.h>

namespace RubberBand {

template <>
void
Window<float>::cut(float *R__ src) const
{
    ippsMul_32f_I(m_cache, src, m_size);
}

template <>
void
Window<double>::cut(double *R__ src) const
{
    ippsMul_64f_I(m_cache, src, m_size);
}

}

#endif

