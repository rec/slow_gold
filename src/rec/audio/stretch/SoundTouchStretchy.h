#ifndef __REC_AUDIO_STRETCH_SOUNDTOUCHSTRETCHY__
#define __REC_AUDIO_STRETCH_SOUNDTOUCHSTRETCHY__

#include "rec/audio/stretch/Stretchy.h"

namespace rec {
namespace audio {
namespace stretch {

Stretchy* createSoundTouchStretchy(Source* p, const Stretch& s);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_SOUNDTOUCHSTRETCHY__
