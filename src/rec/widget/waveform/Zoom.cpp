#include "rec/widget/waveform/Zoom.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

static const int64 SMALLEST_TIME_SAMPLES = 8 * 44100;
static const double POWER = 4.0;
static const double ZOOM_INCREMENT = 0.3;

double zoomFunction(double increment) {
  return pow(POWER, -increment);
}

ZoomProto zoom(const ZoomProto& z, Samples<44100> length, Samples<44100> t, double k) {
  k = zoomFunction(k * ZOOM_INCREMENT);
  // DCHECK_LE(z.begin(), z.end());
  ZoomProto zoom(z);
  Samples<44100> b = zoom.begin();
  Samples<44100> e = zoom.has_end() ? zoom.end() : length.get();

  if (k >= 1.0 || k * (e - b) >= SMALLEST_TIME_SAMPLES) {
    int64 begin = static_cast<int64>(k * b + (1.0 - k) * t);
    int64 end = static_cast<int64>(k * e + (1.0 - k) * t);
    //DCHECK_LE(0, end) << k << ", "
    //                  << b << ", "
    //                  << e << ", " << z.ShortDebugString();
    zoom.set_begin(std::max(0LL, begin));
    zoom.set_end(std::min(static_cast<int64>(length), end));
    if (zoom.end() < 0) {
      LOG(ERROR) << "Bad zoom: " << zoom.end();
      zoom.set_end(length);
    }
  }
  constrainZoom(&zoom, length);

  return zoom;
}

ZoomProto zoom(const ZoomProto& z, Samples<44100> length, double k) {
  return zoom(z, length, (z.begin() + z.end()) / 2, k);
}

}  // namespace

void constrainZoom(ZoomProto* z, Samples<44100> length) {
  DCHECK(length);

  if (z->begin() < 0)
    z->set_begin(0);

  if (z->end() > length || !z->end())
    z->set_end(length);

  Samples<44100> under = SMALLEST_TIME_SAMPLES - (z->end() - z->begin());
  if (under > 0) {
    Samples<44100> end = z->end() + under;
    if (end < length)
      z->set_end(end);
    else
      z->set_begin(z->begin() - under);
  }
}

void zoom(const VirtualFile& f, Samples<44100> length, Samples<44100> time, double k) {
  data::setProto(zoom(data::getProto<ZoomProto>(&f), length, time, k), &f);
}

void zoom(const VirtualFile& f, Samples<44100> length, double k) {
  data::setProto(zoom(data::getProto<ZoomProto>(&f), length, k), &f);
}

void zoomOutFull(const VirtualFile& f, Samples<44100> length) {
  ZoomProto zoom;
  zoom.set_end(length);
  data::setProto(zoom, &f);
}

void zoomTo(const VirtualFile& f, Samples<44100> begin, Samples<44100> end,
            Samples<44100> length) {
  ZoomProto zoom;
  zoom.set_begin(begin);
  zoom.set_end(end);

  constrainZoom(&zoom, length);
  data::setProto(zoom, &f);
}


}  // namespace waveform
}  // namespace widget
}  // namespace rec
