/*
 *----------------------------------------------------------------------------
 * Copyright notice:
 * (c) Copyright 2000 Audible Magic Corporation
 * All rights reserved.
 *
 * This program is protected as an unpublished work under the U.S. copyright
 * laws. The above copyright notice is not intended to effect a publication of
 * this work.
 *
 * This program is the confidential and proprietary information of Audible
 * Magic.  Neither the binaries nor the source code may be redistributed
 * without prior written permission from Audible Magic.
 *----------------------------------------------------------------------------
 *
 * File: AudioResampler.cpp
 */

#include <memory.h>
#include <stdio.h>
#include <math.h>
#include "AudioResampler.h"

#define MAX_OVERRUN_BUFFER_SIZE 4096

AudioResampler::AudioResampler()
{
  for (int i=0; i<MAX_CHANNELS; i++)
    {
      m_pFOverrunBuffer[i] = NULL;
    }
  Reset();
  // this must be bigger than our winSize variable to make sure that we
  // have pre-read more than the needed window size.  For quality of 1.0
  // winSize is about 20.
  m_lOverlapFrames = 128;
}

AudioResampler::~AudioResampler()
{
  DestroyOverrunBuffers();
}

void AudioResampler::Reset()
{
  DestroyOverrunBuffers();
  m_boolInited = 0;
  m_boolFirstTime = 1;
}

unsigned int AudioResampler::GetOutputBufferSize(unsigned int inBufferSizeIn)
{
  unsigned int size = 0;
  float fRatio = m_RS[0].fRateIn / m_RS[0].fRateOut;

  if (m_boolInited == 1)
    {
      size = (unsigned int)((double)inBufferSizeIn * fRatio);
    }
  return size;
}

unsigned int AudioResampler::GetInputBufferSize(unsigned int inBufferSizeOut)
{
  unsigned int size = 0;
  float fRatio = m_RS[0].fRateOut / m_RS[0].fRateIn;

  // round up to nearest multiple of 128
  unsigned int normalizedSize = (unsigned int)((double)inBufferSizeOut / fRatio);
  normalizedSize = ((normalizedSize/128)+1) * 128;

  if (m_boolInited == 1)
    {
      if (m_boolFirstTime)
        {
          size = 1536 + normalizedSize;
          m_boolFirstTime = 0;
          return size;
        }
      else
        {
          long overruns = GetOverrunBufferNumSamples(0);

          if (overruns >= (long)inBufferSizeOut)
            {
              size = 0;    // already have enough
            }
          else
            {
              size = normalizedSize;
            }
        }
    }
  return size;
}



long AudioResampler::Process(float** inBuf,
                             float** outBuf,
                             unsigned int inNumSamplesIn,
                             unsigned int inNumSamplesOut)
{
  long samplesWritten = 0;

  if (m_boolInited != 1)
    return samplesWritten;

  for (int i=0; i<m_numChannels; i++)
    {
      samplesWritten = ProcessChannel(i, inBuf[i], outBuf[i], inNumSamplesIn, inNumSamplesOut);
    }
  return samplesWritten;
}



