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

#ifndef _HIGHFREQUENCY_AUDIO_CURVE_H_
#define _HIGHFREQUENCY_AUDIO_CURVE_H_

#include "AudioCurveCalculator.h"

namespace RubberBand
{

class HighFrequencyAudioCurve : public AudioCurveCalculator
{
public:
    HighFrequencyAudioCurve(Parameters parameters);

    virtual ~HighFrequencyAudioCurve();

    virtual float processFloat(const float *R__ mag, int increment);
    virtual double processDouble(const double *R__ mag, int increment);
    virtual void reset();
    virtual const char *getUnit() const { return "Vbin"; }
};

}

#endif
