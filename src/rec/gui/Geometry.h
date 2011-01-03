#ifndef __REC_GUI_GEOMETRY__
#define __REC_GUI_GEOMETRY__

#include "rec/base/base.h"
#include "rec/gui/Geometry.pb.h"

namespace rec {
namespace gui {

void drawLine(Graphics& g, const Line& line,
              float sx, float sy, float ex, float ey);

inline void drawLine(Graphics& g, const Line& line, const juce::Rectangle<int>& r) {
  drawLine(g, line, r.getX(), r.getY(), r.getRight(), r.getBottom());
}

void copy(const Rectangle& from, juce::Rectangle<int>* to);
void copy(const juce::Rectangle<int>& from, Rectangle* to);

inline juce::Rectangle<int> copy(const Rectangle& rect) {
  juce::Rectangle<int> r;
  copy(rect, &r);
  return r;
}

inline Rectangle copy(const juce::Rectangle<int>& rect) {
  Rectangle r;
  copy(rect, &r);
  return r;
}

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GEOMETRY__
