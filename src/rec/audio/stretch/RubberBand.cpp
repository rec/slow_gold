#include "rec/audio/stretch/RubberBand.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/util/Math.h"

#include "rubberband/RubberBandStretcher.h"

namespace rec {
namespace audio {
namespace stretch {

using ::RubberBand::RubberBandStretcher;

static const int OPTIONS =
  RubberBandStretcher::OptionPitchHighQuality +
  RubberBandStretcher::OptionProcessRealTime +
  RubberBandStretcher::OptionSmoothingOn +
  RubberBandStretcher::OptionTransientsSmooth
;
static const int RATE = 44100;

RubberBand::RubberBand(PositionableAudioSource* source, const Stretch& stretch)
    : Implementation(source) {
  setStretch(stretch);
}

RubberBand::~RubberBand() {}

void RubberBand::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  for (int copied = 0; copied < info.numSamples; ) {
    Lock l(lock_);
    if (int available = stretcher_->available()) {
      float** out = info.buffer->getArrayOfChannels();
      int startSample = info.startSample + copied;

      std::vector<float*> output(channels_);
      for (int c = 0; c < channels_; ++c)
        output[c] = out[c] + startSample;

      int samples = std::min(info.numSamples - copied, available);
      DCHECK(samples);

      int retrieved = stretcher_->retrieve(&output[0], samples);
      copied += retrieved;
      if (retrieved < samples) {
        if (!retrieved) {
          LOG_FIRST_N(ERROR, 4) << "No samples after promising " << samples;
          return;
        } else {
          LOG_FIRST_N(ERROR, 4) << "Not as many samples as promised: "
                                << retrieved << " vs " << samples;
        }
      }
    } else {
      float** input;
      int chunkSize = chunkSize_;
      // if (size_t required = stretcher_->getSamplesRequired())
      //   chunkSize = required;
      {
        ScopedUnlock m(lock_);
        input = getSourceSamples(chunkSize);
      }
      stretcher_->process(input, chunkSize, false);
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
    chunkSize_ = stretch.chunk_size();
    maxProcessSize_ = stretch.max_process_size();
    stretcher_->setMaxProcessSize(maxProcessSize_);

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
