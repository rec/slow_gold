/*
 * Hermitian FFT of real data
 *
 * Routines for split-radix, real-only transforms. Copyright 1991 NeXT, Inc.
 * All Rights Reserved.
 *
 * These routines are adapted from Sorenson, et. al., (1987) IEEE Trans.
 * Acoustics Speech and Sig. Proc., ASSP-35, 6, pp. 849-863
 *
 * When all x[j] are real the standard DFT of (x[0],x[1],...,x[N-1]), call it
 * x^, has the property of Hermitian symmetry: x^[j] = x^[N-j]*. Thus we only
 * need to find the set (x^[0].re, x^[1].re,..., x^[N/2].re, x^[N/2-1].im,
 * ..., x^[1].im) which, like the original signal x, has N elements. The two
 * key routines perform forward (real-to-Hermitian) FFT, and backward
 * (Hermitian-to-real) FFT, respectively. For example, the sequence:
 *
 * fft_hermitian(x, N); fft_inverse_hermitian(x, N);
 *
 * is an identity operation on the signal x.
 */

#include <stdlib.h>
#include <string.h>

#ifndef _WIN32_WCE
#include <stdio.h>
#endif

#include "hfft.h"
#include "mfMath.h"
#include "mfMacros.h"

#define TWOPI (double)(2*3.14159265358979323846264338327950)
#define SQRTHALF (double)(0.707106781186547524400844362104849)

/* old, slower version, with type of x changed from double to long */
static void scramble_long(long *x, long n)
{
  register long i, j, k;
  long          tmp;
  for (i = 0, j = 0; i < n - 1; i++)
    {
      if (i < j)
        {
          tmp = x[j];
          x[j] = x[i];
          x[i] = tmp;
        }
      k = n >> 1;
      while (k <= j)
        {
          j -= k;
          k >>= 1;
        }
      j += k;
    }
}

static void scramble_data(double * x, FFT_INFO* info)
{
  long       i, j;
  double  tmp;
  double* xip;
  double* xjp;
  long*      flip = info->flip;
  long       n = info->size;

  for (i = n; --i != -1;)
    {
      j = flip[i];
      if (i < j)
        {
          xip = x + i;
          xjp = x + j;
          tmp = *xjp;
          *xjp = *xip;
          *xip = tmp;
        }
    }
}

FFT_INFO* fft_initialize(long n)
{
  long      i;
  double    arg = TWOPI / n;
  FFT_INFO* info;

  info = (FFT_INFO*) Malloc(sizeof(FFT_INFO));
  if (!info)
    return 0;

  info->flip = (long*) Malloc(n * sizeof(long));
  if (!(info->flip))
    {
      Free(info);
      return 0;
    }
  for (i=0; i<n; i++)
    info->flip[i] = i;
  scramble_long(info->flip, n);

  info->cossinarr = (double*) Malloc(2 * n * sizeof(double));
  if (!(info->cossinarr))
    {
      Free(info->flip);
      Free(info);
      return 0;
    }
  for (i = 0; i < n; i++)
    {
      info->cossinarr[2 * i] = cos(i * arg);
      info->cossinarr[2 * i + 1] = sin(i * arg);
    }

  info->size = n;
  return info;
}

void fft_destroy(FFT_INFO* info)
{
  if (!info)
    return;

  if (info->flip)
    Free(info->flip);
  if (info->cossinarr)
    Free(info->cossinarr);
  Free(info);
}

