#ifndef __REC_STRETCHER_CIRCULARBUFFER__
#define __REC_STRETCHER_CIRCULARBUFFER__

#include <vector>

#include "rec/util/Circular.h"
#include "rec/ammf_scaler/AudioTimeScaler.h"
#include "juce_amalgamated.h"

namespace rec {
namespace audio {
namespace timescaler {

class CircularBuffer {
 public:
  typedef rec::util::Circular Circular;

  CircularBuffer(const AudioSampleBuffer& buffer, int64 begin)
      : buffer_(buffer),
        done_(begin, buffer.getNumSamples()),
        samplePositions_(buffer.getNumChannels()) {
    getSamplePositions();
  }

  bool readFrom(int64 chunk, CircularBuffer* in, AudioTimeScaler* scaler) {
    if (!(done_.remaining() && in->done_.remaining()))
      return false;

    int64 outChunk = std::min(chunk, done_.remaining());
    int64 inChunk = std::min((int64) scaler->GetInputBufferSize(outChunk) / 2,
                             in->done_.remaining());
    float** outSamples = &samplePositions_.front();
    float** inSamples = &in->samplePositions_.front();

    int64 outRead = scaler->Process(inSamples, outSamples, inChunk, outChunk);

    jassert(outRead <= outChunk);
    bool moreOut = increment(outRead);
    bool moreIn = in->increment(inChunk);

    return moreOut && moreIn;
  }

  const Circular& done() const { return done_; }

 private:
  bool increment(int64 delta) {
    bool result = done_.increment(delta);
    getSamplePositions();
    return result;
  }

  void getSamplePositions() {
    for (int i = 0; i < buffer_.getNumChannels(); ++i)
      samplePositions_[i] = buffer_.getSampleData(i) + done_.end();
  }

  const AudioSampleBuffer& buffer_;
  Circular done_;
  std::vector<float*> samplePositions_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CircularBuffer);
};

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHER_CIRCULARBUFFER__
