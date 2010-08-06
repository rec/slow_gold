#ifndef __REC_STRETCHER
#define __REC_STRETCHER

#include <vector>

#include "juce_amalgamated.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/audio/Buffer.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace timescaler {

class Stretcher {
 public:
  Stretcher(const Description& d, const AudioSampleBuffer& inBuf)
      : channels_(std::max(d.channels(), (uint32) inBuf.getNumChannels())),
        in_(inBuf, channels_),
        outBuf_(new AudioSampleBuffer(d.channels(), in_.size_ * d.time_scale())),
        out_(*outBuf_, channels_) {
    Init(d, &scaler_);
  }

  bool readNextChunk(int64 outChunk) {
    outChunk = std::min(outChunk, out_.remaining());

    int64 inChunk = scaler_.GetInputBufferSize(outChunk) / 2;
    inChunk = std::min(inChunk, in_.remaining());

    int64 outRead = scaler_.Process(in_.top(), out_.top(), inChunk, outChunk);
    jassert(outRead <= outChunk);
    in_.advance(inChunk);
    out_.advance(outRead);

    return in_.remaining() && out_.remaining();
  }

  AudioSampleBuffer* getBuffer() const { return outBuf_; }

 private:
  const int channels_;
  rec::audio::Buffer in_;
  AudioSampleBuffer* const outBuf_;
  rec::audio::Buffer out_;
  AudioTimeScaler scaler_;

  DISALLOW_COPY_AND_ASSIGN(Stretcher);
};

}  // namespace timescaler
}  // namespace audio
}  // namespace rec

#endif  // __REC_STRETCHER
