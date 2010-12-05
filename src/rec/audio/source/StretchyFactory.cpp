#include "rec/audio/source/StretchyFactory.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Stretchy.h"

using namespace rec::widget::pane;

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


typedef rec::util::thread::Factory<Runny, const Track&> StretchyFactoryBase;

class StretchyFactory : public StretchyFactoryBase {
 public:
  StretchyFactory(Thread *thread = NULL) : thread_(thread) {}

  bool threadShouldExit() const { return thread_ && thread_->threadShouldExit(); }

  virtual Runny* makeProduct(const Track& track) {
    if (threadShouldExit())
      return NULL;

    AudioFormatReader* reader = widget::tree::createReader(track.file());
    Source* source = new juce::AudioFormatReaderSource(reader, true);
    Stretchy* stretchy = new Stretchy(source);
    stretchy->setDescription(track.timestretch());

    scoped_ptr<Runny> runny(new Runny(track.runny(), stretchy));
    do {
      if (threadShouldExit())
        return NULL;
    } while (!runny->fill());

    return runny.transfer();
  };

 private:
  Thread* thread_;
  DISALLOW_COPY_AND_ASSIGN(StretchyFactory);
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
