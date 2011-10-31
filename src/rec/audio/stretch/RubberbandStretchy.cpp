#include "rec/audio/stretch/RubberbandStretchy.h"
#include "rec/audio/stretch/Stretch.h"
#include "rubberband/RubberBandStretcher.h"

namespace rec {
namespace audio {
namespace stretch {

using RubberBand::RubberBandStretcher;

static RubberBandStretcher* makeStretcher(const Stretch& stretch) {
  return new RubberBandStretcher(44100, stretch.channels(),
                                 RubberBandStretcher::OptionProcessRealTime,
                                 timeScale(stretch),
                                 pitchScale(stretch));
}

RubberbandStretchy::RubberbandStretchy(PositionableAudioSource* source,
                                       const Stretch& stretch)
    : Implementation(source) {
  setStretch(stretch);
}

RubberbandStretchy::~RubberbandStretchy() {}

void RubberbandStretchy::nextStretchedAudioBlock(
    const AudioSourceChannelInfo& info) {
}

void RubberbandStretchy::setStretch(const Stretch& stretch) {
  if (stretcher_) {
    stretcher_.reset(makeStretcher(stretch));
  } else {
    stretcher_->setTimeRatio(timeScale(stretch));
    stretcher_->setPitchScale(pitchScale(stretch));
  }
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
