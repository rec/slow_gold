#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/Range.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList&);

bool isCloseTo(const LoopPointList&, Samples<44100>);

LoopPointList getSelected(const LoopPointList& loops, bool selected);
LoopPointList cutSelected(const LoopPointList& loops, bool selected);

LoopPointList addLoopPoints(const LoopPointList&, const LoopPointList&);
LoopPointList addLoopPoint(const LoopPointList&, Samples<44100>);



void sort(LoopPointList*);

void addLoopPointToData(const VirtualFile&, Samples<44100> time);

int getSelectionCount(const LoopPointList&);

int getSegment(const LoopPointList&, Samples<44100>);

void toggleSelectionSegment(LoopPointList*, Samples<44100>);

Range<Samples<44100> > contiguousSelectionContaining(const LoopPointList&,
                                                     Samples<44100>);

}  // namespace audio
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPPOINT__
