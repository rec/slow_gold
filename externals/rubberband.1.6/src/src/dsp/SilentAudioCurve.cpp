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

#include "SilentAudioCurve.h"

#include <cmath>

namespace RubberBand
{


SilentAudioCurve::SilentAudioCurve(Parameters parameters) :
    AudioCurveCalculator(parameters)
{
}

SilentAudioCurve::~SilentAudioCurve()
{
}

void
SilentAudioCurve::reset()
{
}

float
SilentAudioCurve::processFloat(const float *R__ mag, int)
{
    const int hs = m_lastPerceivedBin;
    static float threshold = powf(10.f, -6);

    for (int i = 0; i <= hs; ++i) {
        if (mag[i] > threshold) return 0.f;
    }
        
    return 1.f;
}

double
SilentAudioCurve::processDouble(const double *R__ mag, int)
{
    const int hs = m_lastPerceivedBin;
    static double threshold = pow(10.0, -6);

    for (int i = 0; i <= hs; ++i) {
        if (mag[i] > threshold) return 0.f;
    }
        
    return 1.f;
}

}

