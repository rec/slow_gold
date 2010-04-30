#include <getopt.h>
#include <inttypes.h>
#include <stdlib.h>

#include <string>

#include "juce_amalgamated.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/base/scoped_ptr.h"

using std::string;
using rec::audio::timescaler::Description;

class PitchTimeShifter {
 public:
  PitchTimeShifter()
      : in_("~/aaa.wav"),
        out_("~/aaa.out.wav"),
        sampleRate_(44100),
        timeScale_(1.0),
        pitchScale_(1.0),
        chunkSize_(512) {
  }

  static long longValue() {
    return strtol(optarg, (char **)NULL, 10);
  }

  static float floatValue() {
    return strtof(optarg, (char **)NULL);
  }

  bool getOpt(int argc, char** argv) {
    while (true) {
      char ch = getopt_long(argc, argv, shortOpts_, longOpts_, NULL);
      switch (ch) {
       case 'c': chunkSize_ = (int) longValue(); break;
       case 'h': usage(); return false;
       case 'i': in_ = string(optarg);           break;
       case 'o': out_ = string(optarg);          break;
       case 'p': pitchScale_ = floatValue();     break;
       case 'r': sampleRate_ = floatValue();     break;
       case 't': timeScale_ = floatValue();      break;
       default:
        if (ch == -1)
          return true;
        usage();
        return false;
      }
    }
    return true;
  }

  void usage() {
    std::cout << "Usage: pitch_shift --pitch_shift=1.0 --in=file.wav"
              << " --out=outfile.wav --time_scale=1.0 --chunk_size=512"
              << std::endl;
  }

  int shiftPitchAndTime() {
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    File input(in_.c_str());

    scoped_ptr<AudioFormatReader> reader(formatManager.createReaderFor(input));
    if (!reader) {
      std::cerr << "No file for " << in_ << std::endl;
      return -1;
    }

    int numChannels = reader->numChannels;
    int lengthInSamples = reader->lengthInSamples;
    int bitsPerSample = reader->bitsPerSample;
    int sampleRate = reader->sampleRate;

    std::cout << "Reading " << in_ << std::endl
              << "  sampleRate: " << sampleRate << std::endl
              << "  bitsPerSample: " << bitsPerSample << std::endl
              << "  lengthInSamples: " << lengthInSamples << std::endl
              << "  numChannels: " << numChannels << std::endl
              << "  usesFloatingPointData: " << reader->usesFloatingPointData
              << std::endl << std::endl;

    std::cout << "shifting: " << std::endl
              << "  chunkSize: " << chunkSize_ << std::endl
              << "  pitchScale: " << pitchScale_ << std::endl
              << "  sampleRate: " << sampleRate_ << std::endl
              << "  timeScale: " << timeScale_ << std::endl;

    AudioSampleBuffer outBuffer(numChannels, 2 * lengthInSamples);
    AudioSampleBuffer inBuffer(numChannels, lengthInSamples + chunkSize_);
    inBuffer.readFromAudioReader(reader.get(), 0, lengthInSamples, 0,
                                 true, true);

    for (int i = 0; i < chunkSize_; ++i)
      for (int c = 0; c < numChannels; ++c)
        *inBuffer.getSampleData(c, i + lengthInSamples) = 0.0;

    int samplesRead[numChannels];
    for (int c = 0; c < numChannels; ++c)
      samplesRead[c] = 0;

    for (int c = 0; c < numChannels; ++c) {
      AudioTimeScaler scaler;
      Description desc = Description::Default();
      desc.timeScale = timeScale_;
      desc.pitchScale = pitchScale_;
      desc.sampleRate = sampleRate_;
      for (long in = 0, out = 0; in < lengthInSamples; ) {
        int nSamplesToRead = scaler.GetInputBufferSize(chunkSize_) / 2;
        float *inFloat[] = {inBuffer.getSampleData(c, in)};
        float *outFloat[] = {outBuffer.getSampleData(c, out)};
        int read = scaler.Process(inFloat, outFloat,
                                  nSamplesToRead, chunkSize_);
        out += read;
        samplesRead[c] += read;
        in += nSamplesToRead;
      }
    }

    File output(out_.c_str());
    output.deleteFile();
    OutputStream* outStream = output.createOutputStream();
    if (!outStream) {
      std::cerr << "No output file " << out_ << std::endl;
      return -1;
    }

    WavAudioFormat wavFormat;
    scoped_ptr<AudioFormatWriter> writer(
        wavFormat.createWriterFor(outStream, sampleRate, numChannels,
                                  bitsPerSample, StringPairArray(), 0));
    outBuffer.writeToAudioWriter(writer.get(), 0, samplesRead[0]);

    std::cout << "Writing " << samplesRead[0] << " samples" << std::endl;
    return 0;
  }

 private:
  string in_;
  string out_;
  float sampleRate_;
  float timeScale_;
  float pitchScale_;
  int chunkSize_;

  static const char shortOpts_[];
  static const struct option longOpts_[];

  DISALLOW_COPY_AND_ASSIGN(PitchTimeShifter);
};

const char PitchTimeShifter::shortOpts_[] = "cioprt";

const struct option PitchTimeShifter::longOpts_[] = {
  { "chunk_size",   required_argument, NULL, 'c' },
  { "help",         no_argument,       NULL, 'h' },
  { "in",           required_argument, NULL, 'i' },
  { "out",          required_argument, NULL, 'o' },
  { "pitch_scale",  required_argument, NULL, 'p' },
  { "sample_rate",  required_argument, NULL, 'r' },
  { "time_scale",   required_argument, NULL, 't' },
  { NULL, 0, NULL,           0 }
};

int main(int argc, char* argv[]) {
  PitchTimeShifter shifter;
  return shifter.getOpt(argc, argv) ? shifter.shiftPitchAndTime() : 0;
}
