#include "rec/gui/Geometry.h"
#include "rec/util/Math.h"

using namespace rec::util;

namespace rec {
namespace gui {

void drawLine(Graphics& g, const Line& line,
              float sx, float sy, float ex, float ey) {
  float t = line.thickness();
  if (int d = line.dashing_size())
    g.drawDashedLine(juce::Line<float>(sx, sy, ex, ey), line.dashing().data(), d, t);
  else
    g.drawLine(sx, sy, ex, ey, t);
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

void drawLine(Graphics& g, const Line& line, const juce::Rectangle<int>& r) {
  drawLine(g, line, r.getX(), r.getY(), r.getRight(), r.getBottom());
}

juce::Rectangle<int> copy(const Rectangle& rect) {
  juce::Rectangle<int> r;
  copy(rect, &r);
  return r;
}

Rectangle copy(const juce::Rectangle<int>& rect) {
  Rectangle r;
  copy(rect, &r);
  return r;
}

juce::Rectangle<int> centerSquare(const juce::Rectangle<int>& r) {
  int s = juce::jmin(r.getWidth(), r.getHeight());
  juce::Point<int> c = r.getCentre();
  return juce::Rectangle<int>(c.getX() - s / 2, c.getY() - s / 2, s, s);
}

}  // namespace gui
}  // namespace rec
