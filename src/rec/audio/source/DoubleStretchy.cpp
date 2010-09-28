// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/source/DoubleStretchy.h"

namespace rec {
namespace audio {
namespace source {

using rec::audio::timescaler::TimeStretch;

DoubleStretchy::DoubleStretchy(Source* s0, Source* s1)
    : descriptionChanged_(false),
      gettingBlock_(false),
      buffer0_(s0),
      buffer1_(s1),
      buffer_(NULL),
      next_(NULL) {
}

DoubleStretchy::~DoubleStretchy() {}

void DoubleStretchy::setDescription(const TimeStretch& description) {
  ScopedLock l(lock_);
  descriptionChanged_ = true;
  description_.CopyFrom(description);

  if (!buffer_) {
    buffer_ = &buffer0_;
    buffer_->setDescription(description_, getNextReadPosition());
  }
}

int DoubleStretchy::getTotalLength() const {
  ScopedLock l(lock_);
  return buffer_->getTotalLength();
}

int DoubleStretchy::getNextReadPosition() const {
  ScopedLock l(lock_);
  return buffer_->getNextReadPosition();
}

void DoubleStretchy::setNextReadPosition(int position) {
  ScopedLock l(lock_);
  buffer_->setNextReadPosition(position);
  // TODO.
}

int DoubleStretchy::available() const {
  ScopedLock l(lock_);
  return buffer_->available();
}

void DoubleStretchy::prepareToPlay(int s, double r) {
  buffer0_.prepareToPlay(s, r);
  buffer1_.prepareToPlay(s, r);
}

void DoubleStretchy::releaseResources() {
  buffer0_.releaseResources();
  buffer1_.releaseResources();
}

bool DoubleStretchy::fillNext() {
  ScopedLock l(lock_);

  Buffery* toFill = buffer_;
  if (next_) {
    if (buffer_->ready(description_.next_buffer_fill_size()))
      toFill = next_;
  }

  bool filled = toFill->filled();
  if (!filled) {
    ScopedUnlock l(lock_);
    toFill->fillNext(description_.chunk_size());
  }

  if (gettingBlock_)
    return true;  // Don't rock the boat until that's done.

  if (toFill == next_) {
    if (toFill->ready(description_.prefill_size())) {
      // Your new file is ready!
      buffer_ = next_;
      next_ = NULL;
    }
    return true;
  }

  if (!next_ && descriptionChanged_) {
    float scale = description_.time_scale() /
      buffer_->getDescription().time_scale();

    next_ = (buffer_ == &buffer1_) ? &buffer0_ : &buffer1_;
    next_->setDescription(description_, getNextReadPosition() * scale);
    descriptionChanged_ = false;
  }

  return next_ || !filled;
}

void DoubleStretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);
  gettingBlock_ = true;
  {
    ScopedUnlock l(lock_);
    buffer_->getNextAudioBlock(info);
  }
  gettingBlock_ = false;
}

bool DoubleStretchy::isLooping() const {
  ScopedLock l(lock_);
  return buffer_->isLooping();
}

void DoubleStretchy::setLooping(bool looping) {
  ScopedLock l(lock_);
  buffer0_.setLooping(looping);
  buffer1_.setLooping(looping);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
