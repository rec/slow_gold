#include <glog/logging.h>

#include "rec/gui/Color.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace gui {
namespace color {

namespace {

uint32 makeARGB(const Color& c) {
  if (c.has_argb())
    return c.argb();

  else if (c.has_rgb())
    return (c.alpha() << 24) | c.rgb();

  else
    return (c.alpha() << 24) | (c.red() << 16) | (c.green() << 8) | c.blue();
}

Colour makeColour(const Color& color) {
  return Colour(makeARGB(color));
}

}  // namespace

Colour get(unsigned int i) {
  static Colour DEFAULT_COLORS[] = {
    Colours::white,
    Colours::lightblue,
    Colours::black
  };

  static int SIZE = arraysize(DEFAULT_COLORS);
  if (i < SIZE)
    return DEFAULT_COLORS[i];

  LOG(ERROR) << "Couldn't get color " << i;
  return DEFAULT_COLORS[arraysize(DEFAULT_COLORS) - 1];
};

Colour get(const Colors& colors, unsigned int i) {
  return i < colors.color_size() ? makeColour(colors.color(i)) : get(i);
}

}  // namespace color
}  // namespace gui
}  // namespace rec