unsigned int AudioResampler::Init( double inRate, double outRate,
                                   unsigned int inNumChannels, float fQuality, float fCutoffFreq, float gain)
{
  ResampleStruct* pRS;
  int i;
  int one = 1;            /* for kaiser call */
  unsigned int err;

  for (i=0; i<MAX_CHANNELS; i++)
    {
      memset((void*)&m_RS[i], 0, sizeof(ResampleStruct));

      pRS = &m_RS[i];

      pRS->pFInput1  = 0;  /* pointer to start of input buffer */
      pRS->pFInput2  = 0;  /* pointer to start of input buffer */
      pRS->pFWindow  = 0;  /* pointer to center of analysis window */
      pRS->N = 120;    /* length of sinc period */
      pRS->L = 120;    /* internal sample rate is L*inRate */
      pRS->nMin = 0;   /* first sample */
      pRS->fBeta = 6.8;/* parameter for Kaiser window */
      pRS->fL = 120.;  /* float L */

      pRS->bufRead.index = pRS->bufWrite.index = 0;
      pRS->bufRead.nSamples = pRS->bufWrite.nSamples = 0;
      pRS->isStream = FALSE; /*TLB HARDWIRED FOR NON-AO CASE -- AudioObjectIsStream(pAOin);*/

      pRS->fRateIn  = inRate; /*pAOin->info->rate;*/
      pRS->fRateOut = outRate; /*fOutputSampleRate;*/

      pRS->nChannelsIn = inNumChannels; /*pAOin->info->channels;*/
      m_numChannels = inNumChannels;

      /*
       * calculate increment: if decimating, then pFWindow is impulse
       * response of low-pass filter with cutoff frequency at half of
       * fRateOut; if interpolating, then pFWindow is impulse response of
       * lowpass filter with cutoff frequency at half of fRateIn.
       */

      pRS->fDelta = ((float) (pRS->L * pRS->fRateIn) / pRS->fRateOut);
      pRS->delta = pRS->fDelta;
      pRS->fDeltaInt = pRS->delta;
      if (pRS->delta > pRS->L)
        pRS->N = pRS->delta;

      pRS->winLength = fQuality * pRS->N * 10 + 1;

      pRS->nChunkSize = IBUF / 8; //2;

      /*
       * make pFWindow: pFWindow is the product of a kaiser and a sin(x)/x
       * low-pass filter.
       */

      if ((pRS->pFWindow = (float *) Calloc((pRS->winLength+1), sizeof(float))) == NULL)
        {
          err = OUT_OF_MEMORY_ERR;
          return err;
        }

      pRS->winSizeL = (pRS->winLength-1)/2;
      pRS->pFWindow += pRS->winSizeL; /* move the pointer to the middle of the window */
      pRS->winSize = (pRS->winLength/2 - pRS->L) / pRS->L;

      /* weird call because translated from FORTRAN */
      /* Generate the positive side of the filter window.*/
      kaiser(&pRS->winLength, pRS->pFWindow, &pRS->winSizeL, &one, &pRS->fBeta);

      /* Then mirror the positive elements onto the negative side. */
      for (i = 1; i <= pRS->winSizeL; i++)
        pRS->pFWindow[-i] = pRS->pFWindow[i];

      /*
       * allow the cutoff frequency to be altered slightly by applying
       * user-specified cutoff multiplier.
       */
      for (i = 1; i <= pRS->winSizeL; i++)
        pRS->pFWindow[i] = pRS->pFWindow[-i] *= pRS->N * sin((double) fCutoffFreq*PI*i/pRS->N) / (PI*i);

      pRS->fSum = pRS->pFWindow[0];
      for (i = pRS->L-1; i <= pRS->winSizeL; i += pRS->L)
        pRS->fSum += pRS->pFWindow[-i] + pRS->pFWindow[i];

      pRS->fSum = 1.0 / pRS->fSum;

      pRS->pFWindow[0] *= pRS->fSum;
      for (i = 1; i <= pRS->winSizeL; i++)
        pRS->pFWindow[i] = pRS->pFWindow[-i] *= pRS->fSum;

      pRS->pFWindow[pRS->winSizeL+1] = 0;

      /*
       * set up input buffer:  nextIn1 is the index of the next empty
       * word in the input buffer for channel 1. (nextIn2 is the equivalent
       * for channel 2 if input AudioObject is stereo.) If the buffer is
       * full, then nextIn1(&2) jumps back to the beginning, and the old
       * values are written over.
       */
      if ((pRS->pFInput1 = (float *) Calloc(IBUF, sizeof(float))) == NULL)
        {
          err = OUT_OF_MEMORY_ERR;
          return err;
        }
      if (pRS->nChannelsIn == 2)
        {
          if ((pRS->pFInput2 = (float *) Calloc(IBUF, sizeof(float))) == NULL)
            {
              err = OUT_OF_MEMORY_ERR;
              return err;
            }
        }

      pRS->nextIn1 = 0;
      if (pRS->nChannelsIn == 2)
        pRS->nextIn2 = 0;

      pRS->fQuality = fQuality;
      pRS->fCutoffFreq = fCutoffFreq;
      pRS->fGain = gain;
      pRS->boolFirstCall = TRUE;
      pRS->boolStopping = FALSE;
      pRS->clipCount = 0;
    }

  m_numChannels = inNumChannels;
  m_boolInited = 1;

  // now create overrun buffers
  DestroyOverrunBuffers();
  CreateOverrunBuffers(MAX_OVERRUN_BUFFER_SIZE, m_numChannels);

  return 0;    // success
}

