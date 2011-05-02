#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Empty.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

Wrappy::Wrappy(PositionableAudioSource* s) : position_(0), prepared_(false) {
  setSource(s);
}

SampleTime Wrappy::mod(SampleTime x) const {
  return util::mod(x, getTotalLength());
}

SampleTime Wrappy::getNextReadPosition() const {
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

void Wrappy::prepareToPlay(int s, double r) {
  source()->prepareToPlay(s, r);

  ScopedLock l(lock_);
  prepared_ = true;
}

void Wrappy::setNextReadPosition(SampleTime p) {
  {
    ScopedLock l(lock_);
    position_ = p;
  }
  source()->setNextReadPosition(p);
}

void Wrappy::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  source()->getNextAudioBlock(info);

  ScopedLock l(lock_);
  position_ = mod(position_ + info.numSamples);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
