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

#ifndef _RUBBERBAND_STRETCHERCHANNELDATA_H_
#define _RUBBERBAND_STRETCHERCHANNELDATA_H_

#include "StretcherImpl.h"

#include <set>

//#define EXPERIMENT 1

namespace RubberBand
{

class Resampler;

class RubberBandStretcher::Impl::ChannelData
{
public:        
    /**
     * Construct a ChannelData structure.
     *
     * The sizes passed in here are for the time-domain analysis
     * window and FFT calculation, and most of the buffer sizes also
     * depend on them.  In practice they are always powers of two, the
     * window and FFT sizes are either equal or generally in a 2:1
     * relationship either way, and except for very extreme stretches
     * the FFT size is either 1024, 2048 or 4096.
     *
     * The outbuf size depends on other factors as well, including
     * the pitch scale factor and any maximum processing block
     * size specified by the user of the code.
     */
    ChannelData(size_t windowSize,
                size_t fftSize,
                size_t outbufSize);

    /**
     * Construct a ChannelData structure that can process at different
     * FFT sizes without requiring reallocation when the size changes.
     * The sizes can subsequently be changed with a call to setSizes.
     * Reallocation will only be necessary if setSizes is called with
     * values not equal to any of those passed in to the constructor.
     *
     * The outbufSize should be the maximum possible outbufSize to
     * avoid reallocation, which will happen if setOutbufSize is
     * called subsequently.
     */
    ChannelData(const std::set<size_t> &sizes,
                size_t initialWindowSize,
                size_t initialFftSize,
                size_t outbufSize);
    ~ChannelData();

    /**
     * Reset buffers
     */
    void reset();

    /**
     * Set the FFT, analysis window, and buffer sizes.  If this
     * ChannelData was constructed with a set of sizes and the given
     * window and FFT sizes here were among them, no reallocation will
     * be required.
     */
    void setSizes(size_t windowSize, size_t fftSizes);

    /**
     * Set the outbufSize for the channel data.  Reallocation will
     * occur.
     */
    void setOutbufSize(size_t outbufSize);

    /**
     * Set the resampler buffer size.  Default if not called is no
     * buffer allocated at all.
     */
    void setResampleBufSize(size_t resamplebufSize);
    
    RingBuffer<float> *inbuf;
    RingBuffer<float> *outbuf;

    process_t *mag;
    process_t *phase;

    process_t *prevPhase;
    process_t *prevError;
    process_t *unwrappedPhase;

    size_t *freqPeak;

    float *accumulator;
    size_t accumulatorFill;
    float *windowAccumulator;
    float *interpolator; // only used when time-domain smoothing is on
    int interpolatorScale;

    float *fltbuf;
    process_t *dblbuf; // owned by FFT object, only used for time domain FFT i/o
    process_t *envelope; // for cepstral formant shift
    bool unchanged;

    size_t prevIncrement; // only used in RT mode

    size_t chunkCount;
    size_t inCount;
    long inputSize; // set only after known (when data ended); -1 previously
    size_t outCount;

    bool draining;
    bool outputComplete;

    FFT *fft;
    std::map<size_t, FFT *> ffts;

    Resampler *resampler;
    float *resamplebuf;
    size_t resamplebufSize;

private:
    void construct(const std::set<size_t> &sizes,
                   size_t initialWindowSize, size_t initialFftSize,
                   size_t outbufSize);
};        

}

#endif