/*
 * ProcessResample
 *  This is the non-AudioObject version of the bufferized
 *  routine written by Jim 7/29/02.  It does NOT
 *  support changed to resample rate, gain, or quality inbetween
 *  calls.  Also, this requires the input buffer to be a
 *  multiple of 512!!! And the input and output buffers contain
 *  float 32-bit samples.
 *
 *  NOTE: this version of the routine allocates the output
 *  buffer and updates the argument containing number of output samples.
 */
long AudioResampler::ProcessChannel(int channel,
                                    float*    inBuf,
                                    float*    outBuf,
                                    unsigned int    inNumSamplesIn,
                                    unsigned int    inNumSamplesOut)
{
  int        i,j,k;              /* index variables */
  float*    pOutBuf;
  float*    pInBuf;

  unsigned int    numSamplesWritten = 0;
  unsigned int    numSamplesReadTotal = 0;
  float    sample = 0.0;

  ResampleStruct* pRS = &m_RS[channel];

  pOutBuf = outBuf;
  pInBuf = inBuf;

  if (pRS->boolFirstCall)
    {
      // first time through we stop short of using all samples
      pRS->boolFirstCall = FALSE;    /* reset */
      pRS->nFrames = inNumSamplesIn/pRS->nChannelsIn - m_lOverlapFrames;
      pRS->nFramesRead = 0;

      // fill double 512 sample buffers (1024 samples) with incoming data.
      for (i = 0; i < IBUF; i++)
        {
          if ((pRS->nFramesRead < pRS->nFrames))
            {
              pRS->sample = *pInBuf++;
              pRS->nFramesRead++;
              numSamplesReadTotal++;
            }
          else
            pRS->sample = 0;
          pRS->pFInput1[pRS->nextIn1++] = pRS->fGain * pRS->sample;

        }
      pRS->jMin = -(pRS->winSize + 1) * pRS->L;
      pRS->mMax = IBUF;
      pRS->o = pRS->n = pRS->m = 0;
      pRS->fO = 0.;
    }
  else
    {
      // first see if we can load the overrun samples into the output buffer
      unsigned int lNumSamples = GetOverrunBufferNumSamples(channel);
      if (lNumSamples > 0)
        {
          if (lNumSamples <= inNumSamplesOut)
            {
              EmptyOverrunBuffer(channel, lNumSamples, pOutBuf);
              pOutBuf += lNumSamples;
              numSamplesWritten += lNumSamples;
            }
          else
            {
              // only need part of the overrun buffer!
              EmptyOverrunBuffer(channel, inNumSamplesOut, pOutBuf);
              return inNumSamplesOut;
            }
        }
      // each time we are called, add the number of incoming frames
      // from pAOin to pRS->nFrames
      pRS->nFrames += inNumSamplesIn/pRS->nChannelsIn;
    }

  while ((pRS->n < pRS->nFrames))
    {
      /*
       * case 1:  (fRateIn / fRateOut) * 120 = integer
       */

      if (pRS->fDeltaInt == pRS->fDelta)
        {

          /*
           * apply pFWindow (pFWindow is sampled at L * fRateIn)
           */

          pRS->fSum1 = 0.;
          j = pRS->jMin - pRS->o;
          k = pRS->m - pRS->winSize;
          if (k < 0) k += IBUF;
          for (i = -pRS->winSize; i <= pRS->winSize+1; i++)
            {
              j += pRS->L;
              if (++k >= IBUF)
                k = 0;
              pRS->fSum1 += pRS->pFWindow[j] * pRS->pFInput1[k];
            }

          sample = pRS->fSum1;
          if (numSamplesWritten < inNumSamplesOut)
            {
              *pOutBuf++ = sample;
              numSamplesWritten++;
            }
          else
            {
              // store remaining samples in overrun buffer
              WriteToOverrunBuffer(channel, sample);
            }

          /*
           * move pFWindow (pFWindow advances by o samples at
           * L * fRateIn sample rate)
           */

          pRS->o += pRS->delta;
          while (pRS->o >= pRS->L)
            {
              pRS->o -= pRS->L;
              pRS->n++;
              pRS->m++;
              if (pRS->m + pRS->winSize + 1 >= pRS->mMax)
                {
                  pRS->mMax += pRS->nChunkSize;
                  if (pRS->nextIn1 >= IBUF)
                    pRS->nextIn1 = 0;
                  // read next chunk size (128) frames
                  for (i = 0; i < pRS->nChunkSize; i++)
                    {
                      pRS->sample = *pInBuf++;
                      pRS->nFramesRead++;
                      numSamplesReadTotal++;

                      pRS->pFInput1[pRS->nextIn1++] = pRS->fGain * pRS->sample;
                    }
                }
              if (pRS->m >= IBUF)
                {
                  pRS->m = 0;
                  pRS->mMax = pRS->nChunkSize;
                }
            }

        }

      /*
       * case 2: (fRateIn / fRateOut) * 120 = non-integer constant
       */

      else
        {

          /*
           * apply pFWindow (pFWindow values are linearly interpolated)
           */

          pRS->fSum1 = 0.;
          pRS->o = pRS->fO;
          pRS->fOFrac = pRS->fO - pRS->o;
          j = pRS->jMin - pRS->o;
          k = pRS->m - pRS->winSize;
          if (k < 0)
            k += IBUF;
          for (i = -pRS->winSize; i <= pRS->winSize+1; i++)
            {
              j += pRS->L;
              if (++k >= IBUF)
                k = 0;
              pRS->fInterpVal = pRS->pFWindow[j] + pRS->fOFrac * (pRS->pFWindow[j+1] - pRS->pFWindow[j]);
              pRS->fSum1 += pRS->fInterpVal * pRS->pFInput1[k];
            }

          sample = pRS->fSum1;
          if (numSamplesWritten < inNumSamplesOut)
            {
              *pOutBuf++ = sample;
              numSamplesWritten++;
            }
          else
            {
              // store remaining samples in overrun buffer
              WriteToOverrunBuffer(channel, sample);
            }

          /*
           * move pFWindow
           */

          pRS->fO += pRS->fDelta;
          while (pRS->fO >= pRS->fL)
            {
              pRS->fO -= pRS->fL;
              pRS->n++;
              pRS->m++;
              if (pRS->m + pRS->winSize + 1 >= pRS->mMax)
                {
                  pRS->mMax += pRS->nChunkSize;
                  if (pRS->nextIn1 >= IBUF)
                    pRS->nextIn1 = 0;
                  for (i = 0; i < pRS->nChunkSize; i++)
                    {
                      pRS->sample = *pInBuf++;
                      pRS->nFramesRead++;
                      numSamplesReadTotal++;

                      pRS->pFInput1[pRS->nextIn1++] = pRS->fGain * pRS->sample;
                    }
                }
              if (pRS->m >= IBUF)
                {
                  pRS->m = 0;
                  pRS->mMax = pRS->nChunkSize;
                }
            }

        }
    }


  return numSamplesWritten;

}


