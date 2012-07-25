#ifndef __REC_GUI_AUDIO_LOOPPOINT__
#define __REC_GUI_AUDIO_LOOPPOINT__

#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/range/Range.h"

namespace rec {

namespace util {

typedef Range<SampleTime> SampleRange;
typedef SampleRange::Set SampleRangeSet;
typedef SampleRange::Vector SampleRangeVector;

}  // namespace util

namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList&,
                                       bool isSelected = true,
                                       bool allowEmpty = false);

const SampleRangeSet getTimeSelectionSet(const LoopPointList&,
                                        bool isSelected = true,
                                        bool allowEmpty = false);

const SampleRangeVector getTimeSelectionVector(const LoopPointList&,
                                              bool isSelected = true,
                                              bool allowEmpty = false);

bool isCloseTo(const LoopPointList&, SampleTime);

LoopPointList getSelected(const LoopPointList& loops, bool selected);
LoopPointList cutSelected(const LoopPointList& loops, bool selected);

LoopPointList addLoopPoints(const LoopPointList&, const LoopPointList&);
LoopPointList addLoopPoint(const LoopPointList&, SampleTime);

static const RealTime CLOSE_LOOPS = 0.05;

// inline RealTime closeLoopsTime() { return RealTime(0.05); }

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
