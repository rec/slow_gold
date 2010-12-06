#ifndef __REC_WIDGET_PANES__
#define __REC_WIDGET_PANES__

#include "rec/base/base.h"
#include "rec/widget/Panes.pb.h"
#include "rec/widget/tree/VolumeFile.h"

using rec::audio::source::TimeStretch;

namespace rec {
namespace widget {
namespace pane {

inline bool operator==(const Track& x, const Track& y) {
  const TimeStretch& sx = x.timestretch();
  const TimeStretch& sy = y.timestretch();
  return x.file() == y.file()
    && sx.sample_rate() == sy.sample_rate()
    && sx.channels() == sy.channels()
    && sx.pitch_scale() == sy.pitch_scale();
}

inline bool operator!=(const Track& x, const Track& y) {
  return !(x == y);
}

}  // namespace pane
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_PANES__
