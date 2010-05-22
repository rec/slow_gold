#include <vector>

#include "rec/audio/stretch/SimpleStretcher.h"
#include "rec/audio/stretch/TimeScaler.h"

namespace rec {
namespace audio {
namespace timescaler {

const int Simple::CHUNK_SIZE = 512;
  
bool Simple::requestRescale(const Description& desc,
                            const AudioSampleBuffer& inbuf,
                            scoped_ptr<AudioSampleBuffer> *outbuf) {
  {
    ScopedLock l(lock_);
    nextDescription_ = desc;
    scaleNeeded_ = true;
    if (duringScaleOperation_) 
      return false;

    duringScaleOperation_ = true;
  }

  scoped_ptr<AudioSampleBuffer> buffer;
  while (true) {
    {
      ScopedLock l(lock_);
      if (!scaleNeeded_) {
        duringScaleOperation_ = false;
        outbuf->reset(buffer.transfer());
        return true;
      }
      description_ = nextDescription_;
      scaleNeeded_ = false;
    }

    double timeScale = description_.timeScale_;
    int outChannels = description_.channels_;
    int inChannels = inbuf.getNumChannels();
    int sampleCount = inbuf.getNumSamples();

    // TODO: this is truncating... is it a big deal?
    int outSampleCount = int(inbuf.getNumSamples() * timeScale);

    buffer.reset(new AudioSampleBuffer(outChannels, outSampleCount));

    AudioTimeScaler scaler;
    description_.Init(&scaler);

    std::vector<float*> inSamples(inChannels), outSamples(outChannels);
    for (int written = 0, read = 0; written < outSampleCount && read < sampleCount; ) {
      int outChunk = std::min(CHUNK_SIZE, outSampleCount - written);
      int64 inChunk = std::min(scaler.GetInputBufferSize(outChunk) / 2,
                               (unsigned) (sampleCount - read));

      for (int c = 0; c < std::max(inChannels, outChannels); ++c) {
        inSamples[c] = inbuf.getSampleData(c % inChannels) + read;
        outSamples[c] = buffer->getSampleData(c % outChannels) + written;
      }

      written += scaler.Process(&inSamples[0], &outSamples[0], inChunk, outChunk);
      read += inChunk;
    }
  }
}

}  // namespace timescaler
}  // namespace audio
}  // namespace rec
