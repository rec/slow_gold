#ifndef __REC_UTIL_LISTENER_TIME__
#define __REC_UTIL_LISTENER_TIME__

#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace util {
namespace listener {

class Time : public Listener<int>,
             public Listener<float>,
             public ChangeListener {
 public:
  Time(float sr = 44100f0) : sampleRate_(sr) {}

  virtual void operator()(float time) = 0;
  virtual void operator()(int time) { (*this)(time / sampleRate_); }

  virtual void changeListenerCallback(ChangeBroadcaster* x) {
    (*this)(((PositionableAudioSource*) x)->getNextReadPosition());
  }

 private:
  const float sampleRate_;
  DISALLOW_COPY_AND_ASSIGN(Time);
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_TIME__
