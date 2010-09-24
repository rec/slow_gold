#include "AudioTimeScaler.h"

#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "rec/base/arraysize.h"

#include "mfglobals.h"
#include "JuceLibraryCode/JuceHeader.h"

char*	StrFileIn = 0;
char*	StrFileOut = 0;
double	TimeScaleFactor	= 2.0;
double	PitchShiftFactor= 1.0;
short	ScaleChannelNum	= 0;
float	SampleRateIn	= (float) 44100.0;

void Arguments (int argc, char* argv[]);
int TestTimeScaler(FILE* fIn, FILE* fOut);

#ifndef BOOL

#define BOOL int

#endif

#ifndef WINDOZE

const int _MAX_PATH = 1024;
#define _stat stat
#define _fstat fstat
#define _fileno fileno

#endif

#define SAMPLES_PER_CHUNK   128	    /* must be multiple of 128 */

using std::vector;

int TestTimeScaler(FILE* fIn, FILE* fOut, double timeScaleFactor) {
  AudioTimeScaler timeScaler;

  // assume fIn is a raw (headerless) soundfile containing
  // stereo, 16-bit, 44.1 kHz samples.

  long	nTotalSamplesRead = 0;
  long	nTotalSamplesWritten = 0;

  // create fixed output buffer size, ask for this many output samples
  // for each loop

  int fno = _fileno(fIn);
  struct _stat statBuf;
  if (_fstat(fno, &statBuf) != 0)
    return -1;

  timeScaler.Init(timeScaleFactor, 44100, 1, 1.0, 1024, 1);
  while (true) {
    vector<float> afSamplesOut(SAMPLES_PER_CHUNK, 0);

    // ask how many input samples are needed for SAMPLES_PER_CHUNK output samples
    long nSamplesToRead = timeScaler.GetInputBufferSize(SAMPLES_PER_CHUNK);
    // assumes test input file contains raw CD-QUALITY samples
    // (i.e., interleaved stereo, 16-bit, 44.1 kHz)

    // create a buffer of shorts (16 bits)
    vector<short> asSamplesIn(nSamplesToRead);

    // Time scaler Process function requires mono, 32-bit! samples,
    // so we have to do some conversion before passing input
    // to it.
    //
    // [1] create a buffer of floats (32 bits) to hold the converted input
    long nSamplesToProcess = nSamplesToRead / 2; /* must pass in mono samples */
    vector<float> afSamplesIn(nSamplesToProcess);

    // [2] read CD-FORMAT/QUALITY input samples from test file
    long nSamplesRead = fread(&asSamplesIn[0], sizeof(short), nSamplesToRead, fIn);

    if (nSamplesRead != nSamplesToRead)
      break;  // out of samples

    // [3] convert stereo shorts to mono 32-bit floats
    // based on ScaleChannelNum input arg
    //
    // ScaleChannelNum definition:
    // 0: All channels of the input file are averaged together
    //	and the result is scaled, creating mono output
    // 1 or 2: Scale only this channel of the input file and
    //	create mono output.
    int j = 0;
    for (int i=0; i<nSamplesRead; i+=2)
      {
        short leftChan = asSamplesIn[i];
        short rightChan = asSamplesIn[i+1];

        if (ScaleChannelNum == 0)
          {
            afSamplesIn[j++] = (((float) leftChan / ((long)(0x7fff)))
                                + ((float) rightChan / ((long)(0x7fff)))) / (float) 2.0;
          }
        else if (ScaleChannelNum == 1)
          afSamplesIn[j++] = ((float) leftChan / ((long)(0x7fff)));
        else if (ScaleChannelNum == 2)
          afSamplesIn[j++] = ((float) rightChan / ((long)(0x7fff)));
        else
          return -1;  /* bogus ScaleChannelNum spec */
      }

    nTotalSamplesRead += nSamplesRead;
    // [4] now send the samples into ats for processing
    float* sout[] = {&afSamplesOut.front()};
    float* sin[] = {&afSamplesIn.front()};
    long numSamplesOut = timeScaler.Process(sin, sout,
                                            nSamplesToProcess, SAMPLES_PER_CHUNK);

    // [5] convert output samples to 16-bit

    vector<short> asSamplesOut(numSamplesOut);

    for (int i = 0; i<numSamplesOut; i++)
      asSamplesOut[i] = ((long) (afSamplesOut[i] * ((float) (0x7fff))));

    // [6] write processed samples to output file
    //numSamplesWritten = fwrite(afSamplesOut, sizeof(float),
    unsigned int numSamplesWritten = fwrite(&asSamplesOut[0], sizeof(short),
                                            numSamplesOut, fOut);

    nTotalSamplesWritten += numSamplesWritten;
  }
  return true;
}


static void BadArgument()
{
  fprintf(stderr, "audioprocess [flags] \nValid arguments:\n");
  fprintf(stderr, "\t-i inputFile\n");
  fprintf(stderr, "\t-o outputFile\n");
  fprintf(stderr, "\t-f(requencyShift) factor [default 1.0]\n");
  fprintf(stderr, "\t-t(imeScale) factor\n");
  fprintf(stderr, "\t-c(hannel number to scale) [0=mix chans (default); 1=left only; 2=right only]\n");
  exit(1);
}

void Arguments(int argc, char* argv[])
{
  void BadArgument();
  int  i = 1;
  while (i < argc)
    {
      if (*(argv[i]) == '-')
        {
          switch (*(argv[i] + 1))
            {
           case 'i':
          StrFileIn = argv[++i];
          break;
           case 'o':
          StrFileOut = argv[++i];
          break;
           case 'c':
          sscanf(argv[++i], "%hd", &ScaleChannelNum);
          if (ScaleChannelNum > 2 || ScaleChannelNum < 0)
            BadArgument();
          break;
           case 's':
          sscanf(argv[++i], "%f", &SampleRateIn);
          break;
           case 't':
          sscanf(argv[++i], "%lf", &TimeScaleFactor);
          break;
           case 'f':
          sscanf(argv[++i], "%lf", &PitchShiftFactor);
          break;
           default:
          BadArgument();
          break;
            }
        } else
        BadArgument();
      i++;
    }
}


int main(int argc, char* argv[])
{

  const ScopedJuceInitialiser_NonGUI juceSystemInitialiser;
  FILE* fIn = NULL;
  FILE* fOut = NULL;

  static char* my_argv[] = {"./console", "-i", "/Users/tom/bbb.raw",
                          "-o", "/Users/tom/bbb3.raw", "-t", "1.0"};
  if (argc == 1)
    Arguments(arraysize(my_argv), my_argv);
  else
    Arguments(argc, argv);

  // must enter something for input and output files
  if (!StrFileIn)
    return -1;

  if (!StrFileOut)
    return -1;

  if (strcmp((const char*) StrFileIn, (const char*) "") == 0)
    return -1;
  else
    {
      if ((fIn = fopen(StrFileIn, "rb")) == NULL)
        return -1;
    }
  if (strcmp((const char*) StrFileOut, (const char*) "") == 0)
    return -1;
  else
    {
      if ((fOut = fopen(StrFileOut, "wb")) == NULL)
        return -1;
    }

  return TestTimeScaler(fIn, fOut, TimeScaleFactor);
}

