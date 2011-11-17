#ifndef __REC_AUDIO_SOURCE_SNOOPY__
#define __REC_AUDIO_SOURCE_SNOOPY__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Listener.h"

namespace rec {
namespace audio {
namespace source {

class Snoopy : public Wrappy,
               public listener::Broadcaster<const AudioSourceChannelInfo&> {
 public:
  Snoopy(PositionableAudioSource* source) : Wrappy(source) {}

  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
    Wrappy::getNextAudioBlock(info);
    broadcast(info);
  }

  static
  Snoopy* add(PositionableAudioSource* source,
              listener::Listener<const AudioSourceChannelInfo&> *listener) {
    ptr<Snoopy> s(new Snoopy(source));
    s->addListener(listener);
    return s.transfer();
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Snoopy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SNOOPY__