// PRIVATE HELPER FUNCTIONS
#if 0
/*
 * flushes remaining samples
 */
int AudioResampler::flushSamplesNonAO(float* outBuf, RWBuffer* bufWrite,
                                      unsigned int numSamplesOutMax, unsigned int* pNumSamplesWritten)
{
  int        err = 0;    /* SUCCESS */
  int        writeErr = 0;
  long    nSamplesTotal = 0;
  long    i, j;

  long start = 0;

  j = 0;
  while (nSamplesTotal < bufWrite->index)
    {
      long nSamplesWritten;

      if (((bufWrite->index)-nSamplesTotal) < (numSamplesOutMax - *pNumSamplesWritten))
        {
          for (i=nSamplesTotal; i<((bufWrite->index)-nSamplesTotal); i++)
            {
              outBuf[j++] = ((float) bufWrite->samples[i] / (float) 32767);
            }
          nSamplesWritten = (bufWrite->index)-nSamplesTotal;
          nSamplesTotal += nSamplesWritten;
        }
      else
        {
          for (i=nSamplesTotal; i<(numSamplesOutMax - *pNumSamplesWritten); i++)
            {
              outBuf[j++] = ((float) bufWrite->samples[i] / (float) 32767);
            }
          nSamplesWritten = (numSamplesOutMax - *pNumSamplesWritten);
          nSamplesTotal += nSamplesWritten;
        }
#if 0
      if (CheckTimeout(&start, 10000))
        {
          bufWrite->index = 0;
          return writeErr;
        }
      Sleep(1);
#endif

    }
  bufWrite->index = 0;
  *pNumSamplesWritten += nSamplesTotal;

  return err;
}
#endif

