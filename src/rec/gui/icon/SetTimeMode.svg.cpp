#include "rec/gui/icon/SetTimeMode.svg.h"
#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {
namespace icon {

using juce::Drawable;

// Created by the command line:
// new src/rec/gui/icon/SetTimeMode.svg

Drawable* SetTimeMode::create() {
  static const char data[] = "<?xml version=\"1.0\" ?>\n"
  "<svg height=\"100\" id=\"svg2\" version=\"1.0\" width=\"100\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:cc=\"http://"
  "web.resource.org/cc/\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:rdf=\"http://www.w3.org/1999/02/"
  "22-rdf-syntax-ns#\" xmlns:svg=\"http://www.w3.org/2000/svg\">\n"
  "  \n"
  "  \n"
  "  <g id=\"layer\">\n"
  "    \n"
  "    \n"
  "    <path d=\"M 50,1 L 50,35 z \" id=\"up\" style=\"stroke: #ff0000; stroke-width:10;\"/>\n"
  "    \n"
  "    \n"
  "    <path d=\"M 50,65 L 50,100 z \" id=\"down\" style=\"stroke: #ff0000; stroke-width:10;\"/>\n"
  "    \n"
  "    \n"
  "    <path d=\"M 35,50 L 0,50 z \" id=\"left\" style=\"stroke: #ff0000; stroke-width:10;\"/>\n"
  "    \n"
  "    \n"
  "    <path d=\"M 100,50 L 65,50 z \" id=\"right\" style=\"stroke: #ff0000; stroke-width:10;\"/>\n"
  "    \n"
  "	\n"
  "    <circle cx=\"50\" cy=\"50\" fill=\"none\" r=\"33\" style=\"stroke:#ff0000; stroke-width:10;\"/>\n"
  "    \n"
  "  \n"
  "  </g>\n"
  "  \n"
  "\n"
  "</svg>\n"
  " "
;
  return createBinary<Drawable>(data, arraysize(data), "SetTimeMode.svg");
};

}  // namespace icon
}  // namespace gui
}  // namespace rec
