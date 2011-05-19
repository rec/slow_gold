#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace audio {

block::BlockSet getTimeSelection(const LoopPointList& list,
                                 RealTime length, double scale,
                                 bool emptyMeansAll) {
  block::BlockSet sel;
  for (int i = 0, j, size = list.loop_point_size(); i < size; ) {
    for (; i < size && !list.selected(i); ++i);
    for (j = i; j < size && list.selected(j); ++j);
    if (j != i) {
      RealTime begin = scale * list.loop_point(i).time();
      RealTime end = scale * (j < size ? list.loop_point(j).time() : length);
      sel.insert(block::makeBlock(timeToSamples(begin), timeToSamples(end)));
    }
    i = j;
  }
  if (emptyMeansAll && sel.empty())
    sel.insert(block::makeBlock(0, timeToSamples(length)));
  return sel;
}


}  // namespace audio
}  // namespace rec