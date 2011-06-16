#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Empty.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

Wrappy::Wrappy(PositionableAudioSource* s) : position_(0), prepared_(false) {
  setSource(s);
}

SamplePosition Wrappy::mod(SamplePosition x) const {
  ScopedLock l(lock_);
  int64 length = getTotalLength();
  return length ? util::mod<int64>(x, length) : 0;
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

PositionableAudioSource* Wrappy::getSource() const {
  ScopedLock l(lock_);
  return source_.get();
}

void Wrappy::swap(ptr<PositionableAudioSource>* other) {
  ScopedLock l(lock_);
  source_.swap(*other);
}

void Wrappy::prepareToPlay(int s, double r) {
  ScopedLock l(lock_);

  source()->prepareToPlay(s, r);
  prepared_ = true;
}

void Wrappy::setNextReadPosition(int64 p) {
  ScopedLock l(lock_);

  position_ = p;
  source()->setNextReadPosition(p);
}

void Wrappy::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);

  source()->getNextAudioBlock(info);
  position_ = mod(position_ + info.numSamples);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
