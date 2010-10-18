#ifndef __REC_AUDIO_SOURCE_DOUBLESTRETCHYTHREAD__
#define __REC_AUDIO_SOURCE_DOUBLESTRETCHYTHREAD__

#include "rec/audio/source/DoubleStretchy.h"

namespace rec {
namespace audio {
namespace source {

class DoubleStretchyThread : public DoubleStretchy, Thread {
 public:
  DoubleStretchyThread(Source* s0, Source* s1)
    : DoubleStretchy(s0, s1), Thread("DoubleStretchy") {
  }

  virtual void setDescription(const TimeStretch& description) {
    DoubleStretchy::setDescription(description);
    waitTime_ = description.inactive_wait_time();
    setPriority(description.thread_priority());
    if (isThreadRunning())
      notify();
    else
      startThread();
  }

  virtual void run() {
    while (!threadShouldExit()) {
      if (!(fillNext() || threadShouldExit()))
        wait(waitTime_);
    }
  }

  void stop() {
    signalThreadShouldExit();
    notify();
  }

  juce_UseDebuggingNewOperator

 private:
  int waitTime_;

  DISALLOW_COPY_AND_ASSIGN(DoubleStretchyThread);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLESTRETCHYTHREAD__
