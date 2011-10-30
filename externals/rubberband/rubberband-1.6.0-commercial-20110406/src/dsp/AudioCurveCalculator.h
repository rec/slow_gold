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

#ifndef _AUDIO_CURVE_CALCULATOR_H_
#define _AUDIO_CURVE_CALCULATOR_H_

#include <sys/types.h>


#include "system/sysutils.h"

namespace RubberBand 
{

class AudioCurveCalculator
{
public:
    struct Parameters {
        Parameters(int _sampleRate, int _fftSize) :
            sampleRate(_sampleRate),
            fftSize(_fftSize)
        { }
        int sampleRate;
        int fftSize;
    };

    AudioCurveCalculator(Parameters parameters);
    virtual ~AudioCurveCalculator();

    int getSampleRate() const { return m_sampleRate; }
    int getFftSize() const { return m_fftSize; }

    virtual void setSampleRate(int newRate);
    virtual void setFftSize(int newSize);

    Parameters getParameters() const {
        return Parameters(m_sampleRate, m_fftSize);
    }
    void setParameters(Parameters p) {
        setSampleRate(p.sampleRate);
        setFftSize(p.fftSize);
    }

    // You may not mix calls to the various process functions on a
    // given instance


    virtual float processFloat(const float *R__ mag, int increment) = 0;
    virtual double processDouble(const double *R__ mag, int increment) = 0;

    virtual void reset() = 0;

    virtual const char *getUnit() const { return ""; }

protected:
    int m_sampleRate;
    int m_fftSize;
    int m_lastPerceivedBin;
    void recalculateLastPerceivedBin();
};


}

#endif

