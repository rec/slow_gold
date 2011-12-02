#include "rec/widget/waveform/Zoom.h"
#include "rec/data/Data.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

static const int64 SMALLEST_TIME_SAMPLES = 100 * 441;
static const double POWER = 4.0;
static const double ZOOM_INCREMENT = 0.3;

double zoomFunction(double increment) {
  return pow(POWER, -increment);
}

ZoomProto zoom(const ZoomProto& z, Samples<44100> length, Samples<44100> t, double k) {
  k = zoomFunction(k * ZOOM_INCREMENT);
  DCHECK_LE(z.begin(), z.end());
  ZoomProto zoom(z);
  Samples<44100> b = zoom.begin();
  Samples<44100> e = zoom.has_end() ? zoom.end() : length.get();

  if (k >= 1.0 || k * (e - b) >= SMALLEST_TIME_SAMPLES) {
    int64 begin = static_cast<int64>(k * b + (1.0 - k) * t);
    int64 end = static_cast<int64>(k * e + (1.0 - k) * t);
    DCHECK_LE(0, end) << k << ", "
                      << b << ", "
                      << e << ", " << z.ShortDebugString();
    zoom.set_begin(std::max(0LL, begin));
    zoom.set_end(std::min(static_cast<int64>(length), end));
    if (zoom.end() < 0) {
      LOG(DFATAL) << "Bad zoom: " << zoom.end();
      zoom.set_end(length);
    }
  }

  return zoom;
}

ZoomProto zoom(const ZoomProto& z, Samples<44100> length, double k) {
  return zoom(z, length, (z.begin() + z.end()) / 2, k);
}

}  // namespace

void zoom(const VirtualFile& f, Samples<44100> length, Samples<44100> time, double k) {
  data::set(zoom(data::get<ZoomProto>(f), length, time, k), f);
}

void zoom(const VirtualFile& f, Samples<44100> length, double k) {
  data::set(zoom(data::get<ZoomProto>(f), length, k), f);
}


}  // namespace waveform
}  // namespace widget
}  // namespace rec
