#ifndef __REC_AUDIO_SOURCE_THREADEDSOURCE__
#define __REC_AUDIO_SOURCE_THREADEDSOURCE__

#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

class ThreadedSource : public Wrappy, public Thread {
 public:
  ThreadedSource(PositionableAudioSource* source, const String& name)
      : Wrappy(source), Thread(name) {
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ThreadedSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_THREADEDSOURCE__
