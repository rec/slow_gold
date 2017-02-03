#pragma once

#include "rec/base/base.h"

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
                                                      int /*startOffsetInDestBuffer*/,  // Why isn't this used?
                                                      int64 startSampleInFile,
                                                      int numSamples) {
        numDestChannels = std::min(static_cast<int>(numChannels), numDestChannels);

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
                    s = (endian_ ? input->readShortBigEndian() : input->readShort()) * 65536;
                else if (bitsPerSample == 32)
                    s = (endian_ ? input->readIntBigEndian() : input->readInt()) * 65536;
                else {
                    DCHECK(false) << "Unknown bits per sample " << bitsPerSample;
                    s = 0;
                }

                destSamples[c][i + startSampleInFile] = s;
            }
        }
        return true;  // Might not be right.
    }

    Endianness endian_;
    int frameSize_;

  private:
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(RawFormatReader);
};

}  // namespace raw
}  // namespace format
}  // namespace audio
}  // namespace rec

