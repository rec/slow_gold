#include "rec/audio/SampleRate.h"
#include "rec/audio/stretch/RubberBand.h"
#include "rec/util/Math.h"

#include "rubberband/RubberBandStretcher.h"

namespace rec {
namespace audio {
namespace stretch {

static const int OPTIONS =
  RubberBandStretcher::OptionPitchHighQuality +
  RubberBandStretcher::OptionProcessRealTime +
  // RubberBandStretcher::OptionSmoothingOn +
  RubberBandStretcher::OptionTransientsSmooth +
  0
;

static const int DEATH_OPTIONS =
  RubberBandStretcher::OptionPitchHighQuality |
  RubberBandStretcher::OptionProcessRealTime |
  RubberBandStretcher::OptionSmoothingOn |
  // RubberBandStretcher::OptionTransientsSmooth +
  0
;

RubberBand::RubberBand(PositionableAudioSource* source, const Stretch& stretch)
    : Implementation(source), detuneCents_(0.0) {
  sampleRate_ = audio::getSampleRate();
  setStretch(stretch);
  CHECK_DDD(7134, 1893, int32, int16);
}

RubberBand::~RubberBand() {}

void RubberBand::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  DLOG(INFO) << "RubberBand::getNextAudioBlock " << info.numSamples;
  if (!stretcher_) {
    LOG(ERROR) << "No stretcher!";
    Lock l(lock_);
    stretchChanged();
  }

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
      if (size_t required = stretcher_->getSamplesRequired())
        chunkSize = required;

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
  DLOG(INFO) << stretch_.ShortDebugString();
  stretch_ = stretch;
  stretchChanged();
}

void RubberBand::stretchChanged() {
  channels_ = stretch_.channels();
  double tr = timeScale(stretch_);
  double ps = pitchScale(stretch_, detuneCents_);

  if (!stretcher_) {
    DLOG(INFO) << "new stretcher";
    stretcher_.reset(new RubberBandStretcher(sampleRate_, channels_,
                                             OPTIONS, tr, ps));
    chunkSize_ = stretch_.chunk_size();
    maxProcessSize_ = stretch_.max_process_size();
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

void RubberBand::setMasterTune(double detune) {
  Lock l(lock_);
  if (!near(detuneCents_, detune, EPSILON)) {
    detuneCents_ = detune;
    stretchChanged();
  }
}

void RubberBand::setSampleRate(int sampleRate) {
  Lock l(lock_);
  if (sampleRate != sampleRate_) {
    sampleRate_ = sampleRate;
    stretcher_.reset();
    stretchChanged();
  }
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
