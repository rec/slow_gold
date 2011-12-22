#include "rec/gui/icon/Crosshairs.svg.h"
#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {
namespace icon {

using juce::Drawable;

// Created by the command line:
// new src/rec/gui/icon/Crosshairs.svg

Drawable* Crosshairs::create() {
  static const char data[] = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
  "<svg xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:cc=\"http://web.resource.org/cc/\" xmlns:rdf=\"http://"
  "www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" "
  "width=\"100\" height=\"100\" id=\"svg2\" version=\"1.0\">\n"
  "  <g id=\"layer\" >\n"
  "    <path style=\"stroke: #ff0000; stroke-width:10;\" d=\"M 50,1 L 50,35 z \" id=\"up\"/>\n"
  "    <path style=\"stroke: #ff0000; stroke-width:10;\" d=\"M 50,65 L 50,100 z \" id=\"down\"/>\n"
  "    <path style=\"stroke: #ff0000; stroke-width:10;\" d=\"M 35,50 L 0,50 z \" id=\"left\"/>\n"
  "    <path style=\"stroke: #ff0000; stroke-width:10;\" d=\"M 100,50 L 65,50 z \" id=\"right\"/>\n"
  "	<circle style=\"stroke:#ff0000; stroke-width:10;\" cx=\"50\" cy=\"50\" r=\"33\" fill=\"none\"/>\n"
  "  </g>\n"
  "</svg> "
;

  return createBinary<Drawable>(data, arraysize(data));
};

}  // namespace icon
}  // namespace gui
}  // namespace rec
