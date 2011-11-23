#ifndef __REC_AUDIO_FORMAT_RAW_RAWFORMATWRITER__
#define __REC_AUDIO_FORMAT_RAW_RAWFORMATWRITER__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace format {
namespace raw {

class RawFormatWriter : public AudioFormatWriter {
 public:
  RawFormatWriter(OutputStream* destStream,
                  const String& formatName,
                  double sampleRate,
                  unsigned int numberOfChannels,
                  unsigned int bitsPerSample)
      : AudioFormatWriter(destStream, formatName, sampleRate, numberOfChannels,
                          bitsPerSample), endian_(LITTLE_END) {
  }

  virtual bool write (const int** samplesToWrite, int numSamples) {
    for (int i = 0; i < numSamples; ++i) {
      for (int c = 0; c < getNumChannels(); ++c) {
        int sample = samplesToWrite[c][i];
        if (bitsPerSample == 8) {
          output->writeByte(static_cast<char>(sample));
        } else {
          if (endian_) {
            if (bitsPerSample == 16)
              output->writeShortBigEndian(static_cast<short>(sample));
            else
              output->writeIntBigEndian(sample);
          } else {
            if (bitsPerSample == 16)
              output->writeShort(static_cast<short>(sample));
            else
              output->writeInt(sample);
          }
        }
      }
    }
    return false;
  }

 private:
  Endianness endian_;
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(RawFormatWriter);
};

}  // namespace raw
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_RAW_RAWFORMATWRITER__
