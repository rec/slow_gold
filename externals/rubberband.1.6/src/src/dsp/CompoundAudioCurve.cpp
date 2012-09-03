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

#include "CompoundAudioCurve.h"

#include "MovingMedian.h"

#include <iostream>

namespace RubberBand
{


CompoundAudioCurve::CompoundAudioCurve(Parameters parameters) :
    AudioCurveCalculator(parameters),
    m_percussive(parameters),
    m_hf(parameters),
    m_hfFilter(new MovingMedian<double>(19, 85)),
    m_hfDerivFilter(new MovingMedian<double>(19, 90)),
    m_type(CompoundDetector),
    m_lastHf(0.0),
    m_lastResult(0.0),
    m_risingCount(0)
{
}

CompoundAudioCurve::~CompoundAudioCurve()
{
    delete m_hfFilter;
    delete m_hfDerivFilter;
}

void
CompoundAudioCurve::setType(Type type)
{
    m_type = type;
}

void
CompoundAudioCurve::reset()
{
    m_percussive.reset();
    m_hf.reset();
    m_hfFilter->reset();
    m_hfDerivFilter->reset();
    m_lastHf = 0.0;
    m_lastResult = 0.0;
}

void
CompoundAudioCurve::setFftSize(int newSize)
{
    m_percussive.setFftSize(newSize);
    m_hf.setFftSize(newSize);
    m_fftSize = newSize;
    m_lastHf = 0.0;
    m_lastResult = 0.0;
}

float
CompoundAudioCurve::processFloat(const float *R__ mag, int increment)
{
    float percussive = 0.f;
    float hf = 0.f;
    switch (m_type) {
    case PercussiveDetector:
        percussive = m_percussive.processFloat(mag, increment);
        break;
    case CompoundDetector:
        percussive = m_percussive.processFloat(mag, increment);
        hf = m_hf.processFloat(mag, increment);
        break;
    case SoftDetector:
        hf = m_hf.processFloat(mag, increment);
        break;
    }
    return processFiltering(percussive, hf);
}

double
CompoundAudioCurve::processDouble(const double *R__ mag, int increment)
{
    double percussive = 0.0;
    double hf = 0.0;
    switch (m_type) {
    case PercussiveDetector:
        percussive = m_percussive.processDouble(mag, increment);
        break;
    case CompoundDetector:
        percussive = m_percussive.processDouble(mag, increment);
        hf = m_hf.processDouble(mag, increment);
        break;
    case SoftDetector:
        hf = m_hf.processDouble(mag, increment);
        break;
    }
    return processFiltering(percussive, hf);
}

double
CompoundAudioCurve::processFiltering(double percussive, double hf)
{
    if (m_type == PercussiveDetector) {
        return percussive;
    }

    double rv = 0.f;
    
    double hfDeriv = hf - m_lastHf;

    m_hfFilter->push(hf);
    m_hfDerivFilter->push(hfDeriv);

    double hfFiltered = m_hfFilter->get();
    double hfDerivFiltered = m_hfDerivFilter->get();

    m_lastHf = hf;

    double result = 0.f;
    
    double hfExcess = hf - hfFiltered;

    if (hfExcess > 0.0) {
        result = hfDeriv - hfDerivFiltered;
    }

    if (result < m_lastResult) {
        if (m_risingCount > 3 && m_lastResult > 0) rv = 0.5;
        m_risingCount = 0;
    } else {
        m_risingCount ++;
    }

    if (m_type == CompoundDetector) {
        if (percussive > 0.35 && percussive > rv) {
            rv = percussive;
        }
    }

    m_lastResult = result;

    return rv;
}


}

