#include "rec/audio/stretch/Stretchy.h"

#include "rec/audio/SampleRate.h"
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

Stretchy::Stretchy(Source* s) : Wrappy(s), strategy_(Stretch::NONE),
                                channels_(2), timeScale_(1.0), bypass_(false),
                                detune_(0.0),
                                sampleRate_(44100) {
}

Stretchy::~Stretchy() {}

int64 Stretchy::getTotalLength() const {
  Lock l(lock_);
  return scale(source()->getTotalLength());
}

int64 Stretchy::getNextReadPosition() const {
  Lock l(lock_);
  return scale(source()->getNextReadPosition());
}

void Stretchy::setNextReadPosition(int64 position) {
  Lock l(lock_);
  source()->setNextReadPosition(static_cast<int64>(position / timeScale_));
}

static Implementation* makeImplementation(Source* src, const Stretch& stretch) {
  switch (stretch.strategy()) {
   case Stretch::RUBBERBAND: return new RubberBand(src, stretch);
   default:
    LOG(DFATAL) << "Didn't understand strategy " << stretch.strategy();
    return NULL;
  }
}

void Stretchy::setMasterTune(double detune) {
  Lock l(lock_);
  detune_ = detune;
  if (implementation_)
    implementation_->setMasterTune(detune_);
}

void Stretchy::setSampleRate(int sampleRate) {
  Lock l(lock_);
  sampleRate_ = sampleRate;
  if (implementation_)
    implementation_->setMasterTune(sampleRate_);
}

void Stretchy::setStretch(const stretch::Stretch& stretch) {
  Lock l(lock_);
  stretch_ = stretch;
  channels_ = stretch.channels();

  static const double DELTA = 0.00001;
  timeScale_ = stretch::timeScale(stretch);

  // TODO: this "bypass" code is dodgy.
  bypass_ = stretch.passthrough_when_disabled() &&
    near(timeScale_, 1.0, DELTA) &&
    near(stretch::pitchScale(stretch, detune_), 1.0, DELTA);

  if (!bypass_) {
    if (!implementation_ || strategy_ != stretch.strategy()) {
      implementation_.reset(makeImplementation(source(), stretch));
      implementation_->setMasterTune(detune_);
      implementation_->setSampleRate(sampleRate_);
    } else {
      implementation_->setStretch(stretch);
    }
  }

  if (bypass_)
    timeScale_ = 1.0;

  DCHECK(implementation_ || bypass_);
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  {
    Lock l(lock_);
    if (!bypass_) {
      DCHECK_EQ(info.buffer->getNumChannels(), channels_);
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

