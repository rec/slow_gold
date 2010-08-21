// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/source/DoubleStretchy.h"

namespace rec {
namespace audio {
namespace source {

DoubleStretchy::DoubleStretchy(const Description& description,
                               PositionableAudioSource* s0,
                               PositionableAudioSource* s1)
    : position_(0),
      currentReader_(0),
      descriptionChanged_(false),
      description_(description),
      gettingBlock_(false) {
  readers_[0].source_.reset(s0);
  readers_[1].source_.reset(s1);

  readers_[0].reset(description, 0);
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
  for (SourceReader* i = readers_; i != readers_ + SIZE; ++i) {
    if (position_ <= getTotalLength())
      i->offset_ = 0;
    if (i->buffered_)
      i->buffered_->setNextReadPosition(position + i->offset_);
  }
}

int DoubleStretchy::available() const {
  ScopedLock l(lock_);
  return source()->available();
}

void DoubleStretchy::prepareToPlay(int s, double r) {
  for (SourceReader* i = readers_; i != readers_ + SIZE; ++i) {
    if (i->buffered_)
      i->buffered_->prepareToPlay(s, r);
  }
}

void DoubleStretchy::releaseResources() {
  for (SourceReader* i = readers_; i != readers_ + SIZE; ++i) {
    if (i->buffered_)
      i->buffered_->releaseResources();
  }
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
        SourceReader& current = readers_[currentReader_];
        current.buffered_.swap(bufferDeleter);
        current.reader_.swap(stretchyDeleter);
        currentReader_ = 1 - currentReader_;
        DCHECK(!next());
      }

    } else if (descriptionChanged_) {
      descriptionChanged_ = false;

      SourceReader& sr = readers_[currentReader_];
      float scale = description_.time_scale() / sr.description_.time_scale();
      int offset = (position_ + sr.offset_) * scale - position_;

      LOG(INFO) << "position=" << position_ << " offset=" << offset
                << " sr.offset_=" << sr.offset_ << " scale=" << scale;

      readers_[1 - currentReader_].reset(description_, offset);
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
  for (SourceReader* i = readers_; i != readers_ + SIZE; ++i)
    if (i->buffered_)
      i->buffered_->setLooping(looping);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
