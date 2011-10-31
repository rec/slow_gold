#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/stretch/AudioMagic.h"
#include "rec/audio/stretch/RubberBand.h"
#include "rec/audio/stretch/SoundTouch.h"
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

static Implementation* makeImplementation(Source* source, const Stretch& stretch) {
  switch (stretch.strategy()) {
   case Stretch::AUDIO_MAGIC: return new AudioMagic(source, stretch);
   case Stretch::SOUNDTOUCH: return new SoundTouch(source, stretch);
   case Stretch::RUBBERBAND: return new RubberBand(source, stretch);
   default: return NULL;
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
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  Lock l(lock_);
  DCHECK_EQ(info.buffer->getNumChannels(), channels_);
  bool bypass;
  {
    ScopedLock l(lock_);
    bypass = bypass_;
  }
  if (bypass)
    Wrappy::getNextAudioBlock(info);
  else
    implementation_->nextStretchedAudioBlock(info);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

