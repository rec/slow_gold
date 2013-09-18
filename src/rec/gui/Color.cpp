#include "rec/gui/Color.h"
#include "rec/base/ArraySize.h"

using namespace juce;

namespace rec {
namespace gui {
namespace color {

namespace {

uint32 nameToARGB(const string& name, const juce::Colour& dflt) {
  return juce::Colours::findColourForName(str(name), dflt).getARGB();
}

Colour COLOURS[] = {
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

std::pair<Colour*, Colour*> getColours() {
  return std::make_pair(COLOURS, COLOURS + arraysize(COLOURS));
}

Colour get(int i) {
  if (i < std::end(COLOURS) - std::begin(COLOURS))
    return COLOURS[i];

  LOG(DFATAL) << "Couldn't get color " << i;
  return std::end(COLOURS)[-1];
};


Colors getDefaultInternal() {
  Colors colors;
  for (auto& c: COLOURS)
    colors.add_color()->set_argb(c.getARGB());
  return colors;
};

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

const Colors& getDefaultColors() {
  static Colors colors = getDefaultInternal();
  return colors;
}

Colour get(const Colors& colors, int i) {
  return i < colors.color_size() ? makeColour(colors.color(i)) : get(i);
}

}  // namespace color
}  // namespace gui
}  // namespace rec
