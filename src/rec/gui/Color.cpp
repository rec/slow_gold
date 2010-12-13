#include <glog/logging.h>

#include "rec/gui/Color.h"
#include "rec/base/ArraySize.h"

using namespace juce;

namespace rec {
namespace gui {
namespace color {

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


static Colors getDefaultInternal() {
  static Colour DEFAULT_COLORS[] = {
    Colours::white,
    Colours::lightblue,
    Colours::black
  };

  Colors colors;
  for (int i = 0; i < arraysize(DEFAULT_COLORS); ++i)
    colors.add_color()->set_argb(DEFAULT_COLORS[i].getARGB());
  return colors;
};

const Colors& getDefaultColors() {
  static Colors colors = getDefaultInternal();
  return colors;
}

Colour get(const Colors& colors, unsigned int i) {
  return i < colors.color_size() ? makeColour(colors.color(i)) : get(i);
}

void prepare(const Colors& colors, Graphics* g) {
  g->fillAll(get(colors, 0));
  g->setColour(get(colors, 1));
}

static void push(const ColorArg& colorArg, Colors* colors) {
  colors->add_color()->set_argb(colorArg);
}

Colors makeColors() {
  Colors colors;
  return colors;
}

Colors makeColors(CCA a1) {
  Colors colors;
  push(a1, &colors);
  return colors;
}

Colors makeColors(CCA a1, CCA a2) {
  Colors colors;
  push(a1, &colors);
  push(a2, &colors);
  return colors;
}

Colors makeColors(CCA a1, CCA a2, CCA a3) {
  Colors colors;
  push(a1, &colors);
  push(a2, &colors);
  push(a3, &colors);
  return colors;
}

Colors makeColors(CCA a1, CCA a2, CCA a3, CCA a4) {
  Colors colors;
  push(a1, &colors);
  push(a2, &colors);
  push(a3, &colors);
  push(a4, &colors);
  return colors;
}

Colors makeColors(CCA a1, CCA a2, CCA a3, CCA a4, CCA a5) {
  Colors colors;
  push(a1, &colors);
  push(a2, &colors);
  push(a3, &colors);
  push(a4, &colors);
  push(a5, &colors);
  return colors;
}

Colors makeColors(CCA a1, CCA a2, CCA a3, CCA a4, CCA a5, CCA a6) {
  Colors colors;
  push(a1, &colors);
  push(a2, &colors);
  push(a3, &colors);
  push(a4, &colors);
  push(a5, &colors);
  push(a6, &colors);
  return colors;
}

Colors makeColors(CCA a1, CCA a2, CCA a3, CCA a4, CCA a5, CCA a6, CCA a7) {
  Colors colors;
  push(a1, &colors);
  push(a2, &colors);
  push(a3, &colors);
  push(a4, &colors);
  push(a5, &colors);
  push(a6, &colors);
  push(a7, &colors);
  return colors;
}

Colors makeColors(CCA a1, CCA a2, CCA a3, CCA a4, CCA a5, CCA a6, CCA a7, CCA a8) {
  Colors colors;
  push(a1, &colors);
  push(a2, &colors);
  push(a3, &colors);
  push(a4, &colors);
  push(a5, &colors);
  push(a6, &colors);
  push(a7, &colors);
  push(a8, &colors);
  return colors;
}


}  // namespace color
}  // namespace gui
}  // namespace rec
