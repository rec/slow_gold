#include "rec/audio/source/StretchyFactory.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/slow/Preferences.h"

using namespace rec::widget::pane;
typedef rec::slow::proto::Preferences Preferences;

namespace rec {
namespace audio {
namespace source {

Runny* newRunny(const Track& track) {
  AudioFormatReader* reader = widget::tree::createReader(track.file());
  Source* source = new juce::AudioFormatReaderSource(reader, true);
  Stretchy* stretchy = new Stretchy(source);
  stretchy->setDescription(track.timestretch());

  return new Runny(track.runny(), stretchy);
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

Runny* StretchyFactory::makeProduct(const Preferences& prefs) {
  if (threadShouldExit())
    return NULL;
  
  const Track& track = prefs.track();

  scoped_ptr<AudioFormatReader> reader(widget::tree::createReader(track.file()));
  if (!reader)
    return false;
  scoped_ptr<Source> source(new juce::AudioFormatReaderSource(reader.get(), true));
  scoped_ptr<Stretchy> stretchy(new Stretchy(source.transfer()));
  stretchy->setDescription(track.timestretch());

  scoped_ptr<Runny> runny(new Runny(track.runny(), stretchy.transfer()));
  do {
    if (threadShouldExit())
      return NULL;
  } while (!runny->fill());

  return runny.transfer();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
