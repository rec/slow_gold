#include "rec/audio/source/StretchyRunny.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/util/ShouldExit.h"

namespace rec {
namespace audio {
namespace source {

Runny* makeStretchyRunny(PositionableAudioSource* source,
                         const StretchyProto& stretchyDesc,
                         const RunnyProto& runnyDesc,
                         int position) {
  if (source) {
    ptr<Stretchy> stretchy(new Stretchy(source, stretchyDesc));
    ptr<Runny> runny(new Runny(stretchy.transfer(), runnyDesc));
    runny->setNextReadPosition(position);

    Thread* thread = Thread::getCurrentThread();
    while (!shouldExit(thread)) {
      if (runny->fill()) {
        if (shouldExit(thread))
          return NULL;

        runny->startThread();
        return runny.transfer();
      }
    }
  }

  return NULL;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
