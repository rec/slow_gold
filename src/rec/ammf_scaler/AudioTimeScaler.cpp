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
 * File: AudioTimeScaler.cpp
 */

#include <memory.h>
#include <stdio.h>
#include <math.h>
#include "mfmacros.h"
#include "AudioTimeScaler.h"

static const int MAX_OVERRUN_BUFFER_SIZE = 4096;

static const int MINIMUM_STARTING_SAMPLES_TIME_STRETCH	= 8192;
static const int MINIMUM_STARTING_SAMPLES_TIME_COMPRESS  = 24576;

AudioTimeScaler::AudioTimeScaler() {
  for (int i=0; i<MAX_CHANNELS; i++)
    m_pFOverrunBuffer[i] = NULL;

  Reset();
}

AudioTimeScaler::~AudioTimeScaler() {
  DestroyOverrunBuffers();
}

MFError AudioTimeScaler::Init(double dTimeScale,
                              double dSampleRate,
                              int numChannels,
                              double dPitchScale,
                              int nBands,
                              int filterOverlap) {
  for (int i=0; i<MAX_CHANNELS; i++) {
    memset((void*)&m_PTS[i], 0, sizeof(PitchTimeState));

    // user init values:
    m_PTS[i].dPitchScale = dPitchScale;
    m_PTS[i].dTimeScale = dTimeScale;
    m_PTS[i].nBands = nBands;
    m_PTS[i].filterOverlap = filterOverlap;
    m_PTS[i].dSampleRate = dSampleRate;
    m_PTS[i].channelsIn = 1;           // force to mono for this version
    m_PTS[i].sampleWidthInBytes = 4;    // no longer used - accepts floats only

    // now init variables for first time through
    m_PTS[i].pDInputBuf = 0;  /* pointer to start of input buffer */
    m_PTS[i].pDOutputBuf = 0;  /* pointer to start of output buffer */
    m_PTS[i].pDAnal = 0;  /* pointer to start of analysis buffer */
    m_PTS[i].pDSyn = 0;  /* pointer to start of synthesis buffer */
    m_PTS[i].pDAnalWindowAlloc = 0;
    m_PTS[i].pDSynWindowAlloc = 0;
    m_PTS[i].pDAnalWindow = 0;  /* pointer to center of analysis window */
    m_PTS[i].pDSynWindow = 0;  /* pointer to center of synthesis window */
    m_PTS[i].pDOldInPhase = 0;  /* pointer to start of input phase buffer */
    m_PTS[i].pDOldOutPhase = 0;/* pointer to start of output phase buffer */
    m_PTS[i].pFftInfoAnal = 0;  /* FFT_INFO structure for analysis */
    m_PTS[i].pFftInfoSynth = 0;/* FFT_INFO structure for synthesis */

    m_PTS[i].analWinLen = 0;  /* length of pDAnalWindow impulse response */
    m_PTS[i].synWinLen = 0;  /* length of pDSynWindow impulse response */
    m_PTS[i].samplesTotal = 0;  /* total number of samples in the input */

    m_PTS[i].inputPrevSumSq = 0.02;
    m_PTS[i].outputPrevSumSq = 0.02;
    m_PTS[i].inputPrevMean = 0;
    m_PTS[i].outputPrevMean = 0;
    m_PTS[i].inputVariance = 0.07;
    m_PTS[i].outputVariance = 0.05;
    m_PTS[i].correction = 1.1;
    m_PTS[i].inputCount = 2;
    m_PTS[i].outputCount = 2;

    if (MFError err = AdjustParameters(&m_PTS[i].analHop, &m_PTS[i].synthHop, &m_PTS[i].nBands, &m_PTS[i].analWinLen, &m_PTS[i].synWinLen, m_PTS[i].filterOverlap, &m_PTS[i].dPitchScale, &m_PTS[i].dTimeScale))
      {
        return err;
      }
    m_PTS[i].dFundFreq = m_PTS[i].dSampleRate / m_PTS[i].nBands;

    m_PTS[i].lInBufLen = 4 * m_PTS[i].analWinLen;
    m_PTS[i].lOutBufLen = 4 * m_PTS[i].synWinLen;

    /* synthesis transform will be nBandsScaled points */
    m_PTS[i].nBandsScaled = (int) (((double) m_PTS[i].nBands / m_PTS[i].dPitchScale) + 0.5);
    if ((m_PTS[i].nBandsScaled % 2) != 0)
      m_PTS[i].nBandsScaled += 1;

    /* compute power of two above nBandsScaled */
    m_PTS[i].nBandsScaled2 = 0;
    while (m_PTS[i].nBandsScaled > (1 << m_PTS[i].nBandsScaled2))
      m_PTS[i].nBandsScaled2++;
    m_PTS[i].nBandsScaled2 = 1 << m_PTS[i].nBandsScaled2;

    /* nBands / nBandsScaled = synthHop / analHop = pitch change */
    m_PTS[i].dPitchScale = ((double) m_PTS[i].nBands / m_PTS[i].nBandsScaled);

    m_PTS[i].synthHopScaled = (int) (((double) m_PTS[i].synthHop / m_PTS[i].dPitchScale));

    InitAnalWindow(&m_PTS[i].pDAnalWindow, &m_PTS[i].pDAnalWindowAlloc,
                   m_PTS[i].analWinLen, m_PTS[i].nBands, &m_PTS[i].dSum, &m_PTS[i].analWinHalfLen);
    InitSynWindow(&m_PTS[i].pDSynWindow, &m_PTS[i].pDSynWindowAlloc,
                  m_PTS[i].synWinLen, m_PTS[i].synthHopScaled, m_PTS[i].dSum, &m_PTS[i].synWinHalfLen);

    InitIOBuffers(&m_PTS[i].pDInputBuf, m_PTS[i].lInBufLen, &m_PTS[i].pDOutputBuf, m_PTS[i].lOutBufLen);
    m_PTS[i].nextIn = 0;
    m_PTS[i].nextOut = 0;

    InitBuffers(&m_PTS[i].pDAnal, &m_PTS[i].pDOldInPhase, &m_PTS[i].pFftInfoAnal, m_PTS[i].nBands);
    InitBuffers(&m_PTS[i].pDSyn, &m_PTS[i].pDOldOutPhase, &m_PTS[i].pFftInfoSynth, m_PTS[i].nBandsScaled2);

    /*
     * initialization: input time starts negative so that the rightmost
     * edge of the analysis filter just catches the first non-zero
     * input samples; output time is always dTimeScale times input time.
     */
    m_PTS[i].lInCount = 0;
    m_PTS[i].lOutCount = 0;

    m_PTS[i].dAnalRate = m_PTS[i].dSampleRate / m_PTS[i].analHop;
    m_PTS[i].dSynthRate = m_PTS[i].dSampleRate / m_PTS[i].synthHop;

    m_PTS[i].lCurrAnalSample = -(m_PTS[i].analWinHalfLen / m_PTS[i].analHop) * m_PTS[i].analHop;
    m_PTS[i].lCurrSynthSample = (long) (((double) m_PTS[i].dTimeScale / m_PTS[i].dPitchScale * m_PTS[i].lCurrAnalSample));

    m_PTS[i].samplesToRead = m_PTS[i].analWinHalfLen + m_PTS[i].lCurrAnalSample + 1;
    m_PTS[i].samplesToWrite = 0;
    m_PTS[i].samplesToWriteScaled = 0;

    m_PTS[i].eofFlag = 0;

    /* MODIFICATIONS */
    /* Adjust the history length of the variance estimators to
     * take into acount the time scaling of the output.
     */
    m_PTS[i].inputHistorySamples = (long) (MF_ESTIMATOR_HISTORY* m_PTS[i].dSampleRate);
    m_PTS[i].outputHistorySamples = (long)(MF_ESTIMATOR_HISTORY* m_PTS[i].dSampleRate * m_PTS[i].dTimeScale / m_PTS[i].dPitchScale);
    /****************/
    m_PTS[i].lLastSample = MAX_SAMPLES;
    m_PTS[i].samplesTotal = MAX_SAMPLES;

    if (MFError err = AdjustParameters(&m_PTS[i].analHop, &m_PTS[i].synthHop, &m_PTS[i].nBands,
                                       &m_PTS[i].analWinLen, &m_PTS[i].synWinLen, m_PTS[i].filterOverlap, &m_PTS[i].dPitchScale,
                                       &m_PTS[i].dTimeScale))
      {
        return err;
      }
    m_PTS[i].inputSampleCounter = 0;
  }
  m_numChannels = numChannels;
  m_boolInited = 1;

  // now create overrun buffers
  this->DestroyOverrunBuffers();
  this->CreateOverrunBuffers(MAX_OVERRUN_BUFFER_SIZE, m_numChannels);
  return NULL;
}

