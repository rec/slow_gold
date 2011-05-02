#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/util/Range.h"
#include "rec/audio/Audio.h"

namespace rec {

namespace gui { namespace audio { class LoopPointList; }}


namespace audio {

SampleSelection getTimeSelection(const gui::audio::LoopPointList&, RealTime length,
                                 double scale = 1.0);

}  // namespace audio
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPPOINT__
