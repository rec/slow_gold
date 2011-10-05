#ifndef __AUDIO_TIME_SCALER_H__
#define __AUDIO_TIME_SCALER_H__

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
 * File: AudioTimeScaler.h
 */

/* These are default values for the time scaling algorithm */
static const int MF_PITCHTIME_NBANDS = 2048;
static const int DEFAULT_FILTER_OVERLAP = 1;

/* Error codes -- may have to be removed */
static const int UNITIALIZED_PT_STATE_ERR    = 1;
//static const int OUT_OF_MEMORY_ERR      = 2;

static const int MAX_CHANNELS = 10;
static const float MF_ESTIMATOR_HISTORY = 7.0f; /* seconds */

/* REMIND: remove this restriction */
static const long MAX_SAMPLES = 1000000000L;

#include "hfft.h"

typedef const char* MFError;

/*
 * NOTE WELL: See bottom of this file
 * for C API.
 */

typedef struct PitchTimeState
{
  double    dSampleRate;  /* input audio object sample rate */
  double*   pDInputBuf;  /* pointer to start of input buffer */
  double*   pDOutputBuf;  /* pointer to start of output buffer */
  double*   pDAnal;  /* pointer to start of analysis buffer */
  double*   pDSyn;  /* pointer to start of synthesis buffer */
  double*   pDAnalWindowAlloc;
  double*   pDSynWindowAlloc;
  double*   pDAnalWindow;  /* pointer to center of analysis window */
  double*   pDSynWindow;  /* pointer to center of synthesis window */
  double*   pDOldInPhase;  /* pointer to start of input phase buffer */
  double*   pDOldOutPhase;/* pointer to start of output phase buffer */
  FFT_INFO* pFftInfoAnal;  /* FFT_INFO structure for analysis */
  FFT_INFO* pFftInfoSynth;/* FFT_INFO structure for synthesis */

  int       analHop;    /* analysis hop size */
  int       synthHop;    /* synthesis hop size */
  int       analWinLen;  /* length of pDAnalWindow impulse response */
  int       synWinLen;  /* length of pDSynWindow impulse response */
  int       analWinHalfLen;  /* half-length of analysis window */
  int       synWinHalfLen;  /* half-length of synthesis window */
  int       nextIn;    /* index of next empty word in input */
  int       nextOut;    /* index of next empty word in output */
  int       oldNextOut;       /* MODIFICATION: used in second MODIFICATION */

  long      lInCount;          /* number of input samples */
  long      lOutCount;  /* number of samples written to output */
  long      lInBufLen;  /* length of input buffer */
  long      lOutBufLen;  /* length of output buffer */
  long      lLastSample;   /* last sample to be processed */
  long      lCurrAnalSample;  /* current input (analysis) sample */
  long      lCurrSynthSample;  /* current output (synthesis) sample */
  long      lMaxOut;          /* last output (synthesis) sample */

  double    dSum;    /* used in window normalization */
  double    dAnalRate;  /* decimated sampling rate */
  double    dSynthRate;  /* pre-interpolated sampling rate */
  double    dFundFreq;  /* fundamental frequency of analysis */

  int       samplesTotal;  /* total number of samples in the input */
  int       samplesToRead;  /* inputs to read (samplesToRead<=analHop) */
  int       samplesToWrite;  /* outputs to write (samplesToWrite<=synthHop)*/
  int       nBandsScaled;  /* synthesis nBandsScaled=nBands/dPitchScale */
  int       nBandsScaled2;  /* power of 2 above nBandsScaled */
  int       synthHopScaled;  /* synthHop/dPitchScale */
  int       samplesToWriteScaled;  /* samplesToWrite/dPitchScale */

  int       eofFlag;    /* end-of-input flag */

  int        channelsIn;  /* TLB: tested with mono only */
  int        sampleWidthInBytes;   /* TLB added */

  double inputPrevSumSq;
  double outputPrevSumSq;
  double inputPrevMean;
  double outputPrevMean;
  double inputVariance;
  double outputVariance;
  double correction;
  double inputCount;
  double outputCount;
  long inputHistorySamples;
  long outputHistorySamples;

  double dPitchScale;
  double dTimeScale;
  int nBands;
  int filterOverlap;

  int inputSampleCounter;

} PitchTimeState;


class AudioTimeScaler
{
 public:
  AudioTimeScaler();
  virtual ~AudioTimeScaler();

  // Returns NULL on success or a character error code.
  MFError Init(double dTimeScale,
               double dSampleRate,
               int numChannels,
               double dPitchScale = 1.0,
               int nBands = MF_PITCHTIME_NBANDS,
               int filterOverlap = DEFAULT_FILTER_OVERLAP);

  void Reset();

  unsigned int GetOutputBufferSize(unsigned int inBufferSizeIn);
  unsigned int GetInputBufferSize(unsigned int inBufferSizeOut);

  // Returns the number of samples WRITTEN.
  virtual long Process(float** inBuf,
                       float** outBuf,
                       unsigned int inNumSamplesIn,
                       unsigned int inNumSamplesOut);

  double GetTimeScaleFactor();


 protected:

  PitchTimeState m_PTS[MAX_CHANNELS];

  int     m_numChannels;

  int     m_boolInited;
  int     m_boolFirstTime;

  float*  m_pFOverrunBuffer[MAX_CHANNELS];
  long    m_overrunPosition[MAX_CHANNELS];
  long    m_sizeOverrunBuffer;

  // process one channel of data.
  long ProcessChannel(int channel,
                      float* inBuf,
                      float* outBuf,
                      unsigned int inNumSamplesIn,
                      unsigned int inNumSamplesOut);


  // overrun buffer handlers
  void ClearOverrunBuffers();

  void CreateOverrunBuffers(long bufSize, int numChannels);

  void DestroyOverrunBuffers();

  void WriteToOverrunBuffer(int channel, float fValue);

  void EmptyOverrunBuffer(int channel, int count, float* pFBuffer);

  long GetOverrunBufferNumSamples(int channel);

 private:

  void runningMean(double previousData, double newData, double count, double* mean);

  void correctSample(double inputVariance, double outputVariance, double* sample, double* scaleFactor) ;

  void runningVariance(double* prevSquareSum, double* previousMean,
                       double sample, double* count, double* newVariance,
                       double historySamples);

  void Hann(double* pDWin, int winLen);

  MFError AdjustParameters(int* pAnalHop, int* pSynthHop,
                           int* pNBands, int* pAnalWinLen, int* pSynWinLen, int filterOverlap,
                           double* pDPitchScale, double* pDTimeScale);

  void AllocateAndClear(double** pPDArray, long lSize);

  void InitAnalWindow(double** pPDAnalWindow, double** pPDAnalWindowAlloc,
                      int analWinLen, int nBands, double* pDSum, int* pAnalWinHalfLen);

  void InitSynWindow(double** pPDSynWindow, double** pPDSynWindowAlloc,
                     int synWinLen, int synthHopScaled, double dSum, int* pSynWinHalfLen);

  void InitIOBuffers(double** pPDInputBuf, long lInBufLen,
                     double** pPDOutputBuf, long lOutBufLen);

  void InitBuffers(double** pPD, double** pPDPhase,
                   FFT_INFO** pPFftInfo, int nBands);

};

#endif  // __AUDIO_TIME_SCALER_H__

