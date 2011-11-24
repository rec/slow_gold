#include "rec/gui/Color.h"
#include "rec/base/ArraySize.h"

using namespace juce;

namespace rec {
namespace gui {
namespace color {

uint32 nameToARGB(const string& name, const juce::Colour& dflt) {
  return juce::Colours::findColourForName(str(name), dflt).getARGB();
}

uint32 makeARGB(const Color& c) {
  if (c.has_name()) {
    int argb = nameToARGB(c.name(), juce::Colour());
    if (argb || !nameToARGB(c.name(), juce::Colours::white))
      return argb;
  }

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

static std::pair<Colour*, Colour*> getColours() {
  static Colour COLORS[] = {
    Colours::white,
    Colours::lightblue,
    Colours::seagreen,
    juce::Colour(0xffd3d3d3),
    juce::Colour(0xff809090),
    juce::Colours::red,
    juce::Colours::black,
    juce::Colour(0xff607070),
    // Colours::grey,
    // Colours::blue, //grey
  };
  return std::make_pair(COLORS, COLORS + arraysize(COLORS));
}

Colour get(int i) {
  std::pair<Colour*, Colour*> colours = getColours();
  if (i < colours.second - colours.first)
    return colours.first[i];

  LOG(DFATAL) << "Couldn't get color " << i;
  return colours.second[-1];
};


static Colors getDefaultInternal() {
  Colors colors;
  std::pair<Colour*, Colour*> colours = getColours();
  for (Colour* c = colours.first; c != colours.second; ++c)
    colors.add_color()->set_argb(c->getARGB());
  return colors;
};

const Colors& getDefaultColors() {
  static Colors colors = getDefaultInternal();
  return colors;
}

Colour get(const Colors& colors, int i) {
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
