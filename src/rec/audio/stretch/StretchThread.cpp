#include <vector>

#include "rec/audio/stretch/StretchThread.h"

namespace rec {
namespace audio {
namespace stretch {

virtual void StretchThread::run() {
  CircularSamples<float**>& in = desc_->in_;
  CircularSamples<float**>& out = desc_->out_;

  int channels = in.samples_.length();
  std::vector<float*> inSamples(channels), outSamples(channels);

  AudioTimeScaler scaler;
  timeScale_.Init(&scaler);

  bool needsNotify = true;

  for (int written = 0; written < out.circular_.size && !threadShouldExit(); ) {
    int outChunk = std::min(CHUNK_SIZE, out.circular_.remaining());
    int64 inChunk = scaler.GetInputBufferSize(outChunk) / 2;

    for (int c = 0; c < channels; ++c) {
      inSamples[c] = in.getSamples(c);
      outSamples[c] = out.getSamples(c);
    }

    written += scaler.Process(&inSamples[0], &outSamples[0], inChunk, outChunk);
    if (threadShouldExit())
      break;

    if (needsNotify && written >= INITIAL_SAMPLES) {
      ready();
      needsNotify = false;
    }

    in.circular_.increment(inChunk);
    out.circular_.increment(outChunk);
  }
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
