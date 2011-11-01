#include "rec/audio/stretch/RubberBand.h"
#include "rec/audio/stretch/Stretch.h"
#include "rubberband/RubberBandStretcher.h"

namespace rec {
namespace audio {
namespace stretch {

using ::RubberBand::RubberBandStretcher;

static const int OPTIONS = RubberBandStretcher::OptionProcessRealTime;
static const int RATE = 44100;

RubberBand::RubberBand(PositionableAudioSource* source, const Stretch& stretch)
    : Implementation(source) {
  setStretch(stretch);
}

RubberBand::~RubberBand() {}

void RubberBand::nextStretchedAudioBlock(
    const AudioSourceChannelInfo& info) {
  for (int copied = 0; copied < info.numSamples; ) {
    if (size_t required = stretcher_->getSamplesRequired()) {
      float** samples = getSourceSamples(required);
      stretcher_->process(samples, required, false);
    }

    int available = stretcher_->available();
    if (!available) {
      LOG(ERROR) << "Failed to get any data from RubberBandStretcher";
      return;
    }
    int toCopy = std::min(info.numSamples - copied, available);
    int startSample = info.startSample + copied;
    float** samples = info.buffer->getArrayOfChannels();
    std::vector<float*> outSamples(channels_);

    for (int c = 0; c < channels_; ++c)
      outSamples[c] = samples[c] + startSample;
    if (int retrieved = stretcher_->retrieve(&outSamples.front(), toCopy)) {
      if (retrieved < toCopy) {
        LOG_FIRST_N(ERROR, 4) << "Didn't get as many samples as promised.";
      }
      copied += retrieved;
    } else {
      LOG(ERROR) << "Didn't get any samples at all";
      return;
    }
  }
}

void RubberBand::setStretch(const Stretch& stretch) {
  double time = timeScale(stretch);
  double pitch = pitchScale(stretch);
  channels_ = stretch.channels();
  if (stretcher_) {
    stretcher_.reset(new RubberBandStretcher(channels_, RATE, OPTIONS, 
                                             time, pitch));
  } else {
    stretcher_->setTimeRatio(time);
    stretcher_->setPitchScale(pitch);
  }
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
