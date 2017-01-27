#include "rec/base/DropDead.h"
#include "rec/base/SampleRate.h"
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

#ifdef DEATH
static const int DEATH_OPTIONS =
  RubberBandStretcher::OptionPitchHighQuality |
  RubberBandStretcher::OptionProcessRealTime |
  RubberBandStretcher::OptionSmoothingOn |
  // RubberBandStretcher::OptionTransientsSmooth +
  0
;
#endif

static const double EPSILON = 1e-6;

RubberBand::RubberBand(Source* s, const StretchParameters& stretch)
    : Implementation(s, stretch),
      outputSampleRate_(0),
      timeScale_(0.0),
      pitchScale_(0.0) {
  doLog("RubberBand::RubberBand");
  CHECK_DDD(7134, 1893, int32, int16);
  doLog("RubberBand::RubberBand done");
}

RubberBand::~RubberBand() {}

bool RubberBand::canBypass() const {
  Lock l(lock_);
  return near(timeScale_, 1.0, EPSILON) && near(pitchScale_, 1.0, EPSILON);
}

void RubberBand::init() {
  doLog("RubberBand::init");
  stretchChanged();
  doLog("RubberBand::init done");
}

void RubberBand::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  if (!stretcher_) {
    LOG(ERROR) << "No stretcher!";
    Lock l(lock_);
    stretchChanged();
  }

  for (int copied = 0; copied < info.numSamples; ) {
    Lock l(lock_);
    if (int retrieved = retrieve(copied, info))
      copied += retrieved;
    else
      process();
  }
}

int RubberBand::retrieve(int copied, const AudioSourceChannelInfo& info) {
  int available = stretcher_->available();
  if (!available)
    return 0;

  float** out = info.buffer->getArrayOfWritePointers();
  int startSample = info.startSample + copied;

  vector<float*> output(2);
  for (int c = 0; c < 2; ++c)
    output[c] = out[c] + startSample;

  int samples = std::min(info.numSamples - copied, available);
  DCHECK(samples);

  int retrieved = stretcher_->retrieve(&output[0], samples);
  if (retrieved < samples) {
    LOG_FIRST_N(ERROR, 4) << "Not enough: " << retrieved << " vs " << samples;
  }
  return retrieved;
}

void RubberBand::process() {
  float** input;
  int required = stretcher_->getSamplesRequired();
  if (!required) {
    DLOG(ERROR) << "required nothing!";
    required = 512;
  }

  {
    ScopedUnlock m(lock_);
    input = getSourceSamples(required);
  }

  stretcher_->process(input, required, false);
}

void RubberBand::stretchChanged() {
  doLog("RubberBand::stretchChanged");
  double tr = timeScale();
  double ps = pitchScale();

  if (!stretcher_ || outputSampleRate_ != stretch_.output_sample_rate()) {
    outputSampleRate_ = stretch_.output_sample_rate();
    size_t rate = static_cast<size_t>(outputSampleRate_);
    DCHECK(rate);
    doLog(String("RubberBandStretcher::RubberBandStretcher ") +
          String(outputSampleRate_) +
          ", " + String(tr) + ", " + String(ps));
    stretcher_.reset(new RubberBandStretcher(rate, 2, OPTIONS, tr, ps));
    doLog("RubberBandStretcher::RubberBandStretcher done");

  } else if (near(tr, timeScale_, EPSILON) && near(ps, pitchScale_, EPSILON)) {
    return;

  } else {
    DCHECK_GT(tr, 0.00001);
    stretcher_->setTimeRatio(tr);
    stretcher_->setPitchScale(ps);
  }

  timeScale_ = tr;
  pitchScale_ = ps;
  doLog("RubberBand::stretchChanged done");
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
