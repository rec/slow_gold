// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/source/DoubleStretchy.h"
#include "rec/audio/source/MultiWrappy.h"

namespace rec {
namespace audio {
namespace source {

DoubleStretchy::DoubleStretchy(const Description& description,
                               PositionableAudioSource* s0,
                               PositionableAudioSource* s1)
    : position_(0),
      descriptionChanged_(false),
      description_(description),
      gettingBlock_(false),
      source_(new SourceReader),
      nextSource_(new SourceReader) {
  source_->source_.reset(s0);
  nextSource_->source_.reset(s1);
  source_->reset(description, 0);
}

void DoubleStretchy::setDescription(const Description& description) {
  ScopedLock l(lock_);
  descriptionChanged_ = true;
  description_.CopyFrom(description);
}

int DoubleStretchy::getTotalLength() const {
  ScopedLock l(lock_);
  return source()->getTotalLength();
}

int DoubleStretchy::getNextReadPosition() const {
  ScopedLock l(lock_);
  return source()->getNextReadPosition();
}

void DoubleStretchy::setNextReadPosition(int position) {
  ScopedLock l(lock_);
  if (position_ <= getTotalLength()) {
    source_->offset_ = 0;
    nextSource_->offset_ = 0;
  }

  if (source_->buffered_)
    source_->buffered_->setNextReadPosition(position + source_->offset_);

  if (nextSource_->buffered_)
    nextSource_->buffered_->setNextReadPosition(position + nextSource_->offset_);

  position_ = position;
}

int DoubleStretchy::available() const {
  ScopedLock l(lock_);
  return source()->available();
}

void DoubleStretchy::prepareToPlay(int s, double r) {
  if (source_->buffered_)
    source_->buffered_->prepareToPlay(s, r);

  if (nextSource_->buffered_)
    nextSource_->buffered_->prepareToPlay(s, r);
}

void DoubleStretchy::releaseResources() {
  if (source_->buffered_)
    source_->buffered_->releaseResources();

  if (nextSource_->buffered_)
    nextSource_->buffered_->releaseResources();
}

bool DoubleStretchy::fillNext() {
  // Make sure our memory management is done out of the lock.
  scoped_ptr<Buffery> bufferDeleter;
  scoped_ptr<PositionableAudioSource> stretchyDeleter;

  {
    ScopedLock l(lock_);

    int prefillSize = description_.prefill_size();
    bool isNext = next() && source()->ready(prefillSize);
    Buffery* fill = isNext ? next() : source();
    int chunkSize = description_.chunk_size();

    bool result;
    {
      ScopedUnlock l(lock_);
      result = fill->fillNext(chunkSize);
    }

    if (gettingBlock_)
      return true;  // Don't rock the boat until that's done.

    if (isNext) {
      if (fill->ready(prefillSize)) {
        // Your new file is ready!
        source_.swap(nextSource_);
        DCHECK(!next());
      }

    } else if (descriptionChanged_) {
      descriptionChanged_ = false;

      float scale = description_.time_scale() /
        source_->description_.time_scale();
      int offset = (position_ + source_->offset_) * scale - position_;

      LOG(INFO) << "position=" << position_ << " offset=" << offset
                << " source_->offset_=" << source_->offset_ << " scale=" << scale;

      nextSource_->reset(description_, offset);
    }

    return result || next();
  }
}

void DoubleStretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);
  PositionableAudioSource* buffered = source();

  gettingBlock_ = true;
  {
    ScopedUnlock l(lock_);
    buffered->getNextAudioBlock(info);
  }
  gettingBlock_ = false;
}

bool DoubleStretchy::isLooping() const {
  ScopedLock l(lock_);
  return source()->isLooping();
}

void DoubleStretchy::setLooping(bool looping) {
  ScopedLock l(lock_);
  if (source_->buffered_)
    source_->buffered_->setLooping(looping);

  if (nextSource_->buffered_)
    nextSource_->buffered_->setLooping(looping);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
