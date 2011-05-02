#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/util/Range.h"

namespace rec {
namespace gui {
namespace audio {

class LoopPointList;

SampleSelection getTimeSelection(const LoopPointList&, RealTime length,
                                 double scale = 1.0);

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPPOINT__
