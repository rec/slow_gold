#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/Range.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList&);

bool isCloseTo(const LoopPointList&, RealTime);

LoopPointList getSelected(const LoopPointList& loops, bool selected);
LoopPointList addLoopPoints(const LoopPointList&, const LoopPointList&);
LoopPointList addLoopPoint(const LoopPointList&, RealTime);

void sort(LoopPointList*);

void addLoopPointToEditable(const VirtualFile&, RealTime time);

int getSelectionCount(const LoopPointList&);

int getSegment(const LoopPointList&, RealTime);

void toggleSelectionSegment(LoopPointList*, RealTime);

Range<RealTime> contiguousSelectionContaining(const LoopPointList&, RealTime);

}  // namespace audio
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPPOINT__
