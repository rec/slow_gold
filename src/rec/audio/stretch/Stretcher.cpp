#include <vector>

#include "rec/audio/stretch/Stretcher.h"
#include "rec/util/Circular.h"

#include "rec/ammf_scaler/AudioTimeScaler.h"
#include "juce_amalgamated.h"
#include "rec/audio/stretch/TimeScaler.h"

namespace rec {
namespace audio {
namespace timescaler {

using rec::util::Circular;

class CircularBuffer {
 public:
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
      samplePositions_[i] = buffer_.getSampleData(i) + done_.end_;
  }

  const AudioSampleBuffer& buffer_;
  Circular done_;
  std::vector<float*> samplePositions_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CircularBuffer);
};

Stretcher::Stretcher() : scaler_(new AudioTimeScaler) {}
Stretcher::~Stretcher() {}

void Stretcher::startStretch(const Description& description,
                             const AudioSampleBuffer& inbuf,
                             int inStart) {
  Description d(description);
  uint32 channels = std::min(d.channels(), (uint32) inbuf.getNumChannels());
  d.set_channels(channels);

  Init(d, scaler_.get());
  chunkSize_ = description.chunk_size();

  int outSamples = inbuf.getNumSamples() * d.time_scale();
  buffer_.reset(new AudioSampleBuffer(channels, outSamples));
  in_.reset(new CircularBuffer(inbuf, inStart));
  out_.reset(new CircularBuffer(*buffer_, inStart * d.time_scale()));
}

bool Stretcher::readNextChunk() {
  return out_->readFrom(chunkSize_, in_.get(), scaler_.get());
}

const Circular& Stretcher::in() const { return in_->done(); }
const Circular& Stretcher::out() const { return out_->done(); }

AudioSampleBuffer* Stretcher::stretchOnce(const Description& description,
                                          const AudioSampleBuffer& inbuf) {
  Stretcher stretcher;
  stretcher.startStretch(description, inbuf, 0);

  while (stretcher.readNextChunk()) {}
  return stretcher.transferBuffer();
}

}  // namespace timescaler
}  // namespace audio
}  // namespace rec
