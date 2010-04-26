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
 * File: AudioResampler.h
 */

#ifndef MF_AUDIORESAMPLER_H
#define MF_AUDIORESAMPLER_H

#include "mfGlobals.h"
#include "mfMacros.h"

#define MAX_UNSIGNED_LONG 4294967295
#define IBUF 1024

#define PI 3.141592653589793

/* sample value max and min for clippin */
#define SMAX 2147483647
#define SMIN -2147483647

#define MF_SAMPLE_CLIPPED	101

#define RW_BUFFER_SIZE	1024

/* TLB: Error codes for non-AO bufferized version */
#define UNINITIALIZED_RESAMPLE_STATE_ERR	    (1)
#define OUT_OF_MEMORY_ERR			    (2)
#define UNEXPECTED_INITIALIZED_RESAMPLE_STATE_ERR   (3)
#define END_OF_FILE_ERR				    (4)
#define	SAMPLE_CLIPPED_WARNING			    (5)

#define DEFAULT_RESAMPLE_QUALITY	1.0
#define DEFAULT_RESAMPLE_GAIN		1.0
#define DEFAULT_RESAMPLE_CUT_OFF	1.0

#define MAX_CHANNELS 10

typedef struct
{
    long samples[RW_BUFFER_SIZE];
    long index;
    long nSamples;
} RWBuffer;

typedef struct
{
    float   fRateIn;
    float   fRateOut;
    short   nChannelsIn;

    float*  pFInput1;  /* pointer to start of input buffer */
    float*  pFInput2;  /* pointer to start of input buffer */
    float*  pFWindow;  /* pointer to center of analysis window */

    float   sample;     /* sample read from input audio object */
    int     nextIn1;    /* index of next empty word in pFInput1 */
    int     nextIn2;    /* index of next empty word in pFInput2 */
    int     winLength;  /* length of pFWindow impulse response */
    int     N;    /* length of sinc period */
    int     L;    /* internal sample rate is L*fRateIn */
    int     m;          /* current input sample in buffer */
    int     o;          /* current input at L*fRateIn mod L */
    int     delta;      /* increment */
    int     winSizeL;   /* half-length of pFWindow at L*fRateIn */
    int     winSize;    /* half-length of pFWindow at fRateIn */
    int     jMin;       /* initial offset in pFWindow */
    int     mMax;       /* maximum valid m */
    int     nChunkSize;      /* IBUF / 8 = 128 samples */

    unsigned long   n;          /* current input frame */
    unsigned long   nFrames;    /* number of input frames */
    unsigned long   nFramesRead;/* number of input frames read */
    long    nMin;   /* first sample */

    /*char  ch;*/       /* needed for getopt commandline interpreter */
    float   fBeta;/* parameter for Kaiser window */
    float   fSum;       /* scale factor for normalizing windows */
    float   fDelta;     /* float delta */
    float   fDeltaInt;  /* integer part of delta */

    float   fInterpVal; /* interpolated window */
    float   fO;         /* float o */
    float   fOFrac;     /* fractional o */
    float   fL;  /* float L */
    float   fSum1;      /* scale factor for normalizing windows (chan 1) */
    float   fSum2;      /* scale factor for normalizing windows (chan 2) */


    bool isStream;

    RWBuffer bufWrite;
    RWBuffer bufRead;
/* TLB ADDED FOLLOWING */
    float   fQuality;
    float   fCutoffFreq;
    float   fGain;
    bool boolFirstCall;
    bool boolStopping;
    unsigned long   clipCount;
} ResampleStruct;


class AudioResampler
{
public:
    AudioResampler();
    ~AudioResampler();

    unsigned int Init(  double inRate,
		double outRate,
		unsigned int inNumChannels,
		float fQuality  = DEFAULT_RESAMPLE_QUALITY,
		float fCutoffFreq = DEFAULT_RESAMPLE_CUT_OFF,
		float gain = DEFAULT_RESAMPLE_GAIN);

    void Reset();

    unsigned int GetOutputBufferSize(unsigned int inBufferSizeIn);
    unsigned int GetInputBufferSize(unsigned int inBufferSizeOut);

    long Process(float** inBuf,
                float** outBuf,
                unsigned int inNumSamplesIn,
                unsigned int inNumSamplesOut);


protected:

    long ProcessChannel(int channel,
			float* inBuf,
			float* outBuf,
			unsigned int inNumSamplesIn,
			unsigned int inNumSamplesOut);

    ResampleStruct m_RS[MAX_CHANNELS];

    int     m_numChannels;

    int     m_boolInited;
    int	    m_boolFirstTime;
    long    m_lOverlapFrames;

    float*  m_pFOverrunBuffer[MAX_CHANNELS];
    long    m_overrunPosition[MAX_CHANNELS];
    long    m_sizeOverrunBuffer;
    // overrun buffer handlers
    void ClearOverrunBuffers();

    void CreateOverrunBuffers(long bufSize, int numChannels);

    void DestroyOverrunBuffers();

    void WriteToOverrunBuffer(int channel, float fValue);

    void EmptyOverrunBuffer(int channel, int count, float* pFBuffer);

    long GetOverrunBufferNumSamples(int channel);


private:

    int flushSamplesNonAO(  float* outBuf,
			    RWBuffer* bufWrite,
			    unsigned int numSamplesOutMax,
			    unsigned int* pNumSamplesWritten);


    int ReadSampleNonAO(    float* pSample,
			    float* pInBuf,
			    unsigned int inNumSamplesTotal,
			    unsigned int* pNumSamplesRead,
			    unsigned int* pNumSamplesReadTotal,
			    bool stopping,
			    bool isStream,
			    RWBuffer* bufRead);

    void kaiser(int *filterLen,
		float window[],
                int *filterHalfLen,
		int *isFLenOdd,
                float *kaiserBeta);

    float ino(float x);



};

#endif
