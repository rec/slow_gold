#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHYTHREAD__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHYTHREAD__

#include "rec/audio/source/DoubleStretchy.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchyThread : public DoubleStretchy, Thread {
 public:
  typedef rec::audio::timescaler::Description Description;

  DoubleStretchyThread(const Description& d,
                       Source* s0, Source* s1)
      : DoubleStretchy(d, s0, s1),
        Thread("DoubleStretchy"),
        waitTime_(d.inactive_wait_time()) {
    setPriority(d.thread_priority());
    startThread();
  }

  virtual void setDescription(const Description& description) {
    DoubleStretchy::setDescription(description);
    notify();
  }

  virtual void run() {
    while (!threadShouldExit()) {
      LOG_IF(ERROR, false) << "stretching";
      if (!(this->fillNext() || threadShouldExit()))
        wait(waitTime_);
    }
    LOG_IF(ERROR, false) << "exiting";
  }

  void stop() {
    signalThreadShouldExit();
    notify();
  }

 private:
  int waitTime_;
  DISALLOW_COPY_AND_ASSIGN(DoubleStretchyThread);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHYTHREAD__
