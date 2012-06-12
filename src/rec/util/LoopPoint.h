#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/Range.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList&);

bool isCloseTo(const LoopPointList&, SampleTime);

LoopPointList getSelected(const LoopPointList& loops, bool selected);
LoopPointList cutSelected(const LoopPointList& loops, bool selected);

LoopPointList addLoopPoints(const LoopPointList&, const LoopPointList&);
LoopPointList addLoopPoint(const LoopPointList&, SampleTime);

inline SampleTime closeLoops() {
  return SampleTime(0.05);
}

void sort(LoopPointList*);

void addLoopPointToData(const VirtualFile&, SampleTime time);

int getSelectionCount(const LoopPointList&);

int getSegment(const LoopPointList&, SampleTime);

void toggleSelectionSegment(LoopPointList*, SampleTime);

Range<SampleTime > contiguousSelectionContaining(const LoopPointList&,
                                                 SampleTime);

}  // namespace audio
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPPOINT__
