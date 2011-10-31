#include "rec/audio/stretch/RubberBand.h"
#include "rec/audio/stretch/Stretch.h"
#include "rubberband/RubberBandStretcher.h"

namespace rec {
namespace audio {
namespace stretch {

using ::RubberBand::RubberBandStretcher;

static RubberBandStretcher* makeStretcher(const Stretch& stretch) {
  return new RubberBandStretcher(44100, stretch.channels(),
                                 RubberBandStretcher::OptionProcessRealTime,
                                 timeScale(stretch),
                                 pitchScale(stretch));
}

RubberBand::RubberBand(PositionableAudioSource* source, const Stretch& stretch)
    : Implementation(source) {
  setStretch(stretch);
}

RubberBand::~RubberBand() {}

void RubberBand::nextStretchedAudioBlock(
    const AudioSourceChannelInfo& info) {

}

void RubberBand::setStretch(const Stretch& stretch) {
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
