#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList&,
                                       Samples<44100> length,
                                       double scale = 1.0,
                                       bool emptyMeansAll = true);

bool isCloseTo(const LoopPointList&, RealTime);

LoopPointList getSelected(const LoopPointList& loops, bool selected);

LoopPointList addLoopPoints(const LoopPointList&, const LoopPointList&);

void sort(LoopPointList*);

}  // namespace audio
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPPOINT__
