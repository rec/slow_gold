#include "rec/audio/stretch/Stretchy.h"

#include "rec/base/SampleRate.h"
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

Stretchy::Stretchy(Source* s, const Stretchy& stretchy)
    : Wrappy(s),
      implementation_(new RubberBand(s, stretchy.implementation_->stretch())) {
}

Stretchy::Stretchy(Source* s) : Wrappy(s) {}

void Stretchy::init(SampleRate sampleRate) {
  StretchParameters stretch;
  stretch.set_output_sample_rate(sampleRate);
  implementation_.reset(new RubberBand(source_.get(), stretch));
  implementation_->init();
}

Stretchy::~Stretchy() {}

double Stretchy::timeScale() const {
  double ts = implementation_->timeScale();
  DCHECK_GE(fabs(ts), 0.001);
  return ts;
}

int64 Stretchy::getTotalLength() const {
  return static_cast<int64>(source()->getTotalLength() * timeScale());
}

int64 Stretchy::getNextReadPosition() const {
  return static_cast<int64>(source()->getNextReadPosition() * timeScale());
}

void Stretchy::setNextReadPosition(int64 position) {
  source()->setNextReadPosition(static_cast<int64>(position / timeScale()));
}

void Stretchy::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  if (implementation_->canBypass())
    Wrappy::getNextAudioBlock(info);
  else
    implementation_->getNextAudioBlock(info);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

