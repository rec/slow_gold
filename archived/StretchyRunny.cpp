#if 0
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

ThreadedSource* stretchyRunny(const RunnyProto& desc,
                              const StretchLoop& loop,
                              int pos, PositionableAudioSource* s) {
  // CHECK_GT(loop.loop().end(), 0.001);
  ptr<PositionableAudioSource> source(s);


  if (loop.has_loop()) {
    // int len = s->getTotalLength();
    int begin = static_cast<int>(timeToSamples(loop.loop().begin()));
    int end = static_cast<int>(timeToSamples(loop.loop().end()));
    if (end < 0.001)
      end = s->getTotalLength();
    source.reset(new Seggy(SampleRange(begin, end), source.transfer()));
  }

  ptr<ThreadedSource> runny(new Runny(source.transfer(), desc));
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
#endif
