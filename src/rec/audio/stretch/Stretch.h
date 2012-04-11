#ifndef __REC_AUDIO_STRETCH_STRETCHY__
#define __REC_AUDIO_STRETCH_STRETCHY__

#include "rec/audio/stretch/Stretch.pb.h"

namespace rec {
namespace audio {
namespace stretch {

double timeScale(const Stretch&);
double pitchScale(const Stretch&);
double pitchSemitones(const Stretch&);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_STRETCHY__