void fft_hermitian(double * z, FFT_INFO* info)
{
  long      n = info->size;
  double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8;
  double t1, t2, t3, t4, t5, t6;
  long      nn = n >> 1, is, id0, i0, i1;
  double sqrthalf = SQRTHALF;
  double *x, *y, e;
  double cc1, ss1, cc3, ss3, cas1, cas3;
  long      n2, n4, n8, i, j, a, a3, pc, nminus = n - 1;
  double *cossinarr = info->cossinarr;

  scramble_data(z, info);
  x = z - 1;  /* FORTRAN indexing compatibility. */
  is = 1;
  id0 = 4;
  do
    {
      for (i0 = is; i0 <= n; i0 += id0)
        {
          i1 = i0 + 1;
          e = x[i0];
          x[i0] = e + x[i1];
          x[i1] = e - x[i1];
        }
      id0 += id0;
      is = id0 - 1;
      id0 += id0;
    } while (is < n);
  n2 = 2;
  pc = n >> 2;
  while (nn >>= 1)
    {
      n2 += n2;
      n8 = n2 >> 3;
      n4 = n2 >> 2;
      is = 0;
      id0 = n2 + n2;
      do
        {
          if (n4 == 1)
            for (i = is; i < n; i += id0)
              {
                x1 = x + i + 1;
                x2 = x1 + n4;
                x3 = x2 + n4;
                x4 = x3 + n4;
                t1 = *x4 + *x3;
                *x4 -= *x3;
                *x3 = *x1 - t1;
                *x1 += t1;
              } else
            {
              x1 = x + is + 1;
              x2 = x1 + n4;
              x3 = x2 + n4;
              x4 = x3 + n4;
              i0 = id0 - n8;
              for (i = is; i < n; i += id0)
                {
                  t1 = *x4 + *x3;
                  *x4 -= *x3;
                  *x3 = *x1 - t1;
                  *x1 += t1;
                  x1 += n8;
                  x2 += n8;
                  x3 += n8;
                  x4 += n8;
                  t1 = (*x3 + *x4) * sqrthalf;
                  t2 = *x3;
                  t2 -= *x4;
                  t2 = t2 * sqrthalf;
                  *x4 = *x2 - t1;
                  *x3 = -*x2 - t1;
                  *x2 = *x1 - t2;
                  *x1 += t2;
                  x1 += i0;
                  x2 += i0;
                  x3 += i0;
                  x4 += i0;
                }
            }
          id0 += id0;
          is = id0 - n2;
          id0 += id0;
        } while (is < n);
      a = pc;
      for (j = 2; j <= n8; j++)
        {
          a3 = a + a;
          y = cossinarr + a3;
          a3 += a;
          a3 &= nminus;
          cc1 = *y++;
          ss1 = *y;
          a3 += a3;
          y = cossinarr + a3;
          cc3 = *y++;
          ss3 = *y;
          cas1 = cc1 + ss1;
          cas3 = cc3 + ss3;
          a += pc;
          a &= nminus;
          is = 0;
          id0 = n2 + n2;
          do
            {
              x1 = x + is + j;
              x2 = x1 + n4;
              x3 = x2 + n4;
              x4 = x3 + n4;
              x5 = x2 + 2 - j - j;
              x6 = x5 + n4;
              x7 = x6 + n4;
              x8 = x7 + n4;
              for (i = is + id0; i < n; i += id0)
                {
                  /*
                   * These old butterflies have been
                   * replaced by 3-mul convolutions. t1
                   * = (*x3) * (cc1) + (*x7) * (ss1); t2
                   * = (*x7) * (cc1) - (*x3) * (ss1); t3
                   * = (*x4) * (cc3) + (*x8) * (ss3); t4
                   * = (*x8) * (cc3) - (*x4) * (ss3);
                   */

                  t5 = ((*x3 + *x7)) * ( cas1);
                  t2 = (*x7) * ( cc1);
                  t6 = (*x3) * ( ss1);
                  t1 = t5 - t6 - t2;
                  t2 -= t6;

                  t5 = ((*x4 + *x8)) * ( cas3);
                  t4 = (*x8) * ( cc3);
                  t6 = (*x4) * ( ss3);
                  t3 = t5 - t6 - t4;
                  t4 -= t6;

                  t5 = t1 + t3;
                  t6 = t2 + t4;
                  t3 = t1 - t3;
                  t4 -= t2;
                  *x8 = *x6 + t6;
                  *x3 = t6 - *x6;
                  *x4 = *x2 - t3;
                  *x7 = -*x2 - t3;
                  *x6 = *x1 - t5;
                  *x1 += t5;
                  *x2 = *x5 - t4;
                  *x5 += t4;
                  x1 += id0;
                  x2 += id0;
                  x3 += id0;
                  x4 += id0;
                  x5 += id0;
                  x6 += id0;
                  x7 += id0;
                  x8 += id0;
                }
              t5 = ((*x3 + *x7)) * ( cas1);
              t2 = (*x7) * ( cc1);
              t6 = (*x3) * ( ss1);
              t1 = t5 - t6 - t2;
              t2 -= t6;
              t5 = ((*x4 + *x8)) * ( cas3);
              t4 = (*x8) * ( cc3);
              t6 = (*x4) * ( ss3);
              t3 = t5 - t6 - t4;
              t4 -= t6;

              t5 = t1 + t3;
              t6 = t2 + t4;
              t3 = t1 - t3;
              t4 -= t2;   /* negative that in prev.
                           * version */
              *x8 = *x6 + t6;
              *x3 = t6 - *x6;
              *x4 = *x2 - t3;
              *x7 = -*x2 - t3;
              *x6 = *x1 - t5;
              *x1 += t5;
              *x2 = *x5 - t4;
              *x5 += t4;

              id0 += id0;
              is = id0 - n2;
              id0 += id0;
            } while (is < n);
        }
      pc >>= 1;
    }
}

