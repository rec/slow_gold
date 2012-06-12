#include "rec/widget/waveform/Zoom.h"

#include "rec/audio/Audio.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

static const double POWER = 4.0;
static const double ZOOM_INCREMENT = 0.3;

double zoomFunction(double increment) {
  return pow(POWER, -increment);
}

Zoom makeZoom(const Zoom& z, SampleTime length, SampleTime t,
              double k) {
  k = zoomFunction(k * ZOOM_INCREMENT);
  // DCHECK_LE(z.begin(), z.end());
  Zoom zoom(z);
  SampleTime b = zoom.begin();
  SampleTime e = zoom.has_end() ? zoom.end() : length.get();

  if (k >= 1.0 || k * (e - b) >= audio::minimumFileSize()) {
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

Zoom makeZoom(const Zoom& z, SampleTime length, double k) {
  return makeZoom(z, length, (z.begin() + z.end()) / 2, k);
}

}  // namespace

void constrainZoom(Zoom* z, SampleTime length) {
  DCHECK(length);

  if (z->begin() < 0)
    z->set_begin(0);

  if (z->end() > length || !z->has_end())
    z->set_end(length);

  SampleTime under = audio::minimumFileSize() - (z->end() - z->begin());
  if (under > 0) {
    SampleTime end = z->end() + under;
    if (end < length)
      z->set_end(end);
    else
      z->set_begin(z->begin() - under);
  }
}

void zoomScaleAt(const VirtualFile& f, SampleTime length, SampleTime time, double k) {
  Viewport vp(data::getProto<Viewport>(&f));
  vp.mutable_zoom()->CopyFrom(makeZoom(vp.zoom(), length, time, k));
  data::setProto(vp, &f);
}

void zoomScale(const VirtualFile& f, SampleTime length, double k) {
  Viewport vp(data::getProto<Viewport>(&f));
  vp.mutable_zoom()->CopyFrom(makeZoom(vp.zoom(), length, k));
  data::setProto(vp, &f);
}

void zoomOutFull(const VirtualFile& f, SampleTime length) {
  Viewport vp(data::getProto<Viewport>(&f));
  vp.mutable_zoom()->set_begin(0);
  vp.mutable_zoom()->set_end(length);
  data::setProto(vp, &f);
}

void zoomTo(const VirtualFile& f, SampleTime begin, SampleTime end,
            SampleTime length) {
  Viewport vp(data::getProto<Viewport>(&f));
  Zoom* zoom = vp.mutable_zoom();
  zoom->set_begin(begin);
  zoom->set_end(end);

  constrainZoom(zoom, length);
  data::setProto(vp, &f);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
