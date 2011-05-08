#ifndef __REC_WIDGET_WAVEFORM_ZOOM__
#define __REC_WIDGET_WAVEFORM_ZOOM__

#include "rec/base/base.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace widget {
namespace waveform {

// The factor of k indicates how much wider or narrower the displayed area will
// be after the zoom.
ZoomProto zoom(const ZoomProto& z, RealTime length, RealTime time, double k);

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_ZOOM__
