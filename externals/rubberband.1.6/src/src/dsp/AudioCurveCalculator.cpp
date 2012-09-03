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

#include "AudioCurveCalculator.h"

#include <iostream>

namespace RubberBand
{

static const int MaxPerceivedFreq = 16000;

AudioCurveCalculator::AudioCurveCalculator(Parameters parameters) :
    m_sampleRate(parameters.sampleRate),
    m_fftSize(parameters.fftSize)
{
    recalculateLastPerceivedBin();
}

AudioCurveCalculator::~AudioCurveCalculator()
{
}

void
AudioCurveCalculator::setSampleRate(int newRate)
{
    m_sampleRate = newRate;
    recalculateLastPerceivedBin();
}

void
AudioCurveCalculator::setFftSize(int newSize)
{
    m_fftSize = newSize;
    recalculateLastPerceivedBin();
}

void
AudioCurveCalculator::recalculateLastPerceivedBin()
{
    if (m_sampleRate == 0) {
        m_lastPerceivedBin = 0;
        return;
    }
    m_lastPerceivedBin = ((MaxPerceivedFreq * m_fftSize) / m_sampleRate);
    if (m_lastPerceivedBin > m_fftSize/2) {
        m_lastPerceivedBin = m_fftSize/2;
    }
}


}
