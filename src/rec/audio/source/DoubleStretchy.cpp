#include "rec/audio/source/DoubleStretchy.h"

#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/audio/source/TimeScaler.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/audio/source/Wrappy.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

class BufferedStretchy : public Buffery {
 public:
  BufferedStretchy(Source* s) : Buffery(&stretchy_), stretchy_(s) {}

  void setDescription(const TimeStretch& t, int position) {
    stretchy_.setDescription(t);
    resetFrom(t.channels(), position);
    setNextReadPosition(position);
  }

  const TimeStretch& getDescription() const {
    return stretchy_.getDescription();
  }

 private:
  Stretchy stretchy_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferedStretchy);
};

DoubleStretchy::DoubleStretchy(Source* s0, Source* s1)
    : descriptionChanged_(false),
      description_(new TimeStretch),
      gettingBlock_(false),
      buffer0_(new BufferedStretchy(s0)),
      buffer1_(new BufferedStretchy(s1)),
      buffer_(NULL),
      next_(NULL) {
}

DoubleStretchy::~DoubleStretchy() {}

void DoubleStretchy::initialize() {
  buffer0_->initialize();
  buffer1_->initialize();
}


void DoubleStretchy::setDescription(const TimeStretch& description) {
  ScopedLock l(lock_);
  descriptionChanged_ = true;
  description_->CopyFrom(description);

  if (!buffer_) {
    buffer_ = buffer0_.get();
    buffer_->setDescription(*description_, getNextReadPosition());
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

bool DoubleStretchy::ready(int amount) const {
  ScopedLock l(lock_);
  return buffer_->ready(amount);
}

void DoubleStretchy::prepareToPlay(int s, double r) {
  buffer0_->prepareToPlay(s, r);
  buffer1_->prepareToPlay(s, r);
}

void DoubleStretchy::releaseResources() {
  buffer0_->releaseResources();
  buffer1_->releaseResources();
}

bool DoubleStretchy::fillNext() {
  ScopedLock l(lock_);

  Buffery* toFill = buffer_;
  if (next_) {
    if (buffer_->ready(description_->next_buffer_fill_size()))
      toFill = next_;
  }

  bool filled = toFill->filled();
  if (!filled) {
    juce:ScopedUnlock l(lock_);
    toFill->fillNext(description_->chunk_size());
  }

  if (gettingBlock_)
    return true;  // Don't rock the boat until that's done.

  if (toFill == next_) {
    if (toFill->ready(description_->prefill_size())) {
      // Your new file is ready!
      buffer_ = next_;
      next_ = NULL;
    }
    return true;
  }

  if (!next_ && descriptionChanged_) {
    float scale = description_->time_scale() /
      buffer_->getDescription().time_scale();

    next_ = (buffer_ == buffer1_.get()) ? buffer0_.get() : buffer1_.get();
    next_->setDescription(*description_, getNextReadPosition() * scale);
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
    if (false && next_)
      next_->advance(info.numSamples);
  }
  gettingBlock_ = false;
}

bool DoubleStretchy::isLooping() const {
  ScopedLock l(lock_);
  return buffer_->isLooping();
}

void DoubleStretchy::setLooping(bool looping) {
  ScopedLock l(lock_);
  buffer0_->setLooping(looping);
  buffer1_->setLooping(looping);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
