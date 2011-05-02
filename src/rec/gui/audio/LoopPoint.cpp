#include "rec/gui/audio/LoopPoint.h"
#include "rec/gui/audio/LoopPoint.pb.h"

namespace rec {
namespace gui {
namespace audio {

SampleSelection getTimeSelection(const LoopPointList& list, double scale) {
  SampleSelection selection;
  for (int i = 0, j, size = list.loop_point_size(); i < size; ) {
    for (; i < size && !list.selected(i); ++i);
    for (j = i; j < size && list.selected(j); ++j);
    if (j != i) {
      SampleRange range(scale * list.loop_point(i).time(),
                        scale * list.loop_point(j).time());
      selection.insert(range);
    }
  }
  return selection;
}


}  // namespace audio
}  // namespace gui
}  // namespace rec
