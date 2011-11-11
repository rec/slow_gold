#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/stretch/AudioMagic.h"
#include "rec/audio/stretch/RubberBand.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Implementation.h"
#include "rec/util/Math.h"

using namespace juce;
using namespace google;

using rec::audio::stretch::Stretch;

namespace rec {
namespace audio {
namespace stretch {

Stretchy::Stretchy(Source* s) : Wrappy(s), strategy_(Stretch::NONE) {
}

Stretchy::~Stretchy() {}

int64 Stretchy::getTotalLength() const {
  ScopedLock l(lock_);
  return scale(source()->getTotalLength());
}

int64 Stretchy::getNextReadPosition() const {
  ScopedLock l(lock_);
  return scale(source()->getNextReadPosition());
}

void Stretchy::setNextReadPosition(int64 position) {
  ScopedLock l(lock_);
  source()->setNextReadPosition(static_cast<int64>(position / timeScale_));
}

static Implementation* makeImplementation(Source* src, const Stretch& stretch) {
  switch (stretch.strategy()) {
#ifdef USE_AUDIO_MAGIC
   case Stretch::AUDIO_MAGIC: return new AudioMagic(src, stretch);
#endif

   case Stretch::RUBBERBAND: return new RubberBand(src, stretch);
   default:
    LOG(ERROR) << "Didn't understand strategy " << stretch.strategy();
    return NULL;
  }
}

void Stretchy::setStretch(const stretch::Stretch& stretch) {
  ScopedLock l(lock_);
  channels_ = stretch.channels();

  static const double DELTA = 0.00001;
  timeScale_ = stretch::timeScale(stretch);
  bypass_ = stretch.passthrough_when_disabled() &&
    near(timeScale_, 1.0, DELTA) &&
    near(stretch::pitchScale(stretch), 1.0, DELTA);

  if (!bypass_) {
    if (!implementation_ || strategy_ != stretch.strategy())
      implementation_.reset(makeImplementation(source(), stretch));
    else if (implementation_)
      implementation_->setStretch(stretch);

    bypass_ = !implementation_;
  }

  if (bypass_)
    timeScale_ = 1.0;

  DCHECK(implementation_ || bypass_);
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  {
    Lock l(lock_);
    DCHECK_EQ(info.buffer->getNumChannels(), channels_);
    if (!bypass_) {
      if (implementation_) {
        implementation_->getNextAudioBlock(info);
      } else {
        LOG_FIRST_N(ERROR, 1) << "No implementation of stretchy found";
      }
      return;
    }
  }

  Wrappy::getNextAudioBlock(info);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

