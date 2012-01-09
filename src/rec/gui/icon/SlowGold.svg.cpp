#include "rec/gui/icon/SlowGold.svg.h"
#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {
namespace icon {

using juce::Drawable;

// Created by the command line:
// new src/rec/gui/icon/SlowGold.svg

Drawable* SlowGold::create() {
  static const char data[] = "<?xml version=\"1.0\" ?>\n"
  "<!-- Generator: Adobe Illustrator 15.1.0, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->\n"
  "<!DOCTYPE svg\n"
  "  PUBLIC '-//W3C//DTD SVG 1.1//EN'\n"
  "  'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'>\n"
  "<svg enable-background=\"new 0 0 612 792\" height=\"792px\" id=\"Layer_1\" version=\"1.1\" viewBox=\"0 0 612 792\" "
  "width=\"612px\" x=\"0px\" xml:space=\"preserve\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/"
  "1999/xlink\" y=\"0px\">\n"
  "  \n"
  "\n"
  "</svg>\n"
  " "
;
  return createBinary<Drawable>(data, arraysize(data), "SlowGold.svg");
};

}  // namespace icon
}  // namespace gui
}  // namespace rec
