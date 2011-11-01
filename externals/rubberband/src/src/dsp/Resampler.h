/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*- vi:set ts=8 sts=4 sw=4: */

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

#ifndef _RUBBERBAND_RESAMPLER_H_
#define _RUBBERBAND_RESAMPLER_H_

#include "system/sysutils.h"

namespace RubberBand {

class ResamplerImpl;

class Resampler
{
public:
    enum Quality { Best, FastestTolerable, Fastest };
    enum Exception { ImplementationError };

    /**
     * Construct a resampler with the given quality level and channel
     * count.  maxBufferSize gives a bound on the maximum incount size
     * that may be passed to the resample function before the
     * resampler needs to reallocate its internal buffers.
     */
    Resampler(Quality quality, int channels, int maxBufferSize = 0,
              int debugLevel = 0);
    ~Resampler();

    /**
     * Resample the given multi-channel buffers, where incount is the
     * number of frames in the input buffers.  Returns the number of
     * frames written to the output buffers.
     */
    int resample(const float *const R__ *const R__ in,
                 float *const R__ *const R__ out,
                 int incount,
                 float ratio,
                 bool final = false);

    /**
     * Resample the given interleaved buffer, where incount is the
     * number of frames in the input buffer (i.e. it has incount *
     * getChannelCount() samples).  Returns the number of frames
     * written to the output buffer.
     */
    int resampleInterleaved(const float *const R__ in,
                            float *const R__ out,
                            int incount,
                            float ratio,
                            bool final = false);

    int getChannelCount() const;

    void reset();

protected:
    ResamplerImpl *d;
    int m_method;
};

}

#endif
