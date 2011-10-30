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

#ifndef _RUBBERBAND_RINGBUFFER_H_
#define _RUBBERBAND_RINGBUFFER_H_

#include <sys/types.h>

#include "Scavenger.h"

//#define DEBUG_RINGBUFFER 1

#include "system/sysutils.h"
#include "system/Allocators.h"

#ifdef DEBUG_RINGBUFFER
#include <iostream>
#endif

namespace RubberBand {

/**
 * RingBuffer implements a lock-free ring buffer for one writer and N
 * readers, that is to be used to store a sample type T.
 */

template <typename T, int N = 1>
class RingBuffer
{
public:
    /**
     * Create a ring buffer with room to write n samples.
     *
     * Note that the internal storage size will actually be n+1
     * samples, as one element is unavailable for administrative
     * reasons.  Since the ring buffer performs best if its size is a
     * power of two, this means n should ideally be some power of two
     * minus one.
     */
    RingBuffer(int n = 0);

    virtual ~RingBuffer();

    /**
     * Return the total capacity of the ring buffer in samples.
     * (This is the argument n passed to the constructor.)
     */
    int getSize() const;

    /**
     * Resize the ring buffer.  This also empties it; use resized()
     * below if you do not want this to happen.  Actually swaps in a
     * new, larger buffer; the old buffer is scavenged after a seemly
     * delay.  Should be called from the write thread.
     */
    void resize(int newSize);

    /**
     * Return a new ring buffer (allocated with "new" -- called must
     * delete when no longer needed) of the given size, containing the
     * same data as this one.  If another thread reads from or writes
     * to this buffer during the call, the results may be incomplete
     * or inconsistent.  If this buffer's data will not fit in the new
     * size, the contents are undefined.
     */
    RingBuffer<T, N> *resized(int newSize, int R = 0) const;

    /**
     * Lock the ring buffer into physical memory.  Returns true
     * for success.
     */
    bool mlock();

    /**
     * Reset read and write pointers, thus emptying the buffer.
     * Should be called from the write thread.
     */
    void reset();

    /**
     * Return the amount of data available for reading by reader R, in
     * samples.
     */
    int getReadSpace(int R = 0) const;

    /**
     * Return the amount of space available for writing, in samples.
     */
    int getWriteSpace() const;

    /**
     * Read n samples from the buffer, for reader R.  If fewer than n
     * are available, the remainder will be zeroed out.  Returns the
     * number of samples actually read.
     *
     * This is a template function, taking an argument S for the target
     * sample type, which is permitted to differ from T if the two
     * types are compatible for assignment.
     */
    template <typename S>
    int read(S *const R__ destination, int n, int R = 0);

    /**
     * Read n samples from the buffer, for reader R, adding them to
     * the destination.  If fewer than n are available, the remainder
     * will be left alone.  Returns the number of samples actually
     * read.
     */
    int readAdding(T *const R__ destination, int n, int R = 0);

    /**
     * Read one sample from the buffer, for reader R.  If no sample is
     * available, this will silently return zero.  Calling this
     * repeatedly is obviously slower than calling read once, but it
     * may be good enough if you don't want to allocate a buffer to
     * read into.
     */
    T readOne(int R = 0);

    /**
     * Read n samples from the buffer, if available, for reader R,
     * without advancing the read pointer -- i.e. a subsequent read()
     * or skip() will be necessary to empty the buffer.  If fewer than
     * n are available, the remainder will be zeroed out.  Returns the
     * number of samples actually read.
     */
    int peek(T *const R__ destination, int n, int R = 0) const;

    /**
     * Read one sample from the buffer, if available, without
     * advancing the read pointer -- i.e. a subsequent read() or
     * skip() will be necessary to empty the buffer.  Returns zero if
     * no sample was available.
     */
    T peekOne(int R = 0) const;

    /**
     * Pretend to read n samples from the buffer, for reader R,
     * without actually returning them (i.e. discard the next n
     * samples).  Returns the number of samples actually available for
     * discarding.
     */
    int skip(int n, int R = 0);

    /**
     * Write n samples to the buffer.  If insufficient space is
     * available, not all samples may actually be written.  Returns
     * the number of samples actually written.
     *
     * This is a template function, taking an argument S for the source
     * sample type, which is permitted to differ from T if the two
     * types are compatible for assignment.
     */
    template <typename S>
    int write(const S *const R__ source, int n);

    /**
     * Write n zero-value samples to the buffer.  If insufficient
     * space is available, not all zeros may actually be written.
     * Returns the number of zeroes actually written.
     */
    int zero(int n);

protected:
    T *R__           m_buffer;
    volatile int     m_writer;
    volatile int     m_readers[N];
    int              m_size;
    bool             m_mlocked;