void AudioTimeScaler::Reset()
{
  DestroyOverrunBuffers();
  m_boolInited = 0;
  m_boolFirstTime = 1;
}

unsigned int AudioTimeScaler::GetOutputBufferSize(unsigned int inBufferSizeIn)
{
  unsigned int size = 0;

  if (m_boolInited == 1)
    {
      // round up to nearest multiple of 512
      unsigned int normalizedSize = (unsigned int)((double)inBufferSizeIn * m_PTS[0].dTimeScale);
      normalizedSize = ((normalizedSize/512)+1) * 512;

      if (m_boolFirstTime)
        {
          // make sure we don't promise samples unless we have minimum size
          if (this->m_PTS[0].dTimeScale > 1.0)
            {
              if (inBufferSizeIn < MINIMUM_STARTING_SAMPLES_TIME_STRETCH)
                size = 0;
              else
                size = normalizedSize - MINIMUM_STARTING_SAMPLES_TIME_STRETCH;
            }
          else
            {
              if (inBufferSizeIn < MINIMUM_STARTING_SAMPLES_TIME_COMPRESS)
                size = 0;
              else
                size = normalizedSize - MINIMUM_STARTING_SAMPLES_TIME_COMPRESS;

            }
          m_boolFirstTime = 0;
          return size;
        }
      else
        {
          size = normalizedSize;
        }
    }
  return size;
}

