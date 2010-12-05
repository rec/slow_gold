#ifndef __REC_AUDIO_SOURCE_STRETCHYFACTORY__
#define __REC_AUDIO_SOURCE_STRETCHYFACTORY__

#include "rec/base/base.h"
#include "rec/util/thread/Factory.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/widget/Panes.h"

namespace rec {
namespace audio {
namespace source {

Runny* newRunny(const widget::pane::Track& track);
Runny* filledRunny(const Track& track, widget::pane::Thread* thread);

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_STRETCHYFACTORY__
