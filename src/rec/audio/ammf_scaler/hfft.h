#ifndef HFFT_H
#define HFFT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _fft_info
{
    long      *flip;
    double *cossinarr;
    long      size;
} FFT_INFO;

/*
 * create an FFT_INFO data structure.
 */
FFT_INFO* fft_initialize(long n);

/*
 * destroy an FFT_INFO data structure.
 */
void fft_destroy(FFT_INFO* info);

/*
 * Fast Fourier Transform for real input data z. The length n must be a power
 * of 2. Output is Re[0],...,Re[n/2],Im[n/2-1],...,Im[1]. Uses a
 * decimation-in-time, in-place, split-radix algorithm. Reference: Sorenson,
 * et. al., (1987) IEEE Trans. Acoustics Speech and Sig. Proc., ASSP-35, 6,
 * pp. 849-863.
 */
void fft_hermitian(double * z, FFT_INFO* info);

/*
 * Inverse of fft_real_to_hermitian(). Input is
 * Re[0],...,Re[n/2],Im[n/2-1],...,Im[1]. Uses a decimation-in-frequency,
 * in-place, split-radix algorithm.
 */
void fft_inverse_hermitian(double * z, FFT_INFO* info);

#ifdef __cplusplus
}
#endif

#endif
