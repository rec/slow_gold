#ifndef __REC_AUDIO_SOURCE_SNOOPY__
#define __REC_AUDIO_SOURCE_SNOOPY__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Listener.h"

namespace rec {
namespace audio {
namespace source {

class Snoopy : public Wrappy, public Broadcaster<const Info&> {
 public:
  Snoopy(PositionableAudioSource* source) : Wrappy(source) {}

  virtual void getNextAudioBlock(const Info& info) {
    Wrappy::getNextAudioBlock(info);
    broadcast(info);
  }

  static Snoopy* add(Source* source, Listener<const Info&> *listener) {
    ptr<Snoopy> s(new Snoopy(source));
    s->addListener(listener);
    return s.transfer();
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Snoopy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SNOOPY__