void fft_inverse_hermitian(double * z, FFT_INFO* info)
{
  long      n = info->size;
  double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8;
  double t1, t2, t3, t4, t5;
  long      nn = n >> 1, is, id0, i0, i1;
  double sqrthalf = SQRTHALF;
  double *x, *y, e;
  double cc1, ss1, cc3, ss3, cas1, cas3;
  long      n2, n4, n8, i, j, a, a3, pc, nminus = n - 1;
  long      n_2 = n >> 1, n_4 = n >> 2, n3_4 = n_2 + n_4;
  double *cossinarr = info->cossinarr;

  x = z - 1;
  n2 = n + n;
  pc = 1;
  while (nn >>= 1)
    {
      is = 0;
      id0 = n2;
      n2 >>= 1;
      n4 = n2 >> 2;
      n8 = n4 >> 1;
      do
        {
          if (n4 == 1)
            {
              for (i = is; i < n; i += id0)
                {
                  x1 = x + i + 1;
                  x2 = x1 + n4;
                  x3 = x2 + n4;
                  x4 = x3 + n4;
                  t1 = *x1 - *x3;
                  *x1 += *x3;
                  *x2 += *x2;
                  *x3 = *x4;
                  *x3 += *x3;
                  *x4 = *x3 + t1;
                  *x3 = t1 - *x3;
                }
            } else
            {
              x1 = x + is + 1;
              x2 = x1 + n4;
              x3 = x2 + n4;
              x4 = x3 + n4;
              i0 = id0 - n8;
              for (i = is; i < n; i += id0)
                {
                  t1 = *x1 - *x3;
                  *x1 += *x3;
                  *x2 += *x2;
                  *x3 = *x4;
                  *x3 += *x3;
                  *x4 = *x3 + t1;
                  *x3 = t1 - *x3;
                  x1 += n8;
                  x2 += n8;
                  x3 += n8;
                  x4 += n8;
                  t1 = ((*x2 - *x1)) * ( sqrthalf);
                  t2 = ((*x4 + *x3)) * ( sqrthalf);
                  *x1 += *x2;
                  *x2 = *x4 - *x3;
                  t3 = t1 - t2;
                  *x4 = t3 + t3;
                  t3 = -t2 - t1;  /* $$$rec fixed bug. */
                  *x3 = t3 + t3;
                  x1 += i0;
                  x2 += i0;
                  x3 += i0;
                  x4 += i0;
                }
            }
          id0 += id0;
          is = id0 - n2;
          id0 += id0;
        } while (is < nminus);


      a = pc;
      for (j = 2; j <= n8; j++)
        {
          is = 0;
          id0 = n2 + n2;

          if (a == 0)
            {   /* (1+0i, 1+0i) butterfly. */
              a += pc;
              a &= nminus;
              do
                {
                  x1 = x + is + j;
                  x2 = x1 + n4;
                  x3 = x2 + n4;
                  x4 = x3 + n4;
                  x5 = x2 + 2 - j - j;
                  x6 = x5 + n4;
                  x7 = x6 + n4;
                  x8 = x7 + n4;
                  for (i = is + id0; i < n; i += id0)
                    {
                      t1 = *x1 - *x6;
                      *x1 += *x6;
                      t2 = *x5 - *x2;
                      *x5 += *x2;
                      t3 = *x8 + *x3;
                      *x6 = *x8 - *x3;
                      t4 = *x4 + *x7;
                      *x2 = *x4 - *x7;
                      t5 = t1 - t4;
                      t1 += t4;
                      t4 = t2 - t3;
                      t2 += t3;

                      *x3 = t5;   /* Trivial 'fly. */
                      *x7 = -t4;
                      *x4 = t1;
                      *x8 = t2;

                      x1 += id0;
                      x2 += id0;
                      x3 += id0;
                      x4 += id0;
                      x5 += id0;
                      x6 += id0;
                      x7 += id0;
                      x8 += id0;
                    }
                  t1 = *x1 - *x6;
                  *x1 += *x6;
                  t2 = *x5 - *x2;
                  *x5 += *x2;
                  t3 = *x8 + *x3;
                  *x6 = *x8 - *x3;
                  t4 = *x4 + *x7;
                  *x2 = *x4 - *x7;
                  t5 = t1 - t4;
                  t1 += t4;
                  t4 = t2 - t3;
                  t2 += t3;

                  *x3 = t5;
                  *x7 = t5 - t4;
                  *x8 = t2;
                  *x4 = t1 - t2;

                  id0 += id0;
                  is = id0 - n2;
                  id0 += id0;
                } while (is < nminus);
            } else if (a == n_4)
            {   /* (0+1i, 0-1i) butterfly. */
              a += pc;
              a &= nminus;
              do
                {
                  x1 = x + is + j;
                  x2 = x1 + n4;
                  x3 = x2 + n4;
                  x4 = x3 + n4;
                  x5 = x2 + 2 - j - j;
                  x6 = x5 + n4;
                  x7 = x6 + n4;
                  x8 = x7 + n4;
                  for (i = is + id0; i < n; i += id0)
                    {
                      t1 = *x1 - *x6;
                      *x1 += *x6;
                      t2 = *x5 - *x2;
                      *x5 += *x2;
                      t3 = *x8 + *x3;
                      *x6 = *x8 - *x3;
                      t4 = *x4 + *x7;
                      *x2 = *x4 - *x7;
                      t5 = t1 - t4;
                      t1 += t4;
                      t4 = t2 - t3;
                      t2 += t3;

                      *x3 = t4;   /* Trivial 'fly. */
                      *x7 = t5;
                      *x4 = t2;
                      *x8 = -t1;

                      x1 += id0;
                      x2 += id0;
                      x3 += id0;
                      x4 += id0;
                      x5 += id0;
                      x6 += id0;
                      x7 += id0;
                      x8 += id0;
                    }
                  t1 = *x1 - *x6;
                  *x1 += *x6;
                  t2 = *x5 - *x2;
                  *x5 += *x2;
                  t3 = *x8 + *x3;
                  *x6 = *x8 - *x3;
                  t4 = *x4 + *x7;
                  *x2 = *x4 - *x7;
                  t5 = t1 - t4;
                  t1 += t4;
                  t4 = t2 - t3;
                  t2 += t3;

                  *x3 = t4 - t5;
                  *x7 = t5;
                  *x8 = -t1;
                  *x4 = t2;

                  id0 += id0;
                  is = id0 - n2;
                  id0 += id0;
                } while (is < nminus);
            } else if (a == n_2)
            {   /* (-1+0i, -1+0i) butterfly. */
              a += pc;
              a &= nminus;
              do
                {
                  x1 = x + is + j;
                  x2 = x1 + n4;
                  x3 = x2 + n4;
                  x4 = x3 + n4;
                  x5 = x2 + 2 - j - j;
                  x6 = x5 + n4;
                  x7 = x6 + n4;
                  x8 = x7 + n4;
                  for (i = is + id0; i < n; i += id0)
                    {
                      t1 = *x1 - *x6;
                      *x1 += *x6;
                      t2 = *x5 - *x2;
                      *x5 += *x2;
                      t3 = *x8 + *x3;
                      *x6 = *x8 - *x3;
                      t4 = *x4 + *x7;
                      *x2 = *x4 - *x7;
                      t5 = t1 - t4;
                      t1 += t4;
                      t4 = t2 - t3;
                      t2 += t3;

                      *x3 = -t5;  /* Trivial 'fly. */
                      *x7 = t4;
                      *x4 = -t1;
                      *x8 = -t2;

                      x1 += id0;
                      x2 += id0;
                      x3 += id0;
                      x4 += id0;
                      x5 += id0;
                      x6 += id0;
                      x7 += id0;
                      x8 += id0;
                    }
                  t1 = *x1 - *x6;
                  *x1 += *x6;
                  t2 = *x5 - *x2;
                  *x5 += *x2;
                  t3 = *x8 + *x3;
                  *x6 = *x8 - *x3;
                  t4 = *x4 + *x7;
                  *x2 = *x4 - *x7;
                  t5 = t1 - t4;
                  t1 += t4;
                  t4 = t2 - t3;
                  t2 += t3;

                  *x3 = -t5;
                  *x7 = t4;
                  *x8 = -t2;
                  *x4 = -t1;

                  id0 += id0;
                  is = id0 - n2;
                  id0 += id0;
                } while (is < nminus);
            } else if (a == n3_4)
            {   /* (0-1i,0+1i) butterfly. */
              a += pc;
              a &= nminus;
              do
                {
                  x1 = x + is + j;
                  x2 = x1 + n4;
                  x3 = x2 + n4;
                  x4 = x3 + n4;
                  x5 = x2 + 2 - j - j;
                  x6 = x5 + n4;
                  x7 = x6 + n4;
                  x8 = x7 + n4;
                  for (i = is + id0; i < n; i += id0)
                    {
                      t1 = *x1 - *x6;
                      *x1 += *x6;
                      t2 = *x5 - *x2;
                      *x5 += *x2;
                      t3 = *x8 + *x3;
                      *x6 = *x8 - *x3;
                      t4 = *x4 + *x7;
                      *x2 = *x4 - *x7;
                      t5 = t1 - t4;
                      t1 += t4;
                      t4 = t2 - t3;
                      t2 += t3;

                      *x3 = -t4;  /* Trivial 'fly. */
                      *x7 = -t5;
                      *x4 = -t2;
                      *x8 = t1;

                      x1 += id0;
                      x2 += id0;
                      x3 += id0;
                      x4 += id0;
                      x5 += id0;
                      x6 += id0;
                      x7 += id0;
                      x8 += id0;
                    }
                  t1 = *x1 - *x6;
                  *x1 += *x6;
                  t2 = *x5 - *x2;
                  *x5 += *x2;
                  t3 = *x8 + *x3;
                  *x6 = *x8 - *x3;
                  t4 = *x4 + *x7;
                  *x2 = *x4 - *x7;
                  t5 = t1 - t4;
                  t1 += t4;
                  t4 = t2 - t3;
                  t2 += t3;

                  *x3 = -t4;
                  *x7 = t5;
                  *x8 = t1;
                  *x4 = -t2;

                  id0 += id0;
                  is = id0 - n2;
                  id0 += id0;
                } while (is < nminus);
            } else
            {
              a3 = a + a;
              y = cossinarr + a3;
              a3 += a;
              a3 &= nminus;
              a += pc;
              a &= nminus;
              cc1 = *y++;
              ss1 = *y;
              a3 += a3;
              y = cossinarr + a3;
              cc3 = *y++;
              ss3 = *y;
              cas1 = cc1 + ss1;
              cas3 = cc3 + ss3;


              do
                {
                  x1 = x + is + j;
                  x2 = x1 + n4;
                  x3 = x2 + n4;
                  x4 = x3 + n4;
                  x5 = x2 + 2 - j - j;
                  x6 = x5 + n4;
                  x7 = x6 + n4;
                  x8 = x7 + n4;
                  for (i = is + id0; i < n; i += id0)
                    {
                      t1 = *x1 - *x6;
                      *x1 += *x6;
                      t2 = *x5 - *x2;
                      *x5 += *x2;
                      t3 = *x8 + *x3;
                      *x6 = *x8 - *x3;
                      t4 = *x4 + *x7;
                      *x2 = *x4 - *x7;
                      t5 = t1 - t4;
                      t1 += t4;
                      t4 = t2 - t3;
                      t2 += t3;

                      /*
                       * These old butterflies have
                       * been replaced by 3-mul
                       * convolutions. x3 =
                       * t5 * cc1 + (t4) * (ss1);
                       * x7 = (t5) * (ss1) -
                       * (t4) * (cc1); x4 =
                       * (t1) * (cc3) - (t2) * (ss3);
                       * x8 = (t2) * (cc3) +
                       * (t1) * (ss3);
                       */

                      t3 = ((t5 + t4)) * ( cas1);
                      t4 = (t4) * ( cc1);
                      t5 = (t5) * ( ss1);
                      *x3 = t3 - t4 - t5;
                      *x7 = t5 - t4;
                      t3 = ((t1 + t2)) * ( cas3);
                      t2 = (t2) * ( ss3);
                      t1 = (t1) * ( cc3);
                      *x8 = t3 - t2 - t1;
                      *x4 = t1 - t2;

                      x1 += id0;
                      x2 += id0;
                      x3 += id0;
                      x4 += id0;
                      x5 += id0;
                      x6 += id0;
                      x7 += id0;
                      x8 += id0;
                    }
                  t1 = *x1 - *x6;
                  *x1 += *x6;
                  t2 = *x5 - *x2;
                  *x5 += *x2;
                  t3 = *x8 + *x3;
                  *x6 = *x8 - *x3;
                  t4 = *x4 + *x7;
                  *x2 = *x4 - *x7;
                  t5 = t1 - t4;
                  t1 += t4;
                  t4 = t2 - t3;
                  t2 += t3;

                  t3 = ((t5 + t4)) * ( cas1);
                  t4 = (t4) * ( cc1);
                  t5 = (t5) * ( ss1);
                  *x3 = t3 - t4 - t5;
                  *x7 = t5 - t4;
                  t3 = ((t1 + t2)) * ( cas3);
                  t2 = (t2) * ( ss3);
                  t1 = (t1) * ( cc3);
                  *x8 = t3 - t2 - t1;
                  *x4 = t1 - t2;

                  id0 += id0;
                  is = id0 - n2;
                  id0 += id0;
                } while (is < nminus);
            }
        }
      pc += pc;
    }
  is = 1;
  id0 = 4;
  do
    {
      for (i0 = is; i0 <= n; i0 += id0)
        {
          i1 = i0 + 1;
          e = x[i0];
          x[i0] = e + x[i1];
          x[i1] = e - x[i1];
        }
      id0 += id0;
      is = id0 - 1;
      id0 += id0;
    } while (is < n);
  scramble_data(z, info);

  e = 1 / (double) n;
  for (i = (n >> 2), x = z; --i != -1;)
    {
      *x++ *= e;
      *x++ *= e;
      *x++ *= e;
      *x++ *= e;
    }
}
