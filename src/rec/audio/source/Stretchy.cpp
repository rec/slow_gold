#include "rec/audio/source/Stretchy.h"
#include "rec/audio/stretch/AudioMagicStretchy.h"
#include "rec/audio/stretch/SoundTouchStretchy.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/util/Math.h"

using namespace juce;
using namespace google;

using rec::audio::stretch::Stretch;

namespace rec {
namespace audio {
namespace source {

Stretchy::Stretchy(Source* s, const Stretch& stretch) : Wrappy(s) {
  setStretch(stretch);
}

Stretchy::~Stretchy() {}

// static
Stretchy* Stretchy::create(Source* p, const Stretch& s) {
  switch (s.strategy()) {
   case Stretch::AUDIO_MAGIC: return stretch::createAudioMagicStretchy(p, s);
   case Stretch::SOUNDTOUCH: return stretch::createSoundTouchStretchy(p, s);
   default: return NULL;
  }
}

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

void Stretchy::setStretch(const stretch::Stretch& s) {
  ScopedLock l(lock_);
  stretch_ = s;

  static const double DELTA = 0.00001;
  timeScale_ = stretch::timeScale(stretch_);
  bypass_ = stretch_.passthrough_when_disabled() &&
    near(timeScale_, 1.0, DELTA) &&
    near(stretch::pitchScale(stretch_), 1.0, DELTA);
  if (bypass_) {
    timeScale_ = 1.0;
    return;
  }

  initializeStretcher();
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  Lock l(lock_);
  DCHECK_EQ(info.buffer->getNumChannels(), stretch_.channels());
  bool bypass;
  {
    ScopedLock l(lock_);
    bypass = bypass_;
  }
  if (bypass)
    Wrappy::getNextAudioBlock(info);
  else
    nextStretchedAudioBlock(info);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
