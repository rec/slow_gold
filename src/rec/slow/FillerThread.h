#ifndef __REC_SLOW_FILLERTHREAD__
#define __REC_SLOW_FILLERTHREAD__

#include "rec/util/Listener.h"
#include "rec/util/range/SampleRange.h"

namespace rec { namespace audio { namespace util { class BufferFiller; }}}
namespace rec { namespace audio { namespace util { class CurrentTimeBase; }}}

namespace rec {
namespace slow {

class FillerThread : public Thread, public Broadcaster<const SampleRange&> {
 public:
  FillerThread(audio::util::CurrentTimeBase* currentTime,
               audio::util::BufferFiller* bufferFiller)
      : Thread("Filler"),
        currentTime_(currentTime),
        bufferFiller_(bufferFiller) {
  }
  virtual ~FillerThread() {}
  virtual void run();

 private:
  void setFillPositionOrJump();

  audio::util::CurrentTimeBase* currentTime_;
  audio::util::BufferFiller* bufferFiller_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(FillerThread);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_FILLERTHREAD__
