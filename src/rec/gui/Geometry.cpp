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

void copy(const Rectangle& from, juce::Rectangle<int>* to) {
  to->setX(from.top_left().x());
  to->setY(from.top_left().y());
  to->setWidth(from.dimensions().x());
  to->setHeight(from.dimensions().y());

}

void copy(const juce::Rectangle<int>& from, Rectangle* to) {
  gui::Point *p = to->mutable_top_left();
  p->set_x(from.getX());
  p->set_y(from.getY());

  p = to->mutable_dimensions();
  p->set_x(from.getWidth());
  p->set_y(from.getHeight());
}

}  // namespace gui
}  // namespace rec
