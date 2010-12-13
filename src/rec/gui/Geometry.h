#ifndef __REC_GUI_GEOMETRY__
#define __REC_GUI_GEOMETRY__

#include "rec/base/base.h"
#include "rec/gui/Geometry.pb.h"

namespace rec {
namespace gui {

using juce::Rectangle;

inline void drawLine(Graphics& g, const Line& line, const Rectangle<int>& r) {
  drawLine(g, line, r.getX(), r.getY(), r.getRight(), r.getBottom());
}

void drawLine(Graphics& g, const Line& line,
              float sx, float sy, float ex, float ey);


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GEOMETRY__
