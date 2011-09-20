#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace audio {

const SampleSelection getTimeSelection(const LoopPointList& list,
                                       double scale,
                                       bool emptyMeansAll) {
  SampleSelection sel;
  int size = list.loop_point_size() - 1;
  if (size > 0) {
    for (int i = 0, j; i < size; ++i) {
      for (; i < size && !list.loop_point(i).selected(); ++i);
      for (j = i; j < size && list.loop_point(j).selected(); ++j);
      if (j != i) {
        RealTime begin = scale * list.loop_point(i).time();
        RealTime end = scale * list.loop_point(j).time();
        sel.insert(block::makeBlock(SamplePosition(begin), SamplePosition(end)));
      }
      i = j;
    }
    if (emptyMeansAll && sel.empty())
      sel.insert(block::makeBlock(0, SamplePosition(list.loop_point(size).time())));
  }
  return sel;
}

}  // namespace audio
}  // namespace rec
