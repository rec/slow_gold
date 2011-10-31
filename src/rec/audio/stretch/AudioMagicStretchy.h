#ifndef __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__
#define __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__

#include "rec/audio/stretch/Stretchy.h"

namespace rec {
namespace audio {
namespace stretch {

Stretchy* createAudioMagicStretchy(
    Source* p, const Stretch& s = Stretch::default_instance());

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__
