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

Stretchy::Stretchy(Source* s) : Wrappy(s), implementation_(new RubberBand(s)) {}

Stretchy::Stretchy(Source* s, const Stretchy& stretchy)
    : Wrappy(s),
      implementation_(new RubberBand(s, stretchy.implementation_->stretch())) {
}

Stretchy::~Stretchy() {}

int64 Stretchy::getTotalLength() const {
  return static_cast<int64>(source()->getTotalLength() *
                            implementation_->timeScale());
}

int64 Stretchy::getNextReadPosition() const {
  return static_cast<int64>(source()->getNextReadPosition() *
                            implementation_->timeScale());
}

void Stretchy::setNextReadPosition(int64 position) {
  double timeScale = implementation_->timeScale();
  source()->setNextReadPosition(static_cast<int64>(position / timeScale));
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

