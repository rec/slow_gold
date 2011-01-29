#ifndef __REC_AUDIO_STRETCH_STRETCHY__
#define __REC_AUDIO_STRETCH_STRETCHY__

#include "rec/audio/stretch/Stretch.pb.h"

namespace rec {
namespace audio {
namespace stretch {

double timeScale(const Stretch& d);
double pitchScale(const Stretch& d);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_STRETCHY__
