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

Runny* filledRunny(const Track& track, int position) {
  scoped_ptr<AudioFormatReader> reader(createReader(track.file()));
  if (!reader)
    return NULL;
  
  scoped_ptr<Source> source(
      new AudioFormatReaderSource(reader.transfer(), true));

  scoped_ptr<Stretchy> stretchy(
      new Stretchy(track.timestretch(), source.transfer()));

  scoped_ptr<Runny> runny(
      new Runny(track.runny(), stretchy.transfer()));
  runny->setNextReadPosition(position);

  Thread* thread = Thread::getCurrentThread();
  while (!(thread && thread->threadShouldExit())) {
    if (runny->fill()) {
      runny->startThread();
      return runny.transfer();
    }
  }
  return NULL;
}


}  // namespace source
}  // namespace audio
}  // namespace rec
