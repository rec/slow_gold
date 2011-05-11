#ifndef __REC_AUDIO_SOURCE_TIMER__
#define __REC_AUDIO_SOURCE_TIMER__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

class Timer : public Wrappy, public Broadcaster<SampleTime> {
 public:
  explicit Timer(PositionableAudioSource* s = NULL) : Wrappy(s) {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
    Wrappy::getNextAudioBlock(i);
    broadcast(position_);
  }

  virtual void setNextReadPosition(SampleTime time) {
    Wrappy::setNextReadPosition(time);
    broadcast(time);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Timer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_TIMER__
