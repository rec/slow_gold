#include <vector>

#include "rec/audio/stretch/Stretcher.h"
#include "rec/audio/stretch/CircularBuffer.h"
#include "rec/util/Circular.h"

#include "rec/ammf_scaler/AudioTimeScaler.h"
#include "rec/audio/stretch/TimeScaler.h"

#include "juce_amalgamated.h"

namespace rec {
namespace audio {
namespace timescaler {

using rec::util::Circular;

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
