#ifndef __REC_AUDIO_SOURCE_STRETCHYRUNNY__
#define __REC_AUDIO_SOURCE_STRETCHYRUNNY__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

class Runny;
class RunnyProto;
class StretchyProto;

Runny* makeStretchyRunny(PositionableAudioSource* source,
                         const StretchyProto& stretchyDesc,
                         const RunnyProto& runnyDesc,
                         int position);

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STRETCHYRUNNY__
