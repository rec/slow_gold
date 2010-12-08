#ifndef __REC_AUDIO_SOURCE_STRETCHYFACTORY__
#define __REC_AUDIO_SOURCE_STRETCHYFACTORY__

#include "rec/audio/source/StretchyFactory.h"

#include "rec/util/thread/Factory.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/widget/Panes.h"
#include "rec/slow/Preferences.h"

namespace rec {
namespace audio {
namespace source {

class Runny;

Runny* filledRunny(const widget::pane::Track& track, int position);

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STRETCHYFACTORY__
