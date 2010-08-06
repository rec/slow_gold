#include <vector>

#include "rec/audio/stretch/Stretcher.h"
#include "rec/audio/stretch/SimpleStretcher.h"
#include "rec/audio/Buffer.h"
#include "rec/audio/stretch/TimeScaler.h"

namespace rec {
namespace audio {
namespace timescaler {

AudioSampleBuffer* stretchOnce(const Description& description,
                               const AudioSampleBuffer& inbuf) {
#if 0
  double timeScale = description.timeScale_;
  int outChannels = description.channels_;
  int chunkSize = description.chunkSize_;

  int inChannels = inbuf.getNumChannels();
  int sampleCount = inbuf.getNumSamples();

  // TODO: this is truncating... is it a big deal?
  int outSampleCount = int(inbuf.getNumSamples() * timeScale);

  AudioSampleBuffer* buf = new AudioSampleBuffer(outChannels, outSampleCount);
  AudioTimeScaler scaler;
  description.Init(&scaler);

  std::vector<float*> inSamples(inChannels), outSamples(outChannels);
  for (int written = 0, read = 0; written < outSampleCount && read < sampleCount; ) {
    int outChunk = std::min(chunkSize, outSampleCount - written);
    int64 inChunk = std::min(scaler.GetInputBufferSize(outChunk) / 2,
                             (unsigned) (sampleCount - read));

    for (int c = 0; c < std::max(inChannels, outChannels); ++c) {
      inSamples[c] = inbuf.getSampleData(c % inChannels) + read;
      outSamples[c] = buf->getSampleData(c % outChannels) + written;
    }

    written += scaler.Process(&inSamples[0], &outSamples[0], inChunk, outChunk);
    read += inChunk;
  }
  return buf;
#else
  Stretcher stretcher_(description, inbuf);
  while (stretcher_.readNextChunk(description.chunk_size()));
  return stretcher_.getBuffer();
#endif
}

}  // namespace timescaler
}  // namespace audio
}  // namespace rec
