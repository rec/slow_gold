#ifndef __REC_AUDIO_SOURCE_TIMER__
#define __REC_AUDIO_SOURCE_TIMER__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Listener.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/StateListener.h"

namespace rec {
namespace audio {
namespace source {

class Timer : public Wrappy {
 public:
  explicit Timer(PositionableAudioSource* s) : Wrappy(s), thread_(nullptr) {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
    Wrappy::getNextAudioBlock(i);
    if (thread_)
      thread_->notify();
  }

  virtual void setNextReadPosition(int64 time) {
    DCHECK_GE(time, 0);
    Wrappy::setNextReadPosition(time);
    if (thread_)
      thread_->notify();
  }

  void setThread(Thread* t) { thread_ = t; }

  void broadcastTime() {
    broadcastState<SampleTime>(getNextReadPosition());
  }

 private:
  Thread* thread_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Timer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_TIMER__
