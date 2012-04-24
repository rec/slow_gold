#ifndef __REC_AUDIO_UTIL_TIMEKEEPER__
#define __REC_AUDIO_UTIL_TIMEKEEPER__

#include "rec/util/Listener.h"

namespace rec {
namespace audio {
namespace util {

class TimeKeeper {
 public:
  TimeKeeper();
  virtual ~TimeKeeper() {}

  void setSelection(const LoopPointList& s) {
    Lock l(lock_);
    selection_ = s;
    onSelection();
  }

  void requestTime(Samples<44100> t) {
    Lock l(lock_);
    requestedTime_ = t;
    onRequestTime();
  }

  void setTime(Samples<44100> t) {
    Lock l(lock_);
    time_ = t;
    onTime();
  }

  const LoopPointList selection() const { Lock l(lock_); return selection_; }

  Samples<44100> length() const { Lock l(lock_); return selection_.length(); }
  Samples<44100> time() const { Lock l(lock_); return time_; }
  Samples<44100> requestedTime() const { Lock l(lock_); return requestedTime_; }

 protected:
  virtual void onSelection() = 0;
  virtual void onRequestTime() = 0;
  virtual void onTime() = 0;

  CriticalSection lock_;
  Samples<44100> time_, requestedTime_;
  LoopPointList selection_;
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_TIMEKEEPER__