    static Scavenger<ScavengerArrayWrapper<T> > m_scavenger;

private:
    RingBuffer(const RingBuffer &); // not provided
    RingBuffer &operator=(const RingBuffer &); // not provided
};

template <typename T, int N>
Scavenger<ScavengerArrayWrapper<T> > RingBuffer<T, N>::m_scavenger;

template <typename T, int N>
RingBuffer<T, N>::RingBuffer(int n) :
    m_writer(0),
    m_size(n + 1),
    m_mlocked(false)
{
    m_buffer = allocate<T>(n + 1);

#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::RingBuffer(" << n << ")" << std::endl;
#endif

    for (int i = 0; i < N; ++i) m_readers[i] = 0;

    m_scavenger.scavenge();
}

template <typename T, int N>
RingBuffer<T, N>::~RingBuffer()
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::~RingBuffer" << std::endl;
#endif

    if (m_mlocked) {
	MUNLOCK((void *)m_buffer, m_size * sizeof(T));
    }

    deallocate<T>(m_buffer);

    m_scavenger.scavenge();
}

template <typename T, int N>
int
RingBuffer<T, N>::getSize() const
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::getSize(): " << m_size-1 << std::endl;
#endif

    return m_size - 1;
}

template <typename T, int N>
void
RingBuffer<T, N>::resize(int newSize)
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::resize(" << newSize << ")" << std::endl;
#endif

    m_scavenger.scavenge();

    if (m_mlocked) {
	MUNLOCK((void *)m_buffer, m_size * sizeof(T));
    }

    m_scavenger.claim(new ScavengerArrayWrapper<T>(m_buffer));

    reset();
    m_buffer = allocate<T>(newSize + 1);
    m_size = newSize + 1;

    if (m_mlocked) {
	if (MLOCK((void *)m_buffer, m_size * sizeof(T))) {
	    m_mlocked = false;
	}
    }
}

template <typename T, int N>
RingBuffer<T, N> *
RingBuffer<T, N>::resized(int newSize, int R) const
{
    RingBuffer<T, N> *newBuffer = new RingBuffer<T, N>(newSize);

    int w = m_writer;
    int r = m_readers[R];

    while (r != w) {
        T value = m_buffer[r];
        newBuffer->write(&value, 1);
        if (++r == m_size) r = 0;
    }

    return newBuffer;
}

template <typename T, int N>
bool
RingBuffer<T, N>::mlock()
{
    if (MLOCK((void *)m_buffer, m_size * sizeof(T))) return false;
    m_mlocked = true;
    return true;
}

template <typename T, int N>
void
RingBuffer<T, N>::reset()
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::reset" << std::endl;
#endif

    m_writer = 0;
    for (int i = 0; i < N; ++i) m_readers[i] = 0;
}

template <typename T, int N>
int
RingBuffer<T, N>::getReadSpace(int R) const
{
    int writer = m_writer;
    int reader = m_readers[R];
    int space;

#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::getReadSpace(" << R << "): reader " << reader << ", writer " << writer << std::endl;
#endif

    if (writer > reader) space = writer - reader;
    else if (writer < reader) space = (writer + m_size) - reader;
    else space = 0;

#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::getReadSpace(" << R << "): " << space << std::endl;
#endif

    return space;
}

template <typename T, int N>
int
RingBuffer<T, N>::getWriteSpace() const
{
    int space = 0;
    for (int i = 0; i < N; ++i) {
        int writer = m_writer;
        int reader = m_readers[i];
	int here = (reader + m_size - writer - 1);
        if (here >= m_size) here -= m_size;
	if (i == 0 || here < space) space = here;
    }

#ifdef DEBUG_RINGBUFFER
    int rs(getReadSpace()), rp(m_readers[0]);

    std::cerr << "RingBuffer: write space " << space << ", read space "
	      << rs << ", total " << (space + rs) << ", m_size " << m_size << std::endl;
    std::cerr << "RingBuffer: reader " << rp << ", writer " << m_writer << std::endl;
#endif

#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::getWriteSpace(): " << space << std::endl;
#endif

    return space;
}

template <typename T, int N>
template <typename S>
int
RingBuffer<T, N>::read(S *const R__ destination, int n, int R)
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::read(dest, " << n << ", " << R << ")" << std::endl;
#endif

    int available = getReadSpace(R);
    if (n > available) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: Only " << available << " samples available"
		  << std::endl;
#endif
        for (int i = available; i < n; ++i) {
            destination[i] = S(0);
        }
	n = available;
    }
    if (n == 0) return n;

    int reader = m_readers[R];
    int here = m_size - reader;
    T *const R__ bufbase = m_buffer + reader;

    if (here >= n) {
        v_convert<T, S>(destination, bufbase, n);
    } else {
        v_convert<T, S>(destination, bufbase, here);
        v_convert<T, S>(destination + here, m_buffer, n - here);
    }

    reader += n;
    while (reader >= m_size) reader -= m_size;
    m_readers[R] = reader;

