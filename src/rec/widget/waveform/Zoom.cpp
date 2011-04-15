#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace widget {
namespace waveform {

ZoomProto zoomIn(const ZoomProto& z, int length, double time) {
  ZoomProto zoom(z);
  double begin = zoom.begin();
  double end = zoom.end();
  if (!end)
    end = length;

  double size = end - begin;
  double middle = time;
  zoom.set_begin(juce::jmax(0.0, middle - size / 4.0));
  zoom.set_end(juce::jmin(middle + size + 4.0, length));

  return zoom;
}

ZoomProto zoomOut(const ZoomProto& z, int length) {
  ZoomProto zoom(z);
  double begin = zoom.begin();
  double end = zoom.end();

  if (!end)
    end = length;
  double size = end - begin;
  double middle = begin + (end - begin) / 2.0;
  zoom.set_begin(juce::jmax(0.0, middle - size));
  zoom.set_end(juce::jmin(middle + size, length));

  return zoom;
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
