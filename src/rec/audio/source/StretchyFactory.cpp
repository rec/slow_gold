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


typedef rec::util::thread::Factory<Runny, const Track&> StretchyFactoryBase;

class StretchyFactory : public StretchyFactoryBase {
 public:
  StretchyFactory() {}

  virtual Runny* makeProduct(const Track& track) {
    if (threadShouldExit())
      return NULL;

    AudioFormatReader* reader = widget::tree::createReader(track.file());
    Source* source = new juce::AudioFormatReaderSource(reader, true);
    Stretch* stretchy = new Stretchy(source);
    stretchy->setDescription(track.timestretch());

    scoped_ptr<Runny> runny(new Runny(track.runny(), stretchy));
    do {
      if (threadShouldExit())
        return NULL;
    } while (!runny->fill());

    return runny.transfer();
  };

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(StretchyFactory);
};


#if 0
    trash_.empty();

  util::thread::Trash trash_;


  void signalThreadShouldExit() {
    Thread::signalThreadShouldExit();
    trash_.signalThreadShouldExit();
  }


  ChangeLocker<Description> changeLocker_;

#endif

}  // namespace source
}  // namespace audio
}  // namespace rec
