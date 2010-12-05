#ifndef __REC_WIDGET_PANES__
#define __REC_WIDGET_PANES__

#include "rec/base/base.h"
#include "rec/widget/Panes.pb.h"
#include "rec/widget/VolumeFile.h"

namespace rec {
namespace widget {
namespace pane {

inline bool operator==(const Track& x, const Track& y) {
  const TimeStretch& sx = x.timestretch();
  const TimeStretch& sy = y.timestretch();
  return x.volume() == y.volume()
    && x.sample_rate() == y.sample_rate()
    && x.channels() == y.channels()
    && x.pitch_scale() == y.pitch_scale();
 }
}

}  // namespace pane
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_PANES__