unsigned int AudioTimeScaler::GetInputBufferSize(unsigned int inBufferSizeOut)
{
  unsigned int size = 0;

  // round up to nearest multiple of 512
  unsigned int normalizedSize = (unsigned int)((double)inBufferSizeOut / m_PTS[0].dTimeScale);
  normalizedSize = ((normalizedSize/512)+1) * 512;

  if (m_boolInited == 1)
    {
      if (m_boolFirstTime)
        {
          if (this->m_PTS[0].dTimeScale > 1.0)
            size = MINIMUM_STARTING_SAMPLES_TIME_STRETCH + normalizedSize;
          else
            size = MINIMUM_STARTING_SAMPLES_TIME_COMPRESS + normalizedSize;  // should handle down to scale factor of 0.1
          m_boolFirstTime = 0;
          return size;
        }
      long overruns = GetOverrunBufferNumSamples(0);

      if (overruns >= (long)inBufferSizeOut)
        {
          size = 0;  // already have enough
        }
      else
        {
          size = normalizedSize;
        }
    }
  return size;
}

long AudioTimeScaler::Process(float** inBuf,
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


long AudioTimeScaler::ProcessChannel(int channel,
                                     float* inBuf,
                                     float* outBuf,
                                     unsigned int inNumSamplesIn,
                                     unsigned int inNumSamplesOut)
{
  int        i,j,k;
  float*      pOutBuf;
  unsigned int    numSamplesRead = 0;
  unsigned int    numSamplesWritten = 0;

  PitchTimeState* pPTS = &m_PTS[channel];


  if (m_boolInited != 1)
    return 0;

  pOutBuf = outBuf;

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

  while (1)
    {
      //  if (pAOin->bStopOp)
      //            goto finish;

      /*
       * prepare for analysis: read next samplesToRead input values
       */
      while (pPTS->inputSampleCounter < pPTS->samplesToRead)
        {
          // TLB: input buffer of float samples
          float fSample;
          double l_dInput;
          fSample = *inBuf++;
          numSamplesRead++;
          if (numSamplesRead > inNumSamplesIn)
            return numSamplesWritten;
          pPTS->inputSampleCounter++; // keep track of input count

          l_dInput = fSample;

          /* Update the running estimate of the signal variance  */
          runningVariance(&pPTS->inputPrevSumSq, &pPTS->inputPrevMean,
                          l_dInput, &pPTS->inputCount, &pPTS->inputVariance,
                          pPTS->inputHistorySamples);

          pPTS->inputCount++;

          pPTS->pDInputBuf[pPTS->nextIn++] = l_dInput;
          pPTS->lInCount++;


          //      /* check to see if done */
          //      if ((pPTS->lInCount == pPTS->samplesTotal) || (err == MF_END_OF_FILE))
          //    pPTS->samplesToRead = i;

          if (pPTS->nextIn >= pPTS->lInBufLen)
            pPTS->nextIn -= pPTS->lInBufLen;
        }
      pPTS->inputSampleCounter = 0;   // reset counter for next input batch

      //if (samplesToRead)
      //inputMagnitude = sqrt(inputMagnitude/samplesToRead);

      if (pPTS->lCurrAnalSample > 0)
        {
          /* zero fill at EOF */
          for (i = pPTS->samplesToRead; i < pPTS->analHop; i++)
            {
              pPTS->pDInputBuf[pPTS->nextIn++] = 0.;
              if (pPTS->nextIn >= pPTS->lInBufLen)
                pPTS->nextIn -= pPTS->lInBufLen;
              //                boolFlush = TRUE;   // JW - check this!!!!
            }
        }

      /*
       * analysis: The analysis subroutine computes the complex
       * output at time n of (nBands/2 + 1) of the spectral
       * channels.  It operates on input samples (n - analWinHalfLen)
       * thru (n + analWinHalfLen) and expects to find these in
       * input[(n +- analWinHalfLen) mod lInBufLen].
       * It expects pDAnalWindow to point to the center of an odd
       * symmetric window of length (2 * analWinHalfLen +1).
       * The results are returned
       * in pDAnal as succesive pairs of real and imaginary values
       * for the lowest (nBands/2 + 1) channels.
       */

      /*initialize*/
      for (i = 0; i < pPTS->nBands+2; i++)
        pPTS->pDAnal[i] = 0.;

      j = (pPTS->lCurrAnalSample - pPTS->analWinHalfLen - 1 + pPTS->lInBufLen) % pPTS->lInBufLen;
      k = (pPTS->lCurrAnalSample - pPTS->analWinHalfLen - 1 + 10 * pPTS->nBands) % pPTS->nBands;

      for (i = -pPTS->analWinHalfLen; i <= pPTS->analWinHalfLen; i++)
        {
          if (++j >= pPTS->lInBufLen)
            j -= pPTS->lInBufLen;
          if (++k >= pPTS->nBands)
            k -= pPTS->nBands;
          pPTS->pDAnal[k] += pPTS->pDAnalWindow[i] * pPTS->pDInputBuf[j];
        }

      fft_hermitian(pPTS->pDAnal, pPTS->pFftInfoAnal);

      /*
       * conversion: The real and imaginary values in pDAnal are
       * converted to magnitude and angle-difference-per-second
       * (assuming an intermediate sampling rate of dAnalRate)
       * and are returned in pDSyn.
       */
      for (i = 0; i <= pPTS->nBands/2; i++)
        {
          double dReal;
          double dImag;
          double dMag;
          double dPhase;
          double dAngleDiff;

          /* check to see if we have gone off the end of the syn buffer */
          if (i > pPTS->nBandsScaled/2)
            break;

          dReal = pPTS->pDAnal[i];
          if ((i == 0) || (i == pPTS->nBands/2))
            dImag = 0;
          else
            dImag = pPTS->pDAnal[pPTS->nBands - i];

          dMag = sqrt(dReal * dReal + dImag * dImag);

          if (dMag == 0)
            dAngleDiff = 0;
          else
            {
              /*
               * - compute phase & phase difference
               * - unwrap if phase difference too big
               */
              dPhase = atan2(dImag, dReal);
              dAngleDiff = dPhase - pPTS->pDOldInPhase[i];
              pPTS->pDOldInPhase[i] = dPhase;

              if (dAngleDiff > M_PI)
                dAngleDiff -= M_TWOPI;
              if (dAngleDiff < -M_PI)
                dAngleDiff += M_TWOPI;
            }

          /*
           * add in filter center frequency
           */
          dPhase = dAngleDiff * (pPTS->dAnalRate/M_TWOPI)
            + ((double) i * pPTS->dFundFreq);

          pPTS->pDSyn[i] = dMag;
          if (!((i==0) || (i == pPTS->nBandsScaled2/2)))
            pPTS->pDSyn[pPTS->nBandsScaled2 - i] = dPhase;
        }

      /* pad out the syn buffer if necessary */
      for (i = pPTS->nBands/2+1; i <= pPTS->nBandsScaled2/2; i++)
        {
          pPTS->pDSyn[i] = 0;
          if (!((i==0) || (i == pPTS->nBandsScaled2/2)))
            pPTS->pDSyn[pPTS->nBandsScaled2 - i] = 0;
        }

      /* increment analysis time */
      pPTS->lCurrAnalSample += pPTS->analHop;

      /*
       * reconversion: The magnitude and angle-difference-per
       * -second in pDSyn (assuming an intermediate sampling
       * rate of dSynthRate) are converted to real and imaginary
       * values and are returned in pDSyn.
       */
      for (i = 0; i <= pPTS->nBandsScaled/2; i++)
        {
          double dMag;
          double dPhase;

          dMag = pPTS->pDSyn[i];

          if ((i == 0) || (i == pPTS->nBandsScaled2/2))
            pPTS->pDOldOutPhase[i] = 0;
          else
            pPTS->pDOldOutPhase[i] += pPTS->pDSyn[pPTS->nBandsScaled2-i] -
              ((double) i * pPTS->dFundFreq);

          dPhase = pPTS->pDOldOutPhase[i] * M_TWOPI / pPTS->dSynthRate;

          pPTS->pDSyn[i] = dMag * cos(dPhase);
          if (!((i == 0) || (i == pPTS->nBandsScaled2/2)))
            pPTS->pDSyn[pPTS->nBandsScaled2-i] = dMag * sin(dPhase);
        }

      if (pPTS->dPitchScale != 1.)
        {
          for (i = 0; i < pPTS->nBandsScaled+2; i++)
            pPTS->pDSyn[i] /= pPTS->dPitchScale;
        }

      /*
       * synthesis: The synthesis subroutine uses the Weighted
       * Overlap-Add technique to reconstruct the time-domain
       * signal.  The (nBandsScaled/2 + 1) spectral channel
       * outputs at time n are inverse Fourier transformed,
       * windowed, and added into the output array.
       */
      fft_inverse_hermitian(pPTS->pDSyn, pPTS->pFftInfoSynth);

      /*
       * scale the result from nBandsScaled2 to nBandsScaled
       */
      if (pPTS->nBandsScaled2 != pPTS->nBandsScaled)
        {
          double increment = ((double) pPTS->nBandsScaled2)/((double) pPTS->nBandsScaled);
          double index     = increment;
          for (i=1; i<pPTS->nBandsScaled; i++)
            {
              long   lIndex   = (long) index;
              double frac  = index - (double) lIndex;
              double base  = pPTS->pDSyn[lIndex];
              pPTS->pDSyn[i]   = base + frac*(pPTS->pDSyn[lIndex+1]-base);
              index          += increment;
            }
        }

      /*
       * The 50 and the 500 are so that the modulo works the way we
       * want for negative values.  Adding in a multiple of the modulus
       * doesn't affect the answer, but insures that the left hand
       * side is positive.
       */
      j = (pPTS->lCurrSynthSample - pPTS->synWinHalfLen - 1 + 50 * pPTS->lOutBufLen)
        % pPTS->lOutBufLen;
      k = (pPTS->lCurrSynthSample - pPTS->synWinHalfLen - 1 + 500 * pPTS->nBandsScaled)
        % pPTS->nBandsScaled;

      /*
       * overlap-add
       */
      for (i = -pPTS->synWinHalfLen; i <= pPTS->synWinHalfLen; i++)
        {
          if (++j >= pPTS->lOutBufLen)
            j -= pPTS->lOutBufLen;
          if (++k >= pPTS->nBandsScaled)
            k -= pPTS->nBandsScaled;
          pPTS->pDOutputBuf[j] += pPTS->pDSyn[k] * pPTS->pDSynWindow[i];
        }

      /*************************** MODIFICATIONS *************/
      /* Update the running estimate of the output signal variance  */
      /* Unlike the input variance esimation, look at the entire output
         buffer before correcting samples so that the output variance
         estimate can "catch up" to the input variance estimate */
      pPTS->oldNextOut = pPTS->nextOut;
      for (i=0; i<pPTS->samplesToWriteScaled; i++)
        {
          runningVariance(&pPTS->outputPrevSumSq, &pPTS->outputPrevMean,
                          pPTS->pDOutputBuf[pPTS->nextOut], &pPTS->outputCount,
                          &pPTS->outputVariance, pPTS->outputHistorySamples);

          pPTS->outputCount++;
          pPTS->nextOut++;
          if (pPTS->nextOut >= pPTS->lOutBufLen)
            pPTS->nextOut -= pPTS->lOutBufLen;
        }
      pPTS->nextOut = pPTS->oldNextOut; /* Reset the array index to its previous value */
      /*******************************************************/

      for (i = 0; i < pPTS->samplesToWriteScaled; i++)
        {
          pPTS->lMaxOut = (long) (((double) pPTS->dTimeScale / pPTS->dPitchScale * pPTS->lInCount) + 0.5);
          if (pPTS->lOutCount <= pPTS->lMaxOut)
            {
              double dSample;
              float sample;

              dSample = pPTS->pDOutputBuf[pPTS->nextOut];
              correctSample(pPTS->inputVariance, pPTS->outputVariance, &dSample, &pPTS->correction);

              if (dSample > 1.0)
                dSample = 1.0;
              else if (dSample < -1.0)
                dSample = -1.0;

              sample = (float)dSample;
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

              pPTS->pDOutputBuf[pPTS->nextOut++] = 0.;
              if (pPTS->nextOut >= pPTS->lOutBufLen)
                pPTS->nextOut -= pPTS->lOutBufLen;
              pPTS->lOutCount++;
            }
        }

      //if (samplesToWriteScaled)
      //outputMagnitude = sqrt(outputMagnitude/samplesToWriteScaled);

      if (!pPTS->eofFlag)
        {
          if ((pPTS->lCurrAnalSample > 0) && (pPTS->samplesToRead < pPTS->analHop))
            {
              pPTS->eofFlag = 1;
              pPTS->lLastSample = pPTS->lCurrAnalSample + pPTS->analWinHalfLen
                - (pPTS->analHop - pPTS->samplesToRead);
            }
        }

      /* increment synthesis time */
      pPTS->lCurrSynthSample += pPTS->synthHopScaled;

      if ((pPTS->lCurrAnalSample + pPTS->analWinHalfLen) <= pPTS->lLastSample)
        pPTS->samplesToRead = pPTS->analHop;
      else
        {
          if ((pPTS->lCurrAnalSample + pPTS->analWinHalfLen - pPTS->analHop) <= pPTS->lLastSample)
            {
              pPTS->samplesToRead = pPTS->lLastSample
                - (pPTS->lCurrAnalSample + pPTS->analWinHalfLen - pPTS->analHop);
            }
          else
            pPTS->samplesToRead = 0;
        }

      if (pPTS->lCurrSynthSample > (pPTS->synWinHalfLen + pPTS->synthHop))
        pPTS->samplesToWrite = pPTS->synthHop;
      else
        {
          if (pPTS->lCurrSynthSample > pPTS->synWinHalfLen)
            pPTS->samplesToWrite = pPTS->lCurrSynthSample - pPTS->synWinHalfLen;
          else
            {
              pPTS->samplesToWrite = 0;
              for (i=pPTS->lCurrSynthSample + pPTS->synWinHalfLen; i<pPTS->lOutBufLen;i++)
                {
                  if (i > 0)
                    pPTS->pDOutputBuf[i] = 0.;
                }
            }
        }

      pPTS->samplesToWriteScaled = (int) (((double) pPTS->samplesToWrite / pPTS->dPitchScale));

#if 0
      if (boolTrace)
        {
          char str[260];
          sprintf(str, "Input: %d  Output: %d", pPTS->lInCount, pPTS->lOutCount);
          MessageBox(NULL, str, "", MB_OK);
        }
#endif
    }

  pPTS->lMaxOut = (long) (((double) pPTS->dTimeScale / pPTS->dPitchScale * pPTS->lInCount) + 0.5);
  while (pPTS->lOutCount <= pPTS->lMaxOut)
    {
      float sample;
      double dSample;

      dSample = pPTS->pDOutputBuf[pPTS->nextOut];

      correctSample(pPTS->inputVariance, pPTS->outputVariance, &dSample, &pPTS->correction);

      sample = (float)dSample;
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

      pPTS->lOutCount++;
      if (pPTS->nextOut >= pPTS->lOutBufLen)
        pPTS->nextOut -= pPTS->lOutBufLen;
    }

  return numSamplesWritten;

}

double AudioTimeScaler::GetTimeScaleFactor()
{
  if (m_boolInited != 1)
    return 0.0;
  return m_PTS[0].dTimeScale;
}



void AudioTimeScaler::ClearOverrunBuffers()
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

void AudioTimeScaler::CreateOverrunBuffers(long bufSize, int numChannels)
{
  DestroyOverrunBuffers();
  m_sizeOverrunBuffer = bufSize;
  for (int i=0; i<numChannels; i++)
    {
      m_pFOverrunBuffer[i] = (float*)Calloc((unsigned)m_sizeOverrunBuffer, (unsigned)sizeof(float));
      m_overrunPosition[i] = 0;
    }

}

long AudioTimeScaler::GetOverrunBufferNumSamples(int channel)
{
  if (m_pFOverrunBuffer[channel] != NULL)
    {
      return m_overrunPosition[channel];
    }
  else
    return 0;
}



void AudioTimeScaler::DestroyOverrunBuffers()
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

void AudioTimeScaler::WriteToOverrunBuffer(int channel, float fValue)
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

void AudioTimeScaler::EmptyOverrunBuffer(int channel, int count, float* pFOutBuffer)
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




// Private Helper functions:
///////////////////////////////////////////////////////////////////////////

/* runningMean: Given a previous estimate of the sample mean, previous, calculate
 * a new estimate of the sample mean given one additional sample from the population, new.
 * Count is the total number of samples used for the new estimate, e.g., one more than
 * the number of samples used for the previous estimate.
 *
 */
void AudioTimeScaler::runningMean(double previousData, double newData, double count, double* mean)
{
  if (count < 2)
    count = 2;

  *mean = ((count-1)/count)*previousData + (1/count)*newData;
}

/* correctSample: given the current estimates of the variances of the input and output buffers,
 * scale 'sample' by a scale factor designed to equalize the variances of the input and output
 * audio of the time-scaling algorithm.  A two point running mean (low-pass filter) is applied to the
 * scaleFactor to eliminate the possibility of sudden amplitude jumps (which are very unlikely).
 *
 */
void AudioTimeScaler::correctSample(double inputVariance, double outputVariance, double* sample, double* scaleFactor)
{
  double scaleFactorOld = *scaleFactor;

  if (inputVariance <= 0 || inputVariance <= 0)
    return;

  *scaleFactor = sqrt(inputVariance / outputVariance);

  if (*scaleFactor > 5.0 || *scaleFactor < 0.2)
    return;

  /* Two Point Running Average of the scaleFactor to prevent big jumps */
  runningMean(scaleFactorOld, *scaleFactor, 2, scaleFactor);

  *sample *= *scaleFactor;
}


/* runningVariance: Similar to runningMean... given a new sample,
 * re-estimate the population variance.  The parameter historySamples
 * limits how far backwards in time the estimator looks.  In the case
 * when historySamples is equal to the total number of samples, newVariance
 * will converge to the sample variance of all the samples.  Using the
 * history accounts for the (likely) possibility that the variance of
 * the input time-series changes with time.
 *
 * Note: the expression for newVariance assumes that the updated mean
 * is in fact the true mean of all the data, rather than just the
 * mean of the current historySamples of data.  This is probably not
 * the best thing to do, but for audio, it hardly matters because
 * the means are always near 0.
 *
 */
void AudioTimeScaler::runningVariance(double* prevSquareSum, double* previousMean,
                                      double sample, double* count, double* newVariance,
                                      double historySamples)
{
  double count_ = *count-1;
  double sample2 = sample*sample;
  double newMean;
  double newSquareSum;

  if (*count < 2)
    *count = 2;

  if ((*count)>historySamples)
    *count = (historySamples);

  runningMean(*previousMean, sample, *count, &newMean);

  newSquareSum = (count_ / *count)*(*prevSquareSum) + (1/(*count))*sample2;
  *newVariance = (*prevSquareSum) + (1/count_)*sample2 - 2*newMean*((*previousMean)+(1/count_)*sample) +
    (*count/count_)*newMean*newMean;
  *previousMean = newMean;
  *prevSquareSum = newSquareSum;
}


void AudioTimeScaler::Hann(double* pDWin, int winLen)
{
  int i;

  pDWin[0] = 1.;

  for (i=1; i<=winLen; i++)
    {
      double temp = (double)cos(M_PI*i/(2*winLen));
      pDWin[i] = pDWin[-i] = temp*temp;
    }
}

MFError AudioTimeScaler::AdjustParameters(
                                          int* pAnalHop, int* pSynthHop,
                                          int* pNBands, int* pAnalWinLen, int* pSynWinLen, int filterOverlap,
                                          double* pDPitchScale, double* pDTimeScale) {
  // filterOverlap must be between 0 and 3.
  // pDTimeScale *= *pDPitchScale are positive.

  /* make sure pNBands is even */
  if ((*pNBands % 2) != 0)
    *pNBands += 1;

  if (filterOverlap == 0)
    *pAnalWinLen = 4*(*pNBands) - 1;
  else if (filterOverlap == 1)
    *pAnalWinLen = 2*(*pNBands) - 1;
  else if (filterOverlap == 2)
    *pAnalWinLen = (*pNBands) - 1;
  else if (filterOverlap == 3)
    *pAnalWinLen = (*pNBands)/2 - 1;

  if (((*pAnalWinLen)%2) == 0)
    *pAnalWinLen -= 1;         /* window length must be odd number */

  /*
   * this is somewhat of a hack.
   * in the pitch scaling situation, it is a little hard to know what
   * the user means by setting the synWinLen and analWinLen to different
   * values.
   */
  if (*pSynWinLen == 0)
    *pSynWinLen = *pAnalWinLen;
  else if (((*pSynWinLen)%2) == 0)
    *pSynWinLen -= 1;         /* window length must be odd number */

  /* pitch change is time change plus resamp */
  if (*pDPitchScale != 1.)
    *pDTimeScale *= *pDPitchScale;

  if (*pDTimeScale <= 0.)
    return "bad time scale";

  /*
   * NOTE: divisor of 8 is required to be able to insure that we
   *   can unwrap phase in time.  The 0.5 is for rounding.
   */
  if (*pDTimeScale > 1)
    (*pAnalHop) = (int) (((double) ((*pAnalWinLen)+1) / (8.**pDTimeScale)) + 0.5);
  else
    (*pAnalHop) = (int) (((double) ((*pAnalWinLen)+1) / 8.) + 0.5);

  if ((*pAnalHop) == 0)
    return "Empty anal hop";

  (*pSynthHop) = (int) (((double) *pDTimeScale * (*pAnalHop)) + 0.5);

  if ((*pSynthHop) == 0)
    return "Empty pSynthHop";

  *pDTimeScale = ((double) (*pSynthHop) / (*pAnalHop));

  return NULL;
}

/*
 * this allocates a floating-point buffer of size size and sets it to
 * zero.  if the buffer has already been allocated, it is freed first.
 */
void AudioTimeScaler::AllocateAndClear(double** pPDArray, long lSize) {
  if (*pPDArray != 0)
    Free((char*) *pPDArray);

  *pPDArray = (double*) Calloc((unsigned)lSize, (unsigned)sizeof(double));
}

/*
 * set up analysis window: The window is assumed to be symmetric
 *    with an odd number of total points given by analWinLen. After
 *    the initial memory allocation, pDAnalWindow always points
 *    to the midpoint of the window, and analWinHalfLen is half
 *    of the true window length (rounded down). Any low pass
 *    window will work; a Hann window is generally fine.
 *    If the window duration is
 *    longer than the transform (analWinLen > nBands), then the window is
 *    multiplied by a sin(x)/x function to meet the condition:
 *    pDAnalWindow[Ni] = 0 for i != 0.  In either case, the
 *    window is normalized so that the spectral amplitude
 *    estimates are properly scaled.  The maximum allowable
 *    window duration is lInBufLen/2.
 */
void AudioTimeScaler::InitAnalWindow(
                                     double** pPDAnalWindow, double** pPDAnalWindowAlloc,
                                     int analWinLen, int nBands, double* pDSum, int* pAnalWinHalfLen) {
  int     i;
  AllocateAndClear(pPDAnalWindow, analWinLen);
  *pPDAnalWindowAlloc = *pPDAnalWindow;
  *pPDAnalWindow += (*pAnalWinHalfLen = (analWinLen-1)/2);

  Hann(*pPDAnalWindow, *pAnalWinHalfLen);

  if (analWinLen > nBands)
    {
      for (i = 1; i <= *pAnalWinHalfLen; i++)
        {
          (*pPDAnalWindow)[i] = (*pPDAnalWindow)[-i] *= nBands
            * (double)sin((double) M_PI*i/nBands) / ((double)M_PI*i);
        }
    }

  *pDSum = (*pPDAnalWindow)[0];
  for (i = 1; i <= *pAnalWinHalfLen; i++)
    *pDSum += (*pPDAnalWindow)[-i] + (*pPDAnalWindow)[i];

  *pDSum = 2.f / *pDSum;  /*factor of 2 comes in later in trig identity*/

  (*pPDAnalWindow)[0] *= *pDSum;
  for (i = 1; i <= *pAnalWinHalfLen; i++)
    (*pPDAnalWindow)[i] = (*pPDAnalWindow)[-i] *= *pDSum;
}

/*
 * set up synthesis window:  The synthesis window can be
 * viewed as an interpolating filter converting from
 * sample rate dSampleRate/synthHopScaled to dSampleRate.  For the moment,
 * a Hann window multiplied by a sin(M_PI*i/synthHopScaled)
 * /(M_PI*i/synthHopScaled) is being used.
 * The other considerations are the same as for the
 * analysis window above.
 */
void AudioTimeScaler::InitSynWindow(
                                    double** pPDSynWindow, double** pPDSynWindowAlloc,
                                    int synWinLen, int synthHopScaled, double dSum, int* pSynWinHalfLen) {
  int     i;

  AllocateAndClear(pPDSynWindow, synWinLen);

  *pPDSynWindowAlloc = *pPDSynWindow;
  *pPDSynWindow += (*pSynWinHalfLen = (synWinLen-1)/2);

  Hann(*pPDSynWindow, *pSynWinHalfLen);

  for (i = 1; i <= *pSynWinHalfLen; i++)
    {
      (*pPDSynWindow)[i] = (*pPDSynWindow)[-i]
        *= synthHopScaled*(double)sin((double) M_PI*i/synthHopScaled) / ((double)M_PI*i);
    }

  dSum = 1.0f / dSum;

  (*pPDSynWindow)[0] *= dSum;
  for (i = 1; i <= *pSynWinHalfLen; i++)
    (*pPDSynWindow)[i] = (*pPDSynWindow)[-i] *= dSum;
}

void AudioTimeScaler::InitIOBuffers(double** pPDInputBuf, long lInBufLen,
                                    double** pPDOutputBuf, long lOutBufLen)
{
  /*
   * set up input buffer:  nextIn is always the index of the next empty
   * word in the input buffer (i.e., the sample following
   * sample number (n + analWinHalfLen)).  If the buffer is full,
   * then nextIn jumps back to the beginning, and the old
   * values are written over.
   */
  AllocateAndClear(pPDInputBuf, lInBufLen);

  /*
   * set up output buffer:  nextOut is the index of the next word
   * to be written out.  The shift is simulated by writing the
   * output value and then setting that word of the buffer to
   * zero.  When nextOut reaches the end of the buffer, it
   * jumps back to the beginning.
   */
  AllocateAndClear(pPDOutputBuf, lOutBufLen);
}

void AudioTimeScaler::InitBuffers(double** pPD, double** pPDPhase,
                                  FFT_INFO** pPFftInfo, int nBands)
{
  AllocateAndClear(pPD, nBands+2);
  AllocateAndClear(pPDPhase, nBands/2+1);
  *pPFftInfo = fft_initialize(nBands);
}


