#include "rec/gui/Geometry.h"
#include "rec/util/Math.h"

using namespace rec::util;

namespace rec {
namespace gui {

void drawLine(Graphics& g, const Line& line,
              float sx, float sy, float ex, float ey) {
  float thick = line.thickness();
  if (int dash = line.dashing_size())
    g.drawDashedLine(sx, sy, ex, ey, line.dashing().data(), dash, thick);
  else
    g.drawLine(sx, sy, ex, ey, thick);
}

}  // namespace gui
}  // namespace rec
