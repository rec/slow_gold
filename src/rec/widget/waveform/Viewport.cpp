#include "rec/widget/waveform/Viewport.h"

#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/util/LoopPoint.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace widget {
namespace waveform {

void addLoopPointToViewport(const VirtualFile& file, SampleTime time) {
  Viewport vp = data::getProto<Viewport>(&file);
  LoopPointList *lpl = vp.mutable_loop_points();
  *lpl = audio::addLoopPoint(*lpl, time);
  data::setProto(vp, &file);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
