#include "rec/widget/waveform/Zoom.h"
#include "rec/data/Data.h"

namespace rec {
namespace widget {
namespace waveform {

static const int64 SMALLEST_TIME_SAMPLES = 4 * 44100;

ZoomProto zoom(const ZoomProto& z, Samples<44100> length, Samples<44100> t, double k) {
  DCHECK_LE(z.begin(), z.end());
  ZoomProto zoom(z);
  Samples<44100> b = zoom.begin();
  Samples<44100> e = zoom.end();
  if (!e)
    e = length;  // TODO:  delete these?

  if (k >= 1.0 || k * (e - b) >= SMALLEST_TIME_SAMPLES) {
    int64 begin = static_cast<int64>(k * b + (1.0 - k) * t);
    int64 end = static_cast<int64>(k * e + (1.0 - k) * t);
    DCHECK_LE(0, end) << k << ", " << b << ", " << e << ", " << z.ShortDebugString();
    zoom.set_begin(std::max(0LL, begin));
    zoom.set_end(std::min(static_cast<int64>(length), end));
    if (zoom.end() < 0) {
      LOG(DFATAL) << "Bad zoom: " << zoom.end();
      zoom.set_end(length);
    }
  }

  return zoom;
}

void zoom(const VirtualFile& f, Samples<44100> length, Samples<44100> time, double k) {
  data::set(zoom(data::get<ZoomProto>(f), length, time, k), f);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
