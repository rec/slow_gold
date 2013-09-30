#ifndef __REC_SLOW_FILLERTHREAD__
#define __REC_SLOW_FILLERTHREAD__

#include "rec/util/range/SampleRange.h"

namespace rec {
namespace audio {
namespace util {

class BufferFiller;
class CurrentTimeBase;

class FillerThread : public Thread {
 public:
  FillerThread(CurrentTimeBase* currentTime, BufferFiller* bufferFiller)
      : Thread("Filler"),
        currentTime_(currentTime),
        bufferFiller_(bufferFiller) {
  }
  virtual ~FillerThread() {}
  virtual void run();

 private:
  void setFillPositionOrJump();

  CurrentTimeBase* currentTime_;
  BufferFiller* bufferFiller_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(FillerThread);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_SLOW_FILLERTHREAD__
