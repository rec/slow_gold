#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace widget {
namespace waveform {

ZoomProto zoomIn(const ZoomProto& z, RealTime length, RealTime time) {
  ZoomProto zoom(z);
  RealTime begin = zoom.begin();
  RealTime end = zoom.end();
  if (!end)
    end = length;  // TODO:  delete these?

  RealTime size = end - begin;
  RealTime middle = time;
  zoom.set_begin(juce::jmax(0.0, middle - size / 4.0));
  zoom.set_end(juce::jmin(middle + size / 4.0, length));

  return zoom;
}

ZoomProto zoomOut(const ZoomProto& z, RealTime length) {
  ZoomProto zoom(z);
  RealTime begin = zoom.begin();
  RealTime end = zoom.end();
  if (!end)
    end = length;

  RealTime size = end - begin;
  RealTime middle = begin + (end - begin) / 2.0;
  zoom.set_begin(juce::jmax(0.0, middle - size));
  zoom.set_end(juce::jmin(middle + size, length));

  return zoom;
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
