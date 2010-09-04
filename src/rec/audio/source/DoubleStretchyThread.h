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
                       PositionableAudioSource* s0, PositionableAudioSource* s1)
      : DoubleStretchy(d, s0, s1),
        Thread("DoubleStretchy"),
        waitTime_(d.inactive_wait_time()) {
    setPriority(d.thread_priority());
    startThread();
  }

  void run() {
    while (!threadShouldExit()) {
      if (!(this->fillNext() || threadShouldExit()))
        wait(waitTime_);
    }
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
