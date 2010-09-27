// Wrap an incoming AudioSource, and time-stretch it.

#include "rec/audio/source/DoubleStretchy.h"
#include "rec/audio/source/Offset.h"

namespace rec {
namespace audio {
namespace source {

using rec::audio::timescaler::TimeStretch;

struct SourceReader {
  TimeStretch description_;

  scoped_ptr<Source> source_;
  scoped_ptr<Source> stretchy_;
  scoped_ptr<Source> offset_;
  scoped_ptr<Buffery> buffered_;

  void reset(const TimeStretch& description, int offset) {
    description_.CopyFrom(description);
    stretchy_.reset(new Stretchy(description_, source_.get()));
    offset_.reset(new Offset(stretchy_.get(), offset));
    buffered_.reset(new Buffery(description_.channels(), stretchy_.get()));
  }
};

DoubleStretchy::DoubleStretchy(const TimeStretch& description,
                               Source* s0,
                               Source* s1)
    : descriptionChanged_(false),
      description_(description),
      gettingBlock_(false),
      source_(new SourceReader),
      nextSource_(new SourceReader) {
  source_->source_.reset(s0);
  nextSource_->source_.reset(s1);
  source_->reset(description, 0);
}

DoubleStretchy::~DoubleStretchy() {}

void DoubleStretchy::setDescription(const TimeStretch& description) {
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
  LOG(INFO) << "setNextReadPosition " << position;
  ScopedLock l(lock_);
  source()->setNextReadPosition(position);
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
  scoped_ptr<Source> stretchyDeleter;

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
        // DCHECK(!next());
      }

    } else if (descriptionChanged_) {
      descriptionChanged_ = false;

      float scale = description_.time_scale() /
        source_->description_.time_scale();

#if 0
      int offset = (position_ + source_->offset_) * scale -
        getNextReadPosition();
#else
      int offset = 0;
#endif
      nextSource_->reset(description_, offset);
      LOG(INFO) << "scale: " << scale << "pos: " << getNextReadPosition()
                 << " offset: " << offset;
    }

    return result || next();
  }
}

void DoubleStretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  LOG(INFO) << "getNextAudioBlock " << getNextReadPosition();
  ScopedLock l(lock_);
  Source* buffered = source();

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


Buffery* DoubleStretchy::source() {
  return source_->buffered_.get();
}

const Buffery* DoubleStretchy::source() const {
  return source_->buffered_.get();
}

Buffery* DoubleStretchy::next() {
  return nextSource_->buffered_.get();
}


}  // namespace source
}  // namespace audio
}  // namespace rec
