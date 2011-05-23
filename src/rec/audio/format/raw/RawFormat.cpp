#include "rec/audio/format/raw/RawFormat.h"
#include "rec/base/Arraysize.h"

namespace rec {
namespace audio {
namespace format {
namespace raw {

enum Endianness { LITTLE_END, BIG_END };

class RawFormatReader : public AudioFormatReader {
 public:
  RawFormatReader(InputStream* s, Endianness e = LITTLE_END)
      : AudioFormatReader(s, "raw"), endian_(e) {
    sampleRate = 44100.0;
    bitsPerSample = 16;
    lengthInSamples = -1;
    numChannels = 2;
    usesFloatingPointData = false;
    frameSize_ = -1;
  }

  virtual ~RawFormatReader() {}

  virtual bool readSamples(int** destSamples,
                           int numDestChannels,
                           int startOffsetInDestBuffer,
                           int64 startSampleInFile,
                           int numSamples) {
    if (numDestChannels > numChannels)
      numDestChannels = numChannels;
    if (lengthInSamples < 0) {
      frameSize_ = (numChannels * bitsPerSample / 8);
      lengthInSamples = input->getTotalLength() / frameSize_;
    }
    input->setPosition(startSampleInFile * frameSize_);
    for (int i = 0; i < numSamples; ++i) {
      for (int c = 0; c < numDestChannels; ++c) {
        int s;
        if (bitsPerSample == 8)
          s = input->readByte() * 256 * 65536;
        else if (bitsPerSample == 16)
          s = (endian_ ? input->readShort() : input->readShortBigEndian()) * 65536;
        else if (bitsPerSample == 32)
          s = (endian_ ? input->readInt() : input->readIntBigEndian()) * 65536;

        destSamples[c][i + startSampleInFile] = s;
      }
    }
    return true;  // TODO
  }

  Endianness endian_;
  int frameSize_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(RawFormatReader);
};

RawFormat::RawFormat() : AudioFormat("raw", StringArray(".raw")) {}

AudioFormatReader* RawFormat::createReaderFor(InputStream* source, bool) {
  return new RawFormatReader(source);
}

AudioFormatWriter* RawFormat::createWriterFor(OutputStream* output,
                                              double sampleRateToUse,
                                              unsigned int numChannels,
                                              int bitsPerSample,
                                              const StringPairArray& meta,
                                              int quality) {
  return NULL;
}

const juce::Array<int> RawFormat::getPossibleSampleRates() {
  static int rates[] = {22050, 24000, 44100, 48000, 88200, 96000};
  return juce::Array<int>(rates, arraysize(rates));
}

const juce::Array<int> RawFormat::getPossibleBitDepths() {
  static const int depths[] = {8, 16, 32};
  return juce::Array<int>(depths, arraysize(depths));
}

}  // namespace raw
}  // namespace format
}  // namespace audio
}  // namespace rec
