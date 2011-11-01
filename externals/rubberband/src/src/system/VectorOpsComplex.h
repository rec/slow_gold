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

#ifndef _RUBBERBAND_VECTOR_OPS_COMPLEX_H_
#define _RUBBERBAND_VECTOR_OPS_COMPLEX_H_

#include "VectorOps.h"


namespace RubberBand {


template<typename T>
inline void c_phasor(T *real, T *imag, T phase)
{
    //!!! IPP contains ippsSinCos_xxx in ippvm.h -- these are
    //!!! fixed-accuracy, test and compare
#if defined HAVE_VDSP
    int one = 1;
    if (sizeof(T) == sizeof(float)) {
        vvsincosf((float *)imag, (float *)real, (const float *)&phase, &one);
    } else {
        vvsincos((double *)imag, (double *)real, (const double *)&phase, &one);
    }
#elif defined __GNUC__
    if (sizeof(T) == sizeof(float)) {
        sincosf(phase, (float *)imag, (float *)real);
    } else {
        sincos(phase, (double *)imag, (double *)real);
    }
#else
    if (sizeof(T) == sizeof(float)) {
        *real = cosf(phase);
        *imag = sinf(phase);
    } else {
        *real = cos(phase);
        *imag = sin(phase);
    }
#endif
}

template<typename T>
inline void c_magphase(T *mag, T *phase, T real, T imag)
{
    *mag = sqrt(real * real + imag * imag);
    *phase = atan2(imag, real);
}

#ifdef USE_APPROXIMATE_ATAN2
// NB arguments in opposite order from usual for atan2f
extern float approximate_atan2f(float real, float imag);
template<>
inline void c_magphase(float *mag, float *phase, float real, float imag)
{
    float atan = approximate_atan2f(real, imag);
    *phase = atan;
    *mag = sqrtf(real * real + imag * imag);
}
#else
template<>
inline void c_magphase(float *mag, float *phase, float real, float imag)
{
    *mag = sqrtf(real * real + imag * imag);
    *phase = atan2f(imag, real);
}
#endif


template<typename T>
void v_polar_to_cartesian(T *const R__ real,
                          T *const R__ imag,
                          T *const R__ mag,
                          T *const R__ phase,
                          const int count)
{
    for (int i = 0; i < count; ++i) {
        c_phasor(real + i, imag + i, phase[i]);
    }
    v_multiply(real, mag, count);
    v_multiply(imag, mag, count);
}

template<typename T>
void v_polar_interleaved_to_cartesian_inplace(T *const R__ srcdst,
                                              const int count)
{
    T real, imag;
    for (int i = 0; i < count*2; i += 2) {
        c_phasor(&real, &imag, srcdst[i+1]);
        real *= srcdst[i];
        imag *= srcdst[i];
        srcdst[i] = real;
        srcdst[i+1] = imag;
    }
}

template<typename T>
void v_cartesian_to_polar(T *const R__ mag,
                          T *const R__ phase,
                          T *const R__ real,
                          T *const R__ imag,
                          const int count)
{
    for (int i = 0; i < count; ++i) {
        c_magphase(mag + i, phase + i, real[i], imag[i]);
    }
}

template<typename T>
void v_cartesian_interleaved_to_polar(T *const R__ mag,
                                      T *const R__ phase,
                                      const T *const R__ src,
                                      const int count)
{
    for (int i = 0; i < count; ++i) {
        c_magphase(mag + i, phase + i, src[i*2], src[i*2+1]);
    }
}

#ifdef HAVE_VDSP
template<>
inline void v_cartesian_to_polar(float *const R__ mag,
                                 float *const R__ phase,
                                 float *const R__ real,
                                 float *const R__ imag,
                                 const int count)
{
    DSPSplitComplex c;
    c.realp = real;
    c.imagp = imag;
    vDSP_zvmags(&c, 1, phase, 1, count); // using phase as a temporary dest
    vvsqrtf(mag, phase, &count); // using phase as the source
    vvatan2f(phase, imag, real, &count);
}
template<>
inline void v_cartesian_to_polar(double *const R__ mag,
                                 double *const R__ phase,
                                 double *const R__ real,
                                 double *const R__ imag,
                                 const int count)
{
    // double precision, this is significantly faster than using vDSP_polar
    DSPDoubleSplitComplex c;
    c.realp = real;
    c.imagp = imag;
    vDSP_zvmagsD(&c, 1, phase, 1, count); // using phase as a temporary dest
    vvsqrt(mag, phase, &count); // using phase as the source
    vvatan2(phase, imag, real, &count);
}
#endif

template<typename T>
void v_cartesian_to_polar_interleaved_inplace(T *const R__ srcdst,
                                              const int count)
{
    T mag, phase;
    for (int i = 0; i < count * 2; i += 2) {
        c_magphase(&mag, &phase, srcdst[i], srcdst[i+1]);
        srcdst[i] = mag;
        srcdst[i+1] = phase;
    }
}

}

#endif