void AudioResampler::ClearOverrunBuffers()
{
  for (int i=0; i<MAX_CHANNELS; i++)
    {
      if (m_pFOverrunBuffer[i] != NULL)
        {
          memset((void*)m_pFOverrunBuffer[i], 0, m_sizeOverrunBuffer*sizeof(float));
          m_overrunPosition[i] = 0;
        }
    }
}

void AudioResampler::CreateOverrunBuffers(long bufSize, int numChannels)
{
  DestroyOverrunBuffers();
  m_sizeOverrunBuffer = bufSize;
  for (int i=0; i<numChannels; i++)
    {
      m_pFOverrunBuffer[i] = (float*)Calloc((unsigned)m_sizeOverrunBuffer, (unsigned)sizeof(float));
      m_overrunPosition[i] = 0;
    }

}

long AudioResampler::GetOverrunBufferNumSamples(int channel)
{
  if (m_pFOverrunBuffer[channel] != NULL)
    {
      return m_overrunPosition[channel];
    }
  else
    return 0;
}



void AudioResampler::DestroyOverrunBuffers()
{
  for (int i=0; i<MAX_CHANNELS; i++)
    {
      if (m_pFOverrunBuffer[i] != NULL)
        {
          Free(m_pFOverrunBuffer[i]);
          m_pFOverrunBuffer[i] = NULL;
        }
    }
}

void AudioResampler::WriteToOverrunBuffer(int channel, float fValue)
{
  if (m_pFOverrunBuffer[channel] != NULL)
    {
      if (m_overrunPosition[channel] >= m_sizeOverrunBuffer)
        {
          // DANGER TOO MANY INPUT SAMPLES HAVEN'T BEEN EATEN
          return;
        }
      float* pFOverrunBuffer = m_pFOverrunBuffer[channel];
      long position = m_overrunPosition[channel];
      pFOverrunBuffer[position] = fValue;
      m_overrunPosition[channel]++;
    }
}

void AudioResampler::EmptyOverrunBuffer(int channel, int count, float* pFOutBuffer)
{
  if (m_pFOverrunBuffer[channel] != NULL)
    {
      float* pFOverrunBuffer = m_pFOverrunBuffer[channel];
      for (int i=0; i<count; i++)
        {
          *pFOutBuffer++ = *pFOverrunBuffer++;
        }
      if (count < m_overrunPosition[channel])
        {
          // didn't copy all of the floats out, so move them down
          // inefficient, but shouldn't happen if sizes being passed to
          // Process(...) are large enough
          long index = 0;
          for (int i=count; i<m_overrunPosition[channel]; i++)
            {
              pFOverrunBuffer = m_pFOverrunBuffer[channel];
              pFOverrunBuffer[index++] = pFOverrunBuffer[i];
            }
          m_overrunPosition[channel] -= count;
        }
      else
        {
          memset((void*)m_pFOverrunBuffer[channel], 0, m_sizeOverrunBuffer*sizeof(float));
          m_overrunPosition[channel] = 0;
        }
    }
}



