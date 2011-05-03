#include "rec/gui/audio/LoopPoint.h"
#include "rec/gui/audio/LoopPoint.pb.h"

namespace rec {
namespace audio {

using namespace rec::gui::audio;

SampleSelection getTimeSelection(const gui::audio::LoopPointList& list,
                                 RealTime length, double scale) {
  SampleSelection selection;
  for (int i = 0, j, size = list.loop_point_size(); i < size; ) {
    for (; i < size && !list.selected(i); ++i);
    for (j = i; j < size && list.selected(j); ++j);
    if (j != i) {
      RealTime begin = scale * list.loop_point(i).time();
      RealTime end = scale * (j < size ? list.loop_point(j).time() : length);
      selection.insert(SampleRange(begin, end));
    }
  }
  return selection;
}


}  // namespace audio
}  // namespace rec
