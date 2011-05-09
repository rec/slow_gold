#include "rec/audio/source/Buffered.h"
#include "rec/audio/util/CopySamples.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Buffered::Buffered(PositionableAudioSource* source, SampleTime size)
    : source_(source),
      buffer_(2, size),
      circular_(size),
      prepared_(false) {
  setBuffer(&buffer_);
}

void Buffered::getNextAudioBlock(const AudioSourceChannelInfo& i) {
  BufferSource::getNextAudioBlock(i);
  circular_.consume(i.numSamples);
}

void Buffered::fillOnce(SampleTime size) {
  ScopedLock l(lock_);
  Range<SampleTime> fillable = circular_.fillable();
  AudioSourceChannelInfo info;

  info.buffer = &buffer_;
  info.startSample = fillable.begin_;
  info.numSamples = juce::jmin(size, fillable.size());

  if (info.numSamples > 0) {
    ScopedUnlock l(lock_);
    if (!prepared_)
      prepareToPlay(size, 44100);

    source_->getNextAudioBlock(info);
  }

  circular_.fill(info.numSamples);
}

}  // namespace source
}  // namespace audio
}  // namespace rec

