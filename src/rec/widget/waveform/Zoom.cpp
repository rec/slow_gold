#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace widget {
namespace waveform {

ZoomProto zoom(const ZoomProto& z, RealTime length, RealTime t, double k) {
  ZoomProto zoom(z);
  RealTime b = zoom.begin();
  RealTime e = zoom.end();
  if (!e)
    e = length;  // TODO:  delete these?

  if (k >= 1.0 || k * (e - b) >= SMALLEST_TIME) {
    zoom.set_begin(std::max(0.0, k * b + (1.0 - k) * t));
    zoom.set_end(std::min(length, k * e + (1.0 - k) * t));
    if (zoom.end() < 0) {
      LOG(ERROR) << "Bad zoom: " << zoom.end();
      zoom.set_end(length);
    }
  }

  return zoom;
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
