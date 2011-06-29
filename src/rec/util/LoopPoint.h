#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/util/block/Block.h"
#include "rec/audio/Audio.h"

namespace rec {
namespace util {

class LoopPointList;
typedef block::BlockSet SampleSelection;

}

namespace audio {

const SampleSelection getTimeSelection(const LoopPointList&,
                                       RealTime length,
                                       double scale = 1.0,
                                       bool emptyMeansAll = true);

}  // namespace audio
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPPOINT__
