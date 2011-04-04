#include "rec/audio/source/StretchyRunny.h"

#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Seggy.h"
#include "rec/audio/source/Stereo.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/ShouldExit.h"

using namespace rec::audio::stretch;

namespace rec {
namespace audio {
namespace source {

Runny* stretchyRunny(const RunnyProto& desc, const StretchLoop& loop,
                     int pos, PositionableAudioSource* s) {
  ptr<PositionableAudioSource> source(s);

  const Stretch& stretch = loop.stretch();
  static const double DELTA = 0.00001;
  double timeRatio = timeScale(stretch);
  if (!(stretch.passthrough_when_disabled() &&
        near(timeRatio, 1.0, DELTA) &&
        near(stretch::pitchScale(stretch), 1.0, DELTA))) {
    source.reset(new Stretchy(source.transfer(), stretch));
  }

  source.reset(new Stereo(source.transfer(), stretch.stereo()));

  if (loop.has_loop()) {
    // int len = s->getTotalLength();
    int begin = static_cast<int>(loop.loop().begin() * 44100);
    int end = static_cast<int>(loop.loop().end() * 44100);
    if (end < 0.001)
      end = s->getTotalLength();
    source.reset(new Seggy(SampleRange(begin, end), source.transfer()));
  }
  ptr<Runny> runny(new Runny(source.transfer(), desc));
	if (shouldExit(Thread::getCurrentThread()))
    return NULL;

  runny->setNextReadPosition(pos);

	if (shouldExit(Thread::getCurrentThread()))
    return NULL;
    
  runny->startThread();
  return runny.transfer();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
