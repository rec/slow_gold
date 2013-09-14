#ifndef __REC_SLOW_FILLERTHREAD__
#define __REC_SLOW_FILLERTHREAD__

#include "rec/base/base.h"

namespace rec { namespace audio { namespace util { class BufferFiller; }}}

namespace rec {
namespace slow {

class CurrentTime;

class FillerThread : public Thread {
 public:
  FillerThread(CurrentTime* currentTime,
               audio::util::BufferFiller* bufferFiller)
      : Thread("Filler"),
        currentTime_(currentTime),
        bufferFiller_(bufferFiller) {
  }
  virtual ~FillerThread() {}
  virtual void run();

 private:
  void setFillPositionOrJump();

  CurrentTime* currentTime_;
  audio::util::BufferFiller* bufferFiller_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(FillerThread);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_FILLERTHREAD__
