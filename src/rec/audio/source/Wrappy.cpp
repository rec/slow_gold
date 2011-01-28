#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

Wrappy::Wrappy(PositionableAudioSource* s) : position_(0) {
  setSource(s);
}

int64 Wrappy::getNextReadPosition() const {
  ScopedLock l(lock_);
  return position_;
}

PositionableAudioSource* Wrappy::source() const {
  ScopedLock l(lock_);
  if (PositionableAudioSource* source = getSource())
    return source;

  static Empty empty;
  return &empty;
}

void Wrappy::setSource(PositionableAudioSource* s) {
  ScopedLock l(lock_);
  source_.reset(s);
}

void Wrappy::setNextReadPosition(int64 p) {
  source()->setNextReadPosition(p);
  ScopedLock l(lock_);
  position_ = p;
}

void Wrappy::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  source()->getNextAudioBlock(info);

  ScopedLock l(lock_);
  position_ = mod(position_ + info.numSamples);
}


}  // namespace source
}  // namespace audio
}  // namespace rec
