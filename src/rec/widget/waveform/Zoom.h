#ifndef __REC_WIDGET_WAVEFORM_ZOOM__
#define __REC_WIDGET_WAVEFORM_ZOOM__

#include "rec/base/base.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace widget {
namespace waveform {

ZoomProto zoomIn(const ZoomProto& z, RealTime length, RealTime time);
ZoomProto zoomOut(const ZoomProto& z, RealTime length);

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_ZOOM__
