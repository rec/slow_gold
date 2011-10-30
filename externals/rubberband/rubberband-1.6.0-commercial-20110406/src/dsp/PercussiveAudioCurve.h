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

#ifndef _PERCUSSIVE_AUDIO_CURVE_H_
#define _PERCUSSIVE_AUDIO_CURVE_H_

#include "AudioCurveCalculator.h"

namespace RubberBand
{

class PercussiveAudioCurve : public AudioCurveCalculator
{
public:
    PercussiveAudioCurve(Parameters parameters);

    virtual ~PercussiveAudioCurve();

    virtual void setFftSize(int newSize);

    virtual float processFloat(const float *R__ mag, int increment);
    virtual double processDouble(const double *R__ mag, int increment);


    virtual void reset();
    virtual const char *getUnit() const { return "bin/total"; }

protected:
    double *R__ m_prevMag;
};

}

#endif
