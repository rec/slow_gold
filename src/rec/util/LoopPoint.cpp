#include "rec/audio/Audio.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList& list,
                                       Samples<44100> length,
                                       double scale,
                                       bool emptyMeansAll) {
  block::BlockSet sel;
  int size = list.loop_point_size();
  if (size > 0) {
    for (int i = 0, j; i < size; ++i) {
      for (; i < size && !list.loop_point(i).selected(); ++i);
      for (j = i; j < size && list.loop_point(j).selected(); ++j);
      if (j != i && j < size) {
        RealTime begin = scale * list.loop_point(i).time();
        RealTime end = scale * list.loop_point(j).time();
        sel.insert(block::makeBlock(Samples<44100>(begin), Samples<44100>(end)));
      }
      i = j;
    }
  }
  if (emptyMeansAll && sel.empty())
    sel.insert(block::makeBlock(0, Samples<44100>(length)));
  return sel;
}

}  // namespace audio
}  // namespace rec
