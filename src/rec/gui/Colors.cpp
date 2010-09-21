#include "rec/gui/Colors.h"

namespace rec {
namespace gui {
namespace color {

namespace {

Colour DEFAULT_COLORS[] = {
  Colours::white,
  Colours::lightblue,
  Colours::black
};

uint32 makeARGB(const Color& c) {
  if (c.has_argb())
    return c.argb();

  else if (c.has_rgb())
    return (c.alpha() << 24) | c.rgb();

  else
    return (c.alpha() << 24) | (c.red() << 16) | (c.green() << 8) | c.blue();
}

Colour makeColor(const Color& color) {
  return Colour(makeARGB(color));
}

}  // namespace


Colour get(const Colors& colors, unsigned int index) {
  if (index < colors.color_size())
    return makeColor(colors.color(index)));

  if (index < arraysize(DEFAULT_COLORS))
    return DEFAULT_COLORS[index];

  LOG(ERROR) << "Couldn't get color " << index;
  return DEFAULT_COLORS[arraysize(DEFAULT_COLORS) - 1];
}

void set(const Colors& colors, unsigned int index, Graphics* g) {
  g->setColour(getColor(colors, index));
}


}  // namespace color
}  // namespace gui
}  // namespace rec
