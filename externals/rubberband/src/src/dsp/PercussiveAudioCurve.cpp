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

#include "PercussiveAudioCurve.h"

#include "system/Allocators.h"
#include "system/VectorOps.h"

#include <cmath>
#include <iostream>
namespace RubberBand
{


PercussiveAudioCurve::PercussiveAudioCurve(Parameters parameters) :
    AudioCurveCalculator(parameters)
{
    m_prevMag = allocate_and_zero<double>(m_fftSize/2 + 1);
}

PercussiveAudioCurve::~PercussiveAudioCurve()
{
    deallocate(m_prevMag);
}

void
PercussiveAudioCurve::reset()
{
    v_zero(m_prevMag, m_fftSize/2 + 1);
}

void
PercussiveAudioCurve::setFftSize(int newSize)
{
    m_prevMag = reallocate(m_prevMag, m_fftSize/2 + 1, newSize/2 + 1);
    AudioCurveCalculator::setFftSize(newSize);
    reset();
}

float
PercussiveAudioCurve::processFloat(const float *R__ mag, int increment)
{
    static float threshold = powf(10.f, 0.15f); // 3dB rise in square of magnitude
    static float zeroThresh = powf(10.f, -8);

    int count = 0;
    int nonZeroCount = 0;

    const int sz = m_lastPerceivedBin;

    for (int n = 1; n <= sz; ++n) {
        float v = 0.f;
        if (m_prevMag[n] > zeroThresh) v = mag[n] / m_prevMag[n];
        else if (mag[n] > zeroThresh) v = threshold;
        bool above = (v >= threshold);
        if (above) ++count;
        if (mag[n] > zeroThresh) ++nonZeroCount;
    }

    v_convert(m_prevMag, mag, sz + 1);

    if (nonZeroCount == 0) return 0;
    else return float(count) / float(nonZeroCount);
}

double
PercussiveAudioCurve::processDouble(const double *R__ mag, int increment)
{
    static double threshold = powf(10., 0.15); // 3dB rise in square of magnitude
    static double zeroThresh = powf(10., -8);

    int count = 0;
    int nonZeroCount = 0;

    const int sz = m_lastPerceivedBin;

    for (int n = 1; n <= sz; ++n) {
        double v = 0.0;
        if (m_prevMag[n] > zeroThresh) v = mag[n] / m_prevMag[n];
        else if (mag[n] > zeroThresh) v = threshold;
        bool above = (v >= threshold);
        if (above) ++count;
        if (mag[n] > zeroThresh) ++nonZeroCount;
    }

    v_copy(m_prevMag, mag, sz + 1);

    if (nonZeroCount == 0) return 0;
    else return double(count) / double(nonZeroCount);
}


}

