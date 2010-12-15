#include "rec/audio/source/StretchyFactory.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/slow/Preferences.h"

using namespace rec::widget::pane;
using namespace rec::widget::tree;
typedef rec::slow::proto::Preferences Preferences;

namespace rec {
namespace audio {
namespace source {

Stretchy* createStretchyReader(const TimeStretch& ts, AudioFormatReader* r) {
  return r ? new Stretchy(ts, new AudioFormatReaderSource(r, true)) : NULL;
}

Stretchy* createStretchyReader(const Track& track) {
  return createStretchyReader(track.timestretch(), createReader(track.file()));
}

Runny* createStretchyRunny(const Track& track) {
  return new Runny(track.runny(), createStretchyReader(track));
}

Runny* fillRunny(Runny* r, int position) {
  scoped_ptr<Runny> runny(r);
  if (runny) {
    runny->setNextReadPosition(position);

    Thread* thread = Thread::getCurrentThread();
    while (!(thread && thread->threadShouldExit())) {
      if (runny->fill()) {
        runny->startThread();
        return runny->transfer();
      }
    }
  }
  return NULL;
}

Runny* filledRunny(const Track& track, int position) {
  return fillRunny(createStretchyRunny(track), position);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
