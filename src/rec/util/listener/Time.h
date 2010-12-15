#ifndef __REC_UTIL_LISTENER_TIME__
#define __REC_UTIL_LISTENER_TIME__

#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace util {
namespace listener {

class Time : public Listener<int>, public Listener<float> {
 public:
  TimeListener(float sr = 44100f) : sampleRate_(sr) {}

  virtual void operator()(int time) { (*this)(time / sampleRate_); }

 private:
  const float sampleRate_;
  DISALLOW_COPY_AND_ASSIGN(Time);
};

class TimeChangeListener : public ChangeListener, public Time {
 public:
  explicit TimeBroadcaster(float sr = 44100f) : Time(sr) {}
  virtual void changeListenerCallback(ChangeBroadcaster* x) {
    (*this)(((PositionableAudioSource*) x)->getNextReadPosition());
  }

 private:
  const float sampleRate_;

  DISALLOW_COPY_AND_ASSIGN(TimeBroadcaster);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_TIME__