/*
 * ReadSampleNonAO
 *   read a single float sample from the input buffer
 */
int AudioResampler::ReadSampleNonAO(float* pSample, float* pInBuf, unsigned int inNumSamplesTotal,
                                    unsigned int* pNumSamplesRead, unsigned int* pNumSamplesReadTotal, bool stopping,
                                    bool isStream, RWBuffer* bufRead)
{
  unsigned int  err = 0;

  int i = 0;

  if (bufRead->index < bufRead->nSamples)
    {
      *pSample = bufRead->samples[bufRead->index++];
      return err;
    }

  bufRead->nSamples = 0;
  bufRead->index = 0;
  *pNumSamplesRead = 0;

  /* keep reading until you get a sample */
  while (bufRead->nSamples == 0)
    {
      if (stopping)
        return END_OF_FILE_ERR;    /* this will cause us to exit */
      if ((*pNumSamplesRead + *pNumSamplesReadTotal) >= inNumSamplesTotal)
        break;

      for (i = 0; i < RW_BUFFER_SIZE; i++)
        {
          if (*pNumSamplesReadTotal >= inNumSamplesTotal)
            {
              err = END_OF_FILE_ERR;
              break;
            }

          bufRead->samples[i /*bufRead->index++*/] = (long) ((float) 32767 * *pInBuf++);
          bufRead->nSamples++;
          *pNumSamplesRead += 1;
          *pNumSamplesReadTotal += 1;
        }
      if ((!isStream) || (((err != END_OF_FILE_ERR) && (err != 0)) && isStream))
        break;

      err = 0;    /* SUCCESS */

#if 0
      if (CheckTimeout(&start, 10000))
        return END_OF_FILE_ERR;
      Sleep(1);
#endif
    }

  *pSample = bufRead->samples[bufRead->index++];
  return err;
}





/*-----------------------------------------------------------------------
 * FUNCTION:  INO
 * BESSEL FUNCTION FOR KAISER WINDOW
 *
 * TRANSLATED FROM FORTRAN
 *-----------------------------------------------------------------------
 */
float AudioResampler::ino(float x)
{
  int i;
  float de, e, ino_v, sde, t, xi, y;

  y = x/2.0;
  t = 1.0e-08;
  e = 1.0;
  de = 1.0;
  for( i = 1; i <= 25; i++ )
    {
      xi = i;
      de = de*y/xi;
      sde = de*de;
      e = e + sde;
      if ((e*t - sde) <= 0.0)
        goto L_10;
      else
        goto L_20;
    L_10:
      ;
    }
 L_20:
  ino_v = e;
  return( ino_v );
} /* end of function */


/*-----------------------------------------------------------------------
 * SUBROUTINE:  KAISER
 * KAISER WINDOW
 *
 * TRANSLATED FROM FORTRAN
 *-----------------------------------------------------------------------
 */
void AudioResampler::kaiser(int *filterLen, float window[],
                            int *filterHalfLen, int *isFLenOdd,
                            float *kaiserBeta)
{
  int i;
  float bes, xi, xind;

  /*
   *  filterLen: Filter length in samples
   *  window: Window array of size (filterHalfLen)
   *  filterHalfLen: Filter half length ((filterLen+1)/2)
   *  isFLenOdd: Oddness flag for filterLen, 0 if filterLen is even
   *  kaiserBeta: Parameter of Kaiser window, fed into Bessel function above
   */
  bes = ino( *kaiserBeta );
  xind = (float)( *filterLen - 1 )*(float)( *filterLen - 1 );
  for( i = 0; i < *filterHalfLen; i++ )
    {
      xi = i;
      if(! *isFLenOdd)
        xi = xi + 0.5;
      xi = 4.0*xi*xi;
      window[i] = ino((float) (*kaiserBeta * sqrt((double) (1.0 - xi/xind))));
      window[i] = window[i]/bes;
    }
  return;
} /* end of function */



