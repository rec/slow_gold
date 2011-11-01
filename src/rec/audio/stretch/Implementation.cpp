#include "rec/audio/stretch/Implementation.h"

namespace rec {
namespace audio {
namespace stretch {

Implementation::Implementation(PositionableAudioSource* source, int channels)
    : source_(source), buffer_(channels, INITIAL_BUFFER_SIZE) {
  info_.buffer = &buffer_;
  info_.startSample = 0;
}

float** Implementation::getSourceSamples(int numSamples) {
  info_.numSamples = numSamples;
  buffer_.setSize(buffer_.getNumChannels(), numSamples, false, false, true);
  source_->getNextAudioBlock(info_);
  return buffer_.getArrayOfChannels();
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
