#include "rec/audio/source/StretchyRunny.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/ShouldExit.h"

namespace rec {
namespace audio {
namespace source {

Runny* makeStretchyRunny(const RunnyProto& desc, const Stretch& stretch,
                         double timeRatio, int pos, PositionableAudioSource* s) {
  ptr<PositionableAudioSource> source(s);
  static const double DELTA = 0.00001;
  if (!(stretch.passthrough_when_disabled() &&
        near(timeRatio, 1.0, DELTA) &&
        near(stretch::pitchScale(stretch), 1.0, DELTA))) {
    source.reset(new Stretchy(source.transfer(), stretch));
  }

  ptr<Runny> runny(new Runny(source.transfer(), desc));
  runny->setNextReadPosition(pos);

  Thread* thread = Thread::getCurrentThread();
  while (!(shouldExit(thread) || runny->isFull()))
    runny->fill();

  if (shouldExit(thread))
    return NULL;

  runny->startThread();
  return runny.transfer();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
