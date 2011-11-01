#include "rec/audio/stretch/RubberBand.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/util/Math.h"

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

void RubberBand::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  for (int copied = 0; copied < info.numSamples; ) {
    Lock l(lock_);
    if (size_t samples = stretcher_->getSamplesRequired()) {
      float** input;
      {
        ScopedUnlock m(lock_);
        input = getSourceSamples(samples);
      }
      stretcher_->process(input, samples, false);
    }
    int available = stretcher_->available();
    if (!available) {
      DLOG(ERROR) << "No samples available!";
      return;
    }

    std::vector<float*> output(channels_);

    float** out = info.buffer->getArrayOfChannels();
    int startSample = info.startSample + copied;

    for (int c = 0; c < channels_; ++c)
      output[c] = out[c] + startSample;

    int samples = std::min(info.numSamples - copied, available);
    int retrieved = stretcher_->retrieve(&output[0], samples);
    copied += retrieved;
    if (retrieved < samples) {
      if (!retrieved) {
        LOG(ERROR) << "No samples after a promise!";
        return;
      }
      LOG(ERROR) << "Not as many samples as promised: " << retrieved;
    }
  }
}

static const double EPSILON = 1e-6;

void RubberBand::setStretch(const Stretch& stretch) {
  Lock l(lock_);

  channels_ = stretch.channels();
  double tr = timeScale(stretch);
  double ps = pitchScale(stretch);

  if (!stretcher_) {
    stretcher_.reset(new RubberBandStretcher(RATE, channels_, OPTIONS, tr, ps));
  } else if (near(tr, timeRatio_, EPSILON) && near(ps, pitchScale_, EPSILON)) {
    return;
  } else {
    stretcher_->setTimeRatio(tr);
    stretcher_->setPitchScale(ps);
  }
  timeRatio_ = tr;
  pitchScale_ = ps;
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#if 0
void RubberBand::getNextAudioBlock(
    const AudioSourceChannelInfo& info) {
  for (int copied = 0, fail = 0; copied < info.numSamples; ) {
    if (size_t samples = stretcher_->getSamplesRequired()) {
      LOG_FIRST_N(INFO, 8) << "Required " << samples;
      float** input = getSourceSamples(samples);
      stretcher_->process(input, samples, false);
    } else {
      LOG_FIRST_N(INFO, 8) << "No data required!";
    }

    int available = stretcher_->available();
    if (available) {
      DLOG(INFO) << "There is data available: " << available;
      fail = 0;
    } else if (fail++ <= 4) {
      LOG_FIRST_N(ERROR, 32) << "Failure " << fail;
    	continue;
    } else {
      LOG_FIRST_N(ERROR, 8) << "Failed to get any data from RubberBandStretcher";
      return;
    }
    int samples = std::min(info.numSamples - copied, available);
    int startSample = info.startSample + copied;
    float** out = info.buffer->getArrayOfChannels();
    std::vector<float*> output(channels_);

    for (int c = 0; c < channels_; ++c)
      output[c] = out[c] + startSample;

    if (int retrieved = stretcher_->retrieve(&output[0], samples)) {
      if (retrieved < samples) {
        LOG_FIRST_N(ERROR, 8) << "Didn't get as many samples as promised:"
                              << retrieved;
      } else {
        LOG_FIRST_N(ERROR, 8) << "Got all " << samples << " samples.";
      }
      copied += retrieved;
    } else {
      LOG_FIRST_N(ERROR, 8) << "Didn't get any samples at all";
      return;
    }
  }
}

#endif

