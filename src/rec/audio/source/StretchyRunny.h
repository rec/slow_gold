#ifndef __REC_AUDIO_SOURCE_STRETCHYRUNNY__
#define __REC_AUDIO_SOURCE_STRETCHYRUNNY__

#include "rec/base/base.h"
#include "rec/audio/source/Stretchy.h"

namespace rec {
namespace audio {
namespace source {

class Runny;
class RunnyProto;

Runny* makeStretchyRunny(const RunnyProto& desc, const Stretch& stretch,
                         double timeRatio, int pos, PositionableAudioSource* s);

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STRETCHYRUNNY__
