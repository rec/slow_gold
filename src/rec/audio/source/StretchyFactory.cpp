#include "rec/audio/source/StretchyFactory.h"

namespace rec {
namespace audio {
namespace source {

Runny* newRunny(const Track& track) {
  AudioFormatReader* reader = widget::tree::createReader(track.file());
  Source* source = new juce::AudioFormatReaderSource(reader, true);
  Stretch* stretchy = new Stretchy(source);
  stretchy->setDescription(track.timestretch());

  return new Runny(track.runny(), stretchy));
}

Runny* filledRunny(const Track& track, Thread* thread) {
  scoped_ptr<Runny> runny;
  while (!(thread && thread->threadShouldExit())) {
    if (!runny)
      runny.reset(newRunny(track));

    else if (runny->fill())
      return runny.transfer();
  }
  return NULL;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
