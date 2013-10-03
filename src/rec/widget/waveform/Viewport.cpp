#include "rec/widget/waveform/Viewport.h"

#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/util/LoopPoint.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace widget {
namespace waveform {

void addLoopPointToViewport(const VirtualFile& file, SampleTime time) {
  Viewport vp = data::getProto<Viewport>(file);
  LoopPointList *lpl = vp.mutable_loop_points();
  *lpl = audio::addLoopPoint(*lpl, time);
  data::setProto(vp, file);
}

double selectionInZoom(const Viewport& vp) {
  auto& lp = vp.loop_points();
  static const int NO_SEGMENT = -1;
  SampleTime begin = NO_SEGMENT, end;
  for (int i = 0; i < lp.loop_point_size(); ++i) {
    auto& point = lp.loop_point(i);
    if (point.selected()) {
      if (begin == NO_SEGMENT)
        begin = point.time();
      if (i < lp.loop_point_size() - 1)
        end = lp.loop_point(i + 1).time();
      else
        end = lp.length();
    }
  }

  if (begin == NO_SEGMENT) {
    begin = 0;
    end = lp.length();
  }

  auto& zoom = vp.zoom();

  if (begin < zoom.begin() || end > zoom.end())
    return 2.0;

  return (1.0 * (end - begin)) / (zoom.end() - zoom.begin());
}


}  // namespace waveform
}  // namespace widget
}  // namespace rec
