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

#ifndef _SAMPLE_FILTER_H_
#define _SAMPLE_FILTER_H_

#include <cassert>

namespace RubberBand
{

template <typename T>
class SampleFilter
{
public:
    SampleFilter(int size) : m_size(size) {
	assert(m_size > 0);
    }

    virtual ~SampleFilter() { }

    int getSize() const { return m_size; }

    virtual void push(T) = 0;
    virtual T get() const = 0;
    virtual void reset() = 0;

protected:
    const int m_size;

private:
    SampleFilter(const SampleFilter &);
    SampleFilter &operator=(const SampleFilter &);
};

}

#endif