#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::read: read " << n << ", reader now " << m_readers[R] << std::endl;
#endif

    return n;
}

template <typename T, int N>
int
RingBuffer<T, N>::readAdding(T *const R__ destination, int n, int R)
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::readAdding(dest, " << n << ", " << R << ")" << std::endl;
#endif

    int available = getReadSpace(R);
    if (n > available) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: Only " << available << " samples available"
		  << std::endl;
#endif
	n = available;
    }
    if (n == 0) return n;

    int reader = m_readers[R];
    int here = m_size - reader;
    const T *const R__ bufbase = m_buffer + reader;

    if (here >= n) {
        v_add(destination, bufbase, n);
    } else {
        v_add(destination, bufbase, here);
        v_add(destination + here, m_buffer, n - here);
    }

    reader += n;
    while (reader >= m_size) reader -= m_size;
    m_readers[R] = reader;
    return n;
}

template <typename T, int N>
T
RingBuffer<T, N>::readOne(int R)
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::readOne(" << R << ")" << std::endl;
#endif

    if (m_writer == m_readers[R]) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: No sample available"
		  << std::endl;
#endif
	return 0;
    }
    int reader = m_readers[R];
    T value = m_buffer[reader];
    if (++reader == m_size) reader = 0;
    m_readers[R] = reader;
    return value;
}

template <typename T, int N>
int
RingBuffer<T, N>::peek(T *const R__ destination, int n, int R) const
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::peek(dest, " << n << ", " << R << ")" << std::endl;
#endif

    int available = getReadSpace(R);
    if (n > available) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: Only " << available << " samples available"
		  << std::endl;
#endif
	memset(destination + available, 0, (n - available) * sizeof(T));
	n = available;
    }
    if (n == 0) return n;

    int reader = m_readers[R];
    int here = m_size - reader;
    const T *const R__ bufbase = m_buffer + reader;

    if (here >= n) {
        v_copy(destination, bufbase, n);
    } else {
        v_copy(destination, bufbase, here);
        v_copy(destination + here, m_buffer, n - here);
    }

#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::peek: read " << n << std::endl;
#endif

    return n;
}

template <typename T, int N>
T
RingBuffer<T, N>::peekOne(int R) const
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::peek(" << R << ")" << std::endl;
#endif

    if (m_writer == m_readers[R]) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: No sample available"
		  << std::endl;
#endif
	return 0;
    }
    T value = m_buffer[m_readers[R]];
    return value;
}

template <typename T, int N>
int
RingBuffer<T, N>::skip(int n, int R)
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::skip(" << n << ", " << R << ")" << std::endl;
#endif

    int available = getReadSpace(R);
    if (n > available) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: Only " << available << " samples available"
		  << std::endl;
#endif
	n = available;
    }
    if (n == 0) return n;

    int reader = m_readers[R];
    reader += n;
    while (reader >= m_size) reader -= m_size;
    m_readers[R] = reader;
    return n;
}

template <typename T, int N>
template <typename S>
int
RingBuffer<T, N>::write(const S *const R__ source, int n)
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::write(" << n << ")" << std::endl;
#endif

    int available = getWriteSpace();
    if (n > available) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: Only room for " << available << " samples"
		  << std::endl;
#endif
	n = available;
    }
    if (n == 0) return n;

    int writer = m_writer;
    int here = m_size - writer;
    T *const R__ bufbase = m_buffer + writer;

    if (here >= n) {
        v_convert<S, T>(bufbase, source, n);
    } else {
        v_convert<S, T>(bufbase, source, here);
        v_convert<S, T>(m_buffer, source + here, n - here);
    }

    writer += n;
    while (writer >= m_size) writer -= m_size;
    m_writer = writer;

#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::write: wrote " << n << ", writer now " << m_writer << std::endl;
#endif

    return n;
}

template <typename T, int N>
int
RingBuffer<T, N>::zero(int n)
{
#ifdef DEBUG_RINGBUFFER
    std::cerr << "RingBuffer<T," << N << ">[" << this << "]::zero(" << n << ")" << std::endl;
#endif

    int available = getWriteSpace();
    if (n > available) {
#ifdef DEBUG_RINGBUFFER
	std::cerr << "WARNING: Only room for " << available << " samples"
		  << std::endl;
#endif
	n = available;
    }
    if (n == 0) return n;

    int writer = m_writer;
    int here = m_size - writer;
    T *const R__ bufbase = m_buffer + writer;

    if (here >= n) {
        v_zero(bufbase, n);
    } else {
        v_zero(bufbase, here);
        v_zero(m_buffer, n - here);
    }

    writer += n;
    while (writer >= m_size) writer -= m_size;
    m_writer = writer;

#ifdef DEBUG_RINGBUFFER
    std::cerr << "writer -> " << m_writer << std::endl;
#endif

    return n;
}

}

#endif // _RINGBUFFER_H_
