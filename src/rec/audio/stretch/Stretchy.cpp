#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/stretch/AudioMagicStretchy.h"
#include "rec/audio/stretch/SoundTouchStretchy.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Stretcher.h"
#include "rec/util/Math.h"

using namespace juce;
using namespace google;

using rec::audio::stretch::Stretch;

namespace rec {
namespace audio {
namespace stretch {

Stretchy::Stretchy(Source* s) : Wrappy(s) {
}

Stretchy::~Stretchy() {}

#if 0
// static
Stretchy* Stretchy::create(Source* p, const Stretch& s) {
  switch (s.strategy()) {
   case Stretch::AUDIO_MAGIC: return stretch::createAudioMagicStretchy(p, s);
   case Stretch::SOUNDTOUCH: return stretch::createSoundTouchStretchy(p, s);
   default: return NULL;
  }
}
#endif

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

static Stretcher* makeStretcher(Source* source, const Stretch& stretch) {
  switch (stretch.strategy()) {
   case Stretch::AUDIO_MAGIC: return new AudioMagicStretchy(source, stretch);
   case Stretch::SOUNDTOUCH: return new SoundTouchStretchy(source, stretch);
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
  if (bypass_) {
    timeScale_ = 1.0;
    return;
  }

  stretcher_.reset(makeStretcher(source(), stretch));
  if (!stretcher_)
    bypass_ = true;
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
    stretcher_->nextStretchedAudioBlock(info);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

