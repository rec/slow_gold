#pragma once

#include "rec/base/base.h"
#include "rec/gui/Geometry.pb.h"

namespace rec {
namespace gui {

void drawLine(Graphics& g, const Line& line,
              float sx, float sy, float ex, float ey);

void drawLine(Graphics& g, const Line& line, const juce::Rectangle<int>& r);

void copy(const Rectangle& from, juce::Rectangle<int>* to);
void copy(const juce::Rectangle<int>& from, Rectangle* to);

juce::Rectangle<int> copy(const Rectangle& rect);
Rectangle copy(const juce::Rectangle<int>& rect);

inline void clear(juce::Rectangle<int>* r) {
  r->setX(0);
  r->setY(0);
  r->setWidth(0);
  r->setHeight(0);
}

template <typename Number>
void addInto(const juce::Rectangle<Number>& from, juce::Rectangle<Number>* to) {
  int x = std::min(to->getX(), from.getX());
  int width = std::max(to->getRight(), from.getRight()) - x;
  int y = std::min(to->getY(), from.getY());
  int height = std::max(to->getBottom(), from.getBottom()) - y;
  to->setX(x);
  to->setY(y);
  to->setWidth(width);
  to->setHeight(height);
}

juce::Rectangle<int> centerSquare(const juce::Rectangle<int>& rect);

String toString(const Rectangle&);
String toString(const juce::Rectangle<int>&);

String toString(int x, int y, bool isDimensions = false);
String toString(const Point& p, bool isDimensions = false);

}  // namespace gui
}  // namespace rec

