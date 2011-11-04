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

/**
 * AudioCurveCalculator turns a sequence of audio "columns" --
 * short-time spectrum magnitude blocks -- into a sequence of numbers
 * representing some quality of the input such as power or likelihood
 * of an onset occurring.
 *
 * These are typically low-level building-blocks: AudioCurveCalculator
 * is a simple causal interface in which each input column corresponds
 * to exactly one output value which is returned immediately.  They
 * have far less power (because of the causal interface and
 * magnitude-only input) and flexibility (because of the limited
 * return types) than for example the Vamp plugin interface.
 *
 * AudioCurveCalculator implementations typically remember the history
 * of their processing data, and the caller must call reset() before
 * resynchronising to an unrelated piece of input audio.
 */
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


    /**
     * Process the given magnitude spectrum block and return the curve
     * value for it.  The mag input contains (fftSize/2 + 1) values
     * corresponding to the magnitudes of the complex FFT output bins
     * for a windowed input of size fftSize.  The hop (expressed in
     * time-domain audio samples) from the previous to the current
     * input block is given by increment.
     */
    virtual float processFloat(const float *R__ mag, int increment) = 0;

    /**
     * Process the given magnitude spectrum block and return the curve
     * value for it.  The mag input contains (fftSize/2 + 1) values
     * corresponding to the magnitudes of the complex FFT output bins
     * for a windowed input of size fftSize.  The hop (expressed in
     * time-domain audio samples) from the previous to the current
     * input block is given by increment.
     */
    virtual double processDouble(const double *R__ mag, int increment) = 0;

    /**
     * Reset the calculator, forgetting the history of the audio input
     * so far.
     */
    virtual void reset() = 0;

    /**
     * If the output of this calculator has a known unit, return it as
     * text.  For example, "Hz" or "V".
     */
    virtual const char *getUnit() const { return ""; }

protected:
    int m_sampleRate;
    int m_fftSize;
    int m_lastPerceivedBin;
    void recalculateLastPerceivedBin();
};


}

#endif

